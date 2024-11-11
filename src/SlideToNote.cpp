#include "SlideToNote.hpp"

#include "Channel.hpp"

SlideToNote::SlideToNote(Channel& channel)
    : _channel(channel)
{
}

void SlideToNote::init(uint8_t delta, uint16_t destPeriod)
{
    if (destPeriod) {
        _destPeriod = destPeriod;
    }
    if (delta) {
        _delta = delta;
    }
}

void SlideToNote::apply()
{
    auto period = _channel.getPeriod();

    if (period < _destPeriod) {
        period += _delta;
        if (period > _destPeriod) {
            period = _destPeriod;
        }
        _channel.setPeriod(period);
    } else if (period > _destPeriod) {
        period -= _delta;
        if (period < _destPeriod) {
            period = _destPeriod;
        }
        _channel.setPeriod(period);
    }
}
