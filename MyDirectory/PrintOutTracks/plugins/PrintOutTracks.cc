// -*- C++ -*-
//
// Package:    MyDirectory/PrintOutTracks
// Class:      PrintOutTracks
//
/**\class PrintOutTracks PrintOutTracks.cc MyDirectory/PrintOutTracks/plugins/PrintOutTracks.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Brunella D'Anzi
//         Created:  Tue, 20 Dec 2022 19:31:29 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
//
// class declaration
//

using reco::TrackCollection;

class PrintOutTracks : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit PrintOutTracks(const edm::ParameterSet&);
  ~PrintOutTracks() override = default;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  

private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  
  // ----------member data ---------------------------
  edm::EDGetTokenT<edm::View<reco::Track> > tracksToken_;  //used to select which tracks to read from configuration file
  int indexEvent_;
};

//
// constructors and destructor
//
PrintOutTracks::PrintOutTracks(const edm::ParameterSet& iConfig)
 : tracksToken_(consumes<edm::View<reco::Track> >(iConfig.getUntrackedParameter<edm::InputTag>("tracks", edm::InputTag("generalTracks")) ))
{
  //now do what ever initialization is needed
  indexEvent_ = 0;
}


//
// member functions
//

// ------------ method called for each event  ------------
void
PrintOutTracks::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::cout << "Event " << indexEvent_ << std::endl;

   edm::Handle<edm::View<reco::Track> > trackHandle;
   iEvent.getByToken(tracksToken_, trackHandle);
   if ( !trackHandle.isValid() ) return;
   const edm::View<reco::Track>& tracks = *trackHandle;
   size_t iTrack = 0;
   for ( auto track : tracks ) {
     std::cout << "    Track " << iTrack << " "
	       << track.charge()/track.pt() << " "
               << track.phi() << " "
               << track.eta() << " "
               << track.dxy() << " "
               << track.dz()
	       << std::endl;
     iTrack++;
   }
   ++indexEvent_;
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrintOutTracks::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.addUntracked<edm::InputTag>("tracks",edm::InputTag("generalTracks"));
  descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrintOutTracks);
