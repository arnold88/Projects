# 
# $Id: qthello.pro,v 1.1.1.1 2000/08/06 10:21:10 amos Exp $
#
# TMake project file for QtHello
#
# Jan Borsodi <jb@ez.no>
# Created on: <06-Oct-1999 19:13:55 amos>
#
# Copyright (C) 1999-2000 Jan Borsodi.
#

PROJECT			= QtHello
CONFIG			= warn_on debug qt

OBJECTS_DIR		= obj
MOC_DIR			= moc

#TMAKE_CXXFLAGS		+= -O2

HEADERS			= \
			piece.hpp \
			matrix.hpp \
			exception.hpp \
			player.hpp \
			board.hpp \
			boardwidget.hpp \
			othello.hpp \
			brain.hpp \
			humanbrain.hpp \
			computerbrain.hpp \
			randomcomputer.hpp \
			playerinfo.hpp \
			humanconfig.hpp \
			firstbestcomputer.hpp \
			computerconfig.hpp \
			playerprofile.hpp \
			playerlist.hpp \
			weights.hpp \
			alphabetanormalcomputer.hpp \
			alphabetaevalcomputer.hpp \
			alphabetadyncomputer.hpp \
			alphabetacomputer.hpp

SOURCES			= \
			  main.cpp \
			  piece.cpp \
			  matrix.cpp \
			  player.cpp \
			  board.cpp \
			  boardwidget.cpp \
			  othello.cpp \
			  brain.cpp \
			  humanbrain.cpp \
			  computerbrain.cpp \
			  randomcomputer.cpp \
			  playerinfo.cpp \
			  humanconfig.cpp \
			  firstbestcomputer.cpp \
			  computerconfig.cpp \
			  playerprofile.cpp \
			  playerlist.cpp \
			  alphabetanormalcomputer.cpp \
			  alphabetaevalcomputer.cpp \
			  alphabetadyncomputer.cpp \
			  alphabetacomputer.cpp

TARGET			= qthello
