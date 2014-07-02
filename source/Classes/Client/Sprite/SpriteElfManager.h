#pragma once

#include "SpriteElf.h"
#include "Singleton_t.h"
#include "SpriteSeer.h"
#include <map>

class SpriteElfManager : public TSingleton<SpriteElfManager>
{
	//friend class SpriteElf;
public:    
	SpriteElfManager();
	virtual ~SpriteElfManager(); 

	/**
	* Instruction : �����������
	* @param 
	*/	
	SpriteElf*	CreateInstance(unsigned int s_id,int type);

	/**
	* Instruction : ����һ���������
	* @param 
	*/
	SpriteElf* CreateInstance(int type);

	/**
	* Instruction : ����Id��ȡһ���������
	* @param 
	*/	
	SpriteElf* GetOneInstance(int s_id);

	/**
	* Instruction : ��ȡ���еľ���ʵ��
	* @param 
	*/	
	const map<int, SpriteElf*>& GetAllInstance(void) const 
	{
		return m_mapElfIdAndInstances;
	}

	/**
	* Instruction : ���ݾ���Idɾ������
	* @param 
	*/	
	bool RemoveOneElf(unsigned int s_id,bool bDeleteElf  = true);

	/**
	* Instruction : �󶨾��鵺��������
	* @param 
	*/
	void AttachElfToOneHero(unsigned int elfTypeId,unsigned int heroId,SpriteSeer* parent = 0);

	/**
	* Instruction : ��վ���
	* @param 
	*/
	void ClearAllData();

	/**
	* Instruction : ɾ�����еľ���
	* @param 
	*/
	void RemoveAllElfInstance();

	/**
	* Instruction : ����һ��׷��״̬
	* @param 
	*/
	void PushOneElfChaseState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : ����һ������״̬
	* @param 
	*/
	void PushOneElfCloseToState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : ����һ������״̬
	* @param 
	*/
	void PushOneElfAttackState(SpriteSeer* pHero,int skillId,BaseElfAttachData* pData = 0);

	/**
	* Instruction : called by LevelLayer
	* @param 
	*/	
	void Update(float dt);
protected:
	/**
	* Instruction : ���һ��ʵ��
	* @param 
	*/	
	bool Add(unsigned int id,SpriteElf * instance);
public:
	// Note: ��������
	static cocos2d::CCPoint s_fixDistanceToHero;
protected:
	std::map<int, SpriteElf*> m_mapElfIdAndInstances;
};
