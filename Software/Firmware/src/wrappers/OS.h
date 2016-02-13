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

			void *userData;
		public:
			Task(const char *name, TaskFunction iCallback, uint32_t stackSize=512, void *userData=NULL, osPriority priority = osPriorityNormal);

			void *getUserData();
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
