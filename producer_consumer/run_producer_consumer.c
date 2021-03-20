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

	// Reads user input
	int bufferSize = strtol(argv[1], NULL, 10);
	int producersCount = strtol(argv[2], NULL, 10);
	int consumersCount = strtol(argv[3], NULL, 10);

	printf("Producer-Consumer: [Executing with: BufferSize %d, %d Producers and %d Consumers]\n", bufferSize, producersCount, consumersCount);
	printf("===\n");

	// Creates a new Buffer
	int* buffer = malloc(sizeof(int) * bufferSize);
	int totalProduction = 0;
	int totalComsuption = 0;
	Producer** producersList = newProducersListOfSize(producersCount);
	Consumer** consumersList = newConsumersListOfSize(consumersCount);

	// Creates Producers and Consumers
	pthread_t producers[producersCount], consumers[consumersCount];
	pthread_mutex_t resources;
	pthread_setconcurrency(producersCount+consumersCount);

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
		args->buffer = buffer;
		args->bufferSize = bufferSize;
		args->resources = &resources;
		args->totalProduction = &totalProduction;
		args->producer = producersList[i];
		pthread_create(&consumers[i], NULL, produce, args);
	}

	// Create Consumers threads
	for (int i = 0; i < consumersCount; i++) {
		ConsumeArgs* args = malloc(sizeof(ConsumeArgs));
		args->buffer = buffer;
		args->bufferSize = bufferSize;
		args->resources = &resources;
		args->totalConsumption = &totalComsuption;
		args->consumer = consumersList[i];
		pthread_create(&consumers[i], NULL, consume, args);
	}

	// Start Producers
	for (int i = 0; i < producersCount; i++) {
		pthread_join(producers[i], NULL);

		int production = producersList[i]->production;
		if (production == 0) {
			printf("The [Producer %d] didn't produced anything.\n", i);
		}
		else {
			printf("The [Producer %d] produced the [Product %d]\n", i, production);
		}
	}

	// Start Consumers
	for (int i = 0; i < consumersCount; i++) {
	}

	// Destroy resources
	pthread_mutex_destroy(&resources);

	printf("===\n");

}