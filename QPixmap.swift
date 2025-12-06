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
// QPixmap.swift

class QPixmap : QObject
{
	convenience init (_ path: String?) {
		self.init ()
		objectID = Conduit.createPixmapWithPath (path ?? "")
		if let objectID = objectID {
			QObject.registerObject (objectID, self)
		} else {
			print ("QPixmap is missing an object ID.")
		}
	}

	convenience init (_ width: Int, _ height: Int) {
		self.init ()
		objectID = Conduit.createPixmapWithSize (width, height)
		if let objectID = objectID {
			QObject.registerObject (objectID, self)
		} else {
			print ("QPixmap is missing an object ID.")
		}
	}

	func load (_ path: String) -> Bool {
		if let objectID = objectID {
			return Conduit.pixmapLoad (objectID, path)
		}
		return false
	}

	func width () -> Int {
		if let objectID = objectID {
			return Conduit.pixmapWidth (objectID)
		}
		return 0 
	}
	func height () -> Int {
		if let objectID = objectID {
			return Conduit.pixmapHeight (objectID)
		}
		return 0 
	}
	func depth () -> Int {
		if let objectID = objectID {
			return Conduit.pixmapDepth (objectID)
		}
		return 0 
	}
}
