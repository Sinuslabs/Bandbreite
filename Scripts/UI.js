namespace UI {
	
	const var background = Content.getComponent("background");
	const var display = Content.getComponent("display");
	const var Controls_Container = Content.getComponent("MainPanel_Controls_Container");
	
	Theme.registerThemePanel(background);
	background.setPaintRoutine(function(g) {
	
		var a = this.getLocalBounds(0);
		
		g.fillAll(Theme.THEME.Colors.UI.background);
		g.addNoise({
				alpha: 0.06,
				monochromatic: false,
				scaleFactor: 1.7,
				area: a
			});
	});
	
	display.setPaintRoutine(function(g)
	{
		var a = this.getLocalBounds(2);
		g.setColour(Theme.THEME.Colors.Display.display);
		g.fillRoundedRectangle(a, Primitives.BorderRadius.lg);
		g.setColour(Colours.black);
		g.drawRoundedRectangle(a, Primitives.BorderRadius.lg, Primitives.BorderSize.lg);
		g.addNoise({
				alpha: 0.04,
				monochromatic: false,
				scaleFactor: 1.7,
				area: a
			});
	});	
}