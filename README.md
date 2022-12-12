# SimpleNtuplizer
simple miniaod ntuplizer for 2022 data
# SimpleNtuplizer
simple miniaod ntuplizer for 2022 data

### 1) CMS environment setting (>12_4_X)
```
export SCRAM_ARCH=slc7_amd64_gcc10 #12_2_X
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
echo "$VO_CMS_SW_DIR $SCRAM_ARCH"
source $VO_CMS_SW_DIR/cmsset_default.sh
voms-proxy-init --voms cms
```
```
cmsrel CMSSW_12_4_10_patch3
cd CMSSW_12_4_10_patch3/src
cmsenv
```
### 2) Cloning master git branch under src directory
```
git clone -b master https://github.com/jeongeun/SimpleNtuplizer.git
scram b -j 4
```

### 3) Test with cmsRun 
```
cmsRun makeTree_run3.py
```
