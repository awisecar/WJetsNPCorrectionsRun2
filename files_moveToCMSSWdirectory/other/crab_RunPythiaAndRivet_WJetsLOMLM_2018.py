from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = False
config.General.requestName = '2018_WJetsLOMLM_NonPertON'
config.section_('JobType')
config.JobType.psetName = 'runPythia8AndRivetAnalysis_WJetsLOMLM_2018.py'
config.JobType.pluginName = 'Analysis'
config.JobType.maxJobRuntimeMin = 2000
config.JobType.maxMemoryMB = 2000
config.JobType.outputFiles = ['wjets13tev_hadmpiON.yoda']
config.section_('Data')
# config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIWinter15wmLHE-MCRUN2_71_V1_ext1-v1/LHE'
config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM'
config.Data.publication = False
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 10
# config.Data.totalUnits = 4800 # this parameter tells CRAB how many files to analyze (i.e. imposes a limit)
config.Data.outLFNDirBase = '/store/user/awisecar/NPCorrections_WJetsRun2/'
config.Data.outputDatasetTag = '2018_WJetsLOMLM_NonPertON'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
