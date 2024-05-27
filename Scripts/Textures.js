namespace Textures {
	
	const var TextureKnobs = [Content.getComponent("Dust_knb"),
	                        Content.getComponent("Wear_knb"),
	                        Content.getComponent("Freq_knb"),
             	            Content.getComponent("Rez_knb")	];
	
	const var Dust_Control_Container = Content.getComponent("Textures_Container");
	
	Dust_Control_Container.setPaintRoutine(function(g){});
	
	for (knb in TextureKnobs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayTextKnob);
		knb.setControlCallback(onTextureKnobs);
	}
	
	inline function onTextureKnobs(component, value) {
		switch (component.getId()) {
			case 'Dust_knb':
				BandFX.setAttribute(BandFX.Textures_Dust, value);
				break;
			case 'Wear_knb':
				BandFX.setAttribute(BandFX.Textures_Wear, value);
				break;
			case 'Freq_knb':
				BandFX.setAttribute(BandFX.Textures_Freq, value);
				break;
			case 'Rez_knb':
				BandFX.setAttribute(BandFX.Textures, value);
				break;
		}
	}	
}