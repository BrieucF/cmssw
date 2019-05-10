import FWCore.ParameterSet.Config as cms

process = cms.Process("L1DTTrigPhase2Prod")

process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cff")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.DTGeometryESModule.applyAlignment = False

# import of standard configurations
process.load('Configuration.Geometry.GeometryExtended2023D38Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023D38_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')



process.load("Phase2L1Trigger.CalibratedDigis.CalibratedDigis_cfi")
process.CalibratedDigis.dtDigiTag = "simMuonDTDigis"
process.load("L1Trigger.DTPhase2Trigger.dtTriggerPhase2PrimitiveDigis_cfi")
process.dtTriggerPhase2PrimitiveDigis.useRPC = True
#process.dtTriggerPhase2PrimitiveDigis.debug = True

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
