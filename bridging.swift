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
//
// SwiftQt
// bridging.swift
// Links Swift to C code.
// 

import Foundation

var appDelegate : ApplicationDelegate? = nil

// TODO: Add an event handler that can take a dictionary e.g. of command-line args.

@_cdecl("swiftEventHandler") 
public func swiftEventHandler(event: Event) -> Int 
{
	let widget : QWidget? = QWidget.widgets[event.recipient]
	if let widget = widget {
		return widget.processEvent (event)
	}

	let object : QObject? = QObject.objects[event.recipient]
	if let object = object {
		return object.processEvent (event)
	}

	switch (event.type) {
	case EventTypeAppLaunched:	
		print ("Bridge: LAUNCH EVENT RECEIVED")

		// Prepare to pass argc, argv to the Swift code.
		let argc : Int = Int(event.argc)
		var argv : [String] = []
		for index in 0..<argc {
			let unsafeString : UnsafePointer<CChar>? = event.argv[index]
			if let unsafeString = unsafeString {
				let safeString : String = String (cString:unsafeString)
				argv.append(safeString)
			}
		}

		// App has told us its name and given us its object.
		appDelegate = appMain(argc: argc, argv: argv)
		if let appDelegate = appDelegate {
			print ("Bridge: CREATED APP CALLING ITSELF \(appDelegate.name()), asking it to construct UI.")
			appDelegate.constructUI ()
		} else {
			print ("Bridge: appMain didn't return an appDelegate!")
		}

	case EventTypeWindowResized:
		if let appDelegate = appDelegate {
			appDelegate.windowResized (event.x, event.y)
		}

	case EventTypeAppExiting: 	
		if let appDelegate = appDelegate {
			appDelegate.willExit()
		}

	default:	
		if let appDelegate = appDelegate {
			return appDelegate.processEvent(event) 
		} else {
			print ("Bridge: EVENT RECEIVED BEFORE APP OBJECT CREATED.");
			return -1;
		}
	}

	return 0
}

#if false // Not used.
@_cdecl("swiftEventHandlerForString") 
public func swiftEventHandlerForString(event: EventType, parameter1: Int, parameter2: Int) -> UnsafeMutablePointer<CChar>
{
	var response : String

	switch (event) {
	case EventTypeRequireAppNameString:	
		response = app?.name ?? "No Name"

	default:	
		response = ""
	}

	let convertibleResponse : NSString = NSString(string: response)
	let unsafe = UnsafeMutablePointer<CChar>(mutating: convertibleResponse.utf8String)
	return unsafe!
}
#endif

// TODO: Add an event handler that can take a dictionary e.g. of command-line args.

extension Point {
	mutating func zero() -> Point {
		return Point.zero
	}
}

extension Size {
	mutating func zero() -> Size {
		return Size.zero
	}
	func equals(_ size: Size) -> Bool {
		return Size.equals(self, size)
	}
}

extension Rect {
	mutating func zero() -> Rect {
		return Rect.zero
	}
	func print() -> Void {
		Rect.print(self)
	}
	func equals(_ rect: Rect) -> Bool {
		return Rect.equals(self, rect)
	}
	func containsPoint(_ x: Int, _ y: Int) -> Bool {
		return Rect.containsPoint(self, x, y)
	}
}

