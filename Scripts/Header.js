namespace Header {
	
	//invisble click btn
	const var extra_click_area_btn = Content.getComponent("extra_click_area_btn");

	const var LAF_breitband_btn = Content.createLocalLookAndFeel();
	LAF_breitband_btn.registerFunction('drawToggleButton', breitband_btn_laf);
	
	const var Update_btn = Content.getComponent("Update_btn");
	Update_btn.setControlCallback(onUpdateBtn);
	Update_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);
	
	Update_btn.showControl(false);
	
	const var Breitband_btn = Content.getComponent("Breitband_btn");
	Breitband_btn.setLocalLookAndFeel(LAF_breitband_btn);
	Breitband_btn.setControlCallback(onBreitband);
	
	const var Oversample_pnl = Content.getComponent("Oversample_pnl");
	const var Oversample_knb = Content.getComponent("Oversample_knb");
	
	Oversample_knb.setControlCallback(onOversample);
	Oversample_pnl.setPaintRoutine(oversampleRoutine);
	
	Oversample_pnl.setValue({
		oversample: 0,
		hover: 0
	});
	
	
	Oversample_pnl.setMouseCallback(function(event) {
	
		var data = this.getValue();
		var oversample;
	
		if (event.clicked) {
			oversample = (data.oversample + 1) % 3;
			Oversample_knb.setValue(oversample);
			Oversample_knb.changed();			
		}
	});
	

	const var LAF_hiddenBTN = Content.createLocalLookAndFeel();
	LAF_hiddenBTN.registerFunction('drawToggleButton', hiddenBtn_LAF);
	
	extra_click_area_btn.setLocalLookAndFeel(LAF_hiddenBTN);
	extra_click_area_btn.setControlCallback(onBackToTape);
	
	const var Product_Logo_btn = Content.getComponent("Product_Logo_btn");	
	const var ThemeSpinner_btn = Content.getComponent("ThemeSpinner_btn");
	const var Bypass_btn = Content.getComponent("Bypass_btn");
	const var Hot_btn = Content.getComponent("Hot_btn");
	
	Bypass_btn.setLocalLookAndFeel(Styles.LAF_BypasButton);
	Bypass_btn.setControlCallback(onBypass);
	
	Hot_btn.setLocalLookAndFeel(Styles.LAF_displayIconButton);
	Hot_btn.setControlCallback(onHot);
	
	inline function onUpdateBtn(component, value) {
		Router.goTo('About');
	}
	
	inline function onHot(component, value) {
		if (value) {
			component.set('text', 'scream');
			BandFX.setAttribute(BandFX.Hot, 3);	
		} else {
			component.set('text', 'worried');
			BandFX.setAttribute(BandFX.Hot, 0);
		}
	}
	
	inline function onOversample(component, value) {
		
		BandFX.setAttribute(BandFX.oversample, value);
		
		local newData = {
			hover: event.hover,
			oversample: value
		};
		
		Oversample_pnl.setValue(newData);
		Oversample_pnl.repaint();		
	}
	
	inline function onBypass(component, value) {
		
		Main_Controls.Container.set('enabled', !value);
		Tape.Tape_Control_Container.set('enabled', !value);
		Hot_btn.set('enabled', !value);
		TapeAnimation.TapeAnimation_wrapper_pnl.set('visible', !value);
		TapeAnimation.AnimationPanel_overlay.set('visible', value);
		Main_Controls.Gains[0].set('enabled', !value);
		Main_Controls.Gains[1].set('enabled', !value);
		if (value) {
			TapeAnimation.AnimationPanel.stopTimer();
		} else {
			TapeAnimation.AnimationPanel.startTimer(TapeAnimation.timer);
		}
		InputGain.setBypassed(value);
		BandFX.setBypassed(value);
		OutGain.setBypassed(value);
	}

	// sync to theme
	ThemeSpinner_btn.setValue(0);
	ThemeSpinner_btn.setControlCallback(onTheme);
	ThemeSpinner_btn.setLocalLookAndFeel(LAF_hiddenBTN);
	
	Product_Logo_btn.setLocalLookAndFeel(LAF_hiddenBTN);
	Product_Logo_btn.setControlCallback(onLogo);
	
	inline function onBreitband(component, value) {
		Product_Logo_btn.setValue(1);
		Product_Logo_btn.changed();
	}
	
	inline function onBackToTape(component, value) {
		if (value) {
			Router.goTo('Tape');
		}
	}
	
	inline function onLogo(component, value) {
		
		if (Router.currentRoute === 'About') {
			Breitband_btn.setValue(0);
			Router.goTo('Tape');
			return;
		}
		
		Breitband_btn.setValue(1);
		Router.goTo('About');
	}
	
	reg clickCounter = 0;
	const var clickThreshold = 5; // Number of clicks required to trigger custom function
	const var decreaseInterval = 500;
	const var decraseClick = 0.5;
	
	const var easteregg_timer = Engine.createTimerObject();
	easteregg_timer.setTimerCallback(onEastereggTimer);
	
	inline function onTheme(component, value) {
	
		Theme.toggleTheme(value);	
		ThemeAnimation.onClick(value);
		
		clickCounter++;
		
		if (!easteregg_timer.isTimerRunning()) {
				easteregg_timer.startTimer(decreaseInterval);
		}
	}
	
	inline function onEastereggTimer() {
		Console.print(clickCounter);
		clickCounter = clickCounter - decraseClick;

		if (clickCounter <= 0) easteregg_timer.stopTimer();
		if (clickCounter >= clickThreshold) {
			Router.goTo('Easteregg');
			ConfettiAnimation.burstAnimation();			
			easteregg_timer.stopTimer();
			clickCounter = 0;
			Product_Logo_btn.setValue(0);
			Breitband_btn.setValue(0);
		}
	}
	
	inline function hiddenBtn_LAF(g, obj) {
		local a = obj.area;
		a = StyleHelpers.addPadding(a, 1);
		g.setColour(Colours.withAlpha(Colours.black, 0.2));
		
		if (Router.currentRoute === 'About') {
			if (obj.text === 'Product_Logo_btn') {
				return;
			}
		}
	
		if (!obj.over) {
			g.fillRoundedRectangle(a, Primitives.BorderRadius.sm);
		}
		

	}
	
	inline function breitband_btn_laf(g, obj) {
		local a = obj.area;
		g.rotate(Math.toRadians(90), [a[2] / 2, a[3] / 2]);
		
		a = [
			-55,
			a[1],
			125,
			a[3]
		];
		
		g.setColour(Theme.THEME.Colors.UI.background);
		g.fillRect(a);
		g.setColour(Theme.THEME.Colors.UI.on_background_text_disabled);
				
		if (obj.over) {
			g.setColour(Theme.THEME.Colors.UI.on_background_var);
		}
		
		if (obj.value) {
			g.setColour(Theme.THEME.Colors.UI.on_background_var);
		}	
	
		g.setFont(Theme.SemiBold, 20);
		g.drawAlignedText('BANDBREITE', a, 'centred');
		
		g.addNoise({
				alpha: 0.04,
				monochromatic: false,
				scaleFactor: 1.7,
				area: a
			});		
	}
	
	inline function oversampleRoutine(g, obj) {
		
		local a = this.getLocalBounds(0);
		local data = this.getValue();
		local oversample = data.oversample;
		local text = '1X';
		
		if (obj.value || data.hover) {
			g.setColour(Theme.THEME.Colors.Display.on_display);			
		} else {
			g.setColour(Theme.THEME.Colors.Display.on_display_var);
		}
		
		g.setFont(Theme.Regular, 22);
		
		switch(oversample) {
			case 0: 
				text = '1X';
				break;
			case 1: 
				text = '2X';
				break;
			case 2: 
				text = '4X';
				break;
		}
		
		g.drawAlignedText(text, a, 'centred');
		
	}
	
	
	
}