# ashew: a tiny shell

I'd like this to be an actual usable shell that is not 10k LOC, has sansane
variable names (all editors have completion enabled, there is no excuse for
abbreviating unreadable variable names) and performs decently well.

This is also an excuse to learn more C + UNIX.

- [reference article](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [POSIX headers](https://pubs.opengroup.org/onlinepubs/9699919799/)



I built this to demystify how UNIX handles processes and to practice writing
clean, maintainable C. Most shells use heavily abbreviated variable names for
legacy reasons; ashew is an experiment in writing a shell that is easy to read
and understand.


## Made with some very big simplifications
aka:

```sh
ashew > cat "file name with spaces"
# This currently splits into:
# arg 1: "file
# arg 2: name
# arg 3: with
# arg 4: spaces"
```

## Limitations / future expansions:
- No piping
- No io redirecting
- No globbing
- naive input parsing using `strtok`:
    - commands have to be in one line
    - parsing only splits on whitespaces (no quotes or escaping)
- very few builtins
- No arrow support
- No signal handling
- No history
- Add child count
- Synchronous only (no & operator)

## Roadmap
- Implement '>' (dup2?)
- Ditch `strtok` and implement custom lexer
- history
- Implement '|'
