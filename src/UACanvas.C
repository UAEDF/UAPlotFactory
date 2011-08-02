
#include "../includes/UACanvas.h"

#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

#include <TSystem.h>

// Init() / Reset ()

void UACanvas::Init() {

   CanvasName_  = "UACanvas" ; 
   CanvasTitle_ = "UACanvas" ; 
   CanvasSizeX_ = 700 ;
   CanvasSizeY_ = 700 ;
   CanvasPosX_  = 0 ;
   CanvasPosY_  = 0 ;

   nPadX_ = 0 ;
   nPadY_ = 0 ;
   
}

void UACanvas::Reset() {
  
   for ( Int_t iPad = 0 ; iPad < (signed) Pads_.size() ; ++iPad ) delete Pads_.at(iPad) ;
   Pads_.clear()     ; 
   PadName_.clear()  ; 
   PadTitle_.clear() ;
   PadxLow_.clear()  ;
   PadyLow_.clear()  ;
   PadxUp_.clear()   ;
   PadyUp_.clear()   ;

   //this->Init();

   nPadX_ = 0 ;
   nPadY_ = 0 ;

   delete Canvas_;
   Canvas_ = new TCanvas(CanvasName_ , CanvasTitle_ , CanvasSizeX_ , CanvasSizeY_ ) ;

   Canvas_->cd(); 
}

// Defaul Constructor

UACanvas::UACanvas(){

  this->Init(); 

  Canvas_ = new TCanvas(CanvasName_ , CanvasTitle_ , CanvasSizeX_ , CanvasSizeY_ ) ;
  Canvas_->cd();

}

// Constructor

UACanvas::UACanvas( Int_t CanvasSizeX , Int_t CanvasSizeY ) {

  this->Init(); 

  CanvasSizeX_ = CanvasSizeX ;
  CanvasSizeY_ = CanvasSizeY ;

  Canvas_ = new TCanvas(CanvasName_ , CanvasTitle_ , CanvasSizeX_ , CanvasSizeY_ ) ;
  Canvas_->cd();

}

// Constructor

UACanvas::UACanvas( TString CanvasName , TString CanvasTitle , Int_t CanvasSizeX , Int_t CanvasSizeY ) {

  this->Init(); 

  CanvasName_  = CanvasName ;
  CanvasTitle_ = CanvasTitle ;
  CanvasSizeX_ = CanvasSizeX ;
  CanvasSizeY_ = CanvasSizeY ;

  Canvas_ = new TCanvas(CanvasName_ , CanvasTitle_ , CanvasSizeX_ , CanvasSizeY_ ) ;
  Canvas_->cd();

}

// Destructor 

UACanvas::~UACanvas(){
   
   cout << "UACanvas: Destructor" <<Pads_.size()   << endl; 

   for ( Int_t iPad = 0 ; iPad < (signed) Pads_.size() ; ++iPad ) delete Pads_.at(iPad) ;
   delete Canvas_ ;

}

// Create Pad

void UACanvas::CreatePad ( Double_t PadxLow , Double_t PadyLow , Double_t PadxUp , Double_t PadyUp  ) {

  Int_t   iPad     = (signed) Pads_.size() + 1 ; 
  stringstream Name("");
  Name << "UAPad_" << iPad ;

  PadName_.push_back( Name.str() ) ;
  PadTitle_.push_back( Name.str() ) ;
  PadxLow_.push_back( PadxLow ) ;
  PadyLow_.push_back( PadyLow ) ;
  PadxUp_.push_back( PadxUp ) ;
  PadyUp_.push_back( PadyUp ) ;

  Canvas_->cd();
  Pads_.push_back( new TPad ( PadName_.at(PadName_.size()-1) ,  PadTitle_.at(PadTitle_.size()-1) , PadxLow , PadyLow , PadxUp , PadyUp ) ) ;
  Pads_.at(Pads_.size()-1)->Draw();
  Pads_.at(Pads_.size()-1)->cd();
}

void UACanvas::Divide ( Int_t nPadX , Int_t nPadY ) {
  if ( nPadX * nPadY <= 0 )  {
    cout << "[UACanvas::Divide] WARNING : Divide not possible --> return !!!! " << endl;
    return;
  }   

  if ( nPadX_ * nPadY_ > 0 ) {
    cout << "[UACanvas::Divide] WARNING : Canvas_ already divided --> Reset() DONE !!!! " << endl; 
    this->Reset();
  } 
 
  nPadX_ = nPadX ;
  nPadY_ = nPadY ;

  Double_t PadWidthX = 1. / (double) nPadX ;
  Double_t PadWidthY = 1. / (double) nPadY ;

  for ( Int_t iPadY = nPadY-1 ; iPadY >= 0 ; --iPadY ) {
    for ( Int_t iPadX = 0 ; iPadX < nPadX ; ++iPadX ) {
       Double_t PadxLow = (double)iPadX * PadWidthX  ; 
       Double_t PadyLow = (double)iPadY * PadWidthY   ;
       Double_t PadxUp  = (double)(iPadX+1) * PadWidthX  ;  
       Double_t PadyUp  = (double)(iPadY+1) * PadWidthY  ;
       this->CreatePad( PadxLow , PadyLow , PadxUp , PadyUp );
    }
  }
}

TPad* UACanvas::GetPad(Int_t iPad) {
  if    ( iPad <= 0 || iPad > (signed) Pads_.size() ) return Canvas_ ;
  else                                                return Pads_.at(iPad-1);
} 

// Glue 2 Pads

void UACanvas::GluePads( Int_t iPad1 , Int_t iPad2 ) {

  if ( iPad1 == iPad2 ) {
     cout << "[UACanvas:GluePads] WARNING : iPad1 == iPad2 --> return !!!! " << endl;
    return;
  } 

  if ( iPad1 <= 0 || iPad2 <= 0 )  {
    cout << "[UACanvas:GluePads] WARNING : iPad# <= 0 --> return !!!! " << endl;
    return;
  } 

  if ( iPad1 >  (signed) Pads_.size() || iPad2 >  (signed) Pads_.size() )  {
    cout << "[UACanvas::GluePads] WARNING : Pads do not exist --> return !!!! " << endl;
    return;
  }

  Int_t iPadMin = min ( iPad1 , iPad2 ) ;
  Int_t iPadMax = max ( iPad1 , iPad2 ) ;

  --iPadMin;
  --iPadMax;

  if (     ( iPadMin % nPadX_ == iPadMax % nPadX_ )
       &&  ( int( iPadMin / nPadX_ + 1 ) == int( iPadMax / nPadX_ )  )   
     )             
  {
       Pads_.at(iPadMin)->SetBottomMargin (0.) ;
       Pads_.at(iPadMax)->SetTopMargin    (0.) ;
  } 


  if (    ( int( iPadMin / nPadX_ ) == int( iPadMax / nPadX_ )  ) 
       && ( int( iPadMin + 1 )      == int( iPadMax ) )
     )      
  {
       Pads_.at(iPadMin)->SetRightMargin (0.) ;
       Pads_.at(iPadMax)->SetLeftMargin  (0.) ;
  }

}

// Glue All Pads

void UACanvas::GlueAllPads( ) {

  for ( Int_t iPad1 = 1 ; iPad1 <= nPadX_*nPadY_-1  ; ++ iPad1 ) {
    for ( Int_t iPad2 = iPad1+1 ; iPad2 <= nPadX_*nPadY_  ; ++ iPad2 ) {
      this->GluePads( iPad1 , iPad2 ) ;
    }
  }

}

void UACanvas::AddText( TString text , Double_t x , Double_t y , Double_t size ) {

  cout << "[UACanvas::AddText()] Adding text \"" << text << "\" at pos : " << x << " , " << y << endl;
  TLatex* t = new TLatex( x , y , text);
  t->SetNDC(kTRUE);
  t->SetTextSize(size);
  t->Draw();
}

void UACanvas::AddText( TString text , Double_t size ) {
  Int_t length = text.Length()/10+1;
  Double_t x = (1.-0.1*length)/2.;
  this->AddText(text,x,0.965,size);
}

void UACanvas::Save(TString name , TString basedir){

  string filename ("");
  filename += basedir;
  filename += "/gif/";
  if (!gSystem->OpenDirectory(filename.c_str())) gSystem->mkdir(filename.c_str(),true);
  filename += name;
  if(Canvas_->GetLogy()) filename +="_logY";
  filename += ".gif";
  Canvas_->SaveAs(filename.c_str(),"");
  cout << "[UACanvas::Save] Saved Canvas in gif : " << filename << endl;


  filename = "";
  filename += basedir;
  filename += "/eps/";
  if (!gSystem->OpenDirectory(filename.c_str())) gSystem->mkdir(filename.c_str(),true);
  filename += name;
  if(Canvas_->GetLogy()) filename +="_logY";
  filename += ".eps";
  Canvas_->SaveAs(filename.c_str(),"");
  cout << "[UACanvas::Save] Saved Canvas in eps : " << filename << endl;
  
  string command("convert ") ;
  command += filename + " "; 
  filename = "";
  filename += basedir;
  filename += "/pdf/";
  if (!gSystem->OpenDirectory(filename.c_str())) gSystem->mkdir(filename.c_str(),true);
  filename += name;
  if(Canvas_->GetLogy()) filename +="_logY";
  filename += ".pdf";
  command += filename;
  gSystem->Exec(command.c_str());
  cout << "[UACanvas::Save] Saved Canvas in pdf : " << filename << endl;
  
  
}
