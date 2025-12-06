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
// QAction.swift

class QAction : QObject
{
	var triggeredHandler: ()->Void = {
		print ("ACTION WAS TRIGGERED")
	}

	required convenience init (_ text: String) {
		self.init ()
		objectID = Conduit.createAction (text)
		if let objectID = objectID {
			QObject.registerObject (objectID, self)
		} else {
			print ("QAction is missing an object ID.");
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeActionTriggered:
				triggeredHandler ()

			// TODO
			// changed
			// hovered
			// toggled
			default: 
				print ("QAction unknown event.");
		}
		return 0
	}

	func setShortcut (_ sequence: QKeySequence) {
		if let objectID = objectID, let sequenceID = sequence.objectID {
			Conduit.actionSetShortcut (objectID, sequenceID)
		}
	}

	func checked () -> Bool {
		// return Conduit.(widgetID, string);
		return false
	}
	func setChecked (_ value:Bool) {
		// Conduit.(widgetID, string);
	}
	func enabled () -> Bool {
		// return Conduit.(widgetID, string);
		return false
	}
	func setEnabled (_ value:Bool) {
		// Conduit.(widgetID, string);
	}

}
