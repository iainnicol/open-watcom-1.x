;
; Frame buffer API function numbers
;
FRAMEBUF_INFORMATION		=	00h		; Get Frame Buffer Information
FRAMEBUF_ENABLE_CONSOLE		=	01h		; Enable Frame Buffer Console Window
FRAMEBUF_DISABLE_CONSOLE	=	02h		; Disable Frame Buffer Console Window
FRAMEBUF_SET_CONSOLE_WINDOW	=	03h		; Set Frame Buffer Console Window
FRAMEBUF_FILL_RECTANGLE		=	04h		; Fill Rectangle
FRAMEBUF_COPY_RECTANGLE		=	05h		; Copy Rectangle
FRAMEBUF_DRAW_IMAGE		=	06h		; Draw Image
FRAMEBUF_CURSOR_OPERATION	=	07h		; Cursor Operation
FRAMEBUF_SET_PALETTE		=	08h		; Set Palette Register
;
; Frame buffer cursor operations
;
FRAMEBUF_CURSOR_ON		=	0		; Enable Cursor
FRAMEBUF_CURSOR_OFF		=	1		; Disable Cursor
FRAMEBUF_CURSOR_SHAPE		=	2		; Set Cursor Shape And Hot Spot
FRAMEBUF_CURSOR_POSITION	=	3		; Set Cursor Position
