#include "AutoDeafen.hpp"
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingEvent.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

int64_t s_percent;
bool s_enabled;

struct PlayLayerHooks : Modify<PlayLayerHooks, PlayLayer> {
	bool init(GJGameLevel *level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects))
			return false;

		s_percent = Mod::get()->getSettingValue<int64_t>("percentage");
		s_enabled = Mod::get()->getSettingValue<bool>("enabled");

		return true;
	}

	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);

		auto c_percent = this->getCurrentPercentInt();

		// log::info("s_percent: {}, c_percent: {}", m_fields->s_percent, this->getCurrentPercentInt());

		if (s_enabled) {
			if (c_percent >= s_percent && !AutoDeafen::enabled && !this->m_player1->m_isDead && !this->m_player2->m_isDead && c_percent != 100) {
				AutoDeafen::toggleDeafen();
			} else if (AutoDeafen::enabled && c_percent < s_percent) {
				AutoDeafen::toggleDeafen();
			}
		}
	}

	void onQuit() {
		PlayLayer::onQuit();

		if (AutoDeafen::enabled)
			AutoDeafen::toggleDeafen();
	}

	void onExit() {
		PlayLayer::onExit();

		if (AutoDeafen::enabled)
			AutoDeafen::toggleDeafen();
	}

	void resetLevel() {
		PlayLayer::resetLevel();

		if (AutoDeafen::enabled)
			AutoDeafen::toggleDeafen();
	}

	void destroyPlayer(PlayerObject *player, GameObject *p1) {
		PlayLayer::destroyPlayer(player, p1);

		if (player && player->m_isDead && AutoDeafen::enabled)
			AutoDeafen::toggleDeafen();
	}

	void levelComplete() {
		PlayLayer::levelComplete();

		if (AutoDeafen::enabled)
			AutoDeafen::toggleDeafen();
	}
};

struct PauseLayerHooks : Modify<PauseLayerHooks, PauseLayer> {
	// this should disable deafening on pause btw :)
	void customSetup() {
		PauseLayer::customSetup();

		if (AutoDeafen::enabled) {
			AutoDeafen::toggleDeafen();
		}

		auto menu = this->getChildByID("right-button-menu");

		auto spr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
		spr->setScale(0.7f);

		auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(PauseLayerHooks::settingsBtn));

		menu->addChild(btn);
		menu->updateLayout();
	}

	void settingsBtn(CCObject *sender) {
		auto mod = Mod::get();
		openSettingsPopup(mod);
	}

	void onResume(CCObject *sender) {
		PauseLayer::onResume(sender);

		s_percent = Mod::get()->getSettingValue<int64_t>("percentage");
		s_enabled = Mod::get()->getSettingValue<bool>("enabled");
	}

	void onRestart(CCObject *sender) {
		PauseLayer::onRestart(sender);

		s_percent = Mod::get()->getSettingValue<int64_t>("percentage");
		s_enabled = Mod::get()->getSettingValue<bool>("enabled");
	}

	void onPracticeMode(CCObject *sender) {
		PauseLayer::onPracticeMode(sender);

		s_percent = Mod::get()->getSettingValue<int64_t>("percentage");
		s_enabled = Mod::get()->getSettingValue<bool>("enabled");
	}

	void onNormalMode(CCObject *sender) {
		PauseLayer::onNormalMode(sender);

		s_percent = Mod::get()->getSettingValue<int64_t>("percentage");
		s_enabled = Mod::get()->getSettingValue<bool>("enabled");
	}
};
