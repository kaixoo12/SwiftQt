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
// QLabel.swift

class QLabel : QWidget
{
	convenience init (_ parent: QWidget, _ text: String?) {
		self.init ()
		if let parentID = parent.widgetID {
			widgetID = Conduit.createLabel (parentID, text ?? "")
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeMouseHover:
				print ("QLabel hover event."); // TODO

			default: 
				print ("QLabel unknown event.");
		}
		return 0
	}

	func clear () {
		if let widgetID = widgetID {
			Conduit.labelClear (widgetID)
		}
	}
	func text () -> String {
		if let widgetID = widgetID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.labelText (widgetID)
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
			Conduit.labelSetText (widgetID, text)
		}
	}
	func setImage (_ image: QImage) {
		if let widgetID = widgetID, let imageID = image.objectID {
			Conduit.labelSetImage (widgetID, imageID)
		}
	}
	func setPixmap (_ pixmap: QPixmap) {
		if let widgetID = widgetID, let pixmapID = pixmap.objectID {
			Conduit.labelSetPixmap (widgetID, pixmapID)
		}
	}

	func wordWrap () -> Bool {
		if let widgetID = widgetID {
			return Conduit.labelWordWrap (widgetID)
		}
		return false
	}
	func setWordWrap (_ value: Bool) {
		if let widgetID = widgetID {
			return Conduit.labelSetWordWrap (widgetID, value)
		}
	}
	func indent () -> Int {
		if let widgetID = widgetID {
			return Conduit.labelIndent (widgetID)
		}
		return 0
	}
	func setIndent (_ value: Int) {
		if let widgetID = widgetID {
			return Conduit.labelSetIndent (widgetID, value)
		}
	}
	func margin () -> Int {
		if let widgetID = widgetID {
			return Conduit.labelMargin (widgetID)
		}
		return 0
	}
	func setMargin (_ value: Int) {
		if let widgetID = widgetID {
			return Conduit.labelSetMargin (widgetID, value)
		}
	}
	func alignment () -> Int {
		if let widgetID = widgetID {
			return Conduit.labelAlignment (widgetID)
		}
		return Qt.AlignNone
	}
	func setAlignment (_ value: Int) {
		if let widgetID = widgetID {
			return Conduit.labelSetAlignment (widgetID, value)
		}
	}
}
