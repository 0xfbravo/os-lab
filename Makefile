all: run_dp.o run_pc.o

# --
# Dining Philosophers
#--
run_dp.o: dp.o
	gcc dining_philosophers/run_dining_philosophers.c -o run_dining_philosophers.o
	rm -rf dp.o

dp.o: dining_philosophers/dining_philosophers.c dining_philosophers/dining_philosophers.h
	gcc -c dining_philosophers/dining_philosophers.c -o dp.o

# --
# Producer-Consumer
# --
run_pc.o: pc.o
	gcc producer_consumer/run_producer_consumer.c -o run_producer_consumer.o
	rm -rf pc.o

pc.o: producer_consumer/producer_consumer.c producer_consumer/producer_consumer.h
	gcc -c producer_consumer/producer_consumer.c -o pc.o

# --
# Utils
# --
clean:
	rm -rf *.o *.gch