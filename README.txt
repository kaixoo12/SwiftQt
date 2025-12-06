+----------------+
| SwiftQt README |
+----------------+

SwiftQt by Zack T Smith
(zck twenty-two at mail dotcom)
-------------------------------------------------------------------------------

This is a project to get Swift working with the Qt GUI library to allow 
construction of conventional (imperative) GUIs.

It is not an attempt at producing an open-source equivalent to SwiftUI, 
which is the declarative GUI building system that Apple released aroun 2019,
nor is SwiftQT an attempt to create a Swift variant of QML, which is the
declarative GUI building system devised by Nokia around 2008.

SwiftQt has the purpose of helping me create personal apps on Linux with Qt 
using Swift instead of C++ or Python, which could be beneficial in some ways.

Who knows, perhaps someday SwiftQt will also allow creation of Swift GUI apps
on other platforms that Qt supports.

Is getting Swift to work with Qt easy? No, it consists of "wiring things up"
so that Swift talks to C, which talks to C++, and then in the opposite 
direction, for each of the classes and methods that would be useful.

Ultimately Swift C++ direct interoperation could be a better approach, if 
it ultimately provides all of the needed functionality with a syntax that is
readable.

This is a work in progress and still in the alpha stage of development.

+-----------+
| COMPILING |
+-----------+

What you will need:

* The 5.9 or better Swift compiler.
* Qt 5, with all its packages.
	-> On Debian, you'd type: sudo apt install "qt5*" "libqt5*"
* C++ compiler, make.

This code currently works fine on the Raspberry Pi 4 with 8GB of RAM,
when running the latest Raspberry Pi OS 64-bit (a variant of Debian).

To build:
1. ./configure
2. make 

This will build sampleGridLayoutApp.

+---------+
|  TO DO  |
+---------+

* Need more Qt classes in Swift.
	- QTabWidget
	- QFileDialog
	- QTimer
	- QDateTime
	- Qt OpenGL
	- Video and audio playback support.
* Move all SwiftQt classes into subdirectory.
* Refactor QDate.

