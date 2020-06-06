#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "Weapon.h"
USING_NS_CC;


class Player :public Entity {
	CC_SYNTHESIZE(int, _HP, HP);
	CC_SYNTHESIZE(int, _MP, MP);
	CC_SYNTHESIZE(int, _AC, AC);
public:
//by lzy
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
	bool bindWeapon(Weapon* Weapon);//������
//by lq
	void run();
	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);

private:
//by lzy
	Weapon* m_weapon;				//Player��ǰʹ�õ�����
	Vector<Weapon*> m_weaponArr;	//PlayerЯ������������
//by lq
	TMXTiledMap* m_map;
	TMXLayer* meta;//�����ײ�ĵ�ͼ��?
	/*���������ת��Ϊ��ͼ�������*/
	Point tileCoordForPosition(Point pos);
};

#endif