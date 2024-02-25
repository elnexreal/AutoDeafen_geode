#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

struct AutoDeafen : Modify<AutoDeafen, PlayLayer> {
	bool init(GJGameLevel *level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects))
			return false;

		return true;
	}
};
