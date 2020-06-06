#include "SimpleMoveController.h"
#include <map>
#include "Player.h"

bool SimpleMoveController::init()
{
	this->m_ixspeed = 0;
	this->m_iyspeed = 0;

	registeKeyBoardEvent();//ע����̿����¼�
	this->scheduleUpdate();

	return true;
}

void SimpleMoveController::update(float dt)
{
	if (m_controllerListener == NULL)
		return;
	//���̿���ʵ��
	//�����ƶ������X����ֵ
	Point pos = m_controllerListener->get_tag_position();
	pos.x += m_ixspeed;
	pos.y += m_iyspeed;
	m_controllerListener->set_tag_position(pos.x, pos.y);

}

void SimpleMoveController::set_speed(int ispeed)
{
	this->m_ixspeed = ispeed;
}

void SimpleMoveController::set_ixspeed(int ispeed)
{
	this->m_ixspeed = ispeed;
}

void SimpleMoveController::set_iyspeed(int ispeed)
{
	this->m_iyspeed = ispeed;
}

//���̿���ʵ��
void SimpleMoveController::registeKeyBoardEvent()
{


	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W://�Ϸ����;
			set_iyspeed(2);
			break;
		case EventKeyboard::KeyCode::KEY_A://�����;
			set_ixspeed(-2);
			break;
		case EventKeyboard::KeyCode::KEY_S://�ҷ����;
			set_iyspeed(-2);
			break;
		case EventKeyboard::KeyCode::KEY_D://�·����;
			set_ixspeed(2);
			break;

		}
	};

	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:
			set_iyspeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_A://�Ϸ����;
			set_ixspeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_S://�Ϸ����;
			set_iyspeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_D://�Ϸ����;
			set_ixspeed(0);
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

}

