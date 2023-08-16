OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=./bin
MODEL_BIN1 = ./bin/a2-model-rider
MODEL_BIN2 = ./bin/a2-model-bike
MODEL_BIN3 = ./bin/a2-model-track
SRCS1=./src/rider/model_rider.cpp ./src/rider/rider_gl_framework.cpp ./src/rider/shader_util.cpp ./src/rider/hierarchy_node.cpp
SRCS2=./src/bike/model_bike.cpp ./src/bike/bike_gl_framework.cpp ./src/bike/shader_util.cpp ./src/bike/hierarchy_node.cpp
SRCS3=./src/track/model_track.cpp ./src/track/track_gl_framework.cpp ./src/track/shader_util.cpp ./src/track/hierarchy_node.cpp
INCLUDES1=./src/rider/rider_gl_framework.hpp ./src/rider/shader_util.hpp ./src/rider/model_rider.hpp ./src/rider/hierarchy_node.hpp
INCLUDES2=./src/bike/bike_gl_framework.hpp ./src/bike/shader_util.hpp ./src/bike/model_bike.hpp ./src/bike/hierarchy_node.hpp  
INCLUDES3=./src/track/track_gl_framework.hpp ./src/track/shader_util.hpp ./src/track/model_track.hpp ./src/track/hierarchy_node.hpp 

all: $(MODEL_BIN1) $(MODEL_BIN2) $(MODEL_BIN3)

$(shell mkdir -p $(BIN))

$(MODEL_BIN1): $(SRCS1) $(INCLUDES1)
	g++ $(CPPFLAGS) $(SRCS1) -o $(MODEL_BIN1) $(LDFLAGS) $(LIBS)
	
$(MODEL_BIN2): $(SRCS2) $(INCLUDES2)
	g++ $(CPPFLAGS) $(SRCS2) -o $(MODEL_BIN2) $(LDFLAGS) $(LIBS)

$(MODEL_BIN3): $(SRCS3) $(INCLUDES3)
	g++ $(CPPFLAGS) $(SRCS3) -o $(MODEL_BIN3) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(MODEL_BIN1) $(MODEL_BIN2) $(MODEL_BIN3)
	rmdir $(BIN)
