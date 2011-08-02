#ifndef __UALegend_H__
#define __UALegend_H__

#include <TLegend.h>
#include <TString.h>

#include "UACurveStyle.h"
#include "UACurve.h"
//#include "UAPlot.h"

#include <vector>

using  namespace std;

class UALegend {

  private:

    TLegend*  Legend_ ;
    TString   LegendTitle_ ;

    vector<UACurve*> vLegCurves_;

  public:

    UALegend() ;
    UALegend(TString) ;
    virtual ~UALegend() ;
    
   TLegend* GetLegend(){return Legend_;} ;
   
    void AddLegend( bool , UACurveStyle& , TString="NONE" ) ;
    void AddLegend(     UACurve&         , TString="NONE" ) ;

    void BuildLegend(Double_t , Double_t);
    void BuildLegend(Int_t ipos = 0){BuildLegend(x[ipos] , y[ipos]);};
    void Draw();
    
    static Double_t x[] ;
    static Double_t y[] ;
 
};

#endif


