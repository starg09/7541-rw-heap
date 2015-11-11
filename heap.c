#include "heap.h"
#include "vector_dinamico.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

/* LARGO INICIAL DEL HEAP, FACTORES DE OCUPACION Y REDIMENSIONAMIENTO */
#define LARGO_INICIAL 20
#define FACTOR_REDIMENSIONAMIENTO 2
#define FACTOR_DE_OCUPACION 80
#define FACTOR_DE_DESOCUPACION 25

/* DEFINICION DE LA ESTRUCTURA */
struct heap {
	vector_t* vector;
	cmp_func_t cmp;
	size_t elem;
};

/* El elemento mayor estara en la posicion 0 del vector dinamico */
/* Siendo j la posicion actual, la posicion del padre es de la forma (j - 1)/2 */
/* Siendo i el padre, el hijo izquierdo es de la forma 2*i + 1, y el hijo derecho de la forma 2*i + 2 */

/* FUNCIONES AUXILIARES PARA EL HEAP COMO TDA */

void swap(vector_t* vector, size_t pos_uno, size_t pos_dos) {
	void* dato_aux_1 = NULL;
	void* dato_aux_2 = NULL;
	vector_obtener(vector, pos_uno, &dato_aux_1);
	vector_obtener(vector, pos_dos, &dato_aux_2);
	vector_guardar(vector, pos_uno, dato_aux_2);
	vector_guardar(vector, pos_dos, dato_aux_1);

}

void downheap(vector_t* vector, size_t cant_elem, size_t pos_actual, cmp_func_t cmp) {
	if (pos_actual > cant_elem) {
		return;
	}
	size_t pos_hijo_izq = pos_actual*2 + 1;
	size_t pos_hijo_der = pos_actual*2 + 2;
	size_t pos_mayor;
	void* dato_temp1 = NULL;
	void* dato_temp2 = NULL;
	void* dato_temp3 = NULL;
	if (vector_obtener(vector, pos_actual, &dato_temp1) && vector_obtener(vector, pos_hijo_izq, &dato_temp2) && vector_obtener(vector, pos_hijo_der, &dato_temp3)) {
		if ((pos_hijo_izq < cant_elem) && (cmp(dato_temp1,dato_temp2) < 0)) {
	 		pos_mayor = pos_hijo_izq;
		}
		else {
			pos_mayor = pos_actual;
		}
		if (pos_mayor == pos_actual) {
			if ((pos_hijo_der < cant_elem) && (cmp(dato_temp1,dato_temp3) < 0)) {
		 		pos_mayor = pos_hijo_der;
			}
		}
		else {
			if ((pos_hijo_der < cant_elem) && (cmp(dato_temp2,dato_temp3) < 0)) {
		 		pos_mayor = pos_hijo_der;
			}
		}
		if (pos_mayor != pos_actual) {
			swap(vector, pos_actual, pos_mayor);
			downheap(vector, cant_elem, pos_mayor, cmp);
		}
	}	
}

void upheap(vector_t* vector, size_t cant_elem, size_t pos_actual, cmp_func_t cmp){
	size_t pos_padre = (pos_actual-1)/2;
	void* dato_temp1 = NULL;
	void* dato_temp2 = NULL;
	int comparacion;
	vector_obtener(vector, pos_actual, &dato_temp1);
	vector_obtener(vector, pos_padre, &dato_temp2);
	if (dato_temp1 && dato_temp2) {
		comparacion = cmp(dato_temp1, dato_temp2);
		if (comparacion > 0) { 
			swap(vector, pos_actual, pos_padre); 
			upheap(vector, cant_elem, pos_padre, cmp);
		}
		else if (comparacion == 0) {
			vector_guardar(vector, pos_actual, NULL);
		}
	}
}


void heapify(vector_t* vector, size_t cant_elem, cmp_func_t cmp) {
	for (size_t i = (cant_elem/2) - 1; i > 0; i--) {
		downheap(vector, cant_elem, i, cmp);
	}
}

/* DEFINICION DE PRIMITIVAS */

heap_t *heap_crear(cmp_func_t cmp) {
	if (cmp == NULL)
		return NULL;
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) {
		return NULL;
	}
	vector_t* vector = vector_crear(LARGO_INICIAL);
	if (!vector) {
		free(heap);
		return NULL;
	}
	heap->vector = vector;
	heap->cmp = cmp;
	heap->elem = 0;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	void* elemento_temp;
	while (!heap_esta_vacio(heap)) {
		elemento_temp = heap_desencolar(heap);
		if (destruir_elemento != NULL) {
			destruir_elemento(elemento_temp);
		}
	}
	vector_destruir(heap->vector);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
	return heap->elem;
}

bool heap_esta_vacio(const heap_t *heap) {
	return (heap->elem == 0);
}

bool heap_encolar(heap_t *heap, void *elem) {
	if (heap_esta_vacio(heap)){
		heap->elem = 1;
		return vector_guardar((heap->vector), 0, elem);
	}
	if(vector_guardar(heap->vector, heap->elem, elem)) {
		heap->elem++;
		if ((heap_cantidad(heap) >= vector_obtener_tamanio(heap->vector)*FACTOR_DE_OCUPACION/100)) {
				vector_redimensionar(heap->vector, vector_obtener_tamanio(heap->vector)*FACTOR_REDIMENSIONAMIENTO);
		}
		upheap(heap->vector, heap->elem, heap->elem-1, heap->cmp);
    	return true;
    }
    return false;
}


void *heap_ver_max(const heap_t *heap) {
	if (heap_esta_vacio(heap))
		return NULL;
	void* elemento_temp = NULL;
	vector_obtener(heap->vector, 0, &elemento_temp);
	return elemento_temp;
}

void *heap_desencolar(heap_t *heap) {
	if(!heap_esta_vacio(heap)) {
		void* maximo = heap_ver_max(heap);
		void* nuevo_tope = NULL;
		if(vector_obtener(heap->vector, heap_cantidad(heap)-1, &nuevo_tope) && vector_guardar(heap->vector, 0, nuevo_tope)) {
			if ((heap_cantidad(heap) <= vector_obtener_tamanio(heap->vector)*FACTOR_DE_DESOCUPACION/100) && (vector_obtener_tamanio(heap->vector) > LARGO_INICIAL)) {
				vector_redimensionar(heap->vector, vector_obtener_tamanio(heap->vector)/FACTOR_REDIMENSIONAMIENTO);	
			}
			heap->elem--;
			downheap(heap->vector, heap->elem, 0, heap->cmp);
			return maximo;
		}
	}
	return NULL;
}

/* HEAPSORT + FUNCIONES AUXILIARES HEAPSORT */
void swap_heapsort(void* vector[], size_t pos_uno, size_t pos_dos) {
	void* dato_aux = NULL;
	dato_aux = vector[pos_uno];
	vector[pos_uno] = vector[pos_dos];
	vector[pos_dos] = dato_aux;
}

void downheap_heapsort(void* vector[], size_t cant_elem, size_t pos_actual, cmp_func_t cmp) {
	if (pos_actual > cant_elem) {
		return;
	}
	size_t pos_hijo_izq = pos_actual*2 + 1;
	size_t pos_hijo_der = pos_actual*2 + 2;
	size_t pos_mayor = pos_actual;
	if ((pos_hijo_izq < cant_elem) && (cmp(vector[pos_mayor],vector[pos_hijo_izq]) < 0)) {
		pos_mayor = pos_hijo_izq;
	}
	if ((pos_hijo_der < cant_elem) && (cmp(vector[pos_mayor],vector[pos_hijo_der]) < 0)) {
		pos_mayor = pos_hijo_der;
	}
	if (pos_mayor != pos_actual) {
		swap_heapsort(vector, pos_actual, pos_mayor);
		downheap_heapsort(vector, cant_elem, pos_mayor, cmp);
	}
}

void heapify_heapsort(void* vector[], size_t cant_elem, cmp_func_t cmp) {
	for (size_t i = (cant_elem/2); i > 0; i--) {
		downheap_heapsort(vector, cant_elem, i-1, cmp);
	}
}

void heap_sort(void* elementos[], size_t cant, cmp_func_t cmp) {
	heapify_heapsort(elementos, cant, cmp);

	for (size_t i = 1; i <= cant; i++) {
		swap_heapsort(elementos, 0, cant-i);
		downheap_heapsort(elementos, cant-i, 0, cmp);
	}
    //printf("Elementos sin procesar: %d - Indice actual: %d\n", (int)cant, (int)i);
}
