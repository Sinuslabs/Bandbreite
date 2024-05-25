namespace Main_Controls {
	
	const var Controls_Container = Content.getComponent("MainPanel_Controls_Container");
	const var MainControls = [Content.getComponent("Saturation_knb"),
	                          Content.getComponent("Texture_knb"),
	                          Content.getComponent("Mix_knb")];
	
	const var Gains = [Content.getComponent("InputGain_knb"),
	                   Content.getComponent("OutputGain_knb")];
	                   
	                   
	for (knb in MainControls) {
		knb.setControlCallback(onMainControl);
	}
	
	for (knb in Gains) {
		knb.setControlCallback(onGainControl);
	}
	
	inline function onMainControl(component, value) {
		
		switch(component.getId()) {
			case 'Saturation_knb':
				BandFX.setAttribute(BandFX.Tube, value);
				break;
			case 'Texture_knb':
				BandFX.setAttribute(BandFX.TextureMix, value);
				break;
			case 'Mix_knb':
				BandFX.setAttribute(BandFX.Mix, value);
				break;			
		}
	}
	
	inline function onGainControl(component, value) {		
		switch(component.getId()) {
			case 'InputGain_knb':
				InputGain.setAttribute(InputGain.Gain, value);
				break;
			case 'OutputGain_knb':
				OutGain.setAttribute(OutGain.Gain, value);
				break;
			
		}
	}
	
}