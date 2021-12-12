
#include <string.h>
#include "elt.h"

#ifdef ELT_STRING
	_element duplicateElt(_element e){
		return strdup(e);
	}
#else
	_element duplicateElt(_element e){
		return e;
	}
#endif