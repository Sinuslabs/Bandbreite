namespace Textures {
	
	const var Mode_Select = [Content.getComponent("Textures_Dust_btn"),
	                         Content.getComponent("Textures_Pocky_btn")];
	const var Pocky_Control_Container = Content.getComponent("Pocky_Control_Container");
	const var Dust_Control_Container = Content.getComponent("Dust_Control_Container");
	
	
	Dust_Control_Container.setPaintRoutine(function(g){});
	Pocky_Control_Container.setPaintRoutine(function(g){});
	
	// DUST KNOB
	const var Dust_knb = Content.getComponent("Dust_knb");
	
	Dust_knb.setControlCallback(onDust);
	Dust_knb.setLocalLookAndFeel(Styles.LAF_displayKnob);
	
	inline function onDust(component, value) {
		BandFX.setAttribute(BandFX.Dust, value);
	}
	
	// POCKY KNOBS
	const var Pocky_lottie_knobs = [Content.getComponent("Pocky_Brightness_Mid_knb"),
	                         Content.getComponent("Pocky_Punch_Mid_knb"),
	                         Content.getComponent("Pocky_Brightness_Side_knb"),
	                         Content.getComponent("Pocky_Punch_Side_knb"),
	                         ];
	                         
	for (knb in Pocky_lottie_knobs) {
		knb.setControlCallback(onLottieKnob);
	}
	
	inline function onLottieKnob(component, value) {
		
		switch(component.getId()) {
			case 'Pocky_Brightness_Mid_knb':
				LottieKnobs.Brightness_Mid_SetFrame(value);
				BandFX.setAttribute(BandFX.BrightM, value);
			case 'Pocky_Punch_Mid_knb':
				BandFX.setAttribute(BandFX.PunchyM, value);
				LottieKnobs.Punch_Mid_SetFrame(value);
			case 'Pocky_Brightness_Side_knb':
				BandFX.setAttribute(BandFX.BrightS, value);
				LottieKnobs.Brightness_Side_SetFrame(value);
			case 'Pocky_Punch_Side_knb':
				BandFX.setAttribute(BandFX.PunchyS, value);
				LottieKnobs.Punch_Side_SetFrame(value);
		}
		
	}
	
	for (btn in Mode_Select) {
		btn.setControlCallback(onModeSelect);
		btn.setLocalLookAndFeel(Styles.LAF_displayButton);
	}
	
	inline function onModeSelect(component, value) {
		switch(component.getId()) {
			case 'Textures_Dust_btn':
				Dust_Control_Container.set('visible', value);
				Pocky_Control_Container.set('visible', !value);
				BandFX.setAttribute(BandFX.Mode, 0);
				break;
			case 'Textures_Pocky_btn':
				Dust_Control_Container.set('visible', !value);
				Pocky_Control_Container.set('visible', value);
				BandFX.setAttribute(BandFX.Mode, 1);
				break;
		}
		
	}
	
}