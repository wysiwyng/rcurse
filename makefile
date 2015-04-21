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

LIBS := -lncurses -lpthread

all: debug-linux release-linux

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

release-dirs:
	mkdir release-linux
	mkdir release-linux/src
	mkdir release-linux/pugixml
	mkdir release-linux/pugixml/src

debug-dirs:
	mkdir debug-linux
	mkdir debug-linux/src
	mkdir debug-linux/pugixml
	mkdir debug-linux/pugixml/src

clean:
	rm -rf ./release-linux ./debug-linux
