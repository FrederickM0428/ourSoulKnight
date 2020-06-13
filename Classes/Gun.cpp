#include "Gun.h"
#include <math.h>

Gun::Gun() {
	_attack = 5;
	_attackMode = 1;
	_mpConsumption = 1;
	/*_bullet = Sprite::create("Resources/Projectile.png");
	if (_bullet = nullptr) {
		log("Failed to initialize _bullet");
	}*/
	_bulletSpeed = 1000;
	this->setAnchorPoint(Vec2(0, 0));
}
Gun::~Gun() {

}

Gun* Gun::create(const std::string& filename)
{
	Gun* sprite = new Gun;
	if (sprite && sprite->init(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Gun::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	return true;
}

void Gun::fire(Scene* currentScene,const Vec2& pos) {
	//������з���;���
	auto offset = pos - this->getPosition();
	offset.normalize();
	auto destination = offset * 2000;

	//�ӵ���ӵ�ǹ�ڵ�λ�ã���ʱ����Ϊ����ê���λ�ã����ڸ�
	auto bullet = Sprite::create("Projectile.png");
	bullet->setScale(0.5);
	bullet->setPosition(Vec2(this->getPositionX(), this->getPositionY()));
	currentScene->addChild(bullet, 3);

	//�����ӵ��Ķ���
	auto bulletMove = MoveBy::create(2.0f, destination);
	auto actionRemove = RemoveSelf::create();
	
	//��־���touch�����ꡢ������ʼ���ꡢ�ӵ����з���
	log("Touch:x=%f, y=%f", pos.x, pos.y);
	log("Weapon:x=%f, y=%f", this->getPositionX(), this->getPositionY());
	log("Bullet:x=%f, y=%f", bullet->getPositionX(), bullet->getPositionY());
	log("Direction:x=%f, y=%f", offset.x, offset.y);

	//�����ӵ�
	bullet->runAction(Sequence::create(bulletMove, actionRemove, nullptr));
}