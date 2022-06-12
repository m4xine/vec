#include <stdio.h>
#include <vec.h>

int 
main(void)
{
  VecInt ints;
  vec(&ints);

  for (int i = 0; i < 10; ++i)
    vec_push(&ints, i * 3);

  for (size_t i = 0; i < ints.len; ++i)
    printf("%zu: %i\n", i, vec_at(&ints, i));

  vec_del(&ints);
  return 0;
}