#include "BaseObject.h"

BaseObject::BaseObject() { // Khởi tạo
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject() { // Hủy
    Free(); // Giải phóng bộ nhớ
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 255, 255)); // Xóa nền trắng nếu cần
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            rect_.w = load_surface->w;
            rect_.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    p_object_ = new_texture;
    return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) { // Vẽ ảnh
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h}; // Tạo tọa độ vẽ
    SDL_RenderCopy(des, p_object_, clip, &renderquad); // Vẽ texture lên màn hình
}

void BaseObject::Free() { // Giải phóng
    if (p_object_ != NULL) {
        SDL_DestroyTexture(p_object_); // Hủy texture
        p_object_ = NULL;
        rect_.w = 0; // Đặt lại chiều rộng
        rect_.h = 0; // Đặt lại chiều cao
    }
}