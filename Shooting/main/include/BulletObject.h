#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"

class BulletObject : public BaseObject { // Kế thừa lớp BaseObject
public:
    BulletObject(); // Khởi tạo
    ~BulletObject(); // Hủy

    enum BulletDir { // Các hướng đạn bắn
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_UP_LEFT = 23,
        DIR_UP_RIGHT = 24,
        DIR_DOWN_LEFT = 25,
        DIR_DOWN_RIGHT = 26,
    };

    enum BulletType { // Loại đạn bắn
        BULLET = 50,
        LASER_BULLET = 51,
        
    };

    void set_x_val(const int& xVal) { x_val_ = xVal; } // Đặt giá trị x
    void set_y_val(const int& yVal) { y_val_ = yVal; } // Đặt giá trị y
    int get_x_val() const { return x_val_; } // Lấy giá trị x
    int get_y_val() const { return y_val_; } // Lấy giá trị y

    void set_is_move(const bool isMove) { is_move_ = isMove; } // Đặt trạng thái di chuyển
    bool get_is_move() const { return is_move_; } // Lấy trạng thái di chuyển

    void set_bullet_dir(const unsigned int& bulletDir) { bullet_dir_ = bulletDir; } // Đặt hướng đạn
    unsigned int get_bullet_dir() const { return bullet_dir_; } // Lấy hướng đạn

    void set_bullet_type(const unsigned int& bulletType) { bullet_type_ = bulletType; } // Đặt loại đạn
    unsigned int get_bullet_type() const { return bullet_type_; } // Lấy loại đạn

    void HandleMove(const int& x_border, const int& y_border); // Xử lý di chuyển đạn
    void HandleMovePlayer(const int& x_border, const int& y_border); // Xử lý di chuyển đạn của người chơi
    bool LoadImgBullet(SDL_Renderer* des); // Tải ảnh đạn

private:
    int x_val_; // Giá trị x khi di chuyển
    int y_val_; // Giá trị y khi di chuyển
    bool is_move_; // Kiểm tra đạn có di chuyển hay không
    unsigned int bullet_dir_; // Hướng đạn
    unsigned int bullet_type_; // Loại đạn
};

#endif // BULLET_OBJECT_H_