#include "mmenu.h"

int main() {
	char* options[5] = {"Hey", "There", "Fella", "Choose", "Me"};
	printf("%i", mmenu(options, 5, "Choose an option: "));
}
