/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/

// ================[BEGIN typical specialization]==================
#include <cstdint>
class ConcreteInputPinTrio final : public cmspk::iopins::InputPinTrio {
  public:
    ~ConcreteInputPinTrio() {}
    ConcreteInputPinTrio(std::array<uint8_t,3> indices, uint8_t* value) : cmspk::iopins::InputPinTrio(indices), value(value) {}

  private:
    uint8_t* value;

    virtual std::expected<void, IoFailureReason> checkReadability() noexcept { return std::expected<void, IoFailureReason>(); }
    virtual std::expected<std::bitset<3>, IoFailureReason> doRead() noexcept { return std::bitset<3>(*value); }
};
// ================[END typical specialization]==================

Test(InputPinGroup, can_read_multiple_pin) {
    uint8_t mockValue{6}; // expected bit set : [0,1,1] from LSB to MSB
    ConcreteInputPinTrio p({1,42,5}, &mockValue);

    // verify predicates
    cr_assert(p.isReadable());
    cr_assert(p.isNotWritable());
    cr_assert(p.isEnabled());
    cr_assert_not(p.isNotReadable());
    cr_assert_not(p.isWritable());
    cr_assert_not(p.isDisabled());

    // verify ids
    cr_assert_eq(p.getPinIds()[0], 1);
    cr_assert_eq(p.getPinIds()[1], 42);
    cr_assert_eq(p.getPinIds()[2], 5);

    // verify read
    auto readResult = p.read();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value()[0], false);
    cr_assert_eq(readResult.value()[1], true);
    cr_assert_eq(readResult.value()[2], true);

    // verify read to get another value
    mockValue = 3; // expected bit set : [1,1,0] from LSB to MSB
    readResult = p.read();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value()[0], true);
    cr_assert_eq(readResult.value()[1], true);
    cr_assert_eq(readResult.value()[2], false);
}
