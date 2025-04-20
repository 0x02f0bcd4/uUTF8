#include "uUTF8_FI.h"
#include "uUTF8.h"
#include<stdlib.h>
#include<stdbool.h>


bool uUTF8_Initialize_FI(uint8_t *arr, struct uUTF8_FI* ds){
    if(arr == NULL || ds == NULL){
        return false;
    }
    
    size_t arr_size = 0;
    while(arr[arr_size]!= 0x0){
        arr_size++;
    }

    uint32_t *codepoints = calloc(arr_size, sizeof(uint32_t));
    if(codepoints == NULL){
        return false;
    }
    
    int itr = 0;
    int len = 0;
    int end = 0;
    int ret_codepoint = 0;
    while(arr[itr] != 0x0){
        if(arr[itr] <= 0x7f){
            codepoints[len++] = (uint32_t)(arr[itr++]);
        }else{
            ret_codepoint = uUTF8_GetCodepoint(arr,itr,&end);
            if(ret_codepoint == (~0x0)){
				free(codepoints);
                return false;
            }

            codepoints[len++] = ret_codepoint;
            itr = end;
        }
    }

    //now, delete the unnecessary codepoints
    ds->data_arr = calloc(len, sizeof(uint32_t));
    ds->len = len;
    for(size_t i = 0; i < len; i++){
        ds->data_arr[i] = codepoints[i];
    }
    free(codepoints);

    return true;
}

void uUTF8_Destroy_FI(struct uUTF8_FI *ds){
	if(ds != NULL){
		free(ds->data_arr);
		ds->data_arr = NULL;
		ds->len = 0;
	}
}

static bool buildPreprocessingTable(int **table, const struct uUTF8_FI *pat){
	if(pat->len <= 0 || pat->data_arr == NULL){
		return false;
	}

	*table = calloc(sizeof(int),pat->len);
	if(*table == NULL){
		return false;
	}

	
	for(int i = pat->len - 2, j = 0; i >= 0; ){
		if(pat->data_arr[i] == pat->data_arr[pat->len - (j+1)]){
			(*table)[i] = ++j;
			i--;
		}else if(j > 0){
			j = 0;
		}else{
			i--;
		}
	}

	return true;
}

int uUTF8_FindSubstring(const struct uUTF8_FI *src, const struct uUTF8_FI *pat){
	if(src == NULL || pat == NULL){
		return -3;
	}

	if(pat->len > src->len){
		return -4;
	}

	int *table = NULL;
	if(!buildPreprocessingTable(&table,pat)){
		return -2;
	}

	int src_idx = pat->len - 1;
	int pat_idx = pat->len - 1;
	int to_find = -1;
	int traverser = -1;

	while(src_idx < src->len){
		while(src->data_arr[src_idx] == pat->data_arr[pat_idx] && pat_idx >= 0){
			pat_idx--;
			src_idx--;
		}

		if(pat_idx == -1){
			return (++src_idx);
		}

		//else, we had a mismatch
		traverser = pat_idx - 1;
		to_find = (pat->len - (pat_idx + 1));
		if(to_find > 0){
			while(traverser > 0){
				if(table[traverser] == to_find && table[traverser-1] != (to_find + 1)){
					break;
				}

				traverser--;
			}
		}

		if(to_find > 0 && traverser > 0){
			src_idx = to_find + src_idx + (pat_idx - (traverser - 1));
		}else{
			src_idx += 1;
		}
	}

	free(table);
	table = NULL;
	return -1;
}

uint8_t* uUTF8_Decode_FI(const struct uUTF8_FI *ds){
	if(ds == NULL){
		return NULL;
	}

	size_t required_space = 0;

	for(size_t itr = 0; itr < ds->len; itr++){
		if(ds->data_arr[itr] <= 0x7f){
			required_space++;
		}else if(ds->data_arr[itr] <= 0x7ff){
			required_space+=2;
		}else if(ds->data_arr[itr] <= 0xffff){
			//it's not possible, since it's within the bound of surrogate pair
			if(ds->data_arr[itr] >= 0xD800 && ds->data_arr[itr] <= 0xDFFF){
				return NULL;
			}

			required_space += 3;
		}else if(ds->data_arr[itr] <= 0x10FFFF){
			required_space += 4;
		}
	}

	uint8_t *decoded_value = malloc((required_space + 1) * sizeof(uint8_t));
	if(decoded_value == NULL){
		return NULL;
	}

	decoded_value[required_space] = 0x0; //NULL Ending
	
	size_t decoder_itr = 0;
	uint8_t insert_itr = 0;
	uint32_t strip_mask = 0x0;
	
	uint32_t copier = 0x0;
	for(size_t itr = 0; itr < ds->len; itr++){
		if(ds->data_arr[itr] <= 0x7f){
			//just insert it as is
			decoded_value[decoder_itr++] = (uint8_t)(ds->data_arr[itr]);
		}else{
			if(ds->data_arr[itr] <= 0x7ff){
				insert_itr = 2;
				decoded_value[decoder_itr] = 0xC0;
			}else if(ds->data_arr[itr] <= 0xffff){
				insert_itr = 3;
				decoded_value[decoder_itr] = 0xE0;
			}else{
				insert_itr = 4;
				decoded_value[decoder_itr] = 0xF0;
			}
			
			strip_mask = 0x3f;
			copier = ds->data_arr[itr];

			for(uint8_t i = 0; i < insert_itr; i++){
				if(i != insert_itr - 1){
					decoded_value[decoder_itr + insert_itr - (i + 1)] = 0x80;
				}

				decoded_value[decoder_itr + insert_itr - (i+1)] |= (uint8_t)((copier & strip_mask) >> (i * 6));
				strip_mask <<= 6;
			}

			decoder_itr += insert_itr;
		}
	}

	return decoded_value;
}
