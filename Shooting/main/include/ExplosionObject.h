#ifndef EXPLOSION_OBJECT_H
#define EXPLOSION_OBJECT_H

#include "BaseObject.h"

#define NUM_FRAME_EXP 8 // Số khung hình vụ nổ

class ExplosionObject : public BaseObject {
public:
    ExplosionObject(); // Khởi tạo
    ~ExplosionObject(); // Hủy

    void set_clip(); // Thiết lập khung hình
    void set_frame(const int& fr) { frame_ = fr; } // Đặt khung hình hiện tại
    virtual bool LoadImg(std::string path, SDL_Renderer* screen); // Tải ảnh
    void Show(SDL_Renderer* screen); // Hiển thị vụ nổ
    int get_frame_width() const { return frame_width_; } // Lấy chiều rộng khung
    int get_frame_height() const { return frame_height_; } // Lấy chiều cao khung

private:
    int frame_width_; // Chiều rộng khung hình
    int frame_height_; // Chiều cao khung hình
    unsigned frame_; // Khung hình hiện tại
    SDL_Rect frame_clip_[8]; // Mảng lưu các khung hình
};

#endif // EXPLOSION_OBJECT_H