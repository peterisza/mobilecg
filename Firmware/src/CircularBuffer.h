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
		full=false;
	}

	int rpos;
	int wpos;
	bool full;
};

/**
 * Circular buffer class.
 *
 * It's elements can be accessed both by their relative and their absolute position.
 *
 */
template <typename Type, int vectorSizeMax, bool useMemcpy=false, bool overwrite=true> class CircularBuffer
{
    private:
        Type vector[vectorSizeMax];
        int vectorSize;
        CircularBufferState state;


        inline int wrap(int a) const{
            if (a>=vectorSize)
                return a-vectorSize;
            else
            	return a;
        }

        inline void wrapInc(int &a) const{
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

        	vectorSize=newSize;
        	clear();
        }

        ~CircularBuffer(){
        }

        int maxSize() const {
        	return vectorSizeMax;
        }

        int size() const{
            return vectorSize;
        }

        bool isEmpty(){
            return (state.full==false && state.rpos==state.wpos);
        }

        bool isFull(){
            return state.full;
        }

        void clear(){
            state.clear();
        }

        int used() const {
            if (state.full)
                return vectorSize;
            else if (state.wpos>=state.rpos){
                return state.wpos-state.rpos;
            } else {
                return vectorSize+state.wpos-state.rpos;
            }
        }

        int free() const {
            return vectorSize-used();
        }

        Type &operator[](const int index){
            register int realIndex=wrap(state.rpos+index);
            return vector[realIndex];
        }

        Type &getElement(const int absoluteIndex){
            return vector[absoluteIndex];
        }

        void add(const Type &t){
            vector[state.wpos]=t;

            if (state.full){
                wrapInc(state.wpos);
                wrapInc(state.rpos);
            } else {
                wrapInc(state.wpos);
                if (state.wpos==state.rpos){
                	state.full=true;
                }
            }
        }

        void add(const Type *data, int cnt){
            if (cnt==0)
                return;

            if (cnt > vectorSize){
            	data += cnt - vectorSize;
            	cnt = vectorSize;
            }

            state.full = free() <= cnt;

            if (!overwrite){
            	cnt=free();
            }

            while (cnt){
            	int copySize = std::min(vectorSize - state.wpos, cnt);
            	if (useMemcpy){
            		//Memcpy can be much faster depending on your data size,
            		//but not works with custom operator =
            		memcpy((char*)&vector[state.wpos], (const char*)data, copySize);
            		state.wpos+=copySize;
            		data+=copySize;
            	} else {
            		for (; state.wpos<copySize; state.wpos++, data++)
            			vector[state.wpos] = *data;
            	}

            	state.wpos = wrap(state.wpos);
            	cnt -= copySize;
            }

            if (state.full)
            	state.rpos=state.wpos;
        }

        Type get(){
            Type result=vector[state.rpos];

            if (!state.full && state.wpos==state.rpos){
                return result;
            }

            wrapInc(state.rpos);
            state.full=false;

            return result;
        }

        int get(Type *dest, int cnt){
        	int toRead = std::min(cnt, used());

        	cnt = toRead;
        	while (cnt){
        		int copySize = std::min(vectorSize - state.rpos, cnt);
        		if (useMemcpy){
        			//Memcpy can be much faster depending on your data size,
        			//but not works with custom operator =
					memcpy((char*)dest, (const char*)&vector[state.rpos], copySize);
					state.rpos+=copySize;
					dest+=copySize;
				} else {
					for (; state.rpos<copySize; state.rpos++, dest++)
						*dest = vector[state.rpos];
				}

        		state.rpos = wrap(state.rpos);
				cnt -= copySize;
        	}

        	return toRead;
        }

        int getContinousReadBuffer(Type *&buffer){
        	int blockSize=std::min(used(), vectorSize - state.rpos);
        	buffer = &vector[state.rpos];

        	return blockSize;
        }

        int getContinousWriteBuffer(Type *&buffer){
        	int blockSize=std::min(free(), vectorSize - state.wpos);
        	buffer = &vector[state.wpos];

        	return blockSize;
        }

        void added(int n){
        	state.wpos = wrap(state.wpos + n);
        }

        void skip(int n){
        	if (n==0)
        		return;

        	n = std::min(n, used());
        	state.rpos = wrap(state.rpos + n);
        	state.full=false;
        }

        const Type *constData(){
            return vector;
        }

        void fill(const Type &data){
            for (int a=0; a<size(); a++)
                vector[a]=data;
        }
};

#endif // CIRCULARBUFFER_H
