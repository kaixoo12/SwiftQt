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
// QCheckBox.swift
// 

class QCheckBox : QAbstractButton
{
	var stateChangedHandler : ()->Void = {
		print ("State changed.")
	}

	convenience init (_ parent: QWidget, _ string: String) {
		self.init ()
		if let parentID = parent.widgetID {
			widgetID = Conduit.createCheckBox (parentID, string)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeOptionStateChanged:
				stateChangedHandler()

			default: 
				print ("QCheckBox unknown event.");
		}
		return 0
	}

	func isTristate () -> Bool {
		if let widgetID = widgetID {
			return Conduit.checkBoxIsTristate(widgetID)
		}
		return false
	}

	func setTristate (_ value: Bool) {
		if let widgetID = widgetID {
			Conduit.checkBoxSetTristate (widgetID, value)
		}
	}

	func checkState () -> Int {
		if let widgetID = widgetID {
			return Conduit.checkBoxCheckState(widgetID)
		}
		return Qt.Unchecked
	}

	func setCheckState (_ value: Int) {
		if value != Qt.Checked && value != Qt.Unchecked && value != Qt.PartiallyChecked {
			return
		}
		if let widgetID = widgetID {
			Conduit.checkBoxSetCheckState (widgetID, value)
		}
	}

}
