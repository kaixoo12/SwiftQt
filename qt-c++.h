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

#ifndef QT_CPP_H
#define QT_CPP_H

#include <QWidget>
#include <map>
#include <deque>

#include "MainWindow.h"
extern "C" {
#include "graphics.h"
}

class CallPropagator : QObject {
Q_OBJECT

public:
	CallPropagator ();
	~CallPropagator ();

	//---------------------------------------------------------------------
	// QDate
	//---------------------------------------------------------------------
	DateID createDate (long,long,long);
	DateID createCurrentDate ();
	long dateDay (DateID);
	long dateMonth (DateID);
	long dateYear (DateID);

	//---------------------------------------------------------------------
	// QCalendarWidget
	//---------------------------------------------------------------------
	WidgetID createCalendarWidget (WidgetID);
	void calendarWidgetClearMaximumDate(WidgetID);
	void calendarWidgetClearMinimumDate(WidgetID);
	long calendarWidgetMonthShown(WidgetID);
	long calendarWidgetYearShown(WidgetID);
	long calendarWidgetHorizontalHeaderFormat (WidgetID widgetID);
	long calendarWidgetVerticalHeaderFormat (WidgetID widgetID);
	void calendarWidgetSetHorizontalHeaderFormat (WidgetID widgetID, long value);
	void calendarWidgetSetVerticalHeaderFormat (WidgetID widgetID, long value);
	long calendarWidgetFirstDayOfWeek(WidgetID);
	void calendarWidgetSetFirstDayOfWeek(WidgetID, long);
	long calendarWidgetSelectedDate(WidgetID);

	//---------------------------------------------------------------------
	// QLayout (abstract class)
	//---------------------------------------------------------------------
	void layoutAddWidget (WidgetID, WidgetID);
	void layoutRemoveWidget (WidgetID, WidgetID);
	long layoutSpacing (ObjectID);
	void layoutSetSpacing (ObjectID, long);

	//---------------------------------------------------------------------
	// QGridLayout
	//---------------------------------------------------------------------
	ObjectID createGridLayout (WidgetID);
	void gridLayoutAddWidget(ObjectID,WidgetID,long row,long column,long alignment);
	void gridLayoutAddWidgetWithSpans(ObjectID,WidgetID,long row,long column,long rowspan,long colspan,long alignment);
	Rect gridLayoutCellRect(ObjectID,long,long);
	long gridLayoutColumnCount(ObjectID);
	long gridLayoutColumnMinimumWidth(ObjectID, long);
	long gridLayoutColumnStretch(ObjectID, long);
	long gridLayoutHorizontalSpacing(ObjectID);
	long gridLayoutRowCount(ObjectID);
	long gridLayoutRowMinimumHeight(ObjectID, long);
	long gridLayoutRowStretch(ObjectID, long);
	void gridLayoutSetColumnMinimumWidth(ObjectID,long, long);
	void gridLayoutSetColumnStretch(ObjectID,long, long);
	void gridLayoutSetHorizontalSpacing(ObjectID,long);
	void gridLayoutSetRowMinimumHeight(ObjectID,long, long);
	void gridLayoutSetRowStretch(ObjectID,long, long);
	void gridLayoutSetVerticalSpacing(ObjectID,long);
	long gridLayoutVerticalSpacing(ObjectID);

	//---------------------------------------------------------------------
	// QBoxLayout
	//---------------------------------------------------------------------
	ObjectID createBoxLayout (WidgetID, long direction);
	void boxLayoutAddWidget (ObjectID, WidgetID, int stretch, int alignment);
	void boxLayoutAddSpacing (ObjectID, long);
	void boxLayoutAddStretch (ObjectID, long);
	void boxLayoutAddStrut (ObjectID, long);

	//---------------------------------------------------------------------
	// QHBoxLayout
	//---------------------------------------------------------------------
	ObjectID createHBoxLayout (WidgetID);

	//---------------------------------------------------------------------
	// QVBoxLayout
	//---------------------------------------------------------------------
	ObjectID createVBoxLayout (WidgetID);

	//---------------------------------------------------------------------
	// QPixmap
	//---------------------------------------------------------------------
	ObjectID createPixmapWithPath(const char*path);
	ObjectID createPixmapWithSize(Coord,Coord);
	bool pixmapLoad (ObjectID objectID, const char *path);
	Coord pixmapWidth (ObjectID objectID);
	Coord pixmapHeight (ObjectID objectID);
	Coord pixmapDepth (ObjectID objectID);

	//---------------------------------------------------------------------
	// QImage
	//---------------------------------------------------------------------
	ObjectID createImage(const char*path);
	bool imageLoad (ObjectID objectID, const char *path);
	bool imageIsGrayscale (ObjectID objectID);
	Coord imageWidth (ObjectID objectID);
	Coord imageHeight (ObjectID objectID);
	Coord imageDepth (ObjectID objectID);

	//---------------------------------------------------------------------
	// QMainWindow
	//---------------------------------------------------------------------
	WidgetID createWindow (Coord x, Coord y, Coord width, Coord height);
	int totalWindows(void);
	MainWindow *lookupWindow (int index);
	MainWindow *mainWindow (void);
        Coord windowWidth (WidgetID);
        Coord windowHeight (WidgetID);
        void windowSetMinimumSize (WidgetID, Coord, Coord);
        void windowSetMaximumSize (WidgetID, Coord, Coord);
	const char *windowTitle (WidgetID);
	void windowSetTitle (WidgetID, const char *);
	void windowSetCentralWidget (WidgetID, WidgetID);

	//---------------------------------------------------------------------
	// QStatusBar
	//---------------------------------------------------------------------
	WidgetID createStatusBar (WidgetID parentID, const char *text = nullptr);
	void windowSetStatusBar (WidgetID, WidgetID);
	void windowSetMenuBar (WidgetID, WidgetID);
	void statusBarShowMessage (WidgetID statusBarID, const char *text = nullptr, long duration = 0);

	//---------------------------------------------------------------------
	// QGroupBox
	//---------------------------------------------------------------------
	WidgetID createGroupBox (WidgetID, const char* title);
	long groupBoxAlignment (WidgetID groupBoxID);
	void groupBoxSetAlignment (WidgetID groupBoxID, long);
	const char* groupBoxTitle (WidgetID);
	void groupBoxSetTitle (WidgetID, const char*);

	//---------------------------------------------------------------------
	// QLabel
	//---------------------------------------------------------------------
	WidgetID createLabel (WidgetID parent, const char *text = nullptr);
	void labelClear (WidgetID);
	const char* labelText (WidgetID);
	void labelSetText (WidgetID, const char*);
	void labelSetPixmap (WidgetID, ObjectID); 
	void labelSetImage (WidgetID, ObjectID); 
	bool labelWordWrap (WidgetID labelID);
	void labelSetWordWrap (WidgetID labelID, bool value);
	long labelAlignment (WidgetID labelID);
	void labelSetAlignment (WidgetID labelID, long value);
	long labelIndent (WidgetID labelID);
	void labelSetIndent (WidgetID labelID, long value);
	long labelMargin (WidgetID labelID);
	void labelSetMargin (WidgetID labelID, long value);

	//---------------------------------------------------------------------
	// QMenuBar
	//---------------------------------------------------------------------
	WidgetID createMenuBar (void);
	void menuBarAddMenu (WidgetID parent, WidgetID menu);

	//---------------------------------------------------------------------
	// QMenu
	//---------------------------------------------------------------------
	WidgetID createMenu (const char *title = nullptr);
	const char *menuTitle (WidgetID);
	void menuSetTitle (WidgetID, const char *);
	void menuAddAction (WidgetID, ObjectID);
	void menuAddSeparator (WidgetID);

	//---------------------------------------------------------------------
	// QAction
	//---------------------------------------------------------------------
	ObjectID createAction (const char*title);
	void actionSetShortcut (ObjectID actionID, ObjectID keySequenceID);

	//---------------------------------------------------------------------
	// QColor
	//---------------------------------------------------------------------
	ObjectID createColor (long red, long green, long blue);

	//---------------------------------------------------------------------
	// QKeySequence
	//---------------------------------------------------------------------
	ObjectID createKeySequence (const char*);

	//---------------------------------------------------------------------
	// QAbstractButton
	//---------------------------------------------------------------------
	const char *abstractButtonText (WidgetID);
	void abstractButtonSetText (WidgetID, const char *);
	bool abstractButtonIsChecked (WidgetID);
	void abstractButtonSetChecked (WidgetID, bool);

	//---------------------------------------------------------------------
	// QRadioButton
	//---------------------------------------------------------------------
	WidgetID createRadioButton (WidgetID parentID, const char *text = nullptr);

	//---------------------------------------------------------------------
	// QCheckBox
	//---------------------------------------------------------------------
	WidgetID createCheckBox (WidgetID parentID, const char *text = nullptr);
	bool checkBoxIsTristate (WidgetID);
	void checkBoxSetTristate (WidgetID, bool);
	long checkBoxCheckState (WidgetID);
	void checkBoxSetCheckState (WidgetID, long);

	//---------------------------------------------------------------------
	// QPushButton
	//---------------------------------------------------------------------
	WidgetID createPushButton (WidgetID parentID, const char *text = nullptr);
	bool pushButtonIsFlat (WidgetID);
	void pushButtonSetFlat (WidgetID, bool);
	bool pushButtonIsDefault (WidgetID);
	void pushButtonSetDefault (WidgetID, bool);

	//---------------------------------------------------------------------
	// QTableWidgetItem
	//---------------------------------------------------------------------
	ObjectID createTableWidgetItem (const char*);
	const char *tableWidgetItemText (ObjectID);
	void tableWidgetItemSetText (ObjectID,const char*);

	//---------------------------------------------------------------------
	// QTableWidget
	//---------------------------------------------------------------------
	WidgetID createTableWidget (WidgetID parent);
	long tableWidgetColumnCount (WidgetID);
	void tableWidgetSetColumnCount (WidgetID,long);
	long tableWidgetRowCount (WidgetID);
	void tableWidgetSetRowCount (WidgetID,long);
	long tableWidgetCurrentColumn (WidgetID);
	long tableWidgetCurrentRow (WidgetID);
	void tableWidgetSetCurrentCell (WidgetID,long,long);
	ObjectID tableWidgetItem (WidgetID,long,long);
	void tableWidgetSetItem (WidgetID,long,long,ObjectID);
	ObjectID tableWidgetCurrentItem (WidgetID);
	WidgetID tableWidgetCellWidget (WidgetID,long,long);
	void tableWidgetSetCellWidget (WidgetID,long,long,WidgetID);
	void tableWidgetInsertColumn (WidgetID tableID, long column);
	void tableWidgetInsertRow (WidgetID tableID, long row);
	void tableWidgetSetVerticalHeaderLabel (WidgetID tableID, const char *, bool is_last);
	void tableWidgetSetHorizontalHeaderLabel (WidgetID tableID, const char *, bool is_last);

	//---------------------------------------------------------------------
	// QTextEdit
	//---------------------------------------------------------------------
	WidgetID createTextEdit (WidgetID parent);
	const char *textEditToPlainText (WidgetID);
	const char *textEditToHTML (WidgetID);
	void textEditSetReadOnly (WidgetID, bool);
	void textEditSetText (WidgetID, const char *);
	//void textEditSetHTML (WidgetID, const char *);
	void textEditSetAcceptRichText (WidgetID, bool);

	//---------------------------------------------------------------------
	// QWebEngineView
	//---------------------------------------------------------------------
	WidgetID createWebEngineView (WidgetID parentID);
	void webEngineViewSetHTML (WidgetID, const char *);

	//---------------------------------------------------------------------
	// QLineEdit
	//---------------------------------------------------------------------
	WidgetID createLineEdit (WidgetID parentID);
	const char *lineEditText (WidgetID);
	void lineEditSetText (WidgetID, const char *);

	//---------------------------------------------------------------------
	// QWidget
	//---------------------------------------------------------------------
	WidgetID createWidget (WidgetID);
	void setFrame (WidgetID, Rect);
	Rect frame (WidgetID);
	void setMinimumSize (WidgetID, Size);
	Size minimumSize (WidgetID);
	Coord height (WidgetID);
	Coord width (WidgetID);
	void move (WidgetID, Coord, Coord);
	void resize (WidgetID, Coord, Coord);
	void setHidden (WidgetID, bool);
	bool isHidden (WidgetID);
	void setStyleSheet (WidgetID, const char*);
	const char *styleSheet (WidgetID);
	void raise (WidgetID);
	void lower (WidgetID);
	WidgetID layout (WidgetID);
	void setLayout (WidgetID, ObjectID);
	void setMaximumHeight(WidgetID, long maxh);
	void setMaximumWidth(WidgetID, long maxw);
	void setMinimumHeight(WidgetID, long minh);
	void setMinimumWidth(WidgetID, long minw);
	void setParent(WidgetID, WidgetID);
	WidgetID parentWidget(WidgetID);

	//---------------------------------------------------------------------
	// QSlider
	//---------------------------------------------------------------------
	WidgetID createSlider (WidgetID parentID);
	long sliderTickPosition (WidgetID);
	long sliderTickInterval (WidgetID);
	void sliderSetTickPosition (WidgetID, long);
	void sliderSetTickInterval (WidgetID, long);

	//---------------------------------------------------------------------
	// QAbstractSlider
	//---------------------------------------------------------------------
	void abstractSliderSetMaximum (WidgetID, long maximum);
	void abstractSliderSetMinimum (WidgetID, long minimum);
	void abstractSliderSetPageStep (WidgetID, long pageStep);
	void abstractSliderSetValue (WidgetID, long value);
	void abstractSliderSetSliderDown (WidgetID, bool value);
	bool abstractSliderIsSliderDown(WidgetID);
	long abstractSliderMaximum (WidgetID);
	long abstractSliderMinimum (WidgetID);
	long abstractSliderPageStep (WidgetID);
	long abstractSliderValue (WidgetID);
	long abstractSliderOrientation (WidgetID);
	void abstractSliderSetOrientation (WidgetID,long);

	//---------------------------------------------------------------------
	// QLCDNumber
	//---------------------------------------------------------------------
	WidgetID createLCDNumber (WidgetID, long);
	void lcdNumberSetHexMode (WidgetID);
	void lcdNumberSetBinMode (WidgetID);
	void lcdNumberSetDecMode (WidgetID);
	void lcdNumberSetOctMode (WidgetID);
	double lcdNumberValue (WidgetID);
	long lcdNumberIntValue (WidgetID);
	long lcdNumberDigitCount (WidgetID);
	void lcdNumberDisplayInt (WidgetID, long);
	void lcdNumberDisplayDouble (WidgetID, double);
	bool lcdNumberSmallDecimalPoint (WidgetID);
	void lcdNumberSetSmallDecimalPoint (WidgetID,bool);

	//---------------------------------------------------------------------
	// Included for convenience
	//---------------------------------------------------------------------
	void conveniencePopup (const char* title, const char* message);
	bool convenienceQuestion (const char* title, const char* message);

private:
	WidgetID lookupWidget (QWidget*);
	ObjectID lookupObject (QObject*);
	DateID lookupDate (QDate*);
	int widgetObjectCounter = 100;
	std::map<WidgetID, QWidget*> widgets;
	std::map<ObjectID, QObject*> objects;
	std::map<DateID, QDate*> dates;
	std::deque<const char*> tableHorizontalHeaderLabels;
	std::deque<const char*> tableVerticalHeaderLabels;

public slots:
	// None

};

#endif
