#ifndef SAVING_H_INCLUDED
#define SAVING_H_INCLUDED



#include "tools.h"
#include <stdlib.h>
#include <stdio.h>


#define STRING_SIZE 50

bool SaveArrayIntoFile(char* filename, void* data, size_t data_size, size_t count);
bool CheckIfFileExists(char* filename);
bool ReadSaveFile(char* filename, void* data, size_t data_size, size_t count);








#endif