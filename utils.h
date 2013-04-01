#ifndef __UTILS_H__
#define __UTILS_H__
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define LENGTH(arr) (sizeof(( arr )) == 0 ? 0 : sizeof((arr))/ sizeof(( arr )[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
