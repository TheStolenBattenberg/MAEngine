#include "utils.h"

#include <string.h>

const char* GetExtension(const char* file) {
	size_t len = strlen(file);

	const char* p = file + len;

	for (; p > file && *p != '.' && *p != '\\'; --p) { }

	if (*p == '.')
		return p + 1;

	return file + len;
}
