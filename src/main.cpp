#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

struct Settings {

	bool m_enabled;
	bool m_cube;
	bool m_ship;
	bool m_ufo;
	bool m_ball;
	bool m_wave;
	bool m_robot;
	bool m_spider;
	bool m_swing;
	bool m_shouldMirrorHorizontally;
	bool m_shouldMirrorVertically;
	float m_rotationModifier;

	void loadSettings() {
		m_enabled = Mod::get()->getSettingValue<bool>("toggle");
		m_cube = Mod::get()->getSettingValue<bool>("cube-enable");
		m_ship = Mod::get()->getSettingValue<bool>("ship-enable");
		m_ufo = Mod::get()->getSettingValue<bool>("ufo-enable");
		m_ball = Mod::get()->getSettingValue<bool>("ball-enable");
		m_wave = Mod::get()->getSettingValue<bool>("wave-enable");
		m_robot = Mod::get()->getSettingValue<bool>("robot-enable");
		m_spider = Mod::get()->getSettingValue<bool>("spider-enable");
		m_swing = Mod::get()->getSettingValue<bool>("swing-enable");
		m_shouldMirrorHorizontally = Mod::get()->getSettingValue<bool>("horizontal-mirror");
		m_shouldMirrorVertically = Mod::get()->getSettingValue<bool>("vertical-mirror");
		m_rotationModifier = Mod::get()->getSettingValue<float>("rotation-modifier");
	}

	static Settings& get() {
		static Settings settings;
		return settings;
	};

};

$execute {
	Settings::get().loadSettings();
	listenForAllSettingChanges([](std::shared_ptr<SettingV3>) {
		Settings::get().loadSettings();
	});
}

class $modify(MyPlayerObject, PlayerObject) {

	bool isCube() {
		return !m_isShip && !m_isBird && !m_isBall && !m_isDart && !m_isRobot && !m_isSpider && !m_isSwing;
	}

	void update(float dt) {
		PlayerObject::update(dt);
		const auto& settings = Settings::get();
		if (!settings.m_enabled) return;

		if (!settings.m_cube && isCube()) return;
		if (!settings.m_ship && m_isShip) return;
		if (!settings.m_ufo && m_isBird) return;
		if (!settings.m_ball && m_isBall) return;
		if (!settings.m_wave && m_isDart) return;
		if (!settings.m_robot && m_isRobot) return;
		if (!settings.m_spider && m_isSpider) return;
		if (!settings.m_swing && m_isSwing) return;

		int mod = -1;
		float rot = 0;
		if (m_isUpsideDown) mod = 1;
		if (m_isSideways) {
			mod = -mod;
			rot = -90;
		}

		if (settings.m_shouldMirrorVertically) {
			if (m_isSwing) m_mainLayer->setScaleY(-1);
			else {
				m_mainLayer->setScaleY(mod);
			}
		}

		if (settings.m_shouldMirrorHorizontally) {
			m_mainLayer->setScaleX(mod);
		}

		m_mainLayer->setRotation(-getRotation() + (settings.m_rotationModifier * getRotation()) + rot);
	}
};