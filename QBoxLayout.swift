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
// QBoxLayout.swift
// 

class QBoxLayout : QLayout
{
	// QBoxLayout::Direction
	static let LeftToRight = 0
	static let RightToLeft = 1
	static let TopToBottom = 2
	static let BottomToTop = 3

	convenience init (_ direction: Int, _ parent: QMainWindow) {
		self.init ()
		if let windowID = parent.widgetID {
			objectID = Conduit.createBoxLayout (windowID, direction)
			QWidget.registerObject (objectID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QBoxLayout unknown event.");
		}
		return 0
	}

	// Note, Box layout's addWidget has 3 parameters, Layout's has 1.
	func addWidget (_ widget : QWidget, stretch: Int = 0, alignment: Int = 0) {
		if let objectID = objectID, let subwidgetID = widget.widgetID {
			Conduit.boxLayoutAddWidget (objectID, subwidgetID, stretch, alignment)
		}
	}

	func addSpacing (_ value: Int) {
		if let objectID = objectID {
			Conduit.boxLayoutAddSpacing (objectID, value)
		}
	}
	func addStretch (_ value: Int = 0) {
		if let objectID = objectID {
			Conduit.boxLayoutAddStretch (objectID, value)
		}
	}
	func addStrut (_ value: Int) {
		if let objectID = objectID {
			Conduit.boxLayoutAddStrut (objectID, value)
		}
	}
}
