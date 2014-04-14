#ifndef HGCalSimProducers_HGCDigitizer_h
#define HGcalSimProducers_HGCDigitizer_h

#include "DataFormats/DetId/interface/DetId.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"

#include <vector>

class PCaloHit;
class PileUpEventPrincipal;

class HGCDigitizer
{
public:
  
  explicit HGCDigitizer(const edm::ParameterSet& ps);
  virtual ~HGCDigitizer();

  /**
     @short handle SimHit accumulation
   */
  void accumulate(edm::Event const& e, edm::EventSetup const& c);
  void accumulate(PileUpEventPrincipal const& e, edm::EventSetup const& c);
  void accumulate(edm::Handle<edm::PCaloHitContainer> const &hits, int bxCrossing);

  /**
     @short actions at the start/end of event
   */
  void initializeEvent(edm::Event const& e, edm::EventSetup const& c);
  void finalizeEvent(edm::Event& e, edm::EventSetup const& c);

  /**
      @short actions at the start/end of run
   */
  void beginRun(const edm::EventSetup & es);
  void endRun();

private :

  std::string hitCollection_;

  //handle sim hits
  int maxSimHitsAccTime_;
  typedef std::vector<double> CaloSimHitData;
  typedef std::map<uint32_t, CaloSimHitData> CaloSimHitDataAccumulator;
  CaloSimHitDataAccumulator simHitAccumulator_;  
  void resetSimHitDataAccumulator() { for( std::map<uint32_t, CaloSimHitData>::iterator it = simHitAccumulator_begin(); it!=simHitAccumulator_.end(); it++) std::fill(it->begin(), it->end(),0.); }
  
};

#endif


 
