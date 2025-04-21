#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "BaseObject.h"
#define MAX_TILES 20 // Số ô hình ảnh tối đa

class TileMat : public BaseObject { // TileMat kế thừa BaseObject
public:
    TileMat() {} // Khởi tạo
    ~TileMat() {} // Hủy
};

class GameMap {
public:
    GameMap() {} // Khởi tạo
    ~GameMap() {} // Hủy

    void LoadMap(char* name); // Đọc map từ file text
    void LoadTiles(SDL_Renderer* screen); // Tải hình ảnh cho tile map
    void DrawMap(SDL_Renderer* screen); // Vẽ map lên màn hình
    Map getMap() const { return game_map_; } // Lấy dữ liệu map
    void SetMap(Map& map_data) { game_map_ = map_data; } // Đặt dữ liệu map

private:
    Map game_map_; // Lưu trạng thái bản đồ
    TileMat tile_mat[MAX_TILES]; // Lưu trữ hình ảnh tile
};

#endif // GAME_MAP_H