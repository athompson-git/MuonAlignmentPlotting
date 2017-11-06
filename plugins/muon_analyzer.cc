// -*- C++ -*-
//
// Package:    analysis/muon_analyzer
// Class:      muon_analyzer
//
/**\class muon_analyzer muon_analyzer.cc analysis/muon_analyzer/plugins/muon_analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Adrian Thompson
//         Created:  Sun, 05 Nov 2017 20:47:11 GMT
//
//


// system include files
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include <vector>

// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class muon_analyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit muon_analyzer(const edm::ParameterSet&);
      ~muon_analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      // ----------member data ---------------------------
      TH1D * histo;
      // 1. Create a token to hold a vector of global muon Tracks.
      edm::EDGetTokenT<std::vector<reco::Track>> globalmuon_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

// 2. Tell the token to consume the "globalmuon" input tag defined in the python cfg file.
muon_analyzer::muon_analyzer(const edm::ParameterSet& iConfig) :
globalmuon_(consumes<std::vector<reco::Track>>(iConfig.getParameter<edm::InputTag>("globalmuon")))
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   // 3. Make a histogram.
   histo = fs->make<TH1D>("pt", "Muon Pt", 100, 250, 1000);
   hist->GetXaxis->SetTitle("Muon Pt (GeV/c)");
   hist->GetYaxis->SetTitle("Events");
}


muon_analyzer::~muon_analyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void muon_analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
   using namespace edm;

   // 4. Make a handle of the same object type as the token.
   edm::Handle<std::vector<reco::Track>> globalmuon;

   // 5. Get the data by token; this uses getByToken(token, handle).
   iEvent.getByToken(globalmuon_, globalmuon);

   // 6. Main event loop. Make an iterator on the handle and fill the histogram.
   for(std::vector<reco::Track>::const_iterator itTrack = globalmuon->begin();
       itTrack != globalmuon->end(); ++itTrack ) {
       printf("PT = %f \n", itTrack->pt());
       histo->Fill(itTrack->pt());
   }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
muon_analyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
muon_analyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
muon_analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(muon_analyzer);
