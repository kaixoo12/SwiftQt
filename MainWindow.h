//=========================================================================
// This file is part of SwiftQt.
// (C) 2023 Zack T Smith.
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

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

extern "C" {
	#include <stdio.h>
	#include <math.h>
};

#include <QMainWindow>

#include "defs.h"
#include "graphics.h"

class MainWindow : public QMainWindow 
{
Q_OBJECT

public:
	MainWindow();
	virtual ~MainWindow();

	WidgetID windowID;

private:
	void onQuit ();
	void closeEvent(QCloseEvent *event);
	void resizeEvent (QResizeEvent *event);

public slots:
};

#endif
