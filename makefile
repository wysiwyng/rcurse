CPP_SRCS += \
./src/Action.cpp \
./src/Actionbar.cpp \
./src/Character.cpp \
./src/Defs.cpp \
./src/Game.cpp \
./src/GameWindow.cpp \
./src/Hud.cpp \
./src/Loot.cpp \
./src/Map.cpp \
./src/PerlinNoise.cpp \
./src/Serializer.cpp \
./src/Statusbar.cpp \
./src/Timer.cpp \
./src/TimerListener.cpp \
./src/main.cpp \
./pugixml/src/pugixml.cpp

OBJS_DEBUG += \
./debug-linux/src/Action.o \
./debug-linux/src/Actionbar.o \
./debug-linux/src/Character.o \
./debug-linux/src/Defs.o \
./debug-linux/src/Game.o \
./debug-linux/src/GameWindow.o \
./debug-linux/src/Hud.o \
./debug-linux/src/Loot.o \
./debug-linux/src/Map.o \
./debug-linux/src/PerlinNoise.o \
./debug-linux/src/Serializer.o \
./debug-linux/src/Statusbar.o \
./debug-linux/src/Timer.o \
./debug-linux/src/TimerListener.o \
./debug-linux/src/main.o \
./debug-linux/pugixml/src/pugixml.o

OBJS_RELEASE += \
./release-linux/src/Action.o \
./release-linux/src/Actionbar.o \
./release-linux/src/Character.o \
./release-linux/src/Defs.o \
./release-linux/src/Game.o \
./release-linux/src/GameWindow.o \
./release-linux/src/Hud.o \
./release-linux/src/Loot.o \
./release-linux/src/Map.o \
./release-linux/src/PerlinNoise.o \
./release-linux/src/Serializer.o \
./release-linux/src/Statusbar.o \
./release-linux/src/Timer.o \
./release-linux/src/TimerListener.o \
./release-linux/src/main.o \
./release-linux/pugixml/src/pugixml.o

OBJS_DEBUG_SDL += \
./debug-sdl/src/Action.o \
./debug-sdl/src/Actionbar.o \
./debug-sdl/src/Character.o \
./debug-sdl/src/Defs.o \
./debug-sdl/src/Game.o \
./debug-sdl/src/GameWindow.o \
./debug-sdl/src/Hud.o \
./debug-sdl/src/Loot.o \
./debug-sdl/src/Map.o \
./debug-sdl/src/PerlinNoise.o \
./debug-sdl/src/Serializer.o \
./debug-sdl/src/Statusbar.o \
./debug-sdl/src/Timer.o \
./debug-sdl/src/TimerListener.o \
./debug-sdl/src/main.o \
./debug-sdl/pugixml/src/pugixml.o

OBJS_RELEASE_SDL += \
./release-sdl/src/Action.o \
./release-sdl/src/Actionbar.o \
./release-sdl/src/Character.o \
./release-sdl/src/Defs.o \
./release-sdl/src/Game.o \
./release-sdl/src/GameWindow.o \
./release-sdl/src/Hud.o \
./release-sdl/src/Loot.o \
./release-sdl/src/Map.o \
./release-sdl/src/PerlinNoise.o \
./release-sdl/src/Serializer.o \
./release-sdl/src/Statusbar.o \
./release-sdl/src/Timer.o \
./release-sdl/src/TimerListener.o \
./release-sdl/src/main.o \
./release-sdl/pugixml/src/pugixml.o

LIBS := -lncurses -lpthread
LIBS_SDL_DBG := -lpdcurses_d -lSDL -lpthread
LIBS_SDL := -lpdcurses -lSDL -lpthread

all: debug-linux release-linux debug-sdl release-sdl

debug-sdl: debug-dirs-sdl $(OBJS_DEBUG_SDL)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++	 -o "./debug-linux/rcurse" -L"./pdcurses/sdl" $(OBJS_DEBUG) $(LIBS_SDL_DBG)
	@echo 'Finished building target: $@'
	@echo ' '

release-sdl: release-dirs-sdl $(OBJS_RELEASE_SDL)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++	 -o "./release-linux/rcurse" -L"./pdcurses/sdl" $(OBJS_RELEASE) $(LIBS_SDL)
	@echo 'Finished building target: $@'
	@echo ' '

debug-linux: debug-dirs $(OBJS_DEBUG)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++	 -o "./debug-linux/rcurse" $(OBJS_DEBUG) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

release-linux: release-dirs $(OBJS_RELEASE)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++	 -o "./release-linux/rcurse" $(OBJS_RELEASE) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

debug-linux/src/%.o: ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

debug-linux/pugixml/src/%.o: ./pugixml/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

release-linux/src/%.o: ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -O3 -g0 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

release-linux/pugixml/src/%.o: ./pugixml/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -O3 -g0 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

debug-sdl/src/%.o: ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -I"./pdcurses/sdl" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

debug-sdl/pugixml/src/%.o: ./pugixml/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -I"./pdcurses/sdl" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

release-sdl/src/%.o: ./src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -I"./pdcurses/sdl" -O3 -g0 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

release-sdl/pugixml/src/%.o: ./pugixml/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"./pugixml/src" -I"./pdcurses/sdl" -O3 -g0 -Wall -c -fmessage-length=0 -std=c++11 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

release-dirs:
	mkdir -p release-linux/src
	mkdir -p release-linux/pugixml/src

debug-dirs:
	mkdir -p debug-linux/src
	mkdir -p debug-linux/pugixml/src

release-dirs-sdl:
	mkdir -p release-sdl/src
	mkdir -p release-sdl/pugixml/src

debug-dirs-sdl:
	mkdir -p debug-sdl/src
	mkdir -p debug-sdl/pugixml/src

clean:
	rm -rf ./release-linux ./debug-linux

.PHONY: clean all debug-dirs release-dirs
