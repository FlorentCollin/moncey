#pragma once

#include <assert.h>
#include <stdio.h>
#include <malloc/_malloc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

#define MA_DA_INIT_CAP 256

// Append an item to a dynamic array
#define ma_da_append(da, item) \
	do { \
		if ((da)->length >= (da)->capacity) { \
			(da)->capacity = (da)->capacity == 0 ? MA_DA_INIT_CAP : (da)->capacity * 2; \
			(da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items)); \
			assert((da)->items != NULL && "Buy more RAM..."); \
		} \
\
		(da)->items[(da)->length++] = (item); \
	} while(0) \

#define ma_da_free(da) free((da).items)

extern void* ma_debug_malloc(size_t size, char* file, int line);
extern void ma_debug_free(void* ptr, char* file, int line);

typedef struct {
    size_t length;
    const char *data;
} Ma_StringView;

typedef struct {
	size_t start;
	size_t end;
} Ma_StringViewPosition;

Ma_StringView ma_stringview_from_cstr(char* cstr);
Ma_StringView ma_stringview_from_parts(char* cstr, size_t length);
Ma_StringView ma_stringview_sub(Ma_StringView sv, Ma_StringViewPosition pos);
bool ma_stringview_eq(Ma_StringView first, Ma_StringView second);
void ma_stringview_debug(Ma_StringView sv);

#define malloc(size) ma_debug_malloc(size, __FILE__, __LINE__)
#define free(ptr) ma_debug_free(ptr, __FILE__, __LINE__)


///////////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////////
// #define MA_IMPLEMENTATION
#ifdef MA_IMPLEMENTATION

#undef malloc
void* ma_debug_malloc(size_t size, char* file, int line) {
	void* ptr = malloc(size);
	printf("%s:%d allocating %zu bytes, return address %p\n", file, line, size, ptr);
	assert(ptr);

	return ptr;
}
#define malloc(size) ma_debug_malloc(size, __FILE__, __LINE__)

#undef free
void ma_debug_free(void* ptr, char* file, int line) {
	printf("%s:%d freeing %p\n", file, line, ptr);
	free(ptr);
}
#define free(ptr) ma_debug_free(ptr, __FILE__, __LINE__)


/*****************/
/* Ma_StringView */
/*****************/
Ma_StringView ma_stringview_from_cstr(char* cstr) {
	return ma_stringview_from_parts(cstr, strlen(cstr));
}

Ma_StringView ma_stringview_from_parts(char* cstr, size_t length) {
	Ma_StringView sv;
	sv.length = length;
	sv.data = cstr;
	return sv;
}

Ma_StringView ma_stringview_sub(Ma_StringView sv, Ma_StringViewPosition pos) {
	assert(pos.start <= pos.end && "`pos.start` must be <= than `pos.end`");
	assert(pos.end <= sv.length && "`pos.end` must be <= than `sv.length`");

	return (Ma_StringView){
		.length = pos.end - pos.start,
		.data = &sv.data[pos.start],
	};
}

bool ma_stringview_eq(Ma_StringView first, Ma_StringView second) {
	if (first.length != second.length) {
		return false;
	}

	return memcmp(first.data, second.data, first.length) == 0;
}

void ma_stringview_debug(Ma_StringView sv) {
	printf("%.*s\n", (int)sv.length, sv.data);
}

#endif // MA_IMPLEMENTATION
