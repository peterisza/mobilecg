/*****< rfcomapi.h >***********************************************************/
/*      Copyright 2000 - 2014 Stonestreet One.                                */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  RFCOMAPI - Stonestreet One Bluetooth Stack RFCOMM API Type Definitions,   */
/*             Constants, and Prototypes.                                     */
/*                                                                            */
/*  Author:  Tim Thomas                                                       */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   09/11/00  T. Thomas      Initial creation.                               */
/******************************************************************************/
#ifndef __RFCOMAPIH__
#define __RFCOMAPIH__

#include "BTPSKRNL.h"           /* BTPS Kernel Prototypes/Constants.          */

#include "BTAPITyp.h"           /* Bluetooth API Type Definitions.            */
#include "RFCOMMT.h"            /* Bluetooth RFCOMM Type Definitions.         */

#include "BTPSCFG.h"            /* BTPS Configuration Constants.              */

#define RFCOMM_MAXIMUM_SUPPORTED_STACK_FRAME_SIZE                            (BTPS_CONFIGURATION_RFCOMM_MAXIMUM_SUPPORTED_STACK_FRAME_SIZE)

   /* The following constants represent the Minimum, Maximum, and       */
   /* default Timer values (in Seconds) that are allowable for the      */
   /* System Parameters.                                                */
#define RFCOMM_ACKNOWLEDGEMENT_TIMER_MINIMUM_VALUE                           10
#define RFCOMM_ACKNOWLEDGEMENT_TIMER_MAXIMUM_VALUE                           60
#define RFCOMM_ACKNOWLEDGEMENT_TIMER_DEFAULT_VALUE                           (BTPS_CONFIGURATION_RFCOMM_DEFAULT_ACKNOWLEDGEMENT_TIMER_S)

#define RFCOMM_RESPONSE_TIMER_MINIMUM_VALUE                                  10
#define RFCOMM_RESPONSE_TIMER_MAXIMUM_VALUE                                  60
#define RFCOMM_RESPONSE_TIMER_DEFAULT_VALUE                                  (BTPS_CONFIGURATION_RFCOMM_DEFAULT_RESPONSE_TIMER_S)

   /* The following constants represent values for the Line Status      */
   /* Command.                                                          */
#define RFCOMM_LINE_STATUS_NO_ERROR_BIT_MASK                               0x00
#define RFCOMM_LINE_STATUS_OVERRUN_ERROR_BIT_MASK                          0x03
#define RFCOMM_LINE_STATUS_PARITY_ERROR_BIT_MASK                           0x05
#define RFCOMM_LINE_STATUS_FRAMING_ERROR_BIT_MASK                          0x09

   /* The following constants represent the allowable RFCOMM Flow Types.*/
typedef enum
{
   ftCreditFlowNotAllowed,
   ftCreditFlowPreferred,
   ftCreditFlowManditory
} RFCOMM_Flow_Type_t;

   /* The following structure represents options that the user can      */
   /* specify when Opening a Remote RFCOMM Channel.  This structure is  */
   /* used with the RFCOMM_Open_Request() function.                     */
typedef struct _tagRFCOMM_Open_Parameters_t
{
   Byte_t OptionFlags;
   Word_t MaximumFrameSize;
   Byte_t InitialCredits;
} RFCOMM_Open_Parameters_t;

#define RFCOMM_OPEN_PARAMETERS_SIZE                      (sizeof(RFCOMM_Open_Params_t))

   /* The following structure represents the data that can be negotiated*/
   /* with the RFCOMM Port Negotiation Command.                         */
typedef struct _tagRFCOMM_PN_Data_t
{
   Word_t             MaximumFrameSize;
   RFCOMM_Flow_Type_t FlowType;
   Byte_t             Credits;
} RFCOMM_PN_Data_t;

#define RFCOMM_PN_DATA_SIZE                             (sizeof(RFCOMM_PN_Data_t))

   /* The following structure contains the system parameters that are   */
   /* negotiated per RFCOMM session.                                    */
typedef struct _tagRFCOMM_System_Parameters_t
{
   Boolean_t          NegotiateParams;
   Word_t             MaximumFrameSize;
   RFCOMM_Flow_Type_t FlowType;
   Byte_t             InitialCredits;
   Byte_t             AcknowledgementTimer;
   Byte_t             ResponseTimerForMultiplexer;
} RFCOMM_System_Parameters_t;

#define RFCOMM_SYSTEM_PARAMETERS_SIZE                    (sizeof(RFCOMM_System_Parameters_t))

   /* The following enumerated type is used with the                    */
   /* RFCOMM_Get_Channel_Status() function to report the actual         */
   /* status of a specific TEI and/or DLCI.                             */
typedef enum
{
   rsTEIReady,
   rsTEIDoesNotExist,
   rsTEIControlMessageOutstanding,
   rsTEIDisconnecting,
   rsDLCIDoesNotExist,
   rsDLCIReady,
   rsDLCIControlMessageOutstanding,
   rsDLCIDisconnecting
} RFCOMM_Channel_Status_t;

   /* The following enumerated type represents all the allowable RFCOMM */
   /* Events that will be occur in the RFCOMM Layer.                    */
typedef enum
{
   etOpen_Indication,
   etOpen_Confirmation,
   etRelease_Indication,
   etDLCI_Data_Indication,
   etDLCI_Param_Negotiation_Indication,
   etRemote_Port_Negotiation_Indication,
   etRemote_Port_Negotiation_Confirmation,
   etRemote_Line_Status_Indication,
   etRemote_Line_Status_Confirmation,
   etModem_Status_Indication,
   etModem_Status_Confirmation,
   etTest_Confirmation,
   etFlow_Indication,
   etFlow_Confirmation,
   etCredit_Indication,
   etNon_Supported_Command_Indication,
   etTransport_Buffer_Empty_Indication
} RFCOMM_Event_Data_Type_t;

   /* The following structure contains the parameters that can be       */
   /* negotiated between two RFCOMM entities.  These parameters are     */
   /* negotiated prior to the establishment of the DLCI.  The structure */
   /* does not contain a result field.  The initiator of the request    */
   /* will consider the parameters accepted if all of the values are    */
   /* acceptable to the initiator.                                      */
typedef struct _tagRFCOMM_Open_Indication_Data_t
{
   Word_t           TEI;
   Byte_t           DLCI;
   BD_ADDR_t        BD_ADDR;
   RFCOMM_PN_Data_t DLCI_Parameters;
} RFCOMM_Open_Indication_Data_t;

#define RFCOMM_OPEN_INDICATION_DATA_SIZE          (sizeof(RFCOMM_Open_Indication_Data_t))

   /* The following information represents the Open Status that is      */
   /* returned to the caller in the form of an etOpen_Confirmation      */
   /* Event.                                                            */
typedef struct _tagRFCOMM_Open_Confirmation_Data_t
{
   Word_t           TEI;
   Byte_t           DLCI;
   Byte_t           Result;
   RFCOMM_PN_Data_t DLCI_Parameters;
} RFCOMM_Open_Confirmation_Data_t;

#define RFCOMM_OPEN_CONFIRMATION_DATA_SIZE        (sizeof(RFCOMM_Open_Confirmation_Data_t))

   /* The following structure contains the DLCI that is passed to the   */
   /* upper layer when a connection is disconnected.                    */
typedef struct _tagRFCOMM_Release_Indication_Data_t
{
   Word_t TEI;
   Byte_t DLCI;
} RFCOMM_Release_Indication_Data_t;

#define RFCOMM_RELEASE_INDICATION_DATA_SIZE       (sizeof(RFCOMM_Release_Indication_Data_t))

   /* The following structure is used to forward data received to the   */
   /* upper layer.                                                      */
typedef struct _tagRFCOMM_Data_Data_t
{
   Word_t  TEI;
   Byte_t  DLCI;
   Word_t  DataLength;
   Byte_t *Data;
} RFCOMM_Data_Data_t;

#define RFCOMM_DATA_DATA_SIZE                     (sizeof(RFCOMM_Data_Data_t))

   /* The following structure contains parameters that are negotiated   */
   /* for each DLCI.                                                    */
typedef struct _tagRFCOMM_Param_Negotiation_Data_t
{
   Word_t           TEI;
   Byte_t           DLCI;
   RFCOMM_PN_Data_t Params;
} RFCOMM_Param_Negotiation_Data_t;

#define RFCOMM_PARAM_NEGOTIATION_DATA_SIZE        (sizeof(RFCOMM_Param_Negotiation_Data_t))

   /* The following structure contains the Remote Negotiation           */
   /* Parameters that are used with the Remote Port Negotiation Command */
   /* (RPN).                                                            */
typedef struct _tagRFCOMM_RPN_Port_Data_t
{
   Byte_t BaudRate;
   Byte_t DataFormat;
   Byte_t FlowControl;
   Byte_t XOnCharacter;
   Byte_t XOffCharacter;
   Word_t ParameterMask;
} RFCOMM_RPN_Port_Data_t;

#define RFCOMM_RPN_PORT_DATA_SIZE                 (sizeof(RFCOMM_RPN_Port_Data_t))

   /* The following structure contains configuration information about  */
   /* the remote port that are to be negotiated for each DLCI.          */
typedef struct _tagRFCOMM_Remote_Port_Negotiation_Data_t
{
   Word_t                 TEI;
   Byte_t                 DLCI;
   Boolean_t              ParameterRequest;
   RFCOMM_RPN_Port_Data_t PortData;
} RFCOMM_Remote_Port_Negotiation_Data_t;

#define RFCOMM_REMOTE_PORT_NEGOTIATION_DATA_SIZE  (sizeof(RFCOMM_Remote_Port_Negotiation_Data_t))

   /* The following structure contains the line status information to be*/
   /* set for the local device.                                         */
typedef struct _tagRFCOMM_Remote_Line_Status_Data_t
{
   Word_t TEI;
   Byte_t DLCI;
   Byte_t LineStatus;
} RFCOMM_Remote_Line_Status_Data_t;

#define RFCOMM_REMOTE_LINE_STATUS_DATA_SIZE       (sizeof(RFCOMM_Remote_Line_Status_Data_t))

   /* The following structure contains the parameters that are required */
   /* to notify a user that a Line Status Confirmation has been         */
   /* received.                                                         */
typedef struct _tagRFCOMM_Remote_Line_Status_Confirmation_Data_t
{
   Word_t TEI;
   Byte_t DLCI;
} RFCOMM_Remote_Line_Status_Confirmation_Data_t;

#define RFCOMM_REMOTE_LINE_STATUS_CONFIRMATION_DATA_SIZE (sizeof(RFCOMM_Remote_Line_Status_Confirmation_Data_t))

   /* The following structure contains Modem Status information.  The   */
   /* value of the BreakLength is only meaningful when BreakSignal is   */
   /* set to TRUE.  Refer to the MODEM_STATUS Bit Masks for information */
   /* about the mapping of the modem status bits.                       */
typedef struct _tagRFCOMM_Modem_Status_t
{
   Byte_t    ModemStatus;
   Boolean_t BreakSignal;
   Byte_t    BreakLength;
} RFCOMM_Modem_Status_t;

#define RFCOMM_MODEM_STATUS_SIZE                        (sizeof(RFCOMM_Modem_Status_t))

   /* The Modem status byte is a packed Byte of Bits that provide       */
   /* specific status information.  These defines are provide to assist */
   /* in setting and decoding the status information.                   */
#define RFCOMM_MODEM_STATUS_FC_BIT_MASK                                   0x02
#define RFCOMM_MODEM_STATUS_RTC_BIT_MASK                                  0x04
#define RFCOMM_MODEM_STATUS_RTR_BIT_MASK                                  0x08
#define RFCOMM_MODEM_STATUS_IC_BIT_MASK                                   0x40
#define RFCOMM_MODEM_STATUS_DV_BIT_MASK                                   0x80
#define RFCOMM_MODEM_STATUS_BIT_MASK                                      0xCE

   /* The following structure contains Modem Status Event Indication    */
   /* Information.                                                      */
typedef struct _tagRFCOMM_Modem_Status_Data_t
{
   Word_t                TEI;
   Byte_t                DLCI;
   RFCOMM_Modem_Status_t ModemStatus;
} RFCOMM_Modem_Status_Data_t;

#define RFCOMM_MODEM_STATUS_DATA_SIZE             (sizeof(RFCOMM_Modem_Status_Data_t))

   /* The following structure contains the parameters that are required */
   /* to notify a user that a Modem Status Confirmation has been        */
   /* received.                                                         */
typedef struct _tagRFCOMM_Modem_Status_Confirmation_Data_t
{
   Word_t TEI;
   Byte_t DLCI;
} RFCOMM_Modem_Status_Confirmation_Data_t;

#define RFCOMM_MODEM_STATUS_CONFIRMATION_DATA_SIZE (sizeof(RFCOMM_Modem_Status_Confirmation_Data_t))

   /* The following structure contains length and sequence representing */
   /* a test message.  The length of the message should not exceed the  */
   /* maximum frame size negotiated for the DLCI on which the test      */
   /* message is sent.                                                  */
typedef struct _tagRFCOMM_Test_Data_t
{
   Word_t  TEI;
   Word_t  SequenceLength;
   Byte_t *Sequence;
} RFCOMM_Test_Data_t;

#define RFCOMM_TEST_DATA_SIZE                     (sizeof(RFCOMM_Test_Data_t))

   /* The following structure contains information about the remote     */
   /* entity's ability to receive data.  When ReceiverNotReady is TRUE, */
   /* no data is to be sent no the DLCI channel.                        */
typedef struct _tagRFCOMM_Flow_Data_t
{
   Word_t    TEI;
   Byte_t    DLCI;
   Boolean_t ReceiverReady;
} RFCOMM_Flow_Data_t;

#define RFCOMM_FLOW_DATA_SIZE                     (sizeof(RFCOMM_Flow_Data_t))

   /* The following structure contains the parameters that are required */
   /* to notify a user that a Flow Confirmation Request was sent has    */
   /* been received and processed successfully.                         */
typedef struct _tagRFCOMM_Flow_Confirmation_Data_t
{
   Word_t TEI;
} RFCOMM_Flow_Confirmation_Data_t;

#define RFCOMM_FLOW_CONFIRMATION_DATA_SIZE         (sizeof(RFCOMM_Flow_Confirmation_Data_t))

   /* The following structure is used to notify the upper layer of new  */
   /* Credits that have been received.                                  */
typedef struct _tagRFCOMM_Credit_Indication_Data_t
{
   Word_t  TEI;
   Byte_t  DLCI;
   Byte_t  NewCredits;
   DWord_t TotalCredits;
} RFCOMM_Credit_Indication_Data_t;

#define RFCOMM_CREDIT_INDICATION_DATA_SIZE        (sizeof(RFCOMM_Credit_Indication_Data_t))

   /* The following structure is used to identify an unknown command    */
   /* that was received.                                                */
typedef struct _tagRFCOMM_Non_Supported_Command_Data_t
{
   Word_t TEI;
   Byte_t DLCI;
   Byte_t UnsupportedCommand;
} RFCOMM_Non_Supported_Command_Data_t;

#define RFCOMM_NON_SUPPORTED_COMMAND_DATA_SIZE    (sizeof(RFCOMM_Non_Supported_Command_Data_t))

   /* The following structure is used to identify that RFCOMM has Data  */
   /* Buffers free for transmit.  Note that this event is ONLY          */
   /* dispatched when the caller issues the RFCOMM_Send_Data() function */
   /* and receives the BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE return      */
   /* value.  Seee RFCOMM_Send_Data() for more information.             */
typedef struct _tagRFCOMM_Transport_Buffer_Empty_Data_t
{
   Word_t TEI;
   Byte_t DLCI;
} RFCOMM_Transport_Buffer_Empty_Data_t;

#define RFCOMM_TRANSPORT_BUFFER_EMPTY_DATA_SIZE   (sizeof(RFCOMM_Transport_Buffer_Empty_Data_t))

   /* The following structure contains Information about known event    */
   /* that has occurred in an RFCOMM entity.  The information is passed */
   /* to a higher level for interpretation and processing.              */
typedef struct _tagRFCOMM_Event_Data_t
{
   RFCOMM_Event_Data_Type_t RFCOMM_Event_Data_Type;
   DWord_t                  Event_Data_Length;
   union
   {
      RFCOMM_Open_Indication_Data_t                 *RFCOMM_Open_Indication_Event_Data;
      RFCOMM_Open_Confirmation_Data_t               *RFCOMM_Open_Confirmation_Event_Data;
      RFCOMM_Release_Indication_Data_t              *RFCOMM_Release_Indication_Event_Data;
      RFCOMM_Data_Data_t                            *RFCOMM_Data_Indication_Event_Data;
      RFCOMM_Param_Negotiation_Data_t               *RFCOMM_Param_Negotiation_Indication_Event_Data;
      RFCOMM_Remote_Port_Negotiation_Data_t         *RFCOMM_Remote_Port_Negotiation_Indication_Event_Data;
      RFCOMM_Remote_Port_Negotiation_Data_t         *RFCOMM_Remote_Port_Negotiation_Confirmation_Event_Data;
      RFCOMM_Remote_Line_Status_Data_t              *RFCOMM_Remote_Line_Status_Indication_Event_Data;
      RFCOMM_Remote_Line_Status_Confirmation_Data_t *RFCOMM_Remote_Line_Status_Confirmation_Event_Data;
      RFCOMM_Modem_Status_Data_t                    *RFCOMM_Modem_Status_Indication_Event_Data;
      RFCOMM_Modem_Status_Confirmation_Data_t       *RFCOMM_Modem_Status_Confirmation_Event_Data;
      RFCOMM_Test_Data_t                            *RFCOMM_Test_Confirmation_Event_Data;
      RFCOMM_Flow_Data_t                            *RFCOMM_Flow_Indication_Event_Data;
      RFCOMM_Flow_Confirmation_Data_t               *RFCOMM_Flow_Confirmation_Event_Data;
      RFCOMM_Credit_Indication_Data_t               *RFCOMM_Credit_Indication_Event_Data;
      RFCOMM_Non_Supported_Command_Data_t           *RFCOMM_Non_Supported_Command_Data;
      RFCOMM_Transport_Buffer_Empty_Data_t          *RFCOMM_Transport_Buffer_Empty_Data;
   } RFCOMM_Event_Data;
} RFCOMM_Event_Data_t;

#define RFCOMM_EVENT_DATA_SIZE                          (sizeof(RFCOMM_Event_Data_t))

   /* The following declared type represents the Prototype Function for */
   /* an RFCOMM Event Callback.  This function will be called whenever a*/
   /* defined RFCOMM Action occurs within the Bluetooth Protocol Stack  */
   /* that is specified with the specified Bluetooth Stack ID.  This    */
   /* function passes to the caller the Bluetooth Stack ID, the RFCOMM  */
   /* Event Data associated with the RFCOMM Event that occurred, and the*/
   /* RFCOMM Callback Parameter that was specified when this Callback   */
   /* was installed.  The caller is free to use the contents of the     */
   /* RFCOMM Event Data ONLY in the context of this callback.  If the   */
   /* caller requires the Data for a longer period of time, then the    */
   /* callback function MUST copy the data into another Data Buffer.    */
   /* This function is guaranteed NOT to be invoked more than once      */
   /* simultaneously for the specified installed callback (i.e.  this   */
   /* function DOES NOT have be reentrant).  It Needs to be noted       */
   /* however, that if the same Callback is installed more than once,   */
   /* then the callbacks will be called serially.  Because of this, the */
   /* processing in this function should be as efficient as possible.   */
   /* It should also be noted that this function is called in the Thread*/
   /* Context of a Thread that the User does NOT own.  Therefore,       */
   /* processing in this function should be as efficient as possible    */
   /* (this argument holds anyway because another RFCOMM Event will not */
   /* be processed while this function call is outstanding).            */
   /* ** NOTE **  This function MUST NOT Block and wait for events that */
   /*             can only be satisfied by Receiving other Bluetooth    */
   /*             Stack Events.  A Deadlock WILL occur because other    */
   /*             Callbacks might not be issued while this function     */
   /*             is currently outstanding.                             */
typedef void (BTPSAPI *RFCOMM_Event_Callback_t)(unsigned int BluetoothStackID, RFCOMM_Event_Data_t *RFCOMM_Event_Data, unsigned long CallbackParameter);

   /* The following function is responsible for setting system wide     */
   /* parameters.  These parameters are used to control aspects of each */
   /* DLCI that are opened by the local or remote side.  When a Server  */
   /* is registered, the current System Params are used as the          */
   /* parameters that are to be negotiated for that server connection.  */
   /* This function takes as it parameters a Bluetooth Stack ID to      */
   /* identify the Bluetooth device that this command is associated     */
   /* with.  The SystemParams is a structure that contains the          */
   /* parameters are to be used when configuring the channel.  If the   */
   /* parameters were successfully saved by the RFCOMM provider, the    */
   /* function will return a zero value.  If an error occurs while      */
   /* submitting the parameters, a negative number will be returned that*/
   /* identifies the reason for the failure.                            */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Set_System_Parameters(unsigned int BluetoothStackID, RFCOMM_System_Parameters_t *SystemParams);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Set_System_Parameters_t)(unsigned int BluetoothStackID, RFCOMM_System_Parameters_t *SystemParams);
#endif

   /* The following function is responsible for getting system wide     */
   /* parameters.  These parameters are used to control aspects of each */
   /* DLCI that are opened by the remote side.  This function takes as  */
   /* it parameters a Bluetooth Stack ID to identify the Bluetooth      */
   /* device that this command is associated with.  The SystemParams is */
   /* a structure that will receive the parameters are to be used when  */
   /* configuring the channel.  If the parameters were successfully     */
   /* accessed, the function will return a zero value.  If an error     */
   /* occurs while retrieving the parameters, a negative number will be */
   /* returned that identifies the reason for the failure.              */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Get_System_Parameters(unsigned int BluetoothStackID, RFCOMM_System_Parameters_t *SystemParams);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Get_System_Parameters_t)(unsigned int BluetoothStackID, RFCOMM_System_Parameters_t *SystemParams);
#endif

   /* The following function is responsible for setting system wide     */
   /* queuing parameters.  These parameters are used to control aspects */
   /* of the number of data packets (and only data packets) that can be */
   /* queued into the lower level (per individual DLCI).  This mechanism*/
   /* allows for the flexibility to limit the amount of RAM that is used*/
   /* for streaming type applications (where the remote side has a large*/
   /* number of credits that were granted).  This function accepts as   */
   /* input the Bluetooth Stack ID of the Bluetooth stack in which to   */
   /* set the system wide queuing parameters, followed by the maximum   */
   /* number of queued data packets (per DLCI), followed by the low     */
   /* threshold (used be the lower layer to inform RFCOMM when it can   */
   /* send another data packet).  This function returns zero if         */
   /* successful or a negative return error code if there is an error.  */
   /* * NOTE * This function can only be called when there are NO active*/
   /*          connections.                                             */
   /* * NOTE * Setting both parameters to zero will disable the queuing */
   /*          mechanism.  This means that the amount of queued packets */
   /*          will only be limited via the amount of available RAM.    */
   /* * NOTE * RFCOMM_Send_Credits() is not considered a data packet in */
   /*          terms of queuing.  The only functions that count towards */
   /*          these values are:                                        */
   /*             - RFCOMM_Send_Data()                                  */
   /*             - RFCOMM_Send_Data_With_Credits()                     */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Set_Data_Queuing_Parameters(unsigned int BluetoothStackID, unsigned int MaximumNumberDataPackets, unsigned int QueuedDataPacketsThreshold);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Set_Data_Queuing_Parameters_t)(unsigned int BluetoothStackID, unsigned int MaximumNumberDataPackets, unsigned int QueuedDataPacketsThreshold);
#endif

   /* The following function is responsible for getting system wide     */
   /* queuing parameters.  These parameters are used to control aspects */
   /* of the number of data packets (and only data packets) that can be */
   /* queued into the lower level (per individual DLCI).  This mechanism*/
   /* allows for the flexibility to limit the amount of RAM that is used*/
   /* for streaming type applications (where the remote side has a large*/
   /* number of credits that were granted).  This function accepts as   */
   /* input the Bluetooth Stack ID of the Bluetooth stack in which to   */
   /* get the system wide queuing parameters, followed by a pointer to a*/
   /* variable that is to receive the maximum number of queued data     */
   /* packets (per DLCI), followed by the low threshold (used be the    */
   /* lower layer to inform RFCOMM when it can send another data        */
   /* packet).  This function returns zero if successful or a negative  */
   /* return error code if there is an error.                           */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Get_Data_Queuing_Parameters(unsigned int BluetoothStackID, unsigned int *MaximumNumberDataPackets, unsigned int *QueuedDataPacketsThreshold);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Get_Data_Queuing_Parameters_t)(unsigned int BluetoothStackID, unsigned int *MaximumNumberDataPackets, unsigned int *QueuedDataPacketsThreshold);
#endif

   /* The following function is responsible for Registering a server    */
   /* channel that the RFCOMM Layer is to provide services for.  After  */
   /* the channel is registered, all events that occur on the specified */
   /* channel will be dispatched to the upper layer via the Callback    */
   /* function provided.  The first parameter to this function specifies*/
   /* the Bluetooth Device that the RFCOMM Server Channel is to be      */
   /* registered with.  The ServerChannel parameter identifies the      */
   /* Channel number that this server supports.  The                    */
   /* RFCOMM_Event_Callback identifies the callback function that is to */
   /* be called when a events that reference this server channel are    */
   /* received.  The CallbackParameter is a user definable value.  When */
   /* the Callback is made with result information about the request,   */
   /* the CallbackParameter will be returned in the callback function.  */
   /* If the Server information is successfully registered, the function*/
   /* will return a positive, non-zero value that represents the server */
   /* ID that can be passed to the RFCOMM_Un_Register_Server_Channel()  */
   /* to un-register the server.  If an error occurs while registering  */
   /* the parameters, a negative vakue will be returned that identifies */
   /* the reason for the failure.                                       */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Register_Server_Channel(unsigned int BluetoothStackID, Byte_t ServerChannel, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Register_Server_Channel_t)(unsigned int BluetoothStackID, Byte_t ServerChannel, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for UnRegistering a server  */
   /* channel that the RFCOMM Layer provides services for.  Upon        */
   /* completion of this function, ALL access to this RFCOMM channel    */
   /* will fail.  The ServerID parameter specifies the server that is to*/
   /* be unregistered.  If the Server information is successfully       */
   /* unregistered, the function will return zero.  If an error occurs  */
   /* while unregistering the parameters, a negative number will be     */
   /* returned that identifies the reason for the failure.              */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Un_Register_Server_Channel(unsigned int BluetoothStackID, unsigned int ServerID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Un_Register_Server_Channel_t)(unsigned int BluetoothStackID, unsigned int ServerID);
#endif

   /* The following function is used to instanciate an RFCOMM service   */
   /* channel between the client application residing above this RFCOMM */
   /* layer and a destination endpoint (server) that resides on the     */
   /* device associated with the Bluetooth BD_ADDR supplied.  Only One  */
   /* L2CAP/ACL connection can exist between 2 RFCOMM entities, so this */
   /* function will first check to see if an RFCOMM connection already  */
   /* exists between the 2 devices.  If a connection already exists,    */
   /* then a new channel will be negotiated between the two devices over*/
   /* an existing L2CAP connection.  If a connection does not exist,    */
   /* this function will initiate a L2CAP connection between the two    */
   /* devices on which the RFCOMM channel will be created in the future.*/
   /* The function takes as its arguments the BluetoothStackID on which */
   /* the connection should be associated, the BD_ADDR of the device to */
   /* which the connection should be made, the Server Channel to open on*/
   /* the remote RFCOMM entity, a pointer to the Callback function that */
   /* is to handle all of the events that occur in the channel, and a   */
   /* Callback Parameter that the will be returned as a parameter to the*/
   /* Callback function.  The user is free to use this parameter as     */
   /* needed.  A negative return value indicates that the attempt to    */
   /* open the specified channel was not successful.  If a connection   */
   /* request was successfully initiated the TEI (Terminal Endpoint     */
   /* Identifier) and DLCI values are returned and must be supplied in  */
   /* future call to functions that are to operate on the connection.   */
   /* If this function successfully submits the RFCOMM Open Request then*/
   /* this function will return zero and the success or failure of the  */
   /* connection will be indicated via a future                         */
   /* etDLCEstablishmentConfirmation event.                             */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Open_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Channel, Word_t *TEI, Byte_t *DLCI, RFCOMM_Open_Parameters_t *OpenParams, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Open_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Channel, Word_t *TEI, Byte_t *DLCI, RFCOMM_Open_Parameters_t *OpenParams, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is provided to allow a method for a server */
   /* to accept or reject a connection request.  When a connection is   */
   /* being established to a server, an etOpen_Indication is dispatched */
   /* to the upper layer.  The upper layer should examine the parameters*/
   /* that are being requested and supply an Accept or Reject for the   */
   /* connection via this function.  This function takes as its         */
   /* parameters a Bluetooth Stack ID, the TEI and DLCI that identifies */
   /* the connection to which the response is associated, and a BOOLEAN */
   /* value indicating the acceptance (TRUE) or rejection (FALSE) of the*/
   /* connection.  This function will return zero if the response was   */
   /* successfully submitted to the lower layers of the stack.  This    */
   /* does not indicate that the command has been successfully executed */
   /* and received to the remote device.  If the stack failed to submit */
   /* the response to the lower layers, a negative value is returned    */
   /* indicating the reason the failure occurred.  Upon receiving a     */
   /* successful result from this function the user can consider the    */
   /* port to be in an Open State.                                      */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Open_Response(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t Accept);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Open_Response_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t Accept);
#endif

   /* The following function is used to disconnect an RFCOMM channel    */
   /* that is currently open or in the process of being opened.  This   */
   /* function takes as it parameters a Bluetooth Stack ID to identify  */
   /* the Bluetooth device that this command is associated with and the */
   /* TEI and DLCI (to identify the channel that is to be disconnected).*/
   /* If the request was successfully submitted to the lower layers, the*/
   /* function will return zero.  If an error occurs while submitting   */
   /* the request to the lower layers, a negative number will be        */
   /* returned that identifies the reason for the failure.  Upon the    */
   /* release of the channel, a Release Indication will be issued via   */
   /* the callback.                                                     */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Release_Request(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Release_Request_t)(unsigned int BluetoothStackID,  Word_t TEI, Byte_t DLCI);
#endif

   /* The following function is used to send credits to an RFCOMM       */
   /* channel that is currently open.  This function takes as its       */
   /* parameters a Bluetooth Stack ID to identify the Bluetooth device  */
   /* that this command is associated with, the TEI and DLCI (to        */
   /* identify the channel to which the Credits are to be sent), and the*/
   /* number of Credits that are to be granted to the receiver.  The    */
   /* number of credits that are received by the receiver will be added */
   /* the number of credits that are already available to the receiver. */
   /* If the request was successfully submitted to the lower layer for  */
   /* delivery zero is returned.  If an error occurred while submitting */
   /* the Credits, a negative value is returned that identifies the     */
   /* reason for the failure.  It must be noted that this function is   */
   /* only available for those channels that have been configured to use*/
   /* Credit Based Flow control.                                        */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing Data Queue.  The caller    */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etTransport_Buffer_Empty_Indication                   */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Send_Credits(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t Credits);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Send_Credits_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t Credits);
#endif

   /* The following function is used to send data to a specific RFCOMM  */
   /* channel that is currently open.  This function takes as its       */
   /* parameters a Bluetooth Stack ID (to identify the Bluetooth device */
   /* that this command is associated with), the TEI and DLCI (to       */
   /* identify the channel to which the data is to be sent), the Length */
   /* of Data to send (in Bytes), and a pointer to the Data Buffer to   */
   /* send.  The Data parameter is a pointer to an array of bytes to be */
   /* sent over the channel.  The channel must be in a connected state  */
   /* and have the proper flow control requirements met before a        */
   /* successful data transfer can be expected.  If the request is      */
   /* successfully submitted to the lower layer, the return value will  */
   /* be zero.  If an error occurs while submitting the request to      */
   /* transfer the data, a negative value is returned identifying the   */
   /* reason for the failure.                                           */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing Data Queue.  The caller    */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etTransport_Buffer_Empty_Indication                   */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Send_Data(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Word_t Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Send_Data_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Word_t Length, Byte_t *Data);
#endif

   /* The following function is used to send data (and the specified    */
   /* Credits are included within the header of the RFCOMM Data) to a to*/
   /* a specific RFCOMM channel that is currently open.  This function  */
   /* takes as its parameters a Bluetooth Stack ID (to identify the     */
   /* Bluetooth device that this command is associated with), the TEI   */
   /* and DLCI (to identify the channel to which the data is to be      */
   /* sent), the number of Credits that are to be sent, the Length of   */
   /* Data to send (in Bytes), and a pointer to the Data Buffer to send.*/
   /* The Data parameter is a pointer to an array of bytes to be sent   */
   /* over the channel.  The channel must be in a connected state and   */
   /* have the proper flow control requirements met before a successful */
   /* data transfer can be expected.  If the request is successfully    */
   /* submitted to the lower layer, the return value will be zero.  If  */
   /* an error occurs while submitting the request to transfer the data,*/
   /* a negative value is returned identifying the reason for the       */
   /* failure.                                                          */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing Data Queue.  The caller    */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etTransport_Buffer_Empty_Indication                   */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Send_Data_With_Credits(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t Credits, Word_t Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Send_Data_With_Credits_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t Credits, Word_t Length, Byte_t *Data);
#endif

   /* The following function is used to send a Response to a Parameter  */
   /* Negotiation request.  A parameter negotiation request, stated in  */
   /* the specification, can be received at any time.  However, if a    */
   /* request is received after a channel is open, then the             */
   /* re-negotiation of the parameters that were accepted at the time   */
   /* the channel was opened, is optional.  The first parameter to this */
   /* function is the Bluetooth Stack ID which identifies the Bluetooth */
   /* device that this command is associated with.  The next two        */
   /* parameters, TEI and DLCI, identify the channel to which the       */
   /* parameters are associated with.  The final parameter,             */
   /* ParamNegotiationData is a structure of type RFCOMM_PN_Data_t that */
   /* identifies each parameter that is be negotiated.  The values      */
   /* received in the etDLCI_Param_Negotiation_Indication event should  */
   /* be examined and if they are acceptable, the response should return*/
   /* these values to the caller.  If any parameter is not acceptable,  */
   /* the parameter should be changed to a value that is acceptable and */
   /* returned to the caller.  If the response is successfully submitted*/
   /* to the lower layers of the stack, the function will return zero.  */
   /* If an error occurs while submitting the response, a negative value*/
   /* is returned identifying the reason for the failure.               */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Parameter_Negotiation_Response(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_PN_Data_t *ParamNegotiationData);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *RFCOMM_Parameter_Negotiation_Response_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_PN_Data_t *ParamNegotiationData);
#endif

   /* The following function is used to send test data to RFCOMM        */
   /* Multiplexor channel.  This function has no purpose but to test to */
   /* see if a remote end is responsive.  The remote RFCOMM multiplexor */
   /* will echo all data contained if the request back to the caller.   */
   /* The initiator will receive the data back via future               */
   /* etTest_Confirmation event.  This function takes as its first      */
   /* parameter the Bluetooth Stack ID to identify the Bluetooth device */
   /* that this command is associated with.  The second parameter (TEI) */
   /* identifies the RFCOMM Multiplexor to which the test information is*/
   /* to be directed.  The Length parameter identifies the number of    */
   /* Bytes that are to be transferred in the request.  The Data        */
   /* parameter is a pointer to an array of bytes that are to be sent   */
   /* with the request.  The RFCOMM_Event_Callback parameter identifies */
   /* the callback function that is to be called when a response to the */
   /* Test Message is received or a timeout waiting for a response      */
   /* occurs.  The CallbackParameter is a user definable value.  When   */
   /* the Callback is made with result information about the request,   */
   /* the CallbackParameter will be returned in the callback function.  */
   /* If the request is successfully submitted to the lower layers of   */
   /* the stack, the function will return zero.  If an error occurs     */
   /* during the submitting of the request, a negative value is returned*/
   /* that identifies the reason for the failure.                       */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Test_Request(unsigned int BluetoothStackID, Word_t TEI, Word_t Length, Byte_t *Data, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Test_Request_t)(unsigned int BluetoothStackID, Word_t TEI, Word_t Length, Byte_t *Data, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is used to control the flow of incoming    */
   /* data on an aggregate basis.  The function requires a callback in  */
   /* order to receive confirmation that the state has changed.  In this*/
   /* implementation, no data buffers reside in RFCOMM, so a request to */
   /* halt the flow of data is sent to the remote entity.  A            */
   /* confirmation must be received before the new state will become in */
   /* effect.  Data Flow is enabled or disabled via the State parameter.*/
   /* If the state is TRUE then data is allowed to flow between RFCOMM  */
   /* entities.  This first parameter to this function is the Bluetooth */
   /* Stack ID that identifies the Bluetooth device that this command is*/
   /* associated with.  The second parameter is the TEI (RFCOMM         */
   /* Multiplexor) that is being requested to halt all flow.  It should */
   /* be noted that since the Multiplexor is being halted, all DLCIs    */
   /* associated with that Multiplexor will be halted with the exception*/
   /* of the Multiplexor Control channel (DLCI 0) on which the RFCOMM   */
   /* entities communicate.  The Receiver Ready parameter is used to    */
   /* identify the ability to transfer data between RFCOMM entities.    */
   /* When this value is TRUE, flow between the 2 entities is enabled.  */
   /* RFCOMM_Event_Callback identifies the callback function that is to */
   /* be called when a response to the Flow Request is received or a    */
   /* timeout waiting for a response occurs.  The CallbackParameter is a*/
   /* user definable value.  When the Callback is made with result      */
   /* information about the request, the CallbackParameter will be      */
   /* returned in the callback function.  This function returns zero if */
   /* successful, or a negative return error code if the request was    */
   /* not submitted successfully.                                       */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Flow_Request(unsigned int BluetoothStackID, Word_t TEI, Boolean_t ReceiverReady, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Flow_Request_t)(unsigned int BluetoothStackID, Word_t TEI, Boolean_t ReceiverReady, RFCOMM_Event_Callback_t RFCOMM_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is used to convey modem status information */
   /* between the RFCOMM entities.  RFCOMM transparently passes the     */
   /* status information to the other entity and supplies the response  */
   /* for the command.  RFCOMM will inspect the FC (Flow Control) bit of*/
   /* the Modem Status Byte and set the Flow State of the DLCI receiving*/
   /* the status information to the state reflected in the FC bit.  This*/
   /* function operates on user DLCI's and can not be directed to the   */
   /* Control channel (DLCI 0).  Confirmation of the delivery of the    */
   /* Modem status information will be provided via the Callback        */
   /* function that is assigned to the DLCI for which the status        */
   /* applies.  This function takes as its first parameter the Bluetooth*/
   /* Stack ID to identify the Bluetooth device that this command is    */
   /* associated with.  The next two parameters, TEI and DLCI, are used */
   /* to identify the channel where the Status information is directed. */
   /* The ModemStatus parameter is a structure that contains the status */
   /* information being sent to the remote entity.  If the request is   */
   /* successfully submitted to the RFCOMM transport layer, this        */
   /* function will return zero.  If an error occurs during the         */
   /* submitting of the request, a negative value is returned that      */
   /* identifies the reason for the failure.                            */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Modem_Status(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_Modem_Status_t *ModemStatus);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Modem_Status_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_Modem_Status_t *ModemStatus);
#endif

   /* The following function is used to convey line status change       */
   /* information between the RFCOMM channels.  RFCOMM transparently    */
   /* passes the status information to the other entity and supplies a  */
   /* response for the message.  RFCOMM does not inspect any bits of the*/
   /* Line Status information, but rather passes the information to the */
   /* upper layer for processing.  This function operates on user DLCI  */
   /* and can not be directed to the Control channel (DLCI 0).          */
   /* Confirmation of the delivery of the line status information will  */
   /* be provided via the Callback function that is assigned to the DLCI*/
   /* for which the status applies.  This function takes as it          */
   /* parameters a Bluetooth Stack ID to identify the Bluetooth device  */
   /* that this command is associated with.  The TEI and DLCI identify  */
   /* the channel to which the status information applies.  The         */
   /* LineStatus parameter is a structure that contains the status      */
   /* information that is to be sent.  If the status information is     */
   /* successfully submitted for transport, this function will return a */
   /* Zero value.  If an error occurs during the submitting of the      */
   /* request, a negative value is returned that identifies the reason  */
   /* for the failure.                                                  */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Line_Status_Change(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t LineStatus);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Line_Status_Change_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, Byte_t LineStatus);
#endif

   /* The following function is used to perform a Remote Port           */
   /* Negotiation.  The Remote Port Negotiation command is used to      */
   /* exchange/retrieve port configuration usage information that may be*/
   /* useful to the upper layers.  The command specified the Baud Rate, */
   /* software Flow Control information, etc.  The usage of this command*/
   /* is optional.  This function takes as it parameters a Bluetooth    */
   /* Stack ID to identify the Bluetooth device that this command is    */
   /* associated with.  The TEI and DLCI identify the channel to which  */
   /* the request information applies.  The PortData parameter is a     */
   /* structure that contains the information that is to be negotiated. */
   /* If the information is successfully submitted for transport, this  */
   /* function will return a Zero value.  If an error occurs during the */
   /* submitting of the request, a negative value is returned that      */
   /* identified the reason for the failure.  A response to the request */
   /* will be received via a etRemote_Port_Negotiation_Confirmation     */
   /* event.                                                            */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Remote_Port_Negotiation_Request(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_RPN_Port_Data_t *PortData);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Remote_Port_Negotiation_Request_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_RPN_Port_Data_t *PortData);
#endif

   /* The following function is used to respond to a Remote Port        */
   /* Negotiation Request.  The Remote Port Negotiation command is used */
   /* to exchange/retrieve port configuration usage information that may*/
   /* be useful to the upper layers.  This command specifies the Baud   */
   /* Rate, software Flow Control information, etc.  The usage of this  */
   /* command is mandatory if a Remote Port Negotiation Parameter       */
   /* Indication is received.  This function takes as its first         */
   /* parameter the Bluetooth Stack ID to identify the Bluetooth device */
   /* that this command is associated with.  The next two parameters    */
   /* (TEI and DLCI) identify the channel to which the request          */
   /* information applies.  The PortData parameter is a structure that  */
   /* contains the information that is to being negotiated.  If the     */
   /* information is successfully submitted to the transport layer, this*/
   /* function will return zero.  If an error occurs during the         */
   /* submitting of the response, a negative value is returned that     */
   /* identifies the reason for the failure.                            */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Remote_Port_Negotiation_Response(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_RPN_Port_Data_t *PortData);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Remote_Port_Negotiation_Response_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI, RFCOMM_RPN_Port_Data_t *PortData);
#endif

   /* The following function is used to Query the Remote Sides' Remote  */
   /* Port Negotiation Parameters.  The Remote Port Negotiation command */
   /* is used to exchange/retrieve port configuration usage information */
   /* that may be useful to the upper layers.  This command specifies   */
   /* the Baud Rate, software Flow Control information, etc.  The usage */
   /* of this command is optional.  This function takes as it parameters*/
   /* the Bluetooth Stack ID (to identify the Bluetooth device that this*/
   /* command is associated with) and the TEI and DLCI (which identifies*/
   /* the channel to which the request applies).  If the request is     */
   /* successfully submitted to the transport layer, this function will */
   /* return a zero.  If an error occurs during the submitting of the   */
   /* request, a negative value is returned that identifies the reason  */
   /* for the failure.                                                  */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Query_Remote_Port_Negotiation(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Query_Remote_Port_Negotiation_t)(unsigned int BluetoothStackID, Word_t TEI, Byte_t DLCI);
#endif

   /* The following function is a utility function that exists to allow */
   /* a mechanism to determine the current TEI and/or DLCI state for a  */
   /* specific Bluetooth RFCOMM Connection.  This function accepts as   */
   /* input the Bluetooth Stack of the Bluetooth stack that the query is*/
   /* valid, followed by the Bluetooth Device Address of the Connection */
   /* in question, followed by the Channel to query the status of,      */
   /* followed by a flag that specifies whether the Channel in question */
   /* (if not the Control Channel) is a Server (TRUE) or a Client       */
   /* (FALSE) Channel, followed by a pointer to the variable that is to */
   /* receive the status.  This function returns zero if successful, or */
   /* a negative return error code if there was an error.               */
   /* * NOTE * This function will only supply a value in the RFCOMM     */
   /*          Status parameter if the return value from this function  */
   /*          is success (0).  If this function returns an error, then */
   /*          the contents of this variable will be undefined.         */
   /* * NOTE * The Bluetooth Address is a required parameter and is     */
   /*          used to determine the TEI of the RFCOMM Connection.      */
   /* * NOTE * The Channel parameter must be one of the following:      */
   /*             - 0 (queries the status of the Control Channel)       */
   /*             - RFCOMM_MINIMUM_SERVER_CHANNEL_ID                    */
   /*             - RFCOMM_MAXIMUM_SERVER_CHANNEL_ID                    */
   /*          Note that the above values are NOT the DLCI values, but  */
   /*          rather the actual RFCOMM Channel Numbers !!!!!!!!!!!!!!! */
   /* * NOTE * This is a very low level function and exists solely to   */
   /*          allow a mechanism to determine the current Control       */
   /*          Message State for a specified TEI and/or DLCI.  This     */
   /*          is needed in some circumstances when trying to connect or*/
   /*          disconnect RFCOMM Channels and the user has no way of    */
   /*          knowing the current Status (keep in mind that there can  */
   /*          only be a single Control Message outstanding on any      */
   /*          given RFCOMM Channel).                                   */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Get_Channel_Status(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Channel, Boolean_t ServerChannel, RFCOMM_Channel_Status_t *RFCOMM_Channel_Status);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Get_Channel_Status_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Channel, Boolean_t ServerChannel, RFCOMM_Channel_Status_t *RFCOMM_Channel_Status);
#endif

   /* The following function is provided to allow a mechanism to        */
   /* determine if the specified Server Channel is present on the       */
   /* system.  This allows application developers a means to determine  */
   /* if there are free/active RFCOMM servers on specific RFCOMM ports. */
   /* This function accepts the Bluetooth Stack ID, followed by the     */
   /* RFCOMM Channel number to query.  The final parameters is a pointer*/
   /* to a variable that will hold the value (on success) for the server*/
   /* being present.  This value will be BOOLEAN TRUE if a server is    */
   /* registered with the system, or FALSE if there is not a server     */
   /* registered with the system.  This function returns zero if        */
   /* successful, or a negative return error code if there was an error.*/
   /* * NOTE * The Channel parameter must be one of the following:      */
   /*             - RFCOMM_MINIMUM_SERVER_CHANNEL_ID                    */
   /*             - RFCOMM_MAXIMUM_SERVER_CHANNEL_ID                    */
   /*          Note that the above values are NOT the DLCI values, but  */
   /*          rather the actual RFCOMM Channel Numbers !!!!!!!!!!!!!!! */
BTPSAPI_DECLARATION int BTPSAPI RFCOMM_Query_Server_Channel_Present(unsigned int BluetoothStackID, Byte_t Channel, Boolean_t *ServerChannelPresent);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_RFCOMM_Query_Server_Channel_Present_t)(unsigned int BluetoothStackID, Byte_t Channel, Boolean_t *ServerChannelPresent);
#endif

#endif
