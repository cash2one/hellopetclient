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

#include "ILogicManager.h"
#include "SceneLayer.h"
#include "errcode.pb.h"
#include "cs_battle.pb.h"
#include "cocos2d.h"

#include "TXGUIHeader.h"
#include "IEvent.h"


using namespace cocos2d;




/*
* @XLogicManager, 	
@/// �߼����Ĺ������������л�����ͬ�ĺ�����Ϸģ��, ��Щģ������Ϸ����Ϊ���ݽ����з�
*
*/
class XLogicManager : 
	public CCNode, 
	public ILogicManager , 
	public TXGUI::ObserverProtocol,
    public ISocketEvent
{
public:
	/// �߼�����ö�ٱ�������
	typedef enum  
	{
		E_NOE          = 0,
		E_SELECT_ZONE  = 1,		//ѡ������������������
		E_CREATE_PLAYER_LAYER ,	//����������
		E_SELECT_CHARACTER ,    //��ɫѡ����沽��
		E_MAIN_GAME_LAYER ,		//��ʼ��Ϸ���
		E_GAME_HELP_LAYER ,		//��������
		E_PVP_LAYER ,	//pvpս�����
		E_PVE_LAYER,	//pve�������
		E_TASK_PANEL_LAYER ,

		// add more...

	}GAME_LOGIC_LAYER;

	typedef enum
	{
		E_WAITIN_FOR_COMMOND = 0, // ����״̬
		E_SENDING_SEVER = 1,	// �Ѿ����͵�¼/������/������Э���ȥ���������ȴ��ذ������������ƵĲ���
	}LOGIC_CHANGE_LAYER_STATUS;

	typedef void (*errFun)(db_errcode_t); 

public:
	XLogicManager();
	virtual ~XLogicManager();

	void  updateFps(float dt);

	void  updateNetChecker(float dt);

	void  WillEnterForeground();

	void  DidEnterBackground();

	//////////////////////////////////////////////////////////////////////////
		/// implement the interface of ILogicManager
	/*
	* @prototype: goToFrontend()
	* @note:
	*     bring the game to the front of the screen. prepare the resources and init all the game components.
	* @param: void
	* @return: void
	*/
	virtual void goToFrontend();

		
	/*
	* @prototype: startGame()
	* @note:
	*     start the game now, bring the player to the hometown.
	* @param: void
	* @return: void
	*/
	virtual void startGame();
	virtual void exitGame();

	// static instance
	static XLogicManager* sharedManager();

	// functions
	// go to a specific scene
	void  goToLayer(GAME_LOGIC_LAYER sceneTag, void *userData = NULL); 

	void connectToServer();

	void onConnectToSever();

	int getLoginStep();

	void logIn();

	void logInError(db_errcode_t error);

	void logOut();

	void networkDisConnected();

	void registerNetErrFun(errFun fun) { pNetErrFun = fun; }

	void unRegisterNetErrFun() {  pNetErrFun = NULL;  }

	void createRole(const std::string nick, const unsigned int type);

	void goToFb(unsigned int mapId, unsigned int battleId);

	void backToTown();

	void LeaveBattle();

	void FinishBattle();

	void createBattle(int battleId, int mapId);

	void changeMap(int mapId, KMapFromType fromMapType);

	void receivedItemsInfo();

	// ��Ϸ����ʱ������������Ҫ����Ϣ
	void initUserInfoFromSever(float time);

	db_errcode_t getNetErrorCode();

	void reqPlayerAttributes(int attributeId);

	void reqPlayerAttributes(int attributes[],int length);

	void reqAllPlayerAttributes();

	bool isAlreadyLogin();
	void loginSuccess();
protected:

	/// on messagebox network error!
	void OnNetworkMessageOK(CCObject* pObject);


	/// ��Ϣ��Ӧ����
	virtual void onBroadcastMessage(BroadcastMessage* msg);
    
    /// override ISocketEvent
	virtual void OnSocketError(int nError);
	virtual void OnConnected(int nResult);
	virtual void OnDisconnect();

protected:
	GAME_LOGIC_LAYER  m_eCurLayer;
	LOGIC_CHANGE_LAYER_STATUS  m_eCurStatus;
	int m_loginStep;
	errFun pNetErrFun;
	db_errcode_t mErrorCode;
	bool isGameStart;
	bool isRequiredItemsInfo;
	float	m_loginDataTime;
	bool	isInitLoginData;
	bool	b_isLoginGame;
	//// time ticked when application move to background
	long long   m_LastEnterBackgroundTime; 
};

extern "C"{

	extern void playerlogOut();
}