namespace Theme {
    
    //FONTS
    Engine.loadFontAs("{PROJECT_FOLDER}Fonts/Inter-SemiBold.ttf", "inter-semi");
    Engine.loadFontAs("{PROJECT_FOLDER}Fonts/Inter-Regular.ttf", "inter-reg");
    Engine.setGlobalFont("inter-semi");
    
    reg THEME = ThemeData.LIGHT_THEME;
	const SemiBold = 'inter-semi';
	const Regular = 'inter-reg';
    
    inline function setTheme(theme) {
	    if (theme === 'light') {
		    THEME = ThemeData.LIGHT_THEME;
	    }
	    
	    if (theme === 'dark') {
  			THEME = ThemeData.DARK_THEME;
	    }
	    
	    UserSettings.save('theme', theme);
	    repaintAll();
    }
    
    inline function toggleTheme(value) {
	    if (value) {
		    setTheme('light');
	    } else {
		    setTheme('dark');
	    }
    }
    
    
    reg panels = [];
    reg knobs = [];
    
    inline function repaintAll() {
	    
	    for (pnl in panels) {
		    pnl.repaint();
	    }
	    
	    for (knb in knobs) {
		    knb.sendRepaintMessage();
	    }
    }
    
    inline function registerThemePanel(panel) {
	    panels.push(panel);
    }
    
    inline function registerThemeComponent(component) {
	    knobs.knobs();
    }
}