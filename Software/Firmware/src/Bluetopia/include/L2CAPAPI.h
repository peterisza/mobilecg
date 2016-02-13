/*****< l2capapi.h >***********************************************************/
/*      Copyright 2000 - 2014 Stonestreet One.                                */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  L2CAPAPI - Stonestreet One Bluetooth Stack L2CAP API Type Definitions,    */
/*             Constants, and Prototypes.                                     */
/*                                                                            */
/*  Author:  Tim Thomas                                                       */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   09/11/00  T. Thomas      Initial creation.                               */
/*   09/18/08  T. Thomas      Updates for BT 2.1                              */
/******************************************************************************/
#ifndef __L2CAPAPIH__
#define __L2CAPAPIH__

#include "BTPSKRNL.h"           /* BTPS Kernel Prototypes/Constants.          */

#include "BTAPITyp.h"           /* Bluetooth API Type Definitions.            */
#include "L2CAPTyp.h"           /* Bluetooth L2CAP Type Definitions/Constants.*/

#include "BTPSCFG.h"            /* BTPS Configuration Constants.              */

#define L2CAP_MAXIMUM_SUPPORTED_STACK_MTU                          (BTPS_CONFIGURATION_L2CAP_MAXIMUM_SUPPORTED_STACK_MTU)

   /* The following defines the amount of time in seconds that an L2CAP */
   /* signaling request can go unacknowledged before some action is     */
   /* taken.                                                            */
#define L2CAP_RTX_TIMER_MINIMUM_VALUE                               1
#define L2CAP_RTX_TIMER_MAXIMUM_VALUE                              60
#define L2CAP_RTX_TIMER_DEFAULT_VALUE                              (BTPS_CONFIGURATION_L2CAP_DEFAULT_RTX_TIMER_TIMEOUT_S)

   /* The following defines the amount of time in seconds that a Pending*/
   /* L2CAP signaling request can go unacknowledged before some action  */
   /* is taken.                                                         */
#define L2CAP_ERTX_TIMER_MINIMUM_VALUE                             60
#define L2CAP_ERTX_TIMER_MAXIMUM_VALUE                            300
#define L2CAP_ERTX_TIMER_DEFAULT_VALUE                             (BTPS_CONFIGURATION_L2CAP_DEFAULT_ERTX_TIMER_TIMEOUT_S)

   /* The following defines the amount of time in seconds that a        */
   /* connection is maintained with no active logical channels before   */
   /* the connection is removed.                                        */
#define L2CAP_IDLE_TIMER_MINIMUM_VALUE                              0
#define L2CAP_IDLE_TIMER_MAXIMUM_VALUE                             30
#define L2CAP_IDLE_TIMER_DEFAULT_VALUE                             (BTPS_CONFIGURATION_L2CAP_DEFAULT_IDLE_TIMER_TIMEOUT_S)

   /* The following defines then amount of time in seconds that a       */
   /* connection is allowed to be in the Config State.  If the CID can  */
   /* not be negotiated in this amount of time, the channel is          */
   /* disconnected.                                                     */
#define L2CAP_CONFIG_TIMER_MINIMUM_VALUE                            1
#define L2CAP_CONFIG_TIMER_MAXIMUM_VALUE                          120
#define L2CAP_CONFIG_TIMER_DEFAULT_VALUE                           (BTPS_CONFIGURATION_L2CAP_DEFAULT_CONFIG_TIMER_TIMEOUT_S)

   /* The following defines the amount of time in seconds that a        */
   /* multi-segmented L2CAP packet segment may be outstanding on the    */
   /* receive end.  If the next segment is not received in the amount of*/
   /* time specified, the partial received message will be discarded.   */
#define L2CAP_RECEIVE_TIMER_MINIMUM_VALUE                           1
#define L2CAP_RECEIVE_TIMER_MAXIMUM_VALUE                          60
#define L2CAP_RECEIVE_TIMER_DEFAULT_VALUE                          (BTPS_CONFIGURATION_L2CAP_DEFAULT_RECEIVE_TIMER_TIMEOUT_S)

   /* The following define declare the Bit Masks that are to be used    */
   /* with the Option_Flags field of the Config Request Structure .     */
#define L2CA_CONFIG_OPTION_FLAG_MTU                                (0x0001 <<  0)
#define L2CA_CONFIG_OPTION_FLAG_FLUSH_TIMEOUT                      (0x0001 <<  1)
#define L2CA_CONFIG_OPTION_FLAG_QOS                                (0x0001 <<  2)
#define L2CA_CONFIG_OPTION_FLAG_MODE_INFO                          (0x0001 <<  3)
#define L2CA_CONFIG_OPTION_FLAG_FCS_OPTION                         (0x0001 <<  4)
#define L2CA_CONFIG_OPTION_FLAG_EXTENDED_FLOW_SPEC                 (0x0001 <<  5)
#define L2CA_CONFIG_OPTION_FLAG_EXTENDED_WINDOW_SIZE               (0x0001 <<  6)
#define L2CA_CONFIG_OPTION_FLAG_CONTINUATION                       (0x0001 << 15)

#define L2CA_CONFIG_SUPPORTED_OPTIONS                              (L2CA_CONFIG_OPTION_FLAG_MTU | L2CA_CONFIG_OPTION_FLAG_FLUSH_TIMEOUT | L2CA_CONFIG_OPTION_FLAG_QOS | L2CA_CONFIG_OPTION_FLAG_MODE_INFO | L2CA_CONFIG_OPTION_FLAG_FCS_OPTION)

   /* The following Type Declaration defines the L2CA Event Callback    */
   /* Data Types.  These types are used with the L2CA_Event_Data_t      */
   /* structure to determine the type of Data the L2CAP Event Callback  */
   /* structure contains.                                               */
typedef enum
{
   etConnect_Indication,
   etConnect_Confirmation,
   etConfig_Indication,
   etConfig_Confirmation,
   etDisconnect_Indication,
   etDisconnect_Confirmation,
   etTimeout_Indication,
   etEcho_Confirmation,
   etInformation_Confirmation,
   etData_Indication,
   etData_Error_Indication,
   etGroup_Data_Indication,
   etGroup_Member_Status,
   etChannel_Buffer_Empty_Indication,
   etConnection_Parameter_Update_Indication,
   etConnection_Parameter_Update_Confirmation,
   etFixed_Channel_Connect_Indication,
   etFixed_Channel_Disconnect_Indication,
   etFixed_Channel_Data_Indication,
   etFixed_Channel_Buffer_Empty_Indication
} L2CA_Event_Type_t;

   /* The following structure represents the structure of the L2CAP     */
   /* Timers that user to control timeouts in the L2CAP layer.  This    */
   /* structure is used when a L2CA_Set_Timer_Values of                 */
   /* L2CA_Get_Timer_Values function is called.  The timers that are    */
   /* provided in this structure can be adjusted to provide appropriate */
   /* timing for the profile being implemented.  The timer values are   */
   /* specified in seconds.  Timers RTXTimerVal and ERTXTimerVal are    */
   /* defined in the L2CAP specifications.  Refer to the specification  */
   /* for information on these timers.  The IdleTimerVal is added to    */
   /* support the idea of Client and Server L2CAP connections.  L2CAP   */
   /* connections are established by Clients to Servers.  At the time   */
   /* that the ACL connection is to be terminated, the Client should be */
   /* the one to initiate the disconnection of the ACL link.  When an   */
   /* L2CAP server denotes that no CIDs are open on an ACL link, a timer*/
   /* of value IdleTimerVal is started to allow the Client time to      */
   /* disconnect the ACL link.  If the Client fails to disconnect the   */
   /* ACL link that the expiration of this timer, the server will then  */
   /* perform the disconnection.  If this timer is set to a value of    */
   /* Zero, then the Server will attempt to disconnect the ACL when the */
   /* last L2CAP channel is released.  The ConfigStateTimerVal is used  */
   /* to control the amount of time that the stack is allowed to be in  */
   /* the Config State.  If the configuration process is not complete at*/
   /* the expiration of this timer, the connection will be terminated.  */
   /* The ReceiveSegmentTimerVal is used to control the time that the   */
   /* stack will wait for the next segmented data packet to arrive.  If */
   /* the stack is waiting on a continuation information during the     */
   /* recombination of packets at the time this timer expires, the      */
   /* collected data will be discarded and an Error Event will be       */
   /* issues.  Refer to the defined constants for each timer for the    */
   /* range of values that each timer may be set.                       */
typedef struct _tagL2CA_Timer_Values_t
{
   unsigned int RTXTimerVal;
   unsigned int ERTXTimerVal;
   unsigned int IdleTimerVal;
   unsigned int ConfigStateTimerVal;
   unsigned int ReceiveSegmentTimerVal;
} L2CA_Timer_Values_t;

#define L2CA_TIMER_VALUES_SIZE                          (sizeof(L2CA_Timer_Values_t))

   /* The following enumerated type is used with the                    */
   /* L2CA_Get_Link_Connection_Configuration() and the                  */
   /* L2CA_Set_Link_Connection_Configuration() functions.  These types  */
   /* dictate how L2CAP will Issue Connection Requests and Respond to   */
   /* Connection Requests.  This functionality is NOT provided as part  */
   /* of L2CAP in the specification and exists to allow Role Switching  */
   /* to take place at the HCI Layer when L2CAP is controlling the HCI  */
   /* Connection Establishment (which is the default).                  */
   /* The Connect Request Configuration Types control how L2CAP will    */
   /* handle the Allow Role Switch parameter for the HCI Connection     */
   /* when L2CAP physically issues the HCI_Connect_Request() function.  */
   /* The Connect Response Configuration Types control how L2CAP will   */
   /* handle responding to an HCI_Connect_Request_Event.  The Ignore    */
   /* Request Response type should ONLY be used when some other entity  */
   /* is watching Connection Requests and controlling them (some form   */
   /* of connection manager).  In almost ALL circumstances, L2CAP can   */
   /* handle all HCI ACL Connection Requests/Responses so it is not     */
   /* envisioned that the Ignore Request will be used in practice.      */
   /* * NOTE * All of the Connect Request/Response parameters below     */
   /*          ONLY Apply to lower level HCI Role Switching parameters. */
   /*          These parameters are only needed in circumstances where  */
   /*          the programmer needs Point to Multi-Point capability     */
   /*          (either client or server).  The defaults for L2CAP are   */
   /*          given by the constants:                                  */
   /*             - L2CAP_DEFAULT_LINK_CONNECT_REQUEST_CONFIG           */
   /*             - L2CAP_DEFAULT_LINK_CONNECT_RESPONSE_CONFIG          */
   /*                                                                   */
typedef enum
{
   cqNoRoleSwitch,
   cqAllowRoleSwitch
} L2CA_Link_Connect_Request_Config_t;

typedef enum
{
   csMaintainCurrentRole,
   csRequestRoleSwitch,
   csIgnoreConnectionRequest
} L2CA_Link_Connect_Response_Config_t;

   /* The following structure represents the structure of the L2CAP     */
   /* Connection Configuration Parameters.  This structure is used with */
   /* the L2CA_Get_Link_Connection_Configuration() and the              */
   /* L2CA_Set_Link_Connection_Configuration() functions.               */
typedef struct _tagL2CA_Link_Connect_Params_t
{
   L2CA_Link_Connect_Request_Config_t  L2CA_Link_Connect_Request_Config;
   L2CA_Link_Connect_Response_Config_t L2CA_Link_Connect_Response_Config;
} L2CA_Link_Connect_Params_t;

#define L2CA_LINK_CONNECT_PARAMS_SIZE                   (sizeof(L2CA_Link_Connect_Params_t))

   /* The following constants represent the default Link Connect        */
   /* Parameters that is used by L2CAP.                                 */
#define L2CAP_DEFAULT_LINK_CONNECT_REQUEST_CONFIG       (BTPS_CONFIGURATION_L2CAP_DEFAULT_LINK_CONNECT_REQUEST_CONFIG)
#define L2CAP_DEFAULT_LINK_CONNECT_RESPONSE_CONFIG      (BTPS_CONFIGURATION_L2CAP_DEFAULT_LINK_CONNECT_RESPONSE_CONFIG)

   /* The following structure and these flags are used to control that  */
   /* handling of data packets at the L2CAP Layer.  The Flags parameter */
   /* specifies options that can be used when sending data.  The        */
   /* QueueLimit value indicates the upper limit at which the channel is*/
   /* considered full.  The LowThreshold is the limit at which the      */
   /* channel is unlocked and data can once again be sent on the        */
   /* channel.  The units of QueueLimit and LowThreshold will depend on */
   /* the Flags that are set in the Flags parameter.  If                */
   /* L2CA_QUEUEING_FLAG_LIMIT_BY_PACKETS is indicated, then the units  */
   /* are in Packets.  If L2CA_QUEUEING_FLAG_LIMIT_BY_SIZE is indicated */
   /* then the units are in Bytes.                                      */
   /* * NOTE * The L2CA_QUEUEING_FLAG_DISCARD_OLDEST Flag is only valid */
   /*          when L2CA_QUEUEING_FLAG_LIMIT_BY_PACKETS is indicated.   */
typedef struct _tagL2CA_Queueing_Parameters_t
{
   DWord_t Flags;
   DWord_t QueueLimit;
   DWord_t LowThreshold;
} L2CA_Queueing_Parameters_t;

#define L2CA_QUEUEING_PARAMETERS_SIZE                    (sizeof(L2CA_Queueing_Parameters_t))

   /* The following defines the Bit Flags that are used with the Flags  */
   /* parameter of the L2CA_Queueing_Parmeters_t structure.             */
   /* * NOTE * L2CA_QUEUEING_FLAG_LIMIT_BY_SIZE is no longer supported  */
   /*          but is left here for backwards compatibility.            */
#define L2CA_QUEUEING_FLAG_LIMIT_BY_PACKETS              0x00000000L
#define L2CA_QUEUEING_FLAG_LIMIT_BY_SIZE                 0x00000001L
#define L2CA_QUEUEING_FLAG_DISCARD_OLDEST                0x00000002L

   /* The following structure is used with the                          */
   /* L2CA_Get_Channel_Queue_Threshold() and the                        */
   /* L2CA_Set_Channel_Queue_Threshold() functions to change the L2CAP  */
   /* Channel Queue Thresholds.  These functions allow the caller a     */
   /* mechanism to artificially limit the amount of data that L2CAP     */
   /* will buffer internally (per L2CAP Channel).  This mechanism can   */
   /* be used to instruct L2CAP to return a Memory Allocation Error     */
   /* when the specified Threshold is reached (as opposed to only       */
   /* returning the Memory Allocation Error when all the memory is      */
   /* exhausted).  See the L2CA_Get_Channel_Queue_Threshold() and the   */
   /* L2CA_Set_Channel_Queue_Threshold() functions for more information.*/
   /* * NOTE * This mechanism has been DEPRECATED AND IS NO LONGER      */
   /*          SUPPORTED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
   /* * NOTE * This functionality has been SUPERCEDED by the            */
   /*          L2CA_Enhanced_Data_Write() function !!!!!!!!!!!!!!!!!!!! */
typedef struct _tagL2CA_Channel_Queue_Threshold_t
{
   unsigned int SizeThreshold;
   unsigned int DepthThreshold;
   unsigned int LowQueueThreshold;
} L2CA_Channel_Queue_Threshold_t;

#define L2CA_CHANNEL_QUEUE_THRESHOLD_SIZE               (sizeof(L2CA_Channel_Queue_Threshold_t))

   /* The following type represents the various Controller Types that   */
   /* are supported.                                                    */
typedef enum
{
   ctBR_EDR,
   ctLE
} L2CA_Controller_Type_t;

   /* The following enumerated type is used with the                    */
   /* L2CA_Get_Link_Connection_State() function and denotes various link*/
   /* states that a Bluetooth device is currently operating (with       */
   /* regards to the L2CAP framework).                                  */
typedef enum
{
   lcsDisconnected,
   lcsConnecting,
   lcsConnected,
   lcsDisconnecting
} L2CA_Link_Connection_State_t;

   /* The following structure represents the structure of the L2CAP     */
   /* Connect Indication Event Data.  This structure is used when an    */
   /* L2CAP Connect Request is received.  The Upper Layer is provided   */
   /* the Connect Request information in the L2CA_Connect_Indication    */
   /* Callback Function. The LCID is the Local CID that should be used  */
   /* to reference this connection.  The Board address is provided as   */
   /* Extra information about the device that is requesting the         */
   /* connection.                                                       */
typedef struct _tagL2CA_Connect_Indication_t
{
  Word_t                        PSM;
  Word_t                        LCID;
  Byte_t                        Identifier;
  BD_ADDR_t                     BD_ADDR;
  L2CAP_Extended_Feature_Mask_t ExtendedFeatures;
} L2CA_Connect_Indication_t;

#define L2CA_CONNECT_INDICATION_SIZE                    (sizeof(L2CA_Connect_Indication_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Connect Confirmation Event Data.  The LCID is the Local CID that  */
   /* is used to reference this connection.                             */
   /* * NOTE *  This structure is also used as a Connection Pending.    */
   /*           When supplying a connection Pending Indication the      */
   /*           Result is used to denote the Pending Status.            */
typedef struct _tagL2CA_Connect_Confirmation_t
{
  Word_t                        LCID;
  Word_t                        Result;
  Word_t                        Status;
  L2CAP_Extended_Feature_Mask_t ExtendedFeatures;
} L2CA_Connect_Confirmation_t;

#define L2CA_CONNECT_CONFIRMATION_SIZE                  (sizeof(L2CA_Connect_Confirmation_t))

   /* The following structure represents the L2CA QoS Flow Spec         */
   /* parameters.                                                       */
typedef struct _tagL2CA_Flow_Spec_t
{
   Byte_t   Flags;
   Byte_t   ServiceType;
   DWord_t  TokenRate;
   DWord_t  TokenBucketSize;
   DWord_t  PeakBandwidth;
   DWord_t  Latency;
   DWord_t  DelayVariation;
} L2CA_Flow_Spec_t;

#define L2CA_FLOW_SPEC_SIZE                             (sizeof(L2CA_Flow_Spec_t))

   /* The following structure represents the L2CA Retransmission and    */
   /* Flow Control Mode parameters.                                     */
typedef struct _tagL2CA_Mode_Info_t
{
   Byte_t Mode;
   Byte_t TxWindowSize;
   Byte_t MaxTransmitAttempts;
   Word_t RetransmissionTimeout;
   Word_t MonitorTimeout;
   Word_t MaxPDUSize;
} L2CA_Mode_Info_t;

#define L2CA_MODE_INFO_SIZE                             (sizeof(L2CA_Mode_Info_t))

   /* The following structure represents the L2CA Extended Flow Spec    */
   /* parameters.                                                       */
typedef struct _tagL2CA_Extended_Flow_Spec_t
{
   Byte_t  Identifier;
   Byte_t  ServiceType;
   Word_t  MaxSDU;
   DWord_t SDUInterArrivalTime;
   DWord_t AccessLatency;
   DWord_t FlushTimeout;
} L2CA_Extended_Flow_Spec_t;

#define L2CA_EXTENDED_FLOW_SPEC_SIZE                    (sizeof(L2CA_Extended_Flow_Spec_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Config Request Data Structure.                                    */
typedef struct _tagL2CA_Config_Request_t
{
  Word_t                    Option_Flags;
  Word_t                    InMTU;
  Word_t                    OutFlushTO;
  L2CA_Flow_Spec_t          OutFlow;
  L2CA_Mode_Info_t          ModeInfo;
  Byte_t                    FCS_Option;
  L2CA_Extended_Flow_Spec_t ExtendedFlowSpec;
  Word_t                    ExtendedWindowSize;
} L2CA_Config_Request_t;

#define L2CA_CONFIG_REQUEST_SIZE                        (sizeof(L2CA_Config_Request_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Config Confirmation Event Data.                                   */
typedef struct _tagL2CA_Config_Confirmation_t
{
  Word_t                    LCID;
  Word_t                    Result;
  Word_t                    Option_Flags;
  Word_t                    InMTU;
  Word_t                    OutFlushTO;
  L2CA_Flow_Spec_t          OutFlow;
  L2CA_Mode_Info_t          ModeInfo;
  Byte_t                    FCS_Option;
  L2CA_Extended_Flow_Spec_t ExtendedFlowSpec;
  Word_t                    ExtendedWindowSize;
} L2CA_Config_Confirmation_t;

#define L2CA_CONFIG_CONFIRMATION_SIZE                   (sizeof(L2CA_Config_Confirmation_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Config Indication Event Data.                                     */
typedef struct _tagL2CA_Config_Indication_t
{
  Word_t                    LCID;
  Word_t                    Option_Flags;
  Word_t                    OutMTU;
  Word_t                    InFlushTO;
  L2CA_Flow_Spec_t          InFlow;
  L2CA_Mode_Info_t          ModeInfo;
  Byte_t                    FCS_Option;
  L2CA_Extended_Flow_Spec_t ExtendedFlowSpec;
  Word_t                    ExtendedWindowSize;
} L2CA_Config_Indication_t;

#define L2CA_CONFIG_INDICATION_SIZE                     (sizeof(L2CA_Config_Indication_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Config Response Event Data.                                       */
typedef struct _tagL2CA_Config_Response_t
{
  Word_t                    Option_Flags;
  Word_t                    OutMTU;
  Word_t                    InFlushTO;
  L2CA_Flow_Spec_t          InFlow;
  L2CA_Mode_Info_t          ModeInfo;
  Byte_t                    FCS_Option;
  L2CA_Extended_Flow_Spec_t ExtendedFlowSpec;
  Word_t                    ExtendedWindowSize;
} L2CA_Config_Response_t;

#define L2CA_CONFIG_RESPONSE_SIZE                       (sizeof(L2CA_Config_Response_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Config Parameters.  This structure is used with the               */
   /* L2CA_Get_Current_Channel_Configuration() function.                */
typedef struct _tagL2CA_Config_Params_t
{
  Word_t           OutMTU;
  Word_t           InFlushTO;
  Word_t           OutFlushTO;
  L2CA_Flow_Spec_t InFlow;
  Word_t           RemoteCID;
} L2CA_Config_Params_t;

#define L2CA_CONFIG_PARAMS_SIZE                         (sizeof(L2CA_Config_Params_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Disconnect Indication Event Data.                                 */
typedef struct _tagL2CA_Disconnect_Indication_t
{
  Word_t LCID;
  Byte_t Reason;
} L2CA_Disconnect_Indication_t;

#define L2CA_DISCONNECT_INDICATION_SIZE                 (sizeof(L2CA_Disconnect_Indication_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Disconnect Confirmation Event Data.                               */
typedef struct _tagL2CA_Disconnect_Confirmation_t
{
  Word_t Result;
  Word_t LCID;
} L2CA_Disconnect_Confirmation_t;

#define L2CA_DISCONNECT_CONFIRMATION_SIZE               (sizeof(L2CA_Disconnect_Confirmation_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Timeout Indication Event Data.                                    */
typedef struct _tagL2CA_Timeout_Indication_t
{
  Word_t LCID;
} L2CA_Timeout_Indication_t;

#define L2CA_TIMEOUT_INDICATION_SIZE                    (sizeof(L2CA_Timeout_Indication_t))

   /* The following structure represents the structure of the L2CAP Echo*/
   /* Confirmation Event Data.                                          */
typedef struct _tagL2CA_Echo_Confirmation_t
{
   BD_ADDR_t  BD_ADDR;
   Word_t     Result;
   Word_t     Echo_Data_Length;
   Byte_t    *Variable_Data;
} L2CA_Echo_Confirmation_t;

#define L2CA_ECHO_CONFIRMATION_SIZE                      (sizeof(L2CA_Echo_Confirmation_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Information Confirmation Event Data.                              */
typedef struct _tagL2CA_Information_Confirmation_t
{
   BD_ADDR_t  BD_ADDR;
   Word_t     InfoType;
   Word_t     Result;
   Byte_t    *Variable_Data;
} L2CA_Information_Confirmation_t;

#define L2CA_INFORMATION_CONFIRMATION_SIZE               (sizeof(L2CA_Information_Confirmation_t))

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Read a specified Connectionless MTU Value in the   */
   /* L2CA Information Confirmation Data.  The first parameter is a     */
   /* pointer to a Data Buffer that is a                                */
   /* L2CA_Information_Confirmation_t.                                  */
   /* * NOTE * No Check of any of the input data is performed !         */
#define L2CA_INFORMATION_CONFIRMATION_READ_CONNECTIONLESS_MTU_DATA(_x)      (((Word_t *)(((L2CA_Information_Confirmation_t *)(_x))->Variable_Data))[0])

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Set a specified Connectionless MTU Value in the    */
   /* L2CA Information Confirmation Data.  The first parameter is a     */
   /* pointer to a Data Buffer that is a                                */
   /* L2CA_Information_Confirmation_t.  The second parameter is the     */
   /* value of the Connectionless MTU to set in the data structure.     */
   /* * NOTE * No Check of any of the input data is performed !         */
#define L2CA_INFORMATION_CONFIRMATION_SET_CONNECTIONLESS_MTU_DATA(_x, _y)   (((Word_t *)(((L2CA_Information_Confirmation_t *)(_x))->Variable_Data))[0] = (Word_t)(_y))

   /* The following structure represents the structure of the L2CAP     */
   /* Connectionless Data Indication Event Data.                        */
typedef struct _tagL2CA_Group_Data_Indication_t
{
   Word_t     PSM;
   Word_t     GroupCID;
   BD_ADDR_t  BD_ADDR;
   Word_t     Data_Length;
   Byte_t    *Variable_Data;
} L2CA_Group_Data_Indication_t;

#define L2CA_GROUP_DATA_INDICATION_SIZE                  (sizeof(L2CA_Group_Data_Indication_t))

   /* The following structure represents the structure of the L2CAP Data*/
   /* Indication Event Data.                                            */
typedef struct _tagL2CA_Data_Indication_t
{
   Word_t  CID;
   Word_t  Data_Length;
   Byte_t *Variable_Data;
} L2CA_Data_Indication_t;

#define L2CA_DATA_INDICATION_SIZE                        (sizeof(L2CA_Data_Indication_t))

   /* The following structure represents the structure of the L2CAP Data*/
   /* Error Indication Event.  The Data Error Event is issued when an   */
   /* inconsistency is detected in the reception of data on a channel   */
   /* that is configured for reliable operation.                        */
typedef struct _tagL2CA_Data_Error_Indication_t
{
   Word_t Result;
   Word_t Status;
   Word_t CID;
} L2CA_Data_Error_Indication_t;

   /* The following MACRO is a utility MACRO that exists to aid code    */
   /* readability to Determine the size (in Bytes) of an                */
   /* L2CA Data Error Indication Structure.                             */
#define L2CA_DATA_ERROR_INDICATION_SIZE                 (sizeof(L2CA_Data_Error_Indication_t))

   /* The following structure represents the structure of the L2CA Group*/
   /* Member Status Event Data.  Upon the successful addition of a      */
   /* member to the group, the information in the structure will be     */
   /* dispatched, via the Callback function that was supplied when the  */
   /* Group was created, to indicate the Connection State of the remote */
   /* device.  There will be a Callback made for each Connection and    */
   /* Disconnection of the remote device.  The BD_ADDR indicates the    */
   /* Board Address of the member that was attempted to be added and the*/
   /* CID references the Group in which the Member was to be added.     */
typedef struct _tagL2CA_Group_Member_Status_t
{
   Word_t    PSM;
   Word_t    GroupCID;
   BD_ADDR_t BD_ADDR;
   Boolean_t Connected;
} L2CA_Group_Member_Status_t;

#define L2CA_GROUP_MEMBER_STATUS_SIZE                   (sizeof(L2CA_Group_Member_Status_t))

   /* The following structure represents the event that is dispatched   */
   /* when the L2CAP Channel Buffers are Empty.  This event is ONLY     */
   /* dispatched when the caller has tried to write data and the        */
   /* Channel Buffers are full.  See the L2CAP_Data_Write() and the     */
   /* L2CAP_Group_Data_Write() functions for more information.          */
typedef struct _tagL2CA_Channel_Buffer_Empty_Indication_t
{
   Word_t CID;
} L2CA_Channel_Buffer_Empty_Indication_t;

#define L2CA_CHANNEL_BUFFER_EMPTY_INDICATION_SIZE       (sizeof(L2CA_Channel_Buffer_Empty_Indication_t))

   /* The following structure represents the event that is dispatched   */
   /* when the L2CAP Connection Parameter Update request is received.   */
typedef struct _tagL2CA_Connection_Parameter_Update_Indication_t
{
   Word_t    FCID;
   BD_ADDR_t BD_ADDR;
   Word_t    IntervalMin;
   Word_t    IntervalMax;
   Word_t    SlaveLatency;
   Word_t    TimeoutMultiplier;
} L2CA_Connection_Parameter_Update_Indication_t;

#define L2CA_CONNECTION_PARAMETER_UPDATE_INDICATION_SIZE   (sizeof(L2CA_Connection_Parameter_Update_Indication_t))

   /* The following structure represents the event that is dispatched   */
   /* when the L2CAP Connection Parameter Update response is received.  */
typedef struct _tagL2CA_Connection_Parameter_Update_Confirmation_t
{
   Word_t    FCID;
   BD_ADDR_t BD_ADDR;
   Word_t    Result;
} L2CA_Connection_Parameter_Update_Confirmation_t;

#define L2CA_CONNECTION_PARAMETER_UPDATE_CONFIRMATION_SIZE (sizeof(L2CA_Connection_Parameter_Update_Confirmation_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Fixed Channel Connect Indication Event Data.                      */
typedef struct _tagL2CA_Fixed_Channel_Connect_Indication_t
{
   Word_t                 FCID;
   BD_ADDR_t              BD_ADDR;
   L2CA_Controller_Type_t ControllerType;
} L2CA_Fixed_Channel_Connect_Indication_t;

#define L2CA_FIXED_CHANNEL_CONNECT_INDICATION_SIZE         (sizeof(L2CA_Fixed_Channel_Connect_Indication_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Fixed Channel Disconnect Indication Event Data.                   */
typedef struct _tagL2CA_Fixed_Channel_Disconnect_Indication_t
{
  Word_t                 FCID;
  BD_ADDR_t              BD_ADDR;
  L2CA_Controller_Type_t ControllerType;
} L2CA_Fixed_Channel_Disconnect_Indication_t;

#define L2CA_FIXED_CHANNEL_DISCONNECT_INDICATION_SIZE      (sizeof(L2CA_Fixed_Channel_Disconnect_Indication_t))

   /* The following structure represents the structure of the L2CAP     */
   /* Fixed Channel Data Indication Event Data.                         */
typedef struct _tagL2CA_Fixed_Channel_Data_Indication_t
{
   Word_t     FCID;
   BD_ADDR_t  BD_ADDR;
   Word_t     Data_Length;
   Byte_t    *Variable_Data;
} L2CA_Fixed_Channel_Data_Indication_t;

#define L2CA_FIXED_CHANNEL_DATA_INDICATION_SIZE          (sizeof(L2CA_Fixed_Channel_Data_Indication_t))

   /* The following structure represents the event that is dispatched   */
   /* when a specific fixed channel connection's buffers are empty.     */
   /* This event is ONLY dispatched when the caller has tried to write  */
   /* data and the Fixed Channel Buffers are full.  See the             */
   /* L2CAP_Enhanced_Fixed_Channel_Data_Write() function for more       */
   /* information.                                                      */
typedef struct _tagL2CA_Fixed_Channel_Buffer_Empty_Indication_t
{
   Word_t    FCID;
   BD_ADDR_t BD_ADDR;
} L2CA_Fixed_Channel_Buffer_Empty_Indication_t;

#define L2CA_FIXED_CHANNEL_BUFFER_EMPTY_INDICATION_SIZE  (sizeof(L2CA_Fixed_Channel_Buffer_Empty_Indication_t))

typedef struct _tagL2CA_Event_Data_t
{
   L2CA_Event_Type_t L2CA_Event_Type;
   DWord_t           Event_Data_Length;
   union
   {
      L2CA_Connect_Indication_t                       *L2CA_Connect_Indication;
      L2CA_Connect_Confirmation_t                     *L2CA_Connect_Confirmation;
      L2CA_Config_Indication_t                        *L2CA_Config_Indication;
      L2CA_Config_Confirmation_t                      *L2CA_Config_Confirmation;
      L2CA_Disconnect_Indication_t                    *L2CA_Disconnect_Indication;
      L2CA_Disconnect_Confirmation_t                  *L2CA_Disconnect_Confirmation;
      L2CA_Echo_Confirmation_t                        *L2CA_Echo_Confirmation;
      L2CA_Information_Confirmation_t                 *L2CA_Information_Confirmation;
      L2CA_Timeout_Indication_t                       *L2CA_Timeout_Indication;
      L2CA_Data_Indication_t                          *L2CA_Data_Indication;
      L2CA_Data_Error_Indication_t                    *L2CA_Data_Error_Indication;
      L2CA_Group_Data_Indication_t                    *L2CA_Group_Data_Indication;
      L2CA_Group_Member_Status_t                      *L2CA_Group_Member_Status;
      L2CA_Channel_Buffer_Empty_Indication_t          *L2CA_Channel_Buffer_Empty_Indication;
      L2CA_Connection_Parameter_Update_Indication_t   *L2CA_Connection_Parameter_Update_Indication;
      L2CA_Connection_Parameter_Update_Confirmation_t *L2CA_Connection_Parameter_Update_Confirmation;
      L2CA_Fixed_Channel_Connect_Indication_t         *L2CA_Fixed_Channel_Connect_Indication;
      L2CA_Fixed_Channel_Disconnect_Indication_t      *L2CA_Fixed_Channel_Disconnect_Indication;
      L2CA_Fixed_Channel_Data_Indication_t            *L2CA_Fixed_Channel_Data_Indication;
      L2CA_Fixed_Channel_Buffer_Empty_Indication_t    *L2CA_Fixed_Channel_Buffer_Empty_Indication;
   } Event_Data;
} L2CA_Event_Data_t;

   /* The following Constant represents the actual size of the L2CA     */
   /* Event Data Structure.  This Constant is to be used instead of     */
   /* simply using sizeof(L2CA_Event_Data_t) to get the size.  The      */
   /* reason for this was explained above, and is primarily to aid in   */
   /* code readability and efficiency.                                  */
#define L2CA_EVENT_DATA_SIZE                            (sizeof(L2CA_Event_Data_t))

   /* The following declared type represents the Prototype Function for */
   /* an L2CAP Event Callback.  This function will be called whenever a */
   /* define L2CAP Action occurs within the Bluetooth Protocol Stack    */
   /* that is specified with the specified Bluetooth Stack ID.  This    */
   /* function passes to the caller the Bluetooth Stack ID, the L2CAP   */
   /* Event Data associated with the L2CAP Event that occurred, and the */
   /* L2CAP Callback Parameter that was specified when this Callback was*/
   /* installed.  The caller is free to use the contents of the L2CAP   */
   /* Event Data ONLY in the context of this callback.  If the caller   */
   /* requires the Data for a longer period of time, then the callback  */
   /* function MUST copy the data into another Data Buffer.  This       */
   /* function is guaranteed NOT to be invoked more than once           */
   /* simultaneously for the specified installed callback (i.e. this    */
   /* function DOES NOT have be reentrant).  It Needs to be noted       */
   /* however, that if the same Callback is installed more than once,   */
   /* then the callbacks will be called serially.  Because of this, the */
   /* processing in this function should be as efficient as possible.   */
   /* It should also be noted that this function is called in the       */
   /* Thread Context of a Thread that the User does NOT own.  Therefore,*/
   /* processing in this function should be as efficient as possible    */
   /* (this argument holds anyway because another L2CAP Event will not  */
   /* be processed while this function call is outstanding).            */
   /* ** NOTE ** This function MUST NOT Block and wait for events that  */
   /*            can only be satisfied by Receiving other Bluetooth     */
   /*            Stack Events.  A Deadlock WILL occur because other     */
   /*            Callbacks might not be issued while this function is   */
   /*            currently outstanding.                                 */
typedef void (BTPSAPI *L2CA_Event_Callback_t)(unsigned int BluetoothStackID, L2CA_Event_Data_t *L2CA_Event_Data, unsigned long CallbackParameter);

   /* The following function is responsible for setting Timer Values    */
   /* that are used to control the operation of the Stack.  Refer to the*/
   /* documentation for the L2CA_Timer_Values_t structure for           */
   /* information on the available timers and their function.  This     */
   /* function takes as its parameters a BluetoothStackID that specifies*/
   /* the Bluetooth Protocol Stack for which the values are to be set   */
   /* and a pointer to a structure that contains the new timer values.  */
   /* If the new values are successfully set, the function will return a*/
   /* value of Zero.  If any error occurs while settings these values, a*/
   /* negative value will be returned.  Once set, these timer values    */
   /* will be used for all future L2CAP connections.  Connections that  */
   /* currently exist will not be affected.                             */
   /* **NOTE ** Prior to setting any timer with a new value, each of the*/
   /*           values will be tested to ensure that the value is       */
   /*           within the valid range for that timer.                  */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Set_Timer_Values(unsigned int BluetoothStackID, L2CA_Timer_Values_t *L2CA_Timer_Values);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Set_Timer_Values_t)(unsigned int BluetoothStackID, L2CA_Timer_Values_t *L2CA_Timer_Values);
#endif

   /* The following function is responsible for retrieving the current  */
   /* Timer Values that are used to control the operation of the Stack. */
   /* Refer to the documentation for the L2CA_Timer_Values_t structure  */
   /* for information on the available timers and their function.  This */
   /* function takes as its parameters a BluetoothStackID that specifies*/
   /* the Bluetooth Protocol Stack for which the values are to be       */
   /* retrieved and a pointer to a structure to receive the current     */
   /* timer values.  If the values are successfully retrieved, the      */
   /* function will return a value of Zero.  If any error occurs while  */
   /* obtaining these values, a negative value will be returned.        */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Timer_Values(unsigned int BluetoothStackID, L2CA_Timer_Values_t *L2CA_Timer_Values);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Timer_Values_t)(unsigned int BluetoothStackID, L2CA_Timer_Values_t *L2CA_Timer_Values);
#endif

   /* The following function is responsible for Registering an L2CAP    */
   /* Callback function, with the L2CAP Layer associated with the       */
   /* specified Bluetooth Stack ID, to handle incoming L2CAP Events     */
   /* destined for the specified PSM Number.  The first parameter to    */
   /* this function is the Bluetooth Stack ID that specifies the        */
   /* Bluetooth Protocol Stack to install the L2CAP Callback with.  The */
   /* second parameter is the PSM Number to register the L2CAP Callback */
   /* for, and the last two parameters specify the Callback Function    */
   /* and the Callback Parameter that will be passed to the callback    */
   /* function when an Event occurs for the specified PSM.  This        */
   /* function returns a non-zero, positive return value which          */
   /* represents the L2CAP PSM Callback ID if successful, or a          */
   /* negative return code if the function is unsuccessful.  The caller */
   /* can use the return value from this function (if successful) as    */
   /* the L2CAP_PSMID parameter for the L2CA_Un_Register_PSM()          */
   /* function when the caller wants to Un-Register the PSM from the    */
   /* L2CAP Layer associated with the Bluetooth Stack specified by the  */
   /* Bluetooth Stack ID parameter.                                     */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Register_PSM(unsigned int BluetoothStackID, Word_t PSM, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Register_PSM_t)(unsigned int BluetoothStackID, Word_t PSM, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for Un-Registering an L2CAP */
   /* Callback function that was previously registered via a successful */
   /* call to the L2CA_Register_PSM() function.  The first parameter to */
   /* this function is the Bluetooth Stack ID that specifies the        */
   /* Bluetooth Protocol Stack that the L2CAP PSM Callback Function was */
   /* previously installed, and the second parameter is the L2CAP PSM   */
   /* Callback ID.  This ID is the return value from the                */
   /* L2CA_Register_PSM() function.  This function returns zero if the  */
   /* L2CAP PSM Callback was successfully removed from the Bluetooth    */
   /* Protocol Stack or a negative return value if the operation was    */
   /* unsuccessful.  If this function completes successfully, then the  */
   /* specified Callback will NO longer be called when an L2CAP Event   */
   /* occurs for the PSM Number that was associated with the specified  */
   /* L2CAP Callback function.                                          */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Un_Register_PSM(unsigned int BluetoothStackID, unsigned int L2CAP_PSMID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Un_Register_PSM_t)(unsigned int BluetoothStackID, unsigned int L2CAP_PSMID);
#endif

   /* The following function is responsible for Registering an L2CAP    */
   /* Callback function, with the L2CAP Layer associated with the       */
   /* specified Bluetooth Stack ID, to handle incoming L2CAP Events     */
   /* destined for the specified Fixed Channel.  The first parameter to */
   /* this function is the Bluetooth Stack ID that specifies the        */
   /* Bluetooth Protocol Stack to install the L2CAP Callback with.  The */
   /* second parameter is the Fixed Channel to register the L2CAP       */
   /* Callback for.  The third channel is a pointer to channel specific */
   /* information that may be needed to support the fixed channel.  The */
   /* last two parameters specify the Callback Function and the Callback*/
   /* Parameter that will be passed to the callback function when an    */
   /* Event occurs for the specified channel.  This function returns a  */
   /* non-zero, positive return value which represents the registered   */
   /* Fixed channel ID (FCID) if successful, or a negative return code  */
   /* if the function is unsuccessful.  The caller can use the return   */
   /* value from this function (if successful) as the L2CAP_FCID        */
   /* parameter for the L2CA_Un_Register_Fixed_Channel() function when  */
   /* the caller wants to Un-Register the Channel from the L2CAP Layer  */
   /* associated with the Bluetooth Stack specified by the Bluetooth    */
   /* Stack ID parameter.                                               */
   /* * NOTE * The ChannelParameters parameter is a placeholder for     */
   /*          channel Specific information.  At this time there are no */
   /*          specific parameters assigned for any fixed channel.      */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Register_Fixed_Channel(unsigned int BluetoothStackID, Word_t FixedChannel, void *ChannelParameters, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Register_Fixed_Channel_t)(unsigned int BluetoothStackID, Word_t FixedChannel, void *ChannelParameters, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for un-registering an L2CAP */
   /* callback function that was previously registered via a successful */
   /* call to the L2CA_Register_Fixed_Channel() function.  The first    */
   /* parameter to this function is the Bluetooth Stack ID that         */
   /* specifies the Bluetooth Protocol Stack that the L2CAP Callback    */
   /* Function was previously installed, and the second parameter is the*/
   /* Fixed Channel ID Value (returned via a successful call to the     */
   /* L2CA_Register_Fixed_Channel() function).  This function returns   */
   /* zero if the Callback was successfully removed from the Bluetooth  */
   /* Protocol Stack or a negative return value if the operation was    */
   /* unsuccessful.  If this function completes successfully, then the  */
   /* specified Callback will NO longer be called when an L2CAP Event   */
   /* occurs for the Channel that was associated with the specified     */
   /* L2CAP Callback function.                                          */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Un_Register_Fixed_Channel(unsigned int BluetoothStackID, Word_t FCID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Un_Register_Fixed_Channel_t)(unsigned int BluetoothStackID, Word_t FCID);
#endif

   /* The following function is responsible for requesting the creation */
   /* of a Logical L2CAP Connection with the specified Bluetooth Board  */
   /* Address.  This function, accepts as input the Bluetooth Stack ID  */
   /* of the Bluetooth Stack to create the L2CAP Connection.  The       */
   /* second parameter to this function is the Bluetooth Board Address  */
   /* of the Bluetooth Device to establish the L2CAP Connection with.   */
   /* The third parameter is the PSM Number of the Protocol to request  */
   /* connection with (on the remote side), and the last two parameters */
   /* specify the L2CAP Callback Function and Callback Parameter that   */
   /* will be associated with ALL L2CAP Events that occur related to    */
   /* the requested Connection.  This function returns a positive,      */
   /* non-zero Local Channel Identifier (LCID) if the L2CAP Connection  */
   /* Request was issued successfully, or a negative, return error code */
   /* indicating an error.                                              */
   /* * NOTE * If this function is successful, then all further Status  */
   /*          and Event Notifications will occur through the Callback  */
   /*          Function that is specified with this function.           */
   /* * NOTE * A Positive return value (LCID) does NOT mean that a      */
   /*          connection already exists, only that the Connection      */
   /*          Request has been successfully submitted.                 */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Connect_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t PSM, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Connect_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t PSM, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for Responding to a L2CAP   */
   /* Connect Indication Event.  This function allows the recipient of  */
   /* the L2CAP Event the option of Responding to the Connection        */
   /* Indication with a Positive Accept, a Negative Accept, or a        */
   /* Pending Accept.  This function should be called ONLY upon receipt */
   /* of an L2CAP Connect Indication Event Callback.  The input         */
   /* parameter to this function are the Bluetooth Protocol Stack ID,   */
   /* the Bluetooth Board Address of the Bluetooth Device Requesting the*/
   /* L2CAP Connection, the L2CAP Identifier (this value was passed to  */
   /* the caller in the L2CAP Connect Indication Event), and the L2CAP  */
   /* Connection Accept Result (Accept, Pending, or Rejection Reason),  */
   /* and finally the Status of the Connection (Authorization Pending,  */
   /* etc.).  This function returns zero if the L2CAP Connection        */
   /* Response was successfully submitted, or a negative return error   */
   /* code if the Response was NOT successfully submitted.              */
   /* * NOTE * A successful return value (zero) does NOT mean that the  */
   /*          connection response was sent, only that the Connection   */
   /*          Response has been successfully submitted to the L2CAP    */
   /*          Layer associated with the Local Bluetooth Protocol Stack.*/
BTPSAPI_DECLARATION int BTPSAPI L2CA_Connect_Response(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Identifier, Word_t LCID, Word_t Response, Word_t Status);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Connect_Response_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Byte_t Identifier, Word_t LCID, Word_t Response, Word_t Status);
#endif

   /* The following function is used to issue an Configuration Request  */
   /* to the other peer.  The configuration data is passed to this      */
   /* function in a structure.  Since those options that the user does  */
   /* not want to negotiate, but assume the default, are not included in*/
   /* the structure.  In order to determine which options are present in*/
   /* the structure, the structure holds an Option_Flags field the is a */
   /* bit mask of the options that are included in the structure.       */
   /* Option fields that are not marked in the Option_Flags field are to*/
   /* be ignored.  NOTE: This function will scan the options record and */
   /* the Option_Flags bit mask in order to build a Options String that */
   /* is compatible with the L2CAP specification.  The Options string is*/
   /* variable string of options that begin with an Option Flag, Option */
   /* length and Option Data for each option in the list.               */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Config_Request(unsigned int BluetoothStackID, Word_t LCID, Word_t LinkTO, L2CA_Config_Request_t *ConfigRequest);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Config_Request_t)(unsigned int BluetoothStackID, Word_t LCID, Word_t LinkTO, L2CA_Config_Request_t *ConfigRequest);
#endif

   /* The following function is used to issue an Configuration Response */
   /* to the other peer.  The configuration data is passed to this      */
   /* function in a structure.  Those options that the user will accept */
   /* in the request are not included in the structure.  In order to    */
   /* determine which options are present in the structure, the         */
   /* structure holds an Option_Flags field the is a bit mask of the    */
   /* options that are included in the structure.  Option fields that   */
   /* are not marked in the Option_Flags field are accepted by the local*/
   /* user.  NOTE: This function will scan the options record and the   */
   /* Option_Flags bit mask in order to build a Options String that is  */
   /* compatible with the L2CAP specification.  The Options string is   */
   /* variable string of options that begin with an Option Flag, Option */
   /* length and Option Data for each option in the list.               */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Config_Response(unsigned int BluetoothStackID, Word_t LCID, Word_t Result, L2CA_Config_Response_t *ConfigResponse);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Config_Response_t)(unsigned int BluetoothStackID, Word_t LCID, Word_t Result, L2CA_Config_Response_t *ConfigResponse);
#endif

   /* The following function is responsible for requesting the          */
   /* Disconnection of a logical L2CAP Connection that has previously   */
   /* been established (either created or accepted).  The input         */
   /* parameters to this function are the Bluetooth stack ID of the     */
   /* Bluetooth Stack that is maintaining the L2CAP Connection, and the */
   /* Local Channel Identifier (LCID) of the Logical L2CAP Connection   */
   /* to terminate.  This function returns a zero value if the          */
   /* L2CAP Connection was terminated, or a negative, return error      */
   /* code if unsuccessful.  If this function completes successfully    */
   /* then an L2CAP Disconnect Indication will be sent to the L2CAP     */
   /* Callback Function that was handling the L2CAP Events for this     */
   /* connection.                                                       */
   /* * NOTE * It should be noted that after this function is called    */
   /*          (if it completes successfully), the LCID is NO Longer    */
   /*          able to be used (i.e. Logical Connection is terminated). */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Disconnect_Request(unsigned int BluetoothStackID, Word_t LCID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Disconnect_Request_t)(unsigned int BluetoothStackID, Word_t LCID);
#endif

   /* The following function is responsible for Responding to a L2CAP   */
   /* Disconnect Indication Event.  This function allows the recipient  */
   /* of the L2CAP Event the option of Responding to the Disconnection  */
   /* Indication.  There is no option provided to reject or deny the    */
   /* request. This function should be called ONLY upon receipt of an   */
   /* L2CAP Disconnect Indication Event Callback.  The input parameter  */
   /* to this function are the Bluetooth Protocol Stack ID and the L2CAP*/
   /* Identifier (this value was passed to the caller in the caller in  */
   /* the L2CAP Disconnect Indication Event).  This function returns    */
   /* zero if the L2CAP Disconnection Response was successfully         */
   /* submitted, or a negative return error code if the Response was NOT*/
   /* successfully submitted.                                           */
   /* * NOTE * A successful return value (zero) does NOT mean that the  */
   /*          disconnection response was sent, only that the           */
   /*          Disconnection Response has been successfully submitted to*/
   /*          the L2CAP Layer associated with the Local Bluetooth      */
   /*          Protocol Stack.  Any further use of the specified CID    */
   /*          will be rejected by the stack.                           */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Disconnect_Response(unsigned int BluetoothStackID, Word_t LCID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Disconnect_Response_t)(unsigned int BluetoothStackID, Word_t LCID);
#endif

   /* The following function is responsible for Sending L2CAP Data to   */
   /* the specified L2CAP Connection.  The L2CAP Connection ID (LCID)   */
   /* that is passed to this function MUST have been established        */
   /* by either Accepting an L2CAP Connection or Initiating an L2CAP    */
   /* Connection (and having the other side accept the Connection).     */
   /* The input parameters to this function are the Bluetooth Stack ID  */
   /* of the Bluetooth Stack that the second parameter is valid for     */
   /* (LCID - Logical Connection Channel Identifier), the Length of     */
   /* the Data to send and a pointer to the Data Buffer to Send.  This  */
   /* function returns a zero if the data was successfully sent, or     */
   /* a negative return error code if unsuccessful.                     */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing L2CAP Queue.  The caller   */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etChannel_Buffer_Empty_Indication                     */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Data_Write(unsigned int BluetoothStackID, Word_t LCID, Word_t Data_Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Data_Write_t)(unsigned int BluetoothStackID, Word_t LCID, Word_t Data_Length, Byte_t *Data);
#endif

   /* The following function is responsible for Sending L2CAP Data to   */
   /* the specified L2CAP Connection.  This function provides additional*/
   /* functionallity to control the amount of buffer usage for each data*/
   /* channel .The L2CAP Connection ID (LCID) that is passed to this    */
   /* function MUST have been established by either Accepting an L2CAP  */
   /* Connection or Initiating an L2CAP Connection (and having the other*/
   /* side accept the Connection).  The input parameters to this        */
   /* function are the Bluetooth Stack ID of the Bluetooth Stack that   */
   /* the second parameter is valid for (LCID - Logical Connection      */
   /* Channel Identifier), a pointer to a structure that contains       */
   /* conditional queueing parameters, the Length of the Data to send   */
   /* and a pointer to the Data Buffer to Send.  This function returns a*/
   /* zero if the data was successfully sent, or a negative return error*/
   /* code if unsuccessful.                                             */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing L2CAP Queue.  The caller   */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etChannel_Buffer_Empty_Indication                     */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
   /* * NOTE * If this function is called with QueueingParameters set to*/
   /*          NULL, then this function operates like the legacy        */
   /*          L2CA_Data_Write function.                                */
   /* * NOTE * If this function is called with a non-NULL               */
   /*          QueueingParameters then the data is queued conditionally.*/
   /*          If successful, the return value will indicate the number */
   /*          of packets/bytes that are currently queued on the        */
   /*          specified channel at the time the function returns.      */
BTPSAPI_DECLARATION long BTPSAPI L2CA_Enhanced_Data_Write(unsigned int BluetoothStackID, Word_t LCID, L2CA_Queueing_Parameters_t *QueueingParameters, Word_t Data_Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef long (BTPSAPI *PFN_L2CA_Enhanced_Data_Write_t)(unsigned int BluetoothStackID, Word_t LCID, L2CA_Queueing_Parameters_t *QueueingParameters, Word_t Data_Length, Byte_t *Data);
#endif

   /* The following function is responsible for Sending L2CAP Data to   */
   /* the specified L2CAP Connection over a specified Fixed Channel.    */
   /* The L2CAP Connection ID (FCID) that is passed to this function    */
   /* identifies the Fixed Channel on which the data is to be sent.  The*/
   /* input parameters to this function are the Bluetooth Stack ID of   */
   /* the Bluetooth Stack.  The second parameter identifies the address */
   /* of the remote device that is to receive the data.  The third      */
   /* parameter identifies the Fixed Channel on which the data is to be */
   /* sent.  The Length of the Data to send and a pointer to the Data   */
   /* Buffer to Send follows.  This function returns a zero if the data */
   /* was successfully sent, or a negative return error code if         */
   /* unsuccessful.                                                     */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Fixed_Channel_Data_Write(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t FCID, Word_t Data_Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Fixed_Channel_Data_Write_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t FCID, Word_t Data_Length, Byte_t *Data);
#endif

   /* The following function is responsible for Sending L2CAP Data to   */
   /* the specified L2CAP Connection over a specified Fixed Channel.    */
   /* The L2CAP Connection ID (FCID) that is passed to this function    */
   /* identifies the Fixed Channel on which the data is to be sent.  The*/
   /* input parameters to this function are the Bluetooth Stack ID of   */
   /* the Bluetooth Stack.  The second parameter identifies the address */
   /* of the remote device that is to receive the data.  The third      */
   /* parameter identifies the Fixed Channel on which the data is to be */
   /* sent.  The fourth parameter contains the optional Queueing        */
   /* Paramaters to use when sending the data.  The fifth and sixth     */
   /* parameters contain Length of the Data to send and a pointer to the*/
   /* Data Buffer to Send follows.  This function returns a zero if the */
   /* data was successfully sent, or a negative return error code if    */
   /* unsuccessful.                                                     */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing L2CAP Queue.  The caller   */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etFixed_Channel_Buffer_Empty_Indication               */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
   /* * NOTE * If this function is called with QueueingParameters set to*/
   /*          NULL, then this function operates like the legacy        */
   /*          L2CA_Fixed_Channel_Data_Write() function.                */
   /* * NOTE * If this function is called with a non-NULL               */
   /*          QueueingParameters then the data is queued conditionally.*/
   /*          If successful, the return value will indicate the number */
   /*          of packets that are currently queued on the specified    */
   /*          channel at the time the function returns.                */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Enhanced_Fixed_Channel_Data_Write(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t FCID, L2CA_Queueing_Parameters_t *QueueingParameters, Word_t Data_Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Enhanced_Fixed_Channel_Data_Write_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t FCID, L2CA_Queueing_Parameters_t *QueueingParameters, Word_t Data_Length, Byte_t *Data);
#endif

   /* The following function is responsible for Sending L2CAP Data to   */
   /* the specified Group.  The L2CAP Connection ID (LCID) references   */
   /* a Group and the members of the group.  A group need not have any  */
   /* members, but if members are assigned to the group, a message is   */
   /* formatted and sent to each member of the group.  The data is set  */
   /* to each member on CID 0002, which is the Connectionless Data      */
   /* channel.  Along with the data, the Destination PSM is included to */
   /* direct the connectionless data to the proper endpoint.  When a    */
   /* member is added to the group, a connection to the BD_ADDR is      */
   /* established.  However, the connection may have been terminated    */
   /* some time after the member was added, and this function will make */
   /* no effort to verify that a connection still exists prior to       */
   /* sending the data.  This function returns a zero if the data was   */
   /* successfully sent, or a negative return error code if             */
   /* unsuccessful.                                                     */
   /* * NOTE * If this function returns the Error Code:                 */
   /*                                                                   */
   /*             BTPS_ERROR_INSUFFICIENT_BUFFER_SPACE                  */
   /*                                                                   */
   /*          then this is a signal to the caller that the requested   */
   /*          data could NOT be sent because the requested data could  */
   /*          not be queued in the Outgoing L2CAP Queue.  The caller   */
   /*          then, must wait for the                                  */
   /*                                                                   */
   /*             etChannel_Buffer_Empty_Indication                     */
   /*                                                                   */
   /*          Event before trying to send any more data.               */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Group_Data_Write(unsigned int BluetoothStackID, Word_t LCID, Word_t Data_Length, Byte_t *Data);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Group_Data_Write_t)(unsigned int BluetoothStackID, Word_t LCID, Word_t Data_Length, Byte_t *Data);
#endif

   /* The following function is responsible for Initiating an L2CAP     */
   /* Echo Request to the specified Bluetooth Board Address.  This      */
   /* function allows the caller to specify data (not required) that is */
   /* be sent to the specified Bluetooth Board Address and returned     */
   /* (hence the name Echo Request).  This function accepts as input    */
   /* the Bluetooth Protocol Stack that is to issue the L2CAP Echo      */
   /* Request, the Bluetooth Board Address of the Target Bluetooth      */
   /* Device, The data to exchange in the request (optional), and an    */
   /* L2CAP Event Callback Function that is to receive the L2CAP Echo   */
   /* Response Event.  This function returns a positive, non-zero       */
   /* return value if the L2CAP Echo Request was successfully submitted,*/
   /* or a negative return error value if unsuccessful.                 */
   /* * NOTE * A successful return value (zero) does NOT mean that the  */
   /*          L2CA Echo Request was sent, only that the L2CA Echo      */
   /*          Request has been successfully submitted to the L2CAP     */
   /*          Layer associated with the Local Bluetooth Protocol Stack.*/
   /* * NOTE * Upon successful completion of this function, the caller  */
   /*          will have to process the result of the Echo Request in   */
   /*          the L2CA Event Callback that was specified as input to   */
   /*          this function.                                           */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Ping(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Data_Length, Byte_t *Data, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Ping_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Data_Length, Byte_t *Data, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for Initiating an L2CAP Info*/
   /* Request to the specified Bluetooth Board Address.  This function  */
   /* allows the caller to specify the Info Parameter that is be sent to*/
   /* the specified Bluetooth Board Address.  The return Information    */
   /* will be received in an Information Confirmation Event.  This      */
   /* function accepts as input the Bluetooth Protocol Stack that is to */
   /* issue the L2CAP Information Request, the Bluetooth Board Address  */
   /* of the Target Bluetooth Device.  This function returns a positive,*/
   /* non-zero return value if the L2CA Get Info Request was            */
   /* successfully submitted or a negative return error value if        */
   /* unsuccessful.                                                     */
   /* * NOTE * A successful return value (zero) does NOT mean that the  */
   /*          L2CA Get Info Request was sent, only that the L2CA Get   */
   /*          Info Request has been successfully submitted to the L2CAP*/
   /*          Layer associated with the Local Bluetooth Protocol Stack.*/
   /* * NOTE * Upon successful completion of this function, the caller  */
   /*          will have to process the result of the Info Request in   */
   /*          the L2CA Event Callback that was specified as input to   */
   /*          this function.                                           */
   /* * NOTE * If a connection to the specified Board Address does not  */
   /*          exist at the time the request is made, the request will  */
   /*          be suspended until a connection to the device has been   */
   /*          established.                                             */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Info(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Info_Type, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Info_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Info_Type, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for Initiating a request to */
   /* Update Connection Parameters.  This function should only be called*/
   /* from an LE Slave.  This function accepts as its first parameter   */
   /* the Bluetooth Stack ID that is to issue the Request.  The next    */
   /* parameter is the BD_ADDR of the device that this command is       */
   /* directed to.  The remaining parameters are the connection         */
   /* parameter values that are to be updated.  This function returns a */
   /* positive, non-zero return value if the request was successfully   */
   /* submitted or a negative return error value if unsuccessful.       */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Connection_Parameter_Update_Request(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t IntervalMin, Word_t IntervalMax, Word_t SlaveLatency, Word_t TimeoutMultiplier);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Connection_Parameter_Update_Request_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t IntervalMin, Word_t IntervalMax, Word_t SlaveLatency, Word_t TimeoutMultiplier);
#endif

   /* The following function is responsible for Initiating an L2CAP     */
   /* response to an Update Connection Parameters request.  This        */
   /* function should only be called from an LE Masters.  This function */
   /* accepts as its first parameter the Bluetooth Stack ID that is to  */
   /* issue the Request.  The next parameter is the BD_ADDR of the      */
   /* device that this command is directed to.  The last parameter is   */
   /* the result code for the request.  This function returns a         */
   /* positive, non-zero return value if the request was successfully   */
   /* submitted or a negative return error value if unsuccessful.       */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Connection_Parameter_Update_Response(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Result);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Connection_Parameter_Update_Response_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, Word_t Result);
#endif

   /* The following function is responsible for processing the L2CA     */
   /* Group Create.  A Group is created in order to send and receive    */
   /* Connectionless data from other devices.  When a Group is Created, */
   /* a PSM value is specified.  This value provides a filter for the   */
   /* various Connectionless Data packets that arrive at the local      */
   /* device.  Only those Group Messages that are destined for the PSM  */
   /* specified during the group create will be sent up the stack.  This*/
   /* function accepts as input the Bluetooth Protocol Stack on which   */
   /* the group is created, the PSM value for the group, A flag to      */
   /* specify if the receiver is to be enabled or disabled on Create, a */
   /* Callback function and Parameter to be used when dispatching Group */
   /* data to the Group Owner.  If the RxEnabled flag is set to TRUE,   */
   /* Group Data received for the specified PSM will be dispatched to   */
   /* the group owner.  If FALSE, Group data will be ignored at this    */
   /* layer.                                                            */
   /* * NOTE * A Group is created in order to receive group data.  No   */
   /*          Group Members are required in order to receive messages. */
   /*          Group Members are requires to send data to a specified   */
   /*          Group.                                                   */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Group_Create(unsigned int BluetoothStackID, Word_t PSM, Boolean_t RxEnabled, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Group_Create_t)(unsigned int BluetoothStackID, Word_t PSM, Boolean_t RxEnabled, L2CA_Event_Callback_t L2CA_Event_Callback, unsigned long CallbackParameter);
#endif

   /* The following function is responsible for processing the L2CA     */
   /* Group Close.  When a Group is closed, the Group Owner will no     */
   /* longer be able to receive Group Messages for the Group PSM.  If   */
   /* the Group contains members, each group member is removed from the */
   /* group and connections to each group member will be terminated if  */
   /* the connection is not required for any other purpose.  The        */
   /* function accepts as input the Bluetooth Protocol Stack on which   */
   /* the group exists, and the CID that references the Group.  If the  */
   /* removal of the Group was successful, the return value will be     */
   /* a non-negative value.  A negative return value indicates a failure*/
   /* to remove the Group.                                              */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Group_Close(unsigned int BluetoothStackID, Word_t CID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Group_Close_t)(unsigned int BluetoothStackID, Word_t CID);
#endif

   /* The following function is used to Add a Member to an existing     */
   /* Group.  The function takes as input the Bluetooth Protocol Stack  */
   /* on which the Group resides, the Board Address of the Member to be */
   /* added and the CID that references the Group.  If a connection to  */
   /* the Member to be added does not exist, a connection to the device */
   /* attempt to be established.  A negative return value from this     */
   /* function indicates the Request to Add member failed to complete.  */
   /* A non-negative result indicates the request was successfully      */
   /* submitted.                                                        */
   /* * NOTE * A non-negative result does not indicate the member was   */
   /*          added, but that the request to add the member was        */
   /*          submitted.  Information about the success or failure of  */
   /*          the addition of the member will be received later via    */
   /*          the Callback function that was supplied when the Group   */
   /*          was created.                                             */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Group_Add_Member(unsigned int BluetoothStackID, Word_t CID, BD_ADDR_t BD_ADDR);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Group_Add_Member_t)(unsigned int BluetoothStackID, Word_t CID, BD_ADDR_t BD_ADDR);
#endif

   /* This function is used to Remove a Group Member from the Member    */
   /* List.  If a member is removed from the list and the connection to */
   /* the device is no longer needed, then the connection to the device */
   /* removed will be terminated.  The function takes as input the      */
   /* Bluetooth Protocol Stack, the CID that references the Group in    */
   /* which the member resides and the Board Address of the Member to be*/
   /* removed.  A non-negative result indicates the removal of the      */
   /* member was successful.                                            */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Group_Remove_Member(unsigned int BluetoothStackID, Word_t CID, BD_ADDR_t BD_ADDR);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Group_Remove_Member_t)(unsigned int BluetoothStackID, Word_t CID, BD_ADDR_t BD_ADDR);
#endif

   /* The following function is used to obtain a list of Members to an  */
   /* existing Group.  The function takes as input the Bluetooth        */
   /* Protocol Stack on which the Group exists, the CID that references */
   /* the Group on the Stack, a Pointer to a buffer in which to receive */
   /* the Member List, and the Size of the buffer in Bytes.  The        */
   /* function also received a pointer in which to return the number of */
   /* members that have been inserted into the list and a pointer in    */
   /* which to receive the result of the request.  A negative result    */
   /* indicates an error occurred while executing the request.          */
   /* * NOTE * A non-negative result from the function does not indicate*/
   /*          that the function was successful.  A Non-Negative result */
   /*          indicates that the parameters were acceptable to complete*/
   /*          the request. The Result value should be examined to      */
   /*          determine if the command was successfully completed.     */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Group_Membership(unsigned int BluetoothStackID, Word_t CID, unsigned int *Result, unsigned int *MemberCount, unsigned int BufferSize, BD_ADDR_t *BD_ADDR);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Group_Membership_t)(unsigned int BluetoothStackID, Word_t CID, unsigned int *Result, unsigned int *MemberCount, unsigned int BufferSize, BD_ADDR_t *BD_ADDR);
#endif

   /* This function is used to Enable the reception of Group Messages.  */
   /* The function takes as input the Bluetooth Protocol Stack in which */
   /* the Group resides, and the PSM Group of Messages that are to be   */
   /* enabled.  If the PSM value supplied is 0x0000, then all Group     */
   /* Messages will be enabled.  A Non-Negative return value for the    */
   /* function indicates the messages were successfully enabled.        */
   /* * NOTE * A CID is used to reference a Group and a PSM is used to  */
   /*          reference a Group Message.  Thus, there may be multiple  */
   /*          Groups whom have registered for the particular PSM       */
   /*          Message.  Thus, enabling a PSM Message may effect        */
   /*          multiple Groups.                                         */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Enable_CLT(unsigned int BluetoothStackID, Word_t PSM);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Enable_CLT_t)(unsigned int BluetoothStackID, Word_t PSM);
#endif

   /* This function is used to Disable the reception of Group Messages. */
   /* The function takes as input the Bluetooth Protocol Stack in which */
   /* the Group resides, and the PSM Group of Messages that are to be   */
   /* disabled.  If the PSM value supplied is 0x0000, then all Group    */
   /* Messages will be disabled.  A Non-Negative return value for the   */
   /* function indicates the messages were successfully disabled.       */
   /* * NOTE * A CID is used to reference a Group and a PSM is used to  */
   /*          reference a Group Message.  Thus, there may be multiple  */
   /*          Groups whom have registered for the particular PSM       */
   /*          Message.  Thus, disabling a PSM Message may effect       */
   /*          multiple Groups.                                         */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Disable_CLT(unsigned int BluetoothStackID, Word_t PSM);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Disable_CLT_t)(unsigned int BluetoothStackID, Word_t PSM);
#endif

   /* The following function is responsible for flushing all data       */
   /* that is current queued for transmission for the specified CID.    */
   /* This function takes as its parameters the Bluetooth Stack ID that */
   /* identifies the stack in which the data is currently queued, and   */
   /* the Local L2CAP CID that identifies the channel on which the data */
   /* is currently queued.  This function will return Zero if           */
   /* successful, otherwise the function will return a negative error   */
   /* code.                                                             */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Flush_Channel_Data(unsigned int BluetoothStackID, Word_t CID);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Flush_Channel_Data_t)(unsigned int BluetoothStackID, Word_t CID);
#endif

   /* The following function is responsible for retrieving Config       */
   /* information on a specified CID.  The call must supply a pointer to*/
   /* memory for this routine to pass the configuration information.    */
   /* When a channel is created, the configuration parameters are set to*/
   /* default values, and are updated during the configuration process  */
   /* to reflect non-default values that are negotiated.  The config    */
   /* information only applies to Normal Channel types.  Other channel  */
   /* type do not configuration parameters.                             */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Current_Channel_Configuration(unsigned int BluetoothStackID, Word_t CID, L2CA_Config_Params_t *Channel_Config_Params);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Current_Channel_Configuration_t)(unsigned int BluetoothStackID, Word_t CID, L2CA_Config_Params_t *Channel_Config_Params);
#endif

   /* The following function is provided to allow a means to query the  */
   /* current Link Connection Request/Response Configuration.  The Link */
   /* Request/Response Configuration parameters mandate how L2CAP is to */
   /* issue Lower Link Requests and respond to Lower Link Requests      */
   /* during connection setup.  These parameters primarily mandate how  */
   /* Master/Slave Role Switching is to be supported in L2CAP (if L2CAP */
   /* is managing ALL Lower Level Connection Request/Acceptance (which  */
   /* is the default).  The first parameter to this function is the     */
   /* Bluetooth Stack ID of the Bluetooth Device that the L2CAP Link    */
   /* Connection Configuration parameters are to be retrieved.  The     */
   /* second parameter to this function is a pointer to a buffer that   */
   /* is to receive the current L2CAP Link Connection Configuration     */
   /* parameters.  This function returns zero if successful or a        */
   /* negative return value if an error occurred.                       */
   /* * NOTE * This function, and it's counterpart, the                 */
   /*          L2CAP_Set_Link_Connection_Configuration() function, are  */
   /*          really only of use when Point to Multi-Point usage is    */
   /*          required (either Local or Remote).  The default values   */
   /*          are:                                                     */
   /*                                                                   */
   /*             cqNoRoleSwitch                                        */
   /*             csMaintainCurrentRole                                 */
   /*                                                                   */
   /*          which means that if a connection is requested by L2CAP   */
   /*          the Local Device will NOT allow a Role switch and will   */
   /*          remain the Master of the Connection.  If a connection is */
   /*          responded to by L2CAP then NO Role Switch will be        */
   /*          attempted (the Local Device will remain the Slave).      */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Link_Connection_Configuration(unsigned int BluetoothStackID, L2CA_Link_Connect_Params_t *L2CA_Link_Connect_Params);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Link_Connection_Configuration_t)(unsigned int BluetoothStackID, L2CA_Link_Connect_Params_t *L2CA_Link_Connect_Params);
#endif

   /* The following function is provided to allow a means to change the */
   /* current Link Connection Request/Response Configuration.  The Link */
   /* Request/Response Configuration parameters mandate how L2CAP is to */
   /* issue Lower Link Requests and respond to Lower Link Requests      */
   /* during connection setup.  These parameters primarily mandate how  */
   /* Master/Slave Role Switching is to be supported in L2CAP (if L2CAP */
   /* is managing ALL Lower Level Connection Request/Acceptance (which  */
   /* is the default).  The first parameter to this function is the     */
   /* Bluetooth Stack ID of the Bluetooth Device that the L2CAP Link    */
   /* Connection Configuration parameters are to be changed.  The       */
   /* second parameter to this function is a pointer to a buffer that   */
   /* contains the new L2CAP Link Connection Configuration parameters.  */
   /* This function returns zero if successful or a negative return     */
   /* value if an error occurred.                                       */
   /* * NOTE * After this function has completed, the parameters will   */
   /*          ONLY be in effect when the next Lower Level Link Action  */
   /*          occurs (i.e. for future Link Connections).  Any current  */
   /*          L2CAP Links that are established are un-affected by the  */
   /*          action of this function.                                 */
   /* * NOTE * This function, and it's counterpart, the                 */
   /*          L2CAP_Get_Link_Connection_Configuration() function, are  */
   /*          really only of use when Point to Multi-Point usage is    */
   /*          required (either Local or Remote).  The default values   */
   /*          are:                                                     */
   /*                                                                   */
   /*             cqNoRoleSwitch                                        */
   /*             csMaintainCurrentRole                                 */
   /*                                                                   */
   /*          which means that if a connection is requested by L2CAP   */
   /*          the Local Device will NOT allow a Role switch and will   */
   /*          remain the Master of the Connection.  If a connection is */
   /*          responded to by L2CAP then NO Role Switch will be        */
   /*          attempted (the Local Device will remain the Slave).      */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Set_Link_Connection_Configuration(unsigned int BluetoothStackID, L2CA_Link_Connect_Params_t *L2CA_Link_Connect_Params);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Set_Link_Connection_Configuration_t)(unsigned int BluetoothStackID, L2CA_Link_Connect_Params_t *L2CA_Link_Connect_Params);
#endif

   /* The following function is provided to allow a mechanism to        */
   /* determine the current connection state of the specified link      */
   /* (specified by device address).  This function accepts as input the*/
   /* Bluetooth stack ID of the Bluetooth stack for which the query is  */
   /* destined.  The second parameter to this function is the Bluetooth */
   /* device address of the device that is to have it's link connection */
   /* state information returned.  The final parameter to this function */
   /* is a pointer to a variable that is to receive the current link    */
   /* connection state (if successful).  This function returns zero if  */
   /* successful (and fills in the specified Link Connection Status     */
   /* parameter), or a negative return error code if there was an error.*/
   /* * NOTE * This function should be called with the stack lock held  */
   /*          to guard against the state being returned to be invalid  */
   /*          (due to race condition/timing).                          */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Link_Connection_State(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, L2CA_Link_Connection_State_t *L2CA_Link_Connection_State);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Link_Connection_State_t)(unsigned int BluetoothStackID, BD_ADDR_t BD_ADDR, L2CA_Link_Connection_State_t *L2CA_Link_Connection_State);
#endif

   /* The following function is responsible for retrieving the current  */
   /* L2CAP Channel Queing Threshold information for the Bluetooth      */
   /* Stack L2CAP Module.  This function returns the current L2CAP      */
   /* Channel Queue Threshold Information.  This information is used by */
   /* the L2CAP Module to artificially limit the amount of Data that the*/
   /* L2CAP Module will buffer internally (per L2CAP Channel).  This    */
   /* will help alleviate the case where L2CAP always accepts data to   */
   /* be written when memory is available, which can lead to complete   */
   /* memory allocation usage (in the future).  The two parameters in   */
   /* the Queue Threshold structure specify the Minimum Size (in Bytes) */
   /* of an individual L2CAP ACL Segment that should be used as a       */
   /* check, and the Depth (the amount of these packet sizes) that is   */
   /* allowed.  This function returns the current L2CAP Queue Threshold */
   /* values.  This function returns zero if successful (and fills in   */
   /* the specified Threshold Information structure), or a negative     */
   /* return error code if there was an error.                          */
   /* * NOTE * This mechanism has been DEPRECATED AND IS NO LONGER      */
   /*          SUPPORTED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
   /* * NOTE * This functionality has been SUPERCEDED by the            */
   /*          L2CA_Enhanced_Data_Write() function !!!!!!!!!!!!!!!!!!!! */
   /* * NOTE * An L2CAP ACL Queue Threshold Depth of zero means that    */
   /*          NO Threshold limits are to be used (i.e. this            */
   /*          functionality is disabled).  A non-zero value specifies  */
   /*          the number of segments (greater than or equal to) the    */
   /*          Threshold Size that can be queued per L2CAP Channel.     */
   /* * NOTE * The L2CAP ACL Queue Threshold size is used to affect     */
   /*          the Threshold Depth.  Only queued segments that are      */
   /*          larger than the specified size are used to count the     */
   /*          Threshold Depth.  This means that smaller packets can be */
   /*          allowed to always be sent, while larger ones can be      */
   /*          guarded.                                                 */
   /* * NOTE * The Threshold values are set globally and reflect the    */
   /*          Threshold that will be applied to each individual L2CAP  */
   /*          Channel individually (not all channels).                 */
   /* * NOTE * This function exists so the caller can query the         */
   /*          current Threshold values.  The default values for both   */
   /*          of the Threshold settings is zero (disabled).  The       */
   /*          caller must use the L2CA_Set_Channel_Queue_Threshold()   */
   /*          API function to change this functionality.               */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Get_Channel_Queue_Threshold(unsigned int BluetoothStackID, L2CA_Channel_Queue_Threshold_t *L2CA_Channel_Queue_Threshold);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Get_Channel_Queue_Threshold_t)(unsigned int BluetoothStackID, L2CA_Channel_Queue_Threshold_t *L2CA_Channel_Queue_Threshold);
#endif

   /* The following function is responsible for changing the current    */
   /* L2CAP Channel Queing Threshold information for the Bluetooth      */
   /* Stack L2CAP Module.  This function changes the current L2CAP      */
   /* Channel Queue Threshold Information to match the L2CAP Channel    */
   /* Queue Threshold Information of the Threshold Information that is  */
   /* passed to this function.  This information is used by the L2CAP   */
   /* Module to artificially limit the amount of Data that the L2CAP    */
   /* Module will buffer internally (per L2CAP Channel).  This helps    */
   /* alleviate the case where L2CAP always accepts data to be written  */
   /* (queued) when memory is available, which can lead to complete     */
   /* memory allocation usage (in the future).  The two parameters in   */
   /* the Queue Threshold structure specify the Minimum Size (in Bytes) */
   /* of an individual L2CAP ACL Segment that should be used as a       */
   /* check, and the Depth (the amount of these packet sizes) that is   */
   /* allowed.  This function changes the current L2CAP Queue Threshold */
   /* values.  This function returns zero if the information was        */
   /* successfully changed, or a negative return error code if there    */
   /* was an error.                                                     */
   /* * NOTE * This mechanism has been DEPRECATED AND IS NO LONGER      */
   /*          SUPPORTED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
   /* * NOTE * This functionality has been SUPERCEDED by the            */
   /*          L2CA_Enhanced_Data_Write() function !!!!!!!!!!!!!!!!!!!! */
   /* * NOTE * An L2CAP ACL Queue Threshold Depth of zero means that    */
   /*          NO Threshold limits are to be used (i.e. this            */
   /*          functionality is disabled).  A non-zero value specifies  */
   /*          the number of segments (greater than or equal to) the    */
   /*          Threshold Size that can be queued per L2CAP Channel.     */
   /* * NOTE * The L2CAP ACL Queue Threshold size is used to affect     */
   /*          the Threshold Depth.  Only queued segments that are      */
   /*          larger than the specified size are used to count the     */
   /*          Threshold Depth.  This means that smaller packets can be */
   /*          allowed to always be sent, while larger ones can be      */
   /*          guarded.                                                 */
   /* * NOTE * The Threshold values are set globally and reflect the    */
   /*          Threshold that will be applied to each individual L2CAP  */
   /*          Channel individually (not all channels).                 */
   /* * NOTE * This function exists so the caller can change the        */
   /*          current Threshold values.  The default values for both   */
   /*          of the Threshold settings is zero (disabled).  The       */
   /*          caller can use the L2CA_Get_Channel_Queue_Threshold()    */
   /*          API function to query the current Threshold values.      */
BTPSAPI_DECLARATION int BTPSAPI L2CA_Set_Channel_Queue_Threshold(unsigned int BluetoothStackID, L2CA_Channel_Queue_Threshold_t *L2CA_Channel_Queue_Threshold);

#ifdef INCLUDE_BLUETOOTH_API_PROTOTYPES
   typedef int (BTPSAPI *PFN_L2CA_Set_Channel_Queue_Threshold_t)(unsigned int BluetoothStackID, L2CA_Channel_Queue_Threshold_t *L2CA_Channel_Queue_Threshold);
#endif

#endif
