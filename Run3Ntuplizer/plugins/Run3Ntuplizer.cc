/*
 * \file Run3Ntuplizer.cc
 *
 * \author Jeong eun LEE
 * Created:  Thu, 27 Oct 2022
 * Updated:  Wed, 03 Jan 2023
 * Written for miniAOD
 */ //EgammaWork/ElectronNtupler/plugins/SimpleElectronNtupler.cc

// Standard C++ includes
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
// CMSSW data format
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "PhysicsTools/SelectorUtils/interface/CutApplicatorWithEventContentBase.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "CommonTools/Egamma/interface/ConversionTools.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "CommonTools/Egamma/interface/EffectiveAreas.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
//#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// ROOT includes
#include "map"
#include "Math/VectorUtil.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"

using namespace edm;
using std::cout;
using std::endl;
using std::vector;

// class declaration

class Run3Ntuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
   public:
      explicit Run3Ntuplizer(const edm::ParameterSet&);
      ~Run3Ntuplizer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      //enum IsoType { UNDEF = -1, ISO_ECAL = 0, ISO_HCAL = 1 };

      enum ElectronMatchType {UNMATCHED = 0,            // 0; unmatched
                              TRUE_PROMPT_ELECTRON,     // 1; prompt electron
                              TRUE_ELECTRON_FROM_TAU,   // 2; electron from prompt tau
                              TRUE_NON_PROMPT_ELECTRON, // 3; The non_prompt_electron include tau parents
                              TRUE_ELECTRON_FROM_C,     // 4; electron from c
                              TRUE_ELECTRON_FROM_B,     // 5; electron from b
                              TRUE_PROMPT_PHOTON        // 6; prompt photon (likely conversion)
                             };
   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      int matchToTruth(const edm::Ptr<reco::GsfElectron> el, const edm::Handle<edm::View<reco::GenParticle>> &prunedGenParticles, float &genPt);
      void findFirstNonElectronMother(const reco::Candidate *particle, int &ancestorPID, int &ancestorStatus);
      void printAndsaveCutFlowResult(vid::CutFlowResult &cutflow);
      double deltaPhi(double phi1, double phi2);
      double deltaR(double eta1, double phi1, double eta2, double phi2);

      // ----------member data ---------------------------
      // Data members that are the same for AOD and miniAOD
      edm::EDGetTokenT<edm::View<PileupSummaryInfo> > pileupToken_;
      edm::EDGetTokenT<double> rhoToken_;
      edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
      edm::EDGetTokenT<GenEventInfoProduct> genEventInfoProduct_;
      // MiniAOD case data members
      edm::EDGetToken electronsToken_;
      edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
      edm::EDGetTokenT<edm::View<reco::GenParticle>> genParticlesToken_;
      edm::EDGetTokenT<reco::ConversionCollection> conversionsToken_;
      edm::EDGetTokenT<edm::ValueMap<bool>> eleVetoIdMapToken_; //ID decisions objects
      edm::EDGetTokenT<edm::ValueMap<bool>> eleLooseIdMapToken_;
      edm::EDGetTokenT<edm::ValueMap<bool>> eleMediumIdMapToken_;
      edm::EDGetTokenT<edm::ValueMap<bool>> eleTightIdMapToken_;
      edm::EDGetTokenT<edm::ValueMap<bool>> eleHEEPIdMapToken_;
      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult>> eleIdFullInfoMapToken_;
      edm::EDGetTokenT<edm::View<pat::MET>> pfMETToken_;
      edm::EDGetTokenT<edm::View<pat::MET>> puppiMETToken_;
      edm::EDGetTokenT<trigger::TriggerEvent> triggerEventLabel_;
      edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;
      edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsToken_;
//      edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescalesToken_;
      // Verbose output for Electron ID
      bool   verboseIdFlag_;
      bool   doGenMatch_;
      double trgFilterDeltaPtCut_ ;
      double trgFilterDeltaRCut_  ;
      int    LoopNumber;

      TTree *tree_;

      // all variables for the output tree
      Int_t     run_;
      Int_t     lumis_;
      Long64_t  event_;
      Bool_t    isData_;
      // Vertex, Pileup variables
      Int_t   pvNTracks_; // Num of Tracks in primary vertex
      Int_t   nPUTrue_;   // true pile-up
      Int_t   nPU_;       // generated pile-up
      Int_t   nPV_;       // number of reconsrtucted primary vertices
      Int_t   nVtx_;
      Int_t   nGoodVtx_;
      Bool_t   isPVGood_;
      Float_t vtx_;
      Float_t vty_;
      Float_t vtz_;
      Float_t rho_;       // the rho variable
      Float_t genWeight_; // weight (can be negative)

      // Electron variables
      Int_t   nElectrons_; // number of electrons in the event
      std::vector<Float_t> Ele_pt_;
      std::vector<Int_t>   Ele_ecalDriven_;    //cut#0
      std::vector<Float_t> Ele_etaSC_;         //cut#1
      std::vector<Int_t>   Ele_isEB_;          //cut#2
      std::vector<Int_t>   Ele_isEE_;          //cut#3
      std::vector<Int_t>   Ele_isEE3_;
      std::vector<Int_t>   Ele_charge_;
      std::vector<Float_t> Ele_genPt_;
      std::vector<Float_t> Ele_Esct_;
      std::vector<Float_t> Ele_Et_;
      std::vector<Float_t> Ele_phiSC_;
      std::vector<Float_t> Ele_dEtaIn_;
      std::vector<Float_t> Ele_dEtaSeed_;      //cut#1
      std::vector<Float_t> Ele_dPhiIn_;
      std::vector<Float_t> Ele_full5x5_sigmaIetaIeta_; //cut#4
      std::vector<Float_t> Ele_E5x5_;
      std::vector<Float_t> Ele_E2x5_;
      std::vector<Float_t> Ele_E1x5_;
      std::vector<Float_t> Ele_E2x5OverE5x5_;  //cut#5
      std::vector<Float_t> Ele_E1x5OverE5x5_;
      std::vector<Float_t> Ele_R9_;
      std::vector<Float_t> Ele_hOverE_;        //cut#6
      std::vector<Float_t> Ele_dr03TkSumPt_;   //cut#7
      std::vector<Float_t> Ele_dr03EcalRecHitSumEt_;
      std::vector<Float_t> Ele_dr03HcalTowerSumEt_;
      std::vector<Float_t> Ele_dr03HcalDepth1TowerSumEt_;
      std::vector<Float_t> Ele_isoEmHadDepth1_;   //cut#8  deprecated.
      std::vector<Float_t> Ele_isoChargedHadrons_;
      std::vector<Float_t> Ele_isoNeutralHadrons_;
      std::vector<Float_t> Ele_isoPhotons_;
      std::vector<Float_t> Ele_isoChargedFromPU_;
      std::vector<Float_t> Ele_CombIsoWithEA_;
      std::vector<Float_t> Ele_relCombIsoWithEA_;
      std::vector<Float_t> Ele_ecalPFClusterIso_; //cut#8 test roc
      std::vector<Float_t> Ele_hcalPFClusterIso_; //cut#8 test roc
      std::vector<Float_t> Ele_CombPFClusterIsoWithEA_ ;    //cut#8
      std::vector<Float_t> Ele_relCombPFClusterIsoWithEA_ ; //cut#8 test values
      std::vector<Float_t> Ele_ooEmooP_;
      std::vector<Float_t> Ele_dxy_;
      std::vector<Float_t> Ele_dz_;
      std::vector<Int_t>   Ele_MissingInnerHits_;
      std::vector<Int_t>   Ele_passConversionVeto_;
      std::vector<Int_t>   Ele_passVetoId_;
      std::vector<Int_t>   Ele_passLooseId_;
      std::vector<Int_t>   Ele_passMediumId_;
      std::vector<Int_t>   Ele_passTightId_;
      std::vector<Int_t>   Ele_passHEEPId_;
      std::vector<Int_t>   Ele_isMatchTrue_;
      std::vector<Int_t>   Ele_genPartFlav_;
      EffectiveAreas       effectiveAreas_;
      std::vector<Int_t>   Ele_HEEP0cut_ ; //GsfEleMinEcalEtCut_0
      std::vector<Int_t>   Ele_HEEP1cut_ ; //GsfEleSCEtaMultiRangeCut_0
      std::vector<Int_t>   Ele_HEEP2cut_ ; //GsfEleEBEECut_0
      std::vector<Int_t>   Ele_HEEP3cut_ ; //GsfEleEBEECut_1
      std::vector<Int_t>   Ele_HEEP4cut_ ; //GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0
      std::vector<Int_t>   Ele_HEEP5cut_ ; //GsfEleFull5x5E2x5OverE5x5WithSatCut_0
      std::vector<Int_t>   Ele_HEEP6cut_ ; //GsfEleHadronicOverEMLinearCut_0
      std::vector<Int_t>   Ele_HEEP7cut_ ; //GsfEleTrkPtIsoCut_0
      std::vector<Int_t>   Ele_HEEP8cut_ ; //GsfEleEmHadD1IsoRhoCut_0
      std::vector<Int_t>   Ele_HEEP9cut_ ; //GsfEleDxyCut_0
      std::vector<Int_t>   Ele_HEEP10cut_; //GsfEleMissingHitsCut_0
      std::vector<Int_t>   Ele_HEEP11cut_; //GsfEleEcalDrivenCut_0
      std::vector<Float_t> Ele_HEEP0cutVal_ ; //GsfEleMinEcalEtCut_0
      std::vector<Float_t> Ele_HEEP1cutVal_ ; //GsfEleSCEtaMultiRangeCut_0
      std::vector<Float_t> Ele_HEEP2cutVal_ ; //GsfEleEBEECut_0
      std::vector<Float_t> Ele_HEEP3cutVal_ ; //GsfEleEBEECut_1
      std::vector<Float_t> Ele_HEEP4cutVal_ ; //GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0
      std::vector<Float_t> Ele_HEEP5cutVal_ ; //GsfEleFull5x5E2x5OverE5x5WithSatCut_0
      std::vector<Float_t> Ele_HEEP6cutVal_ ; //GsfEleHadronicOverEMLinearCut_0
      std::vector<Float_t> Ele_HEEP7cutVal_ ; //GsfEleTrkPtIsoCut_0
      std::vector<Float_t> Ele_HEEP8cutVal_ ; //GsfEleEmHadD1IsoRhoCut_0
      std::vector<Float_t> Ele_HEEP9cutVal_ ; //GsfEleDxyCut_0
      std::vector<Float_t> Ele_HEEP10cutVal_; //GsfEleMissingHitsCut_0
      std::vector<Float_t> Ele_HEEP11cutVal_; //GsfEleEcalDrivenCut_0

      // MET variables
      Float_t genMET_;
      Float_t genMET_Phi_;
      Float_t genMET_SumEt_;
      Float_t genMET_Significance_;
      Float_t pfMET_;
      Float_t pfMET_Phi_;
      Float_t pfMET_SumEt_;
      Float_t pfMET_Significance_;
      Float_t pfMET_T1JERUp_;
      Float_t pfMET_T1JERDo_;
      Float_t pfMET_T1JESUp_;
      Float_t pfMET_T1JESDo_;
      Float_t pfMET_T1MESUp_;
      Float_t pfMET_T1MESDo_;
      Float_t pfMET_T1EESUp_;
      Float_t pfMET_T1EESDo_;
      Float_t pfMET_T1PESUp_;
      Float_t pfMET_T1PESDo_;
      Float_t pfMET_T1TESUp_;
      Float_t pfMET_T1TESDo_;
      Float_t pfMET_T1UESUp_;
      Float_t pfMET_T1UESDo_;
      Float_t pfMET_T1TxyPhi_;
      Float_t pfMET_T1TxyPt_;
      Float_t pfMET_Phi_T1JESUp_;
      Float_t pfMET_Phi_T1JESDo_;
      Float_t pfMET_Phi_T1UESUp_;
      Float_t pfMET_Phi_T1UESDo_;
      Float_t puppiMET_;
      Float_t puppiMET_Phi_;
      Float_t puppiMET_SumEt_;
      Float_t puppiMET_Significance_;

      // Trigger variables
      ULong64_t HLTMuX_;
//      ULong64_t HLTMuXIsPrescaled_;
      ULong64_t HLTEleX_;
//      ULong64_t HLTEleXIsPrescaled_;
      ULong64_t HLTPhoX_;
//      ULong64_t HLTPhoXIsPrescaled_;
      ULong64_t HLTMETX_;
//      ULong64_t HLTMETXIsPrescaled_;

      Bool_t isHLTEle30Pass_;
      Bool_t isHLTEle35Pass_;
      Bool_t isHLTEle115Pass_;
      Bool_t isHLTPho175Pass_;
      Bool_t isHLTPho200Pass_;
      Bool_t isHLTPFMET120Pass_;
      Bool_t isHLTPFMETNoMu120Pass_;
      Bool_t isHLTMuPass_;
      Bool_t isHLTMETPass_;
//      Int_t  pho175Prescale_;
      Float_t trgmatch_dR_;
      Float_t trgmatch_dPt_;
      Float_t trgmatch_dEta_;
      Float_t trgmatch_dPhi_;
      std::vector<Int_t>   istrgMatchTrue_;
      std::vector<Int_t>   trgobj_idx_;
      std::vector<Float_t> trgobj_ele_pt_;
      std::vector<Float_t> trgobj_ele_eta_;
      std::vector<Float_t> trgobj_ele_phi_;
      std::vector<ULong64_t> eleFiredSingleTrgs_;
};

Run3Ntuplizer::Run3Ntuplizer(const edm::ParameterSet& iConfig):
  eleVetoIdMapToken_(consumes<edm::ValueMap<bool>>  (iConfig.getParameter<edm::InputTag>("eleIdMap_Cut94V2_Veto"))),
  eleLooseIdMapToken_(consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>("eleIdMap_Cut94V2_Loose"))),
  eleMediumIdMapToken_(consumes<edm::ValueMap<bool>>(iConfig.getParameter<edm::InputTag>("eleIdMap_Cut94V2_Medium"))),
  eleTightIdMapToken_(consumes<edm::ValueMap<bool>> (iConfig.getParameter<edm::InputTag>("eleIdMap_Cut94V2_Tight"))),
  eleHEEPIdMapToken_(consumes<edm::ValueMap<bool>>  (iConfig.getParameter<edm::InputTag>("eleIdMap_HEEPV71"))),
  eleIdFullInfoMapToken_(consumes<edm::ValueMap<vid::CutFlowResult>>(iConfig.getParameter<edm::InputTag>("eleIdFullInfoMap"))),
  verboseIdFlag_(iConfig.getParameter<bool>("eleIdVerbose")),
  effectiveAreas_((iConfig.getParameter<edm::FileInPath>("effAreasConfigFile")).fullPath())
{
     doGenMatch_ = false;
     LoopNumber = 0;
     // Prepare tokens for all input collections and objects
     if(iConfig.existsAs<edm::InputTag>("genParticles")){
        // only available for MC sample
        doGenMatch_ = true;
        genParticlesToken_ = consumes<edm::View<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticles"));
        genEventInfoProduct_ = consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("genEventInfoProduct"));
        pileupToken_ = consumes<edm::View<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileup"));
     }
     rhoToken_ = consumes<double>(iConfig.getParameter<edm::InputTag>("rho"));
     beamSpotToken_ = consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpot"));
     electronsToken_ = consumes<edm::View<reco::GsfElectron>>(iConfig.getParameter<edm::InputTag>("electrons"));
     vtxToken_ = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"));
     conversionsToken_ = consumes< reco::ConversionCollection>(iConfig.getParameter<edm::InputTag>("conversions"));
     pfMETToken_ = consumes<View<pat::MET>>(iConfig.getParameter<InputTag>("pfmets"));
     puppiMETToken_ = consumes<View<pat::MET>>(iConfig.getParameter<InputTag>("puppimets"));
     triggerResultsToken_ = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
     triggerObjectsToken_ = consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerObjects"));
//     triggerPrescalesToken_ = consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("triggerPrescales"));

     // Set up the ntuple structure
     edm::Service<TFileService> fs;
     tree_ = fs->make<TTree> ("tree", "Tree");
     tree_->Branch("run"                         , &run_   , "run/I"  );
     tree_->Branch("lumis"                       , &lumis_ , "lumis/I");
     tree_->Branch("event"                       , &event_ );
     tree_->Branch("isData"                      , &isData_);
     tree_->Branch("pvNTracks"                   , &pvNTracks_ , "pvNTracks/I");
     tree_->Branch("nPV"                         , &nPV_       , "nPV/I"      );
     tree_->Branch("nPU"                         , &nPU_       , "nPU/I"      );
     tree_->Branch("nPUTrue"                     , &nPUTrue_   , "nPUTrue/I"  );
     tree_->Branch("nVtx"                        , &nVtx_      , "nVtx/I" );
     tree_->Branch("nGoodVtx"                    , &nGoodVtx_  , "nGoodVtx/I" );
     tree_->Branch("isPVGood"                    , &isPVGood_  );
     tree_->Branch("vtx"                         , &vtx_       , "vtx/F"      );
     tree_->Branch("vty"                         , &vty_       , "vty/F"      );
     tree_->Branch("vtz"                         , &vtz_       , "vtz/F"      );
     tree_->Branch("rho"                         , &rho_       , "rho/F"      );
     tree_->Branch("genWeight"                   , &genWeight_ , "genWeight/F" );
     tree_->Branch("nEle"                        , &nElectrons_, "nEle/I");
     tree_->Branch("Ele_pt"                      , &Ele_pt_    );
     tree_->Branch("Ele_genPt"                   , &Ele_genPt_    );
     tree_->Branch("Ele_Esct"                     , &Ele_Esct_    );
     tree_->Branch("Ele_Et"                      , &Ele_Et_    );
     tree_->Branch("Ele_etaSC"                   , &Ele_etaSC_ );
     tree_->Branch("Ele_phiSC"                   , &Ele_phiSC_ );
     tree_->Branch("Ele_ecalDriven"              , &Ele_ecalDriven_    );
     tree_->Branch("Ele_isEB"                    , &Ele_isEB_    );
     tree_->Branch("Ele_isEE"                    , &Ele_isEE_    );
     tree_->Branch("Ele_isEE3"                   , &Ele_isEE3_   );
     tree_->Branch("Ele_charge"                  , &Ele_charge_ );
     tree_->Branch("Ele_dEtaIn"                  , &Ele_dEtaIn_);
     tree_->Branch("Ele_dEtaSeed"                , &Ele_dEtaSeed_);
     tree_->Branch("Ele_dPhiIn"                  , &Ele_dPhiIn_);
     tree_->Branch("Ele_full5x5_sigmaIetaIeta"   , &Ele_full5x5_sigmaIetaIeta_);
     tree_->Branch("Ele_E5x5"                    , &Ele_E5x5_    );
     tree_->Branch("Ele_E2x5"                    , &Ele_E2x5_    );
     tree_->Branch("Ele_E1x5"                    , &Ele_E1x5_    );
     tree_->Branch("Ele_E2x5OverE5x5"            , &Ele_E2x5OverE5x5_    );
     tree_->Branch("Ele_E1x5OverE5x5"            , &Ele_E1x5OverE5x5_    );
     tree_->Branch("Ele_R9"                      , &Ele_R9_);
     tree_->Branch("Ele_hOverE"                  , &Ele_hOverE_);
     tree_->Branch("Ele_dr03TkSumPt"             , &Ele_dr03TkSumPt_);
     tree_->Branch("Ele_dr03EcalRecHitSumEt"     , &Ele_dr03EcalRecHitSumEt_);
     tree_->Branch("Ele_dr03HcalTowerSumEt"      , &Ele_dr03HcalTowerSumEt_);
     tree_->Branch("Ele_dr03HcalDepth1TowerSumEt", &Ele_dr03HcalDepth1TowerSumEt_);
     tree_->Branch("Ele_isoEmHadDepth1"          , &Ele_isoEmHadDepth1_);
     tree_->Branch("Ele_isoChargedHadrons"       , &Ele_isoChargedHadrons_);
     tree_->Branch("Ele_isoNeutralHadrons"       , &Ele_isoNeutralHadrons_);
     tree_->Branch("Ele_isoPhotons"              , &Ele_isoPhotons_);
     tree_->Branch("Ele_CombIsoWithEA"           , &Ele_CombIsoWithEA_);
     tree_->Branch("Ele_relCombIsoWithEA"        , &Ele_relCombIsoWithEA_);
     tree_->Branch("Ele_isoChargedFromPU"        , &Ele_isoChargedFromPU_);
     tree_->Branch("Ele_ecalPFClusterIso"        , &Ele_ecalPFClusterIso_);
     tree_->Branch("Ele_hcalPFClusterIso"        , &Ele_hcalPFClusterIso_);
     tree_->Branch("Ele_CombPFClusterIsoWithEA"  , &Ele_CombPFClusterIsoWithEA_ );    //cut#8
     tree_->Branch("Ele_relCombPFClusterIsoWithEA",&Ele_relCombPFClusterIsoWithEA_ ); //cut#8 test values
     tree_->Branch("Ele_ooEmooP"                 , &Ele_ooEmooP_);
     tree_->Branch("Ele_dxy"                      , &Ele_dxy_);
     tree_->Branch("Ele_dz"                      , &Ele_dz_);
     tree_->Branch("Ele_MissingInnerHits"        , &Ele_MissingInnerHits_);
     tree_->Branch("Ele_passConversionVeto"      , &Ele_passConversionVeto_);
     tree_->Branch("Ele_passVetoId"              , &Ele_passVetoId_);
     tree_->Branch("Ele_passLooseId"             , &Ele_passLooseId_);
     tree_->Branch("Ele_passMediumId"            , &Ele_passMediumId_);
     tree_->Branch("Ele_passTightId"             , &Ele_passTightId_);
     tree_->Branch("Ele_passHEEPId"              , &Ele_passHEEPId_);
     tree_->Branch("Ele_isMatchTrue"             , &Ele_isMatchTrue_);
     tree_->Branch("Ele_genPartFlav"             , &Ele_genPartFlav_);
     tree_->Branch("Ele_HEEP0cut"      ,  &Ele_HEEP0cut_    );
     tree_->Branch("Ele_HEEP1cut"      ,  &Ele_HEEP1cut_    );
     tree_->Branch("Ele_HEEP2cut"      ,  &Ele_HEEP2cut_    );
     tree_->Branch("Ele_HEEP3cut"      ,  &Ele_HEEP3cut_    );
     tree_->Branch("Ele_HEEP4cut"      ,  &Ele_HEEP4cut_    );
     tree_->Branch("Ele_HEEP5cut"      ,  &Ele_HEEP5cut_    );
     tree_->Branch("Ele_HEEP6cut"      ,  &Ele_HEEP6cut_    );
     tree_->Branch("Ele_HEEP7cut"      ,  &Ele_HEEP7cut_    );
     tree_->Branch("Ele_HEEP8cut"      ,  &Ele_HEEP8cut_    );
     tree_->Branch("Ele_HEEP9cut"      ,  &Ele_HEEP9cut_    );
     tree_->Branch("Ele_HEEP10cut"     ,  &Ele_HEEP10cut_   );
     tree_->Branch("Ele_HEEP11cut"     ,  &Ele_HEEP11cut_   );
     tree_->Branch("Ele_HEEP0cutVal"   ,  &Ele_HEEP0cutVal_ );
     tree_->Branch("Ele_HEEP1cutVal"   ,  &Ele_HEEP1cutVal_ );
     tree_->Branch("Ele_HEEP2cutVal"   ,  &Ele_HEEP2cutVal_ );
     tree_->Branch("Ele_HEEP3cutVal"   ,  &Ele_HEEP3cutVal_ );
     tree_->Branch("Ele_HEEP4cutVal"   ,  &Ele_HEEP4cutVal_ );
     tree_->Branch("Ele_HEEP5cutVal"   ,  &Ele_HEEP5cutVal_ );
     tree_->Branch("Ele_HEEP6cutVal"   ,  &Ele_HEEP6cutVal_ );
     tree_->Branch("Ele_HEEP7cutVal"   ,  &Ele_HEEP7cutVal_ );
     tree_->Branch("Ele_HEEP8cutVal"   ,  &Ele_HEEP8cutVal_ );
     tree_->Branch("Ele_HEEP9cutVal"   ,  &Ele_HEEP9cutVal_ );
     tree_->Branch("Ele_HEEP10cutVal"  ,  &Ele_HEEP10cutVal_);
     tree_->Branch("Ele_HEEP11cutVal"  ,  &Ele_HEEP11cutVal_);
     tree_->Branch("genMET"                      , &genMET_);
     tree_->Branch("genMET_Phi"                  , &genMET_Phi_);
     tree_->Branch("genMET_SumEt"                , &genMET_SumEt_);
     tree_->Branch("genMET_Significance"         , &genMET_Significance_);
     tree_->Branch("pfMET"                       , &pfMET_);
     tree_->Branch("pfMET_Phi"                   , &pfMET_Phi_);
     tree_->Branch("pfMET_SumEt"                 , &pfMET_SumEt_);
     tree_->Branch("pfMET_Significance"          , &pfMET_Significance_);
     tree_->Branch("pfMET_T1JERUp"               , &pfMET_T1JERUp_);
     tree_->Branch("pfMET_T1JERDo"               , &pfMET_T1JERDo_);
     tree_->Branch("pfMET_T1JESUp"               , &pfMET_T1JESUp_);
     tree_->Branch("pfMET_T1JESDo"               , &pfMET_T1JESDo_);
     tree_->Branch("pfMET_T1UESUp"               , &pfMET_T1UESUp_);
     tree_->Branch("pfMET_T1UESDo"               , &pfMET_T1UESDo_);
     tree_->Branch("pfMET_Phi_T1JESUp"           , &pfMET_Phi_T1JESUp_);
     tree_->Branch("pfMET_Phi_T1JESDo"           , &pfMET_Phi_T1JESDo_);
     tree_->Branch("pfMET_Phi_T1UESUp"           , &pfMET_Phi_T1UESUp_);
     tree_->Branch("pfMET_Phi_T1UESDo"           , &pfMET_Phi_T1UESDo_);
     tree_->Branch("puppiMET"                    , &puppiMET_);
     tree_->Branch("puppiMET_Phi"                , &puppiMET_Phi_);
     tree_->Branch("puppiMET_SumEt"              , &puppiMET_SumEt_);
     tree_->Branch("puppiMET_Significance"       , &puppiMET_Significance_);
     tree_->Branch("isHLTEle30Pass"              , &isHLTEle30Pass_);
     tree_->Branch("isHLTEle35Pass"              , &isHLTEle35Pass_);
     tree_->Branch("isHLTEle115Pass"             , &isHLTEle115Pass_);
     tree_->Branch("isHLTPho175Pass"             , &isHLTPho175Pass_);
     tree_->Branch("isHLTPho200Pass"             , &isHLTPho200Pass_);
     tree_->Branch("isHLTPFMET120Pass"           , &isHLTPFMET120Pass_);
     tree_->Branch("isHLTPFMETNoMu120Pass"       , &isHLTPFMETNoMu120Pass_);
     tree_->Branch("isHLTMuXPass"                , &isHLTMuPass_);
     tree_->Branch("isHLTMETPass"                , &isHLTMETPass_);
//     tree_->Branch("pho175Prescale_"             , &pho175Prescale_);
     tree_->Branch("trgobj_idx"                  , &trgobj_idx_);
     tree_->Branch("trgobj_ele_pt"               , &trgobj_ele_pt_);
     tree_->Branch("trgobj_ele_eta"              , &trgobj_ele_eta_);
     tree_->Branch("trgobj_ele_phi"              , &trgobj_ele_phi_);
     tree_->Branch("eleFiredSingleTrgs"          , &eleFiredSingleTrgs_);
     tree_->Branch("trgMatch_dPt"                , &trgmatch_dPt_);
     tree_->Branch("trgMatch_dEta"               , &trgmatch_dEta_);
     tree_->Branch("trgMatch_dPhi"               , &trgmatch_dPhi_);
     tree_->Branch("trgMatch_dR"                 , &trgmatch_dR_);
     tree_->Branch("istrgMatchTrue"              , &istrgMatchTrue_ ) ;
     tree_->Branch("HLTMuX"                      , &HLTMuX_);
//     tree_->Branch("HLTMuXIsPrescaled"           , &HLTMuXIsPrescaled_);
     tree_->Branch("HLTMETX"                     , &HLTMETX_);
//     tree_->Branch("HLTMETXIsPrescaled"          , &HLTMETXIsPrescaled_);
     tree_->Branch("HLTEleX"                     , &HLTEleX_);
//     tree_->Branch("HLTEleXIsPrescaled"          , &HLTEleXIsPrescaled_);
     tree_->Branch("HLTPhoX"                     , &HLTPhoX_);
//     tree_->Branch("HLTPhoXIsPrescaled"          , &HLTPhoXIsPrescaled_);
}

Run3Ntuplizer::~Run3Ntuplizer(){}

// ------------ method called for each event  ------------
void Run3Ntuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  using namespace std;
  using namespace edm;
  using namespace reco;

  LoopNumber++;

  run_    = iEvent.id().run();
  event_  = iEvent.id().event();
  lumis_  = iEvent.luminosityBlock();
  isData_ = iEvent.isRealData();

  edm::Handle<edm::View<reco::GenParticle> > genParticles; // Get the MC collection
  edm::Handle< GenEventInfoProduct > genWeightH;           // Get gen weight info
  edm::Handle<edm::View<PileupSummaryInfo> > pileupHandle; // Get Pileup info

  if((!isData_ and doGenMatch_)){
       iEvent.getByToken(genParticlesToken_,genParticles);
       iEvent.getByToken(genEventInfoProduct_,genWeightH);
       genWeight_ = genWeightH->GenEventInfoProduct::weight();
       iEvent.getByToken(pileupToken_, pileupHandle);
       for( auto & puInfoElement : *pileupHandle){
          if( puInfoElement.getBunchCrossing() == 0 ){
              nPU_    = puInfoElement.getPU_NumInteractions();
              nPUTrue_= puInfoElement.getTrueNumInteractions();
          }
       }
       //pho175Prescale_ = 0; //becasue MC doesn't have prescale value
  }
  edm::Handle< double > rhoH;
  iEvent.getByToken(rhoToken_,rhoH);                     // Get rho value
  rho_ = rhoH.isValid() ? (float)(*rhoH) : 0;

  edm::Handle<reco::BeamSpot> theBeamSpot;
  iEvent.getByToken(beamSpotToken_,theBeamSpot);         // Get the beam spot

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(vtxToken_, vertices);                // Get vertex
  if (!vertices.isValid()) return; // skip the event if no vertex found
  nVtx_     = 0;
  nGoodVtx_ = 0;
  nPV_      = vertices->size();
  const reco::Vertex &pv = vertices->front();
  pvNTracks_ = pv.nTracks();

  for (vector<reco::Vertex>::const_iterator v = vertices->begin(); v != vertices->end(); ++v) {

      if (nVtx_ == 0) { //check only the first vertex = primary vertex
          vtx_ = v->x();
          vty_ = v->y();
          vtz_ = v->z();
          isPVGood_ = false;
          if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) isPVGood_ = true;
      }//primary vertex check done.

      if (!v->isFake() && v->ndof() > 4. && fabs(v->z()) <= 24. && fabs(v->position().rho()) <= 2.) nGoodVtx_++; // count num of good vertex in the event
      nVtx_++; // check all vertices
  }

  edm::Handle<reco::ConversionCollection> conversions;
  iEvent.getByToken(conversionsToken_, conversions);     // Get the conversions

  //-------------------------------//
  //--- Fill Electron Variables ---//
  //-------------------------------//

  edm::Handle<edm::View<reco::GsfElectron> > electrons;  // Get Electron
  iEvent.getByToken(electronsToken_, electrons);
  if( !electrons.isValid() ){ printf("Please Check ! : electrons is not Valid\n"); }
  // Get the electron ID data from the event stream.
  // Note: this implies that the VID ID modules have been run upstream.
  edm::Handle<edm::ValueMap<bool>> veto_id_decisions  ; iEvent.getByToken(eleVetoIdMapToken_  , veto_id_decisions)  ;
  edm::Handle<edm::ValueMap<bool>> loose_id_decisions ; iEvent.getByToken(eleLooseIdMapToken_ , loose_id_decisions) ;
  edm::Handle<edm::ValueMap<bool>> medium_id_decisions; iEvent.getByToken(eleMediumIdMapToken_, medium_id_decisions);
  edm::Handle<edm::ValueMap<bool>> tight_id_decisions ; iEvent.getByToken(eleTightIdMapToken_ , tight_id_decisions) ;
  edm::Handle<edm::ValueMap<bool>> heep_id_decisions  ; iEvent.getByToken(eleHEEPIdMapToken_  , heep_id_decisions)  ;
  // Full cut flow info for one of the working points:
  edm::Handle<edm::ValueMap<vid::CutFlowResult> > heep_id_cutflow_data;
  iEvent.getByToken(eleIdFullInfoMapToken_,heep_id_cutflow_data);
  nElectrons_ = 0;
  Ele_pt_.clear();
  Ele_ecalDriven_.clear();
  Ele_isEB_.clear();
  Ele_isEE_.clear();
  Ele_isEE3_.clear();
  Ele_charge_.clear();
  Ele_genPt_.clear();
  Ele_Esct_.clear();
  Ele_Et_.clear();
  Ele_etaSC_.clear();
  Ele_phiSC_.clear();
  Ele_dEtaIn_.clear();
  Ele_dEtaSeed_.clear();
  Ele_dPhiIn_.clear();
  Ele_full5x5_sigmaIetaIeta_.clear();
  Ele_E5x5_.clear();
  Ele_E2x5_.clear();
  Ele_E1x5_.clear();
  Ele_E2x5OverE5x5_.clear();
  Ele_E1x5OverE5x5_.clear();
  Ele_R9_.clear();
  Ele_dr03EcalRecHitSumEt_.clear();
  Ele_dr03HcalTowerSumEt_.clear();
  Ele_dr03HcalDepth1TowerSumEt_.clear();
  Ele_isoEmHadDepth1_.clear();
  Ele_hOverE_.clear();
  Ele_dr03TkSumPt_.clear();
  Ele_isoChargedHadrons_.clear();
  Ele_isoNeutralHadrons_.clear();
  Ele_isoPhotons_.clear();
  Ele_relCombIsoWithEA_.clear();
  Ele_isoChargedFromPU_.clear();
  Ele_ecalPFClusterIso_.clear();
  Ele_hcalPFClusterIso_.clear();
  Ele_CombPFClusterIsoWithEA_.clear();
  Ele_relCombPFClusterIsoWithEA_.clear();
  Ele_ooEmooP_.clear();
  Ele_dxy_.clear();
  Ele_dz_.clear();
  Ele_MissingInnerHits_.clear();
  Ele_passConversionVeto_.clear();
  Ele_passVetoId_.clear();
  Ele_passLooseId_.clear();
  Ele_passMediumId_.clear();
  Ele_passTightId_.clear();
  Ele_passHEEPId_.clear();
  Ele_isMatchTrue_.clear();
  Ele_genPartFlav_.clear();
  Ele_HEEP0cut_.clear();
  Ele_HEEP1cut_.clear();
  Ele_HEEP2cut_.clear();
  Ele_HEEP3cut_.clear();
  Ele_HEEP4cut_.clear();
  Ele_HEEP5cut_.clear();
  Ele_HEEP6cut_.clear();
  Ele_HEEP7cut_.clear();
  Ele_HEEP8cut_.clear();
  Ele_HEEP9cut_.clear();
  Ele_HEEP10cut_.clear();
  Ele_HEEP11cut_.clear();
  Ele_HEEP0cutVal_.clear();
  Ele_HEEP1cutVal_.clear();
  Ele_HEEP2cutVal_.clear();
  Ele_HEEP3cutVal_.clear();
  Ele_HEEP4cutVal_.clear();
  Ele_HEEP5cutVal_.clear();
  Ele_HEEP6cutVal_.clear();
  Ele_HEEP7cutVal_.clear();
  Ele_HEEP8cutVal_.clear();
  Ele_HEEP9cutVal_.clear();
  Ele_HEEP10cutVal_.clear();
  Ele_HEEP11cutVal_.clear();
  trgobj_idx_.clear();
  trgobj_ele_pt_.clear();
  trgobj_ele_eta_.clear();
  trgobj_ele_phi_.clear();
  eleFiredSingleTrgs_.clear();

  double ele_pt  = -999 ; //used for trg matching at the last part
  double ele_eta = -999 ;
  double ele_phi = -999 ;
  // Start Loop over electrons in the event
  for (size_t i = 0; i < electrons->size(); ++i){
    ele_pt  = electrons->ptrAt(0)->pt();
    ele_eta = electrons->ptrAt(0)->superCluster()->eta() ;
    ele_phi = electrons->ptrAt(0)->superCluster()->phi() ;

    const auto el = electrons->ptrAt(i);
    if(el->pt() < 10) continue; // keep only electrons above 10 GeV
    nElectrons_++;
    Ele_pt_.push_back( el->pt() );
    Ele_ecalDriven_.push_back( el->ecalDriven() );
    Ele_charge_.push_back( el->charge() );
    Ele_etaSC_.push_back( el->superCluster()->eta() );
    float abseta =  abs(el->superCluster()->eta());

    int isEB = 0; int isEE = 0; int isEE3 = 0;
    if ( abseta < 1.4442) isEB = 1;
    if ( abseta > 1.566 and abseta < 2.5) isEE = 1;
    if ( abseta >= 2.5) isEE3 = 1; //for Run3 eta extended to 3.0
    Ele_isEB_.push_back(isEB);
    Ele_isEE_.push_back(isEE);
    Ele_isEE3_.push_back(isEE3);

    float sinTheta = el->p() != 0. ? el->pt() / el->p() : 0.;
    Ele_Esct_.push_back( el->ecalEnergy() * sinTheta);
    Ele_Et_.push_back( el->superCluster()->energy() * sinTheta );
    Ele_phiSC_.push_back( el->superCluster()->phi() );
    Ele_dEtaIn_.push_back( el->deltaEtaSuperClusterTrackAtVtx() );
    //Ele_dEtaSeed_.push_back( el->deltaEtaSeedClusterTrackAtVtx() );
    // Calculation of Ele_dEtaSeed is taken from VID (by HEEP folks)
    // https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/RecoEgamma/ElectronIdentification/plugins/cuts/GsfEleDEtaInSeedCut.cc#L31-L32
    if(el->superCluster().isNonnull() and el->superCluster()->seed().isNonnull()) {
         Ele_dEtaSeed_.push_back(el->deltaEtaSuperClusterTrackAtVtx() - el->superCluster()->eta() + el->superCluster()->seed()->eta());
    }else {
         Ele_dEtaSeed_.push_back(std::numeric_limits<float>::max());
    }
    Ele_dPhiIn_.push_back( el->deltaPhiSuperClusterTrackAtVtx() );
    Ele_full5x5_sigmaIetaIeta_.push_back( el->full5x5_sigmaIetaIeta() );
    Ele_E5x5_.push_back( el->full5x5_e5x5() );
    Ele_E2x5_.push_back( el->full5x5_e2x5Max() );
    Ele_E1x5_.push_back( el->full5x5_e1x5() );
    double E2x5OverE5x5 = 0;  double E1x5OverE5x5 = 0;
    if (el->full5x5_e5x5() != 0) {
         E2x5OverE5x5 = (el->full5x5_e2x5Max() / el->full5x5_e5x5());
         E1x5OverE5x5 = (el->full5x5_e1x5() / el->full5x5_e5x5());
    }
    Ele_E2x5OverE5x5_.push_back( E2x5OverE5x5 );
    Ele_E1x5OverE5x5_.push_back( E1x5OverE5x5 );
    Ele_hOverE_.push_back( el->hcalOverEcal() );
    Ele_R9_.push_back( el->r9() );
    Ele_dr03TkSumPt_.push_back( el->dr03TkSumPt() );
    Ele_dr03EcalRecHitSumEt_.push_back( el->dr03EcalRecHitSumEt() );
    Ele_dr03HcalTowerSumEt_.push_back( el->dr03HcalTowerSumEt() );
    Ele_dr03HcalDepth1TowerSumEt_.push_back( el->dr03HcalTowerSumEt(1) );
    Ele_isoEmHadDepth1_.push_back(el->dr03EcalRecHitSumEt() + el->dr03HcalTowerSumEt(1));
    Ele_ecalPFClusterIso_.push_back(el->ecalPFClusterIso());
    Ele_hcalPFClusterIso_.push_back(el->hcalPFClusterIso());

    // |1/E-1/p| = |1/E - EoverPinner/E| is computed below
    // The if protects against ecalEnergy == inf or zero
    // (always the case for miniAOD for electrons <5 GeV)
    if( el->ecalEnergy() == 0 ){
      printf("Electron energy is zero! => ooEmooP set to 1e30\n");
      Ele_ooEmooP_.push_back( 1e30 );
    }else if( !std::isfinite(el->ecalEnergy())){
      printf("Electron energy is not finite! => ooEmooP set to 1e30\n");
      Ele_ooEmooP_.push_back( 1e30 );
    }else{
      Ele_ooEmooP_.push_back( fabs(1.0/el->ecalEnergy() - el->eSuperClusterOverP()/el->ecalEnergy() ) );
    }

    // Isolation
    GsfElectron::PflowIsolationVariables pfIso = el->pfIsolationVariables();
    // Compute individual PF isolations
    Ele_isoChargedHadrons_.push_back( pfIso.sumChargedHadronPt );
    Ele_isoNeutralHadrons_.push_back( pfIso.sumNeutralHadronEt );
    Ele_isoPhotons_.push_back( pfIso.sumPhotonEt );
    Ele_isoChargedFromPU_.push_back( pfIso.sumPUPt );

    // Compute combined relative PF isolation with the effective area correction for pile-up
    float eA = effectiveAreas_.getEffectiveArea(abseta);
    Ele_CombIsoWithEA_.push_back(pfIso.sumChargedHadronPt + std::max( 0.0f, pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - eA*rho_) );
    Ele_relCombIsoWithEA_.push_back((pfIso.sumChargedHadronPt + std::max( 0.0f, pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - eA*rho_)) / el->pt() );
    Ele_CombPFClusterIsoWithEA_.push_back((std::max( 0.0f, el->ecalPFClusterIso() + el->hcalPFClusterIso() - eA*rho_)) );
    Ele_relCombPFClusterIsoWithEA_.push_back((std::max( 0.0f, el->ecalPFClusterIso() + el->hcalPFClusterIso() - eA*rho_)) / el->pt() );

    // Impact parameter
    reco::GsfTrackRef theTrack = el->gsfTrack();
    Ele_dxy_.push_back( theTrack->dxy(pv.position() ) );
    Ele_dz_.push_back( theTrack->dz( pv.position() ) );

    // Conversion rejection
    Ele_MissingInnerHits_.push_back(el->gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS) );

    bool passConvVeto = !ConversionTools::hasMatchedConversion(*el, *conversions, theBeamSpot->position());
    Ele_passConversionVeto_.push_back( (int) passConvVeto );

    // Look up and save the ID decisions
    bool isPassVeto   = (*veto_id_decisions)[el]  ;
    bool isPassLoose  = (*loose_id_decisions)[el] ;
    bool isPassMedium = (*medium_id_decisions)[el];
    bool isPassTight  = (*tight_id_decisions)[el] ;
    bool isPassHEEP   = (*heep_id_decisions)[el]  ;

    Ele_passVetoId_.push_back  ( (int)isPassVeto  );
    Ele_passLooseId_.push_back ( (int)isPassLoose );
    Ele_passMediumId_.push_back( (int)isPassMedium);
    Ele_passTightId_.push_back ( (int)isPassTight );
    Ele_passHEEPId_.push_back  ( (int)isPassHEEP ) ;

    //// The full info for HEEP ID
    vid::CutFlowResult fullCutFlowData = (*heep_id_cutflow_data)[el];
    // Full printout
    //printf("\nDEBUG CutFlow start, full info for candidate with pt, eta=%f, %f:\n", el->pt(), el->superCluster()->eta());
    printAndsaveCutFlowResult(fullCutFlowData);

    // Example of how to find the ID decision with one cut removed,
    // this could be needed for N-1 efficiency studies.
    //const int cutIndexToMask = 8; //isocut
    //vid::CutFlowResult maskedCutFlowData = fullCutFlowData.getCutFlowResultMasking(cutIndexToMask);
    ////printf("DEBUG CutFlow, the result with cut %s masked out\n",
    ////             maskedCutFlowData.getNameAtIndex(cutIndexToMask).c_str());
    ////printAndsaveCutFlowResult(maskedCutFlowData);
/*
    Index               cut name                 isMasked value-cut-upon  pass?
       0                    GsfEleMinEcalEtCut_0    0        58.264587      1
       1              GsfEleSCEtaMultiRangeCut_0    0        2.681049       0
       2                         GsfEleEBEECut_0    0        0.082915       0
       3                         GsfEleEBEECut_1    0        0.036590       1
       4  GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0    1        0.029677       1
       5   GsfEleFull5x5E2x5OverE5x5WithSatCut_0    0        1.434267       1
       6         GsfEleHadronicOverEMLinearCut_0    0        60.346268      0
       7                     GsfEleTrkPtIsoCut_0    0        0.000000       1
       8                GsfEleEmHadD1IsoRhoCut_0    0        4.827967       1
       9                          GsfEleDxyCut_0    0        0.004763       1
      10                  GsfEleMissingHitsCut_0    0        0.000000       1
      11                   GsfEleEcalDrivenCut_0    0        0.000000       0
*/

    //if( verboseIdFlag_  and LoopNumber < 5) {
    //    vid::CutFlowResult fullCutFlowData = (*heep_id_cutflow_data)[el];
    //    // Full printout
    //    printf("\nDEBUG CutFlow start, full info for candidate with pt, eta=%f, %f:\n", el->pt(), el->superCluster()->eta());
    //    printAndsaveCutFlowResult(fullCutFlowData);

    //    // Example of how to find the ID decision with one cut removed,
    //    // this could be needed for N-1 efficiency studies.
    //    const int cutIndexToMask = 4;
    //    vid::CutFlowResult maskedCutFlowData = fullCutFlowData.getCutFlowResultMasking(cutIndexToMask);
    //    printf("DEBUG CutFlow, the result with cut %s masked out\n",
    //               maskedCutFlowData.getNameAtIndex(cutIndexToMask).c_str());
    //    printAndsaveCutFlowResult(maskedCutFlowData);
/*
    //    Index               cut name                 isMasked value-cut-upon  pass?
    //       0                    GsfEleMinEcalEtCut_0    0        58.264587      1
    //       1              GsfEleSCEtaMultiRangeCut_0    0        2.681049       0
    //       2                         GsfEleEBEECut_0    0        0.082915       0
    //       3                         GsfEleEBEECut_1    0        0.036590       1
    //       4  GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0    1        0.029677       1
    //       5   GsfEleFull5x5E2x5OverE5x5WithSatCut_0    0        1.434267       1
    //       6         GsfEleHadronicOverEMLinearCut_0    0        60.346268      0
    //       7                     GsfEleTrkPtIsoCut_0    0        0.000000       1
    //       8                GsfEleEmHadD1IsoRhoCut_0    0        4.827967       1
    //       9                          GsfEleDxyCut_0    0        0.004763       1
    //      10                  GsfEleMissingHitsCut_0    0        0.000000       1
    //      11                   GsfEleEcalDrivenCut_0    0        0.000000       0
*/
    //}
    // Save MC truth match
    if(!isData_ and doGenMatch_){
          float genPt = 0;
          Ele_genPartFlav_.push_back(matchToTruth( el, genParticles, genPt));
          //cout << " Ele_genPartFlav " << matchToTruth( el, genParticles, genPt) << " , Ele_genPt " << genPt << endl;
          //if( matchToTruth( el, genParticles, genPt) == 0 ) cout << "---> 0; unmatched                                  " << endl;
          //if( matchToTruth( el, genParticles, genPt) == 1 ) cout << "---> 1; prompt electron                            " << endl;
          //if( matchToTruth( el, genParticles, genPt) == 2 ) cout << "---> 2; electron from prompt tau                   " << endl;
          //if( matchToTruth( el, genParticles, genPt) == 3 ) cout << "---> 3; The non_prompt_electron include tau parents" << endl;
          //if( matchToTruth( el, genParticles, genPt) == 4 ) cout << "---> 4; electron from c                            " << endl;
          //if( matchToTruth( el, genParticles, genPt) == 5 ) cout << "---> 5; electron from b                            " << endl;
          //if( matchToTruth( el, genParticles, genPt) == 6 ) cout << "---> 6; prompt photon (likely conversion)          " << endl;
          int ismatch = ( matchToTruth( el, genParticles, genPt) == 1 ) ? 1 : 0 ;
          Ele_isMatchTrue_.push_back(ismatch);
          Ele_genPt_.push_back(genPt);
    }
  } // end electrons loop


  //-------------------------------//
  //---- Fill MET Variables -------//
  //-------------------------------//

  // Saving PF,GEN MissingET info
  edm::Handle<edm::View<pat::MET> > pfMETHandle;
  iEvent.getByToken(pfMETToken_, pfMETHandle);
  if (pfMETHandle.isValid()) {
       const pat::MET *pfMET = 0;
       pfMET               = &(pfMETHandle->front());
       pfMET_              = pfMET->et();
       pfMET_Phi_          = pfMET->phi();
       pfMET_SumEt_        = pfMET->sumEt();
       pfMET_Significance_ = pfMET->metSignificance();

       genMET_              = (isData_) ? -999.0 : pfMET->genMET()->et();
       genMET_Phi_          = (isData_) ? -999.0 : pfMET->genMET()->phi();
       genMET_SumEt_        = (isData_) ? -999.0 : pfMET->genMET()->sumEt();
       genMET_Significance_ = (isData_) ? -999.0 : pfMET->genMET()->significance();

       pfMET_T1JERUp_       = pfMET->shiftedPt(pat::MET::JetResUp);
       pfMET_T1JERDo_       = pfMET->shiftedPt(pat::MET::JetResDown);
       pfMET_T1JESUp_       = pfMET->shiftedPt(pat::MET::JetEnUp);
       pfMET_T1JESDo_       = pfMET->shiftedPt(pat::MET::JetEnDown);
       pfMET_T1UESUp_       = pfMET->shiftedPt(pat::MET::UnclusteredEnUp);
       pfMET_T1UESDo_       = pfMET->shiftedPt(pat::MET::UnclusteredEnDown);
       pfMET_Phi_T1JESUp_   = pfMET->shiftedPhi(pat::MET::JetEnUp);
       pfMET_Phi_T1JESDo_   = pfMET->shiftedPhi(pat::MET::JetEnDown);
       pfMET_Phi_T1UESUp_   = pfMET->shiftedPhi(pat::MET::UnclusteredEnUp);
       pfMET_Phi_T1UESDo_   = pfMET->shiftedPhi(pat::MET::UnclusteredEnDown);
  }
  // Saving PUPPI MissingET info
  edm::Handle<edm::View<pat::MET> > puppiMETHandle;
  iEvent.getByToken(puppiMETToken_, puppiMETHandle);
  if (puppiMETHandle.isValid()) {
       const pat::MET *puppiMET = 0;
       puppiMET               = &(puppiMETHandle->front());
       puppiMET_              = puppiMET->et();
       puppiMET_Phi_          = puppiMET->phi();
       puppiMET_SumEt_        = puppiMET->sumEt();
       puppiMET_Significance_ = puppiMET->metSignificance();
  }

  //-------------------------------//
  //---- Fill Trigger Infos -------//
  //-------------------------------//

  HLTMuX_          = 0 ;  //HLTMuXIsPrescaled_  = 0;
  HLTMETX_         = 0 ;  //HLTMETXIsPrescaled_ = 0;
  HLTEleX_         = 0 ;  //HLTEleXIsPrescaled_ = 0;
  HLTPhoX_         = 0 ;  //HLTPhoXIsPrescaled_ = 0;

  isHLTEle30Pass_  = 0 ;
  isHLTEle35Pass_  = 0 ;
  isHLTEle115Pass_ = 0 ;
  isHLTPho175Pass_ = 0 ;
  isHLTPho200Pass_ = 0 ;
  isHLTPFMET120Pass_ = 0 ;
  isHLTPFMETNoMu120Pass_ = 0 ;
  isHLTMuPass_     = 0 ;
  isHLTMETPass_    = 0 ;

  istrgMatchTrue_.clear();
  int Nprint = 5;

  if(LoopNumber < Nprint ) cout << "\n == TRIGGER PATH = " << endl;

  edm::Handle<edm::TriggerResults> triggerResultsHandle;
  iEvent.getByToken(triggerResultsToken_, triggerResultsHandle);

//  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
//  iEvent.getByToken(triggerPrescalesToken_, triggerPrescales);

  const edm::TriggerNames &triggerNames = iEvent.triggerNames(*triggerResultsHandle);
  for (size_t i = 0; i < triggerNames.size(); ++i) {
    const string &name = triggerNames.triggerName(i);
    // HLT name => bit
    int bitMuX  = -1;
    int bitEleX = -1;
    int bitPhoX = -1;
    int bitMETX = -1;

    if(LoopNumber < Nprint) {
        cout << "Trigger " << triggerNames.triggerName(i) ;//<<", prescale " << triggerPrescales->getPrescaleForIndex(i)
        cout << ": " << (triggerResultsHandle->accept(i) ? "PASS" : "fail (or not run)") << endl;
    }
    if(triggerResultsHandle->accept(i)) { string pathName = triggerNames.triggerName(i);}

    // Single Mu triggers
    if (name.find("HLT_Mu8_TrkIsoVVL_v")        != string::npos) bitMuX = 0 ;
    else if (name.find("HLT_Mu8_v")             != string::npos) bitMuX = 1 ;
    else if (name.find("HLT_Mu12_IP6_v")        != string::npos) bitMuX = 2 ;
    else if (name.find("HLT_Mu15_v")            != string::npos) bitMuX = 3 ;
    else if (name.find("HLT_Mu17_TrkIsoVVL_v")  != string::npos) bitMuX = 4 ;
    else if (name.find("HLT_Mu17_v")            != string::npos) bitMuX = 5 ;
    else if (name.find("HLT_Mu19_TrkIsoVVL_v")  != string::npos) bitMuX = 6 ;
    else if (name.find("HLT_Mu19_v")            != string::npos) bitMuX = 7 ;
    else if (name.find("HLT_Mu20_v")            != string::npos) bitMuX = 8 ;
    else if (name.find("HLT_Mu27_v")            != string::npos) bitMuX = 9 ;
    else if (name.find("HLT_Mu50_v")            != string::npos) bitMuX = 10 ;
    else if (name.find("HLT_Mu55_v")            != string::npos) bitMuX = 11 ;
    else if (name.find("HLT_IsoMu20_v")         != string::npos) bitMuX = 12 ;
    else if (name.find("HLT_IsoMu24_eta2p1_v")  != string::npos) bitMuX = 13 ;
    else if (name.find("HLT_IsoMu24_v")         != string::npos) bitMuX = 14 ;
    else if (name.find("HLT_IsoMu27_v")         != string::npos) bitMuX = 15 ;
    else if (name.find("HLT_HighPtTkMu100_v")   != string::npos) bitMuX = 16 ;
    else if (name.find("HLT_TkMu100_v")         != string::npos) bitMuX = 17 ;   //only mc
    else if (name.find("HLT_OldMu100_v")        != string::npos) bitMuX = 18 ;   //only mc
    // Single Electron triggers
    if (name.find("HLT_Ele15_WPLoose_Gsf_v")              != string::npos) bitEleX = 0 ;
    else if (name.find("HLT_Ele17_WPLoose_Gsf_v")         != string::npos) bitEleX = 1 ;
    else if (name.find("HLT_Ele20_WPLoose_Gsf_v")         != string::npos) bitEleX = 2 ;
    else if (name.find("HLT_Ele20_eta2p1_WPLoose_Gsf_v")  != string::npos) bitEleX = 3 ;
    else if (name.find("HLT_Ele20_WPTight_Gsf_v")         != string::npos) bitEleX = 4 ;
    else if (name.find("HLT_Ele27_WPTight_Gsf_v")         != string::npos) bitEleX = 5 ;
    else if (name.find("HLT_Ele28_WPTight_Gsf_v")         != string::npos) bitEleX = 6 ;
    else if (name.find("HLT_Ele30_WPTight_Gsf_v")         != string::npos) bitEleX = 7 ;  // Ele30 reference etrigg
    else if (name.find("HLT_Ele32_WPTight_Gsf_v")         != string::npos) bitEleX = 8 ;
    else if (name.find("HLT_Ele35_WPTight_Gsf_v")         != string::npos) bitEleX = 9 ;
    else if (name.find("HLT_Ele35_WPTight_Gsf_L1EGMT_v")  != string::npos) bitEleX = 10 ;
    else if (name.find("HLT_Ele38_WPTight_Gsf_v")         != string::npos) bitEleX = 11 ;
    else if (name.find("HLT_Ele40_WPTight_Gsf_v")         != string::npos) bitEleX = 12 ;
    else if (name.find("HLT_Ele115_CaloIdVT_GsfTrkIdT_v") != string::npos) bitEleX = 13 ; //<-- W' trigger 115
    else if (name.find("HLT_Ele135_CaloIdVT_GsfTrkIdT_v") != string::npos) bitEleX = 14 ; //<-- W' OR trigger 135
    else if (name.find("HLT_ECALHT800_v")                 != string::npos) bitEleX = 15 ;
    // Single Photon triggers
    if (name.find("HLT_Photon50_v")             != string::npos) bitPhoX = 0 ;
    else if (name.find("HLT_Photon75_v")        != string::npos) bitPhoX = 1 ;
    else if (name.find("HLT_Photon90_v")        != string::npos) bitPhoX = 2 ;
    else if (name.find("HLT_Photon120_v")       != string::npos) bitPhoX = 3 ;
    else if (name.find("HLT_Photon150_v")       != string::npos) bitPhoX = 4 ;
    else if (name.find("HLT_Photon175_v")       != string::npos) bitPhoX = 5 ; //<-- W' trigger 175, prescaled 64
    else if (name.find("HLT_Photon200_v")       != string::npos) bitPhoX = 6 ; //<-- W' trigger 200
    else if (name.find("HLT_Photon300_NoHE_v")  != string::npos) bitPhoX = 7 ;
    // MET triggers
    if (name.find("HLT_CaloMET80_NotCleaned_v")                                 != string::npos) bitMETX = 0;
    else if (name.find("HLT_CaloMET100_NotCleaned_v")                           != string::npos) bitMETX = 1;
    else if (name.find("HLT_CaloMET250_NotCleaned_v")                           != string::npos) bitMETX = 2;
    else if (name.find("HLT_CaloMET300_NotCleaned_v")                           != string::npos) bitMETX = 3;
    else if (name.find("HLT_CaloMET350_NotCleaned_v")                           != string::npos) bitMETX = 4;
    else if (name.find("HLT_MET105_IsoTrk50_v")                                 != string::npos) bitMETX = 5;
    else if (name.find("HLT_MET120_IsoTrk50_v")                                 != string::npos) bitMETX = 6;
    else if (name.find("HLT_PFMET100_PFMHT100_IDTight_PFHT60_v")                != string::npos) bitMETX = 7;
    else if (name.find("HLT_PFMET105_IsoTrk50_v")                               != string::npos) bitMETX = 8;
    else if (name.find("HLT_PFMET110_PFMHT110_IDTight_v")                       != string::npos) bitMETX = 9;
    else if (name.find("HLT_PFMET120_PFMHT120_IDTight_PFHT60_v")                != string::npos) bitMETX = 10;
    else if (name.find("HLT_PFMET120_PFMHT120_IDTight_v")                       != string::npos) bitMETX = 11;//<-- W' OR trigger?
    else if (name.find("HLT_PFMET130_PFMHT130_IDTight_v")                       != string::npos) bitMETX = 12;
    else if (name.find("HLT_PFMET140_PFMHT140_IDTight_v")                       != string::npos) bitMETX = 13;
    else if (name.find("HLT_PFMET200_BeamHaloCleaned_v")                        != string::npos) bitMETX = 14;
    else if (name.find("HLT_PFMET200_NotCleaned_v")                             != string::npos) bitMETX = 15;
    else if (name.find("HLT_PFMET250_NotCleaned_v")                             != string::npos) bitMETX = 16;
    else if (name.find("HLT_PFMET300_NotCleaned_v")                             != string::npos) bitMETX = 17;
    else if (name.find("HLT_PFMETNoMu100_PFMHTNoMu100_IDTight_PFHT60_v")        != string::npos) bitMETX = 18;
    else if (name.find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_FilterHF_v")      != string::npos) bitMETX = 19;
    else if (name.find("HLT_PFMETNoMu110_PFMHTNoMu110_IDTight_v")               != string::npos) bitMETX = 20;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_FilterHF_v")      != string::npos) bitMETX = 21;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v")        != string::npos) bitMETX = 22;
    else if (name.find("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v")               != string::npos) bitMETX = 23;//<-- W' OR trigger?
    else if (name.find("HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_FilterHF_v")      != string::npos) bitMETX = 24;
    else if (name.find("HLT_PFMETNoMu130_PFMHTNoMu130_IDTight_v")               != string::npos) bitMETX = 25;
    else if (name.find("HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_FilterHF_v")      != string::npos) bitMETX = 26;
    else if (name.find("HLT_PFMETNoMu140_PFMHTNoMu140_IDTight_v")               != string::npos) bitMETX = 27;
    else if (name.find("HLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_v")         != string::npos) bitMETX = 28;
    else if (name.find("HLT_PFMETTypeOne110_PFMHT110_IDTight_v")                != string::npos) bitMETX = 29;
    else if (name.find("HLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_v")         != string::npos) bitMETX = 30;
    else if (name.find("HLT_PFMETTypeOne120_PFMHT120_IDTight_v")                != string::npos) bitMETX = 31;
    else if (name.find("HLT_PFMETTypeOne130_PFMHT130_IDTight_v")                != string::npos) bitMETX = 32;
    else if (name.find("HLT_PFMETTypeOne140_PFMHT140_IDTight_v")                != string::npos) bitMETX = 33;
    else if (name.find("HLT_PFMETTypeOne200_BeamHaloCleaned_v")                 != string::npos) bitMETX = 34;
    // Tau triggers: HLT_LooseDeepTauPFTauHPS180_L2NN_eta2p1_v:Run3 (HLT_MediumChargedIsoPFTau180HighPtRelaxedIso_Trk50_eta2p1_v:Run2)
    if (bitMuX > 0)   { isHLTMuPass_            = (triggerResultsHandle->accept(i)); }
    if (bitMETX > 0)  { isHLTMETPass_           = (triggerResultsHandle->accept(i)); }
    if (bitEleX == 7) { isHLTEle30Pass_         = (triggerResultsHandle->accept(i)); }
    if (bitEleX == 9) { isHLTEle35Pass_         = (triggerResultsHandle->accept(i)); }
    if (bitEleX == 13){ isHLTEle115Pass_        = (triggerResultsHandle->accept(i)); }
    if (bitPhoX == 5) { isHLTPho175Pass_        = (triggerResultsHandle->accept(i)); }
    if (bitPhoX == 6) { isHLTPho200Pass_        = (triggerResultsHandle->accept(i)); }
    if (bitMETX == 11){ isHLTPFMET120Pass_      = (triggerResultsHandle->accept(i)); }
    if (bitMETX == 23){ isHLTPFMETNoMu120Pass_  = (triggerResultsHandle->accept(i)); }
    //if ( name.find("HLT_Photon175_v") != std::string::npos){
    //    //cout << i << " " << name << " prescale " << triggerPrescales->getPrescaleForIndex(i) << endl;
    //    //pho175Prescale_ = triggerPrescales->getPrescaleForIndex(i) ;
    //}

    //indicates prescaling and whether trigger was fired or not
    //ULong64_t isPrescaled = (triggerPrescales->getPrescaleForIndex(i) !=1 ) ? 1 : 0 ;
    ULong64_t isFired     = (triggerResultsHandle->accept(i)) ? 1 : 0;
    if (bitMuX >= 0) {
      HLTMuX_            |= (isFired << bitMuX);
      //HLTMuXIsPrescaled_ |= (isPrescaled << bitMuX);
    }
    if (bitEleX >= 0) {
      HLTEleX_            |= (isFired << bitEleX);
      //HLTEleXIsPrescaled_ |= (isPrescaled << bitEleX);
    }
    if (bitPhoX >= 0) {
      HLTPhoX_            |= (isFired << bitPhoX);
      //HLTPhoXIsPrescaled_ |= (isPrescaled << bitPhoX);
    }
    if (bitMETX >= 0) {
      HLTMETX_            |= (isFired << bitMETX);
      //HLTMETXIsPrescaled_ |= (isPrescaled << bitMETX);
    }
  } // triggername  loop end

  //-------------------------------//
  //-- TriggerObject , Fill Trigger-Reco Matching--//
  //-------------------------------//
  // dPT < 0.5, dR < 0.3

  vector<float> trgSingleElePt[64], trgSingleEleEta[64], trgSingleElePhi[64];

  for (size_t i = 0; i < 64; ++i) {
    trgSingleElePt [i].clear();
    trgSingleEleEta[i].clear();
    trgSingleElePhi[i].clear();
  }

  static std::map<string,size_t> eleSingleFilters;

  if (eleSingleFilters.size() == 0) {
    //eleSingleFilters["hltEG175HEFilter"]                                                 = 0;
    //eleSingleFilters["hltEG200HEFilter"]                                                 = 1;
    //eleSingleFilters["hltEle115CaloIdVTGsfTrkIdTGsfDphiFilter"]                          = 2;
    //eleSingleFilters["hltEle135CaloIdVTGsfTrkIdTGsfDphiFilter"]                          = 3;
    eleSingleFilters["hltEG120HEFilter"]                                                 = 0;
    eleSingleFilters["hltEG120R9Id90HE10IsoMTrackIsoFilter"]                             = 1;
    eleSingleFilters["hltEG150HEFilter"]                                                 = 2;
    eleSingleFilters["hltEG165R9Id90HE10IsoMTrackIsoFilter"]                             = 3;
    eleSingleFilters["hltEG175HEFilter"]                                                 = 4;
    eleSingleFilters["hltEG18Iso60CaloId15b35eHE12R9Id50b80eTrackIsoUnseededLastFilter"] = 5;
    eleSingleFilters["hltEG18R9Id85b90eHE12R9Id50b80eR9UnseededLastFilter"]              = 6;
    eleSingleFilters["hltEG200HEFilter"]                                                 = 7;
    eleSingleFilters["hltEG27L1IsoEG22erORIsoEG24erORIsoEG24ORIsoEG26OREG40EtFilter"]    = 8;
    eleSingleFilters["hltEG300erEtFilter"]                                               = 9;
    eleSingleFilters["hltEG32L1SingleAndDoubleEGEtFilter"]                               = 10;
    eleSingleFilters["hltEG32L1SingleEGOrEtFilter"]                                      = 11;
    eleSingleFilters["hltEG33L1EG26HEFilter"]                                            = 12;
    eleSingleFilters["hltEG50HEFilter"]                                                  = 13;
    eleSingleFilters["hltEG50R9Id90HE10IsoMTrackIsoFilter"]                              = 14;
    eleSingleFilters["hltEG75HEFilter"]                                                  = 15;
    eleSingleFilters["hltEG75R9Id90HE10IsoMTrackIsoFilter"]                              = 16;
    eleSingleFilters["hltEG90HEFilter"]                                                  = 17;
    eleSingleFilters["hltEG90R9Id90HE10IsoMTrackIsoFilter"]                              = 18;
    eleSingleFilters["hltEGL1SingleEG40ORSingleIsoEG22erOrSingleIsoEG24erORSingleIsoEG24OrSingleIsoEG26Filter"] = 19;
    eleSingleFilters["hltEle115CaloIdVTGsfTrkIdTGsfDphiFilter"]                          = 20;
    eleSingleFilters["hltEle12CaloIdLTrackIdLIsoVLTrackIsoFilter"]                       = 21;
    eleSingleFilters["hltEle135CaloIdVTGsfTrkIdTGsfDphiFilter"]                          = 22;
    eleSingleFilters["hltEle15WPLooseGsfTrackIsoFilter"]                                 = 23;
    eleSingleFilters["hltEle17CaloIdLTrackIdLIsoVLTrackIsoFilter"]                       = 24;
    eleSingleFilters["hltEle20WPLooseGsfTrackIsoFilter"]                                 = 25;
    eleSingleFilters["hltEle22WPLooseL1SingleIsoEG20erGsfTrackIsoFilter"]                = 26;
    eleSingleFilters["hltEle23CaloIdLTrackIdLIsoVLTrackIsoFilter"]                       = 27;
    eleSingleFilters["hltEle24WPLooseL1IsoEG22erTau20erGsfTrackIsoFilter"]               = 28;
    eleSingleFilters["hltEle24WPLooseL1SingleIsoEG22erGsfTrackIsoFilter"]                = 29;
    eleSingleFilters["hltEle25erWPLooseGsfTrackIsoFilter"]                               = 30;
    eleSingleFilters["hltEle25erWPTightGsfTrackIsoFilter"]                               = 31;
    eleSingleFilters["hltEle25WP60SC4HcalIsoFilter"]                                     = 32;
    eleSingleFilters["hltEle25WPTightGsfTrackIsoFilter"]                                 = 33;
    eleSingleFilters["hltEle27erWPLooseGsfTrackIsoFilter"]                               = 34;
    eleSingleFilters["hltEle27erWPTightGsfTrackIsoFilter"]                               = 35;
    eleSingleFilters["hltEle27noerWPLooseGsfTrackIsoFilter"]                             = 36;
    eleSingleFilters["hltEle27WPLooseGsfTrackIsoFilter"]                                 = 37;
    eleSingleFilters["hltEle27WPTightGsfTrackIsoFilter"]                                 = 38;
    eleSingleFilters["hltEle27WPTightGsfTrackIsoL1TauJetSeededFilter"]                   = 39;
    eleSingleFilters["hltEle28WPTightGsfTrackIsoFilter"]                                 = 40;
    eleSingleFilters["hltEle30WPTightGsfTrackIsoFilter"]                                 = 41;
    eleSingleFilters["hltEle32noerWPTightGsfTrackIsoFilter"]                             = 42;
    eleSingleFilters["hltEle32WPTightGsfTrackIsoFilter"]                                 = 43;
    eleSingleFilters["hltEle35WPLooseGsfTrackIsoFilter"]                                 = 44;
    eleSingleFilters["hltEle38WPTightGsfTrackIsoFilter"]                                 = 45;
    eleSingleFilters["hltEle40WPTightGsfTrackIsoFilter"]                                 = 46;
    eleSingleFilters["hltEle45WPLooseGsfTrackIsoFilter"]                                 = 47;
    eleSingleFilters["hltEle8CaloIdLTrackIdLIsoVLTrackIsoFilter"]                        = 48;
    eleSingleFilters["hltHtEcal800"]                                                     = 49;
    eleSingleFilters["hltL1sSingleEG"]                                                   = 50;
    eleSingleFilters["hltL1sSingleEGNonIsoOrWithJetAndTau"]                              = 51;
    eleSingleFilters["hltL1sSingleEGor"]                                                 = 52;
    eleSingleFilters["hltL1sSingleJetAndTauHighPtOr"]                                    = 53;
    eleSingleFilters["hltOverlapFilterIsoEle24WPLooseGsfLooseIsoPFTau20"]                = 54;
    eleSingleFilters["hltOverlapFilterSingleIsoEle22WPLooseGsfLooseIsoPFTau20"]          = 55;
    eleSingleFilters["hltSingleEle22WPLooseGsfTrackIsoFilter"]                           = 56;
    eleSingleFilters["hltSingleEle24WPLooseGsfTrackIsoFilter"]                           = 57;
  }

  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjectsHandle;
  iEvent.getByToken(triggerObjectsToken_, triggerObjectsHandle);

  edm::Handle<std::string> filterLabels_;
  iEvent.getByLabel("slimmedPatTrigger:filterLabels", filterLabels_);

  double trgobj_ele_pt  = -999.0;
  double trgobj_ele_eta = -999.0;
  double trgobj_ele_phi = -999.0;
  double trgFilterDeltaPtCut_ = 0.5;
  double trgFilterDeltaRCut_  = 0.3;

  //start loop over trgobj
  for (pat::TriggerObjectStandAlone obj : *triggerObjectsHandle) {
     obj.unpackPathNames(triggerNames);
     obj.unpackFilterLabels(iEvent, *triggerResultsHandle);
     //cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << endl;
     //cout << "\t   Collection: " << obj.collection() << endl;

     //std::vector pathNamesAll = obj.pathNames(false);
     //std::vector pathNamesLast = obj.pathNames(true);
     //std::cout << "\t   Paths (" << pathNamesAll.size()<<"/"<<pathNamesLast.size()<<"):    ";

     //for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
     //     bool isBoth = obj.hasPathName( pathNamesAll[h], true, true );
     //     bool isL3   = obj.hasPathName( pathNamesAll[h], false, true );
     //     bool isLF   = obj.hasPathName( pathNamesAll[h], true, false );
     //     bool isNone = obj.hasPathName( pathNamesAll[h], false, false );
     //     std::cout << "   " << pathNamesAll[h];
     //     if (isBoth) std::cout << "(L,3)";
     //     if (isL3 && !isBoth) std::cout << "(*,3)";
     //     if (isLF && !isBoth) std::cout << "(L,*)";
     //     if (isNone && !isBoth && !isL3 && !isLF) std::cout << "(*,*)";
     //}
     //std::cout << std::endl;

     for (size_t iF = 0; iF < obj.filterLabels().size(); ++iF) {
        //if (obj.collection() != "hltEgammaCandidates::HLT") continue;
        string label = obj.filterLabels()[iF];
        //cout << "filterLabels " << label << endl;
        std::map<string,size_t>::iterator idxEleSingle = eleSingleFilters.find(label);

        if (idxEleSingle != eleSingleFilters.end()) {
           size_t idx = idxEleSingle->second;
           trgSingleElePt [idx].push_back(obj.pt());
           trgSingleEleEta[idx].push_back(obj.eta());
           trgSingleElePhi[idx].push_back(obj.phi());
           trgobj_ele_pt  = 1;
           //cout << " pass idxEleSingle != eleSingleFilters.end()i===========" <<  " trgobj_ele_pt " << trgobj_ele_pt << endl;
        }
     }
  }//trgObj loop over

//  if(trgobj_ele_pt > 0) trgobj_idx_.push_back(LoopNumber);
//  trgobj_ele_pt_.push_back(trgobj_ele_pt);
//  trgobj_ele_eta_.push_back(trgobj_ele_eta);
//  trgobj_ele_phi_.push_back(trgobj_ele_phi);
//
  double trgmatch_dPt  = -999;
  double trgmatch_dEta = -999;
  double trgmatch_dPhi = -999;
  double trgmatch_dR   = -999;
  int istrgMatchTrue = 0;

//  //fill trig matching required variables and istrgMatchTrue
//  if(ele_eta != -999 && trgobj_ele_eta != -999){
//     trgmatch_dPt_  = ele_pt  - trgobj_ele_pt  ;
//     trgmatch_dEta_ = ele_eta - trgobj_ele_eta ;
//     trgmatch_dPhi_ = ele_phi - trgobj_ele_phi ;
//     if (trgmatch_dPhi_ >  TMath::Pi()) trgmatch_dPhi_ -= 2.*TMath::Pi();
//     if (trgmatch_dPhi_ < -TMath::Pi()) trgmatch_dPhi_ += 2.*TMath::Pi();
//
//     trgmatch_dR_ = TMath::Sqrt( trgmatch_dEta_*trgmatch_dEta_ + trgmatch_dPhi_*trgmatch_dPhi_ );
//
//     if(abs(trgmatch_dPt_)/trgobj_ele_pt < trgFilterDeltaPtCut_  && trgmatch_dR_ < trgFilterDeltaRCut_ ) istrgMatchTrue = 1;
//  }
//  istrgMatchTrue_.push_back(istrgMatchTrue);

  if(trgobj_ele_pt > 0) {
     ULong64_t result = 0;
     for (size_t f = 0; f < 64; ++f)
       for (size_t v = 0; v < trgSingleElePt[f].size(); ++v)
         if (abs(ele_pt - trgSingleElePt[f][v])/trgSingleElePt[f][v] < trgFilterDeltaPtCut_ &&
             deltaR(ele_eta, ele_phi, trgSingleEleEta[f][v], trgSingleElePhi[f][v]) < trgFilterDeltaRCut_) {
             result |= (1ULL<<f);
             eleFiredSingleTrgs_.push_back(result);
             istrgMatchTrue = 1;
             trgobj_ele_pt  = trgSingleElePt[f][v];
             trgobj_ele_eta = trgSingleEleEta[f][v];
             trgobj_ele_phi = trgSingleElePhi[f][v];
             trgmatch_dR  = deltaR(ele_eta, ele_phi, trgSingleEleEta[f][v], trgSingleElePhi[f][v]) ;
             trgmatch_dPt  = ele_pt  - trgobj_ele_pt  ;
             trgmatch_dEta = ele_eta - trgobj_ele_eta ;
             trgmatch_dPhi = ele_phi - trgobj_ele_phi ;

//           cout << "f " << f << " v " << v << " pt " << ele_pt << " trgpt " << trgSingleElePt[f][v] << " eta " << ele_eta << " trgeta " << trgobj_ele_eta << " phi " << ele_phi << " trgphi  " << trgobj_ele_phi << endl;
//             cout << "======> eleFredSingleTrgs = result " << result << " istrgMatch " << istrgMatchTrue << endl;
             break;
         }
  }

//  cout << "####################################################################" << endl;
//  cout << "Final choice ===> trgobj_ele_pt " << trgobj_ele_pt << " trgobj_ele_eta " << trgobj_ele_eta << " trgobj_ele_phi " << trgobj_ele_phi << " istrgMatchTrue " << istrgMatchTrue << endl;
//  cout << "####################################################################" << endl;
  trgobj_ele_pt_.push_back(trgobj_ele_pt);
  trgobj_ele_eta_.push_back(trgobj_ele_eta);
  trgobj_ele_phi_.push_back(trgobj_ele_phi);
  trgmatch_dR_   = trgmatch_dR   ;
  trgmatch_dPt_  = trgmatch_dPt  ;
  trgmatch_dEta_ = trgmatch_dEta ;
  trgmatch_dPhi_ = trgmatch_dPhi ;
  istrgMatchTrue_.push_back(istrgMatchTrue);


  // Tree Fill
  tree_->Fill();
}

void
Run3Ntuplizer::beginJob(){}

void
Run3Ntuplizer::endJob(){}

void
Run3Ntuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

int Run3Ntuplizer::matchToTruth(const edm::Ptr<reco::GsfElectron> el,
          const edm::Handle<edm::View<reco::GenParticle>> &prunedGenParticles, float &genPt){
  // Explicit loop and geometric matching method (advised by Josh Bendavid)
  // Find the closest status 1 gen electron to the reco electron
  double dR = 999;
  const reco::Candidate *closestElectron = nullptr;
  for(size_t i=0; i<prunedGenParticles->size();i++){
    const reco::Candidate *particle = &(*prunedGenParticles)[i];
    // Drop everything that is not electron or not status 1
    if( abs(particle->pdgId()) != 11 || particle->status() != 1 )
      continue;
    double dRtmp = ROOT::Math::VectorUtil::DeltaR( el->p4(), particle->p4() );
    if( dRtmp < dR ){
      dR = dRtmp;
      closestElectron = particle;
    }
  }
  // See if the closest electron (if it exists) is close enough.
  // If not, no match found.

  if( !(closestElectron != nullptr && dR < 0.01) ) {
    return UNMATCHED;
  }

  genPt = closestElectron->pt();
  int ancestorPID = -999;
  int ancestorStatus = -999;
  findFirstNonElectronMother(closestElectron, ancestorPID, ancestorStatus);

  if( ancestorPID == -999 && ancestorStatus == -999 ){
    // No non-electron parent??? This should never happen.
    // Print out the complain.
    //printf("Run3Ntuplizer: ERROR! Electron does not apper to have a non-electron parent\n");
    return UNMATCHED; // 0
  }

//  (LOG) https://github.com/cms-sw/cmssw/blob/master/DataFormats/HepMCCandidate/interface/GenStatusFlags.h
//  https://github.com/cms-sw/cmssw/blob/master/PhysicsTools/NanoAOD/plugins/CandMCMatchTableProducer.cc
//      case MElectron:
//        flavDoc_ =
//            "1 = prompt electron (including gamma*->mu mu), 15 = electron from prompt tau, 22 = prompt photon (likely "
//            "conversion), "  // continues below
//            "5 = electron from b, 4 = electron from c, 3 = electron from light or unknown, 0 = unmatched";
//  isPrompt()                          //is particle prompt (not from hadron, muon, or tau decay)
//  isDecayedLeptonHadron()             //is particle a decayed hadron, muon, or tau (does not include resonance decays like W,Z,Higgs,top,etc)
//  isTauDecayProduct()                 //this particle is a direct or indirect tau decay product
//  isPromptTauDecayProduct()           //this particle is a direct or indirect decay product of a prompt tau
//  isDirectTauDecayProduct()           //this particle is a direct tau decay product
//  isDirectPromptTauDecayProduct()     //this particle is a direct decay product from a prompt tau
//  isDirectHadronDecayProduct()        //this particle is a direct decay product from a hadron
//  isHardProcess()                     //this particle is part of the hard process
//  fromHardProcess()                   //this particle is the direct descendant of a hard process particle of the same pdg id
//  isHardProcessTauDecayProduct()      //this particle is a direct or indirect decay product of a tau from the hard process
//  isDirectHardProcessTauDecayProduct()//this particle is a direct decay product of a tau from the hard process
//  fromHardProcessBeforeFSR()          //this particle is the direct descendant of a hard process particle of the same pdg id For outgoing particles the kinematics are those before QCD or QED FSR

  if( abs(ancestorPID) == 15 && ancestorStatus == 2) return TRUE_ELECTRON_FROM_TAU; // 2
  //if( closestElectron->isDirectPromptTauDecayProductFinalState()) return TRUE_ELECTRON_FROM_TAU; // 2
  //if( (abs(ancestorPID) == 4 || abs(ancestorPID) / 100 == 4 || abs(ancestorPID) / 1000 == 4  ) )   return TRUE_ELECTRON_FROM_C; // 4; electron from c
  if( (abs(ancestorPID) == 4 || abs(ancestorPID) / 100 == 4 || abs(ancestorPID) / 1000 == 4  ) )   return TRUE_ELECTRON_FROM_C; // 4; electron from c
  if( (abs(ancestorPID) == 5 || abs(ancestorPID) / 100 == 5 || abs(ancestorPID) / 1000 == 5  ) )   return TRUE_ELECTRON_FROM_B; // 5; electron from b
  if( abs(ancestorPID) > 50 && ancestorStatus == 2)  return TRUE_NON_PROMPT_ELECTRON; // 3
  //if( abs(ancestorPID) == 22 && ancestorStatus == 1)   return TRUE_PROMPT_PHOTON;   // 6; prompt photon (likely conversion)
  if( abs(ancestorPID) == 22 )   return TRUE_PROMPT_PHOTON;   // 6; prompt photon (likely conversion)

  // What remains is true prompt electrons
  return TRUE_PROMPT_ELECTRON; // 1

}

void Run3Ntuplizer::findFirstNonElectronMother(const reco::Candidate *particle, int &ancestorPID, int &ancestorStatus){

  if( particle == 0 ){
    printf("Run3Ntuplizer: ERROR! null candidate pointer, this should never happen\n");
    return;
  }

  // Is this the first non-electron parent? If yes, return, otherwise
  // go deeper into recursion
  if( abs(particle->pdgId()) == 11 ){
    findFirstNonElectronMother(particle->mother(0), ancestorPID, ancestorStatus);
  }else{
    ancestorPID = particle->pdgId();
    ancestorStatus = particle->status();
  }

  return;
}

//PhysicsTools/NanoAOD/plugins/VIDNestedWPBitmapProducer.cc
void Run3Ntuplizer::printAndsaveCutFlowResult(vid::CutFlowResult &cutflow){

  //printf("    CutFlow name= %s    decision is %d\n",
//       cutflow.cutFlowName().c_str(),
//       (int) cutflow.cutFlowPassed());
  int ncuts = cutflow.cutFlowSize();
//  printf(" Index                               cut name              isMasked    value-cut-upon     pass?\n");
//  for(int icut = 0; icut<ncuts; icut++){
//    printf("  %2d      %50s    %d        %f          %d\n", icut,
//         cutflow.getNameAtIndex(icut).c_str(), //cutname
//         (int)cutflow.isCutMasked(icut), //isMasked
//         cutflow.getValueCutUpon(icut), //value
//         (int)cutflow.getCutResultByIndex(icut));//pass?
//  }

   Ele_HEEP0cut_.push_back((int)cutflow.getCutResultByIndex(0))  ; //GsfEleMinEcalEtCut_0
   Ele_HEEP1cut_.push_back((int)cutflow.getCutResultByIndex(1))  ; //GsfEleSCEtaMultiRangeCut_0
   Ele_HEEP2cut_.push_back((int)cutflow.getCutResultByIndex(2))  ; //GsfEleEBEECut_0
   Ele_HEEP3cut_.push_back((int)cutflow.getCutResultByIndex(3))  ; //GsfEleEBEECut_1
   Ele_HEEP4cut_.push_back((int)cutflow.getCutResultByIndex(4))  ; //GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0
   Ele_HEEP5cut_.push_back((int)cutflow.getCutResultByIndex(5))  ; //GsfEleFull5x5E2x5OverE5x5WithSatCut_0
   Ele_HEEP6cut_.push_back((int)cutflow.getCutResultByIndex(6))  ; //GsfEleHadronicOverEMLinearCut_0
   Ele_HEEP7cut_.push_back((int)cutflow.getCutResultByIndex(7))  ; //GsfEleTrkPtIsoCut_0
   Ele_HEEP8cut_.push_back((int)cutflow.getCutResultByIndex(8))  ; //GsfEleEmHadD1IsoRhoCut_0
   Ele_HEEP9cut_.push_back((int)cutflow.getCutResultByIndex(9))  ; //GsfEleDxyCut_0
   Ele_HEEP10cut_.push_back((int)cutflow.getCutResultByIndex(10))  ; //GsfEleMissingHitsCut_0
   Ele_HEEP11cut_.push_back((int)cutflow.getCutResultByIndex(11))  ; //GsfEleEcalDrivenCut_0
   Ele_HEEP0cutVal_.push_back((float)cutflow.getValueCutUpon(0))  ; //GsfEleMinEcalEtCut_0
   Ele_HEEP1cutVal_.push_back((float)cutflow.getValueCutUpon(1))  ; //GsfEleSCEtaMultiRangeCut_0
   Ele_HEEP2cutVal_.push_back((float)cutflow.getValueCutUpon(2))  ; //GsfEleEBEECut_0
   Ele_HEEP3cutVal_.push_back((float)cutflow.getValueCutUpon(3))  ; //GsfEleEBEECut_1
   Ele_HEEP4cutVal_.push_back((float)cutflow.getValueCutUpon(4))  ; //GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0
   Ele_HEEP5cutVal_.push_back((float)cutflow.getValueCutUpon(5))  ; //GsfEleFull5x5E2x5OverE5x5WithSatCut_0
   Ele_HEEP6cutVal_.push_back((float)cutflow.getValueCutUpon(6))  ; //GsfEleHadronicOverEMLinearCut_0
   Ele_HEEP7cutVal_.push_back((float)cutflow.getValueCutUpon(7))  ; //GsfEleTrkPtIsoCut_0
   Ele_HEEP8cutVal_.push_back((float)cutflow.getValueCutUpon(8))  ; //GsfEleEmHadD1IsoRhoCut_0
   Ele_HEEP9cutVal_.push_back((float)cutflow.getValueCutUpon(9))  ; //GsfEleDxyCut_0
   Ele_HEEP10cutVal_.push_back((float)cutflow.getValueCutUpon(10)) ; //GsfEleMissingHitsCut_0
   Ele_HEEP11cutVal_.push_back((float)cutflow.getValueCutUpon(11)) ; //GsfEleEcalDrivenCut_0

/* Example of the output

DEBUG CutFlow, full info for candidate with pt=58.264584:
    CutFlow name= heepElectronID-HEEPV71    decision is 0
 Index                               cut name              isMasked    value-cut-upon     pass?
   0                                    GsfEleMinEcalEtCut_0    0        58.264587          1
   1                              GsfEleSCEtaMultiRangeCut_0    0        2.681049          0
   2                                         GsfEleEBEECut_0    0        0.082915          0
   3                                         GsfEleEBEECut_1    0        0.036590          1
   4                  GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0    0        0.029677          1
   5                   GsfEleFull5x5E2x5OverE5x5WithSatCut_0    0        1.434267          1
   6                         GsfEleHadronicOverEMLinearCut_0    0        60.346268          0
   7                                     GsfEleTrkPtIsoCut_0    0        0.000000          1
   8                                GsfEleEmHadD1IsoRhoCut_0    0        4.827967          1
   9                                          GsfEleDxyCut_0    0        0.004763          1
  10                                  GsfEleMissingHitsCut_0    0        0.000000          1
  11                                   GsfEleEcalDrivenCut_0    0        0.000000          0
DEBUG CutFlow, the result with cut GsfEleFull5x5SigmaIEtaIEtaWithSatCut_0 masked out
*/
}

double Run3Ntuplizer::deltaPhi(double phi1, double phi2) {

  double dPhi = phi1 - phi2;
  if (dPhi > TMath::Pi()) dPhi -= 2.*TMath::Pi();
  if (dPhi < -TMath::Pi()) dPhi += 2.*TMath::Pi();

  return dPhi;
  }

double Run3Ntuplizer::deltaR(double eta1, double phi1, double eta2, double phi2) {

  double dEta, dPhi ;
  dEta = eta1 - eta2;
  dPhi = deltaPhi(phi1, phi2);

  return sqrt(dEta*dEta+dPhi*dPhi);
  }

//define this as a plug-in
DEFINE_FWK_MODULE(Run3Ntuplizer);
