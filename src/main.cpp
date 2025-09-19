#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

bool toggled = true; //for the sake of no fields access

class $modify(MyPlayerObject, PlayerObject) {

    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4) {
        if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;
        toggled = Mod::get()->getSettingValue<bool>("toggle");
        return true;
    }

    void update(float dt) {
        PlayerObject::update(dt);
        if (!toggled) return;

        int mod = -1;
        float rot = 0;

        if (m_isUpsideDown) mod = 1;
        if (m_isSideways) {
            mod = -mod;
            rot = -90;
        }

        // Exclude Ship (1) and UFO (3) from flipping
        if (m_playerType == 1 || m_playerType == 3) {
            m_mainLayer->setScaleY(1);
        } else if (m_isSwing) {
            m_mainLayer->setScaleY(-1);
        } else {
            m_mainLayer->setScaleY(mod);
        }

        m_mainLayer->setRotation(-getRotation() * 2 + rot);
    }
};
