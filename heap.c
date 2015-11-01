#include "heap.h"
#include "vector_dinamico.h"
#include <stdlib.h>
#include <string.h>

/* LARGO INICIAL DEL HEAP */
#define LARGO_INICIAL 20;

/* DEFINICION DE ESTRUCTURAS */
struct heap {
	vector_t* vector;
	cmp_func_t* cmp;
	size_t elem;
};

/* El elemento mayor estara en la posicion 0 del vector dinamico */
/* Siendo j la posicion actual, la posicion del padre es de la forma (j - 1)/2 */
/* Siendo i el padre, el hijo izquierdo es de la forma 2*i + 1, y el hijo derecho de la forma 2*i + 2 */

/* DEFINICION DE PRIMITIVAS */
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

bool heap_encolar(heap_t *heap, void *elem);

void *heap_ver_max(const heap_t *heap) {
	void* elemento_temp;
	return vector_obtener(heap->vector, 0, elemento_temp) ? elemento_temp : NULL;
}

void *heap_desencolar(heap_t *heap);

void downheap(vector_t* vector, size_t cant_elem, size_t pos_actual, cmp_func_t cmp);
/* PSEUDOCODIGO (A IMPLEMENTAR):
	if pos_actual >= cant_elem: return
	pos_hijo_izq = pos_actual*2 + 1
	pos_hijo_der = pos_actual*2 + 2
	pos_mayor = pos_actual
	if pos_hijo_izq < cant_elem and heap[pos_actual] < heap[pos_hijo_izq]: pos_mayor = pos_hijo_izq
	if pos_hijo_der < cant_elem and heap[pos_actual] < heap[pos_hijo_der]: pos_mayor = pos_hijo_der
	if pos_mayor != pos_actual: swap(heap, pos_actual, pos_mayor) downheap(heap, cant_elem, pos_mayor)
*/

void upheap(vector_t* vector, size_t cant_elem, size_t pos_actual, cmp_func_t cmp);
/* PSEUDOCODIGO (A IMPLEMENTAR):
	if pos_actual == 0: return
	pos_padre = (pos_actual - 1)/2
	if heap[pos_actual] > heap[pos_padre]: swap(heap, pos_actual, pos_padre) upheap(heap, cant_elem, pos_padre)
*/

void heapify(vector_t* vector, size_t cant_elem, cmp_func_t cmp);		
/* PSEUDOCODIGO (A IMPLEMENTAR):
	for i = (cant_elem/2 - 1) to 0: downheap(heap, cant_elem, i, cmp)
*/

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);
/* PSEUDOCODIGO (A IMPLEMENTAR):
	heapify(elementos[], cant, cmp)
	for i = cant-1 to 0: swap(elementos[], 0, i) downheap(elementos[], i, 0)
*/
	
