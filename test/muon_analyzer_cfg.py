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
'file:/afs/cern.ch/work/a/adthomps/public/9_4_0_alignment/CMSSW_9_4_0_pre2/src/analysis/642B085F-1E8E-E711-9B76-02163E01A20D.root'
)
)

process.demo = cms.EDAnalyzer('muon_analyzer',
globalmuon = cms.InputTag("ALCARECOMuAlCalIsolatedMu", "globalmuon", "RECO"),
)

process.TFileService = cms.Service("TFileService",
fileName = cms.string('outfile.root')
)

process.p = cms.Path(process.demo)

