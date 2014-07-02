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
#include <stdlib.h>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "cmdDefine.h"

#include "Singleton_t.h"
#include "MonsterInfo.h"
#include "PetInfo.h"
#include "CharacterInfo.h"


using namespace  std;

//////////////////////////////////////////////////////////////////////////

class INFOID
{
public:
	INFOID(void) : id(0){}

	unsigned int  id;
};

class BATTLEINFO
{
public:
	BATTLEINFO();

	unsigned int physical_attack;
	unsigned int magic_attack;
	unsigned int skill_attack;
	unsigned int physical_defence;
	unsigned int magic_defence;
	unsigned int skill_defence;
	unsigned int health_point;
	unsigned int accurate ; // ����
	unsigned int dodge;		// ����
	unsigned int wreck;		// �ƻ�
	unsigned int parry;		// ��
	unsigned int critical_strike;	// ����
	unsigned int tenacity;			// ����
	unsigned int slay;				// ��ɱ
	unsigned int proficiency;
	unsigned int speed;				// ����
	unsigned int total_hp;
	unsigned int courage; // ����
	unsigned int charm; // ħ��
	unsigned int trick; // ����
	unsigned int effectiveness; // ս����
};

/// user base information
class USERINFO : public INFOID, public BATTLEINFO
{
public:

	USERINFO();

	char			userSession[SESSION_LENGTH];
	char szName[16];	
	char ip[30];
	char lastServerName[30];
	unsigned int port;
	long createdTime;

	unsigned int tokenId;
	unsigned int level;
	unsigned int exp;
	unsigned int nextExp;
	unsigned int mapId;
	unsigned int xPos;
	unsigned int yPos;
	unsigned int orient;
	unsigned int type;
	// add more data parameters
	unsigned int battleId;
	
	unsigned int battleSide;

	unsigned int m_spriteEnergy;	//����
	unsigned int m_gold;			//���
	unsigned int m_diamond;			//��ʯ
	unsigned int m_spriteChip;		//��ʯ����
	unsigned int m_reputation;		//����
	unsigned int m_stamina;			//����
	unsigned int m_alchemyBagUnlockPos;		//��ʯ�����ѽ�������
	unsigned int m_alchemyStorageUnlockPos;	//��ʯ�ֿ��ѽ�������
	unsigned int m_searchSpriteNpc;	//Ѱ��NPC
	unsigned int m_equipLvUpTotalTimes;		//װ�������ܴ���
	unsigned int m_equipLvUsedTimes;		//װ��������ʹ�ô���
	unsigned int m_gemRecastTimes;			//��ʯ��������
	unsigned int m_player_exploit;			//��ҹ�ѫ
	unsigned int m_playerExploerExperience; //�������
	unsigned int m_playerGemAnima;			//��ʯ����
};



class UserData : public TSingleton<UserData>
{
public :
	UserData();

	static const USERINFO & GetUserInfo();
	
	/// get user name
	static const char *  getUserName();

	/// get user id
	static unsigned int getUserId();

	static const char*	getUserSession();

	static unsigned int getTokenId();

	static unsigned int GetUserLevel();

	static unsigned int GetUserExp();

	static unsigned int GetUserMapId();

	static unsigned int GetUserXPos();

	static unsigned int GetUserYPos();

	static unsigned int GetUserOrient();

	static unsigned int GetUserType();

	static unsigned int GetSpriteEnergy();

	static unsigned int GetGold();
	
	static unsigned int GetDiamond();

	static unsigned int GetUserChip();

	static unsigned int GetLastPort();

	static const char* GetLastIP();

	static const char* GetLastServerName();

	static unsigned int getHeroHp();

	static unsigned int getHeroTotalHp();

	static void SetUserInfo(USERINFO info);

	void SetUserInfo(unsigned int id, USERINFO& info);
	USERINFO* GetUserInfo(unsigned int id);

	std::list<unsigned int>* GetOtherUserId();
	void clearOtherUserInfo();
	void removeOtherUser(unsigned int id);
protected:
	USERINFO m_stUserinfo;
	
	std::map<unsigned int, USERINFO> m_userInfoList;
};


// --------------------------------------------------------------------------------------------

class EntityInfo : public TSingleton<EntityInfo>
{
public:
	
	void Set(INFOID* pInfo);
	INFOID* GetInfo(unsigned int id);

	void Clear(void);

protected:
	std::map<unsigned int, INFOID*> m_infoList;
};