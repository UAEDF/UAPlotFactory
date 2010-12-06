
#include "../includes/UAPlot.h"

#include <iostream>
#include <sstream>
using namespace std;

// Defaul Constructor ----------------------------------------------------------

UAPlot::UAPlot(){
 
   mcstack_ = false; 
   cout << "UAPlot Constructor" << endl;
 
}

UAPlot::UAPlot( bool mcstack ){
 
   mcstack_ = mcstack; 
   cout << "UAPlot Constructor" << endl;

}


// Destructor ------------------------------------------------------------------

UAPlot::~UAPlot(){
  
   int iC = 1;
   cout << "UAPlot Destructor" << endl;
   for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
     cout << "UAPlot Delete # : " << iC++ << endl;
     delete (*itC);
   }
   vUACurves_.clear();

   for ( vector<UACurve*>::iterator itC = vMCStack_.begin() ; itC != vMCStack_.end() ; ++itC ){
     cout << "UAPlot Delete # : " << iC++ << endl;
     delete (*itC);
   }
   vMCStack_.clear();

}

// AddCurve -------------------------------------------------------------------- 

void UAPlot::AddCurve() {
  vUACurves_.push_back(new UACurve());
}


void UAPlot::AddCurve( UACurve* pCurve )
{
/*
  Color_t colors  [5] = { kBlack , kRed , kMagenta , kBlue , kGreen } ;
  Style_t lines   [3] = {    1   ,   2  ,    2 } ;
  Style_t markers [5] = { kFullCircle , kOpenCircle , kFullTriangleUp , kOpenTriangleUp , kFullStar } ;   
*/

  vUACurves_.push_back(new UACurve(*pCurve) ) ;

/*
  // Automatic Style
  int iC = vUACurves_.size()-1 ;
  if ( (vUACurves_.at(iC))->isMC() ) { nMC++ } ; 
  else                               { ++nData      
*/

}

// AddCurve -------------------------------------------------------------------- 

void UAPlot::AddCurve(bool isMC, TString fileName , TString histoName , TString dirName ) {
  vUACurves_.push_back(new UACurve( isMC, fileName , histoName , dirName ));
}

// DeleteCurve ------------------------------------------------------------------ 

void UAPlot::DeleteCurve( int iCDel ) {

  int iC = 1;
  for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
    //if ( iC++ == iCDel ) { vUACurves_.erase(itC--); }
    if ( iC++ == iCDel ) { delete (*itC) ; vUACurves_.erase(itC--); }
  }
}

// GetMaximum () ----------------------------------------------------------------

Double_t UAPlot::GetMaximum () {

  Double_t hMax = 0. ;
  for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
    if ( (*itC)->GetMaximum() > hMax ) { hMax =  (*itC)->GetMaximum() ; }
  }
  for ( vector<UACurve*>::iterator itC = vMCStack_.begin() ; itC != vMCStack_.end() ; ++itC ){
    if ( (*itC)->GetMaximum() > hMax ) { hMax =  (*itC)->GetMaximum() ; }
  }
  return hMax ;

}

// AutoStyle() ------------------------------------------------------------------

void UAPlot::AutoStyle() {

  // Up to 5 data
  Style_t markers [5] = { kFullCircle , kOpenCircle , kFullTriangleUp , kOpenTriangleUp , kFullStar } ;   

  // Up to 15 MC
  Color_t colors  [5] = { kBlack , kRed , kMagenta , kBlue , kGreen } ;
  Style_t lines   [3] = {    1   ,   2  ,    3 } ;

  int iMC   = 0 ;
  int iData = 0 ;

  for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
    if ( (*itC)->isMC() ) {
      if      ( iMC <  5 )  { (*itC)->lineColor = colors[iMC++    ] ; (*itC)->lineStyle = 1 ; }
      else if ( iMC < 10 )  { (*itC)->lineColor = colors[iMC++ -5 ] ; (*itC)->lineStyle = 2 ; }
      else if ( iMC < 15 )  { (*itC)->lineColor = colors[iMC++ -10] ; (*itC)->lineStyle = 3 ; }
    } else {
      if ( iData < 5 ) { (*itC)->markerStyle =  markers[iData++] ;  }
    }

  }

}

// ResetMCStack() ---------------------------------------------------------------

void UAPlot::ResetMCStack() {

   for ( vector<UACurve*>::iterator itC = vMCStack_.begin() ; itC != vMCStack_.end() ; ++itC ){
     delete (*itC);
   }
   vMCStack_.clear();
}

// BuildMCStack() ---------------------------------------------------------------

void UAPlot::BuildMCStack() {

  cout << "[UAPlot::BuildMCStack()] Started " << endl;

  ResetMCStack(); 

  int iC = 0 ;
  for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
    if ( (*itC)->isMC() ) {
      if (iC == 0) { vMCStack_.push_back(new UACurve(**itC)) ; }
      else {
         vMCStack_.push_back(new UACurve(**itC)) ;        
         //cout << "iC = " << iC << " " << (vMCStack_.at(iC-1))->GetMaximum() << endl;  
         vMCStack_.at(iC)->Add( vMCStack_.at(iC-1) ) ;
      }  
      ++iC ;
    }
  }

  cout << "MCStack size "  << vMCStack_.size() << endl;

}

// Norm -------------------------------------------------------------------------
    /* Norm() Tool

       First int is norm type, others are bin limits 
       0 = All Curve to Unit Integral Independently
       1 = All Curve to Unit Integral but MC considered as a stack
       2 = All Curve respecting to first data curve Independently
       3 = All Curve respecting to first data curve but MC considered as a stack
       If **EXTERNAL** UACurve given, norm done respecting to that one and only
       option 2 & 3 are available 
    */

void UAPlot::Norm( Int_t Type ,  Int_t binx1, Int_t binx2 , Int_t biny1, Int_t biny2 ) {


  if ( Type == 0 ) {
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) 
      { (*itC)->Norm(binx1,binx2,biny1,biny2) ; }
  } 

  if ( Type == 1 ) {
    Double_t MCSumInt = 0. ;
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      if ( (*itC)->isMC() ) MCSumInt += (*itC)->Integral(binx1, binx2 , biny1, biny2 ) ;
    }
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      if ( (*itC)->isMC() ) (*itC)->Scale( (double) (1./MCSumInt) ) ;
      else                  (*itC)->Scale( (double) (1./((*itC)->Integral(binx1, binx2 , biny1, biny2))) ) ; 
    } 
  }

  if ( Type == 2 ) {
    bool firstData = true ;
    Double_t DataInt = 0. ;
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      if ( ! (*itC)->isMC() && firstData ) { firstData=false ; DataInt = (*itC)->Integral(binx1, binx2 , biny1, biny2 ) ; }    
    }
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      (*itC)->Scale( (double) (DataInt/((*itC)->Integral(binx1, binx2 , biny1, biny2))) ) ;
    } 
  }

  if ( Type == 3 ) {
    bool firstData = true ;
    Double_t DataInt = 0. ;
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      if ( ! (*itC)->isMC() && firstData ) { firstData=false ; DataInt = (*itC)->Integral(binx1, binx2 , biny1, biny2 ) ; }    
    }
    Double_t MCSumInt = 0. ;
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      if ( (*itC)->isMC() ) MCSumInt += (*itC)->Integral(binx1, binx2 , biny1, biny2 ) ;
    }
    for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ) {
      if ( (*itC)->isMC() ) (*itC)->Scale( (double) (DataInt/MCSumInt) ) ;
      else                  (*itC)->Scale( (double) (DataInt/((*itC)->Integral(binx1, binx2 , biny1, biny2))) ) ; 
    } 
  }



/*
  cout << "[UACurve::Norm]  " << Curve_->ClassName() <<  endl;

  if ( this->isTH1() || this->isTH2() || this->isTGraph() ) {
    //cout << this->Integral(binx1, binx2 , biny1, biny2 ) << endl;
    this->Scale( (double) (1./this->Integral(binx1, binx2 , biny1, biny2 )) ) ; 
  } else {
    cout << "[UACurve::Norm] WARNING: Unknown Type : " << Curve_->ClassName() <<  endl;
  }
*/

}



// Draw -------------------------------------------------------------------------

void UAPlot::Draw(TString opt) {

  opt.ToLower();

  // Plot to same canvas ?
  bool plSame = false ;
  if ( opt.Contains("same") ) plSame = true ;

  // Set Automatic style
  if ( opt.Contains("style") ) AutoStyle();
 
  // Build vMCStack_ if requested
  bool plMCStack = false ;
  if ( opt.Contains("mcstack") || mcstack_ ) { plMCStack = true ; BuildMCStack() ; } ;

  // Norm All histo 

  int iC = 0;

  // First plot MCStack
  if ( plMCStack ) {
    for ( vector<UACurve*>::iterator itC = vMCStack_.begin() ; itC != vMCStack_.end() ; ++itC ){
      if (iC++ ==0 && !plSame ) { 
        ( (TH1*) (*itC)->pCurve())->GetYaxis()->SetRangeUser( 0.00001, (this->GetMaximum())*1.1 );
        if ( (*itC)->isTH1() || (*itC)->isTH2() ) { (*itC)->Draw();    }
        if ( (*itC)->isTGraph() )                 { (*itC)->Draw("a"); }
      } else  {
        if ( (*itC)->isTH1() || (*itC)->isTH2() ) { (*itC)->Draw("same"); }
        if ( (*itC)->isTGraph() )                 { (*itC)->Draw();    }
      }
    }
  }

  // Then Plot Curves not belonging to the MCStack
  for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
    if ( !plMCStack || ( plMCStack && !((*itC)->isMC()) ) ) {
      if (iC++ ==0 && !plSame) { 
        ( (TH1*) (*itC)->pCurve())->GetYaxis()->SetRangeUser( 0.00001, (this->GetMaximum())*1.1 );
        if ( (*itC)->isTH1() || (*itC)->isTH2() ) { (*itC)->Draw();    }
        if ( (*itC)->isTGraph() )                 { (*itC)->Draw("a"); }
      } else  {
        if ( (*itC)->isTH1() || (*itC)->isTH2() ) { (*itC)->Draw("same"); }
        if ( (*itC)->isTGraph() )                 { (*itC)->Draw();    }
      }
    }
  }

  // Make Legend
  cout << "*********** Making Legend ************" << endl ;
  for ( vector<UACurve*>::iterator itC = vUACurves_.begin() ; itC != vUACurves_.end() ; ++itC ){
     cout << "Plot Legend : " << (*itC)->GetLegend() << endl;
     (*itC)->Print();      
     UALegend_.AddLegend( **itC  ) ;
  } 
  UALegend_.BuildLegend() ;

}
