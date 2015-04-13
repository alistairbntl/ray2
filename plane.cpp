/** 
 CpSc 2100

**/

#include "plane.h"
#include "hitinfo.h"

using namespace std;

// Constructor
plane_t:: plane_t(ifstream &infile) : sobj_t(infile, "plane")
{
   point = myvector();  // initalize point to <0,0,0>
   normal = myvector(); // initalize normal to <0,0,0>

   load(infile);
   normal = orient1.cross(orient2);
}

void plane_t:: load(ifstream &infile)
{
   string token;
   infile >> token;

   while(token != ";")
   {
      if (token == "orient1") {
         infile >> orient1;
      }
      else if(token == "orient2")
      {
         infile >> orient2;
      }
      else if (token == "point") {
         infile >> point;
      }
      else 
      {
         cerr << "bad plane token " << token 
              << ". exiting" << endl;
         exit(1);
      }
      infile >> token;
   }
}

/*  Return a point on the plane  */

myvector plane_t::getpoint(){
  myvector point_on_plane;
 
  point_on_plane.x = point.getx();
  point_on_plane.y = point.gety();
  point_on_plane.z = point.getz();
 
  return point_on_plane;
}


/*  Return the plane's normal  */

myvector plane_t::getnormal(){
  myvector plane_normal;
 
  plane_normal.x = normal.getx();
  plane_normal.y = normal.gety();
  plane_normal.z = normal.getz();

  return point_on_plane;
}


/* detect if plane is hit */

int point_t::hits (myvector &base, myvector &dir, hitinfo_t &hit){
  myvector hit_point;
  double hit_distance;
  myvector normal = getnormal();

  /* check if ray is parallel to plane */
  if (normal.dot(dir) ==   0) {
	  return 0;
  }
  
  /* calculate hit distance */
  hit_distance = ((normal.dot(point) - normal.dot(base)) / normal.dot(dir));
  
  /* check if hit lies behind viewpoint */
  if (hit_distance < 0) {
	  return 0;
  }
  
  /* calculate hit point */
  hit_point = base + (dir * hit_distance);
  
  /* check if hit lies behind screen */
  if (hit_point > 0) {
	  return 0;
  }
  
  /* set hit info */
  hit.setnormal(normal);
  hit.setdistance(hit_distance);
  hit.sethitpoint(hit_point);
  
  return 1;
}


/* dump info to dump file */

void dump(){
	cerr << "   point:   " << point << endl;
	cerr << "   orient1: " << orient1 << endl;
	cerr << "   orient2: " << orient2 << endl;
	cerr << "   normal:  " << normal << endl;
}