#pragma once
#include<stdint.h>
#include<stdbool.h>
#include<stddef.h>

/*
* Use this when you need Fast Indexing(FI) of the codepoints
*/
struct uUTF8_FI{
    uint32_t *data_arr;
    size_t len;
};

/*
* make sure to end the arr with an extra NULL-byte termination
* (like seen in ASCII string)
*
* @Parameters
* arr - an uint8_t array containing the raw UTF8 data (NULL-byte terminated)
* ds - an uUTF8_FI data structure to be initialized. This function doesn't
* allocate any memory
* 
* @Return 
* bool - true if everthing went correctly, false otherwise
*/
bool uUTF8_Initialize_FI(uint8_t *arr, struct uUTF8_FI* ds);

/*
* 	Return the index of the first time pat was found inside src
*
* 	@Return
* 	>=0: The location
*	-1: pat wasn't found inside src
*	-2: Couldn't preprocess the pattern
*	-3: Either src/pattern is null
*	-4: pat is larger than src
*/
int uUTF8_FindSubstring(const struct uUTF8_FI *src, const struct uUTF8_FI *pat);

/*
 * Be noted - this doesn't free any allocated dynamic memory. 
 * If you obtained uUTF8_FI through a dynamic memory allocation
 * You are solely responsible to clear it up
 */
void uUTF8_Destroy_FI(struct uUTF8_FI *ds);


/*
 * Decode the given codepoints to a uint8_t array
 * Dynamically allocated memory, use free() to deallocate 
 * after using them
 * 
 * @Return
 * uint8_t* - NULL if error occurs, else a dynamically allocated
 * array containing the decoded data
 */
uint8_t *uUTF8_Decode_FI(const struct uUTF8_FI *ds);
