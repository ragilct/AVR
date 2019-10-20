/*
Custom char set for alphanumeric LCD Module
LCD Custom Char Builder!

*/

#ifndef __CUSTOMCHAR_H
#define __CUSTOMCHAR_H

unsigned char __cgram[]=
{
	0x00, 0x00, 0x04, 0x0E, 0x04, 0x00, 0x00, 0x00, //Char0 DOT Small
	0x00, 0x04, 0x0E, 0x1F, 0x0E, 0x04, 0x00, 0x00, //Char1 DOT Big
	0x00, 0x01, 0x01, 0x05, 0x05, 0x15, 0x15, 0x00, //Char2 3
	0x00, 0x00, 0x00, 0x04, 0x04, 0x14, 0x14, 0x00, //Char3 2
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, //Char4 1
	0x1F, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, //Char5 Tower
	0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, //Char6 X
	0x1E, 0x1F, 0x1F, 0x1F, 0x11, 0x1F, 0x1F, 0x00, //Char7 SIM
};
#endif

