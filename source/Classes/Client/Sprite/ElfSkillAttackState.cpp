#include "ElfSkillAttackState.h"

#include "StateEventType.h"
#include "SkillInfo.h"
#include "SkillDispMgr.h"
#include "BaseAttackState.h"
#include "LevelManager.h"
#include "SpriteMonsterMgr.h"
#include "GameAudioManager.h"
#include "LevelLayer.h"
#include "ParticleManager.h"
#include "SpriteElfConfigFromLua.h"
#include "StoryInstanceDirector.h"

// ---------------------------------------------------------------------------------

ElfAttackTrigger::ElfAttackTrigger( BaseElfEvt* pEvt )
	: ElfBaseState(pEvt)
{
	m_Type = ToElfAttackTrigger;
}

bool ElfAttackTrigger::Entered()
{
	ElfBaseState::Entered();

	m_cd = 0.0f;

	m_outerCircleRadius = SpriteElfConfigFromLuaManager::getInstance()->GetOuterCircleRadius();

	m_outerCircleRadius *= m_outerCircleRadius;

	return true;
}

void ElfAttackTrigger::Update( float dt )
{
	ElfBaseState::Update(dt);

	if(m_pRole->getTag() != MAP_TAG_SEER)
		return;

	m_cd -= dt;
	if(m_cd <= 0.0f)
	{
		float dis = ccpDistanceSQ(m_pRole->getPosition(), m_pElf->getPosition());
		if(dis < m_outerCircleRadius && !StoryInstanceDirector::Get()->IsStart())
		{
			if(GetNearestMonster() || m_pSkill->aim == FAIRY_SKILL_INFO::E_HERO)
			{
				m_pSkillStateMachine->Remove(ToElfCloseTo);

				m_cd = m_pSkill->ownCD;
				m_pSkillStateMachine->Push(m_pStateFactory->Create(ToElfSkillAttack, m_pRole, m_actionId, m_pEvt->m_pAttachData));
			}
		}
		
	}
}

void ElfAttackTrigger::Exited()
{
	ElfBaseState::Exited();


}


cocos2d::CCNode* ElfAttackTrigger::GetNearestMonster( void )
{
	cocos2d::CCNode* pRet = NULL;
	float minDis = 0.0f;
	minDis = m_pSkill->longDistanceAttackRange;

	if(minDis <= 0.0f)
		minDis = 320.0f;

	minDis *= minDis;
	if(LevelManager::sShareInstance()->isCurrentPVPLevel())
	{
		if(LevelManager::sShareInstance()->getCurrentLevelLayer())
		{
			USERINFO* pHeroInfo = UserData::Get()->GetUserInfo(m_pRole->GetID());

			std::map<unsigned int, OthersPlayerInfo>& otherPlayer = LevelManager::sShareInstance()->getCurrentLevelLayer()->m_othersPlayerInfo;
			for(std::map<unsigned int, OthersPlayerInfo>::const_iterator iter = otherPlayer.begin(); iter != otherPlayer.end(); iter++)
			{
				SpriteSeer* pOhterHero = iter->second.seer; 

				if(m_pRole == pOhterHero || pOhterHero == NULL)
					continue;

				USERINFO* pOtherInfo = UserData::Get()->GetUserInfo(pOhterHero->GetID());
				if(pHeroInfo && pOhterHero)
				{
					if(pHeroInfo->battleSide % 2 == pOtherInfo->battleSide % 2)
						continue;
				}

				float dis = ccpDistanceSQ(pOhterHero->getPosition(), m_pElf->getPosition());
				if( dis <= minDis)
				{
					pRet = pOhterHero;
					minDis = dis;

				}
			}

			
		}
	}
	else
	{
		const map<int, SpriteMonster*>& allMonster = SpriteMonsterMgr::Get()->GetAllMonster();
		for(map<int, SpriteMonster*>::const_iterator iter = allMonster.begin(); iter != allMonster.end(); iter++)
		{
			float dis = ccpDistanceSQ(iter->second->getPosition(), m_pElf->getPosition());
			if( dis <= minDis)
			{
				pRet = iter->second;
				minDis = dis;

			}
		}
	}
	

	return pRet;
}
// ---------------------------------------------------------------------------------

ElfAimDirectionHandler::ElfAimDirectionHandler( BaseElfEvt* pEvt )
	:ElfBaseState(pEvt)
	, m_bEntered(false)

{
	m_Type = ToElfAimDirectionHandler;
}

bool ElfAimDirectionHandler::Entered()
{
	ElfBaseState::Entered();
	if(m_bEntered)
		return false;

	m_bAimMonster = false;

	SkillBeginReceiverHandler* pReceiver = dynamic_cast<SkillBeginReceiverHandler*>(m_pContainer->GetState(ToSkillBeginReceiverHandler));
	if(pReceiver)
	{
		m_aimDir = pReceiver->GetDirection();
		m_bAimMonster = pReceiver->IsAimMonster();
		m_nearestMonsterPos = pReceiver->GetNearestMonsterPos();
		CCLog("cur Pos(%f, %f), receiver Pos(%f, %f)", m_pRole->getPosition().x, m_pRole->getPosition().y, pReceiver->GetRolePos().x, pReceiver->GetRolePos().y);
		
	}
	else
	{
		m_aimDir = GetAimDirection();

	}
	return true;
}

cocos2d::CCPoint ElfAimDirectionHandler::GetNearestMonsterPos( void )
{
	return m_nearestMonsterPos;
}

bool ElfAimDirectionHandler::IsAimMonster( void )
{
	return m_bAimMonster;
}

cocos2d::CCPoint ElfAimDirectionHandler::GetDirection( void )
{
	return m_aimDir;
}


cocos2d::CCPoint ElfAimDirectionHandler::GetAimDirection()
{
	CCPoint ret = m_pElf->getDirectionVector();
	CCPoint rolePos = m_pElf->getPosition();

	
	if(LevelManager::sShareInstance()->isCurrentPVPLevel())
	{
		if(LevelManager::sShareInstance()->getCurrentLevelLayer())
		{
			float minDis = m_pSkill->longDistanceAttackRange;

			if(minDis <= 0.0f)
				minDis = 320.0f;

			minDis *= minDis;

			SpriteSeer* pNearestHero = NULL;

			std::map<unsigned int, OthersPlayerInfo>& otherPlayer = LevelManager::sShareInstance()->getCurrentLevelLayer()->m_othersPlayerInfo;

			for(std::map<unsigned int, OthersPlayerInfo>::const_iterator iter = otherPlayer.begin(); iter != otherPlayer.end(); iter++)
			{
				SpriteSeer* pOhterHero = iter->second.seer; 
				if(m_pRole == pOhterHero || pOhterHero == NULL)
					continue;

				float dis = ccpDistanceSQ(pOhterHero->getPosition(), m_pElf->getPosition());
				if( dis <= minDis)
				{
					pNearestHero = pOhterHero;
					minDis = dis;

				}
			}

			if(pNearestHero)
			{
				m_bAimMonster = true;
				m_nearestMonsterPos = pNearestHero->getPosition();
				ret = ccpSub(m_nearestMonsterPos, rolePos);
			}
		}
	}
	else
	{
		SpriteMonster* pNearestMonster = GetNearestMonster();

		if(pNearestMonster)
		{
			m_bAimMonster = true;
			m_nearestMonsterPos = pNearestMonster->getPosition();
			ret = ccpSub(m_nearestMonsterPos, rolePos);

		}
	}

	

	ret = ccpNormalize(ret);

	return ret;
}

SpriteMonster* ElfAimDirectionHandler::GetNearestMonster( void )
{
	SpriteMonster* pRet = NULL;
	float minDis = 0.0f;
	minDis = m_pSkill->longDistanceAttackRange;

	if(minDis <= 0.0f)
		minDis = 320.0f;

	minDis *= minDis;

	const map<int, SpriteMonster*>& allMonster = SpriteMonsterMgr::Get()->GetAllMonster();
	for(map<int, SpriteMonster*>::const_iterator iter = allMonster.begin(); iter != allMonster.end(); iter++)
	{
		float dis = ccpDistanceSQ(iter->second->getPosition(), m_pElf->getPosition());
		if( dis <= minDis)
		{
			pRet = iter->second;
			minDis = dis;

		}
	}

	return pRet;
}

// --------------------------------------------------------------------------------------------------------
ElfAnimHandler::ElfAnimHandler( BaseElfEvt* pEvt  )
	:ElfBaseState(pEvt)
	, m_bAnimMonster(false)
{
	m_Type = ToElfAnimHandler;
}


bool ElfAnimHandler::Entered()
{
	ElfBaseState::Entered();

	m_effectDisplacement = m_pSkill->longDistanceAttackRange;

	m_bAnimMonster = false;
	m_bStartLinkTime = false;

	if(m_pSkill->soundID > 0)
		GameAudioManager::sharedManager()->playEffect(m_pSkill->soundID, false);

	/*UserSkillInfo info;
	if(SkillDispMgr::Get()->GetOneSkillInfoById(m_pSkill->id, info))
		m_fContinueTime = info.parts(0).continue_time();*/
	m_fContinueTime = 0.0f;
	//m_fContinueTime = m_pSkill->continueTime;

	FState* pState = m_pContainer->GetState(ToElfAimDirectionHandler);

	if(!pState)
	{
		pState = m_pStateFactory->Create(ToElfAimDirectionHandler, m_pRole, m_actionId, m_pEvt->m_pAttachData);
		m_pContainer->Push(pState);
	}

	ElfAimDirectionHandler* pAimDirection = dynamic_cast<ElfAimDirectionHandler*>(pState);
	if(pAimDirection)
	{
		m_bAnimMonster = pAimDirection->IsAimMonster();
		m_aimDir = pAimDirection->GetDirection();
		m_nearestMonsterPos = pAimDirection->GetNearestMonsterPos();

		if(m_bAnimMonster)
		{
			if(m_pSkill->longDistanceEffectSpeed <= 0)
				m_effectDisplacement = ccpDistance(m_pElf->getPosition(), m_nearestMonsterPos);
		}
	}

	SetNormalAttackDir();

	return true;
}



void ElfAnimHandler::Update( float dt )
{
	ElfBaseState::Update(dt);

	if(m_pSkill->animation[DIRECTION_LEFT].animationID != (unsigned int)-1 &&
		m_pSkill->animation[DIRECTION_LEFT].animationID != 0)
	{
		ANIMATION_STATE aniState = m_pElf->getCurAnimationState();
		switch(aniState)
		{
		case kType_COMPLETE:
			m_bStartLinkTime = true;
			break;
		default:
			break;
		}
	}


	//m_fContinueTime -= dt;

	//float fContinueTime = 0.0f; 
	/*UserSkillInfo info;
	if(SkillDispMgr::Get()->GetOneSkillInfoById(m_pSkill->id, info))
	fContinueTime = info.parts(0).continue_time();*/

	/*fContinueTime = m_pSkill->continueTime;

	if(fContinueTime > 0.0f && m_fContinueTime <= 0.0f)
	{

	ChangeToLinkTime();
	return;


	}
	else */if(m_bStartLinkTime)
	{
		/*if(m_fContinueTime > 0.0f)
		{
			m_bStartLinkTime = false;
			SetNormalAttackDir();
		}
		else*/
		{
			ChangeToLinkTime();
		}
	}
}

void ElfAnimHandler::Exited()
{
	ElfBaseState::Exited();
		
	GameAudioManager::sharedManager()->stopEffect(m_pSkill->soundID);
	
}

void ElfAnimHandler::SetNormalAttackDir()
{
	if(m_pSkill == NULL)
		return;

	bool bFlipX = false; 
	DIRECTION_ACTOR faceDir = DIRECTION_UP;
	if(m_aimDir.x > 0.0f)
	{
		if(m_aimDir.y > 0.0f)
		{
			// 第一象限
			faceDir = DIRECTION_UP;
		}
		else
		{
			faceDir = DIRECTION_BOTTOM;
			bFlipX = true;
		}
	}
	else
	{
		if(m_aimDir.y > 0.0f)
		{
			// 第二象限
			faceDir = DIRECTION_UP;
			bFlipX = true;
		}
		else
		{
			faceDir = DIRECTION_BOTTOM;
		}
	}

	const tagSkillInfo::ANIMATION_INFO* pAnimation = NULL;

	pAnimation = &(m_pSkill->animation[faceDir]);

	m_animationID = pAnimation->animationID;

	if(m_animationID > 0)
	{
		m_pElf->SetAnim(pAnimation->animationID, 1, false);
		m_pElf->SetAnimFlipX(bFlipX);
	}
	else
	{	
		// TODO : 
		ChangeToLinkTime();
	}

}

void ElfAnimHandler::ChangeToLinkTime( void )
{
	if(m_pContainer != NULL)
	{
		m_pContainer->Remove(this);
		m_pSkillStateMachine->Remove(dynamic_cast<FState*>(m_pContainer));
	}
}

// ------------------------------------------------------------------------

ElfEffectAnimHandler::ElfEffectAnimHandler( BaseElfEvt* pEvt )
	: ElfBaseState(pEvt)
	, m_bInitDir(false)
{
	m_Type = ToElfEffectAnimHandler;
}

bool ElfEffectAnimHandler::Entered()
{
	ElfBaseState::Entered();

	m_pEffect = NULL;
	m_continueTime = 0.0f;

	if(m_pSkill->effectID > 0)
	{
		if(m_pSkill->effectSoundID > 0)
		{
			GameAudioManager::sharedManager()->playEffect(m_pSkill->effectSoundID, false);
		}

		m_pEffect = GetEffect(m_pSkill->effectID);
		
		Push(new MagicCheckerHandler(new MagicCheckerEvt(m_pRole, m_actionId, m_pEffect)));


		ATTACH_POINT_TYPE apt = kType_SHOOT_HOR;
		switch(GetAnimDir())
		{
		case DIRECTION_UP:
			apt = kType_SHOOT_UP;
			break;
		case DIRECTION_BOTTOM:
			apt = kType_SHOOT_DOWN;
			break;
		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
			apt = kType_SHOOT_HOR;
			break;
		default:
			apt = kType_SHOOT_HOR;
			break;
		}

		m_dir = m_attackDir;
		m_displacement = m_attackDisplacement;

		if(m_pSkill->type != FAIRY_SKILL_INFO::E_BUFFER)
		{
			if(!m_pSkill->bLock)
			{
				m_pEffect->setPosition(ccp(0.0f, 0.0f));
				m_initDir.setPoint(0.0f, 1.0f);
				float degree = acosf(ccpDot(m_initDir, m_dir)) / 3.1415926 * 180.0f;
				if(m_dir.x < 0)
					degree = -degree;
				m_pEffect->getRoot()->setRotation(degree);
			}
		}
		



		m_speed = m_pSkill->longDistanceEffectSpeed;
		
		CCPoint pos = m_pElf->getAttachPoint(apt);
		switch(m_pSkill->aim)
		{
		case FAIRY_SKILL_INFO::E_HERO:
			{
				CCPoint pos = m_pRole->getPosition();
				pos.y += 16.0f;
				m_pEffect->setPosition(pos);
				m_continueTime = m_pSkill->continueTime;
			}
			break;
		case FAIRY_SKILL_INFO::E_FULL_SCREEN:
			{
				CCPoint cameraOffset = CCDirector::sharedDirector()->getLevelRenderCameraOffset();
				CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
				m_pEffect->setPosition(ccp(cameraOffset.x + visibleSize.width / 2, cameraOffset.y + visibleSize.height / 2));
			}
			break;
		default:
			m_pEffect->setPosition( m_pElf->getPosition() + pos );
			break;
		}
		
		if(m_speed <= 0.0f && m_displacement > 0.0f)
		{
			m_pEffect->SetAnim(kType_Play,1,false);

		}
		else
		{
			m_pEffect->SetAnim(kType_Play,1,true);
		}

		if(m_pEffect->getParent() != LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer())
		{
			LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer()->addChild(m_pEffect, LevelLayer::sCalcZorder(m_pEffect->getPosition()));
		}
		else
		{
			m_pEffect->setZOrder(LevelLayer::sCalcZorder(m_pEffect->getPosition()));
		}

	}

	return true;
}

void ElfEffectAnimHandler::Update( float dt )
{
	ElfBaseState::Update(dt);
	StatePoller::Update(dt);

	if(m_pEffect == NULL)
	{
		m_pContainer->Remove(this);

		FState* pState = dynamic_cast<FState*>(m_pContainer);
		m_pSkillStateMachine->Remove(pState);

	}
	else
	{
		if(m_pSkill->aim == FAIRY_SKILL_INFO::E_HERO)
		{
			if(m_pSkill->type == FAIRY_SKILL_INFO::E_BUFFER && m_continueTime <= 0.0f)
			{
				bool bComplete = false;
				
				ANIMATION_STATE aniState = m_pEffect->getCurAnimationState();
				switch(aniState)
				{
				case kType_COMPLETE:
					bComplete = true;
					break;
				default:
					break;
				}
				
				if(bComplete)
				{
					m_pEffect->setVisible(false);
					m_pContainer->Remove(this);
					FState* pState = dynamic_cast<FState*>(m_pContainer);
					m_pSkillStateMachine->Remove(pState);
				}
			}
			else
			{
				m_continueTime -= dt;
				if(m_continueTime > 0.0f)
				{
					CCPoint pos = m_pRole->getPosition();
					pos.y += 16.0f;
					m_pEffect->setPosition(pos);
					LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer()->reorderChild(m_pEffect, LevelLayer::sCalcZorder(pos));

				}
				else
				{
					m_pEffect->setVisible(false);
					m_pContainer->Remove(this);
					FState* pState = dynamic_cast<FState*>(m_pContainer);
					m_pSkillStateMachine->Remove(pState);
				}
			}
			
		}
		else
		{
			if(m_displacement > 0.0f)
			{
				float d = 0.0f;
				if(m_speed <= 0.0f)
				{
					d = m_displacement;
				}
				else
				{
					d = m_speed * dt;

					if(m_displacement < d)
					{
						d = m_displacement;
					}
				}

				m_displacement -= d;
				CCPoint pos = m_pEffect->getPosition();
				pos = ccpAdd(pos, ccpMult(m_dir, d));
				m_pEffect->setPosition(pos);

				LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer()->reorderChild(m_pEffect, MAP_Z_OBJ_TOP);
			}
			else
			{
				bool bComplete = true;
				if(m_speed <= 0.0f)
				{
					bComplete = false;
					ANIMATION_STATE aniState = m_pEffect->getCurAnimationState();
					switch(aniState)
					{
					case kType_COMPLETE:
						bComplete = true;
						break;
					default:
						break;
					}
				}

				if(bComplete)
				{
					m_pEffect->setVisible(false);
					m_pContainer->Remove(this);
					FState* pState = dynamic_cast<FState*>(m_pContainer);
					m_pSkillStateMachine->Remove(pState);
				}

			}
		}
		
	}
}

void ElfEffectAnimHandler::Exited()
{
	ElfBaseState::Exited();
	StatePoller::Exit();

	if(LevelManager::sShareInstance()->getCurrentLevelLayer() &&
		LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer())
	{
		cocos2d::CCArray* pArray = LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer()->getChildren();
		if(pArray)
		{
			for(unsigned int i = 0; i < pArray->data->num; i++)
			{
				EffectSprite* pEffect = dynamic_cast<EffectSprite*>(pArray->data->arr[i]);
				if(pEffect)
				{
					if(m_pEffect == pEffect)
					{
						m_pEffect->setVisible(false);
						m_pEffect = NULL;
					}
				}
			}
		}
	}

}

void ElfEffectAnimHandler::SetInitDirection( CCPoint dir )
{
	m_bInitDir = true;
	m_initDir = dir;
}

cocos2d::CCPoint ElfEffectAnimHandler::GetAnimDirVector( void )
{
	CCPoint ret;
	int animID = m_pElf->GetAnimID();
	if(m_pSkill->animation[DIRECTION_LEFT].animationID == animID)
	{
		if(m_pElf->IsAnimFlipX())
		{
			ret.setPoint(1.0f, 0.0f);
		}
		else
		{
			ret.setPoint(-1.0f, 0.0f);
		}

	}
	else if(m_pSkill->animation[DIRECTION_RIGHT].animationID == animID)
	{
		ret.setPoint(1.0f, 0.0f);
	}
	else if(m_pSkill->animation[DIRECTION_UP].animationID == animID)
	{
		ret.setPoint(0.0f, 1.0f);
	}
	else if(m_pSkill->animation[DIRECTION_BOTTOM].animationID == animID)
	{
		ret.setPoint(0.0f, -1.0f);
	}

	CCLog("ElfEffectAnimHandler animID : %ld, Dir : (%f, %f)", animID, ret.x, ret.y );

	return ret;
}

DIRECTION_ACTOR ElfEffectAnimHandler::GetAnimDir(void)
{
	DIRECTION_ACTOR ret;
	int animID = m_pRole->GetAnimID();


	if(m_pSkill->animation[DIRECTION_LEFT].animationID == animID)
	{
		if(m_pRole->IsAnimFlipX())
		{
			ret = DIRECTION_RIGHT;
		}
		else
		{
			ret = DIRECTION_LEFT;
		}
	}
	else if(m_pSkill->animation[DIRECTION_UP].animationID == animID)
	{
		ret = DIRECTION_UP;

	}
	else if(m_pSkill->animation[DIRECTION_BOTTOM].animationID == animID)
	{
		ret = DIRECTION_BOTTOM;

	}
	else
	{
		ret = DIRECTION_UNKNOW;
	}

	CCLog("ElfEffectAnimHandler animID : %ld, Dir : %ld", animID, ret );

	return ret;
}


void ElfEffectAnimHandler::SetAttackDir( CCPoint dir, float displacement )
{
	m_attackDir = dir;
	m_attackDisplacement = displacement;

}

EffectSprite* ElfEffectAnimHandler::GetEffect( int id )
{
	EffectSprite* pRet = NULL;
	if(LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer())
	{
		cocos2d::CCArray* pArray = LevelManager::sShareInstance()->getCurrentLevelLayer()->getObjectLayer()->getChildren();
		if(pArray)
		{
			for(unsigned int i = 0; i < pArray->data->num; i++)
			{
				EffectSprite* pEffect = dynamic_cast<EffectSprite*>(pArray->data->arr[i]);
				if(pEffect)
				{
					if(pEffect->getType() == id)
					{
						if(!pEffect->isVisible())
						{
							pRet = pEffect;
							break;
						}
					}
				}
			}
		}
	}

	if(pRet == NULL)
	{
		pRet = ParticleManager::Get()->createEffectSprite(id,"");

	}

	pRet->setVisible(true);

	return pRet;
}


// ----------------------------------------------------------------------------------

ElfSkillAttackState::ElfSkillAttackState(BaseElfEvt *pEvt) : ElfBaseState(pEvt)
{
	m_Type = ToElfSkillAttack;
}

ElfSkillAttackState::~ElfSkillAttackState( void )
{
}

bool ElfSkillAttackState::Entered()
{
	ElfBaseState::Entered();
	//CCLog("ElfSkillAttackState::Entered()----------------------------------");
	if(!m_pSkill)
		return false;

	m_attackBoxFrame = -1;

	ElfAnimHandler* pAnimHandler = (ElfAnimHandler*)m_pStateFactory->Create(ToElfAnimHandler, m_pRole, m_actionId, m_pEvt->m_pAttachData);
	Push(pAnimHandler);

	m_attackDir = pAnimHandler->GetAttackDir();
	m_attackDisplacement = pAnimHandler->GetEffectDisplacement();
	
	Push(new SkillBeginSenderHandler( new BaseAttackEvt( m_pRole, m_actionId ) ));

	return true;
}

void ElfSkillAttackState::Exited()
{
	ElfBaseState::Exited();
	StatePoller::Exit();

	m_pSkillStateMachine->Push(m_pStateFactory->Create(ToElfCloseTo, m_pRole, m_actionId, m_pEvt->m_pAttachData));
}

void ElfSkillAttackState::Update(float dt)
{
	ElfBaseState::Update(dt);
	StatePoller::Update(dt);

	if(m_pSkill->effectID > 0)
	{
		int animID = m_pElf->GetAnimID();
		//CCLOG("animID : %ld , Cur Fram : %ld", animID, m_pRole->getCurAnimationFrameID());
		if(animID == m_pSkill->animation[DIRECTION_LEFT].animationID ||
			animID == m_pSkill->animation[DIRECTION_RIGHT].animationID ||
			animID == m_pSkill->animation[DIRECTION_UP].animationID ||
			animID == m_pSkill->animation[DIRECTION_BOTTOM].animationID 

			)
		{
			cocos2d::CCRect heroAttackBox = m_pElf->getRelativeParentAttackBox();
			if(heroAttackBox.size.width > 0 || heroAttackBox.size.height > 0 )
			{
				int curFrame = m_pRole->getCurAnimationFrameID();
				if(m_attackBoxFrame == -1)
				{
					m_attackBoxFrame = curFrame;
					ElfEffectAnimHandler* pEffect = (ElfEffectAnimHandler*)m_pStateFactory->Create(ToElfEffectAnimHandler,m_pRole,  m_actionId, m_pEvt->m_pAttachData);
					pEffect->SetAttackDir(m_attackDir, m_attackDisplacement);
					m_pSkillStateMachine->Push(pEffect);
				}

			}
		}

	}

}

void ElfSkillAttackState::Reset()
{
	ElfBaseState::Reset();
}