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
#include <random>
using namespace std;

pthread_mutex_t mutexCar;
pthread_cond_t condFillingGasStation;
pthread_barrier_t barrierGasStations;
int amountGasToFill = 10000; // This value, represente the amount of gas, but in quetzales.
int gasPerGasStation = 2000; // This value is in quetzales. Could be in global, but try to avoid the global variables.

struct GasStation{
	int stationID;
	int carID;
	int carSpending;
	int carsArriving;
	int gasAmount = 2000;
} Data;


void *gasStation(void *args);
void *carPurchase(void *args);
void *fillGas(void *args);


int main(int argc, char *argv[])
{
	cout << "How many gas stations do you want to generate? : ";
	int gasStations;
	cin >> gasStations;
	
	pthread_t numGasStation[gasStations];
	pthread_mutex_init(&mutexCar, NULL);
	pthread_cond_init(&condFillingGasStation, NULL);
	pthread_barrier_init(&barrierGasStations, NULL, gasStations);
	int i;
	
	for (i = 0; i < gasStations; i++)
	{
		Data.stationID = i;
		//cout << Data.stationID;
		if (pthread_create(&numGasStation[i], NULL, &gasStation, (void*)&Data) != 0) // modified the forth NULL, if considered to pass a parameter to the method.
		{
			perror("\nFailed to create the thread.");
		}
	}
	
	for (i = 0; i < gasStations; i++)
	{
		if (pthread_join(numGasStation[i], NULL) != 0)
		{
			perror("\nFailed to join the current thread, to the main thread.");
		}
	}
	
	pthread_cond_destroy(&condFillingGasStation);
	pthread_mutex_destroy(&mutexCar);
	return 0;
}

void *gasStation(void *args)
{
	struct GasStation *arguments = (struct GasStation *)args;
	GasStation LocalData;

	LocalData.carsArriving = rand() % 10; // RandGenerate Cars(0 - 9) How many cars visit a gas station in a day.
	LocalData.stationID = arguments->stationID;
	
	pthread_t cars[LocalData.carsArriving];
	int i = 0;

	srand(time(NULL));
	for (i = 0; i < LocalData.carsArriving; i++)
	{
		LocalData.carID = i;
		if (pthread_create(&cars[i], NULL, &carPurchase, (void*)&LocalData) != 0)
		{
			perror("\nFailed to create the thread");
		}
	}
	for (i = 0; i < LocalData.carsArriving; i++)
	{
		if (pthread_join(cars[i], NULL) != 0) // Modified, if consideres to receive a paramter from the method.
		{
			perror("\nFailed to join the thread.");
		}
	}
	return (void*)arguments;
}

void *carPurchase(void *args)
{
	struct GasStation *arguments = (struct GasStation *)args;

	int carSpending = rand() % 450; // RandGenerate Q(0 - 449) How much a car spends per purchase.
	srand(time(NULL));
	
	arguments->gasAmount -= carSpending;
	cout << "\nA car (" << arguments->carID << ") has purchased Q" << carSpending << " at station No." << arguments->stationID << "\nGas remaining:" << arguments->gasAmount;
	
	return (void*)arguments;
}

void *fillGas(void *argument)
{
	return 0;
}