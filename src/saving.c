#include "saving.h"

#define STRING_SIZE 50




bool SaveArrayIntoFile(char* filename, void* data, size_t data_size, size_t count){
    FILE* fp = fopen(filename, "wb");
    if(!fp){
        return false;
    }
    fwrite(data, data_size, count, fp);
    fclose(fp);
    return true;
}

bool CheckIfFileExists(char* filename){
    FILE* fp = fopen(filename, "r");
    if(!fp) return false;
    else return true;
}

bool ReadSaveFile(char* filename, void* data, size_t data_size, size_t count){
    FILE* fp = fopen(filename, "rb");
    if(!fp){
        printf("Failure\n");
        exit(0);
        return false;
    }
    fread(data, data_size, count, fp);
    fclose(fp);
    return true;
}