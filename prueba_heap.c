#include "heap.h"
#include "testing.h"
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LONGITUD_ARRAY_PRUEBA 25

int cmp(const void* a, const void* b) {
	int* a_temp = (int*)a;
	int* b_temp = (int*)b;
	return (*a_temp - *b_temp);
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
	heap_t* heap = heap_crear(cmp);
	print_test("El heap fue creado, y no es NULL", (heap != NULL));
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	print_test("El heap esta vacio", heap_esta_vacio(heap));
	print_test("El maximo del heap es NULL", heap_ver_max(heap) == NULL);
	heap_destruir(heap, NULL);
	/* HEAP POCOS ELEMENTOS */
	heap = heap_crear(cmp);
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
		/*inicializar_vector(vector_pruebas);
	imprimir_vector_pruebas(vector_pruebas);
	heap_sort(vector_pruebas, LONGITUD_ARRAY_PRUEBA, cmp);
	imprimir_vector_pruebas(vector_pruebas);*/

}