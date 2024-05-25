
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::tovinyl4_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/ToVinyl4/ToVinyl4.h"

#include "../../External/airwindows/plugins/LinuxVST/src/ToVinyl4/ToVinyl4.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/ToVinyl4/ToVinyl4Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::tovinyl4_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ToVinyl4, tovinyl4_ns);

}  // namespace project
