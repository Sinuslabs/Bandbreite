namespace EasterEgg {
	
	const var discount_lbl = Content.getComponent("discount_lbl");
	const var code_copied_lbl = Content.getComponent("code_copied_lbl");
	
	code_copied_lbl.showControl(false);
	
	const var discount_copy = Content.getComponent("discount_copy_btn");
	discount_copy.setControlCallback(onCopy);
	
	const var discount_close_btn = Content.getComponent("discount_close_btn");
	discount_close_btn.setControlCallback(onClose);
	
	discount_copy.setLocalLookAndFeel(Styles.LAF_displayButton);
	discount_close_btn.setLocalLookAndFeel(Styles.LAF_textButton);
	
	inline function onCopy(component, value){
		if(value) {
			code_copied_lbl.showControl(true);
			Engine.copyToClipboard(discount_lbl.get('text'));
		}
	}
	
	inline function onClose(component, value) {
		if (value) {
			Router.goTo('Tape');
		}
	}
	
}