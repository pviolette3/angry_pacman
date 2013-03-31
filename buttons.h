#ifndef __BUTTONS_H__
#define __BUTTONS_H__
#define A (1 << 0)
#define B (1 << 1)
#define SEL (1 << 2)
#define START (1 << 3)
#define D_RIGHT (1 << 4)
#define D_LEFT (1 << 5)
#define D_UP (1 << 6)
#define D_DOWN (1 << 7)
#define R (1 << 8)
#define L (1 << 9)

#define BUTTONS_MASK (*(unsigned int *) 0x4000130)
#define KEY_PRESSED(KEY) (~BUTTONS_MASK & (KEY))

typedef unsigned int button_data;
#endif
