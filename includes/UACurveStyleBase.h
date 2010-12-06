#ifndef __UACurveStyleBase_H__
#define __UACurveStyleBase_H__

#include <Rtypes.h>
#include <TString.h>

class UACurveStyleBase  {

  private:

  public:
    UACurveStyleBase ();
    virtual ~UACurveStyleBase ();

    // Global style: Marker
    static Color_t g_markerColor ;
    static Style_t g_markerStyle ; 
    static Size_t  g_markerSize ;

    // Global style: Line  
    static Color_t g_lineColor ;
    static Style_t g_lineStyle ; 
    static Width_t g_lineWidth ;

    // Global style: Fill Area
    static Color_t g_fillColor ;
    static Style_t g_fillStyle ;
/*
    // 2D PLot Style
    static TString g_2DplotOpt ;
*/
};

#endif

