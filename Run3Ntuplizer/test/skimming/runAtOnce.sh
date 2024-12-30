export LD_LIBRARY_PATH=${CMSSW_BASE}/src:${LD_LIBRARY_PATH}
g++ `root-config --cflags` `root-config --libs` makeHist.cc -L${CMSSW_BASE}/src -o makeHist.exe
g++ `root-config --cflags` `root-config --libs` makeAlpha.cc -L${CMSSW_BASE}/src -o makeAlpha.exe

#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v1-v1_D_MINIAOD_240323_035236/condorOut/ heff_23Muon0_ReReco_Cv1_mergebins1.root  >& sum_23Muon_ReReco_Cv1_mergebins1.log
#echo "DONE Eff ==> (1/12)./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v1-v1_D_MINIAOD_240323_035236/condorOut/ heff_23Muon0_ReReco_Cv1_mergebins1.root  >& sum_23Muon_ReReco_Cv1_mergebins1.log"
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v2-v1_D_MINIAOD_240323_035302/condorOut/ heff_23Muon0_ReReco_Cv2_mergebins1.root  >& sum_23Muon_ReReco_Cv2_mergebins1.log  
#echo "DONE Eff ==> (2/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v2-v1_D_MINIAOD_240323_035302/condorOut/ heff_23Muon0_ReReco_Cv2_mergebins1.root  >& sum_23Muon_ReReco_Cv2_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v3-v1_D_MINIAOD_240323_035323/condorOut/ heff_23Muon0_ReReco_Cv3_mergebins1.root  >& sum_23Muon_ReReco_Cv3_mergebins1.log  
#echo "DONE Eff ==> (3/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v3-v1_D_MINIAOD_240323_035323/condorOut/ heff_23Muon0_ReReco_Cv3_mergebins1.root  >& sum_23Muon_ReReco_Cv3_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v4-v1_D_MINIAOD_240323_035344/condorOut/ heff_23Muon0_ReReco_Cv4_mergebins1.root  >& sum_23Muon_ReReco_Cv4_mergebins1.log  
#echo "DONE EFF ==> (4/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023C-22Sep2023_v4-v1_D_MINIAOD_240323_035344/condorOut/ heff_23Muon0_ReReco_Cv4_mergebins1.root  >& sum_23Muon_ReReco_Cv4_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023D-22Sep2023_v1-v1_D_MINIAOD_240330_024947/condorOut/ heff_23Muon0_ReReco_Dv1_mergebins1.root  >& sum_23Muon_ReReco_Dv1_mergebins1.log  
#echo "DONE Eff ==> (5/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023D-22Sep2023_v1-v1_D_MINIAOD_240330_024947/condorOut/ heff_23Muon0_ReReco_Dv1_mergebins1.root  >& sum_23Muon_ReReco_Dv1_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023D-22Sep2023_v2-v1_D_MINIAOD_240330_025101/condorOut/ heff_23Muon0_ReReco_Dv2_mergebins1.root  >& sum_23Muon_ReReco_Dv2_mergebins1.log  
#echo "DONE Eff ==> (6/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon0_D_Run2023D-22Sep2023_v2-v1_D_MINIAOD_240330_025101/condorOut/ heff_23Muon0_ReReco_Dv2_mergebins1.root  >& sum_23Muon_ReReco_Dv2_mergebins1.log  "
#                                                                                                                                                                                                                                              
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v1-v1_D_MINIAOD_240323_035408/condorOut/ heff_23Muon1_ReReco_Cv1_mergebins1.root  >& sum_23Muon_ReReco_Cv1_mergebins1.log  
#echo "DONE Eff ==> (7/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v1-v1_D_MINIAOD_240323_035408/condorOut/ heff_23Muon1_ReReco_Cv1_mergebins1.root  >& sum_23Muon_ReReco_Cv1_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v2-v1_D_MINIAOD_240323_035423/condorOut/ heff_23Muon1_ReReco_Cv2_mergebins1.root  >& sum_23Muon_ReReco_Cv2_mergebins1.log  
#echo "DONE Eff ==> (8/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v2-v1_D_MINIAOD_240323_035423/condorOut/ heff_23Muon1_ReReco_Cv2_mergebins1.root  >& sum_23Muon_ReReco_Cv2_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v3-v1_D_MINIAOD_240323_035442/condorOut/ heff_23Muon1_ReReco_Cv3_mergebins1.root  >& sum_23Muon_ReReco_Cv3_mergebins1.log  
#echo "DONE Eff ==> (9/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v3-v1_D_MINIAOD_240323_035442/condorOut/ heff_23Muon1_ReReco_Cv3_mergebins1.root  >& sum_23Muon_ReReco_Cv3_mergebins1.log  "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v4-v1_D_MINIAOD_240323_035454/condorOut/ heff_23Muon1_ReReco_Cv4_mergebins1.root  >& sum_23Muon_ReReco_Cv4_mergebins1.log  
#echo "DONE Eff ==> (10/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023C-22Sep2023_v4-v1_D_MINIAOD_240323_035454/condorOut/ heff_23Muon1_ReReco_Cv4_mergebins1.root  >& sum_23Muon_ReReco_Cv4_mergebins1.log  "

./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023D-22Sep2023_v1-v1_D_MINIAOD_240330_025116/condorOut/ heff_23Muon1_ReReco_Dv1_mergebins1.root  >& sum_23Muon_ReReco_Dv1_mergebins1.log  
echo "DONE Eff ==> (11/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023D-22Sep2023_v1-v1_D_MINIAOD_240330_025116/condorOut/ heff_23Muon1_ReReco_Dv1_mergebins1.root  >& sum_23Muon_ReReco_Dv1_mergebins1.log  "
./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023D-22Sep2023_v2-v1_D_MINIAOD_240330_025134/condorOut/ heff_23Muon1_ReReco_Dv2_mergebins1.root  >& sum_23Muon_ReReco_Dv2_mergebins1.log  
echo "DONE Eff ==> (12/12) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2023/Muon/condor_Muon1_D_Run2023D-22Sep2023_v2-v1_D_MINIAOD_240330_025134/condorOut/ heff_23Muon1_ReReco_Dv2_mergebins1.root  >& sum_23Muon_ReReco_Dv2_mergebins1.log  "

./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/preEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2_D_MINIAODSIM_240321_174906/condorOut/ heff_22MC_preEE.root >& sum_22MC_preEE_mergebins1.log
echo "DONE Eff ==> (1/4 mc) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/preEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2_D_MINIAODSIM_240321_174906/condorOut/ heff_22MC_preEE.root >& sum_22MC_preEE_mergebins1.log"

./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/postEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2_D_MINIAODSIM_240321_175015/condorOut/  heff_22MC_postEE.root >& sum_22MC_postEE_mergebins1.log
echo "DONE Eff ==> (2/4 mc)./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/postEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2_D_MINIAODSIM_240321_175015/condorOut/  heff_22MC_postEE.root >& sum_22MC_postEE_mergebins1.log"

./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2_D_MINIAODSIM_240323_035511/condorOut/ heff_23MC_preBPIX.root >& sum_23MC_preBPIX_mergebins1.log
echo "DONE Eff ==> (3/4 mc) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2_D_MINIAODSIM_240323_035511/condorOut/ heff_23MC_preBPIX.root >& sum_23MC_preBPIX_mergebins1.log"

./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v3_D_MINIAODSIM_240330_025149/condorOut/ heff_23MC_postBPIX.root >& sum_23MC_postBPIX_mergebins1.log
echo "DONE Eff ==> (4/4 mc) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v3_D_MINIAODSIM_240330_025149/condorOut/ heff_23MC_postBPIX.root >& sum_23MC_postBPIX_mergebins1.log"


#2022 alpha MC
./makeAlpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/preEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2_D_MINIAODSIM_240321_174906/condorOut/ halpha_22MC_preEE.root >& sum_alpha_22MC_preEE.log 
echo "DONE As 22pre ==>./get_alpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/preEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv4-130X_mcRun3_2022_realistic_v5-v2_D_MINIAODSIM_240321_174906/condorOut/ heff_22MC_preEE_alpha.root >& sum_22MC_preEE_alpha.log "

./makeAlpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/postEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2_D_MINIAODSIM_240321_175015/condorOut/  halpha_22MC_postEE.root >& sum_alpha_22MC_postEE.log 
echo "DONE As 22post ==> ./get_alpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2022/124X_2023Sep/postEE/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv4-130X_mcRun3_2022_realistic_postEE_v6-v2_D_MINIAODSIM_240321_175015/condorOut/  heff_22MC_postEE_alpha.root >& sum_22MC_postEE_alpha.log "

#2023 alpha MC preBPIX :
./makeAlpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2_D_MINIAODSIM_240323_035511/condorOut/ halpha_23MC_preBPIX.root >& sum_alpha_23MC_preBPIX.log
echo "DONE As 23pre ==> ./makeAlpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2_D_MINIAODSIM_240323_035511/condorOut/ halpha_23MC_preBPIX.root >& sum_alpha_23MC_preBPIX.log"
./makeAlpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v3_D_MINIAODSIM_240330_025149/condorOut/ halpha_23MC_postBPIX.root >& sum_alpha_23MC_postBPIX.log
echo "DONE As 23post ==> ./makeAlpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v3_D_MINIAODSIM_240330_025149/condorOut/ halpha_23MC_postBPIX.root >& sum_alpha_23MC_postBPIX.log"

#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022C-22Sep2023-v1_D_MINIAOD_240314_050032/condorOut/  heff_22Muon_ReReco_C_mergebins1.root  >& sum_22Muon_ReReco_C_mergebins1.log 
#echo "DONE Eff==> (1/5 DATAs) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022C-22Sep2023-v1_D_MINIAOD_240314_050032/condorOut/  heff_22Muon_ReReco_C_mergebins1.root  >& sum_22Muon_ReReco_C_mergebins1.log "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022D-22Sep2023-v1_D_MINIAOD_240314_050051/condorOut/  heff_22Muon_ReReco_D_mergebins1.root  >& sum_22Muon_ReReco_D_mergebins1.log 
#echo "DONE==> (2/5 DATAs) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022D-22Sep2023-v1_D_MINIAOD_240314_050051/condorOut/  heff_22Muon_ReReco_D_mergebins1.root  >& sum_22Muon_ReReco_D_mergebins1.log "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022E-22Sep2023-v1_D_MINIAOD_240314_050103/condorOut/  heff_22Muon_ReReco_E_mergebins1.root  >& sum_22Muon_ReReco_E_mergebins1.log 
#echo "DONE Eff==> (3/5 DATAs) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022E-22Sep2023-v1_D_MINIAOD_240314_050103/condorOut/  heff_22Muon_ReReco_E_mergebins1.root  >& sum_22Muon_ReReco_E_mergebins1.log "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022F-22Sep2023-v2_D_MINIAOD_240314_050114/condorOut/  heff_22Muon_ReReco_F_mergebins1.root  >& sum_22Muon_ReReco_F_mergebins1.log 
#echo "DONE Eff==> (4/5 DATAs) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022F-22Sep2023-v2_D_MINIAOD_240314_050114/condorOut/  heff_22Muon_ReReco_F_mergebins1.root  >& sum_22Muon_ReReco_F_mergebins1.log "
#
#./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022G-22Sep2023-v1_D_MINIAOD_240314_050127/condorOut/  heff_22Muon_ReReco_G_mergebins1.root  >& sum_22Muon_ReReco_G_mergebins1.log 
#echo "DONE Eff==> (5/5 DATAs) ./makeHist.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022G-22Sep2023-v1_D_MINIAOD_240314_050127/condorOut/  heff_22Muon_ReReco_G_mergebins1.root  >& sum_22Muon_ReReco_G_mergebins1.log "
#0719

#2023 preBPIX :
#./get_alpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23MiniAODv4-130X_mcRun3_2023_realistic_v14-v2_D_MINIAODSIM_240323_035511/condorOut/ heff_23MC_preBPIX_alpha.root >& sum_23MC_preBPIX_alpha.log
#2023 postBPIX:
#./get_alpha.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/mc2023/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer23BPixMiniAODv4-130X_mcRun3_2023_realistic_postBPix_v2-v3_D_MINIAODSIM_240330_025149/condorOut/ heff_23MC_postBPIX_alpha.root >& sum_23MC_postBPIX_alpha.log

#0412 final
#g++ `root-config --cflags` `root-config --libs` drop_check.cc -L${CMSSW_BASE}/src -o drop_check.exe

#./efficiency_2023.exe ../condor_Muon0_D_Run2023C-PromptReco-v4_D_MINIAOD_230823_134504/condorOut/  heff_Mu0_23C-v4.root >&  sum_Mu0_23C-v4.log   
#./efficiency_2023.exe ../condor_Muon1_D_Run2023C-PromptReco-v4_D_MINIAOD_230823_134619/condorOut/  heff_Mu1_23C-v4.root >&  sum_Mu1_23C-v4.log   
#./efficiency_2023.exe ../condor_Muon0_D_Run2023D-PromptReco-v1_D_MINIAOD_230823_134637/condorOut/  heff_Mu0_23D-v1.root >&  sum_Mu0_23D-v1.log   
#./efficiency_2023.exe ../condor_Muon1_D_Run2023D-PromptReco-v1_D_MINIAOD_230823_134654/condorOut/  heff_Mu1_23D-v1.root >&  sum_Mu1_23D-v1.log   
#./efficiency_2023.exe ../condor_Muon0_D_Run2023D-PromptReco-v2_D_MINIAOD_230823_134803/condorOut/  heff_Mu0_23D-v2.root >&  sum_Mu0_23D-v2.log   
#./efficiency_2023.exe ../condor_Muon1_D_Run2023D-PromptReco-v2_D_MINIAOD_230823_134820/condorOut/  heff_Mu1_23D-v2.root >&  sum_Mu1_23D-v2.log   

#./efficiency_2023.exe /d0/scratch/jelee/Run3HLT/2023March/CMSSW_12_4_16/src/SimpleNtuplizer/Run3Ntuplizer/test/condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_231114_050109/condorOut/ heff_Mu_22F-DPupdate_full.root >&  sum_Mu_22F-DPupdate_full.log

#./efficiency_2023.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022C-22Sep2023-v1_D_MINIAOD_240314_050032/condorOut/ heff_Mu_22C.root  >& sum_Mu_22C.log  
#./efficiency_2023.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022D-22Sep2023-v1_D_MINIAOD_240314_050051/condorOut/ heff_Mu_22D.root  >& sum_Mu_22D.log  
#./efficiency_2023.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022E-22Sep2023-v1_D_MINIAOD_240314_050103/condorOut/ heff_Mu_22E.root  >& sum_Mu_22E.log  
#./efficiency_2023.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022F-22Sep2023-v2_D_MINIAOD_240314_050114/condorOut/ heff_Mu_22F.root  >& sum_Mu_22F.log  
#./efficiency_2023.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/13p6TeV/data2022/Muon_ReReco-22Sep2023/condor_Muon_D_Run2022G-22Sep2023-v1_D_MINIAOD_240314_050127/condorOut/ heff_Mu_22G.root  >& sum_Mu_22G.log  










#./efficiency_2023_divideRun.exe ../condor_Muon0_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112250/condorOut/ heff_Mu0_23C-PR4_Run368557_JEC.root 368557 9999999 >& sum_Mu0_23C-PR4_Run368557_JEC.log  
#./efficiency_2023_divideRun.exe ../condor_Muon1_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112302/condorOut/ heff_Mu1_23C-PR4_Run368557_JEC.root 368557 9999999 >& sum_Mu1_23C-PR4_Run368557_JEC.log 
#
#./efficiency_2023_divideRun.exe ../condor_Muon0_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112250/condorOut/ heff_Mu0_23C-PR4_Run367990_MuAl.root 367990 368557 >& sum_Mu0_23C-PR4_Run367990_MuAl.log  
#./efficiency_2023_divideRun.exe ../condor_Muon1_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112302/condorOut/ heff_Mu1_23C-PR4_Run367990_MuAl.root 367990 368557 >& sum_Mu1_23C-PR4_Run367990_MuAl.log 
#
#./efficiency_2023_divideRun.exe ../condor_Muon0_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112250/condorOut/ heff_Mu0_23C-PR4_Run367765_SC.root 367765 367990 >& sum_Mu0_23C-PR4_Run367765_SC.log  
#./efficiency_2023_divideRun.exe ../condor_Muon1_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112302/condorOut/ heff_Mu1_23C-PR4_Run367765_SC.root 367765 367990 >& sum_Mu1_23C-PR4_Run367765_SC.log 

#./efficiency_2023_divideRun.exe ../condor_Muon0_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112250/condorOut/ heff_Mu0_23C-PR4_Run367661_HCALSC.root 367661 367990 >& sum_Mu0_23C-PR4_Run367661_HCALSC.log  
#./efficiency_2023_divideRun.exe ../condor_Muon1_D_Run2023C-PromptReco-v4_D_MINIAOD_230709_112302/condorOut/ heff_Mu1_23C-PR4_Run367661_HCALSC.root 367661 367990 >& sum_Mu1_23C-PR4_Run367661_HCALSC.log 

#./efficiency_2023_divideRun.exe ../condor_Muon1_D_Run2023C-PromptReco-v1_D_MINIAOD_230531_010610/condorOut/ heff_Mu1_23C-PR1_beforeV11.root 0 9999999  >& sum_Mu1_23C-PR1_beforeV11.log 
#./efficiency_2023_divideRun.exe ../condor_Muon1_D_Run2023C-PromptReco-v2_D_MINIAOD_230531_010621/condorOut/ heff_Mu1_23C-PR2_beforeV11.root 0 9999999  >& sum_Mu1_23C-PR2_beforeV11.log 


#no ./efficiency_2023.exe ../condor_Muon1_D_Run2023B-PromptReco-v1_D_MINIAOD_230709_112110/condorOut/ heff_Mu1_23B-PR1.root >& sum_Mu1_23B-PR1.log 
#no ./efficiency_2023.exe ../condor_Muon0_D_Run2023B-PromptReco-v1_D_MINIAOD_230709_230719/condorOut/ heff_Mu0_23B-PR1.root >& sum_Mu0_23B-PR1.log 
#no ./efficiency_2023.exe ../condor_Muon1_D_Run2023D-PromptReco-v1_D_MINIAOD_230709_112325/condorOut/ heff_Mu1_23D-PR1.root >& sum_Mu1_23D-PR1.log 
#no ./efficiency_2023.exe ../condor_Muon0_D_Run2023D-PromptReco-v1_D_MINIAOD_230709_112315/condorOut/ heff_Mu0_23D-PR1.root >& sum_Mu0_23D-PR1.log 
#no ./efficiency_2023.exe ../condor_Muon0_D_Run2023C-PromptReco-v1_D_MINIAOD_230709_230731/condorOut/ heff_Mu0_23C-PR1.root >& sum_Mu0_23C-PR1.log 
#no ./efficiency_2023.exe ../condor_Muon0_D_Run2023C-PromptReco-v2_D_MINIAOD_230709_230745/condorOut/ heff_Mu0_23C-PR2.root >& sum_Mu0_23C-PR2.log 
#no ./efficiency_2023.exe ../condor_Muon0_D_Run2023C-PromptReco-v3_D_MINIAOD_230709_112227/condorOut/ heff_Mu0_23C-PR3.root >& sum_Mu0_23C-PR3.log 
#no ./efficiency_2023.exe ../condor_Muon1_D_Run2023C-PromptReco-v3_D_MINIAOD_230709_112238/condorOut/ heff_Mu1_23C-PR3.root >& sum_Mu1_23C-PR3.log 








#./efficiency_2023.exe ../condor_Muon1_D_Run2023B-PromptReco-v1_D_MINIAOD_230518_193631/condorOut/       heff_Muon2023B1_2023.root >& sum_Muon2023B1_2023.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022C-PromptReco-v1_D_MINIAOD_230404_024950/condorOut/        heff_Muon2022C1_new.root >& sum_Muon2022C1_new.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022D-PromptReco-v1_D_MINIAOD_230404_025022/condorOut/        heff_Muon2022D1_new.root >& sum_Muon2022D1_new.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022D-PromptReco-v2_D_MINIAOD_230404_025159/condorOut/        heff_Muon2022D2_new.root >& sum_Muon2022D2_new.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022D-PromptReco-v3_D_MINIAOD_230404_025426/condorOut/        heff_Muon2022D3_new.root >& sum_Muon2022D3_new.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022E-PromptReco-v1_D_MINIAOD_230403_223453/condorOut/        heff_Muon2022E1_new.root >& sum_Muon2022E1_new.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_230403_223506/condorOut/        heff_Muon2022F1_new.root >& sum_Muon2022F1_new.log 
#./efficiency_new.exe ../condor_Muon_D_Run2022G-PromptReco-v1_D_MINIAOD_230403_223547/condorOut/        heff_Muon2022G1_new.root >& sum_Muon2022G1_new.log
#./efficiency_new.exe ../condor_SingleMuon_D_Run2022B-PromptReco-v1_D_MINIAOD_230404_024907/condorOut/  heff_Muon2022B1_new.root >& sum_Muon2022B1_new.log 

#./drop_check.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022E-PromptReco-v1_D_MINIAOD_221104_233352/condorOut/ >& dropcheck.log

#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022C-PromptReco-v1_D_MINIAOD_221102_212157/condorOut/ heff_MuonC_0412.root >& sum_C_0412.log

#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022D-PromptReco-v1_D_MINIAOD_221103_151105/condorOut/ heff_MuonD1_0412.root >& sum_D1_0412.log
#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022D-PromptReco-v2_D_MINIAOD_221103_151141/condorOut/ heff_MuonD2_0412.root >& sum_D2_0412.log
#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022D-PromptReco-v3_D_MINIAOD_221104_162835/condorOut/ heff_MuonD3_0412.root >& sum_D3_0412.log
#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022E-PromptReco-v1_D_MINIAOD_221104_233352/condorOut/ heff_MuonE_0412.root >& sum_E_0412.log
#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_221104_233518/condorOut/ heff_MuonF_0412.root >& sum_F_0412.log
#./efficiency_final.exe /pnfs/knu.ac.kr/data/cms/store/user/jelee/ntuples/condor_Muon_D_Run2022G-PromptReco-v1_D_MINIAOD_230308_014158/condorOut/ heff_MuonG_0412.root >& sum_G_0412.log

#condor_Muon_D_Run2022C-PromptReco-v1_D_MINIAOD_221102_212157/
#condor_Muon_D_Run2022D-PromptReco-v1_D_MINIAOD_221103_151105/
#condor_Muon_D_Run2022D-PromptReco-v2_D_MINIAOD_221103_151141/
#condor_Muon_D_Run2022D-PromptReco-v3_D_MINIAOD_221104_162835/
#condor_Muon_D_Run2022E-PromptReco-v1_D_MINIAOD_221104_233352/
#condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_221104_233518/
#condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_230308_014134/
#condor_Muon_D_Run2022G-PromptReco-v1_D_MINIAOD_230308_014158/
#condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1-v2_D_MINIAODSIM_230308_014802/
#condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v4_D_MINIAODSIM_230308_011755/


#./efficiency_test.exe  root://cluster142.knu.ac.kr//store/user/jelee/ntuples/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1-v2_D_MINIAODSIM_230308_014802/condorOut/  heff_2022_TTto2L2Nu_postEE.root >& sum_22_postEE_mc.log
#./efficiency_test.exe  root://cluster142.knu.ac.kr//store/user/jelee/ntuples/condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v4_D_MINIAODSIM_230308_011755/condorOut/  heff_2022_TTto2L2Nu_preEE.root >& sum_22_preEE_mc.log










#./efficiency_test.exe  ../condor_SingleMuon_D_Run2022B-PromptReco-v1_D_MINIAOD_230330_230931/condorOut/   heff_2022_B.root >& sum_22B_data.log
#echo " end 2022G running --------------------------------------- "
# echo " @@@@@@ Start 2022 running --------------------------------------- "
#./efficiency_test.exe  ../condor_Muon_D_Run2022C-PromptReco-v1_D_MINIAOD_221102_212157/condorOut/    heff_2022_C1_v2.root >& sum_22C1_data.log       
# echo " end 2022C running --------------------------------------- "
#./efficiency_test.exe  ../condor_Muon_D_Run2022D-PromptReco-v1_D_MINIAOD_221103_151105/condorOut/    heff_2022_D1_v2.root >& sum_22D1_data.log      
# echo " end 2022D1 running --------------------------------------- "
#./efficiency_test.exe  ../condor_Muon_D_Run2022D-PromptReco-v2_D_MINIAOD_221103_151141/condorOut/    heff_2022_D2_v2.root >& sum_22D2_data.log      
# echo " end 2022D2 running --------------------------------------- "
#./efficiency_test.exe  ../condor_Muon_D_Run2022E-PromptReco-v1_D_MINIAOD_221104_233352/condorOut/    heff_2022_E1_v2.root >& sum_22E1_data.log   
# echo " end 2022E running --------------------------------------- "
#./efficiency_test.exe  ../condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_221104_233518/condorOut/    heff_2022_F1_v2.root >& sum_22F1_data.log   
# echo " end 2022F running --------------------------------------- "
#./efficiency_test.exe  ../condor_Muon_D_Run2022G-PromptReco-v1_D_MINIAOD_230308_014158/condorOut/    heff_2022_G1_v1_all.root >& sum_22G1_data_all.log
#echo " end 2022G running --------------------------------------- "
#./efficiency_test.exe  ../condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1-v2_D_MINIAODSIM_230308_014802/condorOut/  heff_mc_TT_postEE.root >& sum_postEE_mc.log
# echo " end 2022 MC postEE running --------------------------------------- "
#./efficiency_test.exe  ../condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v4_D_MINIAODSIM_230308_011755/condorOut/ heff_mc_TT_preEE.root >& sum_preEE_mc.log
# echo " end 2022 MC preEE running --------------------------------------- "
#./efficiency.exe  ../condor_TTTo2L2Nu_CP5_13p6TeV_powheg-pythia8_D_Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2_D_MINIAODSIM_221102_215748/condorOut/           heff_mc_tt_2022_v2.root   >& sum_22mc_tt.log 
# echo " end 2022 TT running --------------------------------------- "
#./efficiency.exe  ../condor_WJetsToLNu_TuneCP5_13p6TeV-madgraphMLM-pythia8_D_Run3Winter22MiniAOD-122X_mcRun3_2021_realistic_v9-v2_D_MINIAODSIM_221102_220921/condorOut/ heff_mc_wjet_2022_v2.root >& sum_22mc_wjet.log        
# echo " end 2022 WJet running --------------------------------------- "
#
# echo " @@@@@@ Start 2018 running --------------------------------------- "
#./efficiency.exe  ../condor_SingleMuon_D_Run2018A-UL2018_MiniAODv2-v3_D_MINIAOD_221104_233852/condorOut/     heff_data_muon_2018_A_v2.root >& sum_data_18A.log        
# echo " end 2018A  running --------------------------------------- "
#./efficiency.exe  ../condor_SingleMuon_D_Run2018B-UL2018_MiniAODv2-v2_D_MINIAOD_221104_234015/condorOut/     heff_data_muon_2018_B_v2.root >& sum_data_18B.log        
# echo " end 2018B  running --------------------------------------- "
#./efficiency.exe  ../condor_SingleMuon_D_Run2018C-UL2018_MiniAODv2-v2_D_MINIAOD_221104_234056/condorOut/     heff_data_muon_2018_C_v2.root >& sum_data_18C.log        
# echo " end 2018C  running --------------------------------------- "
#./efficiency.exe  ../condor_SingleMuon_D_Run2018D-UL2018_MiniAODv2-v3_D_MINIAOD_221104_234121/condorOut/     heff_data_muon_2018_D_v2.root >& sum_data_18D.log        
# echo " end 2018D  running --------------------------------------- "
#./efficiency.exe  ../condor_WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_D_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2_D_MINIAODSIM_221104_233743/condorOut/ heff_mc_wjet_2018_v2.root >& sum_18mc_wjet.log         
# echo " end 2018 WJet  running --------------------------------------- "
#./efficiency.exe  ../condor_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_D_RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1_D_MINIAODSIM_221104_233626/condorOut/                    heff_mc_2018_v2.root >& sum_18mc_tt.log  
# echo " end 2018 TT running --------------------------------------- "
#
# echo " @@@@@@ ALL DONE !!! --------------------------------------- "
#
#rm efficiency.exe
#../condor_Muon_D_Run2022C-PromptReco-v1_D_MINIAOD_221102_212157/
#../condor_Muon_D_Run2022D-PromptReco-v1_D_MINIAOD_221103_151105/
#../condor_Muon_D_Run2022D-PromptReco-v2_D_MINIAOD_221103_151141/
#../condor_Muon_D_Run2022D-PromptReco-v3_D_MINIAOD_221104_162835/
#../condor_Muon_D_Run2022E-PromptReco-v1_D_MINIAOD_221104_233352/
#../condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_221104_233518/
#../condor_Muon_D_Run2022F-PromptReco-v1_D_MINIAOD_230308_014134/
#../condor_Muon_D_Run2022G-PromptReco-v1_D_MINIAOD_230308_014158/
#../condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1-v2_D_MINIAODSIM_230308_014802/
#../condor_TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8_D_Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12-v4_D_MINIAODSIM_230308_011755/

