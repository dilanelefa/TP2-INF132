#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aide.h"

char *toUpperCase(char *str) 
{
    int i;
    char *str_cpy = malloc((strlen(str))*sizeof(char));
    char cons = 'A'-'a';
    for( i = 0; i < strlen(str); i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
            str_cpy[i] = str[i] + cons;
        else 
        	str_cpy[i] = str[i];
    }
    
    return str_cpy;
}

char *toLowerCase(char *str) 
{
    int i;
    char *str_cpy = malloc((strlen(str))*sizeof(char));
    char cons = 'a'-'A';
    for( i = 0; i < strlen(str); i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str_cpy[i] = str[i] + cons;
        else 
        	str_cpy[i] = str[i];
    }
    
    return str_cpy;
}
