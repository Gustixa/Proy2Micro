// /**
//  * @file Code.cpp
//  * @author your name (you@domain.com)
//  * @brief
//  * @version 0.1
//  * @date 2022-10-02
//  *
//  * @copyright Copyright (c) 2022
//  *
//  *
//  *---------------------------------------
// Alejandro Martinez 21430
// ---------------------------------------*/
// #include <stdio.h>
// #include <pthread.h>
// #include <iostream>
// #include <vector>
// using namespace std;

// pthread_mutex_t candado;
// pthread_cond_t cond;
// void *calc(void *args)
// {
// 	pthread_mutex_lock(&candado); // lock
// 	vector<int> *arguments = (vector<int> *)args;
// 	printf("Limite Inferior: %d\n", arguments[0][0]);
// 	printf("Limite Superior: %d\n", arguments[0].back());
// 	int Resultado =  1;
// 	for (const auto& e: arguments[0]) // multiplicar todos los elementos en el vector
// 	Resultado *= e;
// 	printf("Factorial: %d\n", Resultado); // imprimit factorizacion de elementos en el thread
// 	pthread_mutex_unlock(&candado); // unlock
// 	pthread_cond_signal(&cond);
// 	return (void*)Resultado;
// }

// int main()
// {
// 	vector<int> Suma_Total;
// 	int Gasolineras_Iniciales;
// 	cout << "Gasolineras iniciales: ";
// 	cin >> Gasolineras_Iniciales; // Recupera el valor del usuario para el numero que se quiere factorizar
// 	pthread_t SC0, SC1, SC2; // Declara los 3 threads
// 	int x = Gasolineras_Iniciales;
// 	pthread_mutex_init(&candado, NULL);
// 	pthread_cond_init(&cond, NULL); //Declaracionde mutex y variable de condicion
// 	Data_de_Gasolinera SC0_Val; //Declara los vectores con las variables que se le pasaran a los threads
// 	Data_de_Gasolinera SC1_Val;
// 	Data_de_Gasolinera SC2_Val;
// 	for (int i = 1; i <= Bloques; i++) //Alimenta los vectores con los valores que se tienen que multiplicar en cada thread, cada thread tiene parametros distintos 
// 	{
// 		SC0_Val.push_back(i);
// 	}
// 	for (int i = 1; i <= Bloques; i++)
// 	{
// 		SC1_Val.push_back(i+Bloques);
// 	}
// 	for (int i = 1; i <= Bloques + Residue; i++)
// 	{
// 		SC2_Val.push_back(i+Bloques*2);
// 	}
// 	int Result;
// 	pthread_create(&SC0, NULL, calc, (void *)&SC0_Val); // Crear y unir cada thread y guardar el resultado
// 	printf("______________\n-- SC0 --\n");
// 	pthread_join(SC0, (void **)&Result);
// 	int SC0_Res = Result;
// 	pthread_create(&SC1, NULL, calc, (void *)&SC1_Val);
// 	printf("______________\n-- SC1 --\n");
// 	pthread_join(SC1, (void **)&Result);
// 	int SC1_Res = Result;
// 	pthread_create(&SC2, NULL, calc, (void *)&SC2_Val);
// 	printf("______________\n-- SC2 --\n");
// 	pthread_join(SC2, (void **)&Result);
// 	int SC2_Res = Result;
// 	printf("\nResultado Final: %d\n", SC0_Res * SC1_Res * SC2_Res); // Multiplicar los resultados de cada thread para obtener el resultado final e imprimirlo
// 		pthread_cond_destroy (&cond);
// }

#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;

Funcion gasolinera Como puntero Generico (argumento Como puntero Generico)
Funcion costoGasolina Como puntero Generico (argumento Como puntero Generico)
Funcion cargarGasolinera Como puntero Generico (argumento Como puntero Generico)

struct estadisticas {
		int cantidadcarrosEnGasolinera = 0;
		int gananciasGasolineraComo = 0;
	};

int main(){
	pthread_t threads[];
	pthread_t camionRecargardor[];
	pthread_mutex_t recargarGasolinera;
	pthread_cond_t recargandoGasolinera;
	int i = 0;
	int cantidadDias = 0;
	int ganancias = 0;
	int cantidadDeGasolineras = 0;
	int cantidadGasolinaRecargar = 10000; // En quetzales
	int gasolinaPorGasolinera = 2000; // En Quetzales
	

	pthread_mutex_init(&recargarGasolinera);
	pthread_cond_init(&recargandoGasolinera, NULL);

	cout << "Ingrese la cantidad de gasolinas con las cuales desea iniciar para su franquicia";
	cin >> cantidadDeGasolineras;

	for (i; i < cantidadDeGasolineras; i++){
		if (pthread_create(&threads[gasolineraRecurrente], NULL, NULL ) != 0) {
			cout << "Failed to create the thread";
		}
		if (pthread_create(&camion Recargador[gasolineraRecurrente], NULL,&cargarGasolinera ,NULL) != 0), {
			cout << "Failed to create the thread";
		}
	}

	for (i; i < cantidadDeGasolineras; i++){
		if (pthread_join(threads[gasolinera recurrente], (void**)&) != 0) {
			cout << "Failed to join the current thread";
		}
		if (pthread_join(camionRecargador[camion recargador], NULL) != 0) {
			cout << "Failed to join the current thread";
		}
	}
	pthread_mutex_destroy(&recargarGasolinera);
	pthread_cond_destroy(&recargarGasolinera);
}



/*FUNCION PARA CREAR SIMULAR LA FUNCIONALIDAD DE LAS GASOLINERAS
* Este hilo, es una gasolinera, donde se generaran vehiculos de manera pseudoaleatoria.
* Estos vehiculos, seran hilo, y se iran al metodo costoGasolina, donde se genera el precio
* o cantidad de gasolina adquirida (en quetzales) por cada vehiculo
*/
Funcion gasolinera Como puntero Generico (argumento Como puntero Generico)
	Definir cantidad de carros Como valor aleatorio de tipo Entero
Definir threads[] Como pthread_t
Definir gananciaPorCarro Como Entero <- (Entero*)locación de memoria(tamaño de(Entero*))
*gananciaPorCarro = 0;
Definir i Como Entero
	Para i<-0 Hasta cantidad de carros Con paso 1, hacer:
Si pthread_create(&threads[carro recurrente), NULL, &costoGasolina, gananciaPorCarro) es diferente de cero, hacer:
	Escribir "Failed to create the thread"
Fin condicional
	Fin Para
Fin Funcion 

/* FUNCION PARA GENERAR LAS GANANCIAS DE CADA CARRO
* Esta funcion, obtiene la adquisición de gasolina del carro actual con respecto a su gasolinera.
* Devuelve su cantidad al metodo gasolinera
*/
Funcion costoGasolina Como puntero Generico (argumento Como puntero Generico)
	Definir gasolinaAdquirida Como Entero <- *(Entero*)argumento // Quetzales
Definir gasolinaPorCarro Como aleatorio de tipo Entero
Definir gasolinaAdquirida Como Entero (Valor aleatorio)
	pthread_mutex_lock(&recargarGasolinera) // Esta variable, se crear una asi, diferente, para no confundirse
	gasolinaPorGasolinera <- gasolinaPorGasolinera - gasolinaPorCarro
	pthread_mutex_unlock(&recargarGasolinera)
	pthread_cond_broadcast(&recargandoGasolinera)
	cantidadGasolina <- cantidadGasolina - gasolinaAdquirida
	
	*(Entero*)argumento <- gasolinaPorCarro
	retornar argumento
	
Fin Funcion




/* FUNCION PARA RECARGAR LA GASOLINERA 
* Funcion donde se recarga la gasolinera, en caso de quedarse sin gasolina, simula la llegada de un camion
* para llegar y recargar la gasolinera
*/
Funcion carga gasolinera Como puntero Generico (argumento Como puntero Generico)
	pthread_mutex_lock(&recargarGasolinera)
	Mientras gasolinaPorGasolinera mayor a 0 hacer:
		pthread_cond_wait(&recargargandoGasolinera,&recargarGasolinera)
	Fin mientras
	gasolinaPorGasolinera <- gasolinaPorGasolinera + cantidadGasolinaRecargar
	pthread_mutex_unlock(&recargarGasolinera)
Fin Funcion
