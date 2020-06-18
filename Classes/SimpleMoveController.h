#ifndef _SIMPLEMOVECONTROLLER_H_
#define _SIMPLEMOVECONTROLLER_H_


#include "cocos2d.h"
#include "Controller.h"
using namespace cocos2d;

class SimpleMoveController :public My_Controller
{
public:
	CREATE_FUNC(SimpleMoveController);
	virtual bool init();
	virtual void update(float dt);

	void set_speed(int ispeed);//�����ƶ��ٶ�
	void set_ixspeed(int ispeed);

	void set_iyspeed(int ispeed);
private:
	int m_ixspeed;//x������ƶ��ٶ�
	int m_iyspeed;//y������ƶ��ٶ�

	void registeKeyBoardEvent();
	ValueMap   map;
};

#endif
#pragma once