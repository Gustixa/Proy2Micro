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
	int gasolineraID;
	
	int cantidadDeCarros = 25;
	int gananciaPorCarro = 150;
	
} data;


void *gasStation(void *argument);
void *gasPrice(void *argument);
void *fillGas(void *argument);


int main(int argc, char *argv[])
{
	cout << "Ingrese la cantidad de gasolineras iniciales: ";
	int amountGasStation;
	cin >> amountGasStation;
	
	pthread_t numGasStation[amountGasStation];
	pthread_mutex_init(&mutexCar, NULL);
	pthread_cond_init(&condFillingGasStation, NULL);
	pthread_barrier_init(&barrierGasStations, NULL, amountGasStation);
	
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

void *gasPrice(void *argument)
{
	cout << "Thread";
	srand(time(NULL));
	int valor = rand() % 600;
	pthread_mutex_lock(&mutexCar);
	gasPerGasStation -= valor;
	pthread_mutex_unlock(&mutexCar);
	return 0;
}

void *fillGas(void *argument)
{
	return 0;
}