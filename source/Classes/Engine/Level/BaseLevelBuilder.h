#ifndef BASE_LEVEL_BUILDER_H
#define BASE_LEVEL_BUILDER_H

#include "cocos2d.h"
#include "SpriteSeer.h"
#include "SpriteTransPoint.h"
#include "ATLObjectInfo.h"

//////////////////////////////////////////////////////////////////////////
#define ELF_MAX						3


class LevelLayer;



class BaseLevelBuilder
{

public:

	BaseLevelBuilder(LevelLayer* levelLayer);
	virtual ~BaseLevelBuilder();


public:
	
	virtual bool			build(bool bStoryMode = false);
	virtual bool			excuteScript();

public:

	//----------------------------------------------------
	//			base creator used when build level
	//----------------------------------------------------
	void		createBacks();
	void		createPhysicsLayer();
	void		createObjects(CATLObjectInfo &info);

	void		createTransPoints();	

	void		createNpcs();
	void		createSeer();		

	void		createMonster();
	void		createMonsterBornPoints();

	//----------------------------------------------------
	//			used to add/remove other players
	//----------------------------------------------------
	void		addOtherPlayer(unsigned int uid, const char* userName,unsigned int playerType, cocos2d::CCPoint pt, unsigned int orient, unsigned int battleSide);
	void		removeOtherPlayer(unsigned int uid);
	SpriteSeer* getPlayer(unsigned int uid);

	///  add monster / delete monster
	void	addMonster(MonsterInitInfo info);
	void    removeMonster(unsigned int uid);

	void	showMonsterOrNot(bool bShow);

	/**
	* Instruction : 获取主城中的传送点实例
	* @param 
	*/
	virtual SpriteTransPoint* GetMainLandTransPointInstance();

private:

	LevelLayer*			m_level;

	SpriteTransPoint* m_mainLandTranspoint;
};



#endif