#include "CommonFunc.h"

// Kiểm tra va chạm giữa hai hình chữ nhật
bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Trường hợp 1: Kích thước object1 < object2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b || bottom_a > top_b && bottom_a < bottom_b)
            return true;
    }
    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b || bottom_a > top_b && bottom_a < bottom_b)
            return true;
    }

    // Trường hợp 2: Kích thước object1 > object2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a || bottom_b > top_a && bottom_b < bottom_a)
            return true;
    }
    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a || bottom_b > top_a && bottom_b < bottom_a)
            return true;
    }

    // Trường hợp 3: Kích thước object1 = object2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
        return true;

    return false;
}

// Kiểm tra điểm (x, y) có nằm trong hình chữ nhật
bool SDLCommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    return (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h);
}