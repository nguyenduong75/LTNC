#include "ThreatsObjects.h"

ThreatsObjects::ThreatsObjects() { // Khởi tạo
    width_frame_ = height_frame_ = 0;
    x_val_ = y_val_ = x_pos_ = y_pos_ = 0.0;
    on_ground_ = come_back_time_ = frame_ = 0;
    animation_a_ = animation_b_ = 0;
    input_type_.left_ = 0; // Mặc định quay trái
    type_move_ = MOVE_THREAT; // Chỉ giữ threat động
    dir_threats_ = 0;
}

ThreatsObjects::~ThreatsObjects() {}

bool ThreatsObjects::LoadImg(std::string path, SDL_Renderer* screen) { // Tải ảnh threat
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame_ = rect_.w / THREAT_FRAME_NUM; // Chia frame
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect ThreatsObjects::GetRectFrame() { // Lấy khung hiện tại
    return {rect_.x, rect_.y, width_frame_, height_frame_};
}

void ThreatsObjects::set_clips() { // Cắt frame animation
    if (width_frame_ > 0 && height_frame_ > 0) {
        for (int i = 0; i < 8; i++) {
            frame_clip_[i] = {i * width_frame_, 0, width_frame_, height_frame_};
        }
    }
}

void ThreatsObjects::Show(SDL_Renderer* des) { // Hiển thị threat
    if (come_back_time_ == 0) {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= 8) frame_ = 0;

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
    }
}

void ThreatsObjects::DoPlayer(Map& gMap) { // Xử lý di chuyển threat
    if (come_back_time_ == 0) {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;; // Tốc độ rơi
        if (y_val_ >= THREAT_MAX_FALL_SPEED) y_val_ = THREAT_MAX_FALL_SPEED;

        if (input_type_.left_ == 1) x_val_ -= THREAT_SPEED;
        else if (input_type_.right_ == 1) x_val_ += THREAT_SPEED;

        CheckToMap(gMap);
        if (input_type_.jump_ == 1 && on_ground_) { // Nhảy
            y_val_ = -18;
            on_ground_ = false;
            input_type_.jump_ = 0;
        }
    } else if (come_back_time_ > 0) {
        come_back_time_--;
        if (come_back_time_ == 0) InitThreats();
    }
}

void ThreatsObjects::InitThreats() { // Reset threat
    x_val_ = y_val_ = 0;
    if (x_pos_ > 256) {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    } else x_pos_ = 0;
    y_pos_ = 0;
    come_back_time_ = 0;
    input_type_.left_ = 1;
}

void ThreatsObjects::RemoveBullet(const int& idx) { // Xóa đạn
    if (idx < bullet_list_.size()) {
        BulletObject* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);
        delete p_bullet;
    }
}

void ThreatsObjects::CheckToMap(Map& gMap) { // Kiểm tra va chạm
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;
    y1 = y_pos_ / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (x_val_ > 0) { // Sang phải
            int val1 = gMap.tile[y1][x2], val2 = gMap.tile[y2][x2];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                x_pos_ = x2 * TILE_SIZE - (width_frame_ + 1);
                x_val_ = 0;
            }
        } else if (x_val_ < 0) { // Sang trái
            int val1 = gMap.tile[y1][x1], val2 = gMap.tile[y2][x1];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = x_pos_ / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;
    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + height_frame_ - 1 + y_val_) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (y_val_ > 0) { // Rơi xuống
            int val1 = gMap.tile[y2][x1], val2 = gMap.tile[y2][x2];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                y_pos_ = y2 * TILE_SIZE - (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        } else if (y_val_ < 0) { // Nhảy lên
            int val1 = gMap.tile[y1][x1], val2 = gMap.tile[y1][x2];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0) x_pos_ = 0;
    else if (x_pos_ + width_frame_ > gMap.max_x_) x_pos_ = gMap.max_x_ - width_frame_ - 1;

    if (y_pos_ > gMap.max_y_) come_back_time_ = 60; // Rơi quá sâu
}

void ThreatsObjects::ImpMoveType(SDL_Renderer* screen, Map& gMap) { // Xử lý kiểu di chuyển động
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;
    y1 = y_pos_ / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (on_ground_) {
        if (x_pos_ > animation_b_ + 100 || gMap.tile[y1][x2] != BLANK_TILE || gMap.tile[y2][x2] != BLANK_TILE) {
            dir_threats_ = WALK_RIGHT;
            input_type_.jump_ = 1;
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            LoadImg("img//vgt_left.png", screen);
        } else if (x_pos_ < animation_a_ - 100 || gMap.tile[y1][x1] != BLANK_TILE || gMap.tile[y2][x1] != BLANK_TILE) {
            dir_threats_ = WALK_LEFT;
            input_type_.jump_ = 1;
            input_type_.left_ = 0;
            input_type_.right_ = 1;
            LoadImg("img//vgt_right.png", screen);
        }
    } else if (input_type_.left_ == 1) {
        LoadImg("img//vgt_left.png", screen);
    }
}

void ThreatsObjects::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen) { // Khởi tạo đạn
    if (p_bullet && p_bullet->LoadImgBullet(screen)) {
        int x_th = x_pos_ - map_x_, y_th = y_pos_ - map_y_;
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(x_th + 5, y_th + 10);
        p_bullet->set_x_val(15);
        bullet_list_.push_back(p_bullet);
    }
}

void ThreatsObjects::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit) { // Xử lý đạn
    for (int i = 0; i < bullet_list_.size(); i++) {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet) {
            if (p_bullet->get_is_move()) {
                int bullet_distance = rect_.x - p_bullet->GetRect().x + width_frame_;
                if (bullet_distance < 300 && bullet_distance > -300) {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
                } else {
                    p_bullet->set_is_move(false);
                }
            } else {
                p_bullet->set_is_move(true);
                if (input_type_.left_ == 1) {
                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(rect_.x + 5, rect_.y + 10);
                } else if (input_type_.right_ == 1) {
                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(rect_.x + 20, rect_.y + 10);
                }
            }
        }
    }
}