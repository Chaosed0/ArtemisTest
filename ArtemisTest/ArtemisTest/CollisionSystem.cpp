
#include "SATCollision.h"

#include "CollisionSystem.h"
#include "Entity.h"
#include "TransformableComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "AnimManager.h"
#include "Constants.h"
#include "Utility.h"

CollisionSystem::CollisionSystem()
{
	addComponentType<TransformableComponent>();
	addComponentType<CollisionComponent>();
}

void CollisionSystem::initialize()
{
	transformableMapper.init(*world);
	collisionMapper.init(*world);

	class BeamEnemyHandler : public CollisionHandler {
	public:
		BeamEnemyHandler(CollisionSystem& collisionSystem) :
			CollisionHandler(collisionSystem) ,
			damagePerSec(500.0f) ,
			maxShakeIntensity(5.0f)
		{ }
		virtual void HandleCollision(artemis::Entity* a, artemis::Entity* b) {
			float damage = damagePerSec * collisionSystem.world->getDelta();
			float& health = b->getComponent<HealthComponent>()->health;
			health -= damage;
			printf("%g\n", health);
			float shakeIntensity = (1-health/100) * maxShakeIntensity;
			b->getComponent<TransformableComponent>()->transformable->setPosition(
				b->getComponent<TransformableComponent>()->transformable->getPosition() +
				sf::Vector2f(getRandom(-shakeIntensity, shakeIntensity),
					getRandom(-shakeIntensity, shakeIntensity)));
		}
		float damagePerSec;
		float maxShakeIntensity;
	};

	collisionGroups.push_back(std::move(CollisionSystem::CollisionGroup(
		world->getGroupManager()->getEntities(constants::beamGroup),
		world->getGroupManager()->getEntities(constants::enemyGroup),
		new BeamEnemyHandler(*this), *this))
	);
}

void CollisionSystem::processEntities(artemis::ImmutableBag<artemis::Entity*>& entities)
{
	for(unsigned int i = 0; i < collisionGroups.size(); i++) {
		collisionGroups[i].CheckForCollisions();
	}
}

bool CollisionSystem::checkProcessing()
{
	return true;
}

CollisionSystem::CollisionHandler::CollisionHandler(CollisionSystem& collisionSystem) :
	collisionSystem(collisionSystem)
{ }

CollisionSystem::CollisionGroup::CollisionGroup(artemis::ImmutableBag<artemis::Entity*>* entityGroup1,
		artemis::ImmutableBag<artemis::Entity*>* entityGroup2, CollisionHandler* handler,
		CollisionSystem& collisionSystem) :
	handler(handler) ,
	entityGroup1(entityGroup1) ,
	entityGroup2(entityGroup2) ,
	collisionSystem(collisionSystem)
{
}

void CollisionSystem::CollisionGroup::CheckForCollisions() {
	for(int a = 0; entityGroup1->getCount() > a; a++) {
		artemis::Entity* entity1 = entityGroup1->get(a);
		if(entity1->getComponent<CollisionComponent>()->isCollidable) {
			for(int b = 0; entityGroup2->getCount() > b; b++) {
				artemis::Entity* entity2 = entityGroup2->get(b);
				if(entity2->getComponent<CollisionComponent>()->isCollidable &&
						CollisionExists(entity1, entity2)) {
					handler->HandleCollision(entity1, entity2);
				}
			}
		}
	}
}

bool CollisionSystem::CollisionGroup::CollisionExists(artemis::Entity* entity1, artemis::Entity* entity2)
{
	return SATCollision::IsColliding(
		SATCollision::GetTransformedRect(*entity1->getComponent<TransformableComponent>()->transformable,
			entity1->getComponent<CollisionComponent>()->collisionRect),
		SATCollision::GetTransformedRect(*entity2->getComponent<TransformableComponent>()->transformable,
			entity2->getComponent<CollisionComponent>()->collisionRect)
	);
}