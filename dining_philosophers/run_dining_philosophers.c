#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "dining_philosophers.h"

int main(int argc, char **argv) {

	// Arguments validation
	if (argc != 4) {
		fprintf(stderr, "O programa não pode ser executado pois os parâmetros estão errados\n");
		fprintf(stderr, "Para a execução é necessário passar: 1) Número de Filósofos; 2) Tempo de Pensamento; 3) Tempo comendo\n");
		fprintf(stderr, "Exemplo: ./run_dining_philosophers 5 10 10\n");
		return EXIT_FAILURE;
	}

	// Reads list mode and size from user input
	int philosophersCount = strtol(argv[1], NULL, 10);
	int thinkingTime = strtol(argv[2], NULL, 10);
	int eatingTime = strtol(argv[3], NULL, 10);

	printf("--- Executing with: %d Philosophers, Thinking for %ds and Eating for %ds\n", philosophersCount, thinkingTime, eatingTime);

	// Creates Philosophers and Chopsticks
	pthread_t philosophersThreads[philosophersCount];
	pthread_mutex_t chopsticksResources[philosophersCount];
	Philosopher** philosophers = newPhilosophersListOfSize(philosophersCount);
	Chopstick** chopsticks = newChopsticksListOfSize(philosophersCount);

	for (int i = 0; i < philosophersCount; i++) {
		philosophers[i] = newPhilosopher(i, eatingTime, thinkingTime);
		chopsticks[i] = newChopstick(i);
		pthread_mutex_init(&chopsticksResources[i],NULL);
	}

	// Open threads
	for (int i = 0; i < philosophersCount; i++) {
		TakeChopstickArgs* args = malloc(sizeof(TakeChopstickArgs));
		args->chopsticksResources = chopsticksResources;
		args->chopsticksList = chopsticks;
		args->philosophersCount = philosophersCount;
		args->philosopher = philosophers[i];
		pthread_create(&philosophersThreads[i], NULL, takeChopstick, args);
	}

	// Wait/join threads
	for (int i = 0; i < philosophersCount; i++) {
		pthread_join(philosophersThreads[i], NULL);
	}

	// Destroy resources
	for (int i = 0; i < philosophersCount; i++) {
		pthread_mutex_destroy(&chopsticksResources[i]);
	}

	// Check if the all philosophers did eat
	printf("Did all philosophers eat?");
	for (int i = 0; i < philosophersCount; i++) {
		printf("Philosopher %d - %s\n", philosophers[i]->id, (philosophers[i]->didEat == 0) ? "false" : "true");
	}

	freeMemory(philosophers, chopsticks, philosophersCount);

}