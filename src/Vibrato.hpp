#ifndef VIBRATO_HPP
#define VIBRATO_HPP

#include "Effect.hpp"

#include <cstdint>

class Channel;

class Vibrato final : public Effect {
public:
    explicit Vibrato(Channel& channel);

    void init(uint8_t rate, uint8_t depth);
    void apply() override;

private:
    Channel& _channel;
    uint8_t _rate {0};
    uint8_t _depth {0};
};

#endif // VIBRATO_HPP
