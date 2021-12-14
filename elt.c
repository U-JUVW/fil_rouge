
#include <string.h>
#include "elt.h"

#ifdef ELT_STRING
    _element duplicateElt(_element e){
        return strdup(e);
    }
    int compareElt(_element e1, _element e2){
        return strcmp(e1,e2);
    }

#elif defined(ELT_STRUCT)
    ////////////// A MODIFIER ///////////////
    _element duplicateElt(_element e){
        return e;
    }
    int compareElt(_element e1, e2){
        return 0;
    }
    /////////////////////////////////////////
#else
    _element duplicateElt(_element e){
        return e;
    }
    int compareElt(_element e1, _element e2){
        return e1 - e2;
    }
#endif