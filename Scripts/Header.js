namespace Header {
	
	const var Product_Logo_pnlbtn = Content.getComponent("Product_Logo_pnlbtn");
	const var Textures_btn = Content.getComponent("Textures_btn");
	
	const var ThemeSpinner_pnlbtn = Content.getComponent("ThemeSpinner_pnlbtn");

	Textures_btn.setControlCallback(onTextures);
	
	// sync to theme
	ThemeSpinner_pnlbtn.setValue({value: true});
	ThemeSpinner_pnlbtn.setPaintRoutine(fakeHoverRoutine);
	ThemeSpinner_pnlbtn.setControlCallback(onTheme);
	ThemeSpinner_pnlbtn.setMouseCallback(onPanelMouseCallback);
	
	Product_Logo_pnlbtn.setValue({value: false});
	Product_Logo_pnlbtn.setPaintRoutine(fakeHoverRoutine);
	Product_Logo_pnlbtn.setControlCallback(onLogo);
	Product_Logo_pnlbtn.setMouseCallback(onPanelMouseCallback);
	
	inline function onLogo(component, value) {
		Console.print(trace(value));
		if (value.value) {
			Router.goTo('About');
			Textures_btn.setValue(0);
		} else {
			Router.goTo('Tape');
		}
	}
	
	inline function onTheme(component, value) {
		Console.print(value.value);
		Theme.toggleTheme(value.value);	
		ThemeAnimation.onClick(value.value);
	}
	
	inline function onTextures(component, value) {
		if (value) {
			Router.goTo('Textures');
			Product_Logo_pnlbtn.setValue({value: false});
			Product_Logo_pnlbtn.repaint();
		} else {
			Router.goTo('Tape');
		}
	}
	
	inline function fakeHoverRoutine(g) {
		local data = this.getValue();
		local a = this.getLocalBounds(1);
		if (data.hover) {
			g.setColour(Colours.withAlpha(Colours.black, 0.2));
			g.fillRoundedRectangle(a, Primitives.BorderRadius.sm);
		}
	}
	
	inline function onPanelMouseCallback(event) {
		local data = this.getValue();
		local props = {
			value: data.value,
			hover: event.hover
		};
		
		if (event.clicked && !event.mouseUp) {
			props.value = !data.value;
			this.setValue(props);
			this.changed();
			this.repaint();
			return;
		}
		this.setValue(props);
		this.repaint();
	}
	
	

	
}