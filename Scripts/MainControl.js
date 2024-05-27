namespace Main_Controls {
	
	const var MainControls = [Content.getComponent("Saturation_knb"),
	                          Content.getComponent("Texture_knb"),
	                          Content.getComponent("Tape_knb")];
	
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
			case 'Tape_knb':
				BandFX.setAttribute(BandFX.Tape, value);
				TapeAnimation.setGlow(value);
				break;
			case 'Texture_knb':
				BandFX.setAttribute(BandFX.Textures, value);
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
	 	 local padding = 5;
	 	 local a = [
	 	 	0 + padding,
	 	 	0 + padding,
	 	 	this.getWidth() - padding * 2,
	 	 	this.getHeight() -padding * 2,
	 	 ];
	 	 
	 	 g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
	 	 g.drawRoundedRectangle(a, Primitives.BorderRadius.md, Primitives.BorderSize.md);
	 	 
	 	 local text_a = [
	 	 	73,
	 	 	49,
	 	 	110,
	 	 	20
	 	 ];
	 	 
	 	 g.rotate(Math.toRadians(90), [text_a[2] / 2, text_a[3] / 2]);
	 	 
	 	 g.setColour(Theme.THEME.Colors.UI.background);
	 	 g.fillRect(text_a);
	 	 
 	 	 g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
	 	 g.setFont(Theme.SemiBold, 20);
	 	 g.drawAlignedText('BREITBAND', text_a, 'centred');

	 	 
	 }
	
}