/*

	dinput_joy2.c - DirectInput Joystick 2 DATAFORMAT

	Written by Filip Navara <xnavara@volny.cz>

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/

#include "dinput_private.h"

static DIOBJECTDATAFORMAT c_rgodfDIJoy2[] SECTION_TEXT =
{
	{&GUID_XAxis,0x0,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_YAxis,0x4,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_ZAxis,0x8,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_RxAxis,0xc,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_RyAxis,0x10,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_RzAxis,0x14,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_Slider,0x18,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_Slider,0x1c,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTPOSITION},
	{&GUID_POV,0x20,DIDFT_POV|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{&GUID_POV,0x24,DIDFT_POV|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{&GUID_POV,0x28,DIDFT_POV|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{&GUID_POV,0x2c,DIDFT_POV|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x30,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x31,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x32,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x33,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x34,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x35,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x36,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x37,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x38,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x39,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x3a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x3b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x3c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x3d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x3e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x3f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x40,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x41,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x42,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x43,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x44,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x45,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x46,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x47,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x48,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x49,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x4a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x4b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x4c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x4d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x4e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x4f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x50,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x51,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x52,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x53,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x54,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x55,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x56,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x57,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x58,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x59,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x5a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x5b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x5c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x5d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x5e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x5f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x60,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x61,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x62,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x63,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x64,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x65,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x66,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x67,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x68,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x69,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x6a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x6b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x6c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x6d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x6e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x6f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x70,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x71,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x72,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x73,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x74,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x75,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x76,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x77,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x78,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x79,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x7a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x7b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x7c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x7d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x7e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x7f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x80,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x81,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x82,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x83,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x84,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x85,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x86,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x87,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x88,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x89,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x8a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x8b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x8c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x8d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x8e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x8f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x90,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x91,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x92,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x93,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x94,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x95,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x96,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x97,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x98,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x99,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x9a,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x9b,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x9c,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x9d,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x9e,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0x9f,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa0,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa1,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa2,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa3,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa4,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa5,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa6,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa7,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa8,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xa9,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xaa,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xab,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xac,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xad,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xae,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{NULL,0xaf,DIDFT_BUTTON|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,0x0},
	{&GUID_XAxis,0xb0,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_YAxis,0xb4,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_ZAxis,0xb8,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_RxAxis,0xbc,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_RyAxis,0xc0,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_RzAxis,0xc4,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_Slider,0x18,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_Slider,0x1c,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTVELOCITY},
	{&GUID_XAxis,0xd0,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_YAxis,0xd4,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_ZAxis,0xd8,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_RxAxis,0xdc,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_RyAxis,0xe0,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_RzAxis,0xe4,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_Slider,0x18,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_Slider,0x1c,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTACCEL},
	{&GUID_XAxis,0xf0,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_YAxis,0xf4,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_ZAxis,0xf8,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_RxAxis,0xfc,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_RyAxis,0x100,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_RzAxis,0x104,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_Slider,0x18,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE},
	{&GUID_Slider,0x1c,DIDFT_ABSAXIS|DIDFT_RELAXIS|DIDFT_ANYINSTANCE|DIDFT_OPTIONAL,DIDOI_ASPECTFORCE}
};

DIDATAFORMAT c_dfDIJoystick2 SECTION_RDATA = {sizeof(DIDATAFORMAT),sizeof(DIOBJECTDATAFORMAT),DIDF_ABSAXIS,272,sizeof(c_rgodfDIJoy2)/sizeof(c_rgodfDIJoy2[0]),c_rgodfDIJoy2};
