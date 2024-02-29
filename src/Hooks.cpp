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

	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);

		auto c_percent = this->getCurrentPercentInt();

		// log::info("s_percent: {}, c_percent: {}", m_fields->s_percent, this->getCurrentPercentInt());

		if (m_fields->s_enabled) {
			if (c_percent >= m_fields->s_percent && !AutoDeafen::enabled && !this->m_player1->m_isDead && !this->m_player2->m_isDead && c_percent != 100) {
				AutoDeafen::toggleDeafen();
			}
		}
	}
};

struct PauseLayerHooks : Modify<PauseLayerHooks, PauseLayer> {
	// this should disable deafening on pause btw :)
	void customSetup() {
		PauseLayer::customSetup();

		if (AutoDeafen::enabled) {
			AutoDeafen::toggleDeafen();
		}
	}
};
