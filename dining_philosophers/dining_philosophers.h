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
	int thinkingTime;
	int eatingTime;
	Chopstick *leftHand;
	Chopstick *rightHand;
} Philosopher;

/**
 * Vinculates a Chopstick to a Philosopher
 **/
void takeChopstick(Philosopher*, Chopstick*);

/**
 * The Philosopher starts eating
 **/
void eat(Philosopher*);

/**
 * The Philosopher starts thinking
 **/
void think(Philosopher*);

/**
 * Creates a new Philosophers List
 **/
Philosopher** newPhilosophersListOfSize(int);

/**
 * Creates a new Chopsticks List
 **/
Chopstick** newChopsticksListOfSize(int);


/**
 * Creates a new Philosopher
 **/
Philosopher* newPhilosopher(int, int, int);

/**
 * Creates a new Chopstick
 **/
Chopstick* newChopstick(int);

/**
 * Frees the memory
 **/
void freeMemory(Philosopher**, Chopstick**, int);

#endif
