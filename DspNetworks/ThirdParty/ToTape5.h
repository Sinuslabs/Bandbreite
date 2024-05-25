
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::totape5_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/ToTape5/ToTape5.h"

#include "../../External/airwindows/plugins/LinuxVST/src/ToTape5/ToTape5.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/ToTape5/ToTape5Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::totape5_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ToTape5, totape5_ns);

}  // namespace project
