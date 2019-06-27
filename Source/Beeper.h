//
// Created by Angel Paunov Georgiev on 2019-06-25.
//

#ifndef CPP_PING_PONG_BEEPER_H
#define CPP_PING_PONG_BEEPER_H

#include <queue>
#include <cmath>
#include <SDL.h>

const int AMPLITUDE = 28000;
const int FREQUENCY = 44100;

struct BeepObject {
    double freq;
    int samplesLeft;
};

class Beeper {

  private:

    double v;
    std::queue<BeepObject> beeps;

  public:
    Beeper();
    ~Beeper();
    void Beep(double freq, int duration);
    void GenerateSamples(Sint16* stream, int length);
    void Wait();
};

void audio_callback(void*, Uint8*, int);

#endif //CPP_PING_PONG_BEEPER_H
