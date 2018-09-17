#include <pthread.h>


//#ifndef PTHREAD_MUTEXTYPE_RECURSIVE
#ifdef PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEXTYPE_RECURSIVE PTHREAD_MUTEX_RECURSIVE
#endif
//#endif

int main(void) {
return (int)MUTEX_TYPE_COUNTING_FAST;
}
