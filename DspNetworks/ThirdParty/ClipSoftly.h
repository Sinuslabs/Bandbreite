
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::clipsoftly_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/ClipSoftly/ClipSoftly.h"

#include "../../External/airwindows/plugins/LinuxVST/src/ClipSoftly/ClipSoftly.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/ClipSoftly/ClipSoftlyProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::clipsoftly_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(ClipSoftly, clipsoftly_ns);

}  // namespace project
