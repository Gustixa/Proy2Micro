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

struct GasStation{
	int stationID;
	int carID;
	int carSpending;
	int carsArriving;
} Data;


void *gasStation(void *argument);
void *carPurchase(void *argument);
void *fillGas(void *argument);


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
		if (pthread_create(&numGasStation[i], NULL, &gasStation, (void*)&Data) != 0) // modified the forth NULL, if considered to pass a parameter to the method.
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

void *gasStation(void *args)
{
	struct GasStation *arguments = (struct GasStation *)args;
	struct GasStation *ThreadResult = (GasStation *)malloc(sizeof(GasStation));

	srand(time(NULL));
	ThreadResult->carsArriving = rand() % 200; // RandGenerate Cars(0 - 199) How many cars visit a gas station in a day.
	ThreadResult->stationID = arguments->stationID;

	pthread_t cars[ThreadResult->carsArriving];
	int i = 0;
	for (i = 0; i < ThreadResult->carsArriving; i++)
	{
		ThreadResult->carID = i;
		if (pthread_create(&cars[i], NULL, &carPurchase, (void*)&ThreadResult) != 0)
		{
			perror("Failed to create the thread");
		}
	}
	for (i = 0; i < ThreadResult->carsArriving; i++)
	{
		if (pthread_join(cars[i], NULL) != 0) // Modified, if consideres to receive a paramter from the method.
		{
			perror("Failed to join the thread.");
		}
	}
	return 0;
}

void *carPurchase(void *args)
{
	struct GasStation *arguments = (struct GasStation *)args;
	struct GasStation *ThreadResult = (GasStation *)malloc(sizeof(GasStation));

	ThreadResult->carID = arguments->carID;
	ThreadResult->stationID = arguments->stationID;

	srand(time(NULL));

	ThreadResult->carSpending = rand() % 450; // RandGenerate Q(0 - 449) How much a car spends per purchase.

	cout << "A car (" << ThreadResult->carID << ") has purchased " << ThreadResult->carSpending << " at station No." << ThreadResult->stationID;
	pthread_mutex_lock(&mutexCar);
	gasPerGasStation -= ThreadResult->carSpending;
	pthread_mutex_unlock(&mutexCar);

	return 0;
}

void *fillGas(void *argument)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <numeric>
using namespace std;
struct Thread_Parameters
{
    int ID;
    int Calc;
    int Last_Residue;
    vector<int> Resultado;
} Data;

void* Thread_Function(void* args)
{
    struct Thread_Parameters *arguments = (struct Thread_Parameters *)args;
    struct Thread_Parameters *ThreadResult = (Thread_Parameters *)malloc(sizeof(Thread_Parameters));
    for (int i =0; i < arguments->Calc + arguments->Last_Residue; i++){
        arguments->ID * arguments->Calc;
        ThreadResult->Resultado.push_back( ((arguments->ID) * arguments->Calc) + 1 - arguments->Calc + i);
    }
    ThreadResult->ID = arguments->ID;
    return (void*)ThreadResult;
}

int main(int argc, char *argv[])
{
    vector<int> Suma_Total;
    int P_Threads, Max_Val, Val_N, Max_Threads, Residue;
    cout << "Número de threads a crear:";
    cin >> P_Threads;
    cout << "Valor máximo: ";
    cin >> Max_Val;
    if (Max_Val < P_Threads){
        Val_N = 1;
        Max_Threads = Max_Val+1;
        Residue = 0;
    }else{
        Val_N = Max_Val / P_Threads;
        Max_Threads = P_Threads+1;
        Residue = Max_Val - Val_N * P_Threads;
    }
    cout << "Valores N: " << Val_N << "\n";
    cout << "Residuo: " << Residue << "\n";

	Thread_Parameters *Result;
    pthread_t THREADS[P_Threads];
    for (int i = 1; i < Max_Threads; i++){
        Data.ID = i;
        Data.Calc = Val_N;
        if (Data.ID == P_Threads) {
            Data.Last_Residue = Residue;
        }
        else {
            Data.Last_Residue = 0;
        }
        pthread_create(&THREADS[i], NULL, &Thread_Function, (void *)&Data);
        pthread_join(THREADS[i], (void **)&Result);
        printf("______________\n");
        printf("THREAD: %d\n", Result->ID);
        printf("_______\n");
        printf("Limite Inferior: %d\n", Result->Resultado[0]);
        printf("Limite Superior: %d\n", Result->Resultado.back());
        
        for (int n = 0; n < Result->Resultado.size(); n++){
            printf("%d\n", Result->Resultado[n]);
        }
        printf("Suma: %d\n", accumulate(Result->Resultado.begin(), Result->Resultado.end(), 0));
        Suma_Total.push_back(accumulate(Result->Resultado.begin(), Result->Resultado.end(), 0));
        
    }
    printf("SUMA TOTAL: %d\n", accumulate(Suma_Total.begin(), Suma_Total.end(), 0));
    return 0;
}
