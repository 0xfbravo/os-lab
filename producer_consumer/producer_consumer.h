#ifndef PRODUCER_CONSUMER
#define PRODUCER_CONSUMER
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <unistd.h>

#define EMPTY_SEMAPHORE_NAME "emptySemaphore"
#define FULL_SEMAPHORE_NAME "fullSemaphore"

pthread_mutex_t resources;
sem_t *emptySemaphore;
sem_t *fullSemaphore;
int *buffer;
int bufferSize;
int totalProduction;
int totalConsumption;

typedef struct producer {
	int id;
	int production;
} Producer;

typedef struct consumer {
	int id;
	int consumption;
} Consumer;

/**
 * Structure used to send arguments to thread function
 **/
typedef struct produce_args {
	Producer *producer;
} ProduceArgs;

typedef struct consume_args {
	Consumer *consumer;
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