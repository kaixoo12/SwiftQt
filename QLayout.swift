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
// QLayout.swift
// QLayout is an abstract class.
// 

class QLayout : QObject
{
	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QLayout unknown event.");
		}
		return 0
	}

	func addWidget (_ widget : QWidget) {
		if let objectID = objectID, let widgetID = widget.widgetID {
			Conduit.layoutAddWidget (objectID, widgetID)
		}
	}

	func removeWidget (_ widget : QWidget) {
		if let objectID = objectID, let widgetID = widget.widgetID {
			Conduit.layoutRemoveWidget (objectID, widgetID)
		}
	}

	func spacing () -> Int {
		if let objectID = objectID {
			return Conduit.layoutSpacing (objectID)
		}
		return 0
	}

	func setSpacing (_ value: Int) {
		if let objectID = objectID {
			Conduit.layoutSetSpacing (objectID, value)
		}
	}

}
