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
#ifndef X_NIX_WAIT_H_
# define X_NIX_WAIT_H_

# include "common.h"
# include "pid.h"
# include "signal.h"

# ifdef XNIX_VANILLA_WIN32
#  define WNOHANG 1      /* Don't block waiting.  */
#  define WUNTRACED 2    /* Report status of stopped children.  */
# endif

# ifdef XNIX_VANILLA_WIN32
static inline unsigned int xnix_seh_to_signal(int exit_code) {
    switch (exit_code) {
        case STATUS_FLOAT_DENORMAL_OPERAND:
        case STATUS_FLOAT_DIVIDE_BY_ZERO:
        case STATUS_FLOAT_INEXACT_RESULT:
        case STATUS_FLOAT_INVALID_OPERATION:
        case STATUS_FLOAT_OVERFLOW:
        case STATUS_FLOAT_STACK_CHECK:
        case STATUS_FLOAT_UNDERFLOW:
        case STATUS_INTEGER_DIVIDE_BY_ZERO:
        case STATUS_INTEGER_OVERFLOW:           return SIGFPE;

        case STATUS_ILLEGAL_INSTRUCTION:
        case STATUS_PRIVILEGED_INSTRUCTION:
        case STATUS_NONCONTINUABLE_EXCEPTION:   return SIGILL;

        case STATUS_TIMEOUT:                    return SIGALRM;

        case STATUS_ACCESS_VIOLATION:
        case STATUS_DATATYPE_MISALIGNMENT:
        case STATUS_ARRAY_BOUNDS_EXCEEDED:
        case STATUS_GUARD_PAGE_VIOLATION:
        case STATUS_IN_PAGE_ERROR:
        case STATUS_NO_MEMORY:
        case STATUS_INVALID_DISPOSITION:
        case STATUS_STACK_OVERFLOW:             return SIGSEGV;

        case STATUS_CONTROL_C_EXIT:             return SIGINT;

        default: return 0;
    }
}

static inline pid_t waitpid(pid_t pid, int *status, int mode) {
    assert(pid > 0);

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    DWORD waitmillis = mode & WNOHANG ? 0 : INFINITE;
    DWORD res = WaitForSingleObject(processHandle, waitmillis);
    if (!(mode & WUNTRACED) && waitmillis == INFINITE) {
        while (res == WAIT_ABANDONED) {
            Sleep(100);
            res = WaitForSingleObject(processHandle, waitmillis);
        }
    }

    if (mode & WUNTRACED && res == WAIT_ABANDONED) {
        *status = 0x7f;
        CloseHandle(processHandle);
        return pid;
    }

    DWORD exit_code;
    GetExitCodeProcess(processHandle, &exit_code);

    CloseHandle(processHandle);

    unsigned int sig = xnix_seh_to_signal(exit_code);

    int exit_status = exit_code > 127 ? 127 : (exit_code < -127 ? -127 : exit_code);

    *status = sig ? sig : exit_status << 8;

    return pid;
}

static inline pid_t wait(int *status) {
    return waitpid(-1, status, 0);
}
# endif

#endif /* !X_NIX_WAIT_H_ */
