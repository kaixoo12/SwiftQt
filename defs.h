//=========================================================================
// This file is part of SwiftQt.
// (C) 2023-2024 Zack T Smith.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// The author may be reached at zck22 at mail dotcom.
//=========================================================================
//
// SwiftQt
// defs.h
// Qt-based UI library for Swift desktop applications on Linux, BSD, Windows.
// 
//------------
// CHANGE LOG 
//------------
// 0.1 	Basic structure
// 0.2 	C Conduit routines; Swift calls them to talk with C++ code.
// 0.3 	C++ CallPropagator, C++ calls to Swift via bridge.
// 0.4 	Sample app which calls Conduit routines.
// 0.5 	Creation of Swift object stand-ins for Qt objects.
// 0.6 	Added processEvent to widgets.
// 0.7 	Added Swift QObject class.
// 0.8 	Added closures for some push button events.
// 0.9 	Added closures for some text edit events.
// 0.10	Work on QMenuBar, QMenu, QAction.
// 0.11	Added some of QTableWidget & supporting classes.
// 0.12	More QTableWidget & QTableWidgetItem support.
// 0.13	QTableWidget vertical & horizontal headers.
// 0.14	SwiftQt class convenience functions. Code cleanup.
// 0.15	Basic QImage & QPixel support. More QLabel methods.
// 0.16	QAbstractButton, QRadioButton, QCheckBox.
// 0.17	QLayout, QBoxLayout, QVBoxLayout, QHBoxLayout, sampleBoxLayoutApp.
// 0.18	QKeySequence, QGridLayout, QCalendarWidget, QDate, QLCDNumber.
// 0.19	QAbstractSlider, QSlider
// 0.20	Updated for Qt 6 and Swift 5.9.2.
// 0.21	Downgrade to Qt 5. 

#define kKitName "SwiftQt"
#define kKitVersion "0.21"

