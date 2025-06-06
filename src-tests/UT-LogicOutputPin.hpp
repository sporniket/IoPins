/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/

// ================[BEGIN typical specialization]==================
class ConcreteLogicOutputPin final : public LogicOutputPin {
  public:
    ~ConcreteLogicOutputPin() {}
    ConcreteLogicOutputPin(uint8_t index, BoolValue* value) : LogicOutputPin(index), value(value) {}

  private:
    BoolValue* value;

    virtual std::expected<void, IoFailureReason> checkWritability() noexcept {
        return std::expected<void, IoFailureReason>();
    }

    virtual std::expected<void, IoFailureReason> doWrite(const bool value) noexcept {
        this->value->value = value;
        return std::expected<void, IoFailureReason>();
    }
};
// ================[END typical specialization]==================

Test(LogicOutputPin, writable_LogicOutputPin_is_an_IoPin) {
    BoolValue mockValue{true};
    ConcreteLogicOutputPin p(43, &mockValue);

    // verify predicates
    cr_assert(p.isEnabled());
    cr_assert(p.isNotReadable());
    cr_assert(p.isWritable());
    cr_assert_not(p.isReadable());
    cr_assert_not(p.isNotWritable());
    cr_assert_not(p.isDisabled());

    // verify id
    cr_assert_eq(p.getPinId(), 43);

    // verify write
    auto writeResult = p.write(false);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);

    // verify another write
    writeResult = p.write(true);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);
}

Test(LogicOutputPin, writeLogic_depends_on_logic_setting) {
    BoolValue mockValue{false};
    ConcreteLogicOutputPin p(43, &mockValue);

    // verify write
    auto writeResult = p.writeLogic(true);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);

    // use wrappers
    writeResult = p.toNegated();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);
    writeResult = p.toAsserted();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);

    // change logic setting
    p.setLogicSetting(LogicIoPinSetting::ACTIVE_LOW);
    writeResult = p.writeLogic(true);
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);

    // use wrappers
    writeResult = p.toNegated();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, true);
    writeResult = p.toAsserted();
    cr_assert(writeResult.has_value());
    cr_assert_eq(mockValue.value, false);
}
