#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// helper read test data
int readFromTestFile(char fileName[30], struct Animal testData [NUM_TEST_DATA]);

//helper sorting algorithm
void sortDistances(float distances[NUM_SAMPLES], int indices[NUM_SAMPLES], int isAscending);