
#include "SATCollision.h"
#include "Utility.h"

std::vector<sf::Vector2f> SATCollision::GetTransformedRect(
	const sf::Transformable& transformable, const sf::FloatRect& rect)
{
	std::vector<sf::Vector2f> points(4);
	points[0] = sf::Vector2f(rect.left, rect.top);
	points[1] = sf::Vector2f(rect.left+rect.width, rect.top);
	points[2] = sf::Vector2f(rect.left, rect.top+rect.height);
	points[3] = sf::Vector2f(rect.left+rect.width, rect.top+rect.height);

	points[0] = transformable.getTransform().transformPoint(points[0]);
	points[1] = transformable.getTransform().transformPoint(points[1]);
	points[2] = transformable.getTransform().transformPoint(points[2]);
	points[3] = transformable.getTransform().transformPoint(points[3]);

	return points;
}

bool SATCollision::IsColliding(const std::vector<sf::Vector2f>& b1, const std::vector<sf::Vector2f>& b2)
{
	std::vector<sf::Vector2f> axes(4);
	axes[0] = b1[1] - b1[0];
	axes[1] = b1[2] - b1[0];
	axes[2] = b2[1] - b2[0];
	axes[3] = b2[2] - b2[0];

	for(unsigned int axis = 0; axis < axes.size(); axis++) {
		float maxb1 = -FLT_MAX, minb1 = FLT_MAX;
		float maxb2 = -FLT_MAX, minb2 = FLT_MAX;

		for(unsigned int i = 0; i < b1.size(); i++) {
			float projection = dot(Project(b1[i], axes[axis]), axes[axis]);
			maxb1 = std::max(maxb1, projection);
			minb1 = std::min(minb1, projection);
		}
		for(unsigned int i = 0; i < b2.size(); i++) {
			float projection = dot(Project(b2[i], axes[axis]), axes[axis]);
			maxb2 = std::max(maxb2, projection);
			minb2 = std::min(minb2, projection);
		}

		if((minb1 > maxb2 && minb1 > minb2) || (minb2 > maxb1 && minb2 > minb1)) {
			return false;
		}
	}

	return true;
}

sf::Vector2f SATCollision::Project(const sf::Vector2f& point, const sf::Vector2f& axis)
{
	float coefficient = (point.x * axis.x + point.y * axis.y) / (axis.x*axis.x + axis.y*axis.y);
	return sf::Vector2f(coefficient*axis.x, coefficient*axis.y);
}

void SATCollision::TestCollision()
{
	const int winWidth = 800;
	const int winHeight = 600;

	initRandom();

	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Test");

	sf::RectangleShape rect1(sf::Vector2f(20, 100));
	rect1.setFillColor(sf::Color(0, 255, 0, 255));
	rect1.setOrigin(10, 10);
	rect1.setPosition(300, 400);
	sf::RectangleShape rect2(sf::Vector2f(50, 50));
	rect2.setFillColor(sf::Color(255, 0, 0, 255));
	rect2.setOrigin(rect2.getSize()/2.0f);
	rect2.setPosition(355, 400);

	bool rotLeft = false;
	bool rotRight = false;

    while(true){
		sf::Event anEvent;

		while(window.pollEvent(anEvent)) {
			if(anEvent.type == sf::Event::KeyPressed) {
				switch(anEvent.key.code) {
				case sf::Keyboard::A :
					rotLeft = true;
					break;
				case sf::Keyboard::D :
					rotRight = true;
					break;
				}
			} else if(anEvent.type == sf::Event::KeyReleased) {
				switch(anEvent.key.code) {
				case sf::Keyboard::A :
					rotLeft = false;
					break;
				case sf::Keyboard::D :
					rotRight = false;
					break;
				}
			}
		}

		if(rotLeft) {
			rect1.setRotation(rect1.getRotation()-1.0f);
		}
		if(rotRight) {
			rect1.setRotation(rect1.getRotation()+1.0f);
		}

		sf::FloatRect bbox1 = rect1.getLocalBounds();
		sf::FloatRect bbox2 = rect2.getLocalBounds();
		std::vector<sf::Vector2f> rect1pts = GetTransformedRect(rect1, bbox1);
		std::vector<sf::Vector2f> rect2pts = GetTransformedRect(rect2, bbox2);
		bool collide = IsColliding(rect1pts, rect2pts);
		printf("%s\n", (collide?"colliding":"not colliding"));

		sf::CircleShape point(3.0f);
		point.setOrigin(point.getRadius()/2.0f, point.getRadius()/2.0f);
		window.clear();
		window.draw(rect1);
		window.draw(rect2);

		for(unsigned int i = 0; i < rect1pts.size(); i++) {
			point.setPosition(rect1pts[i]);
			window.draw(point);
		}
		for(unsigned int i = 0; i < rect2pts.size(); i++) {
			point.setPosition(rect2pts[i]);
			window.draw(point);
		}
		window.display();

		sf::sleep(sf::seconds(0.005f));
    }
}