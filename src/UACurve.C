
#include "../includes/UACurve.h"

#include <TFile.h>
#include <TDirectory.h>

#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

// Defaul Constructor ----------------------------------------------------------

UACurve::UACurve( bool isMC , TString Legend ){

  cout << "UACurve: Constructor" << endl ;
  isMC_       = isMC ;
  Legend_     = Legend ;
  Curve_      = (TObject*) new TH1D() ; // Dummy TH1

}

// Constructor: Fetching TObject from file -------------------------------------

UACurve::UACurve( bool isMC, TString fileName , TString histoName , TString Legend ){

  cout << "UACurve: Constructor" << endl ;

/*
  TString histoFullName ("");
  if ( dirName != "none" && dirName != "NONE" ) histoFullName += dirName + "/"; 
  //if ( histoName == "AUTO" ) histoFullName += dataSetHisto.at(iData);
  histoFullName += histoName;
*/

  isMC_       = isMC;
  Legend_     = Legend ;

  TFile*   File     = new TFile(fileName,"READ");  
  TObject* Curve    = (TObject*) File->Get(histoName); 
  gROOT->cd(); // Have to create the new object Curve_ outside of gDirectory from File_
  Curve_ = (TObject*) Curve->Clone();
  delete  Curve ;
  File->Close();
  delete File;
  
}

// Destructor ------------------------------------------------------------------

UACurve::~UACurve(){

  cout << "UACurve: Destructor BEGIN " << endl ;
  delete Curve_;

}

// isTH1() ----------------------------------------------------------------------

bool UACurve::isTH1(){
                
    if (    ( (string) (Curve_->ClassName()) ).compare("TH1")  == 0 
         || ( (string) (Curve_->ClassName()) ).compare("TH1C") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH1D") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH1F") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH1I") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH1K") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH1S") == 0 ) return true;
  
    return false;
} 

// isTH2() ----------------------------------------------------------------------

bool UACurve::isTH2(){

    if (    ( (string) (Curve_->ClassName()) ).compare("TH2")  == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH2C") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH2D") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH2F") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH2I") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TH2S") == 0 ) return true;

    return false;
} 

// isTGraph() -------------------------------------------------------------------

bool UACurve::isTGraph(){

    if (    ( (string) (Curve_->ClassName()) ).compare("TGraph")  == 0
         || ( (string) (Curve_->ClassName()) ).compare("TGraphErrors") == 0
         || ( (string) (Curve_->ClassName()) ).compare("TGraphAsymmErrors") == 0 ) return true;

    return false; 

}

// Add : this = this + c1*Curv1 -------------------------------------------------

void UACurve::Add( UACurve* Curv1 , Double_t c1 ) { 
  cout << "[UACurve::Add] Started" << endl ;

  // TH1
  if      ( this->isTH1() && Curv1->isTH1() ) 
     { ( (TH1*) (this->Curve_) )->Add( (TH1*) (Curv1->Curve_) , c1 ) ; }
  
  // TH2 
  else if ( this->isTH2() && Curv1->isTH2() )
     { ( (TH2*) (this->Curve_) )->Add( (TH2*) (Curv1->Curve_) , c1 ) ; }
 
  else {  cout << "[UACurve::Add] WARNING: Unknown TypeS : " << Curve_->ClassName() 
               << " " << (Curv1->Curve_)->ClassName() <<  endl; }


}

// Add : this = c1*Curv1 + c2*Curv2 ---------------------------------------------

void UACurve::Add( UACurve* Curv1 , UACurve* Curv2 , Double_t c1 , Double_t c2 ) {
  ;
}


// Scale( Double_t cScale ) -----------------------------------------------------

void UACurve::Scale ( Double_t cScale ){

  // TH1
  if      (this->isTH1()) { ((TH1*) Curve_)->Scale(cScale) ; }    

  // TH2
  else if (this->isTH2()) { ((TH2*) Curve_)->Scale(cScale) ; } 

  // TGraph
  else if (this->isTGraph() ) {

    for(int i = 0 ; i < ((TGraphAsymmErrors*) Curve_)->GetN() ; ++i) {
      Double_t x,y,eyup,eydown ;
      ((TGraphAsymmErrors*) Curve_)->GetPoint(i,x,y);
      eyup   = ((TGraphAsymmErrors*) Curve_)->GetErrorYhigh(i);
      eydown = ((TGraphAsymmErrors*) Curve_)->GetErrorYlow(i);
      y      *= cScale;
      eyup   *= cScale;
      eydown *= cScale;
      ((TGraphAsymmErrors*) Curve_)->SetPoint(i,x,y);
      ((TGraphAsymmErrors*) Curve_)->SetPointEYhigh(i,eyup);
      ((TGraphAsymmErrors*) Curve_)->SetPointEYlow(i,eydown);
    }
   
  } else {  cout << "[UACurve::Scale] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl; }

}

// Integral () ------------------------------------------------------------------

Double_t UACurve::Integral ( Int_t binx1, Int_t binx2 , Int_t biny1, Int_t biny2 ) {

  // TH1 Like
  if ( this->isTH1() ) {
 
    if ( binx1 == -1 ) binx1 = 1 ;
    if ( binx2 == -1 ) binx2 = ((TH1*) Curve_)->GetNbinsX() ;
    if ( binx1 < 1  || binx2 > ((TH1*) Curve_)->GetNbinsX() ) {
       cout << "[UACurve::Integral] Out of Range --> return 0 " << endl;
       return 0;
    }
    return ((TH1*) Curve_)->Integral(binx1,binx2) ;

  // TH2 Like
  } else if ( this->isTH2() ) {

    if ( binx1 == -1 ) binx1 = 1 ;
    if ( binx2 == -1 ) binx2 = ((TH2*) Curve_)->GetNbinsX() ;
    if ( biny1 == -1 ) biny1 = 1 ;
    if ( biny2 == -1 ) biny2 = ((TH2*) Curve_)->GetNbinsY() ;
    if (    binx1 < 1  || binx2 > ((TH1*) Curve_)->GetNbinsX() 
         || biny1 < 1  || biny2 > ((TH1*) Curve_)->GetNbinsY() ) {
       cout << "[UACurve::Integral] Out of Range --> return 0 " << endl;
       return 0;
    }

    return ((TH2*) Curve_)->Integral(binx1,binx2,biny1,biny2) ;

  // TGraph Like: Integral of a TGraph assuming x error bar as bin width
  } else if ( this->isTGraph() ) {

    if ( binx1 == -1 ) binx1 = 0 ;
    if ( binx2 == -1 ) binx2 = ((TGraphAsymmErrors*) Curve_)->GetN();   
    if ( binx1 < 0  || binx2 > ((TGraphAsymmErrors*) Curve_)->GetN()  ) {
       cout << "[UACurve::Integral] Out of Range --> return 0 " << endl;
       return 0;
    } 

    Double_t Integral = 0.;
    for(int i = binx1 ; i < binx2 ; ++i) {
      Double_t x,y,deltax ;
      ((TGraphAsymmErrors*) Curve_)->GetPoint(i,x,y);
      deltax = ((TGraphAsymmErrors*) Curve_)->GetErrorXhigh(i) + ((TGraphAsymmErrors*) Curve_)->GetErrorXlow(i) ;
      Integral += y*deltax ;
    }
    return Integral;

  }  else {
    cout << "[UACurve::Integral] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;
    return 0.;
  }

}

// Norm() -----------------------------------------------------------------------

void UACurve::Norm( Int_t binx1, Int_t binx2 , Int_t biny1, Int_t biny2 ) {

  cout << "[UACurve::Norm]  " << Curve_->ClassName() <<  endl;

  if ( this->isTH1() || this->isTH2() || this->isTGraph() ) {
    //cout << this->Integral(binx1, binx2 , biny1, biny2 ) << endl;
    this->Scale( (double) (1./this->Integral(binx1, binx2 , biny1, biny2 )) ) ; 
  } else {
    cout << "[UACurve::Norm] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;
  }

}

// Norm( UACurve ) --------------------------------------------------------------

void UACurve::Norm ( UACurve* RefCurve , Int_t binx1, Int_t binx2 , Int_t biny1, Int_t biny2 ){
   this->Norm () ;
   cout << "[UACurve::Norm] WARNING: Passing Pointers Not Implemented" << endl; 
}

void UACurve::Norm ( UACurve& RefCurve , Int_t binx1, Int_t binx2 , Int_t biny1, Int_t biny2 ){

  if ( this->isTH1() || this->isTH2() || this->isTGraph() ) {
    Double_t nReference = RefCurve.Integral(binx1, binx2 , biny1, biny2 ); 
    Double_t nCurrent   = this->Integral(binx1, binx2 , biny1, biny2 );
    this->Scale( (double) (nReference/nCurrent) ) ;
  } else {
    cout << "[UACurve::Norm] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;
  }

}

// ApplyStyle() -------------------------------------------------------------------

void UACurve::ApplyStyle(){

   cout << Curve_->ClassName() << endl;
   Print();

   // Setting Curve Style
   if ( this->isTH1() ) { 
     // Curve style: Marker
     ((TH1*) Curve_)->SetMarkerColor(markerColor);
     ((TH1*) Curve_)->SetMarkerStyle(markerStyle);
     ((TH1*) Curve_)->SetMarkerSize (markerSize);
     // Curve style: Line 
     ((TH1*) Curve_)->SetLineColor(lineColor);
     ((TH1*) Curve_)->SetLineStyle(lineStyle);
     ((TH1*) Curve_)->SetLineWidth(lineWidth);
     // Curve style: Fill Area
     ((TH1*) Curve_)->SetFillColor(fillColor);
     ((TH1*) Curve_)->SetFillStyle(fillStyle);
   }
   else if ( this->isTH2() ) {
     cout << "[UACurve::Draw] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl; 
   }
   else if ( this->isTGraph() ) {
     // Curve style: Marker
     ((TGraph*) Curve_)->SetMarkerColor(markerColor);
     ((TGraph*) Curve_)->SetMarkerStyle(markerStyle);
     ((TGraph*) Curve_)->SetMarkerSize (markerSize);
     // Curve style: Line 
     ((TGraph*) Curve_)->SetLineColor(lineColor);
     ((TGraph*) Curve_)->SetLineStyle(lineStyle);
     ((TGraph*) Curve_)->SetLineWidth(lineWidth);
     // Curve style: Fill Area
     ((TGraph*) Curve_)->SetFillColor(fillColor);
     ((TGraph*) Curve_)->SetFillStyle(fillStyle);
   }
   else {
     cout << "[UACurve::Draw] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;
   }

}

// GetMaximum() --------------------------------------------------------------------

Double_t UACurve::GetMaximum () {

  Double_t hMax = 0. ;
  if ( this->isTH1() || this->isTH2() ) {
     hMax = ((TH1*) Curve_)->GetMaximum() ; 
  } else if  ( this->isTGraph() ) {
     hMax = ((TGraph*) Curve_)->GetHistogram()->GetMaximum() ; 
  } else {
     cout << "[UAVurve::GetMaximum]: WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;  
  }    
  return hMax ;

}


// GetMinimum() --------------------------------------------------------------------

Double_t UACurve::GetMinimum () {

  Double_t hMin = 0. ;
  if ( this->isTH1() || this->isTH2() ) {
     hMin = ((TH1*) Curve_)->GetMinimum() ; 
  } else if  ( this->isTGraph() ) {
     hMin = ((TGraph*) Curve_)->GetHistogram()->GetMinimum() ; 
  } else {
     cout << "[UAVurve::GetMinimum]: WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;  
  }    
  return hMin ;

}


// Draw() -------------------------------------------------------------------------

void UACurve::Draw(TString opt){

   cout << Curve_->ClassName() << endl;

   ApplyStyle();

   // Draw Option
   TString DrawOpt (opt);
   if ( this->isTH1() ) {
     if    ( isMC_ ) { DrawOpt += "hist" ; }
     else            { DrawOpt += "e"    ; }  
   }
   else if ( this->isTH2() ) {
     DrawOpt += "colz" ;
   }
   else if ( this->isTGraph() ) {
     if    ( isMC_ ) { DrawOpt += "c" ; }
     else            { DrawOpt += "p" ; }
   }

   if  ( this->isTH1()    ) ( (TH1*)    Curve_)->Draw(DrawOpt);
   if  ( this->isTH2()    ) ( (TH2*)    Curve_)->Draw(DrawOpt);
   if  ( this->isTGraph() ) ( (TGraph*) Curve_)->Draw(DrawOpt);

//   gPad->Update();

}

// OPERATORS ========================================================================

void  UACurve::Copy ( UACurve& New ) const {

  New.SetStyle( (UACurveStyle*) this );
  New.Curve_  = (TObject*) this->Curve_->Clone();
  New.isMC_   = this->isMC_ ;
  New.Legend_ = this->Legend_ ; 

} 

UACurve::UACurve ( const UACurve& C ) : UACurveStyle() {
  cout << "copy constructor" << endl;
  ((UACurve&)C).Copy(*this) ;
} 

UACurve& UACurve::operator= ( const UACurve& Curve ) { 
  cout << "equal " << endl;

  if (this != &Curve ) ((UACurve&)Curve).Copy(*this);
  return *this;

}


