# rcurse
roguelike (pd)curses game thingy

building
--------

1. clone repo (in eclipse preferrably)
2. import into eclipse by doing file -> import -> existing project (if not cloned into eclipse right away)
3. select build config, debug-linux / release-linux work as-is if you have the curses development headers installed
4. for other configs follow instructions in pdcurses folder
5. hit build all (ctrl + b)
6. open console, navigate to build directory
7. run by typing ./rcurse
8. menu is operated by arrow keys, movement with w a s d
9. ???
10. profit!
11. develop ai

windows build
-------------

windows builds are done by the msvc compiler, eclipse must be run from the microsoft developer console to set environment variables accordingly (google for more info)
