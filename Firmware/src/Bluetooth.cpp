/*
 * Bluetooth.cpp
 *
 *  Created on: 2015. dec. 21.
 *      Author: xdever
 */

#include "Bluetooth.h"
#include <cstring>
#include <helpers.h>

Bluetooth::Bluetooth(const char *i_macAddr, const char *i_name) {
	this->name = i_name;
	memcpy(this->macAddr, i_macAddr, 6);
}

Bluetooth::~Bluetooth() {

}

int Bluetooth::displayCallback(int length, char *message){
	UNUSED(length);
	UNUSED(message);
    return TRUE;
}

/* The following function is used to initialize the application      */
  /* instance.  This function should open the stack and prepare to     */
  /* execute commands based on user input.  The first parameter passed */
  /* to this function is the HCI Driver Information that will be used  */
  /* when opening the stack and the second parameter is used to pass   */
  /* parameters to BTPS_Init.  This function returns the               */
  /* BluetoothStackID returned from BSC_Initialize on success or a     */
  /* negative error code (of the form APPLICATION_ERROR_XXX).          */
int Bluetooth::initializeApplication()
{
  int ret_val = -1;

  /* Initiailize some defaults.                                        */
  /*SerialPortID           = 0;
  UI_Mode                = UI_MODE_SELECT;
  LoopbackActive         = FALSE;
  DisplayRawData         = FALSE;
  AutomaticReadActive    = FALSE;
  NumberofValidResponses = 0;*/

 /* Try to Open the stack and check if it was successful.          */
 if(!openStack())
 {
	/* The stack was opened successfully.  Now set some defaults.  */

	/* First, attempt to set the Device to be Connectable.         */
	ret_val = setConnect();

	/* Next, check to see if the Device was successfully made      */
	/* Connectable.                                                */
	if(!ret_val)
	{
	   /* Now that the device is Connectable attempt to make it    */
	   /* Discoverable.                                            */
	   ret_val = setDisc();

	   /* Next, check to see if the Device was successfully made   */
	   /* Discoverable.                                            */
	   if(!ret_val)
	   {
		  /* Now that the device is discoverable attempt to make it*/
		  /* pairable.                                             */
		  ret_val = setPairable();
		  if(!ret_val)
		  {
			 /* Attempt to register a HCI Event Callback.          */
			 ret_val = HCI_Register_Event_Callback(bluetoothStackID, HCI_Event_Callback, (unsigned long)this);
			 if(ret_val > 0)
			 {
				/* Assign a NULL BD_ADDR for comparison.           */
				ASSIGN_BD_ADDR(NullADDR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

				/* Return success to the caller.                   */
				ret_val = (int)bluetoothStackID;
			 }

		  }

	   }

	}

	/* In some error occurred then close the stack.                */
	if(ret_val < 0)
	{
	   /* Close the Bluetooth Stack.                               */
	   closeStack();
	}
 }
 else
 {
	/* There was an error while attempting to open the Stack.      */
	return -1;
 }
}

/* The following function is responsible for placing the Local       */
/* Bluetooth Device into Connectable Mode.  Once in this mode the    */
/* Device will respond to Page Scans from other Bluetooth Devices.   */
/* This function requires that a valid Bluetooth Stack ID exists     */
/* before running.  This function returns zero on success and a      */
/* negative value if an error occurred.                              */
int Bluetooth::setConnect(){
	int ret_val = 0;

	/* First, check that a valid Bluetooth Stack ID exists.              */
	if(bluetoothStackID){
		/* Attempt to set the attached Device to be Connectable.          */
		ret_val = GAP_Set_Connectability_Mode(bluetoothStackID, cmConnectableMode);
	} else {
		return -1;
	}

	return ret_val;
}

/* The following function is responsible for placing the Local       */
/* Bluetooth Device into General Discoverablity Mode.  Once in this  */
/* mode the Device will respond to Inquiry Scans from other Bluetooth*/
/* Devices.  This function requires that a valid Bluetooth Stack ID  */
/* exists before running.  This function returns zero on successful  */
/* execution and a negative value if an error occurred.              */
int Bluetooth::setDisc(){
	int ret_val = 0;

	/* First, check that a valid Bluetooth Stack ID exists.              */
	if(bluetoothStackID){
		/* A semi-valid Bluetooth Stack ID exists, now attempt to set the */
		/* attached Devices Discoverablity Mode to General.               */
		ret_val = GAP_Set_Discoverability_Mode(bluetoothStackID, dmGeneralDiscoverableMode, 0);
	} else {
		return -1;
	}

	return(ret_val);
}

void BTPSAPI Bluetooth::GAP_Event_Callback(unsigned int BluetoothStackID, GAP_Event_Data_t *GAP_Event_Data, unsigned long CallbackParameter){
	((Bluetooth *)CallbackParameter)->gapEventCallback(BluetoothStackID, GAP_Event_Data);
}

void BTPSAPI Bluetooth::HCI_Event_Callback(unsigned int BluetoothStackID, HCI_Event_Data_t *HCI_Event_Data, unsigned long CallbackParameter){
	((Bluetooth *)CallbackParameter)->hciEventCallback(BluetoothStackID, HCI_Event_Data);
}


void Bluetooth::gapEventCallback(unsigned int BluetoothStackID, GAP_Event_Data_t *GAP_Event_Data){
	UNUSED(BluetoothStackID);
	UNUSED(GAP_Event_Data);

}

void Bluetooth::hciEventCallback(unsigned int BluetoothStackID, HCI_Event_Data_t *HCI_Event_Data){
	UNUSED(BluetoothStackID);
	UNUSED(HCI_Event_Data);
}

/* The following function is responsible for placing the local       */
/* Bluetooth device into Pairable mode.  Once in this mode the device*/
/* will response to pairing requests from other Bluetooth devices.   */
/* This function returns zero on successful execution and a negative */
/* value on all errors.                                              */
int Bluetooth::setPairable()
{
	int Result;
	int ret_val = 0;

	/* First, check that a valid Bluetooth Stack ID exists.              */
	if(bluetoothStackID)
	{
		/* Attempt to set the attached device to be pairable.             */
		Result = GAP_Set_Pairability_Mode(bluetoothStackID, pmPairableMode);

		/* Next, check the return value of the GAP Set Pairability mode   */
		/* command for successful execution.                              */
		if(!Result){
			/* The device has been set to pairable mode, now register an   */
			/* Authentication Callback to handle the Authentication events */
			/* if required.                                                */
			Result = GAP_Register_Remote_Authentication(bluetoothStackID, GAP_Event_Callback, (unsigned long)this);

			/* Next, check the return value of the GAP Register Remote     */
			/* Authentication command for successful execution.            */
			if(Result){
				/* An error occurred while trying to execute this function. */
				ret_val = Result;
			}
		}
		else{
			/* An error occurred while trying to make the device pairable. */
			ret_val = Result;
		}
	} else {
		/* No valid Bluetooth Stack ID exists.                            */
		ret_val = -1;
	}

	return(ret_val);
}


/* The following function is a utility function that exists to delete*/
/* the specified Link Key from the Local Bluetooth Device.  If a NULL*/
/* Bluetooth Device Address is specified, then all Link Keys will be */
/* deleted.                                                          */
int Bluetooth::deleteLinkKey(BD_ADDR_t BD_ADDR){
	int       result;
	Byte_t    Status_Result;
	Word_t    Num_Keys_Deleted = 0;
	BD_ADDR_t NULL_BD_ADDR;

	result = HCI_Delete_Stored_Link_Key(bluetoothStackID, BD_ADDR, TRUE, &Status_Result, &Num_Keys_Deleted);

	/* Any stored link keys for the specified address (or all) have been */
	/* deleted from the chip.  Now, let's make sure that our stored Link */
	/* Key Array is in sync with these changes.                          */

	/* First check to see all Link Keys were deleted.                    */
	ASSIGN_BD_ADDR(NULL_BD_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

	if(COMPARE_BD_ADDR(BD_ADDR, NULL_BD_ADDR))
	   BTPS_MemInitialize(linkKeyInfo, 0, sizeof(linkKeyInfo));
	else
	{
	   /* Individual Link Key.  Go ahead and see if know about the entry */
	   /* in the list.                                                   */
	   for(result=0;(result<(int)(sizeof(linkKeyInfo)/sizeof(LinkKeyInfo_t)));result++)
	   {
		  if(COMPARE_BD_ADDR(BD_ADDR, linkKeyInfo[result].BD_ADDR))
		  {
			 linkKeyInfo[result].BD_ADDR = NULL_BD_ADDR;
			 break;
		  }
	   }
	}

	return(result);
}

/* The following function is responsible for opening the SS1         */
/* Bluetooth Protocol Stack.  This function accepts a pre-populated  */
/* HCI Driver Information structure that contains the HCI Driver     */
/* Transport Information.  This function returns zero on successful  */
/* execution and a negative value on all errors.                     */
int Bluetooth::openStack(){
	int                        result;
	int                        ret_val = 0;
	char                       bluetoothAddress[16];
	Byte_t                     status;
	BD_ADDR_t                  bd_addr;
	HCI_Version_t              HCIVersion;
	L2CA_Link_Connect_Params_t L2CA_Link_Connect_Params;

	/* First check to see if the Stack has already been opened.          */
	if(!bluetoothStackID)
	{

	  /* Initialize BTPSKNRl.                                        */
	  BTPS_Init(&BTPS_Initialization);

	  /* Initialize the Stack                                        */
	  result = BSC_Initialize(&HCI_DriverInformation, 0);

	  /* Next, check the return value of the initialization to see if*/
	  /* it was successful.                                          */
	  if(result > 0)
	  {

		 /* The Stack was initialized successfully, inform the user  */
		 /* and set the return value of the initialization function  */
		 /* to the Bluetooth Stack ID.                               */
		 bluetoothStackID = result;

		 /* Initialize the default Secure Simple Pairing parameters. */
		/* IOCapability     = DEFAULT_IO_CAPABILITY;
		 OOBSupport       = FALSE;
		 MITMProtection   = DEFAULT_MITM_PROTECTION;*/


		 /* Set the Name for the initial use.              */
		 GAP_Set_Local_Device_Name (bluetoothStackID, const_cast<char *>(name));

		 /* Go ahead and allow Master/Slave Role Switch.             */
		 L2CA_Link_Connect_Params.L2CA_Link_Connect_Request_Config  = cqAllowRoleSwitch;
		 L2CA_Link_Connect_Params.L2CA_Link_Connect_Response_Config = csMaintainCurrentRole;

		 L2CA_Set_Link_Connection_Configuration(bluetoothStackID, &L2CA_Link_Connect_Params);

		 if(HCI_Command_Supported(bluetoothStackID, HCI_SUPPORTED_COMMAND_WRITE_DEFAULT_LINK_POLICY_BIT_NUMBER) > 0)
			HCI_Write_Default_Link_Policy_Settings(bluetoothStackID, (HCI_LINK_POLICY_SETTINGS_ENABLE_MASTER_SLAVE_SWITCH|HCI_LINK_POLICY_SETTINGS_ENABLE_SNIFF_MODE), &status);

		 /* Delete all Stored Link Keys.                             */
		 ASSIGN_BD_ADDR(bd_addr, macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

		 deleteLinkKey(bd_addr);
	  } else
		  return -1;
	}

	return 0;
}

/* The following function is responsible for closing the SS1         */
/* Bluetooth Protocol Stack.  This function requires that the        */
/* Bluetooth Protocol stack previously have been initialized via the */
/* OpenStack() function.  This function returns zero on successful   */
/* execution and a negative value on all errors.                     */
int Bluetooth::closeStack()
{
	int ret_val = 0;

	/* First check to see if the Stack has been opened.                  */
	if(bluetoothStackID)
	{
		/* Simply close the Stack                                         */
		BSC_Shutdown(bluetoothStackID);

		/* Free BTPSKRNL allocated memory.                                */
		BTPS_DeInit();

		/* Flag that the Stack is no longer initialized.                  */
		bluetoothStackID = 0;

		/* Flag success to the caller.                                    */
		ret_val          = 0;
	}
	else {
		/* A valid Stack ID does not exist, inform to user.               */
		ret_val = -1;
	}

	return(ret_val);
}


void Bluetooth::init(){
	int result;
	HCI_DRIVER_SET_COMM_INFORMATION(&HCI_DriverInformation, 1, VENDOR_BAUD_RATE, cpHCILL_RTS_CTS);
	HCI_DriverInformation.DriverInformation.COMMDriverInformation.InitializationDelay = 100;

	/* Set up the application callbacks.                                 */
	BTPS_Initialization.MessageOutputCallback = displayCallback;

	/* Initialize the application.                                       */
	if((result = initializeApplication()) > 0){

	}
}
