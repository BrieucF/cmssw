import FWCore.ParameterSet.Config as cms

process = cms.Process("L1DTTrigPhase2Prod")

# import of standard configurations
#process.load('Configuration.StandardSequences.Services_cff')
#process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
#process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.EventContent.EventContent_cff')
#process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D38Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023D38_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
#process.load('Configuration.StandardSequences.Generator_cff')
#process.load('IOMC.EventVertexGenerators.VtxSmearedHLLHC_cfi')
#process.load('GeneratorInterface.Core.genFilterSummary_cff')
#process.load('Configuration.StandardSequences.SimIdeal_cff')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')


#process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cff")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.DTGeometryESModule.applyAlignment = False

process.load("Phase2L1Trigger.CalibratedDigis.CalibratedDigis_cfi")
process.CalibratedDigis.dtDigiTag = "simMuonDTDigis"
process.load("L1Trigger.DTPhase2Trigger.dtTriggerPhase2PrimitiveDigis_cfi")

#Produce RPC clusters from RPCDigi
process.load("RecoLocalMuon.RPCRecHit.rpcRecHits_cfi")
process.rpcRecHits.rpcDigiLabel = cms.InputTag('simMuonRPCDigis')

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('file:/eos/cms/store/group/dpg_dt/comm_dt/TriggerSimulation/SamplesReco/SingleMu_FlatPt-2to100/Version_10_5_0/SimRECO_1.root'))
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(100))

process.out = cms.OutputModule("PoolOutputModule",
                                       outputCommands = cms.untracked.vstring('keep *'),
                                                                      fileName = cms.untracked.string('DTTriggerPhase2Primitives.root')
                                                                      #fileName = cms.untracked.string('/eos/cms/store/group/dpg_rpc/comm_rpc/UpgradePhaseII/RPC_PLUS_DT/SingleMu_FlatPt-2to100_10_5_0_MaryCruz_WithRPCRecHits/SimRECO_1.root')
                                                                      )

process.p = cms.Path(process.rpcRecHits*process.CalibratedDigis*process.dtTriggerPhase2PrimitiveDigis)
process.this_is_the_end = cms.EndPath(process.out)


#process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cff")
#process.load("Geometry.DTGeometry.dtGeometry_cfi")
#process.DTGeometryESModule.applyAlignment = False
#
#process.load("L1Trigger.DTPhase2Trigger.dtTriggerPhase2PrimitiveDigis_cfi")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
#process.GlobalTag.globaltag = "80X_dataRun2_2016SeptRepro_v7"

#process.load("Phase2L1Trigger.CalibratedDigis.CalibratedDigis_cfi")
#process.load("L1Trigger.DTPhase2Trigger.dtTriggerPhase2PrimitiveDigis_cfi")
#
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('file:/eos/cms/store/group/dpg_dt/comm_dt/TriggerSimulation/SamplesReco/SingleMu_FlatPt-2to100/Version_10_5_0/SimRECO_1.root'))
#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))
#
#process.out = cms.OutputModule("PoolOutputModule",
#                               outputCommands = cms.untracked.vstring('keep *'),
#                               fileName = cms.untracked.string('DTTriggerPhase2Primitives.root')
#)
#
#process.p = cms.Path(process.CalibratedDigis*process.dtTriggerPhase2PrimitiveDigis)
#process.this_is_the_end = cms.EndPath(process.out)
