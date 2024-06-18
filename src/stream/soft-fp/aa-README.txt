https://gcc.gnu.org/onlinedocs/gccint/Soft-float-library-routines.html

1.Arithmetic functions

Runtime Function: float __addsf3 (float a, float b)
Runtime Function: double __adddf3 (double a, double b)
    These functions return the sum of a and b.

Runtime Function: float __subsf3 (float a, float b)
Runtime Function: double __subdf3 (double a, double b)
    These functions return the difference between b and a; that is, a - b.

Runtime Function: float __mulsf3 (float a, float b)
Runtime Function: double __muldf3 (double a, double b)
    These functions return the product of a and b.

Runtime Function: float __divsf3 (float a, float b)
Runtime Function: double __divdf3 (double a, double b)
    These functions return the quotient of a and b; that is, a / b.

Runtime Function: float __negsf2 (float a)
Runtime Function: double __negdf2 (double a)
    These functions return the negation of a. They simply flip the sign bit, so they can produce negative zero and negative NaN.

2.Conversion functions

Runtime Function: double __extendsfdf2 (float a)
    These functions extend a to the wider mode of their return type.

Runtime Function: float __truncdfsf2 (double a)
    These functions truncate a to the narrower mode of their return type, rounding toward zero.

Runtime Function: int __fixsfsi (float a)
Runtime Function: int __fixdfsi (double a)
    These functions convert a to a signed integer, rounding toward zero.

Runtime Function: long __fixsfdi (float a)
Runtime Function: long __fixdfdi (double a)
    These functions convert a to a signed long, rounding toward zero.

Runtime Function: long long __fixsfti (float a)
Runtime Function: long long __fixdfti (double a)
    These functions convert a to a signed long long, rounding toward zero.


Runtime Function: unsigned int __fixunssfsi (float a)
Runtime Function: unsigned int __fixunsdfsi (double a)
    These functions convert a to an unsigned integer, rounding toward zero. Negative values all become zero.

Runtime Function: unsigned long __fixunssfdi (float a)
Runtime Function: unsigned long __fixunsdfdi (double a)
    These functions convert a to an unsigned long, rounding toward zero. Negative values all become zero.

Runtime Function: unsigned long long __fixunssfti (float a)
Runtime Function: unsigned long long __fixunsdfti (double a)
    These functions convert a to an unsigned long long, rounding toward zero. Negative values all become zero.


Runtime Function: float __floatsisf (int i)
Runtime Function: double __floatsidf (int i)
    These functions convert i, a signed integer, to floating point.

Runtime Function: float __floatdisf (long i) ¶
Runtime Function: double __floatdidf (long i)
    These functions convert i, a signed long, to floating point.


Runtime Function: float __floatunsisf (unsigned int i)
Runtime Function: double __floatunsidf (unsigned int i)
    These functions convert i, an unsigned integer, to floating point.

Runtime Function: float __floatundisf (unsigned long i)
Runtime Function: double __floatundidf (unsigned long i)
    These functions convert i, an unsigned long, to floating point.

3.Comparison functions
