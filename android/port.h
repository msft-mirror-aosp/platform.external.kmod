/*
 * Copyright (C) 2024 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define _GNU_SOURCE

#include <endian.h>

#if defined(__APPLE__)

#include <endian-darwin.h>
#define HAVE_DECL_STRNDUPA
#define strndupa(_s,_l)        strdup(_s)
char* basename(const char*);
#define init_module     darwin_init_module
#define delete_module   darwin_delete_module
#define program_invocation_short_name "depmod"

#endif

#if defined(__ANDROID__) || defined(__APPLE__)
#include <stdlib.h>
#include <unistd.h>
static inline char *get_current_dir_name(void) {
    return getcwd(malloc(PATH_MAX), PATH_MAX);
}
#endif

#if defined(ANDROID_HOST_MUSL)

// musl string.h doesn't have basename. libgen.h's basename is
// different from GNU basename. Define our own basename to avoid confusion.

extern char* strrchr(const char*, int);
static inline char* basename(const char* path) {
  const char* last_slash = strrchr(path, '/');
  return (char*)((last_slash != 0) ? last_slash + 1 : path);
}

#endif // defined(ANDROID_HOST_MUSL)
