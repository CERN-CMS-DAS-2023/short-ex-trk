// -*- C++ -*-
//
// Package:    MyDirectory/PrintOutTracks_MVA
// Class:      PrintOutTracks_MVA
//
/**\class PrintOutTracks_MVA PrintOutTracks_MVA.cc MyDirectory/PrintOutTracks/plugins/PrintOutTracks_MVA.cc

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

class PrintOutTracks_MVA : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit PrintOutTracks_MVA(const edm::ParameterSet&);
  ~PrintOutTracks_MVA() override = default;
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  
  // ----------member data ---------------------------
  edm::EDGetTokenT<edm::View<reco::Track> > tracksToken_;  //used to select which tracks to read from configuration file
  edm::EDGetTokenT<edm::View<float> > mvaValsToken_;
  int indexEvent_;
};


//
// constructors and destructor
//
PrintOutTracks_MVA::PrintOutTracks_MVA(const edm::ParameterSet& iConfig)
  : tracksToken_(consumes<edm::View<reco::Track> >(iConfig.getUntrackedParameter<edm::InputTag>("tracks", edm::InputTag("generalTracks")) )),
    mvaValsToken_( consumes<edm::View<float> >(iConfig.getUntrackedParameter<edm::InputTag>("mvaValues", edm::InputTag("generalTracks", "MVAValues")) ) )
{
   //now do what ever initialization is needed
  indexEvent_ = 0;
}

//
// member functions
//

// ------------ method called for each event  ------------
void
PrintOutTracks_MVA::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   std::cout << "Event " << indexEvent_ << std::endl;
   edm::Handle<edm::View<reco::Track> > trackHandle;
   iEvent.getByToken(tracksToken_, trackHandle);   
   if ( !trackHandle.isValid() ) return;
   const auto numTotal = trackHandle->size();
   edm::Handle<edm::View<float> > trackMVAstoreHandle;
   iEvent.getByToken(mvaValsToken_,trackMVAstoreHandle);
   if ( !trackMVAstoreHandle.isValid() ) return;
   auto numLoose = 0;
   auto numTight = 0;
   auto numHighPurity = 0;
   const edm::View<reco::Track>& tracks = *trackHandle;
   size_t iTrack = 0;
   for ( auto track : tracks ) {
     if (track.quality(track.qualityByName("loose"))     ) ++numLoose;
     if (track.quality(track.qualityByName("tight"))     ) ++numTight;
     if (track.quality(track.qualityByName("highPurity"))) ++numHighPurity;
     std::cout << "    Track " << iTrack << " "
	       << track.charge()/track.pt() << " "
	       << track.phi() << " "
	       << track.eta() << " "
	       << track.dxy() << " "
	       << track.dz()
	       << track.chi2() << " "
	       << track.ndof() << " "
	       << track.numberOfValidHits() << " "
	       << track.algoName() << " "
	       << trackMVAstoreHandle->at(iTrack)
	       << std::endl;
     iTrack++;
   }
   ++indexEvent_;
   std::cout << "Event " << indexEvent_
	     << " numTotal: " << numTotal
	     << " numLoose: " << numLoose
	     << " numTight: " << numTight
	     << " numHighPurity: " << numHighPurity
	     << std::endl;
}


// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrintOutTracks_MVA::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.addUntracked<edm::InputTag>("tracks",edm::InputTag("generalTracks"));
  desc.addUntracked<edm::InputTag>("mvaValues",edm::InputTag("generalTracks","MVAValues"));
  descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrintOutTracks_MVA);
