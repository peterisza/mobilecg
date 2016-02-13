/*****< sppapi.h >*************************************************************/
/*      Copyright 2000 - 2014 Stonestreet One.                                */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  SPPAPI - Stonestreet One Bluetooth Stack SPP API Type Definitions,        */
/*           Constants, and Prototypes.                                       */
/*                                                                            */
/*  Author:  Damon Lange                                                      */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   03/15/01  D. Lange       Initial creation.                               */
/******************************************************************************/
#ifndef __SPPAPIH__
#define __SPPAPIH__

#include "BTPSKRNL.h"          /* BTPS Kernel Prototypes/Constants.           */

#include "BTAPITyp.h"          /* Bluetooth API Type Definitions.             */
#include "BTTypes.h"           /* Bluetooth Type Definitions/Constants.       */
#include "RFCOMMT.h"           /* Bluetooth RFCOMM Type Definitions/Constants.*/
#include "SDPAPI.h"            /* Bluetooth SDP API Definitions/Constants.    */

#include "BTPSCFG.h"            /* BTPS Configuration Constants.              */

   /* The following Constants represent the Minimum and Maximum Port    */
   /* Numbers that can be opened (both locally and remotely).  These    */
   /* constants specify the range for the Port Number parameters in the */
   /* Open Port Functions.                                              */
#define SPP_PORT_NUMBER_MINIMUM           (RFCOMM_MINIMUM_SERVER_CHANNEL_ID)
#define SPP_PORT_NUMBER_MAXIMUM           (RFCOMM_MAXIMUM_SERVER_CHANNEL_ID)

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability of testing whether or not a specified SPP Port Number */
   /* Value is valid.  The first parameter to this MACRO is the SPP     */
   /* Port Number Value to verify.  This MACRO returns a boolean value  */
   /* based upon whether or not the specified SPP Port Number value     */
   /* is valid.  This MACRO returns a boolean TRUE if the specified     */
   /* SPP Port Number value is valid, or a boolean FALSE if the         */
   /* specified SPP Port Number value is invalid.                       */
#define SPP_VALID_PORT_NUMBER(_x)                               (((_x) >= SPP_PORT_NUMBER_MINIMUM) && ((_x) <= SPP_PORT_NUMBER_MAXIMUM))

   /* SDP Service Classes for the Serial Port Profile.                  */

   /* The following MACRO is a utility MACRO that assigns the Serial    */
   /* Port Service Class Bluetooth Universally Unique Identifier        */
   /* (SERIAL_PORT_PROFILE_UUID_16) to the specified UUID_16_t variable.*/
   /* This MACRO accepts one parameter which is the UUID_16_t variable  */
   /* that is to receive the SERIAL_PORT_PROFILE_UUID_16 Constant value.*/
#define SDP_ASSIGN_SERIAL_PORT_PROFILE_UUID_16(_x)  ASSIGN_SDP_UUID_16((_x), 0x11, 0x01)

   /* The following MACRO is a utility MACRO that assigns the Serial    */
   /* Port Service Class Bluetooth Universally Unique Identifier        */
   /* (SERIAL_PORT_PROFILE_UUID_16) to the specified UUID_32_t variable.*/
   /* This MACRO accepts one parameter which is the UUID_32_t variable  */
   /* that is to receive the SERIAL_PORT_PROFILE_UUID_32 Constant value.*/
#define SDP_ASSIGN_SERIAL_PORT_PROFILE_UUID_32(_x)  ASSIGN_SDP_UUID_32((_x), 0x00, 0x00, 0x11, 0x01)

   /* The following MACRO is a utility MACRO that assigns the Serial    */
   /* Port Service Class Bluetooth Universally Unique Identifier        */
   /* (SERIAL_PORT_PROFILE_UUID_128) to the specified UUID_128_t        */
   /* variable.  This MACRO accepts one parameter which is the          */
   /* UUID_128_t variable that is to receive the                        */
   /* SERIAL_PORT_PROFILE_UUID_128 Constant value.                      */
#define SDP_ASSIGN_SERIAL_PORT_PROFILE_UUID_128(_x) ASSIGN_SDP_UUID_128((_x), 0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB)

   /* The following constants represent the Port Open Status Values     */
   /* that are possible in the SPP Open Port Confirmation Event Data    */
   /* Information.                                                      */
#define SPP_OPEN_PORT_STATUS_SUCCESS                                    0x00
#define SPP_OPEN_PORT_STATUS_CONNECTION_TIMEOUT                         0x01
#define SPP_OPEN_PORT_STATUS_CONNECTION_REFUSED                         0x02
#define SPP_OPEN_PORT_STATUS_UNKNOWN_ERROR                              0x03

   /* The following Constants represent the allowable Minimum and       */
   /* Maximum Baud Rate (Bits/Second) that are supported by the Serial  */
   /* Port Profile.                                                     */
#define SPP_BAUD_RATE_MINIMUM                                           2400
#define SPP_BAUD_RATE_MAXIMUM                                         230400

   /* The following Constants represent the ONLY allowable Baud Rates   */
   /* (Bits/Second) that are supported by the Serial Port Profile.      */
#define SPP_BAUD_RATE_2400                                              2400
#define SPP_BAUD_RATE_4800                                              4800
#define SPP_BAUD_RATE_7200                                              7200
#define SPP_BAUD_RATE_9600                                              9600
#define SPP_BAUD_RATE_19200                                            19200
#define SPP_BAUD_RATE_38400                                            38400
#define SPP_BAUD_RATE_57600                                            57600
#define SPP_BAUD_RATE_115200                                          115200
#define SPP_BAUD_RATE_230400                                          230400

   /* The following Constants represent the allowable Minimum and       */
   /* Maximum Number of Data bits that are supported by the Serial      */
   /* Port Profile.                                                     */
#define SPP_DATA_BITS_MINIMUM                                           0x05
#define SPP_DATA_BITS_MAXIMUM                                           0x08

#define SPP_DATA_BITS_5                                                 0x05
#define SPP_DATA_BITS_6                                                 0x06
#define SPP_DATA_BITS_7                                                 0x07
#define SPP_DATA_BITS_8                                                 0x08

   /* The following enumerated type represents the supported Stop Bit   */
   /* types for the Serial Port Profile.                                */
typedef enum
{
   sbOneStopBit,
   sbOneOneHalfStopBit
} SPP_Stop_Bits_t;

   /* The following enumerated type represents the supported Parity     */
   /* types for the Serial Port Profile.                                */
typedef enum
{
   ptNone,
   ptOdd,
   ptEven,
   ptMark,
   ptSpace
} SPP_Parity_t;

   /* The following Bit Definitions represent the defined Bit Maps that */
   /* specify how many fields (if any) of the                           */
   /* SPP_Port_Open_Information_t are present.                          */
#define SPP_PORT_INFORMATION_NONE_VALUE                         0x00000000
#define SPP_PORT_INFORMATION_BAUD_RATE_BIT                      0x00000001
#define SPP_PORT_INFORMATION_DATA_BITS_BIT                      0x00000002
#define SPP_PORT_INFORMATION_STOP_BITS_BIT                      0x00000004
#define SPP_PORT_INFORMATION_PARITY_BIT                         0x00000008
#define SPP_PORT_INFORMATION_XON_CHARACTER_BIT                  0x00000010
#define SPP_PORT_INFORMATION_XOFF_CHARACTER_BIT                 0x00000020
#define SPP_PORT_INFORMATION_FLOW_CONTROL_BIT                   0x00000040

   /* The following Bit Definitions represent the defined Flow Control  */
   /* Bit Masks that are supported by the Serial Port Profile.          */
#define SPP_FLOW_CONTROL_DISABLED_VALUE                         0x00000000
#define SPP_FLOW_CONTROL_XON_XOFF_INPUT_ENABLED_BIT             0x00000001
#define SPP_FLOW_CONTROL_XON_XOFF_OUTPUT_ENABLED_BIT            0x00000002
#define SPP_FLOW_CONTROL_CTS_INPUT_ENABLED_BIT                  0x00000004
#define SPP_FLOW_CONTROL_RTS_OUTPUT_ENABLED_BIT                 0x00000008
#define SPP_FLOW_CONTROL_DSR_INPUT_ENABLED_BIT                  0x00000010
#define SPP_FLOW_CONTROL_DTR_OUTPUT_ENABLED_BIT                 0x00000020

   /* The following structure represents the Port Information that can  */
   /* be specified when opening a Port.  This information is optional   */
   /* because the Serial Port Profile does NOT need this information to */
   /* virtualize a Serial Port over Bluetooth.  This information would  */
   /* only be of value for an application that needed to open a Serial  */
   /* Port (physical) to pass data through.  There also exist API's to  */
   /* query and set the this information about a Serial Port.           */
typedef struct _tagSPP_Port_Information_t
{
   unsigned int    PortInformationMask;
   unsigned long   BaudRate;
   unsigned int    DataBits;
   SPP_Stop_Bits_t StopBits;
   SPP_Parity_t    Parity;
   Byte_t          XOnCharacter;
   Byte_t          XOffCharacter;
   unsigned int    FlowControlMask;
} SPP_Port_Information_t;

#define SPP_PORT_INFORMATION_SIZE                       (sizeof(SPP_Port_Information_t))

   /* The following structure is used with the SPP_Register_SDP_Record()*/
   /* function.  This structure (when specified) contains additional    */
   /* SDP Service Information that will be added to the SDP SPP Service */
   /* Record Entry.  The first member of this strucuture specifies the  */
   /* Number of Service Class UUID's that are present in the            */
   /* SDPUUIDEntries Array.  This member must be at least one, and      */
   /* the SDPUUIDEntries member must point to an array of SDP UUID      */
   /* Entries that contains (at least) as many entries specified by     */
   /* the NumberServiceClassUUID member.  The ProtocolList member is    */
   /* an SDP Data Element Sequence that contains a list of Protocol     */
   /* Information that will be added to the generic SDP Service         */
   /* Record.                                                           */
typedef struct _tagSPP_SDP_Service_Record_t
{
   unsigned int        NumberServiceClassUUID;
   SDP_UUID_Entry_t   *SDPUUIDEntries;
   SDP_Data_Element_t *ProtocolList;
} SPP_SDP_Service_Record_t;

#define SPP_SDP_SERVICE_RECORD_SIZE                     (sizeof(SPP_SDP_Service_Record_t))

   /* The following structure is used with the                          */
   /* SPP_Register_Raw_SDP_Record() function.  This structure (when     */
   /* specified) contains additional SDP Service Information that will  */
   /* be added to the SDP SPP Service Record Entry.  The first member of*/
   /* this strucuture specifies the Number of Service Class UUID's that */
   /* are present in the SDPUUIDEntries Array.  This member must be at  */
   /* least one, and the SDPUUIDEntries member must point to an array of*/
   /* SDP UUID Entries that contains (at least) as many entries         */
   /* specified by the NumberServiceClassUUID member.  The              */
   /* NumberOfProtocolDataListUUIDOffsets and                           */
   /* ProtocolDataListUUIDOffsets specify the offsets of the UUIDs in   */
   /* the specified ProtocolDataList data (if any UUIDs).  The          */
   /* ProtocolDataListLength and ProtocolDataList members must contain  */
   /* (if specified) a formatted SDP Data Element Sequence that contains*/
   /* a list of Protocol Information that will be added to the generic  */
   /* SDP Service Record.                                               */
typedef struct _tagSPP_SDP_Raw_Service_Record_t
{
   unsigned int      NumberServiceClassUUID;
   SDP_UUID_Entry_t *SDPUUIDEntries;
   unsigned int      NumberOfProtocolDataListUUIDOffsets;
   Word_t           *ProtocolDataListUUIDOffsets;
   unsigned int      ProtocolDataListLength;
   Byte_t           *ProtocolDataList;
} SPP_SDP_Raw_Service_Record_t;

#define SPP_SDP_RAW_SERVICE_RECORD_SIZE                  (sizeof(SPP_SDP_Raw_Service_Record_t))

   /* The following Constants represent the Minimum, Maximum and        */
   /* Default Buffer Sizes that are supported for Transmit/Receive      */
   /* Buffers.  These Constants can be used with the                    */
   /* SPP_Change_Buffer_Size(), SPP_Set_Configuration_Parameters(), and */
   /* the SPP_Get_Configuration_Parameters() functions.  The special    */
   /* Constant SPP_BUFFER_SIZE_CURRENT is used with the                 */
   /* SPP_Change_Buffer_Size() and the                                  */
   /* SPP_Set_Configuration_Parameters() function to inform the function*/
   /* NOT to change the Buffer Size.                                    */
#define SPP_BUFFER_SIZE_MINIMUM                                        (BTPS_CONFIGURATION_SPP_MINIMUM_SUPPORTED_STACK_BUFFER_SIZE)
#define SPP_BUFFER_SIZE_MAXIMUM                                        (BTPS_CONFIGURATION_SPP_MAXIMUM_SUPPORTED_STACK_BUFFER_SIZE)
#define SPP_BUFFER_SIZE_DEFAULT_TRANSMIT                               (BTPS_CONFIGURATION_SPP_DEFAULT_TRANSMIT_BUFFER_SIZE)
#define SPP_BUFFER_SIZE_DEFAULT_RECEIVE                                (BTPS_CONFIGURATION_SPP_DEFAULT_RECEIVE_BUFFER_SIZE)
#define SPP_BUFFER_SIZE_CURRENT                                         0

   /* The following Constants represent the Minimum, Maximum and Default*/
   /* RFCOMM Frame Sizes that are supported by the SPP Module.  These   */
   /* Constants can be used with the SPP_Set_Configuration_Parameters() */
   /* and the SPP_Get_Configuration_Parameters() functions.  The special*/
   /* Constant SPP_FRAME_SIZE_CURRENT is used with the                  */
   /* SPP_Set_Configuration_Parameters() function to inform the function*/
   /* NOT to change the Default Frame Size.                             */
#define SPP_FRAME_SIZE_MINIMUM                                         (RFCOMM_FRAME_SIZE_MINIMUM_VALUE)
#define SPP_FRAME_SIZE_MAXIMUM                                         (RFCOMM_MAXIMUM_SUPPORTED_STACK_FRAME_SIZE)
#define SPP_FRAME_SIZE_DEFAULT                                         (BTPS_CONFIGURATION_SPP_DEFAULT_FRAME_SIZE)
#define SPP_FRAME_SIZE_CURRENT                                          0

   /* The following structure represents the structure of the User      */
   /* configurable parameter structure that can be used to change the   */
   /* default behaviour of SPP Clients and Servers.  This structure is  */
   /* used with the SPP_Get_Configuration_Parameters() and the          */
   /* SPP_Set_Configuration_Parameters() functions.                     */
typedef struct _tagSPP_Configuration_Params_t
{
   Word_t       MaximumFrameSize;
   unsigned int TransmitBufferSize;
   unsigned int ReceiveBufferSize;
} SPP_Configuration_Params_t;

#define SPP_CONFIGURATION_PARAMS_SIZE                   (sizeof(SPP_Configuration_Params_t))

   /* The following Bit Definitions represent the allowable Flags for an*/
   /* SPP_Purge_Buffer() operation.  Either Transmit or Receive can be  */
   /* specified simultaneously.  Abort and Flush may not be used        */
   /* simultaneously.                                                   */
#define SPP_PURGE_MASK_TRANSMIT_ABORT_BIT                       0x00000001
#define SPP_PURGE_MASK_RECEIVE_ABORT_BIT                        0x00000002
#define SPP_PURGE_MASK_TRANSMIT_FLUSH_BIT                       0x00000004

   /* The following enumerated type represents the Status of the Break  */
   /* Signal for a specified Serial Port.                               */
typedef enum
{
   bsBreakCleared,
   bsBreakReceived
} SPP_Break_Status_t;

   /* The following Constants represent the Bit Mask that specifies     */
   /* the value of an individual Modem/Port Control Signal.  If the     */
   /* specified Bit has a binary value of '1', then the Signal is       */
   /* considered to be set, else it is considered NOT set (clear).      */
   /* This Bit Mask is used with the SPP_Port_Status() function.        */
#define SPP_PORT_STATUS_CLEAR_VALUE                             0x00000000
#define SPP_PORT_STATUS_RTS_CTS_BIT                             0x00000001
#define SPP_PORT_STATUS_DTR_DSR_BIT                             0x00000002
#define SPP_PORT_STATUS_RING_INDICATOR_BIT                      0x00000004
#define SPP_PORT_STATUS_CARRIER_DETECT_BIT                      0x00000008

   /* The following constants represent the valid SPP Break Interval    */
   /* values that can be used with the SPP_Send_Break() function.       */
#define SPP_BREAK_SIGNAL_DETECTED           (RFCOMM_BREAK_SIGNAL_DETECTED)
#define SPP_BREAK_SIGNAL_MINIMUM            (RFCOMM_BREAK_TIMEOUT_INTERVAL*RFCOMM_BREAK_SIGNAL_MINIMUM)
#define SPP_BREAK_SIGNAL_MAXIMUM            (RFCOMM_BREAK_TIMEOUT_INTERVAL*RFCOMM_BREAK_SIGNAL_MAXIMUM)

   /* The following Constants represent the Bit Mask that specifies     */
   /* the value of an individual Modem/Port Line Status Signal.  If the */
   /* specified Bit has a binary value of '1', then the Signal is       */
   /* considered to be set, else it is considered NOT set (clear).      */
   /* This Bit Mask is used with the SPP_Line_Status() function.        */
#define SPP_LINE_STATUS_NO_ERROR_VALUE                                  0x00
#define SPP_LINE_STATUS_OVERRUN_ERROR_BIT_MASK                          0x01
#define SPP_LINE_STATUS_PARITY_ERROR_BIT_MASK                           0x02
#define SPP_LINE_STATUS_FRAMING_ERROR_BIT_MASK                          0x04

   /* The following enumerated type represents the supported Server     */
   /* Connection Modes supported by a specified Serial Port Server.     */
typedef enum
{
   smAutomaticAccept,
   smAutomaticReject,
   smManualAccept
} SPP_Server_Connection_Mode_t;

#define SPP_DEFAULT_SERVER_CONNECTION_MODE                              (BTPS_CONFIGURATION_SPP_DEFAULT_SERVER_CONNECTION_MODE)

   /* The following enumerated type is used with the                    */
   /* SPP_Get_Port_Connection_State() function to determine the current */
   /* SPP/RFCOMM Connection state of a specific Client/Server Port.     */
typedef enum
{
   csPortNotPresent,
   csPortBusy,
   csPortDisconnecting,
   csPortReady
} SPP_Port_Connection_State_t;

   /* SPP Event API Types.                                              */
typedef enum
{
   etPort_Open_Indication,
   etPort_Open_Confirmation,
   etPort_Close_Port_Indication,
   etPort_Status_Indication,
   etPort_Data_Indication,
   etPort_Transmit_Buffer_Empty_Indication,
   etPort_Line_Status_Indication,
   etPort_Send_Port_Information_Indication,
   etPort_Send_Port_Information_Confirmation,
   etPort_Query_Port_Information_Indication,
   etPort_Query_Port_Information_Confirmation,
   etPort_Open_Request_Indication
} SPP_Event_Type_t;

typedef struct _tagSPP_Open_Port_Indication_Data_t
{
   unsigned int SerialPortID;
   BD_ADDR_t    BD_ADDR;
} SPP_Open_Port_Indication_Data_t;

#define SPP_OPEN_PORT_INDICATION_DATA_SIZE              (sizeof(SPP_Open_Port_Indication_Data_t))

typedef struct _tagSPP_Open_Port_Confirmation_Data_t
{
   unsigned int SerialPortID;
   unsigned int PortOpenStatus;
} SPP_Open_Port_Confirmation_Data_t;

#define SPP_OPEN_PORT_CONFIRMATION_DATA_SIZE            (sizeof(SPP_Open_Port_Confirmation_Data_t))

typedef struct _tagSPP_Close_Port_Indication_Data_t
{
   unsigned int SerialPortID;
} SPP_Close_Port_Indication_Data_t;

#define SPP_CLOSE_PORT_INDICATION_DATA_SIZE             (sizeof(SPP_Close_Port_Indication_Data_t))

typedef struct _tagSPP_Port_Status_Indication_Data_t
{
   unsigned int       SerialPortID;
   unsigned int       PortStatus;
   SPP_Break_Status_t BreakStatus;
   unsigned int       BreakTimeout;
} SPP_Port_Status_Indication_Data_t;

#define SPP_PORT_STATUS_INDICATION_DATA_SIZE           (sizeof(SPP_Port_Status_Indication_Data_t))

typedef struct _tagSPP_Data_Indication_Data_t
{
   unsigned int  SerialPortID;
   Word_t        DataLength;
} SPP_Data_Indication_Data_t;

#define SPP_DATA_INDICATION_DATA_SIZE                   (sizeof(SPP_Data_Indication_Data_t))

typedef struct _tagSPP_Transmit_Buffer_Empty_Indication_Data_t
{
   unsigned int  SerialPortID;
} SPP_Transmit_Buffer_Empty_Indication_Data_t;

#define SPP_TRANSMIT_BUFFER_EMPTY_INDICATION_DATA_SIZE  (sizeof(SPP_Transmit_Buffer_Empty_Indication_Data_t))

typedef struct _tagSPP_Line_Status_Indication_Data_t
{
   unsigned int      SerialPortID;
   unsigned int      SPPLineStatusMask;
} SPP_Line_Status_Indication_Data_t;

#define SPP_LINE_STATUS_INDICATION_DATA_SIZE            (sizeof(SPP_Line_Status_Indication_Data_t))

typedef struct _tagSPP_Send_Port_Information_Indication_Data_t
{
   unsigned int           SerialPortID;
   SPP_Port_Information_t SPPPortInformation;
} SPP_Send_Port_Information_Indication_Data_t;

#define SPP_SEND_PORT_INFORMATION_INDICATION_DATA_SIZE (sizeof(SPP_Send_Port_Information_Indication_Data_t))

typedef struct _tagSPP_Send_Port_Information_Confirmation_Data_t
{
   unsigned int           SerialPortID;
   SPP_Port_Information_t SPPPortInformation;
} SPP_Send_Port_Information_Confirmation_Data_t;

#define SPP_SEND_PORT_INFORMATION_CONFIRMATION_DATA_SIZE (sizeof(SPP_Send_Port_Information_Confirmation_Data_t))

typedef struct _tagSPP_Query_Port_Information_Indication_Data_t
{
   unsigned int  SerialPortID;
} SPP_Query_Port_Information_Indication_Data_t;

#define SPP_QUERY_PORT_INFORMATION_INDICATION_DATA_SIZE (sizeof(SPP_Query_Port_Information_Indication_Data_t))

typedef struct _tagSPP_Query_Port_Information_Confirmation_Data_t
{
   unsigned int           SerialPortID;
   SPP_Port_Information_t SPPPortInformation;
} SPP_Query_Port_Information_Confirmation_Data_t;

#define SPP_QUERY_PORT_INFORMATION_CONFIRMATION_DATA_SIZE (sizeof(SPP_Query_Port_Information_Confirmation_Data_t))

typedef struct _tagSPP_Open_Port_Request_Indication_Data_t
{
   unsigned int SerialPortID;
   BD_ADDR_t    BD_ADDR;
} SPP_Open_Port_Request_Indication_Data_t;

#define SPP_OPEN_PORT_REQUEST_INDICATION_DATA_SIZE      (sizeof(SPP_Open_Port_Request_Indication_Data_t))

   /* The following structure represents the container structure for    */
   /* Holding all SPP Event Data Data.                                  */
typedef struct _tagSPP_Event_Data_t
{
   SPP_Event_Type_t Event_Data_Type;
   Word_t           Event_Data_Size;
   union
   {
      SPP_Open_Port_Indication_Data_t                *SPP_Open_Port_Indication_Data;
      SPP_Open_Port_Confirmation_Data_t              *SPP_Open_Port_Confirmation_Data;
      SPP_Close_Port_Indication_Data_t               *SPP_Close_Port_Indication_Data;
      SPP_Port_Status_Indication_Data_t              *SPP_Port_Status_Indication_Data;
      SPP_Data_Indication_Data_t                     *SPP_Data_Indication_Data;
      SPP_Transmit_Buffer_Empty_Indication_Data_t    *SPP_Transmit_Buffer_Empty_Indication_Data;
      SPP_Line_Status_Indication_Data_t              *SPP_Line_Status_Indication_Data;
      SPP_Send_Port_Information_Indication_Data_t    *SPP_Send_Port_Information_Indication_Data;
      SPP_Send_Port_Information_Confirmation_Data_t  *SPP_Send_Port_Information_Confirmation_Data;
      SPP_Query_Port_Information_Indication_Data_t   *SPP_Query_Port_Information_Indication_Data;
      SPP_Query_Port_Information_Confirmation_Data_t *SPP_Query_Port_Information_Confirmation_Data;
      SPP_Open_Port_Request_Indication_Data_t        *SPP_Open_Port_Request_Indication_Data;
   } Event_Data;
} SPP_Event_Data_t;

#define SPP_EVENT_DATA_SIZE                             (sizeof(SPP_Event_Data_t))

   /* The following declared type represents the Prototype Function for */
   /* an SPP Event Receive Data Callback.  This function will be called */
   /* whenever a SPP Event occurs that is associated with the specified */
   /* Bluetooth Stack ID.  This function passes to the caller the       */
   /* Bluetooth Stack ID, the SPP Event Data that occurred and the SPP  */
   /* Event Callback Parameter that was specified when this Callback    */
   /* was installed.  The caller is free to use the contents of the SPP */
   /* SPP Event Data ONLY in the context of this callback.  If the      */
   /* caller requires the Data for a longer period of time, then the    */
   /* callback function MUST copy the data into another Data Buffer.    */
   /* This function is guaranteed NOT to be invoked more than once      */
   /* simultaneously for the specified installed callback (i.e. this    */
   /* function DOES NOT have be reentrant).  It Needs to be noted       */
   /* however, that if the same Callback is installed more than once,   */
   /* then the callbacks will be called serially.  Because of this, the */
   /* processing in this function should be as efficient as possible.   */
   /* It should also be noted that this function is called in the Thread*/
   /* Context of a Thread that the User does NOT own.  Therefore,       */
   /* processing in this function should be as efficient as possible    */
   /* (this argument holds anyway because another SPP Event will not be */
   /* processed while this function call is outstanding).               */
   /* ** NOTE ** This function MUST NOT Block and wait for events that  */
   /*            can only be satisfied by Receiving SPP Event Packets.  */
   /*            A Deadlock WILL occur because NO SPP Event Callbacks   */
   /*            will be issued while this function is currently        */
   /*            outstanding.                                           */
typedef void (BTPSAPI *SPP_Event_Callback_t)(unsigned int BluetoothStackID, SPP_Event_Data_t *SPP_Event_Data, unsigned long CallbackParameter);

   /* The following function is responsible for establishing a Serial   */
   /* Port Server (will wait for a connection to occur on the port      */
   /* established by this function).  This function accepts as input the*/
   /* Bluetooth Stack ID of the Bluetooth Protocol Stack that this      */
   /* Serial Port is to be established with.  The second parameter is   */
   /* the Port Number to establish.  This number *MUST* be between      */
   /* SPP_PORT_NUMBER_MINIMUM and SPP_PORT_NUMBER_MAXIMUM.  The last two*/
   /* parameters specify the SPP Event Callback function and Callback   */
   /* Parameter, respectively, that will be called with SPP Events that */
   /* occur on the specified Serial Port.  This function returns a      */
   /* non-zero, positive, number on success or a negative return error  */
   /* code if an error occurred (see BTERRORS.H).  A successful return  */
   /* code will be a Serial Port ID that can be used to reference the   */
   /* Opened Serial Port in ALL other functions in this module (except  */
   /* the SPP_Open_Remote_Port() function).  Once a Server Serial Port  */
   /* is opened, it can only be Un-Registered via a call to the         */
   /* SPP_Close_Server_Port() function (passing the return value from   */
   /* this function).  The SPP_Close_Port() function can be used to     */
   /* Disconnect a Client from the Server Port (if one is connected, it */
   /* will NOT Un-Register the Server Port however.                     */
BTPSAPI_DECLARATION int BTPSAPI SPP_Open_Server_Port(unsigned int BluetoothStackID, unsigned int ServerPort, SPP_Event_Callback_t SPP_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Open_Server_Port_t)(unsigned int BluetoothStackID, unsigned int ServerPort, SPP_Event_Callback_t SPP_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for Un-Registering a Serial */
   /* Port Server (which was Registered by a successful call to the     */
   /* SPP_Open_Server_Port() function).  This function accepts as input */
   /* the Bluetooth Stack ID of the Bluetooth Protocol Stack that the   */
   /* Serial Port specified by the Second Parameter is valid for.       */
   /* This function returns zero if successful, or a negative return    */
   /* error code if an error occurred (see BTERRORS.H).  Note that this */
   /* function does NOT delete any SDP Service Record Handles.          */
BTPSAPI_DECLARATION int BTPSAPI SPP_Close_Server_Port(unsigned int BluetoothStackID, unsigned int SerialPortID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Close_Server_Port_t)(unsigned int BluetoothStackID, unsigned int SerialPortID);
#endif

   /* The following function is responsible for responding to requests  */
   /* to connect to a Serial Port Server.  This function accepts as     */
   /* input the Bluetooth Stack ID of the Local Bluetooth Protocol      */
   /* Stack, the Serial Port ID (which *MUST* have been obtained by     */
   /* calling the SPP_Open_Server_Port() function), and as the final    */
   /* parameter whether to accept the pending connection request.  This */
   /* function returns zero if successful, or a negative return value if*/
   /* there was an error.                                               */
BTPSAPI_DECLARATION int BTPSAPI SPP_Open_Port_Request_Response(unsigned int BluetoothStackID, unsigned int SerialPortID, Boolean_t AcceptConnection);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Open_Port_Request_Response_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, Boolean_t AcceptConnection);
#endif

   /* The following function is provided to allow a means to add a      */
   /* Generic SDP Service Record to the SDP Database.  This function    */
   /* takes as input the Bluetooth Stack ID of the Local Bluetooth      */
   /* Protocol Stack, the Serial Port ID (which *MUST* have been        */
   /* obtained by calling the SPP_Open_Server_Port() function.  The     */
   /* third parameter (if specified) specifies any additional SDP       */
   /* Information to add to the record.  The fourth parameter specifies */
   /* the Service Name to associate with the SDP Record.  The final     */
   /* parameter is a pointer to a DWord_t which receives the SDP        */
   /* Service Record Handle if this function successfully creates an    */
   /* SDP Service Record.  If this function returns zero, then the      */
   /* SDPServiceRecordHandle entry will contain the Service Record      */
   /* Handle of the added SDP Service Record.  If this function fails,  */
   /* a negative return error code will be returned (see BTERRORS.H)    */
   /* and the SDPServiceRecordHandle value will be undefined.           */
   /* * NOTE * This function should only be called with the SerialPortID*/
   /*          that was returned from the SPP_Open_Server_Port()        */
   /*          function.  This function should NEVER be used with the   */
   /*          Serial Port ID returned from the SPP_Open_Remote_Port()  */
   /*          function.                                                */
   /* * NOTE * The Service Record Handle that is returned from this     */
   /*          function will remain in the SDP Record Database until    */
   /*          it is deleted by calling the SDP_Delete_Service_Record() */
   /*          function.                                                */
   /* * NOTE * A MACRO is provided to Delete the Service Record from    */
   /*          the SDP Data Base.  This MACRO maps the                  */
   /*          SPP_Un_Register_SDP_Record() to                          */
   /*          SDP_Delete_Service_Record().                             */
   /* * NOTE * If NO UUID Information is specified in the               */
   /*          SDPServiceRecord Parameter, then the default SPP Service */
   /*          Class's are added.  Any Protocol Information that is     */
   /*          specified (if any) will be added in the Protocol         */
   /*          Attribute AFTER the default SPP Protocol List (L2CAP     */
   /*          and RFCOMM).                                             */
   /* * NOTE * The Service Name is always added at Attribute ID 0x0100. */
   /*          A Language Base Attribute ID List is created that        */
   /*          specifies that 0x0100 is UTF-8 Encoded, English Language.*/
BTPSAPI_DECLARATION int BTPSAPI SPP_Register_SDP_Record(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_SDP_Service_Record_t *SDPServiceRecord, char *ServiceName, DWord_t *SDPServiceRecordHandle);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Register_SDP_Record_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_SDP_Service_Record_t *SDPServiceRecord, char *ServiceName, DWord_t *SDPServiceRecordHandle);
#endif

   /* The following MACRO is a utility MACRO that simply registers a    */
   /* generic SPP SDP Service Record.  This MACRO simply maps to the    */
   /* SPP_Register_Raw_SDP_Record() function.  This MACRO is only       */
   /* provided so that the caller doesn't have to sift through the SDP  */
   /* API for very simplistic applications.  This function accepts as   */
   /* input the Bluetooth Stack ID of the Bluetooth Protocol Stack that */
   /* the Service Record exists on, the Serial Port ID (returned from a */
   /* successful call to the SPP_Open_Server_Port() function), the      */
   /* Service Name and a pointer to return the SDP Service Record       */
   /* Handle.  See the SPP_Register_Raw_SDP_Record() function for more  */
   /* information.  This MACRO returns the result of the                */
   /* SPP_Register_Raw_SDP_Record() function, which is zero for success */
   /* or a negative return error code (see BTERRORS.H).                 */
#define SPP_Register_Generic_SDP_Record(__BluetoothStackID, __SerialPortID, __ServiceName, __SDPServiceRecordHandle) \
   (SPP_Register_Raw_SDP_Record(__BluetoothStackID, __SerialPortID, NULL, __ServiceName, __SDPServiceRecordHandle))

   /* The following function is provided to allow a means to add a      */
   /* Generic raw SDP Service Record to the SDP Database.  This function*/
   /* takes as input the Bluetooth Stack ID of the Local Bluetooth      */
   /* Protocol Stack, the Serial Port ID (which *MUST* have been        */
   /* obtained by calling the SPP_Open_Server_Port() function.  The     */
   /* third parameter (if specified) specifies any additional SDP       */
   /* Information to add to the record.  The fourth parameter specifies */
   /* the Service Name to associate with the SDP Record.  The final     */
   /* parameter is a pointer to a DWord_t which receives the SDP Service*/
   /* Record Handle if this function successfully creates an SDP Service*/
   /* Record.  If this function returns zero, then the                  */
   /* SDPServiceRecordHandle entry will contain the Service Record      */
   /* Handle of the added SDP Service Record.  If this function fails, a*/
   /* negative return error code will be returned (see BTERRORS.H) and  */
   /* the SDPServiceRecordHandle value will be undefined.               */
   /* * NOTE * This function should only be called with the SerialPortID*/
   /*          that was returned from the SPP_Open_Server_Port()        */
   /*          function.  This function should NEVER be used with the   */
   /*          Serial Port ID returned from the SPP_Open_Remote_Port()  */
   /*          function.                                                */
   /* * NOTE * The Service Record Handle that is returned from this     */
   /*          function will remain in the SDP Record Database until it */
   /*          is deleted by calling the SDP_Delete_Service_Record()    */
   /*          function.                                                */
   /* * NOTE * A MACRO is provided to Delete the Service Record from the*/
   /*          SDP Data Base.  This MACRO maps the                      */
   /*          SPP_Un_Register_SDP_Record() to                          */
   /*          SDP_Delete_Service_Record().                             */
   /* * NOTE * If NO UUID Information is specified in the               */
   /*          SDPServiceRecord Parameter, then the default SPP Service */
   /*          Class's are added.  Any Protocol Information that is     */
   /*          specified (if any) will be added in the Protocol         */
   /*          Attribute AFTER the default SPP Protocol List (L2CAP and */
   /*          RFCOMM).                                                 */
   /* * NOTE * The Service Name is always added at Attribute ID 0x0100. */
   /*          A Language Base Attribute ID List is created that        */
   /*          specifies that 0x0100 is UTF-8 Encoded, English Language.*/
BTPSAPI_DECLARATION int BTPSAPI SPP_Register_Raw_SDP_Record(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_SDP_Raw_Service_Record_t *SDPServiceRecord, char *ServiceName, DWord_t *SDPServiceRecordHandle);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Register_Raw_SDP_Record_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_SDP_Raw_Service_Record_t *SDPServiceRecord, char *ServiceName, DWord_t *SDPServiceRecordHandle);
#endif

   /* The following MACRO is a utility MACRO that simply deletes the    */
   /* SPP SDP Service Record (specified by the third parameter) from    */
   /* SDP Database.  This MACRO simply maps to the                      */
   /* SDP_Delete_Service_Record() function.  This MACRO is only         */
   /* provided so that the caller doesn't have to sift through the SDP  */
   /* API for very simplistic applications.  This function accepts as   */
   /* input the Bluetooth Stack ID of the Bluetooth Protocol Stack that */
   /* the Service Record exists on, the Serial Port ID (returned from   */
   /* a successful call to the SPP_Open_Server_Port() function), and the*/
   /* SDP Service Record Handle.  The SDP Service Record Handle was     */
   /* returned via a succesful call to the SPP_Register_SDP_Record()    */
   /* function.  See the SPP_Register_SDP_Record() function for more    */
   /* information.  This MACRO returns the result of the                */
   /* SDP_Delete_Service_Record() function, which is zero for success   */
   /* or a negative return error code (see BTERRORS.H).                 */
#define SPP_Un_Register_SDP_Record(__BluetoothStackID, __SerialPortID, __SDPRecordHandle) \
        (SDP_Delete_Service_Record(__BluetoothStackID, __SDPRecordHandle))

   /* The following function is responsible for Opening a Remote Serial */
   /* Port on the specified Remote Device.  This function accepts the   */
   /* Bluetooth Stack ID of the Bluetooth Stack which is to open the    */
   /* Serial Connection as the first parameter.  The second parameter   */
   /* specifies the Board Address (NON NULL) of the Remote Bluetooth    */
   /* Device to connect with.  The next parameter specifies the Remote  */
   /* Server Channel ID to connect.  The final two parameters specify   */
   /* the SPP Event Callback function, and callback parameter,          */
   /* respectively, of the SPP Event Callback that is to process any    */
   /* further interaction with the specified Remote Port (Opening       */
   /* Status, Data Writes, etc).  This function returns a non-zero,     */
   /* positive, value if successful, or a negative return error code if */
   /* this function is unsuccessful.  If this function is successful,   */
   /* the return value will represent the Serial Port ID that can be    */
   /* passed to all other functions that require it.  Once a Serial Port*/
   /* is opened, it can only be closed via a call to the                */
   /* SPP_Close_Port() function (passing the return value from this     */
   /* function).                                                        */
BTPSAPI_DECLARATION int BTPSAPI SPP_Open_Remote_Port(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, unsigned int ServerPort, SPP_Event_Callback_t SPP_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Open_Remote_Port_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, unsigned int ServerPort, SPP_Event_Callback_t SPP_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function exists to close a Serial Port that was     */
   /* previously opened with the SPP_Open_Server_Port() function OR the */
   /* SPP_Open_Remote_Port() function.  This function accepts as input  */
   /* the Bluetooth Stack ID of the Bluetooth Stack which the Open      */
   /* Serial Port resides and the Serial Port ID (return value from one */
   /* of the above mentioned Open functions) of the Port to Close.  This*/
   /* function returns zero if successful, or a negative return value   */
   /* if there was an error.  This function does NOT Un-Register a SPP  */
   /* Server Port from the system, it ONLY disconnects any connection   */
   /* that is currently active on the Server Port.  The                 */
   /* SPP_Close_Server_Port() function can be used to Un-Register the   */
   /* SPP Server Port.                                                  */
BTPSAPI_DECLARATION int BTPSAPI SPP_Close_Port(unsigned int BluetoothStackID, unsigned int SerialPortID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Close_Port_t)(unsigned int BluetoothStackID, unsigned int SerialPortID);
#endif

   /* The following function is responsible for Reading Serial Data from*/
   /* the specified Serial Connection.  The SerialPortID that is passed */
   /* to this function MUST have been established by either Accepting   */
   /* a Serial Port Connection (callback from the SPP_Open_Server_Port()*/
   /* function) or by initiating a Serial Port Connection (via calling  */
   /* the SPP_Open_Remote_Port() function and having the remote side    */
   /* accept the Connection).  The input parameters to this function are*/
   /* the Bluetooth Stack ID of the Bluetooth Stack that the second     */
   /* parameter is valid for (Serial Port Identifier), the Size of the  */
   /* Data Buffer to be used for reading and a pointer to the Data      */
   /* Buffer.  This function returns the number of data bytes that were */
   /* successfully read (zero if there were no Data Bytes ready to be   */
   /* read), or a negative return error code if unsuccessful.           */
BTPSAPI_DECLARATION int BTPSAPI SPP_Data_Read(unsigned int BluetoothStackID, unsigned int SerialPortID, Word_t DataBufferSize, Byte_t *DataBuffer);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Data_Read_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, Word_t DataBufferSize, Byte_t *DataBuffer);
#endif

   /* The following function is responsible for Sending Serial Data to  */
   /* the specified Serial Connection.  The SerialPortID that is passed */
   /* to this function MUST have been established by either Accepting   */
   /* a Serial Port Connection (callback from the SPP_Open_Server_Port()*/
   /* function) or by initiating a Serial Port Connection (via calling  */
   /* the SPP_Open_Remote_Port() function and having the remote side    */
   /* accept the Connection).  The input parameters to this function are*/
   /* the Bluetooth Stack ID of the Bluetooth Stack that the second     */
   /* parameter is valid for (Serial Port Identifier), the Length of    */
   /* the Data to send and a pointer to the Data Buffer to Send.  This  */
   /* function returns the number of data bytes that were successfully  */
   /* sent, or a negative return error code if unsuccessful.            */
   /* * NOTE * If this function is unable to send all of the data that  */
   /*          was specified (via the DataLength parameter), this       */
   /*          function will return the number of bytes that were       */
   /*          actually sent (zero or more, but less than the DataLength*/
   /*          parameter value).  When this happens (and ONLY when      */
   /*          this happens), the user can expect to be notified when   */
   /*          the Serial Port is able to send data again via the       */
   /*          etPort_Transmit_Buffer_Empty_Indication SPP Event.  This */
   /*          will allow the user a mechanism to know when the Transmit*/
   /*          Buffer is empty so that more data can be sent.           */
BTPSAPI_DECLARATION int BTPSAPI SPP_Data_Write(unsigned int BluetoothStackID, unsigned int SerialPortID, Word_t DataLength, Byte_t *DataBuffer);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Data_Write_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, Word_t DataLength, Byte_t *DataBuffer);
#endif

   /* The following function is provided to allow the programmer a      */
   /* means to change the default Transmit and Receive Buffer Sizes.    */
   /* This function accepts as input the Bluetooth Stack ID of the      */
   /* Bluetooth Protocol Stack that the specified Serial Port has been  */
   /* previously opened (second parameter), and the next two parameters */
   /* represent the requested Buffer size to change the Receive and     */
   /* Transmit Buffer to (respectively).  The special constant          */
   /* SPP_BUFFER_SIZE_CURRENT can be used to specify that the requested */
   /* Buffer Size (either Transmit and/or Receive) NOT be changed.      */
   /* This function returns zero if the specified Buffer Size(s) were   */
   /* changed, or a negative return error code if there was an error.   */
   /* * NOTE * This function causes ALL Data in each Buffer to be       */
   /*          lost.  This function clears the each Data Buffer so that */
   /*          all the available data buffer is available to be used.   */
BTPSAPI_DECLARATION int BTPSAPI SPP_Change_Buffer_Size(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int ReceiveBufferSize, unsigned int TransmitBufferSize);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Change_Buffer_Size_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int ReceiveBufferSize, unsigned int TransmitBufferSize);
#endif

   /* The following function exists to allow the user a mechanism for   */
   /* either aborting ALL Data present in either an Input or an Output  */
   /* Buffer, or a means to wait until a ALL Data present in either an  */
   /* Input or Output buffer has been removed.  This function takes as  */
   /* input the Bluetooth Stack ID of the Bluetooth Stack that contains */
   /* the Serial Port that was opened previously (specified by the next */
   /* parameter).  The final parameter is a BIT MASK that represents    */
   /* type of operation to perform.  This function returns zero if      */
   /* successful, or a negative return error code if unsuccessful.      */
   /* ** NOTE ** When using a PurgeBufferMask of                        */
   /*            SPP_PURGE_MASK_TRANSMIT_FLUSH_BIT, if the SPP Transmit */
   /*            Buffer is already empty this function will return      */
   /*            BTPS_ERROR_SPP_BUFFER_EMPTY.                           */
BTPSAPI_DECLARATION int BTPSAPI SPP_Purge_Buffer(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int PurgeBufferMask);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Purge_Buffer_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int PurgeBufferMask);
#endif

   /* The following function is provided to allow the programmer a      */
   /* means to notify the remote side of the Serial Connection of a     */
   /* Break Condition.  This function accepts as input the Bluetooth    */
   /* Stack ID of the Bluetooth Protocol Stack that the Serial Port     */
   /* is valid with (specified by the second parameter).  The final     */
   /* parameter (if specified specifies the length of time that the     */
   /* Break was detected.  This function returns zero if successful, or */
   /* a negative return value if there was an error.                    */
BTPSAPI_DECLARATION int BTPSAPI SPP_Send_Break(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int BreakTimeout);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Send_Break_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int BreakTimeout);
#endif

   /* The following function is provided to allow the programmer a      */
   /* method to send the existing state of the Line Status to the       */
   /* remote side.  This function accepts as input the Bluetooth Stack  */
   /* ID of the Bluetooth Protocol Stack that the specified Serial Port */
   /* has been opened on (the second parameter is the Serial Port), and */
   /* the Current Line Status State.  This function returns zero if     */
   /* successful, or a negative return value if there was an error.     */
BTPSAPI_DECLARATION int BTPSAPI SPP_Line_Status(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int SPPLineStatusMask);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Line_Status_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int SPPLineStatusMask);
#endif

   /* The following function is provided to allow the programmer a      */
   /* method to send the existing state of ALL Modem/Port Control       */
   /* Signals to the remote side.  This function accepts as input the   */
   /* Bluetooth Stack ID of the Bluetooth Protocol Stack that the       */
   /* specified Serial Port has been opened on (the second parameter is */
   /* the Serial Port), and the Current State of all the Modem Control  */
   /* Signals.  This function returns zero if successful, or a negative */
   /* return value if there was an error.                               */
BTPSAPI_DECLARATION int BTPSAPI SPP_Port_Status(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int PortStatus);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Port_Status_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, unsigned int PortStatus);
#endif

   /* The following function is provided to allow the programmer a      */
   /* method to inform the remote Side of the Serial Port Parameters    */
   /* that are to be used.  This function accepts as input the          */
   /* Bluetooth Stack ID of the Bluetooth Protocol Stack the specified  */
   /* Serial Port has been opened on (the second parameter is the       */
   /* Serial Port).  The final parameter to this function is the        */
   /* Requested Serial Port Information and cannot be NULL.  This       */
   /* function returns zero if successful, or a negative return value   */
   /* if there was an error.                                            */
BTPSAPI_DECLARATION int BTPSAPI SPP_Send_Port_Information(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Port_Information_t *SPPPortInformation);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Send_Port_Information_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Port_Information_t *SPPPortInformation);
#endif

   /* The following function is provided to allow the programmer a      */
   /* method to respond to a Serial Port Parameters Indication from the */
   /* remote side.  This function accepts as input the Bluetooth Stack  */
   /* ID of the Bluetooth Protocol Stack that the specified Serial Port */
   /* has been opened on (the second parameter is the Serial Port), and */
   /* the status fo the specified Port Information (acceptable or       */
   /* unacceptable).  This function returns zero if successful, or a    */
   /* negative return value if there was an error.                      */
BTPSAPI_DECLARATION int BTPSAPI SPP_Respond_Port_Information(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Port_Information_t *SPPPortInformation);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Respond_Port_Information_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Port_Information_t *SPPPortInformation);
#endif

   /* The following function is provided to allow the programmer a      */
   /* method to query the existing Serial Port Parameters from the      */
   /* remote side.  This function accepts as input the Bluetooth Stack  */
   /* ID of the Bluetooth Protocol Stack that the specified Serial Port */
   /* has been opened on (the second parameter is the Serial Port).     */
   /* This function returns zero if successful, or a negative return    */
   /* value if there was an error.                                      */
BTPSAPI_DECLARATION int BTPSAPI SPP_Query_Remote_Port_Information(unsigned int BluetoothStackID, unsigned int SerialPortID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Query_Remote_Port_Information_t)(unsigned int BluetoothStackID, unsigned int SerialPortID);
#endif

   /* The following function is provided to allow the programmer a      */
   /* method to respond to a Serial Port Parameters Request from the    */
   /* remote side.  This function accepts as input the Bluetooth Stack  */
   /* ID of the Bluetooth Protocol Stack that the specified Serial Port */
   /* has been opened on (the second parameter is the Serial Port), and */
   /* the Current Local Port Information.  This function returns zero   */
   /* if successful, or a negative return value if there was an error.  */
BTPSAPI_DECLARATION int BTPSAPI SPP_Respond_Query_Port_Information(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Port_Information_t *SPPPortInformation);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Respond_Query_Port_Information_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Port_Information_t *SPPPortInformation);
#endif

   /* The following function is responsible for allowing a mechanism to */
   /* query the current SPP Configuration Parameters.  These parameters */
   /* are the parameters that control the RFCOMM Frame Size (and the    */
   /* default Transmit and Receive Buffer sizes) that SPP will use when */
   /* opening/accepting SPP connections.  The first parameter to this   */
   /* function is the Bluetooth Stack ID of the Bluetooth Stack which   */
   /* this function is to query the SPP Configuration of.  The second   */
   /* parameter is a pointer to structure that will receive the current */
   /* SPP Configuration Information that is in use.  This function      */
   /* returns zero if successful or a negative return error code if an  */
   /* error occurs.                                                     */
   /* * NOTE * These parameters are set globally for the entire SPP     */
   /*          entity (per Bluetooth Stack Instance).  These values     */
   /*          can only be changed when NO SPP Clients or Servers are   */
   /*          open.                                                    */
   /* * NOTE * The Transmit and Receive Buffer sizes *MUST* be AT LEAST */
   /*          the size of the Maximum Frame Size that is being set.    */
BTPSAPI_DECLARATION int BTPSAPI SPP_Get_Configuration_Parameters(unsigned int BluetoothStackID, SPP_Configuration_Params_t *SPPConfigurationParams);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Get_Configuration_Parameters_t)(unsigned int BluetoothStackID, SPP_Configuration_Params_t *SPPConfigurationParams);
#endif

   /* The following function is responsible for allowing a mechanism    */
   /* to change the default SPP Configuration Parameters.  These        */
   /* parameters are the parameters that control the RFCOMM Frame Size  */
   /* (and the default Transmit and Receive Buffer sizes) that SPP will */
   /* use when opening/accepting SPP connections.  The first parameter  */
   /* to this function is the Bluetooth Stack ID of the Bluetooth Stack */
   /* which this function is to change the SPP Configuration of.  The   */
   /* second parameter is a pointer to structure that contains the new  */
   /* SPP Configuration Information to use.  This function returns zero */
   /* if successful or a negative return error code if an error occurs. */
   /* * NOTE * These parameters are set globally for the entire SPP     */
   /*          entity (per Bluetooth Stack Instance).  These values     */
   /*          can only be changed when NO SPP Clients or Servers are   */
   /*          open (i.e. this function can only be called when no      */
   /*          SPP Clients or Servers are active).                      */
   /* * NOTE * The Transmit and Receive Buffer sizes *MUST* be AT LEAST */
   /*          the size of the Maximum Frame Size that is being set.    */
BTPSAPI_DECLARATION int BTPSAPI SPP_Set_Configuration_Parameters(unsigned int BluetoothStackID, SPP_Configuration_Params_t *SPPConfigurationParams);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Set_Configuration_Parameters_t)(unsigned int BluetoothStackID, SPP_Configuration_Params_t *SPPConfigurationParams);
#endif

   /* The following function is responsible for allowing a mechanism to */
   /* query the SPP Server Connection Mode.  This function accepts as   */
   /* input the Bluetooth Stack ID of the Local Bluetooth Protocol      */
   /* Stack, the Serial Port ID (which *MUST* have been obtained by     */
   /* calling the SPP_Open_Server_Port() function), and as the final    */
   /* parameter a pointer to a Server Connection Mode variable which    */
   /* will receive the current Server Connection Mode.  This function   */
   /* returns zero if successful, or a negative return value if there   */
   /* was an error.                                                     */
BTPSAPI_DECLARATION int BTPSAPI SPP_Get_Server_Connection_Mode(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Server_Connection_Mode_t *SPPServerConnectionMode);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Get_Server_Connection_Mode_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Server_Connection_Mode_t *SPPServerConnectionMode);
#endif

   /* The following function is responsible for allowing a mechanism to */
   /* change the current SPP Server Connection Mode.  This function     */
   /* accepts as input the Bluetooth Stack ID of the Local Bluetooth    */
   /* Protocol Stack, the Serial Port ID (which *MUST* have been        */
   /* obtained by calling the SPP_Open_Server_Port() function), and as  */
   /* the final parameter the new Server Connection Mode to use.  This  */
   /* function returns zero if successful, or a negative return value if*/
   /* there was an error.                                               */
BTPSAPI_DECLARATION int BTPSAPI SPP_Set_Server_Connection_Mode(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Server_Connection_Mode_t SPPServerConnectionMode);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Set_Server_Connection_Mode_t)(unsigned int BluetoothStackID, unsigned int SerialPortID, SPP_Server_Connection_Mode_t SPPServerConnectionMode);
#endif

   /* The following function is a utility function that exists to       */
   /* determine the current SPP (RFCOMM) Connection state for a specific*/
   /* SPP/RFCOMM Connection.  This function accepts as input, the       */
   /* Bluetooth Stack ID of the Bluetooth Stack for which the request is*/
   /* valid for, followed by the Bluetooth Device Address of the        */
   /* connection in question (required), followed by the SPP/RFCOMM     */
   /* Server Port Number of the connection in question, followed by a   */
   /* flag that specifies whether or not the connection is to a Local   */
   /* SPP Server (TRUE) or a Remote SPP Server (FALSE), followed by a   */
   /* pointer to state variable that is to receive the state            */
   /* information.  This function returns zero if successful, or a      */
   /* negative return error code if there was an error.                 */
   /* * NOTE * This function will only supply a value in the SPP        */
   /*          Port Connection State parameter if the return value from */
   /*          this function is success (0).  If this function returns  */
   /*          an error, then the contents of this variable will be     */
   /*          undefined.                                               */
   /* * NOTE * The Bluetooth Address is a required parameter and is     */
   /*          used to determine the TEI of the underlying RFCOMM       */
   /*          Connection.                                              */
   /* * NOTE * The ServerPort parameter must be one of the following:   */
   /*             - 0 (queries if a connection to the remote device     */
   /*               specifies is possible)                              */
   /*             - SPP_PORT_NUMBER_MINIMUM                             */
   /*             - SPP_PORT_NUMBER_MAXIMUM                             */
   /*          Note that the above values are NOT the SPP Port ID       */
   /*          values returned from the SPP_Open_Server_Port() or the   */
   /*          SPP_Open_Remote_Port() functions, but rather are the     */
   /*          actual SPP/RFCOMM Port Channel Numbers !!!!!!!!!!!!!!!!! */
   /* * NOTE * This is a very low level function and exists solely to   */
   /*          allow a mechanism to determine the current Control       */
   /*          Message State for the underlying RFCOMM Transport.  This */
   /*          is needed in some circumstances when trying to connect or*/
   /*          disconnect SPP Ports and the user has no way of knowning */
   /*          knowing the current Status (keep in mind that there can  */
   /*          only be a single Control Message outstanding on any      */
   /*          given RFCOMM Channel).                                   */
BTPSAPI_DECLARATION int BTPSAPI SPP_Get_Port_Connection_State(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, unsigned int ServerPort, Boolean_t LocalPort, SPP_Port_Connection_State_t *SPP_Port_Connection_State);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Get_Port_Connection_State_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, unsigned int ServerPort, Boolean_t LocalPort, SPP_Port_Connection_State_t *SPP_Port_Connection_State);
#endif

   /* The following function is responsible for setting the lower level */
   /* queuing parameters.  These parameters are used to control aspects */
   /* of the amount of data packets that can be queued into the lower   */
   /* level (per individual channel).  This mechanism allows for the    */
   /* flexibility to limit the amount of RAM that is used for streaming */
   /* type applications (where the remote side has a large number of    */
   /* credits that were granted).  This function accepts as input the   */
   /* Bluetooth Stack ID of the Bluetooth stack in which to set the     */
   /* system wide queuing parameters, followed by the maximum number of */
   /* queued data packets (per DLCI), followed by the low threshold     */
   /* (used be the lower layer to inform RFCOMM when it can send another*/
   /* data packet).  This function returns zero if successful or a      */
   /* negative return error code if there is an error.                  */
   /* * NOTE * This function can only be called when there are NO active*/
   /*          connections.                                             */
   /* * NOTE * Setting both parameters to zero will disable the queuing */
   /*          mechanism.  This means that the amount of queued packets */
   /*          will only be limited via the amount of available RAM.    */
   /* * NOTE * These parameters do not affect the transmit and receive  */
   /*          buffers and do not affect any frame sizes and/or credit  */
   /*          logic.  These parameters ONLY affect the number of       */
   /*          data packets queued into the lower level.                */
BTPSAPI_DECLARATION int BTPSAPI SPP_Set_Queuing_Parameters(unsigned int BluetoothStackID, unsigned int MaximumNumberDataPackets, unsigned int QueuedDataPacketsThreshold);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Set_Queuing_Parameters_t)(unsigned int BluetoothStackID, unsigned int MaximumNumberDataPackets, unsigned int QueuedDataPacketsThreshold);
#endif

   /* The following function is responsible for setting the lower level */
   /* queuing parameters.  These parameters are used to control aspects */
   /* of the amount of data packets that can be queued into the lower   */
   /* level (per individual channel).  This mechanism allows for the    */
   /* flexibility to limit the amount of RAM that is used for streaming */
   /* type applications (where the remote side has a large number of    */
   /* credits that were granted).  This function accepts as input the   */
   /* Bluetooth Stack ID of the Bluetooth stack in which to get the     */
   /* lower level queuing parameters, followed by a pointer to a        */
   /* variable that is to receive the maximum number of queued data     */
   /* packets (per channel), followed by the low threshold (used be the */
   /* lowest layer to inform the lower layer when it can send another   */
   /* data packet).  This function returns zero if successful or a      */
   /* negative return error code if there is an error.                  */
BTPSAPI_DECLARATION int BTPSAPI SPP_Get_Queuing_Parameters(unsigned int BluetoothStackID, unsigned int *MaximumNumberDataPackets, unsigned int *QueuedDataPacketsThreshold);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Get_Queuing_Parameters_t)(unsigned int BluetoothStackID, unsigned int *MaximumNumberDataPackets, unsigned int *QueuedDataPacketsThreshold);
#endif

   /* The following function is provided to allow a mechanism to        */
   /* determine if a SPP Server Port is open on the specified RFCOMM    */
   /* Server Port.  This allows application developers a means to       */
   /* determine if there are free/active SPP servers on specific RFCOMM */
   /* ports.  This function accepts the Bluetooth Stack ID, followed by */
   /* the SPP Server Port (RFCOMM Channel) number to query.  The final  */
   /* parameters is a pointer to a variable that will hold the value (on*/
   /* success) for the server being present.  This value will be BOOLEAN*/
   /* TRUE if a server is registered with the system, or FALSE if there */
   /* is not a server registered with the system.  This function returns*/
   /* zero if successful, or a negative return error code if there was  */
   /* an error.                                                         */
   /* * NOTE * The ServerPort parameter must be one of the following:   */
   /*             - SPP_PORT_NUMBER_MINIMUM                             */
   /*             - SPP_PORT_NUMBER_MAXIMUM                             */
   /*          Note that the above values are NOT the SPP Port ID       */
   /*          values returned from the SPP_Open_Server_Port() function,*/
   /*          but rather are the actual SPP/RFCOMM Port Channel        */
   /*          Numbers !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
BTPSAPI_DECLARATION int BTPSAPI SPP_Query_Server_Present(unsigned int BluetoothStackID, unsigned int ServerPort, Boolean_t *ServerPresent);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_SPP_Query_Server_Present_t)(unsigned int BluetoothStackID, unsigned int ServerPort, Boolean_t *ServerPresent);
#endif

#endif
