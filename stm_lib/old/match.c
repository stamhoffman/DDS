#include "match.h"

// construction of degree t in k
int exponentiation(int t, int k)
{
  int res = 1;
  while (k)
      {
        if (k & 1)
            res *= t;
	t *= t;
	k >>= 1;
      }
  return res;
}


