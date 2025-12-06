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

class QMainWindow : QWidget 
{
	let menuBarHeight = 44
	var statusBar : QStatusBar? = nil

	required init (x: Coord, y: Coord, width: Coord, height: Coord) {
		super.init ()
		widgetID = Conduit.createWindow (x, y, width, height)
		// Don't register the widget since it is a window.
	}

	deinit {
		// Don't unregister window.
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QMainWindow unknown event.");
		}
		return 0
	}

	static func totalWindows () -> Int {
		return Int(Conduit.totalWindows ())
	}

	func setTitle (_ title : String) {
		if let widgetID = widgetID {
			Conduit.windowSetTitle (widgetID, title)
		}
	}

	func show () {
		if let widgetID = widgetID {
			Conduit.showWindow (widgetID)
		}
	}

	/*! This is necessary in order to provide an alternative layout.
	 *  First create the central widget, then apply desired layout to it,
	 *  then call setCentralWidget. (Note, this isn't necessary for QWindow.)
	 */
	func setCentralWidget (_ widget: QWidget) {
		if let widgetID = widgetID, let subwidgetID = widget.widgetID {
			return Conduit.windowSetCentralWidget (widgetID, subwidgetID)
		}
	}

	func setMinimumSize (_ width: Int, _ height: Int) {
		if let widgetID = widgetID {
			return Conduit.windowSetMinimumSize (widgetID, width, height)
		}
	}
	func setMaximumSize (_ width: Int, _ height: Int) {
		if let widgetID = widgetID {
			return Conduit.windowSetMaximumSize (widgetID, width, height)
		}
	}

	func windowWidth () -> Int {
		if let widgetID = widgetID {
			return Conduit.windowWidth (widgetID)
		}
		return 0
	}

	func windowHeight () -> Int {
		if let widgetID = widgetID {
			return Conduit.windowHeight (widgetID)
		}
		return 0
	}

	func setMenuBar (_ menuBar: QMenuBar) {
		if let windowID = widgetID { 
			if let menuBarID = menuBar.widgetID {
				Conduit.windowSetMenuBar (windowID, menuBarID)
			}
		}
	}

	func setStatusBar (_ statusBar: QStatusBar) {
		if let windowID = widgetID { 
			if let statusBarID = statusBar.widgetID {
				Conduit.windowSetStatusBar (windowID, statusBarID)
			}
		}
	}

	func windowTitle () -> String {
		if let widgetID = widgetID {
			let unsafeString : UnsafePointer<CChar>? = Conduit.windowTitle(widgetID)
			if let unsafeString = unsafeString {
				let safeString : String = String (cString:unsafeString);
				unsafeString.deallocate()
				return safeString
			}
		}
		return ""
	}

	func setWindowTitle (_ title: String) {
		if let widgetID = widgetID {
			Conduit.windowSetTitle (widgetID, title)
		}
	}
}

