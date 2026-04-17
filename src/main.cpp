#include <Geode/Geode.hpp>
#include <windows.h>
using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto RestartButton = CCMenuItemSpriteExtra::create(
			CCSprite::create("Restart.png"_spr),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("close-menu");
		if (!menu) return true;
		menu->addChild(RestartButton);

		RestartButton->setID("Res-Button");

		RestartButton->setPosition({16, -8});
		RestartButton->setScale(0.2f);
		

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject* sender) {
		auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);
		btn->setScale(0.2f);

		createQuickPopup(
		"Restart?",
		"Do you want to restart?",
		"No",
		"Yes",
		[](FLAlertLayer*, bool btn2) {
			if (btn2) {
				char path[MAX_PATH];
				GetModuleFileNameA(NULL, path, MAX_PATH);

				ShellExecuteA(NULL, "open", path, NULL ,NULL, SW_SHOW);

				exit(0);
			}
		}
	  );
	}

};