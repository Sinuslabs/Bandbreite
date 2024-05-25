
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::tube2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Tube2/Tube2.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Tube2/Tube2.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Tube2/Tube2Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tube2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Tube2, tube2_ns);

}  // namespace project
