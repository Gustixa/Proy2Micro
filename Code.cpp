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
    int ID;
    int amountCars;
    int holdings = 1000;
    std::vector<int> prices;
    int price;
} data;


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
    srand(time(NULL));

    for (i = 1; i < amountGasStation+1; i++) {
        data.ID = i;
        
        int amountCars = rand() % 20;
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
    
    struct GasStation *result;
    for (i = 1; i < amountGasStation+1; i++) {
        if (pthread_join(GasStation[i], NULL) != 0){
            perror("Failed to join the current thread (Gas Station Thread), to the main thread.\n");
        }
    }

    pthread_cond_destroy(&condFillingGasStation);
    pthread_mutex_destroy(&mutexCar);
    return 0;
}

int amountGasStationInput() {
    int amountGasStation = 0;
    bool next_step = false;
    do {
        try {
            printf("\nIngrese la cantidad de gasolineras con las cuales desea iniciar su franquicia! (1-3): ");
            scanf("%d", &amountGasStation);
            if (amountGasStation < 1 || amountGasStation > 3){
                throw 404;
            }
            else {
                next_step = true;
            }
        }
        catch (int x) {
            printf("\nDebe ingresar un valor entre el rango %d", x);
        }
    } while (!next_step);
    return amountGasStation;
}


void *gasStation(void *argument) {
    
    struct GasStation *Station = (struct GasStation *)argument;
    pthread_t cars[Station->amountCars];
    
    int i = 0;
    printf("Cantidad de carros para la gasolinera %d: %d\n", Station->ID, Station->amountCars);
    for (i = 0; i < Station->amountCars; i++) {
        Station->price = Station->prices[i];
        struct GasStation *dataCar = (struct GasStation*)malloc(sizeof(struct GasStation));
        *dataCar = *Station;
        if (pthread_create(&cars[i], NULL, &gasPrice, dataCar) != 0) {
            perror("Failed to create the car thread.\n");
        }
    }
    struct GasStation *result;
    for (i = 0; i < Station->amountCars; i++) {
        if (pthread_join(cars[i], (void**)&result) != 0) {
            perror("Failed to join the car thread.\n");
        }
        free(result);
    }
    *Station = *result;
    
    return 0;
}

void *gasPrice(void *argument) {
    
    struct GasStation *Station = (struct GasStation *)argument;
    
    pthread_mutex_lock(&mutexCar);
    
    if (Station->price < Station->holdings) {
        Station->holdings -= Station->price;
        gains += Station->price;
        printf("Car purchase of: Q%d at station No.%d || Gasoline remaining:%d\n", Station->price, Station->ID, Station->holdings);
        printf("Total Holdings: %d\n", gains);
    }else{
        Station->holdings += 5000;
        gains -= 5000;
        printf("Refueled Q5000");
    }
    
    pthread_mutex_unlock(&mutexCar);
    argument = Station;
    *(struct GasStation*)  argument;
    return argument;
}