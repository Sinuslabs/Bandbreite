namespace Tape {
	
	const var Controls = [Content.getComponent("Tape_Slam_knb"),
	                      Content.getComponent("Tape_Low_knb"),
	                      Content.getComponent("Tape_High_knb"),
	                      Content.getComponent("Tape_Flutter_knb"),
	                      Content.getComponent("Tape_Sweeten_knb")
	                      ];
	
	const var Tape_Control_Container = Content.getComponent("Tape_Control_Container");
	Tape_Control_Container.setPaintRoutine(function (g) {});
	
	for (knb in Controls) {
		knb.setControlCallback(onControl);
		knb.setLocalLookAndFeel(Styles.LAF_DisplayTextKnob);
	}
	
	inline function onControl(component, value) {
		switch(component.getId()) {
			case 'Tape_Slam_knb':
				BandFX.setAttribute(BandFX.Tape_Slam, value);
				TapeAnimation.setSlam(value);
			case 'Tape_Bump_knb':
				BandFX.setAttribute(BandFX.Tape_Bump, value);
			case 'Tape_Low_knb':
				BandFX.setAttribute(BandFX.Tape_low, value);
			case 'Tape_High_knb':
				BandFX.setAttribute(BandFX.Tape_high, value);
			case 'Tape_Flutter_knb':
				BandFX.setAttribute(BandFX.Flutter, value);
				TapeAnimation.setFlutter(value);
			case 'Tape_Sweeten_knb':
				BandFX.setAttribute(BandFX.Tape_Sweeten, value);
				TapeAnimation.setSweeten(value);
		}		
	}
}