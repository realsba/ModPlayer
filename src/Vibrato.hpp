#ifndef VIBRATO_HPP
#define VIBRATO_HPP

#include "Effect.hpp"

#include <cstdint>
#include <cmath>
#include <array>
#include <iostream>

class Channel;

class Vibrato final : public Effect {
public:
    explicit Vibrato(Channel& channel);

    void init(uint8_t rate, uint8_t depth);
    void apply() override;

private:
    static constexpr int SINE_TABLE_SIZE = 64;
    static constexpr int SINE_TABLE_SCALE = 255;
    static constexpr std::array<int16_t, SINE_TABLE_SIZE> SINE_TABLE = []
    {
        std::array<int16_t, SINE_TABLE_SIZE> sineTable {};
        for (int i = 0; i < SINE_TABLE_SIZE; ++i) {
            sineTable[i] = static_cast<int16_t>(SINE_TABLE_SCALE * std::sin(2 * M_PI * i / SINE_TABLE_SIZE));
        }
        return sineTable;
    }();

    Channel& _channel;
    uint8_t _speed {0};
    uint8_t _depth {0};
    uint8_t _position {0};
};

#endif // VIBRATO_HPP
