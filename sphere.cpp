/** CpSc 2100

    The sphere_t class is derived from the sobj_t class.
**/

#include "sphere.h"
#include "math.h"

using namespace std;

// Constructor
sphere_t:: sphere_t(ifstream &infile) : sobj_t(infile, "sphere")
{
  center = myvector(); // intialize point to <0,0,0>
  double radius = 0;   // initialize point to 0
  
  load(infile);
  
}

void sphere_t:: load(ifstream &infile) 
{
   string token;

   infile >> token;
   while(token != ";")
   {
      if (token == "center") {
         infile >> center;
      }
      else
      if (token == "radius") {
         infile >> radius;
      }
      else 
      {
         cerr << "Unknown sphere attribute " << token << "exiting." 
              << endl;
         exit(1);
      }
      infile >> token;
   }
}

myvector sphere_t::getcenter(){
  myvector my_center ( center.getx(), center.gety(), center.getz());
  return my_center;
}

double sphere_t::getradius(){

  return radius;

}

int sphere_t::hits(myvector &base, myvector &dir, hitinfo_t &hit){

  double a,b,c,discriminant,t_h;
  dir = dir.unitvec();
  /* sum(const myvector &addend) */
  /* scale(double fact) */
  myvector new_base = base + center*-1.0;
  myvector hit_point;

  // first calculate the values for the quadratic formula
  a = dir.dot(dir);
  b = 2*new_base.dot(dir);
  c = new_base.dot(new_base) - radius*radius;

  discriminant = b*b - 4*a*c;

  if (discriminant <= 0) return 0;

  t_h = (-b - sqrt(discriminant))/(2*a);
  if (t_h<0) return 0;

  hit_point = base + dir*t_h;
  if (hit_point.getz() > 0) return 0;
  
  hit.sethitpoint(hit_point);
  myvector normal_temp = hit_point+center*-1;
  hit.setnormal(normal_temp*normal_temp.length());
  myvector distance_temp = hit_point*-1 + base;
  hit.setdistance(distance_temp.length());

  return 0;
}

void sphere_t::dump(){
  
  std::cout << "     center:     ";
  center.print() ;
  std::cout << endl;
  std::cout << "     radius:     " << radius << endl;
 
}
