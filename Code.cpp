/**
 * @file Code.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutexCar;
int none;

// Prototypes
void *gasStation(void *argument);
void *gasPrice(void *argument);
void *fillGas(void *argument);

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    int amountGasStation;
    pthread_t numGasStation[amountGasStation];
    pthead_mutex_init(&mutexCar);

    pthread_mutex_destroy(&mutexCar);
    return 0;
}

void *gasStation(void *argument)
{
}

void *gasPrice(void *argument)
{
}

void *fillGas(void *argument)
{
}
