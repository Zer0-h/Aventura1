/*
 * This code is a test of the functions implemented in my_libc1.c
 * It's required to declare the functions and types in my_lib1.h
 */
 
#include <stdio.h>
#include <string.h>
#include "my_lib.h"

void red () {
  printf("\033[1;31m");
}

void green () {
  printf("\033[1;32m");
}

void reset () {
  printf("\033[0m");
}

int sign(int x) {
	return (x > 0) - (x < 0);
}

int test_strlen(char *strs[], int n) {
	int i;
	
    reset();printf("\n***** Testeando my_strlen() frente a strlen() *****\n");

	for (i= 0; i < n; i++) {
		
		if (strlen(strs[i]) != my_strlen(strs[i])) {
			printf("strs[%d]:\"%s\"\t",i, strs[i]);
			printf("strlen(strs[%d]): %lu\t", i, strlen(strs[i]));
        	printf("my_strlen(strs[%d]): %lu\n", i, my_strlen(strs[i]));
			red();printf("%s failed :-(\n", __func__);
			return EXIT_FAILURE; 
		}
	}

	green();printf("%s passed :-)\n", __func__);
	return EXIT_SUCCESS; 
}

int test_strcmp(char *strs[], int n) {
	int i, j;

	reset();printf("\n***** Testeando my_strcmp() frente a strcmp() *****\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
	
            if (sign(strcmp(strs[i], strs[j])) != sign(my_strcmp(strs[i], strs[j]))) {
                printf("strs[%d]:\"%s\"\t",i, strs[i]);
				printf("strs[%d]:\"%s\"\n",j, strs[j]);
				printf("strcmp(strs[%d], strs[%d])): %d\n", i, j, strcmp(strs[i], strs[j]));
            	printf("my_strcmp(strs[%d], strs[%d])): %d\n", i, j, my_strcmp(strs[i], strs[j]));
				red();printf("%s failed :-(\n", __func__);
                return EXIT_FAILURE;
            }
        }
    }

	green();printf("%s passed :-)\n", __func__);
	return EXIT_SUCCESS;
}

int test_strcpy(char *strs[], int n) {
	int i;
	char dest[20];
	char dest1[20];
	char dest2[20];
	
    reset();printf("\n***** Testeando my_strcpy() frente a strcpy() *****\n");
	dest[0] = 0; dest1[0] = 0; dest2[0] = 0; // Mark as empty strings

	for (i=0; i < n; i++) {
		strcpy(dest1, strs[i]);
		my_strcpy(dest2, strs[i]);
		if (strcmp(dest1, dest2)) {		
			printf("dest: \"%s\"\n",dest);
			printf("strs[%d]: \"%s\"\n",i, strs[i]);
			printf("strcpy(dest, strs[%d]): \"%s\"\n",i,dest1);
			printf("my_strcpy(dest, strs[%d]): \"%s\"\n",i, dest2);
			red();printf("%s failed :-(\n", __func__);
			return EXIT_FAILURE;
		}
		strcpy(dest,dest2);
	}

	green();printf("%s passed :-)\n", __func__);
	return EXIT_SUCCESS;
}

int test_strncpy(char *strs[], int n) {
	int i, len;
	char dest[20];
	char dest1[20];
	char dest2[20];

	memset(dest, 0, sizeof(dest));
	memset(dest1, 0, sizeof(dest1));
	memset(dest2, 0, sizeof(dest2));

	reset();printf("\n***** Testeando my_strncpy() frente a strncpy() *****\n");
	for (i=0; i < n; i++) {

		//dest[0] = 0; dest1[0] = 0; dest2[0] = 0; // Mark as empty strings
		for (len = 1; len < strlen(strs[i]) + 3; len++) { // we test for length 1 to strlen(strs[i]) + 3
			strncpy(dest1, strs[i], len);
			my_strncpy(dest2, strs[i], len);
			//if (strncmp(dest2, strs[i], len)) {
			if (strncmp(dest1, dest2,len)) {
				printf("dest: \"%s\"\n",dest);
				printf("strs[%d]: \"%s\"\n",i, strs[i]);
				printf("strncpy(dest, strs[%d], %d): \"%s\"\n",i,len, dest1);
				printf("my_strncpy(dest, strs[%d], %d): \"%s\"\n",i,len, dest2);
				red();printf("%s failed :-(\n", __func__);
				return EXIT_FAILURE;
			}
			strcpy(dest,dest2);
		}
	}
	green();printf("%s passed :-)\n", __func__);
	return EXIT_SUCCESS;
}

int test_strcat(char *strs[], int n) {
	int i;
	char dest[60];
	char dest1[60];
	char dest2[60];

	reset();printf("\n***** Testeando my_strcat() frente a strcat() *****\n");
	dest[0] = dest1[0] = dest2[0] = 0; // Mark as empty strings

	for (i=0; i < n; i++) {
		strcat(dest1, strs[i]);
		my_strcat(dest2, strs[i]);

		if (strcmp(dest1, dest2)) {
			printf("dest: \"%s\"\n",dest);
			printf("strs[%d]: \"%s\"\n",i, strs[i]);
			printf("strcat(dest, strs[%d]): \"%s\"\n",i, dest1);
			printf("my_strcat(dest, strs[%d]): \"%s\"\n",i,dest2);

		
			red();printf("%s failed :-(\n", __func__);
			return EXIT_FAILURE;
		}
		strcpy(dest,dest2);
	}
	green();printf("%s passed :-)\n", __func__);
	return EXIT_SUCCESS;
}


int main() {
	char *strs[3];
	int n = 3;

	// Init the array of char * with several strings and NULL at the end
	strs[0] = "programa"; // longitud 8
	strs[1] = "compilador"; // longitud 10 
	strs[2] = "depurador"; // longitud 9 

	test_strlen(strs, n);
	test_strcmp(strs, n);
	test_strcpy(strs, n);
	test_strncpy(strs, n);
	test_strcat(strs, n);
	
	printf("\n");
	return EXIT_SUCCESS; // To avoid warning in -Wall
}

