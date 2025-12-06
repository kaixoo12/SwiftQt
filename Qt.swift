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

class Qt {
	// Qt::Alignment
	static let AlignNone = 0
	static let AlignLeft = 1
	static let AlignRight = 2
	static let AlignCenter = 4
	static let AlignJustify = 8
	static let AlignTop = 0x20
	static let AlignBottom = 0x40
	static let AlignVCenter = 0x80
	static let AlignBaseline = 0x100

	static let AnchorLeft = 0
	static let AnchorHorizontalCenter = 1
	static let AnchorRight = 2
	static let AnchorTop = 3
	static let AnchorVerticalCenter	= 4
	static let AnchorBottom	= 5

	// Qt::Orientation
	static let Horizontal = 1
	static let Vertical = 2

	static let NoArrow = 0
	static let UpArrow = 1
	static let DownArrow = 2
	static let LeftArrow = 3
	static let RightArrow = 4

	// QSizePolicy::PolicyFlag
	static let GrowFlag = 1
	static let ExpandFlag = 2
	static let ShrinkFlag = 4
	static let IgnoreFlag = 8

	// QSizePolicy::Policy
	static let Fixed = 0
	static let Minimum = GrowFlag
	static let Maximum = ShrinkFlag
	static let Preferred = GrowFlag | ShrinkFlag
	static let Expanding = GrowFlag | ShrinkFlag | ExpandFlag
	static let MinimumExpanding = GrowFlag | ExpandFlag
	static let Ignored = ShrinkFlag | GrowFlag | IgnoreFlag

	// Qt::CheckState
	static let Unchecked = 0
	static let PartiallyChecked = 1
	static let Checked = 2

	// Qt::DayOfWeek
	static let Monday = 1
	static let Tuesday = 2
	static let Wednesday = 3
	static let Thursday = 4
	static let Friday = 5
	static let Saturday = 6
	static let Sunday = 7

	// Qt ItemFlags
	static let NoItemFlags = 0
	static let ItemIsSelectable = 1
	static let ItemIsEditable = 2
	static let ItemIsDragEnabled = 4
	static let ItemIsDropEnabled = 8
	static let ItemIsUserCheckable = 16
	static let ItemIsEnabled = 32
	static let ItemIsTristate = 64
}

