#include <stdlib.h>
#include <stdio.h>
#include "producer_consumer.h"

void* produce(void *arguments) {

	ProduceArgs *args = arguments;
	pthread_mutex_t* resources;
	int** buffer = args->buffer;
	int* resourcesProduced = args->resourcesProduced;

	return 0;

}

void* consume(void *arguments) {

	ProduceArgs *args = arguments;
	pthread_mutex_t* resources;
	int** buffer = args->buffer;
	int* resourcesConsumed = args->resourcesConsumed;

	return 0;

}