#pragma once
#ifndef IMG_H
#define IMG_H
#include<SFML/Graphics.hpp>
#include<SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include<string>
#include<windows.h>
#include<cmath>
#include<tchar.h>
using namespace sf;
using namespace std;
class img
{
private: // спецификатор доступа private
    string path; int x; int y;
    Image _base_image;
    Texture _base_texture;
    Sprite _base_sprite;
    sf::Image screenShot;
public: // спецификатор доступа public

    Sprite create(string path, int x, int y);
    Sprite GetFullScreenShot();
    Sprite GetScreenShot(int x1 = 0, int y1 = 0, int width = GetDeviceCaps(GetDC(nullptr), HORZRES), int height = GetDeviceCaps(GetDC(nullptr), VERTRES));
    
};
#endif

