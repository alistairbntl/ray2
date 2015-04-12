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
    
    /** STUBBED. COMPLETE FOR RAY2  **/
   
    load(infile);
}

/* load takes in a file and reads in the values of the provided attribute. */
void pointlight_t::load(ifstream &infile)
{
    /** STUBBED. COMPLETE FOR RAY2  **/

}



myvector pointlight_t::getcenter()
{
    /** STUBBED. COMPLETE FOR RAY2  **/

    return myvector(0.0, 0.0, 0.0);   /** MODIFY FOR RAY2  **/
}


mycolor pointlight_t::getcolor()
{
    /** STUBBED. COMPLETE FOR RAY2  **/

    return mycolor(0.0, 0.0, 0.0) ;  /** MODIFY FOR RAY2  **/
}


double pointlight_t::getbrightness()
{
    /** STUBBED. COMPLETE FOR RAY2  **/

    return 0.0;                     /** MODIFY FOR RAY2  **/
}


void pointlight_t::dump()
{
    /** STUBBED. COMPLETE FOR RAY2  **/
    
}


myvector pointlight_t::processLight(scene_t *scene, entity_t *ent, hitinfo_t &hit) 
{
    /** STUBBED. COMPLETE FOR RAY2  **/
    
    return myvector(0.0, 0.0, 0.0);  /** MODIFY FOR RAY2  **/
}
