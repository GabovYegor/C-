TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x -pthread -lboost_thread -lboost_chrono
LIBS += -pthread -lboost_thread -lboost_chrono
SOURCES += main.cpp
