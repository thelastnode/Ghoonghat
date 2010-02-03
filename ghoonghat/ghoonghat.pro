HEADERS += light.hpp \
    point.hpp \
    gesturerecognizer.hpp \
    gesture.hpp \
    pointhandler.hpp \
    constants.hpp
SOURCES += light.cpp \
    point.cpp \
    gesturerecognizer.cpp \
    gesture.cpp \
    main.cpp \
    pointhandler.cpp
CFLAGS += -I/usr/include/opencv
LIBS += -lcxcore -lcv -lhighgui -lcvaux -lml
