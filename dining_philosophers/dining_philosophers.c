#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "dining_philosophers.h"

void* takeChopstick(void *arguments) {

	TakeChopstickArgs *args = arguments;
	
	int philosophersCount = args->philosophersCount;
	pthread_mutex_t *chopsticksResources = args->chopsticksResources;
	Chopstick** chopsticks = args-> chopsticksList;
	
	Philosopher *philosopher = args->philosopher;
	int leftHandIndex = philosopher->id;
	int rightHandIndex = (leftHandIndex + 1) % philosophersCount;

	// Lock resources
	Chopstick *leftHand = chopsticks[leftHandIndex];
	Chopstick *rightHand = chopsticks[rightHandIndex];
	pthread_mutex_lock(&chopsticksResources[leftHandIndex]);
	pthread_mutex_lock(&chopsticksResources[rightHandIndex]);

	if (philosopher->leftHand == NULL) {
		philosopher->leftHand = leftHand;
		printf("The [Philosopher %d] is using the [Chopstick %d] on his left hand.\n", philosopher->id, leftHand->id);
	}
	
	if (philosopher->rightHand == NULL) {
		philosopher->rightHand = rightHand;
		printf("The [Philosopher %d] is using the [Chopstick %d] on his right hand.\n", philosopher->id, rightHand->id);
	}
	
	eat(philosopher);
	think(philosopher);

	// Unlock resources
	pthread_mutex_unlock(&chopsticksResources[leftHandIndex]);
	pthread_mutex_unlock(&chopsticksResources[rightHandIndex]);
	philosopher->leftHand = NULL;
	philosopher->rightHand = NULL;

	return 0;

}

void eat(Philosopher *philosopher) {

	if (philosopher->leftHand == NULL || philosopher->rightHand == NULL) {
		printf("The [Philosopher %d] need two Chopsticks to eat!\n", philosopher->id);
		think(philosopher);
		return;
	}

	printf("The [Philosopher %d] started eating.\n", philosopher->id);
	sleep(philosopher->eatingTime);
	printf("The [Philosopher %d] ended eating.\n", philosopher->id);

}

void think(Philosopher *philosopher) {

	printf("The [Philosopher %d] started thinking.\n", philosopher->id);
	sleep(philosopher->thinkingTime);
	printf("The [Philosopher %d] ended thinking.\n", philosopher->id);

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
