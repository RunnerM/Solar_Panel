
#pragma once

#include <stdint.h>

enum special_keys {
	A = 10,
	B,
	C,
	D,
	STAR,
	HASH
};

void matrix_keyboard_init(void);

int8_t matrix_keyboard_get_key(void);
