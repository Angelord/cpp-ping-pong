//
// Created by Angel Paunov Georgiev on 2019-06-23.
//

#ifndef CPP_PING_PONG_TIMER_H
#define CPP_PING_PONG_TIMER_H


class Timer {

    bool started;
    bool paused;
    unsigned startTicks;    // Time when the timer was started
    unsigned pausedTicks;   // Time when the timer was paused

  public:

    Timer();

    void Start();
    void Stop();
    void Pause();
    void Unpause();

    unsigned GetTicks();

    bool IsStarted() const { return started; }
    bool IsPaused() const { return paused; }
};


#endif //CPP_PING_PONG_TIMER_H
