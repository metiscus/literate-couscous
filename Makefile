CXX := g++
CXXFLAGS := -g -Wall -Wextra -std=c++17 -MD
LDFLAGS := -L.

JSON_CFLAGS := -Iextern/StaticJSON/include -Iextern/rapidjson/include
CXXFLAGS += $(JSON_CFLAGS)

default: test

libStaticJson.a: extern/StaticJSON/src/staticjson.o
	ar -rcs libStaticJson.a extern/StaticJSON/src/staticjson.o

SRC:=\
	src/character.cpp\
	src/inventory.cpp\
	src/object.cpp\
	src/physicalcomponent.cpp\
	src/test.cpp\
	src/submap.cpp\
	src/map.cpp\

OBJ:=$(SRC:.cpp=.o)

test: $(SRC) $(OBJ) libStaticJson.a
	$(CXX) $(CXXFLAGS) $(JSON_CFLAGS) -o test $(OBJ) $(LDFLAGS) -lStaticJson

clean:
	-rm -f $(OBJ) $(OBJ:.o=.d)
	-rm -f libStaticJson.a extern/StaticJSON/src/staticjson.o extern/StaticJSON/src/staticjson.d

-include $(OBJ:.o=.d)