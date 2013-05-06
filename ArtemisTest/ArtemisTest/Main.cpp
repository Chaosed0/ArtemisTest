
#include "World.h"
#include "Entity.h"
#include "SystemManager.h"

#include <SFML/Graphics.hpp>

#include "MovementSystem.h"
#include "AngularSystem.h"
#include "RenderSystem.h"
#include "RenderBoxSystem.h"
#include "PlayerInputSystem.h"
#include "BeamSystem.h"
#include "Utility.h"
#include "CollisionSystem.h"
#include "SATCollision.h"

#include "EntityFactory.h"

int main(int argc, char **argv)
{
	/*SATCollision::TestCollision();
	return 0;*/

	const int winWidth = 800;
	const int winHeight = 600;

	initRandom();

	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Test");
	sf::Clock deltaTimer;

	sf::Time frameTime = sf::seconds(1.0f/60.0f);

	deltaTimer.restart();

    artemis::World world;
    artemis::SystemManager * sm = world.getSystemManager();
    MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());
	AngularSystem * angularsys = (AngularSystem*)sm->setSystem(new AngularSystem());
    PlayerInputSystem * inputsys = (PlayerInputSystem*)sm->setSystem(new PlayerInputSystem());
	BeamSystem* beamsys = (BeamSystem*)sm->setSystem(new BeamSystem());
	RenderSystem * rendersys = (RenderSystem*)sm->setSystem(new RenderSystem(window));
	//RenderBoxSystem * renderboxsys = (RenderBoxSystem*)sm->setSystem(new RenderBoxSystem(window));
	CollisionSystem * collisionsys = (CollisionSystem*)sm->setSystem(new CollisionSystem());
    artemis::EntityManager * em = world.getEntityManager();

    sm->initializeAll();

	EntityFactory::CreatePlayer(world, sf::Vector2f(0.0f, 0.0f));

	bool running = true;

    while(running){
        world.loopStart();
        world.setDelta(deltaTimer.getElapsedTime().asSeconds());
		deltaTimer.restart();

		inputsys->SetMouse(sf::Mouse::getPosition(window));
		beamsys->SetMouse(sf::Mouse::getPosition(window));
		sf::Event anEvent;
		while(window.pollEvent(anEvent)) {
			if(anEvent.type == sf::Event::KeyPressed) {
				inputsys->KeyDown(anEvent.key.code);
			} else if(anEvent.type == sf::Event::KeyReleased) {
				inputsys->KeyRelease(anEvent.key.code);
			} else if(anEvent.type == sf::Event::MouseButtonPressed) {
				inputsys->MousePress(anEvent.mouseButton.button);
			} else if(anEvent.type == sf::Event::MouseButtonReleased) {
				inputsys->MouseRelease(anEvent.mouseButton.button);
			} else if(anEvent.type == sf::Event::Closed) {
				running = false;
			}
		}

		inputsys->process();
        movementsys->process();
		angularsys->process();
		beamsys->process();
		collisionsys->process();

		window.clear();
		rendersys->process();
		//renderboxsys->process();
		window.display();

		sf::Time timePassed = deltaTimer.getElapsedTime();
		if(timePassed < frameTime) {
			sf::sleep(frameTime - timePassed);
		}
    }

    return 0;
}
