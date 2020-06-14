#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "Weapon.h"
#include "Bullet.h"

USING_NS_CC;


class Player :public Entity {
//by lzy
	CC_SYNTHESIZE(int, _HP, HP);		
	CC_SYNTHESIZE(int, _MP, MP);		
	CC_SYNTHESIZE(int, _AC, AC);
	CC_SYNTHESIZE(Vec2, _weaponPosition, WpPos);				//�����̶��������ϵ����λ��,Ĭ��ֵΪplayer������
	CC_SYNTHESIZE(Weapon*, _currentWeapon, CurrentWeapon);
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
//by lzy
	bool bindSprite(Sprite* sprite);							//ͬʱ���������ײģ��
	bool bindWeapon(Weapon* Weapon);							//������

	void attack(Scene* currentScene, const Vec2& pos);			//���ù�������,����Ҫ��������Ĺ���
	virtual void switchWeapon();								//�ӿڣ��л���������ɫ��ͬ�л�������Ч����ͬ
	void pickWeapon();											//�ӿڣ�ʰȡ����
	virtual void skill();										//����
//by lq
	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);
private:
//by lzy
	Weapon* m_weapon;											//Player��ǰʹ�õ�����
	Vector<Weapon*> m_weaponArr;								//PlayerЯ������������
//by lq
	TMXTiledMap* m_map;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);
};

#endif