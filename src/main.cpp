#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(MyPlayerObject, PlayerObject) {

	void update(float dt) {
		PlayerObject::update(dt);
		int mod = -1;
		float rot = 0;
		if (m_isUpsideDown) mod = 1;
		if (m_isSideways) {
			mod = -mod;
			rot = -90;
		}
		if (m_isSwing) m_mainLayer->setScaleY(-1);
		else {
			m_mainLayer->setScaleY(mod);
		}
		m_mainLayer->setRotation(-getRotation()*2 + rot);
	}
};