#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "CommonFunc.h"

class BaseObject {
public:
    BaseObject(); // Khởi tạo
    ~BaseObject(); // Hủy
    void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; } // Đặt tọa độ hình chữ nhật
    SDL_Rect GetRect() const { return rect_; } // Lấy hình chữ nhật
    SDL_Texture* GetObject() const { return p_object_; } // Lấy đối tượng

    virtual bool LoadImg(std::string path, SDL_Renderer* screen); // Tải ảnh
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL); // Vẽ ảnh
    void Free(); // Giải phóng

protected:
    SDL_Texture* p_object_; // Lưu texture
    SDL_Rect rect_; // Lưu kích thước
};

#endif // BASE_OBJECT_H_