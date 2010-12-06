#include "../includes/UACurveStyleBase.h"

// Global style: Marker
Color_t UACurveStyleBase::g_markerColor = kBlack      ;
Style_t UACurveStyleBase::g_markerStyle = kFullCircle ; 
Size_t  UACurveStyleBase::g_markerSize  = 1           ;

// Global style: Line  
Color_t UACurveStyleBase::g_lineColor = kBlack ;
Style_t UACurveStyleBase::g_lineStyle = 1      ; 
Width_t UACurveStyleBase::g_lineWidth = 1      ;

// Global style: Fill Area
Color_t UACurveStyleBase::g_fillColor = 0;
Style_t UACurveStyleBase::g_fillStyle = 0;

// Constructor --------------------------------------------------------
UACurveStyleBase::UACurveStyleBase  () {;}

// Destructor ---------------------------------------------------------
UACurveStyleBase::~UACurveStyleBase () {;}

