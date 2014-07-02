#pragma once

#include "Singleton_t.h"
#include "SpriteSeer.h"
#include "UILayout.h"

typedef struct AIPlayerInfo
{
	string name;
	int level;
	int rank;
	int type;
	int id;
}AIPlayerInfo;

typedef struct AILogInfo
{
	string name;
	bool direct;//true ������false����
	bool win;
}AILogInfo;

typedef struct AILayerBasicInfo
{
	int remainCount;
	long coolDownTime;
	long rewardGetTime;
	int rewardCoin;
	int rewardReputation;
}AILayerBasicInfo;

class PvAIManager : public TSingleton<PvAIManager>
{
public:
	PvAIManager();
	~PvAIManager();

	//����������ת
	void sendPvAIReq(int buttonIndex);
	void sendPvAIInfoReq();

	//����������Ϣ
	void setHeroRank(int rank){this->heroRank = rank;}

	void setAIPlayerId(int uid){this->aiPlayerId = uid;}
	int getAIPlayerId(){return aiPlayerId;}

	void setAIPlayerVec(vector<AIPlayerInfo> infos){this->aiPlayerVec = infos;}
	void setAILogInfoVec(vector<AILogInfo> logs){this->aiLogInfoVec = logs;}

	void setAISkillsId(vector<int> equipSkills){this->skills = equipSkills;}

	void setAIAutoAttack(bool autoAttack);

	//��������
	void refreshPvAILayer();
	void Update(float dt);
private:
	void moveToHero();

	int getBestSkill();

private:
	//���������Ϣ
	int heroRank;

	SpriteSeer * aiPlayer;

	vector<int> skills;

	float aiAutoAttackCDTime;
	bool aiAutoAttack;
	int aiPlayerId;

	vector<AIPlayerInfo> aiPlayerVec;
	vector<AILogInfo> aiLogInfoVec;
	AILayerBasicInfo basicInfo;

	TXGUI::UILayout * pvaiLayout;
};