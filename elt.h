//Defining the type of _element and the prototypes of the functions
//ELT_INT was used for testing purpose

//#define ELT_INT
#define ELT_STRING      
    
#if !defined(ELT_INT) && !defined(ELT_STRING)
    #define ELT_STRING
#endif

#ifdef ELT_INT
    typedef int _element; 
#endif

#ifdef ELT_STRING
    typedef char * _element; 
    char *sortstr(char *str);
#endif

//Prototypes of functions used for both types
char * toString(_element e); 
_element genElt(void);
_element duplicateElt(_element e); 
int compareElt(_element e1, _element e2); 