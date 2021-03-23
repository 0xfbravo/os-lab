#include <stdlib.h>
#include <stdio.h>
#include "producer_consumer.h"

void* produce(void *arguments) {

	ProduceArgs *args = arguments;
	Producer *producer = args->producer;

	do {
		sleep(1);
		// Lock resources
		sem_wait(emptySemaphore);
		pthread_mutex_lock(&resources);
		for (int i = 0; i < producer->capacity; i++) {
			if (fullSlots == bufferSize)
				break;

			buffer[fullSlots] = rand();
			printf("[Producer %d] producing the product (P%d) and saving on slot [%d].\n", producer->id, buffer[fullSlots], fullSlots);
			producer->production++;
			fullSlots++;
		}
		// Unlock resources
		pthread_mutex_unlock(&resources);
		sem_post(fullSemaphore);
	}
	while (1);

}

void* consume(void *arguments) {

	ConsumeArgs *args = arguments;
	Consumer *consumer = args->consumer;

	do {
		sleep(1);
		// Lock resources
		sem_wait(fullSemaphore);
		pthread_mutex_lock(&resources);
		// Consume
		for (int i = 0; i < consumer->capacity; i++) {
			if (fullSlots == 0)
				break;

			int productToConsume = buffer[fullSlots-1];
			printf("[Consumer %d] consuming the product (P%d) from slot [%d].\n", consumer->id, productToConsume, fullSlots-1);
			consumer->consumption++;
			fullSlots--;
		}
		// Unlock resources
		pthread_mutex_unlock(&resources);
		sem_post(emptySemaphore);
	}
	while (1);
}

Producer* newProducer(int id, int capacity) {

	Producer *newProducer = malloc(sizeof(Producer));
	newProducer->id = id;
	newProducer->capacity = capacity;
	newProducer->production = 0;
	printf("[Producer %d] created.\n", id);
	return newProducer;

}

Consumer* newConsumer(int id, int capacity) {

	Consumer *newConsumer = malloc(sizeof(Consumer));
	newConsumer->id = id;
	newConsumer->capacity = capacity;
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

void freeMemory(Producer **producers, int producersQuantity, Consumer **consumers, int consumersQuantity) {

	for (int i = 0; i < producersQuantity; i++) {
		free(producers[i]);
	}

	for (int i = 0; i < consumersQuantity; i++) {
		free(consumers[i]);
	}

}