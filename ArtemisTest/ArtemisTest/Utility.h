/**
 * \brief Collection of utility functions
 * \author Edward Lu
 * \date March 20 2013
 */

#ifndef __UTILITY_H
#define __UTILITY_H

#include <SFML/Graphics.hpp>

#include <random>

//The constant PI, in radians
#define PI 3.14159f
//Conversion factor from radians to degrees
#define TO_DEG 57.2958279f
//Conversion factor from degrees to radians
#define TO_RAD 0.0174532778f

//snprintf is c99, but Visual Studio doesn't support it
#ifdef _MSC_VER
#define snprintf sprintf_s
#endif

/** Gets the magnitude of vec */
float magnitude(const sf::Vector2f& vec);
/** Returns the dot product of a and b. */
float dot(const sf::Vector2f& a, const sf::Vector2f& b);
/** Shifts the angle to between 0 and 2*PI */
float shiftAngle(float angle);
/** Initializes the random seed engine that getRandom() uses. */
void initRandom();
/** Gets a random number in the range [0, 1]. */
float getRandom();
/** Gets a random number in the range [begin, end]. */
float getRandom(float begin, float end);
/** Checks whether the string is a valid property from GetLiteralProperty() */
bool IsValidProperty(const std::string& prop);
/** Returns -1 if val is negative, 1 if val is positive, 0 otherwise. */
int sign(float val);


#endif