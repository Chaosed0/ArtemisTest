
#include "PlayerInputSystem.h"
#include "TransformableComponent.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"
#include "EntityFactory.h"
#include "BeamComponent.h"
#include "Constants.h"
#include "Utility.h"
#include "SoundManager.h"

const float PlayerInputSystem::playerMoveSpeed = 200.0f;
const float PlayerInputSystem::playerSlowMoveSpeed = 100.0f;
const sf::Time PlayerInputSystem::powerDownTime = sf::seconds(1.5f);

PlayerInputSystem::PlayerInputSystem()
{
	addComponentType<VelocityComponent>();
	addComponentType<TransformableComponent>();
	addComponentType<PlayerComponent>();

	keyDown.resize(sf::Keyboard::KeyCount);
	mouseDown.resize(sf::Mouse::ButtonCount);
	beamTime = sf::Time::Zero;
	shootingBeam = false;
};

void PlayerInputSystem::initialize() {
	velocityMapper.init(*world);
	TransformableMapper.init(*world);
	playerMapper.init(*world);
};

void PlayerInputSystem::processEntity(artemis::Entity &e) {
	PlayerComponent* playerMap = playerMapper.get(e);
	sf::Vector2f playerPos = TransformableMapper.get(e)->transformable->getPosition();
	sf::Vector2f movement;

	if(keyDown[playerMap->rightKey]) {
		movement.x += playerMoveSpeed;
	}
	if(keyDown[playerMap->leftKey]) {
		movement.x -= playerMoveSpeed;
	}

	if(keyDown[playerMap->downKey]) {
		movement.y += playerMoveSpeed;
	}
	if(keyDown[playerMap->upKey]) {
		movement.y -= playerMoveSpeed;
	}

	if(mouseDown[playerMap->shootButton] && beamTime <= sf::Time::Zero && !shootingBeam) {
		artemis::Entity& beam = EntityFactory::CreateBeam(*world, playerPos, mousePt);
		beamTime = powerDownTime;
		shootingBeam = true;
	} else if(!mouseDown[playerMap->shootButton] && shootingBeam) {
		artemis::ImmutableBag<artemis::Entity*> * beamBag = 
			world->getGroupManager()->getEntities(constants::beamGroup);

		for(int i = 0; i < beamBag->getCount(); i++) {
			BeamComponent* beam = beamBag->get(i)->getComponent<BeamComponent>();
			beam->curSound->stop();
			world->deleteEntity(*beamBag->get(i));
		}

		SoundManager::PlaySound("assets/sound/powerdown.ogg",false);
		shootingBeam = false;
	}
	if(mouseDown[sf::Mouse::Right]) {
		EntityFactory::CreateStaticTest(*world, sf::Vector2f(getRandom(0, 800), getRandom(0,600)));
	}

	if(!shootingBeam && beamTime > sf::Time::Zero) {
		beamTime -= sf::seconds(world->getDelta());
	}

	if(shootingBeam && magnitude(movement) != 0) {
		movement = movement/magnitude(movement)*playerSlowMoveSpeed;
	}

	velocityMapper.get(e)->velocity = movement;

	/*sf::Vector2f pos = positionMapper.get(e)->pos;
	float angle = atan2(mousePt.y - pos.y, mousePt.x - pos.x);
	velocityMapper.get(e)->velocity = sf::Vector2f(
		playerMoveSpeed*cos(angle), playerMoveSpeed*sin(angle));*/
	//positionMapper.get(e)->pos = sf::Vector2f(mousePt.x, mousePt.y);
};

void PlayerInputSystem::SetMouse(sf::Vector2i mouse) {
	mousePt = mouse;
}

void PlayerInputSystem::KeyDown(sf::Keyboard::Key key) {
	if(key != sf::Keyboard::Unknown) {
		keyDown[key] = true;
	} else {
		fprintf(stderr, "WARNING: Received unknown key press\n");
	}
}

void PlayerInputSystem::KeyRelease(sf::Keyboard::Key key) {
	if(key != sf::Keyboard::Unknown) {
		keyDown[key] = false;
	} else {
		fprintf(stderr, "WARNING: Received unknown key release\n");
	}
}

void PlayerInputSystem::MousePress(sf::Mouse::Button button) {
	mouseDown[button] = true;
}

void PlayerInputSystem::MouseRelease(sf::Mouse::Button button) {
	mouseDown[button] = false;
}
