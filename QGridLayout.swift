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
// QGridLayout.swift
// 

class QGridLayout : QLayout
{
	convenience init (_ parent: QWidget) {
		self.init ()
		if let widgetID = parent.widgetID {
			objectID = Conduit.createGridLayout (widgetID)
			QWidget.registerObject (objectID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QGridLayout unknown event.");
		}
		return 0
	}

	func addWidget (_ widget : QWidget, 
				row: Int,
				column: Int,
				alignment: Int = 0) {
		if let objectID = objectID, let subwidgetID = widget.widgetID {
			Conduit.gridLayoutAddWidget (objectID, subwidgetID, row, column, alignment)
		}
	}
	func addWidget (_ widget : QWidget, 
				row: Int,
				column: Int,
				rowSpan: Int,
				columnSpan: Int,
				alignment: Int = 0) {
		if let objectID = objectID, let subwidgetID = widget.widgetID {
			Conduit.gridLayoutAddWidgetWithSpans (objectID, subwidgetID, row, column, rowSpan, columnSpan, alignment)
		}
	}

	func cellRect (_ row: Int, _ column: Int) -> Rect {
		if let objectID = objectID {
			return Conduit.gridLayoutCellRect (objectID, row, column)
		}
		return Rect.zero
	}
	func columnCount () -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutColumnCount (objectID)
		}
		return 0
	}
	func rowCount () -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutRowCount (objectID)
		}
		return 0
	}
	func columnMinimumWidth (_ column: Int) -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutColumnMinimumWidth (objectID, column)
		}
		return 0
	}
	func rowMinimumHeight (_ row: Int) -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutRowMinimumHeight (objectID, row)
		}
		return 0
	}
	func columnStretch (_ column: Int) -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutColumnStretch (objectID, column)
		}
		return 0
	}
	func rowStretch (_ row: Int) -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutRowStretch (objectID, row)
		}
		return 0
	}
	func horizontalSpacing () -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutHorizontalSpacing (objectID)
		}
		return 0
	}
	func verticalSpacing () -> Int {
		if let objectID = objectID {
			return Conduit.gridLayoutVerticalSpacing (objectID)
		}
		return 0
	}
	func setColumnMinimumWidth (column: Int, _ value: Int)  {
		if let objectID = objectID {
			Conduit.gridLayoutSetColumnMinimumWidth (objectID, column, value)
		}
	}
	func setRowMinimumHeight (row: Int, _ value: Int)  {
		if let objectID = objectID {
			Conduit.gridLayoutSetRowMinimumHeight (objectID, row, value)
		}
	}
	func setColumnStretch (column: Int, _ value: Int)  {
		if let objectID = objectID {
			Conduit.gridLayoutSetColumnStretch (objectID, column, value)
		}
	}
	func setRowStretch (row: Int, _ value: Int)  {
		if let objectID = objectID {
			Conduit.gridLayoutSetRowStretch (objectID, row, value)
		}
	}
	func setHorizontalSpacing (_ value: Int)  {
		if let objectID = objectID {
			Conduit.gridLayoutSetHorizontalSpacing (objectID, value)
		}
	}
	func setVerticalSpacing (_ value: Int)  {
		if let objectID = objectID {
			Conduit.gridLayoutSetVerticalSpacing (objectID, value)
		}
	}
}
