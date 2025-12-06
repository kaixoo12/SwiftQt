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
// sampleBoxLayoutApp.swift
// 

import Foundation

/* This gives the C++ side access to the Swift application.
 */
func appMain (argc:Int, argv:[String]) -> some ApplicationDelegate
{
	print ("argc=\(argc)")
	print ("argv=\(argv)")
	return SampleBoxLayoutApp()
}

class SampleBoxLayoutApp : ApplicationDelegate {

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
	var tableLabel : QLabel?
	var imageView : QLabel?
	var webEngineView : QWebEngineView? 
	var centralWidget : QWidget?
	var leftmostWidget : QWidget?
	var radioButton : QRadioButton?
	var checkBox : QCheckBox?

	var mainHorizontalBoxLayout : QHBoxLayout?
	var verticalBoxLayout1 : QVBoxLayout?

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
	 * Lays out the user interface.
	 */
	func layoutUI () {
		if let window = window {
			let windowWidth : Int = window.windowWidth ()
			let windowHeight : Int = window.windowHeight ()
			print ("Swift: LAYING OUT UI, WINDOW IS \(windowWidth)x\(windowHeight)")
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
			weak var weakSelf = self

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
			let action6 = viewMenu.addAction ("Update status bar")
			action6!.triggeredHandler = { [weakSelf] in
				weakSelf?.statusBar?.showMessage ("A status bar message...", 10 * 1000 /* milliseconds */)
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

		window = QMainWindow (x: 100, y: 100, width: 810, height: 600)
		if let window = window {
			let releaseString = SwiftQt.release()
			window.setTitle("Sample App using Box Layouts built with SwiftQt \(releaseString)")

			createMenus()

			statusBar = QStatusBar (window, "This is the status bar.")
			window.setStatusBar (statusBar!)
		
			// Create box layouts and their contents
			centralWidget = QWidget(window)
			mainHorizontalBoxLayout = QHBoxLayout(centralWidget!)

			leftmostWidget = QWidget(window)
			leftmostWidget!.setMinimumSize (Size(200,1))
			verticalBoxLayout1 = QVBoxLayout(leftmostWidget!)
			verticalBoxLayout1!.setSpacing(5)

			mainHorizontalBoxLayout!.addWidget (leftmostWidget!)

			webEngineView = QWebEngineView (window)
			webEngineView!.setHTML ("<html><h1>This is a QWebEngineView.</h1> This is a QWebEngineView.  <p><i>This is a QWebEngineView.</i> <p><b>This is a QWebEngineView.</b><img src=https://apod.nasa.gov/apod/image/2310/WitchHead_Alharbi_3051.jpg >")
			mainHorizontalBoxLayout!.addWidget (webEngineView!)
			webEngineView!.setMinimumSize (Size(200,1))

			imageView = QLabel(window, "")
			let image = QImage("PIA25970.tif")
			print ("image loaded, size is \(image.width())x\(image.height())")

			// This also works.
			//let pixmap = QPixmap("PIA25970.tif")
			//print ("pixmap loaded, size is \(pixmap.width())x\(pixmap.height())")

			imageView!.setImage(image)
			mainHorizontalBoxLayout!.addWidget (imageView!)

			table = QTableWidget(window)
			table!.setMinimumSize (Size(200,1))
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
			mainHorizontalBoxLayout!.addWidget (table!)

			tableLabel = QLabel (window, "QLabel")
			tableLabel!.setStyleSheet ("background-color : red; color : yellow;");
			table!.setCellWidget (5, 0, tableLabel!)

			label1 = QLabel (window, "A QLabel w/word wrap, left/bottom aligned")
			label1!.setStyleSheet ("background-color : cyan; color : #008;");
			label1!.setWordWrap (true)
			label1!.setAlignment (Qt.AlignLeft + Qt.AlignBottom)
			verticalBoxLayout1?.addWidget(label1!)

			button1 = QPushButton (window, "Regular QPushButton")
			button1!.clickedHandler = { [self] in
				let string = self.button1!.text()
				print ("Button \"\(string)\" clicked.")
				window.setWindowTitle ("This is a test")
				SwiftQt.infoPopup ("Hello World")
			}
			button1!.setStyleSheet ("background-color : white; color : #080;");
			verticalBoxLayout1?.addWidget(button1!)

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
				label1?.setText("Label1")
			}
			verticalBoxLayout1?.addWidget(button2!)

			button3 = QPushButton (window, "Default QPushButton")
			button3!.setDefault (true)
			button3!.clickedHandler = { [self] in
				let string = self.button3!.text()
				print ("Button \"\(string)\" clicked.")
				label1?.clear()
				QApplication.beep()
			}
			verticalBoxLayout1?.addWidget(button3!)

			radioButton = QRadioButton (window, "QRadioButton")
			radioButton!.toggledHandler = { [self] in
				let value = radioButton!.isChecked()
				print ("The radio button was toggled, isChecked=\(value)")
			}
			verticalBoxLayout1?.addWidget(radioButton!)

			checkBox = QCheckBox (window, "QCheckBox")
			checkBox!.stateChangedHandler = { [self] in
				let checkState = checkBox!.checkState() // 3 possible values
				var string = "?"
				switch (checkState) {
				case Qt.Checked: 
					string = "checked"
				case Qt.PartiallyChecked: 
					string = "partiallychecked"
				default: 
					string = "unchecked"
				}
				print ("The checkbox was toggled, checkstate=\(string)")
			}
			verticalBoxLayout1?.addWidget(checkBox!)

			editor = QTextEdit (window)
			editor?.setText ("QTextEdit\nSed ut perspiciatis, unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo.")
			verticalBoxLayout1?.addWidget(editor!)

			textField = QLineEdit (window)
			textField?.setText ("QLineEdit text field")
			verticalBoxLayout1?.addWidget(textField!)

			window.setCentralWidget(centralWidget!)
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
		print("SampleBoxLayoutApp setup")
	}
	func tearDown () {
		print("SampleBoxLayoutApp teardown")
	}
}
