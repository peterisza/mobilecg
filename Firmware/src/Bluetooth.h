/*
 * Bluetooth.h
 *
 *  Created on: 2015. dec. 21.
 *      Author: xdever
 */

#ifndef SRC_BLUETOOTH_H_
#define SRC_BLUETOOTH_H_

extern "C" {
	#include <HCITRANS.h>
	#include <BTPSKRNL.h>
	#include <GAPAPI.h>
	#include <HCIAPI.h>
	#include <L2CAPAPI.h>
	#include <BSCAPI.h>
}

#include <cstdint>

class Bluetooth {
	private:
		BTPS_Initialization_t         BTPS_Initialization;
		HCI_DriverInformation_t       HCI_DriverInformation;
		HCI_HCILLConfiguration_t      HCILLConfig;
		HCI_Driver_Reconfigure_Data_t DriverReconfigureData;

		BD_ADDR_t           NullADDR;

		static const int MAX_SUPPORTED_LINK_KEYS = 1;

	   /* The following type definition represents the container type which */
	   /* holds the mapping between Bluetooth devices (based on the BD_ADDR)*/
	   /* and the Link Key (BD_ADDR <-> Link Key Mapping).                  */
		typedef struct _tagLinkKeyInfo_t
		{
		   BD_ADDR_t  BD_ADDR;
		   Link_Key_t LinkKey;
		} LinkKeyInfo_t;

		LinkKeyInfo_t linkKeyInfo[MAX_SUPPORTED_LINK_KEYS];

		unsigned int bluetoothStackID;

		static const int VENDOR_BAUD_RATE = 115200;
		static int displayCallback(int length, char *message);

		int deleteLinkKey(BD_ADDR_t BD_ADDR);
		int initializeApplication();
		int openStack();
		int setConnect();
		int setDisc();
		int setPairable();
		int closeStack();

		static void BTPSAPI GAP_Event_Callback(unsigned int BluetoothStackID, GAP_Event_Data_t *GAP_Event_Data, unsigned long CallbackParameter);
		static void BTPSAPI HCI_Event_Callback(unsigned int BluetoothStackID, HCI_Event_Data_t *HCI_Event_Data, unsigned long CallbackParameter);

		void gapEventCallback(unsigned int bluetoothStackID, GAP_Event_Data_t *GAP_Event_Data);
		void hciEventCallback(unsigned int bluetoothStackID, HCI_Event_Data_t *HCI_Event_Data);
	private:
		const char *name;
		uint8_t macAddr[6];

	public:
		Bluetooth(const char *macAddr, const char *name);
		virtual ~Bluetooth();
		void init();
};

#endif /* SRC_BLUETOOTH_H_ */
