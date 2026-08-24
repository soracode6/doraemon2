#ifndef MACROS_H
#define MACROS_H

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define ALIGNED(x) __attribute__((aligned(x)))

#ifndef __GNUC__
#define __attribute__(x)
#endif

#endif
