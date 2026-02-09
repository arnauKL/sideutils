# sideutils (not core)

Rewriting the GNU coreutils.

Was inspired by busybox and this [video](https://www.youtube.com/watch?v=HfRlzYihRr0<F21>) by xyve.

Resources:
- [List of POSIX commands Wikipedia](https://en.wikipedia.org/wiki/List_of_POSIX_commands)
- Section 3 of man pages

I'll skip over some like mkdir since it's just a wrapper for the syscall and
it'll be 20 lines. Some are still WIP (like `grep`).
