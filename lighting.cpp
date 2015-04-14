/** 
    CPSC 2100
    lighting.cpp   

    
**/

#include "lighting.h"


myvector lighting(scene_t *scene, entity_t *ent, hitinfo_t &hit) 
{
	myvector total_illumination, new_light;
	pointlight_t *light_ptr;
	iterator_t *light_iter;
	
	/* set illumination to 0 */
	total_illumination = (0.0, 0.0, 0.0);
	
	/* gather light from all sources */
	light_iter = newIterator(scene->lightList);
	while(l_hasnext(light_iter)) {
		/* set pointer to current light */
		light_ptr = light_iter->position->objPtr;
		
		/* process light */
		new_light = light_ptr.processLight(scene, ent, hit);
		
		/* add to current illumination */
		total_illumination = total_illumination + new_light;
		
		/* move to next light in list */
		light_iter = l_next(light_iter);
	}

    return total_illumination;
}

