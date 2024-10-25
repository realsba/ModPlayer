#ifndef ARPEGGIO_HPP
#define ARPEGGIO_HPP

#include "Effect.hpp"

#include <array>
#include <cstdint>
#include <cmath>

class Module;
class Channel;

class Arpeggio final : public Effect {
public:
    Arpeggio(Module& module, Channel& channel);

    void init(int x, int y);
    void apply() override;

private:
    static constexpr int MAX_FINE_TUNE = 16;

    static constexpr std::array<double, MAX_FINE_TUNE> _fineTuneFactors = []
    {
        auto halfToneFactor = std::pow(2.0, -1.0 / (12.0 * 8.0));
        std::array<double, MAX_FINE_TUNE> factors {};
        for (int i = 0; i < MAX_FINE_TUNE; ++i) {
            factors[i] = std::pow(halfToneFactor, i);
        }
        return factors;
    }();

    Module& _module;
    Channel& _channel;
    uint16_t _period[3] {};
};

#endif // ARPEGGIO_HPP
