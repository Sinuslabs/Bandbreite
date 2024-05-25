namespace Tape {
	
	const var Controls = [Content.getComponent("Tape_Fatter_knb"),
	                      Content.getComponent("Tape_Louder_knb"),
	                      Content.getComponent("Tape_Softer_knb"),
	                      Content.getComponent("Tape_Flutter_knb")];
	
	for (knb in Controls) {
		knb.setControlCallback(onControl);
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