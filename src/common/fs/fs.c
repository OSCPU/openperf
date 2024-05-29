#include "fs.h"
#include <klib.h>

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

// #define ramdisk_start (void *)(0x83000000)
// #define ramdisk_end (void *)(0x88000000)

#define RAMDISK_SIZE ((&ramdisk_end) - (&ramdisk_start))

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;

enum {FD_NULL, FD_INPUT, FD_OUTOUT};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  // panic("should not reach here");
  my_printf("should not reach here\n");
  assert(0);
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  // panic("should not reach here");
  my_printf("should not reach here\n");
  assert(0);
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_NULL]  = {"null", 0, 0, invalid_read, invalid_write},
  [FD_INPUT] = {"/share/viedo/video1.yuv", 4992000, 0, NULL, NULL},
  [FD_OUTOUT] = {"/share/viedo/out.h264", 154332, 4992000, NULL, NULL}
};


size_t ramdisk_read(void *buf, size_t offset, size_t len)
{
  assert(offset + len <= RAMDISK_SIZE);
  memcpy(buf, &ramdisk_start + offset, len);
  return len;
}
size_t ramdisk_write(const void *buf, size_t offset, size_t len)
{
  assert(offset + len <= RAMDISK_SIZE);
  memcpy(&ramdisk_start + offset, buf, len);
  return len;
}



int fs_open(const char *pathname, int flags, int mode)
{
  // my_printf("/share/viedo/video1.yuv at %x\n", &ramdisk_start);
  // my_printf("/share/viedo/out.h264 at %x\n", (uint32_t)&ramdisk_start + 4992000);
  for(int fs_num = 0; fs_num < 3; fs_num ++)
  {
    if(strcmp(pathname, file_table[fs_num].name) == 0) // 匹配成功
    {
      file_table[fs_num].open_offset = 0;
      return fs_num;    
    }
  }
  my_printf("assert no this file : %s\n", pathname);
  assert(0);
}
size_t fs_read(int fd, void *buf, size_t len)
{
  Finfo *file = &file_table[fd];
  size_t real_len = len;
  size_t size = file->size;
  size_t disk_offset = file->disk_offset;  
  size_t open_offset = file->open_offset;
  
  if(file->read != NULL)
  {
    return file->read(buf, file->open_offset, len);
  }

  if(open_offset > size)  // 偏移有误
  {
    return 0;
  }
  if(open_offset + len > size)  // 要读取的数据大于文件的数据
  {
    real_len = size - open_offset;
  }

  ramdisk_read(buf, disk_offset + open_offset, real_len);
  file->open_offset += real_len;
  return real_len;
}

size_t fs_write(int fd, const void *buf, size_t len)
{
  Finfo *file = &file_table[fd];
  size_t real_len = len;
  size_t size = file->size;
  size_t disk_offset = file->disk_offset;  
  size_t open_offset = file->open_offset;

  if(file->write != NULL)
  {
    return file->write(buf, file->open_offset, len);
  }

  if(open_offset > size)  // 偏移有误
  {
    return 0;
  }
  if(open_offset + len > size)  // 要读取的数据大于文件的数据
  {
    real_len = size - open_offset;
  }

  ramdisk_write(buf, disk_offset + open_offset, real_len);
  file->open_offset += real_len;
  return real_len;
}

size_t fs_lseek(int fd, size_t offset, int whence)
{
  size_t new_offset = 0;
  Finfo *file = &file_table[fd];
  switch(whence)
  {
    case SEEK_SET:  new_offset = offset;  break;    // 以开头为基准
    case SEEK_CUR:  new_offset = file->open_offset + offset;  break;    // 以当前位置为基准
    case SEEK_END:  new_offset = file->size + offset;  break;    // 以末尾为基准
    default : return -1;
  }

  if((new_offset < 0 || new_offset > file->size)) // 超出范围
  {
    my_printf("file offset out of bound\n");
    return -1;
  }

  file->open_offset = new_offset;
  return new_offset;
}

int fs_close(int fd)
{
  return 0;
}
