namespace Main_Controls {
	
	const var MainControls = [Content.getComponent("Saturation_knb"),
	                          Content.getComponent("Texture_knb"),
	                          Content.getComponent("Mix_knb")];
	
	const var Gains = [Content.getComponent("InputGain_knb"),
	                   Content.getComponent("OutputGain_knb")];
	 
	 const var Container = Content.getComponent("MainPanel_Controls_Container");
	 Theme.registerThemePanel(Container);               
	 Container.setPaintRoutine(containerRoutine);
	                   
	for (knb in MainControls) {
		knb.setControlCallback(onMainControl);
		knb.setLocalLookAndFeel(Styles.LAF_Knob);
	}
	
	for (knb in Gains) {
		knb.setControlCallback(onGainControl);
		knb.setLocalLookAndFeel(VuMeterSlider.LAF_VU_Slider);
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
	
	inline function containerRoutine(g) {
	 	 
	 	 local a = this.getLocalBounds(Primitives.Spacings.md);
	 	 g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
	 	 g.drawRoundedRectangle(a, Primitives.BorderRadius.md, Primitives.BorderSize.sm);
	 	 
	 	 local text_a = [
	 	 	40,
	 	 	34,
	 	 	80,
	 	 	19
	 	 ];
	 	 
	 	 g.rotate(Math.toRadians(90), [text_a[2] / 2, text_a[3] / 2]);
	 	 
	 	 g.setColour(Theme.THEME.Colors.UI.background);
	 	 g.fillRect(text_a);
	 	 
 	 	 g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
	 	 g.setFont(Theme.SemiBold, 16);
	 	 g.drawAlignedText('BREITBAND', text_a, 'centred');

	 	 
	 }
	
}