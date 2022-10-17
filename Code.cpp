/**
 * @file Code.cpp
 * @author Josúe Samuel Argueta Hernánddez (arg211024@uvg.edu.gt)
 * @brief
 * @version 0.1
 * @date 2022-10-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>

pthread_mutex_t mutexCar;
pthread_cond_t condFillingGasStation;
pthread_barrier_t barrierGasStations;
int amountGasToFill = 10000; // This value, represente the amount of gas, but in quetzales.
int gasPerGasStation = 4000; // This value is in quetzales. Could be in global, but try to avoid the global variables.
struct GasStation
{
    int amountCars;
    int profits;
} data;

// Prototypes
void *gasStation(void *argument);
void *gasPrice(void *argument);
void *fillGas(void *argument);
int amountGasStationInput();
/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    int amountGasStation = amountGasStationInput();

    pthread_t numGasStation[amountGasStation * 2]; // times 2, becasuse, we need the same amount of gas station and tricks to fill it.

    pthread_mutex_init(&mutexCar, NULL);
    pthread_cond_init(&condFillingGasStation, NULL);
    pthread_barrier_init(&barrierGasStations, NULL, amountGasStation);
    int i;
    for (i = 0; i < amountGasStation * 2; i++)
    {

        if (i < amountGasStation)
        {
            printf("Gasolinera NO. %d\n", i);
            // Creating the trucks to fill the gas station when there is no more gas.
            if (pthread_create(&numGasStation[i], NULL, &fillGas, NULL) != 0)
            {
                perror("Failed to create the thread");
            }
        }
        else
        {
            printf("Camion NO. %d\n", i);
            // Creating the gas Stations.
            if (pthread_create(&numGasStation[i], NULL, &gasStation, NULL) != 0) // modified the forth NULL, if considered to pass a parameter to the method.
            {
                perror("Failed to create the thread.");
            }
        }
    }
    for (i = 0; i < amountGasStation * 2; i++)
    {
        if (i < amountGasStation)
        {
            if (pthread_join(numGasStation[i], NULL) != 0)
            {
                perror("Failed to join the current thread, to the main thread.");
            }
        }
        else
        {
            if (pthread_join(numGasStation[i], NULL) != 0)
            {
                perror("Failed to join the current thread, to the main thread.");
            }
        }
    }
    pthread_cond_destroy(&condFillingGasStation);
    pthread_mutex_destroy(&mutexCar);
    return 0;
}

/**
 * @brief
 *
 * @return int
 */
int amountGasStationInput()
{
    int amountGasStation = 0;
    bool next_step = false;

    do
    {
        try
        {
            printf("\nIngrese la cantidad de gasolineras con las cuales desea iniciar su franquicia! (1-3): ");
            scanf("%d", &amountGasStation);
            if (amountGasStation < 1 || amountGasStation > 3)
            {
                throw 404;
            }
            else
            {
                next_step = true;
            }
        }
        catch (int x)
        {
            printf("\nDebe ingresar un valor entre el rango %d", x);
        }
    } while (!next_step);
    return amountGasStation;
}
/**
 * @brief
 *
 * @param argument
 * @return void*
 */
void *gasStation(void *argument)
{
    srand(time(NULL));
    int amountCars = rand() % 200;
    pthread_t cars[amountCars];
    int i = 0;
    for (i = 0; i < amountCars; i++)
    {
        if (pthread_create(&cars[i], NULL, &gasPrice, NULL) != 0)
        {
            perror("Failed to create the thread");
        }
    }
    for (i = 0; i < amountCars; i++)
    {
        if (pthread_join(cars[i], NULL) != 0) // Modified, if consideres to receive a paramter from the method.
        {
            perror("Failed to join the thread.");
        }
    }
    return 0;
}

/**
 * @brief
 *
 * @param argument
 * @return void*
 */
void *gasPrice(void *argument)
{
    srand(time(NULL));
    int valor = rand() % 400;
    pthread_mutex_lock(&mutexCar);
    gasPerGasStation -= valor;
    printf("%d\n", gasPerGasStation);
    pthread_mutex_unlock(&mutexCar);
    pthread_cond_broadcast(&condFillingGasStation);
    return 0;
}

/**
 * @brief
 *
 * @param argument
 * @return void*
 */
void *fillGas(void *argument)
{
    pthread_mutex_lock(&mutexCar);
    // Putting the truck on waiting mode, till the amount of gas in the gas station is lower than 500.
    while (gasPerGasStation > 500)
    {
        pthread_cond_wait(&condFillingGasStation, &mutexCar);
    }
    gasPerGasStation += amountGasToFill;
    printf("Gasolinera recargada!\n");

    pthread_mutex_unlock(&mutexCar);
    return 0;
}
