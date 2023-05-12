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
static int col, row;
static int active_player;


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
	active_player = 1; //player 1 goes first
	
	//Initialise timer (load value, prescaler value, mode value)
	timer_enable();
	
	//Print instructions on text console of VGA
	printf("\n----- Tic Tac Toe Game -----");
	printf("\n---  Get three in a row ----");
	printf("\n---  Player 1 goes first ---");
	printf("\n            1|2|3           ");
	printf("\n            4|5|6           ");
	printf("\n            7|8|9           ");
	
	//First horizontal line
	for(col = 5; col < 96; col++){
		VGA_plot_pixel(col, 40, WHITE);
	}

	//Second horizontal line
	for(col = 5; col < 96; col++){
		VGA_plot_pixel(col, 80, WHITE);
	}

	//Left vertical line
	for(row = 5; row < 116; row++){
		VGA_plot_pixel(33, row, WHITE);
	}

	//Right vertical line
	for(row = 5; row < 116; row++){
		VGA_plot_pixel(66, row, WHITE);
	}


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

	while(1)
		{
			while(KBHIT()==0);
		
			key = UartGetc();
			
			if (key == ONE){
				printf("Key 1 pressed\n");
				display_X(10, 10);
			}else if(key == TWO){
				printf("key 2 pressed\n");
			}else{
				printf("Different key pressed\n");
			}
				
		}
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


