QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../controller/controller.cc \
    ../../model/cave/cave.cc \
    ../../model/maze/maze.cc \
    ../../model/maze/maze_from_file.cc \
    ../../model/maze/maze_generation.cc \
    main.cpp \
    view.cc

HEADERS += \
    ../../controller/controller.h \
    ../../helpers/matrix.h \
    ../../model/cave/cave.h \
    ../../model/maze/maze.h \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
  ../../model/cave/cave1.txt \
  ../../model/cave/cave2.txt \
  ../../model/cave/cave3.txt
