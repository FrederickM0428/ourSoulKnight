#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "audio.h"
#include "safetymapScene.h"
#include"ShotGun.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
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
	// 鍒濆鍖朠hysics
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*add information bar*/
	auto information_bar = Sprite::create("data_bars_blank.png");
	information_bar->setPosition(Vec2(origin.x + 55, visibleSize.height - 10));
	this->addChild(information_bar, 1);

	/*add blood bar
	auto bloodLoadingBar = LoadingBar::create("blood_bar_full.png");
	bloodLoadingBar->setDirection(LoadingBar::Direction::LEFT);
	bloodLoadingBar->setPosition(Vec2(origin.x + 55, visibleSize.height - 10));
	bloodLoadingBar->setPercent(100);
	this->addChild(bloodLoadingBar,2);*/

	/*second method*/
	auto bloodEmpty = Sprite::create("blood_bar_empty.png");
	bloodEmpty->setPosition(Vec2(origin.x + 55, visibleSize.height + 5));
	this->addChild(bloodEmpty, 2);
	auto bloodFull = Sprite::create("blood_bar_full.png");
	bloodProgress = ProgressTimer::create(bloodFull);
	bloodProgress->setType(ProgressTimer::Type::BAR);//type:bar
	bloodProgress->setPosition(Vec2(origin.x + 55, visibleSize.height + 5));
	bloodProgress->setMidpoint(Point(0, 0.5));//from right to left
	bloodProgress->setBarChangeRate(Point(1, 0));
	//bloodProgress->setTag(BLOOD_BAR);//
	this->addChild(bloodProgress, 2);
	schedule(CC_SCHEDULE_SELECTOR(safetymap::scheduleBlood), 0.1f);
	/*play game music*/
	audio_home->stopBackgroundMusic();
	audio_game->playBackgroundMusic("game_music.mp3", true);

	std::string floor_layer_file = "myfirstmap2.tmx";//地图文件

	_tiledmap = TMXTiledMap::create(floor_layer_file);
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2::ZERO);

	log("map size:(%f, %f)", _tiledmap->getContentSize().width,_tiledmap->getContentSize().height);

	//娣诲姞player骞剁粦瀹氭鍣?

	Sprite* player_sprite = Sprite::create("turn right 1.png");
	Knight* mplayer = Knight::create();
	ShotGun* initialWeapon = ShotGun::create("goblin_guard_shotgun.png");
	mplayer->bindSprite(player_sprite);
	mplayer->bindWeapon(initialWeapon);
	mplayer->setTiledMap(_tiledmap);

	
	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("objects");

	ValueMap player_point_map = objGroup->getObject("PlayerPoint");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//璁剧疆鐜╁鍧愭爣
	mplayer->setPosition(Point(playerX,playerY));

	//娣诲姞涓�涓祴璇曠敤鐨刴onster
	Sprite* monster_sprite = Sprite::create("LongRemoteSoldier.png");
	RemoteSoldier* monster = RemoteSoldier::create(LONGREMOTE,this);

	monster->bindSprite(monster_sprite);
	//monster->setTiledMap(_tiledmap);

	TMXObjectGroup* bulletGroup = _tiledmap->getObjectGroup("bullet");

	ValueMap monster_point_map = bulletGroup->getObject("bullet1");
	float monsterX = monster_point_map.at("x").asFloat();
	float monsterY = monster_point_map.at("y").asFloat();
	monster->setPosition(Point(monsterX, monsterY));
	
	//鍒涘缓鎬墿
	RemoteSoldierManager* remoteSoldierManager = RemoteSoldierManager::create(this, mplayer, _tiledmap);
	this->m_remoteSoldierManager = remoteSoldierManager;
	_tiledmap->addChild(remoteSoldierManager, 4);

	//鍒涘缓鐜╁绠�鍗曠Щ鍔ㄦ帶鍒跺櫒
	SimpleMoveController* simple_move_controller = SimpleMoveController::create();

	//璁剧疆绉诲姩閫熷害
	simple_move_controller->set_ixspeed(0);
	simple_move_controller->set_iyspeed(0);

	//灏嗘帶鍒跺櫒娣诲姞鍒板満鏅腑璁︰padate琚皟鐢?
	this->addChild(simple_move_controller);

	//璁剧疆鎺у埗鍣ㄥ埌涓昏韬笂
	mplayer->set_controller(simple_move_controller);
	simple_move_controller->bind_sprite(player_sprite);//Bind player
  
	//璁剧疆纰版挒鎺╃爜
	this->m_player = mplayer;
	this->m_monster = monster;

	m_monster->getPhysicsBody()->setCategoryBitmask(0x02);
	m_monster->getPhysicsBody()->setContactTestBitmask(0x04);
	

	this->addChild(_tiledmap);

	_tiledmap->addChild(mplayer,2);
	_tiledmap->addChild(monster, 2);
	
	//this->addChild(monster,2);
	//this->addChild(mplayer,2);
	log("player pos0:(%f, %f)", playerX, playerY);
	log("monster pos0:(%f, %f)", monsterX, monsterY);

	
	//鍒涘缓EventListener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(safetymap::onTouchBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	//鍒涘缓contactListener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(safetymap::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool safetymap::onTouchBegin(Touch* touch, Event* event) {
	auto target = this->m_monster;
	m_player->resetWeaponPos();
	m_player->attack(this, Vec2(m_player->getPositionX() + 1, m_player->getPositionY()));
	/*if(!target->getalreadyDead())
	{
		Vec2 pos = target->getPosition();
		m_player->rotateWeapon(pos);
		m_player->attack(this,pos);
	}
	else {
		m_player->resetWeaponPos();
		m_player->attack(this, Vec2(m_player->getPositionX() + 1, m_player->getPositionY()));
	}*/
	return true;
}

bool safetymap::onContactBegin(PhysicsContact& contact) {

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() > 0)
		{
			if (nodeB->getTag() == -1)
			{
				this->m_player->takeDamage(nodeA->getTag());
			}
			else if (nodeB->getTag() == -2)
			{
				//this->m_monster->takeDamage(nodeA->getTag());
				//找出是哪个怪物和子弹发生了碰撞
				for (auto Soldier : this->m_remoteSoldierManager->getSoldierArr())
				{
					if (nodeB->getMonsterID() == Soldier->getMonsterID())
					{
						Soldier->takeDamage(nodeA->getTag());
					}
				}
			}
			nodeA->removeFromParentAndCleanup(true);
		}

		//和上面的代码块是镜像的，因为nodeA和nodeB不知道哪一个是子弹
		else if (nodeB->getTag() > 0)
		{
			if (nodeA->getTag() == -1)
			{
				this->m_player->takeDamage(nodeB->getTag());
			}
			else if (nodeA->getTag() == -2)
			{
				//this->m_monster->takeDamage(nodeB->getTag());
				for (auto Soldier : this->m_remoteSoldierManager->getSoldierArr())
				{
					if (nodeA->getMonsterID() == Soldier->getMonsterID())
					{
						Soldier->takeDamage(nodeB->getTag());
					}
				}
			}
			nodeB->removeFromParentAndCleanup(true);
		}
	}
	
	return true;
}

/*void safetymap::add_player(TMXTiledMap* map)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//锟斤拷锟斤拷一锟斤拷锟斤拷
	Sprite* player_sprite = Sprite::create("player.png");
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);
	mplayer->run();

    //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
	mplayer->setPosition(Vec2(100, visibleSize.height / 2));

	_tiledmap->addChild(mplayer);
}*/

void safetymap::scheduleBlood(float delta)
{
	bloodProgress->setPercentage(100);
	if (bloodProgress->getPercentage() < 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(safetymap::scheduleBlood));
	}
}


