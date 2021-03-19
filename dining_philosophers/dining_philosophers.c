#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dining_philosophers.h"

void takeChopstick(Philosopher *philosopher, Chopstick *chopstick) {

	if (chopstick->isTaken) {
		printf("The [Philosopher %d] can't take the [Chopstick %d] right now.\n", philosopher->id, chopstick->id);
		return;
	}

	if (philosopher->leftHand == NULL) {
		philosopher->leftHand = chopstick;
		chopstick->isTaken = 1;
		printf("The [Philosopher %d] is using the [Chopstick %d] on his left hand.\n", philosopher->id, chopstick->id);
	}
	else if (philosopher->rightHand == NULL) {
		philosopher->rightHand = chopstick;
		chopstick->isTaken = 1;
		printf("The [Philosopher %d] is using the [Chopstick %d] on his right hand.\n", philosopher->id, chopstick->id);
	}
	else {
		printf("The [Philosopher %d] can't take more than two Chopsticks!\n", philosopher->id);
	}

}

void eat(Philosopher *philosopher, int eatingTime) {

	if (philosopher->leftHand == NULL || philosopher->rightHand == NULL) {
		printf("The [Philosopher %d] need two Chopsticks to eat!\n", philosopher->id);
		return;
	}

	printf("The [Philosopher %d] started eating.\n", philosopher->id);
	sleep(eatingTime);
	printf("The [Philosopher %d] ended eating.\n", philosopher->id);
	philosopher->leftHand->isTaken = 0;
	philosopher->leftHand = NULL;
	philosopher->rightHand->isTaken = 0;
	philosopher->rightHand = NULL;

}

void think(Philosopher *philosopher, int thinkingTime) {

	printf("The [Philosopher %d] started thinking.\n", philosopher->id);
	sleep(thinkingTime);
	printf("The [Philosopher %d] ended thinking.\n", philosopher->id);
	
}
