#include "SlideDown.hpp"

#include "Channel.hpp"

SlideDown::SlideDown(Channel& channel)
    : _channel(channel)
{
}

void SlideDown::init(uint8_t delta)
{
    _delta = delta;
}

void SlideDown::apply()
{
    _channel.setPeriod(_channel.getPeriod() + _delta);
}
