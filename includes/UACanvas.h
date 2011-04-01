#ifndef __UACanvas_H__
#define __UACanvas_H__

#include <TCanvas.h>
#include <TString.h>
#include <TLatex.h>

#include <vector>
using namespace std;

//class UACanvas : public TObject {
class UACanvas {


  private:

    // Canvas itself
    TCanvas* Canvas_       ;
    TString  CanvasName_   ;
    TString  CanvasTitle_  ; 
    Int_t    CanvasSizeX_  ;
    Int_t    CanvasSizeY_  ;
    Int_t    CanvasPosX_   ;
    Int_t    CanvasPosY_   ;

    // Canvas TPad's
    
    Int_t           nPadX_     ;
    Int_t           nPadY_     ;
    vector<TPad*>   Pads_      ;
    vector<TString> PadName_   ;
    vector<TString> PadTitle_  ;
    vector<Double_t>   PadxLow_  ;
    vector<Double_t>   PadyLow_  ;
    vector<Double_t>   PadxUp_   ;
    vector<Double_t>   PadyUp_   ;

  public:

    UACanvas();
    UACanvas(Int_t, Int_t );
    UACanvas(TString, TString, Int_t, Int_t );
    virtual ~UACanvas();

    void Init() ;
    void Reset();
    void Save(TString , TString = "../figs/");

    TCanvas* GetCanvas()      { return Canvas_ ;}
    TPad*    GetPad(Int_t=0 ) ;

    void CreatePad ( Double_t , Double_t , Double_t , Double_t ); 
    void Divide    ( Int_t , Int_t ) ;
    void cd        (Int_t iPad=0 ) { (this->GetPad(iPad))->cd(); } 
    void GluePads  ( Int_t , Int_t ) ; 
    void GlueAllPads();

    void AddText(TString , Double_t , Double_t , Double_t = 0.04);
};

#endif
