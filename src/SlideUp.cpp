#include "SlideUp.hpp"

#include "Channel.hpp"

SlideUp::SlideUp(Channel& channel)
    : _channel(channel)
{
}

void SlideUp::init(uint8_t delta)
{
    _delta = delta;
}

void SlideUp::apply()
{
    _channel.setPeriod(_channel.getPeriod() - _delta);
}
