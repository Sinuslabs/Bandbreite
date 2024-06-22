namespace LogoAnimation {
	
	const var AnimationPanel = Content.getComponent("Product_Logo_pnl");
	const animation = Animations.logo;
	
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	
	reg frame = 0;
	const frames = 89;
	reg speed = 1;
	const timer = 30;
	
	reg easingFactor = 0.05;
	reg isAnimating = false;
	
	const var logoTimer = Engine.createTimerObject();
	logoTimer.startTimer(400);
	logoTimer.setTimerCallback(onTimer);
	
	inline function onTimer() {
		local level = (InputGain.getCurrentLevel(0) + InputGain.getCurrentLevel(1)) / 2;
		if (level > 0.002 && level <= 1.0) {
			startAnimation();
		} else {
			LogoAnimation.stopAnimation();
		}
		
	}
	
	inline function nextFrame() {
	    if (!isAnimating) {
	        AnimationPanel.stopTimer();
	        return;
	    }
	    
	    AnimationPanel.setAnimationFrame(frame);
	    frame += speed;
	    if (frame >= frames) frame = 0;
	}
	
	inline function startAnimation() {
	    isAnimating = true;
	    AnimationPanel.startTimer(timer);
	}
	
	inline function stopAnimation() {
	    isAnimating = false;
	}
}