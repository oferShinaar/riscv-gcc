/* { dg-options "-Os -msave-restore" } */

/* This test covers a case where we can't (currently) remove the calls to
   the save/restore stubs.  The cast of the return value from BAR requires
   a sign extension between the call to BAR, and the return from FOO, this
   currently prevents the removal of the save/restore calls.  */

typedef enum SomeType
  {
   A = 0,
   B = 1,
   C = 2,
   D = 3
  }
  SomeType;

typedef unsigned int u_32;

extern u_32 bar (u_32 arg);

SomeType foo (u_32 arg)
{
  return (SomeType) bar (arg);
}

/* { dg-final { scan-assembler "call\[ \t\]*t0,__riscv_save_0" } } */
/* { dg-final { scan-assembler "tail\[ \t\]*__riscv_restore_0" } } */
