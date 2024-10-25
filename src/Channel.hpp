#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Arpeggio.hpp"
#include "SlideUp.hpp"
#include "SlideDown.hpp"
#include "Vibrato.hpp"
#include "SlideToNote.hpp"
#include "VolumeSlide.hpp"
#include "CombinedEffect.hpp"

#include <cstdint>
#include <memory>
#include <vector>

struct Instrument {
    std::unique_ptr<char[]> sampleData;
    int32_t sampleLength;
    int32_t loopStart;
    int32_t loopEnd;
    uint8_t fineTune;
    uint8_t volume;
};

struct Note {
    enum class Effect : uint8_t {
        Arpeggio               = 0x0,
        SlideUp                = 0x1,
        SlideDown              = 0x2,
        SlideToNote            = 0x3,
        Vibrato                = 0x4,
        SlideToNoteVolumeSlide = 0x5,
        VibratoVolumeSlide     = 0x6,
        Tremolo                = 0x7,
        SetPanningPosition     = 0x8,
        SetSampleOffset        = 0x9,
        VolumeSlide            = 0xA,
        PositionJump           = 0xB,
        SetVolume              = 0xC,
        PatternBreak           = 0xD,
        ExtendedEffects        = 0xE,
        SetSpeed               = 0xF
    };

    enum class ExtendedEffect {
        SetFilter           = 0x0,
        FineSlideUp         = 0x1,
        FineSlideDown       = 0x2,
        GlissandoControl    = 0x3,
        SetVibratoWaveform  = 0x4,
        SetFineTune         = 0x5,
        SetJumpToLoop       = 0x6,
        SetTremoloWaveform  = 0x7,
        RetrigNote          = 0x9,
        FineVolumeSlideUp   = 0xA,
        FineVolumeSlideDown = 0xB,
        NoteCut             = 0xC,
        NoteDelay           = 0xD,
        PatternDelay        = 0xE,
        InvertLoop          = 0xF
    };

    [[nodiscard]] auto getEffectValueUpper() const { return effectValue >> 4; }
    [[nodiscard]] auto getEffectValueLower() const { return effectValue & 15; }

    uint16_t period: 12;
    Effect effect  : 4;
    uint8_t instrument;
    uint8_t effectValue;
};

class Channel {
public:
    explicit Channel(Module& module, std::vector<Instrument>& instruments, uint32_t mixerFrequency);

    void setFrequency(uint16_t period);

    [[nodiscard]] uint16_t getPeriod() const;
    void setPeriod(uint16_t value);
    [[nodiscard]] uint8_t getVolume() const;
    void setVolume(uint8_t value);

    int16_t getFrame();
    void tick();
    void update(const Note& note);

private:
    static constexpr double AMPLITUDE_SCALE = 63.0;
    static constexpr uint8_t MAX_VOLUME     = 64;
    static constexpr double VOLUME_SCALE    = MAX_VOLUME;
    static constexpr int MAX_SAMPLE_VALUE   = 32767;

    Module& _module;
    const std::vector<Instrument>& _instruments;
    std::unique_ptr<Arpeggio> _arpeggio;
    std::unique_ptr<SlideUp> _slideUp;
    std::unique_ptr<SlideDown> _slideDown;
    std::unique_ptr<SlideToNote> _slideToNote;
    std::unique_ptr<Vibrato> _vibrato;
    std::unique_ptr<CombinedEffect> _slideToNoteVolumeSlide;
    std::unique_ptr<CombinedEffect> _vibratoVolumeSlide;
    std::unique_ptr<VolumeSlide> _volumeSlide;

    double _samplePosition {0};
    double _sampleStep {0};
    Effect* _effect {nullptr};
    const Instrument* _instrument {nullptr};
    const uint32_t _mixerFrequency {0};

    uint16_t _period {0};
    uint8_t _volume {MAX_VOLUME};
};

std::string toString(Note::Effect effect);

#endif // CHANNEL_HPP
