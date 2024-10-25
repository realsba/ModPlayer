#ifndef VOLUMESLIDE_HPP
#define VOLUMESLIDE_HPP

#include "Effect.hpp"

#include <cstdint>

class Channel;

class VolumeSlide final : public Effect {
public:
    explicit VolumeSlide(Channel& channel);

    void init(uint8_t x, uint8_t y);
    void apply() override;

private:
    Channel& _channel;
    int8_t _delta {0};
};

#endif // VOLUMESLIDE_HPP
