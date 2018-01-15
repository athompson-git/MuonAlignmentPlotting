import FWCore.ParameterSet.Config as cms

process = cms.Process("analysis")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
# replace 'myfile.root' with the source file you want to use
fileNames = cms.untracked.vstring(
'root://eoscms.cern.ch://store/data/Run2017C/SingleMuon/ALCARECO/MuAlCalIsolatedMu-PromptReco-v3/000/301/960/00000/642B085F-1E8E-E711-9B76-02163E01A20D.root'
)
)

process.analysis = cms.EDAnalyzer('muon_analyzer',
globalmuon = cms.InputTag("ALCARECOMuAlCalIsolatedMu", "GlobalMuon", "RECO"),
)

process.TFileService = cms.Service("TFileService",
fileName = cms.string('outfile.root')
)

process.p = cms.Path(process.analysis)

