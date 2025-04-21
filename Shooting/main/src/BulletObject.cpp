#include "BulletObject.h"

BulletObject::BulletObject()
{
    // Khởi tạo
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = BULLET;
}

BulletObject::~BulletObject()
{
    // Hủy
}

// Tải hình ảnh đạn
bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if (bullet_type_ == LASER_BULLET)
    {
        ret = LoadImg("img//laser_bullet.png", des);
    }
    else if (bullet_type_ == BULLET)
    {
        ret = LoadImg("img//bullet.png", des);
    }
    return ret;
}

// Di chuyển đạn
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT) // Đạn bắn sang phải
    {
        rect_.x += x_val_; // x(t+1) = x(t) + v_x
        if (rect_.x > x_border) // Ra khỏi biên
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT) // Đạn bắn sang trái
    {
        rect_.x -= x_val_; // x(t+1) = x(t) - v_x
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
}

// Di chuyển đạn của người chơi
void BulletObject::HandleMovePlayer(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT) // Đạn bắn sang phải
    {
        rect_.x += x_val_;
        if (rect_.x > x_border + 500) // Ra khỏi biên
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT) // Đạn bắn sang trái
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
}