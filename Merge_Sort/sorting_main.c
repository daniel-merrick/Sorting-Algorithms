#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "sort.h"


int main(int argc, char **argv){
	if(argc != 3){
		fprintf(stdout, "Usage: <inputFile> <outputFile>\n");
		return EXIT_FAILURE;
	}

	long Size_ = 0;
	long *Elements_ = NULL;
	Elements_ = Read_From_File(argv[1], &Size_);
	if(Elements_ == NULL){
		fprintf(stdout, "Error: Reading from file failed\n");
		return EXIT_FAILURE;
	}

	clock_t start_t, total_t;

	start_t = clock();

	MergeSort(Elements_, Size_);

	total_t = (clock() - start_t);
	
	if(CheckSort(Elements_, Size_) == false){
		free(Elements_);
		return EXIT_FAILURE;
	}

	if(Save_To_File(argv[2], Elements_, Size_) == false){
		fprintf(stdout, "Error: Saving to file failed\n");
		free(Elements_);
		return EXIT_FAILURE;
	}

	free(Elements_);
	fprintf(stdout, "Total number of Clock Tics to sort array: %ld\n", total_t);
	fprintf(stdout, "Total time taken by CPU in seconds to sort: %f\n", (double)(total_t) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}

