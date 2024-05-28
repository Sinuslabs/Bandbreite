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
include("ZoomHandler.js");

Content.makeFrontInterface(480, 540);

const var InputGain = Synth.getEffect("InputGain");
const var BandFX = Synth.getEffect("BandFX");
const var OutGain = Synth.getEffect("OutGain");

inline function addVisualGuide() {
	
	Content.addVisualGuide([240, 0], Colours.yellow);
	Content.addVisualGuide([0, 60], Colours.red);
}

//addVisualGuide();

UserSettings.load();

namespace EasterEgg {
	
	const var discount_lbl = Content.getComponent("discount_lbl");
	const var code_copied_lbl = Content.getComponent("code_copied_lbl");
	
	code_copied_lbl.showControl(false);
	
	const var discount_copy = Content.getComponent("discount_copy_btn");
	discount_copy.setControlCallback(onCopy);
	
	discount_copy.setLocalLookAndFeel(Styles.LAF_displayButton);
	
	inline function onCopy(component, value){
		if(value) {
			code_copied_lbl.showControl(true);
			Engine.copyToClipboard(discount_lbl.get('text'));
		}
	}
	
}

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
 