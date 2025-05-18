/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__LOGIC_INPUT_PIN__HPP
#define CMSPK__IOPINS__LOGIC_INPUT_PIN__HPP
#include <cstdint>
#include <exception>

#include "cmspk/iopins/InputPin.hpp"
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
class LogicInputPin : public BinaryInputPin {
  public:
    ~LogicInputPin() noexcept {}

    /**
     * Fully define a logic I/O pin.
     *
     * @param id the native identification number of the pin.
     * @param direction the direction of the pin.
     * @param logicSetting **optionnal**, the initial logicSetting.
     */
    LogicInputPin(uint8_t id, LogicIoPinSetting logicSetting = LogicIoPinSetting::ACTIVE_HIGH) noexcept
        : BinaryInputPin(id), myLogicSetting(logicSetting) {}

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
     * Read operation, the pin MUST have `READ` direction to be able to succeed.
     *
     * @returns the result of the read operation.
     */
    std::expected<bool, IoFailureReason> readLogic() noexcept {
        std::expected<bool, IoFailureReason> rawRead = read();
        if (rawRead.has_value()) {
            return logicFromRaw(rawRead.value());
        } else {
            return rawRead;
        }
    }

    /**
     * Wrapper calling `readLogic()` and asserting whether it got `true`, **SHOULD be called ONLY when the pin is readable**.
     *
     * @returns `true` only when the pin is readable and is at the logic active state defined as the logic setting.
     */
    bool isAsserted() noexcept {
        std::expected<bool, IoFailureReason> result = readLogic();
        return (result.has_value() && result.value());
    }

    /**
     * Wrapper calling `readLogic()` and asserting whether it got `false`, **SHOULD be called ONLY when the pin is readable**.
     *
     * @returns `true` only when the pin is readable and is at the logic active state defined as the logic setting.
     */
    bool isNegated() noexcept {
        std::expected<bool, IoFailureReason> result = readLogic();
        return (result.has_value() && !(result.value()));
    }

  private:
    LogicIoPinSetting myLogicSetting;

    bool logicFromRaw(bool value) const noexcept { return (LogicIoPinSetting::ACTIVE_HIGH == myLogicSetting) ? value : !value; }
};

// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
