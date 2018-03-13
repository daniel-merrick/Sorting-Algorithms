#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sort.h"



void SelectionSort(long *Elements_, long Size_){
	long i, j, minIdx;

	for(j = 0; j < Size_ - 1; j++){
		minIdx = j;
		for(i = j + 1; i < Size_; i++){
			if(Elements_[i] < Elements_[minIdx]){
				minIdx = i;
			}
		}
		if(minIdx != j){
			long swap = Elements_[j];
			Elements_[j] = Elements_[minIdx];
			Elements_[minIdx] = swap;
		}
	}


}

long *Read_From_File(char *Filename_, long *Size_){
	//open binary file for reading
	FILE * fin = fopen(Filename_, "rb");
	
	//check if file open was successful
	if(fin == NULL){
		fprintf(stderr, "Error: File open failed\n");
		return NULL;
	}
	
	//move to end of file
	fseek(fin, 0, SEEK_END);
	
	//calculate number of long ints in file
	*Size_ = ftell(fin) / sizeof(long);
	
	//move to beginning of file
	fseek(fin, 0, SEEK_SET);
	
	//allocate memory for elements
	long *Elements_ = (long *)malloc(sizeof(long) * (*Size_));
	
	//check if allocation was successful
	if(Elements_ == NULL){
		fprintf(stderr, "Error: Malloc for Elements_ failed\n");
		fclose(fin);
		return NULL;
	}
	
	//read elements from file into array
	long Elements_Read_ = fread(Elements_, sizeof(long), *Size_, fin);	
	
	//check if number of elements read doesn't equal number of elements in file
	if(Elements_Read_ != *Size_){
		fprintf(stderr, "Error: Wrong number of elements read from file\n");
		fclose(fin);
		return NULL;
	}

	//close file
	fclose(fin);
	return Elements_;
}

bool Save_To_File(char *Filename_, long *Elements_, long Size_){
	
	//open binary file for writing
	FILE * fout = fopen(Filename_, "wb");
	
	//check if file open failed
	if(fout == NULL){
		fprintf(stderr, "Error: File open for saving failed\n");
		return false;
	}
	
	//Save elements to file
	long Elements_Written_ = fwrite(Elements_, sizeof(long), Size_, fout);
	
	//check if incorrect number of elements saved to file
	if(Elements_Written_ != Size_){
		fprintf(stderr, "Error: Wrong number of elements saved to file\n");
		fclose(fout);
		return false;
	}	

	//close file
	fclose(fout);
	return true;	
}

bool CheckSort(long *Elements_, long Size_){
	long i = 0;
	for(i = 0; i < Size_ - 1 ; i++){
		if(Elements_[i] > Elements_[i + 1]){
			fprintf(stderr, "Error: Array not sorted\n");
			return false;
		}
	}
	return true;
}
