#include "LCD.h"
#include <XC.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Uses Timer4 to delay <us> microseconds
void Init_LCD_Pins(void)
{
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB6 = 0;
}
void Timer4us(unsigned char t) 
{
     T4CON = 0x8000; // enable Timer4, source PBCLK, 1:1 prescaler
 
    // delay 100us per loop until less than 100us remain
    while( t >= 100)
    {
        t-=100;
        TMR4 = 0;
        while( TMR4 < SYSCLK/10000);
    }
 
    // delay 10us per loop until less than 10us remain
    while( t >= 10)
    {
        t-=10;
        TMR4 = 0;
        while( TMR4 < SYSCLK/100000);
    }
 
    // delay 1us per loop until finished
    while( t > 0)
    {
        t--;
        TMR4 = 0;
        while( TMR4 < SYSCLK/1000000);
    }
    // turn off Timer4 so function is self-contained
    T4CONCLR = 0x8000;
}


void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer4us(250);
}

void LCD_pulse (void)
{
	LCD_E=1;
	Timer4us(40);
	LCD_E=0;
}

void LCD_byte (unsigned char x)
{
    LCD_D7=(x & 0x80)?1:0;
    LCD_D6=(x & 0x40)?1:0;
    LCD_D5=(x & 0x20)?1:0;
    LCD_D4=(x & 0x10)?1:0;
    LCD_pulse();
    Timer4us(40); // Or whatever the name of your us function is
    LCD_D7=(x & 0x08)?1:0;
    LCD_D6=(x & 0x04)?1:0;
    LCD_D5=(x & 0x02)?1:0;
    LCD_D4=(x & 0x01)?1:0;
    LCD_pulse();
}

void WriteData (unsigned char x)
{
	LCD_RS=1;
	LCD_byte(x);
	waitms(2);
}

void WriteCommand (unsigned char x)
{
	LCD_RS=0;
	LCD_byte(x);
	waitms(5);
}

void LCD_4BIT (void)
{
	LCD_E=0; // Resting state of LCD's enable is zero
	LCD_RW=0; // We are only writing to the LCD in this program
	waitms(20);
	// First make sure the LCD is in 8-bit mode and then change to 4-bit mode
	WriteCommand(0x33);
	WriteCommand(0x33);
	WriteCommand(0x32); // Change to 4-bit mode

	// Configure the LCD
	WriteCommand(0x28);
	WriteCommand(0x0c);
	WriteCommand(0x01); // Clear screen command (takes some time)
	waitms(20); // Wait for clear screen command to finsih.
}

void LCDprint(char * string, unsigned char line, int clear)
{
	int j;

	WriteCommand(line==2?0xc0:0x80);
	waitms(5);
	for(j=0; string[j]!=0; j++)	WriteData(string[j]);// Write the message
	if(clear) for(; j<CHARS_PER_LINE; j++) WriteData(' '); // Clear the rest of the line
}

/*void printStringLCD(const char* string, int line_num)
{
    char string_buff[17];
    sprintf(string_buff, "%s", string);
    LCDprint(string_buff, line_num, 1);
}
*/

void printStringLCD(const char* string, int line_num)
{
    xdata char string_buff[17];
    sprintf(string_buff, "%s", string);
    LCDprint(string_buff, line_num, 1);
}