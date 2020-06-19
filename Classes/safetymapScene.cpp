
#include "audio.h"
#include "safetymapScene.h"
#include "SimpleMoveController.h"
#include "Controller.h"

#include "Player.h"

USING_NS_CC;

Scene* safetymap::createScene()
{
	return safetymap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool safetymap::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//������ͼ����


	/*play game music*/
	audio_home->stopBackgroundMusic();
	audio_game->playBackgroundMusic("game_music.mp3", true);

	/*auto tryab = Sprite::create("reservation.png");
	tryab->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(tryab, 5);*/

	std::string floor_layer_file = "myfirstmap2.tmx";//��ͼ�ļ�
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

	
	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("objects");//���ض����
	//��������������
	ValueMap player_point_map = objGroup->getObject("PlayerPoint");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//�����������
	mplayer->setPosition(Point(playerX,playerY));

	


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




	_tiledmap->addChild(mplayer,2);

	this->addChild(_tiledmap);


	
	return true;
}


