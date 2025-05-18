/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__LOGIC_OUTPUT_PIN__HPP
#define CMSPK__IOPINS__LOGIC_OUTPUT_PIN__HPP
#include <cstdint>
#include <exception>

#include "cmspk/iopins/OutputPin.hpp"
#include "cmspk/iopins/LogicIoPinSetting.hpp"
namespace cmspk::iopins {
// ================[ CODE BEGINS ]================
/**
 * Abstraction of a pin that can be **asserted/active** or **negated/inactive**.
 *
 * The **raw** value is accessible through `read()`/`write()` ; the **logic** value
 * is accessible through `readLogic()`/`writeLogic()` and their meaningfully named
 * `isAsserted()`/`isNegated()`/`toAsserted()`/`toNegated()` wrappers.
 *
 * The logic setting can be changed.
 */
class LogicOutputPin : public BinaryOutputPin {
  public:
    ~LogicOutputPin() noexcept {}

    /**
     * Fully define a logic I/O pin.
     *
     * @param id the native identification number of the pin.
     * @param logicSetting **optionnal**, the initial logicSetting.
     */
    LogicOutputPin(uint8_t id, LogicIoPinSetting logicSetting = LogicIoPinSetting::ACTIVE_HIGH) noexcept
        : BinaryOutputPin(id), myLogicSetting(logicSetting) {}

    /**
     * Accessor of `logicSetting` property.
     *
     * @returns the property's value.
     */
    LogicIoPinSetting getLogicSetting() const noexcept { return myLogicSetting; }

    /**
     * Mutator of `logicSetting` property.
     *
     * @param logicSetting the new value.
     */
    void setLogicSetting(LogicIoPinSetting logicSetting) noexcept { myLogicSetting = logicSetting; }

    /**
     * Write operation, the pin MUST have `WRITE` direction to be able to succeed.
     *
     * @param value the value to write to the I/O pin.
     *
     * @returns the result of the write operation.
     */
    std::expected<void, IoFailureReason> writeLogic(const bool value) noexcept { return write(rawFromLogic(value)); }

    /**
     * Wrapper calling `writeLogic(true)`.
     *
     * @returns the result of the write operation.
     */
    std::expected<void, IoFailureReason> toAsserted() noexcept { return writeLogic(true); }

    /**
     * Wrapper calling `writeLogic(false)`.
     *
     * @returns the result of the write operation.
     */
    std::expected<void, IoFailureReason> toNegated() noexcept { return writeLogic(false); }

  private:
    LogicIoPinSetting myLogicSetting;

    bool rawFromLogic(bool value) const noexcept { return (LogicIoPinSetting::ACTIVE_HIGH == myLogicSetting) ? value : !value; }
};

// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
