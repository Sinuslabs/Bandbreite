namespace Header {
	
	const var Product_Logo_pnlbtn = Content.getComponent("Product_Logo_pnlbtn");
	const var Textures_btn = Content.getComponent("Textures_btn");
	const var Theme_btn = Content.getComponent("Theme_btn");
	
	
	Textures_btn.setControlCallback(onTextures);
	Theme_btn.setControlCallback(onTheme);
	
	
	Product_Logo_pnlbtn.setValue({value: false});
	Product_Logo_pnlbtn.setMouseCallback(function(event) {
		var data = this.getValue();
		if (event.mouseUp) {
			var props = {
				value: !data.value
			};
			if (props.value) {
				LogoAnimation.init();			
				Router.goTo('About');
				Textures_btn.setValue(0);
			} else {
				Router.goTo('Tape');
			}
			this.setValue(props);
		}

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