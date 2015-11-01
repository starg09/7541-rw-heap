#include "heap.h"
#include "vector_dinamico.h"
#include <stdlib.h>
#include <string.h>

/* Siendo i el padre, el hijo izquierdo es de la forma 2*i, y el hijo derecho de la forma 2*i + 1 */

heap_t *heap_crear(cmp_func_t cmp);
void heap_destruir(heap_t *heap, void destruir_elemento(void *e));
size_t heap_cantidad(const heap_t *heap);
bool heap_esta_vacio(const heap_t *heap);
bool heap_encolar(heap_t *heap, void *elem);
void *heap_ver_max(const heap_t *heap);
void *heap_desencolar(heap_t *heap);
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);

