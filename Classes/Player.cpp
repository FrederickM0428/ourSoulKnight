#include "Player.h"

Player::Player()
{
	_HP = 5;
	_MP = 100;
	_AC = 5;

}

Player::~Player() {

}
bool Player::init()
{
	return true;
}

bool Player::bindWeapon(Weapon* weapon) {
	this->m_weapon = weapon;
	if (m_weapon == nullptr)
	{
		printf("m_weapon in this player is nullptr, check wether the file used to create the weapon in right dictionary.");
		return false;
	}
	else
	{
		this->addChild(m_weapon);

		Size size = m_sprite->getContentSize();
;
		m_weapon->setPosition(Point(size.width*0.5f, size.height*0.5f));

		return true;
	}
}

void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)
		return;
	Layer* parent = (Layer*)getParent();


	Size mapTiledNum = m_map->getMapSize();


	Size tiledSize = m_map->getTileSize();


	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);


	auto visibleSize = Director::getInstance()->getVisibleSize();


	Point spritePos = getPosition();

	float x = std::max(spritePos.x,visibleSize.width/2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	
	Point desPos = Point(x, y);

	
	Point centPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centPos - desPos;

	parent->setPosition(viewPos);

}

void Player::set_tag_position(int x, int y)
{

	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x+spriteSize.width/2, y);
	Point dstPos_y = Point(x + spriteSize.width / 2, y - spriteSize.height / 2);

	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	Point tiledPos_right = tileCoordForPosition(Point(dstPos.x + spriteSize.width / 2, dstPos.y));
	Point tiledPos_bottom = tileCoordForPosition(Point(dstPos.x, dstPos.y- spriteSize.height / 2));

	int tileGid = meta->getTileGIDAt(tiledPos);
	int tiledGid_right = meta->getTileGIDAt(tiledPos_right); 
	int tiledGid_bottom = meta->getTileGIDAt(tiledPos_bottom);
	//int tileGid = meta->getTileGIDAt(Point(16,12));
	if (tileGid != 0)
	{
		Value properties = m_map->getPropertiesForGID(tileGid);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
		{
			return;
		}
	}
	if(tiledGid_right != 0)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid_right);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
			return;
	}
	if (tiledGid_bottom != 0)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid_bottom);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
			return;
	}
	Entity::set_tag_position(x, y);

	setViewPointByPlayer();
}

void Player::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;

	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}

Point Player::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	
	int x = (pos.x*1.8)/ tiledSize.width;

	int y = (2560-pos.y*1.8) / tiledSize.height;

	if (x > 0)
		x--;
	if (y > 0)
		y-=0;

	return Point(x, y);
}