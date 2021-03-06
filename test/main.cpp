/*
 * Copyright (c) 2018 Martin Jäger / Libre Solar
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tests.h"

// The below lines are added to fix unit test compilation error in PIO.
// The Unit Test Framework uses these functions like a constructor/destructor.
// We can just define two empty functions with these names.
void setUp (void) {}
void tearDown (void) {}

int main()
{
    daq_tests();
    bat_charger_tests();
    power_port_tests();
    half_brigde_tests();
    dcdc_tests();
    device_status_tests();
    load_tests();
}
