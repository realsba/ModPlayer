#ifndef EFFECT_HPP
#define EFFECT_HPP

class Effect {
public:
    virtual ~Effect() = default;
    virtual void apply() = 0;
};

#endif // EFFECT_HPP
