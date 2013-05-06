
#include <vector>

#include "SFML/Graphics.hpp"

class SATCollision
{
public:
	/** Returns a vector of four elements representing the four points of a rectangle */
	static std::vector<sf::Vector2f> GetTransformedRect(const sf::Transformable& transformable, const sf::FloatRect& rect);
	/** Returns true if the two rectangles are colliding, false otherwise. */
	static bool IsColliding(const std::vector<sf::Vector2f>& b1, const std::vector<sf::Vector2f>& b2);

	static void TestCollision();

private:
	/** Returns the projection of a point onto an axis. */
	static sf::Vector2f Project(const sf::Vector2f& point, const sf::Vector2f& axis);
};