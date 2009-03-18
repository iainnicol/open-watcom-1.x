;
; Misc. definitions
;
ETHERNET_MIN	=	60				; Smallest packet size supported for ethernet
ETHERNET_MAX	=	1514				; Largest packet size supported for ethernet
ETHERNET_TYPE	=	1				; Ethernet LINK type
MAX_INTERFACES	=	16				; Maximum number of interfaces
MAX_SESSIONS	=	16				; Maximum number of sessions
MAX_MULTICAST	=	16				; Maximum number of multicast addresses
MAX_TYPE_LENGTH	=	8				; Maximum number of bytes in packet type
MAX_DMA_SIZE	=	1536				; Maximum size of DMA buffers (1.5K)
DMA_UNIT_PAGES	=	MAX_DMA_SIZE SHR 9		; We allocate DMA pages in multiples of this size (3 pages = 12K = 8 buffers)
;
; Packet driver function numbers
;
ENUM PKTDRV_FUNCTIONS	{
			PKTDRV_GET_INFORMATION
			PKTDRV_OPEN_SESSION
			PKTDRV_CLOSE_SESSION
			PKTDRV_SEND_PACKET
			PKTDRV_GET_ADDRESS
			PKTDRV_SET_ADDRESS
			PKTDRV_GET_RECEIVE_MODE
			PKTDRV_SET_RECEIVE_MODE
			PKTDRV_GET_MULTICAST_LIST
			PKTDRV_SET_MULTICAST_LIST
			PKTDRV_GET_PARAMETERS
			PKTDRV_GET_STATISTICS
			PKTDRV_INSTALL_INTERFACE = 80h
			PKTDRV_REMOVE_INTERFACE
			PKTDRV_NUMBER_OF_INTERFACES
			}
;
; Packet driver errors
;
ENUM PKTDRV_ERRORS	{
			PKTDRV_BAD_FUNCTION = 1
			PKTDRV_BAD_TYPE
			PKTDRV_BAD_CLASS
			PKTDRV_BAD_HANDLE
			PKTDRV_BAD_INTERFACE
			PKTDRV_BAD_MODE
			PKTDRV_BAD_ADDRESS
			PKTDRV_NO_MULTICAST
			PKTDRV_NO_SPACE
			PKTDRV_IN_USE
			PKTDRV_CANT_SEND
			PKTDRV_CANT_SET
			}
;
; Packet driver classes
;
ENUM PKTDRV_CLASSES	{
			BLUEBOOK = 1
			PRONET10
			IEEE8025
			OMNINET
			APPLETALK
			SLIP
			STARLAN
			ARCNET
			AX25
			KISS
			IEEE8023
			FDDI
			IX25
			LANSTAR
			SLFP
			P2PP
			IEEE8025R
			P2PPL
			}
;
; Packet driver receive modes
;
ENUM PKTDRV_RCV_MODES	{
			MATCH_INTERFACE_ADDRESS
			MATCH_BROADCAST
			MATCH_SOME_MULTICAST
			MATCH_ALL_MULTICAST
			MATCH_ALL_PACKETS
			}
;
; Packet capture function numbers
;
ENUM PKTDRV_FUNCTIONS	{
			PKTDRV_OPEN_CAPTURE
			PKTDRV_CLOSE_CAPTURE
			PKTDRV_WAIT_PACKET
			}
;
; Supported packet driver interface types (in network order)
;
ETHERNET_IP	=	0008h
ETHERNET_ARP	=	0608h
ETHERNET_RARP	=	3508h
ETHERNET_LENGTH	=	2
CAPTURE_TYPE	=	0ffffh
CAPTURE_LENGTH	=	0
;
; Packet driver information
;
STRUC		PKTDRV_INFO
Version		DD	?				; Driver version number
PointerToName	DD	?				; Pointer to driver name
InterfaceClass	DD	?				; Driver interface class
ENDS
;
; Packet driver parameters
;
STRUC		PARAM
Length		DD	?				; Size of parameter structure
Major		DB	?				; Major revision number
Minor		DB	?				; Minor revision number
MaxMulticast	DB	?				; Maximum number of multicast addresses supported
MaxSessions	DB	?				; Number of sessions supported
MaxDevices	DB	?				; Number of devices supported
NumDevices	DB	?				; Number of devices installed
MTU		DW	?				; MTU size (excludes link layer header)
LinkType	DB	?				; Link layer type
LinkLength	DB	?				; Link layer address length
LinkSize	DB	?				; Link layer header length
		DB	?				; For aligment
ENDS
;
; Packet driver statistics
;
STRUC		STAT
RxPackets	DD	?				; Number of received packets
TxPackets	DD	?				; Number of sent packets
RxCount		DD	?				; Total number of bytes received
TxCount		DD	?				; Total number of bytes sent
RxErrors	DD	?				; Number of receive errors
TxErrors	DD	?				; Number of transmit errors
DroppedPackets	DD	?				; Number of dropped packets
ENDS
