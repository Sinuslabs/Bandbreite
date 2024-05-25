
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::texturizems_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/TexturizeMS/TexturizeMS.h"

#include "../../External/airwindows/plugins/LinuxVST/src/TexturizeMS/TexturizeMS.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/TexturizeMS/TexturizeMSProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::texturizems_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(TexturizeMS, texturizems_ns);

}  // namespace project
