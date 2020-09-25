from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.transferLogs = False
config.General.requestName = '2016_WJetsLOMLM_NonPertON'
config.section_('JobType')
config.JobType.psetName = 'runPythia8AndRivetAnalysis_WJetsLOMLM_2016.py'
config.JobType.pluginName = 'Analysis'
config.JobType.maxJobRuntimeMin = 1200
config.JobType.maxMemoryMB = 2000
config.JobType.outputFiles = ['wjets13tev_hadmpiON.yoda']
config.section_('Data')
config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIWinter15wmLHE-MCRUN2_71_V1_ext1-v1/LHE'
config.Data.publication = False
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 15
config.Data.totalUnits = 4800
config.Data.outLFNDirBase = '/store/user/awisecar/NPCorrections2016_MadgraphLO/'
config.Data.outputDatasetTag = '2016_WJetsLOMLM_NonPertON'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T2_CH_CERN'
