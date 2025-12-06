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

// QKeySequence.swift
// SwiftQt

class QKeySequence : QObject
{
	required init (_ string: String) {
		super.init ()
		objectID = Conduit.createKeySequence (string);
		if let objectID = objectID {
			QObject.registerObject (objectID, self)
		} else {
			print ("QKeySequence is missing an object ID.")
		}
	}

	static func New ()->String	{ return "Ctrl+n"; }
	static func Open ()->String	{ return "Ctrl+o"; }
	static func Close ()->String	{ return "Ctrl+w"; }
	static func Save ()->String	{ return "Ctrl+s"; }
	static func SaveAs ()->String	{ return "Ctrl+Shift+s"; }
	static func Print ()->String	{ return "Ctrl+p"; }
	static func Quit ()->String	{ return "Ctrl+q"; }
	static func SelectAll()->String	{ return "Ctrl+a"; }
	static func Copy ()->String	{ return "Ctrl+c"; }
	static func Cut ()->String	{ return "Ctrl+x"; }
	static func Paste ()->String	{ return "Ctrl+v"; }
	static func Undo ()->String	{ return "Ctrl+z"; }
	static func AddTab ()->String	{ return "Ctrl+t"; }
	static func ZoomIn ()->String	{ return "Ctrl+Plus"; }
	static func ZoomOut ()->String	{ return "Ctrl+Minus"; }
	static func Find ()->String	{ return "Ctrl+f"; }
	static func FindNext ()->String	{ return "Ctrl+g"; }
	static func Bold ()->String	{ return "Ctrl+b"; }
	static func Italic ()->String	{ return "Ctrl+i"; }
	static func Underline()->String	{ return "Ctrl+u"; }
}
