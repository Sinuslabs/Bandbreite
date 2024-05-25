namespace LogoAnimation {
	
	const var AnimationPanel = Content.getComponent("Product_Logo_pnl");
	const animation = Animations.logo;
	
	reg frame = 0;
	const frames = 89;
	const speed = 1;
	const timer = 30;
	
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	AnimationPanel.startTimer(30);
	
	inline function nextFrame() {	
		AnimationPanel.setAnimationFrame(frame);
		frame += speed;
		if (frame >= frames) frame = 0;
	}
}