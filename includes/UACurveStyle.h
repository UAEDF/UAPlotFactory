#ifndef __UACurveStyle_H__
#define __UACurveStyle_H__

#include <Rtypes.h>

#include "UACurveStyleBase.h"

class UACurveStyle : public UACurveStyleBase {

  private:


  public:

    UACurveStyle ();
    virtual ~UACurveStyle ();
    void Init();
    void SetStyle(UACurveStyle&);
    void SetStyle(UACurveStyle*);
    UACurveStyle* GetStyle();
    void Print();

    // Curve style: Marker
    Color_t markerColor ;
    Style_t markerStyle ; 
    Size_t  markerSize  ;

    // Curve style: Line  
    Color_t lineColor ;
    Style_t lineStyle ; 
    Width_t lineWidth ;

    // Curve style: Fill Area
    Color_t fillColor ;
    Style_t fillStyle ;

  // Operators -----------------------------------
/*
    void Copy ( UACurveStyle& ) const ;                  // Copy  
    UACurveStyle( const UACurveStyle& ) ;                // Copy Constructor
    UACurveStyle& operator= ( const UACurveStyle& ) ;    // = operator 
*/


};

#endif

