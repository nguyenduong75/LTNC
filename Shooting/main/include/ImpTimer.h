#ifndef IMP_TIMER_H
#define IMP_TIMER_H

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_paused();
    bool is_started();

private:
    int start_tick_; // Thời gian bắt đầu
    int paused_tick_; // Thời gian tạm dừng

    bool is_paused_; // Trạng thái tạm dừng
    bool is_started_; // Trạng thái bắt đầu
};

#endif // IMP_TIMER_H