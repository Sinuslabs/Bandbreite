namespace Styles {
	
	const var LAF_DisplayTextKnob = Content.createLocalLookAndFeel();
	
	LAF_DisplayTextKnob.registerFunction('drawRotarySlider', DisplayTextKnob_LAF);
	
	inline function DisplayTextKnob_LAF(g, obj) {
		local a = obj.area;
		
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		if (obj.over) {
			g.setColours(Theme.THEME.Colors.Display.on_display);
		}
		
		g.setFont(Theme.SemiBold, 18);
		g.drawAlignedText(obj.valueSuffixString, a, 'centredTop');
		g.setFont(Theme.Regular, 14);
		g.drawAlignedText(obj.text, a, 'centredBottom');
	}
	
	const LAF_displayButton = Content.createLocalLookAndFeel();
	LAF_displayButton.registerFunction('drawToggleButton', displayButtonLAF);
	
	inline function displayButtonLAF(g, obj) {
		
		local a = obj.area;
		local paddedA = StyleHelpers.addPadding(a, 1);
		local textA = StyleHelpers.addPadding(paddedA, 9);
		local BORDER_RADIUS = 2;
		
		if (obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		g.drawRoundedRectangle(paddedA, BORDER_RADIUS, 1);
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
			g.fillRoundedRectangle(paddedA, BORDER_RADIUS);
			g.setColour(Theme.THEME.Colors.Display.on_display_contrast);
		}
		
		g.setFont(Theme.Regular, 14);
		g.drawAlignedText(obj.text, textA, 'centred');
	}
	
	const LAF_displayKnob = Content.createLocalLookAndFeel();
	LAF_displayKnob.registerFunction("drawRotarySlider", displayKnobLAF);
	inline function displayKnobLAF(g, obj) {
		local PADDING = 6;
		local start = 2.5;
		local end = start * 2 * obj.valueNormalized - start;
		local a = obj.area;
		local text = obj.text;
		
		// special padded area
		local iconArea = [
			PADDING,
			PADDING,
			a[2] - PADDING * 2,
			a[2] - PADDING * 2
		];
		
		obj.enabled ? 
			g.setColour(Theme.THEME.Colors.Display.on_display) :
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		if (obj.clicked || obj.hover) {
			text = StyleHelpers.labelToValue(obj);
		}
		
		drawArc(g, a[2], start, end);
		drawDisplayKnobLabel(g, text, a, iconArea);
		drawDisplayKnob(g, obj.valueNormalized, iconArea);
	};
	
	inline function drawDisplayKnob(g, value, iconArea)
	{
		local INDICATOR_THICKNESS = 2;
		local INDICATOR_LENGTH = 25;
		local INDICATOR_GAP = 0;
		local width = iconArea[2] + iconArea[0] * 2;
	
		local start = 2.5;
		local end = start * 2 * value - start;
		
		g.drawEllipse(iconArea, 1);
		g.rotate(end, [width / 2 , width / 2 ]);
		g.fillRoundedRectangle([
			width / 2 - (INDICATOR_THICKNESS / 2),
			iconArea[0] + INDICATOR_GAP,
			INDICATOR_THICKNESS,
		 	(width / 100 ) * INDICATOR_LENGTH],
		 	1
		);
	}
	
	inline function drawDisplayKnobLabel(g, label, a, padded_a)	{
		g.setFont(Theme.Regular, 12);			
		g.drawAlignedText(label, [a[0], padded_a[1] + padded_a[3] * 0.95, a[2], padded_a[3]], 'centred');
	}	
	
	// DEFAULT KNOB
	const LAF_Knob = Content.createLocalLookAndFeel();
		
		// KNOBS LOOK AND FEEL
		// GENERAL
		const DISABLED_OPACITY = 'CC';
		
		// ARC
		const ARC_THICKNESS = 2;
		const ARC_PADDING = 0;
		
		// SOCKEL
		const SOCKEL_PADDING = 3.5;
		
		// INDICATOR
		const INDICATOR_THICKNESS = 6;
		const INDICATOR_LENGTH = 9;
		const INDICATOR_BORDER_RADIUS = 2;
		const INDICATOR_GAP = 5;
		
		// MAIN BODY
		const BORDER = 2 ;
		
		// SHADOW
		const SHADOW_RADIUS = 5;
		const SHADOW_OFFSET = [0, 4];
		const SHADOW_PADDING = 5;
		
		LAF_Knob.registerFunction("drawRotarySlider", function(g, obj){
			
			var a = obj.area;
			// Padding
			var PADDING = 8;
			
			var disabled = !obj.enabled;
			var start = 2.5;
			var end = start * 2 * obj.valueNormalized - start;
			
			var text = obj.text;
			
			var sockelA = StyleHelpers.addPadding([a[0], a[1], a[2], a[2]], SOCKEL_PADDING);
			var knobAreaBorder = StyleHelpers.addPadding([a[0], a[1], a[2], a[2]], PADDING);
			var knobArea = StyleHelpers.addPadding(knobAreaBorder, BORDER);
			var sa = StyleHelpers.addPadding([a[0], a[1], a[2], a[2]], PADDING + SHADOW_PADDING);
			
			// special padded area
			var labelArea = [
				PADDING,
				PADDING,
				a[2] - PADDING * 2,
				a[2] - PADDING * 2
			];
			
			// Colours
			var ARC_COLOUR = Theme.THEME.Colors.Knob.knob_accent;
			var INDICATOR_COLOUR = Theme.THEME.Colors.Knob.knob_accent;
			var SOCKEL = Theme.THEME.Colors.Knob.knob_body;
			var BODY = Theme.THEME.Colors.Knob.knob_body;
			var BORDER_COLOUR = Theme.THEME.Colors.Knob.knob_outline;
			var TEXT_COLOUR = Theme.THEME.Colors.Knob.knob_accent;
			var SHADOW_COLOUR = Colours.black;
			
			if (disabled) {
				// Special case for the ARC Colour since its black transparency is not doing much
				ARC_COLOUR = Theme.THEME.Colors.Knob.knob_accent_disabled;
				INDICATOR_COLOUR = Theme.THEME.Colors.Knob.knob_accent_disabled;
				BODY = Theme.THEME.Colors.Knob.knob_body_disabled;
				LOWER_GRADIENT = Theme.THEME.Colors.Knob.knob_body_disabled;
				BORDER_COLOUR = Theme.THEME.Colors.Knob.knob_outline;
				SHADOW_COLOUR = Colours.withAlpha(Colours.black, 0);
				TEXT_COLOUR = Theme.THEME.Colors.Knob.knob_accent_disabled;
			}
			
			if (obj.hover) {
				text = obj.valueSuffixString;
			}
			
			g.setColour(BODY);
			g.fillEllipse(sockelA);
			
			g.setColour(ARC_COLOUR);
			drawArc(g, a[2], start, end);
						
			g.setColour(TEXT_COLOUR);
			drawLabel(g, text.toUpperCase(),a, labelArea);
			
			drawShadow(g, disabled, sa, SHADOW_COLOUR);
			
			// MAIN BODY
			g.setColour(BODY);
			g.fillEllipse(knobArea);
			
			// BORDER
			g.setColour(BORDER_COLOUR);
			g.drawEllipse(knobAreaBorder, 1);
			
			// INDICATOR
			g.setColour(INDICATOR_COLOUR);
			drawIndicator(g, obj.valueNormalized, knobAreaBorder);
	
		});
		
		inline function drawShadow(g, disabled, area, SHADOW_COLOUR,) {
			local shadowPath = Content.createPath();
			shadowPath.addArc([0.0, 0.0, 1.0, 1.0], 0, Math.PI * 2);
			if (!disabled) {
				g.drawDropShadowFromPath(
					shadowPath,
					area,
					SHADOW_COLOUR,
					SHADOW_RADIUS, SHADOW_OFFSET
				);
			
			}
		}
	
		inline function drawLabel(g, label, a, padded_a)	{
			g.setFont(Theme.SemiBold, 12);			
			g.drawAlignedText(label, [a[0], padded_a[1] + padded_a[3] * 0.95, a[2], padded_a[3]], 'centred');
		}
		
		inline function drawIndicator(g, value, iconArea)
		{
			local INDICATOR_THICKNESS = 4;
			local INDICATOR_LENGTH = 10;
			local INDICATOR_GAP = 5;
			local width = iconArea[2] + iconArea[0] * 2;
			local INDICATOR_BORDER_RADIUS = 2;
		
			local start = 2.5;
			local end = start * 2 * value - start;
			
			g.rotate(end, [width / 2 , width / 2 ]);
			g.fillRoundedRectangle([
				width / 2 - (INDICATOR_THICKNESS / 2),
				iconArea[0] + INDICATOR_GAP,
				INDICATOR_THICKNESS,
			 	(width / 100 ) * INDICATOR_LENGTH],
			 	INDICATOR_BORDER_RADIUS
			);
		}
	
	inline function drawArc(g, stableSize, start, end)
	{
		local ARC_THICKNESS = 2;
		
		local arcThickness = ARC_THICKNESS / 100;
		local arcWidth = (1.0 - 2.0 * arcThickness) + arcThickness;
		
		local arcPath = Content.createPath();
		arcPath.addArc(
			[arcThickness / 2, arcThickness / 2,arcWidth , arcWidth],
			-start,
			end
		 );
		
		local pathArea = arcPath.getBounds(stableSize);
		pathArea = [pathArea[0], pathArea[1], pathArea[2], pathArea[3]];
		g.drawPath(arcPath, pathArea, stableSize * arcThickness );
	}

}
