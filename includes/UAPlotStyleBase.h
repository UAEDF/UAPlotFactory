#ifndef __UAPlotStyleBase_H__
#define __UAPlotStyleBase_H__

#include <Rtypes.h>
#include <TString.h>

class UAPlotStyleBase  {

  private:

  public:
    UAPlotStyleBase ();
    virtual ~UAPlotStyleBase ();

    // Lin/Log
    static bool g_plotLogX ;
    static bool g_plotLogY ;
    static bool g_plotLogZ ;

    // Grid X/Y
    static bool g_plotGridX ;
    static bool g_plotGridY ;


/*
    // 2D PLot Style
    static TString g_2DplotOpt ;

    // Legend
    static bool g_drawLegend ;
*/

};

#endif

