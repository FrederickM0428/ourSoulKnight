#ifndef _Weapon_H_
#define _Weapon_H_

#include "cocos2d.h"
USING_NS_CC;

class Weapon :public Sprite {
	CC_SYNTHESIZE(int, _attack, Attack);						//������
	CC_SYNTHESIZE(int, _mpConsumption, MpConsume);				//���ι�����������
	CC_SYNTHESIZE(int, _attackMode, Mode);						//����ģʽ(Զ��Ϊ0����սΪ1)

public:
//by lzy
	//static Weapon* create(const std::string& filename);
	//virtual bool init(const std::string& filename);

	void hide();												//���ص�ǰ��ʹ�õ�����
	void show();												//�л�����ʱʹ��
	void trackTouch();											//ʹ����ָ������ָ��һ��
	virtual void fire(Scene* _currentScene, const Vec2& pos);	//������
};
#endif // !__Weapon_H__
