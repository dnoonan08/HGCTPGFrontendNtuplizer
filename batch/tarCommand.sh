#!/bin/bash

cd ../../../../..

tar --exclude='*~' --exclude-vcs --exclude='*.root' --exclude='CMSSW_9_4_2/src/HGCTPG/FrontendNtuplizer/.git' --exclude='*tgz' -zcf CMSSW_9_4_2.tgz CMSSW_9_4_2

xrdcp -f CMSSW_9_4_2.tgz root://cmseos.fnal.gov//store/user/${USER}/HGCAL_Concentrator/.

rm CMSSW_9_4_2.tgz

cd CMSSW_9_4_2/src/HGCTPG/FrontendNtuplizer/batch
