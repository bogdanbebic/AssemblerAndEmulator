#include "Psw.hpp"

bool emulator::system::cpu::Psw::psw_read(const PswMasks bit) const
{
    return (this->psw_ & static_cast<word_t>(bit)) != 0;
}

void emulator::system::cpu::Psw::psw_write(const PswMasks bit, const bool value)
{
    if (value)
        this->psw_set(bit);
    else
        this->psw_clear(bit);
}

emulator::system::word_t emulator::system::cpu::Psw::get() const
{
    return this->psw_;
}

void emulator::system::cpu::Psw::set(word_t psw)
{
    this->psw_ = psw;
}

void emulator::system::cpu::Psw::psw_clear(const PswMasks bit)
{
    this->psw_ &= ~static_cast<word_t>(bit);
}

void emulator::system::cpu::Psw::psw_set(const PswMasks bit)
{
    this->psw_ |= static_cast<word_t>(bit);
}
