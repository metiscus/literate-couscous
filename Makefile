CXX := g++
CFLAGS := -Iextern/glad/include
CXXFLAGS := -g -Wall -Wextra -std=c++17 -MD
LDFLAGS := -L. -lboost_system -lboost_filesystem

# StaticJSON
JSON_CFLAGS := -Iextern/StaticJSON/include -Iextern/rapidjson/include
JSON_LIBS := -lStaticJson

#SFML
SMFL_CFLAGS := $(shell pkg-config --cflags sfml-system sfml-window sfml-graphics)
SMFL_LIBS   := $(shell pkg-config --libs sfml-system sfml-window sfml-graphics)

# All libraries
CXXFLAGS += $(JSON_CFLAGS) $(SMFL_CFLAGS) -Isrc -Iextern/nuklear -Iextern/glad/include
LDFLAGS += $(JSON_LIBS) $(SMFL_LIBS)

default: test

# StaticJSON Library
libStaticJson.a: extern/StaticJSON/src/staticjson.o
	ar -rcs libStaticJson.a extern/StaticJSON/src/staticjson.o

# LibNuklear
libNuklear.a: extern/nuklear/nuklear.o
	ar -rcs libNuklear.a extern/nuklear/nuklear.o

# LibGLAD
libGlad.a: extern/glad/src/glad.o
	ar -rcs libGlad.a extern/glad/src/glad.o

SRC:=\
	src/character.cpp\
	src/inventory.cpp\
	src/object.cpp\
	src/physicalcomponent.cpp\
	src/test.cpp\
	src/maptile.cpp\
	src/map.cpp\
	src/game.cpp\
	src/gamestate.cpp\
	src/texturemanager.cpp\
	src/simtime.cpp\
	src/stage.cpp\
	src/weather.cpp\
	src/ui/ui.cpp\
	src/ui/layout.cpp\
	src/ui/window.cpp\
	src/mainmenustate.cpp\
	src/newgamestate.cpp\

OBJ:=$(SRC:.cpp=.o)

test: $(SRC) $(OBJ) libStaticJson.a libNuklear.a libGlad.a
	$(CXX) $(CXXFLAGS) $(JSON_CFLAGS) -o test $(OBJ) $(LDFLAGS) -lStaticJson -lNuklear -lGlad -lGL -ldl

clean:
	-rm -f $(OBJ) $(OBJ:.o=.d)
	-rm -f libStaticJson.a extern/StaticJSON/src/staticjson.o extern/StaticJSON/src/staticjson.d
	-rm -f libNuklear.a extern/nuklear/nuklear.o extern/nuklear/nuklear.d
	-rm -f libGlad.a extern/glad/src/glad.o extern/glad/src/glad.d

-include $(OBJ:.o=.d)