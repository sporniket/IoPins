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
class ConcreteOutputPinTrio final : public cmspk::iopins::OutputPinTrio {
  public:
    ~ConcreteOutputPinTrio() {}
    ConcreteOutputPinTrio(std::array<uint8_t,3> indices, uint8_t* value) : cmspk::iopins::OutputPinTrio(indices), value(value) {}

  private:
    uint8_t* value;

    virtual std::expected<void, IoFailureReason> checkWritability() noexcept { return std::expected<void, IoFailureReason>(); }
    virtual std::expected<void, IoFailureReason> doWrite(std::bitset<3> valueToWrite) noexcept { (*value) = valueToWrite.to_ulong() ; return std::expected<void, IoFailureReason>(); }
};
// ================[END typical specialization]==================

Test(OutputPinGroup, can_write_multiple_pin) {
    uint8_t mockValue{0}; // expected bit set : [0,1,1] from LSB to MSB
    ConcreteOutputPinTrio p({1,42,5}, &mockValue);

    // verify predicates
    cr_assert(p.isNotReadable());
    cr_assert(p.isWritable());
    cr_assert(p.isEnabled());
    cr_assert_not(p.isReadable());
    cr_assert_not(p.isNotWritable());
    cr_assert_not(p.isDisabled());

    // verify ids
    cr_assert_eq(p.getPinIds()[0], 1);
    cr_assert_eq(p.getPinIds()[1], 42);
    cr_assert_eq(p.getPinIds()[2], 5);

    // verify read
    auto writeResults = p.write(0b110); // expected bit set : [0,1,1] from LSB to MSB
    cr_assert(writeResults.has_value());
    cr_assert_eq(mockValue, 6);

    // verify read to get another value
    mockValue = 0 ; // reset mock
    writeResults = p.write(0b011); // expected bit set : [1,1,0] from LSB to MSB
    cr_assert(writeResults.has_value());
    cr_assert_eq(mockValue, 3);

    // verify read to get another value
    mockValue = 0 ; // reset mock
    writeResults = p.write(0b1011); // expected bit 3 and beyond to be ignored
    cr_assert(writeResults.has_value());
    cr_assert_eq(mockValue, 3);
}
