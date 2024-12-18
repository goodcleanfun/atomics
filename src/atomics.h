#ifndef ATOMICS_H
#define ATOMICS_H

#if (defined(__has_include) && __has_include(<stdatomic.h>))
#include <stdatomic.h>
#endif // defined(__has_include) && __has_include(<stdatomic.h>)
#endif // ATOMICS_H