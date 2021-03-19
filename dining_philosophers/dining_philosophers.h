#ifndef DINING_PHILOSOPHERS
#define DINING_PHILOSOPHERS

/**
 * The Chopstick struct
 * Contains an int value that indicates if the resource is taken.
 **/
typedef struct
{
	int id;
	int isTaken;
} Chopstick;

/**
 * The Philosopher struct
 * Contains two pointers that simulate hands pointing to Chopstick.
 * Also have an identification number.
 **/
typedef struct
{
	int id;
	Chopstick *leftHand;
	Chopstick *rightHand;
} Philosopher;

/**
 * Vinculates a Chopstick to a Philosopher
 **/
void takeChopstick(Philosopher *philosopher, Chopstick *chopstick);

/**
 * The Philosopher starts eating
 **/
void eat(Philosopher *philosopher, int eatingTime);

/**
 * The Philosopher starts thinking
 **/
void think(Philosopher *philosopher, int thinkingTime);

#endif
