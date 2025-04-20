#include "test-main.h"
#include<stdlib.h>
#include<stdio.h>

char* readFile(const char *filename){
	FILE *f = fopen(filename,"rb");
	char *arr = NULL;

	if(!f){
		fprintf(stderr,"Failed to open the file - %s\n",filename);
		return arr;
	}else{

		if(fseek(f,0,SEEK_END)){
			fprintf(stderr,"Failed to seek to the END in the file, aborting\n");
			fclose(f);
			return arr;
		}

		long pos = ftell(f);
		if(fseek(f,0,SEEK_SET)){
			fprintf(stderr,"Failed to seek to the SET in the file, aborting\n");
			fclose(f);
			return arr;
		}

		arr = malloc(pos + 1);
		if(arr != NULL){
			arr[pos] = 0;
			if(fread(arr, sizeof(char), pos, f)!= pos){
				free(arr);
				arr = NULL;
				fprintf(stderr,"Failed to read the whole file, aborting\n");
				fclose(f);
				return arr;
			}
		}else{

			fprintf(stderr,"Failed to allocate the memory\n");
		}

		fclose(f);

	}
	return arr;
}
