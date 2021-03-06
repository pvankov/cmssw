import FWCore.ParameterSet.Config as cms

process = cms.Process("TESTPROD")
process.load("FWCore.Framework.test.cmsExceptionsFatal_cff")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(15)
)
process.Thing = cms.EDProducer("ThingProducer")

process.OtherThing = cms.EDProducer("OtherThingProducer")

process.AOtherThing = cms.EDProducer("OtherThingProducer",
    thingTag = cms.InputTag('Thing')
)
process.ZOtherThing = cms.EDProducer("OtherThingProducer",
    thingTag = cms.InputTag('Thing')
)

process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *', 
        'drop *_Thing_*_*'),
    fileName = cms.untracked.string('file:FastMergeTest_ancestor2.root')
)

process.source = cms.Source("EmptySource",
    firstEvent = cms.untracked.uint32(100),
    firstRun = cms.untracked.uint32(200)
)

process.p = cms.Path(process.Thing*(process.OtherThing+process.AOtherThing+process.ZOtherThing))
process.ep = cms.EndPath(process.output)


