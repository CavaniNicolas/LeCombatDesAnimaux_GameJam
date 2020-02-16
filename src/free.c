
#include <SANDAL2/SANDAL2.h>
#include "structure.h"
#include "free.h"

void freeCharacters(Element * characterG, Element * characterD) {
	free(characterG->data);
	free(characterG);
	free(characterD->data);
	free(characterD);
}