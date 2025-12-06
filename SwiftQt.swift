//=========================================================================
// This file is part of SwiftQt.
// (C) 2023 Zack T Smith.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// The author may be reached at zck22 at mail dotcom.
//=========================================================================

class SwiftQt {

	static func release () -> String {
		let unsafeString : UnsafePointer<CChar>? = Conduit.swiftQtRelease()
		if let unsafeString = unsafeString {
			let safeString : String = String (cString:unsafeString);
			unsafeString.deallocate()
			return safeString
		}
		return ""
	}

	static func isDarkMode () -> Bool {
		return Conduit.swiftQtIsDarkMode ();
	}

	static func conveniencePopup (_ title: String, _ message: String) {
		Conduit.swiftQtConveniencePopup (title, message);
	}
	static func infoPopup (_ message: String) {
		conveniencePopup ("Information", message);
	}
	static func warningPopup (_ message: String) {
		conveniencePopup ("Warning", message);
	}
	static func errorPopup (_ message: String) {
		conveniencePopup ("Error", message);
	}

	static func convenienceQuestion (_ title: String, _ message: String) -> Bool {
		return Conduit.swiftQtConvenienceQuestion (title, message);
	}
}
