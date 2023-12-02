/*
 * keypad.c
 *
 * Created: 11/7/2023 11:51:36 PM
 *  Author: VTE
 */ 
#include "keypad.h"
void keypad_vInit(){
	DIO_vsetPINDir(keypadPort,0,1);
	DIO_vsetPINDir(keypadPort,1,1);
	DIO_vsetPINDir(keypadPort,2,1);
	DIO_vsetPINDir(keypadPort,3,1);
	DIO_vsetPINDir(keypadPort,4,0);
	DIO_vsetPINDir(keypadPort,5,0);
	DIO_vsetPINDir(keypadPort,6,0);
	DIO_vsetPINDir(keypadPort,7,0);
	DIO_vconnectpullup(keypadPort,4,1);
	DIO_vconnectpullup(keypadPort,5,1);
	DIO_vconnectpullup(keypadPort,6,1);
	DIO_vconnectpullup(keypadPort,7,1);
}
char keypad_u8check_press(){
	char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}}; //for proteus
	//char arr[4][4]={{'1','2','3','/'},{'4','5','6','*'},{'7','8','9','-'},{'A','0','=','+'}}; //for hardware
	char row,col,x,returnValue=NOTPRESSED;
	for (row=0; row<4; row++) 
	{
		DIO_write(keypadPort,0,1);
		DIO_write(keypadPort,1,1);
		DIO_write(keypadPort,2,1);
		DIO_write(keypadPort,3,1);
		DIO_write(keypadPort,row,0);
		for (col=0; col<4; col++)
		{
			 x=DIO_u8read(keypadPort,col+4);
			if (x==0)
			{
			returnValue=arr[row][col];
			break;
			}			
		}
		if (x==0)
		break;
	}
	return returnValue;
}