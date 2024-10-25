#include "CombinedEffect.hpp"

void CombinedEffect::init(Effect* primary, Effect* secondary)
{
    _primary   = primary;
    _secondary = secondary;
}

void CombinedEffect::apply()
{
    if (_primary) {
        _primary->apply();
    }
    if (_secondary) {
        _secondary->apply();
    }
}
