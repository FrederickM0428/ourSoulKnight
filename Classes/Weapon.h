#ifndef __Weapon_H__
#define __Weapon_H__

#include "cocos2d.h"
USING_NS_CC;

class Weapon :public Sprite {
	CC_SYNTHESIZE(int, _attack, Attack);						//������
	CC_SYNTHESIZE(int, _mpConsumption, MpConsume);				//���ι�����������
	CC_SYNTHESIZE(int, _attackMode, Mode);						//����ģʽ(Զ��Ϊ0����սΪ1)
	CC_SYNTHESIZE(int, _bulletType, BulletType);				//����ʹ�õ��ӵ����ͣ���ս��û��

public:
//by lzy
	//static Weapon* create(const std::string& filename);
	//virtual bool init(const std::string& filename);
	virtual void fire(Scene* currentScene,const Vec2& pos) ;
	void hide();												//���ص�ǰ��ʹ�õ�����
	void show();												//�л�����ʱʹ��
	void trackTouch();											//ʹ����ָ������ָ��һ��
};
#endif // !__Weapon_H__
