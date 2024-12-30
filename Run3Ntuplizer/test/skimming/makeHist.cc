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
  //const int Min_run      = atoi(argv[3]) ;
  //const int Max_run      = atoi(argv[4]) ;
  //cout << "*** Min Run, Max Run " << Min_run << " - " << Max_run << endl;
//  if (Min_run == 0) cout << "Please specify minimum run number" << endl;
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
  vector<float> *hOverE     = 0; 
  vector<float> *dr03EcalRecHitSumEt  = 0;
  vector<float> *dr03HcalTowerSumEt       = 0; 
  vector<float> *dr03HcalDepth1TowerSumEt = 0;
  vector<float> *isoEmHadDepth1           = 0; 
  vector<float> *dEtaSeed   = 0; 
  vector<float> *dPhiIn     = 0; 
  vector<float> *full5x5_sigmaIetaIeta = 0; 
  vector<float> *dxy          = 0; 
  vector<int>   *passHEEPId   = 0;
  vector<int>   *isMatchTrue  = 0;
  vector<int>   *istrgMatchTrue = 0;

  bool isHLTEle35Pass   ;
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
  TBranch *b_hOverE           = 0;       tree->SetBranchAddress("Ele_hOverE"               , &hOverE                , &b_hOverE           );           
  TBranch *b_dr03EcalRecHitSumEt   = 0;  tree->SetBranchAddress("Ele_dr03EcalRecHitSumEt"      , &dr03EcalRecHitSumEt      , &b_dr03EcalRecHitSumEt     );
  TBranch *b_dr03HcalTowerSumEt    = 0;  tree->SetBranchAddress("Ele_dr03HcalTowerSumEt"       , &dr03HcalTowerSumEt       , &b_dr03HcalTowerSumEt          ); 
  TBranch *b_dr03HcalDepth1TowerSumEt= 0;tree->SetBranchAddress("Ele_dr03HcalDepth1TowerSumEt" , &dr03HcalDepth1TowerSumEt , &b_dr03HcalDepth1TowerSumEt    );
  TBranch *b_isoEmHadDepth1        = 0;  tree->SetBranchAddress("Ele_isoEmHadDepth1"           , &isoEmHadDepth1           , &b_isoEmHadDepth1              ); 
  TBranch *b_full5x5_sigmaIetaIeta = 0;  tree->SetBranchAddress("Ele_full5x5_sigmaIetaIeta", &full5x5_sigmaIetaIeta , &b_full5x5_sigmaIetaIeta    ); 
  TBranch *b_dEtaSeed         = 0;       tree->SetBranchAddress("Ele_dEtaSeed"             , &dEtaSeed              , &b_dEtaSeed         );
  TBranch *b_dPhiIn           = 0;       tree->SetBranchAddress("Ele_dPhiIn"               , &dPhiIn                , &b_dPhiIn           );
  TBranch *b_dxy              = 0;       tree->SetBranchAddress("Ele_dxy"                  , &dxy                   , &b_dxy              );
  TBranch *b_passHEEPId       = 0;       tree->SetBranchAddress("Ele_passHEEPId"           , &passHEEPId            , &b_passHEEPId       );   
  TBranch *b_istrgMatchTrue   = 0;       tree->SetBranchAddress("istrgMatchTrue"           , &istrgMatchTrue        , &b_istrgMatchTrue   );           
  TBranch *b_HLTMuX           = 0;       tree->SetBranchAddress("HLTMuX"                   , &HLTMuX                , &b_HLTMuX           );            
  TBranch *b_isHLTEle35Pass   = 0;       tree->SetBranchAddress("isHLTEle35Pass"           , &isHLTEle35Pass        , &b_isHLTEle35Pass   );           
  TBranch *b_isHLTEle115Pass  = 0;       tree->SetBranchAddress("isHLTEle115Pass"          , &isHLTEle115Pass       , &b_isHLTEle115Pass  );           
  TBranch *b_isHLTPho200Pass  = 0;       tree->SetBranchAddress("isHLTPho200Pass"          , &isHLTPho200Pass       , &b_isHLTPho200Pass  );           
  //-- histogram define
  //const Int_t ptbins = 30;
  //double edges[ptbins+1] = {0,20, 30,40, 50 ,60, 70 ,80, 90, 100, 110, 120, 130, 140, 150,160, 170, 180, 190, 200, 250, 300, 350, 400, 450, 500, 600, 700, 800, 1000, 3000};
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
  TH1F *h_heep_sigma       = new TH1F("h_heep_sigma"      , "h_heep_sigma"       , 40, 0, 0.05);   
  TH1F *h_heep_hoe         = new TH1F("h_heep_hoe"        , "h_heep_hoe"         , 30, 0, 0.1);    
  TH1F *h_heep_deta        = new TH1F("h_heep_deta"       , "h_heep_deta"        , 30, 0, 0.01);
  TH1F *h_heep_dphi        = new TH1F("h_heep_dphi"       , "h_heep_dphi"        , 30, 0, 0.1);
  TH1F *h_heep_dxy         = new TH1F("h_heep_dxy"        , "h_heep_dxy "        , 30, 0, 0.1);
  TH1F *h_heep_nPV         = new TH1F("h_heep_nPV"        , "h_heep_nPV"         , 25, 0, 100);  
  TH1F *h_heep_dr03EcalRecHitSumEt        = new TH1F("h_heep_dr03EcalRecHitSumEt",      "h_heep_dr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_heep_dr03HcalTowerSumEt         = new TH1F("h_heep_dr03HcalTowerSumEt",       "h_heep_dr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_heep_dr03HcalDepth1TowerSumEt   = new TH1F("h_heep_dr03HcalDepth1TowerSumEt", "h_heep_dr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_heep_isoEmHadDepth1             = new TH1F("h_heep_isoEmHadDepth1",           "h_heep_isoEmHadDepth1", 25,0,50);             
  TH1F *h_heep_EBdr03EcalRecHitSumEt      = new TH1F("h_heep_EBdr03EcalRecHitSumEt",      "h_heep_EBdr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_heep_EBdr03HcalTowerSumEt       = new TH1F("h_heep_EBdr03HcalTowerSumEt",       "h_heep_EBdr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_heep_EBdr03HcalDepth1TowerSumEt = new TH1F("h_heep_EBdr03HcalDepth1TowerSumEt", "h_heep_EBdr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_heep_EBisoEmHadDepth1           = new TH1F("h_heep_EBisoEmHadDepth1",           "h_heep_EBisoEmHadDepth1", 25,0,50);             

 
  TH1F *h_heep130_etaSC    = new TH1F("h_heep130_etaSC"   , "h_heep130_etaSC"       , 32, -2.5, 2.5); 
  TH1F *h_heep130_phiSC    = new TH1F("h_heep130_phiSC"   , "h_heep130_phiSC"       , 32, -3.2, 3.2); 
  TH1F *h_heep130_sigma    = new TH1F("h_heep130_sigma"   , "h_heep130_sigma"       , 40, 0, 0.05);   
  TH1F *h_heep130_hoe      = new TH1F("h_heep130_hoe"     , "h_heep130_hoe"         , 40, 0, 0.1);    
  TH1F *h_heep130_deta     = new TH1F("h_heep130_deta"    , "h_heep130_deta"        , 30, 0, 0.01);
  TH1F *h_heep130_dphi     = new TH1F("h_heep130_dphi"    , "h_heep130_dphi"        , 30, 0, 0.1);
  TH1F *h_heep130_dxy      = new TH1F("h_heep130_dxy"     , "h_heep130_dxy "        , 30, 0, 0.1);
  TH1F *h_heep130_nPV      = new TH1F("h_heep130_nPV"     , "h_heep130_nPV"         , 25, 0, 100);   
  TH1F *h_heep130_dr03EcalRecHitSumEt      = new TH1F("h_heep130_dr03EcalRecHitSumEt",      "h_heep130_dr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_heep130_dr03HcalTowerSumEt       = new TH1F("h_heep130_dr03HcalTowerSumEt",       "h_heep130_dr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_heep130_dr03HcalDepth1TowerSumEt = new TH1F("h_heep130_dr03HcalDepth1TowerSumEt", "h_heep130_dr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_heep130_isoEmHadDepth1           = new TH1F("h_heep130_isoEmHadDepth1",           "h_heep130_isoEmHadDepth1", 25,0,50);             
  TH1F *h_heep130_EBdr03EcalRecHitSumEt      = new TH1F("h_heep130_EBdr03EcalRecHitSumEt",      "h_heep130_EBdr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_heep130_EBdr03HcalTowerSumEt       = new TH1F("h_heep130_EBdr03HcalTowerSumEt",       "h_heep130_EBdr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_heep130_EBdr03HcalDepth1TowerSumEt = new TH1F("h_heep130_EBdr03HcalDepth1TowerSumEt", "h_heep130_EBdr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_heep130_EBisoEmHadDepth1           = new TH1F("h_heep130_EBisoEmHadDepth1",           "h_heep130_EBisoEmHadDepth1", 25,0,50);             

  TH1F *h_heep240_etaSC    = new TH1F("h_heep240_etaSC"   , "h_heep_etaSC"       , 32, -2.5, 2.5); 
  TH1F *h_heep240_phiSC    = new TH1F("h_heep240_phiSC"   , "h_heep_phiSC"       , 32, -3.2, 3.2); 
  TH1F *h_heep240_sigma    = new TH1F("h_heep240_sigma"   , "h_heep_sigma"       , 40, 0, 0.05);   
  TH1F *h_heep240_hoe      = new TH1F("h_heep240_hoe"     , "h_heep_hoe"         , 40, 0, 0.1);    
  TH1F *h_heep240_deta     = new TH1F("h_heep240_deta"    , "h_heep_deta"        , 30, 0, 0.01);
  TH1F *h_heep240_dphi     = new TH1F("h_heep240_dphi"    , "h_heep_dphi"        , 30, 0, 0.1);
  TH1F *h_heep240_dxy      = new TH1F("h_heep240_dxy"     , "h_heep_dxy "        , 30, 0, 0.1);
  TH1F *h_heep240_nPV      = new TH1F("h_heep240_nPV"     , "h_heep_nPV"         , 25, 0, 100);   
  TH1F *h_heep240_dr03EcalRecHitSumEt      = new TH1F("h_heep240_dr03EcalRecHitSumEt",      "h_heep240_dr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_heep240_dr03HcalTowerSumEt       = new TH1F("h_heep240_dr03HcalTowerSumEt",       "h_heep240_dr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_heep240_dr03HcalDepth1TowerSumEt = new TH1F("h_heep240_dr03HcalDepth1TowerSumEt", "h_heep240_dr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_heep240_isoEmHadDepth1           = new TH1F("h_heep240_isoEmHadDepth1",           "h_heep240_isoEmHadDepth1", 25,0,50);             
  TH1F *h_heep240_EBdr03EcalRecHitSumEt      = new TH1F("h_heep240_EBdr03EcalRecHitSumEt",      "h_heep240_EBdr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_heep240_EBdr03HcalTowerSumEt       = new TH1F("h_heep240_EBdr03HcalTowerSumEt",       "h_heep240_EBdr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_heep240_EBdr03HcalDepth1TowerSumEt = new TH1F("h_heep240_EBdr03HcalDepth1TowerSumEt", "h_heep240_EBdr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_heep240_EBisoEmHadDepth1           = new TH1F("h_heep240_EBisoEmHadDepth1",           "h_heep240_EBisoEmHadDepth1", 25,0,50);             
  //-- numerator
  //TH1F *h_hltEle35_eb_pt   = new TH1F("h_hltEle35_eb_pt"  , "h_hltEle35_eb_pt"   , ptbins, edges );
  //TH1F *h_hltEle35_ee_pt   = new TH1F("h_hltEle35_ee_pt"  , "h_hltEle35_ee_pt"   , ptbins, edges );
  //TH1F *h_hltEle35_etaSC   = new TH1F("h_hltEle35_etaSC"  , "h_hltEle35_etaSC"   , 32, -2.5, 2.5); 
  //TH1F *h_hltEle35_phiSC   = new TH1F("h_hltEle35_phiSC"  , "h_hltEle35_phiSC"   , 32, -3.2, 3.2); 
  //TH1F *h_hltEle35_sigma   = new TH1F("h_hltEle35_sigma"  , "h_hltEle35_sigma"   , 40, 0, 0.05);   
  //TH1F *h_hltEle35_hoe     = new TH1F("h_hltEle35_hoe"    , "h_hltEle35_hoe"     , 40, 0, 0.1);    
  //TH1F *h_hltEle35_deta    = new TH1F("h_hltEle35_deta"   , "h_hltEle35_deta"    , 40, 0, 0.01);
  //TH1F *h_hltEle35_dphi    = new TH1F("h_hltEle35_dphi"   , "h_hltEle35_dphi"    , 40, 0, 0.1);
  //TH1F *h_hltEle35_dxy     = new TH1F("h_hltEle35_dxy"    , "h_hltEle35_dxy "    , 40, 0, 0.1);
  //TH1F *h_hltEle35_nPV     = new TH1F("h_hltEle35_nPV"    , "h_hltEle35_nPV"     , 25, 0, 100);   

  TH1F *h_hltEle115_eb_pt  = new TH1F("h_hltEle115_eb_pt" , "h_hltEle115_eb_pt"  , ptbins, edges );
  TH1F *h_hltEle115_ee_pt  = new TH1F("h_hltEle115_ee_pt" , "h_hltEle115_ee_pt"  , ptbins, edges );
  TH1F *h_hltEle115_etaSC  = new TH1F("h_hltEle115_etaSC" , "h_hltEle115_etaSC"  , 32, -2.5, 2.5); 
  TH1F *h_hltEle115_phiSC  = new TH1F("h_hltEle115_phiSC" , "h_hltEle115_phiSC"  , 32, -3.2, 3.2); 
  TH1F *h_hltEle115_sigma  = new TH1F("h_hltEle115_sigma" , "h_hltEle115_sigma"  , 40, 0, 0.05);   
  TH1F *h_hltEle115_hoe    = new TH1F("h_hltEle115_hoe"   , "h_hltEle115_hoe"    , 40, 0, 0.1);    
  TH1F *h_hltEle115_deta   = new TH1F("h_hltEle115_deta"  , "h_hltEle115_deta"   , 30, 0, 0.01);
  TH1F *h_hltEle115_dphi   = new TH1F("h_hltEle115_dphi"  , "h_hltEle115_dphi"   , 30, 0, 0.1);
  TH1F *h_hltEle115_dxy    = new TH1F("h_hltEle115_dxy"   , "h_hltEle115_dxy "   , 30, 0, 0.1);
  TH1F *h_hltEle115_nPV    = new TH1F("h_hltEle115_nPV"   , "h_hltEle115_nPV"    , 25, 0, 100);   
  TH1F *h_hltEle115_dr03EcalRecHitSumEt      = new TH1F("h_hltEle115_dr03EcalRecHitSumEt",      "h_hltEle115_dr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_hltEle115_dr03HcalTowerSumEt       = new TH1F("h_hltEle115_dr03HcalTowerSumEt",       "h_hltEle115_dr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_hltEle115_dr03HcalDepth1TowerSumEt = new TH1F("h_hltEle115_dr03HcalDepth1TowerSumEt", "h_hltEle115_dr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_hltEle115_isoEmHadDepth1           = new TH1F("h_hltEle115_isoEmHadDepth1",           "h_hltEle115_isoEmHadDepth1", 25,0,50);             
  TH1F *h_hltEle115_EBdr03EcalRecHitSumEt      = new TH1F("h_hltEle115_EBdr03EcalRecHitSumEt",      "h_hltEle115_EBdr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_hltEle115_EBdr03HcalTowerSumEt       = new TH1F("h_hltEle115_EBdr03HcalTowerSumEt",       "h_hltEle115_EBdr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_hltEle115_EBdr03HcalDepth1TowerSumEt = new TH1F("h_hltEle115_EBdr03HcalDepth1TowerSumEt", "h_hltEle115_EBdr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_hltEle115_EBisoEmHadDepth1           = new TH1F("h_hltEle115_EBisoEmHadDepth1",           "h_hltEle115_EBisoEmHadDepth1", 25,0,50);             
                                                                                                   
  TH1F *h_hltPho200_eb_pt  = new TH1F("h_hltPho200_eb_pt" , "h_hltPho200_eb_pt"  , ptbins, edges );
  TH1F *h_hltPho200_ee_pt  = new TH1F("h_hltPho200_ee_pt" , "h_hltPho200_ee_pt"  , ptbins, edges );
  TH1F *h_hltPho200_etaSC  = new TH1F("h_hltPho200_etaSC" , "h_hltPho200_etaSC"  , 32, -2.5, 2.5); 
  TH1F *h_hltPho200_phiSC  = new TH1F("h_hltPho200_phiSC" , "h_hltPho200_phiSC"  , 32, -3.2, 3.2); 
  TH1F *h_hltPho200_sigma  = new TH1F("h_hltPho200_sigma" , "h_hltPho200_sigma"  , 40, 0, 0.05);   
  TH1F *h_hltPho200_hoe    = new TH1F("h_hltPho200_hoe"   , "h_hltPho200_hoe"    , 40, 0, 0.1);    
  TH1F *h_hltPho200_deta   = new TH1F("h_hltPho200_deta"  , "h_hltPho200_deta"   , 30, 0, 0.01);
  TH1F *h_hltPho200_dphi   = new TH1F("h_hltPho200_dphi"  , "h_hltPho200_dphi"   , 30, 0, 0.1);
  TH1F *h_hltPho200_dxy    = new TH1F("h_hltPho200_dxy"   , "h_hltPho200_dxy "   , 30, 0, 0.1);
  TH1F *h_hltPho200_nPV    = new TH1F("h_hltPho200_nPV"   , "h_hltPho200_nPV"    , 25, 0, 100);   
  TH1F *h_hltPho200_dr03EcalRecHitSumEt      = new TH1F("h_hltPho200_dr03EcalRecHitSumEt",      "h_hltPho200_dr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_hltPho200_dr03HcalTowerSumEt       = new TH1F("h_hltPho200_dr03HcalTowerSumEt",       "h_hltPho200_dr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_hltPho200_dr03HcalDepth1TowerSumEt = new TH1F("h_hltPho200_dr03HcalDepth1TowerSumEt", "h_hltPho200_dr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_hltPho200_isoEmHadDepth1           = new TH1F("h_hltPho200_isoEmHadDepth1",           "h_hltPho200_isoEmHadDepth1", 25,0,50);             
  TH1F *h_hltPho200_EBdr03EcalRecHitSumEt      = new TH1F("h_hltPho200_EBdr03EcalRecHitSumEt",      "h_hltPho200_EBdr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_hltPho200_EBdr03HcalTowerSumEt       = new TH1F("h_hltPho200_EBdr03HcalTowerSumEt",       "h_hltPho200_EBdr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_hltPho200_EBdr03HcalDepth1TowerSumEt = new TH1F("h_hltPho200_EBdr03HcalDepth1TowerSumEt", "h_hltPho200_EBdr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_hltPho200_EBisoEmHadDepth1           = new TH1F("h_hltPho200_EBisoEmHadDepth1",           "h_hltPho200_EBisoEmHadDepth1", 25,0,50);             
                                                                                                   
  TH1F *h_hltORALL_eb_pt   = new TH1F("h_hltORALL_eb_pt"  , "h_hltORALL_eb_pt"   , ptbins, edges );   
  TH1F *h_hltORALL_ee_pt   = new TH1F("h_hltORALL_ee_pt"  , "h_hltORALL_ee_pt"   , ptbins, edges );   
  TH1F *h_hltORALL_etaSC   = new TH1F("h_hltORALL_etaSC"  , "h_hltORALL_etaSC"   , 32, -2.5, 2.5);    
  TH1F *h_hltORALL_phiSC   = new TH1F("h_hltORALL_phiSC"  , "h_hltORALL_phiSC"   , 32, -3.2, 3.2);    
  TH1F *h_hltORALL_sigma   = new TH1F("h_hltORALL_sigma"  , "h_hltORALL_sigma"   , 40, 0, 0.05);      
  TH1F *h_hltORALL_hoe     = new TH1F("h_hltORALL_hoe"    , "h_hltORALL_hoe"     , 30, 0, 0.1);       
  TH1F *h_hltORALL_deta    = new TH1F("h_hltORALL_deta"   , "h_hltORALL_deta"    , 30, 0, 0.01);
  TH1F *h_hltORALL_dphi    = new TH1F("h_hltORALL_dphi"   , "h_hltORALL_dphi"    , 30, 0, 0.1);
  TH1F *h_hltORALL_dxy     = new TH1F("h_hltORALL_dxy"    , "h_hltORALL_dxy "    , 30, 0, 0.1);
  TH1F *h_hltORALL_nPV     = new TH1F("h_hltORALL_nPV"    , "h_hltORALL_nPV"     , 25, 0, 100);      
  TH1F *h_hltORALL_dr03EcalRecHitSumEt      = new TH1F("h_hltORALL_dr03EcalRecHitSumEt",      "h_hltORALL_dr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_hltORALL_dr03HcalTowerSumEt       = new TH1F("h_hltORALL_dr03HcalTowerSumEt",       "h_hltORALL_dr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_hltORALL_dr03HcalDepth1TowerSumEt = new TH1F("h_hltORALL_dr03HcalDepth1TowerSumEt", "h_hltORALL_dr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_hltORALL_isoEmHadDepth1           = new TH1F("h_hltORALL_isoEmHadDepth1",           "h_hltORALL_isoEmHadDepth1", 25,0,50);             
  TH1F *h_hltORALL_EBdr03EcalRecHitSumEt      = new TH1F("h_hltORALL_EBdr03EcalRecHitSumEt",      "h_hltORALL_EBdr03EcalRecHitSumEt", 40,0,80);          
  TH1F *h_hltORALL_EBdr03HcalTowerSumEt       = new TH1F("h_hltORALL_EBdr03HcalTowerSumEt",       "h_hltORALL_EBdr03HcalTowerSumEt",  40,0,80);           
  TH1F *h_hltORALL_EBdr03HcalDepth1TowerSumEt = new TH1F("h_hltORALL_EBdr03HcalDepth1TowerSumEt", "h_hltORALL_EBdr03HcalDepth1TowerSumEt", 20,0,20);  
  TH1F *h_hltORALL_EBisoEmHadDepth1           = new TH1F("h_hltORALL_EBisoEmHadDepth1",           "h_hltORALL_EBisoEmHadDepth1", 25,0,50);             

//  TGraphAsymmErrors *eff_hltEle35_eb_pt  =  new TGraphAsymmErrors(h_hltEle35_eb_pt  );  eff_hltEle35_eb_pt ->SetNameTitle("eff_hltEle35_eb_pt" , "eff_hltEle35_eb_pt" );   
//  TGraphAsymmErrors *eff_hltEle35_ee_pt  =  new TGraphAsymmErrors(h_hltEle35_ee_pt  );  eff_hltEle35_ee_pt ->SetNameTitle("eff_hltEle35_ee_pt" , "eff_hltEle35_ee_pt" );
//  TGraphAsymmErrors *eff_hltEle35_etaSC  =  new TGraphAsymmErrors(h_hltEle35_etaSC  );  eff_hltEle35_etaSC ->SetNameTitle("eff_hltEle35_etaSC" , "eff_hltEle35_etaSC" );
//  TGraphAsymmErrors *eff_hltEle35_phiSC  =  new TGraphAsymmErrors(h_hltEle35_phiSC  );  eff_hltEle35_phiSC ->SetNameTitle("eff_hltEle35_phiSC" , "eff_hltEle35_phiSC" );
//  TGraphAsymmErrors *eff_hltEle35_sigma  =  new TGraphAsymmErrors(h_hltEle35_sigma  );  eff_hltEle35_sigma ->SetNameTitle("eff_hltEle35_sigma" , "eff_hltEle35_sigma" );
//  TGraphAsymmErrors *eff_hltEle35_hoe    =  new TGraphAsymmErrors(h_hltEle35_hoe    );  eff_hltEle35_hoe   ->SetNameTitle("eff_hltEle35_hoe"   , "eff_hltEle35_hoe"   );
//  TGraphAsymmErrors *eff_hltEle35_deta   =  new TGraphAsymmErrors(h_hltEle35_deta   );  eff_hltEle35_deta  ->SetNameTitle("eff_hltEle35_deta"  , "eff_hltEle35_deta"  );
//  TGraphAsymmErrors *eff_hltEle35_dphi   =  new TGraphAsymmErrors(h_hltEle35_dphi   );  eff_hltEle35_dphi  ->SetNameTitle("eff_hltEle35_dphi"  , "eff_hltEle35_dphi"  );
//  TGraphAsymmErrors *eff_hltEle35_dxy    =  new TGraphAsymmErrors(h_hltEle35_dxy    );  eff_hltEle35_dxy   ->SetNameTitle("eff_hltEle35_dxy"   , "eff_hltEle35_dxy"   );
//  TGraphAsymmErrors *eff_hltEle35_nPV    =  new TGraphAsymmErrors(h_hltEle35_nPV    );  eff_hltEle35_nPV   ->SetNameTitle("eff_hltEle35_nPV"   , "eff_hltEle35_nPV"   );
//                                                                                                                                                                      
  TGraphAsymmErrors *eff_hltEle115_eb_pt =  new TGraphAsymmErrors(h_hltEle115_eb_pt );  eff_hltEle115_eb_pt->SetNameTitle("eff_hltEle115_eb_pt", "eff_hltEle115_eb_pt"); 
  TGraphAsymmErrors *eff_hltEle115_ee_pt =  new TGraphAsymmErrors(h_hltEle115_ee_pt );  eff_hltEle115_ee_pt->SetNameTitle("eff_hltEle115_ee_pt", "eff_hltEle115_ee_pt"); 
  TGraphAsymmErrors *eff_hltEle115_etaSC =  new TGraphAsymmErrors(h_hltEle115_etaSC );  eff_hltEle115_etaSC->SetNameTitle("eff_hltEle115_etaSC", "eff_hltEle115_etaSC"); 
  TGraphAsymmErrors *eff_hltEle115_phiSC =  new TGraphAsymmErrors(h_hltEle115_phiSC );  eff_hltEle115_phiSC->SetNameTitle("eff_hltEle115_phiSC", "eff_hltEle115_phiSC"); 
  TGraphAsymmErrors *eff_hltEle115_sigma =  new TGraphAsymmErrors(h_hltEle115_sigma );  eff_hltEle115_sigma->SetNameTitle("eff_hltEle115_sigma", "eff_hltEle115_sigma"); 
  TGraphAsymmErrors *eff_hltEle115_hoe   =  new TGraphAsymmErrors(h_hltEle115_hoe   );  eff_hltEle115_hoe  ->SetNameTitle("eff_hltEle115_hoe"  , "eff_hltEle115_hoe"  ); 
  TGraphAsymmErrors *eff_hltEle115_deta  =  new TGraphAsymmErrors(h_hltEle115_deta  );  eff_hltEle115_deta ->SetNameTitle("eff_hltEle115_deta" , "eff_hltEle115_deta" );
  TGraphAsymmErrors *eff_hltEle115_dphi  =  new TGraphAsymmErrors(h_hltEle115_dphi  );  eff_hltEle115_dphi ->SetNameTitle("eff_hltEle115_dphi" , "eff_hltEle115_dphi" );
  TGraphAsymmErrors *eff_hltEle115_dxy   =  new TGraphAsymmErrors(h_hltEle115_dxy   );  eff_hltEle115_dxy  ->SetNameTitle("eff_hltEle115_dxy"  , "eff_hltEle115_dxy"  );
  TGraphAsymmErrors *eff_hltEle115_nPV   =  new TGraphAsymmErrors(h_hltEle115_nPV   );  eff_hltEle115_nPV  ->SetNameTitle("eff_hltEle115_nPV"  , "eff_hltEle115_nPV"  );
  TGraphAsymmErrors *eff_hltEle115_dr03EcalRecHitSumEt   =  new TGraphAsymmErrors(h_hltEle115_dr03EcalRecHitSumEt   );  eff_hltEle115_dr03EcalRecHitSumEt  ->SetNameTitle("eff_hltEle115_dr03EcalRecHitSumEt"  , "eff_hltEle115_dr03EcalRecHitSumEt"  );
  TGraphAsymmErrors *eff_hltEle115_dr03HcalTowerSumEt   =  new TGraphAsymmErrors(h_hltEle115_dr03HcalTowerSumEt   );  eff_hltEle115_dr03HcalTowerSumEt  ->SetNameTitle("eff_hltEle115_dr03HcalTowerSumEt"  , "eff_hltEle115_dr03HcalTowerSumEt"  );
  TGraphAsymmErrors *eff_hltEle115_dr03HcalDepth1TowerSumEt   =  new TGraphAsymmErrors(h_hltEle115_dr03HcalDepth1TowerSumEt   );  eff_hltEle115_dr03HcalDepth1TowerSumEt  ->SetNameTitle("eff_hltEle115_dr03HcalDepth1TowerSumEt"  , "eff_hltEle115_dr03HcalDepth1TowerSumEt"  );
  TGraphAsymmErrors *eff_hltEle115_isoEmHadDepth1   =  new TGraphAsymmErrors(h_hltEle115_isoEmHadDepth1   );  eff_hltEle115_isoEmHadDepth1  ->SetNameTitle("eff_hltEle115_isoEmHadDepth1"  , "eff_hltEle115_isoEmHadDepth1"  );
  TGraphAsymmErrors *eff_hltEle115_EBdr03EcalRecHitSumEt   =  new TGraphAsymmErrors(h_hltEle115_EBdr03EcalRecHitSumEt   );  eff_hltEle115_EBdr03EcalRecHitSumEt  ->SetNameTitle("eff_hltEle115_EBdr03EcalRecHitSumEt"  , "eff_hltEle115_EBdr03EcalRecHitSumEt"  );
  TGraphAsymmErrors *eff_hltEle115_EBdr03HcalTowerSumEt   =  new TGraphAsymmErrors(h_hltEle115_EBdr03HcalTowerSumEt   );  eff_hltEle115_EBdr03HcalTowerSumEt  ->SetNameTitle("eff_hltEle115_EBdr03HcalTowerSumEt"  , "eff_hltEle115_EBdr03HcalTowerSumEt"  );
  TGraphAsymmErrors *eff_hltEle115_EBdr03HcalDepth1TowerSumEt   =  new TGraphAsymmErrors(h_hltEle115_EBdr03HcalDepth1TowerSumEt   );  eff_hltEle115_EBdr03HcalDepth1TowerSumEt  ->SetNameTitle("eff_hltEle115_EBdr03HcalDepth1TowerSumEt"  , "eff_hltEle115_EBdr03HcalDepth1TowerSumEt"  );
  TGraphAsymmErrors *eff_hltEle115_EBisoEmHadDepth1   =  new TGraphAsymmErrors(h_hltEle115_EBisoEmHadDepth1   );  eff_hltEle115_EBisoEmHadDepth1  ->SetNameTitle("eff_hltEle115_EBisoEmHadDepth1"  , "eff_hltEle115_EBisoEmHadDepth1"  );
                                                                                                                                                                     
  TGraphAsymmErrors *eff_hltPho200_eb_pt =  new TGraphAsymmErrors(h_hltPho200_eb_pt );  eff_hltPho200_eb_pt->SetNameTitle("eff_hltPho200_eb_pt", "eff_hltPho200_eb_pt");
  TGraphAsymmErrors *eff_hltPho200_ee_pt =  new TGraphAsymmErrors(h_hltPho200_ee_pt );  eff_hltPho200_ee_pt->SetNameTitle("eff_hltPho200_ee_pt", "eff_hltPho200_ee_pt");
  TGraphAsymmErrors *eff_hltPho200_etaSC =  new TGraphAsymmErrors(h_hltPho200_etaSC );  eff_hltPho200_etaSC->SetNameTitle("eff_hltPho200_etaSC", "eff_hltPho200_etaSC");
  TGraphAsymmErrors *eff_hltPho200_phiSC =  new TGraphAsymmErrors(h_hltPho200_phiSC );  eff_hltPho200_phiSC->SetNameTitle("eff_hltPho200_phiSC", "eff_hltPho200_phiSC");
  TGraphAsymmErrors *eff_hltPho200_sigma =  new TGraphAsymmErrors(h_hltPho200_sigma );  eff_hltPho200_sigma->SetNameTitle("eff_hltPho200_sigma", "eff_hltPho200_sigma");
  TGraphAsymmErrors *eff_hltPho200_hoe   =  new TGraphAsymmErrors(h_hltPho200_hoe   );  eff_hltPho200_hoe  ->SetNameTitle("eff_hltPho200_hoe"  , "eff_hltPho200_hoe"  );
  TGraphAsymmErrors *eff_hltPho200_deta  =  new TGraphAsymmErrors(h_hltPho200_deta  );  eff_hltPho200_deta ->SetNameTitle("eff_hltPho200_deta" , "eff_hltPho200_deta" );
  TGraphAsymmErrors *eff_hltPho200_dphi  =  new TGraphAsymmErrors(h_hltPho200_dphi  );  eff_hltPho200_dphi ->SetNameTitle("eff_hltPho200_dphi" , "eff_hltPho200_dphi" );
  TGraphAsymmErrors *eff_hltPho200_dxy   =  new TGraphAsymmErrors(h_hltPho200_dxy   );  eff_hltPho200_dxy  ->SetNameTitle("eff_hltPho200_dxy"  , "eff_hltPho200_dxy"  );
  TGraphAsymmErrors *eff_hltPho200_nPV   =  new TGraphAsymmErrors(h_hltPho200_nPV   );  eff_hltPho200_nPV  ->SetNameTitle("eff_hltPho200_nPV"  , "eff_hltPho200_nPV"  );
  TGraphAsymmErrors *eff_hltPho200_dr03EcalRecHitSumEt   =  new TGraphAsymmErrors(h_hltPho200_dr03EcalRecHitSumEt   );  eff_hltPho200_dr03EcalRecHitSumEt  ->SetNameTitle("eff_hltPho200_dr03EcalRecHitSumEt"  , "eff_hltPho200_dr03EcalRecHitSumEt"  );
  TGraphAsymmErrors *eff_hltPho200_dr03HcalTowerSumEt   =  new TGraphAsymmErrors(h_hltPho200_dr03HcalTowerSumEt   );  eff_hltPho200_dr03HcalTowerSumEt  ->SetNameTitle("eff_hltPho200_dr03HcalTowerSumEt"  , "eff_hltPho200_dr03HcalTowerSumEt"  );
  TGraphAsymmErrors *eff_hltPho200_dr03HcalDepth1TowerSumEt   =  new TGraphAsymmErrors(h_hltPho200_dr03HcalDepth1TowerSumEt   );  eff_hltPho200_dr03HcalDepth1TowerSumEt  ->SetNameTitle("eff_hltPho200_dr03HcalDepth1TowerSumEt"  , "eff_hltPho200_dr03HcalDepth1TowerSumEt"  );
  TGraphAsymmErrors *eff_hltPho200_isoEmHadDepth1   =  new TGraphAsymmErrors(h_hltPho200_isoEmHadDepth1   );  eff_hltPho200_isoEmHadDepth1  ->SetNameTitle("eff_hltPho200_isoEmHadDepth1"  , "eff_hltPho200_isoEmHadDepth1"  );
  TGraphAsymmErrors *eff_hltPho200_EBdr03EcalRecHitSumEt   =  new TGraphAsymmErrors(h_hltPho200_EBdr03EcalRecHitSumEt   );  eff_hltPho200_EBdr03EcalRecHitSumEt  ->SetNameTitle("eff_hltPho200_EBdr03EcalRecHitSumEt"  , "eff_hltPho200_EBdr03EcalRecHitSumEt"  );
  TGraphAsymmErrors *eff_hltPho200_EBdr03HcalTowerSumEt   =  new TGraphAsymmErrors(h_hltPho200_EBdr03HcalTowerSumEt   );  eff_hltPho200_EBdr03HcalTowerSumEt  ->SetNameTitle("eff_hltPho200_EBdr03HcalTowerSumEt"  , "eff_hltPho200_EBdr03HcalTowerSumEt"  );
  TGraphAsymmErrors *eff_hltPho200_EBdr03HcalDepth1TowerSumEt   =  new TGraphAsymmErrors(h_hltPho200_EBdr03HcalDepth1TowerSumEt   );  eff_hltPho200_EBdr03HcalDepth1TowerSumEt  ->SetNameTitle("eff_hltPho200_EBdr03HcalDepth1TowerSumEt"  , "eff_hltPho200_EBdr03HcalDepth1TowerSumEt"  );
  TGraphAsymmErrors *eff_hltPho200_EBisoEmHadDepth1   =  new TGraphAsymmErrors(h_hltPho200_EBisoEmHadDepth1   );  eff_hltPho200_EBisoEmHadDepth1  ->SetNameTitle("eff_hltPho200_EBisoEmHadDepth1"  , "eff_hltPho200_EBisoEmHadDepth1"  );
                                                                                                                                                                     
  TGraphAsymmErrors *eff_hltORALL_eb_pt  =  new TGraphAsymmErrors(h_hltORALL_eb_pt  );  eff_hltORALL_eb_pt ->SetNameTitle("eff_hltORALL_eb_pt" , "eff_hltORALL_eb_pt" );
  TGraphAsymmErrors *eff_hltORALL_ee_pt  =  new TGraphAsymmErrors(h_hltORALL_ee_pt  );  eff_hltORALL_ee_pt ->SetNameTitle("eff_hltORALL_ee_pt" , "eff_hltORALL_ee_pt" );
  TGraphAsymmErrors *eff_hltORALL_etaSC  =  new TGraphAsymmErrors(h_hltORALL_etaSC  );  eff_hltORALL_etaSC ->SetNameTitle("eff_hltORALL_etaSC" , "eff_hltORALL_etaSC" );
  TGraphAsymmErrors *eff_hltORALL_phiSC  =  new TGraphAsymmErrors(h_hltORALL_phiSC  );  eff_hltORALL_phiSC ->SetNameTitle("eff_hltORALL_phiSC" , "eff_hltORALL_phiSC" );
  TGraphAsymmErrors *eff_hltORALL_sigma  =  new TGraphAsymmErrors(h_hltORALL_sigma  );  eff_hltORALL_sigma ->SetNameTitle("eff_hltORALL_sigma" , "eff_hltORALL_sigma" );
  TGraphAsymmErrors *eff_hltORALL_hoe    =  new TGraphAsymmErrors(h_hltORALL_hoe    );  eff_hltORALL_hoe   ->SetNameTitle("eff_hltORALL_hoe"   , "eff_hltORALL_hoe"   );
  TGraphAsymmErrors *eff_hltORALL_deta   =  new TGraphAsymmErrors(h_hltORALL_deta   );  eff_hltORALL_deta  ->SetNameTitle("eff_hltORALL_deta"  , "eff_hltORALL_deta"  );
  TGraphAsymmErrors *eff_hltORALL_dphi   =  new TGraphAsymmErrors(h_hltORALL_dphi   );  eff_hltORALL_dphi  ->SetNameTitle("eff_hltORALL_dphi"  , "eff_hltORALL_dphi"  );
  TGraphAsymmErrors *eff_hltORALL_dxy    =  new TGraphAsymmErrors(h_hltORALL_dxy    );  eff_hltORALL_dxy   ->SetNameTitle("eff_hltORALL_dxy"   , "eff_hltORALL_dxy"   );
  TGraphAsymmErrors *eff_hltORALL_nPV    =  new TGraphAsymmErrors(h_hltORALL_nPV    );  eff_hltORALL_nPV   ->SetNameTitle("eff_hltORALL_nPV"   , "eff_hltORALL_nPV"   );
  TGraphAsymmErrors *eff_hltORALL_dr03EcalRecHitSumEt   =  new TGraphAsymmErrors(h_hltORALL_dr03EcalRecHitSumEt   );  eff_hltORALL_dr03EcalRecHitSumEt  ->SetNameTitle("eff_hltORALL_dr03EcalRecHitSumEt"  , "eff_hltORALL_dr03EcalRecHitSumEt"  );
  TGraphAsymmErrors *eff_hltORALL_dr03HcalTowerSumEt   =  new TGraphAsymmErrors(h_hltORALL_dr03HcalTowerSumEt   );  eff_hltORALL_dr03HcalTowerSumEt  ->SetNameTitle("eff_hltORALL_dr03HcalTowerSumEt"  , "eff_hltORALL_dr03HcalTowerSumEt"  );
  TGraphAsymmErrors *eff_hltORALL_dr03HcalDepth1TowerSumEt   =  new TGraphAsymmErrors(h_hltORALL_dr03HcalDepth1TowerSumEt   );  eff_hltORALL_dr03HcalDepth1TowerSumEt  ->SetNameTitle("eff_hltORALL_dr03HcalDepth1TowerSumEt"  , "eff_hltORALL_dr03HcalDepth1TowerSumEt"  );
  TGraphAsymmErrors *eff_hltORALL_isoEmHadDepth1   =  new TGraphAsymmErrors(h_hltORALL_isoEmHadDepth1   );  eff_hltORALL_isoEmHadDepth1  ->SetNameTitle("eff_hltORALL_isoEmHadDepth1"  , "eff_hltORALL_isoEmHadDepth1"  );
  TGraphAsymmErrors *eff_hltORALL_EBdr03EcalRecHitSumEt   =  new TGraphAsymmErrors(h_hltORALL_EBdr03EcalRecHitSumEt   );  eff_hltORALL_EBdr03EcalRecHitSumEt  ->SetNameTitle("eff_hltORALL_EBdr03EcalRecHitSumEt"  , "eff_hltORALL_EBdr03EcalRecHitSumEt"  );
  TGraphAsymmErrors *eff_hltORALL_EBdr03HcalTowerSumEt   =  new TGraphAsymmErrors(h_hltORALL_EBdr03HcalTowerSumEt   );  eff_hltORALL_EBdr03HcalTowerSumEt  ->SetNameTitle("eff_hltORALL_EBdr03HcalTowerSumEt"  , "eff_hltORALL_EBdr03HcalTowerSumEt"  );
  TGraphAsymmErrors *eff_hltORALL_EBdr03HcalDepth1TowerSumEt   =  new TGraphAsymmErrors(h_hltORALL_EBdr03HcalDepth1TowerSumEt   );  eff_hltORALL_EBdr03HcalDepth1TowerSumEt  ->SetNameTitle("eff_hltORALL_EBdr03HcalDepth1TowerSumEt"  , "eff_hltORALL_EBdr03HcalDepth1TowerSumEt"  );
  TGraphAsymmErrors *eff_hltORALL_EBisoEmHadDepth1   =  new TGraphAsymmErrors(h_hltORALL_EBisoEmHadDepth1   );  eff_hltORALL_EBisoEmHadDepth1  ->SetNameTitle("eff_hltORALL_EBisoEmHadDepth1"  , "eff_hltORALL_EBisoEmHadDepth1"  );

  //-- event counting check for N-1 eff
  int nMuHLT        = 0; int nHEEP         = 0;
  int nHEEP130      = 0; int nHEEP240      = 0;
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
  h_heep_sigma   ->Sumw2();
  h_heep_hoe     ->Sumw2();
  h_heep_deta    ->Sumw2();
  h_heep_dphi    ->Sumw2();
  h_heep_dxy     ->Sumw2();
  h_heep_nPV     ->Sumw2();
  h_heep_dr03EcalRecHitSumEt     ->Sumw2(); 
  h_heep_dr03HcalTowerSumEt      ->Sumw2(); 
  h_heep_dr03HcalDepth1TowerSumEt->Sumw2(); 
  h_heep_isoEmHadDepth1          ->Sumw2(); 
  h_heep_EBdr03EcalRecHitSumEt     ->Sumw2(); 
  h_heep_EBdr03HcalTowerSumEt      ->Sumw2(); 
  h_heep_EBdr03HcalDepth1TowerSumEt->Sumw2(); 
  h_heep_EBisoEmHadDepth1          ->Sumw2(); 
  h_heep130_etaSC->Sumw2();
  h_heep130_phiSC->Sumw2();
  h_heep130_sigma->Sumw2();
  h_heep130_hoe  ->Sumw2();
  h_heep130_deta ->Sumw2();
  h_heep130_dphi ->Sumw2();
  h_heep130_dxy  ->Sumw2();
  h_heep130_nPV  ->Sumw2();
  h_heep130_dr03EcalRecHitSumEt     ->Sumw2(); 
  h_heep130_dr03HcalTowerSumEt      ->Sumw2(); 
  h_heep130_dr03HcalDepth1TowerSumEt->Sumw2(); 
  h_heep130_isoEmHadDepth1          ->Sumw2(); 
  h_heep130_EBdr03EcalRecHitSumEt     ->Sumw2(); 
  h_heep130_EBdr03HcalTowerSumEt      ->Sumw2(); 
  h_heep130_EBdr03HcalDepth1TowerSumEt->Sumw2(); 
  h_heep130_EBisoEmHadDepth1          ->Sumw2(); 
  h_heep240_etaSC->Sumw2();
  h_heep240_phiSC->Sumw2();
  h_heep240_sigma->Sumw2();
  h_heep240_hoe  ->Sumw2();
  h_heep240_deta ->Sumw2();
  h_heep240_dphi ->Sumw2();
  h_heep240_dxy  ->Sumw2();
  h_heep240_nPV  ->Sumw2();
  h_heep240_dr03EcalRecHitSumEt     ->Sumw2(); 
  h_heep240_dr03HcalTowerSumEt      ->Sumw2(); 
  h_heep240_dr03HcalDepth1TowerSumEt->Sumw2(); 
  h_heep240_isoEmHadDepth1          ->Sumw2(); 
  h_heep240_EBdr03EcalRecHitSumEt     ->Sumw2(); 
  h_heep240_EBdr03HcalTowerSumEt      ->Sumw2(); 
  h_heep240_EBdr03HcalDepth1TowerSumEt->Sumw2(); 
  h_heep240_EBisoEmHadDepth1          ->Sumw2(); 

  //--numerator histograms
 // h_hltEle35_eb_pt->Sumw2();
 // h_hltEle35_ee_pt->Sumw2();
 // h_hltEle35_etaSC->Sumw2();
 // h_hltEle35_phiSC->Sumw2();
 // h_hltEle35_sigma->Sumw2();
 // h_hltEle35_hoe  ->Sumw2();
 // h_hltEle35_deta ->Sumw2();
 // h_hltEle35_dphi ->Sumw2();
 // h_hltEle35_dxy  ->Sumw2();
 // h_hltEle35_nPV  ->Sumw2();

  h_hltEle115_eb_pt->Sumw2();
  h_hltEle115_ee_pt->Sumw2();
  h_hltEle115_etaSC->Sumw2();
  h_hltEle115_phiSC->Sumw2();
  h_hltEle115_sigma->Sumw2();
  h_hltEle115_hoe  ->Sumw2();
  h_hltEle115_deta ->Sumw2();
  h_hltEle115_dphi ->Sumw2();
  h_hltEle115_dxy  ->Sumw2();
  h_hltEle115_nPV  ->Sumw2();
  h_hltEle115_dr03EcalRecHitSumEt     ->Sumw2(); 
  h_hltEle115_dr03HcalTowerSumEt      ->Sumw2(); 
  h_hltEle115_dr03HcalDepth1TowerSumEt->Sumw2(); 
  h_hltEle115_isoEmHadDepth1          ->Sumw2(); 
  h_hltEle115_EBdr03EcalRecHitSumEt     ->Sumw2(); 
  h_hltEle115_EBdr03HcalTowerSumEt      ->Sumw2(); 
  h_hltEle115_EBdr03HcalDepth1TowerSumEt->Sumw2(); 
  h_hltEle115_EBisoEmHadDepth1          ->Sumw2(); 

  h_hltPho200_eb_pt->Sumw2();
  h_hltPho200_ee_pt->Sumw2();
  h_hltPho200_etaSC->Sumw2();
  h_hltPho200_phiSC->Sumw2();
  h_hltPho200_sigma->Sumw2();
  h_hltPho200_hoe  ->Sumw2();
  h_hltPho200_deta ->Sumw2();
  h_hltPho200_dphi ->Sumw2();
  h_hltPho200_dxy  ->Sumw2();
  h_hltPho200_nPV  ->Sumw2();
  h_hltPho200_dr03EcalRecHitSumEt     ->Sumw2(); 
  h_hltPho200_dr03HcalTowerSumEt      ->Sumw2(); 
  h_hltPho200_dr03HcalDepth1TowerSumEt->Sumw2(); 
  h_hltPho200_isoEmHadDepth1          ->Sumw2(); 
  h_hltPho200_EBdr03EcalRecHitSumEt     ->Sumw2(); 
  h_hltPho200_EBdr03HcalTowerSumEt      ->Sumw2(); 
  h_hltPho200_EBdr03HcalDepth1TowerSumEt->Sumw2(); 
  h_hltPho200_EBisoEmHadDepth1          ->Sumw2(); 

  h_hltORALL_eb_pt ->Sumw2();
  h_hltORALL_ee_pt ->Sumw2();
  h_hltORALL_etaSC ->Sumw2();
  h_hltORALL_phiSC ->Sumw2();
  h_hltORALL_sigma ->Sumw2();
  h_hltORALL_hoe   ->Sumw2();
  h_hltORALL_deta  ->Sumw2();
  h_hltORALL_dphi  ->Sumw2();
  h_hltORALL_dxy   ->Sumw2();
  h_hltORALL_nPV   ->Sumw2();
  h_hltORALL_dr03EcalRecHitSumEt     ->Sumw2(); 
  h_hltORALL_dr03HcalTowerSumEt      ->Sumw2(); 
  h_hltORALL_dr03HcalDepth1TowerSumEt->Sumw2(); 
  h_hltORALL_isoEmHadDepth1          ->Sumw2(); 
  h_hltORALL_EBdr03EcalRecHitSumEt     ->Sumw2(); 
  h_hltORALL_EBdr03HcalTowerSumEt      ->Sumw2(); 
  h_hltORALL_EBdr03HcalDepth1TowerSumEt->Sumw2(); 
  h_hltORALL_EBisoEmHadDepth1          ->Sumw2(); 

  //-- start Loop over *Events*
  for(int ievent = 0; ievent < TotalN; ievent++){
      if(TotalN == 0 ) continue;
      if((ievent%per99) == 0) cout << "Running " << (per100++ * 10)<< " % " << ievent << " / " << TotalN << endl;
 
      Long64_t tentry   = tree->LoadTree(ievent);
      b_run                   ->GetEntry(tentry);

      //if(run <= Min_run) continue;
      //if(run > Max_run) continue;
      b_nEle                  ->GetEntry(tentry);
      b_nPV                   ->GetEntry(tentry);
      b_pt                    ->GetEntry(tentry);
      b_et                    ->GetEntry(tentry);
      b_etaSC                 ->GetEntry(tentry);
      b_phiSC                 ->GetEntry(tentry);
      b_hOverE                ->GetEntry(tentry);
      b_dr03EcalRecHitSumEt     ->GetEntry(tentry); 
      b_dr03HcalTowerSumEt      ->GetEntry(tentry); 
      b_dr03HcalDepth1TowerSumEt->GetEntry(tentry); 
      b_isoEmHadDepth1          ->GetEntry(tentry);  
      b_full5x5_sigmaIetaIeta ->GetEntry(tentry);
      b_dEtaSeed              ->GetEntry(tentry);
      b_dPhiIn                ->GetEntry(tentry);
      b_dxy                   ->GetEntry(tentry);
      b_passHEEPId            ->GetEntry(tentry);      
      b_istrgMatchTrue        ->GetEntry(tentry); 
      b_HLTMuX                ->GetEntry(tentry);  
      b_isHLTEle35Pass        ->GetEntry(tentry); 
      b_isHLTEle115Pass       ->GetEntry(tentry); 
      b_isHLTPho200Pass       ->GetEntry(tentry); 
 
      bool isHLTMu  = (HLTMuX > 0);
      if(!isHLTMu) continue; //-- HLT_Mu pass cut--#1
      if(nEle == 0) continue; //-- HLT_Mu pass cut--#1
      nMuHLT++;
      h_total_nPV->Fill(nPV); // hist fill
      //-- start Loop over *Electrons* in one event
      for(int iele = 0; iele < nEle; iele++){
           bool isBarrel    = (fabs(etaSC->at(iele)) < 1.4442);
           bool isEndcap    = (fabs(etaSC->at(iele)) > 1.566);
           bool isHEEP      = passHEEPId->at(iele) ;
           bool isPt130     = (pt->at(iele) > 130);
           bool isPt240     = (pt->at(iele) > 240);
           bool isTrgMatch  = istrgMatchTrue ; 
           bool isHLTEle35  = isHLTEle35Pass ; 
           bool isHLTEle115 = isHLTEle115Pass ; 
           bool isHLTPho200 = isHLTPho200Pass ; 
           bool isHLTORALL  = (isHLTEle115 || isHLTPho200)  ; 
 
           if(isBarrel) nEB_Base++; 
           if(isEndcap) nEE_Base++; 
 
           if(!isHEEP) continue;  //-- heep v70 cut --#2
           if(et->at(iele)<50) continue;  //-- heep v70 cut --#2
           nHEEP++;
           h_heep_etaSC ->Fill(etaSC->at(iele)); 
           h_heep_phiSC ->Fill(phiSC->at(iele));
           h_heep_phiSC ->Fill(phiSC->at(iele));
           h_heep_hoe   ->Fill(hOverE->at(iele));
           h_heep_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
           h_heep_deta  ->Fill(dEtaSeed->at(iele));
           h_heep_dphi  ->Fill(dPhiIn->at(iele));
           h_heep_dxy   ->Fill(dxy->at(iele));
           h_heep_nPV   ->Fill(nPV);
           h_heep_dr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt->at(iele)); 
           h_heep_dr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt->at(iele)); 
           h_heep_dr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
           h_heep_isoEmHadDepth1          ->Fill(isoEmHadDepth1->at(iele)); 

           if(isBarrel){ 
                nEB_HEEP++; 
                h_heep_eb_pt->Fill(et->at(iele));
                h_heep_EBdr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                h_heep_EBdr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                h_heep_EBdr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                h_heep_EBisoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                
               // if(isTrgMatch && isHLTEle35)   h_hltEle35_eb_pt->Fill(et->at(iele)); //-- hltele35 cut #4
                if(isTrgMatch && isHLTEle115)  h_hltEle115_eb_pt->Fill(et->at(iele)); //-- hltele115 cut #4
                if(isTrgMatch && isHLTPho200)  h_hltPho200_eb_pt->Fill(et->at(iele)); //-- hltpho200 cut #6
                if(isTrgMatch && isHLTORALL)   h_hltORALL_eb_pt->Fill(et->at(iele)); //-- hlt OR all cut #7
           }
           if(isEndcap){
                nEE_HEEP++; 
                h_heep_ee_pt->Fill(et->at(iele)); 
               // if(isTrgMatch && isHLTEle35)   h_hltEle35_ee_pt->Fill(et->at(iele)); //-- hltele35 cut #4
                if(isTrgMatch && isHLTEle115)  h_hltEle115_ee_pt->Fill(et->at(iele)); //-- hltele115 cut #4
                if(isTrgMatch && isHLTPho200)  h_hltPho200_ee_pt->Fill(et->at(iele)); //-- hltpho200 cut #6
                if(isTrgMatch && isHLTORALL)   h_hltORALL_ee_pt->Fill(et->at(iele)); //-- hlt OR all cut #7
           }

           if(isBarrel && isTrgMatch) nEB_TrgMatch++; 
           if(isEndcap && isTrgMatch) nEE_TrgMatch++; 

          // if(isTrgMatch && isHLTEle35){ //-- hltele35 cut #4
          //      h_hltEle35_etaSC ->Fill(etaSC->at(iele)); 
          //      h_hltEle35_phiSC ->Fill(phiSC->at(iele));
          //      h_hltEle35_phiSC ->Fill(phiSC->at(iele));
          //      h_hltEle35_hoe   ->Fill(hOverE->at(iele));
          //      h_hltEle35_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
          //      h_hltEle35_deta  ->Fill(dEtaSeed->at(iele));
          //      h_hltEle35_dphi  ->Fill(dPhiIn->at(iele));
          //      h_hltEle35_dxy   ->Fill(dxy->at(iele));
          //      h_hltEle35_nPV   ->Fill(nPV);
          // }
 
           if(!isPt130) continue; //-- offline e pt cut > 130 gev
           nHEEP130++;
           h_heep130_etaSC ->Fill(etaSC->at(iele)); 
           h_heep130_phiSC ->Fill(phiSC->at(iele));
           h_heep130_phiSC ->Fill(phiSC->at(iele));
           h_heep130_hoe   ->Fill(hOverE->at(iele));
           h_heep130_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
           h_heep130_deta  ->Fill(dEtaSeed->at(iele));
           h_heep130_dphi  ->Fill(dPhiIn->at(iele));
           h_heep130_dxy   ->Fill(dxy->at(iele));
           h_heep130_nPV   ->Fill(nPV);
           h_heep130_dr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
           h_heep130_dr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
           h_heep130_dr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
           h_heep130_isoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
           if(isBarrel){ 
               h_heep130_EBdr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
               h_heep130_EBdr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
               h_heep130_EBdr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
               h_heep130_EBisoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
           }
           if(isPt240){ //-- offline e pt cut > 240 gev
                nHEEP240++;
                h_heep240_etaSC ->Fill(etaSC->at(iele)); 
                h_heep240_phiSC ->Fill(phiSC->at(iele));
                h_heep240_phiSC ->Fill(phiSC->at(iele));
                h_heep240_hoe   ->Fill(hOverE->at(iele));
                h_heep240_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
                h_heep240_deta  ->Fill(dEtaSeed->at(iele));
                h_heep240_dphi  ->Fill(dPhiIn->at(iele));
                h_heep240_dxy   ->Fill(dxy->at(iele));
                h_heep240_nPV   ->Fill(nPV);
                h_heep240_dr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                h_heep240_dr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                h_heep240_dr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                h_heep240_isoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                if(isBarrel){ 
                    h_heep240_EBdr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                    h_heep240_EBdr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                    h_heep240_EBdr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                    h_heep240_EBisoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                }

                if(isTrgMatch && isHLTPho200){ //-- hltpho200 cut #6
                     h_hltPho200_etaSC ->Fill(etaSC->at(iele)); 
                     h_hltPho200_phiSC ->Fill(phiSC->at(iele));
                     h_hltPho200_phiSC ->Fill(phiSC->at(iele));
                     h_hltPho200_hoe   ->Fill(hOverE->at(iele));
                     h_hltPho200_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
                     h_hltPho200_deta  ->Fill(dEtaSeed->at(iele));
                     h_hltPho200_dphi  ->Fill(dPhiIn->at(iele));
                     h_hltPho200_dxy   ->Fill(dxy->at(iele));
                     h_hltPho200_nPV   ->Fill(nPV);
                     h_hltPho200_dr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                     h_hltPho200_dr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                     h_hltPho200_dr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                     h_hltPho200_isoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                     if(isBarrel){ 
                         h_hltPho200_EBdr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                         h_hltPho200_EBdr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                         h_hltPho200_EBdr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                         h_hltPho200_EBisoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                     }
                }
           }

           if(!isTrgMatch) continue; //-- trg obj - reco matching dPt, dR
           if(isHLTEle115){ //-- hltele115 cut #4
                h_hltEle115_etaSC ->Fill(etaSC->at(iele)); 
                h_hltEle115_phiSC ->Fill(phiSC->at(iele));
                h_hltEle115_phiSC ->Fill(phiSC->at(iele));
                h_hltEle115_hoe   ->Fill(hOverE->at(iele));
                h_hltEle115_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
                h_hltEle115_deta  ->Fill(dEtaSeed->at(iele));
                h_hltEle115_dphi  ->Fill(dPhiIn->at(iele));
                h_hltEle115_dxy   ->Fill(dxy->at(iele));
                h_hltEle115_nPV   ->Fill(nPV);
                h_hltEle115_dr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                h_hltEle115_dr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                h_hltEle115_dr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                h_hltEle115_isoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                if(isBarrel){ 
                    h_hltEle115_EBdr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                    h_hltEle115_EBdr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                    h_hltEle115_EBdr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                    h_hltEle115_EBisoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                }
           }
           if(isHLTORALL){ //-- hlt OR all cut #7
                h_hltORALL_etaSC ->Fill(etaSC->at(iele)); 
                h_hltORALL_phiSC ->Fill(phiSC->at(iele));
                h_hltORALL_phiSC ->Fill(phiSC->at(iele));
                h_hltORALL_hoe   ->Fill(hOverE->at(iele));
                h_hltORALL_sigma ->Fill(full5x5_sigmaIetaIeta->at(iele));
                h_hltORALL_deta  ->Fill(dEtaSeed->at(iele));
                h_hltORALL_dphi  ->Fill(dPhiIn->at(iele));
                h_hltORALL_dxy   ->Fill(dxy->at(iele));
                h_hltORALL_nPV   ->Fill(nPV);
                h_hltORALL_dr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                h_hltORALL_dr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                h_hltORALL_dr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                h_hltORALL_isoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                if(isBarrel){ 
                    h_hltORALL_EBdr03EcalRecHitSumEt     ->Fill(dr03EcalRecHitSumEt     ->at(iele)); 
                    h_hltORALL_EBdr03HcalTowerSumEt      ->Fill(dr03HcalTowerSumEt      ->at(iele)); 
                    h_hltORALL_EBdr03HcalDepth1TowerSumEt->Fill(dr03HcalDepth1TowerSumEt->at(iele)); 
                    h_hltORALL_EBisoEmHadDepth1          ->Fill(isoEmHadDepth1          ->at(iele)); 
                }
           }
      }//--electron Loop over
  }//-- event Loop over

//  //-- define efficiency plot
//   eff_hltEle35_eb_pt ->Divide( h_hltEle35_eb_pt , h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_ee_pt ->Divide( h_hltEle35_ee_pt , h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_etaSC ->Divide( h_hltEle35_etaSC , h_heep_etaSC    , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_phiSC ->Divide( h_hltEle35_phiSC , h_heep_phiSC    , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_sigma ->Divide( h_hltEle35_sigma , h_heep_sigma    , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_hoe   ->Divide( h_hltEle35_hoe   , h_heep_hoe      , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_deta  ->Divide( h_hltEle35_deta  , h_heep_deta     , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_dphi  ->Divide( h_hltEle35_dphi  , h_heep_dphi     , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_dxy   ->Divide( h_hltEle35_dxy   , h_heep_dxy      , "cl=0.683 b(1,1) mode");  
//   eff_hltEle35_nPV   ->Divide( h_hltEle35_nPV   , h_heep_nPV      , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_eb_pt->Divide( h_hltEle115_eb_pt, h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_ee_pt->Divide( h_hltEle115_ee_pt, h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_etaSC->Divide( h_hltEle115_etaSC, h_heep130_etaSC , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_phiSC->Divide( h_hltEle115_phiSC, h_heep130_phiSC , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_sigma->Divide( h_hltEle115_sigma, h_heep130_sigma , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_hoe  ->Divide( h_hltEle115_hoe  , h_heep130_hoe   , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_deta ->Divide( h_hltEle115_deta , h_heep130_deta  , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_dphi ->Divide( h_hltEle115_dphi , h_heep130_dphi  , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_dxy  ->Divide( h_hltEle115_dxy  , h_heep130_dxy   , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_nPV  ->Divide( h_hltEle115_nPV  , h_heep130_nPV   , "cl=0.683 b(1,1) mode");  
   eff_hltEle115_dr03EcalRecHitSumEt       ->Divide(h_hltEle115_dr03EcalRecHitSumEt       , h_heep130_dr03EcalRecHitSumEt         ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_dr03HcalTowerSumEt        ->Divide(h_hltEle115_dr03HcalTowerSumEt        , h_heep130_dr03HcalTowerSumEt          ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_dr03HcalDepth1TowerSumEt  ->Divide(h_hltEle115_dr03HcalDepth1TowerSumEt  , h_heep130_dr03HcalDepth1TowerSumEt    ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_isoEmHadDepth1            ->Divide(h_hltEle115_isoEmHadDepth1            , h_heep130_isoEmHadDepth1              ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_EBdr03EcalRecHitSumEt     ->Divide(h_hltEle115_EBdr03EcalRecHitSumEt     , h_heep130_EBdr03EcalRecHitSumEt       ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_EBdr03HcalTowerSumEt      ->Divide(h_hltEle115_EBdr03HcalTowerSumEt      , h_heep130_EBdr03HcalTowerSumEt        ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_EBdr03HcalDepth1TowerSumEt->Divide(h_hltEle115_EBdr03HcalDepth1TowerSumEt, h_heep130_EBdr03HcalDepth1TowerSumEt  ,  "cl=0.683 b(1,1) mode"); 
   eff_hltEle115_EBisoEmHadDepth1          ->Divide(h_hltEle115_EBisoEmHadDepth1          , h_heep130_EBisoEmHadDepth1            ,  "cl=0.683 b(1,1) mode"); 

   eff_hltPho200_eb_pt->Divide( h_hltPho200_eb_pt, h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_ee_pt->Divide( h_hltPho200_ee_pt, h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_etaSC->Divide( h_hltPho200_etaSC, h_heep240_etaSC , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_phiSC->Divide( h_hltPho200_phiSC, h_heep240_phiSC , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_sigma->Divide( h_hltPho200_sigma, h_heep240_sigma , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_hoe  ->Divide( h_hltPho200_hoe  , h_heep240_hoe   , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_deta ->Divide( h_hltPho200_deta , h_heep240_deta  , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_dphi ->Divide( h_hltPho200_dphi , h_heep240_dphi  , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_dxy  ->Divide( h_hltPho200_dxy  , h_heep240_dxy   , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_nPV  ->Divide( h_hltPho200_nPV  , h_heep240_nPV   , "cl=0.683 b(1,1) mode");  
   eff_hltPho200_dr03EcalRecHitSumEt       ->Divide(h_hltPho200_dr03EcalRecHitSumEt       , h_heep240_dr03EcalRecHitSumEt         ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_dr03HcalTowerSumEt        ->Divide(h_hltPho200_dr03HcalTowerSumEt        , h_heep240_dr03HcalTowerSumEt          ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_dr03HcalDepth1TowerSumEt  ->Divide(h_hltPho200_dr03HcalDepth1TowerSumEt  , h_heep240_dr03HcalDepth1TowerSumEt    ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_isoEmHadDepth1            ->Divide(h_hltPho200_isoEmHadDepth1            , h_heep240_isoEmHadDepth1              ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_EBdr03EcalRecHitSumEt     ->Divide(h_hltPho200_EBdr03EcalRecHitSumEt     , h_heep240_EBdr03EcalRecHitSumEt       ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_EBdr03HcalTowerSumEt      ->Divide(h_hltPho200_EBdr03HcalTowerSumEt      , h_heep240_EBdr03HcalTowerSumEt        ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_EBdr03HcalDepth1TowerSumEt->Divide(h_hltPho200_EBdr03HcalDepth1TowerSumEt, h_heep240_EBdr03HcalDepth1TowerSumEt  ,  "cl=0.683 b(1,1) mode"); 
   eff_hltPho200_EBisoEmHadDepth1          ->Divide(h_hltPho200_EBisoEmHadDepth1          , h_heep240_EBisoEmHadDepth1            ,  "cl=0.683 b(1,1) mode"); 

   eff_hltORALL_eb_pt ->Divide( h_hltORALL_eb_pt , h_heep_eb_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_ee_pt ->Divide( h_hltORALL_ee_pt , h_heep_ee_pt    , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_etaSC ->Divide( h_hltORALL_etaSC , h_heep130_etaSC , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_phiSC ->Divide( h_hltORALL_phiSC , h_heep130_phiSC , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_sigma ->Divide( h_hltORALL_sigma , h_heep130_sigma , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_hoe   ->Divide( h_hltORALL_hoe   , h_heep130_hoe   , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_deta  ->Divide( h_hltORALL_deta  , h_heep130_deta  , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_dphi  ->Divide( h_hltORALL_dphi  , h_heep130_dphi  , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_dxy   ->Divide( h_hltORALL_dxy   , h_heep130_dxy   , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_nPV   ->Divide( h_hltORALL_nPV   , h_heep130_nPV   , "cl=0.683 b(1,1) mode");  
   eff_hltORALL_dr03EcalRecHitSumEt       ->Divide(h_hltORALL_dr03EcalRecHitSumEt       , h_heep130_dr03EcalRecHitSumEt         ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_dr03HcalTowerSumEt        ->Divide(h_hltORALL_dr03HcalTowerSumEt        , h_heep130_dr03HcalTowerSumEt          ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_dr03HcalDepth1TowerSumEt  ->Divide(h_hltORALL_dr03HcalDepth1TowerSumEt  , h_heep130_dr03HcalDepth1TowerSumEt    ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_isoEmHadDepth1            ->Divide(h_hltORALL_isoEmHadDepth1            , h_heep130_isoEmHadDepth1              ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_EBdr03EcalRecHitSumEt     ->Divide(h_hltORALL_EBdr03EcalRecHitSumEt     , h_heep130_EBdr03EcalRecHitSumEt       ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_EBdr03HcalTowerSumEt      ->Divide(h_hltORALL_EBdr03HcalTowerSumEt      , h_heep130_EBdr03HcalTowerSumEt        ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_EBdr03HcalDepth1TowerSumEt->Divide(h_hltORALL_EBdr03HcalDepth1TowerSumEt, h_heep130_EBdr03HcalDepth1TowerSumEt  ,  "cl=0.683 b(1,1) mode"); 
   eff_hltORALL_EBisoEmHadDepth1          ->Divide(h_hltORALL_EBisoEmHadDepth1          , h_heep130_EBisoEmHadDepth1            ,  "cl=0.683 b(1,1) mode"); 

  h_total_nPV    ->Write();
  h_heep_eb_pt   ->Write(); 
  h_heep_ee_pt   ->Write();
  h_heep_etaSC   ->Write();
  h_heep_phiSC   ->Write();
  h_heep_sigma   ->Write();
  h_heep_hoe     ->Write();
  h_heep_deta    ->Write();
  h_heep_dphi    ->Write();
  h_heep_dxy     ->Write();
  h_heep_nPV     ->Write();
  h_heep_dr03EcalRecHitSumEt     ->Write(); 
  h_heep_dr03HcalTowerSumEt      ->Write(); 
  h_heep_dr03HcalDepth1TowerSumEt->Write(); 
  h_heep_isoEmHadDepth1          ->Write(); 
  h_heep_EBdr03EcalRecHitSumEt     ->Write(); 
  h_heep_EBdr03HcalTowerSumEt      ->Write(); 
  h_heep_EBdr03HcalDepth1TowerSumEt->Write(); 
  h_heep_EBisoEmHadDepth1          ->Write(); 
  h_heep130_etaSC->Write();
  h_heep130_phiSC->Write();
  h_heep130_sigma->Write();
  h_heep130_hoe  ->Write();
  h_heep130_deta ->Write();
  h_heep130_dphi ->Write();
  h_heep130_dxy  ->Write();
  h_heep130_nPV  ->Write();
  h_heep130_dr03EcalRecHitSumEt     ->Write(); 
  h_heep130_dr03HcalTowerSumEt      ->Write(); 
  h_heep130_dr03HcalDepth1TowerSumEt->Write(); 
  h_heep130_isoEmHadDepth1          ->Write(); 
  h_heep130_EBdr03EcalRecHitSumEt     ->Write(); 
  h_heep130_EBdr03HcalTowerSumEt      ->Write(); 
  h_heep130_EBdr03HcalDepth1TowerSumEt->Write(); 
  h_heep130_EBisoEmHadDepth1          ->Write(); 
  h_heep240_etaSC->Write();
  h_heep240_phiSC->Write();
  h_heep240_sigma->Write();
  h_heep240_hoe  ->Write();
  h_heep240_deta ->Write();
  h_heep240_dphi ->Write();
  h_heep240_dxy  ->Write();
  h_heep240_nPV  ->Write();
  h_heep240_dr03EcalRecHitSumEt     ->Write(); 
  h_heep240_dr03HcalTowerSumEt      ->Write(); 
  h_heep240_dr03HcalDepth1TowerSumEt->Write(); 
  h_heep240_isoEmHadDepth1          ->Write(); 
  h_heep240_EBdr03EcalRecHitSumEt     ->Write(); 
  h_heep240_EBdr03HcalTowerSumEt      ->Write(); 
  h_heep240_EBdr03HcalDepth1TowerSumEt->Write(); 
  h_heep240_EBisoEmHadDepth1          ->Write(); 

  //--numerator histograms
  //h_hltEle35_eb_pt->Write();
  //h_hltEle35_ee_pt->Write();
  //h_hltEle35_etaSC->Write();
  //h_hltEle35_phiSC->Write();
  //h_hltEle35_sigma->Write();
  //h_hltEle35_hoe  ->Write();
  //h_hltEle35_deta ->Write();
  //h_hltEle35_dphi ->Write();
  //h_hltEle35_dxy  ->Write();
  //h_hltEle35_nPV  ->Write();

  h_hltEle115_eb_pt->Write();
  h_hltEle115_ee_pt->Write();
  h_hltEle115_etaSC->Write();
  h_hltEle115_phiSC->Write();
  h_hltEle115_sigma->Write();
  h_hltEle115_hoe  ->Write();
  h_hltEle115_deta ->Write();
  h_hltEle115_dphi ->Write();
  h_hltEle115_dxy  ->Write();
  h_hltEle115_nPV  ->Write();
  h_hltEle115_dr03EcalRecHitSumEt     ->Write(); 
  h_hltEle115_dr03HcalTowerSumEt      ->Write(); 
  h_hltEle115_dr03HcalDepth1TowerSumEt->Write(); 
  h_hltEle115_isoEmHadDepth1          ->Write(); 
  h_hltEle115_EBdr03EcalRecHitSumEt     ->Write(); 
  h_hltEle115_EBdr03HcalTowerSumEt      ->Write(); 
  h_hltEle115_EBdr03HcalDepth1TowerSumEt->Write(); 
  h_hltEle115_EBisoEmHadDepth1          ->Write(); 

  h_hltPho200_eb_pt->Write();
  h_hltPho200_ee_pt->Write();
  h_hltPho200_etaSC->Write();
  h_hltPho200_phiSC->Write();
  h_hltPho200_sigma->Write();
  h_hltPho200_hoe  ->Write();
  h_hltPho200_deta ->Write();
  h_hltPho200_dphi ->Write();
  h_hltPho200_dxy  ->Write();
  h_hltPho200_nPV  ->Write();
  h_hltPho200_dr03EcalRecHitSumEt     ->Write(); 
  h_hltPho200_dr03HcalTowerSumEt      ->Write(); 
  h_hltPho200_dr03HcalDepth1TowerSumEt->Write(); 
  h_hltPho200_isoEmHadDepth1          ->Write(); 
  h_hltPho200_EBdr03EcalRecHitSumEt     ->Write(); 
  h_hltPho200_EBdr03HcalTowerSumEt      ->Write(); 
  h_hltPho200_EBdr03HcalDepth1TowerSumEt->Write(); 
  h_hltPho200_EBisoEmHadDepth1          ->Write(); 

  h_hltORALL_eb_pt ->Write();
  h_hltORALL_ee_pt ->Write();
  h_hltORALL_etaSC ->Write();
  h_hltORALL_phiSC ->Write();
  h_hltORALL_sigma ->Write();
  h_hltORALL_hoe   ->Write();
  h_hltORALL_deta  ->Write();
  h_hltORALL_dphi  ->Write();
  h_hltORALL_dxy   ->Write();
  h_hltORALL_nPV   ->Write();
  h_hltORALL_dr03EcalRecHitSumEt     ->Write(); 
  h_hltORALL_dr03HcalTowerSumEt      ->Write(); 
  h_hltORALL_dr03HcalDepth1TowerSumEt->Write(); 
  h_hltORALL_isoEmHadDepth1          ->Write(); 
  h_hltORALL_EBdr03EcalRecHitSumEt     ->Write(); 
  h_hltORALL_EBdr03HcalTowerSumEt      ->Write(); 
  h_hltORALL_EBdr03HcalDepth1TowerSumEt->Write(); 
  h_hltORALL_EBisoEmHadDepth1          ->Write(); 

 // eff_hltEle35_eb_pt->Write("",TObject::kOverwrite);   eff_hltEle115_eb_pt->Write("",TObject::kOverwrite);
 // eff_hltEle35_ee_pt->Write("",TObject::kOverwrite);   eff_hltEle115_ee_pt->Write("",TObject::kOverwrite);
 // eff_hltEle35_etaSC->Write("",TObject::kOverwrite);   eff_hltEle115_etaSC->Write("",TObject::kOverwrite);
 // eff_hltEle35_phiSC->Write("",TObject::kOverwrite);   eff_hltEle115_phiSC->Write("",TObject::kOverwrite);
 // eff_hltEle35_sigma->Write("",TObject::kOverwrite);   eff_hltEle115_sigma->Write("",TObject::kOverwrite);
 // eff_hltEle35_hoe  ->Write("",TObject::kOverwrite);   eff_hltEle115_hoe  ->Write("",TObject::kOverwrite);
 // eff_hltEle35_deta ->Write("",TObject::kOverwrite);   eff_hltEle115_deta ->Write("",TObject::kOverwrite);
 // eff_hltEle35_dphi ->Write("",TObject::kOverwrite);   eff_hltEle115_dphi ->Write("",TObject::kOverwrite);
 // eff_hltEle35_dxy  ->Write("",TObject::kOverwrite);   eff_hltEle115_dxy  ->Write("",TObject::kOverwrite);
 // eff_hltEle35_nPV  ->Write("",TObject::kOverwrite);   eff_hltEle115_nPV  ->Write("",TObject::kOverwrite);
  eff_hltEle115_eb_pt->Write("",TObject::kOverwrite); 
  eff_hltEle115_ee_pt->Write("",TObject::kOverwrite); 
  eff_hltEle115_etaSC->Write("",TObject::kOverwrite); 
  eff_hltEle115_phiSC->Write("",TObject::kOverwrite); 
  eff_hltEle115_sigma->Write("",TObject::kOverwrite); 
  eff_hltEle115_hoe  ->Write("",TObject::kOverwrite); 
  eff_hltEle115_deta ->Write("",TObject::kOverwrite); 
  eff_hltEle115_dphi ->Write("",TObject::kOverwrite); 
  eff_hltEle115_dxy  ->Write("",TObject::kOverwrite); 
  eff_hltEle115_nPV  ->Write("",TObject::kOverwrite); 
  eff_hltEle115_dr03EcalRecHitSumEt       ->Write("",TObject::kOverwrite);   
  eff_hltEle115_dr03HcalTowerSumEt        ->Write("",TObject::kOverwrite);   
  eff_hltEle115_dr03HcalDepth1TowerSumEt  ->Write("",TObject::kOverwrite);   
  eff_hltEle115_isoEmHadDepth1            ->Write("",TObject::kOverwrite);   
  eff_hltEle115_EBdr03EcalRecHitSumEt     ->Write("",TObject::kOverwrite);   
  eff_hltEle115_EBdr03HcalTowerSumEt      ->Write("",TObject::kOverwrite);   
  eff_hltEle115_EBdr03HcalDepth1TowerSumEt->Write("",TObject::kOverwrite); 
  eff_hltEle115_EBisoEmHadDepth1          ->Write("",TObject::kOverwrite); 



  eff_hltPho200_eb_pt->Write("",TObject::kOverwrite);  eff_hltORALL_eb_pt->Write("",TObject::kOverwrite);   
  eff_hltPho200_ee_pt->Write("",TObject::kOverwrite);  eff_hltORALL_ee_pt->Write("",TObject::kOverwrite);   
  eff_hltPho200_etaSC->Write("",TObject::kOverwrite);  eff_hltORALL_etaSC->Write("",TObject::kOverwrite);   
  eff_hltPho200_phiSC->Write("",TObject::kOverwrite);  eff_hltORALL_phiSC->Write("",TObject::kOverwrite);   
  eff_hltPho200_sigma->Write("",TObject::kOverwrite);  eff_hltORALL_sigma->Write("",TObject::kOverwrite);    
  eff_hltPho200_hoe  ->Write("",TObject::kOverwrite);  eff_hltORALL_hoe  ->Write("",TObject::kOverwrite);   
  eff_hltPho200_deta ->Write("",TObject::kOverwrite);  eff_hltORALL_deta ->Write("",TObject::kOverwrite);   
  eff_hltPho200_dphi ->Write("",TObject::kOverwrite);  eff_hltORALL_dphi ->Write("",TObject::kOverwrite);   
  eff_hltPho200_dxy  ->Write("",TObject::kOverwrite);  eff_hltORALL_dxy  ->Write("",TObject::kOverwrite);   
  eff_hltPho200_nPV  ->Write("",TObject::kOverwrite);  eff_hltORALL_nPV  ->Write("",TObject::kOverwrite);   
  eff_hltPho200_dr03EcalRecHitSumEt       ->Write("",TObject::kOverwrite);   
  eff_hltPho200_dr03HcalTowerSumEt        ->Write("",TObject::kOverwrite);   
  eff_hltPho200_dr03HcalDepth1TowerSumEt  ->Write("",TObject::kOverwrite);   
  eff_hltPho200_isoEmHadDepth1            ->Write("",TObject::kOverwrite);   
  eff_hltPho200_EBdr03EcalRecHitSumEt     ->Write("",TObject::kOverwrite);   
  eff_hltPho200_EBdr03HcalTowerSumEt      ->Write("",TObject::kOverwrite);   
  eff_hltPho200_EBdr03HcalDepth1TowerSumEt->Write("",TObject::kOverwrite); 
  eff_hltPho200_EBisoEmHadDepth1          ->Write("",TObject::kOverwrite); 

  eff_hltORALL_dr03EcalRecHitSumEt       ->Write("",TObject::kOverwrite);   
  eff_hltORALL_dr03HcalTowerSumEt        ->Write("",TObject::kOverwrite);   
  eff_hltORALL_dr03HcalDepth1TowerSumEt  ->Write("",TObject::kOverwrite);   
  eff_hltORALL_isoEmHadDepth1            ->Write("",TObject::kOverwrite);   
  eff_hltORALL_EBdr03EcalRecHitSumEt     ->Write("",TObject::kOverwrite);   
  eff_hltORALL_EBdr03HcalTowerSumEt      ->Write("",TObject::kOverwrite);   
  eff_hltORALL_EBdr03HcalDepth1TowerSumEt->Write("",TObject::kOverwrite); 
  eff_hltORALL_EBisoEmHadDepth1          ->Write("",TObject::kOverwrite); 
 //-- print out summary
 cout << "##### " << dirname << " ## outfile = " << outfile << endl;
 cout << " Total Evt                = " << TotalN << endl;
 cout << " Event HLT_Mu             = " << nMuHLT   << " /Total = " << (double (nMuHLT)/ double (TotalN) * 100) << " %" << endl;
 cout << " EB,EE Electron           = " << nEB_Base << " + " << nEE_Base << " = " << (nEB_Base + nEE_Base) << " 	(eb/ee) " << (double (nEB_Base)/ double (nEE_Base)) << endl;
 cout << " EB,EE HEEPV70            = " << nEB_HEEP << " + " << nEE_HEEP << " = " << nHEEP << " (eb/ee) " << (double (nEB_HEEP)/ double (nEE_HEEP)) << endl;
 cout << " EB,EE TrgMatch           = " << nEB_TrgMatch  << " + " << nEE_TrgMatch << " = " << (nEB_TrgMatch + nEE_TrgMatch) << " 	(eb/ee) " << (double (nEB_TrgMatch)/ double (nEE_TrgMatch)) << endl;
 cout << " EB,EE HEEP pt>130 cut    = " << nHEEP << " => " << nHEEP130 << " 	," << (double(nHEEP-nHEEP130)/double(nHEEP))*100 << " % out-" << (nHEEP-nHEEP130) << endl;
 cout << " EB,EE HEEP pt>240 cut    = " << nHEEP << " => " << nHEEP240 << " 	," << (double(nHEEP-nHEEP240)/double(nHEEP))*100 << " % out-" << (nHEEP-nHEEP240)  << endl;
 cout << " EB,EE HLT_Pho200         = " << h_hltPho200_eb_pt->Integral()  << " + " << h_hltPho200_ee_pt->Integral() << " 	(eb/ee) " << (h_hltPho200_eb_pt->Integral()/h_hltPho200_ee_pt->Integral() ) << endl;
 cout << " EB,EE HLT_ORALL          = " << h_hltORALL_eb_pt->Integral()  << " + " << h_hltORALL_ee_pt->Integral()   << " 	(eb/ee) " << (h_hltORALL_eb_pt->Integral()/h_hltORALL_ee_pt->Integral() ) << endl;
 cout << "===== without pt cut ================================== " << endl;
 cout << " eff (HEEP/Base) EB,EE    = " << (double(nEB_HEEP)/double(nEB_Base))*100 << " % 	, " << (double(nEE_HEEP)/double(nEE_Base))*100 << " % " <<endl;
 cout << " eff (TrMatch/HEEP) EB,EE = " << (double(nEB_TrgMatch)/double(nEB_HEEP))*100 << " % 	, " << (double(nEE_TrgMatch)/double(nEE_HEEP))*100 << " % " <<endl;
// cout << " eff (Ele35/HEEP)         = " << (h_hltEle35_eb_pt->Integral()/double(nEB_HEEP))*100 << " % 	, " << (h_hltEle35_ee_pt->Integral()/double(nEE_HEEP))*100 << " % " <<endl;
 cout << " eff (Ele115/HEEP)        = " << (h_hltEle115_eb_pt->Integral()/double(nEB_HEEP))*100 << " % 	, " << (h_hltEle115_ee_pt->Integral()/double(nEE_HEEP))*100 << " % " <<endl;
 cout << " eff (Pho200/HEEP)        = " << (h_hltPho200_eb_pt->Integral()/double(nEB_HEEP))*100 << " % 	, " << (h_hltPho200_ee_pt->Integral()/double(nEE_HEEP))*100 << " % " <<endl;
 cout << " eff (OR/HEEP)115,200 = " << (h_hltORALL_eb_pt->Integral()/double(nEB_HEEP))*100 << " % 	, " << (h_hltORALL_ee_pt->Integral()/double(nEE_HEEP))*100 << " % " <<endl;
 cout << "==== with offline pt cut =================================== " << endl;
 cout << " den (HLT_Mu && HEEP)     = " << h_heep130_etaSC->Integral() << " (130) 	" << h_heep240_etaSC->Integral() << " (240)" << endl;
// cout << " num (den && HLT_Ele35)  = " << h_hltEle35_etaSC->Integral() << 
//                     "  	(Efficiency = " << (h_hltEle35_etaSC->Integral()/h_heep_etaSC->Integral())*100 << " %)" << endl;
 cout << " num (den && HLT_Ele115)  = " << h_hltEle115_etaSC->Integral() << 
                     "  	(Efficiency = " << (h_hltEle115_etaSC->Integral()/h_heep130_etaSC->Integral())*100 << " %)" << endl;
 cout << " num (den && HLT_Pho200)  = " << h_hltPho200_etaSC->Integral() << 
                     "  	(Efficiency = " << (h_hltPho200_etaSC->Integral()/h_heep240_etaSC->Integral())*100 << " %)" << endl;
 cout << " num (den && HLT_ORALL)   = " << h_hltORALL_etaSC->Integral() <<  
                     "  	(Efficiency = " << (h_hltORALL_etaSC->Integral()/h_heep130_etaSC->Integral())*100 << " %)" << endl;
 cout << "======================================= " << endl;

//  outfile->Write();
  outfile->Close();

  cout << "**** File Closed. " << endl;

  return 0;
}
