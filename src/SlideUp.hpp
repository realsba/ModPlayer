#ifndef SLIDEUP_HPP
#define SLIDEUP_HPP

#include "Effect.hpp"

#include <cstdint>

class Channel;

class SlideUp final : public Effect {
public:
    explicit SlideUp(Channel& channel);

    void init(uint8_t delta);
    void apply() override;

private:
    Channel& _channel;
    uint8_t _delta {0};
};

#endif // SLIDEUP_HPP
