namespace Router {
	
	const routes = Content.getAllComponents('_Route');
	
	for (route in routes) {
		route.setPaintRoutine(function(g) {});
	}
	
	reg currentRoute = 'Tape';
	
	inline function goTo(goToRoute) {
		
		if (!goToRoute) return;
		
		for (route in routes) {
			if (route.getId().contains(goToRoute)) {
				currentRoute = goToRoute;
				route.set('visible', true);
			} else {
				route.set('visible', false);
			}
		}
	}
}