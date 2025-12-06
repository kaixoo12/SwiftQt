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
// QTableWidgetItem.swift
// 

class QTableWidgetItem : QObject
{
	convenience init (_ string: String?) {
		self.init ()
		objectID = Conduit.createTableWidgetItem (string ?? "")
		QObject.registerObject (objectID!, self)
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QTableWidgetItem unknown event.");
		}
		return 0
	}

	func text () -> String? {
		if let objectID = objectID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.tableWidgetItemText (objectID)
			if let unsafeString = unsafeString {
				let safeString : String = String (cString:unsafeString);
				unsafeString.deallocate()
				return safeString
			}
		} 
		return nil
	}

	func setText (_ text: String) {
		if let objectID = objectID {
			return Conduit.tableWidgetItemSetText (objectID, text)
		} 
	}

	func setForegroundColor (_ color: QColor) {
		// TODO
	}
	func setBackgroundColor (_ color: QColor) {
		// TODO
	}
	func setFlags (_ flags: Int) {
		// TODO
	}

	override init () {
		super.init ()
	}
}
