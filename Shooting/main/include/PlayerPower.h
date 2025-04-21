#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_
#include "BaseObject.h"

class PlayerPower : public BaseObject { // Quản lý số mạng
public:
    PlayerPower(); // Khởi tạo
    ~PlayerPower(); // Hủy

    void SetNum(const int& num) { number_ = num; } // Đặt số mạng
    void AddPos(const int& xp); // Thêm vị trí
    void Show(SDL_Renderer* screen); // Hiển thị
    void Init(SDL_Renderer* screen); // Khởi tạo

    void Increase(); // Tăng mạng
    void Decrease(); // Giảm mạng

private:
    int number_; // Số mạng
    std::vector<int> pos_list_; // Danh sách vị trí
};

class PlayerMoney : public BaseObject { // Quản lý tiền
public:
    PlayerMoney(); // Khởi tạo
    ~PlayerMoney(); // Hủy

    void Init(SDL_Renderer* screen); // Khởi tạo
    void Show(SDL_Renderer* screen); // Hiển thị
    void SetPos(const int& x, const int& y) { x_pos_ = x; y_pos_ = y; } // Đặt vị trí

private:
    int x_pos_; // Tọa độ x
    int y_pos_; // Tọa độ y
};

class PlayerMusic : public BaseObject { // Quản lý âm thanh
public:
    PlayerMusic(); // Khởi tạo
    ~PlayerMusic(); // Hủy

    void InitMute(SDL_Renderer* screen); // Khởi tạo trạng thái tắt tiếng
    void InitUnmute(SDL_Renderer* screen); // Khởi tạo trạng thái bật tiếng
    void Show(SDL_Renderer* screen); // Hiển thị
    void SetPos(const int& x, const int& y) { x_pos_ = x; y_pos_ = y; } // Đặt vị trí

private:
    int x_pos_; // Tọa độ x
    int y_pos_; // Tọa độ y
};

#endif // PLAYER_POWER_H_