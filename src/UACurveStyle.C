#include "../includes/UACurveStyle.h"

// Constructor --------------------------------------------------------
UACurveStyle::UACurveStyle() { this->Init(); }

// Destructor ---------------------------------------------------------
UACurveStyle::~UACurveStyle() {cout << "UACurveStyle: Destructor"<<endl;}

// Init() -------------------------------------------------------------

void UACurveStyle::Init() {
  
    cout << "[UACurveStyle:Init()]" << endl ; 

    // Curve style: Marker
    markerColor = g_markerColor ;
    markerStyle = g_markerStyle ; 
    markerSize  = g_markerSize  ;

    // Curve style: Line  
    lineColor = g_lineColor ;
    lineStyle = g_lineStyle ; 
    lineWidth = g_lineWidth ;

    // Curve style: Fill Area
    fillColor = g_fillColor ;
    fillStyle = g_fillStyle ;

}

// SetStyle( UACurveStyle ) ---------------------------------------------

void UACurveStyle::SetStyle( UACurveStyle& RefStyle ) {

    // Curve style: Marker
    markerColor = RefStyle.markerColor ;
    markerStyle = RefStyle.markerStyle ; 
    markerSize  = RefStyle.markerSize  ;

    // Curve style: Line  
    lineColor = RefStyle.lineColor ;
    lineStyle = RefStyle.lineStyle ; 
    lineWidth = RefStyle.lineWidth ;

    // Curve style: Fill Area
    fillColor = RefStyle.fillColor ;
    fillStyle = RefStyle.fillStyle ;

} 

void UACurveStyle::SetStyle( UACurveStyle* RefStyle ) {
    SetStyle(*RefStyle);
}

// GetStyle () ----------------------------------------------------------

UACurveStyle* UACurveStyle::GetStyle() { 
  return (UACurveStyle*) this ;
} 

// Print () -------------------------------------------------------------

void UACurveStyle::Print() {

    cout << "[UACurveStyle::Print()] -------------------------" << endl; 

    // Curve style: Marker
    cout << "markerColor = "<< markerColor << endl ;
    cout << "markerStyle = "<< markerStyle << endl ; 
    cout << "markerSize  = "<< markerSize  << endl ;

    // Curve style: Line  
    cout << "lineColor = "<< lineColor << endl ;
    cout << "lineStyle = "<< lineStyle << endl ; 
    cout << "lineWidth = "<< lineWidth << endl ;

    // Curve style: Fill Area
    cout << "fillColor = "<< fillColor << endl ;
    cout << "fillStyle = "<< fillStyle << endl ;

}

// OPERATORS ========================================================================
/*
void  UACurveStyle::Copy ( UACurveStyle& New ) const {

  // Curve style: Marker
  New.markerColor = markerColor ;
  New.markerStyle = markerStyle ; 
  New.markerSize  = markerSize  ;

  // Curve style: Line  
  New.lineColor = lineColor ;
  New.lineStyle = lineStyle ; 
  New.lineWidth = lineWidth ;

  // Curve style: Fill Area
  New.fillColor = fillColor ;
  New.fillStyle = fillStyle ;

} 

UACurveStyle::UACurveStyle ( const UACurveStyle& S ) : UACurveStyleBase() {
  cout << "copy constructor" << endl;
  ((UACurveStyle&)S).Copy(*this) ;
} 

UACurveStyle& UACurveStyle::operator= ( const UACurveStyle& S ) { 
  cout << "equal " << endl;

  if (this != &S ) ((UACurveStyle&)S).Copy(*this);
  return *this;

}
*/

