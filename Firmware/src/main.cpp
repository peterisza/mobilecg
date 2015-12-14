#include <OS.h>
#include <GPIO.h>
extern "C"{
#include "SS1BTPS.h"             /* Main SS1 Bluetooth Stack Header.          */
#include "BTPSKRNL.h"            /* BTPS Kernel Header.                       */
#include "BTVSAPI.h"             /* Vendror Specific header.                  */
#include "HCITRANS.h"
}

GPIO led1('B', 6);
GPIO led2('B', 7);

BTPS_Initialization_t         BTPS_Initialization;
HCI_DriverInformation_t       HCI_DriverInformation;
HCI_HCILLConfiguration_t      HCILLConfig;
HCI_Driver_Reconfigure_Data_t DriverReconfigureData;

void mainTaskCallback (OS::Task &task) {
	UNUSED(task);

	/*HCI_DRIVER_SET_COMM_INFORMATION(&HCI_DriverInformation, 1, 123, cpHCILL_RTS_CTS);
	   HCI_DriverInformation.DriverInformation.COMMDriverInformation.InitializationDelay = 100;

	 BTPS_Initialization.MessageOutputCallback = 0;

	 BTPS_Init(&BTPS_Initialization);
	 HCI_Command_Supported(0, HCI_SUPPORTED_COMMAND_WRITE_DEFAULT_LINK_POLICY_BIT_NUMBER);
	   if((InitializeApplication(&HCI_DriverInformation, &BTPS_Initialization)) > 0)
	   {

	   }*/

	while(1){
		led1.on();
		led2.off();

		OS::sleep(500);

		led1.off();
		led2.on();

		OS::sleep(500);
	}
}

TASK(mainTask,mainTaskCallback);


int main(){
	OS::run();
}
