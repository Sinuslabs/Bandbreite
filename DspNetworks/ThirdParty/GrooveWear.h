
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::groovewear_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/GrooveWear/GrooveWear.h"

#include "../../External/airwindows/plugins/LinuxVST/src/GrooveWear/GrooveWear.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/GrooveWear/GrooveWearProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::groovewear_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(GrooveWear, groovewear_ns);

}  // namespace project
