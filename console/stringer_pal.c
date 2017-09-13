#include "stringer_pal.h"
#include <ctype.h>

char stringer_char_xform(char c)
{
    int input = (int )c;
    int output;

    output = ( isupper(input) ? tolower(input) : toupper(input));

    return (char )output;

}
