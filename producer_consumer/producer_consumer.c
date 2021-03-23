#include <stdlib.h>
#include <stdio.h>
#include "producer_consumer.h"

void* produce(void *arguments) {

	ProduceArgs *args = arguments;
	Producer *producer = args->producer;

	do {
		// Lock resources
		sem_wait(emptySemaphore);
		pthread_mutex_lock(&resources);
		producer->production++;
		int bufferSlot = floor(totalProduction % bufferSize);
		printf("[Producer %d] producing the product %d and saving on slot [%d].\n", producer->id, totalProduction, bufferSlot);
		totalProduction++;
		buffer[bufferSlot] = totalProduction;
		// Unlock resources
		pthread_mutex_unlock(&resources);
		sem_post(fullSemaphore);
		sleep(1);
	}
	while (1);

}

void* consume(void *arguments) {

	ConsumeArgs *args = arguments;
	Consumer *consumer = args->consumer;

	do {
		int productToConsume;
		// Lock resources
		sem_wait(fullSemaphore);
		pthread_mutex_lock(&resources);
		// Consume
		int bufferSlot = floor(totalProduction % bufferSize);
		productToConsume = buffer[bufferSlot];
		printf("[Consumer %d] consuming the product %d.\n", consumer->id, productToConsume);
		consumer->consumption++;
		totalConsumption++;
		// Unlock resources
		pthread_mutex_unlock(&resources);
		sem_post(emptySemaphore);
		sleep(1);
	}
	while (1);
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
	newConsumer->consumption = 0;
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