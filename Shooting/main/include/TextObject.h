#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseObject.h"

class TextObject {
public:
    TextObject(); // Khởi tạo
    ~TextObject(); // Hủy

    enum TextColor { // Màu chữ
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen); // Tải văn bản
    void Free(); // Giải phóng
    void SetColor(Uint8 red, Uint8 green, Uint8 blue); // Đặt màu RGB
    void SetColor(int type); // Đặt màu theo loại
    void RenderText(SDL_Renderer* screen, SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE); // Vẽ văn bản
    int GetWidth() const { return rect.w; } // Lấy chiều rộng
    int GetHeight() const { return rect.h; } // Lấy chiều cao
    void SetText(const std::string& text) { str_val_ = text; } // Đặt nội dung văn bản
    std::string GetText() const { return str_val_; } // Lấy nội dung văn bản
    void SetRect(const int& xp, const int& yp) { rect.x = xp, rect.y = yp; } // Đặt vị trí
    SDL_Rect GetRect() const { return rect; } // Lấy vị trí

private:
    std::string str_val_; // Nội dung văn bản
    SDL_Color text_color_; // Màu chữ
    SDL_Texture* texture_; // Quản lý texture văn bản
    SDL_Rect rect; // Vị trí và kích thước
};

namespace Menu {
    int ShowMenu(SDL_Renderer* des, TTF_Font* font); // Hiển thị menu
    int ShowRestart(SDL_Renderer* des, TTF_Font* font); // Hiển thị menu khởi động lại
    int ShowTutorial(SDL_Renderer* des, TTF_Font* font); // Hiển thị hướng dẫn
    int ShowCre(SDL_Renderer* des, TTF_Font* font); // Hiển thị thông tin tác giả
}

#endif // TEXT_OBJECT_H_