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

myvector plane_t::getpoint(){
  myvector plane_normal;
 
  plane_normal.x = normal.getx();
  plane_normal.y = normal.gety();
  plane_normal.z = normal.getz();

  return point_on_plane;
}


int point_t::hits (myvector &base, myvector &dir, hitinfo_t &hit){

}
