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
// QPushButton.swift
// 

class QPushButton : QAbstractButton
{
	convenience init (_ parent: QWidget, _ string: String) {
		self.init ()
		if let parentID = parent.widgetID {
			widgetID = Conduit.createPushButton (parentID, string)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeMouseClick:
				clickedHandler()

			default: 
				print ("QPushButton unknown event.");
		}
		return 0
	}

	func isFlat () -> Bool {
		if let widgetID = widgetID {
			return Conduit.pushButtonIsFlat(widgetID)
		}
		return false
	}

	func setFlat (_ flat: Bool) {
		if let widgetID = widgetID {
			Conduit.pushButtonSetFlat (widgetID, flat)
		}
	}

	func isDefault () -> Bool {
		if let widgetID = widgetID {
			return Conduit.pushButtonIsDefault(widgetID)
		}
		return false
	}

	func setDefault (_ value: Bool) {
		if let widgetID = widgetID {
			Conduit.pushButtonSetDefault (widgetID, value)
		}
	}

}
