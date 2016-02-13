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
 *
 *
 * This file is heavily based on SPPDemo.c example
 * from Bluetopia stack.
 *
 */

#include "Bluetooth.h"
#include <cstring>
#include <helpers.h>
#include <Logger.h>
#include <algorithm>
#include <EEPROM.h>

#define DEFAULT_IO_CAPABILITY          (icNoInputNoOutput)
#define DEFAULT_MITM_PROTECTION                  (FALSE)


Bluetooth::Bluetooth(): sendTask("BTSendTask", sendTaskCallbackStatic, 256, this) {
	Connected=FALSE;
	SPPServerSDPHandle=0;
	bluetoothStackID=0;
	ServerPortID=0;
	SerialPortID=0;
	Connection_Handle=0;
	OOBSupport=FALSE;
	MITMProtection=DEFAULT_MITM_PROTECTION;
	IOCapability     = DEFAULT_IO_CAPABILITY;
	OOBSupport       = FALSE;
	clearNeeded=false;
	lastLinkKeyIndex=0;

	this->name = "";

	running=true;

	setPin("1234");
}

Bluetooth& Bluetooth::instance(){
	static Bluetooth inst;
	return inst;
}

void Bluetooth::sendTaskCallbackStatic(OS::Task &task){
	((Bluetooth *)task.getUserData())->sendTaskCallback();
}


Bluetooth::~Bluetooth() {
	running=false;
	readyToSendEvent.signal();
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
  SerialPortID = 0;

  /* Initiailize some defaults.                                        */
  /*SerialPortID           = 0;
  UI_Mode                = UI_MODE_SELECT;
  LoopbackActive         = FALSE;
  DisplayRawData         = FALSE;
  AutomaticReadActive    = FALSE;
  NumberofValidResponses = 0;*/

 /* Try to Open the stack and check if it was successful.          */
 if(!openStack()){
 	/* The stack was opened successfully.  Now set some defaults.  */

	/* First, attempt to set the Device to be Connectable.         */
	ret_val = setConnectabilityMode(cmConnectableMode);

	/* Next, check to see if the Device was successfully made      */
	/* Connectable.                                                */
	if(!ret_val)
	{
	   /* Now that the device is Connectable attempt to make it    */
	   /* Discoverable.                                            */
	   ret_val = setDiscoverabilityMode(dmGeneralDiscoverableMode);

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

 return ret_val;
}

void BTPSAPI Bluetooth::GAP_Event_Callback(unsigned int BluetoothStackID, GAP_Event_Data_t *GAP_Event_Data, unsigned long CallbackParameter){
	((Bluetooth *)CallbackParameter)->gapEventCallback(BluetoothStackID, GAP_Event_Data);
}

void BTPSAPI Bluetooth::HCI_Event_Callback(unsigned int BluetoothStackID, HCI_Event_Data_t *HCI_Event_Data, unsigned long CallbackParameter){
	((Bluetooth *)CallbackParameter)->hciEventCallback(BluetoothStackID, HCI_Event_Data);
}


void BTPSAPI Bluetooth::SPP_Event_Callback(unsigned int BluetoothStackID, SPP_Event_Data_t *SPP_Event_Data, unsigned long CallbackParameter)
{
	((Bluetooth *)CallbackParameter)->sppEventCallback(BluetoothStackID, SPP_Event_Data);
}


void Bluetooth::sppEventCallback(unsigned int BluetoothStackID, SPP_Event_Data_t *SPP_Event_Data){

	int       ret_val = 0;
	int       TempLength;
	Boolean_t Done;

	/* **** SEE SPPAPI.H for a list of all possible event types.  This   */
	/* program only services its required events.                   **** */

	/* First, check to see if the required parameters appear to be       */
	/* semi-valid.                                                       */
	if((SPP_Event_Data) && (BluetoothStackID))
	{
	  /* The parameters appear to be semi-valid, now check to see what  */
	  /* type the incoming event is.                                    */
	  switch(SPP_Event_Data->Event_Data_Type)
	  {
		 case etPort_Open_Request_Indication:
			/* A remote port is requesting a connection.                */
			/* Accept the connection always.                            */
			SPP_Open_Port_Request_Response(BluetoothStackID, SPP_Event_Data->Event_Data.SPP_Open_Port_Request_Indication_Data->SerialPortID, TRUE);
			break;
		 case etPort_Open_Indication:
			/* A remote port is requesting a connection.                */
			/* Save the Serial Port ID for later use.                   */
			SerialPortID = SPP_Event_Data->Event_Data.SPP_Open_Port_Indication_Data->SerialPortID;

			/* Flag that we are now connected.                          */
			Connected  = TRUE;

			writeBuffer.clear();

			/* Query the connection handle.                             */
			ret_val = GAP_Query_Connection_Handle(BluetoothStackID, SPP_Event_Data->Event_Data.SPP_Open_Port_Indication_Data->BD_ADDR, const_cast<Word_t*>(&Connection_Handle));
			if(ret_val)
			{
			   /* Failed to Query the Connection Handle.                */
			   ret_val           = 0;
			   Connection_Handle = 0;
			}

			readyToSendEvent.signal();
			break;
		 case etPort_Open_Confirmation:
			/* Needed only in client mode. */
			Logger::panic("etPort_Open_Confirmation: not implemented.");
			break;
		 case etPort_Close_Port_Indication:
			/* The Remote Port was Disconnected.                        */
			/* Invalidate the Serial Port ID.                           */
			clearNeeded=true;
			//if the port is closed, signal "bufferHasSpaceEvent",
			//otherwise it will never return.
			bufferHasSpaceEvent.signal();
			SerialPortID = 0;

			Connection_Handle = 0;
			//SendInfo.BytesToSend = 0;

			/* Flag that we are no longer connected.                    */
			Connected         = FALSE;
			break;
		 case etPort_Status_Indication:
			/* Display Information about the new Port Status.           */
			break;
		 case etPort_Data_Indication:
		   /* If we are operating in Raw Data Display Mode then     */
		   /* simply display the data that was give to use.         */

		  /* Initialize Done to false.                          */
		  Done = FALSE;

		  /* Loop through and read all data that is present in  */
		  /* the buffer.                                        */
		  while(!Done)
		  {
			 /* Read as much data as possible.                  */
			 if((TempLength = SPP_Data_Read(BluetoothStackID, SerialPortID, (Word_t)sizeof(tmpBuffer)-1, (Byte_t *)tmpBuffer)) > 0)
			 {
				/* Now simply display each character that we    */
				/* have just read.                              */

			 }
			 else
			 {
				/* Regardless if an error occurred, we are      */
				/* finished with the current loop.              */
				Done = TRUE;
			 }
		  }

			break;
		 case etPort_Send_Port_Information_Indication:
			/* Simply Respond with the information that was sent to us. */
			ret_val = SPP_Respond_Port_Information(BluetoothStackID, SPP_Event_Data->Event_Data.SPP_Send_Port_Information_Indication_Data->SerialPortID, &SPP_Event_Data->Event_Data.SPP_Send_Port_Information_Indication_Data->SPPPortInformation);
			break;
		 case etPort_Transmit_Buffer_Empty_Indication:
			/* The transmit buffer is now empty after being full.  Next */
			/* check the current application state.                     */
			readyToSendEvent.signal();
			break;
		 default:
			break;
	  }


	}

}


void Bluetooth::gapEventCallback(unsigned int BluetoothStackID, GAP_Event_Data_t *GAP_Event_Data){
	UNUSED(BluetoothStackID);
	UNUSED(GAP_Event_Data);


	int                               Result;
	int                               Index;
	GAP_Authentication_Information_t  GAP_Authentication_Information;

	/* First, check to see if the required parameters appear to be       */
	/* semi-valid.                                                       */
	if((BluetoothStackID) && (GAP_Event_Data))
	{
	  /* The parameters appear to be semi-valid, now check to see what  */
	  /* type the incoming event is.                                    */
	  switch(GAP_Event_Data->Event_Data_Type)
	  {
		 case etInquiry_Result:
			break;
		 case etInquiry_Entry_Result:
			break;
		 case etAuthentication:
			/* An authentication event occurred, determine which type of*/
			/* authentication event occurred.                           */
			switch(GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->GAP_Authentication_Event_Type)
			{
			   case atLinkKeyRequest:
				  /* Setup the authentication information response      */
				  /* structure.                                         */
				  GAP_Authentication_Information.GAP_Authentication_Type    = atLinkKey;
				  GAP_Authentication_Information.Authentication_Data_Length = 0;

				  /* See if we have stored a Link Key for the specified */
				  /* device.                                            */
				  for(Index=0;Index<(int)(sizeof(linkKeyInfo)/sizeof(LinkKeyInfo_t));Index++)
				  {
					 if(COMPARE_BD_ADDR(linkKeyInfo[Index].BD_ADDR, GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device))
					 {
						/* Link Key information stored, go ahead and    */
						/* respond with the stored Link Key.            */
						GAP_Authentication_Information.Authentication_Data_Length   = sizeof(Link_Key_t);
						GAP_Authentication_Information.Authentication_Data.Link_Key = linkKeyInfo[Index].LinkKey;

						break;
					 }
				  }

				  /* Submit the authentication response.                */
				  Result = GAP_Authentication_Response(BluetoothStackID, GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device, &GAP_Authentication_Information);

				  break;
			   case atPINCodeRequest:
				  /* Note the current Remote BD_ADDR that is requesting */
				  /* the PIN Code.                                      */
				  CurrentRemoteBD_ADDR = GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device;

				  /* Inform the user that they will need to respond with*/
				  /* a PIN Code Response.                               */
				  pinCodeResponse(pin);
				  break;
			   case atAuthenticationStatus:
				  /* Flag that there is no longer a current             */
				  /* Authentication procedure in progress.              */
				  ASSIGN_BD_ADDR(CurrentRemoteBD_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				  break;
			   case atLinkKeyCreation:
				  for(Index=0,Result=-1;Index<(int)(sizeof(linkKeyInfo)/sizeof(LinkKeyInfo_t));Index++)
				  {
					 if(COMPARE_BD_ADDR(linkKeyInfo[Index].BD_ADDR, GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device)){
						 Result=Index;
						 break;
					 }
				  }

				  if (Result>=0){
					  if ( memcmp((char*)&linkKeyInfo[Result].LinkKey, (char*)&GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Authentication_Event_Data.Link_Key_Info.Link_Key, sizeof(Link_Key_t))){
						  //Update link key if changed.
						  linkKeyInfo[lastLinkKeyIndex].LinkKey = GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Authentication_Event_Data.Link_Key_Info.Link_Key;
						  storeLinkKey(lastLinkKeyIndex);
					  }
				  } else {
					  lastLinkKeyIndex++;
					  if (lastLinkKeyIndex >= MAX_SUPPORTED_LINK_KEYS){
						  lastLinkKeyIndex-=MAX_SUPPORTED_LINK_KEYS;
					  }

					  linkKeyInfo[lastLinkKeyIndex].BD_ADDR = GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device;
					  linkKeyInfo[lastLinkKeyIndex].LinkKey = GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Authentication_Event_Data.Link_Key_Info.Link_Key;
					  storeLinkKey(lastLinkKeyIndex);
					  storeLinkKeyIndex();
				  }
				  break;
			   case atIOCapabilityRequest:
				  /* Setup the Authentication Information Response      */
				  /* structure.                                         */
				  GAP_Authentication_Information.GAP_Authentication_Type                                      = atIOCapabilities;
				  GAP_Authentication_Information.Authentication_Data_Length                                   = sizeof(GAP_IO_Capabilities_t);
				  GAP_Authentication_Information.Authentication_Data.IO_Capabilities.IO_Capability            = (GAP_IO_Capability_t)IOCapability;
				  GAP_Authentication_Information.Authentication_Data.IO_Capabilities.MITM_Protection_Required = MITMProtection;
				  GAP_Authentication_Information.Authentication_Data.IO_Capabilities.OOB_Data_Present         = OOBSupport;

				  /* Submit the Authentication Response.                */
				  Result = GAP_Authentication_Response(BluetoothStackID, GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device, &GAP_Authentication_Information);
				  break;
			   case atIOCapabilityResponse:
				   break;
			   case atUserConfirmationRequest:
				  CurrentRemoteBD_ADDR = GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device;

				  if(IOCapability != icDisplayYesNo)
				  {
					 /* Invoke JUST Works Process...                    */
					 GAP_Authentication_Information.GAP_Authentication_Type          = atUserConfirmation;
					 GAP_Authentication_Information.Authentication_Data_Length       = (Byte_t)sizeof(Byte_t);
					 GAP_Authentication_Information.Authentication_Data.Confirmation = TRUE;

					 /* Submit the Authentication Response.             */
					 Result = GAP_Authentication_Response(BluetoothStackID, GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device, &GAP_Authentication_Information);

					 /* Flag that there is no longer a current          */
					 /* Authentication procedure in progress.           */
					 ASSIGN_BD_ADDR(CurrentRemoteBD_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
				  }
				  break;
			   case atPasskeyRequest:
				  break;
			   case atRemoteOutOfBandDataRequest:
				  /* This application does not support OOB data so      */
				  /* respond with a data length of Zero to force a      */
				  /* negative reply.                                    */
				  GAP_Authentication_Information.GAP_Authentication_Type    = atOutOfBandData;
				  GAP_Authentication_Information.Authentication_Data_Length = 0;

				  Result = GAP_Authentication_Response(BluetoothStackID, GAP_Event_Data->Event_Data.GAP_Authentication_Event_Data->Remote_Device, &GAP_Authentication_Information);
				  break;
			   case atPasskeyNotification:
				  break;
			   case atKeypressNotification:
				  break;
			   default:
				  break;
			}
			break;
		 case etRemote_Name_Result:
			break;
		 case etEncryption_Change_Result:
			break;
		 default:
			break;
	  }
	}

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
		Result = setPairabilityMode(pmPairableMode);

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

/* The following function is responsible for opening the SS1         */
/* Bluetooth Protocol Stack.  This function accepts a pre-populated  */
/* HCI Driver Information structure that contains the HCI Driver     */
/* Transport Information.  This function returns zero on successful  */
/* execution and a negative value on all errors.                     */
int Bluetooth::openStack(){
	int                        result;
	Byte_t                     status;
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
		 IOCapability     = DEFAULT_IO_CAPABILITY;
		 OOBSupport       = FALSE;
		 MITMProtection   = DEFAULT_MITM_PROTECTION;

		 /* Set the Name for the initial use.              */
		 GAP_Set_Local_Device_Name (bluetoothStackID, const_cast<char *>(name));

		 /* Go ahead and allow Master/Slave Role Switch.             */
		 L2CA_Link_Connect_Params.L2CA_Link_Connect_Request_Config  = cqAllowRoleSwitch;
		 L2CA_Link_Connect_Params.L2CA_Link_Connect_Response_Config = csMaintainCurrentRole;

		 L2CA_Set_Link_Connection_Configuration(bluetoothStackID, &L2CA_Link_Connect_Params);

		 if(HCI_Command_Supported(bluetoothStackID, HCI_SUPPORTED_COMMAND_WRITE_DEFAULT_LINK_POLICY_BIT_NUMBER) > 0)
			HCI_Write_Default_Link_Policy_Settings(bluetoothStackID, (HCI_LINK_POLICY_SETTINGS_ENABLE_MASTER_SLAVE_SWITCH|HCI_LINK_POLICY_SETTINGS_ENABLE_SNIFF_MODE), &status);

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

/* The following function is responsible for opening a Serial Port   */
/* Server on the Local Device.  This function opens the Serial Port  */
/* Server on the specified RFCOMM Channel.  This function returns    */
/* zero if successful, or a negative return value if an error        */
/* occurred.                                                         */
int Bluetooth::openServer(unsigned int port){
	int  ret_val;
	char *ServiceName;

	/* First check to see if a valid Bluetooth Stack ID exists.          */
	if(bluetoothStackID)
	{
	   /* Make sure that there is not already a Serial Port Server open. */
	   if(!ServerPortID)
	   {
		 /* Simply attempt to open an Serial Server, on RFCOMM Server*/
		 /* Port 1.                                                  */
		 ret_val = SPP_Open_Server_Port(bluetoothStackID, port, SPP_Event_Callback, (unsigned long)this);

		 /* If the Open was successful, then note the Serial Port    */
		 /* Server ID.                                               */
		 if(ret_val > 0)
		 {
			/* Note the Serial Port Server ID of the opened Serial   */
			/* Port Server.                                          */
			ServerPortID = ret_val;

			/* Create a Buffer to hold the Service Name.             */
			if((ServiceName = (char*)BTPS_AllocateMemory(64)) != NULL)
			{
			   /* The Server was opened successfully, now register a */
			   /* SDP Record indicating that an Serial Port Server   */
			   /* exists. Do this by first creating a Service Name.  */
			   BTPS_SprintF(ServiceName, "Serial Port Server Port %d", port);

			   /* Now that a Service Name has been created try to    */
			   /* Register the SDP Record.                           */
			   ret_val = SPP_Register_Generic_SDP_Record(bluetoothStackID, ServerPortID, ServiceName, const_cast<DWord_t*>(&SPPServerSDPHandle));

			   /* If there was an error creating the Serial Port     */
			   /* Server's SDP Service Record then go ahead an close */
			   /* down the server an flag an error.                  */
			   if(ret_val < 0)
			   {
				  SPP_Close_Server_Port(bluetoothStackID, ServerPortID);

				  /* Flag that there is no longer an Serial Port     */
				  /* Server Open.                                    */
				  ServerPortID = 0;

				  /* Flag that we are no longer connected.           */
				  Connected    = FALSE;

				  ret_val      = -1;
			   }
			   else
			   {
				  /* Simply flag to the user that everything         */
				  /* initialized correctly.                          */
				  /* Flag success to the caller.                     */
				  ret_val = 0;
			   }

			   /* Free the Service Name buffer.                      */
			   BTPS_FreeMemory(ServiceName);
			}

		 }
		 else
		 {
			ret_val = -1;
		 }

	   }
	   else
	   {
		  /* A Server is already open, this program only supports one    */
		  /* Server or Client at a time.                                 */
		 ret_val = -1;
	   }
	}
	else
	{
	   /* No valid Bluetooth Stack ID exists.                            */
	   ret_val = -1;
	}

	return(ret_val);
}

/* The following function is responsible for setting the             */
/* Discoverability Mode of the local device.  This function returns  */
/* zero on successful execution and a negative value on all errors.  */
int Bluetooth::setDiscoverabilityMode(GAP_Discoverability_Mode_t DiscoverabilityMode)
{
	return GAP_Set_Discoverability_Mode(bluetoothStackID, DiscoverabilityMode, (DiscoverabilityMode == dmLimitedDiscoverableMode)?60:0);
}

int Bluetooth::setClassOfDevice(unsigned int classOfDev)
{
   Class_of_Device_t Class_of_Device;

   /* Attempt to submit the command.                              */
   ASSIGN_CLASS_OF_DEVICE(Class_of_Device, (Byte_t)((classOfDev >> 16) & 0xFF), (Byte_t)((classOfDev >> 8) & 0xFF), (Byte_t)(classOfDev & 0xFF));

   return GAP_Set_Class_Of_Device(bluetoothStackID, Class_of_Device);
}

int Bluetooth::setConnectabilityMode(GAP_Connectability_Mode_t ConnectableMode)
{
   return GAP_Set_Connectability_Mode(bluetoothStackID, ConnectableMode);
}

int Bluetooth::setPairabilityMode(GAP_Pairability_Mode_t PairabilityMode)
{
   return GAP_Set_Pairability_Mode(bluetoothStackID, PairabilityMode);
}

int Bluetooth::pinCodeResponse(const char *pinCode)
{
   int                              Result;
   int                              ret_val;
   PIN_Code_t                       PINCode;
   GAP_Authentication_Information_t GAP_Authentication_Information;

   /* First, check that valid Bluetooth Stack ID exists.                */
   if(bluetoothStackID)
   {
      /* First, check to see if there is an on-going Pairing operation  */
      /* active.                                                        */
      if(!COMPARE_BD_ADDR(CurrentRemoteBD_ADDR, NullADDR))
      {
         /* Make sure that all of the parameters required for this      */
         /* function appear to be at least semi-valid.                  */
         if((BTPS_StringLength(pinCode) > 0) && (BTPS_StringLength(pinCode) <= sizeof(PIN_Code_t)))
         {
            /* Parameters appear to be valid, go ahead and convert the  */
            /* input parameter into a PIN Code.                         */

            /* Initialize the PIN code.                                 */
            ASSIGN_PIN_CODE(PINCode, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

            BTPS_MemCopy(&PINCode, pinCode, BTPS_StringLength(pinCode));

            /* Populate the response structure.                         */
            GAP_Authentication_Information.GAP_Authentication_Type      = atPINCode;
            GAP_Authentication_Information.Authentication_Data_Length   = (Byte_t)(BTPS_StringLength(pinCode));
            GAP_Authentication_Information.Authentication_Data.PIN_Code = PINCode;

            /* Submit the Authentication Response.                      */
            Result = GAP_Authentication_Response(bluetoothStackID, CurrentRemoteBD_ADDR, &GAP_Authentication_Information);

            /* Check the return value for the submitted command for     */
            /* success.                                                 */
            if(!Result)
            {
               /* Flag success to the caller.                           */
               ret_val = 0;
            }
            else
            {
               /* Inform the user that the Authentication Response was  */
               /* not successful.                                       */
               ret_val = -1;
            }

            /* Flag that there is no longer a current Authentication    */
            /* procedure in progress.                                   */
            ASSIGN_BD_ADDR(CurrentRemoteBD_ADDR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
         }
         else
         {
             ret_val = -1;
         }
      }
      else
      {
         /* There is not currently an on-going authentication operation,*/
         /* inform the user of this error condition.                    */
         ret_val = -1;
      }
   }
   else
   {
      /* No valid Bluetooth Stack ID exists.                            */
      ret_val = -1;
   }

   return(ret_val);
}

void Bluetooth::storeLinkKey(int index){
	if (!EEPROM::instance().write(EEPROM::VAR_LINKKEY, index*sizeof(LinkKeyInfo_t), &linkKeyInfo[index], sizeof(LinkKeyInfo_t))){
		Logger::panic("EEPROM write failed");
	}
}

void Bluetooth::storeLinkKeyIndex(){
	if (!EEPROM::instance().write(EEPROM::VAR_LAST_LINK_KEY, 0, &lastLinkKeyIndex, sizeof(lastLinkKeyIndex))){
		Logger::panic("EEPROM write failed");
	}
}

void Bluetooth::init(const char *iname){
	int result;
	this->name = iname;

	if (!EEPROM::instance().read(EEPROM::VAR_LAST_LINK_KEY, 0, &lastLinkKeyIndex, sizeof(lastLinkKeyIndex))){
		lastLinkKeyIndex=0;
	}

	for (int a=0; a<MAX_SUPPORTED_LINK_KEYS; a++){
		//Can't read in one pass because not all link keys are stored. If a non-existing key is tried to read,
		//read will fail and the key will be initialized to 0.
		if (!EEPROM::instance().read(EEPROM::VAR_LINKKEY, a*sizeof(LinkKeyInfo_t), &linkKeyInfo[a], sizeof(LinkKeyInfo_t))){
			memset(&linkKeyInfo[a], 0, sizeof(LinkKeyInfo_t));
		}
	}


	HCI_DRIVER_SET_COMM_INFORMATION(&HCI_DriverInformation, 1, VENDOR_BAUD_RATE, cpHCILL_RTS_CTS);
	HCI_DriverInformation.DriverInformation.COMMDriverInformation.InitializationDelay = 100;

	/* Set up the application callbacks.                                 */
	BTPS_Initialization.MessageOutputCallback = displayCallback;

	/* Initialize the application.                                       */
	if((result = initializeApplication()) > 0){
	//	if (!setClassOfDevice(0x80510)){
			openServer(SPP_PORT_NUMBER_MINIMUM);
	//	}
	}
}

void Bluetooth::setPin(const char *i_pin){
	memcpy(pin, i_pin, std::min(strlen(i_pin),(size_t)16));
	pin[16]=0;
}

int Bluetooth::send(const char *data, int size, time_t timeout, bool startSend){
	if (!isConnected())
		return 0;

	if (data==NULL || size==0){
		if (startSend)
			readyToSendEvent.signal();
		return 0;
	}

	if (size==0)
		size = strlen(data);

	int origSize = size;

	while (size){
		if (!isConnected()){
			return -1;
		}

		int toWrite;

		bufferHasSpaceEvent.reset();

		if (clearNeeded){
			writeBuffer.clear();
			clearNeeded=false;
		}

		toWrite = std::min(writeBuffer.free(), size);
		writeBuffer.add(data, toWrite);

		if (toWrite){
			size -= toWrite;
			data += toWrite;

			if (startSend)
				readyToSendEvent.signal();
		}

		if (toWrite==0 || size){
			readyToSendEvent.signal();
		}

		if (size){
			if (!bufferHasSpaceEvent.wait(timeout))
				break;
		}

	}

	return origSize - size;
}

bool Bluetooth::isConnected(){
	return Connected;
}

void Bluetooth::sendTaskCallback(){
	while (running){
		char *buffer;
		int cnt;
		int sent;

		readyToSendEvent.reset();

		if (!isConnected()){
			readyToSendEvent.wait();
			continue;
		}

		if (!clearNeeded){
			cnt=writeBuffer.getContinuousReadBuffer(buffer);
			if (cnt){
				sent=SPP_Data_Write(bluetoothStackID, SerialPortID, cnt, (unsigned char *)buffer);
				if (sent>0)
					writeBuffer.skip(sent);
			} else
				sent=0;

			if (sent>0)
				bufferHasSpaceEvent.signal();
			else
				readyToSendEvent.wait();
		} else {
			readyToSendEvent.wait();
		}

	}
}
