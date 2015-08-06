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
#ifndef X_NIX_PID_H_
# define X_NIX_PID_H_

# include "common.h"

# if defined(XNIX_VANILLA_WIN32) && !defined(__pid_t_defined)
#  ifdef __GNUC__
typedef __pid_t pid_t;
#  else /* __GNUC__ */
typedef DWORD pid_t;
#  endif /* __GNUC__ */
#  define __pid_t_defined
# endif /* XNIX_VANILLA_WIN32 */

# ifdef XNIX_VANILLA_WIN32
static inline pid_t getpid(void) {
    return GetCurrentProcessId();
}
# endif /* XNIX_VANILLA_WIN32 */

#endif /* !X_NIX_PID_H_ */
