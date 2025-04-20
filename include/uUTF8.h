#pragma once
#include<stdint.h>
#include<stddef.h>

/* 
*  Get the related codepoint in starting from beg.
*  @Parameters -
*   arr - the arr of uint8_t code
*   beg - from where to begin (inclusive)
*   end - if non-NULL, then will fill with the endpoint (the index
*   after which the current codepoint ended)
*
*  @Return -
*   uint32_t - returning the codepoint if okay, else ~0x0(aka - 0xFF_FF_FF_FF)
*/
uint32_t uUTF8_GetCodepoint(uint8_t *arr, const int beg, int* end);
