#include <bench_debug.h>
#include <fs.h>
#include <stdarg.h>

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

#define RAMDISK_SIZE ((&ramdisk_end) - (&ramdisk_start))

static Finfo *file_table = NULL;
static size_t file_count = 0;

int fs_init(Finfo *list, size_t count) {
  assert(list);
  file_table = list;
  file_count = count;
  return 0;
}

size_t ramdisk_read(void *buf, size_t offset, size_t len) {
  assert(offset + len <= RAMDISK_SIZE);
  memcpy(buf, &ramdisk_start + offset, len);
  return len;
}
size_t ramdisk_write(const void *buf, size_t offset, size_t len) {
  assert(offset + len <= RAMDISK_SIZE);
  memcpy(&ramdisk_start + offset, buf, len);
  return len;
}

int fs_open(const char *pathname, int flags, int mode) {
  // printf("ex1 addr is %x\n",  (uint32_t)ramdisk_start + 336);
  for (int fs_num = 0; fs_num < file_count; fs_num++) {
    if (strcmp(pathname, file_table[fs_num].name) == 0) {
      file_table[fs_num].open_offset = 0;
      return fs_num;
    }
  }
  bench_printf("assert :no this file : %s\n", pathname);
  assert(0);
}

size_t fs_read(int fd, void *buf, size_t len) {
  assert(file_table);
  assert(buf);
  Finfo *file = &file_table[fd];
  size_t real_len = len;
  size_t size = file->size;
  size_t disk_offset = file->disk_offset;
  size_t open_offset = file->open_offset;

  if (file->read != NULL) {
    return file->read(buf, file->open_offset, len);
  }

  if (open_offset > size) {
    return 0;
  }
  if (open_offset + len > size) {
    real_len = size - open_offset;
  }

  ramdisk_read(buf, disk_offset + open_offset, real_len);
  file->open_offset += real_len;
  return real_len;
}

size_t fs_write(int fd, const void *buf, size_t len) {
  assert(file_table);
  assert(buf);
  Finfo *file = &file_table[fd];
  size_t real_len = len;
  size_t size = file->size;
  size_t disk_offset = file->disk_offset;
  size_t open_offset = file->open_offset;

  if (file->write != NULL) {
    return file->write(buf, file->open_offset, len);
  }

  if (open_offset > size) {
    return 0;
  }
  if (open_offset + len > size) {
    real_len = size - open_offset;
  }

  ramdisk_write(buf, disk_offset + open_offset, real_len);
  file->open_offset += real_len;
  return real_len;
}

size_t fs_lseek(int fd, size_t offset, int whence) {
  assert(file_table);
  size_t new_offset = 0;
  Finfo *file = &file_table[fd];
  switch (whence) {
  case SEEK_SET:
    new_offset = offset;
    break;
  case SEEK_CUR:
    new_offset = file->open_offset + offset;
    break;
  case SEEK_END:
    new_offset = file->size + offset;
    break;
  default:
    return -1;
  }

  if ((new_offset < 0 || new_offset > file->size)) {
    bench_printf("file offset out of bound\n");
    return -1;
  }

  file->open_offset = new_offset;
  return new_offset;
}

int fs_close(int fd) { return 0; }

int fs_tell(int fd) {
  assert(file_table);
  Finfo *file = &file_table[fd];
  return file->open_offset;
}
