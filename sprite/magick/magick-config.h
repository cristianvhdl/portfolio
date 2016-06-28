#ifndef IMAGEMAGICK_MULTILIB
#define IMAGEMAGICK_MULTILIB

#include <bits/wordsize.h>

#if __WORDSIZE == 32
# include "magick-config-32.h"
#elif __WORDSIZE == 64
# include "magick-config-64.h"
#else
# error "unexpected value for __WORDSIZE macro"
#endif

#endif
