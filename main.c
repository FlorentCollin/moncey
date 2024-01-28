#include <stdio.h>
#include <sys/types.h>

#define MA_IMPLEMENTATION
#include "ma.h"
#include "monkey.h"

int main(void) {
	Ma_StringView something = ma_stringview_from_cstr("something");
	Ma_StringView sub = ma_stringview_sub(something, (Ma_StringViewPosition){.start = 1, .end = 4});
	ma_stringview_debug(sub);
}
