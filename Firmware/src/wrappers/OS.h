/*
 * OS.h
 *
 *  Created on: 2015. dec. 13.
 *      Author: xdever
 */

#ifndef SRC_WRAPPERS_OS_H_
#define SRC_WRAPPERS_OS_H_

#include <cstdint>
#include <helpers.h>
#include <time.h>

extern "C"{
	#include "cmsis_os.h"
}

#define TASK(NAME,args...) OS::Task NAME(#NAME, args)

namespace OS{

	class Task{
		private:
			osThreadId freertosThread;
			const osThreadDef_t def;
			osThreadId tid;

			typedef void (*TaskFunction)(Task &task);
			TaskFunction callback;

		public:
			Task(const char *name, TaskFunction iCallback, uint32_t stackSize=512, osPriority priority = osPriorityNormal);
		private:
			static void exec_internal(const void *);
	};

	void run();

	inline void sleep(const TickType_t val){
		vTaskDelay(val);
	}

	class Mutex{
		private:
			SemaphoreHandle_t sem;
		public:
			Mutex();
			~Mutex();

			bool lock(time_t timeout = TIME_INF);
			void unlock();
	};

	class Event{
		private:
			SemaphoreHandle_t sem;
		public:
			Event();
			~Event();

			bool wait(time_t timeout = TIME_INF, bool doReset=false);
			void reset();
			void signal();
	};

	class MutexLocker{
		private:
			Mutex *m;
		public:
			MutexLocker(Mutex &mutex);
			~MutexLocker();
	};
}

#endif /* SRC_WRAPPERS_OS_H_ */
