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
	//'Size_' holds the number of elements in the input file
	long Size_ = 0;
	
	//'Elements_' hold the numbers to be sorted from the input file
	long *Elements_ = NULL;
	
	//store numbers into the array 'Elements_' ... return NULL on failure
	Elements_ = Read_From_File(argv[1], &Size_);
	if(Elements_ == NULL){
		fprintf(stdout, "Error: Reading from file failed\n");
		return EXIT_FAILURE;
	}
	
	clock_t start_t, end_t, total_t;
	//get start clock tic
	start_t = clock();
	
	//sort array
	SelectionSort(Elements_, Size_);	
	
	//get end clock tic
	end_t = clock();

	//get total clock tics
	total_t = (end_t - start_t);
	
	//check if array is properly sorted ... return false if not sorted
	if(CheckSort(Elements_, Size_) == false){
		free(Elements_);
		return EXIT_FAILURE;
	}	
		
	//save sorted array to output file ... return false on save failure
	if(Save_To_File(argv[2], Elements_, Size_) == false){
		fprintf(stdout, "Error: Saving to file failed\n");
		free(Elements_);
		return EXIT_FAILURE;
	}	
	
	//free array of numbers
	free(Elements_);


	//print time taken to sort array
	fprintf(stdout, "Total number of ClockTics to sort array: %ld\n", total_t);
	fprintf(stdout, "Total time taken by CPU in seconds to sort: %f\n", (double)(total_t)/CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}
