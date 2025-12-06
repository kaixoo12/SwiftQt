
class View {

	init (_ color:Int) {
	}

	deinit {
	}
}

class HStack : View {

	init ([View]) {
	}

	deinit {
	}
}

let dict = [
	View(0xf0),
	HStack([
		View(0xf000),
		View(0xf00000)
	])
]


