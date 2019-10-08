#include "visualizer.hpp"

int main() {
    
	Visualizer vis; 

	vis.setPoints(); 

	vis.programmableFilterFunc(); 

	vis.setMapper(); 

	vis.axes(); 

	vis.renderProbe(); 

	vis.render(); 

}
