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

class QTableWidget : QWidget
{
        var cellChangedHandler: (_ row:Int, _ column:Int)->Void = { row, column in
                print ("QTableWidget cellChanged at \(row),\(column)")
        }

        var cellClickedHandler : (_ row:Int, _ column:Int)->Void = { row, column in
                print ("QTableWidget cellClicked at \(row),\(column)")
        }

        var cellDoubleClickedHandler : (_ row:Int, _ column:Int)->Void = { row, column in
                print ("QTableWidget cellDoubleClicked at \(row),\(column)")
        }
	//----------

        var currentCellChangedHandler: (_ row:Int, _ column:Int, _ previousRow:Int, _ previousColumn:Int)->Void = { row, column, previousRow, previousColumn in
                print ("QTableWidget currentCellChanged to \(row),\(column)")
        }

	var itemSelectionChangedHandler: ()->Void = {
                print ("QTableWidget itemSelectionChanged");
	}

	convenience init (_ parent: QMainWindow) {
		self.init ()
		if let windowID = parent.widgetID {
			widgetID = Conduit.createTableWidget (windowID)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
		case EventTypeTableCellChanged:
			cellChangedHandler(event.y, event.x)

		case EventTypeTableCellClicked:
			cellClickedHandler(event.y, event.x)

		case EventTypeTableCellDoubleClicked:
			cellDoubleClickedHandler(event.y, event.x)

		case EventTypeTableCurrentCellChanged:
			currentCellChangedHandler(event.y, event.x, event.previousRow, event.previousColumn)

		case EventTypeTableItemSelectionChanged:
			itemSelectionChangedHandler()

		default: 
			print ("QTableWidget unknown event.");
		}

		return 0
	}

	func columnCount () -> Int {
		if let widgetID = widgetID {
			return Conduit.tableWidgetColumnCount(widgetID)
                }
		return 0
	}
	func setColumnCount (_ count:Int) {
		if let widgetID = widgetID {
			return Conduit.tableWidgetSetColumnCount(widgetID, count)
                }
	}
	func rowCount () -> Int {
		if let widgetID = widgetID {
			return Conduit.tableWidgetRowCount(widgetID)
                }
		return 0
	}
	func setRowCount (_ count:Int) {
		if let widgetID = widgetID {
			return Conduit.tableWidgetSetRowCount(widgetID, count)
                }
	}
	func currentColumn () -> Int {
		if let widgetID = widgetID {
			return Conduit.tableWidgetCurrentColumn(widgetID)
                }
		return -1
	}
	func currentRow () -> Int {
		if let widgetID = widgetID {
			return Conduit.tableWidgetCurrentRow(widgetID)
                }
		return -1
	}
	func setCurrentCell (_ row:Int, _ column:Int) {
		if let widgetID = widgetID {
			return Conduit.tableWidgetSetCurrentCell(widgetID, row, column)
                }
	}
	func setHorizontalHeaderLabels (_ labels:[String]) {
		// The C++ Qt code takes a QStringList. Maybe support that later. TODO
		if let widgetID = widgetID {
			let count = labels.count
			var index = 0
			for label in labels {
				Conduit.tableWidgetSetHorizontalHeaderLabels (widgetID, label, index == count-1)
				index = index+1
			}
                }
	}
	func setVerticalHeaderLabels (_ labels:[String]) {
		// The C++ Qt code takes a QStringList. Maybe support that later. TODO
		if let widgetID = widgetID {
			let count = labels.count
			var index = 0
			for label in labels {
				Conduit.tableWidgetSetVerticalHeaderLabels (widgetID, label, index == count-1)
				index = index+1
			}
                }
	}
	func setItem (_ row:Int, _ column:Int, _ item:QTableWidgetItem) {
		if let widgetID = widgetID, let itemID = item.objectID {
			Conduit.tableWidgetSetItem(widgetID, row, column, itemID)
		}
	}
	func item (_ row:Int, _ column:Int) -> QTableWidgetItem? {
		if let widgetID = widgetID {
			let itemID = Conduit.tableWidgetItem(widgetID, row, column)
			if itemID < 0 {
				return nil
			} else {
				let item = QObject.lookupObject(itemID)
				if let item = item {
					// Object should always be a QTableWidgetItem.
					return (item as! QTableWidgetItem)
				} else {
					let newItem = QTableWidgetItem()
					newItem.objectID = itemID
					QObject.registerObject (itemID, newItem)
					return newItem
				} 
			} 
                }
		return nil
	}
	func currentItem () -> QTableWidgetItem? {
		if let widgetID = widgetID {
			let itemID = Conduit.tableWidgetCurrentItem(widgetID)
			if itemID < 0 {
				return nil
			} else {
				let item = QObject.lookupObject(itemID)
				if let item = item {
					// Object should always be a QTableWidgetItem.
					return (item as! QTableWidgetItem)
				} else {
					let newItem = QTableWidgetItem()
					newItem.objectID = itemID
					QObject.registerObject (itemID, newItem)
					return newItem
				} 
			} 
                }
		return nil
	}
	func cellWidget (_ row:Int, _ column:Int) -> QWidget? {
		if let widgetID = widgetID {
			let cellWidgetID = Conduit.tableWidgetCellWidget(widgetID, row, column)
			if cellWidgetID < 0 {
				return nil
			} else {
				let cellWidget = QWidget.lookupWidget(cellWidgetID)
				if let cellWidget = cellWidget {
					return cellWidget
				} else {
					// We should not reach here, because
					// all widgets placed into the table 
					// cells are ones that were created
					// in Swift code.
					return nil
				} 
			} 
                }
		return nil
	}
	func setCellWidget (_ row: Int, _ column: Int, _ widget: QWidget) {
		if let tableID = widgetID, let widgetID = widget.widgetID {
			Conduit.tableWidgetSetCellWidget (tableID, row, column, widgetID)
		}
	}
	func insertColumn (_ column:Int) {
		if let widgetID = widgetID {
			return Conduit.tableWidgetInsertColumn(widgetID, column)
                }
	}
	func insertRow (_ row:Int) {
		if let widgetID = widgetID {
			return Conduit.tableWidgetInsertRow(widgetID, row)
                }
	}
}

