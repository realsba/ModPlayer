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
    auto period = _channel.getPeriod();

    _period[0] = period;
    _period[1] = period * _fineTuneFactors[x];
    _period[2] = period * _fineTuneFactors[y];
}

void Arpeggio::apply()
{
    _channel.setPeriod(_period[_module.getTickCounter() % 3]);
}
