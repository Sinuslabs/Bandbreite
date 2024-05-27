
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::pocketverbs_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/PocketVerbs/PocketVerbs.h"

#include "../../External/airwindows/plugins/LinuxVST/src/PocketVerbs/PocketVerbs.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/PocketVerbs/PocketVerbsProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::pocketverbs_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(PocketVerbs, pocketverbs_ns);

}  // namespace project
