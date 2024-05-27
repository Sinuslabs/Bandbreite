
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::sweeten_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Sweeten/Sweeten.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Sweeten/Sweeten.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Sweeten/SweetenProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::sweeten_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Sweeten, sweeten_ns);

}  // namespace project
