QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/cave/cave.cc \
    ../model/maze/maze.cc \
    ../model/maze/creating/maze_from_file.cc \
    ../model/maze/creating/maze_generation.cc \
    ../model/maze/answer/maze_answer.cc \
    ../model/drawing/maze_drawing.cc \
    ../model/drawing/cave_drawing.cc \
    ../model/helpers/randomizer/generator.cc \
    ../main.cc \
    view.cc

HEADERS += \
    ../controller/controller.h \
    ../model/helpers/matrix.h \
    ../model/cave/cave.h \
    ../model/maze/maze.h \
    ../model/maze/answer/maze_answer.h \
    ../model/drawing/maze_drawing.h \
    ../model/drawing/cave_drawing.h \
    ../model/helpers/randomizer/generator.h \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = ../../build/
!isEmpty(target.path): INSTALLS += target


