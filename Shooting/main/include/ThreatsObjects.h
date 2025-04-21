#ifndef THREATS_OBJECTS_H_
#define THREATS_OBJECTS_H_

#include "BaseObject.h"
#include "BulletObject.h"
#include <bits/stdc++.h>

#define THREAT_FRAME_NUM 8 // Số khung hình
#define THREAT_GRAVITY_SPEED 0.8 // Tốc độ trọng lực
#define THREAT_MAX_FALL_SPEED 10 // Tốc độ rơi tối đa
#define THREAT_SPEED 3 // Tốc độ di chuyển
#define MOVE_THREAT 1 // Định nghĩa cho threat động

class ThreatsObjects : public BaseObject {
public:
    ThreatsObjects(); // Khởi tạo
    ~ThreatsObjects(); // Hủy

    enum TypeMove { // Loại di chuyển
        MOVE_IN_SPACE_THREAT = 1, // Di chuyển trong khoảng
    };

    enum WalkType { // Hướng di chuyển
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    void set_x_val(const float& xVal) { x_val_ = xVal; } // Đặt giá trị x
    void set_y_val(const float& yVal) { y_val_ = yVal; } // Đặt giá trị y
    void set_x_pos(const float& xp) { x_pos_ = xp; } // Đặt vị trí x
    void set_y_pos(const float& yp) { y_pos_ = yp; } // Đặt vị trí y
    float get_x_pos() const { return x_pos_; } // Lấy vị trí x
    float get_y_pos() const { return y_pos_; } // Lấy vị trí y
    void SetMapXY(const int& mp_x, const int& mp_y) { map_x_ = mp_x; map_y_ = mp_y; } // Đặt vị trí bản đồ
    void set_clips(); // Thiết lập khung hình
    bool LoadImg(std::string path, SDL_Renderer* screen); // Tải ảnh
    void Show(SDL_Renderer* des); // Hiển thị
    int get_width_frame() const { return width_frame_; } // Lấy chiều rộng khung
    int get_height_frame() const { return height_frame_; } // Lấy chiều cao khung
    void DoPlayer(Map& gMap); // Xử lý hành động
    void CheckToMap(Map& gMap); // Kiểm tra va chạm bản đồ
    void InitThreats(); // Khởi tạo threat
    void RemoveBullet(const int& idx); // Xóa đạn
    void set_type_move(const int& typeMove) { type_move_ = typeMove; } // Đặt loại di chuyển
    void SetAnimationPos(const int& pos_a, const int& pos_b) { animation_a_ = pos_a; animation_b_ = pos_b; } // Đặt vị trí hoạt hình
    void set_input_left(const int& ipLeft) { input_type_.left_ = ipLeft; } // Đặt di chuyển trái
    void ImpMoveType(SDL_Renderer* screen, Map& gMap); // Xử lý di chuyển trong khoảng
    SDL_Rect GetRectFrame(); // Lấy khung hình
    std::vector<BulletObject*> get_bullet_list() const { return bullet_list_; } // Lấy danh sách đạn
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) { bullet_list_ = bl_list; } // Đặt danh sách đạn
    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen); // Khởi tạo đạn
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit); // Tạo đạn

private:
    int frame_; // Khung hình hiện tại
    int width_frame_; // Chiều rộng khung
    int height_frame_; // Chiều cao khung
    SDL_Rect frame_clip_[THREAT_FRAME_NUM]; // Mảng khung hình
    bool on_ground_; // Trạng thái trên mặt đất
    int come_back_time_; // Thời gian hồi sinh
    float x_pos_; // Vị trí x
    float y_pos_; // Vị trí y
    float x_val_; // Giá trị thay đổi x
    float y_val_; // Giá trị thay đổi y
    int map_x_; // Vị trí bản đồ x
    int map_y_; // Vị trí bản đồ y
    int type_move_; // Loại di chuyển
    int animation_a_; // Vị trí trái
    int animation_b_; // Vị trí phải
    Input input_type_; // Trạng thái di chuyển
    int dir_threats_; // Hướng threat
    std::vector<BulletObject*> bullet_list_; // Danh sách đạn
};

#endif // THREATS_OBJECTS_H_