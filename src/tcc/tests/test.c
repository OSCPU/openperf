#include "trap.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef uint32_t size_t;
#define NULL 0
#define LENGTH(x) sizeof(x)/sizeof(x[0])

void *memset(void *s, int c, size_t n) {
  char* p = NULL;
  if(s == NULL)
    return s;
  
  p = (char *)s;
  while(n > 0)
  {
    *(p++) = c;
    n--;
  }
  return s;
}

// ***************************************  *************************************** //
int add(int a, int b) {
	int c = a + b;
	return c;
}

int add_test_data[] = {0, 1, 2, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff};
int add_ans[] = {0, 0x1, 0x2, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x1, 0x2, 0x3, 0x80000000, 0x80000001, 0x80000002, 0xffffffff, 0, 0x2, 0x3, 0x4, 0x80000001, 0x80000002, 0x80000003, 0, 0x1, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x7ffffffd, 0x7ffffffe, 0x80000000, 0x80000001, 0x80000002, 0xffffffff, 0, 0x1, 0x7ffffffe, 0x7fffffff, 0x80000001, 0x80000002, 0x80000003, 0, 0x1, 0x2, 0x7fffffff, 0x80000000, 0xfffffffe, 0xffffffff, 0, 0x7ffffffd, 0x7ffffffe, 0x7fffffff, 0xfffffffc, 0xfffffffd, 0xffffffff, 0, 0x1, 0x7ffffffe, 0x7fffffff, 0x80000000, 0xfffffffd, 0xfffffffe};

#define add_NR_DATA 8

int add_main() {
	int i, j, ans_idx = 0;
	for(i = 0; i < add_NR_DATA; i ++) {
		for(j = 0; j < add_NR_DATA; j ++) {
			check(add(add_test_data[i], add_test_data[j]) == add_ans[ans_idx ++]);
		}
		check(j == add_NR_DATA);
	}

	check(i == add_NR_DATA);

	return 0;
}
// ***************************************  *************************************** //
int is_leap_year(int n) {
	return (n % 4 == 0 && n % 100 != 0) || (n % 400 == 0);
}

int leap_year_ans[] = {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0};

int leap_year_main() {
	int i;
	for(i = 0; i < 125; i ++) {
		check(is_leap_year(i + 1890) == leap_year_ans[i]);
	}

	return 0;
}
// ***************************************  *************************************** //
#define bubble_sort_N 20

int bubble_sort_a[bubble_sort_N] = {2, 12, 14, 6, 13, 15, 16, 10, 0, 18, 11, 19, 9, 1, 7, 5, 4, 3, 8, 17};

void bubble_sort() {
	int i, j, t;
	for(j = 0; j < bubble_sort_N; j ++) {
		for(i = 0; i < bubble_sort_N - 1 - j; i ++) {
			if(bubble_sort_a[i] > bubble_sort_a[i + 1]) {
				t = bubble_sort_a[i];
				bubble_sort_a[i] = bubble_sort_a[i + 1];
				bubble_sort_a[i + 1] = t;
			}
		}
	}
}

int bubble_sort_main() {
	bubble_sort();

	int i;
	for(i = 0; i < bubble_sort_N; i ++) {
		check(bubble_sort_a[i] == i);
	}

	check(i == bubble_sort_N);

	bubble_sort();

	for(i = 0; i < bubble_sort_N; i ++) {
		check(bubble_sort_a[i] == i);
	}

	check(i == bubble_sort_N);

	return 0;
}
// ***************************************  *************************************** //
/* from http://rosettacode.org/wiki/CRC-32#C */

char STR[] ="The quick brown fox jumps over the lazy dog";
#define STRLEN (43)
 
uint32_t rc_crc32(uint32_t crc, const char *buf, size_t len) {
	static uint32_t table[256];
	static int have_table = 0;
	uint32_t rem;
	uint8_t octet;
	int i, j;
	const char *p, *q;
 
	/* This check is not thread safe; there is no mutex. */
	if (have_table == 0) {
		/* Calculate CRC table. */
		for (i = 0; i < 256; i++) {
			rem = i;  /* remainder from polynomial division */
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				} else
					rem >>= 1;
			}
			table[i] = rem;
		}
		have_table = 1;
	}
 
	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;  /* Cast to unsigned octet. */
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
	}
	return ~crc;
}
 
int crc32_main() {
  uint32_t res = rc_crc32(0, STR, STRLEN);
  check(res == 0x414FA339);
	return 0;
}
// ***************************************  *************************************** //
#define div_N 10
int div_a[div_N];

int div_main() {
  int i, j;
  for(i = 0; i < div_N; i ++)
    div_a[i] = i;
  for(i = 0; i < div_N; i ++)
    for(j = 1; j < div_N + 1; j ++)
      div_a[i] *= j;
  for(i = 0; i < div_N; i ++)
    for(j = 1; j < div_N + 1; j ++)
      div_a[i] /= j;

  for(i = 0; i < div_N; i ++)
    check(div_a[i] == i);

  return 0;
}

// ***************************************  *************************************** //
int fact_f[15];
int fact_ans[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

int fact(int n) {
	if(n == 0 || n == 1) return 1;
	else return fact(n - 1) * n;
}

int fact_main() {
	int i;
	for(i = 0; i < 13; i ++) {
		fact_f[i] = fact(i);
		check(fact_f[i] == fact_ans[i]);
	}

	return 0;
}
// ***************************************  *************************************** //
int fib_main() {
	int i;
	int fib[40] = {1, 1};
	int ans[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155};
	for(i = 2; i < 40; i ++) {
		fib[i] = fib[i - 1] + fib[i - 2];
		check(fib[i] == ans[i]);
	}

	check(i == 40);

	return 0;
}
// ***************************************  *************************************** //
int is_prime(int n) {
	if(n < 2) return 0;

	int i;
	for(i = 2; i < n; i ++) {
		if(n % i == 0) {
			return 0;
		}
	}

	return 1;
}

int goldbach(int n) {
	int i;
	for(i = 2; i < n; i ++) {
		if(is_prime(i) && is_prime(n - i)) {
			return 1;
		}
	}

	return 0;
}

int goldbach_main() {
	int n;
	for(n = 4; n <= 30; n += 2) {
		check(goldbach(n) == 1);
	}

	return 0;
}

// ***************************************  *************************************** //
int if_else(int n) {
	int cost;
	if(n > 500) cost = 150;
	else if(n > 300) cost = 100;
	else if(n > 100) cost = 75;
	else if(n > 50) cost = 50;
	else cost = 0;

	return cost;
}

int if_else_test_data[] = {-1, 0, 49, 50, 51, 99, 100, 101, 299, 300, 301, 499, 500, 501};
int if_else_ans[] = {0, 0, 0, 0, 50, 50, 50, 75, 75, 75, 100, 100, 100, 150};

#define if_else_NR_DATA 14

int if_else_main() {
	int i, ans_idx = 0;
	for(i = 0; i < if_else_NR_DATA; i ++) {
		check(if_else(if_else_test_data[i]) == if_else_ans[ans_idx ++]);
	}

	check(i == if_else_NR_DATA);

	return 0;
}

// ***************************************  *************************************** //
unsigned short mem[] = {
	0x0, 0x0258, 0x4abc, 0x7fff, 0x8000, 0x8100, 0xabcd, 0xffff
};

unsigned lh_ans[] = {
	0x00000000, 0x00000258, 0x00004abc, 0x00007fff, 0xffff8000, 0xffff8100, 0xffffabcd, 0xffffffff
};

unsigned lhu_ans[] = {
	0x00000000, 0x00000258, 0x00004abc, 0x00007fff, 0x00008000, 0x00008100, 0x0000abcd, 0x0000ffff
};

unsigned  sh_ans[] = {
	0x0000fffd, 0x0000fff7, 0x0000ffdf, 0x0000ff7f, 0x0000fdff, 0x0000f7ff, 0x0000dfff, 0x00007fff
};

unsigned  lwlr_ans[] = {
	0xbc025800, 0x7fff4a, 0xcd810080, 0xffffab
};

int load_store_main() {
	unsigned i;

	for(i = 0; i < LENGTH(mem); i ++) {
		check((short)mem[i] == lh_ans[i]);
	}

	for(i = 0; i < LENGTH(mem); i ++) {
		check(mem[i] == lhu_ans[i]);
	}

	for(i = 0; i < ((LENGTH(mem) / 2) - 1); i ++) {
		unsigned x = ((unsigned*)((void*)mem + 1))[i];
		check(x == lwlr_ans[i]);
	}

	for(i = 0; i < LENGTH(mem); i ++) {
		mem[i] = ~(1 << (2 * i + 1));
		check(mem[i] == sh_ans[i]);
	}

	return 0;
}
// ***************************************  *************************************** //
#define matrix_mul_N 10
int matrix_mul_a[matrix_mul_N][matrix_mul_N] = {
{31, -73, -67, -28, 87, -17, -15, -35, -53, -54},
{52, 36, 9, -91, -27, -78, 42, 82, 19, -6},
{41, -56, 31, 32, -52, 74, 28, 20, 55, -72},
{-59, 2, -79, -8, 44, 55, -83, -95, -45, 50},
{-95, 61, -63, 62, -16, 52, 40, 92, -32, -26},
{-99, 52, 96, 63, -75, -74, -82, 82, -95, 42},
{11, -22, 27, -27, -27, -76, -71, 58, -40, -65},
{91, -53, -67, 72, 36, -77, -3, 93, -24, 97},
{-52, -11, -77, -93, -92, -24, 70, 18, 56, 88},
{-43, -41, -26, 11, -84, -14, -41, 83, 27, -11}
};
int matrix_mul_b[matrix_mul_N][matrix_mul_N] = {
	{-48, -70, -40, -82, -74, -63, -59, -72, -100, -72},
{5, -84, 28, 56, 60, -33, -42, -50, -83, -83},
{-5, 5, 48, 75, -78, -9, 9, 2, 88, 70},
{69, 23, 66, 66, -11, 50, 67, 18, -58, 76},
{30, 45, 32, 25, -73, 57, -67, -14, 53, -33},
{98, -86, -63, 80, -45, -88, 80, -64, 58, -84},
{-55, -39, -13, -27, -37, 8, -96, 84, -89, 31},
{-82, 58, 81, -41, -58, 36, 76, -79, -29, 23},
{86, -46, 16, -18, 81, 90, 35, -90, 43, 55},
{-38, -19, -40, 82, -76, 57, -29, -2, 79, -48},
};

int matrix_mul_ans[matrix_mul_N][matrix_mul_N] = {
	{-1317, 10379, -5821, -14322, -4330, -3114, -9940, 7033, -1883, -6027},
	{-24266, -861, 4044, -19824, -223, 886, -11988, -6442, -13846, -1054},
	{9783, -7073, -918, -5911, -967, -7100, 14605, -7556, -3439, 9607},
	{15980, -520, -13297, 15043, 6185, -3654, 1325, 4193, 16925, -17761},
	{2566, 3187, 10248, 7925, 6318, 1421, 14648, 700, -12193, 1083},
	{-12603, 19006, 20952, 18599, -1539, 5184, 17408, 6740, 6264, 15114},
	{-12715, 15121, 9963, -13717, 2411, -2196, 6147, -1698, -3389, 8200},
	{-19007, 12417, 5723, -11309, -19242, 15740, -3791, -3949, -13130, -21},
	{-12557, -5970, -11570, -8905, 12227, 7814, -5094, 4532, 1071, -1309},
	{-2955, 9381, 6372, -6898, 9117, 5753, 20778, -5045, 1047, 12114}};

int matrix_mul_c[matrix_mul_N][matrix_mul_N];

int matrix_mul_main() {
	int i, j, k;
	for(i = 0; i < matrix_mul_N; i ++) {
		for(j = 0; j < matrix_mul_N; j ++) {
			matrix_mul_c[i][j] = 0;
			for(k = 0; k < matrix_mul_N; k ++) {
				matrix_mul_c[i][j] += matrix_mul_a[i][k] * matrix_mul_b[k][j];
			}
			check(matrix_mul_c[i][j] == matrix_mul_ans[i][j]);
			check(k == matrix_mul_N);
		}
		check(j == matrix_mul_N);
	}

	check(i == matrix_mul_N);

	return 0;
}

// ***************************************  *************************************** //
int max(int x, int y) {
	int z;
	if(x > y) { z = x; }
	else { z = y; }
	return z;
}

int max_test_data[] = {0, 1, 2, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff};
int max_ans[] = {0, 0x1, 0x2, 0x7fffffff, 0, 0, 0, 0, 0x1, 0x1, 0x2, 0x7fffffff, 0x1, 0x1, 0x1, 0x1, 0x2, 0x2, 0x2, 0x7fffffff, 0x2, 0x2, 0x2, 0x2, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff, 0, 0x1, 0x2, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x7fffffff, 0x80000001, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x7fffffff, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x7fffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

#define max_NR_DATA LENGTH(max_test_data)

int max_main() {
	int i, j, ans_idx = 0;
	for(i = 0; i < max_NR_DATA; i ++) {
		for(j = 0; j < max_NR_DATA; j ++) {
			check(max(max_test_data[i], max_test_data[j]) == max_ans[ans_idx ++]);
		}
		check(j == max_NR_DATA);
	}

	check(i == max_NR_DATA);

	return 0;
}

// ***************************************  *************************************** //
/* adapted from http://rosettacode.org/wiki/Factors_of_a_Mersenne_number#C */
int isPrime(int n) {
  int d = 5;
  if (n % 2 == 0) return n==2;
  if (n % 3 == 0) return n==3;
  while (d * d <= n) {
    if (n % d == 0) return 0;
    d += 2;
    if (n % d == 0) return 0;
    d += 4;
  }
  return 1;
}

int mersenne_main() {
  int i, d, p, r, q = 929;
  if (!isPrime(q)) return 1; 
  r = q;
  while (r > 0) r <<= 1;
  d = 2 * q + 1;
  do {
    for (p = r, i = 1; p; p <<= 1) {
      i = ((long)i * i) % d;
      if (p < 0) i *= 2;
      if (i > d) i -= d;
    }
    if (i != 1) d += 2 * q;
    else break;
  } while(1);
  check(d == 13007);
  return 0;
}

// ***************************************  *************************************** //
int min3(int x, int y, int z) {
	int m;
	if(x < y) { m = x; }
	else { m = y; }
	if(z < m) m = z;
	return m;
}

int min3_test_data[] = {0, 0x7fffffff, 0x80000000, 0xffffffff};
int min3_ans [] = {0, 0, -2147483648, -1, 0, 0, -2147483648, -1, -2147483648, -2147483648, -2147483648, -2147483648, -1, -1, -2147483648, -1, 0, 0, -2147483648, -1, 0, 2147483647, -2147483648, -1, -2147483648, -2147483648, -2147483648, -2147483648, -1, -1, -2147483648, -1, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -2147483648, -1, -1, -2147483648, -1, -1, -1, -2147483648, -1, -2147483648, -2147483648, -2147483648, -2147483648, -1, -1, -2147483648, -1};

#define min3_NR_DATA LENGTH(min3_test_data)

int min3_main() {
	int i, j, k, ans_idx = 0;
	for(i = 0; i < min3_NR_DATA; i ++) {
		for(j = 0; j < min3_NR_DATA; j ++) {
			for(k = 0; k < min3_NR_DATA; k ++) {
				check(min3(min3_test_data[i], min3_test_data[j], min3_test_data[k]) == min3_ans[ans_idx ++]);
			}
			check(k == min3_NR_DATA);
		}
		check(j == min3_NR_DATA);
	}

	check(i == min3_NR_DATA);

	return 0;
}

// ***************************************  *************************************** //
volatile int mov_c_A[10];
volatile int mov_c_b;

int mov_c_main() {
	mov_c_A[0] = 0;
	mov_c_A[1] = 1;
	mov_c_A[2] = 2;
	mov_c_A[3] = 3;
	mov_c_A[4] = 4;

	mov_c_b = mov_c_A[3];
	mov_c_A[5] = mov_c_b;

	check(mov_c_A[0] == 0);
	check(mov_c_A[1] == 1);
	check(mov_c_A[2] == 2);
	check(mov_c_A[3] == 3);
	check(mov_c_A[4] == 4);
	check(mov_c_b == 3);
	check(mov_c_A[5] == 3);

	return 0;
}
// ***************************************  *************************************** //
volatile int movsx_A[10];
volatile int movsx_b;
volatile signed char movsx_C[10];
int movsx_main() {
	movsx_A[0] = 0;
	movsx_A[1] = 1;
	movsx_A[2] = 2;
	movsx_A[3] = 3;
	movsx_A[4] = 4;

	movsx_b = movsx_A[3];
	movsx_A[5] = movsx_b;
	movsx_C[0] = 'a';
	check(movsx_C[0] == 'a');
	movsx_C[1] = movsx_C[0];
	check(movsx_C[1] == 'a');
	movsx_A[0] = (int)movsx_C[0];
	check(movsx_A[0] == 'a');
	movsx_C[1] = 0x80;
	movsx_A[0] = (int)movsx_C[1];
	check(movsx_A[1] == 1);
	check(movsx_A[2] == 2);
	check(movsx_A[3] == 3);
	check(movsx_A[4] == 4);
	check(movsx_b == 3);
	check(movsx_A[5] == 3);
	check(movsx_C[1] == 0xffffff80);
	check(movsx_A[0] == 0xffffff80);

	return 0;
}

// ***************************************  *************************************** //
#define pascal_N 31

int pascal_a[pascal_N];
int pascal_ans[] = {1, 30, 435, 4060, 27405, 142506, 593775, 2035800, 5852925, 14307150, 30045015, 54627300, 86493225, 119759850, 145422675, 155117520, 145422675, 119759850, 86493225, 54627300, 30045015, 14307150, 5852925, 2035800, 593775, 142506, 27405, 4060, 435, 30, 1};

int pascal_main() {
	int i, j;
	int t0, t1;
	pascal_a[0] = pascal_a[1] = 1;

	for(i = 2; i < pascal_N; i ++) {
		t0 = 1;
		for(j = 1; j < i; j ++) {
			t1 = pascal_a[j];
			pascal_a[j] = t0 + t1;
			t0 = t1;
		}
		pascal_a[i] = 1;
	}

	for(j = 0; j < pascal_N; j ++) {
		check(pascal_a[j] == pascal_ans[j]);
	}

	check(j == pascal_N);

	return 0;
}

// ***************************************  *************************************** //
int prime_ans[] = {101, 103, 107, 109, 113, 127, 131, 137, 139, 149};

int prime_main() {
	int m, i, n = 0;
	int prime;
	for(m = 101; m <= 150; m += 2) {
		prime = 1;
		for(i = 2; i < m; i ++) {
			if(m % i == 0) {
				prime = 0;
				break;
			}
		}
		if(prime) {
			check(i == prime_ans[n]);
			n ++;
		}
	}

	check(n == 10);

	return 0;
}

// ***************************************  *************************************** //
typedef int cmp_t(const void *, const void *);

static char	*med3(char *, char *, char *, cmp_t *);
static void	 swapfunc(char *, char *, int, int);

#define min(a, b)	(a) < (b) ? a : b

/*
 * Qsort routine from Bentley & McIlroy's "Engineering a Sort Function".
 */
#define swapcode(TYPE, parmi, parmj, n) { 		\
	long i = (n) / sizeof (TYPE); 			\
	TYPE *pi = (TYPE *) (parmi); 		\
	TYPE *pj = (TYPE *) (parmj); 		\
	do { 						\
		TYPE	t = *pi;		\
		*pi++ = *pj;				\
		*pj++ = t;				\
        } while (--i > 0);				\
}

#define SWAPINIT(a, es) swaptype = ((char *)a - (char *)0) % sizeof(long) || \
	es % sizeof(long) ? 2 : es == sizeof(long)? 0 : 1;

static void swapfunc(char *a, char *b, int n, int swaptype)
{
	if(swaptype <= 1)
		swapcode(long, a, b, n)
	else
		swapcode(char, a, b, n)
}

#define swap(a, b)					\
	if (swaptype == 0) {				\
		long t = *(long *)(a);			\
		*(long *)(a) = *(long *)(b);		\
		*(long *)(b) = t;			\
	} else						\
		swapfunc(a, b, es, swaptype)

#define vecswap(a, b, n) 	if ((n) > 0) swapfunc(a, b, n, swaptype)

static inline char *med3(char *a, char *b, char *c, cmp_t *cmp)
{
	return cmp(a, b) < 0 ?
	       (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a ))
              :(cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c ));
}

/*
 * Classical function call recursion wastes a lot of stack space. Each
 * recursion level requires a full stack frame comprising all local variables
 * and additional space as dictated by the processor calling convention.
 *
 * This implementation instead stores the variables that are unique for each
 * recursion level in a parameter stack array, and uses iteration to emulate
 * recursion. Function call recursion is not used until the array is full.
 *
 * To ensure the stack consumption isn't worsened by this design, the size of
 * the parameter stack array is chosen to be similar to the stack frame
 * excluding the array. Each function call recursion level can handle this
 * number of iterative recursion levels.
 */
#define PARAMETER_STACK_LEVELS 8u

void qsort(void *a, size_t n, size_t es, cmp_t *cmp)
{
	char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
	size_t d, r;
	int cmp_result;
	int swaptype, swap_cnt;
	size_t recursion_level = 0;
	struct { void *a; size_t n; } parameter_stack[PARAMETER_STACK_LEVELS];

	SWAPINIT(a, es);
loop:	swap_cnt = 0;
	if (n < 7) {
		/* Short arrays are insertion sorted. */
		for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0;
			     pl -= es)
				swap(pl, pl - es);
		goto pop;
	}

	/* Select a pivot element, move it to the left. */
	pm = (char *) a + (n / 2) * es;
	if (n > 7) {
		pl = a;
		pn = (char *) a + (n - 1) * es;
		if (n > 40) {
			d = (n / 8) * es;
			pl = med3(pl, pl + d, pl + 2 * d, cmp);
			pm = med3(pm - d, pm, pm + d, cmp);
			pn = med3(pn - 2 * d, pn - d, pn, cmp);
		}
		pm = med3(pl, pm, pn, cmp);
	}
	swap(a, pm);

	/*
	 * Sort the array relative the pivot in four ranges as follows:
	 * { elems == pivot, elems < pivot, elems > pivot, elems == pivot }
	 */
	pa = pb = (char *) a + es;
	pc = pd = (char *) a + (n - 1) * es;
	for (;;) {
		/* Scan left to right stopping at first element > pivot. */
		while (pb <= pc && (cmp_result = cmp(pb, a)) <= 0) {
			/* Move elements == pivot to the left (to pa) */
			if (cmp_result == 0) {
				swap_cnt = 1;
				swap(pa, pb);
				pa += es;
			}
			pb += es;
		}
		/* Scan right to left stopping at first element < pivot. */
		while (pb <= pc && (cmp_result = cmp( pc, a)) >= 0) {
			/* Move elements == pivot to the right (to pd) */
			if (cmp_result == 0) {
				swap_cnt = 1;
				swap(pc, pd);
				pd -= es;
			}
			pc -= es;
		}
		if (pb > pc)
			break;
		/* The scan has found two elements to swap with each other. */
		swap(pb, pc);
		swap_cnt = 1;
		pb += es;
		pc -= es;
	}
	if (swap_cnt == 0) {  /* Switch to insertion sort */
		for (pm = (char *) a + es; pm < (char *) a + n * es; pm += es)
			for (pl = pm; pl > (char *) a && cmp(pl - es, pl) > 0;
			     pl -= es)
				swap(pl, pl - es);
		goto pop;
	}

	/*
	 * Rearrange the array in three parts sorted like this:
	 * { elements < pivot, elements == pivot, elements > pivot }
	 */
	pn = (char *) a + n * es;
	r = min(pa - (char *)a, pb - pa);
	vecswap(a, pb - r, r);
	r = min(pd - pc, pn - pd - es);
	vecswap(pb, pn - r, r);
	d = pb - pa; /* d = Size of left part. */
	r = pd - pc; /* r = Size of right part. */
	pn -= r;     /* pn = Base of right part. */

	/*
	 * Check which of the left and right parts are larger.
	 * Set (a, n)  to (base, size) of the larger part.
	 * Set (pa, r) to (base, size) of the smaller part.
	 */
	if (r > d) { /* Right part is the larger part */
		pa = a;
		a = pn;
		n = r;
		r = d;
	}
	else { /* Left part is the larger part, or both are equal. */
		pa = pn;
		n = d;
	}

	/*
	 * The left and right parts each need further sorting if they
	 * contain two elements or more. If both need sorting we use
	 * recursion to sort the smaller part and save the larger part
	 * to be sorted by iteration after the recursion.
	 * Using recursion only for the smaller part guarantees a
	 * recursion depth that is bounded to be less than (log2(n)).
	 */
	if (r > es) {  /* Smaller part > 1 element. Both parts need sorting. */
		if (recursion_level < PARAMETER_STACK_LEVELS) {
			/*
			 * The smaller part needs to be recursively sorted
			 * before the larger part is sorted. To avoid function
			 * call recursion the parameters for the larger part
			 * are pushed on the parameter_stack array. The smaller
			 * part is sorted using iteration and the larger part
			 * will be sorted when the parameter_stack is popped
			 * after the smaller part has been sorted.
			 */
			parameter_stack[recursion_level].a = a;
			parameter_stack[recursion_level].n = n / es;
			recursion_level++;
			a = pa;
			n = r / es;
			goto loop;
		}
		else {
			/*
			 * The parameter_stack array is full. The smaller part
			 * is sorted using function call recursion. The larger
			 * part will be sorted after the function call returns.
			 */
			qsort(pa, r / es, es, cmp);
		}
	}
	if (n > es) {  /* The larger part needs sorting. Iterate to sort.  */
		n = n / es;
		goto loop;
	}
	/* Both left and right parts are one element or less - level done. */
pop:
	if (recursion_level != 0) {
		recursion_level--;
		a = parameter_stack[recursion_level].a;
		n = parameter_stack[recursion_level].n;
		goto loop;
	}
}

#define qsort_N 20

int qsort_a[qsort_N] = {2, 12, 14, 6, 13, 15, 16, 10, 0, 18, 11, 19, 9, 1, 7, 5, 4, 3, 8, 17};

static int case_cmpu(const void *pa, const void *pb)
{
    int a = *(int *)pa;
    int b = *(int *)pb;
    return a < b ? -1 : a > b;
}

int qsort_main() {
	// quick_sort(a, 0, N - 1);
    qsort(qsort_a, qsort_N, sizeof(int), case_cmpu);

	int i;
	for(i = 0; i < qsort_N; i ++) {
		check(qsort_a[i] == i);
	}

	check(i == qsort_N);

	// quick_sort(a, 0, N - 1);
    qsort(qsort_a, qsort_N, sizeof(int), case_cmpu);
	for(i = 0; i < qsort_N; i ++) {
		check(qsort_a[i] == i);
	}

	check(i == qsort_N);

	return 0;
}
// ***************************************  *************************************** //
#define quick_sort_N 20

int quick_sort_a[quick_sort_N] = {2, 12, 14, 6, 13, 15, 16, 10, 0, 18, 11, 19, 9, 1, 7, 5, 4, 3, 8, 17};

int partition(int *a, int p, int q) {
	int pivot = a[p];
	int i = p, j = q;
	while(i < j) {
		while(i < j && a[j] > pivot) j --;
		a[i] = a[j];

		while(i < j && a[i] <= pivot) i ++;
		a[j] = a[i];
	}

	a[i] = pivot;
	return i;
}

void quick_sort(int *a, int p, int q) {
	if(p >= q) return;

	int m = partition(a, p, q);
	quick_sort(a, p, m - 1);
	quick_sort(a, m + 1, q);
}

int quick_sort_main() {
	quick_sort(quick_sort_a, 0, quick_sort_N - 1);

	int i;
	for(i = 0; i < quick_sort_N; i ++) {
		check(quick_sort_a[i] == i);
	}

	check(i == quick_sort_N);

	quick_sort(quick_sort_a, 0, quick_sort_N - 1);

	for(i = 0; i < quick_sort_N; i ++) {
		check(quick_sort_a[i] == i);
	}

	check(i == quick_sort_N);

	return 0;
}

// ***************************************  *************************************** //
int f0(int, int);
int f1(int, int);
int f2(int, int);
int f3(int, int);

int (*func[])(int, int) = {
  f0, f1, f2, f3,
};

int rec = 0, lvl = 0;

int f0(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[3](n / 3, l + 1);
};

int f1(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[0](n - 1, l + 1);
};

int f2(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[1](n, l + 1) + 9;
};

int f3(int n, int l) {
  if (l > lvl) lvl = l;
  rec ++;
  return n <= 0 ? 1 : func[2](n / 2, l + 1) * 3 + func[2](n / 2, l + 1) * 2;
};

int recursion_ans[] = {38270, 218, 20};

int recursion_main() {
  int x = func[0](14371, 0);
  check(x == recursion_ans[0]);   // answer
  check(rec == recursion_ans[1]); // # recursions
  check(lvl == recursion_ans[2]); // max depth
  return 0;
}
// ***************************************  *************************************** //
#include "trap.h"

#define select_sort_N 20

int select_sort_a[select_sort_N] = {2, 12, 14, 6, 13, 15, 16, 10, 0, 18, 11, 19, 9, 1, 7, 5, 4, 3, 8, 17};

void select_sort() {
	int i, j, k, t;
	for(i = 0; i < select_sort_N - 1; i ++) {
		k = i;
		for(j = i + 1; j < select_sort_N; j ++) {
			if(select_sort_a[j] < select_sort_a[k]) {
				k = j;
			}
		}

		t = select_sort_a[i];
		select_sort_a[i] = select_sort_a[k];
		select_sort_a[k] = t;
	}
}

int select_sort_main() {
	select_sort();

	int i;
	for(i = 0; i < select_sort_N; i ++) {
		check(select_sort_a[i] == i);
	}

	check(i == select_sort_N);

	select_sort();

	for(i = 0; i < select_sort_N; i ++) {
		check(select_sort_a[i] == i);
	}

	check(i == select_sort_N);

	return 0;
}

// ***************************************  *************************************** //
unsigned test[] = {
	0x12345678, 0x98765432, 0x0, 0xeffa1000, 0x7fffffff, 0x80000000, 0x33, 0xffffffff
};

unsigned srl_ans[] = {
	0x2468ac, 0x130eca8, 0x0, 0x1dff420, 0xffffff, 0x1000000, 0x0, 0x1ffffff
};

unsigned srlv_ans[] = {
	0x1234567, 0x4c3b2a1, 0x0, 0x1dff420, 0x7fffff, 0x400000, 0x0, 0x1fffff
};

unsigned srav_ans[] = {
	0x1234567, 0xfcc3b2a1, 0x0, 0xffdff420, 0x7fffff, 0xffc00000, 0x0, 0xffffffff
};


int shift_main() {
	unsigned i;

	for(i = 0; i < LENGTH(test); i ++) {
		check((test[i] >> 7) == srl_ans[i]);
	}

	for(i = 0; i < LENGTH(test); i ++) {
		check((unsigned)((int)test[i] >> (i + 4)) == srav_ans[i]);
	}

	for(i = 0; i < LENGTH(test); i ++) {
		check((test[i] >> (i + 4)) == srlv_ans[i]);
	}

	return 0;
}

// ***************************************  *************************************** //
int shuixianhua_ans[] = {153, 370, 371, 407};

int cube(int n) {
	return n * n * n;
}

int shuixianhua_main() {
	int n, n2, n1, n0;
	int k = 0;
	for(n = 100; n < 500; n ++) {
		n2 = n / 100;
		n1 = (n / 10) % 10;
		n0 = n % 10;

		if(n == cube(n2) + cube(n1) + cube(n0)) {
			check(n == shuixianhua_ans[k]);
			k ++;
		}
	}

	check(k == 4);

	return 0;
}

// ***************************************  *************************************** //
int sum_main() {
	int i = 1;
	volatile int sum = 0;
	while(i <= 100) {
		sum += i;
		i ++;
	}

	check(sum == 5050);

	return 0;
}

// ***************************************  *************************************** //
int switch_case(int n) {
	int ret;
	switch(n) {
		case 0: ret = 0; break;
		case 1: ret = 2; break;
		case 2: case 3: ret = 5; break;
		case 4: case 5: case 6: case 7: ret = 8; break;
		case 8: case 9: case 10: case 11: ret = 10; break;
		case 12: ret = 15; break;
		default: ret = -1; break;
	}

	return ret;
}

int switch_ans[] = {-1, 0, 2, 5, 5, 8, 8, 8, 8, 10, 10, 10, 10, 15, -1};

int switch_main() {
	int i;
	for(i = 0; i < 15; i ++) {
		check(switch_case(i - 1) == switch_ans[i]);
	}

	check(i == 15);

	return 0;
}

// ***************************************  *************************************** //
char to_lower_case(char c) {
	return (c >= 'A' && c <= 'Z' ? (c + 32) : c);
}

volatile char to_lower_case_ans [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
	97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,
	91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127};

int to_lower_case_main() {
	int i;
	for(i = 0; i < 128; i ++) {
		check(to_lower_case(i) == to_lower_case_ans[i]);
	}

	return 0;
}

// ***************************************  *************************************** //
volatile unsigned unalign_x = 0xffffffff;
volatile unsigned char unalign_buf[16];

int unalign_main() {

	for(int i = 0; i < 4; i++) {
		*((volatile unsigned*)(unalign_buf + 3)) = 0xaabbccdd;

		unalign_x = *((volatile unsigned*)(unalign_buf + 3));
		check(unalign_x == 0xaabbccdd);

		unalign_buf[0] = unalign_buf[1] = 0;
	}

	return 0;
}

// ***************************************  *************************************** //
int wanshu_ans[] = {6, 28};

int wanshu_main() {
	int n, sum, i, k = 0;
	for(n = 1; n < 30; n ++) {
		sum = 0;
		for(i = 1; i < n; i ++) {
			if(n % i == 0) {
				sum += i;
			}
		}

		if(sum == n) {
			check(n == wanshu_ans[k]);
			k ++;
		}
	}

	check(k == 2);

	return 0;
}

// ***************************************  *************************************** //

// ***************************************  *************************************** //

// ***************************************  *************************************** //

// ***************************************  *************************************** //


int main(){
	add_main();
	leap_year_main();
	bubble_sort_main();
	crc32_main();
	div_main();
	fact_main();
	fib_main();
	goldbach_main();
	if_else_main();
	load_store_main();
	matrix_mul_main();
	max_main();
	mersenne_main();
	min3_main();
	mov_c_main();
	movsx_main();
	pascal_main();
	prime_main();
	qsort_main();
	quick_sort_main();
	recursion_main();
	select_sort_main();
	shift_main();
	shuixianhua_main();
	sum_main();
	switch_main();
	to_lower_case_main();
	unalign_main();
	wanshu_main();
	return 0;
}

