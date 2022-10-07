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
pthread_cond_t condFillingGasStation;
pthead_barrier_t barrierGasStations;
int amountGasToFill = 10000; // This value, represente the amount of gas, but in quetzales.
struct GasStation
{
    int amountCars;
    int profits;
} data;

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
    pthread_cond_init(&condFillingGasStation, NULL);
    pthread_barrier_init(&barrierGasStations, 0, amountGasStation);
    int i;
    for (i = 0; i < amountGasStation; i++)
    {
        if (pthread_create(&numGasStation[i], NULL, &gasStation, NULL) != 0) // modified the forth NULL, if considered to pass a parameter to the method.
        {
            perror("Failed to create the thread.");
        }
    }
    for (i = 0; i < amountGasStation; i++)
    {
        if (pthread_join(numGasStation[i], NULL) != 0)
        {
        }
    }
    pthread_cond_destroy(&condFillingGasStation);
    pthread_mutex_destroy(&mutexCar);
    return 0;
}

void *gasStation(void *argument)
{

    int gasPerGasStation = 2000; // This value is in quetzales. Could be in global, but try to avoid the global variables.
}

void *gasPrice(void *argument)
{
}

void *fillGas(void *argument)
{
}
