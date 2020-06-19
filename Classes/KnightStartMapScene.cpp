#include"KnightStartMapScene.h"
#include"Player.h"
#include "SimpleMoveController.h"
#include"safetymapScene.h"
#include"setupScene.h"
#include"HelloWorldScene.h"
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
	this->scheduleUpdate();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::string floor_layer_file = "safetymap.tmx";//��ͼ�ļ�
	_tiledmap = TMXTiledMap::create(floor_layer_file);
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2::ZERO);

	//����player
	Sprite* player_sprite = Sprite::create("turn right 1.png");
<<<<<<< HEAD
	Player* mplayer = Player::create();
	mplayer->bindSprite(player_sprite);

=======
	mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);
	mplayer->run();
>>>>>>> bbd7442a8b0690efe4fd35c4788f1021c521395b
	mplayer->setTiledMap(_tiledmap);

	//���ض����
	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("objects_knight");

	//��������������
	ValueMap player_point_map = objGroup->getObject("knight");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//�����������
	mplayer->setPosition(Point(playerX, playerY));

<<<<<<< HEAD
=======


>>>>>>> bbd7442a8b0690efe4fd35c4788f1021c521395b
	//������Ҽ��ƶ�������
	SimpleMoveController* simple_move_controller = SimpleMoveController::create();

	//�����ƶ��ٶ�
	simple_move_controller->set_ixspeed(0);
	simple_move_controller->set_iyspeed(0);

	//�����������ӵ���������Upadate������
	this->addChild(simple_move_controller);

	//���ÿ���������������
	mplayer->set_controller(simple_move_controller);
	simple_move_controller->bind_sprite(player_sprite);


	auto knight_animate = Animation::create();
	char nameSize[30] = { 0 };
	for (int i = 1; i <= 2; i++)
	{
		sprintf(nameSize, "standing_right_%d_adjusted.png", i);
		knight_animate->addSpriteFrameWithFile(nameSize);
	}
	knight_animate->setDelayPerUnit(0.1f);//���ö���֡ʱ����
	knight_animate->setLoops(-1);
	knight_animate->setRestoreOriginalFrame(true);
	auto knight_animate_run = Animate::create(knight_animate);
	player_sprite->runAction(knight_animate_run);

<<<<<<< HEAD
	_tiledmap->addChild(mplayer, 10);
=======
	_tiledmap->addChild(mplayer,23);
>>>>>>> bbd7442a8b0690efe4fd35c4788f1021c521395b

	this->addChild(_tiledmap);
	/*add the suspend button*/
	auto suspend_button = MenuItemImage::create(
		"suspend_button.png",
		"suspend_button.png",
		CC_CALLBACK_1(KnightStartMap::menuCloseCallback, this));
	if (suspend_button == nullptr ||
		suspend_button->getContentSize().width <= 0 ||
		suspend_button->getContentSize().height <= 0)
	{
		problemLoading("'suspend_button.png' and 'suspend_button.png'");
	}
	else
	{

		suspend_button->setPosition(Vec2(visibleSize.width+ origin.x-20, visibleSize.height + origin.y-20));

<<<<<<< HEAD
=======
	}
	auto menu2 = Menu::create(suspend_button, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);//just a virtual button which is unvisible

>>>>>>> bbd7442a8b0690efe4fd35c4788f1021c521395b
	return true;
}

void KnightStartMap::menuCloseCallback(Ref* pSender)
{   
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto suspend_scene = Sprite::create("suspend_scene.png");
	suspend_scene->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+300));
	this->addChild(suspend_scene, 1);
	auto suspend_scene_moveBy = MoveBy::create(0.3, Vec2(0,-300));
	suspend_scene->runAction(suspend_scene_moveBy);

	auto suspend_start = MenuItemImage::create(
		"suspend_start.png",
		"suspend_start.png",
		CC_CALLBACK_1(KnightStartMap::start_menuCloseCallback, this));
	if (suspend_start == nullptr ||
		suspend_start->getContentSize().width <= 0 ||
		suspend_start->getContentSize().height <= 0)
	{
		problemLoading("'suspend_button.png' and 'suspend_button.png'");
	}
	else
	{

		suspend_start->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-40+300));
		auto suspend_start_moveBy = MoveBy::create(0.3, Vec2(0, -300));
		suspend_start->runAction(suspend_start_moveBy);
	}
	auto menu2 = Menu::create(suspend_start, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);//just a virtual button which is unvisible
	/*create home button*/
	auto home_button = MenuItemImage::create(
		"home_button1.png",
		"home_button2.png",
		CC_CALLBACK_1(KnightStartMap::home_menuCloseCallback, this));
	if (suspend_start == nullptr ||
		suspend_start->getContentSize().width <= 0 ||
		suspend_start->getContentSize().height <= 0)
	{
		problemLoading("'home_button1' and 'home_button2.png'");
	}
	else
	{

		home_button->setPosition(Vec2(visibleSize.width / 2-60, visibleSize.height / 2 - 40 + 300));
		auto home_button_moveBy = MoveBy::create(0.3, Vec2(0, -300));
		home_button->runAction(home_button_moveBy);
	}
	auto menu3 = Menu::create(home_button, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);//just a virtual button which is unvisible

}

void KnightStartMap::update(float dt)
{
	
	auto player_x = mplayer->getPositionX();
	auto player_y = mplayer->getPositionY();
	int x = player_x * 1.8 / 32;
	int y = (1920 - player_y * 1.8) / 32;
	if (x <= 21 && x >= 18 &&(y==7))
	{
		
		Director::getInstance()->replaceScene(safetymap::createScene());
	}
	
	//��������������
	_tiledmap->getLayer("weapon_information")->setVisible(false);
	if (x <= 15 && x >= 14 && y==50)
	{
		_tiledmap->getLayer("weapon_information")->setVisible(true);
	}

	
}

void KnightStartMap::start_menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->replaceScene(KnightStartMap::createScene());

}

void KnightStartMap::home_menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}



