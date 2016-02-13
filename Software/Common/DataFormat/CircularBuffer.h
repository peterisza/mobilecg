/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <algorithm>
#include <cstring>

struct CircularBufferState{
	CircularBufferState(){
		clear();
	}

	void clear(){
		rpos=0;
		wpos=0;
	}

	volatile int rpos;
	volatile int wpos;
};

/**
 * Circular buffer class.
 *
 * It's elements can be accessed both by their relative and their absolute position.
 *
 */
template <typename Type, int vectorSizeMax, bool useMemcpy=false> class CircularBuffer
{
    private:
        Type vector[vectorSizeMax+1];
        int vectorSize;
        CircularBufferState state;


        inline int wrap(int a) const{
            if (a>=vectorSize)
                return a-vectorSize;
            else
            	return a;
        }

        inline void wrapInc(volatile int &a) {
            a=wrap(a+1);
        }

    public:
        CircularBufferState backup(){
        	return state;
        }

        void restore(const CircularBufferState &istate){
        	this->state=istate;
        }

        CircularBuffer(){
        	vectorSize = vectorSizeMax;
            clear();
        }

        void resize(int newSize){
        	if (newSize>vectorSizeMax)
        		newSize=vectorSizeMax;

        	vectorSize=newSize+1;
        	clear();
        }

        ~CircularBuffer(){
        }

        int maxSize() const {
        	return vectorSizeMax-1;
        }

        int size() const{
            return vectorSize-1;
        }

        bool isEmpty(){
            return state.rpos==state.wpos;
        }

        bool isFull(){
            return wrap(state.wpos+1)==state.rpos;
        }

        void clear(){
            state.clear();
        }

        int used() const {
            if (state.wpos>=state.rpos){
                return state.wpos-state.rpos;
            } else {
                return vectorSize+state.wpos-state.rpos;
            }
        }

        int free() const {
            return vectorSize-1-used();
        }

        Type &operator[](const int index){
            return vector[wrap(state.rpos+index)];
        }

        Type &getElement(const int absoluteIndex){
            return vector[absoluteIndex];
        }

        void add(const Type &t){
            if (isFull())
            	return;

            vector[state.wpos]=t;
			wrapInc(state.wpos);
        }

        void add(const Type *data, int cnt){
        	const int f=free();
            if (f <= cnt){
                cnt=f;
            }

            while (cnt){
            	int copySize = std::min(vectorSize - state.wpos, cnt);
            	if (useMemcpy){
            		// Memcpy can be much faster depending on your data size,
            		// but doesn't work with a custom assignment operator.
            		memcpy((char*)&vector[state.wpos], (const char*)data, copySize*sizeof(Type));
            		state.wpos+=copySize;
            		data+=copySize;
            	} else {
            		for (int i=0; i<copySize; ++i, ++state.wpos, ++data)
            			vector[state.wpos] = *data;
            	}

            	state.wpos = wrap(state.wpos);
            	cnt -= copySize;
            }
        }

        Type get(){
            Type result=vector[state.rpos];

            if (isEmpty()){
                return result;
            }

            wrapInc(state.rpos);
            return result;
        }

        int get(Type *dest, int cnt){
        	int toRead = std::min(cnt, used());

        	cnt=toRead;
        	while (cnt){
        		int copySize = std::min(vectorSize - state.rpos, cnt);
        		if (useMemcpy){
        			// Memcpy can be much faster depending on your data size,
        			// but doesn't work with a custom assignment operator.
					memcpy((char*)dest, (const char*)&vector[state.rpos], copySize*sizeof(Type));
					state.rpos+=copySize;
					dest+=copySize;
				} else {
					for (int i=0; i<copySize; ++i, ++state.rpos, ++dest)
						*dest = vector[state.rpos];
				}

        		state.rpos = wrap(state.rpos);
				cnt -= copySize;
        	}

        	return toRead;
        }

        int getContinuousReadBuffer(Type *&buffer){
        	int blockSize=std::min(used(), vectorSize - state.rpos);
        	buffer = &vector[state.rpos];

        	return blockSize;
        }

        int getContinuousWriteBuffer(Type *&buffer){
        	int blockSize=std::min(free(), vectorSize - state.wpos);
        	buffer = &vector[state.wpos];

        	return blockSize;
        }

        void added(int n){
        	int wasFree=free();
        	state.wpos = wrap(state.wpos + n);
        	if (wasFree<n){
        		state.rpos=wrap(state.wpos+1);
        	}
        }

        void skip(int n){
        	n = std::min(n, used());
        	state.rpos = wrap(state.rpos + n);
        }

        const Type *constData(){
            return vector;
        }

        void fill(const Type &data){
            for (int a=0; a<vectorSize; a++)
                vector[a]=data;
        }
};

#endif // CIRCULARBUFFER_H
