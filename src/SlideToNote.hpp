#ifndef SLIDETONOTE_HPP
#define SLIDETONOTE_HPP

#include "Effect.hpp"

#include <cstdint>

class Channel;

class SlideToNote final : public Effect {
public:
    explicit SlideToNote(Channel& channel);

    void init(uint8_t delta, uint16_t destPeriod);
    void apply() override;

private:
    Channel& _channel;
    uint16_t _destPeriod {0};
    uint8_t _delta {0};
};

#endif // SLIDETONOTE_HPP
