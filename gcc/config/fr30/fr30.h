/*{{{  Comment.  */ 

/* Definitions of FR30 target. 
   Copyright (C) 1998-2016 Free Software Foundation, Inc.
   Contributed by Cygnus Solutions.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

/*}}}*/ 
/*{{{  Run-time target specifications.  */ 

#undef  ASM_SPEC
#define ASM_SPEC ""

/* Define this to be a string constant containing `-D' options to define the
   predefined macros that identify this machine and system.  These macros will
   be predefined unless the `-ansi' option is specified.  */

#define TARGET_CPU_CPP_BUILTINS()		\
  do						\
    {						\
      builtin_define_std ("fr30");		\
      builtin_assert ("machine=fr30");		\
    }						\
   while (0)

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crt0.o%s crti.o%s crtbegin.o%s"

/* Include the OS stub library, so that the code can be simulated.
   This is not the right way to do this.  Ideally this kind of thing
   should be done in the linker script - but I have not worked out how
   to specify the location of a linker script in a gcc command line yet... */
#undef  ENDFILE_SPEC
#define ENDFILE_SPEC  "%{!mno-lsim:-lsim} crtend.o%s crtn.o%s"

#undef  LIB_SPEC
#define LIB_SPEC "-lc"

#undef  LINK_SPEC
#define LINK_SPEC "%{h*} %{v:-V} \
		   %{static:-Bstatic} %{shared:-shared} %{symbolic:-Bsymbolic}"

/*}}}*/ 
/*{{{  Storage Layout.  */ 

#define BITS_BIG_ENDIAN 1

#define BYTES_BIG_ENDIAN 1

#define WORDS_BIG_ENDIAN 1

#define UNITS_PER_WORD 	4

#define PROMOTE_MODE(MODE,UNSIGNEDP,TYPE)	\
  do						\
    {						\
      if (GET_MODE_CLASS (MODE) == MODE_INT	\
	  && GET_MODE_SIZE (MODE) < 4)		\
	(MODE) = SImode;			\
    }						\
  while (0)

#define PARM_BOUNDARY 32

#define STACK_BOUNDARY 32

#define FUNCTION_BOUNDARY 32

#define BIGGEST_ALIGNMENT 32

#define DATA_ALIGNMENT(TYPE, ALIGN)		\
  (TREE_CODE (TYPE) == ARRAY_TYPE		\
   && TYPE_MODE (TREE_TYPE (TYPE)) == QImode	\
   && (ALIGN) < BITS_PER_WORD ? BITS_PER_WORD : (ALIGN))

#define CONSTANT_ALIGNMENT(EXP, ALIGN)  \
  (TREE_CODE (EXP) == STRING_CST	\
   && (ALIGN) < BITS_PER_WORD ? BITS_PER_WORD : (ALIGN))

#define STRICT_ALIGNMENT 1

#define PCC_BITFIELD_TYPE_MATTERS 1

/*}}}*/ 
/*{{{  Layout of Source Language Data Types.  */ 

#define SHORT_TYPE_SIZE 	16
#define INT_TYPE_SIZE 		32
#define LONG_TYPE_SIZE 		32
#define LONG_LONG_TYPE_SIZE 	64
#define FLOAT_TYPE_SIZE 	32
#define DOUBLE_TYPE_SIZE 	64
#define LONG_DOUBLE_TYPE_SIZE 	64

#define DEFAULT_SIGNED_CHAR 1

#undef  SIZE_TYPE
#define SIZE_TYPE "unsigned int"

#undef  PTRDIFF_TYPE
#define PTRDIFF_TYPE "int"

#undef  WCHAR_TYPE
#define WCHAR_TYPE "long int"

#undef  WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE BITS_PER_WORD

/*}}}*/ 
/*{{{  REGISTER BASICS.  */ 

/* Number of hardware registers known to the compiler.  They receive numbers 0
   through `FIRST_PSEUDO_REGISTER-1'; thus, the first pseudo register's number
   really is assigned the number `FIRST_PSEUDO_REGISTER'.  */
#define FIRST_PSEUDO_REGISTER	21

/* Fixed register assignments: */

/* Here we do a BAD THING - reserve a register for use by the machine
   description file.  There are too many places in compiler where it
   assumes that it can issue a branch or jump instruction without
   providing a scratch register for it, and reload just cannot cope, so
   we keep a register back for these situations.  */
#define COMPILER_SCRATCH_REGISTER 0

/* The register that contains the result of a function call.  */
#define RETURN_VALUE_REGNUM	 4

/* The first register that can contain the arguments to a function.  */
#define FIRST_ARG_REGNUM	 4

/* A call-used register that can be used during the function prologue.  */
#define PROLOGUE_TMP_REGNUM	 COMPILER_SCRATCH_REGISTER
     
/* Register numbers used for passing a function's static chain pointer.  If
   register windows are used, the register number as seen by the called
   function is `STATIC_CHAIN_INCOMING_REGNUM', while the register number as
   seen by the calling function is `STATIC_CHAIN_REGNUM'.  If these registers
   are the same, `STATIC_CHAIN_INCOMING_REGNUM' need not be defined.

   The static chain register need not be a fixed register.

   If the static chain is passed in memory, these macros should not be defined;
   instead, the next two macros should be defined.  */
#define STATIC_CHAIN_REGNUM 	12
/* #define STATIC_CHAIN_INCOMING_REGNUM */

/* An FR30 specific hardware register.  */
#define ACCUMULATOR_REGNUM	13

/* The register number of the frame pointer register, which is used to access
   automatic variables in the stack frame.  On some machines, the hardware
   determines which register this is.  On other machines, you can choose any
   register you wish for this purpose.  */
#define FRAME_POINTER_REGNUM	14
     
/* The register number of the stack pointer register, which must also be a
   fixed register according to `FIXED_REGISTERS'.  On most machines, the
   hardware determines which register this is.  */
#define STACK_POINTER_REGNUM	15

/* The following a fake hard registers that describe some of the dedicated
   registers on the FR30.  */
#define CONDITION_CODE_REGNUM	16
#define RETURN_POINTER_REGNUM	17
#define MD_HIGH_REGNUM		18
#define MD_LOW_REGNUM		19

/* An initializer that says which registers are used for fixed purposes all
   throughout the compiled code and are therefore not available for general
   allocation.  These would include the stack pointer, the frame pointer
   (except on machines where that can be used as a general register when no
   frame pointer is needed), the program counter on machines where that is
   considered one of the addressable registers, and any other numbered register
   with a standard use.

   This information is expressed as a sequence of numbers, separated by commas
   and surrounded by braces.  The Nth number is 1 if register N is fixed, 0
   otherwise.

   The table initialized from this macro, and the table initialized by the
   following one, may be overridden at run time either automatically, by the
   actions of the macro `TARGET_CONDITIONAL_REGISTER_USAGE', or by the user
   with the command options `-ffixed-REG', `-fcall-used-REG' and
   `-fcall-saved-REG'.  */
#define FIXED_REGISTERS 			\
  { 1, 0, 0, 0, 0, 0, 0, 0, 	/*  0 -  7 */ 	\
    0, 0, 0, 0, 0, 0, 0, 1,	/*  8 - 15 */ 	\
    1, 1, 1, 1, 1 }		/* 16 - 20 */

/* XXX - MDL and MDH set as fixed for now - this is until I can get the
   mul patterns working.  */

/* Like `FIXED_REGISTERS' but has 1 for each register that is clobbered (in
   general) by function calls as well as for fixed registers.  This macro
   therefore identifies the registers that are not available for general
   allocation of values that must live across function calls.

   If a register has 0 in `CALL_USED_REGISTERS', the compiler automatically
   saves it on function entry and restores it on function exit, if the register
   is used within the function.  */
#define CALL_USED_REGISTERS 			\
  { 1, 1, 1, 1, 1, 1, 1, 1,	/*  0 -  7 */ 	\
    0, 0, 0, 0, 1, 1, 0, 1,	/*  8 - 15 */ 	\
    1, 1, 1, 1, 1 }		/* 16 - 20 */

/* A C initializer containing the assembler's names for the machine registers,
   each one as a C string constant.  This is what translates register numbers
   in the compiler into assembler language.  */
#define REGISTER_NAMES 						\
{   "r0", "r1", "r2",  "r3",  "r4",  "r5", "r6", "r7",	\
    "r8", "r9", "r10", "r11", "r12", "ac", "fp", "sp",	\
    "cc", "rp", "mdh", "mdl", "ap"			\
}

/* If defined, a C initializer for an array of structures containing a name and
   a register number.  This macro defines additional names for hard registers,
   thus allowing the `asm' option in declarations to refer to registers using
   alternate names.  */
#define ADDITIONAL_REGISTER_NAMES 				\
{								\
  {"r13", 13}, {"r14", 14}, {"r15", 15}, {"usp", 15}, {"ps", 16}\
}

/*}}}*/ 
/*{{{  How Values Fit in Registers.  */ 

/* A C expression for the number of consecutive hard registers, starting at
   register number REGNO, required to hold a value of mode MODE.  */

#define HARD_REGNO_NREGS(REGNO, MODE) 			\
  ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

/* A C expression that is nonzero if it is permissible to store a value of mode
   MODE in hard register number REGNO (or in several registers starting with
   that one).  */

#define HARD_REGNO_MODE_OK(REGNO, MODE) 1

/* A C expression that is nonzero if it is desirable to choose register
   allocation so as to avoid move instructions between a value of mode MODE1
   and a value of mode MODE2.

   If `HARD_REGNO_MODE_OK (R, MODE1)' and `HARD_REGNO_MODE_OK (R, MODE2)' are
   ever different for any R, then `MODES_TIEABLE_P (MODE1, MODE2)' must be
   zero.  */
#define MODES_TIEABLE_P(MODE1, MODE2) 1

/*}}}*/ 
/*{{{  Register Classes.  */ 

/* An enumeral type that must be defined with all the register class names as
   enumeral values.  `NO_REGS' must be first.  `ALL_REGS' must be the last
   register class, followed by one more enumeral value, `LIM_REG_CLASSES',
   which is not a register class but rather tells how many classes there are.

   Each register class has a number, which is the value of casting the class
   name to type `int'.  The number serves as an index in many of the tables
   described below.  */
enum reg_class
{
  NO_REGS,
  MULTIPLY_32_REG,	/* the MDL register as used by the MULH, MULUH insns */
  MULTIPLY_64_REG,	/* the MDH,MDL register pair as used by MUL and MULU */
  LOW_REGS,		/* registers 0 through 7 */
  HIGH_REGS,		/* registers 8 through 15 */
  REAL_REGS,		/* i.e. all the general hardware registers on the FR30 */
  ALL_REGS,
  LIM_REG_CLASSES
};

#define GENERAL_REGS 	REAL_REGS
#define N_REG_CLASSES 	((int) LIM_REG_CLASSES)

/* An initializer containing the names of the register classes as C string
   constants.  These names are used in writing some of the debugging dumps.  */
#define REG_CLASS_NAMES \
{			\
  "NO_REGS",		\
  "MULTIPLY_32_REG",	\
  "MULTIPLY_64_REG",	\
  "LOW_REGS", 		\
  "HIGH_REGS", 		\
  "REAL_REGS",		\
  "ALL_REGS"		\
 }

/* An initializer containing the contents of the register classes, as integers
   which are bit masks.  The Nth integer specifies the contents of class N.
   The way the integer MASK is interpreted is that register R is in the class
   if `MASK & (1 << R)' is 1.

   When the machine has more than 32 registers, an integer does not suffice.
   Then the integers are replaced by sub-initializers, braced groupings
   containing several integers.  Each sub-initializer must be suitable as an
   initializer for the type `HARD_REG_SET' which is defined in
   `hard-reg-set.h'.  */
#define REG_CLASS_CONTENTS 				\
{ 							\
  { 0 },						\
  { 1 << MD_LOW_REGNUM },				\
  { (1 << MD_LOW_REGNUM) | (1 << MD_HIGH_REGNUM) },	\
  { (1 << 8) - 1 },					\
  { ((1 << 8) - 1) << 8 },				\
  { (1 << CONDITION_CODE_REGNUM) - 1 },			\
  { (1 << FIRST_PSEUDO_REGISTER) - 1 }			\
}

/* A C expression whose value is a register class containing hard register
   REGNO.  In general there is more than one such class; choose a class which
   is "minimal", meaning that no smaller class also contains the register.  */
#define REGNO_REG_CLASS(REGNO) 			\
  ( (REGNO) < 8 ? LOW_REGS			\
  : (REGNO) < CONDITION_CODE_REGNUM ? HIGH_REGS	\
  : (REGNO) == MD_LOW_REGNUM ? MULTIPLY_32_REG	\
  : (REGNO) == MD_HIGH_REGNUM ? MULTIPLY_64_REG	\
  : ALL_REGS)

/* A macro whose definition is the name of the class to which a valid base
   register must belong.  A base register is one used in an address which is
   the register value plus a displacement.  */
#define BASE_REG_CLASS 	REAL_REGS

/* A macro whose definition is the name of the class to which a valid index
   register must belong.  An index register is one used in an address where its
   value is either multiplied by a scale factor or added to another register
   (as well as added to a displacement).  */
#define INDEX_REG_CLASS REAL_REGS

/* A C expression which is nonzero if register number NUM is suitable for use
   as a base register in operand addresses.  It may be either a suitable hard
   register or a pseudo register that has been allocated such a hard register.  */
#define REGNO_OK_FOR_BASE_P(NUM) 1

/* A C expression which is nonzero if register number NUM is suitable for use
   as an index register in operand addresses.  It may be either a suitable hard
   register or a pseudo register that has been allocated such a hard register.

   The difference between an index register and a base register is that the
   index register may be scaled.  If an address involves the sum of two
   registers, neither one of them scaled, then either one may be labeled the
   "base" and the other the "index"; but whichever labeling is used must fit
   the machine's constraints of which registers may serve in each capacity.
   The compiler will try both labelings, looking for one that is valid, and
   will reload one or both registers only if neither labeling works.  */
#define REGNO_OK_FOR_INDEX_P(NUM) 1

/* A C expression for the maximum number of consecutive registers of
   class CLASS needed to hold a value of mode MODE.

   This is closely related to the macro `HARD_REGNO_NREGS'.  In fact, the value
   of the macro `CLASS_MAX_NREGS (CLASS, MODE)' should be the maximum value of
   `HARD_REGNO_NREGS (REGNO, MODE)' for all REGNO values in the class CLASS.

   This macro helps control the handling of multiple-word values in
   the reload pass.  */
#define CLASS_MAX_NREGS(CLASS, MODE) HARD_REGNO_NREGS (0, MODE)

/*}}}*/ 
/*{{{  Basic Stack Layout.  */ 

/* Define this macro if pushing a word onto the stack moves the stack pointer
   to a smaller address.  */
#define STACK_GROWS_DOWNWARD 1

/* Define this to macro nonzero if the addresses of local variable slots
   are at negative offsets from the frame pointer.  */
#define FRAME_GROWS_DOWNWARD 1

/* Offset from the frame pointer to the first local variable slot to be
   allocated.

   If `FRAME_GROWS_DOWNWARD', find the next slot's offset by subtracting the
   first slot's length from `STARTING_FRAME_OFFSET'.  Otherwise, it is found by
   adding the length of the first slot to the value `STARTING_FRAME_OFFSET'.  */
/* #define STARTING_FRAME_OFFSET -4 */
#define STARTING_FRAME_OFFSET 0

/* Offset from the stack pointer register to the first location at which
   outgoing arguments are placed.  If not specified, the default value of zero
   is used.  This is the proper value for most machines.

   If `ARGS_GROW_DOWNWARD', this is the offset to the location above the first
   location at which outgoing arguments are placed.  */
#define STACK_POINTER_OFFSET 0

/* Offset from the argument pointer register to the first argument's address.
   On some machines it may depend on the data type of the function.

   If `ARGS_GROW_DOWNWARD', this is the offset to the location above the first
   argument's address.  */
#define FIRST_PARM_OFFSET(FUNDECL) 0

/* A C expression whose value is RTL representing the location of the incoming
   return address at the beginning of any function, before the prologue.  This
   RTL is either a `REG', indicating that the return value is saved in `REG',
   or a `MEM' representing a location in the stack.

   You only need to define this macro if you want to support call frame
   debugging information like that provided by DWARF 2.  */
#define INCOMING_RETURN_ADDR_RTX gen_rtx_REG (SImode, RETURN_POINTER_REGNUM)

/*}}}*/ 
/*{{{  Register That Address the Stack Frame.  */ 

/* The register number of the arg pointer register, which is used to access the
   function's argument list.  On some machines, this is the same as the frame
   pointer register.  On some machines, the hardware determines which register
   this is.  On other machines, you can choose any register you wish for this
   purpose.  If this is not the same register as the frame pointer register,
   then you must mark it as a fixed register according to `FIXED_REGISTERS', or
   arrange to be able to eliminate it.  */
#define ARG_POINTER_REGNUM 20

/*}}}*/ 
/*{{{  Eliminating the Frame Pointer and the Arg Pointer.  */ 

/* If defined, this macro specifies a table of register pairs used to eliminate
   unneeded registers that point into the stack frame.  If it is not defined,
   the only elimination attempted by the compiler is to replace references to
   the frame pointer with references to the stack pointer.

   The definition of this macro is a list of structure initializations, each of
   which specifies an original and replacement register.

   On some machines, the position of the argument pointer is not known until
   the compilation is completed.  In such a case, a separate hard register must
   be used for the argument pointer.  This register can be eliminated by
   replacing it with either the frame pointer or the argument pointer,
   depending on whether or not the frame pointer has been eliminated.

   In this case, you might specify:
        #define ELIMINABLE_REGS  \
        {{ARG_POINTER_REGNUM, STACK_POINTER_REGNUM}, \
         {ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM}, \
         {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}

   Note that the elimination of the argument pointer with the stack pointer is
   specified first since that is the preferred elimination.  */

#define ELIMINABLE_REGS				\
{						\
  {ARG_POINTER_REGNUM,	 STACK_POINTER_REGNUM},	\
  {ARG_POINTER_REGNUM,	 FRAME_POINTER_REGNUM},	\
  {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}	\
}

/* This macro returns the initial difference between the specified pair
   of registers.  */
#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET)			\
     (OFFSET) = fr30_compute_frame_size (FROM, TO)

/*}}}*/ 
/*{{{  Passing Function Arguments on the Stack.  */ 

/* If defined, the maximum amount of space required for outgoing arguments will
   be computed and placed into the variable
   `crtl->outgoing_args_size'.  No space will be pushed onto the
   stack for each call; instead, the function prologue should increase the
   stack frame size by this amount.

   Defining both `PUSH_ROUNDING' and `ACCUMULATE_OUTGOING_ARGS' is not
   proper.  */
#define ACCUMULATE_OUTGOING_ARGS 1

/*}}}*/ 
/*{{{  Function Arguments in Registers.  */ 

/* The number of register assigned to holding function arguments.  */
     
#define FR30_NUM_ARG_REGS	 4

/* A C type for declaring a variable that is used as the first argument of
   `FUNCTION_ARG' and other related values.  For some target machines, the type
   `int' suffices and can hold the number of bytes of argument so far.

   There is no need to record in `CUMULATIVE_ARGS' anything about the arguments
   that have been passed on the stack.  The compiler has other variables to
   keep track of that.  For target machines on which all arguments are passed
   on the stack, there is no need to store anything in `CUMULATIVE_ARGS';
   however, the data structure must exist and should not be empty, so use
   `int'.  */
/* On the FR30 this value is an accumulating count of the number of argument
   registers that have been filled with argument values, as opposed to say,
   the number of bytes of argument accumulated so far.  */
#define CUMULATIVE_ARGS int

/* A C statement (sans semicolon) for initializing the variable CUM for the
   state at the beginning of the argument list.  The variable has type
   `CUMULATIVE_ARGS'.  The value of FNTYPE is the tree node for the data type
   of the function which will receive the args, or 0 if the args are to a
   compiler support library function.  The value of INDIRECT is nonzero when
   processing an indirect call, for example a call through a function pointer.
   The value of INDIRECT is zero for a call to an explicitly named function, a
   library function call, or when `INIT_CUMULATIVE_ARGS' is used to find
   arguments for the function being compiled.

   When processing a call to a compiler support library function, LIBNAME
   identifies which one.  It is a `symbol_ref' rtx which contains the name of
   the function, as a string.  LIBNAME is 0 when an ordinary C function call is
   being processed.  Thus, each time this macro is called, either LIBNAME or
   FNTYPE is nonzero, but never both of them at once.  */
#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS) \
  (CUM) = 0

/* A C expression that is nonzero if REGNO is the number of a hard register in
   which function arguments are sometimes passed.  This does *not* include
   implicit arguments such as the static chain and the structure-value address.
   On many machines, no registers can be used for this purpose since all
   function arguments are pushed on the stack.  */
#define FUNCTION_ARG_REGNO_P(REGNO) \
  ((REGNO) >= FIRST_ARG_REGNUM && ((REGNO) < FIRST_ARG_REGNUM + FR30_NUM_ARG_REGS))

/*}}}*/ 
/*{{{  How Large Values are Returned.  */ 

/* Define this macro to be 1 if all structure and union return values must be
   in memory.  Since this results in slower code, this should be defined only
   if needed for compatibility with other compilers or with an ABI.  If you
   define this macro to be 0, then the conventions used for structure and union
   return values are decided by the `TARGET_RETURN_IN_MEMORY' macro.

   If not defined, this defaults to the value 1.  */
#define DEFAULT_PCC_STRUCT_RETURN 1

/*}}}*/ 
/*{{{  Generating Code for Profiling.  */ 

/* A C statement or compound statement to output to FILE some assembler code to
   call the profiling subroutine `mcount'.  Before calling, the assembler code
   must load the address of a counter variable into a register where `mcount'
   expects to find the address.  The name of this variable is `LP' followed by
   the number LABELNO, so you would generate the name using `LP%d' in a
   `fprintf'.

   The details of how the address should be passed to `mcount' are determined
   by your operating system environment, not by GCC.  To figure them out,
   compile a small program for profiling using the system's installed C
   compiler and look at the assembler code that results.  */
#define FUNCTION_PROFILER(FILE, LABELNO)	\
{						\
  fprintf (FILE, "\t mov rp, r1\n" );		\
  fprintf (FILE, "\t ldi:32 mcount, r0\n" );	\
  fprintf (FILE, "\t call @r0\n" );		\
  fprintf (FILE, ".word\tLP%d\n", LABELNO);	\
}

/*}}}*/ 
/*{{{  Trampolines for Nested Functions.  */ 

/* A C expression for the size in bytes of the trampoline, as an integer.  */
#define TRAMPOLINE_SIZE 18

/* We want the trampoline to be aligned on a 32bit boundary so that we can
   make sure the location of the static chain & target function within
   the trampoline is also aligned on a 32bit boundary.  */
#define TRAMPOLINE_ALIGNMENT 32

/*}}}*/ 
/*{{{  Addressing Modes.  */ 

/* A number, the maximum number of registers that can appear in a valid memory
   address.  Note that it is up to you to specify a value equal to the maximum
   number that `GO_IF_LEGITIMATE_ADDRESS' would ever accept.  */
#define MAX_REGS_PER_ADDRESS 1

/* A C compound statement with a conditional `goto LABEL;' executed if X (an
   RTX) is a legitimate memory address on the target machine for a memory
   operand of mode MODE.  */

/* On the FR30 we only have one real addressing mode - an address in a
   register.  There are three special cases however:
   
   * indexed addressing using small positive offsets from the stack pointer
   
   * indexed addressing using small signed offsets from the frame pointer

   * register plus register addressing using R13 as the base register.

   At the moment we only support the first two of these special cases.  */
   
#ifdef REG_OK_STRICT
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)			\
  do									\
    {									\
      if (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X))			\
        goto LABEL;							\
      if (GET_CODE (X) == PLUS						\
	  && ((MODE) == SImode || (MODE) == SFmode)			\
	  && GET_CODE (XEXP (X, 0)) == REG				\
          && REGNO (XEXP (X, 0)) == STACK_POINTER_REGNUM		\
	  && GET_CODE (XEXP (X, 1)) == CONST_INT			\
	  && IN_RANGE (INTVAL (XEXP (X, 1)), 0, (1 <<  6) - 4))		\
	goto LABEL;							\
      if (GET_CODE (X) == PLUS						\
	  && ((MODE) == SImode || (MODE) == SFmode)			\
	  && GET_CODE (XEXP (X, 0)) == REG				\
          && REGNO (XEXP (X, 0)) == FRAME_POINTER_REGNUM		\
	  && GET_CODE (XEXP (X, 1)) == CONST_INT			\
	  && IN_RANGE (INTVAL (XEXP (X, 1)), -(1 << 9), (1 <<  9) - 4))	\
        goto LABEL;							\
    }									\
  while (0)
#else
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)			\
  do									\
    {									\
      if (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X))			\
        goto LABEL;							\
      if (GET_CODE (X) == PLUS						\
	  && ((MODE) == SImode || (MODE) == SFmode)			\
	  && GET_CODE (XEXP (X, 0)) == REG				\
          && REGNO (XEXP (X, 0)) == STACK_POINTER_REGNUM		\
	  && GET_CODE (XEXP (X, 1)) == CONST_INT			\
	  && IN_RANGE (INTVAL (XEXP (X, 1)), 0, (1 <<  6) - 4))		\
	goto LABEL;							\
      if (GET_CODE (X) == PLUS						\
	  && ((MODE) == SImode || (MODE) == SFmode)			\
	  && GET_CODE (XEXP (X, 0)) == REG				\
          && (REGNO (XEXP (X, 0)) == FRAME_POINTER_REGNUM		\
	      || REGNO (XEXP (X, 0)) == ARG_POINTER_REGNUM)		\
	  && GET_CODE (XEXP (X, 1)) == CONST_INT			\
	  && IN_RANGE (INTVAL (XEXP (X, 1)), -(1 << 9), (1 <<  9) - 4))	\
        goto LABEL;							\
    }									\
  while (0)
#endif

/* A C expression that is nonzero if X (assumed to be a `reg' RTX) is valid for
   use as a base register.  For hard registers, it should always accept those
   which the hardware permits and reject the others.  Whether the macro accepts
   or rejects pseudo registers must be controlled by `REG_OK_STRICT' as
   described above.  This usually requires two variant definitions, of which
   `REG_OK_STRICT' controls the one actually used.  */
#ifdef REG_OK_STRICT
#define REG_OK_FOR_BASE_P(X) (((unsigned) REGNO (X)) <= STACK_POINTER_REGNUM)
#else
#define REG_OK_FOR_BASE_P(X) 1
#endif

/* A C expression that is nonzero if X (assumed to be a `reg' RTX) is valid for
   use as an index register.

   The difference between an index register and a base register is that the
   index register may be scaled.  If an address involves the sum of two
   registers, neither one of them scaled, then either one may be labeled the
   "base" and the other the "index"; but whichever labeling is used must fit
   the machine's constraints of which registers may serve in each capacity.
   The compiler will try both labelings, looking for one that is valid, and
   will reload one or both registers only if neither labeling works.  */
#define REG_OK_FOR_INDEX_P(X) REG_OK_FOR_BASE_P (X)

/*}}}*/ 
/*{{{  Describing Relative Costs of Operations */ 

/* Define this macro as a C expression which is nonzero if accessing less than
   a word of memory (i.e. a `char' or a `short') is no faster than accessing a
   word of memory, i.e., if such access require more than one instruction or if
   there is no difference in cost between byte and (aligned) word loads.

   When this macro is not defined, the compiler will access a field by finding
   the smallest containing object; when it is defined, a fullword load will be
   used if alignment permits.  Unless bytes accesses are faster than word
   accesses, using word accesses is preferable since it may eliminate
   subsequent memory access if subsequent accesses occur to other fields in the
   same word of the structure, but to different bytes.  */
#define SLOW_BYTE_ACCESS 1

/*}}}*/ 
/*{{{  Dividing the output into sections.  */ 

/* A C expression whose value is a string containing the assembler operation
   that should precede instructions and read-only data.  Normally `".text"' is
   right.  */
#define TEXT_SECTION_ASM_OP "\t.text"

/* A C expression whose value is a string containing the assembler operation to
   identify the following data as writable initialized data.  Normally
   `".data"' is right.  */
#define DATA_SECTION_ASM_OP "\t.data"

#define BSS_SECTION_ASM_OP "\t.section .bss"

/*}}}*/ 
/*{{{  The Overall Framework of an Assembler File.  */

/* A C string constant describing how to begin a comment in the target
   assembler language.  The compiler assumes that the comment will end at the
   end of the line.  */
#define ASM_COMMENT_START ";"

/* A C string constant for text to be output before each `asm' statement or
   group of consecutive ones.  Normally this is `"#APP"', which is a comment
   that has no effect on most assemblers but tells the GNU assembler that it
   must check the lines that follow for all valid assembler constructs.  */
#define ASM_APP_ON "#APP\n"

/* A C string constant for text to be output after each `asm' statement or
   group of consecutive ones.  Normally this is `"#NO_APP"', which tells the
   GNU assembler to resume making the time-saving assumptions that are valid
   for ordinary compiler output.  */
#define ASM_APP_OFF "#NO_APP\n"

/*}}}*/ 
/*{{{  Output and Generation of Labels.  */ 

/* Globalizing directive for a label.  */
#define GLOBAL_ASM_OP "\t.globl "

/*}}}*/ 
/*{{{  Output of Assembler Instructions.  */ 

/* A C compound statement to output to stdio stream STREAM the assembler syntax
   for an instruction operand X.  X is an RTL expression.

   CODE is a value that can be used to specify one of several ways of printing
   the operand.  It is used when identical operands must be printed differently
   depending on the context.  CODE comes from the `%' specification that was
   used to request printing of the operand.  If the specification was just
   `%DIGIT' then CODE is 0; if the specification was `%LTR DIGIT' then CODE is
   the ASCII code for LTR.

   If X is a register, this macro should print the register's name.  The names
   can be found in an array `reg_names' whose type is `char *[]'.  `reg_names'
   is initialized from `REGISTER_NAMES'.

   When the machine description has a specification `%PUNCT' (a `%' followed by
   a punctuation character), this macro is called with a null pointer for X and
   the punctuation character for CODE.  */
#define PRINT_OPERAND(STREAM, X, CODE)	fr30_print_operand (STREAM, X, CODE)

/* A C expression which evaluates to true if CODE is a valid punctuation
   character for use in the `PRINT_OPERAND' macro.  If
   `PRINT_OPERAND_PUNCT_VALID_P' is not defined, it means that no punctuation
   characters (except for the standard one, `%') are used in this way.  */
#define PRINT_OPERAND_PUNCT_VALID_P(CODE) (CODE == '#')

/* A C compound statement to output to stdio stream STREAM the assembler syntax
   for an instruction operand that is a memory reference whose address is X.  X
   is an RTL expression.  */

#define PRINT_OPERAND_ADDRESS(STREAM, X) fr30_print_operand_address (STREAM, X)

#define REGISTER_PREFIX "%"
#define LOCAL_LABEL_PREFIX "."
#define USER_LABEL_PREFIX ""
#define IMMEDIATE_PREFIX ""

/*}}}*/ 
/*{{{  Output of Dispatch Tables.  */ 

/* This macro should be provided on machines where the addresses in a dispatch
   table are relative to the table's own address.

   The definition should be a C statement to output to the stdio stream STREAM
   an assembler pseudo-instruction to generate a difference between two labels.
   VALUE and REL are the numbers of two internal labels.  The definitions of
   these labels are output using `(*targetm.asm_out.internal_label)', and they must be
   printed in the same way here.  For example,

        fprintf (STREAM, "\t.word L%d-L%d\n", VALUE, REL)  */
#define ASM_OUTPUT_ADDR_DIFF_ELT(STREAM, BODY, VALUE, REL) \
fprintf (STREAM, "\t.word .L%d-.L%d\n", VALUE, REL)

/* This macro should be provided on machines where the addresses in a dispatch
   table are absolute.

   The definition should be a C statement to output to the stdio stream STREAM
   an assembler pseudo-instruction to generate a reference to a label.  VALUE
   is the number of an internal label whose definition is output using
   `(*targetm.asm_out.internal_label)'.  For example,

        fprintf (STREAM, "\t.word L%d\n", VALUE)  */
#define ASM_OUTPUT_ADDR_VEC_ELT(STREAM, VALUE) \
fprintf (STREAM, "\t.word .L%d\n", VALUE)

/*}}}*/ 
/*{{{  Assembler Commands for Alignment.  */ 

/* A C statement to output to the stdio stream STREAM an assembler command to
   advance the location counter to a multiple of 2 to the POWER bytes.  POWER
   will be a C expression of type `int'.  */
#define ASM_OUTPUT_ALIGN(STREAM, POWER) \
  fprintf ((STREAM), "\t.p2align %d\n", (POWER))

/*}}}*/ 
/*{{{  Miscellaneous Parameters.  */ 

/* An alias for a machine mode name.  This is the machine mode that elements of
   a jump-table should have.  */
#define CASE_VECTOR_MODE SImode

/* The maximum number of bytes that a single instruction can move quickly from
   memory to memory.  */
#define MOVE_MAX 8

/* A C expression which is nonzero if on this machine it is safe to "convert"
   an integer of INPREC bits to one of OUTPREC bits (where OUTPREC is smaller
   than INPREC) by merely operating on it as if it had only OUTPREC bits.

   On many machines, this expression can be 1.

   When `TRULY_NOOP_TRUNCATION' returns 1 for a pair of sizes for modes for
   which `MODES_TIEABLE_P' is 0, suboptimal code can result.  If this is the
   case, making `TRULY_NOOP_TRUNCATION' return 0 in such cases may improve
   things.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1

/* An alias for the machine mode for pointers.  On most machines, define this
   to be the integer mode corresponding to the width of a hardware pointer;
   `SImode' on 32-bit machine or `DImode' on 64-bit machines.  On some machines
   you must define this to be one of the partial integer modes, such as
   `PSImode'.

   The width of `Pmode' must be at least as large as the value of
   `POINTER_SIZE'.  If it is not equal, you must define the macro
   `POINTERS_EXTEND_UNSIGNED' to specify how pointers are extended to `Pmode'.  */
#define Pmode SImode

/* An alias for the machine mode used for memory references to functions being
   called, in `call' RTL expressions.  On most machines this should be
   `QImode'.  */
#define FUNCTION_MODE QImode

/*}}}*/ 

/* Local Variables: */
/* folded-file: t   */
/* End:		    */
