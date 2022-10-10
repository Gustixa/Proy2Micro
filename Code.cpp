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
#include <vector>
#include <random>
using namespace std;

pthread_mutex_t mutexCar;
pthread_cond_t condFillingGasStation;
pthread_barrier_t barrierGasStations;
int amountGasToFill = 10000; // This value, represente the amount of gas, but in quetzales.
int gasPerGasStation = 2000; // This value is in quetzales. Could be in global, but try to avoid the global variables.


struct GasStation
{
	int stationID;
	
	int carAmount = 25;
	int purchaseAmount = 150;
	
} stationData;


void *gasStation(void *argument);
void *carPurchase(void *argument);
void *fillGas(void *argument);


int main(int argc, char *argv[])
{
	cout << "Ingrese la cantidad de gasolineras iniciales: ";
	int gasStations;
	cin >> gasStations;
	
	pthread_t numGasStation[gasStations];
	pthread_mutex_init(&mutexCar, NULL);
	pthread_cond_init(&condFillingGasStation, NULL);
	pthread_barrier_init(&barrierGasStations, NULL, gasStations);
	
	int i;
	
	for (i = 0; i < gasStations; i++)
	{
		if (pthread_create(&numGasStation[i], NULL, &gasStation, stationData) != 0) // modified the forth NULL, if considered to pass a parameter to the method.
		{
			perror("Failed to create the thread.");
		}
	}
	
	for (i = 0; i < gasStations; i++)
	{
		if (pthread_join(numGasStation[i], NULL) != 0)
		{
			perror("Failed to join the current thread, to the main thread.");
		}
	}
	
	pthread_cond_destroy(&condFillingGasStation);
	pthread_mutex_destroy(&mutexCar);
	return 0;
}

void *gasStation(void *argument)
{
	cout << "Thread";
	srand(time(NULL));
	int carsArriving = rand() % 200; // RandGenerate Cars(0 - 199) How many cars visit a gas station in a day.
	
	pthread_t cars[carsArriving];
	int i = 0;
	for (i = 0; i < carsArriving; i++)
	{
		if (pthread_create(&cars[i], NULL, &carPurchase, NULL) != 0)
		{
			perror("Failed to create the thread");
		}
	}
	for (i = 0; i < carsArriving; i++)
	{
		if (pthread_join(cars[i], NULL) != 0) // Modified, if consideres to receive a paramter from the method.
		{
			perror("Failed to join the thread.");
		}
	}
	return 0;
}

void *carPurchase(void *argument)
{
	cout << "Thread";
	srand(time(NULL));

	int purchasedAmount = rand() % 450; // RandGenerate Q(0 - 449) How much a car spends per purchase.
	pthread_mutex_lock(&mutexCar);
	gasPerGasStation -= purchasedAmount;
	pthread_mutex_unlock(&mutexCar);
	return 0;
}

void *fillGas(void *argument)
{
	return 0;
}