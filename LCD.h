//============================================================================================================
//Display for LCD using PIC32
//Code source : Dr. Jesus Calvino Fraga (gathered from ELEC291 Winter Term 2 2020-2021 Piazza posts
//Date : April 7, 2021
//===========================================================================================================

#ifndef P__LCD_H
#define P__LCD_H
/**************************************************************************************************************/
//Pin configurations
/**************************************************************************************************************/
#define LCD_RS LATBbits.LATB2
#define LCD_RW LATBbits.LATB15
#define LCD_E  LATBbits.LATB13
#define LCD_D4 LATBbits.LATB12
#define LCD_D5 LATBbits.LATB0		
#define LCD_D6 LATBbits.LATB3		
#define LCD_D7 LATBbits.LATB6		
#define CHARS_PER_LINE 16



/**************************************************************************************************************/
//Initialize LCD pins
/**************************************************************************************************************/
void Init_LCD_Pins(void);
/**************************************************************************************************************/
//Delay t microseconds using timer 4
/**************************************************************************************************************/
void Timer4us(unsigned char t);
/**************************************************************************************************************/
//Wait ms miliseconds
/**************************************************************************************************************/
void waitms(unsigned int ms);
/**************************************************************************************************************/
//
/**************************************************************************************************************/
void LCD_pulse(void);
/**************************************************************************************************************/
//
/**************************************************************************************************************/
void LCD_byte(unsigned char x);
/**************************************************************************************************************/
//
/**************************************************************************************************************/
void WriteData(unsigned char x);
/**************************************************************************************************************/
//
/**************************************************************************************************************/
void WriteCommand(unsigned char x);
/**************************************************************************************************************/
//Initialize LCD into 4-bit mode
/**************************************************************************************************************/
void LCD_4BIT(void);
/**************************************************************************************************************/
//Print string at line "line" of the LCD
/**************************************************************************************************************/
void LCDprint(char* string, unsigned char line, int clear);
/**************************************************************************************************************/
void printStringLCD(const char* string, int line_num);
/**************************************************************************************************************/
void printStringLCD(const char* string, int line_num)
/**************************************************************************************************************/
#endif
