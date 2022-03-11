



#ifndef DRAW_H
#define DRAW_H
#define NOMINMAX
#include<SFML/Graphics.hpp>
#include<SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <cmath>
using namespace sf;
namespace draw {
	sf::RectangleShape fillRectangle(int x, int y, int width, int height, Color color);
	sf::RectangleShape drawRectangle(int x, int y, int width, int height, sf::Color borderColor, int borderRadius);
}
#endif
