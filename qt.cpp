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

//=============================================================================
// The bridging header file is required to be C code only. Therefore any calls
// to Qt, have to go through C middleman functions, which I call the Conduit
// in the C code and CallPropagator in C++.
// Messages from Qt to Swift code go through the bridge's swiftEventHandler.
//=============================================================================

#include <QtGlobal>
#include <QApplication>
#include <QCheckBox>
#include <QColor>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QRadioButton>
#include <QStatusBar>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QGroupBox>
#include <QCalendarWidget>
#include <QLCDNumber>
#include <QSlider>

#include "MainWindow.h"
#include "qt-c++.h"

extern "C" {
        #include <stdio.h>
        #include "bridging.h"
};

static CallPropagator *sharedCallPropagator = NULL;

extern "C" {
	// QSlider
	WidgetID Conduit_createSlider (WidgetID parentID);
	long Conduit_sliderTickPosition (WidgetID);
	long Conduit_sliderTickInterval (WidgetID);
	void Conduit_sliderSetTickPosition (WidgetID, long);
	void Conduit_sliderSetTickInterval (WidgetID, long);

	// QAbstractSlider
	void Conduit_abstractSliderSetMaximum (WidgetID, long maximum);
	void Conduit_abstractSliderSetMinimum (WidgetID, long minimum);
	void Conduit_abstractSliderSetPageStep (WidgetID, long pageStep);
	void Conduit_abstractSliderSetValue (WidgetID, long value);
	void Conduit_abstractSliderSetSliderDown (WidgetID, bool value);
	bool Conduit_abstractSliderIsSliderDown(WidgetID);
	long Conduit_abstractSliderMaximum (WidgetID);
	long Conduit_abstractSliderMinimum (WidgetID);
	long Conduit_abstractSliderPageStep (WidgetID);
	long Conduit_abstractSliderValue (WidgetID);
	long Conduit_abstractSliderOrientation (WidgetID);
	void Conduit_abstractSliderSetOrientation (WidgetID,long);

	// QDate
	DateID Conduit_createDate (long,long,long);
	DateID Conduit_createCurrentDate ();
	long Conduit_dateDay (DateID);
	long Conduit_dateMonth (DateID);
	long Conduit_dateYear (DateID);

	// QCalendarWidget
	WidgetID Conduit_createCalendarWidget (WidgetID);
	void Conduit_calendarWidgetClearMaximumDate(WidgetID);
	void Conduit_calendarWidgetClearMinimumDate(WidgetID);
	long Conduit_calendarWidgetMonthShown(WidgetID);
	long Conduit_calendarWidgetYearShown(WidgetID);
	long Conduit_calendarWidgetHorizontalHeaderFormat(WidgetID);
	long Conduit_calendarWidgetVerticalHeaderFormat(WidgetID);
	void Conduit_calendarWidgetSetHorizontalHeaderFormat(WidgetID,long);
	void Conduit_calendarWidgetSetVerticalHeaderFormat(WidgetID,long);
	long Conduit_calendarWidgetFirstDayOfWeek(WidgetID);
	void Conduit_calendarWidgetSetFirstDayOfWeek(WidgetID, long);
	long Conduit_calendarWidgetSelectedDate(WidgetID);

	// QLayout
	void Conduit_layoutAddWidget (ObjectID, WidgetID);
	void Conduit_layoutRemoveWidget (ObjectID, WidgetID);
	long Conduit_layoutSpacing (ObjectID);
	void Conduit_layoutSetSpacing (ObjectID, long);

	// QGridLayout
	ObjectID Conduit_createGridLayout (WidgetID);
	void Conduit_gridLayoutAddWidget(ObjectID,WidgetID,long row,long column,long alignment);
	void Conduit_gridLayoutAddWidgetWithSpans(ObjectID,WidgetID,long row,long column,long rowspan,long colspan,long alignment);
	Rect Conduit_gridLayoutCellRect(ObjectID,long,long);
	long Conduit_gridLayoutColumnCount(ObjectID);
	long Conduit_gridLayoutColumnMinimumWidth(ObjectID,long);
	long Conduit_gridLayoutColumnStretch(ObjectID,long);
	long Conduit_gridLayoutHorizontalSpacing(ObjectID);
	long Conduit_gridLayoutRowMinimumHeight(ObjectID,long);
	long Conduit_gridLayoutRowStretch(ObjectID,long);
	long Conduit_gridLayoutRowCount (ObjectID layoutID);
	void Conduit_gridLayoutSetColumnMinimumWidth(ObjectID,long,long);
	void Conduit_gridLayoutSetColumnStretch(ObjectID,long,long);
	void Conduit_gridLayoutSetHorizontalSpacing(ObjectID,long);
	void Conduit_gridLayoutSetRowCount(ObjectID,long);
	void Conduit_gridLayoutSetRowMinimumHeight(ObjectID,long,long);
	void Conduit_gridLayoutSetRowStretch(ObjectID,long,long);
	void Conduit_gridLayoutSetVerticalSpacing(ObjectID,long);
	long Conduit_gridLayoutVerticalSpacing(ObjectID);

	// QBoxLayout
	ObjectID Conduit_createBoxLayout (ObjectID, long);
	void Conduit_boxLayoutAddWidget (ObjectID, WidgetID, long stretch, long alignment);
	void Conduit_boxLayoutAddSpacing (ObjectID, long);
	void Conduit_boxLayoutAddStretch (ObjectID, long);
	void Conduit_boxLayoutAddStrut (ObjectID, long);

	// QHBoxLayout
	ObjectID Conduit_createHBoxLayout (ObjectID);

	// QVBoxLayout
	ObjectID Conduit_createVBoxLayout (ObjectID);

	// QKeySequence
	ObjectID Conduit_createKeySequence (const char*);

	// QImage
	ObjectID Conduit_createImage(const char*path);
	bool Conduit_imageLoad (ObjectID objectID, const char *path);
	bool Conduit_imageIsGrayscale (ObjectID objectID);
	Coord Conduit_imageWidth (ObjectID objectID);
	Coord Conduit_imageHeight (ObjectID objectID);
	Coord Conduit_imageDepth (ObjectID objectID);

	// Convenience functions
	const char *Conduit_swiftQtRelease();
	bool Conduit_swiftQtIsDarkMode();
	void Conduit_swiftQtConveniencePopup(const char* title, const char* message);
	bool Conduit_swiftQtConvenienceQuestion(const char* title, const char* message);

	// QMainWindow
	WidgetID Conduit_createWindow (Coord x, Coord y, Coord width, Coord height);
	void Conduit_showWindow (WidgetID);
	Coord Conduit_windowWidth (WidgetID);
	Coord Conduit_windowHeight (WidgetID);
	int Conduit_totalWindows ();
	void Conduit_windowSetMinimumSize (WidgetID, Coord, Coord);
	void Conduit_windowSetMaximumSize (WidgetID, Coord, Coord);
	void Conduit_windowSetStatusBar (WidgetID, WidgetID);
	void Conduit_windowSetMenuBar (WidgetID, WidgetID);
	void Conduit_windowSetCentralWidget (WidgetID, WidgetID);

	// QStatusBar
	void Conduit_statusBarShowMessage (WidgetID, const char*, long);
	WidgetID Conduit_createStatusBar (WidgetID parent, const char *text);

	// QGroupBox
	WidgetID Conduit_createGroupBox (WidgetID parentID, const char*);

	// QWidget
	WidgetID Conduit_createWidget (WidgetID);
	void Conduit_move (WidgetID, Coord, Coord);
	void Conduit_resize (WidgetID, Coord, Coord);
	void Conduit_setFrame (WidgetID, Rect);
	Rect Conduit_frame (WidgetID);
	Coord Conduit_height (WidgetID);
	Coord Conduit_width (WidgetID);
	void Conduit_setHidden (WidgetID, bool);
	bool Conduit_isHidden (WidgetID);
	const char *Conduit_styleSheet (WidgetID);
	void Conduit_setStyleSheet (WidgetID, const char*);
	void Conduit_raise (WidgetID);
	void Conduit_lower (WidgetID);
	WidgetID Conduit_layout (WidgetID);
	void Conduit_setLayout (WidgetID, ObjectID);
	void Conduit_setMinimumSize (WidgetID, Size);
        Size Conduit_minimumSize (WidgetID);
	void Conduit_setMaximumHeight(WidgetID, long maxh);
	void Conduit_setMaximumWidth(WidgetID, long maxw);
	void Conduit_setMinimumHeight(WidgetID, long minh);
	void Conduit_setMinimumWidth(WidgetID, long minw);
	void Conduit_setParent(WidgetID, WidgetID);
	WidgetID Conduit_parentWidget(WidgetID);

	// QLabel
	WidgetID Conduit_createLabel (WidgetID parent, const char *text);
	void Conduit_labelClear (WidgetID);
	const char* Conduit_labelText (WidgetID);
	void Conduit_labelSetText (WidgetID, const char*);
	long Conduit_labelMargin (WidgetID);
	void Conduit_labelSetMargin (WidgetID, long);
	long Conduit_labelIndent (WidgetID);
	void Conduit_labelSetIndent (WidgetID, long);
	long Conduit_labelAlignment (WidgetID);
	void Conduit_labelSetAlignment (WidgetID, long);
	bool Conduit_labelWordWrap (WidgetID);
	void Conduit_labelSetWordWrap (WidgetID, bool);
	void Conduit_setPixmap (WidgetID, ObjectID);
	void Conduit_setImage (WidgetID, ObjectID);

	// QMenuBar
	WidgetID Conduit_createMenuBar ();
	void Conduit_menuBarAddMenu (WidgetID parent, WidgetID menu);

	// QMenu
	WidgetID Conduit_createMenu (const char *title = nullptr);
	const char *Conduit_menuTitle (WidgetID);
	void Conduit_menuSetTitle (WidgetID, const char *);

	// QAbstractButton
	const char *Conduit_abstractButtonText (WidgetID);
	void Conduit_abstractButtonSetText (WidgetID, const char *);
	bool Conduit_abstractButtonIsChecked (WidgetID);
	void Conduit_abstractButtonSetChecked (WidgetID, bool);

	// QPushButton
	WidgetID Conduit_createPushButton (WidgetID parent, const char *text);
	//const char *Conduit_pushButtonText (WidgetID);
	//void Conduit_pushButtonSetText (WidgetID, const char *);
	bool Conduit_pushButtonIsFlat (WidgetID);
	void Conduit_pushButtonSetFlat (WidgetID, bool);
	bool Conduit_pushButtonIsDefault (WidgetID);
	void Conduit_pushButtonSetDefault (WidgetID, bool);

	// QRadioButton
	WidgetID Conduit_createRadioButton (WidgetID parent, const char *text);

	// QCheckBox
	WidgetID Conduit_createCheckBox (WidgetID parent, const char *text);
	bool Conduit_checkBoxIsTristate (WidgetID);
	void Conduit_checkBoxSetTristate (WidgetID, bool);
	long Conduit_checkBoxCheckState (WidgetID);
	void Conduit_checkBoxSetCheckState (WidgetID, long);

	// QLineEdit
	WidgetID Conduit_createLineEdit (WidgetID parent);
	const char *Conduit_lineEditText (WidgetID);
	void Conduit_lineEditSetText (WidgetID, const char *);

	// QTextEdit
	WidgetID Conduit_createTextEdit (WidgetID parent);
	const char *Conduit_textEditToPlainText (WidgetID);
	void Conduit_textEditSetText (WidgetID, const char *);

	// QTableWidgetItem
	ObjectID Conduit_createTableWidgetItem (const char *);
	const char *Conduit_tableWidgetItemText (ObjectID);
	void Conduit_tableWidgetItemSetText (ObjectID,const char*);

	// QTableWidget
	WidgetID Conduit_createTableWidget (WidgetID parent);
	long Conduit_tableWidgetColumnCount (WidgetID);
	void Conduit_tableWidgetSetColumnCount (WidgetID,long);
	long Conduit_tableWidgetRowCount (WidgetID);
	void Conduit_tableWidgetSetRowCount (WidgetID,long);
	long Conduit_tableWidgetCurrentColumn (WidgetID);
	long Conduit_tableWidgetCurrentRow (WidgetID);
	void Conduit_tableWidgetSetCurrentCell (WidgetID,long,long);

	ObjectID Conduit_tableWidgetItem (WidgetID,long,long);
	void Conduit_tableWidgetSetItem (WidgetID,long,long,ObjectID);
	ObjectID Conduit_tableWidgetCurrentItem (WidgetID);

	WidgetID Conduit_tableWidgetCellWidget (WidgetID,long,long);
	void Conduit_tableWidgetSetCellWidget (WidgetID,long,long,ObjectID);

	void Conduit_tableWidgetInsertColumn (WidgetID tableID, long column);
	void Conduit_tableWidgetInsertRow (WidgetID tableID, long row);

	// QWebEngineView
	WidgetID Conduit_createWebEngineView (WidgetID parent);
	//const char *Conduit_webEngineViewHTML (WidgetID);
	void Conduit_webEngineViewSetHTML (WidgetID, const char *);

	// QLCDNumber
	WidgetID Conduit_createLCDNumber (WidgetID, long);
	void Conduit_lcdNumberSetHexMode (WidgetID);
	void Conduit_lcdNumberSetBinMode (WidgetID);
	void Conduit_lcdNumberSetDecMode (WidgetID);
	void Conduit_lcdNumberSetOctMode (WidgetID);
	double Conduit_lcdNumberValue (WidgetID);
	long Conduit_lcdNumberIntValue (WidgetID);
	long Conduit_lcdNumberDigitCount (WidgetID);
	void Conduit_lcdNumberDisplayInt (WidgetID, long);
	void Conduit_lcdNumberDisplayDouble (WidgetID, double);
};

void ensure_call_propagator_exists()
{
	if (!sharedCallPropagator) {
		sharedCallPropagator = new CallPropagator();
	}
}

//--------------------
// QSlider
//--------------------
WidgetID Conduit_createSlider (WidgetID parentID) {
	return sharedCallPropagator->createSlider(parentID);
}
long Conduit_sliderTickPosition (WidgetID widgetID) {
	return sharedCallPropagator->sliderTickPosition(widgetID);
}
long Conduit_sliderTickInterval (WidgetID widgetID) {
	return sharedCallPropagator->sliderTickInterval(widgetID);
}
void Conduit_sliderSetTickPosition (WidgetID widgetID, long value) {
	sharedCallPropagator->sliderSetTickPosition (widgetID, value);
}
void Conduit_sliderSetTickInterval (WidgetID widgetID, long value) {
	sharedCallPropagator->sliderSetTickInterval (widgetID, value);
}

//--------------------
// QAbstractSlider
//--------------------
long Conduit_abstractSliderOrientation (WidgetID widgetID) {
	return sharedCallPropagator->abstractSliderOrientation (widgetID);
}
void Conduit_abstractSliderSetOrientation (WidgetID widgetID, long value) {
	sharedCallPropagator->abstractSliderSetOrientation (widgetID, value);
}
void Conduit_abstractSliderSetMaximum (WidgetID widgetID, long maximum) {
	sharedCallPropagator->abstractSliderSetMaximum (widgetID, maximum);
}
void Conduit_abstractSliderSetMinimum (WidgetID widgetID, long minimum) {
	sharedCallPropagator->abstractSliderSetMinimum (widgetID, minimum);
}
void Conduit_abstractSliderSetPageStep (WidgetID widgetID, long pageStep) {
	sharedCallPropagator->abstractSliderSetPageStep (widgetID, pageStep);
}
void Conduit_abstractSliderSetValue (WidgetID widgetID, long value) {
	sharedCallPropagator->abstractSliderSetValue (widgetID, value);
}
void Conduit_abstractSliderSetSliderDown (WidgetID widgetID, bool value) {
	sharedCallPropagator->abstractSliderSetSliderDown (widgetID, value);
}
bool Conduit_abstractSliderIsSliderDown (WidgetID widgetID) {
	return sharedCallPropagator->abstractSliderIsSliderDown (widgetID);
}
long Conduit_abstractSliderMaximum (WidgetID widgetID) {
	return sharedCallPropagator->abstractSliderMaximum (widgetID);
}
long Conduit_abstractSliderMinimum (WidgetID widgetID) {
	return sharedCallPropagator->abstractSliderMinimum (widgetID);
}
long Conduit_abstractSliderPageStep (WidgetID widgetID) {
	return sharedCallPropagator->abstractSliderPageStep (widgetID);
}
long Conduit_abstractSliderValue (WidgetID widgetID) {
	return sharedCallPropagator->abstractSliderValue (widgetID);
}

//--------------------
// QDate
//--------------------
DateID Conduit_createDate (long y, long m, long d) 
{
	return sharedCallPropagator->createDate(y,m,d);
}
DateID Conduit_createCurrentDate () {
	return sharedCallPropagator->createCurrentDate();
}
long Conduit_dateDay (DateID dateID) {
	return sharedCallPropagator->dateDay(dateID);
}
long Conduit_dateMonth (DateID dateID) {
	return sharedCallPropagator->dateMonth(dateID);
}
long Conduit_dateYear (DateID dateID) {
	return sharedCallPropagator->dateYear(dateID);
}

//--------------------
// QCalendarWidget
//--------------------
WidgetID Conduit_createCalendarWidget (WidgetID parentID) {
	return sharedCallPropagator->createCalendarWidget (parentID);
}

long Conduit_calendarWidgetSelectedDate(WidgetID widgetID) {
	return sharedCallPropagator->calendarWidgetSelectedDate (widgetID);
}

void Conduit_calendarWidgetClearMaximumDate (WidgetID widgetID) {
	sharedCallPropagator->calendarWidgetClearMaximumDate (widgetID);
}

void Conduit_calendarWidgetClearMinimumDate (WidgetID widgetID) {
	sharedCallPropagator->calendarWidgetClearMinimumDate (widgetID);
}

long Conduit_calendarWidgetMonthShown (WidgetID widgetID) {
	return sharedCallPropagator->calendarWidgetMonthShown (widgetID);
}

long Conduit_calendarWidgetYearShown (WidgetID widgetID) {
	return sharedCallPropagator->calendarWidgetYearShown (widgetID);
}

long Conduit_calendarWidgetHorizontalHeaderFormat(WidgetID widgetID)
{
	return sharedCallPropagator->calendarWidgetHorizontalHeaderFormat(widgetID);
}
long Conduit_calendarWidgetVerticalHeaderFormat(WidgetID widgetID)
{
	return sharedCallPropagator->calendarWidgetVerticalHeaderFormat(widgetID);
}
void Conduit_calendarWidgetSetHorizontalHeaderFormat(WidgetID widgetID, long value)
{
	sharedCallPropagator->calendarWidgetSetHorizontalHeaderFormat(widgetID, value);
}
void Conduit_calendarWidgetSetVerticalHeaderFormat(WidgetID widgetID, long value)
{
	sharedCallPropagator->calendarWidgetSetVerticalHeaderFormat(widgetID, value);
}
long Conduit_calendarWidgetFirstDayOfWeek(WidgetID widgetID)
{
	return sharedCallPropagator->calendarWidgetFirstDayOfWeek (widgetID);
}
void Conduit_calendarWidgetSetFirstDayOfWeek(WidgetID widgetID, long value)
{
	sharedCallPropagator->calendarWidgetSetFirstDayOfWeek (widgetID, value);
}

//--------------------
// QGroupBox
//--------------------
WidgetID Conduit_createGroupBox (WidgetID parentID, const char* title)
{
	return sharedCallPropagator->createGroupBox (parentID, title);
}
long Conduit_groupBoxAlignment (WidgetID groupBoxID)
{
	return sharedCallPropagator->groupBoxAlignment (groupBoxID);
}
void Conduit_groupBoxSetAlignment (WidgetID groupBoxID, long value)
{
	sharedCallPropagator->groupBoxSetAlignment (groupBoxID, value);
}
const char* Conduit_groupBoxTitle (WidgetID groupBoxID)
{
	return sharedCallPropagator->groupBoxTitle (groupBoxID);
}
void Conduit_groupBoxSetTitle (WidgetID groupBoxID, const char* title)
{
	sharedCallPropagator->groupBoxSetTitle (groupBoxID, title ?: "");
}

//--------------------
// QLayout
//--------------------
void Conduit_layoutAddWidget (ObjectID layoutID, WidgetID subwidgetID)
{
	sharedCallPropagator->layoutAddWidget (layoutID, subwidgetID);
}
void Conduit_layoutRemoveWidget (ObjectID layoutID, WidgetID subwidgetID)
{
	sharedCallPropagator->layoutRemoveWidget (layoutID, subwidgetID);
}
long Conduit_layoutSpacing (ObjectID layoutID)
{
	return sharedCallPropagator->layoutSpacing(layoutID);
}
void Conduit_layoutSetSpacing (ObjectID layoutID, long spacing)
{
	sharedCallPropagator->layoutSetSpacing(layoutID, spacing);
}

//--------------------
// QGridLayout
//--------------------
ObjectID Conduit_createGridLayout (WidgetID widgetID) {
	return sharedCallPropagator->createGridLayout(widgetID);
}
void Conduit_gridLayoutAddWidget (ObjectID layoutID, WidgetID widgetID, long row, long column, long alignment) {
	sharedCallPropagator->gridLayoutAddWidget (layoutID, widgetID, row, column, alignment);
}
void Conduit_gridLayoutAddWidgetWithSpans (ObjectID layoutID, WidgetID widgetID, 
				   long row, long column, long rowspan, long colspan, long alignment) {
	sharedCallPropagator->gridLayoutAddWidgetWithSpans (layoutID, widgetID, row, column, rowspan, colspan, alignment);
}
Rect Conduit_gridLayoutCellRect (ObjectID layoutID, long row, long column) {
	return sharedCallPropagator->gridLayoutCellRect (layoutID, row, column);
}
long Conduit_gridLayoutColumnCount (ObjectID layoutID) {
	return sharedCallPropagator->gridLayoutColumnCount (layoutID);
}
long Conduit_gridLayoutColumnMinimumWidth (ObjectID layoutID, long column) {
	return sharedCallPropagator->gridLayoutColumnMinimumWidth (layoutID, column);
}
long Conduit_gridLayoutColumnStretch (ObjectID layoutID, long column) {
	return sharedCallPropagator->gridLayoutColumnStretch (layoutID, column);
}
long Conduit_gridLayoutHorizontalSpacing (ObjectID layoutID) {
	return sharedCallPropagator->gridLayoutHorizontalSpacing (layoutID);
}
long Conduit_gridLayoutRowCount (ObjectID layoutID) {
	return sharedCallPropagator->gridLayoutRowCount (layoutID);
}
long Conduit_gridLayoutRowMinimumHeight (ObjectID layoutID, long row) {
	return sharedCallPropagator->gridLayoutRowMinimumHeight (layoutID, row);
}
long Conduit_gridLayoutRowStretch (ObjectID layoutID, long row) {
	return sharedCallPropagator->gridLayoutRowStretch (layoutID, row);
}
void Conduit_gridLayoutSetColumnMinimumWidth (ObjectID layoutID, long column, long value) {
	sharedCallPropagator->gridLayoutSetColumnMinimumWidth (layoutID, column, value);
}
void Conduit_gridLayoutSetColumnStretch (ObjectID layoutID, long column, long value) {
	sharedCallPropagator->gridLayoutSetColumnStretch (layoutID, column, value);
}
void Conduit_gridLayoutSetHorizontalSpacing (ObjectID layoutID, long value) {
	sharedCallPropagator->gridLayoutSetHorizontalSpacing (layoutID, value);
}
void Conduit_gridLayoutSetRowMinimumHeight (ObjectID layoutID, long row, long value) {
	sharedCallPropagator->gridLayoutSetRowMinimumHeight (layoutID, row, value);
}
void Conduit_gridLayoutSetRowStretch (ObjectID layoutID, long row, long value) {
	sharedCallPropagator->gridLayoutSetRowStretch (layoutID, row, value);
}
void Conduit_gridLayoutSetVerticalSpacing (ObjectID layoutID, long value) {
	sharedCallPropagator->gridLayoutSetVerticalSpacing (layoutID, value);
}
long Conduit_gridLayoutVerticalSpacing (ObjectID layoutID) {
	return sharedCallPropagator->gridLayoutVerticalSpacing (layoutID);
}

//--------------------
// QBoxLayout
//--------------------
ObjectID Conduit_createBoxLayout (ObjectID parentID, long direction)
{
	return sharedCallPropagator->createBoxLayout (parentID, direction);
}
void Conduit_boxLayoutAddWidget (ObjectID layoutID, WidgetID subwidgetID, long stretch, long alignment)
{
	sharedCallPropagator->boxLayoutAddWidget (layoutID, subwidgetID, stretch, alignment);
}
void Conduit_boxLayoutAddSpacing (ObjectID layoutID, long value)
{
	sharedCallPropagator->boxLayoutAddSpacing (layoutID, value);
}
void Conduit_boxLayoutAddStretch (ObjectID layoutID, long value)
{
	sharedCallPropagator->boxLayoutAddStretch (layoutID, value);
}
void Conduit_boxLayoutAddStrut (ObjectID layoutID, long value)
{
	sharedCallPropagator->boxLayoutAddStrut (layoutID, value);
}

//--------------------
// QHBoxLayout
//--------------------
ObjectID Conduit_createHBoxLayout (ObjectID parentID)
{
	return sharedCallPropagator->createHBoxLayout (parentID);
}

//--------------------
// QVBoxLayout
//--------------------
ObjectID Conduit_createVBoxLayout (ObjectID parentID)
{
	return sharedCallPropagator->createVBoxLayout (parentID);
}

//--------------------
// QPixmap
//--------------------
ObjectID Conduit_createPixmapWithPath (const char* path)
{
	return sharedCallPropagator->createPixmapWithPath (path);
}
ObjectID Conduit_createPixmapWithSize (Coord width, Coord height)
{
	return sharedCallPropagator->createPixmapWithSize (width, height);
}

bool Conduit_pixmapLoad (ObjectID objectID, const char *path)
{
	return sharedCallPropagator->pixmapLoad (objectID, path);
}

Coord Conduit_pixmapWidth (ObjectID objectID)
{
	return sharedCallPropagator->pixmapWidth (objectID);
}
Coord Conduit_pixmapHeight (ObjectID objectID)
{
	return sharedCallPropagator->pixmapHeight (objectID);
}
Coord Conduit_pixmapDepth (ObjectID objectID)
{
	return sharedCallPropagator->pixmapDepth (objectID);
}

//--------------------
// QImage
//--------------------
ObjectID Conduit_createImage (const char* path)
{
	return sharedCallPropagator->createImage (path);
}

bool Conduit_imageLoad (ObjectID objectID, const char *path)
{
	return sharedCallPropagator->imageLoad (objectID, path);
}

bool Conduit_imageIsGrayscale (ObjectID objectID)
{
	return sharedCallPropagator->imageIsGrayscale (objectID);
}
Coord Conduit_imageWidth (ObjectID objectID)
{
	return sharedCallPropagator->imageWidth (objectID);
}
Coord Conduit_imageHeight (ObjectID objectID)
{
	return sharedCallPropagator->imageHeight (objectID);
}
Coord Conduit_imageDepth (ObjectID objectID)
{
	return sharedCallPropagator->imageDepth (objectID);
}

//--------------------
// Conveniences
//--------------------
void Conduit_swiftQtConveniencePopup(const char* title, const char* message)
{
	sharedCallPropagator->conveniencePopup (title, message);
}

bool Conduit_swiftQtConvenienceQuestion(const char* title, const char* message)
{
	return sharedCallPropagator->convenienceQuestion (title, message);
}

bool Conduit_swiftQtIsDarkMode()
{
	QColor color = QPalette().color(QPalette::Window);
	int average = (color.red() + color.green() + color.blue()) / 3;
	return average < 0x60;
}

const char *Conduit_swiftQtRelease()
{
	return strdup (kKitVersion);
}

//--------------------
// QWidget
//--------------------
WidgetID Conduit_createWidget (WidgetID parentID)
{
	return sharedCallPropagator->createWidget (parentID);
}
void Conduit_move (WidgetID widgetID, Coord x, Coord y)
{
	sharedCallPropagator->move (widgetID, x, y);
}

void Conduit_resize (WidgetID widgetID, Coord width, Coord height)
{
	sharedCallPropagator->resize (widgetID, width, height);
}

void Conduit_setHidden (WidgetID widgetID, bool value)
{
	sharedCallPropagator->setHidden (widgetID, value);
}

bool Conduit_isHidden (WidgetID widgetID)
{
	return sharedCallPropagator->isHidden (widgetID);
}

void Conduit_setMinimumSize (WidgetID widgetID, Size size)
{
	sharedCallPropagator->setMinimumSize (widgetID, size);
}
Size Conduit_minimumSize (WidgetID widgetID)
{
	return sharedCallPropagator->minimumSize (widgetID);
}
void Conduit_setParent(WidgetID widgetID, WidgetID parentID)
{
	sharedCallPropagator->setParent(widgetID, parentID);
}
WidgetID Conduit_parentWidget(WidgetID widgetID)
{
	return sharedCallPropagator->parentWidget(widgetID);
}

void Conduit_setFrame (WidgetID widgetID, Rect rect)
{
	sharedCallPropagator->setFrame (widgetID, rect);
}

Rect Conduit_frame (WidgetID widgetID)
{
	return sharedCallPropagator->frame (widgetID);
}

Coord Conduit_height (WidgetID widgetID)
{
	return sharedCallPropagator->height (widgetID);
}

Coord Conduit_width (WidgetID widgetID)
{
	return sharedCallPropagator->width (widgetID);
}

const char *Conduit_styleSheet (WidgetID widgetID)
{
	return sharedCallPropagator->styleSheet (widgetID);
}

void Conduit_setStyleSheet (WidgetID widgetID, const char* string)
{
	sharedCallPropagator->setStyleSheet (widgetID, string);
}

void Conduit_raise (WidgetID widgetID)
{
	sharedCallPropagator->raise (widgetID);
}
void Conduit_lower (WidgetID widgetID)
{
	sharedCallPropagator->lower (widgetID);
}
WidgetID Conduit_layout (WidgetID widgetID)
{
	return sharedCallPropagator->layout (widgetID);
}
void Conduit_setLayout (WidgetID widgetID, ObjectID layoutID)
{
	sharedCallPropagator->setLayout (widgetID, layoutID);
}

void Conduit_setMaximumHeight (WidgetID widgetID, long value) {
	if (value >= 0) sharedCallPropagator->setMaximumHeight (widgetID, value);
}
void Conduit_setMaximumWidth (WidgetID widgetID, long value) {
	if (value >= 0) sharedCallPropagator->setMaximumWidth (widgetID, value);
}
void Conduit_setMinimumHeight (WidgetID widgetID, long value) {
	if (value >= 0) sharedCallPropagator->setMinimumHeight (widgetID, value);
}
void Conduit_setMinimumWidth (WidgetID widgetID, long value) {
	if (value >= 0) sharedCallPropagator->setMinimumWidth (widgetID, value);
}

//--------------------
// QMainWindow
//--------------------
WidgetID Conduit_createWindow (Coord x, Coord y, Coord width, Coord height)
{
	return sharedCallPropagator->createWindow (x, y, width, height);
}

const char *Conduit_windowTitle (WidgetID windowID)
{
	return sharedCallPropagator->windowTitle (windowID);
}

void Conduit_windowSetTitle (WidgetID windowID, const char *title)
{
	sharedCallPropagator->windowSetTitle (windowID, title);
}

void Conduit_windowSetMinimumSize (WidgetID windowID, Coord width, Coord height)
{
	sharedCallPropagator->windowSetMinimumSize (windowID, width, height);
}
void Conduit_windowSetMaximumSize (WidgetID windowID, Coord width, Coord height)
{
	sharedCallPropagator->windowSetMaximumSize (windowID, width, height);
}

Coord Conduit_windowWidth (WidgetID windowID) // Superfluous?
{
	return sharedCallPropagator->windowWidth (windowID);
}

Coord Conduit_windowHeight (WidgetID windowID) // Superfluous?
{
	return sharedCallPropagator->windowHeight (windowID);
}

void Conduit_showWindow (WidgetID windowID) 
{
	MainWindow *window = sharedCallPropagator->lookupWindow (windowID);
	if (window) {
		// Add menu bar and status bar.
		puts("Qt: SHOWING");
		window->show();
	}
}

void Conduit_windowSetStatusBar (WidgetID windowID, WidgetID statusBarID)
{
	sharedCallPropagator->windowSetStatusBar (windowID, statusBarID);
}

void Conduit_windowSetCentralWidget (WidgetID windowID, WidgetID widgetID)
{
	sharedCallPropagator->windowSetCentralWidget (windowID, widgetID);
}

void Conduit_windowSetMenuBar (WidgetID windowID, WidgetID menuBarID)
{
	sharedCallPropagator->windowSetMenuBar (windowID, menuBarID);
}

int Conduit_totalWindows ()
{
	return sharedCallPropagator->totalWindows();
}

//--------------------
// QStatusBar
//--------------------
WidgetID Conduit_createStatusBar (WidgetID parentID, const char *text)
{
	return sharedCallPropagator->createStatusBar (parentID, text ?: "");
}

void Conduit_statusBarShowMessage (WidgetID widgetID, const char* text, long duration)
{
	sharedCallPropagator->statusBarShowMessage (widgetID, text ?: "", duration);
}

//--------------------
// QMenuBar
//--------------------
WidgetID Conduit_createMenuBar ()
{
	return sharedCallPropagator->createMenuBar ();
}

void Conduit_menuBarAddMenu (WidgetID parent, WidgetID menu)
{
	sharedCallPropagator->menuBarAddMenu (parent, menu);
}

//--------------------
// QMenu
//--------------------
WidgetID Conduit_createMenu (const char *title)
{
	return sharedCallPropagator->createMenu (title);
}

const char *Conduit_menuTitle (WidgetID widgetID)
{
	return sharedCallPropagator->menuTitle (widgetID);
}

void Conduit_menuSetTitle (WidgetID widgetID, const char *title)
{
	sharedCallPropagator->menuSetTitle (widgetID, title);
}

void Conduit_menuAddAction (WidgetID widgetID, ObjectID actionID)
{
	sharedCallPropagator->menuAddAction (widgetID, actionID);
}

void Conduit_menuAddSeparator (WidgetID widgetID)
{
	sharedCallPropagator->menuAddSeparator (widgetID);
}

//--------------------
// QAction
//--------------------
ObjectID Conduit_createAction (const char* text)
{
	return sharedCallPropagator->createAction (text);
}
void Conduit_actionSetShortcut (ObjectID actionID, ObjectID keySequenceID)
{
	return sharedCallPropagator->actionSetShortcut (actionID, keySequenceID);
}

//--------------------
// QKeySequence
//--------------------
ObjectID Conduit_createKeySequence (const char* info)
{
	return sharedCallPropagator->createKeySequence (info);
}

//--------------------
// QColor
//--------------------
ObjectID Conduit_createColor (long red, long green, long blue)
{
	return sharedCallPropagator->createColor (red, green, blue);
}

//--------------------
// QLabel
//--------------------
WidgetID Conduit_createLabel (WidgetID parent, const char *text)
{
	return sharedCallPropagator->createLabel (parent, text);
}
void Conduit_labelClear (WidgetID labelID)
{
	sharedCallPropagator->labelClear (labelID);
}
const char* Conduit_labelText (WidgetID labelID)
{
	return sharedCallPropagator->labelText (labelID);
}
void Conduit_labelSetText (WidgetID labelID, const char*string)
{
	sharedCallPropagator->labelSetText (labelID, string);
}
bool Conduit_labelWordWrap (WidgetID labelID)
{
	return sharedCallPropagator->labelWordWrap (labelID);
}
void Conduit_labelSetWordWrap (WidgetID labelID, bool value)
{
	sharedCallPropagator->labelSetWordWrap (labelID, value);
}
long Conduit_labelAlignment (WidgetID labelID)
{
	return sharedCallPropagator->labelAlignment (labelID);
}
void Conduit_labelSetAlignment (WidgetID labelID, long value)
{
	sharedCallPropagator->labelSetAlignment (labelID, value);
}
long Conduit_labelIndent (WidgetID labelID)
{
	return sharedCallPropagator->labelIndent (labelID);
}
void Conduit_labelSetIndent (WidgetID labelID, long value)
{
	sharedCallPropagator->labelSetIndent (labelID, value);
}
long Conduit_labelMargin (WidgetID labelID)
{
	return sharedCallPropagator->labelMargin (labelID);
}
void Conduit_labelSetMargin (WidgetID labelID, long value)
{
	sharedCallPropagator->labelSetMargin (labelID, value);
}
void Conduit_labelSetPixmap (WidgetID labelID, ObjectID pixmapID)
{
	sharedCallPropagator->labelSetPixmap (labelID, pixmapID);
}
void Conduit_labelSetImage (WidgetID labelID, ObjectID imageID)
{
	sharedCallPropagator->labelSetImage (labelID, imageID);
}

//--------------------
// QAbstractButton
//--------------------
const char *Conduit_abstractButtonText (WidgetID widgetID)
{
	return sharedCallPropagator->abstractButtonText (widgetID);
}

void Conduit_abstractButtonSetText (WidgetID widgetID, const char *text)
{
	sharedCallPropagator->abstractButtonSetText (widgetID, text);
}

bool Conduit_abstractButtonIsChecked (WidgetID widgetID)
{
	return sharedCallPropagator->abstractButtonIsChecked (widgetID);
}

void Conduit_abstractButtonSetChecked (WidgetID widgetID, bool value)
{
	sharedCallPropagator->abstractButtonSetChecked (widgetID, value);
}


//--------------------
// QPushButton
//--------------------
WidgetID Conduit_createPushButton (WidgetID parent, const char *text)
{
	return sharedCallPropagator->createPushButton (parent, text);
}

bool Conduit_pushButtonIsFlat (WidgetID widgetID)
{
	return sharedCallPropagator->pushButtonIsFlat (widgetID);
}

void Conduit_pushButtonSetFlat (WidgetID widgetID, bool value)
{
	sharedCallPropagator->pushButtonSetFlat (widgetID, value);
}

bool Conduit_pushButtonIsDefault (WidgetID widgetID)
{
	return sharedCallPropagator->pushButtonIsDefault (widgetID);
}

void Conduit_pushButtonSetDefault (WidgetID widgetID, bool value)
{
	sharedCallPropagator->pushButtonSetDefault (widgetID, value);
}

//--------------------
// QRadioButton
//--------------------
WidgetID Conduit_createRadioButton (WidgetID parent, const char *text)
{
	return sharedCallPropagator->createRadioButton (parent, text);
}

//--------------------
// QCheckBox
//--------------------
WidgetID Conduit_createCheckBox (WidgetID parent, const char *text)
{
	return sharedCallPropagator->createCheckBox (parent, text);
}
bool Conduit_checkBoxIsTristate (WidgetID widgetID)
{
	return sharedCallPropagator->checkBoxIsTristate (widgetID);
}
void Conduit_checkBoxSetTristate (WidgetID widgetID, bool value)
{
	sharedCallPropagator->checkBoxSetTristate (widgetID, value);
}
long Conduit_checkBoxCheckState (WidgetID widgetID)
{
	return sharedCallPropagator->checkBoxCheckState (widgetID);
}
void Conduit_checkBoxSetCheckState (WidgetID widgetID, long value)
{
	sharedCallPropagator->checkBoxSetCheckState (widgetID, value);
}

//--------------------
// QTextEdit
//--------------------
WidgetID Conduit_createTextEdit (WidgetID parent)
{
	return sharedCallPropagator->createTextEdit (parent);
}

void Conduit_textEditSetText (WidgetID widgetID, const char *text)
{
	sharedCallPropagator->textEditSetText (widgetID, text);
}

void Conduit_textEditSetAcceptRichText (WidgetID widgetID, bool accepts)
{
	sharedCallPropagator->textEditSetAcceptRichText (widgetID, accepts);
}

const char *Conduit_textEditToPlainText (WidgetID widgetID)
{
	return sharedCallPropagator->textEditToPlainText (widgetID);
}

const char *Conduit_textEditToHTML (WidgetID widgetID)
{
	return sharedCallPropagator->textEditToHTML (widgetID);
}

//--------------------
// QLineEdit
//--------------------
const char *Conduit_lineEditText (WidgetID widgetID)
{
	return sharedCallPropagator->lineEditText (widgetID);
}

void Conduit_lineEditSetText (WidgetID widgetID, const char *text)
{
	sharedCallPropagator->lineEditSetText (widgetID, text);
}

WidgetID Conduit_createLineEdit (WidgetID parent)
{
	return sharedCallPropagator->createLineEdit (parent);
}

//--------------------
// QTableWidgetItem
//--------------------
ObjectID Conduit_createTableWidgetItem (const char *text)
{
	return sharedCallPropagator->createTableWidgetItem (text);
}
const char *Conduit_tableWidgetItemText (ObjectID itemID)
{
	return sharedCallPropagator->tableWidgetItemText (itemID);
}
void Conduit_tableWidgetItemSetText (ObjectID itemID, const char* text)
{
	sharedCallPropagator->tableWidgetItemSetText (itemID, text);
}

//--------------------
// QTableWidget
//--------------------
WidgetID Conduit_createTableWidget (WidgetID parent)
{
	return sharedCallPropagator->createTableWidget (parent);
}

void Conduit_tableWidgetInsertColumn (WidgetID tableID, long column)
{
	sharedCallPropagator->tableWidgetInsertColumn (tableID, column);
}
void Conduit_tableWidgetInsertRow (WidgetID tableID, long row)
{
	sharedCallPropagator->tableWidgetInsertRow (tableID, row);
}
long Conduit_tableWidgetColumnCount (WidgetID table) {
	return sharedCallPropagator->tableWidgetColumnCount (table);
}
void Conduit_tableWidgetSetColumnCount (WidgetID tableID, long count) {
	sharedCallPropagator->tableWidgetSetColumnCount (tableID, count);
}
long Conduit_tableWidgetRowCount (WidgetID table) {
	return sharedCallPropagator->tableWidgetRowCount (table);
}
void Conduit_tableWidgetSetRowCount (WidgetID tableID, long count) {
	return sharedCallPropagator->tableWidgetSetRowCount (tableID, count);
}
long Conduit_tableWidgetCurrentColumn (WidgetID table) {
	return sharedCallPropagator->tableWidgetCurrentColumn (table);
}
long Conduit_tableWidgetCurrentRow (WidgetID table) {
	return sharedCallPropagator->tableWidgetCurrentRow (table);
}
void Conduit_tableWidgetSetCurrentCell (WidgetID tableID, long row, long column) {
	return sharedCallPropagator->tableWidgetSetCurrentCell (tableID, row, column);
}
ObjectID Conduit_tableWidgetItem (WidgetID tableID, long row, long column) {
	return sharedCallPropagator->tableWidgetItem (tableID, row, column);
}
void Conduit_tableWidgetSetItem (WidgetID tableID, long row, long column, ObjectID itemID) {
	sharedCallPropagator->tableWidgetSetItem (tableID, row, column, itemID);
}
ObjectID Conduit_tableWidgetCurrentItem (WidgetID table) {
	return sharedCallPropagator->tableWidgetCurrentItem (table);
}
WidgetID Conduit_tableWidgetCellWidget (WidgetID tableID, long row, long column) {
	return sharedCallPropagator->tableWidgetCellWidget (tableID, row, column);
}
void Conduit_tableWidgetSetCellWidget (WidgetID tableID, long row, long column, WidgetID widgetID) {
	sharedCallPropagator->tableWidgetSetCellWidget (tableID, row, column, widgetID);
}
void Conduit_tableWidgetSetVerticalHeaderLabel (WidgetID tableID, const char *string, bool is_last)
{
	sharedCallPropagator->tableWidgetSetVerticalHeaderLabel (tableID, string, is_last);
}
void Conduit_tableWidgetSetHorizontalHeaderLabel (WidgetID tableID, const char *string, bool is_last)
{
	sharedCallPropagator->tableWidgetSetHorizontalHeaderLabel (tableID, string, is_last);
}

//--------------------
// QWebEngineView
//--------------------
WidgetID Conduit_createWebEngineView (WidgetID parent)
{
	return sharedCallPropagator->createWebEngineView (parent);
}

void Conduit_webEngineViewSetHTML (WidgetID widgetID, const char *text)
{
	sharedCallPropagator->webEngineViewSetHTML (widgetID, text);
}

//--------------------
// QLCDNumber
//--------------------
WidgetID Conduit_createLCDNumber (WidgetID widgetID, long numDigits) {
	return sharedCallPropagator->createLCDNumber (widgetID, numDigits);
}
void Conduit_lcdNumberSetHexMode (WidgetID widgetID) {
	sharedCallPropagator->lcdNumberSetHexMode (widgetID);
}
void Conduit_lcdNumberSetBinMode (WidgetID widgetID) {
	sharedCallPropagator->lcdNumberSetBinMode (widgetID);
}
void Conduit_lcdNumberSetDecMode (WidgetID widgetID) {
	sharedCallPropagator->lcdNumberSetDecMode (widgetID);
}
void Conduit_lcdNumberSetOctMode (WidgetID widgetID) {
	sharedCallPropagator->lcdNumberSetOctMode (widgetID);
}
double Conduit_lcdNumberValue (WidgetID widgetID) {
	return sharedCallPropagator->lcdNumberValue (widgetID);
}
long Conduit_lcdNumberIntValue (WidgetID widgetID) {
	return sharedCallPropagator->lcdNumberIntValue (widgetID);
}
long Conduit_lcdNumberDigitCount (WidgetID widgetID) {
	return sharedCallPropagator->lcdNumberDigitCount (widgetID);
}
void Conduit_lcdNumberDisplayInt (WidgetID widgetID, long value) {
	sharedCallPropagator->lcdNumberDisplayInt (widgetID, value);
}
void Conduit_lcdNumberDisplayDouble (WidgetID widgetID, double value) {
	sharedCallPropagator->lcdNumberDisplayDouble (widgetID, value);
}
bool Conduit_lcdNumberSmallDecimalPoint (WidgetID widgetID) {
	return sharedCallPropagator->lcdNumberSmallDecimalPoint (widgetID);
}
void Conduit_lcdNumberSetSmallDecimalPoint (WidgetID widgetID, bool value) {
	sharedCallPropagator->lcdNumberSetSmallDecimalPoint (widgetID, value);
}

//-----------------------------------------------------------------------------
// C++ Code that is called by the C "conduit" code.
//-----------------------------------------------------------------------------

CallPropagator::CallPropagator() 
{
}

CallPropagator::~CallPropagator()
{
	widgets.clear();
	objects.clear();
}

//-----------------------------------------------------------------------------
// QApplication
//-----------------------------------------------------------------------------
void Conduit_applicationQuit()
{
	QApplication::quit();
}

void Conduit_applicationBeep()
{
#ifdef __linux__
	if (!system ("which ffplay > /dev/null")) {
		system ("ffplay -nodisp -autoexit /usr/share/sounds/freedesktop/stereo/bell.oga 2> /dev/null");
	}
#else
	QApplication::beep();
#endif
}

//--------------------
// QLayout
//--------------------
void CallPropagator::layoutAddWidget (ObjectID layoutID, WidgetID subwidgetID)
{
	QLayout *layout = (QLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	QWidget *subwidget = widgets[subwidgetID];
	if (!subwidget) {
		return;
	}
	layout->addWidget (subwidget);
}
void CallPropagator::layoutRemoveWidget (ObjectID layoutID, WidgetID subwidgetID)
{
	QLayout *layout = (QLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	QWidget *subwidget = widgets[subwidgetID];
	if (!subwidget) {
		return;
	}
	layout->removeWidget (subwidget);
}
long CallPropagator::layoutSpacing (ObjectID layoutID)
{
	QLayout *layout = (QLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->spacing();
}
void CallPropagator::layoutSetSpacing (ObjectID layoutID, long spacing)
{
	QLayout *layout = (QLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setSpacing(spacing);
}

//--------------------
// QBoxLayout
//--------------------
ObjectID CallPropagator::createBoxLayout (WidgetID parentID, long direction)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}
	QBoxLayout::Direction dir;
	switch (direction) {
	case 0: dir = QBoxLayout::LeftToRight; break;
	case 1: dir = QBoxLayout::RightToLeft; break;
	default:
	case 2: dir = QBoxLayout::TopToBottom; break;
	case 3: dir = QBoxLayout::BottomToTop; break;
	}
	QBoxLayout *layout = new QBoxLayout(dir, parent);
	int layoutID = widgetObjectCounter++;
	objects[layoutID] = (QObject*) layout;
	return layoutID;
}
void CallPropagator::boxLayoutAddWidget (WidgetID layoutID, WidgetID subwidgetID, int stretch, int value)
{
	QBoxLayout *layout = (QBoxLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	QWidget *subwidget = widgets[subwidgetID];
	if (!subwidget) {
		return;
	}

	Qt::Alignment alignment;
	if (value & 1) alignment |= Qt::AlignLeft;
	if (value & 2) alignment |= Qt::AlignRight;
	if (value & 4) alignment |= Qt::AlignCenter;
	if (value & 8) alignment |= Qt::AlignJustify;
	if (value & 0x20) alignment |= Qt::AlignTop;
	if (value & 0x40) alignment |= Qt::AlignBottom;
	if (value & 0x80) alignment |= Qt::AlignVCenter;
	if (value & 0x100) alignment |= Qt::AlignBaseline;

	layout->addWidget (subwidget, stretch, alignment);
}
void CallPropagator::boxLayoutAddSpacing (ObjectID layoutID, long value)
{
	QBoxLayout *layout = (QBoxLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->addSpacing (value);
}
void CallPropagator::boxLayoutAddStretch (ObjectID layoutID, long value)
{
	QBoxLayout *layout = (QBoxLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->addStretch (value);
}
void CallPropagator::boxLayoutAddStrut (ObjectID layoutID, long value)
{
	QBoxLayout *layout = (QBoxLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->addStrut (value);
}

//--------------------
// QHBoxLayout
//--------------------
ObjectID CallPropagator::createHBoxLayout (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}
	QHBoxLayout *layout = new QHBoxLayout(parent);
	int layoutID = widgetObjectCounter++;
	objects[layoutID] = (QObject*) layout;
	return layoutID;
}

//--------------------
// QVBoxLayout
//--------------------
ObjectID CallPropagator::createVBoxLayout (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}
	QVBoxLayout *layout = new QVBoxLayout(parent);
	int layoutID = widgetObjectCounter++;
	objects[layoutID] = (QObject*) layout;
	return layoutID;
}

//--------------------
// QPixmap
//--------------------
ObjectID CallPropagator::createPixmapWithPath (const char* path)
{
	QPixmap *pixmap;
	if (path && *path) {
		QString qpath(path);
		pixmap = new QPixmap(qpath);
	} else {
		pixmap = new QPixmap();
	}
	int objectID = widgetObjectCounter++;
	objects[objectID] = (QObject*) pixmap;
	return objectID;
}

ObjectID CallPropagator::createPixmapWithSize (Coord width, Coord height)
{
	QPixmap *pixmap;
	if (width > 0 && height > 0) {
		pixmap = new QPixmap(width, height);
	} else {
		pixmap = new QPixmap();
	}
	int objectID = widgetObjectCounter++;
	objects[objectID] = (QWidget*) pixmap;
	return objectID;
}

bool CallPropagator::pixmapLoad (ObjectID objectID, const char *path)
{
	QPixmap *pixmap = (QPixmap*)objects[objectID];
	if (!pixmap) {
		return false;
	}

	bool result = false;
	if (path) {
		QString qpath(path);
		result = pixmap->load (qpath);
	}
	return result;
}

Coord CallPropagator::pixmapWidth (ObjectID objectID)
{
	QPixmap *pixmap = (QPixmap*)objects[objectID];
	if (!pixmap) {
		return false;
	}
	return pixmap->width();
}
Coord CallPropagator::pixmapHeight (ObjectID objectID)
{
	QPixmap *pixmap = (QPixmap*)objects[objectID];
	if (!pixmap) {
		return false;
	}
	return pixmap->height();
}
Coord CallPropagator::pixmapDepth (ObjectID objectID)
{
	QPixmap *pixmap = (QPixmap*)objects[objectID];
	if (!pixmap) {
		return false;
	}
	return pixmap->depth();
}

//--------------------
// QImage
//--------------------
ObjectID CallPropagator::createImage (const char* path)
{
	QImage *image;
	if (path && *path) {
		QString qpath(path);
		image = new QImage(qpath);
	} else {
		image = new QImage();
	}
	int objectID = widgetObjectCounter++;
	objects[objectID] = (QWidget*) image;
	return objectID;
}

bool CallPropagator::imageLoad (ObjectID objectID, const char *path)
{
	QImage *image = (QImage*)objects[objectID];
	if (!image) {
		return false;
	}

	bool result = false;
	if (path) {
		QString qpath(path);
		result = image->load (qpath);
	}
	return result;
}

bool CallPropagator::imageIsGrayscale (ObjectID objectID)
{
	QImage *image = (QImage*)objects[objectID];
	if (!image) {
		return false;
	}
	return image->isGrayscale();
}
Coord CallPropagator::imageWidth (ObjectID objectID)
{
	QImage *image = (QImage*)objects[objectID];
	if (!image) {
		return false;
	}
	return image->width();
}
Coord CallPropagator::imageHeight (ObjectID objectID)
{
	QImage *image = (QImage*)objects[objectID];
	if (!image) {
		return false;
	}
	return image->height();
}
Coord CallPropagator::imageDepth (ObjectID objectID)
{
	QImage *image = (QImage*)objects[objectID];
	if (!image) {
		return false;
	}
	return image->depth();
}

//--------------------
// Conveniences
//--------------------
void CallPropagator::conveniencePopup (const char* title, const char* message)
{
	QMessageBox messageBox;
	messageBox.information (nullptr, title ?: "", message ?: "");
}

bool CallPropagator::convenienceQuestion (const char *title, const char *question)
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question (nullptr, title, question, QMessageBox::Yes | QMessageBox::No);
	return reply == QMessageBox::Yes;
}

//--------------------
// QGroupBox
//--------------------
WidgetID CallPropagator::createGroupBox (WidgetID parentID, const char* title)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}
	QGroupBox *widget = new QGroupBox(title, parent);
	int widgetID = widgetObjectCounter++;
	widgets[widgetID] = (QWidget*) widget;
	return widgetID;
}
long CallPropagator::groupBoxAlignment (WidgetID widgetID)
{
	QGroupBox *widget = (QGroupBox*) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return (long)widget->alignment();
}
void CallPropagator::groupBoxSetAlignment (WidgetID widgetID, long value)
{
	QGroupBox *widget = (QGroupBox*) widgets[widgetID];
	if (!widget) {
		return;
	}

	Qt::Alignment alignment;
	if (value & 1) alignment |= Qt::AlignLeft;
	if (value & 2) alignment |= Qt::AlignRight;
	if (value & 4) alignment |= Qt::AlignCenter;
	if (value & 8) alignment |= Qt::AlignJustify;
	if (value & 0x20) alignment |= Qt::AlignTop;
	if (value & 0x40) alignment |= Qt::AlignBottom;
	if (value & 0x80) alignment |= Qt::AlignVCenter;
	if (value & 0x100) alignment |= Qt::AlignBaseline;

	widget->setAlignment (alignment);
}
const char* CallPropagator::groupBoxTitle (WidgetID widgetID)
{
	QGroupBox *widget = (QGroupBox*) widgets[widgetID];
	if (!widget) {
		return NULL;
	}
	QString title = widget->title();
	std::string string = title.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}
void CallPropagator::groupBoxSetTitle (WidgetID widgetID, const char* string)
{
	QGroupBox *widget = (QGroupBox*) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setTitle (string ?: "");
}

//--------------------
// QWidget
//--------------------
WidgetID CallPropagator::createWidget (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}
	QWidget *widget = new QWidget(parent);
	int index = widgetObjectCounter++;
	widgets[index] = widget;
	return index;
}

void CallPropagator::move (WidgetID widgetID, Coord x, Coord y) 
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->move (x, y);
}

void CallPropagator::resize (WidgetID widgetID, Coord width, Coord height) 
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->resize (width, height);
}

void CallPropagator::setHidden (WidgetID widgetID, bool value)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setHidden (value);
}

bool CallPropagator::isHidden (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (widget) {
		return widget->isHidden();
	}
	return false;
}

void CallPropagator::setFrame (WidgetID widgetID, Rect rect)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->move (rect.origin.x, rect.origin.y);
	widget->resize (rect.size.width, rect.size.height);
	//printf("Qt: %s %s to %ld,%ld %ldx%ld\n", typeid(widget).name(), __FUNCTION__, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

void CallPropagator::setMinimumSize (WidgetID widgetID, Size size)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	QSize qsize;
	qsize.setWidth (size.width);
	qsize.setHeight (size.height);
	widget->setMinimumSize (qsize);
}

Size CallPropagator::minimumSize (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		Size zerosize = {0, 0};
		return zerosize;
	}
	QSize qsize = widget->minimumSize ();
	Size size;
	size.width = qsize.width();
	size.height = qsize.height();
	return size;
}

WidgetID CallPropagator::parentWidget(WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return -1;
	}
	QWidget *parent = widget->parentWidget();
	if (!parent) {
		return -1;
	}
	WidgetID parentID = lookupWidget (parent);
	return parentID;
}

void CallPropagator::setParent(WidgetID widgetID, WidgetID parentID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	if (parentID < 0) {
		widget->setParent(NULL);
		return;
	}
	QWidget *parent = widgets[widgetID];
	if (!parent) {
		return;
	}
	widget->setParent(parent);
}

Coord CallPropagator::width (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->width();
}

Coord CallPropagator::height (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->height();
}

void CallPropagator::setStyleSheet (WidgetID widgetID, const char*string)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setStyleSheet (string);
}

const char *CallPropagator::styleSheet (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return NULL;
	}

	QString text = widget->styleSheet ();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

void CallPropagator::raise (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (widget) {
		widget->raise();
	}
}
void CallPropagator::lower (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (widget) {
		widget->lower();
	}
}
WidgetID CallPropagator::layout (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return -1;
	}
	QLayout *layout = widget->layout();
	ObjectID layoutID = lookupObject ((QObject*)layout);
	return layoutID;
}
void CallPropagator::setLayout (WidgetID widgetID, WidgetID layoutID)
{
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	QLayout *layout = (QLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	widget->setLayout (layout);
}

Rect CallPropagator::frame (WidgetID widgetID)
{
	QWidget *widget = widgets[widgetID];
	Rect rect;
	if (!widget) {
		rect.origin.x = 0;
		rect.origin.y = 0;
		rect.size.width = 0;
		rect.size.height = 0;
		return rect;
	}
	rect.origin.x = widget->x();
	rect.origin.y = widget->y();
	rect.size.width = widget->width();
	rect.size.height = widget->height();

	//printf("Qt: %s %s: %ld,%ld %ldx%ld\n", typeid(widget).name(), __FUNCTION__, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	return rect;
}

void CallPropagator::setMaximumHeight (WidgetID widgetID, long value) {
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setMaximumHeight(value);
}
void CallPropagator::setMaximumWidth (WidgetID widgetID, long value) {
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setMaximumWidth(value);
}
void CallPropagator::setMinimumHeight (WidgetID widgetID, long value) {
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setMinimumHeight(value);
}
void CallPropagator::setMinimumWidth (WidgetID widgetID, long value) {
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setMinimumWidth(value);
}
//--------------------
// QMainWindow
//--------------------
MainWindow *CallPropagator::lookupWindow (WidgetID windowID)
{
	QWidget *ptr = widgets[windowID];
	return dynamic_cast<MainWindow*>(ptr);
}

WidgetID CallPropagator::createWindow (Coord x, Coord y, Coord width, Coord height)
{
	MainWindow *window = new MainWindow();
	int windowID = widgetObjectCounter++;
	widgets[windowID] = (QWidget*) window;
	window->setMinimumSize(width, height);
	window->move(x, y);

	// Set the windowID so that Swift code knows which window it is that events pertain to.
	window->windowID = windowID;

	//window->setMaximumSize(screenWidth, screenHeight);

	return windowID;
}

const char *CallPropagator::windowTitle (WidgetID widgetID)
{
	QMainWindow *window = (QMainWindow *) widgets[widgetID];
	if (!window) {
		return NULL;
	}

	QString text = window->windowTitle();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

void CallPropagator::windowSetTitle (WidgetID widgetID, const char *text)
{
	QMainWindow *window = (QMainWindow *) widgets[widgetID];
	if (!window) {
		return;
	}

	window->setWindowTitle(text);
}

void CallPropagator::windowSetMinimumSize (WidgetID windowID, Coord width, Coord height)
{
	MainWindow *window = lookupWindow (windowID);
	if (window) {
		window->setMinimumSize (width, height);
	}
}
void CallPropagator::windowSetMaximumSize (WidgetID windowID, Coord width, Coord height)
{
	MainWindow *window = lookupWindow (windowID);
	if (window) {
		window->setMaximumSize (width, height);
	}
}

Coord CallPropagator::windowWidth (WidgetID windowID) 
{
	MainWindow *window = lookupWindow (windowID);
	return window? window->width() : 0;
}

Coord CallPropagator::windowHeight (WidgetID windowID) 
{
	MainWindow *window = lookupWindow (windowID);
	return window? window->height() : 0;
}

void CallPropagator::windowSetStatusBar (WidgetID windowID, WidgetID statusBarID)
{
	MainWindow *window = lookupWindow (windowID);
	QStatusBar *statusBar = (QStatusBar*) widgets[statusBarID];
	if (window && statusBar) {
		window->setStatusBar (statusBar);
	}
}

void CallPropagator::windowSetMenuBar (WidgetID windowID, WidgetID menuBarID)
{
	MainWindow *window = lookupWindow (windowID);
	QMenuBar *menuBar = (QMenuBar*) widgets[menuBarID];
	if (window && menuBar) {
		window->setMenuBar (menuBar);
puts("SETTING MENUBAR");
	}
}

void CallPropagator::windowSetCentralWidget (WidgetID windowID, WidgetID widgetID)
{
	MainWindow *window = lookupWindow (windowID);
	if (!window) {
		return;
	}
	QWidget *widget = (QWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}
	window->setCentralWidget (widget);
}

MainWindow *CallPropagator::mainWindow ()
{
	for (const auto & [key, value] : widgets) {
		QWidget *widget = value;
		if (dynamic_cast<MainWindow*>(widget)) {
			return (MainWindow*) widget;
		}
	}
	return NULL;
}

int CallPropagator::totalWindows() {
	int count = 0;

	for (const auto & [key, value] : widgets) {
		QWidget *widget = value;
		if (dynamic_cast<MainWindow*>(widget)) {
			count++;
		}
	}
	return count;
}

//--------------------
// QStatusBar
//--------------------
void CallPropagator::statusBarShowMessage (WidgetID statusBarID, const char *text, long duration)
{
	QStatusBar *statusBar = (QStatusBar*) widgets[statusBarID];
	if (statusBar) {
		statusBar->showMessage (text ?: "", duration);
	} 
}

WidgetID CallPropagator::createStatusBar (WidgetID parentID, const char *text)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	//printf("Qt: STATUS BAR TEXT=%s\n",text);

	QStatusBar *statusBar = new QStatusBar (parent);
	if (text) {
		statusBar->showMessage (text);
	} 
	int index = widgetObjectCounter++;
	widgets[index] = statusBar;

	return index;
}

//--------------------
// QKeySequence
//--------------------
ObjectID CallPropagator::createKeySequence (const char* info)
{
	QKeySequence *sequence = new QKeySequence (info ?: "");
	int index = widgetObjectCounter++;
	objects[index] = (QObject*)sequence;
	return index;
}

//--------------------
// QColor
//--------------------
ObjectID CallPropagator::createColor (long red, long green, long blue)
{
	QColor *color = new QColor (red, green, blue);
	int index = widgetObjectCounter++;
	objects[index] = (QObject*)color;
	return index;
}

//--------------------
// QAction
//--------------------
ObjectID CallPropagator::createAction (const char* text = nullptr)
{
	QAction *action = new QAction (text ?: "");
	int index = widgetObjectCounter++;
	objects[index] = (QObject*)action;

	connect (action, &QAction::triggered, this, [index]() {
		//printf ("QAction triggered, object index %d\n", index);
		Event event;
		event.type = EventTypeActionTriggered;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}
void CallPropagator::actionSetShortcut (ObjectID actionID, ObjectID sequenceID)
{
	QAction *action = (QAction*) objects[actionID];
	if (!action) {
		return;
	}
	QKeySequence *sequence = (QKeySequence*) objects[sequenceID];
	if (!sequence) {
		return;
	}
	action->setShortcut (*sequence);
}

//--------------------
// QMenuBar
//--------------------
WidgetID CallPropagator::createMenuBar ()
{
	QMenuBar *menubar = new QMenuBar ();
	int index = widgetObjectCounter++;
	widgets[index] = menubar;
	return index;
}

void CallPropagator::menuBarAddMenu (WidgetID menubarID, WidgetID menuID)
{
	QMenuBar *menubar = (QMenuBar*) widgets[menubarID];
	if (!menubar) {
		return;
	}
	QMenu *menu = (QMenu*) widgets[menuID];
	if (!menu) {
		return;
	}

	menubar->addMenu(menu);
}

//--------------------
// QMenu
//--------------------
WidgetID CallPropagator::createMenu (const char *title)
{
	QMenu *menu = new QMenu (title);
	int index = widgetObjectCounter++;
	widgets[index] = menu;
	return index;
}

void CallPropagator::menuAddAction (WidgetID widgetID, ObjectID actionID)
{
	QMenu *menu = (QMenu*) widgets[widgetID];
	if (!menu) {
		return;
	}
	QAction *action = (QAction*) objects[actionID];
	if (!action) {
		return;
	}
	menu->addAction(action);
}

void CallPropagator::menuAddSeparator (WidgetID widgetID)
{
	QMenu *menu = (QMenu*) widgets[widgetID];
	if (!menu) {
		return;
	}
	menu->addSeparator();
}

const char *CallPropagator::menuTitle (WidgetID widgetID)
{
	QMenu *menu = (QMenu*) widgets[widgetID];
	if (!menu) {
		return NULL;
	}

	QString title = menu->title();
	std::string string = title.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

void CallPropagator::menuSetTitle (WidgetID widgetID, const char *title)
{
	QMenu *menu = (QMenu*) widgets[widgetID];
	if (!menu) {
		return;
	}

	menu->setTitle (title ?: "");
}

//--------------------
// QLabel
//--------------------
WidgetID CallPropagator::createLabel (WidgetID parentID, const char *text)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QLabel *label = new QLabel (parent);
	if (text) {
		label->setText (text ?: "");
	} 
	int index = widgetObjectCounter++;
	widgets[index] = label;

	connect (label, &QLabel::linkHovered, this, [index, label]() {
		(void)label;
		puts ("Qt: LABEL WAS HOVERED OVER");
		Event event;
		event.type = EventTypeMouseHover;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}

void CallPropagator::labelClear (WidgetID labelID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	label->clear();
}
const char* CallPropagator::labelText (WidgetID labelID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return NULL;
	}
	QString text = label->text();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}
void CallPropagator::labelSetText (WidgetID labelID, const char*string)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	label->setText (string ?: "");
}
bool CallPropagator::labelWordWrap (WidgetID labelID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return false;
	}
	return label->wordWrap();
}
void CallPropagator::labelSetWordWrap (WidgetID labelID, bool value)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	label->setWordWrap (value);
}

long CallPropagator::labelAlignment (WidgetID labelID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return 0;
	}
	return (long)label->alignment();
}

void CallPropagator::labelSetAlignment (WidgetID labelID, long value)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}

	Qt::Alignment alignment;
	if (value & 1) alignment |= Qt::AlignLeft;
	if (value & 2) alignment |= Qt::AlignRight;
	if (value & 4) alignment |= Qt::AlignCenter;
	if (value & 8) alignment |= Qt::AlignJustify;
	if (value & 0x20) alignment |= Qt::AlignTop;
	if (value & 0x40) alignment |= Qt::AlignBottom;
	if (value & 0x80) alignment |= Qt::AlignVCenter;
	if (value & 0x100) alignment |= Qt::AlignBaseline;

	label->setAlignment (alignment);
}

long CallPropagator::labelIndent (WidgetID labelID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return 0;
	}
	return label->indent();
}

long CallPropagator::labelMargin (WidgetID labelID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return 0;
	}
	return label->margin();
}

void CallPropagator::labelSetIndent (WidgetID labelID, long value)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	label->setIndent(value);
}

void CallPropagator::labelSetMargin (WidgetID labelID, long value)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	label->setMargin(value);
}

void CallPropagator::labelSetPixmap (WidgetID labelID, ObjectID pixmapID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	QPixmap *pixmap = (QPixmap*) objects[pixmapID];
	if (!pixmap) {
		return;
	}
	label->setPixmap (*pixmap);
}

void CallPropagator::labelSetImage (WidgetID labelID, ObjectID imageID)
{
	QLabel *label = (QLabel*) widgets[labelID];
	if (!label) {
		return;
	}
	QImage *image = (QImage*) objects[imageID];
	if (!image) {
		return;
	}
	label->setPixmap (QPixmap::fromImage(*image));
}

//--------------------
// QAbstractButton
//--------------------
const char *CallPropagator::abstractButtonText (WidgetID widgetID)
{
	QAbstractButton *abstractButton = (QAbstractButton *) widgets[widgetID];
	if (!abstractButton) {
		return NULL;
	}

	QString text = abstractButton->text();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

void CallPropagator::abstractButtonSetText (WidgetID widgetID, const char *text)
{
	QAbstractButton *abstractButton = (QAbstractButton *) widgets[widgetID];
	if (!abstractButton) {
		return;
	}

	abstractButton->setText(text ?: "");
}

bool CallPropagator::abstractButtonIsChecked (WidgetID widgetID)
{
	QAbstractButton *abstractButton = (QAbstractButton *) widgets[widgetID];
	if (!abstractButton) {
		return false;
	}

	return abstractButton->isChecked();
}

void CallPropagator::abstractButtonSetChecked (WidgetID widgetID, bool value)
{
	QAbstractButton *abstractButton = (QAbstractButton *) widgets[widgetID];
	if (!abstractButton) {
		return;
	}

	abstractButton->setChecked(value);
}

//--------------------
// QRadioButton
//--------------------
WidgetID CallPropagator::createRadioButton (WidgetID parentID, const char *text)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QRadioButton *button = new QRadioButton (parent);
	if (text) {
		button->setText (text ?: "");
	} 

	int index = widgetObjectCounter++;
	widgets[index] = button;

	connect (button, &QRadioButton::toggled, this, [index]() {
		Event event;
		event.type = EventTypeOptionToggled;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}

//--------------------
// QCheckBox
//--------------------
WidgetID CallPropagator::createCheckBox (WidgetID parentID, const char *text)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QCheckBox *button = new QCheckBox (parent);
	if (text) {
		button->setText (text ?: "");
	} 

	int index = widgetObjectCounter++;
	widgets[index] = button;

	connect (button, &QCheckBox::stateChanged, this, [index]() {
		Event event;
		event.type = EventTypeOptionStateChanged;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}
bool CallPropagator::checkBoxIsTristate (WidgetID widgetID)
{
	QCheckBox *checkbox = (QCheckBox *) widgets[widgetID];
	if (!checkbox) {
		return false;
	}

	return checkbox->isTristate();
}
void CallPropagator::checkBoxSetTristate (WidgetID widgetID, bool value)
{
	QCheckBox *checkbox = (QCheckBox *) widgets[widgetID];
	if (!checkbox) {
		return;
	}

	return checkbox->setTristate(value);
}
long CallPropagator::checkBoxCheckState (WidgetID widgetID)
{
	QCheckBox *checkbox = (QCheckBox *) widgets[widgetID];
	if (!checkbox) {
		return Qt::Unchecked;
	}

	return checkbox->checkState();
}
void CallPropagator::checkBoxSetCheckState (WidgetID widgetID, long value)
{
	QCheckBox *checkbox = (QCheckBox *) widgets[widgetID];
	if (!checkbox) {
		return;
	}
	Qt::CheckState state = Qt::Unchecked;
	if (value == 1) {
        	state = Qt::PartiallyChecked;
	} else if (value == 2) {
        	state = Qt::Checked;
	}

	return checkbox->setCheckState(state);
}

//--------------------
// QPushButton
//--------------------
WidgetID CallPropagator::createPushButton (WidgetID parentID, const char *text)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	// printf("Qt: BUTTON TEXT=%s\n",text);

	QPushButton *button = new QPushButton (parent);
	if (text) {
		button->setText (text ?: "");
	} 

	int index = widgetObjectCounter++;
	widgets[index] = button;

	connect (button, &QPushButton::clicked, this, [index]() {
		Event event;
		event.type = EventTypeMouseClick;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}

bool CallPropagator::pushButtonIsFlat (WidgetID widgetID)
{
	QPushButton *pushButton = (QPushButton *) widgets[widgetID];
	if (!pushButton) {
		return false;
	}

	return pushButton->isFlat();
}

void CallPropagator::pushButtonSetFlat (WidgetID widgetID, bool value)
{
	QPushButton *pushButton = (QPushButton *) widgets[widgetID];
	if (!pushButton) {
		return;
	}

	pushButton->setFlat(value);
}

bool CallPropagator::pushButtonIsDefault (WidgetID widgetID)
{
	QPushButton *pushButton = (QPushButton *) widgets[widgetID];
	if (!pushButton) {
		return false;
	}

	return pushButton->isDefault();
}

void CallPropagator::pushButtonSetDefault (WidgetID widgetID, bool value)
{
	QPushButton *pushButton = (QPushButton *) widgets[widgetID];
	if (!pushButton) {
		return;
	}

	pushButton->setDefault(value);
}

//--------------------
// QTableWidget
//--------------------
WidgetID CallPropagator::createTableWidget (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QTableWidget *table = new QTableWidget (parent);

	int index = widgetObjectCounter++;
	widgets[index] = table;

	connect (table, &QTableWidget::cellChanged, this, [index](int row, int column) {
		//printf ("QTableWidget cellChanged\n");
		Event event;
		event.type = EventTypeTableCellChanged;
		event.x = column;
		event.y = row;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (table, &QTableWidget::cellClicked, this, [index](int row, int column) {
		//printf ("QTableWidget cellClicked\n");
		Event event;
		event.type = EventTypeTableCellClicked;
		event.x = column;
		event.y = row;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (table, &QTableWidget::cellDoubleClicked, this, [index](int row, int column) {
		//printf ("QTableWidget cellDoubleClicked\n");
		Event event;
		event.type = EventTypeTableCellDoubleClicked;
		event.x = column;
		event.y = row;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (table, &QTableWidget::itemSelectionChanged, this, [index]() {
		//printf ("QTableWidget itemSelectionChanged\n");
		Event event;
		event.type = EventTypeTableItemSelectionChanged;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (table, &QTableWidget::currentCellChanged, this, [index](int row, int column, int previousRow, int previousColumn) {
		//printf ("QTableWidget currentCellChanged\n");
		Event event;
		event.type = EventTypeTableCurrentCellChanged;
		event.x = column;
		event.y = row;
		event.previousColumn = previousColumn;
		event.previousRow = previousRow;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}

const char *CallPropagator::tableWidgetItemText (ObjectID itemID)
{
	QTableWidgetItem *item = (QTableWidgetItem *)objects[itemID];
	if (!item) {
puts("No such item");
		return NULL;
	}
puts("Found the item");
	QString text = item->text();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}
void CallPropagator::tableWidgetItemSetText (ObjectID itemID, const char* text)
{
	QTableWidgetItem *item = (QTableWidgetItem *)objects[itemID];
	if (!item) {
		return;
	}
	item->setText(text ?: "");
}
ObjectID CallPropagator::createTableWidgetItem (const char *text)
{
	QTableWidgetItem *item = new QTableWidgetItem (text ?: "");
	if (item) {
		int index = widgetObjectCounter++;
		objects[index] = (QObject*) item;
		return index;
	} else {
		return -1;
	}
}

void CallPropagator::tableWidgetSetVerticalHeaderLabel (WidgetID tableID, const char *string, bool is_last)
{
	tableVerticalHeaderLabels.push_back(strdup(string) ?: "");

	// RULE: The Swift code sends each string one by one,
	// because it seems technically infeasible to send an array of them,
	// until the last one is sent which must have the boolean set.

	if (!is_last) {
		return;
	}

	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		tableVerticalHeaderLabels.clear();
		return;
	}

	QStringList list;
	unsigned n = tableVerticalHeaderLabels.size();
	for (unsigned i=0; i < n; i++) {
		const char *label = tableVerticalHeaderLabels.front();
		QString string = QString(label);
		list.append (string);
		tableVerticalHeaderLabels.pop_front();
	}

	table->setVerticalHeaderLabels (list);

	tableVerticalHeaderLabels.clear();
}

void CallPropagator::tableWidgetSetHorizontalHeaderLabel (WidgetID tableID, const char *string, bool is_last)
{
	tableHorizontalHeaderLabels.push_back(strdup(string) ?: "");

	// RULE: The Swift code sends each string one by one,
	// because it seems technically infeasible to send an array of them,
	// until the last one is sent which must have the boolean set.

	if (!is_last) {
		return;
	}

	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		tableHorizontalHeaderLabels.clear();
		return;
	}

	QStringList list;
	unsigned n = tableHorizontalHeaderLabels.size();
	for (unsigned i=0; i < n; i++) {
		const char *label = tableHorizontalHeaderLabels.front();
		QString string = QString(label);
		list.append (string);
		tableHorizontalHeaderLabels.pop_front();
	}

	table->setHorizontalHeaderLabels (list);

	tableHorizontalHeaderLabels.clear();
}

long CallPropagator::tableWidgetColumnCount (WidgetID tableID) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return 0;
	}

	return table->columnCount();
}
void CallPropagator::tableWidgetInsertColumn (WidgetID tableID, long column) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}

	table->insertColumn (column);
}
void CallPropagator::tableWidgetInsertRow (WidgetID tableID, long row) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}

	table->insertRow (row);
}
void CallPropagator::tableWidgetSetColumnCount (WidgetID tableID, long count) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}

	table->setColumnCount (count);
}
long CallPropagator::tableWidgetRowCount (WidgetID tableID) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return 0;
	}

	return table->rowCount();
}
void CallPropagator::tableWidgetSetRowCount (WidgetID tableID, long count) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}

	table->setRowCount (count);
}
long CallPropagator::tableWidgetCurrentColumn (WidgetID tableID) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return -1;
	}

	return table->currentColumn();
}
long CallPropagator::tableWidgetCurrentRow (WidgetID tableID) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return -1;
	}

	return table->currentRow();
}

void CallPropagator::tableWidgetSetCurrentCell (WidgetID tableID, long row, long column)
{
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}
	table->setCurrentCell (row, column);
}

void CallPropagator::tableWidgetSetCellWidget (WidgetID tableID, long row, long column, WidgetID widgetID) 
{
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}

	QWidget *widget = (QWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}

	table->setCellWidget (row, column, widget);
}

WidgetID CallPropagator::tableWidgetCellWidget (WidgetID tableID, long row, long column) 
{
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return -1;
	}

	QWidget *widget = table->cellWidget (row, column);
	if (!widget) {
		return -1;
	}

	WidgetID widgetID = lookupWidget (widget);

	// Send the Swift code an indicator of what subclass of QWidget this is.
	// We should already have a stub object on the Swift side.

	if (dynamic_cast<QLabel*>(widget)) {
		widgetID |= 1 << 24;
	}
	else if (dynamic_cast<QLineEdit*>(widget)) {
		widgetID |= 2 << 24;
	}
	else if (dynamic_cast<QTextEdit*>(widget)) {
		widgetID |= 3 << 24;
	}
	else if (dynamic_cast<QPushButton*>(widget)) {
		widgetID |= 4 << 24;
	}

	return widgetID;
}

WidgetID CallPropagator::lookupWidget (QWidget* widget)
{
	// Check whether we already have this QWidget on file.
	// If not, create an entry for it in the widgets dictionary.
	int index = -1;
	for (const auto & [key, value] : widgets) {
		if (((void*)value) == (void*)widget) {
			index = key;
			break;
		}
	}
	if (index == -1) {
		index = widgetObjectCounter++;
		widgets[index] = (QWidget*) widget;
        } 
	return index;
}

ObjectID CallPropagator::lookupObject (QObject* object)
{
	// Check whether we already have this QObject on file.
	// If not, create an entry for it in the objects dictionary.
	int index = -1;
	for (const auto & [key, value] : objects) {
		if (((void*)value) == (void*)object) {
			index = key;
			break;
		}
	}
	if (index == -1) {
		index = widgetObjectCounter++;
		objects[index] = (QObject*) object;
        } 
	return index;
}
DateID CallPropagator::lookupDate (QDate* date)
{
puts(__FUNCTION__);
	// Check whether we already have this QDate on file.
	// If not, create an entry for it in the dates dictionary.
	int index = -1;
	for (const auto & [key, value] : dates) {
		if (((void*)value) == (void*)date) {
			index = key;
puts("Found it");
			break;
		}
	}
	if (index == -1) {
		index = widgetObjectCounter++;
		dates[index] = date;
puts("Added it");
        } 
	return index;
}

//--------------------
// QTableWidgetItem
//--------------------
ObjectID CallPropagator::tableWidgetItem (WidgetID tableID, long row, long column) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return -1;
	}
	QTableWidgetItem *item = table->item(row, column);
        if (!item) {
                return -1;
	}
	int index = lookupObject((QObject*) item);
	return index;
}
ObjectID CallPropagator::tableWidgetCurrentItem (WidgetID tableID) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return -1;
	}

	QTableWidgetItem *item = table->currentItem();
        if (!item) {
                return -1;
	}
	int index = lookupObject((QObject*) item);
	return index;
}
void CallPropagator::tableWidgetSetItem (WidgetID tableID, long row, long column, ObjectID itemID) {
	QTableWidget *table = (QTableWidget*) widgets[tableID];
	if (!table) {
		return;
	}
	QTableWidgetItem *item = (QTableWidgetItem*) objects[itemID];
	if (!item) {
		return;
	}
	table->setItem (row, column, item);
}

//--------------------
// QTextEdit
//--------------------
WidgetID CallPropagator::createTextEdit (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QTextEdit *editor = new QTextEdit (parent);
        editor->setAcceptRichText (false);
        editor->setWordWrapMode (QTextOption::WordWrap);
        editor->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
        editor->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);

	int index = widgetObjectCounter++;
	widgets[index] = editor;

	connect (editor, &QTextEdit::currentCharFormatChanged, this, [index]() {
		//puts ("Qt: TEXT EDIT CURRENT CHAR FORMAT CHANGED");
		Event event;
		event.type = EventTypeEditorCharFormatChanged;
		event.recipient = index;
		swiftEventHandler (event);
	});

	connect (editor, &QTextEdit::textChanged, this, [index]() {
		//puts ("Qt: TEXT EDIT TEXT CHANGED");
		Event event;
		event.type = EventTypeEditorTextChanged;
		event.recipient = index;
		swiftEventHandler (event);
	});

	connect (editor, &QTextEdit::cursorPositionChanged, this, [index]() {
		//puts ("Qt: TEXT EDIT CURSOR POSN CHANGED");
		Event event;
		event.type = EventTypeEditorCursorMoved;
		event.recipient = index;
		swiftEventHandler (event);
	});

	connect (editor->document(), &QTextDocument::modificationChanged, this, [index]() {
		//puts ("Qt: TEXT EDIT WAS MODIFIED");
		Event event;
		event.type = EventTypeEditorModified;
		event.recipient = index;
		swiftEventHandler (event);
	});

	//connect(editor->document(), &QTextDocument::undoAvailable, actionUndo, &QAction::setEnabled);
	//connect(editor->document(), &QTextDocument::redoAvailable, actionRedo, &QAction::setEnabled);

	return index;
}

const char *CallPropagator::textEditToPlainText (WidgetID widgetID)
{
	QTextEdit *textEdit = (QTextEdit*) widgets[widgetID];
	if (!textEdit) {
		return NULL;
	}

	QString text = textEdit->toPlainText();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

const char *CallPropagator::textEditToHTML (WidgetID widgetID)
{
	QTextEdit *editor = (QTextEdit*) widgets[widgetID];
	if (!editor) {
		return NULL;
	}

	QString html = editor->toHtml();
	std::string string = html.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

void CallPropagator::textEditSetText (WidgetID widgetID, const char *text)
{
	QTextEdit *editor = (QTextEdit*) widgets[widgetID];
	if (!editor) {
		return;
	}

	editor->setText (text ?: "");
}

void CallPropagator::textEditSetAcceptRichText (WidgetID widgetID, bool accepts)
{
	QTextEdit *editor = (QTextEdit*) widgets[widgetID];
	if (!editor) {
		return;
	}

	editor->setAcceptRichText (accepts);
}

//--------------------
// QWebEngineView
//--------------------
WidgetID CallPropagator::createWebEngineView (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QWebEngineView *webview = new QWebEngineView (parent);
	//connect(reloadAction, &QAction::triggered, webview, &QWebEngineView::reload);
	//connect(backAction, &QAction::triggered, webview, &QWebEngineView::back);
	//connect(forwardAction, &QAction::triggered, webview, &QWebEngineView::forward);

	int index = widgetObjectCounter++;
	widgets[index] = webview;

	return index;
}

void CallPropagator::webEngineViewSetHTML (WidgetID widgetID, const char *text)
{
	QWebEngineView *webEngineView = (QWebEngineView*) widgets[widgetID];
	if (!webEngineView) {
		return;
	}

	webEngineView->setHtml (text ?: "");
}

//--------------------
// QLineEdit
//--------------------
const char *CallPropagator::lineEditText (WidgetID widgetID)
{
	QLineEdit *lineEdit = (QLineEdit*) widgets[widgetID];
	if (!lineEdit) {
		return NULL;
	}

	QString text = lineEdit->text();
	std::string string = text.toStdString();
	const char *cstring = string.c_str();
	char *copy = strdup(cstring);
	return copy;
}

void CallPropagator::lineEditSetText (WidgetID widgetID, const char *text)
{
	QLineEdit *lineEdit = (QLineEdit*) widgets[widgetID];
	if (!lineEdit) {
		return;
	}

	lineEdit->setText (text ?: "");
}

WidgetID CallPropagator::createLineEdit (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QLineEdit *lineEdit = new QLineEdit (parent);

	int index = widgetObjectCounter++;
	widgets[index] = lineEdit;

	return index;
}

//--------------------
// QGridLayout
//--------------------
ObjectID CallPropagator::createGridLayout (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}
	QGridLayout *layout = new QGridLayout(parent);
	int layoutID = widgetObjectCounter++;
	objects[layoutID] = (QObject*) layout;
	return layoutID;
}
void CallPropagator::gridLayoutAddWidget (ObjectID layoutID, WidgetID widgetID, long row, long column, long value)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}

	Qt::Alignment alignment;
	if (value & 1) alignment |= Qt::AlignLeft;
	if (value & 2) alignment |= Qt::AlignRight;
	if (value & 4) alignment |= Qt::AlignCenter;
	if (value & 8) alignment |= Qt::AlignJustify;
	if (value & 0x20) alignment |= Qt::AlignTop;
	if (value & 0x40) alignment |= Qt::AlignBottom;
	if (value & 0x80) alignment |= Qt::AlignVCenter;
	if (value & 0x100) alignment |= Qt::AlignBaseline;

	layout->addWidget (widget, row, column, alignment);
}
void CallPropagator::gridLayoutAddWidgetWithSpans (ObjectID layoutID, WidgetID widgetID, long row, long column, long rowspan, long colspan, long value)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	QWidget *widget = widgets[widgetID];
	if (!widget) {
		return;
	}

	Qt::Alignment alignment;
	if (value & 1) alignment |= Qt::AlignLeft;
	if (value & 2) alignment |= Qt::AlignRight;
	if (value & 4) alignment |= Qt::AlignCenter;
	if (value & 8) alignment |= Qt::AlignJustify;
	if (value & 0x20) alignment |= Qt::AlignTop;
	if (value & 0x40) alignment |= Qt::AlignBottom;
	if (value & 0x80) alignment |= Qt::AlignVCenter;
	if (value & 0x100) alignment |= Qt::AlignBaseline;

	layout->addWidget (widget, row, column, rowspan, colspan, alignment);
}
Rect CallPropagator::gridLayoutCellRect (ObjectID layoutID, long row, long column)
{
	Rect rect;
	rect.origin.x = 0;
	rect.origin.y = 0;
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		rect.size.width = 0;
		rect.size.height = 0;
		return rect;
	}
	QRect qrect = layout->cellRect (row, column);
	rect.size.width = qrect.width();
	rect.size.height = qrect.height();
	return rect;
}
long CallPropagator::gridLayoutRowCount (ObjectID layoutID)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->rowCount();
}
long CallPropagator::gridLayoutColumnCount (ObjectID layoutID)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->columnCount();
}
long CallPropagator::gridLayoutColumnMinimumWidth (ObjectID layoutID, long column)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->columnMinimumWidth(column);
}
long CallPropagator::gridLayoutColumnStretch (ObjectID layoutID, long column)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->columnStretch(column);
}
long CallPropagator::gridLayoutHorizontalSpacing (ObjectID layoutID)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->horizontalSpacing();
}
long CallPropagator::gridLayoutRowMinimumHeight (ObjectID layoutID, long row)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->rowMinimumHeight(row);
}
long CallPropagator::gridLayoutRowStretch (ObjectID layoutID, long row)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->rowStretch(row);
}
void CallPropagator::gridLayoutSetColumnMinimumWidth (ObjectID layoutID, long column, long minWidth)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setColumnMinimumWidth (column, minWidth);
}
void CallPropagator::gridLayoutSetColumnStretch (ObjectID layoutID, long column, long stretch)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setColumnStretch (column, stretch);
}
void CallPropagator::gridLayoutSetHorizontalSpacing (ObjectID layoutID, long horizontalSpacing)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setHorizontalSpacing (horizontalSpacing);
}
void CallPropagator::gridLayoutSetRowMinimumHeight (ObjectID layoutID, long row, long minHeight)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setRowMinimumHeight (row, minHeight);
}
void CallPropagator::gridLayoutSetRowStretch (ObjectID layoutID, long row, long stretch)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setRowStretch (row, stretch);
}
void CallPropagator::gridLayoutSetVerticalSpacing (ObjectID layoutID, long verticalSpacing)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return;
	}
	layout->setVerticalSpacing(verticalSpacing);
}
long CallPropagator::gridLayoutVerticalSpacing (ObjectID layoutID)
{
	QGridLayout *layout = (QGridLayout*) objects[layoutID];
	if (!layout) {
		return 0;
	}
	return layout->verticalSpacing();
}

//--------------------
// QCalendarWidget
//--------------------
WidgetID CallPropagator::createCalendarWidget (WidgetID parentID)
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QCalendarWidget *widget = new QCalendarWidget (parent);
	int index = widgetObjectCounter++;
	widgets[index] = widget;

	connect (widget, &QCalendarWidget::selectionChanged, this, [index]() {
		//puts ("Qt: CALENDAR SELECTION CHANGED");
		Event event;
		event.type = EventTypeSelectionChanged;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}
long CallPropagator::calendarWidgetSelectedDate (WidgetID widgetID)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return -1;
	}
	QDate date_ = widget->selectedDate();
	QDate *date = new QDate(date_);
	DateID dateID = lookupDate (date);
	if (dateID < 0) {
		dateID = widgetObjectCounter++;
		dates[dateID] = date;
	}
	return dateID;
}
void CallPropagator::calendarWidgetClearMaximumDate (WidgetID widgetID)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
	widget->clearMaximumDate();
#else
	// TODO Set reasonable value.
#endif
}
void CallPropagator::calendarWidgetClearMinimumDate (WidgetID widgetID)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
	widget->clearMinimumDate();
#else
	// TODO Set reasonable value.
#endif
}
long CallPropagator::calendarWidgetMonthShown (WidgetID widgetID)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->monthShown();
}
long CallPropagator::calendarWidgetYearShown (WidgetID widgetID)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->yearShown();
}
long CallPropagator::calendarWidgetHorizontalHeaderFormat (WidgetID widgetID) {
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return -1;
	}
	return (long) widget->horizontalHeaderFormat();
}
long CallPropagator::calendarWidgetVerticalHeaderFormat (WidgetID widgetID) {
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return -1;
	}
	return (long) widget->verticalHeaderFormat();
}
void CallPropagator::calendarWidgetSetHorizontalHeaderFormat (WidgetID widgetID, long value) {
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}
	QCalendarWidget::HorizontalHeaderFormat format;
	switch (value) {
	case 1: format = QCalendarWidget::SingleLetterDayNames; break;
	case 2: format = QCalendarWidget::ShortDayNames; break;
	case 3: format = QCalendarWidget::LongDayNames; break;
	default: format = QCalendarWidget::NoHorizontalHeader; break;
	}
	widget->setHorizontalHeaderFormat(format);
}
void CallPropagator::calendarWidgetSetVerticalHeaderFormat (WidgetID widgetID, long value) {
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}
	QCalendarWidget::VerticalHeaderFormat format;
	if (value == 1) {
		format = QCalendarWidget::ISOWeekNumbers;
	} else {
		format = QCalendarWidget::NoVerticalHeader;
	}
	widget->setVerticalHeaderFormat(format);
}
long CallPropagator::calendarWidgetFirstDayOfWeek(WidgetID widgetID)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return -1;
	}
	return (long) widget->firstDayOfWeek();
}
void CallPropagator::calendarWidgetSetFirstDayOfWeek(WidgetID widgetID, long value)
{
	QCalendarWidget *widget = (QCalendarWidget*) widgets[widgetID];
	if (!widget) {
		return;
	}
	Qt::DayOfWeek day;
	switch (value) {
	default:
	case 1: day = Qt::Monday; break;
	case 2: day = Qt::Tuesday; break;
	case 3: day = Qt::Wednesday; break;
	case 4: day = Qt::Thursday; break;
	case 5: day = Qt::Friday; break;
	case 6: day = Qt::Saturday; break;
	case 7: day = Qt::Sunday; break;
	}
	widget->setFirstDayOfWeek(day);
}

//--------------------
// QDate
//--------------------
DateID CallPropagator::createDate (long year, long month, long day)
{
	QDate *date = new QDate (year, month, day);
	int index = widgetObjectCounter++;
	dates[index] = date;
	return index;
}
DateID CallPropagator::createCurrentDate ()
{
	QDate currentDate = QDate::currentDate();
	QDate *date = new QDate (currentDate);
	int index = widgetObjectCounter++;
	dates[index] = date;
	return index;
}
long CallPropagator::dateDay (DateID dateID)
{
	QDate *date = (QDate*) dates[dateID];
	if (!date) {
		return -1;
	}
	return date->day();
}
long CallPropagator::dateMonth (DateID dateID)
{
	QDate *date = (QDate*) dates[dateID];
	if (!date) {
		return -1;
	}
	return date->month();
}
long CallPropagator::dateYear (DateID dateID)
{
	QDate *date = (QDate*) dates[dateID];
	if (!date) {
		return -1;
	}
	return date->year();
}

//--------------------
// QSlider
//--------------------
WidgetID CallPropagator::createSlider (WidgetID parentID) 
{
	QWidget *parent = widgets[parentID];
	if (!parent) {
		return -1;
	}

	QSlider *widget = new QSlider (parent);
	int index = widgetObjectCounter++;
	widgets[index] = widget;

	connect (widget, &QSlider::sliderPressed, this, [index]() {
		Event event;
		event.type = EventTypeSliderPressed;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (widget, &QSlider::sliderMoved, this, [index](int value) {
		Event event;
		event.type = EventTypeSliderMoved;
		event.x = value;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (widget, &QSlider::sliderReleased, this, [index]() {
		Event event;
		event.type = EventTypeSliderReleased;
		event.recipient = index;
		swiftEventHandler (event);
	});
	connect (widget, &QSlider::valueChanged, this, [index](int value) {
		Event event;
		event.type = EventTypeSliderValueChanged;
		event.x = value;
		event.recipient = index;
		swiftEventHandler (event);
	});

	return index;
}
long CallPropagator::sliderTickPosition (WidgetID widgetID) {
	QSlider *widget = (QSlider*) widgets[widgetID];
	if (!widget) {
		return -1;
	}
	return widget->tickPosition();
}
long CallPropagator::sliderTickInterval (WidgetID widgetID) {
	QSlider *widget = (QSlider*) widgets[widgetID];
	if (!widget) {
		return -1;
	}
	return widget->tickInterval();
}
void CallPropagator::sliderSetTickPosition (WidgetID widgetID, long value) {
	QSlider *widget = (QSlider*) widgets[widgetID];
	if (!widget) {
		return;
	}
	QSlider::TickPosition pos = QSlider::NoTicks;
	switch (value) {
	default:
	case 0: pos = QSlider::NoTicks; break;
	case 1: pos = QSlider::TicksAbove; break;
	case 2: pos = QSlider::TicksBelow; break;
	case 3: pos = QSlider::TicksBothSides; break;
	}
	widget->setTickPosition(pos);
}
void CallPropagator::sliderSetTickInterval (WidgetID widgetID, long value) {
	QSlider *widget = (QSlider*) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setTickInterval(value);
}

//--------------------
// QAbstractSlider
//--------------------
long CallPropagator::abstractSliderOrientation (WidgetID widgetID) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	Qt::Orientation value = widget->orientation();
	if (value == Qt::Horizontal) {
		return 1;
	} else {
		return 2;
	}
}
void CallPropagator::abstractSliderSetOrientation (WidgetID widgetID, long value) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return;
	}
	Qt::Orientation result = value == 1 ? Qt::Horizontal : Qt::Vertical;
	widget->setOrientation (result);
}
void CallPropagator::abstractSliderSetMaximum (WidgetID widgetID, long maximum) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setMaximum (maximum);
}
void CallPropagator::abstractSliderSetMinimum (WidgetID widgetID, long minimum) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setMinimum (minimum);
}
void CallPropagator::abstractSliderSetPageStep (WidgetID widgetID, long pageStep) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setPageStep (pageStep);
}
void CallPropagator::abstractSliderSetValue (WidgetID widgetID, long value) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setValue (value);
}
void CallPropagator::abstractSliderSetSliderDown (WidgetID widgetID, bool value) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setSliderDown (value);
}
bool CallPropagator::abstractSliderIsSliderDown (WidgetID widgetID) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return false;
	}
	return widget->isSliderDown ();
}
long CallPropagator::abstractSliderMaximum (WidgetID widgetID) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->maximum ();
}
long CallPropagator::abstractSliderMinimum (WidgetID widgetID) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->minimum ();
}
long CallPropagator::abstractSliderPageStep (WidgetID widgetID) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->pageStep ();
}
long CallPropagator::abstractSliderValue (WidgetID widgetID) {
	QAbstractSlider *widget = (QAbstractSlider *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->value ();
}

//--------------------
// QLCDNumber
//--------------------

WidgetID CallPropagator::createLCDNumber (WidgetID parentID, long numDigits) {
	QWidget *parent = (QWidget*) widgets[parentID];
	if (!parent) {
		return -1;
	}
	QLCDNumber *widget = new QLCDNumber (numDigits, parent);
	if (!widget) {
		return -1;
	}
	int index = widgetObjectCounter++;
	widgets[index] = widget;
	return index;
}
void CallPropagator::lcdNumberSetHexMode (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setHexMode();
}
void CallPropagator::lcdNumberSetBinMode (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setBinMode();
}
void CallPropagator::lcdNumberSetDecMode (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setDecMode();
}
void CallPropagator::lcdNumberSetOctMode (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setOctMode();
}
double CallPropagator::lcdNumberValue (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return 0.0;
	}
	return widget->value();
}
long CallPropagator::lcdNumberIntValue (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->intValue();
}
long CallPropagator::lcdNumberDigitCount (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return 0;
	}
	return widget->digitCount();
}
void CallPropagator::lcdNumberDisplayInt (WidgetID widgetID, long value) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->display ((int) value);
}
void CallPropagator::lcdNumberDisplayDouble (WidgetID widgetID, double value) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->display (value);
}
bool CallPropagator::lcdNumberSmallDecimalPoint (WidgetID widgetID) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return false;
	}
	return widget->smallDecimalPoint ();
}
void CallPropagator::lcdNumberSetSmallDecimalPoint (WidgetID widgetID, bool value) {
	QLCDNumber *widget = (QLCDNumber *) widgets[widgetID];
	if (!widget) {
		return;
	}
	widget->setSmallDecimalPoint (value);
}
