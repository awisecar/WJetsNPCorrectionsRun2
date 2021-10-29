#! /usr/bin/env python2
import os
import sys
import datetime
import argparse
#######################################
'''
E.g.
./runMergeYodaHistos.py 2016 OFF
./runMergeYodaHistos.py 2016 ON
./runMergeYodaHistos.py 2017 OFF
./runMergeYodaHistos.py 2017 ON
'''
#######################################
# Parse input arguments
parser = argparse.ArgumentParser()
parser.add_argument("year", help="Year of the MC samples/tune (2016, 2017, 2018)")
parser.add_argument("on_or_off", help="Specify whether NP corrections are ON or OFF")
args = parser.parse_args()
#######################################

# Get directory containing output Yoda files
basedir = "./"+str(args.year)+"_WJetsNLOFXFX_NonPert"+str(args.on_or_off)+"/"
print("\nMerging Yoda files in the following directory... \n"+str(basedir)+"\n")

# Create beginning of command to merge all of the output files together
# command = "./mergeyodahistos -o " + "wjets13tev_"+str(args.year)+"_hadmpi"+str(args.on_or_off)+"_MERGED.yoda"
command = "./mergeyodahistos -o " + str(args.year)+"_hadmpi"+str(args.on_or_off)+"_wjets13tev_MERGED.yoda"

# Add all existing YODA files to the merge script
# NOTE: 2200 YODA files is the maximum number that the mergeyodahistos script can seem to handle
# NOTE: Attempted to adjust the CRAB cfg file parameters accordingly, to get under this limit
for i in range(1, 2200+1):
#for i in range(1+2200, 2200+1+2200):
    fileIn = "wjets13tev_hadmpi"+str(args.on_or_off)+"_"+str(i)+".yoda"
    if not os.path.isfile(basedir+fileIn):
        print ('Could not find file: '+str(fileIn)+', skipping!')
        continue
    command += " "+basedir+fileIn

# Execute command
print ("\nExecuting the command... \n"+command)
os.system(command)
    
print("\nFinished!\n")
