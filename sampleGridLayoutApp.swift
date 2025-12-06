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
// sampleGridLayoutApp.swift
// 

import Foundation

/* This gives the C++ side access to the Swift application.
 */
func appMain (argc:Int, argv:[String]) -> some ApplicationDelegate
{
	print ("argc=\(argc)")
	print ("argv=\(argv)")
	return SampleGridLayoutApp()
}

class SampleGridLayoutApp : ApplicationDelegate {

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
	var radioButton : QRadioButton?
	var checkbox : QCheckBox?
	var groupbox : QGroupBox?
	var calendar : QCalendarWidget?
	var lcdNumber : QLCDNumber?
	var slider : QSlider?

	var mainLayout : QGridLayout?

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

	func layoutUI () {
	}

	/*------------------------------------------------------------------
	 * Called whenever the window is resized.
	 */
	func windowResized (_ width: Int, _ height: Int) {
		print ("Swift: WINDOW RESIZED TO \(width)x\(height)");
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
				weakSelf?.webEngineView?.setParent(nil)
				weakSelf?.webEngineView = nil
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

		window = QMainWindow (x: 100, y: 100, width: 1000, height: 600)
		if let window = window {
			var columnNumber = 0

			let releaseString = SwiftQt.release()
			window.setTitle("Sample App using QGridLayout built with SwiftQt \(releaseString)")

			createMenus()

			statusBar = QStatusBar (window, "This is the status bar.")
			window.setStatusBar (statusBar!)
		
			// Create box layouts and their contents
			centralWidget = QWidget(window)
			mainLayout = QGridLayout(centralWidget!)

			label1 = QLabel (window, "This is a QLabel with word wrap and custom style sheet")
			label1!.setStyleSheet ("background-color : cyan; color : #008;");
			label1!.setWordWrap (true)
			label1!.setAlignment (Qt.AlignCenter)
			mainLayout?.addWidget(label1!, row: 0, column: columnNumber)

			textField = QLineEdit (window)
			textField?.setText ("QLineEdit text field")
			mainLayout?.addWidget(textField!, row: 1, column: columnNumber)

			groupbox = QGroupBox ("QGroupBox", window)
			groupbox?.setStyleSheet ("""
				QGroupBox { 
					border: 1px solid #ccc;
					border-radius: 8px; 
					margin-top: 12px;
					font: italic;
					padding: 12px;
				}
				QGroupBox::title { 
					height: 20px;
					top: -10px;
					padding: 0px 5px 0px 5px;
					border: 1px solid #ccc;
					border-radius: 5px;
					color: yellow;
					background-color: black;
					subcontrol-position: top center;
					/*padding: 13px;*/
				} 
			""")
			mainLayout?.addWidget(groupbox!, row: 2, column: columnNumber, rowSpan: 3, columnSpan: 1)

			calendar = QCalendarWidget(groupbox!)
			calendar!.setMinimumSize (Size(200,250))
			calendar!.setHorizontalHeaderFormat(QCalendarWidget.SingleLetterDayNames)
			mainLayout?.addWidget(calendar!, row: 5, column: columnNumber, rowSpan: 3, columnSpan: 1)
			weak var weakSelf = self
			calendar!.selectionChangedHandler = {
				if let date = weakSelf?.calendar?.selectedDate() {
					let y = date.year()
					let m = date.month()
					let d = date.day()
					print ("year=\(y) month=\(m) day=\(d)")
				}
			}
			columnNumber += 1

			let verticalLayout = QVBoxLayout(groupbox!)

			button1 = QPushButton (groupbox!, "Regular QPushButton")
			button1!.clickedHandler = { [self] in
				let string = self.button1!.text()
				print ("Button \"\(string)\" clicked.")
				window.setWindowTitle ("This is a test")
				SwiftQt.infoPopup ("Hello World")
			}
			button1!.setStyleSheet ("background-color : white; color : #080;");
			verticalLayout.addWidget (button1!)

			button2 = QPushButton (groupbox!, "Flat QPushButton")
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
			verticalLayout.addWidget (button2!)

			button3 = QPushButton (groupbox!, "Default QPushButton")
			button3!.setDefault (true)
			button3!.clickedHandler = { [self] in
				let string = self.button3!.text()
				print ("Button \"\(string)\" clicked.")
				label1?.clear()
				QApplication.beep()
			}
			verticalLayout.addWidget (button3!)

			radioButton = QRadioButton (groupbox!, "QRadioButton")
			radioButton!.toggledHandler = { [self] in
				let value = radioButton!.isChecked()
				print ("The radio button was toggled, isChecked=\(value)")
			}
			verticalLayout.addWidget (radioButton!)

			checkbox = QCheckBox (groupbox!, "QCheckBox")
			checkbox!.stateChangedHandler = { [self] in
				let checkState = checkbox!.checkState() // 3 possible values
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
			verticalLayout.addWidget (checkbox!)

			webEngineView = QWebEngineView (window)
			webEngineView!.setHTML ("<html><h1>This is a QWebEngineView.</h1> This is a QWebEngineView.  <p><i>This is a QWebEngineView.</i> <p><b>This is a QWebEngineView.</b><img src=https://apod.nasa.gov/apod/image/2310/WitchHead_Alharbi_3051.jpg >")
			webEngineView!.setMinimumSize (Size(150,1))
			mainLayout!.addWidget (webEngineView!, row: 0, column: columnNumber, rowSpan: 8, columnSpan: 1)
			columnNumber += 1

			imageView = QLabel(window, "")
			let image = QImage("PIA25970.tif")
			print ("image loaded, size is \(image.width())x\(image.height())")
			mainLayout!.addWidget (imageView!, row: 0, column: columnNumber)
			columnNumber += 1

			// This also works.
			//let pixmap = QPixmap("PIA25970.tif")
			//print ("pixmap loaded, size is \(pixmap.width())x\(pixmap.height())")

			imageView!.setImage(image)
			mainLayout!.addWidget (imageView!, row: 0, column: columnNumber, rowSpan: 8, columnSpan: 1)
			columnNumber += 1

			table = QTableWidget(window)
			table!.setMinimumSize (Size(150,1))
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
			mainLayout!.addWidget (table!, row: 0, column: columnNumber, rowSpan: 8, columnSpan: 1)
			columnNumber += 1

			tableLabel = QLabel (window, "QLabel")
			tableLabel!.setStyleSheet ("background-color : red; color : yellow;");
			table!.setCellWidget (5, 0, tableLabel!)

			lcdNumber = QLCDNumber(8, window)
			if let lcdNumber=lcdNumber {
				mainLayout?.addWidget (lcdNumber, row: 0, column: columnNumber)
				lcdNumber.setSmallDecimalPoint(true)
				lcdNumber.display(3.14159)
				lcdNumber.setStyleSheet ("background-color : black; color : green;")
				lcdNumber.setMaximumHeight (39)
			}

			slider = QSlider(window)
			if let slider=slider {
				slider.setOrientation (Qt.Horizontal)
				slider.setStyleSheet ("background-color : green; color : white;")
				mainLayout?.addWidget (slider, row: 1, column: columnNumber)
				slider.setValue (20)
				slider.valueChangedHandler = { value in 
					print ("Slider value changed to \(value)")
					weakSelf?.lcdNumber?.display(value)
				}
			}

			editor = QTextEdit (window)
			editor?.setText ("QTextEdit\nSed ut perspiciatis, unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo.")
			mainLayout?.addWidget(editor!, row: 2, column: columnNumber, rowSpan: 6, columnSpan: 1)
			editor!.setMinimumSize (Size(200,1))
			columnNumber += 1

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
		print("SampleGridLayoutApp setup")
	}
	func tearDown () {
		print("SampleGridLayoutApp teardown")
	}
}
