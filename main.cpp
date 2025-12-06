/*=========================================================================
 * This file is part of SwiftQt.
 * (C) 2023 Zack T Smith.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * The author may be reached at zck22 at mail dotcom.
 *=======================================================================*/

#include <stdio.h>
#include <string>

#include <QApplication>
#include <QScreen>
#include <QSettings>
#include <QIcon>

#include "defs.h"
#include "MainWindow.h"
#include "qt-c++.h"

extern "C" {
	#include "graphics.h"
	#include "bridging.h"
}

extern void ensure_call_propagator_exists(); // in qt.cpp

QApplication* app = nullptr;

int main (int argc, char **argv)
{
	ensure_call_propagator_exists();

	app = new QApplication(argc, argv);

	//QPixmap pixmap(icon48x48);
	//QIcon icon(pixmap);
	//app->setWindowIcon (icon);

        QScreen *screen = QGuiApplication::primaryScreen();
	int dpi = screen->logicalDotsPerInch();
	printf ("Screen DPI is %d\n", dpi);

	char *scale = getenv("QT_SCALE_FACTOR");
	if (scale) {
		float scaleFactor = atof(scale);
		if (scaleFactor > 0.f) {
			printf ("Screen scale factor is %.1f\n", atof(scale));
		}
	}

        QRect rect = screen->availableVirtualGeometry();
	int screenWidth = rect.size().width();
	int screenHeight = rect.size().height();
	printf ("Screen available area is %dx%d\n", screenWidth, screenHeight);

	// NOTE: The Swift code will construct the UI, including the window and menus.

	Event event;
	event.type = EventTypeAppLaunched;
	event.recipient = -1;
	event.argc = argc;
	event.argv = (const char**) argv;
	swiftEventHandler (event);

	int nWindows = Conduit_totalWindows();
	printf ("nWindows %d\n", nWindows);

	puts ("Entering GUI main loop...");
	return app->exec();
}

