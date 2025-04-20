#include "uUTF8.h"
#include <stdbool.h>

uint32_t uUTF8_GetCodepoint(uint8_t *arr, const int beg, int *end)
{
    int itr = beg;
    uint8_t first = arr[beg];
    uint32_t codepoint = 0x0;

    uint8_t octet_count = 0;
    uint8_t data_temp = 0;
    uint8_t octet_read = 0;

    const uint8_t bitcount_mask = 0x80;

    if (first <= 0x7f)
    {
        codepoint = (uint32_t)first;
    }
    else
    {
        octet_count = 0;
        data_temp = first;

        while ((data_temp & bitcount_mask) != 0 && octet_count < 5)
        {
            octet_read = arr[itr];
            if (octet_count > 0)
            {

                // if it's not the first octet
                // and the major two bits aren't 10
                // then it is a incorrect uint8 array
                if ((octet_read & 0xC0) != 0x80)
                {
                    return (~0x0);
                }
            }else if(octet_read == 0x80){
				//the very first byte can't be 0x80
				return (~0x0);
			}

            // 0x0 is compared because a mf can be ending a string in the middle of the comparison
            if (octet_read == 0x0 || octet_read == 0xC0 || octet_read == 0xC1 || (octet_read >= 0xF5 && octet_read <= 0xff))
            {
                return (~0x0);
            }

            octet_count++;
            data_temp <<= 1;
            itr++;
        }

        if (octet_count > 1 && octet_count < 5)
        {
            // build the codepoint is okay
            // code point of U+D800 to U+DFFF isn't okay
            itr -= octet_count;

            data_temp = 0x0;
            for (int i = 0; i < octet_count; i++)
            {
                if (i != 0)
                {
                    data_temp = arr[i + itr];
                    // shift 6 bits to left, copy them to the last 6 characters
                    codepoint <<= 6;
                    // unset the first two bits (1 and 0)
                    data_temp &= 0x3f;
					codepoint |= (uint32_t)data_temp;
                }
                else
                {
                    data_temp = arr[itr];
                    data_temp = ~data_temp;
                    uint8_t shifter = (int8_t)0x80 >> octet_count;
                    data_temp |= shifter;
                    data_temp = ~data_temp;

					codepoint |= (uint32_t)data_temp;
                }
            }

            itr += octet_count;
            // this range isn't allowed because it's the
            // surrogate range of UTF-16
            // so if someone used it, it's a wrong UTF-8
            // codepoint
            if (codepoint >= 0xD800 && codepoint <= 0xDFFF)
            {
                return (~0x0);
            }
        }
        else
        {
            return (~0x0);
        }
    }

    if(end != NULL)
        *end = itr;

    return codepoint;
}

