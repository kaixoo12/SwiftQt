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
// QCalendarWidget.swift

// TODO Add QDate class.

class QCalendarWidget : QWidget
{
	// QCalendarWidget::HorizontalHeaderFormat
	static let SingleLetterDayNames	= 1
	static let ShortDayNames = 2
	static let LongDayNames	= 3
	static let NoHorizontalHeader = 0

	// QCalendarWidget::VerticalHeaderFormat
	static let NoVerticalHeader = 0
	static let ISOWeekNumbers = 1

	// QCalendarWidget::SelectionMode
	static let NoSelection = 0
	static let SingleSelection = 1

        var selectionChangedHandler: ()->Void = {
                print ("QCalendarWidget selection changed!");
        }

	convenience init (_ parent: QWidget) {
		self.init ()
		if let parentID = parent.widgetID {
			widgetID = Conduit.createCalendarWidget (parentID)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeSelectionChanged:
				selectionChangedHandler()

			default: 
				print ("QCalendarWidget unknown event.");
		}
		return 0
	}

	func horizontalHeaderFormat() -> Int {
		if let widgetID = widgetID {
			return Conduit.calendarWidgetHorizontalHeaderFormat(widgetID)
		}
		return -1
	}
	func verticalHeaderFormat() -> Int {
		if let widgetID = widgetID {
			return Conduit.calendarWidgetVerticalHeaderFormat(widgetID)
		}
		return -1
	}
	func setHorizontalHeaderFormat(_ value : Int) {
		if let widgetID = widgetID {
			Conduit.calendarWidgetSetHorizontalHeaderFormat(widgetID, value)
		}
	}
	func setVerticalHeaderFormat(_ value: Int) {
		if let widgetID = widgetID {
			Conduit.calendarWidgetSetVerticalHeaderFormat(widgetID, value)
		}
	}
	func clearMaximumDate() {
		if let widgetID = widgetID {
			Conduit.calendarWidgetClearMaximumDate(widgetID)
		}
	}
	func clearMinimumDate() {
		if let widgetID = widgetID {
			Conduit.calendarWidgetClearMinimumDate(widgetID)
		}
	}
	func monthShown() -> Int {
		if let widgetID = widgetID {
			return Conduit.calendarWidgetMonthShown(widgetID)
		}
		return 0
	}
	func yearShown() -> Int {
		if let widgetID = widgetID {
			return Conduit.calendarWidgetYearShown(widgetID)
		}
		return 0
	}

	func firstDayOfWeek () -> Int {
		if let widgetID = widgetID {
			return Conduit.calendarWidgetFirstDayOfWeek(widgetID)
		}
		return -1
	}
	func setFirstDayOfWeek (_ value : Int) {
		if let widgetID = widgetID {
			Conduit.calendarWidgetSetFirstDayOfWeek(widgetID, value)
		}
	}
	func selectedDate () -> QDate? {
		if let widgetID = widgetID {
			let dateID = Conduit.calendarWidgetSelectedDate(widgetID)
			if dateID < 0 {
				return nil
			}
			let date : QDate? = QDate.lookupDate(dateID)
			if let date = date {
				return date
			} else {
				let date = QDate()
				date.dateID = dateID
				QDate.registerDate (dateID, date)
				return date
			} 
		}
		return nil
	}
}
