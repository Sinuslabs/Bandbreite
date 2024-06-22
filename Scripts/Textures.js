namespace Textures {

	const var TextureKnobs = [Content.getComponent("Dust_knb"),
		Content.getComponent("Wear_knb"),
		Content.getComponent("Noise_knb"),
		Content.getComponent("Bump_knb"),
		Content.getComponent("Degrade_knb"),
		Content.getComponent("Air_knb"),
	];

	const var Dust_Control_Container = Content.getComponent("Textures_Container");

	Dust_Control_Container.setPaintRoutine(function (g) { });

	for (knb in TextureKnobs) {
		if (knb.getId() === 'Air_knb' || knb.getId() === 'Degrade_knb') {
			knb.setLocalLookAndFeel(Styles.LAF_displayBars);	
		} else {
			knb.setLocalLookAndFeel(Styles.LAF_DisplayTextKnob);	
		}
	
		knb.set('stepSize', 0.001);
	}
	
}