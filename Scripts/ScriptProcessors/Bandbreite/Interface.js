include("Core/Primitives.js");
include("Core/ThemeData.js");
include("Core/Theme.js");
include("Helpers.js");

include("UpdateChecker.js");

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

Globals.canUpdate = false;
Globals.OS = Engine.getOS();
//Globals.OS = 'LINUX';

inline function addVisualGuide() {
	
	Content.addVisualGuide([WIDTH / 2, 0], Colours.yellow);
	Content.addVisualGuide([0, 60], Colours.red);
	Content.addVisualGuide([0, 310], Colours.red);
	Content.addVisualGuide([0, 330], Colours.red);
}

//addVisualGuide();

UserSettings.load();
if (Globals.OS === 'LINUX') {
	Globals.canUpdate = UpdateChecker.checkUpdate(onUpdate);
}

inline function onUpdate(canUpdate) {
	Header.Update_btn.showControl(canUpdate);
	About.UpdateNow_btn.showControl(canUpdate);
}function onNoteOn()
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
 