#=========================================================================
# This file is part of SwiftQt.
# (C) 2023 Zack T Smith.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# The author may be reached at zck22 at mail dotcom.
#=========================================================================
#
# Makefile
# SwiftQt
# 

include Makefile-config

#------------------------------------------------------------------------------
SWIFT_SOURCES=	QObject.swift QWidget.swift QColor.swift QKeySequence.swift \
		QMainWindow.swift QStatusBar.swift QMenu.swift QAction.swift QMenuBar.swift \
		QImage.swift QPixmap.swift \
		QLabel.swift QScrollBar.swift QGroupBox.swift \
		QAbstractButton.swift QCheckBox.swift QPushButton.swift QRadioButton.swift \
		QTextEdit.swift QLineEdit.swift \
		QWebEngineView.swift \
		QTableWidget.swift QTableWidgetItem.swift \
		QLayout.swift QBoxLayout.swift QHBoxLayout.swift QVBoxLayout.swift QGridLayout.swift \
		Qt.swift SwiftQt.swift bridging.swift QApplication.swift ApplicationDelegate.swift \
		QCalendarWidget.swift QDate.swift QLCDNumber.swift \
		QAbstractSlider.swift QSlider.swift

CPP_OBJS=main.o MainWindow.o graphics.o qt.o 

CPP_INC=-I. \
-I${QT_INC} \
-I${QT_INC}/QtCore \
-I${QT_INC}/QtGui \
-I${QT_INC}/QtNetwork \
-I${QT_INC}/QtPositioning \
-I${QT_INC}/QtPrintSupport \
-I${QT_INC}/QtQml \
-I${QT_INC}/QtQmlModels \
-I${QT_INC}/QtQuick \
-I${QT_INC}/QtWebChannel \
-I${QT_INC}/QtWebEngine \
-I${QT_INC}/QtWebEngineCore \
-I${QT_INC}/QtWebEngineWidgets \
-I${QT_INC}/QtWebKit \
-I${QT_INC}/QtWebKitWidgets \
-I${QT_INC}/QtWidgets

QT_LIBS= \
${QT_LIB}/../libQt5Core.so \
${QT_LIB}/../libQt5Gui.so \
${QT_LIB}/../libQt5Network.so \
${QT_LIB}/../libQt5Positioning.so \
${QT_LIB}/../libQt5PrintSupport.so \
${QT_LIB}/../libQt5Quick.so \
${QT_LIB}/../libQt5WebChannel.so \
${QT_LIB}/../libQt5WebEngine.so \
${QT_LIB}/../libQt5WebEngineCore.so \
${QT_LIB}/../libQt5WebEngineWidgets.so \
${QT_LIB}/../libQt5WebKit.so \
${QT_LIB}/../libQt5WebKitWidgets.so \
${QT_LIB}/../libQt5Widgets.so \
-lpthread -lstdc++ 

MOC_OBJS=moc_MainWindow.o moc_qt.o

EXE1=sampleManualLayoutApp
SRC1=sampleManualLayoutApp.swift

EXE2=sampleBoxLayoutApp
SRC2=sampleBoxLayoutApp.swift

EXE3=sampleGridLayoutApp
SRC3=sampleGridLayoutApp.swift

${EXE3}:	mocfiles ${SWIFT_SOURCES} ${SRC3} ${CPP_OBJS}
	swiftc -v -o ${EXE3} -import-objc-header bridging.h ${SRC3} ${SWIFT_SOURCES} -L${QT_LIB}/ ${QT_LIBS} ${MOC_OBJS} ${CPP_OBJS} 

${EXE2}:	mocfiles ${SWIFT_SOURCES} ${SRC2} ${CPP_OBJS}
	swiftc -v -o ${EXE2} -import-objc-header bridging.h ${SRC2} ${SWIFT_SOURCES} -L${QT_LIB}/ ${QT_LIBS} ${MOC_OBJS} ${CPP_OBJS} 

${EXE1}:	mocfiles ${SWIFT_SOURCES} ${SRC1} ${CPP_OBJS}
	swiftc -v -o ${EXE1} -import-objc-header bridging.h ${SRC1} ${SWIFT_SOURCES} -L${QT_LIB}/ ${QT_LIBS} ${MOC_OBJS} ${CPP_OBJS} 

# For verbose link use: swiftc -v -Xlinker --verbose 

graphics.o:	graphics.c
	clang -c -O2 -fPIC -Wall -Wextra graphics.c -o graphics.o

qt.o:	qt.cpp
	clang -c -g -O2 -std=c++17 -Wall -Wextra -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB ${CPP_INC} -o qt.o qt.cpp

main.o:	main.cpp
	clang -c -g -O2 -std=c++17 -Wall -Wextra -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB ${CPP_INC} -o main.o main.cpp

MainWindow.o:	MainWindow.cpp
	clang -v -c -g -O2 -std=c++17 -Wall -Wextra -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB ${CPP_INC} -o MainWindow.o MainWindow.cpp

Makefile-config:
	./configure

clean:
	@rm -f ${CPP_OBJS} ${EXE1} ${EXE2} ${EXE3} ${MOC_OBJS} Makefile-config

mocfiles:
	clang -g -O2 -Wall -Wextra -dM -E -o moc_predefs.h ${QT_LIB}/mkspecs/features/data/dummy.cpp
	/usr/lib/qt5/bin/moc -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB --include moc_predefs.h -I${QT_LIB}/mkspecs/linux-g++ -I. -I${QT_INC} -I${QT_INC}/QtWidgets -I${QT_INC}/QtGui -I${QT_INC}/QtCore -I/usr/include/c++/10 -I/usr/include/aarch64-linux-gnu/c++/10 -I/usr/include/c++/10/backward -I/usr/lib/gcc/aarch64-linux-gnu/10/include -I/usr/local/include -I/usr/include/aarch64-linux-gnu -I/usr/include MainWindow.h -o moc_MainWindow.cpp
	clang -c -g -O2 -Wall -Wextra -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I${QT_INC} -I${QT_INC}/QtWidgets -I${QT_INC}/QtGui -I${QT_INC}/QtCore -I${QT_LIB}/mkspecs/linux-g++ -o moc_MainWindow.o moc_MainWindow.cpp
	/usr/lib/qt5/bin/moc -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB --include moc_predefs.h -I${QT_LIB}/mkspecs/linux-g++ -I. -I${QT_INC} -I${QT_INC}/QtWidgets -I${QT_INC}/QtGui -I${QT_INC}/QtCore -I/usr/include/c++/10 -I/usr/include/aarch64-linux-gnu/c++/10 -I/usr/include/c++/10/backward -I/usr/lib/gcc/aarch64-linux-gnu/10/include -I/usr/local/include -I/usr/include/aarch64-linux-gnu -I/usr/include qt-c++.h -o moc_qt.cpp
	clang -c -g -O2 -Wall -Wextra -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I${QT_INC} -I${QT_INC}/QtWidgets -I${QT_INC}/QtGui -I${QT_INC}/QtCore -I${QT_LIB}/mkspecs/linux-g++ -o moc_qt.o moc_qt.cpp

