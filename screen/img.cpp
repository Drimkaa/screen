#include "img.h"
string path; int x; int y;
Image _base_image;
Texture _base_texture;
Sprite _base_sprite;
sf::Image screenShot;
Sprite img::create(string path, int x, int y) {
    _base_image.loadFromFile(path);
    _base_texture.loadFromImage(_base_image);
    _base_sprite.setTexture(_base_texture);
    _base_sprite.setPosition(x, y);
    return _base_sprite;
}
Sprite img::GetFullScreenShot()
{
    HDC hScreenDC = GetDC(0); // CreateDC("DISPLAY",nullptr,nullptr,nullptr);
    HDC hMemoryDC = CreateCompatibleDC(0);
    int width = GetDeviceCaps(GetDC(nullptr), HORZRES);
    int height = GetDeviceCaps(GetDC(nullptr), VERTRES);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hBitmap));
    BitBlt(hMemoryDC, 0, 0, width , height, hScreenDC, 0, 0, SRCCOPY);
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();
    DeleteObject(hBitmap);
    if (OpenClipboard(nullptr))
    {
        auto cpHandle = GetClipboardData(CF_DIBV5);
        CloseClipboard();
        if (cpHandle)
        {
            auto data = static_cast<sf::Uint8*>(GlobalLock(cpHandle));
            auto header = *reinterpret_cast<BITMAPV5HEADER*>(data);
            screenShot.create(width, height, data + header.bV5Size+12);
            for (int i = 0; i < width * height; ++i)
            {
                auto xx = i % width;
                auto yy = i / width;
                auto color = screenShot.getPixel(xx, yy);
                screenShot.setPixel(xx, yy, sf::Color(color.b, color.g, color.r, color.a));
            }
            screenShot.flipVertically();
        }
    }
    _base_image = screenShot;
    _base_texture.loadFromImage(_base_image);
    _base_sprite.setTexture(_base_texture);
    _base_sprite.setPosition(0, 0);
    return _base_sprite;
}
Sprite img::GetScreenShot(int x1, int y1, int width, int height)
{
    Texture base_texture;
    Sprite base_sprite;
    HDC hScreenDC = CreateDC(_T("DISPLAY"), nullptr, nullptr, nullptr);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hBitmap));
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, x1, y1, SRCCOPY);
    hBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hOldBitmap));
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();
    DeleteObject(hBitmap);
    if (OpenClipboard(nullptr))
    {
        auto cpHandle = GetClipboardData(CF_DIBV5  );
        CloseClipboard();
        if (cpHandle)
        {
            auto data = static_cast<sf::Uint8*>(GlobalLock(cpHandle));
            auto header = *reinterpret_cast<BITMAPV5HEADER*>(data);
            screenShot.create(width, height, data + header.bV5Size + 12);
            for (int i = 0; i < width * height; ++i)
            {
                auto xx = i % width;
                auto yy = i / width;
                auto color = screenShot.getPixel(xx, yy);
                screenShot.setPixel(xx, yy, sf::Color(color.b, color.g, color.r, color.a));
            }
            screenShot.flipVertically();
        }
    }
    _base_image = screenShot;
    _base_texture.loadFromImage(_base_image);
    _base_sprite.setTexture(_base_texture);
    //_base_sprite.setPosition(0, 0);
    return _base_sprite;

}

        