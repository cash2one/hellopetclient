//
//  MineManger.h
//  iSeer
//
//  Created by august on 12-4-9.
//  Copyright (c) 2012�� __MyCompanyName__. All rights reserved.
//

#ifndef iSeer_MineManger_h
#define iSeer_MineManger_h

#include "cocos2d.h"

#define UPDATETIME 43200


class MineManager
{
public:
    static MineManager* shareManager();    

    /*�ж��Ƿ񱻲ɣ���mapid��Ӧ����Ϣ�ڴ浵���м�¼���򷵻ظü�¼��Ӧ����Ϣ���Ѳ�true��δ��false��*/
    bool isMined(int mapid);
    
    /*�޸�mapid��Ӧ�Ĳɿ���Ϣ����ΪisMined*/
    void setIsMined(int mapid,bool isMined);
    
    /*�ж��Ƿ���Ը�����*/
    bool timeOut();
    
    /*����Ѿ�timeOut�������еĲɿ���Ϣ���ó�δ��*/
    void updateMap();
    
};


#endif
