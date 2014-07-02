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
#ifndef NETWORK_MSG_CMD_DEFINE_H
#define NETWORK_MSG_CMD_DEFINE_H


//-----------------------------------------------------------
//		list all message name here
//-----------------------------------------------------------


enum 
{
	CMD_LOGIN_SERVER = 10000,
	CMD_LOGOUT		= 10001,
	CMD_RELOGIN		= 10002,
	CMD_GET_ITEMS   = 10003,

	//...

};


#define CUR_VERSION         1   //��ǰ�汾���룬 ÿ�η��汾ǰһ��Ҫ�޸����ֵ�� ÿ�ε��� 1 ���ڴ浵�����ж�
#define KPLAYER_NAME_LEN		16
#define KDEVICE_ID_LEN      64
#define KVERSION_LEN			5
#define SESSION_LENGTH	24

#endif