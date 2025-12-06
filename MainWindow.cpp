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

#include <QApplication>
#include <QResizeEvent>
#include <QDebug>

extern "C" {
	#include <stdio.h>
	#include "bridging.h"
};

#include "defs.h"
#include "MainWindow.h"

extern QApplication* app;

//----------------------------------------------------------------------------
// Name:	MainWindow 
// Purpose:	Constructor, initializes new object.
// Returns:	MainWindow object
//----------------------------------------------------------------------------
MainWindow::MainWindow ()
{
	windowID = -1; // Not yet set.
}

//----------------------------------------------------------------------------
// Name:	~MainWindow  
// Purpose:	Destructor.
//----------------------------------------------------------------------------
MainWindow::~MainWindow ()
{
}

//----------------------------------------------------------------------------
// Name:	resizeEvent
// Purpose:	Callback for when window is resized.
//----------------------------------------------------------------------------
void MainWindow::resizeEvent (QResizeEvent *resizeEvent) 
{
	if (!resizeEvent) {
		return;
	}

	Event event;
	event.type = EventTypeWindowResized;
	event.x = resizeEvent->size().width();
	event.y = resizeEvent->size().height();
	event.recipient = windowID;
	swiftEventHandler (event);
}

//----------------------------------------------------------------------------
// Name:	onQuit
// Purpose:	Lets the user quit the app, saving first.
//----------------------------------------------------------------------------
void MainWindow::onQuit() 
{
	closeEvent(NULL);
	exit (0);
	//QApplication::quit();
}

//----------------------------------------------------------------------------
// Name:	closeEvent
// Purpose:	Callback for the window's close button, lets user save & quit.
//----------------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *qevent)
{
	if (qevent) {
		// Tell Swift code that a close event was received.
		Event event;
		event.recipient = -1;
		event.type = EventTypeWindowClosed;
		swiftEventHandler (event);

		// Tell Swift code that an app exit is happening.
		event.type = EventTypeAppExiting;
		swiftEventHandler (event);

		QWidget::closeEvent(qevent);
	}
}

