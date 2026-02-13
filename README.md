# POSIX stuff: ashew & sideutils

Rewriting some UNIX coreutils.

The repo consists of two main parts:
- **ashew**: A simple shell.
- **sideutils**: Custom implementations of coreutils.

## Directory Structure

- /ashew: The main shell project. See [detailed README](ashew/README.md)
- /sideutils: cat.c, ls.c, grep.c: Individual POSIX utility implementations.

## Resources:

- [List of POSIX commands Wikipedia](https://en.wikipedia.org/wiki/List_of_POSIX_commands)
- Section 3 of man pages
- [GNU coreutils source
  code](https://github.com/coreutils/coreutils/tree/master)


## Notes

- I was initially inspired by busybox and [this
  video](https://www.youtube.com/watch?v=HfRlzYihRr0<F21>) by xyve.

- I don't like having to decypher variable names when reading code.
  I try to keep mine very descriptive. Editors have autocomplete for a reason.

- Built on raw educational procrastination

- I'll skip over some like mkdir since it's just a wrapper for the syscall and
  it'll be 20 lines. Some are still WIP (like `grep` and the shell).
