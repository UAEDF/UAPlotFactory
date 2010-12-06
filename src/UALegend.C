
#include "../includes/UALegend.h"

#include <iostream>
#include <sstream>
using namespace std;

// Defaul Constructor ----------------------------------------------------------

UALegend::UALegend(){

  cout << "UALegend: Constructor" << endl ;

}

// Defaul Destructor ----------------------------------------------------------

UALegend::~UALegend(){

  cout << "UALegend: Destructor" << endl ;

   for ( vector<UACurve*>::iterator itC = vLegCurves_.begin() ; itC != vLegCurves_.end() ; ++itC ){
     delete (*itC);
   }
   vLegCurves_.clear();

   //delete Legend_ ;

}

// AddLegend (UAStyle&) -------------------------------------------------------

void UALegend::AddLegend ( bool isMC , UACurveStyle& Style , TString LegText ) {

  vLegCurves_.push_back(new UACurve( isMC ));
  vLegCurves_.at(vLegCurves_.size()-1)->SetStyle( &Style );
  vLegCurves_.at(vLegCurves_.size()-1)->SetLegend(LegText);

}

// AddLegend (UAStyle&) -------------------------------------------------------

void UALegend::AddLegend (UACurve& Curve , TString LegText ) {

  vLegCurves_.push_back(new UACurve( Curve.isMC() ));
  vLegCurves_.at(vLegCurves_.size()-1)->SetStyle( &((UACurveStyle) Curve) );
  TString TestLeg(LegText); 
  TestLeg.ToLower();
  if ( TestLeg != "none" ) { vLegCurves_.at(vLegCurves_.size()-1)->SetLegend(LegText); }
  else                     { vLegCurves_.at(vLegCurves_.size()-1)->SetLegend(Curve.GetLegend()); }

}


// BuildLegend() -------------------------------------------------------------

void UALegend::BuildLegend() {

  // Get Legend size:
  int LegendSize = 1;
  for(int iLeg = 0 ; iLeg < (signed) vLegCurves_.size() ; ++iLeg) {
    TString TestLeg( (vLegCurves_.at(iLeg))->GetLegend() );
    TestLeg.ToLower();
    if ( TestLeg != "none" ) ++LegendSize;
  }

  // Set Legend Panel size:

  double xlegmin = .6 ;
  double ylegmax = .9 ;
  double yLegendWidth = .03 ;
  double xLegendWidth = .20 ;
  double  legfactor = 1. ;

  double globalLegendTextSize = .3 ;

  Legend_ = new TLegend (xlegmin ,
                         ylegmax - yLegendWidth * LegendSize * legfactor  ,
                         xlegmin + xLegendWidth,
                         ylegmax );
 
     
  for(int iLeg = 0 ; iLeg < (signed) vLegCurves_.size() ; ++iLeg) {
    TString TestLeg( (vLegCurves_.at(iLeg))->GetLegend() );
    TestLeg.ToLower();
    if ( TestLeg != "none" ) {
      (vLegCurves_.at(iLeg))->ApplyStyle();
      TString opt;
      if ( (vLegCurves_.at(iLeg))->isMC() ) opt  = "l";
      else                                  opt  = "p";
      Legend_->AddEntry( (TH1*) ((vLegCurves_.at(iLeg))->pCurve()) ,  (vLegCurves_.at(iLeg))->GetLegend() , opt );
    }
  }

  Legend_->SetBorderSize(0);
  Legend_->SetFillColor(0);
  Legend_->SetTextSizePixels(globalLegendTextSize);
  Legend_->Draw();


}

