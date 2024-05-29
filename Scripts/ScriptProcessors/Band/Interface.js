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

namespace Smoothing {
	// Define your smoothing time in milliseconds
	const var smoothingTime = 100;
	
	// Create an object to store the smoothed values for each knob
	const var smoothedValues = {};
	
	// Create a queue to store the knobs that need to be smoothed
	const var smoothingQueue = [];
	
	// Create a timer to handle the smoothing
	const var smoothingTimer = Engine.createTimerObject();
	
	// Set up the exponential smoothing function
	smoothingTimer.setTimerCallback(function()
	{
	    for (i = 0; i < smoothingQueue.length; i++)
	    {
	        // Get the current knob id from the queue
	        var knobId = smoothingQueue[i];
	        var knob = Content.getComponent(knobId);
	        
	        // Get the current knob value
	        var targetValue = knob.getValue();
	        
	        // Initialize the smoothed value if not already done
	        if (isDefined(smoothedValues[knobId]))
	            smoothedValues[knobId] = targetValue;
	        
	        // Calculate the smoothing factor
	        var smoothingFactor = 44100 * (smoothingTime / 1000);
	        
	        // Apply exponential smoothing
	        var delta = targetValue - smoothedValues[knobId];
	        smoothedValues[knobId] += delta * (1.0 - Math.exp(-1.0 / smoothingFactor));
	        
	        
	        // Check if the smoothed value is close enough to the target value
	        if (Math.abs(delta) < 0.001)
	        {
	            // Remove the knob id from the queue
	            smoothingQueue.remove(i);
	            i--; // Adjust the index since we removed an item from the queue
	        }
	    }
	    
	    // Stop the timer if the queue is empty
	    if (smoothingQueue.length == 0)
	        smoothingTimer.stopTimer();
	});
	
	// Inline function to handle knob changes
	inline function smooth(component, value)
	{
	    local knobId = component.getId();
	    if (smoothingQueue.indexOf(knobId) == -1)
	    {
	      //  smoothingQueue.push(knobId);
	    }
	    if (!smoothingTimer.isTimerRunning())
	       // smoothingTimer.startTimer(500);
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
 