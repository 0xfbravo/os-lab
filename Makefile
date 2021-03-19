all: run_dp.o run_pc.o

# --
# Dining Philosophers
#--
run_dp.o: dp.o
	gcc dp.o dining_philosophers/run_dining_philosophers.c -o run_dining_philosophers.o -O3
	rm -rf dp.o

dp.o: dining_philosophers/dining_philosophers.h dining_philosophers/dining_philosophers.c
	gcc -c dining_philosophers/dining_philosophers.c -o dp.o -O3

# --
# Producer-Consumer
# --
run_pc.o: pc.o
	gcc pc.o producer_consumer/run_producer_consumer.c -o run_producer_consumer.o -O3
	rm -rf pc.o

pc.o: producer_consumer/producer_consumer.h producer_consumer/producer_consumer.c
	gcc -c producer_consumer/producer_consumer.c -o pc.o -O3

# --
# Utils
# --
clean:
	rm -rf *.o *.gch