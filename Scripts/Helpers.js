namespace Helpers {
	
	inline function randomBool() {
        
        return Math.random() >= 0.5;
	}
	
	inline function randomBoolWithBias(bias) {
		
		local clampedBias = Math.max(-1.0, Math.min(1.0, bias));
		local randValue = Math.random();
		local threshold = 0.5 + clampedBias * 0.5;
		
		return randValue < threshold;
	}
}