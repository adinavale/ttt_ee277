/*
 *-----------------------------------------------------------------------------
 * @file     API.h
 * @date     May 2022
 * @autors   
 *-----------------------------------------------------------------------------
 */


void SoC_init(void); /* SoC initialization */
void rectangle(int x1,int y1,int x2,int y2, int color);/* Draw a rectangle on the screen */
void clear_screen (void);/* Clean up the screen */
int read_switch(); /*Read the value of the 8-bit switches */
void write_LED(int switch_val); /* Write a value to the 8-bit LEDs */
void Display_Int_Times (void);/* Display the number of interrupts that occurred using the 7-segment display */
void Display_Int_Times (void);/* Display the number of interrupts that occurred using the 7-segment display */
char random (char min, char max); /* A simple random generator based on system tick */