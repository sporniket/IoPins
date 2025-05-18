/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/

// ================[BEGIN typical specialization]==================
class ConcreteBinaryInputPin final : public BinaryInputPin {
  public:
    ~ConcreteBinaryInputPin() {}
    ConcreteBinaryInputPin(uint8_t index, BoolValue* value) : BinaryInputPin(index), value(value) {}

  private:
    BoolValue* value;

    virtual std::expected<bool, IoFailureReason> doRead() noexcept { return value->value; }
};
// ================[END typical specialization]==================

Test(InputPin, readable_pin_is_enabled_readable_not_writable) {
    BoolValue mockValue{true};
    ConcreteBinaryInputPin p(42, &mockValue);

    // verify predicates
    cr_assert(p.isReadable());
    cr_assert(p.isNotWritable());
    cr_assert(p.isEnabled());
    cr_assert_not(p.isNotReadable());
    cr_assert_not(p.isWritable());
    cr_assert_not(p.isDisabled());

    // verify id
    cr_assert_eq(p.getPinId(), 42);

    // verify read
    auto readResult = p.read();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), true);

    // verify read to get another value
    mockValue.value = false;
    readResult = p.read();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), false);
}
