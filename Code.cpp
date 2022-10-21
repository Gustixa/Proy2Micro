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
pthread_cond_t condTruckFueler;
pthread_barrier_t barrierStations;

int totalHoldings = 0;

struct GasStation{
	int ID;
	int amountCars;
	int holdings = 5000;
	std::vector<int> prices;
	int price;
} data;

void *gasStation(void *argument);
void *gasPrice(void *argument);
void *fillGas(void *argument);
int amountGasStationInput();
int initialInvestmentInput();

int main(int argc, char *argv[]) {
	
	int amountGasStation = amountGasStationInput();
	int initialInvestment = initialInvestmentInput();
	
	data.holdings = initialInvestment;
	
	pthread_t GasStation[amountGasStation];
	pthread_t trucks[amountGasStation];
	
	pthread_mutex_init(&mutexCar, NULL);
    pthread_cond_init(&condTruckFueler,NULL);
    pthread_barrier_init(&barrierStations,0,amountGasStation+1);
	int i;
	srand(time(NULL));

	for (i = 1; i < amountGasStation+1; i++) {
		data.ID = i;
		
		int amountCars = rand() % 100;
		data.amountCars = amountCars;
		
		data.prices.clear();
		for (int j = 0; j < amountCars; j++) {
			data.prices.push_back(rand() % 400);
		}
		struct GasStation *parameter = (struct GasStation*)malloc(sizeof(struct GasStation));
		*parameter = data;
		if (pthread_create(&GasStation[i], NULL, &gasStation,parameter)!=0) {
			perror("Failed to create the Gas Station thread.\n");
		}
	}
	pthread_barrier_wait(&barrierStations);
	struct GasStation *result;
	for (i = 1; i < amountGasStation+1; i++) {
		if (pthread_join(GasStation[i], (void**)&result) != 0){
			perror("Failed to join the current thread (Gas Station Thread), to the main thread.\n");
		}
	}
	
	pthread_mutex_destroy(&mutexCar);
	pthread_cond_destroy(&condTruckFueler);
	pthread_barrier_destroy(&barrierStations);
	return 0;
}

int amountGasStationInput() {
	int amountGasStation = 0;
	bool next_step = false;
	do {
		try {
			printf("Owned Gas stations (1-3): ");
			scanf("%d", &amountGasStation);
			if (amountGasStation < 1 || amountGasStation > 3){
				throw 404;
			}
			else {
				next_step = true;
			}
		}
		catch (int x) {
			printf("\nInput error, do it again :v  %d\n", x);
		}
	} while (!next_step);
	return amountGasStation;
}

int initialInvestmentInput() {
	int initialInvestment = 0;
	bool next_step = false;
	do {
		try {
			printf("Initial investment per station in Q: suggested (Q250 - Q5000): ");
			scanf("%d", &initialInvestment);
			if (initialInvestment < 100 || initialInvestment > 25000){
				throw 404;
			}
			else {
				next_step = true;
			}
		}
		catch (int x) {
			printf("\nInput error, do it again :v  %d", x);
		}
	} while (!next_step);
	return initialInvestment;
}


void *gasStation(void *argument) {
	pthread_barrier_wait(&barrierStations);
	struct GasStation *Station = (struct GasStation *)argument;
	pthread_t cars[Station->amountCars];
	
	int i = 0;
	printf("Gas station No.%d had %d buyers today.\n", Station->ID, Station->amountCars);
	GasStation *Result;
	for (i = 0; i < Station->amountCars; i++) {
		Station->price = Station->prices[i];
		struct GasStation *dataCar = (struct GasStation*)malloc(sizeof(struct GasStation));
		*dataCar = *Station;
		
		if(pthread_create(&cars[i], NULL, &gasPrice, dataCar) != 0){
            perror("Failed to create the car thread.\n");
		}
	}
	
	for(i = 0; i < Station->amountCars;i++){
	    if(pthread_join(cars[i], (void**)&Result) != 0){
	        perror("Failed to join the car thread");
	    }
	    Station->holdings = Result->holdings;
	}
	
	return (void*)argument;
}

void *gasPrice(void *argument) {
	struct GasStation *Station = (struct GasStation *)argument;
	struct GasStation *Result = (struct GasStation *)malloc(sizeof(struct GasStation));
	
	pthread_mutex_lock(&mutexCar);
	
	if (Station->price < Station->holdings) {
		Station->holdings -= int(Station->price*0.85);
		totalHoldings += Station->price;
		printf("Car purchase of: Q%d at station No.%d || Product remaining: Q%d\n", Station->price, Station->ID, Station->holdings);
		printf("Total Holdings: Q%d\n", totalHoldings);
	}else{
	    
		Station->holdings += 5000;
		totalHoldings -= 5000;

		printf("Refueled Q5000 at Station No.%d\n",Station->ID);
		printf("Total Holdings: Q%d\n", totalHoldings);
	}
	*Result = *Station;
	
	pthread_mutex_unlock(&mutexCar);
	return (void*)Result;
}
