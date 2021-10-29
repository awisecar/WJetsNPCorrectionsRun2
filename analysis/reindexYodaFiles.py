#! /usr/bin/env python2
import os
import sys
import datetime
import argparse
#######################################
# Parse input arguments
parser = argparse.ArgumentParser()
parser.add_argument("year", help="Year of the MC samples/tune (2016, 2017, 2018)")
parser.add_argument("on_or_off", help="Specify whether NP corrections are ON or OFF")
parser.add_argument("spacer", type=int, help="Reindex files up by this number")
args = parser.parse_args()
#######################################

# Get directory containing Yoda files
basedir = "./"+str(args.year)+"_WJetsLOMLM_NonPert"+str(args.on_or_off)+"/"
print("\nRe-indexing Yoda files in the following directory... \n"+str(basedir)+"\n")

# For each file found in folder, re-index up by "spacer"
maxFileIndex = 550 # maximum index of files in folder
for i in range(1, maxFileIndex+1):
    fileIn = "wjets13tev_hadmpi"+str(args.on_or_off)+"_"+str(i)+".yoda"
    if not os.path.isfile(basedir+fileIn):
        print ('Could not find file: '+str(fileIn)+', skipping!')
        continue
    fileOut = "wjets13tev_hadmpi"+str(args.on_or_off)+"_"+str(i+args.spacer)+".yoda"

    command = "mv "+basedir+fileIn+" "+basedir+fileOut
    print(command)
    os.system(command) # execute command
    
print("\nFinished!\n")

