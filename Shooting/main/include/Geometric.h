#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_
#include "BaseObject.h"

struct GeometricFormat { // Định dạng hình học
    GeometricFormat(int left, int top, int width, int height) : left_(left), top_(top), width_(width), height_(height) {}
    int left_; // Vị trí trái
    int top_; // Vị trí trên
    int width_; // Chiều rộng
    int height_; // Chiều cao
};

struct ColorData { // Dữ liệu màu
    ColorData(Uint8 r, Uint8 g, Uint8 b) : red_(r), green_(g), blue_(b) {}
    Uint8 red_; // Màu đỏ
    Uint8 green_; // Màu xanh lá
    Uint8 blue_; // Màu xanh dương
};

class Geometric {
public:
    static void RenderRectangle(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen); // Vẽ hình chữ nhật
    static void RenderOutLine(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen); // Vẽ viền hình chữ nhật

protected:
private:
};

#endif // GEOMETRIC_H_