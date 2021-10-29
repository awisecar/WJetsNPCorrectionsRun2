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
./compareNPCorrRatio_Pythia8vsSherpa.py <distribution-number-NUM> <distribution-number-DENOM> npOFF_example.yoda npON_example.yoda
'''
################################
## Parse input arguments
parser = argparse.ArgumentParser(description='Computes non-perturbative (NP) corrections from input YODA files')
parser.add_argument('basenameNUM', help='Basename of the NUM table')
parser.add_argument('basenameDENOM', help='Basename of the DENOM table')
parser.add_argument('yodaOff1', help='YODA file for NP=Off')
parser.add_argument('yodaOn1', help='YODA file for NP=On')
parser.add_argument('--out', help='Name of output plot')
args = parser.parse_args()
################################
## Get Histo1D objects (e.g. rivet1) that match the given basename
for key, value in yoda.read(args.yodaOff1).items():
    if re.search(args.basenameNUM, key):
        rivet1 = value # NP Off, NUM
for key, value in yoda.read(args.yodaOn1).items():
    if re.search(args.basenameNUM, key):
        rivet2 = value # NP On, NUM
for key, value in yoda.read(args.yodaOff1).items():
    if re.search(args.basenameDENOM, key):
        rivet3 = value # NP Off, DENOM
for key, value in yoda.read(args.yodaOn1).items():
    if re.search(args.basenameDENOM, key):
        rivet4 = value # NP On, DENOM
numBins = rivet1.numBins
xtitle = "Muon pT + Leading AK8 Jet pT" # just assume we're doing this distribution
print "\nTable NUM: "+str(args.basenameNUM)+", Table DENOM: "+str(args.basenameDENOM)+"\n#Bins: "+str(numBins)
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
################################
## Getting rivet3
binCent_NPOff_DENOM, binWidth_NPOff_DENOM, binEdges_NPOff_DENOM, xs_NPOff_DENOM, xsErr_NPOff_DENOM, percErr_NPOff_DENOM = ([] for i in range(6))
for i,b in enumerate(rivet3.bins):
    binCent_NPOff_DENOM.append(b.xMid)
    binWidth_NPOff_DENOM.append( (b.xMax-b.xMin) )
    binEdges_NPOff_DENOM.append(b.xEdges)
    xs_NPOff_DENOM.append(b.height)
    xsErr_NPOff_DENOM.append(b.heightErr)
    percErr_NPOff_DENOM.append( (xsErr_NPOff_DENOM[i]*100.)/xs_NPOff_DENOM[i] )
################################
## Getting rivet4
binCent_NPOn_DENOM, binWidth_NPOn_DENOM, binEdges_NPOn_DENOM, xs_NPOn_DENOM, xsErr_NPOn_DENOM, percErr_NPOn_DENOM = ([] for i in range(6))
for i,b in enumerate(rivet4.bins):
    binCent_NPOn_DENOM.append(b.xMid)
    binWidth_NPOn_DENOM.append( (b.xMax-b.xMin) )
    binEdges_NPOn_DENOM.append(b.xEdges)
    xs_NPOn_DENOM.append(b.height)
    xsErr_NPOn_DENOM.append(b.heightErr)
    percErr_NPOn_DENOM.append( (xsErr_NPOn_DENOM[i]*100.)/xs_NPOn_DENOM[i] )
################################################################
## Calculating NP correction distribution
corrNP, corrNPerrs, corrNPpercErrs = ([] for i in range(3))
for i,b in enumerate(xs_NPOn):
    corrNP.append( xs_NPOn[i]/xs_NPOff[i] )
    corrNPerrs.append( corrNP[i] * math.sqrt( (xsErr_NPOn[i]/xs_NPOn[i])**2. + (xsErr_NPOff[i]/xs_NPOff[i])**2. )  )
    corrNPpercErrs.append(corrNPerrs[i]*100./corrNP[i])
################################
## Calculating NP correction distribution (DENOM)
corrNP_DENOM, corrNPerrs_DENOM, corrNPpercErrs_DENOM = ([] for i in range(3))
for i,b in enumerate(xs_NPOn):
    corrNP_DENOM.append( xs_NPOn_DENOM[i]/xs_NPOff_DENOM[i] )
    corrNPerrs_DENOM.append( corrNP_DENOM[i] * math.sqrt( (xsErr_NPOn_DENOM[i]/xs_NPOn_DENOM[i])**2. + (xsErr_NPOff_DENOM[i]/xs_NPOff_DENOM[i])**2. )  )
    corrNPpercErrs_DENOM.append(corrNPerrs_DENOM[i]*100./corrNP_DENOM[i])
################################
## Calculating NP correction distribution (RATIO)
corrNP_RATIO, corrNPerrs_RATIO, corrNPpercErrs_RATIO = ([] for i in range(3))
for i,b in enumerate(xs_NPOn):
    corrNP_RATIO.append( corrNP[i]/corrNP_DENOM[i] )
    corrNPerrs_RATIO.append( corrNP_RATIO[i] * math.sqrt( (corrNPerrs[i]/corrNP[i])**2. + (corrNPerrs_DENOM[i]/corrNP_DENOM[i])**2. )  )
    corrNPpercErrs_RATIO.append(corrNPerrs_RATIO[i]*100./corrNP_RATIO[i])
print "\nNP_On/NP_Off for RATIO OF "+str(args.basenameNUM)+" TO "+str(args.basenameDENOM)+" --"
print "Bin centers: \n"+str(binCent_NPOn)
print "Values: \n"+str(corrNP_RATIO)
print "Percent errors: \n"+str(corrNPpercErrs_RATIO)
################################################################
## Fitting
## https://docs.scipy.org/doc/scipy/reference/generated/scipy.optimize.curve_fit.html
def func(x, c1, c2, c3):
    return c1 + c2/(x ** c3) 

# Fit over all bins --
popt, pcov = curve_fit(func, binCent_NPOn, corrNP_RATIO, sigma=corrNPerrs_RATIO, bounds=((0.98, -np.inf, -np.inf), (1.02, np.inf, np.inf)))

print("\nResults of fit --")
print("Constants of fit: "+str(popt))
print("NP correction values from the fit:\n"+str( list(func(binCent_NPOn, *popt)) ))
################################
## Plotting

## Setup for plot
xErr = [(b/2.) for b in binWidth_NPOn]
fig, ax = plt.subplots(figsize=(10, 6))

## Plot Pythia8 points and fit
ax.errorbar(binCent_NPOn, corrNP_RATIO, xerr=xErr, yerr=corrNPerrs_RATIO, fmt='ko', elinewidth=1.25, capsize=0.0, label='Pythia8 Simulation')
#ax.errorbar(binCent_NPOn, func(binCent_NPOn, *popt), fmt='r-', linewidth=1.25, label='Pythia8 Fit: c$_{1}$=%5.3f, c$_{2}$=%5.3f, c$_{3}$=%5.3f' % tuple(popt))
ax.errorbar(binCent_NPOn, func(binCent_NPOn, *popt), fmt='r-', linewidth=1.25, label='Pythia8 Fit')

## Aesthetics
ax.set(xlabel=xtitle+' [GeV]', ylabel='NP$_{ON}$/NP$_{OFF}$', title='Non-Perturbative Corrections, '+str(args.basenameNUM)+' to '+str(args.basenameDENOM), xlim=[binCent_NPOn[0]-xErr[0], binCent_NPOn[numBins-1]+xErr[numBins-1]], ylim=[0.4,1.6]) #these are reasonable y-axis bounds
ax.yaxis.label.set_size(18)
ax.axhline(y=1, linewidth=1, color='k', linestyle='--')
ax.legend(loc='upper left')

## Save output plot
if args.out:
    out = args.out
else:
    out = 'npCorrPlot_RATIO_'+args.basenameNUM+'_TO_'+args.basenameDENOM+'.pdf'
fig.savefig(out)

################################
print ("\nFinished!\n")

