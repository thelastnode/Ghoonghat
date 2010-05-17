OUT = ../ghoonghat
SRCS = cvpointhandler.cpp executor.cpp gesture.cpp gesturerecognizer.cpp light.cpp main.cpp point.cpp pointhandler.cpp
OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -I/usr/include/opencv  
LDFLAGS = -lcv -lhighgui -lcvaux -lml -lcxcore  

all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OUT) $(OBJS)
