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
 
#include "OS.h"

using namespace OS;

Task::Task(const char *name, TaskFunction iCallback, uint32_t stackSize, void *iUserData, osPriority priority): def{ name, &exec_internal, priority, 0, stackSize}{
	this->callback = iCallback;
	this->userData = iUserData;
	tid = osThreadCreate(&def, this);
}

void *Task::getUserData(){
	return userData;
}

void Task::exec_internal(const void *inst){
	Task * task = const_cast<Task *>((const Task *)inst);
	task->callback(*task);
}

void OS::run(){
	osKernelStart();
}

Mutex::Mutex(){
	sem = xSemaphoreCreateMutex();
}

Mutex::~Mutex(){
	vSemaphoreDelete(sem);
}

bool Mutex::lock(time_t timeout){
	return xSemaphoreTake(sem, timeout == TIME_INF ? portMAX_DELAY : timeout / portTICK_PERIOD_MS);
}

void Mutex::unlock(){
	xSemaphoreGive(sem);
}

MutexLocker::MutexLocker(Mutex &mutex){
	m=&mutex;
	m->lock();
}

MutexLocker::~MutexLocker(){
	m->unlock();
}

Event::Event(){
	sem = xSemaphoreCreateBinary();

}

Event::~Event(){
	vSemaphoreDelete(sem);
}

void Event::reset(){
	xQueueReset(sem);
	xSemaphoreTake(sem,0);
}

bool Event::wait(time_t timeout, bool doReset){
	if (doReset)
		reset();
	return xSemaphoreTake(sem, timeout == TIME_INF ? portMAX_DELAY : timeout / portTICK_PERIOD_MS);
}

void Event::signal(){
	xSemaphoreGive(sem);
}
