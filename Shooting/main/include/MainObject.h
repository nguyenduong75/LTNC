#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8 // Tốc độ trọng lực
#define MAX_FALL_SPEED 10 // Tốc độ rơi tối đa
#define PLAYER_SPEED 10 // Tốc độ di chuyển
#define PLAYER_JUMP_VAL 18 // Giá trị nhảy

class MainObject : public BaseObject { // Kế thừa lớp BaseObject
public:
    MainObject(); // Khởi tạo
    ~MainObject(); // Hủy

    enum WalkType { // Loại di chuyển
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen); // Tải ảnh nhân vật
    void Show(SDL_Renderer* des); // Hiển thị và tăng frame
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* player_sound[10]); // Xử lý sự kiện phím
    void set_clips(); // Thiết lập clip cho frame

    void DoPlayer(Map& map_data, Mix_Chunk* player_sound[10]); // Xử lý rơi tự do và di chuyển
    void CheckToMap(Map& map_data, Mix_Chunk* player_sound[10]); // Kiểm tra va chạm với bản đồ
    void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; } // Đặt vị trí bản đồ
    void CenterEntityOnMap(Map& map_data); // Giữ nhân vật ở giữa màn hình
    void UpdateImagePlayer(SDL_Renderer* des); // Cập nhật ảnh nhân vật
    SDL_Rect GetRectFrame(); // Lấy khung hình nhân vật

    void set_bullet_list(std::vector<BulletObject*> bullet_list) { p_bullet_list_ = bullet_list; } // Đặt danh sách đạn
    std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; } // Lấy danh sách đạn
    void HandleBullet(SDL_Renderer* des); // Xử lý đạn
    void RemoveBullet(const int& idx); // Xóa đạn khi trúng
    void increase_money(); // Tăng số tiền
    void set_comeback_time(const int& cb_time) { come_back_time_ = cb_time; } // Đặt thời gian hồi sinh
    int GetMoneyCount() const { return money_count; } // Lấy số tiền
    int die = 0; // Số lần chết
    bool get_mute() const { return mute_; } // Lấy trạng thái tắt tiếng
    int get_input_shoot() const { return input_type_.shoot_; }
private:
    int money_count; // Số tiền
    std::vector<BulletObject*> p_bullet_list_; // Danh sách đạn
    float x_val_; // Giá trị thay đổi tọa độ x
    float y_val_; // Giá trị thay đổi tọa độ y
    float x_pos_; // Vị trí hiện tại x
    float y_pos_; // Vị trí hiện tại y
    int width_frame_; // Chiều rộng khung hình
    int height_frame_; // Chiều cao khung hình
    SDL_Rect frame_clip_[8]; // Mảng lưu các khung hình
    Input input_type_; // Trạng thái di chuyển
    int frame_; // Số frame hiện tại
    int status_; // Hướng di chuyển (trái/phải)
    bool on_ground_; // Trạng thái trên mặt đất
    int map_x_; // Vị trí bản đồ x
    int map_y_; // Vị trí bản đồ y
    int come_back_time_; // Thời gian hồi sinh
    bool mute_; // Trạng thái tắt tiếng
    
};

#endif // MAIN_OBJECT_H_