// screen.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


// Глобальные переменные

#include <algorithm>
#include <thread>
#define NOMINMAX

#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <string>
#include <cmath>
#include <windows.h>
#include <tchar.h>  

#include<Strsafe.h>
#include "draw.h"
#include "img.h"
using namespace std;
using namespace sf;
int THREAD_one_Flag = 0;

HWND f;
sf::Vector2i start;
sf::Vector2i pt;
Sprite result;
void    Form1() {
    RenderWindow window(sf::VideoMode::getDesktopMode(), " Scren Capture", sf::Style::None);
    SetWindowPos(window.getSystemHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(75);
    f = window.getSystemHandle();
    img a;
    Sprite ab = a.GetFullScreenShot();
    bool check = false;
    
    
    while (window.isOpen()) {
        window.clear();
        window.draw(ab);
            
        if (!check) {
            window.draw(draw::fillRectangle(0, 0, 1920, 1080, Color(0, 0, 0, 90)));
            
        }
        
        if (check) {
             pt = sf::Mouse::getPosition();
            Color color = Color(0, 0, 0, 90);
            window.draw(draw::fillRectangle(0, 0, 1920, (start.y > pt.y) ? pt.y : start.y, color));
            window.draw(draw::fillRectangle(0, (start.y > pt.y) ? pt.y : start.y, ((start.x > pt.x) ? pt.x : start.x), -((start.y > pt.y) ? pt.y : start.y) + ((start.y < pt.y) ? pt.y : start.y), color));
            window.draw(draw::fillRectangle((start.x < pt.x) ? pt.x : start.x, (start.y > pt.y) ? pt.y : start.y, 1920, -((start.y > pt.y) ? pt.y : start.y) + ((start.y < pt.y) ? pt.y : start.y), color));
            window.draw(draw::fillRectangle(0, (start.y < pt.y) ? pt.y : start.y, 1920, 1080 - ((start.y < pt.y) ? pt.y : start.y), color));
            window.draw(draw::drawRectangle((start.x > pt.x) ? pt.x : start.x, (start.y > pt.y) ? pt.y : start.y, abs(start.x - pt.x), abs(start.y - pt.y), Color(255, 255, 255), 2));
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    check = true;
                    start = sf::Mouse::getPosition();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    check = false;
                    result = a.GetScreenShot(((start.x > pt.x) ? pt.x : start.x) + 1, ((start.y > pt.y) ? pt.y : start.y) + 1, abs(pt.x - start.x) - 1, abs(pt.y - start.y) - 1);
                    
                    window.close();
                    THREAD_one_Flag =  10;
                }
            }
            if (event.type == Event::Closed) {
                window.close();
                THREAD_one_Flag =  5;
            }
        }
        
        
        window.display();
         
    }
    
}
void Form2() {
    img a;

    Sprite ab = a.GetScreenShot(((start.x > pt.x) ? pt.x : start.x) + 1, ((start.y > pt.y) ? pt.y : start.y) + 1, abs(pt.x - start.x) - 1, abs(pt.y - start.y) - 1);
    Sprite aa = ab;
    RenderWindow window(VideoMode(780,600), "ScreenShot Editor v1.0.1");
    Vector2u window_size = window.getSize();
    window.setVerticalSyncEnabled(true);
    float properties = (float)((abs(pt.x - start.x) - 1)) / ((abs(pt.y - start.y) - 1));
    window.setFramerateLimit(75);
    
    while (window.isOpen()) {
        window.clear(Color(125,125,125));
        
        float w = static_cast<float>(window.getSize().x);
        float h = static_cast<float>(window.getSize().y);
        
        window.setView(
            sf::View(
                sf::Vector2f(w / 2.0, h / 2.0),
                sf::Vector2f(w, h)
            )
        );
            
            window_size = window.getSize();
                int MaxHeight = window_size.y - 60;
                int MaxWidth = window_size.x - 20;
            if (int(float(MaxWidth / properties)) >= MaxHeight)
            {
                
                int ab_width = (float) MaxHeight * properties;
                int ab_height = MaxHeight;
                float scale = (float)ab_width / aa.getGlobalBounds().width;
                ab.setScale(scale, scale);
                ab.setPosition((window_size.x - ab_width) / 2, (window_size.y - 40 - ab_height) / 2 + 40);
                window.draw(ab);
            }
            else
            {
                int ab_width = MaxWidth;
                int ab_height = (float)MaxWidth / properties;
                float scale = (float)ab_width / aa.getGlobalBounds().width;
                ab.setScale(scale, scale);
                ab.setPosition((window_size.x - ab_width) / 2, (window_size.y - 40 - ab_height) / 2 + 40);
                window.draw(ab);
            }
            window.display();
            
        Event event;
        while (window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    
                    start = sf::Mouse::getPosition();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                   

                    
                    THREAD_one_Flag = 10;
                }
            }
            if (event.type == Event::Closed) {
                window.close();
                THREAD_one_Flag = 5;
            }
            if (event.type == Event::Resized) {

            }
        }
        
        
    }
    THREAD_one_Flag = 5;
}


int main()
{
    HICON hIcon = static_cast<HICON>(LoadImage(NULL,
        TEXT("C:\\Users\\Дима\\Desktop\\night_stand_bedroom_furniture_icon_209732.ico"),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTCOLOR | LR_SHARED | LR_DEFAULTSIZE | LR_LOADFROMFILE));
    NOTIFYICONDATA nid = {};
    nid.cbSize = sizeof(nid);
    nid.hIcon = hIcon;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    wcscpy(nid.szTip, L"ToolTip");
    static const GUID myGUID = { 0xed65fa2e, 0x7f4f, 0x4b25, { 0xb9, 0xd5, 0xdc, 0x71, 0xdd, 0xef, 0xb4, 0x30 } };
    nid.guidItem = myGUID;
    // This text will be shown as the icon's tooltip.
    nid.uVersion = NOTIFYICON_VERSION_4;
    // Add the icon
    Shell_NotifyIcon(NIM_ADD, &nid);
    // Set the version
    Shell_NotifyIcon(NIM_SETVERSION, &nid);
    
    while (1) {
        
        Sleep(100);
        if ((GetAsyncKeyState(VK_TAB) == -32767)) {
            std::thread MD(Form1);
            MD.join();
                
            
        }
        nid.hWnd = f;
        
        if (THREAD_one_Flag == 10) {
            
            std::thread MD(Form2);
            MD.join();
        }
    }
    Shell_NotifyIcon(NIM_DELETE, &nid);
    
    return 0;
}


    