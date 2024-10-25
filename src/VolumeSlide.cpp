#include "VolumeSlide.hpp"

#include "Channel.hpp"

VolumeSlide::VolumeSlide(Channel& channel)
    : _channel(channel)
{
}

void VolumeSlide::init(uint8_t x, uint8_t y)
{
    _delta = x ? static_cast<int8_t>(x) : static_cast<int8_t>(-y);
}

void VolumeSlide::apply()
{
    _channel.setVolume(std::clamp(_channel.getVolume() + _delta, 0, 64));
}
