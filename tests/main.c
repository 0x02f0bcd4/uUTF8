#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include "uUTF8_FI.h"

int main(int argc, char **argv){
	struct uUTF8_FI ds;
	const char filename[] = "test-file.txt";
	FILE *f = fopen(filename,"rb");
	if(!f){
		fprintf(stderr,"Failed to open the file - %s\n",filename);
		return 1;
	}else{
		long filesize = 0;
		uint8_t *arr = NULL;
		if(fseek(f, 0, SEEK_END) != 0){
			fprintf(stderr,"Failed to seek to the end of the file - %s\n",filename);
			return 2;
		}else{
			filesize = ftell(f);
			// filesize+1 for the NULL-byte termination;
			arr = calloc(filesize + 1, sizeof(uint8_t));
			if(arr == NULL){
				fprintf(stderr,"Failed to allocate memory to retrieve file content - %s\n",filename);
				return 3;
			}else{
				//read the goddamn file
				fseek(f,0,SEEK_SET);
				size_t file_read = 0;
				if((file_read = fread(arr,sizeof(uint8_t),filesize,f)) != filesize){
					fprintf(stderr,"Failed to read the entirety of the file - %s; Required - %ld, read - %lu\n",filename, filesize,file_read);
					return 4;
				}
			}
		}
		
		uUTF8_Initialize_FI(arr, &ds);
		for(size_t i = 0; i < ds.len; i++){
			printf("0x%x, ",ds.data_arr[i]);
		}
		printf("\n");
		uUTF8_Destroy_FI(&ds);
		free(arr);
		fclose(f);
	}
	return 0;
}
