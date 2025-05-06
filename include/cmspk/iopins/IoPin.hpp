/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2025~2025 David SPORN
---
This is part of **I/O pins**.
A C++ abstraction layer for I/O pins of micro-controllers.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#ifndef CMSPK__IOPINS__IO_PIN__HPP
#define CMSPK__IOPINS__IO_PIN__HPP
#include <cstdint>
#include <exception>

#include "IoDirection.hpp"
#include "IoFailureReason.hpp"
namespace cmspk::iopins {
// ================[ CODE BEGINS ]================

// ...your includes...
#include "cmspk/iopins/IoDirection.hpp"
#include "cmspk/iopins/IoFailureReason.hpp"

// ...your code...
/**
 * An abstraction of I/O pins, with a value represented by the given type.
 *
 * This base I/O pin has a fixed direction and cannot be reconfigured.
 *
 * @param S storage type for the value, typically a `bool` or an `uint8_t`
 */
template <typename S>
class IoPin {
  public:
    ~IoPin() {}

    /**
     * Fully define an I/O pin.
     */
    IoPin(uint8_t id, IoDirection direction) : id(id), direction(direction) {}

    /**
     * Predicate about the readability of the pin.
     *
     * @returns `true` when this is an input pin.
     */
    bool isReadable() const { return IoDirection::READ == direction; }

    /**
     * Predicate about the readability of the pin.
     *
     * @returns `true` when this is not an input pin.
     */
    bool isNotReadable() const { return IoDirection::READ != direction; }

    /**
     * Predicate about the writability of the pin.
     *
     * @returns `true` when this is an output pin.
     */
    bool isWritable() const { return IoDirection::WRITE == direction; }

    /**
     * Predicate about the writability of the pin.
     *
     * @returns `true` when this is not an output pin.
     */
    bool isNotWritable() const { return IoDirection::WRITE != direction; }

    /**
     * Predicate about the enabling of the pin.
     *
     * @returns `true` when this pin is enabled.
     */
    bool isEnabled() const { return IoDirection::HIGH_Z != direction; }

    /**
     * Predicate about the enabling of the pin.
     *
     * @returns `true` when this pin is disabled.
     */
    bool isDisabled() const { return IoDirection::HIGH_Z == direction; }

    /**
     * Get the pin id for the underlying microcontroller/board, usually a 1-based index value.
     */
    uint8_t getPinId() const { return id; }

    /**
     * Read operation, the pin MUST have `READ` direction to be able to succeed.
     *
     * @returns the result of the read operation.
     */
    std::expected<S, IoFailureReason> read() noexcept {
        if (isDisabled()) {
            return std::unexpected(IoFailureReason::FAILURE_PIN_IS_DISABLED);
        } else if (isNotReadable()) {
            return std::unexpected(IoFailureReason::FAILURE_PIN_IS_NOT_READABLE);
        } else {
            return std::move(doRead());
        }
    }

    /**
     * Write operation, the pin MUST have `WRITE` direction to be able to succeed.
     *
     * @param value the value to write to the I/O pin.
     *
     * @returns the result of the write operation.
     */
    std::expected<void, IoFailureReason> write(const S value) noexcept {
        if (isDisabled()) {
            return std::unexpected(IoFailureReason::FAILURE_PIN_IS_DISABLED);
        } else if (isNotWritable()) {
            return std::unexpected(IoFailureReason::FAILURE_PIN_IS_NOT_WRITABLE);
        } else {
            return std::move(doWrite(value));
        }
    }

  private:
    /**
     * Extension point to implement for the actual read operation.
     *
     * @returns the result of the read operation.
     */
    virtual std::expected<S, IoFailureReason> doRead() noexcept = 0;
    /**
     * Extension point to implement for the actual write operation.
     *
     * @param value the value to write to the I/O pin.
     *
     * @returns the result of the write operation.
     */
    virtual std::expected<void, IoFailureReason> doWrite(const S value) noexcept = 0;

  private:
    uint8_t id;
    IoDirection direction;
};
// ================[ END OF CODE ]================
};  // namespace cmspk::iopins
#endif
