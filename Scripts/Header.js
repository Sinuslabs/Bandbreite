namespace Header {
	
	//invisble click btn
	const var extra_click_area_btn = Content.getComponent("extra_click_area_btn");

	const var LAF_breitband_btn = Content.createLocalLookAndFeel();
	LAF_breitband_btn.registerFunction('drawToggleButton', breitband_btn_laf);
	
	const var Breitband_btn = Content.getComponent("Breitband_btn");
	Breitband_btn.setLocalLookAndFeel(LAF_breitband_btn);
	Breitband_btn.setControlCallback(onBreitband);

	const var LAF_hiddenBTN = Content.createLocalLookAndFeel();
	LAF_hiddenBTN.registerFunction('drawToggleButton', hiddenBtn_LAF);
	
	extra_click_area_btn.setLocalLookAndFeel(LAF_hiddenBTN);
	extra_click_area_btn.setControlCallback(onBackToTape);
	
	const var Product_Logo_btn = Content.getComponent("Product_Logo_btn");
	const var Textures_btn = Content.getComponent("Textures_btn");
	const var Tape_btn = Content.getComponent("Tape_btn");
	
	const var ThemeSpinner_btn = Content.getComponent("ThemeSpinner_btn");

	Textures_btn.setControlCallback(onTextures);
	Textures_btn.setLocalLookAndFeel(Styles.LAF_textButton);
	
	Tape_btn.setControlCallback(onTape);
	Tape_btn.setLocalLookAndFeel(Styles.LAF_textButton);

	// sync to theme
	ThemeSpinner_btn.setValue(0);
	ThemeSpinner_btn.setControlCallback(onTheme);
	ThemeSpinner_btn.setLocalLookAndFeel(LAF_hiddenBTN);
	
	Product_Logo_btn.setLocalLookAndFeel(LAF_hiddenBTN);
	Product_Logo_btn.setControlCallback(onLogo);
	
	inline function onBreitband(component, value) {
		Product_Logo_btn.setValue(1);
		Product_Logo_btn.changed();
	}
	
	inline function onBackToTape(component, value) {
		if (value) {
			Tape_btn.setValue(1);
			Tape_btn.changed();
		}
	}
	
	inline function onLogo(component, value) {
		
		if (Router.currentRoute === 'About') {
			Breitband_btn.setValue(0);
			Tape_btn.setValue(1);
			Tape_btn.changed();
			return;
		}
		
		Breitband_btn.setValue(1);
		Router.goTo('About');
	}
	
	inline function onTextures(component, value) {
		if (value) {
			Router.goTo('Textures');
		}
	}
	
	inline function onTape(component, value) {
		if (value) {
			Router.goTo('Tape');
		}
	}
	
	inline function onTheme(component, value) {
		Console.print(value);
	
		Theme.toggleTheme(value);	
		ThemeAnimation.onClick(value);
	}
	
	inline function hiddenBtn_LAF(g, obj) {
		local a = obj.area;
		a = StyleHelpers.addPadding(a, 1);
		if (obj.over || Router.currentRoute === 'About') {
			g.setColour(Colours.withAlpha(Colours.black, 0.2));
			g.fillRoundedRectangle(a, Primitives.BorderRadius.sm);
		}
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
		g.drawAlignedText('BREITBAND', a, 'centred');
		
		g.addNoise({
				alpha: 0.04,
				monochromatic: false,
				scaleFactor: 1.7,
				area: a
			});		
	}
}