/* 
	gcc -g -c -Wall -Wshadow -Wvla -g Bufferalumnos.c
	gcc -g -o Bufferalumnos Bufferalumnos.o
*/
#include "bufalumnos.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

Buffer *
bookSpace(int n)
{
	int i = 0;
	Buffer *b = NULL;

	b = malloc(sizeof(Buffer));
	if (!b) {
		return NULL;
	}

	b->size = n;
	b->arr = malloc(n * sizeof(Student));

	if (!b->arr) {
		return NULL;
	}

	for (i = 0; i < b->size; i++) {
		b->arr[i] = NULL;
	}

	return b;

}

//return 0 if everything ok, 1 if no sàcw for the student
int
add(Buffer *b, Student *s)
{
	int i = 0;

	for (i = 0; i < b->size; i++) {
		if (b->arr[i] == NULL) {
			b->arr[i] = s;
			return 0;
		}
	}
	return 1;
}

int
print(Buffer *b)
{
	int i = 0;

	for (i = 0; i < b->size; i++) {
		if (b->arr[i] != NULL) {
			printf("%s %s %d\n", b->arr[i]->name,
			       b->arr[i]->surname, b->arr[i]->mark);
		}
	}

	return 0;
}

int
freeBuffer(Buffer *b)
{
	int i = 0;

	for (i = 0; i < b->size; i++) {
		if (b->arr[i] != NULL) {
			free(b->arr[i]);
			b->arr[i] = NULL;
		}
	}

	free(b->arr);
	b->arr = NULL;
	free(b);
	b = NULL;

	return 0;
}

int
delStudent(Buffer *b, char *name, char *surname)
{
	Student *temp;
	int i = 0;

	for (i = 0; i < b->size; i++) {
		if (b->arr != NULL) {
			if (strcmp(b->arr[i]->name, name) == 0
			    && strcmp(b->arr[i]->surname, surname) == 0) {
				temp = b->arr[i];
				free(temp);
				b->arr[i] = NULL;
				temp = NULL;
				return 0;
			}
		}
	}
	return 1;
}

Student *
extractHigherMark(Buffer *b)
{
	int tempMark = -1;
	int i = 0;
	int temPos = 0;
	int empty = 1;		//works as a bool to check if Bufferfer is empty
	Student *temp;

	for (i = 0; i < b->size; i++) {
		if ((b->arr[i] != NULL) && (b->arr[i]->mark > tempMark)) {
			temp = b->arr[i];
			tempMark = b->arr[i]->mark;
			empty = 0;

			temPos = i;

		}
	}
	if (empty) {
		return NULL;
	}

	b->arr[temPos] = NULL;

	return temp;

}

Student *
extractLowerMark(Buffer *b)
{
	int tempMark = 11;
	int i = 0;
	int temPos = 0;
	int empty = 1;		//works as a bool to check if Bufferfer is empty
	Student *temp;

	for (i = 0; i < b->size; i++) {
		if ((b->arr[i] != NULL) && (b->arr[i]->mark < tempMark)) {
			temp = b->arr[i];
			tempMark = b->arr[i]->mark;
			empty = 0;
			temPos = i;

		}
	}
	if (empty) {
		return NULL;
	}
	b->arr[temPos] = NULL;
	return temp;

}

Student *
extractStudent(Buffer *b, char *name, char *surname)
{
	int i = 0;
	Student *temp;

	for (i = 0; i < b->size; i++) {
		if (b->arr[i] != NULL) {
			if (strcmp(b->arr[i]->name, name) == 0
			    && strcmp(b->arr[i]->surname, surname) == 0) {
				temp = b->arr[i];
				b->arr[i] = NULL;
				return temp;
			}
		}
	}
	return NULL;
}
