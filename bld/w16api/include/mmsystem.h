#ifndef	__MMSYSTEM_H
#define	__MMSYSTEM_H

#ifndef	__WINDOWS_H
#include <windows.h>
#endif

#if (WINVER < 0x30a)
#error	Multimedia APIs require Windows 3.1
#endif

#ifdef	__cplusplus
extern	"C" {
#endif

#pragma	pack(push,1)

#define	MAXPNAMELEN	32
#define	MAXERRORLENGTH	128
#define	TIME_MS	1
#define	TIME_SAMPLES	2
#define	TIME_BYTES	4
#define	TIME_SMPTE	8
#define	TIME_MIDI	0x10
#define	MM_JOY1MOVE	0x3A0
#define	MM_JOY2MOVE	0x3A1
#define	MM_JOY1ZMOVE	0x3A2
#define	MM_JOY2ZMOVE	0x3A3
#define	MM_JOY1BUTTONDOWN	0x3B5
#define	MM_JOY2BUTTONDOWN	0x3B6
#define	MM_JOY1BUTTONUP	0x3B7
#define	MM_JOY2BUTTONUP	0x3B8
#define	MM_MCINOTIFY	0x3B9
#define	MM_WOM_OPEN	0x3BB
#define	MM_WOM_CLOSE	0x3BC
#define	MM_WOM_DONE	0x3BD
#define	MM_WIM_OPEN	0x3BE
#define	MM_WIM_CLOSE	0x3BF
#define	MM_WIM_DATA	0x3C0
#define	MM_MIM_OPEN	0x3C1
#define	MM_MIM_CLOSE	0x3C2
#define	MM_MIM_DATA	0x3C3
#define	MM_MIM_LONGDATA	0x3C4
#define	MM_MIM_ERROR	0x3C5
#define	MM_MIM_LONGERROR	0x3C6
#define	MM_MOM_OPEN	0x3C7
#define	MM_MOM_CLOSE	0x3C8
#define	MM_MOM_DONE	0x3C9
#define	MMSYSERR_BASE	0
#define	WAVERR_BASE	32
#define	MIDIERR_BASE	64
#define	TIMERR_BASE	96
#define	JOYERR_BASE	160
#define	MCIERR_BASE	256
#define	MCI_STRING_OFFSET	512
#define	MCI_VD_OFFSET	1024
#define	MCI_CD_OFFSET	1088
#define	MCI_WAVE_OFFSET	1152
#define	MCI_SEQ_OFFSET	1216
#define	MMSYSERR_NOERROR	0
#define	MMSYSERR_ERROR	(MMSYSERR_BASE	+	1)
#define	MMSYSERR_BADDEVICEID	(MMSYSERR_BASE	+	2)
#define	MMSYSERR_NOTENABLED	(MMSYSERR_BASE	+	3)
#define	MMSYSERR_ALLOCATED	(MMSYSERR_BASE	+	4)
#define	MMSYSERR_INVALHANDLE	(MMSYSERR_BASE	+	5)
#define	MMSYSERR_NODRIVER	(MMSYSERR_BASE	+	6)
#define	MMSYSERR_NOMEM	(MMSYSERR_BASE	+	7)
#define	MMSYSERR_NOTSUPPORTED	(MMSYSERR_BASE	+	8)
#define	MMSYSERR_BADERRNUM	(MMSYSERR_BASE	+	9)
#define	MMSYSERR_INVALFLAG	(MMSYSERR_BASE	+	10)
#define	MMSYSERR_INVALPARAM	(MMSYSERR_BASE	+	11)
#define	MMSYSERR_LASTERROR	(MMSYSERR_BASE	+	11)
#if	(WINVER >= 0x30a)
#define	DRV_CANCEL	DRVCNF_CANCEL
#define	DRV_OK	DRVCNF_OK
#define	DRV_RESTART	DRVCNF_RESTART
#endif
#define	DRV_LOAD	1
#define	DRV_ENABLE	2
#define	DRV_OPEN	3
#define	DRV_CLOSE	4
#define	DRV_DISABLE	5
#define	DRV_FREE	6
#define	DRV_CONFIGURE	7
#define	DRV_QUERYCONFIGURE	8
#define	DRV_INSTALL	9
#define	DRV_REMOVE	10
#define	DRV_RESERVED	0x800
#define	DRV_USER	0x4000
#define	DRV_MCI_FIRST	DRV_RESERVED
#define	DRV_MCI_LAST	(DRV_RESERVED + 0xFFF)
#define	CALLBACK_TYPEMASK	0x70000l
#define	CALLBACK_NULL	0
#define	CALLBACK_WINDOW	0x10000l
#define	CALLBACK_TASK	0x20000l
#define	CALLBACK_FUNCTION	0x30000l
#define	SND_SYNC	0
#define	SND_ASYNC	1
#define	SND_NODEFAULT	2
#define	SND_MEMORY	4
#define	SND_LOOP	8
#define	SND_NOSTOP	0x10
#define	MM_MICROSOFT	1
#define	MM_MIDI_MAPPER	1
#define	MM_WAVE_MAPPER	2
#define	MM_SNDBLST_MIDIOUT	3
#define	MM_SNDBLST_MIDIIN	4
#define	MM_SNDBLST_SYNTH	5
#define	MM_SNDBLST_WAVEOUT	6
#define	MM_SNDBLST_WAVEIN	7
#define	MM_ADLIB	9
#define	MM_MPU401_MIDIOUT	10
#define	MM_MPU401_MIDIIN	11
#define	MM_PC_JOYSTICK	12
#define	WAVERR_BADFORMAT	(WAVERR_BASE + 0)
#define	WAVERR_STILLPLAYING	(WAVERR_BASE + 1)
#define	WAVERR_UNPREPARED	(WAVERR_BASE + 2)
#define	WAVERR_SYNC	(WAVERR_BASE + 3)
#define	WAVERR_LASTERROR	(WAVERR_BASE + 3)
#define	WOM_OPEN	MM_WOM_OPEN
#define	WOM_CLOSE	MM_WOM_CLOSE
#define	WOM_DONE	MM_WOM_DONE
#define	WIM_OPEN	MM_WIM_OPEN
#define	WIM_CLOSE	MM_WIM_CLOSE
#define	WIM_DATA	MM_WIM_DATA
#define	WAVE_MAPPER	(-1)
#define	WAVE_FORMAT_QUERY	1
#define	WAVE_ALLOWSYNC	2
#define	WHDR_DONE	1
#define	WHDR_PREPARED	2
#define	WHDR_BEGINLOOP	4
#define	WHDR_ENDLOOP	8
#define	WHDR_INQUEUE	0x10
#define	WAVECAPS_PITCH	1
#define	WAVECAPS_PLAYBACKRATE	2
#define	WAVECAPS_VOLUME	4
#define	WAVECAPS_LRVOLUME	8
#define	WAVECAPS_SYNC	0x10
#define	WAVE_INVALIDFORMAT	0
#define	WAVE_FORMAT_1M08	1
#define	WAVE_FORMAT_1S08	2
#define	WAVE_FORMAT_1M16	4
#define	WAVE_FORMAT_1S16	8
#define	WAVE_FORMAT_2M08	0x10
#define	WAVE_FORMAT_2S08	0x20
#define	WAVE_FORMAT_2M16	0x40
#define	WAVE_FORMAT_2S16	0x80
#define	WAVE_FORMAT_4M08	0x100
#define	WAVE_FORMAT_4S08	0x200
#define	WAVE_FORMAT_4M16	0x400
#define	WAVE_FORMAT_4S16	0x800
#define	WAVE_FORMAT_PCM	1
#define	MIDIERR_UNPREPARED	(MIDIERR_BASE + 0)
#define	MIDIERR_STILLPLAYING	(MIDIERR_BASE + 1)
#define	MIDIERR_NOMAP	(MIDIERR_BASE + 2)
#define	MIDIERR_NOTREADY	(MIDIERR_BASE + 3)
#define	MIDIERR_NODEVICE	(MIDIERR_BASE + 4)
#define	MIDIERR_INVALIDSETUP	(MIDIERR_BASE + 5)
#define	MIDIERR_LASTERROR	(MIDIERR_BASE + 5)
#define	MIDIPATCHSIZE	128
#define	MIM_OPEN	MM_MIM_OPEN
#define	MIM_CLOSE	MM_MIM_CLOSE
#define	MIM_DATA	MM_MIM_DATA
#define	MIM_LONGDATA	MM_MIM_LONGDATA
#define	MIM_ERROR	MM_MIM_ERROR
#define	MIM_LONGERROR	MM_MIM_LONGERROR
#define	MOM_OPEN	MM_MOM_OPEN
#define	MOM_CLOSE	MM_MOM_CLOSE
#define	MOM_DONE	MM_MOM_DONE
#define	MIDIMAPPER	(-1)
#define	MIDI_MAPPER	(-1)
#define	MIDI_CACHE_ALL	1
#define	MIDI_CACHE_BESTFIT	2
#define	MIDI_CACHE_QUERY	3
#define	MIDI_UNCACHE	4
#define	MOD_MIDIPORT	1
#define	MOD_SYNTH	2
#define	MOD_SQSYNTH	3
#define	MOD_FMSYNTH	4
#define	MOD_MAPPER	5
#define	MIDICAPS_VOLUME	1
#define	MIDICAPS_LRVOLUME	2
#define	MIDICAPS_CACHE	4
#define	MHDR_DONE	1
#define	MHDR_PREPARED	2
#define	MHDR_INQUEUE	4
#define	AUX_MAPPER	(-1)
#define	AUXCAPS_CDAUDIO	1
#define	AUXCAPS_AUXIN	2
#define	AUXCAPS_VOLUME	1
#define	AUXCAPS_LRVOLUME	2
#define	TIMERR_NOERROR	(0)
#define	TIMERR_NOCANDO	(TIMERR_BASE+1)
#define	TIMERR_struct	(TIMERR_BASE+33)
#define	TIME_ONESHOT	0
#define	TIME_PERIODIC	1
#define	JOYERR_NOERROR	(0)
#define	JOYERR_PARMS	(JOYERR_BASE+5)
#define	JOYERR_NOCANDO	(JOYERR_BASE+6)
#define	JOYERR_UNPLUGGED	(JOYERR_BASE+7)
#define	JOY_BUTTON1	1
#define	JOY_BUTTON2	2
#define	JOY_BUTTON3	4
#define	JOY_BUTTON4	8
#define	JOY_BUTTON1CHG	0x100
#define	JOY_BUTTON2CHG	0x200
#define	JOY_BUTTON3CHG	0x400
#define	JOY_BUTTON4CHG	0x800
#define	JOYSTICKID1	0
#define	JOYSTICKID2	1
#define	MMIOERR_BASE	256
#define	MMIOERR_FILENOTFOUND	(MMIOERR_BASE + 1)
#define	MMIOERR_OUTOFMEMORY	(MMIOERR_BASE + 2)
#define	MMIOERR_CANNOTOPEN	(MMIOERR_BASE + 3)
#define	MMIOERR_CANNOTCLOSE	(MMIOERR_BASE + 4)
#define	MMIOERR_CANNOTREAD	(MMIOERR_BASE + 5)
#define	MMIOERR_CANNOTWRITE	(MMIOERR_BASE + 6)
#define	MMIOERR_CANNOTSEEK	(MMIOERR_BASE + 7)
#define	MMIOERR_CANNOTEXPAND	(MMIOERR_BASE + 8)
#define	MMIOERR_CHUNKNOTFOUND	(MMIOERR_BASE + 9)
#define	MMIOERR_UNBUFFERED	(MMIOERR_BASE + 10)
#define	CFSEPCHAR	'+'
#define	MMIO_RWMODE	3
#define	MMIO_SHAREMODE	0x70
#define	MMIO_CREATE	0x1000
#define	MMIO_PARSE	0x100
#define	MMIO_DELETE	0x200
#define	MMIO_EXIST	0x4000
#define	MMIO_ALLOCBUF	0x10000
#define	MMIO_GETTEMP	0x20000
#define	MMIO_DIRTY	0x10000000
#define	MMIO_READ	0
#define	MMIO_WRITE	1
#define	MMIO_READWRITE	2
#define	MMIO_COMPAT	0
#define	MMIO_EXCLUSIVE	0x10
#define	MMIO_DENYWRITE	0x20
#define	MMIO_DENYREAD	0x30
#define	MMIO_DENYNONE	0x40
#define	MMIO_FHOPEN	0x10
#define	MMIO_EMPTYBUF	0x10
#define	MMIO_TOUPPER	0x10
#define	MMIO_INSTALLPROC	0x10000
#define	MMIO_GLOBALPROC	0x10000000
#define	MMIO_REMOVEPROC	0x20000
#define	MMIO_FINDPROC	0x40000
#define	MMIO_FINDCHUNK	0x10
#define	MMIO_FINDRIFF	0x20
#define	MMIO_FINDLIST	0x40
#define	MMIO_CREATERIFF	0x20
#define	MMIO_CREATELIST	0x40
#define	MMIOM_READ	MMIO_READ
#define	MMIOM_WRITE	MMIO_WRITE
#define	MMIOM_SEEK	2
#define	MMIOM_OPEN	3
#define	MMIOM_CLOSE	4
#define	MMIOM_WRITEFLUSH	5
#if	(WINVER >= 0x30a)
#define	MMIOM_RENAME	6
#endif
#define	MMIOM_USER	0x8000
#define	FOURCC_RIFF	mmioFOURCC('R','I','F','F')
#define	FOURCC_LIST	mmioFOURCC('L','I','S','T')
#define	FOURCC_DOS	mmioFOURCC('D','O','S',' ')
#define	FOURCC_MEM	mmioFOURCC('M','E','M',' ')
#ifndef	SEEK_SET
#define	SEEK_SET	0
#define	SEEK_CUR	1
#define	SEEK_END	2
#endif
#define	MMIO_DEFAULTBUFFER	8192
#define	mmioFOURCC(c0,c1,c2,c3)	((DWORD)(BYTE)(c0)|((DWORD)(BYTE)(c1)<<8)|((DWORD)(BYTE)(c2)<<16)|((DWORD)(BYTE)(c3)<<24))
#define	MCIERR_INVALID_DEVICE_ID	(MCIERR_BASE + 1)
#define	MCIERR_UNRECOGNIZED_KEYWORD	(MCIERR_BASE + 3)
#define	MCIERR_UNRECOGNIZED_COMMAND	(MCIERR_BASE + 5)
#define	MCIERR_HARDWARE	(MCIERR_BASE + 6)
#define	MCIERR_INVALID_DEVICE_NAME	(MCIERR_BASE + 7)
#define	MCIERR_OUT_OF_MEMORY	(MCIERR_BASE + 8)
#define	MCIERR_DEVICE_OPEN	(MCIERR_BASE + 9)
#define	MCIERR_CANNOT_LOAD_DRIVER	(MCIERR_BASE + 10)
#define	MCIERR_MISSING_COMMAND_STRING	(MCIERR_BASE + 11)
#define	MCIERR_PARAM_OVERFLOW	(MCIERR_BASE + 12)
#define	MCIERR_MISSING_STRING_ARGUMENT	(MCIERR_BASE + 13)
#define	MCIERR_BAD_INTEGER	(MCIERR_BASE + 14)
#define	MCIERR_PARSER_INTERNAL	(MCIERR_BASE + 15)
#define	MCIERR_DRIVER_INTERNAL	(MCIERR_BASE + 16)
#define	MCIERR_MISSING_PARAMETER	(MCIERR_BASE + 17)
#define	MCIERR_UNSUPPORTED_FUNCTION	(MCIERR_BASE + 18)
#define	MCIERR_FILE_NOT_FOUND	(MCIERR_BASE + 19)
#define	MCIERR_DEVICE_NOT_READY	(MCIERR_BASE + 20)
#define	MCIERR_INTERNAL	(MCIERR_BASE + 21)
#define	MCIERR_DRIVER	(MCIERR_BASE + 22)
#define	MCIERR_CANNOT_USE_ALL	(MCIERR_BASE + 23)
#define	MCIERR_MULTIPLE	(MCIERR_BASE + 24)
#define	MCIERR_EXTENSION_NOT_FOUND	(MCIERR_BASE + 25)
#define	MCIERR_OUTOFRANGE	(MCIERR_BASE + 26)
#define	MCIERR_FLAGS_NOT_COMPATIBLE	(MCIERR_BASE + 28)
#define	MCIERR_FILE_NOT_SAVED	(MCIERR_BASE + 30)
#define	MCIERR_DEVICE_TYPE_REQUIRED	(MCIERR_BASE + 31)
#define	MCIERR_DEVICE_LOCKED	(MCIERR_BASE + 32)
#define	MCIERR_DUPLICATE_ALIAS	(MCIERR_BASE + 33)
#define	MCIERR_BAD_CONSTANT	(MCIERR_BASE + 34)
#define	MCIERR_MUST_USE_SHAREABLE	(MCIERR_BASE + 35)
#define	MCIERR_MISSING_DEVICE_NAME	(MCIERR_BASE + 36)
#define	MCIERR_BAD_TIME_FORMAT	(MCIERR_BASE + 37)
#define	MCIERR_NO_CLOSING_QUOTE	(MCIERR_BASE + 38)
#define	MCIERR_DUPLICATE_FLAGS	(MCIERR_BASE + 39)
#define	MCIERR_INVALID_FILE	(MCIERR_BASE + 40)
#define	MCIERR_NULL_PARAMETER_BLOCK	(MCIERR_BASE + 41)
#define	MCIERR_UNNAMED_RESOURCE	(MCIERR_BASE + 42)
#define	MCIERR_NEW_REQUIRES_ALIAS	(MCIERR_BASE + 43)
#define	MCIERR_NOTIFY_ON_AUTO_OPEN	(MCIERR_BASE + 44)
#define	MCIERR_NO_ELEMENT_ALLOWED	(MCIERR_BASE + 45)
#define	MCIERR_NONAPPLICABLE_FUNCTION	(MCIERR_BASE + 46)
#define	MCIERR_ILLEGAL_FOR_AUTO_OPEN	(MCIERR_BASE + 47)
#define	MCIERR_FILENAME_REQUIRED	(MCIERR_BASE + 48)
#define	MCIERR_EXTRA_CHARACTERS	(MCIERR_BASE + 49)
#define	MCIERR_DEVICE_NOT_INSTALLED	(MCIERR_BASE + 50)
#define	MCIERR_GET_CD	(MCIERR_BASE + 51)
#define	MCIERR_SET_CD	(MCIERR_BASE + 52)
#define	MCIERR_SET_DRIVE	(MCIERR_BASE + 53)
#define	MCIERR_DEVICE_LENGTH	(MCIERR_BASE + 54)
#define	MCIERR_DEVICE_ORD_LENGTH	(MCIERR_BASE + 55)
#define	MCIERR_NO_INTEGER	(MCIERR_BASE + 56)
#define	MCIERR_WAVE_OUTPUTSINUSE	(MCIERR_BASE + 64)
#define	MCIERR_WAVE_SETOUTPUTINUSE	(MCIERR_BASE + 65)
#define	MCIERR_WAVE_INPUTSINUSE	(MCIERR_BASE + 66)
#define	MCIERR_WAVE_SETINPUTINUSE	(MCIERR_BASE + 67)
#define	MCIERR_WAVE_OUTPUTUNSPECIFIED	(MCIERR_BASE + 68)
#define	MCIERR_WAVE_INPUTUNSPECIFIED	(MCIERR_BASE + 69)
#define	MCIERR_WAVE_OUTPUTSUNSUITABLE	(MCIERR_BASE + 70)
#define	MCIERR_WAVE_SETOUTPUTUNSUITABLE	(MCIERR_BASE + 71)
#define	MCIERR_WAVE_INPUTSUNSUITABLE	(MCIERR_BASE + 72)
#define	MCIERR_WAVE_SETINPUTUNSUITABLE	(MCIERR_BASE + 73)
#define	MCIERR_SEQ_DIV_INCOMPATIBLE	(MCIERR_BASE + 80)
#define	MCIERR_SEQ_PORT_INUSE	(MCIERR_BASE + 81)
#define	MCIERR_SEQ_PORT_NONEXISTENT	(MCIERR_BASE + 82)
#define	MCIERR_SEQ_PORT_MAPNODEVICE	(MCIERR_BASE + 83)
#define	MCIERR_SEQ_PORT_MISCERROR	(MCIERR_BASE + 84)
#define	MCIERR_SEQ_TIMER	(MCIERR_BASE + 85)
#define	MCIERR_SEQ_PORTUNSPECIFIED	(MCIERR_BASE + 86)
#define	MCIERR_SEQ_NOMIDIPRESENT	(MCIERR_BASE + 87)
#define	MCIERR_NO_WINDOW	(MCIERR_BASE + 90)
#define	MCIERR_CREATEWINDOW	(MCIERR_BASE + 91)
#define	MCIERR_FILE_READ	(MCIERR_BASE + 92)
#define	MCIERR_FILE_WRITE	(MCIERR_BASE + 93)
#define	MCIERR_CUSTOM_DRIVER_BASE	(MCIERR_BASE + 256)
#define	MCI_OPEN	0x803
#define	MCI_CLOSE	0x804
#define	MCI_ESCAPE	0x805
#define	MCI_PLAY	0x806
#define	MCI_SEEK	0x807
#define	MCI_STOP	0x808
#define	MCI_PAUSE	0x809
#define	MCI_INFO	0x80A
#define	MCI_GETDEVCAPS	0x80B
#define	MCI_SPIN	0x80C
#define	MCI_SET	0x80D
#define	MCI_STEP	0x80E
#define	MCI_RECORD	0x80F
#define	MCI_SYSINFO	0x810
#define	MCI_BREAK	0x811
#define	MCI_SOUND	0x812
#define	MCI_SAVE	0x813
#define	MCI_STATUS	0x814
#define	MCI_CUE	0x830
#define	MCI_REALIZE	0x840
#define	MCI_WINDOW	0x841
#define	MCI_PUT	0x842
#define	MCI_WHERE	0x843
#define	MCI_FREEZE	0x844
#define	MCI_UNFREEZE	0x845
#define	MCI_LOAD	0x850
#define	MCI_CUT	0x851
#define	MCI_COPY	0x852
#define	MCI_PASTE	0x853
#define	MCI_UPDATE	0x854
#define	MCI_RESUME	0x855
#define	MCI_DELETE	0x856
#define	MCI_USER_MESSAGES	(0x400 + DRV_MCI_FIRST)
#define	MCI_ALL_DEVICE_ID	0xFFFF
#define	MCI_DEVTYPE_VCR	(MCI_STRING_OFFSET + 1)
#define	MCI_DEVTYPE_VIDEODISC	(MCI_STRING_OFFSET + 2)
#define	MCI_DEVTYPE_OVERLAY	(MCI_STRING_OFFSET + 3)
#define	MCI_DEVTYPE_CD_AUDIO	(MCI_STRING_OFFSET + 4)
#define	MCI_DEVTYPE_DAT	(MCI_STRING_OFFSET + 5)
#define	MCI_DEVTYPE_SCANNER	(MCI_STRING_OFFSET + 6)
#define	MCI_DEVTYPE_ANIMATION	(MCI_STRING_OFFSET + 7)
#define	MCI_DEVTYPE_DIGITAL_VIDEO	(MCI_STRING_OFFSET + 8)
#define	MCI_DEVTYPE_OTHER	(MCI_STRING_OFFSET + 9)
#define	MCI_DEVTYPE_WAVEFORM_AUDIO	(MCI_STRING_OFFSET + 10)
#define	MCI_DEVTYPE_SEQUENCER	(MCI_STRING_OFFSET + 11)
#define	MCI_DEVTYPE_FIRST	MCI_DEVTYPE_VCR
#define	MCI_DEVTYPE_LAST	MCI_DEVTYPE_SEQUENCER
#define	MCI_MODE_NOT_READY	(MCI_STRING_OFFSET + 12)
#define	MCI_MODE_STOP	(MCI_STRING_OFFSET + 13)
#define	MCI_MODE_PLAY	(MCI_STRING_OFFSET + 14)
#define	MCI_MODE_RECORD	(MCI_STRING_OFFSET + 15)
#define	MCI_MODE_SEEK	(MCI_STRING_OFFSET + 16)
#define	MCI_MODE_PAUSE	(MCI_STRING_OFFSET + 17)
#define	MCI_MODE_OPEN	(MCI_STRING_OFFSET + 18)
#define	MCI_FORMAT_MILLISECONDS	0
#define	MCI_FORMAT_HMS	1
#define	MCI_FORMAT_MSF	2
#define	MCI_FORMAT_FRAMES	3
#define	MCI_FORMAT_SMPTE_24	4
#define	MCI_FORMAT_SMPTE_25	5
#define	MCI_FORMAT_SMPTE_30	6
#define	MCI_FORMAT_SMPTE_30DROP	7
#define	MCI_FORMAT_BYTES	8
#define	MCI_FORMAT_SAMPLES	9
#define	MCI_FORMAT_TMSF	10
#define	MCI_MSF_MINUTE(t)	((BYTE)(t))
#define	MCI_MSF_SECOND(t)	((BYTE)(((WORD)(t))>>8))
#define	MCI_MSF_FRAME(t)	((BYTE)((t)>>16))
#define	MCI_MAKE_MSF(m,s,f)	((DWORD)(((BYTE)(m)|((WORD)(s)<<8))|(((DWORD)(BYTE)(f))<<16)))
#define	MCI_TMSF_TRACK(t)	((BYTE)(t))
#define	MCI_TMSF_MINUTE(t)	((BYTE)(((WORD)(t))>>8))
#define	MCI_TMSF_SECOND(t)	((BYTE)((t)>>16))
#define	MCI_TMSF_FRAME(t)	((BYTE)((t)>>24))
#define	MCI_MAKE_TMSF(t,m,s,f)	((DWORD)(((BYTE)(t)|((WORD)(m)<<8))|(((DWORD)(BYTE)(s)|((WORD)(f)<<8))<<16)))
#define	MCI_HMS_HOUR(t)	((BYTE)(t))
#define	MCI_HMS_MINUTE(t)	((BYTE)(((WORD)(t))>>8))
#define	MCI_HMS_SECOND(t)	((BYTE)((t)>>16))
#define	MCI_MAKE_HMS(h,m,s)	((DWORD)(((BYTE)(h)|((WORD)(m)<<8))|(((DWORD)(BYTE)(s))<<16)))
#define	MCI_NOTIFY_SUCCESSFUL	1
#define	MCI_NOTIFY_SUPERSEDED	2
#define	MCI_NOTIFY_ABORTED	4
#define	MCI_NOTIFY_FAILURE	8
#define	MCI_NOTIFY	1L
#define	MCI_WAIT	2L
#define	MCI_FROM	4L
#define	MCI_TO	8L
#define	MCI_TRACK	0x10L
#define	MCI_OPEN_SHAREABLE	0x100L
#define	MCI_OPEN_ELEMENT	0x200L
#define	MCI_OPEN_ALIAS	0x400L
#define	MCI_OPEN_ELEMENT_ID	0x800L
#define	MCI_OPEN_TYPE_ID	0x1000L
#define	MCI_OPEN_TYPE	0x2000L
#define	MCI_SEEK_TO_START	0x100L
#define	MCI_SEEK_TO_END	0x200L
#define	MCI_STATUS_ITEM	0x100L
#define	MCI_STATUS_START	0x200L
#define	MCI_STATUS_LENGTH	1L
#define	MCI_STATUS_POSITION	2L
#define	MCI_STATUS_NUMBER_OF_TRACKS	3L
#define	MCI_STATUS_MODE	4L
#define	MCI_STATUS_MEDIA_PRESENT	5L
#define	MCI_STATUS_TIME_FORMAT	6L
#define	MCI_STATUS_READY	7L
#define	MCI_STATUS_CURRENT_TRACK	8L
#define	MCI_INFO_PRODUCT	0x100L
#define	MCI_INFO_FILE	0x200L
#define	MCI_GETDEVCAPS_ITEM	0x100L
#define	MCI_GETDEVCAPS_CAN_RECORD	1L
#define	MCI_GETDEVCAPS_HAS_AUDIO	2L
#define	MCI_GETDEVCAPS_HAS_VIDEO	3L
#define	MCI_GETDEVCAPS_DEVICE_TYPE	4L
#define	MCI_GETDEVCAPS_USES_FILES	5L
#define	MCI_GETDEVCAPS_COMPOUND_DEVICE	6L
#define	MCI_GETDEVCAPS_CAN_EJECT	7L
#define	MCI_GETDEVCAPS_CAN_PLAY	8L
#define	MCI_GETDEVCAPS_CAN_SAVE	9L
#define	MCI_SYSINFO_QUANTITY	0x100L
#define	MCI_SYSINFO_OPEN	0x200L
#define	MCI_SYSINFO_NAME	0x400L
#define	MCI_SYSINFO_INSTALLNAME	0x800L
#define	MCI_SET_DOOR_OPEN	0x100L
#define	MCI_SET_DOOR_CLOSED	0x200L
#define	MCI_SET_TIME_FORMAT	0x400L
#define	MCI_SET_AUDIO	0x800L
#define	MCI_SET_VIDEO	0x1000L
#define	MCI_SET_ON	0x2000L
#define	MCI_SET_OFF	0x4000L
#define	MCI_SET_AUDIO_ALL	0
#define	MCI_SET_AUDIO_LEFT	1L
#define	MCI_SET_AUDIO_RIGHT	2L
#define	MCI_BREAK_KEY	0x100L
#define	MCI_BREAK_HWND	0x200L
#define	MCI_BREAK_OFF	0x400L
#define	MCI_RECORD_INSERT	0x100L
#define	MCI_RECORD_OVERWRITE	0x200L
#define	MCI_SOUND_NAME	0x100L
#define	MCI_SAVE_FILE	0x100L
#define	MCI_LOAD_FILE	0x100L
#define	MCI_VD_MODE_PARK	(MCI_VD_OFFSET + 1)
#define	MCI_VD_MEDIA_CLV	(MCI_VD_OFFSET + 2)
#define	MCI_VD_MEDIA_CAV	(MCI_VD_OFFSET + 3)
#define	MCI_VD_MEDIA_OTHER	(MCI_VD_OFFSET + 4)
#define	MCI_VD_FORMAT_TRACK	0x4001
#define	MCI_VD_PLAY_REVERSE	0x10000L
#define	MCI_VD_PLAY_FAST	0x20000L
#define	MCI_VD_PLAY_SPEED	0x40000L
#define	MCI_VD_PLAY_SCAN	0x80000L
#define	MCI_VD_PLAY_SLOW	0x100000L
#define	MCI_VD_SEEK_REVERSE	0x10000L
#define	MCI_VD_STATUS_SPEED	0x4002L
#define	MCI_VD_STATUS_FORWARD	0x4003L
#define	MCI_VD_STATUS_MEDIA_TYPE	0x4004L
#define	MCI_VD_STATUS_SIDE	0x4005L
#define	MCI_VD_STATUS_DISC_SIZE	0x4006L
#define	MCI_VD_GETDEVCAPS_CLV	0x10000L
#define	MCI_VD_GETDEVCAPS_CAV	0x20000L
#define	MCI_VD_SPIN_UP	0x10000L
#define	MCI_VD_SPIN_DOWN	0x20000L
#define	MCI_VD_GETDEVCAPS_CAN_REVERSE	0x4002L
#define	MCI_VD_GETDEVCAPS_FAST_RATE	0x4003L
#define	MCI_VD_GETDEVCAPS_SLOW_RATE	0x4004L
#define	MCI_VD_GETDEVCAPS_NORMAL_RATE	0x4005L
#define	MCI_VD_STEP_FRAMES	0x10000L
#define	MCI_VD_STEP_REVERSE	0x20000L
#define	MCI_VD_ESCAPE_STRING	0x100L
#define	MCI_WAVE_OPEN_BUFFER	0x10000L
#define	MCI_WAVE_SET_FORMATTAG	0x10000L
#define	MCI_WAVE_SET_CHANNELS	0x20000L
#define	MCI_WAVE_SET_SAMPLESPERSEC	0x40000L
#define	MCI_WAVE_SET_AVGBYTESPERSEC	0x80000L
#define	MCI_WAVE_SET_BLOCKALIGN	0x100000L
#define	MCI_WAVE_SET_BITSPERSAMPLE	0x200000L
#define	MCI_WAVE_INPUT	0x400000L
#define	MCI_WAVE_OUTPUT	0x800000L
#define	MCI_WAVE_STATUS_FORMATTAG	0x4001L
#define	MCI_WAVE_STATUS_CHANNELS	0x4002L
#define	MCI_WAVE_STATUS_SAMPLESPERSEC	0x4003L
#define	MCI_WAVE_STATUS_AVGBYTESPERSEC	0x4004L
#define	MCI_WAVE_STATUS_BLOCKALIGN	0x4005L
#define	MCI_WAVE_STATUS_BITSPERSAMPLE	0x4006L
#define	MCI_WAVE_STATUS_LEVEL	0x4007L
#define	MCI_WAVE_SET_ANYINPUT	0x4000000L
#define	MCI_WAVE_SET_ANYOUTPUT	0x8000000L
#define	MCI_WAVE_GETDEVCAPS_INPUTS	0x4001L
#define	MCI_WAVE_GETDEVCAPS_OUTPUTS	0x4002L
#define	MCI_SEQ_DIV_PPQN	(0 + MCI_SEQ_OFFSET)
#define	MCI_SEQ_DIV_SMPTE_24	(1 + MCI_SEQ_OFFSET)
#define	MCI_SEQ_DIV_SMPTE_25	(2 + MCI_SEQ_OFFSET)
#define	MCI_SEQ_DIV_SMPTE_30DROP	(3 + MCI_SEQ_OFFSET)
#define	MCI_SEQ_DIV_SMPTE_30	(4 + MCI_SEQ_OFFSET)
#define	MCI_SEQ_FORMAT_SONGPTR	0x4001
#define	MCI_SEQ_FILE	0x4002
#define	MCI_SEQ_MIDI	0x4003
#define	MCI_SEQ_SMPTE	0x4004
#define	MCI_SEQ_NONE	65533
#define	MCI_SEQ_STATUS_TEMPO	0x4002L
#define	MCI_SEQ_STATUS_PORT	0x4003L
#define	MCI_SEQ_STATUS_SLAVE	0x4007L
#define	MCI_SEQ_STATUS_MASTER	0x4008L
#define	MCI_SEQ_STATUS_OFFSET	0x4009L
#define	MCI_SEQ_STATUS_DIVTYPE	0x400AL
#define	MCI_SEQ_SET_TEMPO	0x10000L
#define	MCI_SEQ_SET_PORT	0x20000L
#define	MCI_SEQ_SET_SLAVE	0x40000L
#define	MCI_SEQ_SET_MASTER	0x80000L
#define	MCI_SEQ_SET_OFFSET	0x1000000L
#define	MCI_ANIM_OPEN_WS	0x10000L
#define	MCI_ANIM_OPEN_PARENT	0x20000L
#define	MCI_ANIM_OPEN_NOSTATIC	0x40000L
#define	MCI_ANIM_PLAY_SPEED	0x10000L
#define	MCI_ANIM_PLAY_REVERSE	0x20000L
#define	MCI_ANIM_PLAY_FAST	0x40000L
#define	MCI_ANIM_PLAY_SLOW	0x80000L
#define	MCI_ANIM_PLAY_SCAN	0x100000L
#define	MCI_ANIM_STEP_REVERSE	0x10000L
#define	MCI_ANIM_STEP_FRAMES	0x20000L
#define	MCI_ANIM_STATUS_SPEED	0x4001L
#define	MCI_ANIM_STATUS_FORWARD	0x4002L
#define	MCI_ANIM_STATUS_HWND	0x4003L
#define	MCI_ANIM_STATUS_HPAL	0x4004L
#define	MCI_ANIM_STATUS_STRETCH	0x4005L
#define	MCI_ANIM_INFO_TEXT	0x10000L
#define	MCI_ANIM_GETDEVCAPS_CAN_REVERSE	0x4001L
#define	MCI_ANIM_GETDEVCAPS_FAST_RATE	0x4002L
#define	MCI_ANIM_GETDEVCAPS_SLOW_RATE	0x4003L
#define	MCI_ANIM_GETDEVCAPS_NORMAL_RATE	0x4004L
#define	MCI_ANIM_GETDEVCAPS_PALETTES	0x4006L
#define	MCI_ANIM_GETDEVCAPS_CAN_STRETCH	0x4007L
#define	MCI_ANIM_GETDEVCAPS_MAX_WINDOWS	0x4008L
#define	MCI_ANIM_REALIZE_NORM	0x10000L
#define	MCI_ANIM_REALIZE_BKGD	0x20000L
#define	MCI_ANIM_WINDOW_HWND	0x10000L
#define	MCI_ANIM_WINDOW_STATE	0x40000L
#define	MCI_ANIM_WINDOW_TEXT	0x80000L
#define	MCI_ANIM_WINDOW_ENABLE_STRETCH	0x100000L
#define	MCI_ANIM_WINDOW_DISABLE_STRETCH	0x200000L
#define	MCI_ANIM_WINDOW_DEFAULT	0
#define	MCI_ANIM_RECT	0x10000L
#define	MCI_ANIM_PUT_SOURCE	0x20000L
#define	MCI_ANIM_PUT_DESTINATION	0x40000L
#define	MCI_ANIM_WHERE_SOURCE	0x20000L
#define	MCI_ANIM_WHERE_DESTINATION	0x40000L
#define	MCI_ANIM_UPDATE_HDC	0x20000L
#define	MCI_OVLY_OPEN_WS	0x10000L
#define	MCI_OVLY_OPEN_PARENT	0x20000L
#define	MCI_OVLY_STATUS_HWND	0x4001L
#define	MCI_OVLY_STATUS_STRETCH	0x4002L
#define	MCI_OVLY_INFO_TEXT	0x10000L
#define	MCI_OVLY_GETDEVCAPS_CAN_STRETCH	0x4001L
#define	MCI_OVLY_GETDEVCAPS_CAN_FREEZE	0x4002L
#define	MCI_OVLY_GETDEVCAPS_MAX_WINDOWS	0x4003L
#define	MCI_OVLY_WINDOW_HWND	0x10000L
#define	MCI_OVLY_WINDOW_STATE	0x40000L
#define	MCI_OVLY_WINDOW_TEXT	0x80000L
#define	MCI_OVLY_WINDOW_ENABLE_STRETCH	0x100000L
#define	MCI_OVLY_WINDOW_DISABLE_STRETCH	0x200000L
#define	MCI_OVLY_WINDOW_DEFAULT	0
#define	MCI_OVLY_RECT	0x10000L
#define	MCI_OVLY_PUT_SOURCE	0x20000L
#define	MCI_OVLY_PUT_DESTINATION	0x40000L
#define	MCI_OVLY_PUT_FRAME	0x80000L
#define	MCI_OVLY_PUT_VIDEO	0x100000L
#define	MCI_OVLY_WHERE_SOURCE	0x20000L
#define	MCI_OVLY_WHERE_DESTINATION	0x40000L
#define	MCI_OVLY_WHERE_FRAME	0x80000L
#define	MCI_OVLY_WHERE_VIDEO	0x100000L
#ifndef	C1_TRANSPARENT
#define	CAPS1	94
#define	C1_TRANSPARENT	1
#define	NEWTRANSPARENT	3
#define	QUERYROPSUPPORT	40
#endif
#define	SELECTDIB	41
#define	DIBINDEX(n)	MAKELONG((n),0x10FF)
#ifndef	SC_SCREENSAVE
#define	SC_SCREENSAVE	0xF140
#endif

#ifndef RC_INVOKED
DECLARE_HANDLE(HWAVE);
DECLARE_HANDLE(HWAVEIN);
DECLARE_HANDLE(HWAVEOUT);
DECLARE_HANDLE(HMIDI);
DECLARE_HANDLE(HMIDIIN);
DECLARE_HANDLE(HMIDIOUT);
DECLARE_HANDLE(HMMIO);

typedef	WORD	VERSION;
typedef	struct mmtime_tag {
	UINT	wType;
	union {
		DWORD	ms;
		DWORD	sample;
		DWORD	cb;
		struct {
			BYTE	hour;
			BYTE	min;
			BYTE	sec;
			BYTE	frame;
			BYTE	fps;
			BYTE	dummy;
		} smpte;
		struct {
			DWORD	songptrpos;
		} midi;
	} u;
} MMTIME,*PMMTIME,NEAR *NPMMTIME,FAR *LPMMTIME;
typedef	void (CALLBACK DRVCALLBACK)(HDRVR,UINT,DWORD,DWORD,DWORD);
typedef	DRVCALLBACK FAR *LPDRVCALLBACK;
typedef	HWAVEIN FAR *LPHWAVEIN;
typedef	HWAVEOUT FAR *LPHWAVEOUT;
typedef	DRVCALLBACK WAVECALLBACK;
typedef	WAVECALLBACK FAR *LPWAVECALLBACK;
typedef	struct wavehdr_tag {
	LPSTR	lpData;
	DWORD	dwBufferLength;
	DWORD	dwBytesRecorded;
	DWORD	dwUser;
	DWORD	dwFlags;
	DWORD	dwLoops;
	struct wavehdr_tag FAR *lpNext;
	DWORD	reserved;
} WAVEHDR,*PWAVEHDR,NEAR *NPWAVEHDR,FAR *LPWAVEHDR;
typedef	struct waveoutcaps_tag {
	UINT	wMid;
	UINT	wPid;
	VERSION	vDriverVersion;
	char	szPname[MAXPNAMELEN];
	DWORD	dwFormats;
	UINT	wChannels;
	DWORD	dwSupport;
} WAVEOUTCAPS,*PWAVEOUTCAPS,NEAR *NPWAVEOUTCAPS,FAR *LPWAVEOUTCAPS;
typedef	struct waveincaps_tag {
	UINT	wMid;
	UINT	wPid;
	VERSION	vDriverVersion;
	char	szPname[MAXPNAMELEN];
	DWORD	dwFormats;
	UINT	wChannels;
} WAVEINCAPS,*PWAVEINCAPS,NEAR *NPWAVEINCAPS,FAR *LPWAVEINCAPS;
typedef	struct waveformat_tag {
	WORD	wFormatTag;
	WORD	nChannels;
	DWORD	nSamplesPerSec;
	DWORD	nAvgBytesPerSec;
	WORD	nBlockAlign;
} WAVEFORMAT,*PWAVEFORMAT,NEAR *NPWAVEFORMAT,FAR *LPWAVEFORMAT;
typedef	struct pcmwaveformat_tag {
	WAVEFORMAT	wf;
	WORD	wBitsPerSample;
} PCMWAVEFORMAT,*PPCMWAVEFORMAT,NEAR *NPPCMWAVEFORMAT,FAR *LPPCMWAVEFORMAT;
typedef	HMIDIIN FAR *LPHMIDIIN;
typedef	HMIDIOUT FAR *LPHMIDIOUT;
typedef	DRVCALLBACK	MIDICALLBACK;
typedef	MIDICALLBACK FAR *LPMIDICALLBACK;
typedef	WORD	PATCHARRAY[MIDIPATCHSIZE];
typedef	WORD FAR *LPPATCHARRAY;
typedef	WORD	KEYARRAY[MIDIPATCHSIZE];
typedef	WORD FAR *LPKEYARRAY;
typedef	struct midioutcaps_tag {
	UINT	wMid;
	UINT	wPid;
	VERSION	vDriverVersion;
	char	szPname[MAXPNAMELEN];
	UINT	wTechnology;
	UINT	wVoices;
	UINT	wNotes;
	UINT	wChannelMask;
	DWORD	dwSupport;
} MIDIOUTCAPS,*PMIDIOUTCAPS,NEAR *NPMIDIOUTCAPS,FAR *LPMIDIOUTCAPS;
typedef	struct midiincaps_tag {
	UINT	wMid;
	UINT	wPid;
	VERSION	vDriverVersion;
	char	szPname[MAXPNAMELEN];
} MIDIINCAPS,*PMIDIINCAPS,NEAR *NPMIDIINCAPS,FAR *LPMIDIINCAPS;
typedef	struct midihdr_tag {
	LPSTR	lpData;
	DWORD	dwBufferLength;
	DWORD	dwBytesRecorded;
	DWORD	dwUser;
	DWORD	dwFlags;
	struct midihdr_tag FAR *lpNext;
	DWORD	reserved;
} MIDIHDR,*PMIDIHDR,NEAR *NPMIDIHDR,FAR *LPMIDIHDR;
typedef	struct auxcaps_tag {
	UINT	wMid;
	UINT	wPid;
	VERSION	vDriverVersion;
	char	szPname[MAXPNAMELEN];
	UINT	wTechnology;
	DWORD	dwSupport;
} AUXCAPS,*PAUXCAPS,NEAR *NPAUXCAPS,FAR *LPAUXCAPS;
typedef	void (CALLBACK TIMECALLBACK)(UINT,UINT,DWORD,DWORD,DWORD);
typedef	TIMECALLBACK FAR *LPTIMECALLBACK;
typedef	struct timecaps_tag {
	UINT	wPeriodMin;
	UINT	wPeriodMax;
} TIMECAPS,*PTIMECAPS,NEAR *NPTIMECAPS,FAR *LPTIMECAPS;
typedef	struct joycaps_tag {
	UINT	wMid;
	UINT	wPid;
	char	szPname[MAXPNAMELEN];
	UINT	wXmin;
	UINT	wXmax;
	UINT	wYmin;
	UINT	wYmax;
	UINT	wZmin;
	UINT	wZmax;
	UINT	wNumButtons;
	UINT	wPeriodMin;
	UINT	wPeriodMax;
} JOYCAPS,*PJOYCAPS,NEAR *NPJOYCAPS,FAR *LPJOYCAPS;
typedef	struct joyinfo_tag {
	UINT	wXpos;
	UINT	wYpos;
	UINT	wZpos;
	UINT	wButtons;
} JOYINFO,*PJOYINFO,NEAR *NPJOYINFO,FAR *LPJOYINFO;
typedef	DWORD	FOURCC;
typedef	char	_huge *	HPSTR;
typedef	LRESULT	(CALLBACK MMIOPROC)(LPSTR,UINT,LPARAM,LPARAM);
typedef	MMIOPROC FAR *LPMMIOPROC;
typedef	struct _MMIOINFO {
	DWORD	dwFlags;
	FOURCC	fccIOProc;
	LPMMIOPROC	pIOProc;
	UINT	wErrorRet;
	HTASK	htask;
	LONG	cchBuffer;
	HPSTR	pchBuffer;
	HPSTR	pchNext;
	HPSTR	pchEndRead;
	HPSTR	pchEndWrite;
	LONG	lBufOffset;
	LONG	lDiskOffset;
	DWORD	adwInfo[3];
	DWORD	dwReserved1;
	DWORD	dwReserved2;
	HMMIO	hmmio;
} MMIOINFO,*PMMIOINFO,NEAR *NPMMIOINFO,FAR *LPMMIOINFO;
typedef	struct _MMCKINFO {
	FOURCC	ckid;
	DWORD	cksize;
	FOURCC	fccType;
	DWORD	dwDataOffset;
	DWORD	dwFlags;
} MMCKINFO,*PMMCKINFO,NEAR *NPMMCKINFO,FAR *LPMMCKINFO;
typedef	UINT (CALLBACK *YIELDPROC)(UINT,DWORD);
typedef	struct tagMCI_GENERIC_PARMS {
	DWORD	dwCallback;
} MCI_GENERIC_PARMS,FAR *LPMCI_GENERIC_PARMS;
typedef	struct tagMCI_OPEN_PARMS {
	DWORD	dwCallback;
	UINT	wDeviceID;
	UINT	wReserved0;
	LPCSTR	lpstrDeviceType;
	LPCSTR	lpstrElementName;
	LPCSTR	lpstrAlias;
} MCI_OPEN_PARMS,FAR *LPMCI_OPEN_PARMS;
typedef	struct tagMCI_PLAY_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrom;
	DWORD	dwTo;
} MCI_PLAY_PARMS,FAR *LPMCI_PLAY_PARMS;
typedef	struct tagMCI_SEEK_PARMS {
	DWORD	dwCallback;
	DWORD	dwTo;
} MCI_SEEK_PARMS,FAR *LPMCI_SEEK_PARMS;
typedef	struct tagMCI_STATUS_PARMS {
	DWORD	dwCallback;
	DWORD	dwReturn;
	DWORD	dwItem;
	DWORD	dwTrack;
} MCI_STATUS_PARMS,FAR *LPMCI_STATUS_PARMS;
typedef	struct tagMCI_INFO_PARMS {
	DWORD	dwCallback;
	LPSTR	lpstrReturn;
	DWORD	dwRetSize;
} MCI_INFO_PARMS,FAR *LPMCI_INFO_PARMS;
typedef	struct tagMCI_GETDEVCAPS_PARMS {
	DWORD	dwCallback;
	DWORD	dwReturn;
	DWORD	dwItem;
} MCI_GETDEVCAPS_PARMS,FAR *LPMCI_GETDEVCAPS_PARMS;
typedef	struct tagMCI_SYSINFO_PARMS {
	DWORD	dwCallback;
	LPSTR	lpstrReturn;
	DWORD	dwRetSize;
	DWORD	dwNumber;
	UINT	wDeviceType;
	UINT	wReserved0;
} MCI_SYSINFO_PARMS,FAR *LPMCI_SYSINFO_PARMS;
typedef	struct tagMCI_SET_PARMS {
	DWORD	dwCallback;
	DWORD	dwTimeFormat;
	DWORD	dwAudio;
} MCI_SET_PARMS,FAR *LPMCI_SET_PARMS;
typedef	struct tagMCI_BREAK_PARMS {
	DWORD	dwCallback;
	int	nVirtKey;
	UINT	wReserved0;
	HWND	hwndBreak;
	UINT	wReserved1;
} MCI_BREAK_PARMS,FAR *LPMCI_BREAK_PARMS;
typedef	struct tagMCI_SOUND_PARMS {
	DWORD	dwCallback;
	LPCSTR	lpstrSoundName;
} MCI_SOUND_PARMS,FAR *LPMCI_SOUND_PARMS;
typedef	struct tagMCI_SAVE_PARMS {
	DWORD	dwCallback;
	LPCSTR	lpfilename;
} MCI_SAVE_PARMS,FAR *LPMCI_SAVE_PARMS;
typedef	struct tagMCI_LOAD_PARMS {
	DWORD	dwCallback;
	LPCSTR	lpfilename;
} MCI_LOAD_PARMS,FAR *LPMCI_LOAD_PARMS;
typedef	struct tagMCI_RECORD_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrom;
	DWORD	dwTo;
} MCI_RECORD_PARMS,FAR *LPMCI_RECORD_PARMS;
typedef	struct tagMCI_VD_PLAY_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrom;
	DWORD	dwTo;
	DWORD	dwSpeed;
} MCI_VD_PLAY_PARMS,FAR *LPMCI_VD_PLAY_PARMS;
typedef	struct tagMCI_VD_STEP_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrames;
} MCI_VD_STEP_PARMS,FAR *LPMCI_VD_STEP_PARMS;
typedef	struct tagMCI_VD_ESCAPE_PARMS {
	DWORD	dwCallback;
	LPCSTR	lpstrCommand;
} MCI_VD_ESCAPE_PARMS,FAR *LPMCI_VD_ESCAPE_PARMS;
typedef	struct tagMCI_WAVE_OPEN_PARMS {
	DWORD	dwCallback;
	UINT	wDeviceID;
	UINT	wReserved0;
	LPCSTR	lpstrDeviceType;
	LPCSTR	lpstrElementName;
	LPCSTR	lpstrAlias;
	DWORD	dwBufferSeconds;
} MCI_WAVE_OPEN_PARMS,FAR *LPMCI_WAVE_OPEN_PARMS;
typedef	struct tagMCI_WAVE_DELETE_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrom;
	DWORD	dwTo;
} MCI_WAVE_DELETE_PARMS,FAR *LPMCI_WAVE_DELETE_PARMS;
typedef	struct tagMCI_WAVE_SET_PARMS {
	DWORD	dwCallback;
	DWORD	dwTimeFormat;
	DWORD	dwAudio;
	UINT	wInput;
	UINT	wReserved0;
	UINT	wOutput;
	UINT	wReserved1;
	UINT	wFormatTag;
	UINT	wReserved2;
	UINT	nChannels;
	UINT	wReserved3;
	DWORD	nSamplesPerSec;
	DWORD	nAvgBytesPerSec;
	UINT	nBlockAlign;
	UINT	wReserved4;
	UINT	wBitsPerSample;
	UINT	wReserved5;
} MCI_WAVE_SET_PARMS,FAR *LPMCI_WAVE_SET_PARMS;
typedef	struct tagMCI_SEQ_SET_PARMS {
	DWORD	dwCallback;
	DWORD	dwTimeFormat;
	DWORD	dwAudio;
	DWORD	dwTempo;
	DWORD	dwPort;
	DWORD	dwSlave;
	DWORD	dwMaster;
	DWORD	dwOffset;
} MCI_SEQ_SET_PARMS,FAR *LPMCI_SEQ_SET_PARMS;
typedef	struct tagMCI_ANIM_OPEN_PARMS {
	DWORD	dwCallback;
	UINT	wDeviceID;
	UINT	wReserved0;
	LPCSTR	lpstrDeviceType;
	LPCSTR	lpstrElementName;
	LPCSTR	lpstrAlias;
	DWORD	dwStyle;
	HWND	hWndParent;
	UINT	wReserved1;
} MCI_ANIM_OPEN_PARMS,FAR *LPMCI_ANIM_OPEN_PARMS;
typedef	struct tagMCI_ANIM_PLAY_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrom;
	DWORD	dwTo;
	DWORD	dwSpeed;
} MCI_ANIM_PLAY_PARMS,FAR *LPMCI_ANIM_PLAY_PARMS;
typedef	struct tagMCI_ANIM_STEP_PARMS {
	DWORD	dwCallback;
	DWORD	dwFrames;
} MCI_ANIM_STEP_PARMS,FAR *LPMCI_ANIM_STEP_PARMS;
typedef	struct tagMCI_ANIM_WINDOW_PARMS {
	DWORD	dwCallback;
	HWND	hWnd;
	UINT	wReserved1;
	UINT	nCmdShow;
	UINT	wReserved2;
	LPCSTR	lpstrText;
} MCI_ANIM_WINDOW_PARMS,FAR *LPMCI_ANIM_WINDOW_PARMS;
typedef	struct tagMCI_ANIM_RECT_PARMS {
	DWORD	dwCallback;
#ifdef	MCI_USE_OFFEXT
	POINT	ptOffset;
	POINT	ptExtent;
#else
	RECT	rc;
#endif
} MCI_ANIM_RECT_PARMS,FAR *LPMCI_ANIM_RECT_PARMS;
typedef	struct tagMCI_ANIM_UPDATE_PARMS {
	DWORD	dwCallback;
	RECT	rc;
	HDC	hDC;
} MCI_ANIM_UPDATE_PARMS,FAR *LPMCI_ANIM_UPDATE_PARMS;
typedef	struct tagMCI_OVLY_OPEN_PARMS {
	DWORD	dwCallback;
	UINT	wDeviceID;
	UINT	wReserved0;
	LPCSTR	lpstrDeviceType;
	LPCSTR	lpstrElementName;
	LPCSTR	lpstrAlias;
	DWORD	dwStyle;
	HWND	hWndParent;
	UINT	wReserved1;
} MCI_OVLY_OPEN_PARMS,FAR *LPMCI_OVLY_OPEN_PARMS;
typedef	struct tagMCI_OVLY_WINDOW_PARMS {
	DWORD	dwCallback;
	HWND	hWnd;
	UINT	wReserved1;
	UINT	nCmdShow;
	UINT	wReserved2;
	LPCSTR	lpstrText;
} MCI_OVLY_WINDOW_PARMS,FAR *LPMCI_OVLY_WINDOW_PARMS;
typedef	struct tagMCI_OVLY_RECT_PARMS {
	DWORD	dwCallback;
#ifdef	MCI_USE_OFFEXT
	POINT	ptOffset;
	POINT	ptExtent;
#else
	RECT	rc;
#endif
} MCI_OVLY_RECT_PARMS,FAR *LPMCI_OVLY_RECT_PARMS;
typedef	struct tagMCI_OVLY_SAVE_PARMS {
	DWORD	dwCallback;
	LPCSTR	lpfilename;
	RECT	rc;
} MCI_OVLY_SAVE_PARMS,FAR *LPMCI_OVLY_SAVE_PARMS;
typedef	struct tagMCI_OVLY_LOAD_PARMS {
	DWORD	dwCallback;
	LPCSTR	lpfilename;
	RECT	rc;
} MCI_OVLY_LOAD_PARMS,FAR *LPMCI_OVLY_LOAD_PARMS;

WORD	WINAPI mmsystemGetVersion(void);
void	WINAPI OutputDebugStr(LPCSTR);
BOOL	WINAPI sndPlaySound(LPCSTR,UINT);
UINT	WINAPI waveOutGetNumDevs(void);
UINT	WINAPI waveOutGetDevCaps(UINT,WAVEOUTCAPS FAR*,UINT);
UINT	WINAPI waveOutGetVolume(UINT,DWORD FAR*);
UINT	WINAPI waveOutSetVolume(UINT,DWORD);
UINT	WINAPI waveOutGetErrorText(UINT,LPSTR,UINT);
UINT	WINAPI waveOutOpen(HWAVEOUT FAR*,UINT,const WAVEFORMAT FAR*,DWORD,DWORD,DWORD);
UINT	WINAPI waveOutClose(HWAVEOUT);
UINT	WINAPI waveOutPrepareHeader(HWAVEOUT,WAVEHDR FAR*,UINT);
UINT	WINAPI waveOutUnprepareHeader(HWAVEOUT,WAVEHDR FAR*,UINT);
UINT	WINAPI waveOutWrite(HWAVEOUT,WAVEHDR FAR*,UINT);
UINT	WINAPI waveOutPause(HWAVEOUT);
UINT	WINAPI waveOutRestart(HWAVEOUT);
UINT	WINAPI waveOutReset(HWAVEOUT);
UINT	WINAPI waveOutBreakLoop(HWAVEOUT);
UINT	WINAPI waveOutGetPosition(HWAVEOUT,MMTIME FAR*,UINT);
UINT	WINAPI waveOutGetPitch(HWAVEOUT,DWORD FAR*);
UINT	WINAPI waveOutSetPitch(HWAVEOUT,DWORD);
UINT	WINAPI waveOutGetPlaybackRate(HWAVEOUT,DWORD FAR*);
UINT	WINAPI waveOutSetPlaybackRate(HWAVEOUT,DWORD);
UINT	WINAPI waveOutGetID(HWAVEOUT,UINT FAR*);
UINT	WINAPI waveInGetNumDevs(void);
UINT	WINAPI waveInGetDevCaps(UINT,WAVEINCAPS FAR*,UINT);
UINT	WINAPI waveInGetErrorText(UINT,LPSTR,UINT);
UINT	WINAPI waveInOpen(HWAVEIN FAR*,UINT,const WAVEFORMAT FAR*,DWORD,DWORD,DWORD);
UINT	WINAPI waveInClose(HWAVEIN);
UINT	WINAPI waveInPrepareHeader(HWAVEIN,WAVEHDR FAR*,UINT);
UINT	WINAPI waveInUnprepareHeader(HWAVEIN,WAVEHDR FAR*,UINT);
UINT	WINAPI waveInAddBuffer(HWAVEIN,WAVEHDR FAR*,UINT);
UINT	WINAPI waveInStart(HWAVEIN);
UINT	WINAPI waveInStop(HWAVEIN);
UINT	WINAPI waveInReset(HWAVEIN);
UINT	WINAPI waveInGetPosition(HWAVEIN,MMTIME FAR*,UINT);
UINT	WINAPI waveInGetID(HWAVEIN,UINT FAR*);
#if (WINVER >= 0x30a)
DWORD	WINAPI waveOutMessage(HWAVEOUT,UINT,DWORD,DWORD);
DWORD	WINAPI waveInMessage(HWAVEIN,UINT,DWORD,DWORD);
#endif
UINT	WINAPI midiOutGetNumDevs(void);
UINT	WINAPI midiOutGetDevCaps(UINT,MIDIOUTCAPS FAR*,UINT);
UINT	WINAPI midiOutGetVolume(UINT,DWORD FAR*);
UINT	WINAPI midiOutSetVolume(UINT,DWORD);
UINT	WINAPI midiOutGetErrorText(UINT,LPSTR,UINT);
UINT	WINAPI midiOutOpen(HMIDIOUT FAR*,UINT,DWORD,DWORD,DWORD);
UINT	WINAPI midiOutClose(HMIDIOUT);
UINT	WINAPI midiOutPrepareHeader(HMIDIOUT,MIDIHDR FAR*,UINT);
UINT	WINAPI midiOutUnprepareHeader(HMIDIOUT,MIDIHDR FAR*,UINT);
UINT	WINAPI midiOutShortMsg(HMIDIOUT,DWORD);
UINT	WINAPI midiOutLongMsg(HMIDIOUT,MIDIHDR FAR*,UINT);
UINT	WINAPI midiOutReset(HMIDIOUT);
UINT	WINAPI midiOutCachePatches(HMIDIOUT,UINT,WORD FAR*,UINT);
UINT	WINAPI midiOutCacheDrumPatches(HMIDIOUT,UINT,WORD FAR*,UINT);
UINT	WINAPI midiOutGetID(HMIDIOUT,UINT FAR*);
UINT	WINAPI midiInGetNumDevs(void);
UINT	WINAPI midiInGetDevCaps(UINT,LPMIDIINCAPS,UINT);
UINT	WINAPI midiInGetErrorText(UINT,LPSTR,UINT);
UINT	WINAPI midiInOpen(HMIDIIN FAR*,UINT,DWORD,DWORD,DWORD);
UINT	WINAPI midiInClose(HMIDIIN);
UINT	WINAPI midiInPrepareHeader(HMIDIIN,MIDIHDR FAR*,UINT);
UINT	WINAPI midiInUnprepareHeader(HMIDIIN,MIDIHDR FAR*,UINT);
UINT	WINAPI midiInAddBuffer(HMIDIIN,MIDIHDR FAR*,UINT);
UINT	WINAPI midiInStart(HMIDIIN);
UINT	WINAPI midiInStop(HMIDIIN);
UINT	WINAPI midiInReset(HMIDIIN);
UINT	WINAPI midiInGetID(HMIDIIN,UINT FAR*);
#if (WINVER >= 0x30a)
DWORD	WINAPI midiOutMessage(HMIDIOUT,UINT,DWORD,DWORD);
DWORD	WINAPI midiInMessage(HMIDIIN,UINT,DWORD,DWORD);
#endif
UINT	WINAPI auxGetNumDevs(void);
UINT	WINAPI auxGetDevCaps(UINT,AUXCAPS FAR*,UINT);
UINT	WINAPI auxSetVolume(UINT,DWORD);
UINT	WINAPI auxGetVolume(UINT,DWORD FAR*);
#if (WINVER >= 0x30a)
DWORD	WINAPI auxOutMessage(UINT,UINT,DWORD,DWORD);
#endif
UINT	WINAPI timeGetSystemTime(MMTIME FAR*,UINT);
DWORD	WINAPI timeGetTime(void);
UINT	WINAPI timeSetEvent(UINT,UINT,LPTIMECALLBACK,DWORD,UINT);
UINT	WINAPI timeKillEvent(UINT);
UINT	WINAPI timeGetDevCaps(TIMECAPS FAR*,UINT);
UINT	WINAPI timeBeginPeriod(UINT);
UINT	WINAPI timeEndPeriod(UINT);
UINT	WINAPI joyGetDevCaps(UINT,JOYCAPS FAR*,UINT);
UINT	WINAPI joyGetNumDevs(void);
UINT	WINAPI joyGetPos(UINT,JOYINFO FAR*);
UINT	WINAPI joyGetThreshold(UINT,UINT FAR*);
UINT	WINAPI joyReleaseCapture(UINT);
UINT	WINAPI joySetCapture(HWND,UINT,UINT,BOOL);
UINT	WINAPI joySetThreshold(UINT,UINT);
FOURCC	WINAPI mmioStringToFOURCC(LPCSTR,UINT);
LPMMIOPROC	WINAPI mmioInstallIOProc(FOURCC,LPMMIOPROC,DWORD);
HMMIO	WINAPI mmioOpen(LPSTR,MMIOINFO FAR*,DWORD);
UINT	WINAPI mmioClose(HMMIO,UINT);
LONG	WINAPI mmioRead(HMMIO,HPSTR,LONG);
LONG	WINAPI mmioWrite(HMMIO,const char _huge*,LONG);
LONG	WINAPI mmioSeek(HMMIO,LONG,int);
UINT	WINAPI mmioGetInfo(HMMIO,MMIOINFO FAR*,UINT);
UINT	WINAPI mmioSetInfo(HMMIO,const MMIOINFO FAR*,UINT);
UINT	WINAPI mmioSetBuffer(HMMIO,LPSTR,LONG,UINT);
UINT	WINAPI mmioFlush(HMMIO,UINT);
UINT	WINAPI mmioAdvance(HMMIO,MMIOINFO FAR*,UINT);
LRESULT	WINAPI mmioSendMessage(HMMIO,UINT,LPARAM,LPARAM);
UINT	WINAPI mmioDescend(HMMIO,MMCKINFO FAR*,const MMCKINFO FAR*,UINT);
UINT	WINAPI mmioAscend(HMMIO,MMCKINFO FAR*,UINT);
UINT	WINAPI mmioCreateChunk(HMMIO,MMCKINFO FAR*,UINT);
#if (WINVER >= 0x30a)
UINT	WINAPI mmioRename(LPCSTR,LPCSTR,MMIOINFO FAR*,DWORD);
#endif
DWORD	WINAPI mciSendCommand(UINT,UINT,DWORD,DWORD);
DWORD	WINAPI mciSendString(LPCSTR,LPSTR,UINT,HWND);
UINT	WINAPI mciGetDeviceID(LPCSTR);
UINT	WINAPI mciGetDeviceIDFromElementID(DWORD,LPCSTR);
BOOL	WINAPI mciGetErrorString(DWORD,LPSTR,UINT);
BOOL	WINAPI mciSetYieldProc(UINT,YIELDPROC,DWORD);
#if (WINVER >= 0x30a)
HTASK	WINAPI mciGetCreatorTask(UINT);
YIELDPROC	WINAPI mciGetYieldProc(UINT,DWORD FAR*);
#endif
#endif /* RC_INVOKED */

#pragma	pack(pop)

#ifdef	__cplusplus
}
#endif

#endif

