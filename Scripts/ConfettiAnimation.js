namespace ConfettiAnimation {
	
	const var AnimationPanel = Content.getComponent("Confetti_pnl");
	const animation = Animations.confetti;
	
	reg frame = 0;
	const frames = 36;
	const speed = 1;
	const timer = 30;
	
	inline function burstAnimation() {
		AnimationPanel.startTimer(timer);
	}
	
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	
	inline function nextFrame() {	
		AnimationPanel.setAnimationFrame(frame);
		frame += speed;
		if (frame >= frames) {
			frame = 0;
			AnimationPanel.stopTimer();
		}
	}
}