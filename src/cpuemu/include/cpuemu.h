#ifndef __CPUEMU_H_
#define __CPUEMU_H_

#define _ASSERT_H
#define NDEBUG

#include <etl/profiles/cpp17_no_stl.h>
#include <etl/platform.h>
#include <am.h>

uint64_t rng64();

void rvmini();
void nutshell();

#endif
