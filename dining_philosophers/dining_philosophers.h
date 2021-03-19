#ifndef DINING_PHILOSOPHERS
#define DINING_PHILOSOPHERS

/**
 * The Fork struct
 * Contains an int value that indicates if the resource is taken.
 **/
typedef struct
{
	int isTaken;
} Fork;

/**
 * The Philosopher struct
 * Contains two pointers that simulate hands pointing to Forks.
 **/
typedef struct
{
	Fork *leftHand;
	Fork *rightHand;
} Philosopher;

/**
 * Vinculates a Fork to a Philosopher
 **/
void takeFork(Philosopher *philosopher, Fork *fork);

/**
 * The Philosopher starts eating
 **/
void eat(Philosopher *philosopher);

/**
 * The Philosopher starts thinking
 **/
void think(Philosopher *philosopher);

#endif