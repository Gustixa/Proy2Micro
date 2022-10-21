/**
 * @file Code.cpp
 * @author Josúe Samuel Argueta Hernández   211024  (arg211024@uvg.edu.gt)
 * @author Alejandro José Martínez de León  21430   (mar21430@uvg.edu.gt)
 * @brief
 * @version 0.1
 * @date 2022-10-02
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <string>
#include <iostream>

#define AMOUNT_CARS 3

pthread_mutex_t mutexStation;
pthread_mutex_t mutexCar;

int totalHoldings = 0;

struct GasStation{
	int ID;
	int amountCars;
	int holdings = 5000;
	std::vector<int> prices;
	int price;
	int profitMargins;
} data;

void *gasStation(void *argument);
void *gasPrice(void *argument);
void *fillGas(void *argument);
int amountGasStationInput();
int initialInvestmentInput();
int profitMarginInput();

int main(int argc, char *argv[]) {
	
	int amountGasStation = amountGasStationInput();
	int initialInvestment = initialInvestmentInput();
	int profitMargins = 0;
	
	data.holdings = initialInvestment;
	
	pthread_t GasStation[amountGasStation];
	pthread_t trucks[amountGasStation];
	
	pthread_mutex_init(&mutexStation, NULL);
	pthread_mutex_init(&mutexCar, NULL);
	
	int i;
	srand(time(NULL));
    while(true){
        printf("\n\nMy Account: Q%d", totalHoldings);
        if (totalHoldings < 0){
            printf("\n!!!WARNING!!! You are in debt. Increase profit margins to offset losses.");
        }
        printf("\nStart a new day: ");
        std::string Var = "";
		profitMargins = profitMarginInput();
    	for (i = 1; i < amountGasStation+1; i++) {
    		data.ID = i;
    		
    		int amountCars = (rand() % 90) + 10; 
    		data.amountCars = amountCars;
    		
    		data.profitMargins = profitMargins += (rand() % 5) - 2;
    		
    		data.prices.clear();
    		for (int j = 0; j < amountCars; j++) {
    			data.prices.push_back((rand() % 375) + 25);
    		}
    		struct GasStation *parameter = (struct GasStation*)malloc(sizeof(struct GasStation));
    		*parameter = data;
    		if (pthread_create(&GasStation[i], NULL, &gasStation,parameter)!=0) {
    			perror("Failed to create the Gas Station thread.\n");
    		}
    	}
    	
    	struct GasStation *result;
    	for (i = 1; i < amountGasStation+1; i++) {
    		if (pthread_join(GasStation[i], NULL) != 0){
    			perror("Failed to join the current thread (Gas Station Thread), to the main thread.\n");
    		}
    	}
    }
	
	pthread_mutex_destroy(&mutexStation);
	pthread_mutex_destroy(&mutexCar);
	return 0;
}

int amountGasStationInput() {
	int amountGasStation = 0;
	bool next_step = false;
	do {
		try {
			printf("Owned Gas stations (1-4): "); 
			scanf("%d", &amountGasStation);
			if (amountGasStation < 1 || amountGasStation > 4){
				throw 404;
			}
			else {
				next_step = true;
			}
		}
		catch (int x) {
			printf("Input error%d\n", x);
		}
	} while (!next_step);
	return amountGasStation;
}

int initialInvestmentInput() {
	int initialInvestment = 0;
	bool next_step = false;
	do {
		try {
			printf("Initial investment per station (Q0 - Q1,000,000): ");
			scanf("%d", &initialInvestment);
			if (initialInvestment < 0 || initialInvestment > 1000000){
				throw 404;
			}
			else {
				next_step = true;
			}
		}
		catch (int x) {
			printf("Input error%d\n", x);
		}
	} while (!next_step);
	return initialInvestment;
}

int profitMarginInput() {
	int profitMargin = 0;
	bool next_step = false;
	do {
		try {
			printf("Please enter today's profit margins you want to use (-100%% - 100%%): ");
			scanf("%d", &profitMargin);
			if (profitMargin < -100 || profitMargin > 100){
				throw 404;
			}
			else {
				next_step = true;
			}
		}
		catch (int x) {
			printf("Input error%d\n", x);
		}
	} while (!next_step);
	return profitMargin;
}

void *gasStation(void *argument) {
	
	struct GasStation *Station = (struct GasStation *)argument;
	pthread_mutex_lock(&mutexStation);
	pthread_t cars[Station->amountCars];
	
	int i = 0;
	printf("\n------------------------Gas station No.%d had %d buyers today, and its margins were of %d%%------------------------\n", Station->ID, Station->amountCars, Station->profitMargins);
	GasStation *Result;
	for (i = 0; i < Station->amountCars; i++) {
		Station->price = Station->prices[i];
		struct GasStation *dataCar = (struct GasStation*)malloc(sizeof(struct GasStation));
		*dataCar = *Station;
		
		pthread_create(&cars[i], NULL, &gasPrice, dataCar);
		
		pthread_join(cars[i], (void**)&Result);
		Station->holdings = Result->holdings;
	}
	pthread_mutex_unlock(&mutexStation);
	return 0;
}

void *gasPrice(void *argument) {
	
	struct GasStation *Station = (struct GasStation *)argument;
	struct GasStation *Result = (struct GasStation *)malloc(sizeof(struct GasStation));
	
	pthread_mutex_lock(&mutexCar);
	
	if (Station->price < Station->holdings) {
		
		printf("\nCar purchase of: Q%d at station No.%d || Product before: Q%d", Station->price, Station->ID, Station->holdings);
		Station->holdings -= int(Station->price*(100-Station->profitMargins)/100);
		printf(". Now remaining: Q%d\n", Station->holdings);

		if (Station->price - int(Station->price*(100-Station->profitMargins)/100) > 0) {
	    	printf("Made a profit of: %dQ",(Station->price - int(Station->price*(100-Station->profitMargins)/100)));
	    	totalHoldings += Station->price;
	    	printf(" || Total Holdings: Q%d\n",  totalHoldings);
	    	
		}else{
		    printf("Made a loss of: %dQ",(Station->price - int(Station->price*(100-Station->profitMargins)/100)));
		    totalHoldings += Station->price + Station->price - int(Station->price*(100-Station->profitMargins)/100);
		    printf(" || Total Holdings: Q%d\n",  totalHoldings);
		}
	}else{
		Station->holdings += 5000;
		totalHoldings -= 5000;
		printf("\nCar attempted a failed purchase of: Q%d at station No.%d || Car was declined and Refueling order was sent.\n", Station->price, Station->ID);
		printf("Refueled Q5000 at Station No.%d",Station->ID);
		printf(" || Total Holdings: Q%d\n",  totalHoldings);
	}
	*Result = *Station;
	
	pthread_mutex_unlock(&mutexCar);
	return (void*)Result;
}
