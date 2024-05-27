include("Core/Primitives.js");
include("Core/ThemeData.js");
include("Core/Theme.js");
include("Helpers.js");

include("Assets.js");
include("StyleHelpers.js");
include("Styles.js");
include("Animations.js");

include("UI.js");
include("VuMeterSlider.js");
include("Header.js");
include("MainControl.js");

include("Router.js");

include("TapeAnimation.js");
include("LogoAnimation.js");
include("ThemeAnimation.js");
include("Randomization.js");

include("Textures.js");
include("Tape.js");
include("About.js");


Content.makeFrontInterface(480, 540);

const var InputGain = Synth.getEffect("InputGain");
const var BandFX = Synth.getEffect("BandFX");
const var OutGain = Synth.getEffect("OutGain");

Settings.setZoomLevel(1);

inline function addVisualGuide() {
	
	Content.addVisualGuide([240, 0], Colours.yellow);
	
}

//addVisualGuide();


function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
 