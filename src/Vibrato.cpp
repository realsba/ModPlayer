#include "Vibrato.hpp"

#include "Channel.hpp"

Vibrato::Vibrato(Channel& channel)
    : _channel(channel)
{
}

void Vibrato::init(uint8_t rate, uint8_t depth)
{
    _rate = rate;
    _depth = depth;
}

void Vibrato::apply()
{
    // TODO: implement
}
