cmsenv
voms-proxy-init -voms cms -valid 100:00 -rfc
source /cvmfs/cms.cern.ch/crab3/crab.sh

./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-50to120_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-120to200_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-200to400_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-400to800_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-800to1500_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-1500to2500_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-2500to4000_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-4000to6000_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/DYto2E_MLL-6000_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/GJet_PT-15to6000_TuneCP5-Flat_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-120to170_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-170to300_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-300_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-1000to1400_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-1400to1800_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-1800to2400_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-2400to3200_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-3200_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
#./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-50to80_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM
#./cmsCondor.sh -py=makeTree_run3_post.py -nfiles=1 -arg=isMC=True -dataset=/QCD_PT-80to120_EMEnriched_TuneCP5_13p6TeV_pythia8/Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2/MINIAODSIM

# 2022 MC
#./cmsCondor.sh -py=makeTree.py -dataset=/TTTo2L2Nu_CP5_13p6TeV_powheg-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM -nfiles=1 -arg=isMC=True
#cmsCondor.sh -py=makeTree.py -dataset=/WJetsToLNu_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM -nfiles=1 -arg=isMC=True
#
## 2022 Data
./cmsCondor.sh -py=makeTree.py  -dataset=/Muon/Run2022C-PromptReco-v1/MINIAOD  -nfiles=10 -json=./Cert_Collisions2022_355100_360491_Golden.json -arg=isMC=False
#./cmsCondor.sh -py=makeTree.py  -dataset=/Muon/Run2022D-PromptReco-v1/MINIAOD  -nfiles=10 -json=./Cert_Collisions2022_355100_360491_Golden.json -arg=isMC=False
#./cmsCondor.sh -py=makeTree.py  -dataset=/Muon/Run2022D-PromptReco-v2/MINIAOD  -nfiles=10 -json=./Cert_Collisions2022_355100_360491_Golden.json -arg=isMC=False
#./cmsCondor.sh -py=makeTree.py  -dataset=/Muon/Run2022D-PromptReco-v3/MINIAOD  -nfiles=10 -json=./Cert_Collisions2022_355100_360491_Golden.json -arg=isMC=False
#./cmsCondor.sh -py=makeTree.py  -dataset=/Muon/Run2022E-PromptReco-v1/MINIAOD  -nfiles=10 -json=./Cert_Collisions2022_355100_360491_Golden.json -arg=isMC=False
#./cmsCondor.sh -py=makeTree.py  -dataset=/Muon/Run2022F-PromptReco-v1/MINIAOD  -nfiles=10 -json=./Cert_Collisions2022_355100_360491_Golden.json -arg=isMC=False
#======================================================
# 2018 UL MC
#cmsCondor.sh -py=makeTree_run2.py -dataset=/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM -nfiles=1 -arg=isMC=True
#cmsCondor.sh -py=makeTree_run2.py -dataset=/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM -nfiles=1 -arg=isMC=True

# 2018 UL Data
#cmsCondor.sh -py=makeTree_run2.py  -dataset=/SingleMuon/Run2018A-UL2018_MiniAODv2-v3/MINIAOD  -nfiles=10 -json=./Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt -arg=isMC=False
#cmsCondor.sh -py=makeTree_run2.py  -dataset=/SingleMuon/Run2018B-UL2018_MiniAODv2-v2/MINIAOD  -nfiles=10 -json=./Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt -arg=isMC=False
#cmsCondor.sh -py=makeTree_run2.py  -dataset=/SingleMuon/Run2018C-UL2018_MiniAODv2-v2/MINIAOD  -nfiles=10 -json=./Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt  -arg=isMC=False
#cmsCondor.sh -py=makeTree_run2.py  -dataset=/SingleMuon/Run2018D-UL2018_MiniAODv2-v3/MINIAOD  -nfiles=10 -json=./Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt -arg=isMC=False


 # how to check
#cmsCondor.sh -check=condor_WprimeToMuNu_M-1800_TuneCUETP8M1_13TeV-pythia8_D_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_D_MINIAODSIM_191115_151736/

#Dataset: /TTTo2L2Nu_CP5_13p6TeV_powheg-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM
#Creation time: 2022-06-30 13:58:41
#/store/mc/Run3Winter22MiniAOD/TTTo2L2Nu_CP5_13p6TeV_powheg-pythia8/MINIAODSIM/122X_mcRun3_2021_realistic_v9-v2/2550000/026b4aa4-fbe9-4d94-9ab9-03b9bd034451.root
#File size: 4.1099144e+09 (4.1GB) File size: 4109914400 (4.1GB) File type: EDM Number of events: 48776
#
#Dataset: /WJetsToLNu_TuneCP5_13p6TeV-madgraphMLM-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM
#Creation time: 2022-04-21 18:56:28
#/store/mc/Run3Winter22MiniAOD/WJetsToLNu_TuneCP5_13p6TeV-madgraphMLM-pythia8/MINIAODSIM/122X_mcRun3_2021_realistic_v9-v2/2820000/060c23a9-0fff-4f32-bbd5-129b748cdc6d.root
#File size: 2.19553133e+08 (219.6MB) File size: 219553133 (219.6MB) File type: EDM Number of events: 3625
#
#Dataset: /WtoLNu_NoTau_CP5_13p6TeV_amcatnloFXFX-pythia8/Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2/MINIAODSIM
#Creation time: 2022-08-11 19:21:53
#/store/mc/Run3Winter22MiniAOD/WtoLNu_NoTau_CP5_13p6TeV_amcatnloFXFX-pythia8/MINIAODSIM/122X_mcRun3_2021_realistic_v9-v2/2560000/005a71d1-7445-42f5-964d-b5b4dc53b924.root
#File size: 3.106147464e+09 (3.1GB) File size: 3106147464 (3.1GB) File type: EDM Number of events: 50217
#
#DATA ( GT : 124X_dataRun3_Prompt_v4)
#Dataset: /Muon/Run2022C-PromptReco-v1/MINIAOD
#Creation time: 2022-08-01 10:52:38
#/store/data/Run2022C/Muon/MINIAOD/PromptReco-v1/000/356/426/00000/66a38e5c-e248-41bb-8729-d2d486018e87.root
#
#Dataset: /Muon/Run2022D-PromptReco-v1/MINIAOD
#Creation time: 2022-08-17 21:37:44
#Dataset: /Muon/Run2022D-PromptReco-v2/MINIAOD
#Creation time: 2022-08-22 17:30:10
#Dataset: /Muon/Run2022D-PromptReco-v3/MINIAOD
#Creation time: 2022-09-04 17:09:34
#Dataset: /Muon/Run2022E-PromptReco-v1/MINIAOD
#Creation time: 2022-09-22 15:10:10
#Dataset: /Muon/Run2022F-PromptReco-v1/MINIAOD
#Creation time: 2022-10-16 07:26:02

#2018 Data
#Dataset: /SingleMuon/Run2018A-UL2018_MiniAODv2-v3/MINIAOD
#/store/data/Run2018A/SingleMuon/MINIAOD/UL2018_MiniAODv2-v3/2530000/002A113D-FB15-1341-A170-638E53A7261F.root
#Dataset: /SingleMuon/Run2018B-UL2018_MiniAODv2-v2/MINIAOD
#Dataset: /SingleMuon/Run2018C-UL2018_MiniAODv2-v2/MINIAOD
#Dataset: /SingleMuon/Run2018D-UL2018_MiniAODv2-v3/MINIAOD
#
#Dataset: /SingleMuon/Run2018C-UL2018_MiniAODv2_GT36-v2/MINIAOD
#Dataset: /SingleMuon/Run2018B-UL2018_MiniAODv2_GT36-v1/MINIAOD
#Dataset: /SingleMuon/Run2018A-UL2018_MiniAODv2_GT36-v1/MINIAOD
#Dataset: /SingleMuon/Run2018D-UL2018_MiniAODv2_GT36-v1/MINIAOD

#2018 UL MC
#Dataset: /TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM
#Dataset: /WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM
#Dataset: /WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM
#Dataset: /WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM
#Dataset: /WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM
#Dataset: /WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM
#Dataset: /WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM
#Dataset: /WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM
#Dataset: /WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM
#/store/mc/RunIISummer20UL18MiniAODv2/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/106X_upgrade2018_realistic_v16_L1v1-v2/2530000/1E119C31-A7B8-0A45-A42D-850C727777D8.root
