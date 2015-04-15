/** 
    CPSC 2100
    lighting.cpp   

    
**/

#include "lighting.h"


myvector lighting(scene_t *scene, entity_t *ent, hitinfo_t &hit) 
{
	myvector total_illumination;
	/* moved pointer declaration to point where address is
	   set so that constructor is not called.
	 */
	//	pointlight_t *light_ptr;
	//      iterator_t *light_iter;
	
	/* set illumination to 0 */
	/* this code not necessary because constructor defaults
	   to */
	//	total_illumination = (0.0, 0.0, 0.0);
	
	/* gather light from all sources */
	iterator_t *light_iter = newIterator(scene->lightList);
	while(l_hasnext(light_iter)) {
	      	/* set pointer to current light 
		   and advance the light_iterator*/
	        pointlight_t *light_ptr = static_cast<pointlight_t*>
		  (l_next(light_iter));
		
		/* process light */
		myvector new_light = light_ptr->processLight(scene, ent, hit);

		/* add to current illumination */
		total_illumination = total_illumination + new_light;
		
		/* move to next light in list */
		//		light_iter = l_next(light_iter);
	}

    return total_illumination;
}

