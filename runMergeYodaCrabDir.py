# To run, do:
# python MergeYodaCrabDir.py [crab dir] [mergedOutputName]
# python MergeYodaCrabDir.py Wjets_MadgraphAODv2 MadgraphAOD_ALL

import sys
import os

crabdir = sys.argv[1]
rename =''
if (len(sys.argv)>2):
    rename = sys.argv[2]

aidas = [(crabdir + '/res/'+x.replace('\n','')).replace('//','/') for x in os.popen('ls -1 '+crabdir+'/res | grep ".yoda"').readlines()]
print aidas

aidaout = crabdir.replace('/','')+'.yoda'
print aidaout

if (rename!=''):
    #os.system('mv '+aidaout+ ' '+rename+'.aida')
    aidaout = rename+'.yoda'

if aidaout in str(os.listdir('.')):
    os.system('rm '+aidaout)
    print 'Removing old aida file'

aidamerge = 'yodamerge -o '+aidaout

for x in aidas:
    aidamerge += ' '+x

#print aidamerge
os.system(aidamerge)