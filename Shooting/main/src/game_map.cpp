#include "game_map.h"
#include <iostream>

void GameMap::LoadMap(char* name) // Đọc file map
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb"); // Mở file chế độ đọc
    if (fp == NULL) return; // Không có file thì thoát

    game_map_.max_x_ = 0; // Khởi tạo max_x
    game_map_.max_y_ = 0; // Khởi tạo max_y
    for (int i = 0; i < MAX_MAP_Y; i++) {
        for (int j = 0; j < MAX_MAP_X; j++) {
            fscanf(fp, "%d", &game_map_.tile[i][j]); // Đọc từng ô trong map
            int val = game_map_.tile[i][j];
            if (val > 0) {
                if (j > game_map_.max_x_) game_map_.max_x_ = j; // Cập nhật max_x
                if (i > game_map_.max_y_) game_map_.max_y_ = i; // Cập nhật max_y
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE; // Tính tọa độ x
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE; // Tính tọa độ y
    game_map_.start_x_ = 0; // Điểm bắt đầu x
    game_map_.start_y_ = 0; // Điểm bắt đầu y
    game_map_.file_name_ = name; // Lưu tên file
    fclose(fp); // Đóng file
}

void GameMap::LoadTiles(SDL_Renderer* screen) // Tải ảnh cho tiles
{
    char file_img[30];
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TILES; i++) {
        sprintf_s(file_img, "map/%d.png", i); // Tạo đường dẫn ảnh
        fopen_s(&fp, file_img, "rb"); // Kiểm tra file ảnh
        if (fp == NULL) continue; // Không có thì bỏ qua
        fclose(fp);
        tile_mat[i].LoadImg(file_img, screen); // Tải ảnh vào screen
    }
}

void GameMap::DrawMap(SDL_Renderer* screen) // Vẽ map lên màn hình
{
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int map_x = game_map_.start_x_ / TILE_SIZE; // Tọa độ x của map
    int map_y = game_map_.start_y_ / TILE_SIZE; // Tọa độ y của map

    x1 = (game_map_.start_x_ % TILE_SIZE) * -1; // Lùi 1 ô
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE); // Mở rộng nếu cần
    y1 = (game_map_.start_y_ % TILE_SIZE) * -1; // Lùi 1 ô
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE); // Mở rộng nếu cần

    for (int i = y1; i < y2; i += TILE_SIZE) {
        map_x = game_map_.start_x_ / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE) {
            int val = game_map_.tile[map_y][map_x];
            if (val > 0) {
                tile_mat[val].SetRect(j, i); // Đặt vị trí tile
                tile_mat[val].Render(screen); // Vẽ tile
            }
            map_x++; // Tăng ô ngang
        }
        map_y++; // Tăng ô dọc
    }
}