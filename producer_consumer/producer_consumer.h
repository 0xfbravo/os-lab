#ifndef PRODUCER_CONSUMER
#define PRODUCER_CONSUMER
#include <pthread.h>
#include <unistd.h>

typedef struct producer {
	int id;
	int production;
} Producer;

typedef struct consumer {
	int id;
	int *comsuption;
} Consumer;

/**
 * Structure used to send arguments to thread function
 **/
typedef struct produce_args {
	pthread_mutex_t *resources;
	int *buffer;
	int bufferSize;
	Producer *producer;
	int *totalProduction;
} ProduceArgs;

typedef struct consume_args {
	pthread_mutex_t *resources;
	int *buffer;
	int bufferSize;
	Consumer *consumer;
	int *totalConsumption;
} ConsumeArgs;

/**
 * Produces a new resource and put it on buffer
 **/
void* produce(void*);

/**
 * Consumes some resource from buffer
 **/
void* consume(void*);

/**
 * Creates a new Producer
 **/
Producer* newProducer(int);

/**
 * Creates a new Consumer
 **/
Consumer* newConsumer(int);

/**
 * Creates a new Producers List
 **/
Producer** newProducersListOfSize(int);

/**
 * Creates a new Consumers List
 **/
Consumer** newConsumersListOfSize(int);

/**
 * Frees the memory
 **/
void freeMemory(Producer**, int, Consumer**, int);

#endif