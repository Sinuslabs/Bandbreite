
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::tapedust_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/TapeDust/TapeDust.h"

#include "../../External/airwindows/plugins/LinuxVST/src/TapeDust/TapeDust.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/TapeDust/TapeDustProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tapedust_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TapeDust, tapedust_ns);

}  // namespace project
