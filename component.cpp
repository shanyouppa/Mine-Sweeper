#include "component.h"

Button::Button(int x, int y, int width, int height, int color, const TCHAR* text)
        : x(x), y(y), width(width), height(height), color(color), text(text), gap(0) {};
void Button::setFun_back(function<void()> fun, std::string log_message)
{
    this->log_message = log_message;
    Fun_back = std::move(fun);
}
void Button::LMouse(MOUSEMSG m) const
{
    if(m.x>x && m.x<x+width && m.y>y && m.y<y+height && m.uMsg == WM_LBUTTONDOWN)
    {
        logger.out(log_message);
        Fun_back();
        closegraph();
    }
}
void Button::draw(MOUSEMSG m) {
    gap = (m.x >= x && m.x <= x + width && m.y >= y && m.y <= y + height) ? 5 : 0;
    setfillcolor(color);
    solidrectangle(x+ gap, y+ gap, x+ width- gap, y+ height- gap);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(x+ width/2- textwidth(text)/2, y+ height/2- textheight(text)/2, text); //居中显示文本
}
void Buttons::setButton(int x, int y, int width, int height, int color, const TCHAR* text) {
    buttons.emplace_back(x, y, width, height, color, text);
}

void Buttons::draw(MOUSEMSG m) {
    for (Button& b : buttons) {
        b.draw(m);
        b.LMouse(m);
    }
}