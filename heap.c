#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INICIAL 17
#define REDIM 2

struct heap{
	void **arreglo;
	size_t cantidad;
	size_t tamanio;
	cmp_func_t cmp;
};
/*********************************************************************/
/*********************FUNCIONES AUXILIARES****************************/
/*********************************************************************/

bool redimension_heap(heap_t* heap, size_t nuevo_tamanio){
	void* aux = realloc (heap->arreglo, (nuevo_tamanio * sizeof(void*)));
	if(aux == NULL){
		return false;
	}
	heap->arreglo = aux;		
	heap->tamanio= nuevo_tamanio;	
	return true;
}

void swap(void **x, void **y){
    void *z;
    z  = *x;
    *x = *y;
    *y =z;
}


void upheap(void*arreglo[],cmp_func_t cmp, size_t posicion){
	if(posicion == 0){
		return;
	}
	size_t pos_padre = (posicion-1)/2;
	if (cmp(arreglo[posicion], arreglo[pos_padre]) > 0) {
		swap (&arreglo[posicion], &arreglo[pos_padre]);
		upheap(arreglo,cmp, pos_padre);
	}
	return;
}


void downheap(void*arreglo[], cmp_func_t cmp, size_t i, size_t cant){
	size_t pos_hijo_izq = 2*i+1;
	size_t pos_hijo_der = 2*i+2;
	size_t pos_max= i;

	if (pos_hijo_izq < cant && (cmp(arreglo[pos_hijo_izq],arreglo[pos_max]) > 0)){
		pos_max = pos_hijo_izq;
	}
	if (pos_hijo_der < cant && (cmp(arreglo[pos_hijo_der],arreglo[pos_max]) > 0)){
		pos_max = pos_hijo_der;
	}
	if (pos_max != i){
		swap (&arreglo[i], &arreglo[pos_max]);
		downheap(arreglo, cmp, pos_max, cant);
	}
	return;
}
void heapify(void*arreglo[], cmp_func_t cmp, size_t i){
	size_t start = (i-1)/2;	
	while (start>0){
		downheap(arreglo, cmp, start, i);
		start--;
	}
	downheap(arreglo, cmp, 0, i);
	return;
}
  /*********************************************************************/
 /*********************PRIMITIVAS HEAP*********************************/
/*********************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) {
		return NULL;
	}
	heap->arreglo = malloc(INICIAL * sizeof(void*));
	if (!heap->arreglo) {
		free(heap);
		return NULL;
	}
	heap->cmp = cmp;
	heap->tamanio = INICIAL;	
	heap->cantidad = 0;
	return heap;
}

bool heap_encolar(heap_t *heap, void *elem){
	heap->cantidad++;
	heap->arreglo[heap->cantidad-1] = elem;
	upheap(heap->arreglo, heap->cmp, heap->cantidad-1);
	if (heap->cantidad == heap->tamanio){
		if (!redimension_heap(heap, heap->tamanio*REDIM)){
			return false;
		}
	}
	return true;
}

void *heap_desencolar(heap_t *heap){
	if (heap_esta_vacio(heap)){
		return NULL;
	}
	void* elemento_a_desencolar = heap_ver_max(heap);
	heap->arreglo[0] = heap->arreglo[heap->cantidad-1];
	downheap(heap->arreglo, heap->cmp, 0, heap->cantidad-1);
	heap->cantidad--;
	if ( heap->cantidad < (heap->tamanio/4) ){
		redimension_heap(heap, heap->tamanio/REDIM);
	}
	return elemento_a_desencolar;
}

void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)){
		 return NULL;
	}
	return heap->arreglo[0];
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad == 0;
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (destruir_elemento) {
		for (int i = 0; i < heap->cantidad; ++i) {
			destruir_elemento(heap->arreglo[i]);
		}
	}
	free(heap->arreglo);
	free(heap);
}

heap_t *heap_crear_arr(void*vector[], size_t n, cmp_func_t cmp){
	heap_t *heap = malloc(sizeof(heap_t));
	if (!heap){
		return NULL;
	}
	void** vect = malloc(n * sizeof(void*));
	if (!vect) {
		free(heap);
		return NULL;
	}	
	memcpy(vect, vector, n * sizeof(void*));
	heapify(vect, cmp, n);
	heap->arreglo = vect;
	heap->cmp = cmp;
	heap->cantidad = n;
	heap->tamanio = n;
	return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cmp, cant);
	while (cant > 0){
		swap(&elementos[0], &elementos[cant-1]);
		downheap(elementos,cmp,0,cant-1);
		cant--;
	}
	return;
}
