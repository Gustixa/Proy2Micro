/**
 * @file Code.cpp
 * @author Josúe Samuel Argueta Hernández   211024  (arg211024@uvg.edu.gt)
 * @author Alejandro José Martínez de León  21430   (mar21430@uvg.edu.gt)
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

int amountGasToFill = 10000;    // This value, represente the amount of gas, but in quetzales.
int amountGasPerStation = 6000; // This value is in quetzales. Could be in global, but try to avoid the global variables.
int gains = 0;

struct GasStation{
	int station;
	int amountCars;
	int holdings = 6000;
	std::vector<int> prices;
} data;

struct Car{
	int station;
	int price;
} Current_car;

void *gasStation(void *argument);
void *gasPrice(void *argument);
void *fillGas(void *argument);
int amountGasStationInput();

int main(int argc, char *argv[]){
	
	int amountGasStation = amountGasStationInput();
	pthread_t GasStation[amountGasStation]; // times 2, becasuse, we need the same amount of gas station and tricks to fill it.
	pthread_t trucks[amountGasStation];
	
	pthread_mutex_init(&mutexCar, NULL);
	
	int i;

	for (i = 0; i < amountGasStation; i++){
		data.station = i;
		
		int amountCars = rand() % 20;
		data.amountCars = amountCars;
		
		data.prices.clear();
		for (int j = 0; j < amountCars; j++){
			data.prices.push_back(rand() % 400);
		}
		
		if (pthread_create(&GasStation[i], NULL, &gasStation, (void *)&data) != 0){
			perror("Failed to create the Gas Station thread.\n");
		}
	}
	
	struct GasStation *result;
	for (i = 0; i < amountGasStation; i++){
		if (pthread_join(GasStation[i], NULL) != 0){
			perror("Failed to join the current thread (Gas Station Thread), to the main thread.\n");
		}
	}

	pthread_cond_destroy(&condFillingGasStation);
	pthread_mutex_destroy(&mutexCar);
	return 0;
}

int amountGasStationInput(){
	int amountGasStation = 0;
	bool next_step = false;
	do{
		try{
			printf("\nIngrese la cantidad de gasolineras con las cuales desea iniciar su franquicia! (1-3): ");
			scanf("%d", &amountGasStation);
			if (amountGasStation < 1 || amountGasStation > 3){
				throw 404;
			}
			else{
				next_step = true;
			}
		}
		catch (int x){
			printf("\nDebe ingresar un valor entre el rango %d", x);
		}
	} while (!next_step);
	return amountGasStation;
}

void *gasStation(void *argument){
	
	struct GasStation *Station = (struct GasStation *)argument;
	
	pthread_t cars[Station->amountCars];
	int i = 0;
	printf("Cantidad de carros para la gasolinera %d: %d\n", Station->station, Station->amountCars);
	for (i = 0; i < Station->amountCars; i++)
	{
		Current_car.station = Station->station;
		Current_car.price = Station->prices[i];
	   
		if (pthread_create(&cars[i], NULL, &gasPrice, (void*)&Current_car) != 0)
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

void *gasPrice(void *argument){
	
	struct Car *Car_Purchase = (struct Car *)argument;
	pthread_mutex_lock(&mutexCar);
	
	int price = Car_Purchase->price;
	
	if (price < amountGasPerStation){
		amountGasPerStation -= price;
		printf("Gasoline remaining: %d\n", amountGasPerStation);
		gains += price;
		printf("Car purchase of: Q%d at station No.%d\n", price, Car_Purchase->station);
		printf("Total Holdings: %d\n", gains);
	}else{
		amountGasPerStation += 5000;
		gains -= 5000;
		printf("Refueled Q5000");
	}
	
	pthread_mutex_unlock(&mutexCar);
	return 0;
}