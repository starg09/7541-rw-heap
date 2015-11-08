#include "heap.h"
#include "testing.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LONGITUD_ARRAY_PRUEBA 25

int comp_ints(const void* a, const void* b) {
	int* a_temp = (int*)a;
	int* b_temp = (int*)b;
	return (*a_temp) - (*b_temp);
}

bool prueba_heapsort_agregar_mayor_masivo(size_t elementos){
	int* lista  = malloc( sizeof(int) * elementos );
	if (lista == NULL)
		return false;
	
	int* lista_a_procesar[elementos];
	
	int* c = lista;
	for (int i = 0; i < elementos; i++){
		*c = i;
		//printf("%d = %d | ", (int)(c-lista), (int)*c);
		lista_a_procesar[i] = c;
		c++;
	}

	heap_sort((void**)lista_a_procesar, elementos, comp_ints);
	free (lista);
	return true;
}

bool heap_encolar_masivo(heap_t* heap, size_t elem){
	int* lista  = malloc( sizeof(int) * elem );
	if (lista == NULL)
		return false;
	int* c = lista;
	for (int i = 0; i < elem; i++){
		*c = i;
		if ( !heap_encolar(heap, c) ){	
			free(lista);
			return false;
		}
		c++;
	}
	return true;
}

bool heap_desencolar_masivo(heap_t* heap, size_t elem){
	int* lista  = malloc( sizeof(int) * elem );
	if (lista == NULL)
		return false;
	int* elems_extraidos = malloc( sizeof(int) * elem );
	if (lista == NULL){
		free(lista);
		return false;
	}
	int* c = elems_extraidos;
	int* dato_temp = NULL;
	for (int i = 0; i < elem; i++){
		dato_temp = (int*)heap_desencolar(heap);
		if ( dato_temp == NULL){
			free(c);
			free(lista);
			return false;
		}
		*c = *(dato_temp);
		free(dato_temp);
		c++;
	}
	bool ok = true;
	int* c1 = lista;
	int* c2 = elems_extraidos + (elem-1);
	for (size_t i = 0; i < elem; i++){
		if (*c1 != *c2){
			printf("%d vs %d \n", *c1, *c2);
			ok = false;
			free(lista);
			break;
		}
		c1++;
		c2--;
	}
	free(lista);
	return ok;
}

/*void inicializar_vector(int *vector_pruebas) {
	srand((unsigned) time(NULL));
	for (size_t i=0; i<LONGITUD_ARRAY_PRUEBA; i++) {
		vector_pruebas[i] = rand();
	}
}*/

void imprimir_vector_pruebas(int *vector_pruebas) {
	for (size_t i=0;i<LONGITUD_ARRAY_PRUEBA;i++) {
		printf("%d\n", vector_pruebas[i] );
	}
}

void pruebas_heap_alumno(void){
	/* VARIABLES AUXILIARES */
	int t1 = 5;
	int t2 = 8;
	int t3 = 2;
	int t4 = 3;
	int t5 = 0;
	//int vector_pruebas[LONGITUD_ARRAY_PRUEBA];
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
	print_test("Encolar 8 es true", heap_encolar(heap, &t2));
	print_test("Encolar 2 es true", heap_encolar(heap, &t3));
	print_test("Encolar 3 es true", heap_encolar(heap, &t4));
	print_test("Encolar 0 es true", heap_encolar(heap, &t5));
	heap_destruir(heap, NULL);
	/* HEAP MUCHOS ELEMENTOS */
	/* HEAPSORT */
	prueba_heapsort_agregar_mayor_masivo(250);
	/*inicializar_vector(vector_pruebas);
	imprimir_vector_pruebas(vector_pruebas);
	heap_sort((void**)vector_pruebas, LONGITUD_ARRAY_PRUEBA, comp_ints);
	imprimir_vector_pruebas(vector_pruebas);*/
	heap = heap_crear(comp_ints);
	print_test("Encolar mayor masivamente", heap_encolar_masivo(heap, 250));
	print_test("desencolar mayor masivamente", heap_desencolar_masivo(heap, 250));
	heap_destruir(heap, NULL);
}