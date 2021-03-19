#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dining_philosophers.h"

void* takeChopstick(void *arguments) {

	TakeChopstickArgs *args = arguments;
	Philosopher *philosopher = args->philosopher;
    Chopstick *leftHand = args->leftHand;
	Chopstick *rightHand = args->rightHand;

	if (leftHand->isTaken || rightHand->isTaken) {
		printf("The [Philosopher %d] can't take the [Chopstick %d] or [Chopstick %d] right now.\n", philosopher->id, leftHand->id, rightHand->id);
		think(philosopher);
		takeChopstick(arguments);
		return 0;
	}

	if (philosopher->leftHand == NULL) {
		philosopher->leftHand = leftHand;
		leftHand->isTaken = 1;
		printf("The [Philosopher %d] is using the [Chopstick %d] on his left hand.\n", philosopher->id, leftHand->id);
	}
	else if (philosopher->rightHand == NULL) {
		philosopher->rightHand = rightHand;
		rightHand->isTaken = 1;
		printf("The [Philosopher %d] is using the [Chopstick %d] on his right hand.\n", philosopher->id, rightHand->id);
	}
	
	eat(philosopher);
	think(philosopher);

	return 0;

}

void* eat(Philosopher *philosopher) {

	if (philosopher->leftHand == NULL || philosopher->rightHand == NULL) {
		printf("The [Philosopher %d] need two Chopsticks to eat!\n", philosopher->id);
		think(philosopher);
		return 0;
	}

	printf("The [Philosopher %d] started eating.\n", philosopher->id);
	sleep(philosopher->eatingTime);
	printf("The [Philosopher %d] ended eating.\n", philosopher->id);
	philosopher->leftHand->isTaken = 0;
	philosopher->leftHand = NULL;
	philosopher->rightHand->isTaken = 0;
	philosopher->rightHand = NULL;

	return 0;

}

void* think(Philosopher *philosopher) {

	printf("The [Philosopher %d] started thinking.\n", philosopher->id);
	sleep(philosopher->thinkingTime);
	printf("The [Philosopher %d] ended thinking.\n", philosopher->id);

	return 0;
	
}

Philosopher* newPhilosopher(int id, int eatingTime, int thinkingTime) {

	Philosopher *newPhilosopher = malloc(sizeof(Philosopher));
	newPhilosopher->id = id;
	newPhilosopher->eatingTime = eatingTime;
	newPhilosopher->thinkingTime = thinkingTime;
	newPhilosopher->leftHand = NULL;
	newPhilosopher->rightHand = NULL;
	printf("[Philosopher %d] created.\n", id);
	return newPhilosopher;

}

Chopstick* newChopstick(int id) {

	Chopstick *newChopstick = malloc(sizeof(Chopstick));
	newChopstick->id = id;
	newChopstick->isTaken = 0;
	printf("[Chopstick %d] created.\n", id);
	return newChopstick;

}

Philosopher** newPhilosophersListOfSize(int size) {

	return malloc(sizeof(Philosopher*) * size);

}

Chopstick** newChopsticksListOfSize(int size) {

	return malloc(sizeof(Chopstick*) * size);

}

void freeMemory(Philosopher** philosophers, Chopstick** chopsticks, int listSize) {

	for (int i = 0; i < listSize; i++) {
		free(philosophers[i]);
		free(chopsticks[i]);
	}

}
