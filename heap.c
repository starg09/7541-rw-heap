#include "heap.h"
#include "vector_dinamico.h"
#include <stdlib.h>
#include <string.h>

#define LARGO_INICIAL 20;

/* DEFINICION DE ESTRUCTURAS */
struct heap {
	vector_t* vector;
	cmp_func_t* cmp;
	size_t elem;
};

/* Siendo i el padre, el hijo izquierdo es de la forma 2*i, y el hijo derecho de la forma 2*i + 1 */

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) {
		return NULL;
	}
	vector_t* vector = vector_crear(LARGO_INICIAL);
	if (!vector) {
		return NULL;
	}
	heap->vector = vector;
	heap->cmp = cmp;
	heap->elem = 0;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e));
size_t heap_cantidad(const heap_t *heap);
bool heap_esta_vacio(const heap_t *heap);
bool heap_encolar(heap_t *heap, void *elem);
void *heap_ver_max(const heap_t *heap);
void *heap_desencolar(heap_t *heap);
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);

