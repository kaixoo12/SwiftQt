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
// QSlider.swift

class QSlider : QAbstractSlider
{
	static let NoTicks = 0
	static let TicksBothSides = 3
	static let TicksAbove = 1
	static let TicksBelow = 2	
	static let TicksLeft = TicksAbove	
	static let TicksRight = TicksBelow

#if false
	var valueChangedHandler: ()->Void = { 
		print ("SLIDER VALUE CHANGED")
	}
	var sliderMovedHandler: ()->Void = {
		print ("SLIDER MOVED")
	}
	var sliderPressedHandler: ()->Void = {
		print ("SLIDER PRESSED")
	}
	var sliderReleasedHandler: ()->Void = {
		print ("SLIDER RELEASED")
	}
#endif
	convenience init (_ parent: QMainWindow) {
		self.init ()
		if let windowID = parent.widgetID {
			widgetID = Conduit.createSlider (windowID)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeSliderValueChanged:
				valueChangedHandler (event.x)
			case EventTypeSliderMoved:
				sliderMovedHandler (event.x)
			case EventTypeSliderPressed:
				sliderPressedHandler ()
			case EventTypeSliderReleased:
				sliderReleasedHandler ()

			default: 
				print ("QSlider unknown event.");
		}
		return 0
	}

	func tickerPosition () -> Int {
		if let widgetID = widgetID {
			return Conduit.sliderTickPosition (widgetID)
		}
		return 0
	}
	func tickerInterval () -> Int {
		if let widgetID = widgetID {
			return Conduit.sliderTickInterval (widgetID)
		}
		return 0
	}
	func setTickPosition (_ value: Int) {
		if let widgetID = widgetID {
			Conduit.sliderSetTickPosition (widgetID, value)
		}
	}
	func setTickInterval (_ value: Int) {
		if let widgetID = widgetID {
			Conduit.sliderSetTickInterval (widgetID, value)
		}
	}
}
