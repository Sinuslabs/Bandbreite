namespace TapeAnimation {
	
	reg frame = 0;
	const frames = 149;
	const speed = 1;
	const timer = 30;
	
	const animation = Animations.tape;
	const var AnimationPanel = Content.getComponent("TapeAnimation");
	
	// ANIMATION SETUP
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	AnimationPanel.startTimer(30);
	
	inline function nextFrame() {	
		AnimationPanel.setAnimationFrame(frame);
		frame += speed;
		if (frame >= frames) frame = 0;
	}
	
}