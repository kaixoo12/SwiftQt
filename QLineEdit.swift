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

class QLineEdit : QWidget
{
	convenience init (_ parent: QMainWindow) {
		self.init ()
		if let windowID = parent.widgetID {
			widgetID = Conduit.createLineEdit (windowID)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QLineEdit unknown event.");
		}
		return 0
	}

	func setPlaceholder (_ string: String) {
		// TODO
	}

	func text () -> String {
		if let widgetID = widgetID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.lineEditText(widgetID)
			if let unsafeString = unsafeString {
				let safeString : String = String (cString:unsafeString);
				unsafeString.deallocate()
				return safeString
			}
		}
		return ""
	}

	func setText (_ text: String) {
		if let widgetID = widgetID {
			Conduit.lineEditSetText (widgetID, text)
		}
	}

}
