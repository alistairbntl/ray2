/** CpSc 2100

    The sphere_t class is derived from the sobj_t class.
**/

#include "sphere.h"
#include "math.h"

using namespace std;

// Constructor
sphere_t:: sphere_t(ifstream &infile) : sobj_t(infile, "sphere")
{
   /**  STUBBED.  COMPLETE FOR RAY2  **/ 

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

/**  IMPLEMENT THE REMAINING METHODS  **/
