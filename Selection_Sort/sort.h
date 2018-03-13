#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/*****************************
 * store number of long ints
 * from input file
 * in 'Size' and return a long
 * *array of stored elements
 * read from input file
 * return NULL on failure
*****************************/
long *Read_From_File(char *Filename, long *Size);

/*****************************
 * Save array of long ints
 * to outputFile and return 
 * false on failure
*****************************/
bool Save_To_File(char *Filename, long *Elements_, long Size);


/******************************
 * Perform SelectionSort on
 * array of Elements_
******************************/
void SelectionSort(long *Elements_, long Size);


/*****************************
 * Check if array of Elements_
 * is sorted ...
 * return false if not sorted
*****************************/
bool CheckSort(long *Elements_, long Size_);
