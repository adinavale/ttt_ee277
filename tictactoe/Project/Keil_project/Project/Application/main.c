//--------------------------------------------------------
// Application demonstrator: SNAKE game
//--------------------------------------------------------


#include "EDK_CM0.h" 
#include "core_cm0.h"
#include "edk_driver.h"
#include "edk_api.h"

#include <stdio.h>

//Maximum snake length
#define N 200							

//Game region
#define left_boundary 5
#define right_boundary 96
#define top_boundary 5
#define bottom_boundary 116
#define boundary_thick 1

//Global variables
static int score1;
static int score2;
static char key;
static int sizedown = 5;

// Structure define
struct target{
	int x;
	int y;
	} Coord;


//---------------------------------------------
// Game
//---------------------------------------------


void Game_Init(void)
{	
	//Draw a game region
	clear_screen();
	// rectangle(left_boundary,top_boundary,right_boundary,top_boundary+boundary_thick,BLUE);
	// rectangle(left_boundary,top_boundary,left_boundary+boundary_thick,bottom_boundary,BLUE);
	// rectangle(left_boundary,bottom_boundary,right_boundary,bottom_boundary+boundary_thick,BLUE);
	// rectangle(right_boundary,top_boundary,right_boundary+boundary_thick,bottom_boundary+boundary_thick,BLUE);	


    // 0,0 ------ 33,0 ----- 66,0 ----- 100,0
	
    // 0,40 ------ 33,40 ----- 66,40 ----- 100,40
	
    // 0,80 ------ 33,80 ----- 66,80 ----- 100,80
	
    // 0,120 ------ 33,120 ----- 66,120 ----- 100,120

	rectangle(0+sizedown, 0+sizedown, 33-sizedown, 40-sizedown, PURPLE); // top left
	rectangle(33+sizedown, 40+sizedown, 66-sizedown, 80-sizedown, PURPLE); // mid center
	rectangle(66+sizedown, 80+sizedown, 100-sizedown, 120-sizedown, PURPLE); // bottom right

	rectangle(66+sizedown, 40+sizedown, 100-sizedown, 80-sizedown, RED); // mid right
	rectangle(0+sizedown, 80+sizedown, 33-sizedown, 120-sizedown, RED); // bottom left

	rect(0, 0, 33, 40, WHITE); // top left
	rect(33, 0, 66, 40, WHITE); // top center
	rect(66, 0, 100, 40, WHITE); // top right

	rect(0, 40, 33, 80, WHITE); // mid left
	rect(33, 40, 66, 80, WHITE); // mid center
	rect(66, 40, 100, 80, WHITE); // mid right
	
	rect(0, 80, 33, 120, WHITE); // bottom left
	rect(33, 80, 66, 120, WHITE); // bottom center
	rect(66, 80, 100, 120, WHITE); // bottom right


	
    // draw boxes	
	score1=1;
	score2=0;
	
	
	//Initialise timer (load value, prescaler value, mode value)
	//timer_init((Timer_Load_Value_For_One_Sec/gamespeed),Timer_Prescaler,1);	
	//timer_enable();
	
	
	//Print instructions

	printf("\n########################\n");
	printf("\n-----  Tic-Tac-Toe -----\n");
	printf("\n########################\n\n\n");
	printf("\nPress any key to start\n\n\n");	

	printf("\nWinner : Blue\n\n\n");	
		
	printf("\nScore Blue=%d  Red=%d\n",score1, score2);

	while(KBHIT()==0);
	
	NVIC_EnableIRQ(Timer_IRQn);			//start timing
	NVIC_EnableIRQ(UART_IRQn);	
}


void Game_Close(void){
	clear_screen();
	score1=0;
	score2=0;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");		//flush screen
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	NVIC_DisableIRQ(Timer_IRQn);			
	NVIC_DisableIRQ(UART_IRQn);	
}


	
int GameOver(void){
	char key;
	
	NVIC_DisableIRQ(UART_IRQn);
	NVIC_DisableIRQ(Timer_IRQn);
	printf("\nScore P1=%d  Score P2=%d\n",score1, score2);
	printf("\nGame over\n");
	if (score1 == score2)
		printf("Game draw");
	else
		printf("Player %d wins!", score1 > score2 ? 1 : 2);
	printf("\nPress 'q' to quit");
	printf("\nPress 'r' to replay");
	score1 = 0;
	score2 = 0;
	while(1){
		while(KBHIT()==0);
		key = UartGetc();
		if (key == RESET){
			return 1;
		}
		else if (key == QUIT){	
			return 0;
		}
		else
			printf("\nInvalid input");
	}
		
}






//---------------------------------------------
// UART ISR -- used to input commands
//---------------------------------------------

void UART_ISR(void)
{	

  key=UartGetc();	
	
}
 

//---------------------------------------------
// TIMER ISR -- used to move the snake
//---------------------------------------------


void Timer_ISR(void)
{
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


