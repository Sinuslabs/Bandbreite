
#pragma once

#include <JuceHeader.h>

#include "../../AdditionalSourceCode/AirWindows.h"

namespace airwindows::flutter_ns {
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wmultichar")
#include "../../External/airwindows/plugins/LinuxVST/src/Flutter/Flutter.h"

#include "../../External/airwindows/plugins/LinuxVST/src/Flutter/Flutter.cpp"
#include "../../External/airwindows/plugins/LinuxVST/src/Flutter/FlutterProc.cpp"
JUCE_END_IGNORE_WARNINGS_GCC_LIKE
}  // namespace airwindows::flutter_ns

namespace project {

using namespace juce;
using namespace hise;
using namespace scriptnode;

DECLARE_AIRWINDOWS_NODE(Flutter, flutter_ns);

}  // namespace project
