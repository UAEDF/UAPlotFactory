
#include "../includes/UALegend.h"

#include <iostream>
#include <sstream>
using namespace std;

Double_t UALegend::x[11] = { 0.57 , 0.35 , 0.20 , 0.70 , 0.70 , 0.75 , 0.45 , 0.80 , 0.20 , 0.55 , 0.60};
Double_t UALegend::y[11] = { 0.80 , 0.40 , 0.40 , 0.85 , 0.90 , 0.90 , 0.87 , 0.87 , 0.90 , 0.40 , 0.93};


// Default Constructor ----------------------------------------------------------

UALegend::UALegend(){

  cout << "UALegend: Default Constructor" << endl ;

}


//  Constructor ----------------------------------------------------------

UALegend::UALegend(TString LegTitle):LegendTitle_(LegTitle){

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
void UALegend::BuildLegend(Double_t xmin , Double_t ymax) {

  // Get Legend size:
  int LegendSize = 1;
  for(int iLeg = 0 ; iLeg < (signed) vLegCurves_.size() ; ++iLeg) {
    TString TestLeg( (vLegCurves_.at(iLeg))->GetLegend() );
    TestLeg.ToLower();
    if ( TestLeg != "none" ) ++LegendSize;
  }

  // Set Legend Panel size:

  double xlegmin = xmin ;
  double ylegmax = ymax ;
  double yLegendWidth = .045 ;
  double xLegendWidth = .20 ;
  double legfactor = 1. ;

  double globalLegendTextSize = 0.04 ;

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
  Legend_->SetTextSize(globalLegendTextSize);
  Legend_->SetHeader(LegendTitle_);
  Legend_->Draw("same");


}

