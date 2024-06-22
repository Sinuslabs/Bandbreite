namespace Styles {
	
	const LAF_displayIconButton = Content.createLocalLookAndFeel();
	LAF_displayIconButton.registerFunction("drawToggleButton", displayIconButtonLAF);
	inline function displayIconButtonLAF(g, obj) {
		local a = obj.area;
		local iconArea = StyleHelpers.addPadding(a, 0);
		local SIZE = 18;
		
		local width = a[2];
		local height = a[3];
		
		iconArea = StyleHelpers.withSizeKeepingCentre(a, 18, 18);
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		obj.over && g.setColour(Theme.THEME.Colors.Display.on_display);
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		}
		
		if (obj.text === 'youtube') {
			g.fillPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE + 20, SIZE]);
		} else {
			g.fillPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE, SIZE]);					
		}
	}
	
	const LAF_displayIconSocialsButton = Content.createLocalLookAndFeel();
	LAF_displayIconSocialsButton.registerFunction("drawToggleButton", displayIconSocialsButtonLAF);
	inline function displayIconSocialsButtonLAF(g, obj) {
		local a = obj.area;
		local iconArea = StyleHelpers.addPadding(a, 0);
		local SIZE = 25;
		
		local width = a[2];
		local height = a[3];
		
		iconArea = StyleHelpers.withSizeKeepingCentre(a, 15, 15);
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		obj.over && g.setColour(Theme.THEME.Colors.Display.on_display);
		
		if (obj.text.contains('$outline')) {
			obj.text = obj.text.replace('$outline', '');
			g.drawPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE, SIZE], 0.5);								
		} else {
			if (obj.text === 'youtube') {
				g.fillPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE + 5, SIZE]);
			} else {
				g.fillPath(Assets.get[obj.text], [iconArea[0], iconArea[1], SIZE, SIZE]);					
			}
		}
	}

	const LAF_displayBars = Content.createLocalLookAndFeel();
	LAF_displayBars.registerFunction('drawRotarySlider', displayBarsLAF);
	inline function displayBarsLAF(g, obj) {
		
		local a = obj.area;
		local BAR_HEIGHT = 1;
		local TEXT_HEIGHT = 1 - BAR_HEIGHT;
		local BORDER_RADIUS = 1;
		local BORDER_SIZE = 2;
		local BAR_PADDING = 10;
		local value = 1 - obj.valueNormalized;
		local upper_area = [a[0], a[1], a[2], a[3] * BAR_HEIGHT];
		local text_area = [a[0], a[3] * BAR_HEIGHT, a[2], a[3] * TEXT_HEIGHT];
	
		local container_area = StyleHelpers.addPadding(upper_area, BAR_PADDING);
		local bar_area = [
			container_area[0],
			container_area[1],
			container_area[2],
			container_area[3] * value
		];
		
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		g.drawRoundedRectangle(container_area, BORDER_RADIUS, BORDER_SIZE);
		g.fillRect(container_area);
		
		g.beginBlendLayer('Difference', 0);
		g.setColour(Theme.THEME.Colors.Effect.blue);
		g.fillRoundedRectangle([0,0, 10, 10], 2);
		g.endLayer();
		
		g.setColour(Colours.white);
		g.fillEllipse([0,0, 20, 20]);
		
		g.setFont(Theme.Regular, 12);
		g.drawAlignedText(obj.text, text_area, 'centred');
	}
	
	const var LAF_DisplayTextKnob = Content.createLocalLookAndFeel();	
	LAF_DisplayTextKnob.registerFunction('drawRotarySlider', DisplayTextKnob_LAF);
	
	inline function DisplayTextKnob_LAF(g, obj) {
		
		local a = obj.area;
		a = StyleHelpers.addPadding(a, 3);
		
		local upper_a = [
			a[0],
			a[1],
			a[2],
			a[3] * 0.6
		];
		
		local lower_a = [
			a[0],
			a[3] * 0.6,
			a[2],
			a[3] * 0.4
		];
		
		local valueText = obj.valueAsText;
		
		if (valueText === '0%') {
			if (obj.value < 0) {
				valueText = '-0.5%';
			}
		}
			
		local textA = StyleHelpers.addPadding(a, Primitives.Spacings.md);
		
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		if (obj.hover || obj.clicked) {
			
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
			g.drawRoundedRectangle(a, Primitives.BorderRadius.lg, Primitives.BorderSize.sm);
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
		
		if (obj.text === 'Low' || obj.text === 'High') {
			if (obj.value > 0) {
				valueText = '+' + valueText;
			}
		}
		
		if (!obj.enabled) {
			g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		};
		
		
		g.setFont(Theme.SemiBold, 23);
		g.drawAlignedText(valueText, upper_a, 'centred');
		g.setFont(Theme.Regular, 16);
		g.drawAlignedText(obj.text, lower_a, 'centred');
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
	
	const LAF_textButton = Content.createLocalLookAndFeel();
	LAF_textButton.registerFunction("drawToggleButton", textButtonLAF);
	inline function textButtonLAF(g, obj) {
		
		local a = obj.area;
		local textArea = StyleHelpers.addPadding(a, 4);
		
		g.setColour(Theme.THEME.Colors.Display.on_display_var);
		
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
		}
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.Display.on_display);
			g.drawLine(0, a[2], a[3] - 1, a[3] - 1, 1);
		}
		
		g.setFontWithSpacing(Theme.Regular, 18, 0.02);
		g.drawAlignedText(obj.text, textArea, "centred");
		
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
		local knobArea = [
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
		drawDisplayKnobLabel(g, text, a, knobArea);
		drawDisplayKnob(g, obj.valueNormalized, knobArea);
	};
	
	inline function drawDisplayKnob(g, value, knobArea)
	{
		local INDICATOR_THICKNESS = 2;
		local INDICATOR_LENGTH = 25;
		local INDICATOR_GAP = 0;
		local width = knobArea[2] + knobArea[0] * 2;
	
		local start = 2.5;
		local end = start * 2 * value - start;
		
		g.drawEllipse(knobArea, 1);
		g.rotate(end, [width / 2 , width / 2 ]);
		g.fillRoundedRectangle([
			width / 2 - (INDICATOR_THICKNESS / 2),
			knobArea[0] + INDICATOR_GAP,
			INDICATOR_THICKNESS,
		 	(width / 100 ) * INDICATOR_LENGTH],
		 	1
		);
	}
	
	inline function drawDisplayKnobLabel(g, label, a, padded_a)	{
		g.setFont(Theme.Regular, 12);			
		g.drawAlignedText(label, [a[0], padded_a[1] + padded_a[3] * 0.95, a[2], padded_a[3]], 'centred');
	}
	
	// DISPLAY SLIDER
	const LAF_displaySlider = Content.createLocalLookAndFeel();
	LAF_displaySlider.registerFunction('drawRotarySlider', displaySlidersLAF);
	inline function displaySlidersLAF(g, obj) {
		local a = obj.area;
		
		local DOT_SIZE = 9;
		local thickness = 1;
		
		local SLIDER_HEIGHT = 0.8;
		local LINE_THICKNESS = 2;
		local DOT_MAX_TRAVEL = 0.76;
		local DOT_RADIUS = 5;
		local LABEL_BOTTOM_PADDING = 14;
		
		local value = obj.valueNormalized;
		
		local x = a[2] / 2 - DOT_SIZE / 2 - Primitives.Spacings.md;
		local y = a[3] * DOT_MAX_TRAVEL * (1 - value);
		local tri_area = [x, y, DOT_SIZE, DOT_SIZE];
		
		local bottomPadding_a = [a[0], a[1], a[2], a[3] - LABEL_BOTTOM_PADDING];
		
		obj.enabled ?
			g.setColour(Theme.THEME.Colors.Display.on_display)
			: Theme.THEME.Colors.Display.on_display_disabled;
		
		g.fillTriangle(tri_area, Math.toRadians(90));
		
		g.setColour(Theme.THEME.Colors.Display.on_display_disabled);
		
		if (obj.hover) {
			g.setFont(Theme.Regular, 12);
			g.drawAlignedText(obj.valueAsText.replace(' dB', ''), bottomPadding_a, 'centredBottom');
			g.setFont(Theme.Regular, 14);
			g.drawAlignedText(obj.suffix, a, 'centredBottom');
		}
		
		g.drawLine(a[2] / 2, a[2] / 2, 0, a[3] * SLIDER_HEIGHT, LINE_THICKNESS);
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
		const SOCKEL_PADDING = 3;
		
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
			var knobArea = StyleHelpers.addPadding([a[0], a[1], a[2], a[2]], PADDING);
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
			var SOCKEL = Theme.THEME.Colors.Knob.knob_base;
			var BODY = Theme.THEME.Colors.Knob.knob_body;
			var BORDER_COLOUR = Theme.THEME.Colors.UI.surface_darkest;
			var TEXT_COLOUR = Theme.THEME.Colors.Knob.knob_accent;
			var SHADOW_COLOUR = Colours.withAlpha(Colours.black, 0.25);
			var TAPE_SOCKEL = Theme.THEME.Colors.Display.on_display_contrast;
			
			if (disabled) {
				ARC_COLOUR = Theme.THEME.Colors.Knob.knob_accent_disabled;
				INDICATOR_COLOUR = Theme.THEME.Colors.Knob.knob_accent_disabled;
				BODY = Theme.THEME.Colors.Knob.knob_body_disabled;
				BORDER_COLOUR = Theme.THEME.Colors.Knob.knob_outline;
				SHADOW_COLOUR = Colours.withAlpha(Colours.black, 0);
				TEXT_COLOUR = Theme.THEME.Colors.Knob.knob_accent_disabled;
			}
			
			if (obj.hover || obj.clicked) {
				text = obj.valueAsText;
			}
			
			g.setColour(SOCKEL);
			
			if (obj.text === 'Tape') {
				g.setColour(Colours.mix(
						Primitives.Colors.Base['100'],
						Primitives.Colors.Base['1000'],
						obj.valueNormalized));
			}
			
			if (obj.text === 'Tube') {
				g.setColour(Colours.mix(
						Primitives.Colors.Orange['100'],
						Primitives.Colors.Orange['600'],
						obj.valueNormalized));
			}
			
			if (obj.text === 'Sweeten') {
				g.setColour(Colours.mix(
						Primitives.Colors.Green['100'],
						Primitives.Colors.Purple['600'],
						obj.valueNormalized));
			}
			if (!obj.enabled) {
				g.setColour(Theme.THEME.Colors.Knob.knob_base_disabled);
			}
			
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
			g.drawEllipse(knobArea, 1);
			
			// INDICATOR
			g.setColour(INDICATOR_COLOUR);
			drawIndicator(g, obj.valueNormalized, knobArea);
	
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
			g.setFont(Theme.SemiBold, 16);			
			g.drawAlignedText(label, [a[0], padded_a[1] + padded_a[3] * 0.9, a[2], padded_a[3]], 'centred');
		}
		
		inline function drawIndicator(g, value, iconArea)
		{
			local INDICATOR_THICKNESS = 5;
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
	
	// BYPASS BUTTON
	const var LAF_BypasButton = Content.createLocalLookAndFeel();
	
	LAF_BypasButton.registerFunction('drawToggleButton', BypasButton_LAF);
	
	inline function BypasButton_LAF(g, obj) {
		
		local a = obj.area;
		a = StyleHelpers.addPadding(a, 7);
		
		local pa = StyleHelpers.addPadding(a, 3);
		
		g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
		g.drawEllipse(pa, 2);
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.UI.on_background);
			g.fillEllipse(pa);
		}
		
	}

}
