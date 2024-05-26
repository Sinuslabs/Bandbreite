namespace VuMeterSlider {
	
	const var InputGain_knb = Content.getComponent("InputGain_knb");
	const var InputGain_VU_pnl = Content.getComponent("InputGain_VU_pnl");
	
	// DISPLAY SLIDER
	const LAF_VU_Slider = Content.createLocalLookAndFeel();
	LAF_VU_Slider.registerFunction('drawRotarySlider', VU_Slider_LAF);
	inline function VU_Slider_LAF(g, obj) {
		local a = obj.area;
		
		local DOT_SIZE = 5;
		local thickness = 1;
		
		local SLIDER_HEIGHT = 1;
		local LINE_THICKNESS = 2;
		local DOT_MAX_TRAVEL = 0.99;
		local DOT_RADIUS = 5;
		local LABEL_BOTTOM_PADDING = 14;
		local value = obj.valueNormalized;
		
		local x = a[2] / 2 - DOT_SIZE / 2 - Primitives.Spacings.md;
		local y = a[3] * DOT_MAX_TRAVEL * (1 - value);
		local tri_area = [x, y, DOT_SIZE, DOT_SIZE];
		
		local bottomPadding_a = [a[0], a[1], a[2], a[3] - LABEL_BOTTOM_PADDING];
		obj.enabled ?
			g.setColour(Theme.THEME.Colors.Display.on_display_var)
			: Theme.THEME.Colors.Display.on_display_disabled;
			
		if (obj.hover) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
		
		//g.fillTriangle(tri_area, Math.toRadians(90));
		g.fillEllipse(tri_area);
		
		g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		
		if (obj.hover || obj.clicked) {
			g.setFont(Theme.Regular, 12);
			g.drawAlignedText(obj.valueAsText.replace(' dB', ''), bottomPadding_a, 'centredBottom');
			g.setFont(Theme.Regular, 14);
			g.drawAlignedText(obj.suffix, a, 'centredBottom');
		}
	}
	
	const locl_laf = Content.createLocalLookAndFeel();
	
	locl_laf.registerFunction("drawRotarySlider", function(g, obj)
	{
	
	var a = obj.area;
    var bottomTextmargin = 0;
    var thickness = 2;	
    var vertpos = obj.valueNormalized;
   
	// Vertical Line Level Meter Fill
	 if (obj.text == "PeakMeterVertFill") {
		 g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		 g.fillRoundedRectangle(a, 0.5);
	 
		g.setColour(Theme.THEME.Colors.Display.on_display);	
		g.fillRoundedRectangle([0, a[3] * (1 - obj.valueNormalized), a[2], a[3]  - a[3] * (1 - obj.valueNormalized)], 0);
 	}
	 	
	// Vertical Line Level Meter Pointer
	 else if (obj.text == "PeakMeterVertPointer") {
	     		
			g.setColour(Theme.THEME.Colors.Display.on_display);		
			g.fillRoundedRectangle([0, a[3] - thickness - (a[3]-thickness)*vertpos, a[2], thickness], 0.5);	
	 	}
	 

	});
	
	const var InputPeakMeter = Content.getComponent("InputPeakMeterFillL");
	const var InputPeakPoint = Content.getComponent("InputPeakMeterPointL");
	const var OutputPeakMeter = Content.getComponent("OutputPeakMeterFillL");
	const var OutputPeakPoint = Content.getComponent("OutputPeakMeterPointL");
	
	OutputPeakMeter.setLocalLookAndFeel(locl_laf);
	OutputPeakPoint.setLocalLookAndFeel(locl_laf);
	
	InputPeakMeter.setLocalLookAndFeel(locl_laf);
	InputPeakPoint.setLocalLookAndFeel(locl_laf);
	
	//Current Values
	var curLevelLM_Fill = 0.0;
	var curLevelLM_Pointer = 0.0;
	//Current Values
	var out_curLevelLM_Fill = 0.0;
	var out_curLevelLM_Pointer = 0.0;
	
	
// Timer Callback
const var t1 = Engine.createTimerObject();

t1.setTimerCallback(function()
{
	
    var LevelLM_Fill = (InputGain.getCurrentLevel(0) + InputGain.getCurrentLevel(1) )/ 2;   
    var LevelLM_Pointer = (InputGain.getCurrentLevel(0) + InputGain.getCurrentLevel(1) ) / 2;  
    
    var Output_LevelLM_Fill = (OutGain.getCurrentLevel(0) + OutGain.getCurrentLevel(1)) / 2;   
    var Output_LevelLM_Pointer = (OutGain.getCurrentLevel(0) + OutGain.getCurrentLevel(1)) / 2;  
    
    // Apply different smoothing based on whether the level is rising or falling
    curLevelLM_Fill = curLevelLM_Fill > LevelLM_Fill ? 
        Math.max(LevelLM_Fill, curLevelLM_Fill * DECAY_RATE_Fill) : 
        (curLevelLM_Fill * (1 - ATTACK_RATE_Fill) + LevelLM_Fill * ATTACK_RATE_Fill);
   	
   	// Apply different smoothing based on whether the level is rising or falling
   	out_curLevelLM_Fill = out_curLevelLM_Fill > Output_LevelLM_Fill ? 
   	    Math.max(Output_LevelLM_Fill, out_curLevelLM_Fill * DECAY_RATE_Fill) : 
   	    (out_curLevelLM_Fill * (1 - ATTACK_RATE_Fill) + Output_LevelLM_Fill * ATTACK_RATE_Fill);
    
    curLevelLM_Pointer = curLevelLM_Pointer > LevelLM_Pointer ? 
        Math.max(LevelLM_Pointer, curLevelLM_Pointer * DECAY_RATE_Pointer) : 
        (curLevelLM_Pointer * (1 - ATTACK_RATE_Pointer) + LevelLM_Pointer * ATTACK_RATE_Pointer);
    
    out_curLevelLM_Pointer = out_curLevelLM_Pointer > Output_LevelLM_Pointer ? 
        Math.max(Output_LevelLM_Pointer, out_curLevelLM_Pointer * DECAY_RATE_Pointer) : 
        (out_curLevelLM_Pointer * (1 - ATTACK_RATE_Pointer) + Output_LevelLM_Pointer * ATTACK_RATE_Pointer);
    
    // Decibel Conversion     
    LevelLM_Fill = Engine.getDecibelsForGainFactor(curLevelLM_Fill);  
    LevelLM_Pointer = Engine.getDecibelsForGainFactor(curLevelLM_Pointer);  
    
    // Set Values  
    InputPeakMeter.setValue(LevelLM_Fill);  
    InputPeakPoint.setValue(LevelLM_Pointer); 
    
    // Decibel Conversion     
    Output_LevelLM_Fill = Engine.getDecibelsForGainFactor(out_curLevelLM_Fill);  
    Output_LevelLM_Pointer = Engine.getDecibelsForGainFactor(out_curLevelLM_Pointer);
    
    // Set Values  
    OutputPeakMeter.setValue(Output_LevelLM_Fill);  
    OutputPeakPoint.setValue(Output_LevelLM_Pointer);   
});

t1.startTimer(20);

// Initialize the current levels
var curLevelLM_Fill = 0.0;
var curLevelLM_Pointer = 0.0;

// Define decay and attack rates
const var DECAY_RATE_Fill = 0.82; // Adjust these values as needed
const var ATTACK_RATE_Fill = 0.2; // Adjust these values as needed
const var DECAY_RATE_Pointer = 0.9; // Adjust these values as needed
const var ATTACK_RATE_Pointer = 0.4; // Adjust these values as needed

	
	
	
	
	
	
	
	
}