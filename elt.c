#include <stdio.h>
#include <string.h>
#include "elt.h"

#if defined(ELT_STRING)
    _element duplicateElt(_element e){
        return strdup(e);
    }
    int compareElt(_element e1, _element e2){
        return strcmp(e1,e2);
    }
    char * toString(_element e){
        return e;
    }
    char* sortstr (char s[50])
    {
        char *str, ch;
        
        str = strdup(s);
          
        int i,j,l;  

        l=strlen(str);

        for(i=1;i<l;i++){
            for(j=0;j<l-i;j++){
                if(str[j]>str[j+1]){
                    ch=str[j];
                    str[j] = str[j+1];
                    str[j+1]=ch;
                }
            }
        }
        
        return strdup(str);
    }
#elif defined(ELT_INT)
    _element duplicateElt(_element e){
        return e;
    }
    
    int compareElt(_element e1, _element e2){
        return e1 - e2;
    }

    char * toString(_element e){
        static char buffer[11];
        sprintf(buffer, "%d", e);
        return buffer;

    }
#endif

