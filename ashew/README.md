# tiny shell

- [reference article](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [POSIX headers](https://pubs.opengroup.org/onlinepubs/9699919799/)

## Made with some very big simplifications, aka:

```sh
ashew > cat "basic error"
arg 0: cat
arg 1: "basic
arg 2: error"
```

## Limitations / future expansions:
- No piping or redirecting
- No globbing
- Input parsing is very limited:
    - commands have to be in one line
    - parsing only splits on whitespaces (no quotes or escaping)
- very few builtins
- No arrow support
- No signals
- No history
