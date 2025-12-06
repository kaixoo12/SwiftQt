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

// QDate.swift
// SwiftQt

// In Qt's C++ code, QDate is not a subclass of any other class,
// and is just a container for a 64-bit value.

class QDate 
{
	var dateID : DateID?

	static var dates: [DateID: QDate] = [:]

	static func lookupDate (_ dateID: DateID) -> QDate? {
		return dates[dateID] 
	}

	static func registerDate (_ dateID: DateID, _ date: QDate) {
		dates[dateID] = date
	}

	static func unregisterDate (_ dateID: DateID) {
		dates[dateID] = nil
	}

	required convenience init (_ y:Int, _ m:Int, _ d:Int) {
		self.init ()
		dateID = Conduit.createDate (y, m, d)
		if let dateID = dateID {
			QDate.registerDate (dateID, self)
		} else {
			print ("QDate is missing an object ID.")
		}
	}

	static func currentDate () -> QDate {
		let dateID : DateID = Conduit.createCurrentDate ()
		let date = QDate ()
		date.dateID = dateID
		QDate.registerDate (dateID, date)
		return date;
	}

	func day () -> Int {
		if let dateID = dateID {
			return Conduit.dateDay (dateID)
		}
		return 0
	}
	func month () -> Int {
		if let dateID = dateID {
			return Conduit.dateMonth (dateID)
		}
		return 0
	}
	func year () -> Int {
		if let dateID = dateID {
			return Conduit.dateYear (dateID)
		}
		return 0
	}
}
