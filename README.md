# ❌-nix

## What is ❌-nix ?

**WARNING:** This library is still experimental. Use with care!

❌-nix (or "cross-nix") is a header-only C library meant to provide a
linux compatibility layer on top of other platforms by including
the right headers or implementing the right functions.

Its end goal is to expose an unified interface for Linux, OS X, and Windows.

## Is ❌-nix for me ?

❌-nix is for you if:
* you want to make your software available on multiple platforms but keep
  some linux-specific features
* you want a compatibility layer rather than an emulated environment
* you can afford to recompile your software on the target platform

## How do I use it ?

Add the `x-nix` directory to your include path, and simply add at the begining
of your source file:

```c
#include <x-nix/x-nix.h>
```

Or, if you want to only add some of the features, include any of the following:

```c
#include <x-nix/pid.h> // pid_t, getpid
#include <x-nix/wait.h> // wait, waitpid
#include <x-nix/pipe.h> // pipe
#include <x-nix/time.h> // clock_gettime
```

## Acknowledgements

Here are some cool alternatives to ❌-nix, with some similarities and differences:

### [Cygwin](http://cygwin.com)

Cygwin a reimplementation of the linux API on top of the windows API -- however,
it requires you to use the Cygwin toolchain and environment to compile
and run your software.

### [Foreign linux](https://github.com/wishstudio/flinux)

Foreign linux is a binary translator that allows you to run unmodified
linux binaries on windows.

