#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <Riostream.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TCut.h"
#include "TMath.h"
#include <cmath>

using namespace std;
using namespace TMath;

//https://github.com/ikrav/EgammaWork/blob/master/AnalysisScripts/computeElectronIDEfficiency.C
int main(int argc, char* argv[]){

  const TString dirname  = argv[1] ;
  const TString output   = argv[2] ;
  const TString treename = "ntuple/tree" ;
  const TString input    = dirname + "ntuple_*" ;

  TChain* tree = new TChain("ntuple/tree");
  tree->Add(input);
  TFile *outfile = new TFile(output,"RECREATE");

  int run;
  int nEle;  int nPV;
  float dPt_   ;  float dEta_  ;  float dPhi_  ;  float trg_dR_;
  ULong64_t HLTMuX ;
  vector<float> *pt         = 0; 
  vector<float> *et         = 0; 
  vector<float> *etaSC      = 0; 
  vector<float> *phiSC      = 0; 
  vector<int>   *passHEEPId   = 0;
  vector<int>   *isMatchTrue  = 0;
  vector<int>   *istrgMatchTrue = 0;

  bool isHLTEle115Pass  ;
  bool isHLTPho175Pass  ;
  bool isHLTPho200Pass  ;
  bool isHLTORALLPass   ;
  bool isHLTMuPass      ;
  bool isHLTMETPass     ;
 
  TBranch *b_run              = 0;       tree->SetBranchAddress("run"                      , &run                   , &b_run             );
  TBranch *b_nEle             = 0;       tree->SetBranchAddress("nEle"                     , &nEle                  , &b_nEle             );
  TBranch *b_nPV              = 0;       tree->SetBranchAddress("nPV"                      , &nPV                   , &b_nPV              );          
  TBranch *b_pt               = 0;       tree->SetBranchAddress("Ele_pt"                   , &pt                    , &b_pt               );          
  TBranch *b_et               = 0;       tree->SetBranchAddress("Ele_Et"                   , &et                    , &b_et               );          
  TBranch *b_etaSC            = 0;       tree->SetBranchAddress("Ele_etaSC"                , &etaSC                 , &b_etaSC            );          
  TBranch *b_phiSC            = 0;       tree->SetBranchAddress("Ele_phiSC"                , &phiSC                 , &b_phiSC            );          
  TBranch *b_passHEEPId       = 0;       tree->SetBranchAddress("Ele_passHEEPId"           , &passHEEPId            , &b_passHEEPId       );   
  TBranch *b_istrgMatchTrue   = 0;       tree->SetBranchAddress("istrgMatchTrue"           , &istrgMatchTrue        , &b_istrgMatchTrue   );           
  TBranch *b_HLTMuX           = 0;       tree->SetBranchAddress("HLTMuX"                   , &HLTMuX                , &b_HLTMuX           );            
  TBranch *b_isHLTEle115Pass  = 0;       tree->SetBranchAddress("isHLTEle115Pass"          , &isHLTEle115Pass       , &b_isHLTEle115Pass  );           
  TBranch *b_isHLTPho200Pass  = 0;       tree->SetBranchAddress("isHLTPho200Pass"          , &isHLTPho200Pass       , &b_isHLTPho200Pass  );           
  //-- histogram define
//  const Int_t ptbins = 30;
//  double edges[ptbins+1] = {0,20, 30,40, 50 ,60, 70 ,80, 90, 100, 110, 120, 130, 140, 150,160, 170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 600, 700, 800, 1000, 3000};
  const Int_t ptbins = 21;
  double edges[ptbins+1] = {0,20, 35, 40, 45, 50 ,60, 70 ,80, 90, 100, 110, 120, 130, 150,160, 170, 180, 190, 200, 300, 3000};

// more wider binning
//  const Int_t ptbins = 16;
//  double edges[ptbins+1] = {0,20, 35, 40, 45, 50 ,60, 70 ,80, 90, 100, 110, 120, 130, 200, 300, 3000};

  //-- denominator
  TH1F *h_total_nPV        = new TH1F("h_total_nPV"       , "h_total_nPV"        , 25, 0, 100);   
  TH1F *h_heep_eb_pt       = new TH1F("h_heep_eb_pt"      , "h_heep_eb_pt"       , ptbins, edges ); 
  TH1F *h_heep_ee_pt       = new TH1F("h_heep_ee_pt"      , "h_heep_ee_pt"       , ptbins, edges );
  TH1F *h_heep_etaSC       = new TH1F("h_heep_etaSC"      , "h_heep_etaSC"       , 32, -2.5, 2.5); 
  TH1F *h_heep_phiSC       = new TH1F("h_heep_phiSC"      , "h_heep_phiSC"       , 32, -3.2, 3.2); 
  TH1F *h_heep_nPV         = new TH1F("h_heep_nPV"        , "h_heep_nPV"         , 25, 0, 100);  
 
  TH1F *h_heep130_etaSC    = new TH1F("h_heep130_etaSC"   , "h_heep130_etaSC"       , 32, -2.5, 2.5); 
  TH1F *h_heep130_phiSC    = new TH1F("h_heep130_phiSC"   , "h_heep130_phiSC"       , 32, -3.2, 3.2); 
  TH1F *h_heep130_nPV      = new TH1F("h_heep130_nPV"     , "h_heep130_nPV"         , 25, 0, 100);   

  TH1F *h_hltMu_eb_pt   = new TH1F("h_hltMu_eb_pt"  , "h_hltMu_eb_pt"   , ptbins, edges );   
  TH1F *h_hltMu_ee_pt   = new TH1F("h_hltMu_ee_pt"  , "h_hltMu_ee_pt"   , ptbins, edges );   
  TH1F *h_hltMu_etaSC   = new TH1F("h_hltMu_etaSC"  , "h_hltMu_etaSC"   , 32, -2.5, 2.5);    
  TH1F *h_hltMu_phiSC   = new TH1F("h_hltMu_phiSC"  , "h_hltMu_phiSC"   , 32, -3.2, 3.2);    
  TH1F *h_hltMu_nPV     = new TH1F("h_hltMu_nPV"    , "h_hltMu_nPV"     , 25, 0, 100);      

  TH1F *h_hltORALL_eb_pt   = new TH1F("h_hltORALL_eb_pt"  , "h_hltORALL_eb_pt"   , ptbins, edges );   
  TH1F *h_hltORALL_ee_pt   = new TH1F("h_hltORALL_ee_pt"  , "h_hltORALL_ee_pt"   , ptbins, edges );   
  TH1F *h_hltORALL_etaSC   = new TH1F("h_hltORALL_etaSC"  , "h_hltORALL_etaSC"   , 32, -2.5, 2.5);    
  TH1F *h_hltORALL_phiSC   = new TH1F("h_hltORALL_phiSC"  , "h_hltORALL_phiSC"   , 32, -3.2, 3.2);    
  TH1F *h_hltORALL_nPV     = new TH1F("h_hltORALL_nPV"    , "h_hltORALL_nPV"     , 25, 0, 100);      

  TH1F *h_hltMuORALL_eb_pt   = new TH1F("h_hltMuORALL_eb_pt"  , "h_hltMuORALL_eb_pt"   , ptbins, edges );   
  TH1F *h_hltMuORALL_ee_pt   = new TH1F("h_hltMuORALL_ee_pt"  , "h_hltMuORALL_ee_pt"   , ptbins, edges );   
  TH1F *h_hltMuORALL_etaSC   = new TH1F("h_hltMuORALL_etaSC"  , "h_hltMuORALL_etaSC"   , 32, -2.5, 2.5);    
  TH1F *h_hltMuORALL_phiSC   = new TH1F("h_hltMuORALL_phiSC"  , "h_hltMuORALL_phiSC"   , 32, -3.2, 3.2);    
  TH1F *h_hltMuORALL_nPV     = new TH1F("h_hltMuORALL_nPV"    , "h_hltMuORALL_nPV"     , 25, 0, 100);      

  TGraphAsymmErrors *eff_hltMu_eb_pt =  new TGraphAsymmErrors(h_hltMu_eb_pt );  eff_hltMu_eb_pt->SetNameTitle("eff_hltMu_eb_pt", "eff_hltMu_eb_pt"); 
  TGraphAsymmErrors *eff_hltMu_ee_pt =  new TGraphAsymmErrors(h_hltMu_ee_pt );  eff_hltMu_ee_pt->SetNameTitle("eff_hltMu_ee_pt", "eff_hltMu_ee_pt"); 
  TGraphAsymmErrors *eff_hltMu_etaSC =  new TGraphAsymmErrors(h_hltMu_etaSC );  eff_hltMu_etaSC->SetNameTitle("eff_hltMu_etaSC", "eff_hltMu_etaSC"); 
  TGraphAsymmErrors *eff_hltMu_phiSC =  new TGraphAsymmErrors(h_hltMu_phiSC );  eff_hltMu_phiSC->SetNameTitle("eff_hltMu_phiSC", "eff_hltMu_phiSC"); 
  TGraphAsymmErrors *eff_hltMu_nPV   =  new TGraphAsymmErrors(h_hltMu_nPV   );  eff_hltMu_nPV  ->SetNameTitle("eff_hltMu_nPV"  , "eff_hltMu_nPV"  );

  TGraphAsymmErrors *eff_hltORALL_eb_pt  =  new TGraphAsymmErrors(h_hltORALL_eb_pt  );  eff_hltORALL_eb_pt ->SetNameTitle("eff_hltORALL_eb_pt" , "eff_hltORALL_eb_pt" );
  TGraphAsymmErrors *eff_hltORALL_ee_pt  =  new TGraphAsymmErrors(h_hltORALL_ee_pt  );  eff_hltORALL_ee_pt ->SetNameTitle("eff_hltORALL_ee_pt" , "eff_hltORALL_ee_pt" );
  TGraphAsymmErrors *eff_hltORALL_etaSC  =  new TGraphAsymmErrors(h_hltORALL_etaSC  );  eff_hltORALL_etaSC ->SetNameTitle("eff_hltORALL_etaSC" , "eff_hltORALL_etaSC" );
  TGraphAsymmErrors *eff_hltORALL_phiSC  =  new TGraphAsymmErrors(h_hltORALL_phiSC  );  eff_hltORALL_phiSC ->SetNameTitle("eff_hltORALL_phiSC" , "eff_hltORALL_phiSC" );
  TGraphAsymmErrors *eff_hltORALL_nPV    =  new TGraphAsymmErrors(h_hltORALL_nPV    );  eff_hltORALL_nPV   ->SetNameTitle("eff_hltORALL_nPV"   , "eff_hltORALL_nPV"   );

  TGraphAsymmErrors *eff_hltMuORALL_eb_pt =  new TGraphAsymmErrors(h_hltMuORALL_eb_pt );  eff_hltMuORALL_eb_pt->SetNameTitle("eff_hltMuORALL_eb_pt", "eff_hltMuORALL_eb_pt"); 
  TGraphAsymmErrors *eff_hltMuORALL_ee_pt =  new TGraphAsymmErrors(h_hltMuORALL_ee_pt );  eff_hltMuORALL_ee_pt->SetNameTitle("eff_hltMuORALL_ee_pt", "eff_hltMuORALL_ee_pt"); 
  TGraphAsymmErrors *eff_hltMuORALL_etaSC =  new TGraphAsymmErrors(h_hltMuORALL_etaSC );  eff_hltMuORALL_etaSC->SetNameTitle("eff_hltMuORALL_etaSC", "eff_hltMuORALL_etaSC"); 
  TGraphAsymmErrors *eff_hltMuORALL_phiSC =  new TGraphAsymmErrors(h_hltMuORALL_phiSC );  eff_hltMuORALL_phiSC->SetNameTitle("eff_hltMuORALL_phiSC", "eff_hltMuORALL_phiSC"); 
  TGraphAsymmErrors *eff_hltMuORALL_nPV   =  new TGraphAsymmErrors(h_hltMuORALL_nPV   );  eff_hltMuORALL_nPV  ->SetNameTitle("eff_hltMuORALL_nPV"  , "eff_hltMuORALL_nPV"  );

  //-- event counting check for N-1 eff
  int nMuHLT        = 0; int nHEEP         = 0;
  int nORALLHLT     = 0; int nMuORALLHLT   = 0;
  int nHEEP130      = 0; 
  int nEB_Base      = 0; int nEE_Base      = 0;
  int nEB_HEEP      = 0; int nEE_HEEP      = 0;
  int nEB_TrgMatch  = 0; int nEE_TrgMatch  = 0;

  int TotalN = tree->GetEntries();
  int per99 = (TotalN > 10) ? TotalN / 9 : 1;
  int per100 = 0;

  //--denominator  histograms 
  h_heep_eb_pt   ->Sumw2(); 
  h_heep_ee_pt   ->Sumw2();
  h_heep_etaSC   ->Sumw2();
  h_heep_phiSC   ->Sumw2();
  h_heep_nPV     ->Sumw2();
  h_heep130_etaSC->Sumw2();
  h_heep130_phiSC->Sumw2();
  h_heep130_nPV  ->Sumw2();

  h_hltMu_eb_pt ->Sumw2();
  h_hltMu_ee_pt ->Sumw2();
  h_hltMu_etaSC ->Sumw2();
  h_hltMu_phiSC ->Sumw2();
  h_hltMu_nPV   ->Sumw2();

  h_hltORALL_eb_pt ->Sumw2();
  h_hltORALL_ee_pt ->Sumw2();
  h_hltORALL_etaSC ->Sumw2();
  h_hltORALL_phiSC ->Sumw2();
  h_hltORALL_nPV   ->Sumw2();

  h_hltMuORALL_eb_pt ->Sumw2();
  h_hltMuORALL_ee_pt ->Sumw2();
  h_hltMuORALL_etaSC ->Sumw2();
  h_hltMuORALL_phiSC ->Sumw2();
  h_hltMuORALL_nPV   ->Sumw2();

  //-- start Loop over *Events*
  for(int ievent = 0; ievent < TotalN; ievent++){
      if(TotalN == 0 ) continue;
      if((ievent%per99) == 0) cout << "Running " << (per100++ * 10)<< " % " << ievent << " / " << TotalN << endl;
 
      Long64_t tentry   = tree->LoadTree(ievent);
      b_run                   ->GetEntry(tentry);
      b_nEle                  ->GetEntry(tentry);
      b_nPV                   ->GetEntry(tentry);
      b_pt                    ->GetEntry(tentry);
      b_et                    ->GetEntry(tentry);
      b_etaSC                 ->GetEntry(tentry);
      b_phiSC                 ->GetEntry(tentry);
      b_passHEEPId            ->GetEntry(tentry);      
      b_istrgMatchTrue        ->GetEntry(tentry); 
      b_HLTMuX                ->GetEntry(tentry);  
      b_isHLTEle115Pass       ->GetEntry(tentry); 
      b_isHLTPho200Pass       ->GetEntry(tentry); 

      bool isBarrel     = 0; 
      bool isEndcap     = 0; 
      bool isHEEP       = 0; 
      bool isPt130      = 0; 
      bool isTrgMatch   = 0; 
      bool isHLTEle115  = 0; 
      bool isHLTPho200  = 0; 
      bool isHLTORALL   = 0; 
      bool isHLTMu      = 0; 
      bool isHLTMuORALL = 0; 
 
      if(nEle == 0) continue; //-- HLT_Mu pass cut--#1
      h_total_nPV->Fill(nPV); // hist fill
      //-- start Loop over *Electrons* in one event
      for(int iele = 0; iele < nEle; iele++){
           bool isBarrel    = (fabs(etaSC->at(iele)) < 1.4442);
           bool isEndcap    = (fabs(etaSC->at(iele)) > 1.566);
           bool isHEEP      = passHEEPId->at(iele) ;
           bool isPt130     = (pt->at(iele) > 130);
           bool isTrgMatch  = istrgMatchTrue ; 
           bool isHLTEle115 = isHLTEle115Pass ; 
           bool isHLTPho200 = isHLTPho200Pass ; 
           bool isHLTORALL  = (isHLTEle115 || isHLTPho200)  ; 
           bool isHLTMu  = (HLTMuX > 0);
           bool isHLTMuORALL  = (isHLTMu && isHLTORALL);

           if(isBarrel) nEB_Base++; 
           if(isEndcap) nEE_Base++; 
 
           if(!isHEEP) continue;  //-- heep v70 cut --#2
           if(et->at(iele)<50) continue;  //-- heep v70 cut --#2
           nHEEP++;
           h_heep_etaSC ->Fill(etaSC->at(iele)); 
           h_heep_phiSC ->Fill(phiSC->at(iele));
           h_heep_nPV   ->Fill(nPV);
           if(isBarrel){ 
                nEB_HEEP++; 
                h_heep_eb_pt->Fill(et->at(iele));
                if(isTrgMatch && isHLTMu)      h_hltMu_eb_pt->Fill(et->at(iele)); //-- hlt mu reference #1
                if(isTrgMatch && isHLTORALL)   h_hltORALL_eb_pt->Fill(et->at(iele)); //-- hlt OR all cut #2
                if(isTrgMatch && isHLTMuORALL) h_hltMuORALL_eb_pt->Fill(et->at(iele)); //-- hlt mu and all cut #3
           }
           if(isEndcap){
                nEE_HEEP++; 
                h_heep_ee_pt->Fill(et->at(iele)); 
                if(isTrgMatch && isHLTMu)      h_hltMu_ee_pt->Fill(et->at(iele)); //-- hlt mu reference #1
                if(isTrgMatch && isHLTORALL)   h_hltORALL_ee_pt->Fill(et->at(iele)); //-- hlt OR all cut #2
                if(isTrgMatch && isHLTMuORALL) h_hltMuORALL_ee_pt->Fill(et->at(iele)); //-- hlt mu and all cut #3
           }

           if(isBarrel && isTrgMatch) nEB_TrgMatch++; 
           if(isEndcap && isTrgMatch) nEE_TrgMatch++; 
 
           if(!isPt130) continue; //-- offline e pt cut > 130 gev
           nHEEP130++;
           if(isHLTMu) nMuHLT++; 
           if(isHLTORALL) nORALLHLT++; 
           if(isHLTMuORALL) nMuORALLHLT++; 
           h_heep130_etaSC ->Fill(etaSC->at(iele)); 
           h_heep130_phiSC ->Fill(phiSC->at(iele));
           h_heep130_nPV   ->Fill(nPV);

           if(!isTrgMatch) continue; //-- trg obj - reco matching dPt, dR
           if(isHLTMu){ //-- hlt OR all cut #7
                h_hltMu_etaSC ->Fill(etaSC->at(iele)); 
                h_hltMu_phiSC ->Fill(phiSC->at(iele));
                h_hltMu_nPV   ->Fill(nPV);
           }
           if(isHLTORALL){ //-- hlt OR all cut #7
                h_hltORALL_etaSC ->Fill(etaSC->at(iele)); 
                h_hltORALL_phiSC ->Fill(phiSC->at(iele));
                h_hltORALL_nPV   ->Fill(nPV);
           }
           if(isHLTMuORALL){ //-- hlt OR all cut #7
                h_hltMuORALL_etaSC ->Fill(etaSC->at(iele)); 
                h_hltMuORALL_phiSC ->Fill(phiSC->at(iele));
                h_hltMuORALL_nPV   ->Fill(nPV);
           }
      }//--electron Loop over
  }//-- event Loop over

//  //-- define efficiency plot
   eff_hltMu_eb_pt ->Divide( h_hltMu_eb_pt , h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltMu_ee_pt ->Divide( h_hltMu_ee_pt , h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltMu_etaSC ->Divide( h_hltMu_etaSC , h_heep130_etaSC , "cl=0.683 b(1,1) mode");  
   eff_hltMu_phiSC ->Divide( h_hltMu_phiSC , h_heep130_phiSC , "cl=0.683 b(1,1) mode");  
   eff_hltMu_nPV   ->Divide( h_hltMu_nPV   , h_heep130_nPV   , "cl=0.683 b(1,1) mode");  

   eff_hltORALL_eb_pt ->Divide( h_hltORALL_eb_pt , h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_ee_pt ->Divide( h_hltORALL_ee_pt , h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_etaSC ->Divide( h_hltORALL_etaSC , h_heep130_etaSC , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_phiSC ->Divide( h_hltORALL_phiSC , h_heep130_phiSC , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_nPV   ->Divide( h_hltORALL_nPV   , h_heep130_nPV   , "cl=0.683 b(1,1) mode");  

   eff_hltMuORALL_eb_pt ->Divide( h_hltMuORALL_eb_pt , h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltMuORALL_ee_pt ->Divide( h_hltMuORALL_ee_pt , h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltMuORALL_etaSC ->Divide( h_hltMuORALL_etaSC , h_heep130_etaSC , "cl=0.683 b(1,1) mode");  
   eff_hltMuORALL_phiSC ->Divide( h_hltMuORALL_phiSC , h_heep130_phiSC , "cl=0.683 b(1,1) mode");  
   eff_hltMuORALL_nPV   ->Divide( h_hltMuORALL_nPV   , h_heep130_nPV   , "cl=0.683 b(1,1) mode");  

  h_total_nPV    ->Write();
  h_heep_eb_pt   ->Write(); 
  h_heep_ee_pt   ->Write();
  h_heep_etaSC   ->Write();
  h_heep_phiSC   ->Write();
  h_heep_nPV     ->Write();
  h_heep130_etaSC->Write();
  h_heep130_phiSC->Write();
  h_heep130_nPV  ->Write();
  //--numerator histograms
  h_hltMu_eb_pt ->Write();
  h_hltMu_ee_pt ->Write();
  h_hltMu_etaSC ->Write();
  h_hltMu_phiSC ->Write();
  h_hltMu_nPV   ->Write();

  h_hltORALL_eb_pt ->Write();
  h_hltORALL_ee_pt ->Write();
  h_hltORALL_etaSC ->Write();
  h_hltORALL_phiSC ->Write();
  h_hltORALL_nPV   ->Write();

  h_hltMuORALL_eb_pt ->Write();
  h_hltMuORALL_ee_pt ->Write();
  h_hltMuORALL_etaSC ->Write();
  h_hltMuORALL_phiSC ->Write();
  h_hltMuORALL_nPV   ->Write();

  eff_hltMu_eb_pt->Write("",TObject::kOverwrite);   
  eff_hltMu_ee_pt->Write("",TObject::kOverwrite);   
  eff_hltMu_etaSC->Write("",TObject::kOverwrite);   
  eff_hltMu_phiSC->Write("",TObject::kOverwrite);   
  eff_hltMu_nPV  ->Write("",TObject::kOverwrite);   

  eff_hltORALL_eb_pt->Write("",TObject::kOverwrite);   
  eff_hltORALL_ee_pt->Write("",TObject::kOverwrite);   
  eff_hltORALL_etaSC->Write("",TObject::kOverwrite);   
  eff_hltORALL_phiSC->Write("",TObject::kOverwrite);   
  eff_hltORALL_nPV  ->Write("",TObject::kOverwrite);   

  eff_hltMuORALL_eb_pt->Write("",TObject::kOverwrite);   
  eff_hltMuORALL_ee_pt->Write("",TObject::kOverwrite);   
  eff_hltMuORALL_etaSC->Write("",TObject::kOverwrite);   
  eff_hltMuORALL_phiSC->Write("",TObject::kOverwrite);   
  eff_hltMuORALL_nPV  ->Write("",TObject::kOverwrite);   
 

//-- print out summary
 cout << "##### " << dirname << " ## outfile = " << outfile << endl;
 cout << " Total Evt                = " << TotalN << endl;
 cout << " EB,EE Electron           = " << nEB_Base << " + " << nEE_Base << " = " << (nEB_Base + nEE_Base) << " 	(eb/ee) " << (double (nEB_Base)/ double (nEE_Base)) << endl;
 cout << " EB,EE HEEPV70            = " << nEB_HEEP << " + " << nEE_HEEP << " = " << nHEEP << " (eb/ee) " << (double (nEB_HEEP)/ double (nEE_HEEP)) << endl;
 cout << " EB,EE TrgMatch           = " << nEB_TrgMatch  << " + " << nEE_TrgMatch << " = " << (nEB_TrgMatch + nEE_TrgMatch) << " 	(eb/ee) " << (double (nEB_TrgMatch)/ double (nEE_TrgMatch)) << endl;
 cout << " EB,EE HEEP pt>130 cut    = " << nHEEP << " => " << nHEEP130 << " 	," << (double(nHEEP-nHEEP130)/double(nHEEP))*100 << " % out-" << (nHEEP-nHEEP130) << endl;

 cout << " Event HLT_Mu             = " << nMuHLT   << " /Total = " << (double (nMuHLT)/ double (TotalN) * 100) << " %" << endl;
 cout << " EB,EE HLT_ORALL          = " << nORALLHLT << " = " << h_hltORALL_eb_pt->Integral()  << " + " << h_hltORALL_ee_pt->Integral()   << " 	(eb/ee) " << (h_hltORALL_eb_pt->Integral()/h_hltORALL_ee_pt->Integral() ) << endl;
 cout << " EB,EE HLT_MuORALL        = " << nMuORALLHLT << " = " << h_hltMuORALL_eb_pt->Integral()  << " + " << h_hltMuORALL_ee_pt->Integral()   << " 	(eb/ee) " << (h_hltMuORALL_eb_pt->Integral()/h_hltMuORALL_ee_pt->Integral() ) << endl;

 cout << "==== with offline pt cut =================================== " << endl;

 cout << " den (offline cut HEEP, pt>130 GeV)     = " << h_heep130_etaSC->Integral() << " (130) 	"  << endl;
 cout << " num (den && HLT_Mu)   = " << h_hltMu_etaSC->Integral() <<  
                     "  	(Efficiency = " << (h_hltMu_etaSC->Integral()/h_heep130_etaSC->Integral())*100 << " %)" << endl;
 cout << " num (den && HLT_ORALL)   = " << h_hltORALL_etaSC->Integral() <<  
                     "  	(Efficiency = " << (h_hltORALL_etaSC->Integral()/h_heep130_etaSC->Integral())*100 << " %)" << endl;
 cout << " num (den && HLT_MuORALL)   = " << h_hltMuORALL_etaSC->Integral() <<  
                     "  	(Efficiency = " << (h_hltMuORALL_etaSC->Integral()/h_heep130_etaSC->Integral())*100 << " %)" << endl;
 cout << "======================================= " << endl;
 cout << " alpha = (eff_wp * eff_mu) / eff_wp_and_mu = " << ((h_hltORALL_etaSC->Integral()/h_heep130_etaSC->Integral()) * (h_hltMu_etaSC->Integral()/h_heep130_etaSC->Integral())) / (h_hltMuORALL_etaSC->Integral()/h_heep130_etaSC->Integral()) << " ~ 1 or not ?" << endl;
//  outfile->Write();
  outfile->Close();

  cout << "**** File Closed. " << endl;

  return 0;
}
