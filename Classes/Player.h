#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "Weapon.h"
#include "Bullet.h"

USING_NS_CC;


class Player :public Entity {
//by lzy	
	CC_SYNTHESIZE(int, _MP, MP);		
	CC_SYNTHESIZE(int, _AC, AC);
	CC_SYNTHESIZE(Vec2, _weaponPosition, WpPos);				//�����̶��������ϵ����λ��,Ĭ��ֵΪplayer������
	CC_SYNTHESIZE(Weapon*, _currentWeapon, CurrentWeapon);
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();

	//����ģ��
	bool bindSprite(Sprite* sprite);							//�󶨾������
	bool bindWeapon(Weapon* Weapon);							//������
	virtual void die();											//��ɫ������ɾ����ɫ�����ذ�ȫ��ͼ
	virtual void takeDamage(int damage);						//�ܻ��ж�������Ѫ
	void attack(Scene* currentScene, const Vec2& pos);			//��������
	void rotateWeapon(const Vec2& pos);							//�������湥������
	virtual void switchWeapon();								//�ӿڣ��л���������ɫ��ͬ�л�������Ч����ͬ
	void pickWeapon();											//�ӿڣ�ʰȡ����
	virtual void skill();										//����


	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);
private:
	Weapon* m_weapon;											//Player��ǰʹ�õ�����
	Vector<Weapon*> m_weaponArr;								//PlayerЯ������������
	TMXTiledMap* m_map;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);
};

#endif
#pragma once