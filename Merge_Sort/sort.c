#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"



void MergeSort(long *Elements_, long Size_){
	long *aux_Elements_ = (long *)malloc(sizeof(long) * Size_);
	memcpy(aux_Elements_, Elements_, sizeof(long) * Size_);
	MergeSort_Helper(aux_Elements_, Elements_, 0, Size_ - 1);
	free(aux_Elements_);
}

void MergeSort_Helper(long *elements_, long* aux, int low, int high){
	if(high > low + 8){ //Use Merge Sort when merging large arrays
		int mid_point = ( (high - low) / 2 ) + low; //Get the midpoint index of the array
		MergeSort_Helper(aux, elements_, low, mid_point);
		MergeSort_Helper(aux, elements_, mid_point + 1, high);

		//Using the concept of 'Natural Merge Sort,' 
		//If the largest element in the left array is 
		//Greater than the smallest elements in the right array
		//Then the arrays are already in sorted order
		if( (elements_[mid_point] <= elements_[mid_point + 1]) ){
			memcpy(aux + low, elements_ + low, (high - low + 1) * sizeof(long));
			return;
		}

		else{ //Merging
			int i, j, k;
			i = low;
			j =  mid_point + 1;
			for(k = low; k <= high; k++){
				if 	(i > mid_point)			{ aux[k] = elements_[j++]; }
				else if	(j > high) 			{ aux[k] = elements_[i++]; }
				else if	(elements_[j] < elements_[i]) 	{ aux[k] = elements_[j++]; }
				else					{ aux[k] = elements_[i++]; }
			}
		}
	}
	else{ //Use insertion sort when sorting small arrays because it is faster
                        int i = 0;
                        int j = 0;
                        for(i = low + 1; i <= high; i++){
                                long swp = aux[i];
                                for(j = i - 1; j >= low && (aux[j] > swp); j--){
                                        aux[j + 1] = aux[j];
                                }
                                aux[j + 1] = swp;
                        }
	}
}


long *Read_From_File(char *Filename_, long *Size_){
	FILE *fin = fopen(Filename_, "rb");

	if(fin == NULL){
		fprintf(stderr, "Error: File open failed\n");
		return NULL;
	}

	fseek(fin, 0, SEEK_END);

	*Size_ = ftell(fin) / sizeof(long);

	fseek(fin, 0, SEEK_SET);

	long *Elements_ = (long *)malloc(sizeof(long) * (*Size_));

	if(Elements_ == NULL){
		fprintf(stderr, "Error: Malloc for Elements_ failed\n");
		fclose(fin);
		return NULL;
	}

	long Elements_Read_ = fread(Elements_, sizeof(long), *Size_, fin);

	if(Elements_Read_ != *Size_){
		fprintf(stderr, "Error: Wrong number of elements read from file\n");
		fclose(fin);
		return NULL;
	}

	fclose(fin);

	return(Elements_);
	
}

bool Save_To_File(char *Filename_, long *Elements_, long Size_){

	FILE * fout = fopen(Filename_, "wb");

	if(fout == NULL){
		fprintf(stderr, "Error: File open for saving failed\n");
		return false;
	}

	long Elements_Written_ = fwrite(Elements_, sizeof(long), Size_, fout);

	if(Elements_Written_ != Size_){
		fprintf(stderr, "Error: Wrong number of elements saved to file\n");
		fclose(fout);
		return false;
	}

	fclose(fout);

	return true;
}

bool CheckSort(long *Elements_, long Size_){
	long i = 0;
	for(i = 0; i < Size_ - 1; i++){
		if(Elements_[i] > Elements_[i + 1]){
			fprintf(stderr, "Error: Array not sorted\n");
			return false;
		}
	}
	return true;
}
