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

pthread_mutex_t mutexCar, mutexGas;
pthread_cond_t condFillingGasStation;
pthread_barrier_t barrierGasStations;
int myEarnings = 10000; // Starting capital to reinvest

struct GasStation{
	int stationID;
	int carID;
	int carSpending;
	int carsArriving;
	int gasAmount = 7500;
} Data;

void *gasStation(void *args);
void *carPurchase(void *args);

int main(int argc, char *argv[])
{
	cout << "How many gas stations do you want to generate? : ";
	int gasStations;
	cin >> gasStations;
	pthread_t numGasStation[gasStations];
	pthread_mutex_init(&mutexGas, NULL);
	pthread_mutex_init(&mutexCar, NULL);
	pthread_cond_init(&condFillingGasStation, NULL);
	pthread_barrier_init(&barrierGasStations, NULL, gasStations);
	int i;
	for (i = 0; i < gasStations+1; i++)
	{
		Data.stationID = i;
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
	srand(time(NULL));
	LocalData.carsArriving = rand() % 10; // RandGenerate Cars(0 - 9) How many cars visit a gas station in a day.
	LocalData.stationID = arguments->stationID;
	pthread_t cars[LocalData.carsArriving];
	int i = 0;

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
		if (pthread_join(cars[i], NULL) != 0)
		{
			perror("\nFailed to join the thread.");
		}
	}
	pthread_mutex_unlock(&mutexGas);
	return (void*)arguments;
}

void *carPurchase(void *args)
{
	struct GasStation *arguments = (struct GasStation *)args;

	srand(time(NULL));
	int carSpending = rand() % 450; // RandGenerate Q(0 - 449) How much a car spends per purchase.
	
	if (carSpending > arguments->gasAmount){
		if (myEarnings < 7500){
			cout << "\n-----------FRANCHISE IS BROKE-------------";
			return 0;
		}else{
			cout << "\nA car (" << arguments->carID+1 << ") has attempted to purchase Q" << carSpending << " at station No." << arguments->stationID << ", but it only had: Q" << arguments->gasAmount << " left in stock, so the purchase was declined and Q7500 were refilled to the station";
			arguments->gasAmount += 7500;
			myEarnings -= 7500;
		}
	}else{
		arguments->gasAmount -= carSpending;
		myEarnings += carSpending;
		cout << "\nA car (" << arguments->carID << ") has purchased Q" << carSpending << " at station No." << arguments->stationID << "\nGas remaining at station No." << arguments->stationID << ": " << arguments->gasAmount << "\nMy Total Earnings: Q" << myEarnings;
	}
	return (void*)arguments;
}