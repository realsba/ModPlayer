#include "Channel.hpp"

#include <iostream>

std::string toString(Note::Effect effect)
{
    switch (effect) {
        case Note::Effect::Arpeggio: return "Arpeggio";
        case Note::Effect::SlideUp: return "Slide Up";
        case Note::Effect::SlideDown: return "Slide Down";
        case Note::Effect::SlideToNote: return "Slide to note";
        case Note::Effect::Vibrato: return "Vibrato";
        case Note::Effect::SlideToNoteVolumeSlide: return "Tone Portamento & Volume Slide";
        case Note::Effect::VibratoVolumeSlide: return "Vibrato & Volume Slide";
        case Note::Effect::Tremolo: return "Tremolo";
        case Note::Effect::SetPanningPosition: return "Set Panning Position";
        case Note::Effect::SetSampleOffset: return "Set Sample Offset";
        case Note::Effect::VolumeSlide: return "Volume Slide";
        case Note::Effect::PositionJump: return "Position Jump";
        case Note::Effect::SetVolume: return "Set Volume";
        case Note::Effect::PatternBreak: return "Pattern Break";
        case Note::Effect::ExtendedEffects: return "Extended Effects";
        case Note::Effect::SetSpeed: return "Set Speed";
        default: return "Unknown Effect";
    }
}

template <typename T, typename... Args>
auto& lazyInit(std::unique_ptr<T>& ptr, Args&&... args)
{
    if (!ptr) {
        ptr = std::make_unique<T>(std::forward<Args>(args)...);
    }
    return ptr;
}

Channel::Channel(Module& module, std::vector<Instrument>& instruments, uint32_t mixerFrequency)
    : _module(module)
    , _instruments(instruments)
    , _mixerFrequency(mixerFrequency)
{
}

void Channel::setFrequency(uint16_t period)
{
    _sampleStep = period > 0 ? 3546895.0 / (period * _mixerFrequency) : 0;
}

uint16_t Channel::getPeriod() const
{
    return _period;
}

void Channel::setPeriod(uint16_t value)
{
    _period = value;
    setFrequency(_period);
}

uint8_t Channel::getVolume() const
{
    return _volume;
}

void Channel::setVolume(uint8_t value)
{
    _volume = value <= MAX_VOLUME ? value : MAX_VOLUME;
}

int16_t Channel::getFrame()
{
    if (!_instrument || _samplePosition >= _instrument->sampleLength) {
        return 0;
    }

    const auto scale  = AMPLITUDE_SCALE * _volume / VOLUME_SCALE;
    const auto output = static_cast<int16_t>(_instrument->sampleData[static_cast<int>(_samplePosition)] * scale);

    _samplePosition += _sampleStep;

    // TODO: Implement full playback from start to finish on first run
    if (_instrument->loopEnd > _instrument->loopStart && _samplePosition >= _instrument->loopEnd) {
        _samplePosition = _instrument->loopStart;
    }

    return output;
}

void Channel::tick()
{
    if (!_instrument || _period == 0) {
        return;
    }

    if (_effect) {
        _effect->apply();
    }
}

void Channel::update(const Note& note)
{
    if (note.effectValue) {
        std::cout << toString(note.effect) << std::endl;
    }

    if (note.period != 0) {
        if (note.effect == Note::Effect::SlideToNote) {
            // TODO: implement
        } else {
            _samplePosition = 0;
            setPeriod(note.period);
        }
    }

    if (note.instrument != 0) {
        _instrument = &_instruments[note.instrument - 1];
        _volume     = _instrument->volume;
        if (note.effect == Note::Effect::SlideToNote) {
            // TODO: Implement full playback from start to finish on first run
        } else {
            _samplePosition = 0;
        }
    }

    switch (note.effect) {
        case Note::Effect::Arpeggio:
            if (note.effectValue) {
                lazyInit(_arpeggio, _module, *this)->init(note.getEffectValueUpper(), note.getEffectValueLower());
                _effect = _arpeggio.get();
            } else {
                _effect = nullptr;
            }
            break;
        case Note::Effect::SlideUp:
            lazyInit(_slideUp, *this)->init(note.effectValue);
            _effect = _slideUp.get();
            break;
        case Note::Effect::SlideDown:
            lazyInit(_slideDown, *this)->init(note.effectValue);
            _effect = _slideUp.get();
            break;
        case Note::Effect::SlideToNote:
            lazyInit(_slideToNote, *this)->init(note.effectValue, note.period);
            _effect = _slideToNote.get();
            break;
        case Note::Effect::Vibrato:
            lazyInit(_vibrato, *this)->init(note.getEffectValueUpper(), note.getEffectValueLower());
            _effect = _vibrato.get();
            break;
        case Note::Effect::SlideToNoteVolumeSlide:
            lazyInit(_volumeSlide, *this)->init(note.getEffectValueUpper(), note.getEffectValueLower());
            lazyInit(_slideToNoteVolumeSlide)->init(_slideToNote.get(), _volumeSlide.get());
            _effect = _slideToNoteVolumeSlide.get();
            break;
        case Note::Effect::VibratoVolumeSlide:
            lazyInit(_volumeSlide, *this)->init(note.getEffectValueUpper(), note.getEffectValueLower());
            lazyInit(_vibratoVolumeSlide)->init(_vibrato.get(), _volumeSlide.get());
            _effect = _vibratoVolumeSlide.get();
            break;
        case Note::Effect::SetSampleOffset:
            _samplePosition += note.effectValue * 256;
            break;
        case Note::Effect::VolumeSlide:
            lazyInit(_volumeSlide, *this)->init(note.getEffectValueUpper(), note.getEffectValueLower());
            _effect = _volumeSlide.get();
            break;
        case Note::Effect::SetVolume:
            _volume = note.effectValue;
            break;
        default: ;
    }
}

