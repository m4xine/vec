#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <string.h>

#ifndef VEC_DEF_CAP 
#define VEC_DEF_CAP 64
#endif // VEC_DEF_CAP

#define Vec(t)    \
  struct          \
  {               \
    t      *raw;  \
    size_t  len,  \
            cap;  \
  }      

typedef Vec(void *) VecVoidP;
typedef Vec(char *) VecCharP;
typedef Vec(int)    VecInt;
typedef Vec(char)   VecChar;
typedef Vec(float)  VecFloat;
typedef Vec(double) VecDouble;

#define vec(v) (memset(v, 0, sizeof(*(v))))

#define vec_grow(v, n) \
  (vec__grow((void **)&(v)->raw, &(v)->len, &(v)->cap, sizeof(*(v)->raw), n))

#define vec_push(v, e) \
  (vec__grow((void **)&(v)->raw, &(v)->len, &(v)->cap, sizeof(*(v)->raw), 1), \
   (v)->raw[(v)->len ++] = (e))

#define vec_at(v, i) ((v)->raw[i])

#define vec_clear(v) ((v)->len = 0)

#define vec_del(v) \
  ((v)->raw ? free((v)->raw) : 0, memset(v, 0, sizeof(*v)), 0) 

void
vec__init(void   **raw, 
          size_t  *len, 
          size_t  *cap,
          size_t   tysz)
{
  if (0 == *cap) *cap = VEC_DEF_CAP;
  if (NULL == raw) *raw = malloc(tysz * *cap);
}

void
vec__grow(void   **raw,
          size_t  *len,
          size_t  *cap,
          size_t   tysz,
          size_t   n)
{
  vec__init(raw, len, cap, tysz);

  while (*cap < *len + n) *cap *= 2;
  *raw = realloc(*raw, tysz * *cap);
}

void
vec__push_n(void   **raw,
            size_t  *len,
            size_t  *cap,
            size_t   tysz,
            void    *ptr,
            size_t   n)
{
  vec__grow(raw, len, cap, tysz, n);

  memcpy((char *)*raw + (tysz * *len), ptr, n * tysz);
  *len += n;
}

#endif // VEC_H