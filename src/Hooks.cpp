#include "AutoDeafen.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

struct PlayLayerHooks : Modify<PlayLayerHooks, PlayLayer> {
	int64_t s_percent;
	bool s_enabled;

	bool init(GJGameLevel *level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects))
			return false;

		m_fields->s_percent = Mod::get()->getSettingValue<int64_t>("percentage");
		m_fields->s_enabled = Mod::get()->getSettingValue<bool>("enabled");

		return true;
	}

};

struct PauseLayerHooks : Modify<PauseLayerHooks, PauseLayer> {
};
