#ifndef COMBINEDEFFECT_HPP
#define COMBINEDEFFECT_HPP

#include "Effect.hpp"

class CombinedEffect final : public Effect {
public:
    void init(Effect* primary, Effect* secondary);
    void apply() override;

private:
    Effect* _primary {nullptr};
    Effect* _secondary {nullptr};
};

#endif // COMBINEDEFFECT_HPP
