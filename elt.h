/////////////////////////////////////////////////////////////////////////
// CHOISIR ICI CE QUE REPRESENTE LE TYPE _element 
//#define ELT_CHAR          // un caractère ?
//#define ELT_INT             // un entier (choix par défaut) ?
#define ELT_STRING        // une chaîne de caractères ?
//#define ELT_STRUCT        // une structure plus complexe ? 
/////////////////////////////////////////////////////////////////////////


#if ! defined(ELT_CHAR) && ! defined(ELT_INT) && ! defined(ELT_STRING) && ! defined(ELT_STRUCT)
    #define ELT_INT
#endif

#ifdef ELT_CHAR
    typedef char _element;
#endif

#ifdef ELT_INT
    typedef int _element; 
#endif

#ifdef ELT_STRING
    typedef char * _element; 
#endif

#ifdef ELT_STRUCT
    typedef struct {
        int * t; 
        int size;   
    } _element; 

#endif


char * toString(_element e); 
_element genElt(void);
_element duplicateElt(_element e); 
int compareElt(_element e1, _element e2); 