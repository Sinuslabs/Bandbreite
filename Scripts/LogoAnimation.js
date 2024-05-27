namespace LogoAnimation {
	
	const var AnimationPanel = Content.getComponent("Product_Logo_pnl");
	const animation = Animations.logo;
	
	AnimationPanel.setAnimation(animation);
	AnimationPanel.setTimerCallback(nextFrame);
	
	reg frame = 0;
	const frames = 89;
	const speed = 1;
	const timer = 30;
	
	reg easingFactor = 0.05;
	reg isAnimating = false;
	
	inline function nextFrame() {
	    if (!isAnimating && speed <= 0) {
	        AnimationPanel.stopTimer();
	        return;
	    }
	    
	    if (isAnimating && speed < maxSpeed) {
	        speed += easingFactor;
	    } else if (!isAnimating && speed > 0) {
	        speed -= easingFactor;
	    }
	    
	    AnimationPanel.setAnimationFrame(frame);
	    frame += speed;
	    if (frame >= frames) frame = 0;
	}
	
	inline function startAnimation() {
	    isAnimating = true;
	    AnimationPanel.startTimer(timerInterval);
	}
	
	inline function stopAnimation() {
	    isAnimating = false;
	}
}