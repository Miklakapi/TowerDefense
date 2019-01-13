#pragma once

namespace Type {
	
	enum Mob {
		Empty,
		FireDude
	};

	enum Content {
		Grass,
		Rock,
		RoadNS,
		RoadEW,
		RoadNE,
		RoadES,
		RoadSW,
		RoadWN
	};

	enum Weapon {
		tower1,
		tower2
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