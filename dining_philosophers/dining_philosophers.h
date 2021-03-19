#ifndef DINING_PHILOSOPHERS
#define DINING_PHILOSOPHERS

/**
 * The Chopstick struct
 * Contains only an identification.
 **/
typedef struct
{
	int id;
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
 * Structure used to send arguments to thread function
 **/
typedef struct takeChopstick_args {
	pthread_mutex_t *chopsticksResources;
	Chopstick** chopsticksList;
	int philosophersCount;
    Philosopher *philosopher;
} TakeChopstickArgs;

/**
 * Vinculates a Chopstick to a Philosopher
 **/
void* takeChopstick(void*);

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
