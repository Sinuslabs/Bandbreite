namespace UserSettings {
	
	reg settingsObj = {
		
		'theme': 'light',
		'zoom': 1
	};
	
	const settingsDir = FileSystem.getFolder(FileSystem.UserPresets).getParentDirectory();
	const settingsFile = settingsDir.getChildFile('settings.json');
	
	inline function save(value, key) {
		settingsObj[value] = key;
		settingsFile.writeObject(settingsObj);
	}
	
	inline function load() {
		
		if (settingsExist()) {
			settingsObj = settingsFile.loadAsObject();
		}	
		restoreParameter();
	}
	
	inline function restoreParameter() {
		switch (settingsObj['theme']) {
			case 'light':
				Theme.setTheme('light');
				Header.ThemeSpinner_btn.setValue(1);
				break;
			case 'dark':
				Theme.setTheme('dark');
				Header.ThemeSpinner_btn.setValue(0);
				break;
			
			Header.ThemeSpinner_btn.changed();
		}
		
		Settings.setZoomLevel(settingsObj['zoom']);
	}
	
	inline function settingsExist() { return settingsFile.isFile();}
	
}