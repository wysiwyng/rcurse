put pdcurses libraries here:

for windows:

- get pdc34dllw.zip from http://sourceforge.net/projects/pdcurses/files/pdcurses/3.4/
- put everything from that zip in win32 folder

for sdl(linux only atm):

- get PDCurses-3.4.tar.gz from http://sourceforge.net/projects/pdcurses/files/pdcurses/3.4/
- extract somewhere
- enter sdl1 folder and run 'make DEBUG=Y'
- rename resulting file libpdcurses.a to libpdcurses_d.a and move to sdl folder
- run 'make clean'
- run 'make' and move resulting lipdcurses.a file to sdl folder
- copy files curses.h and panel.h from pdcurses source folder to sdl folder