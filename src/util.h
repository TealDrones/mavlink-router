/*
 * This file is part of the MAVLink Router project
 *
 * Copyright (C) 2016  Intel Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>


#include "macro.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t usec_t;
typedef uint64_t nsec_t;
#define USEC_INFINITY ((usec_t)-1)

#define MSEC_PER_SEC 1000ULL
#define USEC_PER_SEC ((usec_t)1000000ULL)
#define USEC_PER_MSEC ((usec_t)1000ULL)
#define NSEC_PER_SEC ((nsec_t)1000000000ULL)
#define NSEC_PER_MSEC ((nsec_t)1000000ULL)
#define NSEC_PER_USEC ((nsec_t)1000ULL)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define streq(a, b) (strcmp((a), (b)) == 0)
#define strcaseeq(a, b) (strcasecmp((a), (b)) == 0)
#define strncaseeq(a, b, len) (strncasecmp((a), (b), (len)) == 0)
#define memcaseeq(a, len_a, b, len_b) ((len_a) == (len_b) && strncaseeq(a, b, len_a))

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

int safe_atoull(const char *s, unsigned long long *ret);
int safe_atoul(const char *s, unsigned long *ret);
int safe_atoi(const char *s, int *ret);
usec_t now_usec(void);
usec_t ts_usec(const struct timespec *ts);

int mkdir_p(const char *path, int len, mode_t mode);

size_t mem_cpy(void *dest, size_t dsize, const void *src, size_t ssize, size_t cnt);

#ifdef __cplusplus
}
#endif
