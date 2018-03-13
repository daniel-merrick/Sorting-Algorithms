#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sort.h"



void QuickSort(long *Elements_, long Size_){
	QuickSort_Helper(Elements_, 0, Size_ - 1);
}

void QuickSort_Helper(long *Elements_, long LB_, long UB_){
	if(LB_ >= UB_){
		return;
	}
	long pivot_idx = partition(Elements_, LB_, UB_);
	QuickSort_Helper(Elements_, LB_, pivot_idx - 1);
	QuickSort_Helper(Elements_, pivot_idx + 1, UB_);
}

long partition(long *Elements_, long LB_, long UB_){
	long pivot = Elements_[LB_];
	long down = LB_;
	long up = UB_;
	while(down < up){
		while(Elements_[down] <= pivot && down < UB_){down++;}
		while(Elements_[up] > pivot){up--;}
		if(down < up){
			long swap = Elements_[down];
			Elements_[down] = Elements_[up];
			Elements_[up] = swap;
		}
	}
	Elements_[LB_] = Elements_[up];
	Elements_[up] = pivot;
	return up;
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
