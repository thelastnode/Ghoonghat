HEADERS += light.hpp \
    point.hpp \
    gesturerecognizer.hpp \
    gesture.hpp \
    pointhandler.hpp \
    constants.hpp \
    cvpointhandler.hpp \
    deprecated.hpp \
    executor.hpp
SOURCES += light.cpp \
    point.cpp \
    gesturerecognizer.cpp \
    gesture.cpp \
    main.cpp \
    pointhandler.cpp \
    cvpointhandler.cpp \
    executor.cpp
CFLAGS += -I/usr/include/opencv
LIBS += -lcxcore \
    -lcv \
    -lhighgui \
    -lcvaux \
    -lml
