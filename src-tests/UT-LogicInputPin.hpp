/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/

// ================[BEGIN typical specialization]==================
class ConcreteLogicInputPin final : public LogicInputPin {
  public:
    ~ConcreteLogicInputPin() {}
    ConcreteLogicInputPin(uint8_t index, BoolValue* value) : LogicInputPin(index), value(value) {}

  private:
    BoolValue* value;

    virtual std::expected<bool, IoFailureReason> doRead() noexcept { return value->value; }
};
// ================[END typical specialization]==================

Test(LogicInputPin, readable_LogicInputPin_is_an_IoPin) {
    BoolValue mockValue{true};
    ConcreteLogicInputPin p(42, &mockValue);

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

Test(LogicInputPin, readLogic_depends_on_logic_setting) {
    BoolValue mockValue{true};
    ConcreteLogicInputPin p(42, &mockValue);

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
