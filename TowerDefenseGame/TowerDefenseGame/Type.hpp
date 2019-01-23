#pragma once

namespace Type {

	enum Content {
		Grass,
		Rock,
		RoadNS,
		RoadEW,
		RoadNE,
		RoadES,
		RoadSW,
		RoadWN,
		Base,
		Tower
	};

	enum Direct {
		Right,
		Bottom,
		Top,
		Left,
		EN,
		NE,
		ES,
		SE,
		SW,
		WS,
		NW,
		WN
	};

	enum Options {
		Start,
		Settings,
		Credits,
		Exit,
		FPS,
		Volume,
		Undo,
		Miss
	};
}