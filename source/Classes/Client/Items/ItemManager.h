#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "Singleton_t.h"
#include "cocos2d.h"

#include <map>
#include <list>
#include "ItemBase.h"
#include "EquipmentItem.h"
#include "cs_core.pb.h"
using namespace cocos2d;

#define AlCHEMYBAGCAPACITY	24
#define AlCHEMYSTORAGECAPACITY	18

/*
// id 0~999 ������ 1000~1999 �ֿ�� 2000~2999 װ���� 3000~3999 ��ʯ�� 4000~4999 ��ʯ�ֿ� 5000~5999 ��ʯװ���� 7000 ~ 7999 ��ʯ��
*/
enum
{
	kItemBag = 0,
	kItemStorage = 1000,
	kItemHeroEquip = 2000,
	kItemFairyEquip = 2100,
	kAlchemyBag = 3000,
	kAlchemyStorage = 4000,
	kAlchemyHeroEquip = 5000,
	kAlchemyFairyEquip = 5100,
	kFairyStartId = 6000,
	kItemGemStone = 7000
};

typedef struct EquipmetHole
{
	EquipmetHole(){memset(this, 0x00, sizeof(EquipmetHole));}
	unsigned int hole_index;		// �ױ��
	unsigned int item_gem_id;		// ��ʯid
	unsigned int attr_key;			// Ӱ�����Ե�key
	unsigned int attr_value;		// Ӱ�����Ե�value
	unsigned int max_value;			// ���Կ�����Сֵ
	unsigned int min_value;			// ���Կ������ֵ
}EQUIPHOLE;

typedef struct ItemAttribution
{
	ItemAttribution(){memset(this, 0x00, sizeof(ItemAttribution));}
	unsigned int attr_key;					// ��Ʒ����key
	unsigned int attr_basic_value;			// ��Ʒ�������Զ�Ӧ��value
	unsigned int attr_intensify_value;		// ǿ��Ӱ����Ʒ����value����
	unsigned int attr_gem_value;			// ��ʯӰ����Ʒ����value����
}ITEMATTR;

typedef struct EquipNextAttribution
{
	EquipNextAttribution(){memset(this, 0x00, sizeof(EquipNextAttribution));}
	unsigned int key;					// װ��ǿ����һ������key
	unsigned int value;					// װ��ǿ����һ������value
}EQUIPNEXTATTR;

typedef struct EquipmetInfo
{
	EquipmetInfo(){levelUpCost = 0;}
	unsigned int levelUpCost; // װ����������
	std::list<EQUIPNEXTATTR>	m_nextAttribution; // װ��ǿ����һ������
	std::map<unsigned int,EQUIPHOLE> m_equipHoles;	// װ����
}EQUIPINFO;

typedef struct SpriteStoneInfo
{
	SpriteStoneInfo(){memset(this, 0x00, sizeof(SpriteStoneInfo));}
	unsigned int levelUpCost; // ������Ҫ������
	unsigned int convertSp;	  // ת��������
}SPRITEINFO;

class BackPackItem
{
	// ������
public: 
	BackPackItem(unsigned int packType);
	~BackPackItem();
	ItemBase* getItemInfo();
	void setItemId(unsigned int id);
	void resetEquipInfo();
	void setEquipInfo(EquipmentBase base);
	unsigned int getItemId(){return itemId;}
	void setSpriteInfo(SpiritStoneBase base);
	void resetItem();
public:

	bool isLocked;			// �Ƿ����
	bool isEmpty;			// �Ƿ�Ϊ��	
	unsigned int position;	// ��Ʒλ��
	unsigned int amount;	// ��Ʒ����
	unsigned int itemLevel;	// ��Ʒ�ȼ�
	EQUIPINFO* m_equipInfo;	// װ��ǿ������
	unsigned int packType; // �������ͣ� 0 ����; 1�ֿ� ; 2װ���� ;3 ��ʯ����;4 ��ʯ�ֿ� ; 5��ʯװ���� ;6 ����װ��
	std::list<ITEMATTR*>*	m_attribution;
	SPRITEINFO* m_spriteInfo; // ��ʯ��������

private:
	ItemBase* m_itemInfo;	    // ��Ʒ������������
	unsigned int itemId;		// ��ƷId	

};

class ExchangeItem
{
// ��Ʒ�������

public:
	ExchangeItem();
	~ExchangeItem();
	void setFromItems(std::string fromStr);
	void setToItems(std::string toStr);
private:
	std::list<std::pair<unsigned int ,unsigned int> >* initItemsByString(std::string str);
public:
	unsigned int m_exchangeType;
	unsigned int m_exchangeId;
	std::list<std::pair<unsigned int ,unsigned int> >* m_fromItems;
	std::list<std::pair<unsigned int ,unsigned int> >* m_toItems;
	/*std::map<unsigned int ,unsigned int>* m_fromItems;
	std::map<unsigned int ,unsigned int>* m_toItems;*/
};

typedef std::map<unsigned int ,BackPackItem*> BACKPACK_VECTOR;

class ItemManager : public TSingleton<ItemManager>
{
public:
	ItemManager();
	virtual ~ItemManager();

	void init();

	BackPackItem* findItemByPos(unsigned int pos);
	//bool addItem()	
	void resetItems();
	unsigned int getBackPackEmptyGridIndex();
	void setBackPackDefaultPos(unsigned int ownerPos);
	void setBackPackUnlockPos(unsigned int pos);
	void setStorageUnlockPos(unsigned int pos);
	void setEquipMaxTimes(unsigned int maxTimes);

	unsigned int getBackPackMaxPos(){return m_maxPackPos;}

	void openBackPack();
	void exchangeItemPos(unsigned int from, unsigned int to);
	BackPackItem* setItem(unsigned int pos,unsigned int id, unsigned int level,unsigned int number);

	void setStorageDefaultPos(unsigned int ownerPos);
	unsigned int getStorageEmptyGridIndex();

	unsigned int getStorageMaxPos(){return m_maxStoragePos;}

	void removeItem(unsigned int pos, unsigned int id);
	bool setEquipItemInfor(unsigned int pos,EquipmentBase equipmetInfo);
	void addExchangeItem(unsigned int exchangeId,std::string fromItems, std::string toItems, unsigned int type);

	ItemBase* getItemInfoById(unsigned int id);
	ExchangeItem* getEquipDrawingById(unsigned int equipId); // ���ڲ��ҵ�from item���ҽ������
	ExchangeItem* getExchageItemById(unsigned int exchangeId);						 // ���ڱ��id���ұ��
	std::list<unsigned int>* getExchangeSpriteStones();

	unsigned int getItemNumberById(unsigned int id);
	CCSprite* getIconSpriteById(unsigned int ItemId);
	void loadExchangeItems();

	// alchemy
	void setAlchemyBagUnlockCapacity(unsigned int value);
	void setAlchemyStorageUnlockCapacity(unsigned int value);
	void setAlchemyBackDefaultCapacity(unsigned int pos);
	void setAlchemyStorageDefaultCapacity(unsigned int pos);
	void reqAlchemyUpgradeSelected(unsigned int pos);
	void reqAlchemyUpgradeUnselected();	
	bool getCurrentAlchemyIndex();

	unsigned int getAlchemySearchNpcCost(unsigned int npcID);
	void showItemTipsByPos(unsigned int pos,CCPoint pt);
	void showItemTipsById(unsigned int itemId,CCPoint pt);

	const char* getAttributionText(unsigned int key,unsigned int value);
	CCSprite* getIconFrame(unsigned int level);
	ccColor3B getLabelColorByQuality(unsigned int quality);

	// weapon id 
	unsigned int getHeroWeaponId();
private: 
	// ��ʾ��Ʒ��Ϣ
	void showEquipmentTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showEquipDrawingTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showUnusedItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showusedItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);
	void showAlchemyItemTipByPos(BackPackItem* item,CCSprite* icon,CCPoint pt);

	void showEquipDrawingTipByItemid(ItemBase* item,CCSprite* icon,CCPoint pt);
	void showNormalItemTipByItemid(ItemBase* item,CCSprite* icon,CCPoint pt);
	void resetAlchemyBagPacks(unsigned int ownerPos);
	void resetAlchemyStoragePacks(unsigned int ownerPos);
	void resetBagPacks();
	void resetStoragePacks();
private:
	BACKPACK_VECTOR *m_backPackList;
	BACKPACK_VECTOR *m_storageList;
	BACKPACK_VECTOR *m_equipmentList;
	BACKPACK_VECTOR *m_fairyEquipmentList;
	BACKPACK_VECTOR *m_alchemyBagList;
	BACKPACK_VECTOR *m_alchemyStorageList;
	BACKPACK_VECTOR *m_alchemyEquipList;
	BACKPACK_VECTOR *m_alchemyFairyEquipList;
	BACKPACK_VECTOR *m_gemStoneList;
	unsigned int m_maxPackPos;					// ������������
	unsigned int m_defaultPackPos;				//���Ĭ�ϵı���������
	unsigned int m_unlockPackPos;				//�ѽ����ı���������
	unsigned int m_maxStoragePos;				//�ֿ��������
	unsigned int m_defaultStoragePos;			//Ĭ�ϵĲֿ������
	unsigned int m_unlockStoragePos;			//�ѽ����Ĳֿ�ĸ�����
	unsigned int m_defaultAlchemyBagPos;		//Ĭ�ϵ�������������
	unsigned int m_unlockAlchemyBagPos;			//�ѽ�����������������
	unsigned int m_defaultAlchemyStoragePos;	//Ĭ�ϵ����𱳰�������
	unsigned int m_unlockAlchemyStroragePos;	//�ѽ��������𱳰�������
	unsigned int m_surplusGemRecastNum;			//Ĭ�ϱ�ʯ��������
	std::map<unsigned int ,unsigned int>* m_searchNpcCostMap;
	std::list<ExchangeItem*>* m_exchangeItemList;
	bool b_isLoadExchangeItems;
};

#endif	