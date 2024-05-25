
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::pockey2_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Pockey2/Pockey2.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Pockey2/Pockey2.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Pockey2/Pockey2Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pockey2_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Pockey2, pockey2_ns);

}  // namespace project
