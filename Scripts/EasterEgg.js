namespace EasterEgg {
	
	const var discount_lbl = Content.getComponent("discount_lbl");
	const var code_copied_lbl = Content.getComponent("code_copied_lbl");
	
	code_copied_lbl.showControl(false);
	
	const var discount_copy = Content.getComponent("discount_copy_btn");
	discount_copy.setControlCallback(onCopy);
	
	discount_copy.setLocalLookAndFeel(Styles.LAF_displayButton);
	
	inline function onCopy(component, value){
		if(value) {
			code_copied_lbl.showControl(true);
			Engine.copyToClipboard(discount_lbl.get('text'));
		}
	}
	
}