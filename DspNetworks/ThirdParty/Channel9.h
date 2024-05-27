
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::channel9_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Channel9/Channel9.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Channel9/Channel9.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Channel9/Channel9Proc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::channel9_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Channel9, channel9_ns);

}  // namespace project
