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


//// define GLOBAL message 
#define  GM_CLOSE_PPVELAYER      0x10000001   /// close ppve message
#define  GM_CLOSE_PVPLAYER       0X10000002   /// close pvp message

#define  GM_APPLICATION_RESUME						0x10000003   /// resume from background
#define  GM_APPLICATION_ENTER_BACKGROUND			0x10000004   /// enter background when a phone call coming in

/// download map resources failed, the reason maybe be network disconnected
#define  GM_DOWNLOAD_MAP_FAIL		0x10000005
#define  GM_NETWORK_ERROR			0x10000006

/// userdata update msg
#define  GM_ATTR_COIN_UPDATE			0x10000007			//���������
#define  GM_ATTR_SP_UPDATE				0x10000008			//���ܸ���
#define  GM_ATTR_SP_CHIP_UPDATE			0x10000009			//��ʯ��Ƭ
#define  GM_ATTR_SP_DIAMOND_UPDATE		0x10000010			//שʯ
#define  GM_ATTR_HERO_LEVEL_UPDATE		0x10000011			//��ҵȼ�
#define  GM_ATTR_PHYSICAL_ATTACK_UPDATE		0x10000012		//������
#define  GM_ATTR_MAGIC_ATTACK_UPDATE		0x10000013		//ħ������
#define  GM_ATTR_SKILL_ATTACK_UPDATE		0x10000014		//���ܹ���
#define  GM_ATTR_PHYSICAL_DEFENCE_UPDATE	0x10000015		//�������
#define  GM_ATTR_MAGIC_DEFENCE_UPDATE		0x10000016		//ħ������
#define  GM_ATTR_SKILL_DEFENCE_UPDATE		0x10000017		//���ܷ���
#define  GM_ATTR_HEALTH_POINT_UPDATE		0x10000018		//����ֵ
#define  GM_ATTR_ACCURATE_UPDATE			0x10000019		//��׼
#define  GM_ATTR_DODGE_UPDATE				0x10000020		//����
#define  GM_ATTR_WRECK_UPDATE				0x10000021		//�ƻ�
#define  GM_ATTR_PARRY_UPDATE				0x10000022		//��
#define  GM_ATTR_CRITICAL_STRIKE_UPDATE		0x10000023		//����
#define  GM_ATTR_TENACITY_UPDATE			0x10000024		//����
#define  GM_ATTR_SLAY_UPDATE				0x10000025		//��ɱ
#define  GM_ATTR_SPEED_UPDATE				0x10000026		//����
#define  GM_ATTR_PROFICIENCY_UPDATE			0x10000027		//Ǳ��
#define  GM_ATTR_ABILITY_ALL_UPDATE			0x10000028		//ս��
#define  GM_ATTR_COURAGE_UPDATE				0x10000029		//����
#define  GM_ATTR_CHARM_UPDATE				0x10000030		//ħ��
#define  GM_ATTR_TRICK_UPDATE				0x10000031		//����
#define	 GM_ATTR_STAMINA_UPDATE				0x10000032		//����
#define	 GM_ATTR_REPUTATION_UPDATE			0x10000033		//����
#define	 GM_ATTR_EXP_UPDATE					0x10000034		//����
#define  GM_ATTR_PLAYER_EXPOLIT				0x10000035		//��ѫ
#define  GM_ATTR_PLAYER_EXPLOER_EXP			0x10000036		//��������
#define  GM_ATTR_GEM_RECAST					0x10000037		//��ʯ�����������
#define	 GM_ATTR_PLAYER_GEM_ANIMA			0x10000038		//��ʯ������

#define  GM_ATTR_EQUIP_LVUP_UESED_TIMES			0x10000039		//����ʣ�����
#define  GM_ATTR_EQUIP_LVUP_MAX_TIMES				0x10000040		//�����ܵĴ���

#define  GM_NETWORK_DISCONNCT				0x10000041		//���������ж�


#define  GM_CLOSE_TALENTLAYER    0X10000042  /// close talent message
#define  GM_CLOSE_AUTOONHOOK     0X10000043  /// close autoOnHook message

#define	 GM_LUA_LAYER_CLOSE		 0X10000044
