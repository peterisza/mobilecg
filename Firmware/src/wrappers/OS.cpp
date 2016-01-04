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
