#pragma once

// Lets other UIs open the framework without simulating a keypress.
//
// A tween-menu replacement, an MCM hotkey, a lesser power or a quest script can
// send one of these mod events instead of needing the toggle key bound at all:
//
//   SKSEMenuFramework_Open
//   SKSEMenuFramework_Close
//   SKSEMenuFramework_Toggle
//
// From Papyrus that is a one-liner:
//
//   int handle = ModEvent.Create("SKSEMenuFramework_Toggle")
//   ModEvent.Send(handle)
//
// which matters on a controller, where a spare key to bind is exactly what you
// do not have.
namespace ModEvent {
    void Install();
}
