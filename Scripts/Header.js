namespace Header {
	
	const var Product_Logo_pnlbtn = Content.getComponent("Product_Logo_pnlbtn");
	const var Textures_btn = Content.getComponent("Textures_btn");
	const var Theme_btn = Content.getComponent("Theme_btn");
	
	
	Textures_btn.setControlCallback(onTextures);
	Theme_btn.setControlCallback(onTheme);
	
	Product_Logo_pnlbtn.setPaintRoutine(function(g){
		var data = this.getValue();
		var a = this.getLocalBounds(1);
		Console.print(trace(data));
		if (data.hover) {
			g.setColour(Colours.withAlpha(Colours.black, 0.2));
			g.fillRoundedRectangle(a, Primitives.BorderRadius.sm);
		}
	});
	Product_Logo_pnlbtn.setValue({value: false});
	Product_Logo_pnlbtn.setMouseCallback(function(event) {
		
		var data = this.getValue();
		var props = {
			value: data.value,
			hover: event.hover
		};
		
		if (event.clicked && !event.mouseUp) {
			props.value = !data.value;
			if (props.value) {
				Router.goTo('About');
				Textures_btn.setValue(0);
			} else {
				Router.goTo('Tape');
			}
		}
		this.setValue(props);
		this.repaint();
	});
	
	inline function onTextures(component, value) {
		if (value) {
			Router.goTo('Textures');
			Product_Logo_btn.setValue(0);
		} else {
			Router.goTo('Tape');
		}
	}
	
	
	inline function onTheme(component, value) {
		
		Console.print('on: ' + component.getId() + ' : '  + value);
		
	}
	
}