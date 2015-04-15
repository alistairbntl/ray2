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
  /** intialize the vector with correct points **/
    myvector light_center(center.getx(),center.gety(),center.getz());
    return light_center;
}


/* return color of light */
mycolor pointlight_t::getcolor()
{
  mycolor light_color = (color.getR(),color.getG(),color.getB());
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
	myvector light_ray, light_unit;
	double distance, angle_cos;
	
	/* create ray from hitpoint to center of light */
	/* Tim -- old line made ray in the wrong direction. reversed it. */
	// light_ray = hit.gethitpoint() - center;  (old line)
	light_ray = center - hit.gethitpoint();
	
	/* find light angle */
	/* why is destructure being called? */
	/* ARB -- commented out old line and replaced
	   with new line...don't think destructure should
	   be called);*/
	/* Tim -- meant to call unitize operator. put in intermediate step to make
	   things easier. */
	light_unit = ~light_ray;   
	angle_cos = light_unit.dot(hit.getnormal());
	
    /*  check for self-occlusion */
	if (angle_cos < 0) {
		return myvector(0.0, 0.0, 0.0);
	}

        entity_t *entity_pointer = closest(scene, center, light_unit*(-1), NULL, hit);

	/* check if occluded by other object */
	if (entity_pointer != ent) {
		return myvector(0.0, 0.0, 0.0);
	}
	
	/* find distance between light and object */
	distance = light_ray.length();
	
	/* compute intensity */
	/*** ARB I've changed brightness because
	     its defined as a double in the
	     pointlight class...not sure 
	     if this is correct ***/
	myvector result (color.getR() * brightness * angle_cos / distance,
			 color.getG() * brightness * angle_cos / distance,
			 color.getB() * brightness * angle_cos / distance);
    

    return result;
}
