#
# Compiler flags
#

CXXFLAGS += -Wall -Wextra -std=c++11 -I../pugixml/src

#
# Project files
#
SRCS = Action.cpp \
Actionbar.cpp \
AIControl.cpp \
Character.cpp \
Defs.cpp \
Game.cpp \
GameWindow.cpp \
Hud.cpp \
Loot.cpp \
Map.cpp \
main.cpp \
PerlinNoise.cpp \
Projectile.cpp \
Serializer.cpp \
Statusbar.cpp \
Timer.cpp \
TimerListener.cpp \
../pugixml/src/pugixml.cpp

OBJS = $(SRCS:.cpp=.o)
EXE  = rcurse

#
# Debug build settings
#
DBGDIR = ../debug-linux
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/src/, $(OBJS))
DBGCFLAGS = -g3 -O0 
DBGLDFLAGS = -lncurses -lpthread

#
# Release build settings
#
RELDIR = ../release-linux
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/src/, $(OBJS))
RELCFLAGS = -O2 -g0
RELLDFLAGS = -lncurses -lpthread

#
# SDL Debug build settings
#
SDLDBGDIR = ../debug-sdl
SDLDBGEXE = $(SDLDBGDIR)/$(EXE)
SDLDBGOBJS = $(addprefix $(SDLDBGDIR)/src/, $(OBJS))
SDLDBGCFLAGS = -g3 -O0 -DSDL -I../pdcurses/sdl
SDLDBGLDFLAGS = -L../pdcurses/sdl -lX11 -lSDL -lpdcurses_d -lpthread

#
# SDL Release build settings
#
SDLRELDIR = ../release-sdl
SDLRELEXE = $(SDLRELDIR)/$(EXE)
SDLRELOBJS = $(addprefix $(SDLRELDIR)/src/, $(OBJS))
SDLRELCFLAGS = -g0 -O2 -DSDL -I../pdcurses/sdl
SDLRELLDFLAGS = -L../pdcurses/sdl -lX11 -lSDL -lpdcurses -lpthread

.PHONY: all clean debug prep release remake debug-linux debug-sdl release-linux release-sdl

# Default build
all: debug release
debug: debug-linux debug-sdl
release: release-linux release-sdl

#
# Debug rules
#
debug-linux: prep $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	@echo ' [LD] $(DBGEXE)'	
	@$(CXX) -o $(DBGEXE) $^ $(DBGLDFLAGS)

$(DBGDIR)/src/%.o: %.cpp
	@echo ' [CXX] $<'
	@$(CXX) -c $(CXXFLAGS) $(DBGCFLAGS) -o $@ $<

#
# Release rules
#
release-linux: prep $(RELEXE)

$(RELEXE): $(RELOBJS)
	@echo ' [LD] $(RELEXE)'	
	@$(CXX) -o $(RELEXE) $^ $(RELLDFLAGS)

$(RELDIR)/src/%.o: %.cpp
	@echo ' [CXX] $<'
	@$(CXX) -c $(CXXFLAGS) $(RELCFLAGS) -o $@ $<

#
# SDL Debug rules
#
debug-sdl: prep $(SDLDBGEXE)

$(SDLDBGEXE): $(SDLDBGOBJS)
	@echo ' [LD] $(SDLDBGEXE)'	
	@$(CXX) -o $(SDLDBGEXE) $^ $(SDLDBGLDFLAGS)

$(SDLDBGDIR)/src/%.o: %.cpp
	@echo ' [CXX] $<'
	@$(CXX) -c $(CXXFLAGS) $(SDLDBGCFLAGS) -o $@ $<

#
# SDL Release rules
#
release-sdl: prep $(SDLRELEXE)

$(SDLRELEXE): $(SDLRELOBJS)
	@echo ' [LD] $(SDLRELEXE)'	
	@$(CXX) -o $(SDLRELEXE) $^ $(SDLRELLDFLAGS)

$(SDLRELDIR)/src/%.o: %.cpp
	@echo ' [CXX] $<'
	@$(CXX) -c $(CXXFLAGS) $(SDLRELCFLAGS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR)/src $(DBGDIR)/pugixml/src $(RELDIR)/src $(RELDIR)/pugixml/src
	@mkdir -p $(SDLDBGDIR)/src $(SDLDBGDIR)/pugixml/src $(SDLRELDIR)/src $(SDLRELDIR)/pugixml/src

remake: clean all

clean:
	rm -rf $(RELDIR) $(DBGDIR) $(SDLRELDIR) $(SDLDBGDIR)


