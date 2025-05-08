/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/

// ================[BEGIN typical specialization]==================
class ConcreteLogicIoPin final : public LogicIoPin {
  public:
    ~ConcreteLogicIoPin() {}
    ConcreteLogicIoPin(uint8_t index, IoDirection direction, BoolValue* value) : LogicIoPin(index, direction), value(value) {}

  private:
    BoolValue* value;

    virtual std::expected<bool, IoFailureReason> doRead() noexcept { return value->value; }
    virtual std::expected<void, IoFailureReason> doWrite(const bool value) noexcept {
        this->value->value = value;
        return std::expected<void, IoFailureReason>();
    }
};
// ================[END typical specialization]==================

Test(LogicIoPin, readable_LogicIoPin_is_an_IoPin) {
    BoolValue mockValue{true};
    ConcreteLogicIoPin p(42, IoDirection::READ, &mockValue);

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


Test(LogicIoPin, writable_LogicIoPin_is_an_IoPin) {
    BoolValue mockValue{true};
    ConcreteLogicIoPin p(43, IoDirection::WRITE, &mockValue);

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

Test(LogicIoPin, disabled_LogicIoPin_is_an_IoPin) {
    BoolValue mockValue{true};
    ConcreteLogicIoPin p(44, IoDirection::HIGH_Z, &mockValue);

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

Test(LogicIoPin, readLogic_depends_on_logic_setting) {
    BoolValue mockValue{true};
    ConcreteLogicIoPin p(42, IoDirection::READ, &mockValue);

    // verify logic read
    auto readResult = p.readLogic();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), true);
    cr_assert(p.isAsserted());
    cr_assert_not(p.isNegated());

    // verify another logic read
    mockValue.value = false;
    readResult = p.readLogic();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), false);
    cr_assert(p.isNegated());
    cr_assert_not(p.isAsserted());

    // change logic setting
    p.setLogicSetting(LogicIoPinSetting::ACTIVE_LOW);
    readResult = p.readLogic();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), true);
    cr_assert(p.isAsserted());
    cr_assert_not(p.isNegated());

    // verify another logic read
    mockValue.value = true;
    readResult = p.readLogic();
    cr_assert(readResult.has_value());
    cr_assert_eq(readResult.value(), false);
    cr_assert(p.isNegated());
    cr_assert_not(p.isAsserted());
}

Test(LogicIoPin, writeLogic_depends_on_logic_setting) {
    BoolValue mockValue{false};
    ConcreteLogicIoPin p(43, IoDirection::WRITE, &mockValue);

    // verify write
    auto writeResult = p.writeLogic(true);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);

    // use wrappers
    writeResult = p.negate();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);
    writeResult = p.assert();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);

    // change logic setting
    p.setLogicSetting(LogicIoPinSetting::ACTIVE_LOW);
    writeResult = p.writeLogic(true);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);

    // use wrappers
    writeResult = p.negate();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);
    writeResult = p.assert();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);
}
