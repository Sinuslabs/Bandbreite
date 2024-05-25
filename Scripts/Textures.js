namespace Textures {
	
	const var Mode_Select = [Content.getComponent("Textures_Dust_btn"),
	                         Content.getComponent("Textures_Pocky_btn")];
	const var Pocky_Control_Container = Content.getComponent("Pocky_Control_Container");
	const var Dust_Control_Container = Content.getComponent("Dust_Control_Container");
	
	for (btn in Mode_Select) {
		btn.setControlCallback(onModeSelect);
	}
	
	inline function onModeSelect(component, value) {
		
		switch(component.getId()) {
			case 'Textures_Dust_btn':
				Dust_Control_Container.set('visible', value);
				Pocky_Control_Container.set('visible', !value);
				BandFX.setAttribute(BandFX.Mode, 0);
				break;
			case 'Textures_Pocky_btn':
				Dust_Control_Container.set('visible', !value);
				Pocky_Control_Container.set('visible', value);
				BandFX.setAttribute(BandFX.Mode, 1);
				break;
		}
		
	}
	
}