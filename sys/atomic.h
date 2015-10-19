

#ifndef SYS_ATOMIC_H
#define SYS_ATOMIC_H


#define LOCK "lock ; "

typedef struct { volatile int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

#define atomic_read(v)		((v)->counter)

#define atomic_set(v,i)		(((v)->counter) = (i))

static __inline__ void atomic_add(int i, atomic_t *v)
{
__asm__ __volatile__(
LOCK "addl %1,%0"
:"=m" (v->counter)
:"ir" (i), "m" (v->counter));
}

static __inline__ void atomic_sub(int i, atomic_t *v)
{
__asm__ __volatile__(
LOCK "subl %1,%0"
:"=m" (v->counter)
:"ir" (i), "m" (v->counter));
}


static __inline__ int atomic_add_return(int i, atomic_t *v)
{
int __i;
__i = i;
__asm__ __volatile__(
LOCK "xaddl %0, %1"
:"+r" (i), "+m" (v->counter)
: : "memory");
return i + __i;
}

static __inline__ int atomic_sub_return(int i, atomic_t *v)
{
return atomic_add_return(-i,v);
}


static __inline__ int atomic_sub_and_test(int i, atomic_t *v)
{
unsigned char c;

__asm__ __volatile__(
LOCK "subl %2,%0; sete %1"
:"=m" (v->counter), "=qm" (c)
:"ir" (i), "m" (v->counter) : "memory");
return c;
}

static __inline__ void atomic_inc(atomic_t *v)
{
__asm__ __volatile__(
LOCK "incl %0"
:"=m" (v->counter)
:"m" (v->counter));
}

static __inline__ void atomic_dec(atomic_t *v)
{
__asm__ __volatile__(
LOCK "decl %0"
:"=m" (v->counter)
:"m" (v->counter));
}

static __inline__ int atomic_dec_and_test(atomic_t *v)
{
unsigned char c;

__asm__ __volatile__(
LOCK "decl %0; sete %1"
:"=m" (v->counter), "=qm" (c)
:"m" (v->counter) : "memory");
return c != 0;
}

static __inline__ int atomic_inc_and_test(atomic_t *v)
{
unsigned char c;

__asm__ __volatile__(
LOCK "incl %0; sete %1"
:"=m" (v->counter), "=qm" (c)
:"m" (v->counter) : "memory");
return c != 0;
}

static __inline__ int atomic_add_negative(int i, atomic_t *v)
{
unsigned char c;

__asm__ __volatile__(
LOCK "addl %2,%0; sets %1"
:"=m" (v->counter), "=qm" (c)
:"ir" (i), "m" (v->counter) : "memory");
return c;
}

#define atomic_clear_mask(mask, addr) \
__asm__ __volatile__(LOCK "andl %0,%1" \
: : "r" (~(mask)),"m" (*addr) : "memory")

#define atomic_set_mask(mask, addr) \
__asm__ __volatile__(LOCK "orl %0,%1" \
: : "r" (mask),"m" (*(addr)) : "memory")

#define atomic_inc_return(v)  (atomic_add_return(1,v))
#define atomic_dec_return(v)  (atomic_sub_return(1,v))

#endif // ATOMIC_H