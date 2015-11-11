#include "heap.h"
#include "testing.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CANT_ELEM 1500

void shuffle(int* array[], size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + (size_t)rand() / (size_t)(RAND_MAX / (n - i) + 1);
          int* t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int comp_ints(const void* a, const void* b) {
	int* a_temp = (int*)a;
	int* b_temp = (int*)b;
	if (*a_temp > *b_temp) return 1;
	else if (*a_temp == *b_temp) return 0;
	else {
		return -1;
	}
}

int comp_ints_reves(const void* a, const void* b) {
	int* a_temp = (int*)a;
	int* b_temp = (int*)b;
	if (*a_temp > *b_temp) return -1;
	else if (*a_temp == *b_temp) return 0;
	else {
		return 1;
	}
}

/////////////////////////////////////////////////////////////////////////////////
///    EN LAS PRUEBAS DE HEAPSORT, PARA VER LOS CONTENIDOS DE LAS LISTAS,     ///
/// EN EL ULTIMO CICLO "FOR", COMENTA EL "IF COMPLETO; Y DESCOMENTA EL PRINTF ///
/////////////////////////////////////////////////////////////////////////////////

bool prueba_heapsort_aleatorio_mayor_a_menor(size_t elementos, cmp_func_t cmp){
	int* lista  = malloc( sizeof(int) * elementos );
	if (lista == NULL)
		return false;
	
	int* lista_a_procesar[elementos];
	
	int* c = lista;
	for (int i = 0; i < elementos; i++){
		*c = i;
	//	printf("%d = %d | ", (int)(c-lista), (int)*c);
		lista_a_procesar[i] = c;
		c++;
	}
    shuffle(lista_a_procesar, elementos);
	heap_sort((void**)lista_a_procesar, elementos, cmp);
	for (size_t i = 0; i < elementos; i++){
		printf("%d vs %d - ", *lista_a_procesar[i], elementos-1-i);
	}
	printf("\n");
	for (size_t i = elementos; i > 0; i--){
		if (*(int*)lista_a_procesar[i-1] != (int)(elementos-i)) {
		    free(lista);
		    return false;
		}
	  //printf("%d\n", *(int*)(lista_a_procesar[i-1]));
	}
	free (lista);
	return true;
}

bool prueba_heapsort_aleatorio_menor_a_mayor(size_t elementos, cmp_func_t cmp){
	int* lista  = malloc( sizeof(int) * elementos );
	if (lista == NULL)
		return false;
	
	int* lista_a_procesar[elementos];
	
	int* c = lista;
	for (int i = 0; i < elementos; i++){
		*c = i;
	//	printf("%d = %d | ", (int)(c-lista), (int)*c);
		lista_a_procesar[i] = c;
		c++;
	}
    shuffle(lista_a_procesar, elementos);
	heap_sort((void**)lista_a_procesar, elementos, cmp);
	for (size_t i = 0; i < elementos; i++){
		printf("%d vs %d - ", *lista_a_procesar[i], i);
	}
	printf("\n");
	for (size_t i = 0; i < elementos; i++){
		if (*(int*)lista_a_procesar[i] != (int)i) {
		    free(lista);
		    return false;
		}
	//	printf("%d\n", *(int*)(lista_a_procesar[i]));
	}
	free (lista);
	return true;
}

bool prueba_heapsort_ordenado_menor_a_mayor(size_t elementos, cmp_func_t cmp){
	int* lista  = malloc( sizeof(int) * elementos );
	if (lista == NULL)
		return false;
	
	int* lista_a_procesar[elementos];
	
	int* c = lista;
	for (size_t i = 0; i < elementos; i++){
		*c = (int)(i);
	//	printf("%d = %d | ", (int)(c-lista), (int)*c);
		lista_a_procesar[elementos-1-i] = c;
		c++;
	}
	heap_sort((void**)lista_a_procesar, elementos, cmp);
	// for (size_t i = 0; i < elementos; i++){
	// 	printf("%d vs %d - ", *lista_a_procesar[i], i);
	// }
	// printf("\n");
	for (size_t i = 0; i < elementos; i++){
		if (*(int*)lista_a_procesar[i] != (int)i) {
		    free(lista);
		    return false;
		}
		//printf("%d\n", *(int*)(lista_a_procesar[i]));
	}
	free (lista);
	return true;
}

bool prueba_heapsort_ordenado_mayor_a_menor(size_t elementos, cmp_func_t cmp){
	int* lista  = malloc( sizeof(int) * elementos );
	if (lista == NULL)
		return false;
	
	int* lista_a_procesar[elementos];
	
	int* c = lista;
	for (size_t i = 0; i < elementos; i++){
		*c = (int)(i);
	//	printf("%d = %d | ", (int)(c-lista), (int)*c);
		lista_a_procesar[i] = c;
		c++;
	}
	heap_sort((void**)lista_a_procesar, elementos, cmp);
	// for (size_t i = 0; i < elementos; i++){
	// 	printf("%d vs %d - ", *lista_a_procesar[i], elementos-1-i);
	// }
	// printf("\n");
	printf("\n");
	for (size_t i = 0; i < elementos; i++){
		if (*(int*)lista_a_procesar[i] != (int)(elementos-1-i)) {
		    free(lista);
		    return false;
		}
	//	printf("%d vs %d\n", *(int*)(lista_a_procesar[i]), (int)(elementos-1-i));
	}
	free (lista);
	return true;
}


///////////////////////////////////////////////
///     FIN DE LAS PRUEBAS DEL HEAPSORT     ///
///////////////////////////////////////////////

bool heap_encolar_masivo(heap_t* heap, int* lista_aux, size_t elem){
	if (!lista_aux) return false;
	for (int i = 0; i < elem; i++){
		*lista_aux = i;
		if (!heap_encolar(heap, lista_aux) || (*(int*)heap_ver_max(heap) != i)){	
			free(lista_aux);
			return false;
		}
		lista_aux++;
	}
	printf("Tamaño del Heap: %d.\n", (int)heap_cantidad(heap));
	return true;
}

bool heap_desencolar_masivo(heap_t* heap, int* lista_aux, size_t elem){
	if (!lista_aux) return false;
	int* lista = malloc(sizeof(int)*elem);
	if (!lista) {
		free(lista_aux);
		return false;
	}
	int* dato_temp;
	for (int i = 0; i < elem; i++) {
		dato_temp = (int*)(heap_desencolar(heap));
		if (!dato_temp) {
			free(lista);
			free(lista_aux);
			return false;
		}
		//printf("%d\n", (int)*dato_temp);
		lista[i] = *dato_temp;
	}
	bool ok = true;
	for (size_t i = 0; i < elem; i++) {
		//printf("Ciclo num: %d;\nElem. esperado: %d;\nElem obtenido: %d.\n", (int)i, (int)(elem-1-i), lista[i]);
		if ((elem-1-i) != lista[i]) {
			ok = false;
			break;
		}
	}
	free(lista);
	free(lista_aux);
	printf("Tamaño del Heap: %d.\n", (int)heap_cantidad(heap));
	return ok;
}

void pruebas_heap_alumno(void){
	/* VARIABLES AUXILIARES */
	int t1 = 5;
	int t2 = 8;
	int t3 = 2;
	int t4 = 3;
	int t5 = 10;
	int* lista_aux  = malloc( sizeof(int) * CANT_ELEM );
	/* HEAP VACIO */
	heap_t* heap = heap_crear(comp_ints);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	heap_destruir(heap, NULL);
	/* HEAP DE A UN ELEMENTO */
	heap = heap_crear(comp_ints);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	print_test("Encolar 5 es true", heap_encolar(heap, &t1) == true);
	print_test("El maximo del heap es 5", heap_ver_max(heap) == &t1);
	print_test("Desencolar devuelve 5", heap_desencolar(heap) == &t1);
	print_test("Encolar 8 es true", heap_encolar(heap, &t2));
	print_test("El maximo del heap es 2", heap_ver_max(heap) == &t2);
	print_test("Encolar 2 es true", heap_encolar(heap, &t3));
	print_test("El maximo del heap es 8", heap_ver_max(heap) == &t2);
	print_test("Desencolar devuelve 8", heap_desencolar(heap) == &t2);
	print_test("El maximo del heap es 2", heap_ver_max(heap) == &t3);
	print_test("Desencolar devuelve 2", heap_desencolar(heap) == &t3);
	heap_destruir(heap, NULL);
	/* HEAP POCOS ELEMENTOS */
	heap = heap_crear(comp_ints);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	print_test("Encolar 5 es true", heap_encolar(heap, &t1));
	print_test("El maximo del heap es 5", heap_ver_max(heap) == &t1);
	print_test("Encolar 8 es true", heap_encolar(heap, &t2));
	print_test("El maximo del heap es 8", heap_ver_max(heap) == &t2);
	print_test("Encolar 2 es true", heap_encolar(heap, &t3));
	print_test("El maximo del heap es 8", heap_ver_max(heap) == &t2);
	print_test("Encolar 3 es true", heap_encolar(heap, &t4));
	print_test("El maximo del heap es 8", heap_ver_max(heap) == &t2);
	print_test("Encolar 10 es true", heap_encolar(heap, &t5));
	print_test("El maximo del heap es 10", heap_ver_max(heap) == &t5);
	heap_destruir(heap, NULL);
	print_test("Prueba HEapsort ordenado menor a mayro", prueba_heapsort_ordenado_menor_a_mayor(250, comp_ints));
    print_test("Prueba Heapsotr ordenado maoyr a menor", prueba_heapsort_ordenado_mayor_a_menor(250, comp_ints_reves));
	print_test("Prueba HEapsort aleatorio menor a mayro", prueba_heapsort_aleatorio_menor_a_mayor(250, comp_ints));
    print_test("Prueba Heapsotraleatorio  maoyr a menor", prueba_heapsort_aleatorio_mayor_a_menor(250, comp_ints_reves));
	heap = heap_crear(comp_ints);
	print_test("Encolar mayor masivamente", heap_encolar_masivo(heap, lista_aux, CANT_ELEM));
	print_test("desencolar mayor masivamente", heap_desencolar_masivo(heap, lista_aux, CANT_ELEM));
	heap_destruir(heap, NULL);
}
