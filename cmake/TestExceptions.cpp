void f(void)
            {
                throw "abc";
            }
            void g(void)
            {
                try {
                    f();
                }
                catch(char*){}
            }

int main ()
{

  ;
  return 0;
}
