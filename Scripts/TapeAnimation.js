namespace TapeAnimation {
	
	reg frame = 0;
	const frames = 149;
	reg speed = 1.3;
	const timer = 30;
	const background_timer = 60;
	reg isRunning = false;
	reg tick = 0;
	
	const backwards = Helpers.randomBoolWithBias(0.6);
	
	reg flutter = 0;
	reg slam = 0;
	reg tape = 0.5;
	reg sweeten = 0;
	
	const animation = Animations.tape;
	const var AnimationPanel = Content.getComponent("TapeAnimation");
	AnimationPanel.startTimer(timer);
	
	const var TapeAnimation_wrapper_pnl = Content.getComponent("TapeAnimation_wrapper_pnl");
	TapeAnimation_wrapper_pnl.setPaintRoutine(tubeGlowRoutine);
	
	TapeAnimation_wrapper_pnl.setTimerCallback(function()
	{
		tick++;
		if (tick > 360) tick = 0;
		this.repaint(); 
	});
	
	TapeAnimation_wrapper_pnl.startTimer(background_timer);
	
	inline function setGlow(value) {
		tape = value;
		TapeAnimation_wrapper_pnl.setValue({'glow': value});
		TapeAnimation_wrapper_pnl.repaint();
	}
	
	inline function setFlutter(value) {
		flutter = value;
	}
	
	inline function setSlam(value) {
		slam = value * 4;
	}
	
	inline function setSweeten(value) {
		sweeten = value * 2.3;
	}
	
	inline function tubeGlowRoutine(g) {
		local a = this.getLocalBounds(12);
		local data = this.getValue();
		
		local min = 14;
		local max = 4;
		
		local size = 30.5;
		
		// precise positioning to match animation
		local left_dot_a = [
			38.7,
			41.2,
			size,
			size
		];
		
		local right_dot_a = [
			179.4,
			41.4,
			size,
			size
		];
		
		// flutter animation
		
		local swing_x = Math.sin(tick * 0.8 * flutter) * flutter / 2 * tape;
		local swing_y = Math.sin(tick * 0.9 * flutter) * flutter / 2 * tape;
		
		left_dot_a = [
			left_dot_a[0] + swing_x,
			left_dot_a[1] + swing_y,
			left_dot_a[2],
			left_dot_a[3]
		];
		
		right_dot_a = [
			right_dot_a[0] + swing_x + 0.039,
			right_dot_a[1] + swing_y + 0.069,
			right_dot_a[2],
			right_dot_a[3]
		];
		
		local amount = min + data.glow * (max - min);
		
		left_dot_a = StyleHelpers.addPadding(left_dot_a, amount);
		right_dot_a = StyleHelpers.addPadding(right_dot_a, amount);
		
		local dot_color = Colours.withAlpha(Theme.THEME.Colors.Effect.red, tape);
		
		g.setColour(dot_color);
		g.fillEllipse(left_dot_a);
		g.fillEllipse(right_dot_a);
		
		// Playhead SLAAAM!
		local playhead_a = [
			117.5,
			94.5,
			14,
			22
		];
		
		g.setColour(Theme.THEME.Colors.Display.on_display);
		g.drawPath(Assets.get.playhead, playhead_a, slam * tape);
		
		local circle_size = 15;
		
		// SOOOO SWEET
		local left_circle_a = [
			36 - circle_size,
			39 - circle_size,
			50 + circle_size,
			50 + circle_size
		];
		
		local right_circle_a = [
			177 - circle_size,
			39 - circle_size,
			50 + circle_size,
			50 + circle_size
		];
		
		g.setColour(Theme.THEME.Colors.Effect.red);
		if (backwards) {
			g.drawEllipse(left_circle_a, sweeten * tape);
		} else {
			g.drawEllipse(right_circle_a, sweeten * tape);
		}
	}
	
	// ANIMATION SETUP
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	
	inline function nextFrame() {	
		AnimationPanel.setAnimationFrame(frame);
		if (backwards) {
			frame -= speed;
			if (frame <= 0) frame = frames;
		} else {
			frame += speed;
			if (frame >= frames) frame = 0;
		}
	}
}