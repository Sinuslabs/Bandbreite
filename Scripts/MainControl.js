namespace Main_Controls {
	
	const var LAF_breitband_btn = Content.createLocalLookAndFeel();
	LAF_breitband_btn.registerFunction('drawToggleButton', breitband_btn_laf);
	
	const var MainControls = [
		Content.getComponent("Saturation_knb"),
		Content.getComponent("Sweeten_knb"),
		Content.getComponent("Tape_knb")];

	const var Gains = [Content.getComponent("InputGain_knb"),
	Content.getComponent("OutputGain_knb")];

	const var Container = Content.getComponent("MainPanel_Controls_Container");
	Theme.registerThemePanel(Container);
	Container.setPaintRoutine(containerRoutine);
	
	const var Breitband_btn = Content.getComponent("Breitband_btn");
	Breitband_btn.setLocalLookAndFeel(LAF_breitband_btn);
	
	Breitband_btn.setControlCallback(onBreitband);

	for (knb in MainControls) {
		knb.setControlCallback(onMainControl);
		knb.setLocalLookAndFeel(Styles.LAF_Knob);
		knb.set('stepSize', 0.001);
	}

	for (knb in Gains) {
		knb.setControlCallback(onGainControl);
		knb.setLocalLookAndFeel(VuMeterSlider.LAF_VU_Slider);
	}
	
	inline function onBreitband(component, value) {
		Header.Product_Logo_btn.setValue(1);
		Header.Product_Logo_btn.changed();
	}
	
	inline function onMainControl(component, value) {
		switch (component.getId()) {
			case 'Saturation_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tube, value);
				TapeAnimation.setTube(value);
				break;
			case 'Tape_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape, value);
				TapeAnimation.setGlow(value);
				break;
			case 'Texture_knb':
				FX.BandFX.setAttribute(FX.BandFX.Textures, value);
				break;

		}
	}
	
	inline function onGainControl(component, value) {
		switch (component.getId()) {
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
			this.getHeight() - padding * 2,
		];

		g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
		g.drawRoundedRectangle(a, Primitives.BorderRadius.md, Primitives.BorderSize.md);

	}
	
	inline function breitband_btn_laf(g, obj) {
		local a = obj.area;
		g.rotate(Math.toRadians(90), [a[2] / 2, a[3] / 2]);
		
		a = [
			-55,
			a[1],
			125,
			a[3]
		];
		
		g.setColour(Theme.THEME.Colors.UI.background);
		g.fillRect(a);
	
		
		g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
				
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.UI.on_background_var);
		}
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.UI.on_background_var);
		}	
	
		g.setFont(Theme.SemiBold, 20);
		g.drawAlignedText('BANDBREITE', a, 'centred');
		
		g.addNoise({
				alpha: 0.04,
				monochromatic: false,
				scaleFactor: 1.7,
				area: a
			});		
	}

}