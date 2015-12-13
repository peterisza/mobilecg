#include <OS.h>
#include <GPIO.h>

GPIO led1('B', 6);
GPIO led2('B', 7);

TASK(mainTask, [] (OS::Task &task) {
	UNUSED(task);

	while(1){
		led1.on();
		led2.off();

		OS::sleep(500);

		led1.off();
		led2.on();

		OS::sleep(500);
	}
});


int main(){
	OS::run();
}
