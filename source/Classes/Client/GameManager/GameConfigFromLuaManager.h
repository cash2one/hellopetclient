// TAOMEE GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Taomee Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 2012-2015 Taomee Game Technologies. 
//      All Rights Reserved.
//
// Taomee Game Technologies, Shanghai, China
// http://www.taomee.com
//

#pragma once
#include "Singleton_t.h"
#include <string>
#include "vector"
#include "TXGUI.h"
#include "UILayout.h"


extern "C" {
#	include "lua.h"
#	include "lualib.h"
#	include "lauxlib.h"
}
#include "lua_tinker.h"

struct lua_State;
class EquipmentItem;
class ItemBase;


class GameConfigFromLuaManager :public TSingleton<GameConfigFromLuaManager>
{
public:
	GameConfigFromLuaManager();
	virtual ~GameConfigFromLuaManager();

	int table_next(lua_State *L, int i,char **k, char **v);

	bool checkAnyLoadFile(string filePath);

	bool checkConfigLoadFile(string fileName);

public:
   /**
    * @brief , getItemResourceId()
    * @param itemID, 
    * @return int, the value of given item, 
    * @  get the item resource id which generated by the ASprite tools.
    */
	int getItemResourceId(const int itemId);

	/**
    * @brief , getEquipmentItem()
    * @param itemID, equipment id
	* @param item, EquipmentItem
    * @return bool, if get the value successfully , return true, otherwise return false 
    * @  get the item resource id which generated by the ASprite tools.
    */
	bool  getEquipmentItem(const int itemId, EquipmentItem* item);

	bool  getItem(const int itemId, ItemBase* item);

	//const char* getMonsterDefNameById(const int monsterId);

	//const char* getCharacterNameById(const int id);

	//const char* getCharacterDesById(const int id);

	//const char* getCharacterHeadPicById(const int id);

	//const char* getCharacterPicFileById(const int id);

	//const char* getNpcNameById(const int npcId);

	//const char* getNpcMottoById(const int npcId);

	//int getNpcTypeId(const int npcId);

	//const char* getNpcHeadIconName(const int npcId);

	//const char* getNpcBodyIconName(const int npcId);

	//const char* getNpcTypeFlagIconName(const int npcId);

	//const char* getLocalizationSimpleChinese(const char * flag);

	//const char* getLocalizationChinese(const char * flag);

	//const char* getLocalizationEnglish(const char * flag);

	//const char* getLocalizationKorean(const char * flag);

	//const char* getLocalizationJapanese(const char * flag);

	//int getMusicIdByMapId(const int mapId);

	//// instance information
	//const char* getInstanceIconName(const int instanceId);

	//const char* getInstanceName(const int instanceId);
	
	//const char* getVisionNum();

	int getSearchSpiritNpcCost(int npcId);

	//int getInstanceType(int mapId);

	//long	getOsTimeWithTicks();

	void	getOneMapMonsterIds(unsigned int mapId,std::vector<unsigned int> &monsterIdVec);
	void	getExchangeItems();
	/**
	* Instruction : 创建ToolBar
	* @param 
	*/
	TXGUI::UILayout* InitLayer(CCNode* parentLayer,const char* initFunName);

	// Skill UI 
	void	InitSkillUIDataCenter();

	void	PushSkillItemToLua(unsigned int skillId,unsigned int levelId,unsigned int maxLevel);

	void PushDiffInfoToLua(unsigned int skill_id,unsigned int skill_level,
		unsigned int next_money,unsigned int next_exploit,unsigned int next_lv,float diff_own_cd,float continue_time_cd,unsigned int diff_hurt,
		unsigned int physical_attack,unsigned int magic_attack,unsigned int skill_attack,unsigned int physical_defence,
		unsigned int magic_defence,unsigned int skill_defence,unsigned int health_point,
		unsigned int accurate,unsigned int dodge,unsigned int wreck,unsigned int parry,unsigned int critical_strike,
		unsigned int tenacity,unsigned int slay,unsigned int speed,unsigned int proficiency);

	void AddUserSkillRspToLua(unsigned int skillId,unsigned int level);
	void PushSkillSlotInfoToLua(unsigned int slotIndex,unsigned int value);
	void ListItemDragToSLotItem(unsigned int skillItemIndex,unsigned int slotIndex);
	void SlotItemToSelf(unsigned int preSlotIndex,unsigned int toSlotIndex);
	void SkillLevelUpSucMessage();

	// audio table
	int getInstanceMusicId(const int raidId,const int mapId);

	void PushLayerInstanceToLua(cocos2d::CCLayer* pLayer);
	
private:
	void initLuaState();

	//Gameconfig目录下的文件加载
	

	bool initLuaMusicTable();

	bool checkMapMusicContent();

	//bool checkOsCommondMethodContent();


	bool checkToolBarTableContent();

	bool checkSkillUIContent();

	bool checkCommonDefineContent();


	lua_State* getMainLuaState();

	int getExchangeId(int num);
	/// get equipment string field value
	bool	getEquipmentItemFieldById(const int itemId, const char* field , const char* itemState, std::string& Val) ;

	/// get equipment double field value
	bool	getEquipmentItemFieldById(const int itemId, const char* field , const char* itemState, double& Val) ;

	/// get equipment int field value
	bool	getEquipmentItemFieldById(const int itemId, const char* field , const char* itemState, int& Val) ;

	/// get equipment bool field value
	bool	getEquipmentItemFieldById(const int itemId, const char* field , const char* itemState, bool& Val) ;

	bool	getExchangeItemFieldById(const int itemId, const char* field , std::string& Val) ;

	bool	getExchangeItemFieldById(const int itemId, const char* field , int& Val) ;
private:
	lua_State *m_configLuaState;

	//已经加载的lua文件集合
	set<string> loadedFiles;

	bool m_isLoadMapMusicData;
	//bool m_isLoadOsCommonMethodData;
	bool m_isLoadToolBarTableData;
	bool m_isLoadSkillConfigData;
	bool m_isLoadCommonDefineData;
};


