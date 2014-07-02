#include "InstanceDialogLayer.h"
#include "resources.h"
#include "UIManager.h"
#include "Localization.h"
#include "GameConfigFromLuaManager.h"
#include "GameManager.h"
#include "MainMenuLayer.h"
#include "BattleUILayer.h"
#include "HSJoystick.h"
#include "StoryInstanceDirector.h"
#include "StoryDataCenter.h"

using namespace TXGUI;

InstanceDialogLayer::InstanceDialogLayer()
{
	m_pLayer = 0;
	m_pContentLabel = 0;
	m_leftHeroLogoPic = 0;
}

InstanceDialogLayer::~InstanceDialogLayer()
{
	UIManager::sharedManager()->RemoveUILayout("InstanceDialogLayout");
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void InstanceDialogLayer::setTouchEnabled(bool value)
{
	CCLayer::setTouchEnabled(value);
}

bool InstanceDialogLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	UIManager *manager = UIManager::sharedManager();
	m_pLayer = manager->CreateUILayoutFromFile("UIplist/InstanceDialogLayer.plist", this, "InstanceDialogLayout", true);

	manager->RegisterMenuHandler("InstanceDialogLayout","InstanceDialogLayer::skipDialogEvent",
		menu_selector(InstanceDialogLayer::skipDialogEvent), this);

	UIButton* closeBtn = m_pLayer->FindChildObjectByName<UIButton>("closeBtn");
	m_pContentLabel = m_pLayer->FindChildObjectByName<UILabel>("contentLable");
	m_leftHeroLogoPic = m_pLayer->FindChildObjectByName<UIPicture>("rolePic");

	return true;
}

void InstanceDialogLayer::skipDialogEvent(CCObject* pObj)
{
	StoryInstanceDirector::Get()->Resume();
}

void InstanceDialogLayer::setStoryDialogData(StoryDialogData data)
{
	mStoryDialogData = data;
}

void InstanceDialogLayer::ShowPanel()
{
	std::string contentFlag = mStoryDialogData.getTextID();
	std::string content = Localizatioin::getLocalization(contentFlag.c_str());

	// Note: ��ʾ�Ի�����
	if (m_pContentLabel)
	{
		m_pContentLabel->setString(content.c_str());
	}

	CCNode* leftHeroIcon = this->getChildByTag(8);
	if (leftHeroIcon)
	{
		leftHeroIcon->removeFromParentAndCleanup(true);
	}
	
	// Note: ��ʾ����ͼ��
	std::string picName = "";
	if (StoryDataCenter::Get()->GetOneRoleLeftIcon(mStoryDialogData.getRoleIndex(),picName))
	{
		if (picName == "")
		{
			return ;
		}
		else if (std::string::npos == picName.find(".png"))
		{
			picName = std::string("UI/") + picName + std::string(".png");
		}		

		CCSprite* sprite = CCSprite::create(picName.c_str());	
		CCSize LogoPicSize = m_leftHeroLogoPic->getSpriteSize();
		CCSize SpriteSize = sprite->getContentSize();

		float scaleValue = LogoPicSize.width / SpriteSize.width;
		if (scaleValue > 1.0)
		{
			scaleValue = 1.0;
		}

		sprite->setScale(scaleValue);

		if(sprite)
		{
			this->addChild(sprite,1,8);
			sprite->setAnchorPoint(ccp(0,0));
			sprite->setPosition(ccp(0,0));
		}
	}

	// Note: ��ʾSkip����
}

void InstanceDialogLayer::ClearPanel()
{
	mStoryDialogData.ResetValue();

	// Note: ��ʾ�Ի�����
	if (m_pContentLabel)
	{
		m_pContentLabel->setString("");
	}

	CCNode* leftHeroIcon = this->getChildByTag(8);
	if (leftHeroIcon)
	{
		leftHeroIcon->removeFromParentAndCleanup(true);
	}
}