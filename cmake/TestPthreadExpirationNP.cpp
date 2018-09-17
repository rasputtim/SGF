#include <pthread.h>
#include <time.h>

int main(int argc, char *argv[])
{
    struct timespec   delta;
    struct timespec   abstime;

      pthread_get_expiration_np(&delta, &abstime);

   return 0;
}
