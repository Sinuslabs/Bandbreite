namespace Router {
	
	const routes = Content.getAllComponents('_Route');
	
	Console.print(trace(routes));
	
	reg currentRoute = 'Tape';
	
	inline function goTo(goToRoute) {
		
		if (!goToRoute) return;
		
		Console.print(goToRoute);
	
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