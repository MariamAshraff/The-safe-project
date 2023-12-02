/*
 * BUTTON.h
 *
 * Created: 10/13/2023 6:16:51 AM
 *  Author: VTE
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


void button_vInit(unsigned char portname,unsigned char pinnumber);
unsigned char button_u8read(unsigned char portname,unsigned char pinnumber);


#endif /* BUTTON_H_ */