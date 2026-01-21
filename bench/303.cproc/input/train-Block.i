# 0 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/riscv64-linux-gnu/include/stdc-predef.h" 1 3
# 0 "<command-line>" 2
# 1 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.c"




# 1 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.h" 1







# 1 "/home/ysyx/new-benchmark/bench/100.blockchain/sha256.h" 1







# 1 "/home/projectn/navy-apps/libs/ulib/include/stdint.h" 1




typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned long uintptr_t;

typedef signed long long int64_t;
typedef signed int int32_t;
typedef signed short int16_t;
typedef signed char int8_t;
typedef signed long intptr_t;

typedef unsigned long uintmax_t;
typedef signed long intmax_t;
# 9 "/home/ysyx/new-benchmark/bench/100.blockchain/sha256.h" 2
# 1 "/home/projectn/navy-apps/libs/ulib/include/string.h" 1
# 1 "/home/projectn/navy-apps/libs/ulib/include/stddef.h" 1



typedef unsigned long size_t;
typedef signed long ssize_t;
typedef signed long ptrdiff_t;
# 2 "/home/projectn/navy-apps/libs/ulib/include/string.h" 2

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memchr(const void *s, int c, size_t n);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
size_t strlen(const char *s);
char *strchr(const char *s, int c);
size_t strspn(const char *s, const char *accept);
char *strpbrk(const char *s, const char *accept);
int strcoll(const char *s1, const char *s2);
char *strstr(const char *haystack, const char *needle);
# 10 "/home/ysyx/new-benchmark/bench/100.blockchain/sha256.h" 2




typedef struct SHA256 {
  uint32_t m_tot_len;
  uint32_t m_len;
  uint32_t m_h[8];
  uint8_t m_block[2 * (512 / 8)];
} SHA256;

void sha256(char *output, const char *input);
# 9 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.h" 2
# 1 "/home/projectn/navy-apps/libs/ulib/include/stdint.h" 1




typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned long uintptr_t;

typedef signed long long int64_t;
typedef signed int int32_t;
typedef signed short int16_t;
typedef signed char int8_t;
typedef signed long intptr_t;

typedef unsigned long uintmax_t;
typedef signed long intmax_t;
# 10 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.h" 2

typedef struct Block {
  int64_t _nNonce;
  const char *_sData;
  const char *sPrevHash;
  uint32_t _nIndex;
  uint32_t _tTime;
  char _sHash[2 * (256 / 8) + 1];
} Block;

void initBlock(Block *this, uint32_t nIndexIn, const char *sDataIn);
const char *GetHash(Block *this);
void MineBlock(Block *this, uint32_t nDifficulty);
# 6 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.c" 2

# 1 "/home/ysyx/new-benchmark/libbench/include/bench.h" 1



# 1 "/home/projectn/navy-apps/libs/ulib/include/stdint.h" 1




typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef unsigned long uintptr_t;

typedef signed long long int64_t;
typedef signed int int32_t;
typedef signed short int16_t;
typedef signed char int8_t;
typedef signed long intptr_t;

typedef unsigned long uintmax_t;
typedef signed long intmax_t;
# 5 "/home/ysyx/new-benchmark/libbench/include/bench.h" 2



# 1 "/usr/riscv64-linux-gnu/include/assert.h" 1 3
# 35 "/usr/riscv64-linux-gnu/include/assert.h" 3
# 1 "/usr/riscv64-linux-gnu/include/features.h" 1 3
# 394 "/usr/riscv64-linux-gnu/include/features.h" 3
# 1 "/usr/riscv64-linux-gnu/include/features-time64.h" 1 3
# 20 "/usr/riscv64-linux-gnu/include/features-time64.h" 3
# 1 "/usr/riscv64-linux-gnu/include/bits/wordsize.h" 1 3
# 21 "/usr/riscv64-linux-gnu/include/features-time64.h" 2 3
# 1 "/usr/riscv64-linux-gnu/include/bits/timesize.h" 1 3
# 22 "/usr/riscv64-linux-gnu/include/features-time64.h" 2 3
# 395 "/usr/riscv64-linux-gnu/include/features.h" 2 3
# 502 "/usr/riscv64-linux-gnu/include/features.h" 3
# 1 "/usr/riscv64-linux-gnu/include/sys/cdefs.h" 1 3
# 576 "/usr/riscv64-linux-gnu/include/sys/cdefs.h" 3
# 1 "/usr/riscv64-linux-gnu/include/bits/wordsize.h" 1 3
# 577 "/usr/riscv64-linux-gnu/include/sys/cdefs.h" 2 3
# 1 "/usr/riscv64-linux-gnu/include/bits/long-double.h" 1 3
# 578 "/usr/riscv64-linux-gnu/include/sys/cdefs.h" 2 3
# 503 "/usr/riscv64-linux-gnu/include/features.h" 2 3
# 526 "/usr/riscv64-linux-gnu/include/features.h" 3
# 1 "/usr/riscv64-linux-gnu/include/gnu/stubs.h" 1 3




# 1 "/usr/riscv64-linux-gnu/include/bits/wordsize.h" 1 3
# 6 "/usr/riscv64-linux-gnu/include/gnu/stubs.h" 2 3
# 17 "/usr/riscv64-linux-gnu/include/gnu/stubs.h" 3
# 1 "/usr/riscv64-linux-gnu/include/gnu/stubs-lp64d.h" 1 3
# 18 "/usr/riscv64-linux-gnu/include/gnu/stubs.h" 2 3
# 527 "/usr/riscv64-linux-gnu/include/features.h" 2 3
# 36 "/usr/riscv64-linux-gnu/include/assert.h" 2 3
# 66 "/usr/riscv64-linux-gnu/include/assert.h" 3




# 69 "/usr/riscv64-linux-gnu/include/assert.h" 3
extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     ;


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     ;




extern void __assert (const char *__assertion, const char *__file, int __line)
     ;



# 9 "/home/ysyx/new-benchmark/libbench/include/bench.h" 2
# 1 "/home/projectn/navy-apps/libs/ulib/include/stdio.h" 1



# 1 "/usr/lib/gcc-cross/riscv64-linux-gnu/13/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc-cross/riscv64-linux-gnu/13/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 103 "/usr/lib/gcc-cross/riscv64-linux-gnu/13/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 5 "/home/projectn/navy-apps/libs/ulib/include/stdio.h" 2
# 1 "/home/projectn/navy-apps/libs/ulib/include/stddef.h" 1




# 4 "/home/projectn/navy-apps/libs/ulib/include/stddef.h"
typedef unsigned long size_t;
typedef signed long ssize_t;
typedef signed long ptrdiff_t;
# 6 "/home/projectn/navy-apps/libs/ulib/include/stdio.h" 2
# 20 "/home/projectn/navy-apps/libs/ulib/include/stdio.h"
typedef struct FILE {
  int fd;
  int used;
} FILE;

extern FILE *stdin, *stderr, *stdout;

FILE *fopen(const char *pathname, const char *mode);
FILE *freopen(const char *pathname, const char *mode, FILE *fp);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
int fclose(FILE *stream);

int fputs(const char *s, FILE *fp);
int printf(const char*, ...) ;
int fprintf(FILE *, const char*, ...) ;
int sprintf(char *str, const char *format, ...);
int snprintf(char* buffer, size_t count, const char* format, ...) ;
int vsnprintf(char* buffer, size_t count, const char* format, va_list va);

int getc(FILE *fp);
int ungetc(int c, FILE *stream);
char *fgets(char *s, int size, FILE *fp);
int sscanf(const char *str, const char *format, ...);
int fscanf(FILE *fp, const char *format, ...);

int fflush(FILE *stream);
int ferror(FILE *stream);
int feof(FILE *stream);
void clearerr(FILE *fp);

FILE *tmpfile();
int remove(const char *pathname);
int rename(const char *oldpath, const char *newpath);
char *tmpnam(char *s);

int setvbuf(FILE *fp, char *buf, int mode, size_t size);
# 10 "/home/ysyx/new-benchmark/libbench/include/bench.h" 2
# 1 "/home/projectn/navy-apps/libs/ulib/include/stdlib.h" 1
# 1 "/home/projectn/navy-apps/libs/ulib/include/stddef.h" 1



typedef unsigned long size_t;
typedef signed long ssize_t;
typedef signed long ptrdiff_t;
# 2 "/home/projectn/navy-apps/libs/ulib/include/stdlib.h" 2





int abs(int x);
int atoi(const char *s);

char *getenv(const char *name);

void exit(int status);
void abort();
int system(const char *command);

void *malloc(size_t nbytes);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ap);

int isprint(int c);
int isspace(int c);
int isdigit(int c);
int isxdigit(int c);
int islower(int c);
int isupper(int c);
int isalpha(int c);
int isalnum(int c);
int ispunct(int c);
int iscntrl(int c);
int isgraph(int c);
int tolower(int c);
int toupper(int c);

long strtol(const char *nptr, char **endptr, int base);

int rand();
void srand(unsigned int seed);
# 11 "/home/ysyx/new-benchmark/libbench/include/bench.h" 2
# 1 "/home/projectn/navy-apps/libs/ulib/include/string.h" 1
# 1 "/home/projectn/navy-apps/libs/ulib/include/stddef.h" 1



typedef unsigned long size_t;
typedef signed long ssize_t;
typedef signed long ptrdiff_t;
# 2 "/home/projectn/navy-apps/libs/ulib/include/string.h" 2

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memchr(const void *s, int c, size_t n);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
size_t strlen(const char *s);
char *strchr(const char *s, int c);
size_t strspn(const char *s, const char *accept);
char *strpbrk(const char *s, const char *accept);
int strcoll(const char *s1, const char *s2);
char *strstr(const char *haystack, const char *needle);
# 12 "/home/ysyx/new-benchmark/libbench/include/bench.h" 2


enum {
  BENCH_SETTING_TEST,
  BENCH_SETTING_TRAIN,
  BENCH_SETTING_REF,
  BENCH_SETTING_HUGE,
  BENCH_NR_SETTING,
};

void bench_srand(uint32_t _seed);
uint32_t bench_rand();
uint64_t bench_uptime();
void bench_exit(int status);
uint32_t bench_checksum(const void *start, const void *end);
# 8 "/home/ysyx/new-benchmark/bench/100.blockchain/Block.c" 2

static void _CalculateHash(Block *this) {
  static char str[1024];
  sprintf(str, "%d%d%s%lld%s", this->_nIndex, this->_tTime, this->_sData, this->_nNonce, this->sPrevHash);
  sha256(this->_sHash, str);
}

void initBlock(Block *this, uint32_t nIndexIn, const char *sDataIn) {
  this->_nIndex = nIndexIn;
  this->_sData = sDataIn;
  this->_nNonce = -1;
  this->_tTime = bench_rand();
  this->_sHash[0] = '\0';
}

const char *GetHash(Block *this) {
  return this->_sHash;
}

void MineBlock(Block *this, uint32_t nDifficulty) {
  char *cstr = malloc(nDifficulty + 1);
  memset(cstr, '0', nDifficulty);
  for (uint32_t i = 0; i < nDifficulty; ++i) {
    cstr[i] = '0';
  }
  cstr[nDifficulty] = '\0';

  do {
    this->_nNonce++;
    _CalculateHash(this);
  } while (memcmp(this->_sHash, cstr, nDifficulty) != 0);

  printf("Block mined: %s\n", this->_sHash);
  free(cstr);
}
