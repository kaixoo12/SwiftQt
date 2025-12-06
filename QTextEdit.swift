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

class QTextEdit : QWidget
{
	var formatChangedHandler: ()->Void = {
		print ("QTextEdit format changed!");
	}
	var cursorMovedHandler: ()->Void = {
		print ("QTextEdit cursor moved!");
	}
	var modifiedHandler: ()->Void = {
		print ("QTextEdit modified!");
	}
	var textChangedHandler: ()->Void = {
		print ("QTextEdit text changed!");
	}
	//----------

	convenience init (_ parent: QMainWindow) {
		self.init ()
		if let windowID = parent.widgetID {
			widgetID = Conduit.createTextEdit (windowID)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeEditorCharFormatChanged:
				formatChangedHandler()

			case EventTypeEditorCursorMoved:
				cursorMovedHandler()

			case EventTypeEditorModified:
				modifiedHandler()

			case EventTypeEditorTextChanged:
				textChangedHandler()

			default: 
				print ("QTextEdit unknown event.");
		}
		return 0
	}

	func toPlainText () -> String {
		if let widgetID = widgetID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.textEditToPlainText(widgetID)
			if let unsafeString = unsafeString {
				let safeString : String = String (cString:unsafeString);
				unsafeString.deallocate()
				return safeString
			}
		}
		return ""
	}

	func toHtml () -> String {
		if let widgetID = widgetID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.textEditToHTML(widgetID)
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
			Conduit.textEditSetText (widgetID, text)
		}
	}


}
