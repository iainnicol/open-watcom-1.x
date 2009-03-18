;
; Heap control block
;
STRUC		HEAP
Mutex		DD	8 DUP (?)			; Locking mutex for heap access
Start		DD	?				; Start of heap
Size		DD	?				; Size of heap
Free		DD	?				; Pointer to first free block
Available 	DD	?				; Total free memory
Max		DD	?				; Size of largest free memory block
Clean		DD	?				; Non zero if heap is clean
MaxBlockSize	DD	?				; Maximum block size (excluding size DWORD)
ENDS
