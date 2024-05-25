namespace Tape {
	
	const var Controls = [Content.getComponent("Tape_Fatter_knb"),
	                      Content.getComponent("Tape_Louder_knb"),
	                      Content.getComponent("Tape_Softer_knb"),
	                      Content.getComponent("Tape_Flutter_knb")];
	
	const var Tape_Control_Container = Content.getComponent("Tape_Control_Container");
	Tape_Control_Container.setPaintRoutine(function (g) {});
	
	for (knb in Controls) {
		knb.setControlCallback(onControl);
		knb.setLocalLookAndFeel(Styles.LAF_DisplayTextKnob);
	}
	
	inline function onControl(component, value) {
		switch(component.getId()) {
			case 'Tape_Fatter_knb':
				BandFX.setAttribute(BandFX.Fatter, value);
			case 'Tape_Louder_knb':
				BandFX.setAttribute(BandFX.Louder, value);
			case 'Tape_Softer_knb':
				BandFX.setAttribute(BandFX.Softer, value);
			case 'Tape_Flutter_knb':
				BandFX.setAttribute(BandFX.Flutter, value);
		}
		
	}
	
}