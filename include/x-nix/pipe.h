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
#ifndef X_NIX_PIPE_H_
# define X_NIX_PIPE_H_

# include "common.h"

# ifdef XNIX_VANILLA_WIN32
#  include <io.h>
#  include <fcntl.h>
# else
#  include <sys/fcntl.h>
# endif

# ifdef XNIX_VANILLA_WIN32
static inline int pipe(int fds[2]) {
    HANDLE fhs[2];
    SECURITY_ATTRIBUTES attr = {
        .nLength = sizeof (SECURITY_ATTRIBUTES),
        .bInheritHandle = TRUE
    };
    if (!CreatePipe(fhs, fhs + 1, &attr, 0))
        return -1;

    int modes[] = { _O_RDONLY, _O_WRONLY };
    for (int i = 0; i < 2; ++i) {
        fd[i] = _open_osfhandle((intptr_t) fhs[i], modes[i]);
        if (fd[i] == -1)
            return -1;
    }
}
# endif

#endif /* !X_NIX_PIPE_H_ */
