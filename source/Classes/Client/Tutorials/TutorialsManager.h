#pragma once

#include "cocos2d.h"
#include "TutorialsDataCenter.h"
#include "TutorialBase.h"

USING_NS_CC;

class TutorialsManager
{
public :
	TutorialsManager();
	~TutorialsManager();

	static TutorialsManager* Get();
	static void Destroy();

	void LoadData();
	/**
	* Instruction : ���ñ���
	* @param 
	*/
	void ResetValue();

	/**
	* Instruction : ����һ���̳�
	* @param 
	*/
	void StartOneTutorial(unsigned int id);

	/**
	* Instruction : ����ؼ��¼�
	* @param type 0 ���� 1 ˫��
	*/	
	void HandleOneEvent(const char* name,unsigned int type);
protected:
	/**
	* Instruction : ����һ��UI�̳�
	* @param 
	*/
	void StartOneUiTutorial(unsigned int id);
private:
	static TutorialsManager* mInstance;

	TutorialDataCenter* mDataCenter;
	TutorialBase* mTutorialInstance;	
};