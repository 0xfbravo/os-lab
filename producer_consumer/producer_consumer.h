#ifndef PRODUCER_CONSUMER
#define PRODUCER_CONSUMER
#include <pthread.h>
#include <unistd.h>

/**
 * Structure used to send arguments to thread function
 **/
typedef struct produce_args {
	pthread_mutex_t *resources;
	int **buffer;
	int *resourcesProduced;
	int *resourcesConsumed;
} ProduceArgs;

/**
 * Produces a new resource and put it on buffer
 **/
void* produce(void*);

/**
 * Consumes some resource from buffer
 **/
void* consume(void*);

#endif