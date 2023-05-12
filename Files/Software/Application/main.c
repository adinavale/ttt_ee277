//--------------------------------------------------------
// Application demonstrator: SNAKE game
//--------------------------------------------------------


#include "EDK_CM0.h" 
#include "core_cm0.h"
#include "edk_driver.h"
#include "edk_api.h"

#include <stdio.h>

//Maximum snake length
#define N 100							

//Game region
#define left_boundary 5
#define right_boundary 96
#define top_boundary 5
#define bottom_boundary 116
#define boundary_thick 1

//Global variables
static int i,j;
static char key;
static int score1;
static int score2;
static int snake1_has_moved;
static int snake2_has_moved;
//static int speed_table[10]={6,6,6,6,6,6,6,6,6,6}; //just to simulate self body hit test case


//---------------------------------------------
// Game
//---------------------------------------------

void Game_Init(void)
{	
	//Draw a game region
	clear_screen();

	//Initialise data	
	score1 = 0;
	score2 = 0;
	
	//Initialise timer (load value, prescaler value, mode value)
	timer_enable();
	
	//Print instructions on text console of VGA
	printf("\n------- Snake Game --------");
	printf("\nCentre btn ..... hard reset");
	printf("\nKeyboard r ..... soft reset");
	printf("\n   Player 1:Red Snake   ");//player 1
	printf("\nKeyboard w ........ move up");//player 1
	printf("\nKeyboard s ...... move down");//player 1
	printf("\nKeyboard a ...... move left");//player 1
	printf("\nKeyboard d ..... move right");//player 1
	printf("\n   Player 2:Green Snake   ");//player 2
	printf("\nKeyboard i ........ move up");//player 2
	printf("\nKeyboard k ...... move down");//player 2
	printf("\nKeyboard j ...... move left");//player 2
	printf("\nKeyboard l ..... move right");//player 2
	printf("\nKeyboard space ...... pause");
	printf("\n---------------------------");	
	printf("\nTo run the game, make sure:");
	printf("\n*UART terminal is activated");
	printf("\n*UART baud rate is 19200bps");
	printf("\n*Keyboard is in lower case");
	printf("\n---------------------------");
	printf("\nPress any key to start\n");

	while(KBHIT()==0); //wait till keyboard press is detected
		
	NVIC_EnableIRQ(Timer_IRQn);//start timing
	NVIC_EnableIRQ(UART_IRQn);	
}

void Game_Close(void)
{
	clear_screen();
	
	// Reset scores to 0
	score1 = 0;
	score2 = 0;
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");//flush screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	
	NVIC_DisableIRQ(Timer_IRQn);			
	NVIC_DisableIRQ(UART_IRQn);	
}
	
int GameOver(void)
{
	char key;
	
	NVIC_DisableIRQ(UART_IRQn);
	NVIC_DisableIRQ(Timer_IRQn);
	
	printf("\nGAME OVER !!!\n");
	printf("\nPress 'q' to quit");
	printf("\nPress 'r' to replay\n");
	
	while(1)
		{
			while(KBHIT()==0);
		
			key = UartGetc();
			
			if (key == RESET)
				return 1;
			
			else if (key == QUIT)
				return 0;
			
			else
				printf("\nInvalid Input! Try Again!");
		}		
}


//---------------------------------------------
// UART ISR -- used to input commands
//---------------------------------------------
void UART_ISR(void)
{	

	key=UartGetc();	
	printf("%c", key);	
}
 

//---------------------------------------------
// TIMER ISR -- used to move the snake
//---------------------------------------------


void Timer_ISR(void)
{

	//Display the total distance that the snake has moved
	Display_Int_Times();
		
	//Clear timer irq
	timer_irq_clear();
}	

//---------------------------------------------
// Main Function
//---------------------------------------------
int main(void){

	//Initialise the system
	SoC_init();
	//Initialise the game
	Game_Init();
	
	//Go to sleep mode and wait for interrupts
	while(1)
		__WFI();	
}


