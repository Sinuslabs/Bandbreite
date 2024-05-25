namespace ThemeAnimation {
	
	const var AnimationPanel = Content.getComponent("ThemeSpinner_pnl");
	const animation = Animations.theme;
	
	reg frame = 0;
	const frames = 30;
	const speed = 1;
	const timer = 30;
	reg frame_stop = 15;
	
	inline function onClick(value) {
		AnimationPanel.startTimer(5);
		
		if (value) {
			frame_stop = 15;
		} else {
			frame_stop = 30;
		}
	}
	
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	
	inline function nextFrame() {	
		AnimationPanel.setAnimationFrame(frame);
		frame += speed;
		
		if (frame === frame_stop) {
			AnimationPanel.stopTimer();
		}
		
		if (frame >= frames) frame = 0;
	}
}