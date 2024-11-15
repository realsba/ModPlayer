#include "Arpeggio.hpp"

#include "Module.hpp"
#include "Channel.hpp"

Arpeggio::Arpeggio(Module& module, Channel& channel)
    : _module(module)
    , _channel(channel)
{
}

void Arpeggio::init(int x, int y)
{
    const auto period = _channel.getPeriod();

    _period[0] = period;
    _period[1] = static_cast<uint16_t>(period * FINE_TUNE_FACTORS[x]);
    _period[2] = static_cast<uint16_t>(period * FINE_TUNE_FACTORS[y]);
}

void Arpeggio::apply()
{
    _channel.setPeriod(_period[_module.getTickCounter() % 3]);
}
