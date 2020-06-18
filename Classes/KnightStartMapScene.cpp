#include"KnightStartMapScene.h"
#include"Player.h"
#include "SimpleMoveController.h"
#include"safetymapScene.h"
#include"setupScene.h"
USING_NS_CC;

Scene* KnightStartMap::createScene()
{
	return KnightStartMap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool KnightStartMap::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	std::string floor_layer_file = "safetymap.tmx";//��ͼ�ļ�
	_tiledmap = TMXTiledMap::create(floor_layer_file);
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2::ZERO);



	//���player
	//auto pinfo = AutoPolygon::generatePolygon("player.png");
	Sprite* player_sprite = Sprite::create("turn right 1.png");
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);

	mplayer->run();
	mplayer->setTiledMap(_tiledmap);


	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("objects_knight");//���ض����
	//��������������
	ValueMap player_point_map = objGroup->getObject("knight");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//�����������
	mplayer->setPosition(Point(playerX, playerY));




	//������Ҽ��ƶ�������
	SimpleMoveController* simple_move_controller = SimpleMoveController::create();

	//�����ƶ��ٶ�
	simple_move_controller->set_ixspeed(0);
	simple_move_controller->set_iyspeed(0);

	//����������ӵ���������Upadate������
	this->addChild(simple_move_controller);
	//���ÿ���������������
	mplayer->set_controller(simple_move_controller);
	simple_move_controller->bind_sprite(player_sprite);//Bind player

	auto x = mplayer->getPositionX();
	auto y = mplayer->getPositionY();
	int x1 = (x*1.8) / 32;
	int y1 = (1920 - 1.8*y) / 32;
	if (x1 <= 21 && x1 >= 18 && y == 7)
	{
		
		startgame();
	}


	_tiledmap->addChild(mplayer, 10);

	this->addChild(_tiledmap);


	return true;
}
void KnightStartMap::startgame()
{
	Director::getInstance()->pushScene(safetymap::createScene());
	
}

