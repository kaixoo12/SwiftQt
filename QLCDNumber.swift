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
// QLCDNumber.swift

class QLCDNumber : QWidget
{
	convenience init (_ numDigits: Int, _ parent: QMainWindow) {
		self.init ()
		if let windowID = parent.widgetID {
			widgetID = Conduit.createLCDNumber (windowID, numDigits)
			QWidget.registerWidget (widgetID!, self)
		}
	}

	override func processEvent (_ event: Event) -> Int {
		switch (event.type) {
			default: 
				print ("QLCDNumber unknown event.");
		}
		return 0
	}

	func setHexMode () {
		if let widgetID = widgetID {
			Conduit.lcdNumberSetHexMode (widgetID)
		}
	}
	func setBinMode () {
		if let widgetID = widgetID {
			Conduit.lcdNumberSetBinMode (widgetID)
		}
	}
	func setDecMode () {
		if let widgetID = widgetID {
			Conduit.lcdNumberSetDecMode (widgetID)
		}
	}
	func setOctMode () {
		if let widgetID = widgetID {
			Conduit.lcdNumberSetOctMode (widgetID)
		}
	}
	func value () -> Double {
		if let widgetID = widgetID {
			return Conduit.lcdNumberValue (widgetID)
		}
		return 0.0
	}
	func intValue () -> Int {
		if let widgetID = widgetID {
			return Conduit.lcdNumberIntValue (widgetID)
		}
		return 0
	}
	func digitCount () -> Int {
		if let widgetID = widgetID {
			return Conduit.lcdNumberDigitCount (widgetID)
		}
		return 0
	}
	func smallDecimalPoint () -> Bool {
		if let widgetID = widgetID {
			return Conduit.lcdNumberSmallDecimalPoint (widgetID)
		}
		return false
	}
	func setSmallDecimalPoint (_ value: Bool) {
		if let widgetID = widgetID {
			return Conduit.lcdNumberSetSmallDecimalPoint (widgetID, value)
		}
	}
	func display (_ value: Int) {
		if let widgetID = widgetID {
			Conduit.lcdNumberDisplayInt (widgetID, value)
		}
	}
	func display (_ value: Double) {
		if let widgetID = widgetID {
			Conduit.lcdNumberDisplayDouble (widgetID, value)
		}
	}
}
