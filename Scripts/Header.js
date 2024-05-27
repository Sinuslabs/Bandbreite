namespace Header {
	
	//invisble click btn
	const var extra_click_area_btn = Content.getComponent("extra_click_area_btn");

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
	
	inline function onBackToTape(component, value) {
		if (value) {
			Tape_btn.setValue(1);
			Tape_btn.changed();
		}
	}
		
	inline function onLogo(component, value) {
		Console.print(value);
		
		if (Router.currentRoute === 'About') {
			Tape_btn.setValue(1);
			Tape_btn.changed();
			return;
		}
	
		if (value) {
			Router.goTo('About');
		}
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
		Theme.toggleTheme(value);	
		ThemeAnimation.onClick(value);
	}
	
	inline function hiddenBtn_LAF(g, obj) {
		local a = obj.area;
		a = StyleHelpers.addPadding(a, 1);
		if (obj.over) {
			g.setColour(Colours.withAlpha(Colours.black, 0.2));
			g.fillRoundedRectangle(a, Primitives.BorderRadius.sm);
		}
	}	
}