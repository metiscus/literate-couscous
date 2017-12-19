CXX := g++
CXXFLAGS := -g -Wall -Wextra -std=c++11 -MD
LDFLAGS := -L.

JSON_CFLAGS := -Iextern/StaticJSON/include -Iextern/rapidjson/include
CXXFLAGS += $(JSON_CFLAGS)

default: test

libStaticJson.a: extern/StaticJSON/src/staticjson.o
	ar -rcs libStaticJson.a extern/StaticJSON/src/staticjson.o
	rm -f extern/StaticJSON/src/staticjson.o


SRC:=\
	src/object.cpp\
	src/component.cpp\
	src/physicalcomponent.cpp

OBJ:=$(SRC:.cpp=.o)

test: $(SRC) $(OBJ) libStaticJson.a
	$(CXX) $(CXXFLAGS) $(JSON_CFLAGS) -o test $(OBJ) $(LDFLAGS) -lStaticJson

clean:
	-rm -f $(OBJ) $(OBJ:.o=.d)
	-rm -f libStaticJson.a extern/StaticJSON/src/staticjson.o extern/StaticJSON/src/staticjson.d

-include $(OBJ:.o=.d)