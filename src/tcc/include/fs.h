#ifndef __FS_H__
#define __FS_H__

#include <klib.h>
#include <stddef.h>

#ifndef SEEK_SET
enum {SEEK_SET, SEEK_CUR, SEEK_END};
#endif

enum {FD_STDIN, FD_STDOUT, FD_STDERR};

int fs_open(const char *pathname, int flags, int mode);
size_t fs_read(int fd, void *buf, size_t len);
size_t fs_write(int fd, const void *buf, size_t len);
size_t fs_lseek(int fd, size_t offset, int whence);
int fs_close(int fd);
int fs_tell(int fd);

int fs_printf(int fd, const char *fmt, ...);
void fs_putc(int fd, const char c);
void fs_puts(int fd, const char *s);

#endif
