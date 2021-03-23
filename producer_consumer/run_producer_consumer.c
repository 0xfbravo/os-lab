#include <stdlib.h>
#include <stdio.h>
#include "producer_consumer.h"

int main(int argc, char **argv) {

	// Arguments validation
	if (argc != 6) {
		fprintf(stderr, "O programa não pode ser executado pois os parâmetros estão errados\n");
		fprintf(stderr, "Para a execução é necessário passar: 1) Tamanho do Buffer; 2) Quantidade de Produtores; 3) Capacidade do Produtor; 4) Quantidade de Consumidores; 5) Capacidade do Consumidor\n");
		fprintf(stderr, "Exemplo: ./run_producer_consumer 100 1 10 2 10\n");
		return EXIT_FAILURE;
	}

	sem_unlink(EMPTY_SEMAPHORE_NAME);
	sem_unlink(FULL_SEMAPHORE_NAME);
	pthread_mutex_destroy(&resources);

	// Reads user input
	bufferSize = strtol(argv[1], NULL, 10);
	int producersQuantity = strtol(argv[2], NULL, 10);
	int producerCapacity = strtol(argv[3], NULL, 10);
	int consumersQuantity = strtol(argv[4], NULL, 10);
	int consumerCapacity = strtol(argv[5], NULL, 10);

	printf("Producer-Consumer: [Executing with: BufferSize %d, %d Producers (Producing %d) and %d Consumers (Consuming %d)]\n", bufferSize, producersQuantity, producerCapacity, consumersQuantity, consumerCapacity);
	printf("===\n");

	// Creates a new Buffer
	buffer = malloc(sizeof(int) * bufferSize);
	fullSlots = 0;
	Producer** producersList = newProducersListOfSize(producersQuantity);
	Consumer** consumersList = newConsumersListOfSize(consumersQuantity);

	// Creates Producers and Consumers
	pthread_t producers[producersQuantity], consumers[consumersQuantity];
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
	// pthread_setconcurrency(producersQuantity+consumersQuantity);

	// Create Producers
	for (int i = 0; i < producersQuantity; i++) {
		producersList[i] = newProducer(i, producerCapacity);
	}

	// Create Consumers
	for (int i = 0; i < consumersQuantity; i++) {
		consumersList[i] = newConsumer(i, consumerCapacity);
	}

	// Create Producers threads
	for (int i = 0; i < producersQuantity; i++) {
		ProduceArgs* args = malloc(sizeof(ProduceArgs));
		args->producer = producersList[i];
		pthread_create(&producers[i], NULL, produce, args);
	}

	// Create Consumers threads
	for (int i = 0; i < consumersQuantity; i++) {
		ConsumeArgs* args = malloc(sizeof(ConsumeArgs));
		args->consumer = consumersList[i];
		pthread_create(&consumers[i], NULL, consume, args);
	}

	printf("===\n");

	// Start Producers
	for (int i = 0; i < producersQuantity; i++) {
		Producer *producer = producersList[i];
		pthread_join(producers[i], NULL);
		printf("[Producer %d] produced %d of %d.\n", producer->id, producer->production, bufferSize);
	}

	// Start Consumers
	for (int i = 0; i < consumersQuantity; i++) {
		Consumer *consumer = consumersList[i];
		pthread_join(consumers[i], NULL);
		printf("[Consumer %d] consumed %d of %d.\n", consumer->id, consumer->consumption, bufferSize);
	}

	// Destroy resources
	sem_unlink(EMPTY_SEMAPHORE_NAME);
	sem_unlink(FULL_SEMAPHORE_NAME);
	pthread_mutex_destroy(&resources);

	// Free memory
	freeMemory(producersList, producersQuantity, consumersList, consumersQuantity);

	printf("===\n");

}