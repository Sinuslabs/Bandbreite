namespace Textures {

	const var TextureKnobs = [Content.getComponent("Dust_knb"),
	Content.getComponent("Wear_knb"),
	Content.getComponent("Noise_knb"),
	Content.getComponent("Bump_knb"),
	];

	const var Dust_Control_Container = Content.getComponent("Textures_Container");

	Dust_Control_Container.setPaintRoutine(function (g) { });

	for (knb in TextureKnobs) {
		knb.setLocalLookAndFeel(Styles.LAF_DisplayTextKnob);
		knb.setControlCallback(onTextureKnobs);
	}
	
	inline function onTextureKnobs(component, value) {
		switch (component.getId()) {
			case 'Dust_knb':
				FX.BandFX.setAttribute(FX.BandFX.Textures_Dust, value);
				break;
			case 'Wear_knb':
				FX.BandFX.setAttribute(FX.BandFX.Textures_Wear, value);
				break;
			case 'Noise_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_noise, value);
				break;
			case 'Bump_knb':
				FX.BandFX.setAttribute(FX.BandFX.Tape_Bump, value);
				break;
		}
	}
}