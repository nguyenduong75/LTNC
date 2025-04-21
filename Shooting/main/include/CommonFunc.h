#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

static Mix_Chunk* g_sound_player[10]; // Âm thanh người chơi
static Mix_Chunk* g_sound_exp[5]; // Âm thanh vụ nổ
static Mix_Chunk* g_theme_music[5]; // Nhạc chủ đề
static Mix_Chunk* g_general_music[5]; // Nhạc chung

static SDL_Window* g_window = NULL; // Cửa sổ
static SDL_Renderer* g_screen = NULL; // Màn hình render
static SDL_Event g_event; // Bắt sự kiện bàn phím
static SDL_Renderer* g_img_menu = NULL; // Menu hình ảnh

// Thiết lập màn hình
const int SCREEN_WIDTH = 1280; // Chiều rộng
const int SCREEN_HEIGHT = 640; // Chiều cao
const int SCREEN_BPP = 32; // Độ sâu màu (pixel)

// Thiết lập màu
const int COLOR_KEY_R = 167; // Đỏ
const int COLOR_KEY_G = 175; // Xanh lá
const int COLOR_KEY_B = 180; // Xanh dương

const int RENDER_DRAW_COLOR = 0xFF; // Màu vẽ

const int FRAME_PER_SECOND = 37; // FPS

#define TILE_SIZE 64 // Kích thước ô lưới

#define MAX_MAP_X 400 // Chiều rộng map (cột)
#define MAX_MAP_Y 10 // Chiều cao map (dòng)

#define BLANK_TILE 0 // Ô trống
#define STATE_MONEY 4 // Coin trong file dữ liệu

struct Input { // Trạng thái đầu vào của nhân vật
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int shoot_;
};

struct Map { // Dữ liệu bản đồ
    int start_x_; // Tọa độ x bắt đầu
    int start_y_; // Tọa độ y bắt đầu
    int max_x_; // Vị trí ô theo x
    int max_y_; // Vị trí ô theo y
    int tile[MAX_MAP_Y][MAX_MAP_X]; // Mảng 2 chiều lưu trạng thái map
    char* file_name_; // Tên file map
};

namespace SDLCommonFunc {
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2); // Kiểm tra va chạm
    bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect); // Kiểm tra điểm trong vùng
    int ShowMenu(SDL_Renderer* des, TTF_Font* font); // Hiển thị menu
}

#endif // COMMON_FUNCTION_H_