/*
    OS/2 Multimedia Extensions common definitions.
*/

#ifndef  __OS2MEDEF_H__
#define  __OS2MEDEF_H__

#ifndef __WORDBYTEDWORD__
  #define __WORDBYTEDWORD__
  #ifndef WORD
    typedef USHORT WORD;
  #endif
  #ifndef DWORD
    typedef ULONG  DWORD;
  #endif
#endif

typedef WORD  VERSION;
typedef char FAR *LPSTR;
typedef FAR *LPTR;
typedef FAR *LPRECT;
typedef HWND HANDLE;
typedef WORD *PW;
typedef WORD *PAW;
typedef WORD *PWORD;
typedef PFN FAR *PPFN;
typedef DWORD (APIENTRY FNMCI)(LPTR,WORD,DWORD,DWORD,WORD);
typedef FNMCI *PFNMCI;

typedef char   SZ;
typedef ULONG  MMTIME;
typedef MMTIME FAR *PMMTIME;

typedef ULONG HMMIO;
typedef HMMIO FAR *PHMMIO;

typedef struct _SPCBKEY {
    ULONG ulDataType;
    ULONG ulDataSubType;
    ULONG ulIntKey;
} SPCBKEY, FAR *PSPCBKEY;

#define  _SPCBKEY_DEFINED 1

typedef struct _MMTRACKINFO {
    ULONG ulTrackID;
    ULONG ulMediaType;
    ULONG ulCountry;
    ULONG ulCodePage;
    ULONG ulReserved1;
    ULONG ulReserved2;
} MMTRACKINFO, *PMMTRACKINFO;

#define CF_RMID 10
#define CF_RIFF 11
#define CF_WAVE 12
#define CF_AVI  13

#define RT_RMID 100
#define RT_RIFF 101
#define RT_WAVE 102
#define RT_AVI  103
#define RT_AVS  104

#define DRT_WAVE "Digital audio"
#define DRT_AVI  "Digital video"
#define DRT_MIDI "MIDI"

#define HZ_8000  8000
#define HZ_11025 11025
#define HZ_14700 14700
#define HZ_18900 18900
#define HZ_22050 22050
#define HZ_37800 37800
#define HZ_44100 44100

#define BPS_4  4
#define BPS_8  8
#define BPS_16 16

#define CH_1 1
#define CH_2 2
#define CH_4 4

#define DATATYPE_NULL 0
#define SUBTYPE_NONE  0

#define DATATYPE_WAVEFORM 1

#define WAVE_FORMAT_1M08 0x0001
#define WAVE_FORMAT_1S08 0x0002
#define WAVE_FORMAT_1M16 0x0003
#define WAVE_FORMAT_1S16 0x0004
#define WAVE_FORMAT_2M08 0x0005
#define WAVE_FORMAT_2S08 0x0006
#define WAVE_FORMAT_2M16 0x0007
#define WAVE_FORMAT_2S16 0x0008
#define WAVE_FORMAT_4M08 0x0009
#define WAVE_FORMAT_4S08 0x000a
#define WAVE_FORMAT_4M16 0x000b
#define WAVE_FORMAT_4S16 0x000c
#define WAVE_FORMAT_8M08 0x000d
#define WAVE_FORMAT_8S08 0x000e
#define WAVE_FORMAT_8M16 0x000f
#define WAVE_FORMAT_8S16 0x0010

#define DATATYPE_DIGVIDEO 2

#define DIGVIDEO_PHOTOM  0x544F4850
#define DIGVIDEO_ULTIM   0x49544c55
#define DIGVIDEO_AVI     0x20495641
#define DIGVIDEO_MONITOR 0x206E6F6D
#define DIGVIDEO_FLC     0x63696C66
#define DIGVIDEO_MPEG    0x4745504D

#define DATATYPE_MULAW 0x0101
#define DATATYPE_RIFF_MULAW 7

#define MULAW_8B8KS  1
#define MULAW_8B11KS 2
#define MULAW_8B22KS 3
#define MULAW_8B44KS 4
#define MULAW_8B8KM  5
#define MULAW_8B11KM 6
#define MULAW_8B22KM 7
#define MULAW_8B44KM 8

#define DATATYPE_ALAW 0x0102
#define DATATYPE_RIFF_ALAW 6

#define ALAW_8B8KS  1
#define ALAW_8B11KS 2
#define ALAW_8B22KS 3
#define ALAW_8B44KS 4
#define ALAW_8B8KM  5
#define ALAW_8B11KM 6
#define ALAW_8B22KM 7
#define ALAW_8B44KM 8

#define DATATYPE_ADPCM_AVC 0x0103

#define ADPCM_AVC_VOICE  1
#define ADPCM_AVC_MUSIC  2
#define ADPCM_AVC_STEREO 3
#define ADPCM_AVC_HQ     4

#define DATATYPE_CT_ADPCM 0x0200

#define CT_ADPCM_16B8KS  1
#define CT_ADPCM_16B11KS 2
#define CT_ADPCM_16B22KS 3
#define CT_ADPCM_16B44KS 4
#define CT_ADPCM_16B8KM  5
#define CT_ADPCM_16B11KM 6
#define CT_ADPCM_16B22KM 7
#define CT_ADPCM_16B44KM 8

#define DATATYPE_MIDI    0x0201
#define DATATYPE_GENERIC 0x0202
#define DATATYPE_SPV2    0x0203

#define SPV2_BPCM 1
#define SPV2_PCM  2
#define SPV2_NONE 3

#define DATATYPE_CDXA_VIDEO    0x0204
#define DATATYPE_CDXA_DATA     0x0205
#define DATATYPE_CDXA_AUDIO    0x0206
#define DATATYPE_CDXA_AUDIO_HD 0x0207
#define DATATYPE_CDXA_HEADERS  0x0208

#define CDXA_LEVELB      0
#define CDXA_LEVELC      1
#define CDXA_LEVELB_MONO 2
#define CDXA_LEVELC_MONO 3

#define DATATYPE_DIGISPEECH 0x0208
#define DIGISPEECH_NATIVE 1

#define DATATYPE_MPEG1AUDIO 0x0050

#define MPEG1_FORMAT_3M16 1
#define MPEG1_FORMAT_3S16 2
#define MPEG1_FORMAT_4M16 3
#define MPEG1_FORMAT_4S16 4

#define DATATYPE_UNKNOWN 0xFFFFFFFF

#endif

