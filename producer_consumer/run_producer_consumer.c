#include <stdlib.h>
#include <stdio.h>
#include "producer_consumer.h"

int main(int argc, char **argv) {

	// Arguments validation
	if (argc != 4) {
		fprintf(stderr, "O programa não pode ser executado pois os parâmetros estão errados\n");
		fprintf(stderr, "Para a execução é necessário passar: 1) Tamanho do Buffer; 2) Quantidade de Produtores; 3) Quantidade de Consumidores\n");
		fprintf(stderr, "Exemplo: ./run_producer_consumer 10 2 5\n");
		return EXIT_FAILURE;
	}

	sem_unlink(EMPTY_SEMAPHORE_NAME);
	sem_unlink(FULL_SEMAPHORE_NAME);
	pthread_mutex_destroy(&resources);

	// Reads user input
	bufferSize = strtol(argv[1], NULL, 10);
	int producersCount = strtol(argv[2], NULL, 10);
	int consumersCount = strtol(argv[3], NULL, 10);

	printf("Producer-Consumer: [Executing with: BufferSize %d, %d Producers and %d Consumers]\n", bufferSize, producersCount, consumersCount);
	printf("===\n");

	// Creates a new Buffer
	buffer = malloc(sizeof(int) * bufferSize);
	totalProduction = 0;
	totalConsumption = 0;
	Producer** producersList = newProducersListOfSize(producersCount);
	Consumer** consumersList = newConsumersListOfSize(consumersCount);

	// Creates Producers and Consumers
	pthread_t producers[producersCount], consumers[consumersCount];
	pthread_mutex_init(&resources, NULL);
	emptySemaphore = sem_open(EMPTY_SEMAPHORE_NAME, O_CREAT, S_IRWXU, bufferSize);
	if(emptySemaphore == SEM_FAILED){
		fprintf(stderr, "Error opening semaphore: %s\n!", EMPTY_SEMAPHORE_NAME);
		return EXIT_FAILURE;
	}
	fullSemaphore = sem_open(FULL_SEMAPHORE_NAME, O_CREAT, S_IRWXU, 0);
	if(emptySemaphore == SEM_FAILED){
		fprintf(stderr, "Error opening semaphore: %s\n!", FULL_SEMAPHORE_NAME);
		return EXIT_FAILURE;
	}
	// pthread_setconcurrency(producersCount+consumersCount);

	// Create Producers
	for (int i = 0; i < producersCount; i++) {
		producersList[i] = newProducer(i);
	}

	// Create Consumers
	for (int i = 0; i < consumersCount; i++) {
		consumersList[i] = newConsumer(i);
	}

	// Create Producers threads
	for (int i = 0; i < producersCount; i++) {
		ProduceArgs* args = malloc(sizeof(ProduceArgs));
		args->producer = producersList[i];
		pthread_create(&producers[i], NULL, produce, args);
	}

	// Create Consumers threads
	for (int i = 0; i < consumersCount; i++) {
		ConsumeArgs* args = malloc(sizeof(ConsumeArgs));
		args->consumer = consumersList[i];
		pthread_create(&consumers[i], NULL, consume, args);
	}

	printf("===\n");

	// Start Producers
	for (int i = 0; i < producersCount; i++) {
		Producer *producer = producersList[i];
		pthread_join(producers[i], NULL);
		printf("[Producer %d] produced %d of %d.\n", producer->id, producer->production, bufferSize);
	}

	// Start Consumers
	for (int i = 0; i < consumersCount; i++) {
		Consumer *consumer = consumersList[i];
		pthread_join(consumers[i], NULL);
		printf("[Consumer %d] consumed %d of %d.\n", consumer->id, consumer->consumption, bufferSize);
	}

	// Destroy resources
	sem_unlink(EMPTY_SEMAPHORE_NAME);
	sem_unlink(FULL_SEMAPHORE_NAME);
	pthread_mutex_destroy(&resources);

	// Free memory
	freeMemory(producersList, producersCount, consumersList, consumersCount);

	printf("===\n");

}