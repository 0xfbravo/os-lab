# os-lab

Dining philosophers problem and Producer-Consumer problem implementation in C

## About

This program was written and tested on a MacBook Pro (13-inch, 2020) with these specs:

- Processor: 2 GHz Quad-Core Intel Core i5
- Memory: 16 GB 3733 MHz LPDDR4X

---

## Running

To execute the program just guarantee that you have the `gcc` installed.

After that, navigates to this folder and runs `make` command in the terminal.

Then two compiled programs will appear: `run_dining_philosophers.o` and `run_producer_consumer.o`.

---

To execute *Dining Philosophers* run, in terminal, the command `./run_dining_philosophers.o philosophersQuantity philosopherThinkingTime philosopherEatingTime` like the e.g. below:

    ./run_dining_philosophers.o 5 2 2

To execute *Producer-Consumer* run, in terminal, the command `./run_producer_consumer.o bufferSize producersQuantity producerCapacity consumersQuantity consumerCapacity` like the e.g. below:

    ./run_producer_consumer.o 100 1 10 2 10

