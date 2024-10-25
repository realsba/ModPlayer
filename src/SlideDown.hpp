#ifndef SLIDEDOWN_HPP
#define SLIDEDOWN_HPP

#include "Effect.hpp"

#include <cstdint>

class Channel;

class SlideDown final : public Effect {
public:
    explicit SlideDown(Channel& channel);

    void init(uint8_t delta);
    void apply() override;

private:
    Channel& _channel;
    uint8_t _delta {0};
};

#endif // SLIDEDOWN_HPP
