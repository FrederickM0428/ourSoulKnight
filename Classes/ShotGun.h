#ifndef _ShotGun_H_
#define _ShotGun_H_

#include "Gun.h"
class ShotGun :public Gun {
public:
	ShotGun();													//���ڳ�ʼ�����������ԣ�֮��ŵ�����������������ȥ
	~ShotGun();													//������������ûɶ�ã��ȷ�����
	static ShotGun* create(const std::string& filename);
	virtual bool init(const std::string& filename);
	
	Vec2 increaseBy30Degree(const Vec2& pos);
	Vec2 reduceBy30Degree(const Vec2& pos);
	virtual void fire(Scene* currentScene, const Vec2& pos);
	
};

#endif
#pragma once