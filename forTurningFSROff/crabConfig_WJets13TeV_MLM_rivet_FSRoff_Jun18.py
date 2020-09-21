from CRABClient.UserUtilities import config

config = config()
config.General.requestName = 'Rivet13TeV_WJets_MLM_FSRoff'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
# Name of the CMSSW configuration file
config.JobType.psetName = 'rivet_WJets_MLM_FSRoff_cfg.py'
config.JobType.outputFiles = ['wjets13tev.yoda']
config.JobType.maxJobRuntimeMin = 2800

config.Data.inputDataset = '/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIWinter15wmLHE-MCRUN2_71_V1_ext1-v1/LHE'
#config.Data.inputDBS = 'global' # The default is global.
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 4
config.Data.totalUnits = 4252

#config.Data.splitting = 'EventAwareLumiBased'
#config.Data.runRange = '1,999999'
config.Data.outLFNDirBase = '/store/user/ahortian/Rivet13TeV/' # (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.ignoreLocality = True
config.Data.outputDatasetTag = 'Rivet13TeV_WJets_MLM_FSRoff'


# This string is used to construct the output dataset name
#config.Data.outputDatasetTag = 'CRAB3_Analysis_test1'

# These values only make sense for processing data
#    Select input data based on a lumi mask
#config.Data.lumiMask = 'Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
#    Select input data based on run-ranges
#config.Data.runRange = '190456-194076'

# Where the output files will be transmitted to
config.Site.storageSite = 'T2_CH_CERN'