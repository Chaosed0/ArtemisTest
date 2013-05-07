#include "EntityFactory.h"

#include "VelocityComponent.h"
#include "TransformableComponent.h"
#include "PlayerComponent.h"
#include "BeamComponent.h"
#include "AngularVelComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "AnimationComponent.h"
#include "ExpiresComponent.h"
#include "Utility.h"
#include "Constants.h"

artemis::Entity& EntityFactory::CreatePlayer(artemis::World& world, const sf::Vector2f& pos)
{
	artemis::Entity & player = world.getEntityManager()->create();
	sf::Texture& playerTexture = TextureManager::GetTexture("assets/img/megamanpic.png");
	std::shared_ptr<sf::Sprite> playerSprite(new sf::Sprite(playerTexture));
	playerSprite->setOrigin(playerTexture.getSize().x/2.0f, playerTexture.getSize().y/2.0f);

	player.addComponent(new VelocityComponent(0.0f,0.0f));
	player.addComponent(new HealthComponent(100));
	player.addComponent(new RenderComponent(playerSprite));
	player.addComponent(new TransformableComponent(playerSprite));
	player.addComponent(new CollisionComponent(playerSprite->getLocalBounds(), true));
	player.addComponent(new PlayerComponent(sf::Keyboard::W, sf::Keyboard::S,
		sf::Keyboard::A, sf::Keyboard::D, sf::Mouse::Left));
	player.refresh();

	world.getGroupManager()->set(constants::playerGroup, player);

	return player;
}

artemis::Entity& EntityFactory::CreateBeam(artemis::World& world, const sf::Vector2f& pos,
										   const sf::Vector2i& pointPos)
{
	artemis::Entity& beam = world.getEntityManager()->create();
	std::shared_ptr<sf::RectangleShape> rectShape(new sf::RectangleShape());
	rectShape->setPosition(pos);
	float angle = atan2f(pointPos.y - pos.y, pointPos.x - pos.x)*TO_DEG; 
	rectShape->setRotation(angle);

	beam.addComponent(new RenderComponent(rectShape));
	beam.addComponent(new TransformableComponent(rectShape));
	beam.addComponent(new BeamComponent(rectShape, sf::Vector2f(800,10)));
	beam.addComponent(new CollisionComponent(rectShape->getLocalBounds(), false));
	beam.addComponent(new AngularVelComponent(0.0f));
	beam.refresh();

	world.getGroupManager()->set(constants::beamGroup, beam);

	return beam;
}

artemis::Entity& EntityFactory::CreateStaticTest(artemis::World& world, const sf::Vector2f& pos)
{
	artemis::Entity& test = world.getEntityManager()->create();
	sf::Texture& testTexture = TextureManager::GetTexture("assets/img/what.png");
	std::shared_ptr<sf::Sprite> whatSprite(new sf::Sprite(testTexture));
	whatSprite->setPosition(pos);

	test.addComponent(new HealthComponent(100));
	test.addComponent(new RenderComponent(whatSprite));
	test.addComponent(new TransformableComponent(whatSprite));
	test.addComponent(new CollisionComponent(whatSprite->getLocalBounds(), true));
	test.refresh();

	world.getGroupManager()->set(constants::enemyGroup, test);

	return test;
}

artemis::Entity& EntityFactory::CreateExplosion(artemis::World& world, const sf::Vector2f& pos)
{
	artemis::Entity& explosion = world.getEntityManager()->create();
	sf::Texture& explosionTexture = TextureManager::GetTexture("assets/img/explosion.png");
	std::shared_ptr<sf::Sprite> explosionSprite(new sf::Sprite(explosionTexture));
	explosionSprite->setPosition(pos);

	explosion.addComponent(new RenderComponent(explosionSprite));
	explosion.addComponent(new TransformableComponent(explosionSprite));
	explosion.addComponent(new AnimationComponent(sf::Vector2i(64, 64), "explosion", sf::seconds(0.02)));
	explosion.addComponent(new ExpiresComponent(sf::seconds(1.0f)));
	explosion.refresh();

	AnimManager::AddAnim(*explosion.getComponent<AnimationComponent>(), "explode", 0, 24, false);
	AnimManager::PlayAnim(*explosion.getComponent<AnimationComponent>(), "explode");

	//world.getGroupManager()->set(constants::enemyGroup, test);

	return explosion;
}