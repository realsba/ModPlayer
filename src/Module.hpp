#ifndef MODULE_HPP
#define MODULE_HPP

#include "Channel.hpp"

#include <fstream>
#include <memory>
#include <string>

constexpr uint8_t MAX_ROWS        = 64;
constexpr uint8_t MAX_INSTRUMENTS = 31;

struct Pattern {
    Note rows[4][MAX_ROWS];
};

class Module {
public:
    explicit Module(uint32_t mixerFrequency);

    void load(const std::string& fileName);

    int16_t getFrame();
    uint32_t getTickCounter() const;

private:
    void updateRow();
    void nextRow();

    std::ifstream _file;
    std::vector<std::unique_ptr<Channel>> _channels;
    std::vector<Instrument> _instruments {MAX_INSTRUMENTS};
    std::vector<uint8_t> _patternOrder;
    std::unique_ptr<Pattern[]> _patterns {nullptr};
    double _frameCounter {0};
    const uint32_t _mixerFrequency {0};
    std::optional<int8_t> _patternBreakRowIndex {-1};
    uint32_t _tickCounter {0};
    uint8_t _rowIndex {0};
    uint8_t _songLength {0};               // Song length in patterns (0-80h)
    uint8_t _restartPosition {0};          // Restart byte for song looping
    uint8_t _patternOrderIndex {0};
    uint8_t _speed {6};
    uint8_t _bpm {125};
};

#endif // MODULE_HPP
