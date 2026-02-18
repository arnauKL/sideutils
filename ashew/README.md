# ashew: a tiny shell

I'd like this to be an actual usable shell that has sane variable names and
performs decently.

This is also an excuse to learn more C + UNIX.

- [reference article](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [POSIX headers](https://pubs.opengroup.org/onlinepubs/9699919799/)

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

## Future expansions:
- [ ] Piping
- [ ] io redirecting
- [ ] Globbing
- [ ] Better input parsing than using naive `strtok`
    - [ ] Multi line commands
    - [ ] Parse more than just whitespaces
- [ ] More builtins
- [ ] History
    - [ ] Arrow-key support
- [ ] Add child count
- [ ] Asynchronous (& operator)
- [x] Signal handling (readline)

## Roadmap
- Implement '>' (dup2?)
- Ditch `strtok` and implement custom lexer
- history
- Implement '|'
