#include "MainObject.h"
#include <iostream>
#include "BaseObject.h"

// Khởi tạo đối tượng nhân vật chính
MainObject::MainObject() {
    frame_ = 0; x_pos_ = 0; y_pos_ = 0; x_val_ = 0; y_val_ = 0;
    width_frame_ = 0; height_frame_ = 0;
    input_type_.left_ = 0; input_type_.right_ = 0; input_type_.jump_ = 0;
    input_type_.down_ = 0; input_type_.up_ = 0;
    on_ground_ = false; map_x_ = 0; map_y_ = 0; come_back_time_ = 0;
    money_count = 0; status_ = WALK_RIGHT; mute_ = false; input_type_.shoot_ = 0;
}

// Hủy đối tượng
MainObject::~MainObject() {}

// Tải hình ảnh nhân vật
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) {
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        width_frame_ = rect_.w / 8; height_frame_ = rect_.h;
    }
    return ret;
}

// Lấy khung hình chữ nhật của nhân vật
SDL_Rect MainObject::GetRectFrame() {
    SDL_Rect rect;
    rect.x = rect_.x; rect.y = rect_.y;
    rect.w = width_frame_; rect.h = height_frame_;
    return rect;
}

// Thiết lập khung hình hoạt hình
void MainObject::set_clips() {
    if (width_frame_ > 0 && height_frame_ > 0) {
        for (int i = 0; i < 8; i++) {
            frame_clip_[i].x = i * width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

// Hiển thị nhân vật lên màn hình
void MainObject::Show(SDL_Renderer* des) {
    UpdateImagePlayer(des);
    if (input_type_.left_ == 1 || input_type_.right_ == 1) frame_++;
    else frame_ = 0;
    if (frame_ >= 8) frame_ = 0;
    if (come_back_time_ == 0) {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        SDL_Rect* current_clip = &frame_clip_[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
    }
}

// Xử lý sự kiện đầu vào từ người chơi
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* player_sound[10]) {
    if (events.type == SDL_KEYDOWN) {
        switch (events.key.keysym.sym) {
            case SDLK_RIGHT:
                status_ = WALK_RIGHT; input_type_.right_ = 1; input_type_.left_ = 0;
                UpdateImagePlayer(screen);
                if (on_ground_ && !mute_) {
                    Mix_PlayChannel(-1, player_sound[6], 0);
                    Mix_PlayChannel(-1, player_sound[7], 0);
                }
                break;
            case SDLK_LEFT:
                status_ = WALK_LEFT; input_type_.left_ = 1; input_type_.right_ = 0;
                UpdateImagePlayer(screen);
                if (on_ground_ && !mute_) {
                    Mix_PlayChannel(-1, player_sound[6], 0);
                    Mix_PlayChannel(-1, player_sound[7], 0);
                }
                break;
            case SDLK_UP:
                input_type_.jump_ = 1;
                if (!mute_) Mix_PlayChannel(-1, player_sound[4], 0);
                break;
            case SDLK_m: mute_ = true; break;
            case SDLK_u: mute_ = false; break;
            case SDLK_SPACE:
                input_type_.shoot_ = 1;
                BulletObject* p_bullet = new BulletObject();
                p_bullet->set_bullet_type(BulletObject::BULLET);
                p_bullet->LoadImg("img//bullet.png", screen);
                p_bullet->set_is_move(true);
                int x_player = x_pos_ - map_x_;
                int y_player = y_pos_ - map_y_;
                if (status_ == WALK_LEFT) {
                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(x_player - 20, y_player + height_frame_ * 0.3);
                } else {
                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(x_player + width_frame_ - 15, y_player + height_frame_ * 0.3);
                }
                p_bullet->set_x_val(15); p_bullet->set_y_val(20);
                p_bullet_list_.push_back(p_bullet);
                if (!mute_) Mix_PlayChannel(-1, player_sound[8], 0);
                break;
        }
    } else if (events.type == SDL_KEYUP) {
        switch (events.key.keysym.sym) {
            case SDLK_RIGHT: input_type_.right_ = 0; break;
            case SDLK_LEFT: input_type_.left_ = 0; break;
            case SDLK_UP: input_type_.jump_ = 0; break;
            case SDLK_SPACE: input_type_.shoot_ = 0; break;
        }
    }
}

// Xử lý di chuyển và hiển thị đạn
void MainObject::HandleBullet(SDL_Renderer* des) {
    for (int i = 0; i < p_bullet_list_.size(); i++) {
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if (p_bullet) {
            if (p_bullet->get_is_move()) {
                p_bullet->HandleMovePlayer(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            } else {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                delete p_bullet;
                p_bullet = NULL;
            }
        }
    }
}

// Xóa đạn tại vị trí idx
void MainObject::RemoveBullet(const int& idx) {
    int size = p_bullet_list_.size();
    if (size > 0 && idx < size) {
        BulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);
        if (p_bullet) {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

// Xử lý hành động của nhân vật
void MainObject::DoPlayer(Map& map_data, Mix_Chunk* player_sound[10]) {
    if (come_back_time_ == 0) {
        x_val_ = 0; y_val_ += 0.8;
        if (y_val_ >= MAX_FALL_SPEED) y_val_ = MAX_FALL_SPEED;
        if (input_type_.left_ == 1) x_val_ -= PLAYER_SPEED;
        else if (input_type_.right_ == 1) x_val_ += PLAYER_SPEED;
        if (input_type_.jump_ == 1) {
            if (on_ground_) y_val_ = -PLAYER_JUMP_VAL;
            on_ground_ = false; input_type_.jump_ = 0;
        }
        CheckToMap(map_data, player_sound);
        CenterEntityOnMap(map_data);
    }
    if (come_back_time_ > 0) {
        come_back_time_--;
        if (come_back_time_ == 0) {
            if (x_pos_ > 256) x_pos_ -= 256;
            y_pos_ = 0; x_val_ = 0; y_val_ = 0;
        }
    }
}

// Căn giữa camera theo nhân vật
void MainObject::CenterEntityOnMap(Map& map_data) {
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
    if (map_data.start_x_ < 0) map_data.start_x_ = 0;
    else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    map_data.start_y_ = y_pos_ - SCREEN_HEIGHT;
    if (map_data.start_y_ < 0) map_data.start_y_ = 0;
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
}

// Kiểm tra va chạm với bản đồ
void MainObject::CheckToMap(Map& map_data, Mix_Chunk* player_sound[10]) {
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;
    y1 = y_pos_ / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
        if (x_val_ > 0) {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];
            if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
                map_data.tile[y1][x2] = 0; map_data.tile[y2][x2] = 0;
                if (!mute_) Mix_PlayChannel(-1, player_sound[2], 0);
                increase_money();
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
                x_pos_ = x2 * TILE_SIZE - (width_frame_ + 1);
                x_val_ = 0;
            }
        } else if (x_val_ < 0) {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
                map_data.tile[y1][x1] = 0; map_data.tile[y2][x1] = 0;
                increase_money();
                if (!mute_) Mix_PlayChannel(-1, player_sound[2], 0);
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
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
        if (y_val_ > 0) {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
                map_data.tile[y2][x1] = 0; map_data.tile[y2][x2] = 0;
                increase_money();
                if (!mute_) Mix_PlayChannel(-1, player_sound[2], 0);
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
                y_pos_ = y2 * TILE_SIZE - (height_frame_ + 1);
                y_val_ = 0; on_ground_ = true;
            }
        } else if (y_val_ < 0) {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
                map_data.tile[y1][x1] = 0; map_data.tile[y1][x2] = 0;
                increase_money();
                if (!mute_) Mix_PlayChannel(-1, player_sound[2], 0);
            } else if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_; y_pos_ += y_val_;
    if (x_pos_ < 0) x_pos_ = 0;
    else if (x_pos_ + width_frame_ > map_data.max_x_)
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    if (y_pos_ > map_data.max_y_) {
        come_back_time_ = 60; die++;
    }
}

// Tăng số tiền thu thập
void MainObject::increase_money() {
    money_count++;
}

// Cập nhật hình ảnh nhân vật
void MainObject::UpdateImagePlayer(SDL_Renderer* des) {
    Free();
    if (on_ground_) {
        if (status_ == WALK_LEFT) LoadImg("img//goku_walk_left.png", des);
        else LoadImg("img//goku_walk_right.png", des);
    } else {
        if (status_ == WALK_LEFT) LoadImg("img//goku_jump_left.png", des);
        else LoadImg("img//goku_jump_right.png", des);
    }
}