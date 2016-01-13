/*
 * Bluetooth.h
 *
 *  Created on: 2015. dec. 21.
 *      Author: xdever
 *
 *  This file is heavily based on SPPDemo.c example
 *  from Bluetopia stack.
 *
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
	#include <SPPAPI.h>
}

#include <cstdint>
#include <time.h>
#include <CircularBuffer.h>
#include <OS.h>

class Bluetooth {
	private:
		BTPS_Initialization_t         BTPS_Initialization;
		HCI_DriverInformation_t       HCI_DriverInformation;
		HCI_HCILLConfiguration_t      HCILLConfig;
		HCI_Driver_Reconfigure_Data_t DriverReconfigureData;

		GAP_IO_Capability_t 		IOCapability;
		Boolean_t           OOBSupport;
		Boolean_t           MITMProtection;
		Boolean_t           Connected;

		BD_ADDR_t           NullADDR;
		BD_ADDR_t           CurrentRemoteBD_ADDR;

		int                 ServerPortID;
		int					SerialPortID;

		DWord_t             SPPServerSDPHandle;
		Word_t              Connection_Handle;

		char tmpBuffer[16];

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

		static const int VENDOR_BAUD_RATE = 1500000L;
		static int displayCallback(int length, char *message);

		int deleteLinkKey(BD_ADDR_t BD_ADDR);
		int initializeApplication();
		int openStack();
		int setPairable();
		int closeStack();
		int openServer(unsigned int port);
		int setDiscoverabilityMode(GAP_Discoverability_Mode_t DiscoverabilityMode);
		int setClassOfDevice(unsigned int classOfDev);
		int setConnectabilityMode(GAP_Connectability_Mode_t ConnectableMode);
		int setPairabilityMode(GAP_Pairability_Mode_t PairabilityMode);
		int pinCodeResponse(const char *pinCode);

		bool sendAvailable();

		static void BTPSAPI GAP_Event_Callback(unsigned int BluetoothStackID, GAP_Event_Data_t *GAP_Event_Data, unsigned long CallbackParameter);
		static void BTPSAPI HCI_Event_Callback(unsigned int BluetoothStackID, HCI_Event_Data_t *HCI_Event_Data, unsigned long CallbackParameter);
		static void BTPSAPI SPP_Event_Callback(unsigned int BluetoothStackID, SPP_Event_Data_t *SPP_Event_Data, unsigned long CallbackParameter);

		void gapEventCallback(unsigned int bluetoothStackID, GAP_Event_Data_t *GAP_Event_Data);
		void hciEventCallback(unsigned int bluetoothStackID, HCI_Event_Data_t *HCI_Event_Data);
		void sppEventCallback(unsigned int bluetoothStackID, SPP_Event_Data_t *SPP_Event_Data);
	private:
		const char *name;
		char pin[17];

		CircularBuffer<char, 2048, true> writeBuffer;
		OS::Mutex writeBufferMutex;

		OS::Event bufferHasSpaceEvent;
		OS::Event readyToSendEvent;

		OS::Task sendTask;

		bool running;
		static void sendTaskCallbackStatic(OS::Task &task);

		void sendTaskCallback();
	public:
		Bluetooth(const char *name);
		virtual ~Bluetooth();
		void init();
		void setPin(const char *pin);

		bool isConnected();
		int send(const char *data, int size=0, time_t timeout=TIME_INF);
};

#endif /* SRC_BLUETOOTH_H_ */
