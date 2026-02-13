# POSIX stuff: ashew (shell) & sideutils (coreutils)

Rewriting some coreutils.

*Structure:*

- /ashew: The main shell project. [See more](ashew/README.md)
- /sideutils: cat.c, ls.c, grep.c

## Notes

- I was initially inspired by busybox and [this
  video](https://www.youtube.com/watch?v=HfRlzYihRr0<F21>) by xyve.

- I don't like having to decypher variable names when reading code.
  I try to keep mine very descriptive. Editors have autocomplete for a reason.

- Raw procrastination

- I'll skip over some like mkdir since it's just a wrapper for the syscall and
  it'll be 20 lines. Some are still WIP (like `grep` and the shell).
