namespace About {
	
	const var LAF_logo = Content.createLocalLookAndFeel();
	LAF_logo.registerFunction('drawToggleButton', logo_laf);

	inline function logo_laf(g, obj) {
		local a = obj.area;
		g.setColour(Theme.THEME.Colors.Display.on_display);
		g.fillPath(Assets.get.logo, a);
	}

	const var Get_more_btn = Content.getComponent("Get_more_btn");
	const var Sinuslabs_Logo_btn = Content.getComponent("Sinuslabs_Logo_btn");
	const var Youtube_btn = Content.getComponent("Youtube_btn");
	const var Instagram_btn = Content.getComponent("Instagram_btn");
	
	Youtube_btn.setLocalLookAndFeel(Styles.LAF_displayIconSocialsButton);
	Youtube_btn.setControlCallback(onYT);
	Instagram_btn.setLocalLookAndFeel(Styles.LAF_displayIconSocialsButton);
	Instagram_btn.setControlCallback(onInsta);
	
	inline function onYT(component, value) {
		if (value) {Engine.openWebsite('https://www.youtube.com/channel/UCJfRn0mxY61a5cYVBqEc9Zg');}
	}
	
	inline function onInsta(component, value) {
		if (value) {Engine.openWebsite('https://www.instagram.com/sinuslabs.io/');}
	}
	
	Get_more_btn.setLocalLookAndFeel(Styles.LAF_displayButton);
	Get_more_btn.setControlCallback(onMore);
	Sinuslabs_Logo_btn.setLocalLookAndFeel(LAF_logo);
	Sinuslabs_Logo_btn.setControlCallback(onMore);
	inline function onMore(component, value) {
		if (value) {
			Engine.openWebsite('https://sinuslabs.io');
		}
	}
	
}