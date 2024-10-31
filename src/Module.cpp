#include "Module.hpp"

template <typename T>
T bigEndianToNative(T value)
{
    static_assert(std::is_integral_v<T>, "bigEndianToNative: only integral types are supported");

    if constexpr (std::endian::native == std::endian::little) {
        return std::byteswap(value);
    }
    return value;
}

Module::Module(uint32_t mixerFrequency)
    : _mixerFrequency(mixerFrequency)
{
}

void Module::load(const std::string& fileName)
{
    unsigned char buffer[4];

    _file.open(fileName, std::ios::binary);
    if (!_file) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }

    // skip module title
    _file.seekg(20);

    // TODO: Use the appropriate number of channels based on the MOD file format tag
    _channels.clear();
    for (size_t i = 0; i < 4; ++i) {
        _channels.push_back(std::make_unique<Channel>(*this, _instruments, _mixerFrequency));
    }

    for (auto& instrument : _instruments) {
        // skip sample name
        _file.seekg(22, std::ios_base::cur);

        uint16_t value;

        _file.read(reinterpret_cast<char*>(&value), 2);
        instrument.sampleLength = bigEndianToNative(value) * 2;

        _file.read(reinterpret_cast<char*>(&instrument.fineTune), 1);
        _file.read(reinterpret_cast<char*>(&instrument.volume), 1);

        _file.read(reinterpret_cast<char*>(&value), 2);
        instrument.loopStart = bigEndianToNative(value) * 2;

        _file.read(reinterpret_cast<char*>(&value), 2);
        value = bigEndianToNative(value) * 2;
        if (value == 2) {
            value = 0;
        }
        instrument.loopEnd = instrument.loopStart + value;
    }

    _file.seekg(950);
    _file.read(reinterpret_cast<char*>(&_songLength), 1);
    _file.read(reinterpret_cast<char*>(&_restartPosition), 1);

    _patternOrder.resize(_songLength);
    _file.read(reinterpret_cast<char*>(_patternOrder.data()), _songLength);
    const auto patternCount = *std::max_element(_patternOrder.begin(), _patternOrder.end()) + 1;

    // mod file format tag
    _file.seekg(1080);
    _file.read(reinterpret_cast<char*>(buffer), 4);

    _patterns = std::make_unique<Pattern[]>(patternCount);
    for (int pattern = 0; pattern < patternCount; ++pattern) {
        for (int row = 0; row < MAX_ROWS; ++row) {
            for (auto& channel : _patterns[pattern].rows) {
                _file.read(reinterpret_cast<char*>(buffer), 4);
                auto& note       = channel[row];
                note.instrument  = (buffer[0] & 0xF0) | (buffer[2] >> 4);
                note.period      = (buffer[0] & 0x0F) << 8 | buffer[1];
                note.effect      = static_cast<Note::Effect>(buffer[2] & 0x0F);
                note.effectValue = buffer[3];
            }
        }
    }

    for (auto& instrument : _instruments) {
        instrument.sampleData = std::make_unique<char[]>(instrument.sampleLength);
        _file.read(instrument.sampleData.get(), instrument.sampleLength);
    }

    updateRow();
}

int16_t Module::getFrame()
{
    int32_t output = 0;

    for (const auto& channel : _channels) {
        output += channel->getFrame();
    }

    if (--_frameCounter <= 0) {
        _frameCounter += _mixerFrequency * 2.5 / _bpm;
        if (++_tickCounter == _speed) {
            _tickCounter = 0;
            nextRow();
        }
        for (const auto& channel : _channels) {
            channel->tick();
        }
    }

    return static_cast<int16_t>(std::clamp(
        output,
        static_cast<int32_t>(std::numeric_limits<int16_t>::min()),
        static_cast<int32_t>(std::numeric_limits<int16_t>::max())
    ));
}

uint32_t Module::getTickCounter() const
{
    return _tickCounter;
}

void Module::updateRow()
{
    const auto& [rows] = _patterns[_patternOrder[_patternOrderIndex]];

    for (int channel = 0; channel < 4; ++channel) {
        const auto& note = rows[channel][_rowIndex];

        _channels[channel]->update(note);

        if (note.effect == Note::Effect::PatternBreak) {
            _patternBreakRowIndex = static_cast<int8_t>(
                std::clamp(10 * note.getEffectValueUpper() + note.getEffectValueLower(), 0, MAX_ROWS - 1)
            );
        } else if (note.effect == Note::Effect::SetSpeed) {
            if (note.effectValue < 32) {
                _speed = note.effectValue;
            } else {
                _bpm = note.effectValue;
            }
        }
    }
}

void Module::nextRow()
{
    static auto updateIndexes = [&](int newRowIndex)
    {
        _rowIndex = newRowIndex;
        if (++_patternOrderIndex >= _songLength) {
            _patternOrderIndex = 0;
        }
    };

    if (_patternBreakRowIndex) {
        updateIndexes(_patternBreakRowIndex.value());
        _patternBreakRowIndex.reset();
    } else if (++_rowIndex >= MAX_ROWS) {
        updateIndexes(0);
    }

    updateRow();
}

