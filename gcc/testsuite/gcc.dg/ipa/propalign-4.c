/* { dg-do compile } */
/* { dg-options "-O2 -fdump-ipa-cp"  } */
/* { dg-skip-if "No alignment restrictions" { { ! natural_alignment_32 } && { ! natural_alignment_64 } } } */

int n;

static void
__attribute__ ((noinline))
test(void *a)
{
  __builtin_memset (a,0,n);
}

static __attribute__ ((aligned(16))) int aa[10];

int
main()
{
  test (&aa[1]);
  test (&aa[3]);
  return 0;
}
/* { dg-final { scan-ipa-dump "Alignment 8, misalignment 4"  "cp"  } } */
