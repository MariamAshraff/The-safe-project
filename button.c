/*
 * BUTTON.c
 *
 * Created: 10/13/2023 6:16:17 AM
 *  Author: VTE
 */ 
#include "DIO.h"
void button_vInit(unsigned char portname,unsigned char pinnumber)
{
	DIO_vsetPINDir(portname,pinnumber);
}
unsigned char button_u8read(unsigned char portname,unsigned char pinnumber)
{
	unsigned char x;
	x=DIO_u8read(portname,pinnumber);
	return x ;
}
