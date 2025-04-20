#include "uUTF8_FI.h"
#include<stdio.h>
#include "test-main.h"
#include<stdlib.h>

int main(int argc, char **argv){
	const char filename[] = "test-src.txt";
	char* arr = readFile(filename);

	struct uUTF8_FI ds1;
	struct uUTF8_FI ds2;

	if(arr != NULL){
		if(!uUTF8_Initialize_FI(arr,&ds1)){
			fprintf(stderr,"Failed to initialize the ds1, aborting\n");
			free(arr);
			return 3;
		}
	}else{
		fprintf(stderr,"Failed to read file - %s, aborting\n",filename);
		return 1;
	}

	const char filename1[] = "test-pat.txt";
	arr = readFile(filename1);
	if(arr != NULL){
		if(!uUTF8_Initialize_FI(arr,&ds2)){
			fprintf(stderr,"Failed to initialize ds2, aborting\n");
			free(arr);
			return 4;
		}
	}else{
		fprintf(stderr,"Failed to read file - %s, aborting\n",filename);
		return 2;
	}

	printf("Printing the codepoints of filename -\n");
	for(int i = 0; i < ds1.len; i++){
		printf("%u, ",ds1.data_arr[i]);
	}
	putc('\n',stdout);

	printf("Printing the codepoints of filename2 - \n");
	for(int i = 0; i < ds2.len; i++){
		printf("%u, ",ds2.data_arr[i]);
	}
	putc('\n',stdout);

	int pat_idx = uUTF8_FindSubstring(&ds1, &ds2);
	if(pat_idx >= 0){
		printf("Found the pattern, printing the values\n");
		for(int i = pat_idx; i < pat_idx + ds2.len; i++){
			printf("(%u,%u),",ds1.data_arr[i],ds2.data_arr[i-pat_idx]);
		}
		fputc('\n',stdout);
	}else{
		printf("Didn't found the pattern\n");
	}
	uUTF8_Destroy_FI(&ds1);
	uUTF8_Destroy_FI(&ds2);
	return 0;
}
