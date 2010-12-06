#ifndef __UAPlot_H__
#define __UAPlot_H__

#include "UACurve.h"
#include "UALegend.h"

#include <vector>
using  namespace std;

class UAPlot {

  private:

    vector<UACurve*> vUACurves_ ;

    bool             mcstack_   ;
    vector<UACurve*> vMCStack_  ;
    UALegend         UALegend_  ; 

  public:
    UAPlot ();
    UAPlot ( bool ); 
    virtual ~UAPlot ();

    void AddCurve();
    //void AddCurve(UACurve&);
    void AddCurve(UACurve* );
    void AddCurve(bool,TString , TString , TString="NONE" );

    void DeleteCurve( int );

    Double_t GetMaximum() ; // Find Maximum of all UACurve or Stack 

    void AutoStyle();
    
    void ResetMCStack();
    void BuildMCStack();

    void Norm( Int_t= 0 , Int_t=-1 , Int_t=-1 , Int_t=-1 , Int_t=-1 ); 
    void Norm( UACurve& , Int_t= 0 , Int_t=-1 , Int_t=-1 , Int_t=-1 , Int_t=-1 ); 

    /* Norm() Tool

       First int is norm type, others are bin limits 
       0 = All Curve to Unit Integral Independently
       1 = All Curve to Unit Integral but MC considered as a stack
       2 = All Curve respecting to first data curve Independently
       3 = All Curve respecting to first data curve but MC considered as a stack
       If **EXTERNAL** UACurve given, norm done respecting to that one and only
       option 2 & 3 are available 

       !!!! If you want to build a stack, call norm before !!!!

    */

    void Draw(TString="");   

};

#endif



