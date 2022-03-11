#include "draw.h"

RectangleShape draw::fillRectangle(int x, int y, int width, int height, Color color) {
    RectangleShape rectangle(Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(color);
    return rectangle;
}


RectangleShape draw::drawRectangle(int x, int y, int width, int height, Color borderColor, int borderRadius) {
    RectangleShape rectangle(Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(borderRadius);
    rectangle.setOutlineColor(borderColor);
    return rectangle;
}

