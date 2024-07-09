namespace About {
	
	const INFO = {
		name: 'Bandbreite',
		homepage: 'https://sinuslabs.io',
		repository: 'https://github.com/Sinuslabs/Bandbreite',
		latest_release_windows: '/releases/latest/download/Bandbreite-Windows.exe',
		latest_release_macos: '/releases/latest/download/Bandbreite-MacOS.pkg',
		latest_release_linux: '/releases/latest/'
	};

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
	const var Soundcloud_btn = Content.getComponent("Soundcloud_btn");
	const var UpdateNow_btn = Content.getComponent("UpdateNow_btn");
	
	UpdateNow_btn.showControl(false);
	
	if (Globals.OS === 'LINUX') {
		UpdateNow_btn.set('text', 'Check update');
	}
	
	Youtube_btn.setLocalLookAndFeel(Styles.LAF_displayButton);
	Youtube_btn.setControlCallback(onYT);
	Instagram_btn.setLocalLookAndFeel(Styles.LAF_displayButton);
	Instagram_btn.setControlCallback(onInsta);
	Soundcloud_btn.setLocalLookAndFeel(Styles.LAF_displayButton);
	Soundcloud_btn.setControlCallback(onSoundcloud);
	UpdateNow_btn.setLocalLookAndFeel(Styles.LAF_displayButtonOutline);
	UpdateNow_btn.setControlCallback(onUpdateNow);
	
	inline function onUpdateNow(component, value) {
		
		if (value) {
		
			switch(Globals.OS) {
				case 'WIN':
					Engine.openWebsite(INFO.repository + INFO.latest_release_windows);
					break;
				case 'OSX':
					Engine.openWebsite(INFO.repository + INFO.latest_release_macos);
					break;
				case 'LINUX':
					Engine.openWebsite(INFO.repository + INFO.latest_release_linux);
					break;
			}	
		}
		
	}
	
	inline function onYT(component, value) {
		if (value) {Engine.openWebsite('https://www.youtube.com/channel/UCJfRn0mxY61a5cYVBqEc9Zg');}
	}
	
	inline function onInsta(component, value) {
		if (value) {Engine.openWebsite('https://www.instagram.com/sinuslabs.io/');}
	}
	
	inline function onSoundcloud(component, value) {
		if (value) {Engine.openWebsite('https://soundcloud.com/sinuslabs');}
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