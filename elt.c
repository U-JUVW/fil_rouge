#include <stdio.h>
#include <string.h>
#include "elt.h"

//Case of a string
#if defined(ELT_STRING)
    //Duplicate the _element argument
    _element duplicateElt(_element e){
        return strdup(e);
    }
    //Compare two _element (string) based on lexicographic order
    int compareElt(_element e1, _element e2){
        return strcmp(e1,e2);
    }
    
    char * toString(_element e){
        return e;
    }
    //Sort letters in alphabetical order within a string
    char* sortstr (char * s)
    {
        char *str, ch;
        
        str = strdup(s);
          
        int i,j,l;  

        l=strlen(str);

        //Iterate through the initial string and append letters to the output
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


//USED FOR TESTINF PURPOSE ONLY :
#elif defined(ELT_INT)
    //Duplicate the _element
    _element duplicateElt(_element e){
        return e;
    }

    int compareElt(_element e1, _element e2){
        return e1 - e2;
    }
    //Get a string representation of _element e
    char * toString(_element e){
        static char buffer[11];
        sprintf(buffer, "%d", e);
        return buffer;

    }
#endif

