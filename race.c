#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// including two different libraries depending on what type of computer is running program. 
// The preprocessor directive tests the system to ensure the correct library is included. 
// library windows.h and unistd.h are for the sleep() function, to create a time delay.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// total length of race
#define MAX 70

// speed modifiers for the two contestants. 
// Each element of the array represents 10% of the total move values that the hare, 
// or tortoise, can take. For instance, 20% of the time, the hare does not move forward at all 
// (represented by 0), and 10% of the time he slips and goes backwards 12 lengths.
int hareSpeed[10] = {0, 0, 9, 9, -12, 1, 1, 1, -2, -2};
int tortoiseSpeed[10] = {3, 3, 3, 3, 3, -6, -6, 1, 1, 1};

// function prototypes for displays and time pacing of the race
void raceLines(void);
void header(void);
void oneSecond(int modifier);


int main(void) 
{
	// seed randomizer
	srand(time(NULL));  

	// declare and initialize hare/tortoise variables
	int h = 0, t = 0;

	header();
	// do...while for entirety of race
	do
	{
		// randomized update for the contestant's positions. t and h are integers, and will range 
		// from 0 to 70. The random function will pick one of the 10 elements in the speed arrays 
		// and update the positions accordingly.
		h += hareSpeed[rand()%10];
		if (h < 0) 
			h = 0;

		t += tortoiseSpeed[rand()%10];
		if (t < 0) 
			t = 0;    

		// function to delay each display of the race. Function is not actually one second, 
		// instead 100 miliseconds to make race go a little faster. Integer modifier can 
		// increase or decrease time by factors of 100.
		oneSecond(1);

		raceLines();
		// places blank spaces for each step between starting point (0) and 
		// current position (h) of hare.
		for (int i = 0; i < h  && i < MAX; i++)
		{
			printf(" ");
		}
		printf("H");

		// places blank spaces for each step left to go between current position (h) 
		// and finish line (MAX)
		for (int i = h+1; i < MAX; i++)
			printf(" ");

		// replaces finishing line marker with '!' for a winner
		if (h >= MAX) 
			printf("!\n");
		// if no winner, will maintain finish line (made of '#'s)
		else
			printf("#\n");

		// repeat blank iterations for tortoise position.
		for (int i = 0; i < t && i < MAX; i++)
		{
			printf(" ");
		}
		printf("T");

		for (int i = t+1; i < MAX; i++)
			printf(" ");

		if (t >= MAX) 
			printf("!");
		else
			printf("#");

		raceLines();

		//  if contestants land on the same spot that is not the starting line, 
		// will crash into one another, creating a message.
		if (t == h && t != 0 && h != 0)
		{
			printf("\nOUCH! That was a little too close, better get off each others' toes!\n\n");

			oneSecond(2);
		}

		// tests if a contestant is close to finish line
		if (t == MAX-2 || 
			h == MAX-2 ||
			t == MAX-1 ||
			h == MAX-1)
		{
			printf("\nSo.. close..!!\n\n");
			oneSecond(2);
		}

		// tests winners, displays individual messages based on who won
		if (h >= MAX) 
		{
			printf("\n\n******Hare wins... darn.*****\n");
			// tests how far ahead winner is, if winner is several lengths 
			// (at least a quarter of total) in advance, will create a message stating so.
			if (h > t+(MAX%4))
				printf("\t\t...by a LOT\n");
		}

		if (t >= MAX) 
		{
		  printf("\n\n****TORTOISE WINS! HOORAY!*****\n");
		  if (t > h+(MAX%4))
			printf("\t\t...by a LOT\n");
		}

	}
	
	// condition to continue running loop (until one contestant is clearly past the finish line)
	while (h < MAX && t < MAX);

	return 0;
}

void header(void)
{
	printf("\t\tWelcome to the Races: Tortoise and Hare\n"
		 "\t\t---------------------------------------\n"
		 "\nThe epic duo will compete for an UPHILL, SLIPPERY climb to the finish line!"
		 "They may fall, they may slip backwards, or they might be too lazy to go forward.."
		 " but eventually, someone will win. Hooray!\n\n");

	printf("If you are ready for a thrilling ride.. press enter!");
	int c=getchar();

	printf("\nReady...");
	oneSecond(1);

	printf("\n\nSet..");
	oneSecond(10);

	printf("\n\nGO!!");
	oneSecond(10);
  
}

void raceLines (void)
{
	printf("\n----------------------------------------------------------------------#\n");
}

// works with system for delaying program
void oneSecond(int modifier)
{
	int delayTime=100;

	#ifdef _WIN32
	sleep(delayTime*modifier);
	#else
	usleep(delayTime*1000*modifier); 
	#endif
}