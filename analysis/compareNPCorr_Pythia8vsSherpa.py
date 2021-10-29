#! /usr/bin/env python2
import os
import math
import re
import argparse
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import yoda
################################
'''
Run like this -
./compareNPCorr_Pythia8vsSherpa.py <distribution-number> npOFF_example.yoda npON_example.yoda
E.g. - 
./compareNPCorr_Pythia8vsSherpa.py d56-x01-y01 2016_hadmpiOFF_wjets13tev_MERGED.yoda 2016_hadmpiON_wjets13tev_MERGED.yoda
./compareNPCorr_Pythia8vsSherpa.py d57-x01-y01 2016_hadmpiOFF_wjets13tev_MERGED.yoda 2016_hadmpiON_wjets13tev_MERGED.yoda
'''
################################
## Parse input arguments
parser = argparse.ArgumentParser(description='Computes non-perturbative (NP) corrections from input YODA files')
parser.add_argument('basename', help='Basename of the table')
parser.add_argument('yodaOff1', help='YODA file for NP=Off')
parser.add_argument('yodaOn1', help='YODA file for NP=On')
parser.add_argument('--out', help='Name of output plot')
args = parser.parse_args()
################################
## Get Histo1D objects (e.g. rivet1) that match the given basename
for key, value in yoda.read(args.yodaOff1).items():
    if re.search(args.basename, key):
        rivet1 = value # NP Off
for key, value in yoda.read(args.yodaOn1).items():
    if re.search(args.basename, key):
        rivet2 = value # NP On
numBins = rivet1.numBins
xtitle = "Muon pT + Leading AK8 Jet pT" # just assume we're doing this distribution
print "\nTable: "+str(args.basename)+"\n#Bins: "+str(numBins)
################################
## Getting rivet1
binCent_NPOff, binWidth_NPOff, binEdges_NPOff, xs_NPOff, xsErr_NPOff, percErr_NPOff = ([] for i in range(6))
for i,b in enumerate(rivet1.bins):
    binCent_NPOff.append(b.xMid)
    binWidth_NPOff.append( (b.xMax-b.xMin) )
    binEdges_NPOff.append(b.xEdges)
    xs_NPOff.append(b.height)
    xsErr_NPOff.append(b.heightErr)
    percErr_NPOff.append( (xsErr_NPOff[i]*100.)/xs_NPOff[i] )
# print "\nNP Off --"
# #print "Bin centers: \n"+str(binCent_NPOff)
# print "Diff. xsec values: \n"+str(xs_NPOff)
# print "Diff. xsec errs: \n"+str(xsErr_NPOff)
# print "Percent error: \n"+str(percErr_NPOff)
################################
## Getting rivet2
binCent_NPOn, binWidth_NPOn, binEdges_NPOn, xs_NPOn, xsErr_NPOn, percErr_NPOn = ([] for i in range(6))
for i,b in enumerate(rivet2.bins):
    binCent_NPOn.append(b.xMid)
    binWidth_NPOn.append( (b.xMax-b.xMin) )
    binEdges_NPOn.append(b.xEdges)
    xs_NPOn.append(b.height)
    xsErr_NPOn.append(b.heightErr)
    percErr_NPOn.append( (xsErr_NPOn[i]*100.)/xs_NPOn[i] )
# print "\nNP On --"
# #print "Bin centers: \n"+str(binCent_NPOn)
# print "Diff. xsec values: \n"+str(xs_NPOn)
# print "Diff. xsec errs: \n"+str(xsErr_NPOn)
# print "Percent error: \n"+str(percErr_NPOn)
################################
## Calculating NP correction distribution
corrNP, corrNPerrs, corrNPpercErrs = ([] for i in range(3))
for i,b in enumerate(xs_NPOn):
    corrNP.append( xs_NPOn[i]/xs_NPOff[i] )
    corrNPerrs.append( corrNP[i] * math.sqrt( (xsErr_NPOn[i]/xs_NPOn[i])**2. + (xsErr_NPOff[i]/xs_NPOff[i])**2. )  )
    corrNPpercErrs.append(corrNPerrs[i]*100./corrNP[i])
print "\nNP_On/NP_Off for "+str(args.basename)+" --"
print "Bin centers: \n"+str(binCent_NPOn)
#print "Bin edges: \n"+str(binEdges_NPOn)
print "Values: \n"+str(corrNP)
# print "corrNP errors: \n"+str(corrNPerrs)
print "Percent errors: \n"+str(corrNPpercErrs)
################################
## Fitting
## https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.curve_fit.html
def func(x, c1, c2, c3):
    return c1 + c2/(x ** c3) 

# Fit over all bins --
popt, pcov = curve_fit(func, binCent_NPOn, corrNP, sigma=corrNPerrs, bounds=((0.98, -np.inf, -np.inf), (1.02, np.inf, np.inf)))

# Fit w/ excluding the last bin(s) --
#binCent_NPOn_shortened = []
#corrNP_shortened = []
#corrNPerrs_shortened = []
#for i in range(len(binCent_NPOn)-1):
#    binCent_NPOn_shortened.append(binCent_NPOn[i])
#    corrNP_shortened.append(corrNP[i])
#    corrNPerrs_shortened.append(corrNPerrs[i])
#popt, pcov = curve_fit(func, binCent_NPOn_shortened, corrNP_shortened, sigma=corrNPerrs_shortened, bounds=((0.98, -np.inf, -np.inf), (1.02, np.inf, np.inf)))

print("\nResults of fit --")
print("Constants of fit: "+str(popt))
print("NP correction values from the fit:\n"+str( list(func(binCent_NPOn, *popt)) ))
################################
## Plotting

## Setup for plot
xErr = [(b/2.) for b in binWidth_NPOn]
fig, ax = plt.subplots(figsize=(10, 6))

## Plot Pythia8 points and fit
ax.errorbar(binCent_NPOn, corrNP, xerr=xErr, yerr=corrNPerrs, fmt='ko', elinewidth=1.25, capsize=0.0, label='Pythia8 Simulation')
#ax.errorbar(binCent_NPOn, func(binCent_NPOn, *popt), fmt='r-', linewidth=1.25, label='Pythia8 Fit: c$_{1}$=%5.3f, c$_{2}$=%5.3f, c$_{3}$=%5.3f' % tuple(popt))
ax.errorbar(binCent_NPOn, func(binCent_NPOn, *popt), fmt='r-', linewidth=1.25, label='Pythia8 Fit')

## Aesthetics
ax.set(xlabel=xtitle+' [GeV]', ylabel='NP$_{ON}$/NP$_{OFF}$', title='Non-Perturbative Corrections, '+str(args.basename), xlim=[binCent_NPOn[0]-xErr[0], binCent_NPOn[numBins-1]+xErr[numBins-1]], ylim=[0.4,1.6]) #these are reasonable y-axis bounds
#ax.set(xlabel=xtitle+' [GeV]', ylabel='NP$_{ON}$/NP$_{OFF}$', title='Non-Perturbative Corrections, '+str(args.basename), xlim=[binCent_NPOn[0]-xErr[0], binCent_NPOn[numBins-1]+xErr[numBins-1]], ylim=[0.0,2.0]) #try chaning y-axis bounds
ax.yaxis.label.set_size(18)
ax.axhline(y=1, linewidth=1, color='k', linestyle='--')
ax.legend(loc='upper left')

## Save output plot
if args.out:
    out = args.out
else:
    out = 'npCorrPlot_'+args.basename+'.pdf'
fig.savefig(out)

################################
print ("\nFinished!\n")

