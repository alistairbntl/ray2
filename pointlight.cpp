/**
    CPSC 2100
    pointlight.cpp

    pointlight.cpp contains all of the functions included in the pointlight class,
    which is a light found at a singular point.
**/


#include "pointlight.h"

using namespace std;

pointlight_t::pointlight_t(ifstream &infile) : entity_t(infile, "pointlight")
{
    /* initialize color, brightness, and center */
	color = mycolor();
	center = myvector();
	brightness = 0.0;
	
	/* load data from input file */
    load(infile);
}

/* load takes in a file and reads in the values of the provided attribute. */
void pointlight_t::load(ifstream &infile)
{
 string token;
 
   /* read label for data */
   infile >> token;

   while(token != ";")   //ends at end of object entry
   {
	   /* check label for data type */
      if (token == "color") {
         infile >> color;
      }
      else if(token == "brightness")
      {
         infile >> brightness;
      }
      else if (token == "center") {
         infile >> center;
      }
      else 
      {
         cerr << "bad point light token " << token 
              << ". exiting" << endl;
         exit(1);
      }
	  
	  /* move to next label */
      infile >> token;
   }
}



/* return center of light */
myvector pointlight_t::getcenter()
{
	myvector light_center;
	
	light_center.x = center.getx();
	light_center.y = center.gety();
	light_center.z = center.getz();

    return light_center;
}


/* return color of light */
mycolor pointlight_t::getcolor()
{
 	myvector light_color;
	
	light_color.x = color.getx();
	light_color.y = color.gety();
	light_color.z = color.getz();

    return light_color;
}


/* returns brightness of light */
double pointlight_t::getbrightness()
{
   return brightness;
}


/* dumps data to output file */
void pointlight_t::dump()
{
   cerr << "   color:      " << color << endl;
   cerr << "   brightness: " << brightness << endl;
   cerr << "   center:     " << center << endl;
}


myvector pointlight_t::processLight(scene_t *scene, entity_t *ent, hitinfo_t &hit) 
{
	entity_t *entity_pointer;
	myvector result, light_ray;
	double distance, angle_cos;
	
	/* create ray from hitpoint to center of light */
	light_ray = hit.hitpoint - center;
	
	/* find light angle */
	angle_cos = ~light_ray.dot(hit.normal);
	
    /*  check for self-occlusion */
	if (angle_cos < 0) {
		return myvector(0.0, 0.0, 0.0);
	}
	
	/* find closest object to light */
	entity_pointer = closest(scene, center, ~light_ray, ent, hit);
	
	/* check if occluded by other object */
	if (entity_pointer != ent) {
		return myvector(0.0, 0.0, 0.0);
	}
	
	/* find distance between light and object */
	distance = light_ray.length();
	
	/* compute intensity */
	result.x = color.x * brightness.x * angle_cos / distance;
	result.y = color.y * brightness.y * angle_cos / distance;
	result.z = color.z * brightness.z * angle_cos / distance;
    
    return result;
}
