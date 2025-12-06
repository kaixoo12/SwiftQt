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
// QAbstractSlider.swift
// 

class QAbstractSlider : QWidget
{
	var valueChangedHandler: (_ value: Int)->Void = { value in 
		//print ("Slider value changed to \(value)!");
	}
	var sliderMovedHandler: (_ value: Int)->Void = { value in 
		//print ("Slider moved! New value=\(value)");
	}
	var sliderPressedHandler: ()->Void = {
		//print ("Slider pressed!");
	}
	var sliderReleasedHandler: ()->Void = {
		//print ("Slider released!");
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			case EventTypeSliderValueChanged:
				valueChangedHandler(event.x)
			case EventTypeSliderMoved:
				sliderMovedHandler(event.x)
			case EventTypeSliderPressed:
				sliderPressedHandler()
			case EventTypeSliderReleased:
				sliderReleasedHandler()

			default: 
				print ("QAbstractSlider unknown event.");
		}
		return 0
	}

	func value () -> Int {
		if let widgetID = widgetID {
			return Conduit.abstractSliderValue (widgetID)
		}
		return 0
	}
	func setValue (_ value: Int) {
		if let widgetID = widgetID {
			Conduit.abstractSliderSetValue (widgetID, value)
		}
	}
	func orientation () -> Int {
		if let widgetID = widgetID {
			return Conduit.abstractSliderOrientation (widgetID)
		}
		return 0
	}
	func setOrientation (_ orientation: Int) {
		if let widgetID = widgetID {
			Conduit.abstractSliderSetOrientation (widgetID, orientation)
		}
	}
	func maximum () -> Int {
		if let widgetID = widgetID {
			return Conduit.abstractSliderMaximum (widgetID)
		}
		return 0
	}
	func setMaximum (_ maximum: Int) {
		if let widgetID = widgetID {
			Conduit.abstractSliderSetMaximum (widgetID, maximum)
		}
	}
	func minimum () -> Int {
		if let widgetID = widgetID {
			return Conduit.abstractSliderMinimum (widgetID)
		}
		return 0
	}
	func setMinimum (_ minimum: Int) {
		if let widgetID = widgetID {
			Conduit.abstractSliderSetMinimum (widgetID, minimum)
		}
	}
	func pageStep () -> Int {
		if let widgetID = widgetID {
			return Conduit.abstractSliderPageStep (widgetID)
		}
		return 0
	}
	func setPageStep (_ pageStep: Int) {
		if let widgetID = widgetID {
			Conduit.abstractSliderSetPageStep (widgetID, pageStep)
		}
	}

	func isSliderDown () -> Bool {
		if let widgetID = widgetID {
			return Conduit.abstractSliderIsSliderDown(widgetID)
		}
		return false
	}
	func setSliderDown (_ value: Bool) {
		if let widgetID = widgetID {
			Conduit.abstractSliderSetSliderDown (widgetID, value)
		}
	}

}
