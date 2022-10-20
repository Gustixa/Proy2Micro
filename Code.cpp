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
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <vector>

#define AMOUNT_CARS 3

pthread_mutex_t mutexCar;
pthread_cond_t condFillingGasStation;
pthread_barrier_t barrierGasStations;

int amountGasToFill = 10000;    // This value, represente the amount of gas, but in quetzales.
int amountGasPerStation = 6000; // This value is in quetzales. Could be in global, but try to avoid the global variables.
int gains = 0;
struct GasStation
{
    int station;
    int amountCars;
    // int profits;
    std::vector<int> prices;
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
    pthread_t GasStation[amountGasStation]; // times 2, becasuse, we need the same amount of gas station and tricks to fill it.
    pthread_t trucks[amountGasStation];
    pthread_mutex_init(&mutexCar, NULL);
    pthread_cond_init(&condFillingGasStation, NULL);
    pthread_barrier_init(&barrierGasStations, NULL, AMOUNT_CARS);
    int i;
    srand(time(NULL));
    for (i = 0; i < amountGasStation; i++)
    {

        int amountCars = rand() % 200;
        for (int j = 0; j < amountCars; j++)
        {
            data.prices.push_back(rand() % 400);
        }
        data.amountCars = amountCars;
        data.station = i + 1;

        // Creating the trucks to fill the gas station when there is no more gas.
        if (pthread_create(&GasStation[i], NULL, &gasStation, (void **)&data) != 0)
        {
            perror("Failed to create the Gas Station thread.\n");
        }
        if (pthread_create(&trucks[i], NULL, &fillGas, NULL) != 0)
        {
            perror("Failed to create the currente Thread (Truck thread)\n");
        }
    }
    struct GasStation *result;
    for (i = 0; i < amountGasStation; i++)
    {
        if (pthread_join(GasStation[i], NULL) != 0)
        {
            perror("Failed to join the current thread (Gas Station Thread), to the main thread.\n");
        }
        if (pthread_join(trucks[i], NULL) != 0)
        {
            perror("Failed to join the truck thread.\n");
        }
    }

    pthread_cond_destroy(&condFillingGasStation);
    pthread_mutex_destroy(&mutexCar);
    pthread_barrier_destroy(&barrierGasStations);
    return 0;
}

/**
 * @brief verifying the right input from the user.
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
 * @brief Simulating a Gas Station.
 *
 * @param argument
 * @return void*
 */
void *gasStation(void *argument)
{
    struct GasStation *Station = (struct GasStation *)argument;
    pthread_t cars[Station->amountCars];
    int i = 0;
    printf("Cantidad de carros para la gasolinera %d: %d\n", Station->station, Station->amountCars);
    for (i = 0; i < Station->amountCars + 1; i++)
    {
        int *param = (int *)malloc(sizeof(int));
        *param = Station->prices[i];
        if (pthread_create(&cars[i], NULL, &gasPrice, param) != 0)
        {
            perror("Failed to create the car thread.\n");
        }
    }

    for (i = 0; i < Station->amountCars; i++)
    {
        if (pthread_join(cars[i], NULL) != 0) // Modified, if consideres to receive a paramter from the method.
        {
            perror("Failed to join the car thread.\n");
        }
    }
    return 0;
}

/**
 * @brief Simulating the cars for the gas Station
 *
 * @param argument
 * @return void*
 */
void *gasPrice(void *argument)
{
    int price = *(int *)argument;
    pthread_barrier_wait(&barrierGasStations);
    pthread_mutex_lock(&mutexCar);
    amountGasPerStation -= price;
    // printf("Remanente de gasolina: %d\n", amountGasPerStation);
    gains += price;
    // printf("Compra atcual: %d\n", amountGasPerStation);
    // printf("%d\n", gains);
    pthread_mutex_unlock(&mutexCar);
    pthread_cond_broadcast(&condFillingGasStation);
    free(argument);
    return 0;
}

/**
 * @brief Simulating the trucks to fill the Gas Station.
 *
 * @param argument
 * @return void*
 */
void *fillGas(void *argument)
{
    // if (gains > 2000)
    // {
    pthread_mutex_lock(&mutexCar);
    // adding fuel till the amount of gas in the gas station is lower than 500.
    while (amountGasPerStation > 1000)
    {
        printf("Enough fuel in the gas station\n");
        pthread_cond_wait(&condFillingGasStation, &mutexCar);
    }

    amountGasPerStation += amountGasToFill;

    printf("Gasolinera recargada!\n");
    pthread_mutex_unlock(&mutexCar);
    //    }
    // else
    // {
    //     printf("Not enough money to buy more gas.\n");
    // }

    return 0;
}