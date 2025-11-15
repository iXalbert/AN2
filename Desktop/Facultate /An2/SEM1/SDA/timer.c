/* fisierul timer.c */
#include <time.h>
#include "timer.h"
static clock_t aux; 
void starton(void)
{ aux=clock(); 
} 
float startoff(void)
{ return(clock()-(float)aux)/CLOCKS_PER_SEC;
} 
