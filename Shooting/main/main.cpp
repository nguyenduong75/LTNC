#include "CommonFunc.h"
#include "BaseObject.h"
#include <bits/stdc++.h>
#include <windows.h>
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObjects.h"
#include "ExplosionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"

BaseObject g_background;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
TTF_Font* font_tuto = NULL;
using namespace std;

bool InitData() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("7 viên bi rồng", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!g_window) return false;
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (!g_screen) return false;
    SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;
    if (TTF_Init() == -1) return false;
    font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
    font_menu = TTF_OpenFont("font//Haverbrooke.otf", 40);
    font_tuto = TTF_OpenFont("font//Keylock_Fighter.ttf", 40);
    if (!font_time || !font_menu) return false;
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
    g_sound_player[8] = Mix_LoadWAV("music//sound_gunShot.wav");
    g_sound_player[2] = Mix_LoadWAV("music//player_coin_eating.wav");
    g_sound_player[3] = Mix_LoadWAV("music//player_hurt.wav");
    g_sound_player[4] = Mix_LoadWAV("music//player_jump.wav");
    g_sound_player[5] = Mix_LoadWAV("music//player_landing.wav");
    g_sound_player[6] = Mix_LoadWAV("music//step1.wav");
    g_sound_player[7] = Mix_LoadWAV("music//step2.wav");
    g_sound_player[9] = Mix_LoadWAV("music//failed.wav");
    g_sound_exp[0] = Mix_LoadWAV("music//exp.wav");
    g_sound_player[1] = Mix_LoadWAV("music//Kha.wav"); // Âm thanh Kamehameha
    return success;
}

bool LoadBackground() {
    return g_background.LoadImg("img//mapsl.jpg", g_screen);
}

void close() {
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    SDL_DestroyWindow(g_window);
    g_screen = NULL;
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObjects*> MakeThreadList() {
    std::vector<ThreatsObjects*> list_threats;
    ThreatsObjects* dynamic_threats = new ThreatsObjects[20];
    for (int i = 0; i < 20; i++) {
        ThreatsObjects* p_threat = (dynamic_threats + i);
        if (p_threat) {
            p_threat->LoadImg("img//vgt_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObjects::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);
            p_threat->SetAnimationPos(p_threat->get_x_pos() - 60, p_threat->get_x_pos() - 60);
            p_threat->set_input_left(1);
            BulletObject* p_bullet = new BulletObject();
            p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

int main(int argc, char* argv[]) {
    ImpTimer fps_timer;
    if (!InitData() || !LoadBackground()) return -1;
    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);
    MainObject p_player;
    p_player.LoadImg("img//goku_walk_right.png", g_screen);
    p_player.set_clips();
    PlayerPower player_power;
    player_power.Init(g_screen);
    PlayerMoney player_money;
    player_money.Init(g_screen);
    PlayerMusic player_music;
    player_music.InitUnmute(g_screen);
    std::vector<ThreatsObjects*> threats_list = MakeThreadList();
    ExplosionObject exp_threat, exp_main;
    if (!exp_threat.LoadImg("img//exp3.png", g_screen) || !exp_main.LoadImg("img//exp3.png", g_screen)) return -1;
    exp_threat.set_clip();
    exp_main.set_clip();
    int num_die = 0;
    TextObject time_game, mark_game, money_game;
    time_game.SetColor(TextObject::WHITE_TEXT);
    mark_game.SetColor(TextObject::WHITE_TEXT);
    money_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_value = 0;
    bool is_quit = false;
    int retMenu = Menu::ShowMenu(g_screen, font_menu);
    if (retMenu == 1) is_quit = true;
    else if (retMenu == 2) {
        int t = 1;
        while (t == 1) {
            int retTuto = Menu::ShowTutorial(g_screen, font_tuto);
            if (retTuto == 0) {
                int retMenu1 = Menu::ShowMenu(g_screen, font_menu);
                if (retMenu1 == 1) { is_quit = true; t = 2; }
                else if (retMenu1 == 2) t = 1;
                else t = 2;
            }
        }
    }
    bool kamehameha_playing = false;// Trạng thái âm thanh Kamehameha
    while (!is_quit) {
        fps_timer.start();
        while (SDL_PollEvent(&g_event)) {
            if (g_event.type == SDL_QUIT) is_quit = true;
            p_player.HandleInputAction(g_event, g_screen, g_sound_player);
        }
        if (p_player.get_input_shoot() == 1 && !kamehameha_playing && !p_player.get_mute()) {
            Mix_PlayChannel(-1, g_sound_player[1], 0);
            kamehameha_playing = true;
        } else if (p_player.get_input_shoot() == 0) {
            kamehameha_playing = false;
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);
        g_background.Render(g_screen, NULL);
        Map map_data = game_map.getMap();
        p_player.HandleBullet(g_screen);
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data, g_sound_player);
        p_player.Show(g_screen);
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);
        GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
        ColorData color_data(36, 36, 36);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);
        GeometricFormat outlineSize(1, 1, SCREEN_WIDTH - 1, 40);
        ColorData color_data2(255, 255, 255);
        Geometric::RenderOutLine(outlineSize, color_data2, g_screen);
        player_power.Show(g_screen);
        player_money.Show(g_screen);
        if (!p_player.get_mute()) {
            player_music.InitUnmute(g_screen);
            player_music.Show(g_screen);
        } else {
            player_music.InitMute(g_screen);
            player_music.Show(g_screen);
        }
        for (int i = 0; i < threats_list.size(); i++) {
            ThreatsObjects* p_threat = threats_list.at(i);
            if (p_threat) {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen, map_data);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);
                SDL_Rect rect_player = p_player.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int ii = 0; ii < tBullet_list.size(); ii++) {
                    BulletObject* pt_bullet = tBullet_list.at(ii);
                    if (pt_bullet && SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player)) {
                        if (!p_player.get_mute()) Mix_PlayChannel(-1, g_sound_player[3], 0);
                        if (num_die > 3) { p_threat->RemoveBullet(ii); break; }
                        bCol1 = true;
                    }
                }
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                if (bCol2 || bCol1 || p_player.die) {
                    if (!p_player.get_mute()) Mix_PlayChannel(-1, g_sound_player[3], 0);
                    int width_exp_frame = exp_main.get_frame_width();
                    int height_exp_frame = exp_main.get_frame_height();
                    for (int ex = 0; ex < 8; ex++) {
                        int x_pos2 = p_player.GetRect().x + exp_main.get_frame_width() * 0.5 - width_exp_frame * 0.5;
                        int y_pos2 = p_player.GetRect().y + exp_main.get_frame_height() * 0.5 - height_exp_frame * 0.5;
                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos2, y_pos2);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                    }
                    num_die += p_player.die ? p_player.die : 1;
                    p_player.die = 0;
                    if (num_die < 3) {
                        p_player.SetRect(0, 0);
                        p_player.set_comeback_time(60);
                        SDL_Delay(800);
                        player_power.Decrease();
                        player_power.Render(g_screen);
                        continue;
                    } else {
                        if (Menu::ShowRestart(g_screen, font_menu) == 1) is_quit = true;
                    }
                }
            }
        }
        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0; r < bullet_arr.size(); r++) {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet) {
                for (int t = 0; t < threats_list.size(); t++) {
                    ThreatsObjects* obj_threat = threats_list.at(t);
                    if (obj_threat) {
                        SDL_Rect tRect = {obj_threat->GetRect().x, obj_threat->GetRect().y, obj_threat->get_width_frame(), obj_threat->get_height_frame()};
                        SDL_Rect bRect = p_bullet->GetRect();
                        if (SDLCommonFunc::CheckCollision(bRect, tRect)) {
                            if (!p_player.get_mute()) Mix_PlayChannel(-1, g_sound_exp[0], 0);
                            mark_value += 10;
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;
                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }
                            p_player.RemoveBullet(r);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }
        std::string str_time = "TIME : ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;
        if (val_time <= 0) {
            if (MessageBox(NULL, "FF", "Info", MB_OK | MB_ICONSTOP) == IDOK) is_quit = true;
        } else {
            str_time += std::to_string(val_time);
            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.SetRect(SCREEN_WIDTH - 200, 15);
            time_game.RenderText(g_screen);
        }
        std::string strMark = "YOUR MARK: " + std::to_string(mark_value);
        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.SetRect(SCREEN_WIDTH * 0.5 - 50, 15);
        mark_game.RenderText(g_screen);
        int money_count = p_player.GetMoneyCount();
        money_game.SetText(std::to_string(money_count));
        money_game.LoadFromRenderText(font_time, g_screen);
        money_game.SetRect(SCREEN_WIDTH * 0.5 - 250, 15);
        money_game.RenderText(g_screen);
        SDL_RenderPresent(g_screen);
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000 / FRAME_PER_SECOND;
        if (real_imp_time < time_one_frame) {
            int delay_time = time_one_frame - real_imp_time;
            if (delay_time >= 0) SDL_Delay(delay_time);
        }
    }
    for (int i = 0; i < threats_list.size(); i++) {
        ThreatsObjects* p_threat = threats_list.at(i);
        if (p_threat) {
            p_threat->Free();
            p_threat = NULL;
        }
    }

    return 0;
}
