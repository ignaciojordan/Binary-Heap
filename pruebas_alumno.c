#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //para el random
#define VOLUMEN 45000
/* ******************************************************************
 *                   FUNCIONES AUXILIARES
 * *****************************************************************/

int comparar(const void *a,const void *b){
	const int* valor_1 = a;
	const int* valor_2 = b;
	if (*valor_1 > *valor_2) return 1;
	else if (*valor_1 < *valor_2) return -1;
	return 0;
}


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_heap_vacio(void){
	printf("PRUEBAS HEAP VACÍO\n");
	
	heap_t* h = heap_crear(comparar);
	
	print_test("Crear heap vacío", h != NULL);
	print_test("El heap está vacío", heap_esta_vacio(h));
	/*Pruebo ver el máximo del heap devuelve NULL*/
	print_test("Ver el max del heap devuelve NULL",!heap_ver_max(h));
	/*Pruebo desdesencolar la heap vacía y devuelve false*/
	print_test("Desencolar con el heap vacío devuelve false ",!heap_desencolar(h));
	/*Destruyo el heap*/
	heap_destruir(h,NULL);
}

void pruebas_heap_insertar(void){
	printf("PRUEBAS HEAP DESENCOLAR Y ENCOLAR POCOS ELEMENTOS\n");
	heap_t* h = heap_crear(comparar);


	int v1 = 1, v2 = 2, v3= 3, v4= 4, v5= 5, v6= 6;


	print_test ("Heap_encolar número 5", heap_encolar(h,&v5));

	print_test ("Heap_encolar número 6", heap_encolar(h,&v6));

	print_test ("Heap_encolar número 3", heap_encolar(h,&v3));

	print_test ("Heap_encolar número 1", heap_encolar(h,&v1));

	print_test ("Heap_encolar número 2", heap_encolar(h,&v2));

	print_test ("Heap_encolar número 4", heap_encolar(h,&v4));



	print_test("El heap no está vacío", !heap_esta_vacio(h));

	print_test("El heap tiene cantidad 6", heap_cantidad(h) == 6);

	print_test("Ver max devuelve el valor 6",heap_ver_max(h) == &v6);



	int *aux = heap_desencolar(h);
	print_test("Elemento desencolado es 6 ", *aux == v6);
	print_test("Ver max devuelve el valor 5",heap_ver_max(h) == &v5);
	print_test("El heap no está vacío", !heap_esta_vacio(h));



	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 5", *aux == v5);
	print_test("Ver max devuelve el valor 4",heap_ver_max(h) == &v4);
	print_test("El heap no está vacío", !heap_esta_vacio(h));


	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 4", *aux == v4);
	print_test("Ver max devuelve el valor 3",heap_ver_max(h) == &v3);
	print_test("El heap no está vacío", !heap_esta_vacio(h));


	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 3", *aux == v3);
	print_test("Ver max devuelve el valor 2",heap_ver_max(h) == &v2);
	print_test("El heap no está vacío", !heap_esta_vacio(h));


	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 2", *aux == v2);
	print_test("Ver max devuelve el valor 1",heap_ver_max(h) == &v1);
	print_test("El heap no está vacío", !heap_esta_vacio(h));

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 1  ", *aux == v1);
	print_test("Ver max devuelve NULL",heap_ver_max(h) == NULL);


	print_test("El heap ahora está vacío", heap_esta_vacio(h));
	print_test("El heap tiene cantidad 0", heap_cantidad(h) == 0);
	print_test("Desencolar devuelve NULL", heap_desencolar(h) == NULL);

	heap_destruir (h,NULL);

}
void pruebas_volumen(){
	int arreglo[VOLUMEN];
	for (int i = 0; i<VOLUMEN; i++){
		arreglo[i] = rand();
	}
	heap_t* heap1 = heap_crear(comparar);
	bool ok = true;
	for (int i = 0; i<VOLUMEN; i++){
		ok &=heap_encolar(heap1, &arreglo[i]);
	}
	print_test("todos los elementos fueron encolados correctamente", ok);
	print_test("El heap tiene cantidad 45000", heap_cantidad(heap1) == VOLUMEN);
	ok = true;
	bool ok2;
	for(int i = VOLUMEN-1; i>-1; i--){
		ok2 = heap_esta_vacio(heap1);
		if (ok2) {
			ok = false;
			break;
		}
		int*max=heap_ver_max(heap1);
		int* aux = heap_desencolar(heap1);
		ok &= (*max == *aux);
	}
	print_test("todos los elementos fueron desencolados en el orden correcto", ok);
	print_test("El heap ahora está vacío", heap_esta_vacio(heap1));
	print_test("El heap tiene cantidad 0", heap_cantidad(heap1) == 0);
	print_test("Desencolar devuelve NULL", heap_desencolar(heap1) == NULL);
	heap_destruir(heap1,NULL);

}

void pruebas_array_a_heap(){
	printf("PRUEBA DE CREACION DE HEAP A PARTIR DE UN ARREGLO\n");
	void** arreglo = malloc(7*sizeof(int*));
	int a=5, b = 17, c=12, e = 44, d = 3, f = 6, g = 57;
	arreglo[0] = &b;
	arreglo[1] = &f;
	arreglo[2] = &g;
	arreglo[3] = &a;
	arreglo[4] = &c;
	arreglo[5] = &d;
	arreglo[6] = &e;

	heap_t* heap1 = heap_crear_arr(arreglo, 7, comparar);
	print_test("El heap no está vacío", !heap_esta_vacio(heap1));
	print_test("El heap tiene cantidad 7", heap_cantidad(heap1) == 7);
	print_test("el max es 57", heap_ver_max(heap1) == &g);
	int* aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 57", *aux == 57);
	print_test("el max es 44", heap_ver_max(heap1) == &e);
	aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 44", *aux == 44);
	print_test("el max es 17", heap_ver_max(heap1) == &b);
	aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 17", *aux == 17);
	print_test("el max es 12", heap_ver_max(heap1) == &c);
	aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 12", *aux == 12);
	print_test("el max es 6", heap_ver_max(heap1) == &f);
	aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 6", *aux == 6);
	print_test("el max es 5", heap_ver_max(heap1) == &a);
	aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 5", *aux == 5);
	print_test("el max es 3", heap_ver_max(heap1) == &d);
	aux = heap_desencolar(heap1);
	print_test("EL elemento desencolado es el 3", *aux == 3);
	print_test("Ver max es NULL", !heap_ver_max(heap1));
	print_test("Desencolar con el heap vacío devuelve false ",!heap_desencolar(heap1));
	heap_destruir(heap1,NULL);
}

void pruebas_heapsort(){
	printf("PRUEBA DEL HEAPSORT\n");
	void** arreglo2 = malloc(7*sizeof(int*));
	int a=5, b = 17, c=12, e = 44, d = 3, f = 6, g = 57;
	arreglo2[0] = &b;
	arreglo2[1] = &f;
	arreglo2[2] = &g;
	arreglo2[3] = &a;
	arreglo2[4] = &c;
	arreglo2[5] = &d;
	arreglo2[6] = &e;
	heap_sort(arreglo2,7,comparar);
	bool ok = true;
	for (int i = 0; i<7; i++){
		if((i+1)<7){		
			ok &= (*(int*)arreglo2[i] < *(int*)arreglo2[i+1]);
		}
	}
	print_test("los elementos se ordenaron correctamente", ok);
	free(arreglo2);
}


void pruebas_memoria_dinamica(){
	printf("PRUEBAS HEAP CON MEMORIA DINAMICA\n");
	int* mal1 = malloc(sizeof(int));
	int* mal2 = malloc(sizeof(int));
	int* mal3 = malloc(sizeof(int));
	int* mal4 = malloc(sizeof(int));
	int* mal5 = malloc(sizeof(int));
	int* mal6 = malloc(sizeof(int));
	int* mal7 = malloc(sizeof(int));
	*mal1 = 5;
	*mal2 = 6;
	*mal3 = 9;
	*mal4 = 4;
	*mal5 = 45;
	*mal6 = 12;
	*mal7 = 22;
	heap_t* h = heap_crear(comparar);


	print_test ("Heap_encolar número 5", heap_encolar(h,mal1));

	print_test ("Heap_encolar número 9", heap_encolar(h,mal3));

	print_test ("Heap_encolar número 12", heap_encolar(h,mal6));

	print_test ("Heap_encolar número 45", heap_encolar(h,mal5));

	print_test ("Heap_encolar número 4", heap_encolar(h,mal4));

	print_test ("Heap_encolar número 6", heap_encolar(h,mal2));

	print_test ("Heap_encolar número 22", heap_encolar(h,mal7));

	print_test("El heap no está vacío", !heap_esta_vacio(h));

	print_test("El heap tiene cantidad 7", heap_cantidad(h) == 7);

	print_test("Ver max devuelve el valor 45",heap_ver_max(h) == mal5);

	int *aux = heap_desencolar(h);
	print_test("Elemento desencolado es 45 ", *aux == *mal5);
	print_test("Ver max devuelve el valor 5",heap_ver_max(h) == mal7);



	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 22", *aux == *mal7);
	print_test("Ver max devuelve el valor 12",heap_ver_max(h) == mal6);



	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 12", *aux == *mal6);
	print_test("Ver max devuelve el valor 9",heap_ver_max(h) == mal3);



	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 9", *aux == *mal3);
	print_test("Ver max devuelve el valor 2",heap_ver_max(h) == mal2 );



	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 6", *aux == *mal2);
	print_test("Ver max devuelve el valor 5",heap_ver_max(h) == mal1);


	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 5", *aux == *mal1);
	print_test("Ver max devuelve 4",heap_ver_max(h) == mal4);

	aux = heap_desencolar(h);
	print_test("Elemento desencolado es 4", *aux == *mal4);
	print_test("Ver max devuelve NULL",!heap_ver_max(h));

	print_test("El heap ahora está vacío", heap_esta_vacio(h));
	print_test("El heap tiene cantidad 0", heap_cantidad(h) == 0);
	print_test("Desencolar devuelve NULL", heap_desencolar(h) == NULL);

	//encolo nuevamente los elementos para borrarlos con heap_destruir
	heap_encolar(h,mal1);
	heap_encolar(h,mal3);
	heap_encolar(h,mal5);
	heap_encolar(h,mal4);
	heap_encolar(h,mal2);
	heap_encolar(h,mal7);
	heap_encolar(h,mal6);

	heap_destruir (h,free);

}

void pruebas_heap_alumno() {
	pruebas_heap_vacio();
	pruebas_heap_insertar();
	pruebas_volumen();
	pruebas_array_a_heap();
	pruebas_heapsort();
	pruebas_memoria_dinamica();
}
