import FWCore.ParameterSet.Config as cms
import FWCore.PythonUtilities.LumiList as LumiList

from FWCore.ParameterSet.VarParsing import VarParsing
varOptions = VarParsing('analysis')
varOptions.register("isMC", False, VarParsing.multiplicity.singleton, VarParsing.varType.bool, "isMC" )
varOptions.parseArguments()

process = cms.Process('Ntuplizer')

# import standard configuration
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
#process.load('Configuration.StandardSequences.MagneticField_cff')
# NOTE: the pick the right global tag!
#    for Spring15 25ns MC: global tag is 'auto:run2_mc'
#    for Run 2 data: global tag is 'auto:run2_data'
#  as a rule, find the "auto" global tag in $CMSSW_RELEASE_BASE/src/Configuration/AlCa/python/autoCond.py
#  This auto global tag will look up the "proper" global tag
#  that is typically found in the DAS under the Configs for given datase
from Configuration.AlCa.GlobalTag import GlobalTag
from Configuration.AlCa.autoCond import autoCond

if (varOptions.isMC):
        process.GlobalTag.globaltag = '106X_upgrade2018_realistic_v16_L1v1' # for CMSSW 12_2_X MC production
        inputFileName = [
        'root://cms-xrd-global.cern.ch//store/mc/RunIISummer20UL18MiniAODv2/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/2530000/1E119C31-A7B8-0A45-A42D-850C727777D8.root'
        #'root://cms-xrdr.sdfarm.kr:1094//xrd/store/user/ycyang/store/mc/RunIIFall17MiniAODv2/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/80000/FEA44ADB-B776-E811-90C4-7CD30ACE2445.root',
]
        outputFileName = 'ntuple_mc2018.root'
        process.source = cms.Source("PoolSource", 
                                 fileNames = cms.untracked.vstring(inputFileName),
)
else:
        process.GlobalTag.globaltag = '106X_dataRun2_v37' #for CMSSW >= 12_4_3 PR data 2022
        inputFileName = [
        'root://cms-xrd-global.cern.ch//store/data/Run2018A/SingleMuon/MINIAOD/UL2018_MiniAODv2-v3/2530000/002A113D-FB15-1341-A170-638E53A7261F.root'
#        'file:/cms/ldap_home/jelee/work/Run32022PRdata/muon-runC-PR_test.root'
]
        outputFileName = 'ntuple_data2018.root'
        process.source = cms.Source("PoolSource", 
                                 fileNames = cms.untracked.vstring(inputFileName),
                                 lumisToProcess = LumiList.LumiList(filename = 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt').getVLuminosityBlockRange()
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
#process.TFileService = cms.Service("TFileService", fileName = cms.string('electronTree.root') )
process.TFileService = cms.Service("TFileService", fileName = cms.string(outputFileName) )

print ("### isMC ", varOptions.isMC                      )
print ("### GlobalTag ", process.GlobalTag.globaltag     )
print ("### InFileName ", process.source.fileNames       )
print ("### OutFileName ", process.TFileService.fileName )

# set up electron ID (VID framework)
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V2_cff',
                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV71_cff']

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


# Configure the ntuple module

if (varOptions.isMC):
        process.ntuple = cms.EDAnalyzer('Run3Ntuplizer',
                                 # The module automatically detects AOD vs miniAOD, so we configure both
                                 # Common to all formats objects
                                 pileup   = cms.InputTag("slimmedAddPileupInfo"),
                                 rho      = cms.InputTag("fixedGridRhoFastjetAll"),
                                 beamSpot = cms.InputTag('offlineBeamSpot'),
                                 genEventInfoProduct = cms.InputTag('generator'),
                                 # Objects specific to MiniAOD format
                                 electrons    = cms.InputTag("slimmedElectrons"),
                                 genParticles = cms.InputTag("prunedGenParticles"),
                                 vertices     = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                 conversions  = cms.InputTag('reducedEgamma:reducedConversions'),
                                 eleIdMap_Cut94V2_Veto   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-veto"),
                                 eleIdMap_Cut94V2_Loose  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-loose"),
                                 eleIdMap_Cut94V2_Medium = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-medium"),
                                 eleIdMap_Cut94V2_Tight  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-tight"),
                                 eleIdMap_HEEPV71        = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV71"),
                                 eleIdFullInfoMap        = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV71"),
                                 eleIdVerbose = cms.bool(True),
                                 # Effective areas for computing PU correction for isolations
                                 effAreasConfigFile = cms.FileInPath("MakeNtuple/Run3Ntuplizer/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt"),
	                         triggerResults = cms.InputTag("TriggerResults","","HLT"),
	                         triggerObjects = cms.InputTag("slimmedPatTrigger"),
	                         triggerPrescales = cms.InputTag("patTrigger"),
	                         triggerIdentifiers = cms.vstring(['HLT_Ele*','HLT_Mu*','HLT_TkMu*']),
	                         triggerLabelsName  = cms.vstring(),
                                 # Objects specific to AOD format
                                 #pileup       = cms.InputTag("addPileupInfo"),
                                 #electrons    = cms.InputTag("gedGsfElectrons"),
                                 #genParticles = cms.InputTag("genParticles"),
                                 #vertices     = cms.InputTag("offlinePrimaryVertices"),
                                 #conversions  = cms.InputTag('allConversions'),
                                 )
else:
        process.ntuple = cms.EDAnalyzer('Run3Ntuplizer',
                                 rho      = cms.InputTag("fixedGridRhoFastjetAll"),
                                 beamSpot = cms.InputTag('offlineBeamSpot'),
                                 electrons    = cms.InputTag("slimmedElectrons"),
                                 vertices     = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                 conversions  = cms.InputTag('reducedEgamma:reducedConversions'),
                                 eleIdMap_HEEPV71        = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV71"),
                                 eleIdMap_Cut94V2_Tight  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-tight"),
                                 eleIdMap_Cut94V2_Medium = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-medium"),
                                 eleIdMap_Cut94V2_Loose  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-loose"),
                                 eleIdMap_Cut94V2_Veto   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V2-veto"),
                                 eleIdFullInfoMap = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV71"),
                                 eleIdVerbose = cms.bool(True),
                                 effAreasConfigFile = cms.FileInPath("MakeNtuple/Run3Ntuplizer/data/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt"),
                                 triggerResults = cms.InputTag("TriggerResults","","HLT"),
                                 triggerObjects = cms.InputTag("slimmedPatTrigger"),
                                 triggerPrescales = cms.InputTag("patTrigger"),
                                 triggerIdentifiers = cms.vstring(['HLT_Ele*','HLT_Mu*','HLT_TkMu*']),
                                 triggerLabelsName  = cms.vstring(),
                                 )
process.p = cms.Path(process.egmGsfElectronIDSequence * process.ntuple)
