#include "Vibrato.hpp"

#include "Channel.hpp"

Vibrato::Vibrato(Channel& channel)
    : _channel(channel)
{
}

void Vibrato::init(uint8_t speed, uint8_t depth)
{
    _speed = speed;
    _depth = depth;
}

void Vibrato::apply()
{
    const auto data = SINE_TABLE[_position] * _depth / 128;
    _position = (_position + _speed) % SINE_TABLE_SIZE;
    _channel.setFrequency(_channel.getPeriod() + data);
}
