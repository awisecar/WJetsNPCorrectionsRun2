## Overview --
The goal of this code is to compute the non-perturbative (NP) corrections, i.e. the effects of hadronization/fragmentation and multi-parton interactions in the simulation, that are applied multiplicatively to fixed-order calculations (for each bin) in order to bring these distributions to particle-level, for comparison with unfolded data. 
This is done by re-running the Pythia8HadronizerFilter CMSSW module on top of the LHEEventProduct content of an LHE-tier dataset, which in our case is a Madgraph simulation of W(lnu)+Jets with LO MLM precision up until the 4th jet:
/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIWinter15wmLHE-MCRUN2_71_V1_ext1-v1/LHE
The LHEEventProduct should contain only parton-level information, so it should be sufficient to use these events for deriving NP corrections for all years in the Run 2 analysis, since the main difference in simulation among years is the default PDF set and tune used by Pythia8.
Instructions for running locally in-shell, as well as submissions using CRAB, are given below. The output files are in the YODA format, so all of the associated Rivet-YODA tools should be sufficient for making plots/deriving corrections/etc. (For possible future use, the files in "forTurningFSROff" can be used for looking at effects of turning final state radiation (FSR) off.

## Setup --
mkdir NonPerturbativeCorrections
cd NonPerturbativeCorrections
git pull ...........
cd ...........
cmsrel CMSSW_8_0_34_UL
cd CMSSW_8_0_34_UL/src
cmsenv
git cms-addpkg GeneratorInterface/RivetInterface
scram b -j 8

## Next thing to do is to find a recent valid CMSSW fragment with the Pythia8 module in it
# Apichart used: https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIIWinter15GS-00145/0
# Then ran the cmsDriver.py utility on it to get a CMSSW cfg file
>>> NOTE: the current Pythia8 modules I have use the old 2015 (2016?) tune, so I’ll have to remake these (at least for 2017, 2018)
- can probably get these fragments from McM for my specific samples
- can find the cmsDriver.py command to do this in Apichart’s README

## Move CMSSW cfg files, CRAB cfg files inside work area
mv runPythia8AndRivetAnalysis_WJetsLOMLM*.py ./CMSSW_8_0_34_UL/src
mv crab_*.py ./CMSSW_8_0_34_UL/src

## Move Rivet analysis file into appropriate folder
mv CMS_SMP_WJetsAlphaS_Run2_NPCorrections.cc ./CMSSW_8_0_34_UL/src/GeneratorInterface/RivetInterface/src
>>> NOTE: need to update Rivet analysis with all relevant AK4, AK8 distributions for ratios

## Option 1: Test locally
cd ./CMSSW_8_0_34_UL/src
cmsenv
cmsvoms
scram b -j 8
cmsRun runPythia8AndRivetAnalysis_WJetsLOMLM_old2015.py
 -- or -- 
cmsRun runPythia8AndRivetAnalysis_WJetsLOMLM_HadMpiOFF_old2015.py
then
rivet-mkhtml <output-file-name>.yoda
>> can do this and see results in "plots" folder (NOT YET TESTED!!!)

## Option 2: Run in CRAB

## First make sure you make an output directory listed in the CRAB cfg file for job output on EOS, such as --
## /eos/cms/store/user/awisecar/NPCorrections2016_MadgraphLO

## Then to run jobs --
cd ./CMSSW_8_0_34_UL/src
cmsenv
cmsvoms
sourcecrab
scram b -j 8

# Submit
crab submit -c crab_RunPythiaAndRivet_WJetsLOMLM_old2015.py
crab submit -c crab_RunPythiaAndRivet_WJetsLOMLM_HadMpiOFF_old2015.py

# To check progress:
crab status -d crab_2016_WJetsLOMLM_NonPertON
crab status -d crab_2016_WJetsLOMLM_NonPertOFF

## Then copy Yoda files to local directory, merge using runMergeYodaCrabDir.py utility (NOT YET TESTED!!!)
## Then convert to ROOT file using the yoda2aida, then aida2root utilities, then you have the ROOT files you need to take ratios for the corrections

