;
; Supported address family
;
AF_INET		=	2				; The only supported address family
;
; Levels for getsockopt() and setsockopt()
;
SOL_SOCKET	=	256
SOL_TCP		=	6
SOL_IP		=	0
;
; For select support
;
STRUC		FDSET
Count		DD	?				; Number of entries
Handle		DD	?				; Array of handles
ENDS
;
; Translation of the standard sockaddr structure to AF_INET
;
STRUC		INET
Family		DW	?				; Network family
Port		DW	?				; Port in network order
Address		DD	?				; IP address in network order
Zero		DB	8 DUP (?)			; Unused
ENDS
