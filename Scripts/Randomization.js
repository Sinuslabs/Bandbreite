namespace Randomization {
	
	const var randomPanelButton = Content.getComponent("randomize_pnl_btn");
	
	randomPanelButton.setPaintRoutine(randomPanelRoutine);
	randomPanelButton.setMouseCallback(onRandomPanel);
	
	inline function onRandomPanel(event) {
		if (event.rightClick && event.result) {
			Router.goTo('PresetBrowser');
		}
		
		if (event.clicked && !event.mouseUp) {
			randomPanelButton.repaint();
			randomPreset();
		}
	}
	
	inline function randomPreset() {
		
		Engine.loadNextUserPreset(true);
		Engine.performUndoAction(
			{},
			function(isUndo) {
				if (isUndo) Engine.loadPreviousUserPreset(true);
			});
		
	}
	
	inline function randomPanelRoutine(g) {
	    local a = this.getLocalBounds(0);
	    
	    // Define the padding value
	    local padding = 8;
	
	    // Adjust the width and height by subtracting twice the padding (for both sides)
	    local width = a[2] - 2 * padding;
	    local height = a[3] - 2 * padding;
	
	    // Calculate the width and height of each cell
	    local cellWidth = width / 3;
	    local cellHeight = height / 3;
	
	    // Determine the sizes of the ellipses based on the smaller dimension of the cell
	    local smallSize = Math.min(cellWidth, cellHeight) * 0.4; // 50% of the smallest dimension of the cell
	    local bigSize = Math.min(cellWidth, cellHeight) * 0.6; // 80% of the smallest dimension of the cell
	
	    // Set the color for drawing
	    local COLOUR = Theme.THEME.Colors.Display.on_display;
	
	    // Change color on mouse down
	    if (this.data.mouseDown) {
	        COLOUR = COLOUR.replace('0x', '0x' + PanelTheme.hoverOpacity);
	    }
	
	    g.setColour(COLOUR);
	
	    for(i = 0; i < 3; i++) {
	        for(j = 0; j < 3; j++) {
	            // Calculate the center of each ellipse taking into account the padding
	            local centerX = padding + (j + 0.5) * cellWidth;
	            local centerY = padding + (i + 0.5) * cellHeight;
	
	            local ellipseSize = Math.randInt(0, 2) == 0 ? smallSize : bigSize;
	
	            g.fillEllipse([
	                centerX - ellipseSize / 2, 
	                centerY - ellipseSize / 2, 
	                ellipseSize, 
	                ellipseSize
	            ]);
	        }
	    }
	}
}