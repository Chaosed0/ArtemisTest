
#include "BeamSystem.h"

#include "Entity.h"
#include "BeamComponent.h"
#include "TransformableComponent.h"
#include "AngularVelComponent.h"
#include "CollisionComponent.h"
#include "SoundManager.h"
#include "Constants.h"
#include "Utility.h"

const sf::Time BeamSystem::windupTime = sf::seconds(0.5f);
const sf::Time BeamSystem::sustainTime = sf::seconds(0.75f);
const float BeamSystem::angularVelocity = PI/4.0f;

BeamSystem::BeamSystem() {
	addComponentType<BeamComponent>();
	addComponentType<AngularVelComponent>();
	addComponentType<CollisionComponent>();

	SoundManager::PrecacheSound("assets/sound/windup.ogg");
	SoundManager::PrecacheSound("assets/sound/continuous_laser.ogg");
};

void BeamSystem::initialize() {
	beamMapper.init(*world);
	angularVelMapper.init(*world);
	collisionMapper.init(*world);
};

void BeamSystem::processEntity(artemis::Entity &e) {
	std::shared_ptr<sf::RectangleShape> rect = beamMapper.get(e)->rect;
	sf::Time& beamTimer = beamMapper.get(e)->timer;
	sf::Vector2f beamSize = beamMapper.get(e)->beamSize;

	//printf("Size: %g, %g\n", XFunction(beamSize.x, beamTimer), YFunction(beamSize.y, beamTimer));

	if(!beamMapper.get(e)->isFired && beamTimer > windupTime) {
		beamMapper.get(e)->isFired = true;
	}

	if(!beamMapper.get(e)->isFired && !beamMapper.get(e)->hasPlayedSound) {
		beamMapper.get(e)->curSound = SoundManager::PlaySound("assets/sound/windup.ogg", false);
		beamMapper.get(e)->hasPlayedSound = true;
	} else if(beamTimer > sustainTime && beamMapper.get(e)->hasPlayedSound) {
		beamMapper.get(e)->curSound = SoundManager::PlaySound("assets/sound/continuous_laser.ogg", true);
		beamMapper.get(e)->hasPlayedSound = false;
	}


	//There should only ever be one player
	artemis::Entity* player = world->getGroupManager()->getEntities(constants::playerGroup)->get(0);
	sf::Vector2f playerPos = player->getComponent<TransformableComponent>()->transformable->getPosition();
	rect->setPosition(playerPos);
	rect->setFillColor(sf::Color(getRandom(200, 255), getRandom(150, 255), getRandom(50, 200)));
	rect->setSize(sf::Vector2f(XFunction(beamSize.x, beamTimer),
		YFunction(beamSize.y, beamTimer)));
	rect->setOrigin(0.0f, rect->getSize().y/2.0f);

	float mouseAngle = atan2f(mousePos.y - playerPos.y, mousePos.x - playerPos.x);
	float curAngle = shiftAngle(rect->getRotation()*TO_RAD);
	int relSign;
	if(fabs(mouseAngle+2*PI-curAngle) < fabs(mouseAngle-2*PI-curAngle)) {
		if(fabs(mouseAngle+2*PI-curAngle) < fabs(mouseAngle-curAngle)) {
			relSign = sign(mouseAngle+2*PI-curAngle);
		} else {
			relSign = sign(mouseAngle-curAngle);
		}
	} else {
		if(fabs(mouseAngle-2*PI-curAngle) < fabs(mouseAngle-curAngle)) {
			relSign = sign(mouseAngle-2*PI-curAngle);
		} else {
			relSign = sign(mouseAngle-curAngle);
		}
	}
	angularVelMapper.get(e)->angularVelocity = relSign*angularVelocity;

	collisionMapper.get(e)->collisionRect = rect->getLocalBounds();
	//printf("%g, %g, %s\n", mouseAngle, curAngle, (relSign)>0?"down":"up");
	beamTimer += sf::seconds(world->getDelta());
};

float BeamSystem::XFunction(float beamHeight, sf::Time time) {
	if(time < windupTime) {
		return 40.0f/(time.asSeconds()*20+1);
	} else if(time < sustainTime) {
		return beamHeight*(1.0f - (sustainTime-time).asMicroseconds()
			/(float)(sustainTime-windupTime).asMicroseconds());
	} else {
		return beamHeight+getRandom(-sqrt(beamHeight), sqrt(beamHeight));
	}
}

float BeamSystem::YFunction(float beamWidth, sf::Time time) {
	if(time < windupTime) {
		return beamWidth*40*(time.asSeconds()*time.asSeconds());
	} else if(time < sustainTime) {
		return beamWidth;
	} else {
		return beamWidth+getRandom(-sqrt(beamWidth), sqrt(beamWidth));
	}
}

void BeamSystem::SetMouse(sf::Vector2i mousePos) {
	this->mousePos = mousePos;
}