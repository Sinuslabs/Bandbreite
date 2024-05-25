
include("Core/Primitives.js");
include("Core/ThemeData.js");
include("Core/Theme.js");

include("Animations.js");

include("UI.js");
include("Header.js");
include("MainControl.js");

include("Router.js");

//animations
include("TapeAnimation.js");
include("LogoAnimation.js");

include("Textures.js");
include("Tape.js");

Content.makeFrontInterface(320, 350);

const var InputGain = Synth.getEffect("InputGain");
const var BandFX = Synth.getEffect("BandFX");
const var OutGain = Synth.getEffect("OutGain");

Settings.setZoomLevel(1.3);



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
 