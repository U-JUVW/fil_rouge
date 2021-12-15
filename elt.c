#include <stdio.h>
#include <string.h>
#include "elt.h"

#if defined(ELT_STRING) || defined(ELT_CHAR)
    _element duplicateElt(_element e){
        return strdup(e);
    }
    int compareElt(_element e1, _element e2){
        return strcmp(e1,e2);
    }
    char * toString(_element e){
        return e;
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

