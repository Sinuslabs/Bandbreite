include("Core/Primitives.js");
include("Core/ThemeData.js");
include("Core/Theme.js");
include("Helpers.js");

include("Assets.js");
include("StyleHelpers.js");
include("Styles.js");
include("Animations.js");

include("FX.js");
include("UI.js");
include("VuMeterSlider.js");
include("Header.js");
include("MainControl.js");

include("UserSettings.js");
include("Router.js");

include("TapeAnimation.js");
include("LogoAnimation.js");
include("ThemeAnimation.js");
include("Randomization.js");
include("ConfettiAnimation.js");

include("Textures.js");
include("Tape.js");
include("About.js");
include("EasterEgg.js");
include("ZoomHandler.js");

const WIDTH = 480;
const HEIGHT = 540;

Content.makeFrontInterface(WIDTH, HEIGHT);

const var InputGain = Synth.getEffect("InputGain");
const var BandFX = Synth.getEffect("BandFX");
const var OutGain = Synth.getEffect("OutGain");

inline function addVisualGuide() {
	
	Console.print(trace(Content.getScreenBounds(true)));

	Content.addVisualGuide([WIDTH / 2, 0], Colours.yellow);
	Content.addVisualGuide([0, 60], Colours.red);
	Content.addVisualGuide([0, 310], Colours.red);
	Content.addVisualGuide([0, 330], Colours.red);
}

//addVisualGuide();

UserSettings.load();

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
 