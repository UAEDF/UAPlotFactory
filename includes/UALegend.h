#ifndef __UALegend_H__
#define __UALegend_H__

#include <TLegend.h>
#include <TString.h>

#include "UACurveStyle.h"
#include "UACurve.h"
#include "UAPlot.h"

#include <vector>

using  namespace std;

class UALegend {

  private:

    TLegend*  Legend_ ;
    TString   LegendTitle_ ;

    vector<UACurve*> vLegCurves_;

  public:

    UALegend() ;
    virtual ~UALegend() ;
   
    void AddLegend( bool , UACurveStyle& , TString="NONE" ) ;
    void AddLegend(     UACurve&         , TString="NONE" ) ;

    void BuildLegend();
    void Draw();
 
};

#endif


