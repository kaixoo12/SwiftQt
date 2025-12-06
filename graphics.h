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

// SwiftQt
// graphics.h
// Types shared between C and Swift sides of the library.

#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <uchar.h>

// Each sides has their own version of window and font structs and classes.
typedef int WidgetID;
typedef int ObjectID;
typedef long DateID;
typedef long Coord;
typedef uint32_t RGB;
typedef int32_t Unichar;

typedef struct // 16 bytes
{
	Coord x;
	Coord y;
} Point;

typedef struct // 16 bytes
{
	Coord width;
	Coord height;
} Size;

typedef struct // 32 bytes
{
	Point origin;
	Size size;
} Rect;

// Types of events sent from C layer to Swift layer.
typedef enum {
	EventTypeAppLaunched = 100,
	EventTypeAppExiting = 101,

	EventTypeActionTriggered = 150,

	EventTypeWindowCreated = 200,
	EventTypeWindowClosed = 201,
	EventTypeWindowResized = 202,
	EventTypeWindowShown = 203,
	EventTypeWindowHidden = 204,

	EventTypeMouseButtonDown = 300,
	EventTypeMouseButtonUp = 301,
	EventTypeMouseClick = 302,
	EventTypeMouseHover = 303,

	EventTypePointerEntered = 304,
	EventTypePointerLeft = 305,
	EventTypePointerMoved = 306, // button down
	EventTypePointerMovedPassively = 307, // button NOT down

	EventTypeScrollWheelChanged = 308,
	EventTypeSelectionChanged = 309,

	EventTypeKeyDown = 309, // Just ASCII for now.
	EventTypeKeyUp = 310,

	// QAbstractButton descendants
	EventTypeOptionToggled = 320, // QRadioButton 
	EventTypeOptionStateChanged = 321, // QCheckBox

	// QTextEdit
	EventTypeEditorCharFormatChanged = 400,
	EventTypeEditorCursorMoved = 401,
	EventTypeEditorModified = 402,
	EventTypeEditorTextChanged = 403,

	// QTableWidget
	EventTypeTableCellChanged = 500, 
	EventTypeTableCellClicked = 501, 
	EventTypeTableCellDoubleClicked = 502, 
	EventTypeTableCurrentCellChanged = 503,
	EventTypeTableItemSelectionChanged = 504,

	// QScrollBar
	EventTypeVerticalScrollbarChanged = 510,

	// QAbstractSlider
	EventTypeSliderValueChanged = 520,
	EventTypeSliderMoved = 521,
	EventTypeSliderPressed = 522,
	EventTypeSliderReleased = 523,

} EventType;

typedef struct event
{
	WidgetID recipient; // can be QWidget or QObject
	EventType type;
	Coord x; // AKA column
	Coord y; // AKA row 
	Coord width;
	Coord height;
	long previousRow;
	long previousColumn;
	const char **argv;
	int argc;
} Event;

Point Point_new(Coord,Coord) 	__attribute__((swift_name("Point.init(_:_:)")));
Point Point_zero(void) 	__attribute__((swift_name("getter:Point.zero()")));

Size Size_new(Coord,Coord) 	__attribute__((swift_name("Size.init(_:_:)")));
Size Size_zero(void) 	__attribute__((swift_name("getter:Size.zero()")));
bool Size_equals(Size, Size)	__attribute__((swift_name("Size.equals(_:_:)")));

Rect Rect_new(Coord,Coord,Coord,Coord)  	__attribute__((swift_name("Rect.new(_:_:_:_:)")));
Rect Rect_zero(void)	__attribute__((swift_name("getter:Rect.zero()")));
void Rect_print(Rect)	__attribute__((swift_name("Rect.print(_:)")));
bool Rect_equals(Rect, Rect)	__attribute__((swift_name("Rect.equals(_:_:)")));
bool Rect_containsPoint (Rect rect, Coord x, Coord y)	__attribute__((swift_name("Rect.containsPoint(_:_:_:)")));

RGB Color_lighten(RGB);
RGB Color_darken(RGB);

#endif
