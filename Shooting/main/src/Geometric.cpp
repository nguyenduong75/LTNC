#include "Geometric.h"

void Geometric::RenderRectangle(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect fill_rect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_}; // Tạo hình chữ nhật
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 0xFF); // Đặt màu
    SDL_RenderFillRect(screen, &fill_rect); // Vẽ hình chữ nhật đầy
}

void Geometric::RenderOutLine(const GeometricFormat& geo_size, const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect outRect = {geo_size.left_, geo_size.top_, geo_size.width_, geo_size.height_}; // Tạo viền hình chữ nhật
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 0xFF); // Đặt màu
    SDL_RenderDrawRect(screen, &outRect); // Vẽ viền hình chữ nhật
}