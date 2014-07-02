#pragma once

class TimeProtocol
{
    friend class TimeManager;
public:
    virtual void onUpdateRemainTime(long remainTime) = 0;
};

//��ʱ����ţ����̨Эͬȷ��
#define TIMER_INSTANCE_COUNTDOWN 20001
#define TIMER_PVAI_COOLDOWN 20002
#define TIMER_PVAI_REWARD   20003