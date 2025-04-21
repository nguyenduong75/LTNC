#include "ImpTimer.h"
#include "BaseObject.h"

ImpTimer::ImpTimer()
{
    start_tick_ = 0;
    paused_tick_ = 0;
    is_paused_ = false;
    is_started_ = false;
}

ImpTimer::~ImpTimer()
{
}

void ImpTimer::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop()
{
    is_started_ = false;
    is_paused_ = false;
}

void ImpTimer::paused()
{
    if (is_started_ && !is_paused_) // Chưa tạm dừng
    {
        is_paused_ = true;
        paused_tick_ = SDL_GetTicks() - start_tick_; // Thời gian hiện tại - thời gian đã trôi
    }
}

void ImpTimer::unpaused()
{
    if (is_paused_)
    {
        is_paused_ = false;
        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0;
    }
}

int ImpTimer::get_ticks()
{
    if (is_started_)
    {
        if (is_paused_)
            return paused_tick_;
        else
            return SDL_GetTicks() - start_tick_;
    }
    return 0;
}

bool ImpTimer::is_started()
{
    return is_started_;
}

bool ImpTimer::is_paused()
{
    return is_paused_;
}