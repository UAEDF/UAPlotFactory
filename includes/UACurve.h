#ifndef __UACurve_H__
#define __UACurve_H__

//#include <memory>
//#include <tr1/shared_ptr.h>
//using std::tr1::shared_ptr ;

#include <TString.h>
#include <TObject.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TFile.h>

#include "UACurveStyle.h"

class UACurve : public UACurveStyle  {

  private:


    bool      isMC_   ;  
    TString   Legend_ ;
    //bool      isSyst_ ;
    TObject*  Curve_  ;

  public:
    
    UACurve( bool = true , TString="NONE" );
    UACurve( bool, TString , TString , TString="NONE" );
    UACurve( bool , TString , Int_t = 0 );

    virtual ~UACurve();

    TObject* pCurve() { return Curve_ ; } 

    //UACurveStyle* Style();

    bool isTH1    ();
    bool isTH2    ();
    bool isTGraph ();
    bool isMC() { return isMC_ ; }
    TString GetLegend() { return Legend_ ; }
    void SetLegend(TString Legend = "NONE" ) { Legend_ = Legend; }

    void PrintPtr();

    void Add( UACurve* , Double_t =1. ) ;  // this = this + c1*Curv1 
    void Add( UACurve* , UACurve* , Double_t =1. , Double_t =1. ) ; // this = c1*Curv1 + c2*Curv2


    void Scale ( Double_t = 1. );
    Double_t Integral ( Int_t=-1 , Int_t=-1 , Int_t=-1 , Int_t=-1 ); 
    void Norm  ( Int_t=-1 , Int_t=-1 , Int_t=-1 , Int_t=-1  );
    void Norm  ( UACurve& , Int_t=-1 , Int_t=-1 , Int_t=-1 , Int_t=-1 );
    void Norm  ( UACurve* , Int_t=-1 , Int_t=-1 , Int_t=-1 , Int_t=-1 );

/*
    void Add   ( UACurve& );
    void Add   ( UACurve* );
*/



    void ApplyStyle();
    void SetGoodAxis();

    Double_t GetMaximum() ; // Find Maximum 
    Double_t GetMinimum() ; // Find Minimum 
 
    void Draw(TString ="");

  // Operators -----------------------------------


    void Copy ( UACurve& ) const ;             // Copy  
    UACurve( const UACurve& ) ;                // Copy Constructor
    UACurve& operator= ( const UACurve& ) ;    // = operator 


};

#endif

