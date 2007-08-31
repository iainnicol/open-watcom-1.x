;
; Socket options
;
SO_DEBUG	=	1				; Turn on debugging info recording
SO_ACCEPTCONN	=	1 SHL 1				; Socket was listening
SO_REUSEADDR	=	1 SHL 2				; Allow local address reuse
SO_KEEPALIVE	=	1 SHL 3				; Keep connections alive
SO_DONTROUTE	=	1 SHL 4				; Just use interface addresses
SO_BROADCAST	=	1 SHL 5				; Permit sending of broadcast msgs
SO_USELOOPBACK	=	1 SHL 6				; Bypass hardware when possible
SO_LINGER	=	1 SHL 7				; Linger on close if data present
SO_OOBINLINE	=	1 SHL 8				; Leave received OOB data in line
SO_REUSEPORT	=	1 SHL 9				; Allow local address & port reuse
SO_DONTLINGER	=	NOT SO_LINGER			; Do not linger on close
SO_SNDBUF	=	1001h				; Send buffer size
SO_RCVBUF	=	1002h				; Receive buffer size
SO_SNDLOWAT	=	1003h				; Send low-water mark
SO_RCVLOWAT	=	1004h				; Receive low-water mark
SO_SNDTIMEO	=	1005h				; Send timeout
SO_RCVTIMEO	=	1006h				; Receive timeout
SO_ERROR	=	1007h				; Get error status and clear
SO_TYPE		=	1008h				; Get socket type
;
; User settable IP options
;
IP_TOS		=	1				; Set IP type of service
IP_TTL		=	2				; Set IP time to live
;
; User settable TCP options
;
TCP_NODELAY	=	1				; Don't delay send to coalesce packets
TCP_KEEPALIVE	=	2				; Send KEEPALIVE probes when idle for KeepAliveTime milliseconds
;
; Socket send/receive flags
;
MSG_OOB		=	1				; Send/receive out-of-band data
MSG_PEEK	=	2				; Read data without removing it from queue
MSG_DONTROUTE	=	4				; Do not route packet when sending
;
; IOCTL commands
;
FIONREAD	=	4004667fh			; Returns number of bytes available for next read
SIOCATMARK	=	40047307h			; Returns bolean reflecting out-of-band data read status
;
; Socket driver function numbers
;
ENUM SOCKET_FUNCTIONS	{
	    		SOCKET_OPEN
			SOCKET_CLOSE
			SOCKET_ACCEPT
			SOCKET_BIND
			SOCKET_CONNECT
			SOCKET_LISTEN
			SOCKET_SHUTDOWN
			SOCKET_RECEIVE
			SOCKET_RECEIVE_FROM
			SOCKET_SEND
			SOCKET_SEND_TO
			SOCKET_GET_OPTION
			SOCKET_SET_OPTION
			SOCKET_SELECT
			SOCKET_IOCTL
			SOCKET_REMOTE_ADDRESS
			SOCKET_LOCAL_ADDRESS
			LINK_OPEN
			LINK_CLOSE
			LINK_INFORMATION
			}
;
; Socket driver errors
;
ENUM SOCKET_ERRORS	{
			SOCKET_INVALID_FUNCTION = 1
			SOCKET_INVALID_TYPE
			SOCKET_NO_ROUTE
			SOCKET_IN_USE
			SOCKET_TRANSMIT_FAILED
			SOCKET_FRAGMENT_ERROR
			SOCKET_INVALID_STATE
			SOCKET_NOT_IN_USE
			SOCKET_INVALID_ADDRESS
			SOCKET_INVALID_HANDLE
			SOCKET_INVALID_PORT
			SOCKET_NOT_BOUND
			SOCKET_ALREADY_BOUND
			SOCKET_CONNECTION_FAILED
			SOCKET_CANT_READ
			SOCKET_CANT_WRITE
			SOCKET_INVALID_POINTER
			}
;
; Socket types
;
ENUM SOCKET_TYPES	{
			SOCKET_TCP
			SOCKET_UDP
			SOCKET_RAW
			}
