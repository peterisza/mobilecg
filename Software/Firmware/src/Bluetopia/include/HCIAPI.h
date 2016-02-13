/*****< hciapi.h >*************************************************************/
/*      Copyright 2000 - 2014 Stonestreet One.                                */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  HCIAPI - Stonestreet One Bluetooth Stack HCI API Type Definitions,        */
/*           Constants, and Prototypes.                                       */
/*                                                                            */
/*  Author:  Damon Lange                                                      */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   09/11/00  D. Lange       Initial creation.                               */
/*   12/07/07  D. Mason       Changes for BT 2.1                              */
/******************************************************************************/
#ifndef __HCIAPIH__
#define __HCIAPIH__

#include "BTPSKRNL.h"           /* BTPS Kernel Prototypes/Constants.          */

#include "BTAPITyp.h"           /* Bluetooth API Type Definitions.            */
#include "HCITypes.h"           /* Bluetooth HCI Type Definitions/Constants.  */

#include "BTPSCFG.h"            /* BTPS Configuration Constants.              */

   /* The following enumerated type is used with the                    */
   /* HCI_Version_Supported() function.  These values represent the     */
   /* HCI Layer Specification that the HCI API Layer supports.  Notice  */
   /* that the Version definition for later versions of the Bluetooth   */
   /* HCI Specification are defined as values having a larger           */
   /* numerical value.  This allows simple comparison logic             */
   /* (greater than/less than/equal to/etc. logic to be performed).     */
   /* * NOTE * If a Bluetooth HCI Specification value is NOT listed in  */
   /*          this list then it is NOT supported by the HCI API        */
   /*          present in this file.                                    */
typedef enum
{
   hvSpecification_1_0B,                /* HCI Specification 1.0B.      */
   hvSpecification_1_1,                 /* HCI Specification 1.1.       */
   hvSpecification_1_2,                 /* HCI Specification 1.2.       */
   hvSpecification_2_0,                 /* HCI Specification 2.0.       */
   hvSpecification_2_1,                 /* HCI Specification 2.1 + EDR. */
   hvSpecification_3_0,                 /* HCI Specification 3.0 + HS.  */
   hvSpecification_4_0,                 /* HCI Specification 4.0.       */
   hvSpecification_4_1                  /* HCI Specification 4.1.       */
} HCI_Version_t;

   /* The following structure is used with the                          */
   /* HCI_Write_Stored_Link_Key() function, and represents a single     */
   /* BD_ADDR/Link Key Pair that is required by this function.          */
typedef struct _tagHCI_Stored_Link_Key_Info_t
{
   BD_ADDR_t  BD_ADDR;
   Link_Key_t Link_Key;
} HCI_Stored_Link_Key_Info_t;

#define HCI_STORED_LINK_KEY_INFO_SIZE                   (sizeof(HCI_Stored_Link_Key_Info_t))

   /* The following structure is used with the                          */
   /* HCI_Host_Number_Of_Completed_Packets() function, and represents   */
   /* a single Connection Handle/Host Number of Completed Packets Pair  */
   /* that is required by this function.                                */
typedef struct _tagHCI_Host_Completed_Packets_Info_t
{
   Word_t Connection_Handle;
   Word_t Host_Num_Of_Completed_Packets;
} HCI_Host_Completed_Packets_Info_t;

#define HCI_HOST_COMPLETED_PACKETS_INFO_SIZE            (sizeof(HCI_Host_Completed_Packets_Info_t))

   /* HCI Event API Types.                                              */
typedef enum
{
   etInquiry_Complete_Event,
   etInquiry_Result_Event,
   etConnection_Complete_Event,
   etConnection_Request_Event,
   etDisconnection_Complete_Event,
   etAuthentication_Complete_Event,
   etRemote_Name_Request_Complete_Event,
   etEncryption_Change_Event,
   etChange_Connection_Link_Key_Complete_Event,
   etMaster_Link_Key_Complete_Event,
   etRead_Remote_Supported_Features_Complete_Event,
   etRead_Remote_Version_Information_Complete_Event,
   etQoS_Setup_Complete_Event,
   etHardware_Error_Event,
   etFlush_Occurred_Event,
   etRole_Change_Event,
   etNumber_Of_Completed_Packets_Event,
   etMode_Change_Event,
   etReturn_Link_Keys_Event,
   etPIN_Code_Request_Event,
   etLink_Key_Request_Event,
   etLink_Key_Notification_Event,
   etLoopback_Command_Event,
   etData_Buffer_Overflow_Event,
   etMax_Slots_Change_Event,
   etRead_Clock_Offset_Complete_Event,
   etConnection_Packet_Type_Changed_Event,
   etQoS_Violation_Event,
   etPage_Scan_Mode_Change_Event,
   etPage_Scan_Repetition_Mode_Change_Event,
   etBluetooth_Logo_Testing_Event,
   etVendor_Specific_Debug_Event,
   etDevice_Reset_Event,
   etFlow_Specification_Complete_Event,
   etInquiry_Result_With_RSSI_Event,
   etRead_Remote_Extended_Features_Complete_Event,
   etSynchronous_Connection_Complete_Event,
   etSynchronous_Connection_Changed_Event,
   etSniff_Subrating_Event,
   etExtended_Inquiry_Result_Event,
   etEncryption_Key_Refresh_Complete_Event,
   etIO_Capability_Request_Event,
   etIO_Capability_Response_Event,
   etUser_Confirmation_Request_Event,
   etUser_Passkey_Request_Event,
   etRemote_OOB_Data_Request_Event,
   etSimple_Pairing_Complete_Event,
   etLink_Supervision_Timeout_Changed_Event,
   etEnhanced_Flush_Complete_Event,
   etUser_Passkey_Notification_Event,
   etKeypress_Notification_Event,
   etRemote_Host_Supported_Features_Notification_Event,
   etPhysical_Link_Complete_Event,
   etChannel_Selected_Event,
   etDisconnection_Physical_Link_Complete_Event,
   etPhysical_Link_Loss_Early_Warning_Event,
   etPhysical_Link_Recovery_Event,
   etLogical_Link_Complete_Event,
   etDisconnection_Logical_Link_Complete_Event,
   etFlow_Spec_Modify_Complete_Event,
   etNumber_Of_Completed_Data_Blocks_Event,
   etShort_Range_Mode_Change_Complete_Event,
   etAMP_Status_Change_Event,
   etAMP_Start_Test_Event,
   etAMP_Test_End_Event,
   etAMP_Receiver_Report_Event,
   etLE_Meta_Event,
   etPlatform_Specific_Event
} HCI_Event_Type_t;

   /* LE Meta Event Subevent Types.  (Version 4.0 + LE).                */
typedef enum
{
   meConnection_Complete_Event,
   meAdvertising_Report_Event,
   meConnection_Update_Complete_Event,
   meRead_Remote_Used_Features_Complete_Event,
   meLong_Term_Key_Request_Event
} HCI_LE_Meta_Event_Type_t;

   /* The following structure represents the data that provided by a    */
   /* HCI Inquiry Complete Event.                                       */
   /* * NOTE * The Num_Responses field is ONLY valid if the Bluetooth   */
   /*          Device is using HCI Specification 1.0B, and is NOT       */
   /*          valid if the Bluetooth Device is using HCI Specification */
   /*          Version 1.1 (or greater).  The caller can issue the      */
   /*          HCI_Version_Supported() function to determine if the     */
   /*          Num_Responses field is valid (Version 1.1 or greater).   */
typedef struct _tagHCI_Inquiry_Complete_Event_Data_t
{
   Byte_t Status;
   Byte_t Num_Responses;
} HCI_Inquiry_Complete_Event_Data_t;

#define HCI_INQUIRY_COMPLETE_EVENT_DATA_SIZE            (sizeof(HCI_Inquiry_Complete_Event_Data_t))

   /* The following structure represents the data that is returned in   */
   /* a HCI Inquiry Result Event.  This structure represents an         */
   /* individual entry, and the HCI Inquiry Result Event structure will */
   /* contains an array of these structures (based upon the number of   */
   /* responses).                                                       */
typedef struct _tagHCI_Inquiry_Result_Data_t
{
   BD_ADDR_t         BD_ADDR;
   Byte_t            Page_Scan_Repetition_Mode;
   Byte_t            Page_Scan_Period_Mode;
   Byte_t            Page_Scan_Mode;
   Class_of_Device_t Class_of_Device;
   Word_t            Clock_Offset;
} HCI_Inquiry_Result_Data_t;

#define HCI_INQUIRY_RESULT_DATA_SIZE                    (sizeof(HCI_Inquiry_Result_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Inquiry Result Event.  The HCI_Inquiry_Result_Data   */
   /* member represents a variable array that can contain 0 or more     */
   /* entries.  The Number of Entries in this array is given by the     */
   /* Num_Responses member.  A utility MACRO is provided to aid in the  */
   /* calculation of the Number of Bytes that are occupied by the       */
   /* structure given a specified number of Responses.                  */
typedef struct _tagHCI_Inquiry_Result_Event_Data_t
{
   Byte_t                    Num_Responses;
   HCI_Inquiry_Result_Data_t HCI_Inquiry_Result_Data[1];
} HCI_Inquiry_Result_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Inquiry Result Event Data Structure based upon the number of  */
   /* HCI Inquiry Result Entries associated with the Event.  The first  */
   /* parameter to this MACRO is the number of HCI Inquiry Result       */
   /* Entries.                                                          */
#define HCI_INQUIRY_RESULT_EVENT_DATA_SIZE(_x)          ((sizeof(HCI_Inquiry_Result_Event_Data_t) - sizeof(HCI_Inquiry_Result_Data_t)) + (((Byte_t)(_x))*sizeof(HCI_Inquiry_Result_Data_t)))

#define HCI_INQUIRY_RESULT_EVENT_MAX_DATA_ENTRIES       ((((sizeof(Byte_t))*256)-HCI_INQUIRY_RESULT_EVENT_DATA_SIZE(0))/sizeof(HCI_Inquiry_Result_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Connection Complete Event.                           */
typedef struct _tagHCI_Connection_Complete_Event_Data_t
{
   Byte_t    Status;
   Word_t    Connection_Handle;
   BD_ADDR_t BD_ADDR;
   Byte_t    Link_Type;
   Byte_t    Encryption_Mode;
} HCI_Connection_Complete_Event_Data_t;

#define HCI_CONNECTION_COMPLETE_EVENT_DATA_SIZE         (sizeof(HCI_Connection_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Connection Request Event.                            */
typedef struct _tagHCI_Connection_Request_Event_Data_t
{
   BD_ADDR_t         BD_ADDR;
   Class_of_Device_t Class_of_Device;
   Byte_t            Link_Type;
} HCI_Connection_Request_Event_Data_t;

#define HCI_CONNECTION_REQUEST_EVENT_DATA_SIZE          (sizeof(HCI_Connection_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Disconnection Complete Event.                        */
typedef struct _tagHCI_Disconnection_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Byte_t Reason;
} HCI_Disconnection_Complete_Event_Data_t;

#define HCI_DISCONNECTION_COMPLETE_EVENT_DATA_SIZE      (sizeof(HCI_Disconnection_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Authentication Complete Event.                       */
typedef struct _tagHCI_Authentication_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
} HCI_Authentication_Complete_Event_Data_t;

#define HCI_AUTHENTICATION_COMPLETE_EVENT_DATA_SIZE     (sizeof(HCI_Authentication_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Remote Name Request Complete Event.  The Remote_Name */
   /* member is a variable length field that represents a NULL          */
   /* terminated Name.  The member is guaranteed to have at LEAST one   */
   /* Byte of storage (empty string, single NULL Terminator), and NOT   */
   /* more than MAX_NAME_LENGTH+1 (Maximum Name Length plus one byte for*/
   /* NULL terminator).  A utility MACRO is provided to aid in the      */
   /* calculation of the number of bytes required based upon the        */
   /* number of bytes that the Remote Name String occupies.             */
typedef struct _tagHCI_Remote_Name_Request_Complete_Event_Data_t
{
   Byte_t    Status;
   BD_ADDR_t BD_ADDR;
   char      Remote_Name[1];
} HCI_Remote_Name_Request_Complete_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Remote Name Request Complete Event Data Structure based upon  */
   /* the length (in bytes, including the terminating NULL character)   */
   /* of the Remote Name.  The first parameter to this MACRO is the     */
   /* number of bytes required for the remote name (including           */
   /* terminating NULL character).  The size of the Remote name         */
   /* (including NULL character) will be maximum (MAX_NAME_LENGTH+1)    */
   /* Bytes.                                                            */
#define HCI_REMOTE_NAME_REQUEST_COMPLETE_EVENT_DATA_SIZE(_x)    ((BTPS_STRUCTURE_OFFSET(HCI_Remote_Name_Request_Complete_Event_Data_t, Remote_Name)) + (((Byte_t)(_x))*sizeof(Byte_t)))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Encryption Change Event.                             */
typedef struct _tagHCI_Encryption_Change_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Byte_t Encryption_Enable;
} HCI_Encryption_Change_Event_Data_t;

#define HCI_ENCRYPTION_CHANGE_EVENT_DATA_SIZE           (sizeof(HCI_Encryption_Change_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Change Connection Link Key Complete Event.           */
typedef struct _tagHCI_Change_Connection_Link_Key_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
} HCI_Change_Connection_Link_Key_Complete_Event_Data_t;

#define HCI_CHANGE_CONNECTION_LINK_KEY_COMPLETE_EVENT_DATA_SIZE (sizeof(HCI_Change_Connection_Link_Key_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Master Link Complete Event.                          */
typedef struct _tagHCI_Master_Link_Key_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Byte_t Key_Flag;
} HCI_Master_Link_Key_Complete_Event_Data_t;

#define HCI_MASTER_LINK_KEY_COMPLETE_EVENT_DATA_SIZE    (sizeof(HCI_Master_Link_Key_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Read Remote Supported Features Complete Event.       */
typedef struct _tagHCI_Read_Remote_Supported_Features_Complete_Event_Data_t
{
   Byte_t         Status;
   Word_t         Connection_Handle;
   LMP_Features_t LMP_Features;
} HCI_Read_Remote_Supported_Features_Complete_Event_Data_t;

#define HCI_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE_EVENT_DATA_SIZE (sizeof(HCI_Read_Remote_Supported_Features_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Read Remote Version Information Complete Event.      */
typedef struct _tagHCI_Read_Remote_Version_Information_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Byte_t LMP_Version;
   Word_t Manufacturer_Name;
   Word_t LMP_Subversion;
} HCI_Read_Remote_Version_Information_Complete_Event_Data_t;

#define HCI_READ_REMOTE_VERSION_INFORMATION_COMPLETE_EVENT_DATA_SIZE (sizeof(HCI_Read_Remote_Version_Information_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI QoS Setup Complete Event.                            */
typedef struct _tagHCI_QoS_Setup_Complete_Event_Data_t
{
   Byte_t  Status;
   Word_t  Connection_Handle;
   Byte_t  Flags;
   Byte_t  Service_Type;
   DWord_t Token_Rate;
   DWord_t Peak_Bandwidth;
   DWord_t Latency;
   DWord_t Delay_Variation;
} HCI_QoS_Setup_Complete_Event_Data_t;

#define HCI_QOS_SETUP_COMPLETE_EVENT_DATA_SIZE          (sizeof(HCI_QoS_Setup_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Hardware Error Event.                                */
typedef struct _tagHCI_Hardware_Error_Event_Data_t
{
   Byte_t Hardware_Code;
} HCI_Hardware_Error_Event_Data_t;

#define HCI_HARDWARE_ERROR_EVENT_DATA_SIZE              (sizeof(HCI_Hardware_Error_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Flush Occurred Event.                                */
typedef struct _tagHCI_Flush_Occurred_Event_Data_t
{
   Word_t Connection_Handle;
} HCI_Flush_Occurred_Event_Data_t;

#define HCI_FLUSH_OCCURRED_EVENT_DATA_SIZE              (sizeof(HCI_Flush_Occurred_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Role Change Event.                                   */
typedef struct _tagHCI_Role_Change_Event_Data_t
{
   Byte_t    Status;
   BD_ADDR_t BD_ADDR;
   Byte_t    New_Role;
} HCI_Role_Change_Event_Data_t;

#define HCI_ROLE_CHANGE_EVENT_DATA_SIZE                 (sizeof(HCI_Role_Change_Event_Data_t))

   /* The following structure is used with the HCI Number of Completed  */
   /* Packets Event, and represents a single Connection Handle/Host     */
   /* Number of Completed Packets Pair that is required by this Event.  */
   /* This structure represents an individual entry and a HCI Number of */
   /* Completed Packets Event will contain a variable number of these   */
   /* structures.                                                       */
typedef struct _tagHCI_Number_Of_Completed_Packets_Data_t
{
   Word_t Connection_Handle;
   Word_t HC_Num_Of_Completed_Packets;
} HCI_Number_Of_Completed_Packets_Data_t;

#define HCI_NUMBER_OF_COMPLETED_PACKETS_DATA_SIZE       (sizeof(HCI_Number_Of_Completed_Packets_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Number Of Completed Packets Event.  The              */
   /* HCI_Number_Of_Completed_Packets_Data member represents a          */
   /* variable array that can contain 0 or more entries.  The number of */
   /* Entries in this array is given by the Number_of_Handles member.   */
   /* A utility MACRO is provided to aid in the calculation of the      */
   /* Number of Bytes that are occupied by the structure given a        */
   /* specified number of Handles.                                      */
typedef struct _tagHCI_Number_Of_Completed_Packets_Event_Data_t
{
   Byte_t                                 Number_of_Handles;
   HCI_Number_Of_Completed_Packets_Data_t HCI_Number_Of_Completed_Packets_Data[1];
} HCI_Number_Of_Completed_Packets_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Number of Completed Packets Event Data Structure based upon   */
   /* the number of HCI Number of Completed Packets Event Data Entries  */
   /* associated with the Event.  The first parameter to this MACRO is  */
   /* the number of HCI Number of Completed Packets Entries.            */
#define HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_DATA_SIZE(_x)     ((sizeof(HCI_Number_Of_Completed_Packets_Event_Data_t) - sizeof(HCI_Number_Of_Completed_Packets_Data_t)) + (((Byte_t)(_x))*sizeof(HCI_Number_Of_Completed_Packets_Data_t)))

#define HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_MAX_DATA_ENTRIES  ((((sizeof(Byte_t))*256)-HCI_NUMBER_OF_COMPLETED_PACKETS_EVENT_DATA_SIZE(0))/sizeof(HCI_Number_Of_Completed_Packets_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Mode Change Event.                                   */
typedef struct _tagHCI_Mode_Change_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Byte_t Current_Mode;
   Word_t Interval;
} HCI_Mode_Change_Event_Data_t;

#define HCI_MODE_CHANGE_EVENT_DATA_SIZE                 (sizeof(HCI_Mode_Change_Event_Data_t))

   /* The following structure is used with the HCI Return Link Keys     */
   /* Event, and represents a single BD_ADDR/Link Key Pair that is      */
   /* required by this Event.  This structure represents an individual  */
   /* entry and a HCI Return Link Keys Event will contain a variable    */
   /* number of these structures.                                       */
typedef struct _tagHCI_Return_Link_Keys_Data_t
{
   BD_ADDR_t  BD_ADDR;
   Link_Key_t Link_Key;
} HCI_Return_Link_Keys_Data_t;

#define HCI_RETURN_LINK_KEYS_DATA_SIZE                  (sizeof(HCI_Return_Link_Keys_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Return Link Keys Event.  The                         */
   /* HCI_Return_Link_Keys_Data member represents a variable array that */
   /* that can contain 0 or more entries.  The number of Entries in this*/
   /* array is given by the Num_Keys member.  A utility MACRO is        */
   /* provided to aid in the calculation of the Number of Bytes that    */
   /* are occupied by the structure given a specified Number of Keys.   */
typedef struct _tagHCI_Return_Link_Keys_Event_Data_t
{
   Byte_t                      Num_Keys;
   HCI_Return_Link_Keys_Data_t HCI_Return_Link_Keys_Data[1];
} HCI_Return_Link_Keys_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Return Link Keys Event Data Structure based upon the number of*/
   /* HCI Return Link Key Data Entries associated with the Event.  The  */
   /* first parameter to this MACRO is the number of HCI Return Link    */
   /* Key Entries.                                                      */
#define HCI_RETURN_LINK_KEYS_EVENT_DATA_SIZE(_x)        ((sizeof(HCI_Return_Link_Keys_Event_Data_t) - sizeof(HCI_Return_Link_Keys_Data_t)) + (((Byte_t)(_x))*sizeof(HCI_Return_Link_Keys_Data_t)))

#define HCI_RETURN_LINK_KEYS_EVENT_MAX_DATA_ENTRIES     ((((sizeof(Byte_t))*256)-HCI_RETURN_LINK_KEYS_EVENT_DATA_SIZE(0))/sizeof(HCI_Return_Link_Keys_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI PIN Code Request Event.                              */
typedef struct _tagHCI_PIN_Code_Request_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
} HCI_PIN_Code_Request_Event_Data_t;

#define HCI_PIN_CODE_REQUEST_EVENT_DATA_SIZE            (sizeof(HCI_PIN_Code_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Link Key Request Event.                              */
typedef struct _tagHCI_Link_Key_Request_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
} HCI_Link_Key_Request_Event_Data_t;

#define HCI_LINK_KEY_REQUEST_EVENT_DATA_SIZE            (sizeof(HCI_Link_Key_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Link Key Notification Event.                         */
   /* * NOTE * The Key_Type field is ONLY valid if the Bluetooth Device */
   /*          is using HCI Specification 1.1 (or greater), and is NOT  */
   /*          valid if the Bluetooth Device is using HCI Specification */
   /*          Version 1.0B.  The caller can issue the                  */
   /*          HCI_Version_Supported() function to determine if the     */
   /*          Key_Type field is valid (Version 1.1 or greater).        */
typedef struct _tagHCI_Link_Key_Notification_Event_Data_t
{
   BD_ADDR_t  BD_ADDR;
   Link_Key_t Link_Key;
   Byte_t     Key_Type;
} HCI_Link_Key_Notification_Event_Data_t;

#define HCI_LINK_KEY_NOTIFICATION_EVENT_DATA_SIZE       (sizeof(HCI_Link_Key_Notification_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Loopback Command Event.  The HCI_Command_Packet_Data */
   /* member represents a variable array that can contain 0 or more     */
   /* bytes.  The number of bytes specified in this member is given by  */
   /* the HCI_Command_Packet_Length member.  A utility MACRO is         */
   /* provided to aid in the calculation of the Number of Bytes that    */
   /* are occupied by the structure given a specified HCI Command       */
   /* Packet Length (in bytes).                                         */
typedef struct _tagHCI_Loopback_Command_Event_Data_t
{
   Word_t HCI_Command_Packet_Length;
   Byte_t HCI_Command_Packet_Data[1];
} HCI_Loopback_Command_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* HCI Loopeback Command Event Data Structure based upon the size    */
   /* (in bytes) of the HCI Command Packet Length associated with the   */
   /* Event.  The first parameter to this MACRO is the length (in bytes)*/
   /* of the HCI Command Packet Data.                                   */
#define HCI_LOOPBACK_COMMAND_EVENT_DATA_SIZE(_x)        ((BTPS_STRUCTURE_OFFSET(HCI_Loopback_Command_Event_Data_t, HCI_Command_Packet_Data)) + (((Byte_t)(_x))*sizeof(Byte_t)))

#define HCI_LOOPBACK_COMMAND_EVENT_MAX_DATA_LENGTH      (HCI_LOOPBACK_COMMAND_EVENT_DATA_SIZE(HCI_COMMAND_MAX_SIZE))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Data Buffer Overflow Event.                          */
typedef struct _tagHCI_Data_Buffer_Overflow_Event_Data_t
{
   Byte_t Link_Type;
} HCI_Data_Buffer_Overflow_Event_Data_t;

#define HCI_DATA_BUFFER_OVERFLOW_EVENT_DATA_SIZE        (sizeof(HCI_Data_Buffer_Overflow_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Max Slots Change Event.                              */
typedef struct _tagHCI_Max_Slots_Change_Event_Data_t
{
   Word_t Connection_Handle;
   Byte_t LMP_Max_Slots;
} HCI_Max_Slots_Change_Event_Data_t;

#define HCI_MAX_SLOTS_CHANGE_EVENT_DATA_SIZE            (sizeof(HCI_Max_Slots_Change_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Read Clock Offset Complete Event.                    */
typedef struct _tagHCI_Read_Clock_Offset_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Word_t Clock_Offset;
} HCI_Read_Clock_Offset_Complete_Event_Data_t;

#define HCI_READ_CLOCK_OFFSET_COMPLETE_EVENT_DATA_SIZE  (sizeof(HCI_Read_Clock_Offset_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Connection Packet Type Changed Event.                */
typedef struct _tagHCI_Connection_Packet_Type_Changed_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Word_t Packet_Type;
} HCI_Connection_Packet_Type_Changed_Event_Data_t;

#define HCI_CONNECTION_PACKET_TYPE_CHANGED_EVENT_DATA_SIZE (sizeof(HCI_Connection_Packet_Type_Changed_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI QoS Violation Event.                                 */
typedef struct _tagHCI_QoS_Violation_Event_Data_t
{
   Word_t Connection_Handle;
} HCI_QoS_Violation_Event_Data_t;

#define HCI_QOS_VIOLATION_EVENT_DATA_SIZE               (sizeof(HCI_QoS_Violation_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Page Scan Mode Change Event.                         */
typedef struct _tagHCI_Page_Scan_Mode_Change_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
   Byte_t    Page_Scan_Mode;
} HCI_Page_Scan_Mode_Change_Event_Data_t;

#define HCI_PAGE_SCAN_MODE_CHANGE_EVENT_DATA_SIZE       (sizeof(HCI_Page_Scan_Mode_Change_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Page Scan Repetition Mode Change Event.              */
typedef struct _tagHCI_Page_Scan_Repetition_Mode_Change_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
   Byte_t    Page_Scan_Repetition_Mode;
} HCI_Page_Scan_Repetition_Mode_Change_Event_Data_t;

#define HCI_PAGE_SCAN_REPETITION_MODE_CHANGE_EVENT_DATA_SIZE    (sizeof(HCI_Page_Scan_Repetition_Mode_Change_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Flow Specification Complete Event (Version 1.2).     */
typedef struct _tagHCI_Flow_Specification_Complete_Event_Data_t
{
   Byte_t  Status;
   Word_t  Connection_Handle;
   Byte_t  Flags;
   Byte_t  Flow_Direction;
   Byte_t  Service_Type;
   DWord_t Token_Rate;
   DWord_t Token_Bucket_Size;
   DWord_t Peak_Bandwidth;
   DWord_t Access_Latency;
} HCI_Flow_Specification_Complete_Event_Data_t;

#define HCI_FLOW_SPECIFICATION_COMPLETE_EVENT_DATA_SIZE (sizeof(HCI_Flow_Specification_Complete_Event_Data_t))

   /* The following structure represents the data that is returned in a */
   /* HCI Inquiry Result With RSSI Event.  This structure represents an */
   /* individual entry, and the HCI Inquiry Result With RSSI Event      */
   /* structure will contain an array of these structures (based upon   */
   /* the number of responses).  (Version 1.2)                          */
typedef struct _tagHCI_Inquiry_Result_With_RSSI_Data_t
{
   BD_ADDR_t         BD_ADDR;
   Byte_t            Page_Scan_Repetition_Mode;
   Byte_t            Page_Scan_Period_Mode;
   Class_of_Device_t Class_of_Device;
   Word_t            Clock_Offset;
   SByte_t           RSSI;
} HCI_Inquiry_Result_With_RSSI_Data_t;

#define HCI_INQUIRY_RESULT_WITH_RSSI_DATA_SIZE          (sizeof(HCI_Inquiry_Result_With_RSSI_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Inquiry Result With RSSI Event.  The                 */
   /* HCI_Inquiry_Result_With_RSSI_Data member represents a variable    */
   /* array that can contain 0 or more entries.  The Number of Entries  */
   /* in this array is given by the Num_Responses member.  A utility    */
   /* MACRO is provided to aid in the calculation of the Number of Bytes*/
   /* that are occupied by the structure given a specified number of    */
   /* Responses. (Version 1.2)                                          */
typedef struct _tagHCI_Inquiry_Result_With_RSSI_Event_Data_t
{
   Byte_t                              Num_Responses;
   HCI_Inquiry_Result_With_RSSI_Data_t HCI_Inquiry_Result_With_RSSI_Data[1];
} HCI_Inquiry_Result_With_RSSI_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Inquiry    */
   /* Result With RSSI Event Data Structure based upon the number of HCI*/
   /* Inquiry Result With RSSI Entries associated with the Event.  The  */
   /* first parameter to this MACRO is the number of HCI Inquiry Result */
   /* With RSSI Entries (Version 1.2).                                  */
#define HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_DATA_SIZE(_x)     ((sizeof(HCI_Inquiry_Result_With_RSSI_Event_Data_t) - sizeof(HCI_Inquiry_Result_With_RSSI_Data_t)) + (((Byte_t)(_x))*sizeof(HCI_Inquiry_Result_With_RSSI_Data_t)))

#define HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_MAX_DATA_ENTRIES  ((((sizeof(Byte_t))*256)-HCI_INQUIRY_RESULT_WITH_RSSI_EVENT_DATA_SIZE(0))/sizeof(HCI_Inquiry_Result_With_RSSI_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Read Remote Extended Features Complete Event (Version*/
   /* 1.2).                                                             */
typedef struct _tagHCI_Read_Remote_Extended_Features_Complete_Event_Data_t
{
   Byte_t         Status;
   Word_t         Connection_Handle;
   Byte_t         Page_Number;
   Byte_t         Maximum_Page_Number;
   LMP_Features_t Extended_LMP_Features;
} HCI_Read_Remote_Extended_Features_Complete_Event_Data_t;

#define HCI_READ_REMOTE_EXTENDED_FEATURES_COMPLETE_EVENT_DATA_SIZE (sizeof(HCI_Read_Remote_Extended_Features_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Synchronous Connection Complete Event (Version 1.2). */
typedef struct _tagHCI_Synchronous_Connection_Complete_Event_Data_t
{
   Byte_t    Status;
   Word_t    Connection_Handle;
   BD_ADDR_t BD_ADDR;
   Byte_t    Link_Type;
   Byte_t    Transmission_Interval;
   Byte_t    Retransmission_Window;
   Word_t    Rx_Packet_Length;
   Word_t    Tx_Packet_Length;
   Byte_t    Air_Mode;
} HCI_Synchronous_Connection_Complete_Event_Data_t;

#define HCI_SYNCHRONOUS_CONNECTION_COMPLETE_EVENT_DATA_SIZE (sizeof(HCI_Synchronous_Connection_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Synchronous Connection Changed Event (Version 1.2).  */
typedef struct _tagHCI_Synchronous_Connection_Changed_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Byte_t Transmission_Interval;
   Byte_t Retransmission_Window;
   Word_t Rx_Packet_Length;
   Word_t Tx_Packet_Length;
} HCI_Synchronous_Connection_Changed_Event_Data_t;

#define HCI_SYNCHRONOUS_CONNECTION_CHANGED_EVENT_DATA_SIZE           (sizeof(HCI_Synchronous_Connection_Changed_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Sniff Subrating Event (Version 2.1 + EDR).           */
typedef struct _tagHCI_Sniff_Subrating_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Word_t Maximum_Transmit_Latency;
   Word_t Maximum_Receive_Latency;
   Word_t Minimum_Remote_Timeout;
   Word_t Minimum_Local_Timeout;
} HCI_Sniff_Subrating_Event_Data_t;

#define HCI_SNIFF_SUBRATING_EVENT_DATA_SIZE                          (sizeof(HCI_Sniff_Subrating_Event_Data_t))

   /* The following structure represents the Extended Inquiry Result    */
   /* Format that is associated with Inquiry Mode set to                */
   /*    HCI_INQUIRY_MODE_INQUIRY_RESULT_WITH_RSSI_OR_EXTENDED_RESULT   */
   /* (Version 2.1 + EDR).                                              */
typedef struct _tagHCI_Extended_Inquiry_Result_Data_t
{
   BD_ADDR_t                        BD_ADDR;
   Byte_t                           Page_Scan_Repetition_Mode;
   Byte_t                           Reserved;
   Class_of_Device_t                Class_of_Device;
   Word_t                           Clock_Offset;
   SByte_t                          RSSI;
   Extended_Inquiry_Response_Data_t Extended_Inquiry_Response;
} HCI_Extended_Inquiry_Result_Data_t;

#define HCI_EXTENDED_INQUIRY_RESULT_DATA_SIZE                        (sizeof(HCI_Extended_Inquiry_Result_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Extended Inquiry Result Event (Version 2.1 + EDR).   */
   /* * NOTE * The Num_Responses field is always 1 for extended data.   */
typedef struct _tagHCI_Extended_Inquiry_Result_Event_Data_t
{
   Byte_t                              Num_Responses;
   HCI_Extended_Inquiry_Result_Data_t  HCI_Inquiry_Result_Data;
} HCI_Extended_Inquiry_Result_Event_Data_t;

#define HCI_EXTENDED_INQUIRY_RESULT_EVENT_DATA_SIZE                  (sizeof(HCI_Extended_Inquiry_Result_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Encryption Key Refresh Event (Version 2.1 + EDR).    */
typedef struct _tagHCI_Encryption_Key_Refresh_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
} HCI_Encryption_Key_Refresh_Complete_Event_Data_t;

#define HCI_ENCRYPTION_KEY_REFRESH_COMPLETE_EVENT_DATA_SIZE          (sizeof(HCI_Encryption_Key_Refresh_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI I/O Capability Request Event (Version 2.1 + EDR).    */
typedef struct _tagHCI_IO_Capability_Request_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
} HCI_IO_Capability_Request_Event_Data_t;

#define HCI_IO_CAPABILITY_REQUEST_EVENT_DATA_SIZE                    (sizeof(HCI_IO_Capability_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI I/O Capability Response Event (Version 2.1 + EDR).   */
typedef struct _tagHCI_IO_Capability_Response_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
   Byte_t    IO_Capability;
   Byte_t    OOB_Data_Present;
   Byte_t    Authentication_Requirements;
} HCI_IO_Capability_Response_Event_Data_t;

#define HCI_IO_CAPABILITY_RESPONSE_EVENT_DATA_SIZE                   (sizeof(HCI_IO_Capability_Response_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI User Confirmation Request Event (Version 2.1 + EDR). */
typedef struct _tagHCI_User_Confirmation_Request_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
   DWord_t   Numeric_Value;
} HCI_User_Confirmation_Request_Event_Data_t;

#define HCI_USER_CONFIRMATION_REQUEST_EVENT_DATA_SIZE                (sizeof(HCI_User_Confirmation_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI User Passkey Request Event (Version 2.1 + EDR).      */
typedef struct _tagHCI_User_Passkey_Request_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
} HCI_User_Passkey_Request_Event_Data_t;

#define HCI_USER_PASSKEY_REQUEST_EVENT_DATA_SIZE                     (sizeof(HCI_User_Passkey_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Remote OOB Data Request Event (Version 2.1 + EDR).   */
typedef struct _tagHCI_Remote_OOB_Data_Request_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
} HCI_Remote_OOB_Data_Request_Event_Data_t;

#define HCI_REMOTE_OOB_DATA_REQUEST_EVENT_DATA_SIZE                  (sizeof(HCI_Remote_OOB_Data_Request_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Simple Pairing Complete Event (Version 2.1 + EDR).   */
typedef struct _tagHCI_Simple_Pairing_Complete_Event_Data_t
{
   Byte_t    Status;
   BD_ADDR_t BD_ADDR;
} HCI_Simple_Pairing_Complete_Event_Data_t;

#define HCI_SIMPLE_PAIRING_COMPLETE_EVENT_DATA_SIZE                  (sizeof(HCI_Simple_Pairing_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Link Supervision Timeout Changed Event (Version 2.1 +*/
   /* EDR).                                                             */
typedef struct _tagHCI_Link_Supervision_Timeout_Changed_Event_Data_t
{
   Word_t Connection_Handle;
   Word_t Link_Supervision_Timeout;
} HCI_Link_Supervision_Timeout_Changed_Event_Data_t;

#define HCI_LINK_SUPERVISION_TIMEOUT_CHANGED_EVENT_DATA_SIZE         (sizeof(HCI_Link_Supervision_Timeout_Changed_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Enhanced Flush Complete Event (Version 2.1 + EDR).   */
typedef struct _tagHCI_Enhanced_Flush_Complete_Event_Data_t
{
   Word_t Connection_Handle;
} HCI_Enhanced_Flush_Complete_Event_Data_t;

#define HCI_ENHANCED_FLUSH_COMPLETE_EVENT_DATA_SIZE                  (sizeof(HCI_Enhanced_Flush_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI User Passkey Notification Event (Version 2.1 + EDR). */
typedef struct _tagHCI_User_Passkey_Notification_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
   DWord_t   Passkey;
} HCI_User_Passkey_Notification_Event_Data_t;

#define HCI_USER_PASSKEY_NOTIFICATION_EVENT_DATA_SIZE                (sizeof(HCI_User_Passkey_Notification_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Keypress Notification Event (Version 2.1 + EDR).     */
typedef struct _tagHCI_Keypress_Notification_Event_Data_t
{
   BD_ADDR_t BD_ADDR;
   Byte_t    Notification_Type;
} HCI_Keypress_Notification_Event_Data_t;

#define HCI_KEYPRESS_NOTIFICATION_EVENT_DATA_SIZE                    (sizeof(HCI_Keypress_Notification_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Remote Host Supported Features Notification Event    */
   /* (Version 2.1 + EDR).                                              */
typedef struct _tagHCI_Remote_Host_Supported_Features_Notification_Event_Data_t
{
   BD_ADDR_t      BD_ADDR;
   LMP_Features_t Host_Supported_Features;
} HCI_Remote_Host_Supported_Features_Notification_Event_Data_t;

#define HCI_REMOTE_HOST_SUPPORTED_FEATURES_NOTIFICATION_EVENT_DATA_SIZE    (sizeof(HCI_Remote_Host_Supported_Features_Notification_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Physical Link Complete Event (Version 3.0 + HS).     */
typedef struct _tagHCI_Physical_Link_Complete_Event_Data_t
{
   Byte_t Status;
   Byte_t Physical_Link_Handle;
} HCI_Physical_Link_Complete_Event_Data_t;

#define HCI_PHYSICAL_LINK_COMPLETE_EVENT_DATA_SIZE                         (sizeof(HCI_Physical_Link_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Channel Selected Event (Version 3.0 + HS).           */
typedef struct _tagHCI_Channel_Selected_Event_Data_t
{
   Byte_t Physical_Link_Handle;
} HCI_Channel_Selected_Event_Data_t;

#define HCI_CHANNEL_SELECTED_EVENT_DATA_SIZE                               (sizeof(HCI_Channel_Selected_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Disconnection Physical Link Complete Event (Version  */
   /* 3.0 + HS).                                                        */
typedef struct _tagHCI_Disconnection_Physical_Link_Complete_Event_Data_t
{
   Byte_t Status;
   Byte_t Physical_Link_Handle;
   Byte_t Reason;
} HCI_Disconnection_Physical_Link_Complete_Event_Data_t;

#define HCI_DISCONNECTION_PHYSICAL_LINK_COMPLETE_EVENT_DATA_SIZE           (sizeof(HCI_Disconnection_Physical_Link_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Physical Link Loss Early Warning Event (Version 3.0 +*/
   /* HS).                                                              */
typedef struct _tagHCI_Physical_Link_Loss_Early_Warning_Event_Data_t
{
   Byte_t Physical_Link_Handle;
   Byte_t Link_Loss_Reason;
} HCI_Physical_Link_Loss_Early_Warning_Event_Data_t;

#define HCI_PHYSICAL_LINK_LOSS_EARLY_WARNING_EVENT_DATA_SIZE               (sizeof(HCI_Physical_Link_Loss_Early_Warning_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Physical Link Recovery Event (Version 3.0 + HS).     */
typedef struct _tagHCI_Physical_Link_Recovery_Event_Data_t
{
   Byte_t Physical_Link_Handle;
} HCI_Physical_Link_Recovery_Event_Data_t;

#define HCI_PHYSICAL_LINK_RECOVERY_EVENT_DATA_SIZE                         (sizeof(HCI_Physical_Link_Recovery_Event_Data_t))

   /* The following structure represents the format of the defined      */
   /* Extended Flow Spec information.  This is used with various HCI    */
   /* Commands/Events that deal with Extended Flow Specifications       */
   /* (Version 3.0 + HS).                                               */
typedef struct _tagHCI_Extended_Flow_Spec_Data_t
{
   Byte_t  Identifier;
   Byte_t  Service_Type;
   Word_t  Maximum_SDU_Size;
   DWord_t SDU_Inter_Arrival_Time;
   DWord_t Access_Latency;
   DWord_t Flush_Timeout;
} HCI_Extended_Flow_Spec_Data_t;

#define HCI_EXTENDED_FLOW_SPEC_DATA_SIZE                                   (sizeof(HCI_Extended_Flow_Spec_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Logical Link Complete Event (Version 3.0 + HS).      */
typedef struct _tagHCI_Logical_Link_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Logical_Link_Handle;
   Byte_t Physical_Link_Handle;
   Byte_t Tx_Flow_Spec_ID;
} HCI_Logical_Link_Complete_Event_Data_t;

#define HCI_LOGICAL_LINK_COMPLETE_EVENT_DATA_SIZE                          (sizeof(HCI_Logical_Link_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Disconnection Logical Link Complete Event (Version   */
   /* 3.0 + HS).                                                        */
typedef struct _tagHCI_Disconnection_Logical_Link_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Logical_Link_Handle;
   Byte_t Reason;
} HCI_Disconnection_Logical_Link_Complete_Event_Data_t;

#define HCI_DISCONNECTION_LOGICAL_LINK_COMPLETE_EVENT_DATA_SIZE            (sizeof(HCI_Disconnection_Logical_Link_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Flow Spec Modify Complete Event (Version 3.0 + HS).  */
typedef struct _tagHCI_Flow_Spec_Modify_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Handle;
} HCI_Flow_Spec_Modify_Complete_Event_Data_t;

#define HCI_FLOW_SPEC_MODIFY_COMPLETE_EVENT_DATA_SIZE                      (sizeof(HCI_Flow_Spec_Modify_Complete_Event_Data_t))

   /* The following structure is used with the HCI Number of Completed  */
   /* Data Blocks Event, and represents a single Connection Handle/Host */
   /* Number of Completed Packets/Number of Data Blocks triplet that is */
   /* required by this Event.  This structure represents an individual  */
   /* entry and a HCI Number of Completed Data Blocks Event will contain*/
   /* a variable number of these structures (Version 3.0 + HS).         */
typedef struct _tagHCI_Number_Of_Completed_Data_Blocks_Data_t
{
   Word_t Handle;
   Word_t Num_Of_Completed_Packets;
   Word_t Num_Of_Completed_Blocks;
} HCI_Number_Of_Completed_Data_Blocks_Data_t;

#define HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_DATA_SIZE                      (sizeof(HCI_Number_Of_Completed_Data_Blocks_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Number Of Completed Data Blocks Event (Version 3.0 + */
   /* HS).                                                              */

   /* The following structure represents the Data that is associated    */
   /* with the HCI Number Of Completed Data Blocks Event (Version 3.0 + */
   /* HS).  The HCI_Number_Of_Completed_Data_Blocks_Data member         */
   /* represents a variable array that can contain 0 or more entries.   */
   /* The number of Entries in this array is given by the               */
   /* Number_of_Handles member.  A utility MACRO is provided to aid in  */
   /* the calculation of the Number of Bytes that are occupied by the   */
   /* structure given a specified number of Handles.                    */
typedef struct _tagHCI_Number_Of_Completed_Data_Blocks_Event_Data_t
{
   Word_t                                     Total_Num_Data_Blocks;
   Byte_t                                     Number_of_Handles;
   HCI_Number_Of_Completed_Data_Blocks_Data_t HCI_Number_Of_Completed_Data_Blocks_Data[1];
} HCI_Number_Of_Completed_Data_Blocks_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI Number of  */
   /* Completed Data Blocks Event Data Structure based upon the number  */
   /* of HCI Number of Completed Data Blocks Event Data Entries         */
   /* associated with the Event.  The first parameter to this MACRO is  */
   /* the number of HCI Number of Completed Data Blocks Entries.        */
#define HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_DATA_SIZE(_x)            ((sizeof(HCI_Number_Of_Completed_Data_Blocks_Event_Data_t) - sizeof(HCI_Number_Of_Completed_Data_Blocks_Data_t)) + (((Byte_t)(_x))*sizeof(HCI_Number_Of_Completed_Data_Blocks_Data_t)))

#define HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_MAX_DATA_ENTRIES         ((((sizeof(Byte_t))*256)-HCI_NUMBER_OF_COMPLETED_DATA_BLOCKS_EVENT_DATA_SIZE(0))/sizeof(HCI_Number_Of_Completed_Data_Blocks_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Number Completed Data Blocks Event (Version 3.0 +    */
   /* HS).                                                              */
typedef struct _tagHCI_Short_Range_Mode_Change_Complete_Event_Data_t
{
   Byte_t Status;
   Byte_t Physical_Link_Handle;
   Byte_t Short_Range_Mode_State;
} HCI_Short_Range_Mode_Change_Complete_Event_Data_t;

#define HCI_SHORT_RANGE_MODE_CHANGE_COMPLETE_EVENT_DATA_SIZE               (sizeof(HCI_Short_Range_Mode_Change_Complete_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI AMP Status Change Event (Version 3.0 + HS).          */
typedef struct _tagHCI_AMP_Status_Change_Event_Data_t
{
   Byte_t Status;
   Byte_t AMP_Status;
} HCI_AMP_Status_Change_Event_Data_t;

#define HCI_AMP_STATUS_CHANGE_EVENT_DATA_SIZE                              (sizeof(HCI_AMP_Status_Change_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI AMP Start Test Event (Version 3.0 + HS).             */
typedef struct _tagHCI_AMP_Start_Test_Event_Data_t
{
   Byte_t Status;
   Byte_t Test_Scenario;
} HCI_AMP_Start_Test_Event_Data_t;

#define HCI_AMP_START_TEST_EVENT_DATA_SIZE                                 (sizeof(HCI_AMP_Start_Test_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI AMP Test End Event (Version 3.0 + HS).               */
typedef struct _tagHCI_AMP_Test_End_Event_Data_t
{
   Byte_t Status;
   Byte_t Test_Scenario;
} HCI_AMP_Test_End_Event_Data_t;

#define HCI_AMP_TEST_END_EVENT_DATA_SIZE                                   (sizeof(HCI_AMP_Test_End_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI AMP Receiver Report Event (Version 3.0 + HS).        */
typedef struct _tagHCI_AMP_Receiver_Report_Event_Data_t
{
   Byte_t  Controller_Type;
   Byte_t  Reason;
   DWord_t Event_Type;
   Word_t  Number_Of_Frames;
   Word_t  Number_Of_Error_Frames;
   DWord_t Number_Of_Bits;
   DWord_t Number_Of_Error_Bits;
} HCI_AMP_Receiver_Report_Event_Data_t;

#define HCI_AMP_RECEIVER_REPORT_EVENT_DATA_SIZE                            (sizeof(HCI_AMP_Receiver_Report_Event_Data_t))

   /* The following structures represent the Data that is associated    */
   /* with the LE Meta Event. (Version 4.0 + LE).                       */

   /* The following structure represents the data that is returned in a */
   /* HCI LE Meta Event with Subevent LE Connection Complete Event.     */
   /* (Version 4.0 + LE).                                               */
typedef struct _tagHCI_LE_Connection_Complete_Event_Data_t
{
   Byte_t    Status;
   Word_t    Connection_Handle;
   Byte_t    Role;
   Byte_t    Peer_Address_Type;
   BD_ADDR_t Peer_Address;
   Word_t    Conn_Interval;
   Word_t    Conn_Latency;
   Word_t    Supervision_Timeout;
   Byte_t    Master_Clock_Accuracy;
} HCI_LE_Connection_Complete_Event_Data_t;

#define HCI_LE_CONNECTION_COMPLETE_EVENT_DATA_SIZE                         (sizeof(HCI_LE_Connection_Complete_Event_Data_t))

   /* The following structure represents the data that is returned in a */
   /* HCI LE Meta Event with Subevent LE Avertising Report Event.  This */
   /* structure represents an individual entry, and the HCI LE          */
   /* Advertising Report Event structure will contain an array of       */
   /* these structures (based upon the number of responses).  (Version  */
   /* 4.0 + LE).                                                        */
typedef struct _tagHCI_LE_Advertising_Report_Data_t
{
   Byte_t             Event_Type;
   Byte_t             Address_Type;
   BD_ADDR_t          Address;
   Byte_t             Data_Length;
   Advertising_Data_t Data;
   SByte_t            RSSI;
} HCI_LE_Advertising_Report_Data_t;

#define HCI_LE_ADVERTISING_REPORT_DATA_SIZE                                (sizeof(HCI_LE_Advertising_Report_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI LE Meta Event with Subevent LE Avertising Report     */
   /* Event.  The HCI_LE_Advertising_Report_Data member represents a    */
   /* variable array that can contain 0 or more entries.  The Number of */
   /* Entries in this array is given by the Num_Responses member.  A    */
   /* utility MACRO is provided to aid in the calculation of the Number */
   /* of Bytes that are occupied by the structure given a specified     */
   /* number of Responses.  (Version 4.0 + LE).                         */
typedef struct _tagHCI_LE_Advertising_Report_Event_Data_t
{
   Byte_t                           Num_Responses;
   HCI_LE_Advertising_Report_Data_t HCI_LE_Advertising_Report_Data[1];
} HCI_LE_Advertising_Report_Event_Data_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an HCI LE         */
   /* Advertising Report Event Data Structure that must be allocated to */
   /* store the number of HCI LE Advertising Report Event Entries       */
   /* associated with the Event. The first parameter to this MACRO is   */
   /* the number of HCI LE Advertising Event Entries (Version 4.0 + LE).*/
#define HCI_LE_ADVERTISING_REPORT_EVENT_DATA_SIZE(_x)                      ((sizeof(HCI_LE_Advertising_Report_Event_Data_t) - sizeof(HCI_LE_Advertising_Report_Data_t)) + (((unsigned int)(_x))*sizeof(HCI_LE_Advertising_Report_Data_t)))

#define HCI_LE_ADVERTISING_REPORT_EVENT_MAX_DATA_ENTRIES                   ((((sizeof(Byte_t))*256)-HCI_LE_ADVERTISING_REPORT_EVENT_DATA_SIZE(0))/sizeof(HCI_LE_Advertising_Report_Data_t))

   /* The following structure represents the data that is returned in a */
   /* HCI LE Meta Event with Subevent LE Connection Update Complete     */
   /* Event (Vesion 4.0 + LE).                                          */
typedef struct _tagHCI_LE_Connection_Update_Complete_Event_Data_t
{
   Byte_t Status;
   Word_t Connection_Handle;
   Word_t Conn_Interval;
   Word_t Conn_Latency;
   Word_t Supervision_Timeout;
} HCI_LE_Connection_Update_Complete_Event_Data_t;

#define HCI_LE_CONNECTION_UPDATE_COMPLETE_EVENT_DATA_SIZE                  (sizeof(HCI_LE_Connection_Update_Complete_Event_Data_t))

   /* The following structure represents the data that is returned in a */
   /* HCI LE Meta Event with Subevent LE Read Remote Used Features      */
   /* Complete Event (Version 4.0 + LE).                                */
typedef struct _tagHCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t
{
   Byte_t        Status;
   Word_t        Connection_Handle;
   LE_Features_t LE_Features;
} HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t;

#define HCI_LE_READ_REMOTE_USED_FEATURES_COMPLETE_EVENT_DATA_SIZE          (sizeof(HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t))

   /* The following structure represents the data that is returned in a */
   /* HCI LE Meta Event with Subevent LE Long Term Key Request Event    */
   /* (Vesion 4.0 + LE).                                                */
typedef struct _tagHCI_LE_Long_Term_Key_Request_Event_Data_t
{
   Word_t          Connection_Handle;
   Random_Number_t Random_Number;
   Word_t          Encrypted_Diversifier;
} HCI_LE_Long_Term_Key_Request_Event_Data_t;

#define HCI_LE_LONG_TERM_KEY_REQUEST_EVENT_DATA_SIZE                       (sizeof(HCI_LE_Long_Term_Key_Request_Event_Data_t))

   /* The following represents the structure of an LE Meta Event.       */
typedef struct _tagHCI_LE_Meta_Event_Data_t
{
   HCI_LE_Meta_Event_Type_t LE_Event_Data_Type;
   union
   {
      HCI_LE_Connection_Complete_Event_Data_t                HCI_LE_Connection_Complete_Event_Data;
      HCI_LE_Advertising_Report_Event_Data_t                 HCI_LE_Advertising_Report_Event_Data;
      HCI_LE_Connection_Update_Complete_Event_Data_t         HCI_LE_Connection_Update_Complete_Event_Data;
      HCI_LE_Read_Remote_Used_Features_Complete_Event_Data_t HCI_LE_Read_Remote_Used_Features_Complete_Event_Data;
      HCI_LE_Long_Term_Key_Request_Event_Data_t              HCI_LE_Long_Term_Key_Request_Event_Data;
   } Event_Data;
} HCI_LE_Meta_Event_Data_t;

#define HCI_LE_META_EVENT_DATA_SIZE                                        (sizeof(HCI_LE_Meta_Event_Data_t))

   /* The following structure represents the Data that is associated    */
   /* with the HCI Platform Specific Event.                             */
typedef struct _tagHCI_Platform_Specific_Event_Data_t
{
   DWord_t  Platform_Event_Type;
   void    *Platform_Event_Data;
} HCI_Platform_Specific_Event_Data_t;

#define HCI_PLATFORM_SPECIFIC_EVENT_DATA_SIZE                              (sizeof(HCI_Platform_Specific_Event_Data_t))

   /* The following structure represents the container structure for    */
   /* Holding all HCI Event Data Data.                                  */
typedef struct _tagHCI_Event_Data_t
{
   HCI_Event_Type_t Event_Data_Type;
   Word_t           Event_Data_Size;
   union
   {
      HCI_Inquiry_Complete_Event_Data_t                            *HCI_Inquiry_Complete_Event_Data;
      HCI_Inquiry_Result_Event_Data_t                              *HCI_Inquiry_Result_Event_Data;
      HCI_Connection_Complete_Event_Data_t                         *HCI_Connection_Complete_Event_Data;
      HCI_Connection_Request_Event_Data_t                          *HCI_Connection_Request_Event_Data;
      HCI_Disconnection_Complete_Event_Data_t                      *HCI_Disconnection_Complete_Event_Data;
      HCI_Authentication_Complete_Event_Data_t                     *HCI_Authentication_Complete_Event_Data;
      HCI_Remote_Name_Request_Complete_Event_Data_t                *HCI_Remote_Name_Request_Complete_Event_Data;
      HCI_Encryption_Change_Event_Data_t                           *HCI_Encryption_Change_Event_Data;
      HCI_Change_Connection_Link_Key_Complete_Event_Data_t         *HCI_Change_Connection_Link_Key_Complete_Event_Data;
      HCI_Master_Link_Key_Complete_Event_Data_t                    *HCI_Master_Link_Key_Complete_Event_Data;
      HCI_Read_Remote_Supported_Features_Complete_Event_Data_t     *HCI_Read_Remote_Supported_Features_Complete_Event_Data;
      HCI_Read_Remote_Version_Information_Complete_Event_Data_t    *HCI_Read_Remote_Version_Information_Complete_Event_Data;
      HCI_QoS_Setup_Complete_Event_Data_t                          *HCI_QoS_Setup_Complete_Event_Data;
      HCI_Hardware_Error_Event_Data_t                              *HCI_Hardware_Error_Event_Data;
      HCI_Flush_Occurred_Event_Data_t                              *HCI_Flush_Occurred_Event_Data;
      HCI_Role_Change_Event_Data_t                                 *HCI_Role_Change_Event_Data;
      HCI_Number_Of_Completed_Packets_Event_Data_t                 *HCI_Number_Of_Completed_Packets_Event_Data;
      HCI_Mode_Change_Event_Data_t                                 *HCI_Mode_Change_Event_Data;
      HCI_Return_Link_Keys_Event_Data_t                            *HCI_Return_Link_Keys_Event_Data;
      HCI_PIN_Code_Request_Event_Data_t                            *HCI_PIN_Code_Request_Event_Data;
      HCI_Link_Key_Request_Event_Data_t                            *HCI_Link_Key_Request_Event_Data;
      HCI_Link_Key_Notification_Event_Data_t                       *HCI_Link_Key_Notification_Event_Data;
      HCI_Loopback_Command_Event_Data_t                            *HCI_Loopback_Command_Event_Data;
      HCI_Data_Buffer_Overflow_Event_Data_t                        *HCI_Data_Buffer_Overflow_Event_Data;
      HCI_Max_Slots_Change_Event_Data_t                            *HCI_Max_Slots_Change_Event_Data;
      HCI_Read_Clock_Offset_Complete_Event_Data_t                  *HCI_Read_Clock_Offset_Complete_Event_Data;
      HCI_Connection_Packet_Type_Changed_Event_Data_t              *HCI_Connection_Packet_Type_Changed_Event_Data;
      HCI_QoS_Violation_Event_Data_t                               *HCI_QoS_Violation_Event_Data;
      HCI_Page_Scan_Repetition_Mode_Change_Event_Data_t            *HCI_Page_Scan_Repetition_Mode_Change_Event_Data;
      HCI_Page_Scan_Mode_Change_Event_Data_t                       *HCI_Page_Scan_Mode_Change_Event_Data;
      HCI_Flow_Specification_Complete_Event_Data_t                 *HCI_Flow_Specification_Complete_Event_Data;
      HCI_Inquiry_Result_With_RSSI_Event_Data_t                    *HCI_Inquiry_Result_With_RSSI_Event_Data;
      HCI_Read_Remote_Extended_Features_Complete_Event_Data_t      *HCI_Read_Remote_Extended_Features_Complete_Event_Data;
      HCI_Synchronous_Connection_Complete_Event_Data_t             *HCI_Synchronous_Connection_Complete_Event_Data;
      HCI_Synchronous_Connection_Changed_Event_Data_t              *HCI_Synchronous_Connection_Changed_Event_Data;
      HCI_Sniff_Subrating_Event_Data_t                             *HCI_Sniff_Subrating_Event_Data;
      HCI_Extended_Inquiry_Result_Event_Data_t                     *HCI_Extended_Inquiry_Result_Event_Data;
      HCI_Encryption_Key_Refresh_Complete_Event_Data_t             *HCI_Encryption_Key_Refresh_Complete_Event_Data;
      HCI_IO_Capability_Request_Event_Data_t                       *HCI_IO_Capability_Request_Event_Data;
      HCI_IO_Capability_Response_Event_Data_t                      *HCI_IO_Capability_Response_Event_Data;
      HCI_User_Confirmation_Request_Event_Data_t                   *HCI_User_Confirmation_Request_Event_Data;
      HCI_User_Passkey_Request_Event_Data_t                        *HCI_User_Passkey_Request_Event_Data;
      HCI_Remote_OOB_Data_Request_Event_Data_t                     *HCI_Remote_OOB_Data_Request_Event_Data;
      HCI_Simple_Pairing_Complete_Event_Data_t                     *HCI_Simple_Pairing_Complete_Event_Data;
      HCI_Link_Supervision_Timeout_Changed_Event_Data_t            *HCI_Link_Supervision_Timeout_Changed_Event_Data;
      HCI_Enhanced_Flush_Complete_Event_Data_t                     *HCI_Enhanced_Flush_Complete_Event_Data;
      HCI_User_Passkey_Notification_Event_Data_t                   *HCI_User_Passkey_Notification_Event_Data;
      HCI_Keypress_Notification_Event_Data_t                       *HCI_Keypress_Notification_Event_Data;
      HCI_Remote_Host_Supported_Features_Notification_Event_Data_t *HCI_Remote_Host_Supported_Features_Notification_Event_Data;
      HCI_Physical_Link_Complete_Event_Data_t                      *HCI_Physical_Link_Complete_Event_Data;
      HCI_Channel_Selected_Event_Data_t                            *HCI_Channel_Selected_Event_Data;
      HCI_Disconnection_Physical_Link_Complete_Event_Data_t        *HCI_Disconnection_Physical_Link_Complete_Event_Data;
      HCI_Physical_Link_Loss_Early_Warning_Event_Data_t            *HCI_Physical_Link_Loss_Early_Warning_Event_Data;
      HCI_Physical_Link_Recovery_Event_Data_t                      *HCI_Physical_Link_Recovery_Event_Data;
      HCI_Logical_Link_Complete_Event_Data_t                       *HCI_Logical_Link_Complete_Event_Data;
      HCI_Disconnection_Logical_Link_Complete_Event_Data_t         *HCI_Disconnection_Logical_Link_Complete_Event_Data;
      HCI_Flow_Spec_Modify_Complete_Event_Data_t                   *HCI_Flow_Spec_Modify_Complete_Event_Data;
      HCI_Number_Of_Completed_Data_Blocks_Event_Data_t             *HCI_Number_Of_Completed_Data_Blocks_Event_Data;
      HCI_Short_Range_Mode_Change_Complete_Event_Data_t            *HCI_Short_Range_Mode_Change_Complete_Event_Data;
      HCI_AMP_Status_Change_Event_Data_t                           *HCI_AMP_Status_Change_Event_Data;
      HCI_AMP_Start_Test_Event_Data_t                              *HCI_AMP_Start_Test_Event_Data;
      HCI_AMP_Test_End_Event_Data_t                                *HCI_AMP_Test_End_Event_Data;
      HCI_AMP_Receiver_Report_Event_Data_t                         *HCI_AMP_Receiver_Report_Event_Data;
      HCI_LE_Meta_Event_Data_t                                     *HCI_LE_Meta_Event_Data;
      HCI_Platform_Specific_Event_Data_t                           *HCI_Platform_Specific_Event_Data;
      void                                                         *HCI_Unknown_Event_Data;
   } Event_Data;
} HCI_Event_Data_t;

#define HCI_EVENT_DATA_SIZE                                                (sizeof(HCI_Event_Data_t))

   /* The following declared type represents the Prototype Function for */
   /* an HCI Event Receive Data Callback.  This function will be called */
   /* whenever a complete HCI Event Packet has been received by the     */
   /* HCI Layer that is associated with the specified Bluetooth Stack   */
   /* ID.  This function passes to the caller the Bluetooth Stack ID,   */
   /* the HCI Event Data that was received and the HCI Event Callback   */
   /* Parameter that was specified when this Callback was installed.    */
   /* The caller is free to use the contents of the HCI Event Data ONLY */
   /* in the context of this callback.  If the caller requires the Data */
   /* for a longer period of time, then the callback function MUST copy */
   /* the data into another Data Buffer.  This function is guaranteed   */
   /* NOT to be invoked more than once simultaneously for the specified */
   /* installed callback (i.e. this function DOES NOT have be           */
   /* reentrant).  It Needs to be noted however, that if the same       */
   /* Callback is installed more than once, then the callbacks will be  */
   /* called serially.  Because of this, the processing in this function*/
   /* should be as efficient as possible.  It should also be noted that */
   /* this function is called in the Thread Context of a Thread that    */
   /* the User does NOT own.  Therefore, processing in this function    */
   /* should be as efficient as possible (this argument holds anyway    */
   /* because another HCI Event Packet will not be processed while this */
   /* function call is outstanding).                                    */
   /* ** NOTE ** This function MUST NOT Block and wait for events that  */
   /*            can only be satisfied by Receiving HCI Event Packets.  */
   /*            A Deadlock WILL occur because NO HCI Event Receive     */
   /*            Callbacks will be issued while this function is        */
   /*            currently outstanding.                                 */
typedef void (BTPSAPI *HCI_Event_Callback_t)(unsigned int BluetoothStackID, HCI_Event_Data_t *HCI_Event_Data, unsigned long CallbackParameter);

   /* The following declared type represents the Prototype Function for */
   /* an ACL Data Receive Data Callback.  This function will be called  */
   /* whenever a complete ACL Data Packet has been received by the HCI  */
   /* Layer that is associated with the specified Bluetooth Stack ID.   */
   /* This function passes to the caller the Bluetooth Stack ID, the    */
   /* ACL Data that was received and the HCI ACL Data Callback Parameter*/
   /* that was specified when this Callback was installed.  The caller  */
   /* is free to use the ACL Data Contents ONLY in the context of this  */
   /* callback.  If the caller requires the Data for a longer period of */
   /* time, then the callback function MUST copy the data into another  */
   /* Data Buffer.  This function is guaranteed NOT to be invoked more  */
   /* than once simultaneously for the specified installed callback     */
   /* (i.e. this function DOES NOT have be reentrant).  It needs to be  */
   /* noted however, that if the same Callback is installed more than   */
   /* once, then the callbacks will be called serially.  Because of     */
   /* this, the processing in this function should be as efficient as   */
   /* possible.  It should also be noted that this function is called   */
   /* in the Thread Context of a Thread that the User does NOT own.     */
   /* Therefore, processing in this function should be as efficient as  */
   /* possible (this argument holds anyway because another ACL Data     */
   /* Packet will not be processed while this function call is          */
   /* outstanding).                                                     */
   /* ** NOTE ** This function MUST NOT Block and wait for events that  */
   /*            can only be satisfied by Receiving HCI Event Packets.  */
   /*            A Deadlock WILL occur because NO HCI Event Receive     */
   /*            Callbacks will be issued while this function is        */
   /*            currently outstanding.                                 */
typedef void (BTPSAPI *HCI_ACL_Data_Callback_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flags, Word_t ACLDataLength, Byte_t *ACLData, unsigned long CallbackParameter);

   /* The following declared type represents the Prototype Function for */
   /* an SCO Data Receive Data Callback.  This function will be called  */
   /* whenever a complete SCO Data Packet has been received by the HCI  */
   /* Layer that is associated with the specified Bluetooth Stack ID.   */
   /* This function passes to the caller the Bluetooth Stack ID, any    */
   /* SCO Flags that were returned, the SCO Data that was received and  */
   /* the HCI SCO Data Callback Parameter that was specified when this  */
   /* Callback was installed.  The caller is free to use the SCO Data   */
   /* Contents ONLY in the context of this callback.  If the caller     */
   /* requires the Data for a longer period of time, then the callback  */
   /* function MUST copy the data into another Data Buffer.  This       */
   /* function is guaranteed NOT to be invoked more than once           */
   /* simultaneously for the specified installed callback (i.e. this    */
   /* function DOES NOT have be reentrant).  It needs to be noted       */
   /* however, that if the same Callback is installed more than once,   */
   /* then the callbacks will be called serially.  Because of this, the */
   /* processing in this function should be as efficient as possible.   */
   /* It should also be noted that this function is called in the       */
   /* Thread Context of a Thread that the User does NOT own.  Therefore,*/
   /* processing in this function should be as efficient as possible    */
   /* (this argument holds anyway because another SCO Data Packet will  */
   /* not be processed while this function call is outstanding).        */
   /* ** NOTE ** This function MUST NOT Block and wait for events that  */
   /*            can only be satisfied by Receiving HCI Event Packets.  */
   /*            A Deadlock WILL occur because NO HCI Event Receive     */
   /*            Callbacks will be issued while this function is        */
   /*            currently outstanding.                                 */
typedef void (BTPSAPI *HCI_SCO_Data_Callback_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flags, Byte_t SCODataLength, Byte_t *SCOData, unsigned long CallbackParameter);

   /* HCI API's.                                                        */

   /* The following function exists to allow the caller a simple        */
   /* mechanism for determining the HCI Version that is supported by    */
   /* the HCI API Layer present for the specified Bluetooth Protocol    */
   /* Stack.  The first parameter to this function is the Bluetooth     */
   /* Protocol Stack ID of the Bluetooth Protocol Stack that was        */
   /* successfully opened.  The second parameter is a pointer to a      */
   /* Variable that will receive the HCI Version Information.  This     */
   /* value will only be valid if this function returns zero (which     */
   /* indicates a successful call to the function).  This function      */
   /* returns a negative error code as the return value if the call to  */
   /* this function failed.                                             */
   /* * NOTE * This function should be called instead of issuing an     */
   /*          HCI_Read_Local_Version_Information() function call       */
   /*          because this call will NOT contact the Bluetooth Device  */
   /*          to query the version.  This mechanism is provided to     */
   /*          provide a more efficient, abstracted mechanism to        */
   /*          determine the HCI Specification Version supported.       */
BTPSAPI_DECLARATION int BTPSAPI HCI_Version_Supported(unsigned int BluetoothStackID, HCI_Version_t *HCI_Version);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Version_Supported_t)(unsigned int BluetoothStackID, HCI_Version_t *HCI_Version);
#endif

   /* The following function exists to allow the caller a simple        */
   /* mechanism for determining if a specific HCI function is supported */
   /* by the HCI API Layer present for the specified Bluetooth Protocol */
   /* Stack.  The first parameter to this function is the Bluetooth     */
   /* Protocol Stack ID of the Bluetooth Protocol Stack that was        */
   /* successfully opened.  The second parameter is the supported HCI   */
   /* Command Bit Number (defined in HCITypes.h) for the specified HCI  */
   /* Command that is to be tested.  This function returns a negative   */
   /* error code as the return value if the call to this function       */
   /* failed, zero if the command is NOT supported, or a positive,      */
   /* non-zero, value if the HCI command is supported.                  */
   /* * NOTE * This function should be called instead of issuing an     */
   /*          HCI_Read_Local_Supported_Commands() function call        */
   /*          because this call will NOT contact the Bluetooth Device  */
   /*          to query the version (it is already cached in the        */
   /*          HCI layer).  Also, this function will return the correct */
   /*          value for Bluetooth Devices that do not support the      */
   /*          above call (i.e. Pre Bluetooth 1.2 devices).  This       */
   /*          mechanism is provided to provide a more efficient,       */
   /*          abstracted mechanism to determine if a specified HCI     */
   /*          command is supported by the local Bluetooth Device.      */
   /* * NOTE * The final parameter to this function should be a contant */
   /*          from HCITypes.h for the supported HCI Commands (i.e.     */
   /*          of the format HCI_SUPPORTED_COMMAND_xxx_BIT_NUMBER, where*/
   /*          "xxx" varies depending upon the command being tested).   */
BTPSAPI_DECLARATION int BTPSAPI HCI_Command_Supported(unsigned int BluetoothStackID, unsigned int SupportedCommandBitNumber);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Command_Supported_t)(unsigned int BluetoothStackID, unsigned int SupportedCommandBitNumber);
#endif

   /* The following function is responsible for registering the         */
   /* specified HCI Event Callback Function with the Bluetooth Protocol */
   /* Stack specified by the BluetoothStackID parameter.  The           */
   /* HCIEventCallback parameter is a pointer to the Callback Function  */
   /* and IS NOT optional.  The CallbackParameter parameter is a        */
   /* parameter that the caller can specify which will be provided as   */
   /* a function argument when the Callback Function is called.  This   */
   /* function returns a positive, non-zero value if the specified      */
   /* HCI Event Callback was registered, or a negative value if the     */
   /* callback was unable to be registered.  Upon success, this return  */
   /* value can be used as an argument to HCI_UnRegisterCallback to     */
   /* Remove the Registered Callback from the associated Bluetooth      */
   /* Stack.                                                            */
BTPSAPI_DECLARATION int BTPSAPI HCI_Register_Event_Callback(unsigned int BluetoothStackID, HCI_Event_Callback_t HCI_EventCallback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Register_Event_Callback_t)(unsigned int BluetoothStackID, HCI_Event_Callback_t HCI_EventCallback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for registering the         */
   /* specified HCI ACL Data Callback Function with the Bluetooth       */
   /* Protocol Stack specified by the BluetoothStackID parameter.  The  */
   /* HCIACLDataCallback parameter is a pointer to the Callback Function*/
   /* and IS NOT optional.  The CallbackParameter parameter is a        */
   /* parameter that the caller can specify which will be provided as   */
   /* a function argument when the Callback Function is called.  This   */
   /* function returns a positive, non-zero value if the specified      */
   /* HCI Event Callback was registered, or a negative value if the     */
   /* callback was unable to be registered.  Upon success, this return  */
   /* value can be used as an argument to HCI_UnRegisterCallback to     */
   /* Remove the Registered Callback from the associated Bluetooth      */
   /* Stack.                                                            */
BTPSAPI_DECLARATION int BTPSAPI HCI_Register_ACL_Data_Callback(unsigned int BluetoothStackID, HCI_ACL_Data_Callback_t HCI_ACLDataCallback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Register_ACL_Data_Callback_t)(unsigned int BluetoothStackID, HCI_ACL_Data_Callback_t HCI_ACLDataCallback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for registering the         */
   /* specified HCI SCO Data Callback Function with the Bluetooth       */
   /* Protocol Stack specified by the BluetoothStackID parameter.  The  */
   /* HCISCODataCallback parameter is a pointer to the Callback Function*/
   /* and IS NOT optional.  The CallbackParameter parameter is a        */
   /* parameter that the caller can specify which will be provided as   */
   /* a function argument when the Callback Function is called.  This   */
   /* function returns a positive, non-zero value if the specified      */
   /* HCI Event Callback was registered, or a negative value if the     */
   /* callback was unable to be registered.  Upon success, this return  */
   /* value can be used as an argument to HCI_UnRegisterCallback to     */
   /* Remove the Registered Callback from the associated Bluetooth      */
   /* Stack.                                                            */
BTPSAPI_DECLARATION int BTPSAPI HCI_Register_SCO_Data_Callback(unsigned int BluetoothStackID, HCI_SCO_Data_Callback_t HCI_SCODataCallback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Register_SCO_Data_Callback_t)(unsigned int BluetoothStackID, HCI_SCO_Data_Callback_t HCI_SCODataCallback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for removing a previously   */
   /* installed HCI Callback (either HCI Event, HCI ACL Data, OR HCI    */
   /* SCO Data) for the Bluetooth Protocol Stack specified by the       */
   /* BluetoothStackID parameter.  The second parameter to this         */
   /* function is the Callback ID and is obtained via a successful call */
   /* to either the HCI_Register_Event_Callback() function, the         */
   /* HCI_Register_ACL_Data_Callback() function, OR the                 */
   /* HCI_Register_SCO_Data_Callback() function.  This function returns */
   /* zero if the specified callback was removed, or a negative return  */
   /* value if the callback was unable to be removed.                   */
BTPSAPI_DECLARATION int BTPSAPI HCI_Un_Register_Callback(unsigned int BluetoothStackID, unsigned int CallbackID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Un_Register_Callback_t)(unsigned int BluetoothStackID, unsigned int CallbackID);
#endif

   /* The following function is responsible for sending HCI ACL Packets */
   /* to the Bluetooth Device specifed by the BluetoothStackID          */
   /* Parameter.  This function accepts as it's second argument, a      */
   /* Connection Handle to send the ACL Data Packet to.  This function  */
   /* accepts as it's third argument, the HCI ACL Flags to specify with */
   /* the Connection Handle when building the ACL Packet.  The fourth   */
   /* and fifth parameters specify the Length of the ACL Data, and the  */
   /* physical ACL Data to send, respectively.  The ACLDataLength       */
   /* parameter specifies the number of Bytes in the Buffer pointed to  */
   /* by ACLData to send.  The caller IS NOT responsible for submitting */
   /* an HCI ACL Data Packet.  This function will format an HCI ACL Data*/
   /* Packet in the correct format and submit it to the Bluetooth Device*/
   /* that is specified.  This function returns zero if the Packet was  */
   /* successfully sent, otherwise this function returns a negative     */
   /* error code.                                                       */
BTPSAPI_DECLARATION int BTPSAPI HCI_Send_ACL_Data(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flags, Word_t ACLDataLength, Byte_t *ACLData);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Send_ACL_Data_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flags, Word_t ACLDataLength, Byte_t *ACLData);
#endif

   /* The following function is responsible for sending HCI SCO Packets */
   /* to the Bluetooth Device specifed by the BluetoothStackID          */
   /* Parameter.  This function accepts as it's second argument, a      */
   /* Connection Handle to send the SCO Data Packet to.  The Flags      */
   /* parameter is currently NOT used in the existing Bluetooth         */
   /* Specification.  However, this function will pass off whatever Flag*/
   /* values you pass here.  The fourth and fifth parameters specify the*/
   /* Length of the SCO Data, and the physical SCO Data to send,        */
   /* respectively.  The SCODataLength parameter specifies the number of*/
   /* Bytes in the Buffer pointed to by SCOData to send.  The caller IS */
   /* NOT responsible for submitting an HCI SCO Data Packet.  This      */
   /* function will format an HCI SCO Data Packet in the correct format */
   /* and submit it to the Bluetooth Device that is specified.  This    */
   /* function returns zero if the Packet was successfully sent,        */
   /* otherwise this function returns a negative error code.            */
BTPSAPI_DECLARATION int BTPSAPI HCI_Send_SCO_Data(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flags, Byte_t SCODataLength, Byte_t *SCOData);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Send_SCO_Data_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flags, Byte_t SCODataLength, Byte_t *SCOData);
#endif

   /* HCI Command API's (Generic).                                      */

   /* The following function issues a Raw HCI Command to the Bluetooth  */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the LengthResult variable will contain   */
   /* the Number of Bytes that are valid in the BufferResult variable.  */
   /* The WaitForResponse flag, specifies whether or not this function  */
   /* is to wait for a response from the Bluetooth Device.  This        */
   /* parameter is provided because the Bluetooth Device may not issue  */
   /* any response for this HCI Command.  If you (the caller know that  */
   /* the Bluetooth Device does NOT return data, then set this          */
   /* parameter to FALSE.  If you want to be absolutely sure, you can   */
   /* wait for the Timeout, however the calling therad will block until */
   /* an invalid response OR the Timeout occurs (valid data).           */
   /* The Command_OGF parameter specifies the Bluetooth Command OGF     */
   /* of the Command, wheras the Command_OCF specifies the Bluetooth    */
   /* Command OCF.  The Command_Length parameter specifies the number   */
   /* of bytes to send from the Buffer specified by the Command_Data    */
   /* parameter.  The Command_Data parameter is ignored if              */
   /* Command_Length is zero, and the LengthResult and BufferResult     */
   /* parameters are ignored if the WaitForResponse Flag is FALSE.      */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Send_Raw_Command(unsigned int BluetoothStackID, Byte_t Command_OGF, Word_t Command_OCF, Byte_t Command_Length, Byte_t Command_Data[], Byte_t *StatusResult, Byte_t *LengthResult, Byte_t *BufferResult, Boolean_t WaitForResponse);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Send_Raw_Command_t)(unsigned int BluetoothStackID, Byte_t Command_OGF, Word_t Command_OCF, Byte_t Command_Length, Byte_t Command_Data[], Byte_t *StatusResult, Byte_t *LengthResult, Byte_t *BufferResult, Boolean_t WaitForResponse);
#endif

   /* The following function issues the appropriate call to an HCI      */
   /* driver to get SCO data delivery via the HCI channel enabled or    */
   /* disabled. This function returns zero if successful, or a non-zero */
   /* value if there was an error.                                      */
BTPSAPI_DECLARATION int BTPSAPI HCI_Change_SCO_Configuration(unsigned int BluetoothStackID, HCI_SCOConfiguration_t SCOConfiguration);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Change_SCO_Configuration_t) (unsigned int BluetoothStackID, HCI_SCOConfiguration_t SCOConfiguration);
#endif

   /* The following function issues the appropriate calls to an HCI     */
   /* driver to set the current list of SCO connection handles.  This   */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.                                                     */
BTPSAPI_DECLARATION int BTPSAPI HCI_Change_SCO_Configuration_Handles(unsigned int BluetoothStackID, unsigned int NumberHandles, Word_t *ConnectionHandleList);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
    typedef int (BTPSAPI *PFN_HCI_Change_SCO_Configuration_Handles_t)(unsigned int BluetoothStackID, unsigned int NumberHandles, Word_t *ConnectionHandleList);
#endif

   /* The following function issues the appropriate call to an HCI      */
   /* driver to perform a reconfiguration operation with the specified  */
   /* reconfiguration information.  This function returns a zero or     */
   /* positive value if successful, or a negative value if there was an */
   /* error.                                                            */
   /* * NOTE * This function should ONLY be used if the caller has      */
   /*          explicit knowledge of the reconfiguration process being  */
   /*          requested.                                               */
BTPSAPI_DECLARATION int BTPSAPI HCI_Reconfigure_Driver(unsigned int BluetoothStackID, Boolean_t ResetStateMachines, HCI_Driver_Reconfigure_Data_t *DriverReconfigureData);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Reconfigure_Driver_t)(unsigned int BluetoothStackID, Boolean_t ResetStateMachines, HCI_Driver_Reconfigure_Data_t *DriverReconfigureData);
#endif

   /* The following function is responsible for enabling and disabling  */
   /* handling of Controller to Host Flow Control by this module.  The  */
   /* final two parameters to this function specify the Number of ACL   */
   /* and SCO Data Packets that the Controller can send to the Host     */
   /* without the Host sending credits back to the controller.  This    */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.                                                     */
   /* * NOTE * If NumberOfACLPackets and NumberOfSCOPackets are both    */
   /*          ZERO, then Controller to Host Flow Control will be       */
   /*          disabled.                                                */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_Host_Flow_Control(unsigned int BluetoothStackID, Word_t NumberOfACLPackets, Word_t NumberOfSCOPackets);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_Host_Flow_Control_t)(unsigned int BluetoothStackID, Word_t NumberOfACLPackets, Word_t NumberOfSCOPackets);
#endif

   /* The following function is responsible for querying the Controller */
   /* to Host Flow Control Configuration of this Module.  The final two */
   /* parameters to this function specify pointers to return the Number */
   /* of ACL and SCO Data Packets that the Controller can send to the   */
   /* Host without the Host sending credits back to the controller.     */
   /* This function returns zero if successful, or a non-zero value if  */
   /* there was an error.                                               */
   /* * NOTE * If NumberOfACLPackets and NumberOfSCOPackets are both set*/
   /*          to ZERO on a successfull call to this function, then     */
   /*          Controller to Host Flow Control will be disabled.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Query_Host_Flow_Control(unsigned int BluetoothStackID, Word_t *NumberOfACLPackets, Word_t *NumberOfSCOPackets);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Query_Host_Flow_Control_t)(unsigned int BluetoothStackID, Word_t *NumberOfACLPackets, Word_t *NumberOfSCOPackets);
#endif

   /* HCI Command API's (Link Control).                                 */

   /* The following function issues the HCI_Inquiry Command to the      */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Inquiry(unsigned int BluetoothStackID, LAP_t LAP, Byte_t Inquiry_Length, Byte_t Num_Responses, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Inquiry_t)(unsigned int BluetoothStackID, LAP_t LAP, Byte_t Inquiry_Length, Byte_t Num_Responses, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Inquiry_Cancel Command to   */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Inquiry_Cancel(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Inquiry_Cancel_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Periodic_Inquiry_Mode       */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Periodic_Inquiry_Mode(unsigned int BluetoothStackID, Word_t Max_Period_Length, Word_t Min_Period_Length, LAP_t LAP, Byte_t Inquiry_Length, Byte_t Num_Responses, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Periodic_Inquiry_Mode_t)(unsigned int BluetoothStackID, Word_t Max_Period_Length, Word_t Min_Period_Length, LAP_t LAP, Byte_t Inquiry_Length, Byte_t Num_Responses, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Exit_Periodic_Inquiry_Mode  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Exit_Periodic_Inquiry_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Exit_Periodic_Inquiry_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Create_Connection Command to*/
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Create_Connection(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Packet_Type, Byte_t Page_Scan_Repetition_Mode, Byte_t Page_Scan_Mode, Word_t Clock_Offset, Byte_t Allow_Role_Switch, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Create_Connection_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Packet_Type, Byte_t Page_Scan_Repetition_Mode, Byte_t Page_Scan_Mode, Word_t Clock_Offset, Byte_t Allow_Role_Switch, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Disconnect Command to the   */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Disconnect(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Reason, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Disconnect_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Reason, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Add_SCO_Connection Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Add_SCO_Connection(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Packet_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Add_SCO_Connection_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Packet_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Accept_Connection_Request   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Accept_Connection_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Role, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Accept_Connection_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Role, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Reject_Connection_Request   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Reject_Connection_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Reason, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Reject_Connection_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Reason, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Link_Key_Request_Reply      */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Link_Key_Request_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Link_Key_t Link_Key, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Link_Key_Request_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Link_Key_t Link_Key, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Link_Key_Request_Negative_Reply Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the BD_ADDRResult variable will     */
   /* contain the BD_ADDR Result returned from the Bluetooth Device.    */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Link_Key_Request_Negative_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Link_Key_Request_Negative_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the HCI_PIN_Code_Request_Reply      */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_PIN_Code_Request_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t PIN_Code_Length, PIN_Code_t PIN_Code, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_PIN_Code_Request_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t PIN_Code_Length, PIN_Code_t PIN_Code, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_PIN_Code_Request_Negative_Reply Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the BD_ADDRResult variable will     */
   /* contain the BD_ADDR Result returned from the Bluetooth Device.    */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_PIN_Code_Request_Negative_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_PIN_Code_Request_Negative_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Change_Connection_Packet_Type Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Change_Connection_Packet_Type(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Packet_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Change_Connection_Packet_Type_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Packet_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Authentication_Requested    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Authentication_Requested(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Authentication_Requested_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Set_Connection_Encryption   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_Connection_Encryption(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Encryption_Enable, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_Connection_Encryption_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Encryption_Enable, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Change_Connection_Link_Key  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Change_Connection_Link_Key(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Change_Connection_Link_Key_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Master_Link_Key Command     */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Master_Link_Key(unsigned int BluetoothStackID, Byte_t Key_Flag, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Master_Link_Key_t)(unsigned int BluetoothStackID, Byte_t Key_Flag, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Remote_Name_Request Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Remote_Name_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Page_Scan_Repetition_Mode, Byte_t Page_Scan_Mode, Word_t Clock_Offset, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Remote_Name_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Page_Scan_Repetition_Mode, Byte_t Page_Scan_Mode, Word_t Clock_Offset, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Remote_Supported_Features Command to the Bluetooth Device*/
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Remote_Supported_Features(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Remote_Supported_Features_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Remote_Version_Information Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Remote_Version_Information(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Remote_Version_Information_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Clock_Offset Command   */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Clock_Offset(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Clock_Offset_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Link Control - Version 1.2).                   */

   /* The following function issues the HCI_Create_Connection_Cancel    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Create_Connection_Cancel(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Create_Connection_Cancel_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the HCI_Remote_Name_Request_Cancel  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Remote_Name_Request_Cancel(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Remote_Name_Request_Cancel_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Remote_Extended_Features Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Remote_Extended_Features(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Page_Number, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Remote_Extended_Features_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Page_Number, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_LMP_Handle Command to  */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult variable will*/
   /* contain the Connection Handle Result returned from the Bluetooth  */
   /* Device AND the LMP_HandleResult variable will contain the LMP     */
   /* Handle Result returned from the Device AND the ReservedResult     */
   /* variable will contain the Reserved Result returned from the       */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_LMP_Handle(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *LMP_HandleResult, DWord_t *ReservedResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_LMP_Handle_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *LMP_HandleResult, DWord_t *ReservedResult);
#endif

   /* The following function issues the HCI_Setup_Sychronous_Connection */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Setup_Synchronous_Connection(unsigned int BluetoothStackID, Word_t Connection_Handle, DWord_t Transmit_Bandwidth, DWord_t Receive_Bandwidth, Word_t Max_Latency, Word_t Voice_Setting, Byte_t Retransmission_Effort, Word_t Packet_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Setup_Synchronous_Connection_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, DWord_t Transmit_Bandwidth, DWord_t Receive_Bandwidth, Word_t Max_Latency, Word_t Voice_Setting, Byte_t Retransmission_Effort, Word_t Packet_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Accept_Sychronous_Connection_Request Command to the Bluetooth */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Accept_Synchronous_Connection_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, DWord_t Transmit_Bandwidth, DWord_t Receive_Bandwidth, Word_t Max_Latency, Word_t Content_Format, Byte_t Retransmission_Effort, Word_t Packet_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Accept_Synchronous_Connection_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, DWord_t Transmit_Bandwidth, DWord_t Receive_Bandwidth, Word_t Max_Latency, Word_t Content_Format, Byte_t Retransmission_Effort, Word_t Packet_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Reject_Sychronous_Connection_Request Command to the Bluetooth */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Reject_Synchronous_Connection_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Reason, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Reject_Synchronous_Connection_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Reason, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Link Control - Version 2.1 + EDR).             */

   /* The following function issues the HCI_IO_Capability_Request_Reply */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_IO_Capability_Request_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t IO_Capability, Byte_t OOB_Data_Present, Byte_t Authentication_Requirements, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_IO_Capability_Request_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t IO_Capability, Byte_t OOB_Data_Present, Byte_t Authentication_Requirements, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_User_Confirmation_Request_Reply Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the BD_ADDRResult variable will contain  */
   /* the BD_ADDR Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_User_Confirmation_Request_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_User_Confirmation_Request_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_User_Confirmation_Request_Negative_Reply Command to the       */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the BD_ADDRResult variable will contain  */
   /* the BD_ADDR Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_User_Confirmation_Request_Negative_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_User_Confirmation_Request_Negative_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the HCI_User_Passkey_Request_Reply  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_User_Passkey_Request_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, DWord_t Numeric_Value, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_User_Passkey_Request_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, DWord_t Numeric_Value, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_User_Passkey_Request_Negative_Reply Command to the Bluetooth  */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the BD_ADDRResult variable will contain  */
   /* the BD_ADDR Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_User_Passkey_Request_Negative_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_User_Passkey_Request_Negative_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Remote_OOB_Data_Request_Reply Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the BD_ADDRResult variable will contain the BD_ADDR Result    */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Remote_OOB_Data_Request_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Simple_Pairing_Hash_t Simple_Pairing_Hash, Simple_Pairing_Randomizer_t Simple_Pairing_Randomizer, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Remote_OOB_Data_Request_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Simple_Pairing_Hash_t Simple_Pairing_Hash, Simple_Pairing_Randomizer_t Simple_Pairing_Randomizer, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Remote_OOB_Data_Request_Negative_Reply Command to the         */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the BD_ADDRResult variable will contain  */
   /* the BD_ADDR Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Remote_OOB_Data_Request_Negative_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Remote_OOB_Data_Request_Negative_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_IO_Capability_Request_Negative_Reply Command to the Bluetooth */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the BD_ADDRResult variable will contain  */
   /* the BD_ADDR Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_IO_Capability_Request_Negative_Reply(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Reason, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_IO_Capability_Request_Negative_Reply_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Reason, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* HCI Command API's (Link Control - Version 3.0 + HS).              */

   /* The following function issues the HCI_Create_Physical_Link Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Create_Physical_Link(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Dedicated_AMP_Key_Length, Byte_t Dedicated_AMP_Key_Type, Byte_t Dedicated_AMP_Key[], Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Create_Physical_Link_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Dedicated_AMP_Key_Length, Byte_t Dedicated_AMP_Key_Type, Byte_t Dedicated_AMP_Key[], Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Accept_Physical_Link_Request*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Accept_Physical_Link_Request(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Dedicated_AMP_Key_Length, Byte_t Dedicated_AMP_Key_Type, Byte_t Dedicated_AMP_Key[], Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Accept_Physical_Link_Request_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Dedicated_AMP_Key_Length, Byte_t Dedicated_AMP_Key_Type, Byte_t Dedicated_AMP_Key[], Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Disconnect_Physical_Link    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Disconnect_Physical_Link(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Reason, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Disconnect_Physical_Link_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Reason, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Create_Logical_Link Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Create_Logical_Link(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, HCI_Extended_Flow_Spec_Data_t *Tx_Flow_Spec, HCI_Extended_Flow_Spec_Data_t *Rx_Flow_Spec, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Create_Logical_Link_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, HCI_Extended_Flow_Spec_Data_t *Tx_Flow_Spec, HCI_Extended_Flow_Spec_Data_t *Rx_Flow_Spec, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Accept_Logical_Link Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Accept_Logical_Link(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, HCI_Extended_Flow_Spec_Data_t *Tx_Flow_Spec, HCI_Extended_Flow_Spec_Data_t *Rx_Flow_Spec, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Accept_Logical_Link_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, HCI_Extended_Flow_Spec_Data_t *Tx_Flow_Spec, HCI_Extended_Flow_Spec_Data_t *Rx_Flow_Spec, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Disconnect_Logical_Link     */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Disconnect_Logical_Link(unsigned int BluetoothStackID, Word_t Logical_Link_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Disconnect_Logical_Link_t)(unsigned int BluetoothStackID, Word_t Logical_Link_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Logical_Link_Cancel Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Physical_Link_HandleResult will      */
   /* contain the Physical Link Handle returned from the Bluetooth      */
   /* Device AND the Tx_Flow_Spec_IDResult will return the Tx Flow Spec */
   /* ID returned from the Bluetooth Device.                            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Logical_Link_Cancel(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Tx_Flow_Spec_ID, Byte_t *StatusResult, Byte_t *Physical_Link_HandleResult, Byte_t *Tx_Flow_Spec_IDResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Logical_Link_Cancel_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Tx_Flow_Spec_ID, Byte_t *StatusResult, Byte_t *Physical_Link_HandleResult, Byte_t *Flow_Spec_IDResult);
#endif

   /* The following function issues the HCI_Flow_Spec_Modify Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Flow_Spec_Modify(unsigned int BluetoothStackID, Word_t Handle, HCI_Extended_Flow_Spec_Data_t *Tx_Flow_Spec, HCI_Extended_Flow_Spec_Data_t *Rx_Flow_Spec, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Flow_Spec_Modify_t)(unsigned int BluetoothStackID, Word_t Handle, HCI_Extended_Flow_Spec_Data_t *Tx_Flow_Spec, HCI_Extended_Flow_Spec_Data_t *Rx_Flow_Spec, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Link Policy).                                  */

   /* The following function issues the HCI_Hold_Mode Command to the    */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Hold_Mode(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Hold_Mode_Max_Interval, Word_t Hold_Mode_Min_Interval, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Hold_Mode_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Hold_Mode_Max_Interval, Word_t Hold_Mode_Min_Interval, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Sniff_Mode Command to the   */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Sniff_Mode(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Sniff_Max_Interval, Word_t Sniff_Min_Interval, Word_t Sniff_Attempt, Word_t Sniff_Timeout, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Sniff_Mode_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Sniff_Max_Interval, Word_t Sniff_Min_Interval, Word_t Sniff_Attempt, Word_t Sniff_Timeout, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Exit_Sniff_Mode Command to  */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Exit_Sniff_Mode(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Exit_Sniff_Mode_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Park_Mode Command to the    */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Park_Mode(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Beacon_Max_Interval, Word_t Beacon_Min_Interval, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Park_Mode_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Beacon_Max_Interval, Word_t Beacon_Min_Interval, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Exit_Park_Mode Command to   */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Exit_Park_Mode(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Exit_Park_Mode_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_QoS_Setup Command to the    */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_QoS_Setup(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Flags, Byte_t Service_Type, DWord_t Token_Rate, DWord_t Peak_Bandwidth, DWord_t Latency, DWord_t Delay_Variation, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_QoS_Setup_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Flags, Byte_t Service_Type, DWord_t Token_Rate, DWord_t Peak_Bandwidth, DWord_t Latency, DWord_t Delay_Variation, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Role_Discovery Command to   */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult will contain */
   /* the Connection_Handle Result returned from the Bluetooth Device   */
   /* AND Current_RoleResult will contain the Current Role Result       */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Role_Discovery(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Current_RoleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Role_Discovery_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Current_RoleResult);
#endif

   /* The following function issues the HCI_Switch_Role Command to the  */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Switch_Role(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Role, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Switch_Role_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Role, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Link_Policy_Settings   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult will contain the Connection_Handle Result */
   /* returned from the Bluetooth Device AND Link_Policy_SettingsResult */
   /* will contain the Link Policy Settings Result returned from the    */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Link_Policy_Settings(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Link_Policy_SettingsResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Link_Policy_Settings_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Link_Policy_SettingsResult);
#endif

   /* The following function issues the HCI_Write_Link_Policy_Settings  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult will contain the Connection_Handle Result */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Link_Policy_Settings(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Link_Policy_Settings, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Link_Policy_Settings_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Link_Policy_Settings, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* HCI Command API's (Link Policy - Version 1.2).                    */

   /* The following function issues the                                 */
   /* HCI_Read_Default_Link_Policy_Settings Command to the Bluetooth    */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Link_Policy_SettingsResult will      */
   /* contain the Link Policy Settings Result returned from the         */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Default_Link_Policy_Settings(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Link_Policy_SettingsResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Default_Link_Policy_Settings_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Link_Policy_SettingsResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Default_Link_Policy_Settings Command to the Bluetooth   */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Default_Link_Policy_Settings(unsigned int BluetoothStackID, Word_t Link_Policy_Settings, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Default_Link_Policy_Settings_t)(unsigned int BluetoothStackID, Word_t Link_Policy_Settings, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Flow_Specification Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Flow_Specification(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Flags, Byte_t Flow_Direction, Byte_t Service_Type, DWord_t Token_Rate, DWord_t Token_Bucket_Size, DWord_t Peak_Bandwidth, DWord_t Access_Latency, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Flow_Specification_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Flags, Byte_t Flow_Direction, Byte_t Service_Type, DWord_t Token_Rate, DWord_t Token_Bucket_Size, DWord_t Peak_Bandwidth, DWord_t Access_Latency, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Link Policy - Version 2.1 + EDR).              */

   /* The following function issues the HCI_Sniff_Subrating Command to  */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult will contain */
   /* the Connection_Handle Result returned from the Bluetooth Device.  */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Sniff_Subrating(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Maximum_Latency, Word_t Minimum_Remote_Timeout, Word_t Minimum_Local_Timeout, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Sniff_Subrating_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Maximum_Latency, Word_t Minimum_Remote_Timeout, Word_t Minimum_Local_Timeout, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* HCI Command API's (Host Controller and Baseband).                 */

   /* The following function issues the HCI_Set_Event_Mask Command to   */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_Event_Mask(unsigned int BluetoothStackID, Event_Mask_t Event_Mask, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_Event_Mask_t)(unsigned int BluetoothStackID, Event_Mask_t Event_Mask, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Reset Command to the        */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Reset(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Reset_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Set_Event_Filter Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_Event_Filter(unsigned int BluetoothStackID, Byte_t Filter_Type,  Byte_t Filter_Condition_Type, Condition_t Condition, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_Event_Filter_t)(unsigned int BluetoothStackID, Byte_t Filter_Type,  Byte_t Filter_Condition_Type, Condition_t Condition, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Flush Command to the        */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult variable     */
   /* will contain the Connection Handle Result returned from the       */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Flush(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Flush_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* The following function issues the HCI_Read_PIN_Type Command to the*/
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the PIN_TypeResultResult variable will   */
   /* contain the PIN Type Result returned from the Bluetooth Device.   */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_PIN_Type(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *PIN_TypeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_PIN_Type_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *PIN_TypeResult);
#endif

   /* The following function issues the HCI_Write_PIN_Type Command      */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_PIN_Type(unsigned int BluetoothStackID, Byte_t PIN_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_PIN_Type_t)(unsigned int BluetoothStackID, Byte_t PIN_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Create_New_Unit_Key Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Create_New_Unit_Key(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Create_New_Unit_Key_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Stored_Link_Key Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Max_Num_KeysResult variable will     */
   /* contain the Maximum Number of Keys Result returned from the       */
   /* Bluetooth Device AND the Num_Keys_ReadResult variable will        */
   /* contain the Number of Keys Read Result returned from the          */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Stored_Link_Key(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Read_All_Flag, Byte_t *StatusResult, Word_t *Max_Num_KeysResult, Word_t *Num_Keys_ReadResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Stored_Link_Key_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Read_All_Flag, Byte_t *StatusResult, Word_t *Max_Num_KeysResult, Word_t *Num_Keys_ReadResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Stored_Link_Key Command to the Bluetooth Device that is */
   /* associated with the Bluetooth Protocol Stack specified by the     */
   /* BluetoothStackID parameter.  This function returns zero if        */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Num_Keys_WrittenResult variable will contain the Number   */
   /* of Keys Written Result returned from the Bluetooth Device.  The   */
   /* Num_Keys_To_Write parameter specifies the                         */
   /* Number of HCI_Stored_Link_Key_Info_t entries that are pointed to  */
   /* by the HCI_Stored_Link_Key_Info parameter.  The Num_Keys_To_Write */
   /* parameter CANNOT be zero, and the HCI_Stored_Link_Key_Info        */
   /* parameter MUST point to Num_Keys_To_Write HCI_Stored_Link_Key_Info*/
   /* structures.                                                       */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Stored_Link_Key(unsigned int BluetoothStackID, Byte_t Num_Keys_To_Write, HCI_Stored_Link_Key_Info_t HCI_Stored_Link_Key_Info[], Byte_t *StatusResult, Byte_t *Num_Keys_Written);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Stored_Link_Key_t)(unsigned int BluetoothStackID, Byte_t Num_Keys_To_Write, HCI_Stored_Link_Key_Info_t HCI_Stored_Link_Key_Info[], Byte_t *StatusResult, Byte_t *Num_Keys_Written);
#endif

   /* The following function issues the                                 */
   /* HCI_Delete_Stored_Link_Key Command to the Bluetooth Device that is*/
   /* associated with the Bluetooth Protocol Stack specified by the     */
   /* BluetoothStackID parameter.  This function returns zero if        */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Num_Keys_DeletedResult variable will contain the Number   */
   /* of Keys Deleted Result returned from the Bluetooth Device.        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Delete_Stored_Link_Key(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Delete_All_Flag, Byte_t *StatusResult, Word_t *Num_Keys_DeletedResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Delete_Stored_Link_Key_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Delete_All_Flag, Byte_t *StatusResult, Word_t *Num_Keys_DeletedResult);
#endif

   /* The following function issues the HCI_Change_Local_Name Command to*/
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.  The Name parameter is a NULL terminated    */
   /* String that represents the Name parameter of this HCI function.   */
   /* This name can be up to MAX_NAME_LENGTH Bytes (not counting the    */
   /* NULL terminating character).                                      */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Change_Local_Name(unsigned int BluetoothStackID, char *Name, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Change_Local_Name_t)(unsigned int BluetoothStackID, char *Name, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Local_Name Command to  */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the NameResult variable will contain a   */
   /* NULL terminated String which represents the Name Result that was  */
   /* returned from the Bluetooth Device.  This function requires that  */
   /* NameResult be a pointer to a Buffer that is at least              */
   /* MAX_NAME_LENGTH+1 to hold the largest possible name that can be   */
   /* assigned to a Bluetooth Device.                                   */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_Name(unsigned int BluetoothStackID, Byte_t *StatusResult, char *NameResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_Name_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, char *NameResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Connection_Accept_Timeout Command to the Bluetooth Device*/
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Conn_Accept_TimeoutResult variable will contain the       */
   /* Connection Accept Timeout Result returned from the Bluetooth      */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Connection_Accept_Timeout(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Conn_Accept_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Connection_Accept_Timeout_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Conn_Accept_TimeoutResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Connection_Accept_Timeout Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Connection_Accept_Timeout(unsigned int BluetoothStackID, Word_t Conn_Accept_Timeout, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Connection_Accept_Timeout_t)(unsigned int BluetoothStackID, Word_t Conn_Accept_Timeout, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Page_Timeout Command to*/
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Page_TimeoutResult variable will     */
   /* contain the Page Timeout Result returned from the Bluetooth       */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Page_Timeout(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Page_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Page_Timeout_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Page_TimeoutResult);
#endif

   /* The following function issues the HCI_Write_Page_Timeout Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Page_Timeout(unsigned int BluetoothStackID, Word_t Page_Timeout, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Page_Timeout_t)(unsigned int BluetoothStackID, Word_t Page_Timeout, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Scan_Enable Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Scan_EnableResult variable will      */
   /* contain the Scan Enable Result returned from the Bluetooth        */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Scan_Enable(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Scan_EnableResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Scan_Enable_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Scan_EnableResult);
#endif

   /* The following function issues the HCI_Write_Scan_Enable Command   */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Scan_Enable(unsigned int BluetoothStackID, Byte_t Scan_Enable, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Scan_Enable_t)(unsigned int BluetoothStackID, Byte_t Scan_Enable, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Page_Scan_Activity     */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Page_Scan_IntervalResult variable will contain the Page Scan      */
   /* Interval Result returned from the Bluetooth Device AND the        */
   /* Page_Scan_WindowResult variable will contain the Page Scan        */
   /* Window Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Page_Scan_Activity(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Page_Scan_IntervalResult, Word_t *Page_Scan_WindowResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Page_Scan_Activity_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Page_Scan_IntervalResult, Word_t *Page_Scan_WindowResult);
#endif

   /* The following function issues the HCI_Write_Page_Scan_Activity    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Page_Scan_Activity(unsigned int BluetoothStackID, Word_t Page_Scan_Interval, Word_t Page_Scan_Window, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Page_Scan_Activity_t)(unsigned int BluetoothStackID, Word_t Page_Scan_Interval, Word_t Page_Scan_Window, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Inquiry_Scan_Activity  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Inquiry_Scan_IntervalResult variable will contain the Inquiry Scan*/
   /* Interval Result returned from the Bluetooth Device AND the        */
   /* Inquiry_Scan_WindowResult variable will contain the Inquiry Scan  */
   /* Window Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Inquiry_Scan_Activity(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Inquiry_Scan_IntervalResult, Word_t *Inquiry_Scan_WindowResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Inquiry_Scan_Activity_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Inquiry_Scan_IntervalResult, Word_t *Inquiry_Scan_WindowResult);
#endif

   /* The following function issues the HCI_Write_Inquiry_Scan_Activity */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Inquiry_Scan_Activity(unsigned int BluetoothStackID, Word_t Inquiry_Scan_Interval, Word_t Inquiry_Scan_Window, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Inquiry_Scan_Activity_t)(unsigned int BluetoothStackID, Word_t Inquiry_Scan_Interval, Word_t Inquiry_Scan_Window, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Authentication_Enable  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Authentication_EnableResult variable will contain the             */
   /* Authentication Result returned from the Bluetooth Device.         */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Authentication_Enable(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Authentication_EnableResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Authentication_Enable_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Authentication_EnableResult);
#endif

   /* The following function issues the HCI_Write_Authentication_Enable */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Authentication_Enable(unsigned int BluetoothStackID, Byte_t Authentication_Enable, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Authentication_Enable_t)(unsigned int BluetoothStackID, Byte_t Authentication_Enable, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Encryption_Mode        */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Encryption_ModeResult variable will contain the Encryption Mode   */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Encryption_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Encryption_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Encryption_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Encryption_ModeResult);
#endif

   /* The following function issues the HCI_Write_Encryption_Mode       */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Encryption_Mode(unsigned int BluetoothStackID, Byte_t Encryption_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Encryption_Mode_t)(unsigned int BluetoothStackID, Byte_t Encryption_Mode, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Class_of_Device        */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Class_of_DeviceResult variable will contain the Class of Device   */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Class_of_Device(unsigned int BluetoothStackID, Byte_t *StatusResult, Class_of_Device_t *Class_of_DeviceResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Class_of_Device_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Class_of_Device_t *Class_of_DeviceResult);
#endif

   /* The following function issues the HCI_Write_Class_of_Device       */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Class_of_Device(unsigned int BluetoothStackID, Class_of_Device_t Class_of_Device, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Class_of_Device_t)(unsigned int BluetoothStackID, Class_of_Device_t Class_of_Device, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Voice_Setting Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Voice_SettingResult variable will    */
   /* contain the Voice Setting Result returned from the Bluetooth      */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Voice_Setting(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Voice_SettingResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Voice_Setting_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Voice_SettingResult);
#endif

   /* The following function issues the HCI_Write_Voice_Setting Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Voice_Setting(unsigned int BluetoothStackID, Word_t Voice_Setting, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Voice_Setting_t)(unsigned int BluetoothStackID, Word_t Voice_Setting, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Automatic_Flush_Timeout*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult variable will contain the Connection      */
   /* Handle Result returned from the Bluetooth Device AND the          */
   /* Flush_TimeoutResult variable will contain the Flush Timeout       */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Automatic_Flush_Timeout(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Flush_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Automatic_Flush_Timeout_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Flush_TimeoutResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Automatic_Flush_Timeout Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Connection_HandleResult variable will contain the         */
   /* Connection Handle Result returned from the Bluetooth Device.      */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Automatic_Flush_Timeout(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flush_Timeout, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Automatic_Flush_Timeout_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Flush_Timeout, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Num_Broadcast_Retransmissions Command to the Bluetooth   */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the Num_Broadcast_RetranResult      */
   /* variable will contain the Number of Broadcast Retransmissions     */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Num_Broadcast_Retransmissions(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Num_Broadcast_RetranResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Num_Broadcast_Retransmissions_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Num_Broadcast_RetranResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Num_Broadcast_Retransmissions Command to the Bluetooth  */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Num_Broadcast_Retransmissions(unsigned int BluetoothStackID, Byte_t Num_Broadcast_Retran, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Num_Broadcast_Retransmissions_t)(unsigned int BluetoothStackID, Byte_t Num_Broadcast_Retran, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Hold_Mode_Activity     */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Hold_Mode_ActivityResult variable will contain the Hold Mode      */
   /* Activity Result returned from the Bluetooth Device.               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Hold_Mode_Activity(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Hold_Mode_ActivityResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Hold_Mode_Activity_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Hold_Mode_ActivityResult);
#endif

   /* The following function issues the HCI_Write_Hold_Mode_Activity    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Hold_Mode_Activity(unsigned int BluetoothStackID, Byte_t Hold_Mode_Activity, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Hold_Mode_Activity_t)(unsigned int BluetoothStackID, Byte_t Hold_Mode_Activity, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Transmit_Power_Level   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult variable will contain the Connection      */
   /* Handle Result returned from the Bluetooth Device AND the          */
   /* Transmit_Power_LevelResult variable will contain the Transmit     */
   /* Power Level Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Transmit_Power_Level(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Type, Byte_t *StatusResult, Word_t *Connection_HandleResult, SByte_t *Transmit_Power_LevelResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Transmit_Power_Level_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Type, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Transmit_Power_LevelResult);
#endif

   /* The following function issues the HCI_Read_SCO_Flow_Control_Enable*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* SCO_Flow_Control_EnableResult variable will contain the SCO Flow  */
   /* Control Enable Result returned from the Bluetooth Device.         */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_SCO_Flow_Control_Enable(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *SCO_Flow_Control_EnableResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_SCO_Flow_Control_Enable_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *SCO_Flow_Control_EnableResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_SCO_Flow_Control_Enable Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_SCO_Flow_Control_Enable(unsigned int BluetoothStackID, Byte_t SCO_Flow_Control_Enable, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_SCO_Flow_Control_Enable_t)(unsigned int BluetoothStackID, Byte_t SCO_Flow_Control_Enable, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Set_Host_Controller_To_Host_Flow_Control Command to the       */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_Host_Controller_To_Host_Flow_Control(unsigned int BluetoothStackID, Byte_t Flow_Control_Enable, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_Host_Controller_To_Host_Flow_Control_t)(unsigned int BluetoothStackID, Byte_t Flow_Control_Enable, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Host_Buffer_Size Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Host_Buffer_Size(unsigned int BluetoothStackID, Word_t Host_ACL_Data_Packet_Length, Byte_t Host_SCO_Data_Packet_Length, Word_t Host_Total_Num_ACL_Data_Packets, Word_t Host_Total_Num_SCO_Data_Packets, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Host_Buffer_Size_t)(unsigned int BluetoothStackID, Word_t Host_ACL_Data_Packet_Length, Byte_t Host_SCO_Data_Packet_Length, Word_t Host_Total_Num_ACL_Data_Packets, Word_t Host_Total_Num_SCO_Data_Packets, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Host_Number_Of_Completed_Packets Command to the Bluetooth     */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.  The Number_Of_Handles parameter       */
   /* specifies the Number of HCI_Host_Completed_Packets_Info_t         */
   /* entries that are pointed to by the HCI_Host_Completed_Packets_Info*/
   /* parameter.  The Number_Of_Handles parameter CANNOT be zero, and   */
   /* the HCI_Host_Completed_Packets_Info parameter MUST point to       */
   /* Number_Of_Handles HCI_Host_Completed_Packets_Info structures.     */
   /* The WaitForResponse flag, specifies whether or not this function  */
   /* is to wait for a response from the Bluetooth Device.  This        */
   /* parameter is provided because the Bluetooth Device DOES NOT ISSUE */
   /* ANY RESPONSE for this HCI Command UNLESS the HCI Command has      */
   /* invalid data.  If you (the caller) KNOW that the data you         */
   /* specified is correct, then set this parameter to FALSE.  If you   */
   /* want to be absolutely sure, you can wait for the Timeout, however */
   /* the calling thread will block until either an invalid response    */
   /* OR the Timeout occurs (valid data).                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Host_Number_Of_Completed_Packets(unsigned int BluetoothStackID, Byte_t Number_Of_Handles, HCI_Host_Completed_Packets_Info_t HCI_Host_Completed_Packets_Info[], Byte_t WaitForResponse, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Host_Number_Of_Completed_Packets_t)(unsigned int BluetoothStackID, Byte_t Number_Of_Handles, HCI_Host_Completed_Packets_Info_t HCI_Host_Completed_Packets_Info[], Byte_t WaitForResponse, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Link_Supervision_Timeout Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Connection_HandleResult variable will contain the         */
   /* Connection Handle Result returned from the Bluetooth Device AND   */
   /* the Link_Supervision_TimeoutResult variable will contain the Link */
   /* Supervision Timeout Result returned from the Bluetooth Device.    */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Link_Supervision_Timeout(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Link_Supervision_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Link_Supervision_Timeout_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Link_Supervision_TimeoutResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Link_Supervision_Timeout Command to the Bluetooth Device*/
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Connection_HandleResult variable will contain the         */
   /* Connection Handle Result returned from the Bluetooth Device.      */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Link_Supervision_Timeout(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Link_Supervision_Timeout, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Link_Supervision_Timeout_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Link_Supervision_Timeout, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* The following function issues the HCI_Read_Number_Of_Supported_IAC*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Num_Support_IACResult variable will contain the Number of         */
   /* Supported IAC's Result returned from the Bluetooth Device.        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Number_Of_Supported_IAC(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Num_Support_IACResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Number_Of_Supported_IAC_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Num_Support_IACResult);
#endif

   /* The following function issues the HCI_Read_Current_IAC_LAP Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth      */
   /* Protocol Stack specified by the BluetoothStackID parameter.       */
   /* This function returns zero if successful, or a non-zero value     */
   /* if there was an error.  If this function returns zero (success)   */
   /* then the StatusResult variable will contain the Status Result     */
   /* returned from the Bluetooth Device AND the Num_Current_IACResult  */
   /* variable will contain the Number of LAP_t entries that have been  */
   /* copied into the IAC_LAPResult variable.  This function requires   */
   /* that IAC_LAPResult be a pointer to a Buffer that is at least      */
   /* HCI_READ_CURRENT_IAC_LAP_COMMAND_MAX_IAC_LAPS to holde the maximum*/
   /* number of LAP_t entries taht can be returned by the Bluetooth     */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Current_IAC_LAP(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Num_Current_IACResult, LAP_t *IAC_LAPResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Current_IAC_LAP_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Num_Current_IACResult, LAP_t *IAC_LAPResult);
#endif

   /* The following function issues the HCI_Write_Current_IAC_LAP       */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.  The            */
   /* Num_Current_IAC parameter specifies the Number of LAP_t entries   */
   /* that are pointed to by the IAC_LAP parameter.  The                */
   /* Num_Current_IAC parameter CANNOT be zero, and the IAC_LAP         */
   /* parameter MUST point to Num_Current_IAC LAP_t entries.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Current_IAC_LAP(unsigned int BluetoothStackID, Byte_t Num_Current_IAC, LAP_t IAC_LAP[], Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Current_IAC_LAP_t)(unsigned int BluetoothStackID, Byte_t Num_Current_IAC, LAP_t IAC_LAP[], Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Page_Scan_Period_Mode  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Page_Scan_Period_ModeResult variable will contain the Page Scan   */
   /* Period Mode Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Page_Scan_Period_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Page_Scan_Period_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Page_Scan_Period_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Page_Scan_Period_ModeResult);
#endif

   /* The following function issues the HCI_Write_Page_Scan_Period_Mode */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Page_Scan_Period_Mode(unsigned int BluetoothStackID, Byte_t Page_Scan_Period_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Page_Scan_Period_Mode_t)(unsigned int BluetoothStackID, Byte_t Page_Scan_Period_Mode, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Page_Scan_Mode Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Page_Scan_ModeResult variable will   */
   /* contain the Page Scan Mode Result returned from the Bluetooth     */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Page_Scan_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Page_Scan_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Page_Scan_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Page_Scan_ModeResult);
#endif

   /* The following function issues the HCI_Write_Page_Scan_Mode        */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Page_Scan_Mode(unsigned int BluetoothStackID, Byte_t Page_Scan_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Page_Scan_Mode_t)(unsigned int BluetoothStackID, Byte_t Page_Scan_Mode, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Host Controller and Baseband - Version 1.2).   */

   /* The following function issues the                                 */
   /* HCI_Set_AFH_Host_Channel_Classification Command to the Bluetooth  */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_AFH_Host_Channel_Classification(unsigned int BluetoothStackID, AFH_Channel_Map_t AFH_Host_Channel_Classification, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_AFH_Host_Channel_Classification_t)(unsigned int BluetoothStackID, AFH_Channel_Map_t AFH_Host_Channel_Classification, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Inquiry_Scan_Type      */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Inquiry_Scan_TypeResult variable will contain the Inquiry Scan    */
   /* Type Result returned from the Bluetooth Device.                   */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Inquiry_Scan_Type(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Inquiry_Scan_TypeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Inquiry_Scan_Type_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Inquiry_Scan_TypeResult);
#endif

   /* The following function issues the HCI_Write_Inquiry_Scan_Type     */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Inquiry_Scan_Type(unsigned int BluetoothStackID, Byte_t Scan_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Inquiry_Scan_Type_t)(unsigned int BluetoothStackID, Byte_t Scan_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Inquiry_Mode Command   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Inquiry_ModeResult variable will contain the Inquiry Mode Result  */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Inquiry_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Inquiry_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Inquiry_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Inquiry_ModeResult);
#endif

   /* The following function issues the HCI_Write_Inquiry_Mode Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Inquiry_Mode(unsigned int BluetoothStackID, Byte_t Inquiry_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Inquiry_Mode_t)(unsigned int BluetoothStackID, Byte_t Inquiry_Mode, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Page_Scan_Type Command */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Page_Scan_TypeResult variable will contain the Page Scan Type     */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Page_Scan_Type(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Page_Scan_TypeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Page_Scan_Type_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Page_Scan_TypeResult);
#endif

   /* The following function issues the HCI_Write_Page_Scan_Type Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Page_Scan_Type(unsigned int BluetoothStackID, Byte_t Page_Scan_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Page_Scan_Type_t)(unsigned int BluetoothStackID, Byte_t Page_Scan_Type, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_AFH_Channel_Assessment_Mode Command Command to the       */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the AFH_Channel_Assessment_ModeResult    */
   /* variable will contain the AFH Channel Assessment Mode Result      */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_AFH_Channel_Assessment_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *AFH_Channel_Assessment_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_AFH_Channel_Assessment_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *AFH_Channel_Assessment_ModeResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_AFH_Channel_Assessment_Mode Command to the Bluetooth    */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_AFH_Channel_Assessment_Mode(unsigned int BluetoothStackID, Byte_t AFH_Channel_Assessment_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_AFH_Channel_Assessment_Mode_t)(unsigned int BluetoothStackID, Byte_t AFH_Channel_Assessment_Mode, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Host Controller and Baseband - Version 2.1 +   */
   /* EDR).                                                             */

   /* The following function issues the                                 */
   /* HCI_Read_Extended_Inquiry_Response Command to the Bluetooth Device*/
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the FEC_RequiredResult variable will contain the FEC Required */
   /* parameter returned from the Bluetooth Device AND the              */
   /* Extended_Inquiry_Response_DataResult variable will the contain the*/
   /* Extended Inquiry Response Result returned from the Bluetooth      */
   /* Device.  Note the buffer passed in MUST be at least               */
   /* EXTENDED_INQUIRY_RESPONSE_DATA_MAXIMUM_SIZE in length.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Extended_Inquiry_Response(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *FEC_RequiredResult, Extended_Inquiry_Response_Data_t *Extended_Inquiry_Response_DataResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Extended_Inquiry_Response_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *FEC_RequiredResult, Extended_Inquiry_Response_Data_t *Extended_Inquiry_Response_DataResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Extended_Inquiry_Response Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Extended_Inquiry_Response(unsigned int BluetoothStackID, Byte_t FEC_Required, Extended_Inquiry_Response_Data_t *Extended_Inquiry_Response_Data, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Extended_Inquiry_Response_t)(unsigned int BluetoothStackID, Byte_t FEC_Required, Extended_Inquiry_Response_Data_t *Extended_Inquiry_Response_Data, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Refresh_Encryption_Key      */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Refresh_Encryption_Key(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Refresh_Encryption_Key_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Simple_Pairing_Mode    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Simple_Pairing_ModeResult variable will contain the Simple Pairing*/
   /* Mode returned from the Bluetooth Device.                          */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Simple_Pairing_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Simple_Pairing_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Simple_Pairing_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Simple_Pairing_ModeResult);
#endif

   /* The following function issues the HCI_Write_Simple_Pairing_Mode   */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Simple_Pairing_Mode(unsigned int BluetoothStackID, Byte_t Simple_Pairing_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Simple_Pairing_Mode_t)(unsigned int BluetoothStackID, Byte_t Simple_Pairing_Mode, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Local_OOB_Data Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Simple_Pairing_HashResult variable   */
   /* will contain the Simple Pairing Hash Result returned from the     */
   /* Bluetooth Device AND the Simple_Pairing_RandomizerResult variable */
   /* will contain the Simple Pairing Randomizer Result returned from   */
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_OOB_Data(unsigned int BluetoothStackID, Byte_t *StatusResult, Simple_Pairing_Hash_t *Simple_Pairing_HashResult, Simple_Pairing_Randomizer_t *Simple_Pairing_RandomizerResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_OOB_Data_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Simple_Pairing_Hash_t *Simple_Pairing_HashResult, Simple_Pairing_Randomizer_t *Simple_Pairing_RandomizerResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Inquiry_Response_Transmit_Power_Level Command to the     */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the TX_PowerResult variable will contain */
   /* the TX Power Result returned from the Bluetooth Device.           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Inquiry_Response_Transmit_Power_Level(unsigned int BluetoothStackID, Byte_t *StatusResult, SByte_t *TX_PowerResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Inquiry_Response_Transmit_Power_Level_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, SByte_t *TX_PowerResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Inquiry_Transmit_Power_Level Command to the Bluetooth   */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Inquiry_Transmit_Power_Level(unsigned int BluetoothStackID, SByte_t TX_Power, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Inquiry_Transmit_Power_Level_t)(unsigned int BluetoothStackID, SByte_t TX_Power, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Send_Keypress_Notification  */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* BD_ADDRResult variable will contain the BD_ADDR Result returned   */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Send_Keypress_Notification(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t KeyPress, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Send_Keypress_Notification_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t KeyPress, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Default_Erroneous_Data_Reporting Command to the Bluetooth*/
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Erroneous_Data_ReportingResult       */
   /* variable will contain the Erroneous Data Reporting Result returned*/
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Default_Erroneous_Data_Reporting(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Erroneous_Data_ReportingResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Default_Erroneous_Data_Reporting_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Erroneous_Data_ReportingResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Default_Erroneous_Data_Reporting Command to the         */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Default_Erroneous_Data_Reporting(unsigned int BluetoothStackID, Byte_t Erroneous_Data_Reporting, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Default_Erroneous_Data_Reporting_t)(unsigned int BluetoothStackID, Byte_t Erroneous_Data_Reporting, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Enhanced_Flush Command to   */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Enhanced_Flush(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Packet_Type, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Enhanced_Flush_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t Packet_Type, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Host Controller and Baseband - Version 3.0 +   */
   /* HS).                                                              */

   /* The following function issues the                                 */
   /* HCI_Read_Logical_Link_Accept_Timeout Command to the Bluetooth     */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Logical_Link_Accept_TimeoutResult    */
   /* parameter will contain the Logical Link Accept Timeout Result     */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Logical_Link_Accept_Timeout(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Logical_Link_Accept_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Logical_Link_Accept_Timeout_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Logical_Link_Accept_TimeoutResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Logical_Link_Accept_Timeout Command to the Bluetooth    */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Logical_Link_Accept_Timeout(unsigned int BluetoothStackID, Word_t Logical_Link_Accept_Timeout, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Logical_Link_Accept_Timeout_t)(unsigned int BluetoothStackID, Word_t Logical_Link_Accept_Timeout, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Set_Event_Mask_Page_2       */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Set_Event_Mask_Page_2(unsigned int BluetoothStackID, Event_Mask_t Event_Mask, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Set_Event_Mask_Page_2_t)(unsigned int BluetoothStackID, Event_Mask_t Event_Mask, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Location_Data Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Location_Domain_AwareResult variable */
   /* will contain the Location Domain Aware Result returned from the   */
   /* Bluetooth Device AND the Location_DomainResult variable will      */
   /* contain the Location_Domain Result returned from the Bluetooth    */
   /* Device AND the Location_Domain_OptionsResult variable will contain*/
   /* the Location Domain Options Result AND the Location_OptionsResult */
   /* will contain the Location Options Result returned from the        */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Location_Data(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Location_Domain_AwareResult, Word_t *Location_DomainResult, Byte_t *Location_Domain_OptionsResult, Byte_t *Location_OptionsResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Location_Data_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Location_Domain_AwareResult, Word_t *Location_DomainResult, Byte_t *Location_Domain_OptionsResult, Byte_t *Location_OptionsResult);
#endif

   /* The following function issues the HCI_Write_Location_Data Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Location_Data(unsigned int BluetoothStackID, Byte_t Location_Domain_Aware, Word_t Location_Domain, Byte_t Location_Domain_Options, Byte_t Location_Options, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Location_Data_t)(unsigned int BluetoothStackID, Byte_t Location_Domain_Aware, Word_t Location_Domain, Byte_t Location_Domain_Options, Byte_t Location_Options, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Read_Flow_Control_Mode      */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Flow_Control_ModeResult variable will contain the Flow Control    */
   /* Mode Result returned from the Bluetooth Device.                   */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Flow_Control_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Flow_Control_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Flow_Control_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Flow_Control_ModeResult);
#endif

   /* The following function issues the HCI_Write_Flow_Control_Mode     */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Flow_Control_Mode(unsigned int BluetoothStackID, Byte_t Flow_Control_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Flow_Control_Mode_t)(unsigned int BluetoothStackID, Byte_t Flow_Control_Mode, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Enhanced_Transmit_Power_Level Command to the Bluetooth   */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult Connection   */
   /* Handle Result returned from the Bluetooth Device AND the          */
   /* Transmit_Power_Level_GFSKResult Transmit Power Level (GFSK) Result*/
   /* returned from the Bluetooth Device AND the                        */
   /* Transmit_Power_Level_DQPSKResult Transmit Power Level (DQPSK)     */
   /* Result returned from the Bluetooth Device AND the                 */
   /* Transmit_Power_Level_8DPSKResult Transmit Power Level (8DPSK)     */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Enhanced_Transmit_Power_Level(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, SByte_t *Transmit_Power_Level_GFSKResult, SByte_t *Transmit_Power_Level_DQPSKResult, SByte_t *Transmit_Power_Level_8DPSKResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Enhanced_Transmit_Power_Level_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, SByte_t *Transmit_Power_Level_GFSKResult, SByte_t *Transmit_Power_Level_DQPSKResult, SByte_t *Transmit_Power_Level_8DPSKResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Best_Effort_Flush_Timeout Command to the Bluetooth Device*/
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Best_Effort_Flush_TimeoutResult variable will contain the */
   /* Best Effort Flush Timeout Result returned from the Bluetooth      */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Best_Effort_Flush_Timeout(unsigned int BluetoothStackID, Word_t Logical_Link_Handle, Byte_t *StatusResult, DWord_t *Best_Effort_Flush_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Best_Effort_Flush_Timeout_t)(unsigned int BluetoothStackID, Word_t Logical_Link_Handle, Byte_t *StatusResult, DWord_t *Best_Effort_Flush_TimeoutResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Write_Best_Effort_Flush_Timeout Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Best_Effort_Flush_Timeout(unsigned int BluetoothStackID, Word_t Logical_Link_Handle, DWord_t Best_Effort_Flush_Timeout, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Best_Effort_Flush_Timeout_t)(unsigned int BluetoothStackID, Word_t Logical_Link_Handle, DWord_t Best_Effort_Flush_Timeout, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_Short_Range_Mode Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Short_Range_Mode(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Short_Range_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Short_Range_Mode_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Byte_t Short_Range_Mode, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Host Controller and Baseband - Version 4.0 +   */
   /* LE).                                                              */

   /* The following function issues the HCI_Read_LE_Host_Supported      */
   /* command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* LE_Supported_HostResult variable will contain the LE Supported    */
   /* Host Result returned from the Bluetooth Device AND the            */
   /* Simultaneous_LE_HostResult will contain the Simultaneous LE Host  */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_LE_Host_Supported(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *LE_Supported_HostResult, Byte_t *Simultaneous_LE_HostResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_LE_Host_Supported_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *LE_Supported_HostResult, Byte_t *Simultaneous_LE_HostResult);
#endif

   /* The following function issues the HCI_Read_LE_Write_Supported     */
   /* command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter followed by the Host supported LE parameters.  This This*/
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_LE_Host_Supported(unsigned int BluetoothStackID, Byte_t LE_Supported_Host, Byte_t Simultaneous_LE_Host, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_LE_Host_Supported_t)(unsigned int BluetoothStackID, Byte_t LE_Supported_Host, Byte_t Simultaneous_LE_Host, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Informational Parameters).                     */

   /* The following function issues the                                 */
   /* HCI_Read_Local_Version_Information Command to the Bluetooth Device*/
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the HCI_VersionResult variable will contain the HCI Version   */
   /* Result returned from the Bluetooth Device AND the                 */
   /* HCI_RevisionResult variable will contain the HCI Revision Result  */
   /* returned from the Bluetooth Device AND the LMP_VersionResult      */
   /* variable will contain the LMP Version Result returned from the    */
   /* Bluetooth Device AND the Manufacturer_NameResult variable will    */
   /* contain the Manufacturer Name Result returned from the Bluetooth  */
   /* Device AND the LMP_SubversionResult variable will contain the     */
   /* LMP Subversion Result returned from the Bluetooth Device.         */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_Version_Information(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *HCI_VersionResult, Word_t *HCI_RevisionResult, Byte_t *LMP_VersionResult, Word_t *Manufacturer_NameResult, Word_t *LMP_SubversionResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_Version_Information_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *HCI_VersionResult, Word_t *HCI_RevisionResult, Byte_t *LMP_VersionResult, Word_t *Manufacturer_NameResult, Word_t *LMP_SubversionResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Read_Local_Supported_Features Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the LMP_FeaturesResult variable will contain the LMP Features */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_Supported_Features(unsigned int BluetoothStackID, Byte_t *StatusResult, LMP_Features_t *LMP_FeaturesResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_Supported_Features_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, LMP_Features_t *LMP_FeaturesResult);
#endif

   /* The following function issues the HCI_Read_Buffer_Size Command    */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the HC_ACL_Data_Packet_LengthResult      */
   /* variable will contain the HCI ACL Data Packet Length Result       */
   /* returned from the Bluetooth Device AND the                        */
   /* HC_SCO_Data_Packet_LengthResult variable will contain the HCI SCO */
   /* Data Packet Length Result returned from the Bluetooth Device AND  */
   /* the HC_Total_Num_ACL_Data_PacketsResult variable will contain the */
   /* HCI Total Number ACL Data Packets Result returned from the        */
   /* Bluetooth Device AND the HC_Total_Num_SCO_Data_PacketsResult      */
   /* variable will contain the HCI Total Number SCO Data Packets       */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Buffer_Size(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *HC_ACL_Data_Packet_Length, Byte_t *HC_SCO_Data_Packet_Length, Word_t *HC_Total_Num_ACL_Data_Packets, Word_t *HC_Total_Num_SCO_Data_Packets);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Buffer_Size_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *HC_ACL_Data_Packet_Length, Byte_t *HC_SCO_Data_Packet_Length, Word_t *HC_Total_Num_ACL_Data_Packets, Word_t *HC_Total_Num_SCO_Data_Packets);
#endif

   /* The following function issues the HCI_Read_Country_Code Command   */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Country_CodeResult variable will     */
   /* contain the Country Code Result returned from the Bluetooth       */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Country_Code(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Country_CodeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Country_Code_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Country_CodeResult);
#endif

   /* The following function issues the HCI_Read_BD_ADDR Command to the */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the BD_ADDRResult variable will contain  */
   /* the BD_ADDR Result returned from the Bluetooth Device.            */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_BD_ADDR(unsigned int BluetoothStackID, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_BD_ADDR_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, BD_ADDR_t *BD_ADDRResult);
#endif

   /* HCI Command API's (Informational Parameters - Version 1.2).       */

   /* The following function issues the                                 */
   /* HCI_Read_Local_Supported_Commands Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Supported_CommandsResult variable will contain the        */
   /* Supported Commands Result returned from the Bluetooth Device.     */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_Supported_Commands(unsigned int BluetoothStackID, Byte_t *StatusResult, Supported_Commands_t *Supported_CommandsResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_Supported_Commands_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Supported_Commands_t *Supported_CommandsResult);
#endif

   /* The following function issues the HCI_Read_Local_Extended_Features*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Page_NumberResult variable will contain the Page Number Result    */
   /* returned from the Bluetooth Device AND the                        */
   /* Maximum_Page_NumberResult variable will contain the Maximum Page  */
   /* Number Result returned from the Bluetooth Device AND the          */
   /* Extended_LMP_FeaturesResult variable will contain the Extended LMP*/
   /* Features Result returned from the Bluetooth Device.               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_Extended_Features(unsigned int BluetoothStackID, Byte_t Page_Number, Byte_t *StatusResult, Byte_t *Page_NumberResult, Byte_t *Maximum_Page_NumberResult, LMP_Features_t *Extended_LMP_FeaturesResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_Extended_Features_t)(unsigned int BluetoothStackID, Byte_t Page_Number, Byte_t *StatusResult, Byte_t *Page_NumberResult, Byte_t *Maximum_Page_NumberResult, LMP_Features_t *Extended_LMP_FeaturesResult);
#endif

   /* HCI Command API's (Informational Parameters - Version 3.0 + HS).  */

   /* The following function issues the HCI_Read_Data_Block_Size Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Max_ACL_Data_Packet_LengthResult     */
   /* variable will contain the Maximum ACL Data Packet Length Result   */
   /* returned from the Bluetooth Device AND the Data_Block_LengthResult*/
   /* variable will contain the Data Block Length Result returned from  */
   /* the Bluetooth Device AND the Total_Num_Data_BlocksResult variable */
   /* will contain the Total Number Data Blocks Result returned from the*/
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Data_Block_Size(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Max_ACL_Data_Packet_LengthResult, Word_t *Data_Block_LengthResult, Word_t *Total_Num_Data_BlocksResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Data_Block_Size_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Max_ACL_Data_Packet_LengthResult, Word_t *Data_Block_LengthResult, Word_t *Total_Num_Data_BlocksResult);
#endif

   /* HCI Command API's (Status Parameters).                            */

   /* The following function issues the HCI_Read_Failed_Contact_Counter */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult variable will contain the Connection      */
   /* Handle Result returned from the Bluetooth Device AND the          */
   /* Failed_Contact_CounterResult variable will contain the Failed     */
   /* Contact Counter Result returned from the Bluetooth Device.        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Failed_Contact_Counter(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Failed_Contact_CounterResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Failed_Contact_Counter_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Word_t *Failed_Contact_CounterResult);
#endif

   /* The following function issues the HCI_Reset_Failed_Contact_Counter*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult variable will contain the Connection      */
   /* Handle Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Reset_Failed_Contact_Counter(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Reset_Failed_Contact_Counter_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* The following function issues the HCI_Get_Link_Quality Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult variable will*/
   /* contain the Connection Handle Result returned from the Bluetooth  */
   /* Device AND the Link_QualityResult variable will contain the Link  */
   /* Quality Result returned from the Bluetooth Device.                */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Get_Link_Quality(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Link_QualityResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Get_Link_Quality_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Link_QualityResult);
#endif

   /* The following function issues the HCI_Read_RSSI Command to the    */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult variable will*/
   /* contain the Connection Handle Result returned from the Bluetooth  */
   /* Device AND the RSSIResult variable will contain the RSSI Result   */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_RSSI(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, SByte_t *RSSIResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_RSSI_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, SByte_t *RSSIResult);
#endif

   /* HCI Command API's (Status Parameters - Version 1.2).              */

   /* The following function issues the HCI_Read_AFH_Channel_Map Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult variable will*/
   /* contain the Connection Handle Result returned from the Bluetooth  */
   /* Device AND the AFH_ModeResult variable will contain the AFH Mode  */
   /* Result returned from the Bluetooth Device AND the                 */
   /* AFH_Channel_MapResult variable will contain the AFH Channel Map   */
   /* Result returned from the Bluetooth Device.                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_AFH_Channel_Map(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *AFH_ModeResult, AFH_Channel_Map_t *AFH_Channel_MapResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_AFH_Channel_Map_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *AFH_ModeResult, AFH_Channel_Map_t *AFH_Channel_MapResult);
#endif

   /* The following function issues the HCI_Read_Clock Command to the   */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Connection_HandleResult variable will*/
   /* contain the Connection Handle Result returned from the Bluetooth  */
   /* Device AND the ClockResult variable will contain the Clock Result */
   /* returned from the Bluetooth Device AND the AccuracyResult variable*/
   /* will contain the Accuracy Result returned from the Bluetooth      */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Clock(unsigned int BluetoothStackID, Byte_t Which_Clock, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, DWord_t *ClockResult, Word_t *AccuracyResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Clock_t)(unsigned int BluetoothStackID, Byte_t Which_Clock, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, DWord_t *ClockResult, Word_t *AccuracyResult);
#endif

   /* HCI Command API's (Status Parameters - Version 3.0 + HS).         */

   /* The following function issues the HCI_Read_Encryption_Key_Size    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult variable will contain the Connection      */
   /* Handle Result returned from the Bluetooth Device AND the          */
   /* Key_SizeResult variable will contain the Key Size Result returned */
   /* from the Bluetooth Device .                                       */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Encryption_Key_Size(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Key_SizeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Encryption_Key_Size_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, Byte_t *Key_SizeResult);
#endif

   /* The following function issues the HCI_Read_Local_AMP_Info Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the AMP_StatusResult variable will       */
   /* contain the AMP Status Result returned from the Bluetooth Device  */
   /* AND the Total_BandwidthResult variable will contain the Total     */
   /* Bandwidth Result returned from the Bluetooth Device AND the       */
   /* Max_Guaranteed_BandwidthResult variable will contain the Maximum  */
   /* Guaranteed Bandwidth Result returned from the Bluetooth Device AND*/
   /* the Min_LatencyResult variable will contain the Minimum Latency   */
   /* Result returned from the Bluetooth Device AND the                 */
   /* Max_PDU_SizeResult variable will contain the Maximum PDU Size     */
   /* Result returned from the Bluetooth Device AND the                 */
   /* Controller_TypeResult variable will contain the Controller Type   */
   /* Result returned from the Bluetooth Device AND the                 */
   /* PAL_CapabilitiesResult variable will contain the PAL Capabilities */
   /* Result returned from the Bluetooth Device AND the                 */
   /* Max_AMP_ASSOC_LengthResult variable will contain the Maximum      */
   /* AMP ASSOC Length Result returned from the Bluetooth Device AND the*/
   /* Max_Flush_TimeoutResult variable will contain the Maximum Flush   */
   /* Timeout Result returned from the Bluetooth Device AND the         */
   /* Best_Effort_Flush_TimeoutResult variable will contain the Best    */
   /* Effort Flush Timeout Result returned from the Bluetooth Device.   */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_AMP_Info(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *AMP_StatusResult, DWord_t *Total_BandwidthResult, DWord_t *Max_Guaranteed_BandwidthResult, DWord_t *Min_LatencyResult, DWord_t *Max_PDU_SizeResult, Byte_t *Controller_TypeResult, Word_t *PAL_CapabilitiesResult, Word_t *Max_AMP_ASSOC_LengthResult, DWord_t *Max_Flush_TimeoutResult, DWord_t *Best_Effort_Flush_TimeoutResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_AMP_Info_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *AMP_StatusResult, DWord_t *Total_BandwidthResult, DWord_t *Max_Guaranteed_BandwidthResult, DWord_t *Min_LatencyResult, DWord_t *Max_PDU_SizeResult, Byte_t *Controller_TypeResult, Word_t *PAL_CapabilitiesResult, Word_t *Max_AMP_ASSOC_LengthResult, DWord_t *Max_Flush_TimeoutResult, DWord_t *Best_Effort_Flush_TimeoutResult);
#endif

   /* The following function issues the HCI_Read_Local_AMP_ASSOC Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Physical_Link_HandleResult variable  */
   /* will contain the Physical Link Handle Result returned from the    */
   /* Bluetooth Device AND the AMP_ASSOC_Remaining_LengthResult variable*/
   /* will contain the AMP Association Remaining Length Result returned */
   /* from the Bluetooth Device AND the AMP_ASSOC_FragmentLengthResult  */
   /* variable will contain the number of bytes of the AMP ASSOC        */
   /* Fragment returned from the Bluetooth Device AND the               */
   /* AMP_ASSOC_FragmentResult variable will contain the AMP Association*/
   /* Fragrment Result returned from the Bluetooth Device               */
   /* * NOTE * The fifth parameter (AMP_ASSOC_Fragment_Buffer_Length)   */
   /*          defines the size of the buffer the final parameter       */
   /*          (AMP_ASSOC_FragmentResult) points to.  This size *MUST*  */
   /*          be at least                                              */
   /*          HCI_AMP_ASSOC_FRAGMENT_SIZE_MAXIMUM_FRAGMENT_SIZE bytes  */
   /*          long when the calculated remaining length is greater than*/
   /*          that value.                                              */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Local_AMP_ASSOC(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Word_t Length_So_Far, Word_t Max_Remote_AMP_ASSOC_Length, Byte_t AMP_ASSOC_Fragment_Buffer_Length, Byte_t *StatusResult, Byte_t *Physical_Link_HandleResult, Word_t *AMP_ASSOC_Remaining_LengthResult, Byte_t *AMP_ASSOC_FragmentLengthResult, Byte_t *AMP_ASSOC_FragmentResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Local_AMP_ASSOC_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Word_t Length_So_Far, Word_t Max_Remote_AMP_ASSOC_Length, Byte_t AMP_ASSOC_Fragment_Buffer_Length, Byte_t *StatusResult, Byte_t *Physical_Link_HandleResult, Word_t *AMP_ASSOC_Remaining_LengthResult, Byte_t *AMP_ASSOC_FragmentLengthResult, Byte_t *AMP_ASSOC_FragmentResult);
#endif

   /* The following function issues the HCI_Write_Remote_AMP_ASSOC      */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Physical_Link_HandleResult variable will contain the Physical Link*/
   /* Handle Result returned from the Bluetooth Device.                 */
   /* * NOTE * The fifth paramter (AMP_ASSOC_Fragment_Length) specifies */
   /*          the size of the buffer that is pointed to by the sixth   */
   /*          parameter (AMP_ASSOC_Fragment).  This is the size of the */
   /*          fragment that will be written by this command.           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Remote_AMP_ASSOC(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Word_t Length_So_Far, Word_t AMP_ASSOC_Remaining_Length, Byte_t AMP_ASSOC_Fragment_Length, Byte_t *AMP_ASSOC_Fragment, Byte_t *StatusResult, Byte_t *Physical_Link_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Remote_AMP_ASSOC_t)(unsigned int BluetoothStackID, Byte_t Physical_Link_Handle, Word_t Length_So_Far, Word_t AMP_ASSOC_Remaining_Length, Byte_t AMP_ASSOC_Fragment_Length, Byte_t *AMP_ASSOC_Fragment, Byte_t *StatusResult, Byte_t *Physical_Link_HandleResult);
#endif

   /* HCI Command API's (Testing Commands).                             */

   /* The following function issues the HCI_Read_Loopback_Mode Command  */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the Loopback_ModeResult variable will    */
   /* contain the Connection Handle Result returned from the Bluetooth  */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Read_Loopback_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Loopback_ModeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Read_Loopback_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Loopback_ModeResult);
#endif

   /* The following function issues the HCI_Write_Loopback_Mode Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Loopback_Mode(unsigned int BluetoothStackID, Byte_t Loopback_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Loopback_Mode_t)(unsigned int BluetoothStackID, Byte_t Loopback_Mode, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_Enable_Device_Under_Test_Mode Command to the Bluetooth Device */
   /* that is associated with the Bluetooth Protocol Stack specified by */
   /* the BluetoothStackID parameter.  This function returns zero if    */
   /* successful, or a non-zero value if there was an error.  If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Enable_Device_Under_Test_Mode(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Enable_Device_Under_Test_Mode_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Testing Commands - Version 2.1 + EDR).         */

   /* The following function issues the                                 */
   /* HCI_Write_Simple_Pairing_Debug_Mode Command to the Bluetooth      */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Write_Simple_Pairing_Debug_Mode(unsigned int BluetoothStackID, Byte_t Debug_Mode, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Write_Simple_Pairing_Debug_Mode_t)(unsigned int BluetoothStackID, Byte_t Debug_Mode, Byte_t *StatusResult);
#endif

   /* HCI Command API's (Testing Commands - Version 3.0 + HS).          */

   /* The following function issues the HCI_Enable_AMP_Receiver_Reports */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_Enable_AMP_Receiver_Reports(unsigned int BluetoothStackID, Byte_t Enable, Byte_t Interval, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_Enable_AMP_Receiver_Reports_t)(unsigned int BluetoothStackID, Byte_t Enable, Byte_t Interval, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_AMP_Test_End Command to the */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter.  This function */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_AMP_Test_End(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_AMP_Test_End_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_AMP_Test_Command Command to */
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.  The Parameter_Length parameter specifies   */
   /* the number of bytes to send from the Buffer specified by the      */
   /* Parameter_Data parameter.  The Parameter_Data parameter is ignored*/
   /* if Parameter_Length is zero.                                      */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_AMP_Test_Command(unsigned int BluetoothStackID, Byte_t Parameter_Length, Byte_t Parameter_Data[], Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_AMP_Test_Command_t)(unsigned int BluetoothStackID, Byte_t Parameter_Length, Byte_t Parameter_Data[], Byte_t *StatusResult);
#endif

   /* HCI Command API's (LE Commands - Version 4.0 + LE).               */

   /* The following function issues the HCI_LE_Set_Event_Mask Command to*/
   /* the Bluetooth Device that is associated with the Bluetooth        */
   /* Protocol Stack specified by the BluetoothStackID parameter        */
   /* followed by the LE Event Mask to set.  This function returns zero */
   /* if successful, or a non-zero value if there was an error.  If this*/
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Event_Mask(unsigned int BluetoothStackID, Event_Mask_t LE_Event_Mask, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Event_Mask_t)(unsigned int BluetoothStackID, Event_Mask_t LE_Event_Mask, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Read_Buffer_Size Command */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device AND the HC_LE_ACL_Data_Packet_LengthResult   */
   /* variable will contain the HCI LE ACL Data Packet Length Result    */
   /* returned from the Bluetooth Device AND the                        */
   /* HC_Total_Num_LE_ACL_Data_PacketsResult variable will contain the  */
   /* HCI Total Number LE ACL Data Packets Result returned from the     */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_Buffer_Size(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *HC_LE_ACL_Data_Packet_Length, Byte_t *HC_Total_Num_LE_ACL_Data_Packets);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_Buffer_Size_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *HC_LE_ACL_Data_Packet_Length, Byte_t *HC_Total_Num_LE_ACL_Data_Packets);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Read_Local_Supported_Features Command to the Bluetooth     */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter.  This function       */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the LE_FeaturesResult variable will */
   /* contain the LE Features Result returned from the Bluetooth        */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_Local_Supported_Features(unsigned int BluetoothStackID, Byte_t *StatusResult, LE_Features_t *LE_FeaturesResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_Local_Supported_Features_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, LE_Features_t *LE_FeaturesResult);
#endif

   /* The following function issues the HCI_LE_Set_Random_Address       */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter.  This function returns zero if successful, or a        */
   /* non-zero value if there was an error. If this function returns    */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Random_Address(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Random_Address_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Set_Advertising_Parameters to the Bluetooth Device that is */
   /* associated with the Bluetooth Protocol Stack specified by the     */
   /* BluetoothStackID parameter. This function returns zero if         */
   /* successfull, or a non-zero value if there was an error. If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Advertising_Parameters(unsigned int BluetoothStackID, Word_t Advertising_Interval_Min, Word_t Advertising_Interval_Max, Byte_t Advertising_Type, Byte_t Own_Address_Type, Byte_t Direct_Address_Type, BD_ADDR_t Direct_Address, Byte_t Advertising_Channel_Map, Byte_t Advertising_Filter_Policy, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Advertising_Parameters_t)(unsigned int BluetoothStackID, Word_t Advertising_Interval_Min, Word_t Advertising_Interval_Max, Byte_t Advertising_Type, Byte_t Own_Address_Type, Byte_t Direct_Address_Type, BD_ADDR_t Direct_Address, Byte_t Advertising_Channel_Map, Byte_t Advertising_Filter_Policy, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Read_Advertising_Channel_Tx_Power to the Bluetooth Device  */
   /* that isassociated with the Bluetooth Protocol Stack specified by  */
   /* the BluetoothStackID parameter. This function returns zero if     */
   /* successfull, or a non-zero value if there was an error. If this   */
   /* function returns zero (success) then the StatusResult variable    */
   /* will contain the Status Result returned from the Bluetooth Device */
   /* AND the Transmit_Power_LevelResult variable will contain the      */
   /* Transmit Power Level returned from the Bluetooth Device.          */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_Advertising_Channel_Tx_Power(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Transmit_Power_LevelResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_Advertising_Channel_Tx_Power_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *Transmit_Power_LevelResult);
#endif

   /* The following function issues the HCI_LE_Set_Advertising_Data     */
   /* to the Bluetooth Device that isassociated with the Bluetooth      */
   /* Protocol Stack specified by the BluetoothStackID parameter. This  */
   /* function returns zero if successfull, or a non-zero value if      */
   /* there was an error. If this function returns zero (success) then  */
   /* the StatusResult variable will contain the Status Result returned */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Advertising_Data(unsigned int BluetoothStackID, Byte_t Advertising_Data_Length, Advertising_Data_t *Advertising_Data, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Advertising_Data_t)(unsigned int BluetoothStackID, Byte_t Advertising_Data_Length, Advertising_Data_t *Advertising_Data, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Set_Scan_Response_Data   */
   /* to the Bluetooth Device that isassociated with the Bluetooth      */
   /* Protocol Stack specified by the BluetoothStackID parameter. This  */
   /* function returns zero if successfull, or a non-zero value if      */
   /* there was an error. If this function returns zero (success) then  */
   /* the StatusResult variable will contain the Status Result returned */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Scan_Response_Data(unsigned int BluetoothStackID, Byte_t Scan_Response_Data_Length, Scan_Response_Data_t *Scan_Response_Data, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Scan_Response_Data_t)(unsigned int BluetoothStackID, Byte_t Scan_Response_Data_Length, Scan_Response_Data_t *Scan_Response_Data, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Set_Advertise_Enable     */
   /* to the Bluetooth Device that isassociated with the Bluetooth      */
   /* Protocol Stack specified by the BluetoothStackID parameter. This  */
   /* function returns zero if successfull, or a non-zero value if      */
   /* there was an error. If this function returns zero (success) then  */
   /* the StatusResult variable will contain the Status Result returned */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Advertise_Enable(unsigned int BluetoothStackID, Byte_t Advertising_Enable, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Advertise_Enable_t)(unsigned int BluetoothStackID, Byte_t Advertising_Enable, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Set_Scan_Parameters      */
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter. This  */
   /* function returns zero if successfull, or a non-zero value if      */
   /* there was an error. If this function returns zero (success) then  */
   /* the StatusResult variable will contain the Status Result returned */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Scan_Parameters(unsigned int BluetoothStackID, Byte_t LE_Scan_Type, Word_t LE_Scan_Interval, Word_t LE_Scan_Window, Byte_t Own_Address_Type, Byte_t Scanning_Filter_Policy, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Scan_Parameters_t)(unsigned int BluetoothStackID, Byte_t LE_Scan_Type, Word_t LE_Scan_Interval, Word_t LE_Scan_Window, Byte_t Own_Address_Type, Byte_t Scanning_Filter_Policy, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Set_Scan_Enable          */
   /* to the Bluetooth Device that isassociated with the Bluetooth      */
   /* Protocol Stack specified by the BluetoothStackID parameter. This  */
   /* function returns zero if successfull, or a non-zero value if      */
   /* there was an error. If this function returns zero (success) then  */
   /* the StatusResult variable will contain the Status Result returned */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Scan_Enable(unsigned int BluetoothStackID, Byte_t LE_Scan_Enable, Byte_t Filter_Duplicates, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Scan_Enable_t)(unsigned int BluetoothStackID, Byte_t LE_Scan_Enable, Byte_t Filter_Duplicates, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Create_Connection Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Create_Connection(unsigned int BluetoothStackID, Word_t LE_Scan_Interval, Word_t LE_Scan_Window, Byte_t Initiator_Filter_Policy, Byte_t Peer_Address_Type, BD_ADDR_t Peer_Address, Byte_t Own_Address_Type, Word_t Conn_Interval_Min, Word_t Conn_Interval_Max, Word_t Conn_Latency, Word_t Supervision_Timeout, Word_t Minimum_CE_Length, Word_t Maximum_CE_Length, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Create_Connection_t)(unsigned int BluetoothStackID, Word_t LE_Scan_Interval, Word_t LE_Scan_Window, Byte_t Initiator_Filter_Policy, Byte_t Peer_Address_Type, BD_ADDR_t Peer_Address, Byte_t Own_Address_Type, Word_t Conn_Interval_Min, Word_t Conn_Interval_Max, Word_t Conn_Latency, Word_t Supervision_Timeout, Word_t Minimum_CE_Length, Word_t Maximum_CE_Length, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Create_Connection_Cancel */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Create_Connection_Cancel(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Create_Connection_Cancel_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Read_White_List_Size     */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* White_List_SizeResult variable will contain the White List Size   */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_White_List_Size(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *White_List_SizeResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_White_List_Size_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Byte_t *White_List_SizeResult);
#endif

   /* The following function issues the HCI_LE_Clear_White_List         */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Clear_White_List(unsigned int BluetoothStackID, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Clear_White_List_t)(unsigned int BluetoothStackID, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Add_Device_To_White_List */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Add_Device_To_White_List(unsigned int BluetoothStackID, Byte_t Address_Type, BD_ADDR_t Address, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Add_Device_To_White_List_t)(unsigned int BluetoothStackID, Byte_t Address_Type, BD_ADDR_t Address, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Remove_Device_From_White_List Command to the Bluetooth     */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter. This function        */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Remove_Device_From_White_List(unsigned int BluetoothStackID, Byte_t Address_Type, BD_ADDR_t Address, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Remove_Device_From_White_List_t)(unsigned int BluetoothStackID, Byte_t Address_Type, BD_ADDR_t Address, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Connection_Update Command*/
   /* to the Bluetooth Device that is associated with the Bluetooth     */
   /* Protocol Stack specified by the BluetoothStackID parameter.  This */
   /* function returns zero if successful, or a non-zero value if there */
   /* was an error.  If this function returns zero (success) then the   */
   /* StatusResult variable will contain the Status Result returned from*/
   /* the Bluetooth Device.                                             */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Connection_Update(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Conn_Interval_Min, Word_t Conn_Interval_Max, Word_t Conn_Latency, Word_t Supervision_Timeout, Word_t Minimum_CE_Length, Word_t Maximum_CE_Length, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Connection_Update_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Word_t Conn_Interval_Min, Word_t Conn_Interval_Max, Word_t Conn_Latency, Word_t Supervision_Timeout, Word_t Minimum_CE_Length, Word_t Maximum_CE_Length, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Set_Host_Channel_Classification Command to the Bluetooth   */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter. This function        */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Set_Host_Channel_Classification(unsigned int BluetoothStackID, LE_Channel_Map_t Channel_Map, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Set_Host_Channel_Classification_t)(unsigned int BluetoothStackID, LE_Channel_Map_t Channel_Map, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Read_Channel_Map         */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* Connection_HandleResult variable will contain the Connection      */
   /* Handle returned from the Bluetooth Device AND the                 */
   /* LE_Channel_MapResult variable will contain the LE Channel Map     */
   /* returned from the Bluetooth Device.                               */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_Channel_Map(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, LE_Channel_Map_t *Channel_MapResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_Channel_Map_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult, LE_Channel_Map_t *Channel_MapResult);
#endif

   /* The following function issues the HCI_LE_Read_Remote_Used_Features*/
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_Remote_Used_Features(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_Remote_Used_Features_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Encrypt Command to the   */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter. This function  */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the  Encrypted_DataResult variable  */
   /* will contain the Encrypted Data returned from the Bluetooth       */
   /* Device.                                                           */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Encrypt(unsigned int BluetoothStackID, Encryption_Key_t Key, Plain_Text_Data_t Plain_Text_Data, Byte_t *StatusResult, Encrypted_Data_t *Encrypted_DataResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Encrypt_t)(unsigned int BluetoothStackID, Encryption_Key_t Key, Plain_Text_Data_t Plain_Text_Data, Byte_t *StatusResult, Encrypted_Data_t *Encrypted_DataResult);
#endif

   /* The following function issues the HCI_LE_Rand Command to the      */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter. This function  */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the Random_NumberResult variable    */
   /* will contain the Random Number returned from the Bluetooth Device.*/
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Rand(unsigned int BluetoothStackID, Byte_t *StatusResult, Random_Number_t *Random_NumberResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Rand_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Random_Number_t *Random_NumberResult);
#endif

   /* The following function issues the HCI_LE_Start_Encryption         */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Start_Encryption(unsigned int BluetoothStackID, Word_t Connection_Handle, Random_Number_t Random_Number, Word_t Encrypted_Diversifier, Long_Term_Key_t Long_Term_Key, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Start_Encryption_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Random_Number_t Random_Number, Word_t Encrypted_Diversifier, Long_Term_Key_t Long_Term_Key, Byte_t *StatusResult);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Long_Term_Key_Request_Reply Command to the Bluetooth       */
   /* Device that is associated with the Bluetooth Protocol Stack       */
   /* specified by the BluetoothStackID parameter. This function        */
   /* returns zero if successful, or a non-zero value if there was      */
   /* an error.  If this function returns zero (success) then the       */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the Connection_HandleResult         */
   /* variable will contain the Connection Handle returned from the     */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Long_Term_Key_Request_Reply(unsigned int BluetoothStackID, Word_t Connection_Handle, Long_Term_Key_t Long_Term_Key, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Long_Term_Key_Request_Reply_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Long_Term_Key_t Long_Term_Key, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* The following function issues the                                 */
   /* HCI_LE_Long_Term_Key_Request_Negative_Reply Command to the        */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter. This function  */
   /* returns zero if successful, or a non-zero value if there was      */
   /* an error.  If this function returns zero (success) then the       */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the Connection_HandleResult         */
   /* variable will contain the Connection Handle returned from the     */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Long_Term_Key_Request_Negative_Reply(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Long_Term_Key_Request_Negative_Reply_t)(unsigned int BluetoothStackID, Word_t Connection_Handle, Byte_t *StatusResult, Word_t *Connection_HandleResult);
#endif

   /* The following function issues the HCI_LE_Read_Supported_States    */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device AND the          */
   /* LE_StatesResult variable will contain the LE States returned      */
   /* from the Bluetooth Device.                                        */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Read_Supported_States(unsigned int BluetoothStackID, Byte_t *StatusResult, LE_States_t *LE_StatesResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Read_Supported_States_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, LE_States_t *LE_StatesResult);
#endif

   /* The following function issues the HCI_LE_Receiver_Test            */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Receiver_Test(unsigned int BluetoothStackID, Byte_t RX_Frequency, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Receiver_Test_t)(unsigned int BluetoothStackID, Byte_t RX_Frequency, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Transmitter_Test         */
   /* Command to the Bluetooth Device that is associated with the       */
   /* Bluetooth Protocol Stack specified by the BluetoothStackID        */
   /* parameter. This function returns zero if successful, or a         */
   /* non-zero value if there was an error.  If this function returns   */
   /* zero (success) then the StatusResult variable will contain the    */
   /* Status Result returned from the Bluetooth Device.                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Transmitter_Test(unsigned int BluetoothStackID, Byte_t TX_Frequency, Byte_t Length_Of_Test_Data, Byte_t Packet_Payload, Byte_t *StatusResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Transmitter_Test_t)(unsigned int BluetoothStackID, Byte_t TX_Frequency, Byte_t Length_Of_Test_Data, Byte_t Packet_Payload, Byte_t *StatusResult);
#endif

   /* The following function issues the HCI_LE_Test_End Command to the  */
   /* Bluetooth Device that is associated with the Bluetooth Protocol   */
   /* Stack specified by the BluetoothStackID parameter. This function  */
   /* returns zero if successful, or a non-zero value if there was an   */
   /* error.  If this function returns zero (success) then the          */
   /* StatusResult variable will contain the Status Result returned     */
   /* from the Bluetooth Device AND the Number_Of_PacketsResult         */
   /* variable will contain the Number Of Packets returned from the     */
   /* Bluetooth Device.                                                 */
   /* * NOTE * This function blocks until either a result is returned   */
   /*          from the Bluetooth Device OR the function Times Out      */
   /*          Waiting for a response from the Bluetooth Device.        */
BTPSAPI_DECLARATION int BTPSAPI HCI_LE_Test_End(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Number_Of_PacketsResult);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_HCI_LE_Test_End_t)(unsigned int BluetoothStackID, Byte_t *StatusResult, Word_t *Number_Of_PacketsResult);
#endif

#endif
