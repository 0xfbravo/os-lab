#include <stdlib.h>
#include <stdio.h>
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

	printf("--- Executing with: %d Philosophers, Thinking for %d and Eating for %d\n", philosophersCount, thinkingTime, eatingTime);

	// Creates Philosophers and Chopsticks
	Philosopher** philosophers = newPhilosophersListOfSize(philosophersCount);
	Chopstick** chopsticks = newChopsticksListOfSize(philosophersCount);

	for (int i = 0; i < philosophersCount; i++) {
		philosophers[i] = newPhilosopher(i, eatingTime, thinkingTime);
		chopsticks[i] = newChopstick(i);
	}

	freeMemory(philosophers, chopsticks, philosophersCount);

}