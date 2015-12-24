#include "fs.h"

// Liste
void pfslist(filesystem *fs) {

	// On parcourt le File Entries
	int index = 0;
	while (index < FILE_ENTRIES_NUM) {
		if ((*fs).fe[index].name[0] != '\0')
			printf("%s\n", (*fs).fe[index].name);
		index++;
	}
}