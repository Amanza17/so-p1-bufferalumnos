#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "bufalumnos.h"

/* 
gcc -g -c -Wall -Wshadow -Wvla -g main.c
gcc -g -c -Wall -Wshadow -Wvla -g bufalumnos.c
gcc -g -o main bufalumnos.o main.o

valgrind --leak-check=full -s --show-leak-kinds=all ./main Pedro Perez 3 Luisa Mendez 10 Paco Mirto 6 Juan Ramirez 8

*/

int
main(int argc, char *argv[])
{
	//Local variables
	Buffer *b = NULL;
	int i = 0;
	float mark = 0;
	int status = 0;
	Student *higher = NULL;

	Student *lower = NULL;

	b = bookSpace(30);
	if (b == NULL) {
		fprintf(stderr,
			"Error: No se pudo asignar memoria para un Buffer.\n");
		exit(EXIT_FAILURE);
	}

	if ((argc - 1) % 3 != 0) {
		fprintf(stderr,
			"Debe introducir nombre apellido y nota de cada alumno con el siguiente formato: NOMBRE APELLIDO NOTA\n");
		exit(EXIT_FAILURE);
	}
	//check all params OK
	for (i = 1; i < argc; i++) {
		if ((i % 3) != 0) {
			// we check if name or surname i longer than expected
			if (strlen(argv[i]) >= Maxspace) {
				fprintf(stderr, "El nombre o apellido %s introducido es muy largo. Recuerde que el máximo es de 64 caracteres.\n", argv[i]);	// mirar como pasar el apellido o nombre como parámetro
				exit(EXIT_FAILURE);
			}
		} else {
			mark = strtof(argv[i], NULL);
			// check no string
			if (mark == 0) {
				if (strcmp(argv[i], "0") != 0) {
					fprintf(stderr,
						"Debe introducir una nota valida, un entero del 1 al 10. Usted introdujo algo que no es un número.\n");
					exit(EXIT_FAILURE);
				}
			}
			// chechk no float
			if (mark != (int)mark) {
				fprintf(stderr,
					"Debe introducir una nota valida, un entero del 1 al 10. Usted introdujo una nota que no es un entero.\n");
				exit(EXIT_FAILURE);
			}
			// chechk valid range
			if (mark > 10 || mark < 0) {
				fprintf(stderr,
					"Debe introducir una nota valida, un entero del 1 al 10. Usted introdujo una nota fuera de rango.\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	// add all users to list
	for (i = 1; i < argc; i = i + 3) {
		Student *s = malloc(sizeof(Student));

		if (!s) {
			fprintf(stderr,
				"Error: No se pudo asignar memoria para un estudiante.\n");
			exit(EXIT_FAILURE);
		}
		strcpy(s->name, argv[i]);
		strcpy(s->surname, argv[i + 1]);
		s->mark = strtol(argv[i + 2], NULL, 10);
		status = add(b, s);
		if (status == 1) {
			fprintf(stderr,
				"Error: Tamaño de Buffer demassiado pequeño.\n");
			exit(EXIT_FAILURE);

		}
	}
	print(b);

	higher = extractHigherMark(b);
	if (higher != NULL) {
		printf("Max: %s %s %d\n", higher->name, higher->surname,
		       higher->mark);
	} else {
		fprintf(stderr,
			"Error: Hubo un fallo en la lectura del estudiante con la nota más alta.\n");
		exit(EXIT_FAILURE);
	}

	lower = extractLowerMark(b);
	if (lower != NULL) {
		printf("Min: %s %s %d\n", lower->name, lower->surname,
		       lower->mark);
	} else {
		fprintf(stderr,
			"Error: Hubo un fallo en la lectura del estudiante con la nota más baja.\n");
		exit(EXIT_FAILURE);
	}

	free(lower);
	free(higher);

	freeBuffer(b);

	exit(EXIT_SUCCESS);

}
