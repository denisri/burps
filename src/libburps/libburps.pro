TEMPLATE	= lib
CONFIG		= qt
TARGET		= burps

#!include ../../config

HEADERS = \
	gui/bwin.h \
	gui/locwin.h \
        math/documentation.h \
	math/table.h \
	math/logTable.h \
	math/gaussTable.h \
	math/sigmoTable.h \
	math/orTable.h \
	math/localization.h 

SOURCES = \
	gui/bwin.cc \
	gui/locwin.cc \
	math/table.cc \
	math/logTable.cc \
	math/gaussTable.cc \
	math/sigmoTable.cc \
	math/orTable.cc \
	math/localization.cc
