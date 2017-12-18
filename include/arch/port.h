#ifndef ___PORT_H
#define ___PORT_H

#if defined(__CC_ARM)
 # if defined(CORTEX_M4)
 # include <cortex-m4/arm/port.h>
 # elif defined(CORTEX_M0)
 # include <cortex-m0/arm/port.h>
 # else
 # error "Oh my honey, Please select your target architecture."
 # endif
#elif defined(__GNUC__)
 # if defined(CORTEX_M4)
 # include <cortex-m4/gcc/port.h>
 # elif defined(CORTEX_M0)
 # include <cortex-m0/gcc/port.h>
 # else
 # error "Oh my honey, Please select your target architecture."
 # endif
#elif defined(__ICCARM__)
#error "Sorry, IAR aren't supported now."
#else
#error "Oh my honey, Please select your compilation tool."
#endif

#endif

