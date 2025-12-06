/*=========================================================================
 * This file is a demo of SwiftQt.
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
// sampleApp.swift
// 

import Foundation

/* This gives the C++ side access to the Swift application.
 */
func appMain (argc:Int, argv:[String]) -> some ApplicationDelegate
{
	print ("argc=\(argc)")
	print ("argv=\(argv)")
	return SampleApp()
}

class SampleApp : ApplicationDelegate {

	var window : QMainWindow?
	var menuBar : QMenuBar?
	var statusBar : QStatusBar?
	var label1 : QLabel?
	var button1 : QPushButton?
	var button2 : QPushButton?
	var button3 : QPushButton?
	var editor : QTextEdit?
	var textField : QLineEdit?
	var table : QTableWidget?
	var imageView : QLabel?
	var webEngineView : QWebEngineView? 

	required init () {
	}

	deinit {
	}

	func name () -> String {
		var className : String = NSStringFromClass(type(of: self))
		if className.contains(".") {
			let parts = className.components(separatedBy:".")
			className = parts[parts.count-1]
		}
		return className
	}

	/*------------------------------------------------------------------
	 * Manually lays out the user interface.
	 */
	func layoutUI () {
		if let window = window, let menuBar = menuBar {
			let menuBarHeight : Int = menuBar.height()

			if let label1=label1, 
				let button1=button1, let button2=button2, let button3=button3, 
				let textField=textField, 
				let editor=editor, 
				let webEngineView=webEngineView,
				let table = table,
				let statusBar = statusBar,
				let imageView = imageView
			{
				let statusBarHeight : Int = statusBar.height() 

				let windowWidth : Int = window.windowWidth ()
				let windowHeight : Int = window.windowHeight ()
				print ("Swift: LAYING OUT UI, WINDOW IS \(windowWidth)x\(windowHeight)")

				let spacing : Int = 8

				let ytop : Int = spacing + menuBarHeight
				var y : Int = ytop
				let totalHeight : Int = windowHeight 

				label1.setFrame (Rect.new(20, y, 200, 50))
				y += 50 + spacing
				button1.setFrame (Rect.new(20, y, 200, 50))
				y += 50 + spacing
				button2.setFrame (Rect.new(20, y, 200, 50))
				y += 50 + spacing
				button3.setFrame (Rect.new(20, y, 200, 50))
				y += 50 + spacing
				textField.setFrame (Rect.new(20, y, 200, 50))
				y += 50 + spacing

				let editorHeight = totalHeight - y - spacing - statusBarHeight
				editor.setFrame (Rect.new(20, y, 200, editorHeight))

				let verticalViewWidth = (windowWidth - 240 - spacing)/3

				let webviewHeight = totalHeight - spacing - ytop
				var x = 240
				webEngineView.setFrame (Rect.new(x, ytop, verticalViewWidth, webviewHeight))
				x += verticalViewWidth

				table.setFrame (Rect.new(x, ytop, verticalViewWidth, webviewHeight))
				x += verticalViewWidth

				imageView.setFrame (Rect.new(x, ytop, verticalViewWidth, webviewHeight))
			}
		}
	}

	/*------------------------------------------------------------------
	 * Called whenever the window is resized.
	 */
	func windowResized (_ width: Int, _ height: Int) {
		print ("Swift: WINDOW RESIZED TO \(width)x\(height)");
		layoutUI ();
	}


	func createMenus ()
	{
		if let window = window {
			// Set up menu
			let fileMenu : QMenu = QMenu("&File")
			let action1 = fileMenu.addAction ("&Open")
			action1!.triggeredHandler = {
				print ("FILE->OPEN")
			}
			let action2 = fileMenu.addAction ("Exit")
			action2!.setShortcut (QKeySequence(QKeySequence.Quit()))
			action2!.triggeredHandler = {
				print ("FILE->EXIT")
				QApplication.quit()
			}

			let editMenu : QMenu = QMenu("&Edit")
			let action3 = editMenu.addAction ("Copy")
			action3!.triggeredHandler = {
				print ("EDIT->COPY")
			}
			let action4 = editMenu.addAction ("Cut")
			action4!.triggeredHandler = {
				print ("EDIT->CUT")
			}
			let action5 = editMenu.addAction ("Paste")
			action5!.triggeredHandler = {
				print ("EDIT->PASTE")
			}

			let viewMenu : QMenu = QMenu("&View")
			let action6 = viewMenu.addAction ("Toggle status bar")
			action6!.triggeredHandler = {
				print ("VIEW->STATUSBAR")
			}

			let helpMenu : QMenu = QMenu("&Help")
			let action7 = helpMenu.addAction ("&About")
			action7!.triggeredHandler = {
				print ("HELP->ABOUT")
				SwiftQt.infoPopup ("This is sampleApp.")
			}

			menuBar = QMenuBar ()
			menuBar!.addMenu (fileMenu)
			menuBar!.addMenu (editMenu)
			menuBar!.addMenu (viewMenu)
			menuBar!.addMenu (helpMenu)
			window.setMenuBar (menuBar!)
		}
	}

	/*------------------------------------------------------------------
	 * Constructs the GUI and sets event handlers.
	 */
	func constructUI () {
		print ("sampleApp: Asked to construct the UI.")

		window = QMainWindow (x: 100, y: 100, width: 800, height: 600)
		if let window = window {

			createMenus()
		
			statusBar = QStatusBar (window, "This is the status bar.")
			window.setStatusBar (statusBar!)
		
			table = QTableWidget(window)
			table!.setColumnCount (4)
			table!.setRowCount (80)
			table!.setHorizontalHeaderLabels (["A", "B", "C", "D", "E"])
			table!.setVerticalHeaderLabels (["fee", "fie", "foe", "fum"])
			weak var weakTable : QTableWidget? = table
			table!.cellChangedHandler = { row, column in
				print ("QTableWidget cellChanged at \(row),\(column)")

				let item : QTableWidgetItem? = weakTable?.currentItem()
				if let item = item {
					let text = item.text() ?? ""
					print ("Text was changed to: \(text)")
				} else {
					print ("Didn't get item")
				}
			}
			table!.cellClickedHandler = { row, column in
				let widget = weakTable?.cellWidget(row, column)
				if widget != nil {
					print ("Got widget!")
				} else {
					print ("Didn't get widget")
				}
			}

			label1 = QLabel (window, "A QLabel w/word wrap, left/bottom aligned")
			label1!.setStyleSheet ("background-color : cyan; color : #008;");
			label1!.setWordWrap (true)
			label1!.setAlignment (Qt.AlignLeft + Qt.AlignBottom)

			button1 = QPushButton (window, "Regular QPushButton")
			button1!.clickedHandler = { [self] in
				let string = self.button1!.text()
				print ("Button \"\(string)\" clicked.")
				window.setWindowTitle ("This is a test")
				SwiftQt.infoPopup ("Hello World")
			}
			button1!.setStyleSheet ("background-color : white; color : #080;");

			button2 = QPushButton (window, "Flat QPushButton")
			button2!.setFlat (true)
			button2!.clickedHandler = { [self] in
				let string = self.button2!.text()
				print ("Button \"\(string)\" clicked.")
				
				if SwiftQt.convenienceQuestion ("This is a question popup", "Do you agree?") {
					window.setTitle("You pressed YES")
				} else {
					window.setTitle("You pressed NO")
				}
			}

			button3 = QPushButton (window, "Default QPushButton")
			button3!.setDefault (true)
			button3!.clickedHandler = { [self] in
				let string = self.button3!.text()
				print ("Button \"\(string)\" clicked.")
				label1?.clear()
				QApplication.beep()
			}

			editor = QTextEdit (window)
			editor?.setText ("QTextEdit\nSed ut perspiciatis, unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo.")

			textField = QLineEdit (window)
			textField?.setText ("QLineEdit text field")

			webEngineView = QWebEngineView (window)
			webEngineView!.setHTML ("<html><h1>This is a QWebEngineView.</h1> This is a QWebEngineView.  <p><i>This is a QWebEngineView.</i> <p><b>This is a QWebEngineView.</b><img src=https://apod.nasa.gov/apod/image/2310/WitchHead_Alharbi_3051.jpg >")

			imageView = QLabel(window, "")

			let image = QImage("PIA25970.tif")
			print ("image loaded, size is \(image.width())x\(image.height())")

			let pixmap = QPixmap("PIA25970.tif")
			print ("pixmap loaded, size is \(pixmap.width())x\(pixmap.height())")

			imageView!.setImage(image)

			let releaseString = SwiftQt.release()
			window.setTitle("Sample App using SwiftQt \(releaseString)")
			window.show()
		}
	}

	func willExit () {
		print ("Swift: Application will exit.")
	}

	func processEvent (_ event: Event) -> Int
	{
		// This just handles windows events at the meta level.

		let eventType = event.type

		if eventType == EventTypeAppLaunched {
			return 0
		}
		else if eventType == EventTypeWindowCreated {
			return 0
		}
		else if eventType == EventTypeWindowClosed {
			return 0
		}
		else if eventType == EventTypeWindowShown {
			layoutUI ();
			return 0
		}

		let totalWindows = QMainWindow.totalWindows ()
		if totalWindows == 0 {
			print ("Swift: There are no windows.")
		}

		return -1
	}
	func setUp () {
		print("SampleApp setup")
	}
	func tearDown () {
		print("SampleApp teardown")
	}
}
