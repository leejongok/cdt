/*
 ============================================================================
 Name        : c1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main() {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	printf("%s\n", sqlite3_libversion());
	return EXIT_SUCCESS;
}
