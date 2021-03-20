#include <stdlib.h>
#include <stdio.h>
#include "producer_consumer.h"

void* produce(void *arguments) {

	ProduceArgs *args = arguments;
	pthread_mutex_t *resources = args->resources;
	int *buffer = args->buffer;
	int bufferSize = args->bufferSize;
	int totalProduction = *args->totalProduction;
	Producer *producer = args->producer;

	do {
		// Lock resources
		pthread_mutex_lock(resources);
		// Produce
		totalProduction++;
		// Unlock resources
		pthread_mutex_unlock(resources);
		producer->production++;
	}
	while (totalProduction < bufferSize);

	return 0;

}

void* consume(void *arguments) {

	return 0;

}

Producer* newProducer(int id) {

	Producer *newProducer = malloc(sizeof(Producer));
	newProducer->id = id;
	newProducer->production = 0;
	printf("[Producer %d] created.\n", id);
	return newProducer;

}

Consumer* newConsumer(int id) {

	Consumer *newConsumer = malloc(sizeof(Consumer));
	newConsumer->id = id;
	newConsumer->comsuption = 0;
	printf("[Consumer %d] created.\n", id);
	return newConsumer;

}

Producer** newProducersListOfSize(int size) {

	return malloc(sizeof(Producer*) * size);

}

Consumer** newConsumersListOfSize(int size) {

	return malloc(sizeof(Consumer*) * size);

}

void freeMemory(Producer **producers, int producersCount, Consumer **consumers, int consumersCount) {

	for (int i = 0; i < producersCount; i++) {
		free(producers[i]);
	}

	for (int i = 0; i < consumersCount; i++) {
		free(consumers[i]);
	}

}