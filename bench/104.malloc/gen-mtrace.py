#!/usr/bin/env python3

# usage: python gen-mtrace.py commmand [args]

from sys import argv
import re
import subprocess

cmd = ['ltrace', '-f', '-e', 'malloc+calloc+realloc+free-@libc*'] + argv[1:]
print(f"Executing command: {cmd}")
result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

pool = {}
idx = 0
nr_op = 0

fp = open("mem.trace", "wb");
a = 0
fp.write(a.to_bytes(4)) # placeholder for the number of addresses
fp.write(a.to_bytes(4)) # placeholder for the number of operation

def emit(func, idx = 0, size = 0, arg3 = 0):
  global nr_op
  op = 0
  match func:
    case "malloc":  op = 0
    case "calloc":  op = 1
    case "realloc": op = 2
    case "free":    op = 3
  arg1 = (idx << 2) | op
  fp.write(arg1.to_bytes(4, byteorder='little', signed=True))
  fp.write(size.to_bytes(4, byteorder='little'))
  fp.write(arg3.to_bytes(4, byteorder='little', signed=True))
  nr_op = nr_op + 1

def checkNotAlloc(addr):
  if pool.get(addr) != None:
    #print(addr + " is already allocated!")
    emitFree(addr)
    free(addr)

def checkAlloc(addr):
  if pool.get(addr) == None:
    #print(addr + " is not allocated!")
    global idx
    emit("malloc", idx, 4)
    alloc(addr)

def alloc(addr):
  global idx
  checkNotAlloc(addr)
  pool[addr] = idx
  idx = idx + 1

def free(addr):
  if addr == '0':
    return
  checkAlloc(addr)
  del pool[addr]

def emitFree(addr):
  if addr == '0':
    emit("free", -1)
    return
  checkAlloc(addr)
  emit("free", pool[addr])


fp1 = open("ltrace.txt", "w");
fp1.write(result.stderr)
fp1.close()

lines = result.stderr.split('\n')
print(f"Processing {len(lines)} library calls...")

for line in lines:
  isMalloc = re.search(r'malloc\((.*)\) *= (0x.*)', line)
  if isMalloc:
    size = int(isMalloc.group(1))
    ret =  isMalloc.group(2)
    emit("malloc", idx, size)
    alloc(ret)
    continue

  isCalloc = re.search(r'calloc\((.*),(.*)\) *= (0x.*)', line)
  if isCalloc:
    nmemb = int(isCalloc.group(1))
    size =  int(isCalloc.group(2))
    ret =   isCalloc.group(3)
    emit("calloc", idx, size, nmemb)
    alloc(ret)
    continue

  isRealloc = re.search(r'realloc\((.*),(.*)\) *= (0x.*)', line)
  if isRealloc:
    ptr = isRealloc.group(1)
    size = int(isRealloc.group(2))
    ret = isRealloc.group(3)
    if ptr == '0':
      emit("realloc", idx, size, -1)
      alloc(ret)
    else:
      checkAlloc(ptr)
      if size == 0:
        emit("realloc", -1, 0, pool[ptr])
        free(ptr)
      else:
        emit("realloc", idx, size, pool[ptr])
        free(ptr)
        alloc(ret)
    continue

  isFree = re.search(r'free\((.*)\)', line)
  if isFree:
    addr = isFree.group(1)
    emitFree(addr)
    free(addr)
    continue

  isExit = re.search(r'\+\+\+ exited \(status .*\) \+\+\+', line)
  if isExit:
    if len(pool) != 0:
      print(f"{len(pool)} unfree memory chunks")
      for addr in pool:
        emit("free", pool[addr])
    fp.close()

    print(f"Statistic: {idx} memory addresses, {nr_op} operations")
    fp = open("mem.trace", "r+b");
    fp.write(idx.to_bytes(4, byteorder='little'))
    fp.write(nr_op.to_bytes(4, byteorder='little'))
    fp.close()
    break

  print("Unsupport library call: " + line)
  #exit(-1)
