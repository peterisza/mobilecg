#include "OS.h"

using namespace OS;

Task::Task(const char *name, TaskFunction iCallback, uint32_t stackSize, osPriority priority): def{ name, &exec_internal, priority, 0, stackSize}{
	this->callback = iCallback;
	tid = osThreadCreate(&def, this);
}

void Task::exec_internal(const void *inst){
	Task * task = const_cast<Task *>((const Task *)inst);
	task->callback(*task);
}

void OS::run(){
	osKernelStart();
}
