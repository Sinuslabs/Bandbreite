namespace Tape {

	const var Controls = [Content.getComponent("Tape_Slam_knb"),
	Content.getComponent("Tape_Low_knb"),
	Content.getComponent("Tape_High_knb"),
	Content.getComponent("Tape_Flutter_knb"),
	Content.getComponent("Tape_Dust_knb")
	];

	const var Tape_Control_Container = Content.getComponent("Tape_Control_Container");
	Tape_Control_Container.setPaintRoutine(function (g) { });

	for (knb in Controls) {
		knb.setControlCallback(onControl);
		knb.setLocalLookAndFeel(Styles.LAF_DisplayTextKnob);
	}
	
	inline function onControl(component, value) {
		switch (component.getId()) {
			case 'Tape_Slam_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_Slam, value);
				TapeAnimation.setSlam(value);
			case 'Tape_Bump_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_Bump, value);
			case 'Tape_Low_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_low, value + 0.5);
			case 'Tape_High_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_high, value + 0.5);
			case 'Tape_Flutter_knb':
				FX.BandFX.setAttribute(FX.BandFX.Flutter, value);
				TapeAnimation.setFlutter(value);
			case 'Tape_Dust_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_noise, value);
				TapeAnimation.setSweeten(value);
		}
	}
}