/*
 * The MIT License (MIT)
 *
 * Copyright © 2015 Franklin "Snaipe" Mathieu <http://snai.pe/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef X_NIX_TIME_H_
# define X_NIX_TIME_H_

# include "common.h"

# if defined(__APPLE__)
#  include <mach/clock.h>
#  include <mach/mach.h>
# endif

# if defined(__APPLE__) || defined (XNIX_VANILLA_WIN32)

#  define XNIX_GIGA 1000000000

struct timespec_compat {
    int64_t tv_sec;
    int64_t tv_nsec;
};

static inline int clock_gettime(clockid_t clock, struct timespec *ts) {
#  if defined(__APPLE__)
    clock_serv_t cclock;
    mach_timespec_t mts;

    host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
    int res = clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);

    *ts = (struct timespec) { mts.tv_sec, mts.tv_nsec };
    return res > 0 ? -1 : 0;
#  elif defined(XNIX_VANILLA_WIN32)
    XNIX_ASSERT(clock == CLOCK_MONOTONIC
             || clock == CLOCK_MONOTONIC_RAW
             || clock == CLOCK_MONOTONIC_COARSE, "Clock not supported.");

    LARGE_INTEGER freq, count;
    if (!QueryPerformanceFrequency(&freq) || !QueryPerformanceCounter(&count))
        return -1;

    int64_t sec  = count.QuadPart / freq.QuadPart;
    int64_t nano = (int64_t) ((double) count.QuadPart * XNIX_GIGA / (double) freq.QuadPart) % XNIX_GIGA;

    *ts = (struct timespec) { sec, nano };
    return 0;
#  endif
}

# endif

#endif /* !X_NIX_TIME_H_ */
