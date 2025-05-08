/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/

// ================[BEGIN typical specialization]==================
class ConcreteBinaryIoPin final : public BinaryIoPin {
  public:
    ~ConcreteBinaryIoPin() {}
    ConcreteBinaryIoPin(uint8_t index, IoDirection direction, BoolValue* value) : BinaryIoPin(index, direction), value(value) {}

  private:
    BoolValue* value;

    virtual std::expected<bool, IoFailureReason> doRead() noexcept { return value->value; }
    virtual std::expected<void, IoFailureReason> doWrite(const bool value) noexcept {
        this->value->value = value;
        return std::expected<void, IoFailureReason>();
    }
};
// ================[END typical specialization]==================

Test(IoPin, readable_pin_is_enabled_readable_not_writable) {
    BoolValue mockValue{true};
    ConcreteBinaryIoPin p(42, IoDirection::READ, &mockValue);

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

    // verify write
    auto writeResult = p.write(false);
    cr_assert_not(writeResult.has_value());
    cr_assert_eq(writeResult.error(), IoFailureReason::FAILURE_PIN_IS_NOT_WRITABLE);

    // verify read to get another value
    mockValue.value = false;
    readResult = p.read();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), false);
}

Test(IoPin, writable_pin_is_enabled_writable_not_readable_) {
    BoolValue mockValue{true};
    ConcreteBinaryIoPin p(43, IoDirection::WRITE, &mockValue);

    // verify predicates
    cr_assert(p.isEnabled());
    cr_assert(p.isNotReadable());
    cr_assert(p.isWritable());
    cr_assert_not(p.isReadable());
    cr_assert_not(p.isNotWritable());
    cr_assert_not(p.isDisabled());

    // verify id
    cr_assert_eq(p.getPinId(), 43);

    // verify read
    auto readResult = p.read();
    cr_assert_not(readResult.has_value());
    cr_assert_eq(readResult.error(), IoFailureReason::FAILURE_PIN_IS_NOT_READABLE);

    // verify write
    auto writeResult = p.write(false);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);

    // verify another write
    writeResult = p.write(true);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);
}

Test(IoPin, disabled_pin_is_disabled_not_writable_not_readable_) {
    BoolValue mockValue{true};
    ConcreteBinaryIoPin p(44, IoDirection::HIGH_Z, &mockValue);

    // verify predicates
    cr_assert(p.isNotReadable());
    cr_assert(p.isNotWritable());
    cr_assert(p.isDisabled());
    cr_assert_not(p.isEnabled());
    cr_assert_not(p.isWritable());
    cr_assert_not(p.isReadable());

    // verify id
    cr_assert_eq(p.getPinId(), 44);

    // verify read
    auto readResult = p.read();
    cr_assert_not(readResult.has_value());
    cr_assert_eq(readResult.error(), IoFailureReason::FAILURE_PIN_IS_DISABLED);

    // verify write
    auto writeResult = p.write(false);
    cr_assert_not(writeResult.has_value());
    cr_assert_eq(writeResult.error(), IoFailureReason::FAILURE_PIN_IS_DISABLED);
}
