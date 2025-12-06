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

class QWidget : QObject
{
	var widgetID : WidgetID?
	static var widgets: [WidgetID: QWidget] = [:]
	static let idMask : Int32 = 0x00ffffff
	static let typeMask : Int32 = 0x7f000000

	// Not used
	static func manufactureWidget (fromID widgetID: WidgetID) -> QWidget {
		switch ((widgetID & typeMask) >> 24) {
		case 1: 
			let label : QLabel = QLabel()
			label.widgetID = widgetID
			return label
		case 2: 
			return QLineEdit()
		case 3: 
			return QTextEdit()
		case 4: 
			return QPushButton()
		case 5: 
			let widget : QScrollBar = QScrollBar ()
			widget.widgetID = widgetID
			return widget
		default: 
			return QWidget()
		}
	}

	static func isKnownWidget (_ widgetID: WidgetID) -> Bool {
		return widgets[widgetID & idMask] != nil
	}

	static func lookupWidget (_ widgetID: WidgetID) -> QWidget? {
		return widgets[widgetID & idMask] 
	}

	static func registerWidget (_ widgetID: WidgetID, _ widget: QWidget) {
		widgets[widgetID & idMask] = widget
	}

	static func unregisterWidget (_ widgetID: WidgetID) {
		widgets[widgetID & idMask] = nil
	}

	convenience init (_ parent: QWidget) {
		self.init ()
		if let parentID = parent.widgetID {
			widgetID = Conduit.createWidget (parentID)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	deinit {
		if let widgetID = widgetID {
			QWidget.unregisterWidget (widgetID)
		}
	}

	func move (_ x: Int, _ y: Int) {
		if let widgetID = widgetID {
			Conduit.move (widgetID, x, y)
		}
	}

	func raise () {
		if let widgetID = widgetID {
			Conduit.raise (widgetID)
		}
	}

	func lower () {
		if let widgetID = widgetID {
			Conduit.lower (widgetID)
		}
	}

	func resize (_ width: Int, _ height: Int) {
		if let widgetID = widgetID {
			Conduit.resize (widgetID, width, height)
		}
	}

	func frame (_ rect: Rect) -> Rect {
		if let widgetID = widgetID {
			return Conduit.frame (widgetID)
		}
		return Rect.zero
	}

	func setFrame (_ rect: Rect) {
		if let widgetID = widgetID {
			Conduit.setFrame (widgetID, rect)
		}
	}

	func isHidden () -> Bool {
		if let widgetID = widgetID {
			return Conduit.isHidden (widgetID)
		}
		return false
	}

	func setHidden (_ value: Bool) {
		if let widgetID = widgetID {
			Conduit.setHidden (widgetID, value)
		}
	}

	func width () -> Coord {
		if let widgetID = widgetID {
			return Conduit.width (widgetID)
		}
		return 0
	}

	func height () -> Coord {
		if let widgetID = widgetID {
			return Conduit.height (widgetID)
		}
		return 0
	}

	func styleSheet () -> String {
		if let widgetID = widgetID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.styleSheet(widgetID)
			if let unsafeString = unsafeString {
				let safeString : String = String (cString:unsafeString);
				unsafeString.deallocate()
				return safeString
			}
		}
		return ""
	}

	func setStyleSheet (_ string: String) {
		if let widgetID = widgetID {
			Conduit.setStyleSheet(widgetID, string)
		}
	}

	func minimumSize (_ size: Size) -> Size {
		if let widgetID = widgetID {
			return Conduit.minimumSize (widgetID)
		}
		return Size.zero
	}

	func setMinimumSize (_ size: Size) {
		if let widgetID = widgetID {
			Conduit.setMinimumSize (widgetID, size)
		}
	}

	func setMaximumHeight(_ maxh: Int) {
		if let widgetID = widgetID {
			Conduit.setMaximumHeight (widgetID, maxh)
		}
	}
	func setMaximumWidth(_ maxw: Int) {
		if let widgetID = widgetID {
			Conduit.setMaximumWidth (widgetID, maxw)
		}
	}
	func setMinimumHeight(_ minh: Int) {
		if let widgetID = widgetID {
			Conduit.setMinimumHeight (widgetID, minh)
		}
	}
	func setMinimumWidth(_ minw: Int) {
		if let widgetID = widgetID {
			Conduit.setMinimumWidth (widgetID, minw)
		}
	}
	func setParent(_ parent: QWidget?) {
		if let widgetID = widgetID {
			if let parent = parent {
				if let parentID = parent.widgetID {
					Conduit.setParent(widgetID, parentID)
				}
				else {
					// Remove our widget from its parent.
					Conduit.setParent(widgetID, -1)
				}
			}
		}
	}
	func parentWidget () -> QWidget? {
		if let widgetID = widgetID {
			let parentID = Conduit.parentWidget (widgetID)
			if parentID < 0 {
				return nil
			}
			let parent : QWidget? = QWidget.lookupWidget(parentID)
			return parent
		}
		return nil
	}

}
