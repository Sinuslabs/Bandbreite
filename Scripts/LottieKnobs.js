namespace LottieKnobs {
	
	const var LAF_lottieKnob = Content.createLocalLookAndFeel();
	LAF_lottieKnob.registerFunction('drawRotarySlider', function(g, obj) {
		var a = obj.area;
		var bottom_padding = Primitives.Spacings.md;
		a = [
			a[0], a[1], a[2], a[3] - bottom_padding
		];
		g.setColour(Theme.THEME.Colors.Display.on_display);
		g.setFont(Theme.Regular, 12);
		g.drawAlignedText(obj.text, a, 'centredBottom');
	});
	
	// --- Brightness Mid ----

	const Brightness_animation = Animations.brightness;
	const Brightness_Mid_Lottie_Frames = 149;
	
	const var Brightness_Mid_Container = Content.getComponent("Pocky_Brightness_Mid_Container");
	const var Brightness_Mid_knb = Content.getComponent("Pocky_Brightness_Mid_knb");
	const var Brightness_Mid_Lottie_pnl = Content.getComponent("Pocky_Brightness_Mid_Lottie_pnl");
	
	Brightness_Mid_knb.setLocalLookAndFeel(LAF_lottieKnob);
	Brightness_Mid_Container.setPaintRoutine(function(g){});
	
	Brightness_Mid_Lottie_pnl.setAnimation(Brightness_animation);
	
	inline function Brightness_Mid_SetFrame(value) {
		Brightness_Mid_Lottie_pnl.setAnimationFrame(value * Brightness_Mid_Lottie_Frames);
	}
	
	// --- Brightness Side ----
	
	const Brightness_Side_Lottie_Frames = 149;
	
	const var Brightness_Side_Container = Content.getComponent("Pocky_Brightness_Side_Container");
	const var Brightness_Side_knb = Content.getComponent("Pocky_Brightness_Side_knb");
	const var Brightness_Side_Lottie_pnl = Content.getComponent("Pocky_Brightness_Side_Lottie_pnl");
	
	
	Brightness_Side_knb.setLocalLookAndFeel(LAF_lottieKnob);
	Brightness_Side_Container.setPaintRoutine(function(g){});
	
	Brightness_Side_Lottie_pnl.setAnimation(Brightness_animation);
	
	inline function Brightness_Side_SetFrame(value) {
	  Brightness_Side_Lottie_pnl.setAnimationFrame(value * Brightness_Side_Lottie_Frames);
	}
	
	// --- Punch Mid ----
	
	const Punch_animation = Animations.punch;
	const Punch_animation_frames = 179;
	
	const var Punch_Mid_Container = Content.getComponent("Pocky_Punch_Mid_Container");
	const var Punch_Mid_knb = Content.getComponent("Pocky_Punch_Mid_knb");
	const var Punch_Mid_Lottie_pnl = Content.getComponent("Pocky_Punch_Mid_Lottie_pnl");
	
	Punch_Mid_knb.setLocalLookAndFeel(LAF_lottieKnob);
	Punch_Mid_Container.setPaintRoutine(function(g){});
	
	Punch_Mid_Lottie_pnl.setAnimation(Punch_animation);
	
	inline function Punch_Mid_SetFrame(value) {
	  Punch_Mid_Lottie_pnl.setAnimationFrame(value * Punch_animation_frames);
	}
	
	// --- Punch Mid ----
	
	const var Punch_Side_Container = Content.getComponent("Pocky_Punch_Side_Container");
	const var Punch_Side_knb = Content.getComponent("Pocky_Punch_Side_knb");
	const var Punch_Side_Lottie_pnl = Content.getComponent("Pocky_Punch_Side_Lottie_pnl");
	
	Punch_Side_knb.setLocalLookAndFeel(LAF_lottieKnob);
	Punch_Side_Container.setPaintRoutine(function(g){});
	
	Punch_Side_Lottie_pnl.setAnimation(Punch_animation);
	
	inline function Punch_Side_SetFrame(value) {
	  Punch_Side_Lottie_pnl.setAnimationFrame(value * Punch_animation_frames);
	}
	
}