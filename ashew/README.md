# ashew: a tiny shell

I'd like this to be an actual usable shell that has sane variable names and
performs decently.

This is also an excuse to learn more C + UNIX.

- [reference article](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [POSIX headers](https://pubs.opengroup.org/onlinepubs/9699919799/)

I started using the realine library.
It might be overkill.


## Future expansions:
- [ ] Piping
- [ ] io redirecting
- [ ] Globbing
- [ ] Better input parsing than using naive `strtok`
    - [ ] Multi line commands
    - [ ] Parse more than just whitespaces
- [ ] More builtins
- [x] History
    - [x] Arrow-key support
    - [ ] Write to file (reads but cannot write when quitting via C-c)
- [ ] Add child count
- [ ] Asynchronous (& operator)
- [x] Signal handling (readline)

## Roadmap
- Implement '>' (dup2?)
- Ditch `strtok` and implement custom lexer
- history
- Implement '|'
