#include <bits/atomicity.h>
int
main ()
{

                using namespace __gnu_cxx;
                _Atomic_word i = 0;
                __atomic_add(&i, 1);
                __exchange_and_add(&i, 1);

  ;
  return 0;
}
