/* SPDX-License-Identifier: GPL-3.0-or-later */
/* ** ** ** ** ** ** ** ** ** ** ** ** **

---
Copyright (C) 2021~2025 David SPORN
---
This is part of **Animated values**.
Created to help you go beyond a simple blinking.
* ** ** ** ** ** ** ** ** ** ** ** ** **/
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

#include <cstdint>
// FIXME includes your hpp files from ../include
// e.g. #include "whatever.hpp"
#include "cmspk/iopins.hpp"

// FIXME write actual tests

using cmspk::iopins::IoDirection;
using cmspk::iopins::IoFailureReason;
using cmspk::iopins::IoPin;
using cmspk::iopins::LogicIoPin;
using cmspk::iopins::LogicIoPinSetting;

// common helper classes
struct BoolValue {
    bool value;
};

#include "UT-IoPin.hpp"
#include "UT-LogicIoPin.hpp"
