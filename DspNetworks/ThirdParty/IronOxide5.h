
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::ironoxide5_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/IronOxide5/IronOxide5.h"

#include "../../External/airwindows/plugins/LinuxVST/src/IronOxide5/IronOxide5.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/IronOxide5/IronOxide5Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::ironoxide5_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(IronOxide5, ironoxide5_ns);

}  // namespace project
