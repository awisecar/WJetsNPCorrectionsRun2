// -*- C++ -*-
#include "Rivet/Analysis.hh"
#include "Rivet/Projections/FinalState.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/Projections/WFinder.hh"
#include "Rivet/AnalysisLoader.hh"
#include "Rivet/AnalysisInfo.hh"
#include "Rivet/Tools/RivetYODA.hh"
#include <iostream>

namespace Rivet {

  class CMS_SMP_WJetsAlphaS_Run2_NPCorrections : public Analysis {
  public:

    CMS_SMP_WJetsAlphaS_Run2_NPCorrections()
      : Analysis("CMS_SMP_WJetsAlphaS_Run2_NPCorrections")
    {    }

  public:

    void init() {

      // Initialise and register projections
      FinalState fs;
      WFinder wfinder_mu(fs, Cuts::abseta < 2.4 && Cuts::pT > 0*GeV, PID::MUON, 0*GeV, 1000000*GeV, 0*GeV, 0.1, WFinder::CLUSTERNODECAY, WFinder::TRACK, WFinder::TRANSMASS);
      addProjection(wfinder_mu, "WFinder_mu");

      // Define veto FS
      VetoedFinalState vfs;
      vfs.addVetoOnThisFinalState(wfinder_mu);
      vfs.addVetoPairId(PID::MUON);
      vfs.vetoNeutrinos();

      // Grab jet collections from this lepton-cleaned FinalState object
      // AK4 jets
      FastJets fastjets(vfs, FastJets::ANTIKT, 0.4);
      addProjection(fastjets, "Jets");
      // AK8 jets
      FastJets fastjetsAK8(vfs, FastJets::ANTIKT, 0.8);
      addProjection(fastjetsAK8, "JetsAK8");

      // Jet multiplicity distributions
      _hist_Mult_exc              = bookHisto1D("d01-x01-y01");
      _hist_Mult_exc_AK8          = bookHisto1D("d51-x01-y01");

      // AK4 inclusive jet distributions
      _hist_JetPt_1j              = bookHisto1D("d02-x01-y01");
      _hist_JetPt_2j              = bookHisto1D("d03-x01-y01");
      _hist_JetPt_3j              = bookHisto1D("d04-x01-y01");
      _hist_LepPtJetPt_1j         = bookHisto1D("d06-x01-y01");
      _hist_LepPtJetPt_2j         = bookHisto1D("d07-x01-y01");
      _hist_LepPtJetPt_3j         = bookHisto1D("d08-x01-y01");
      _hist_Ht2_2j                = bookHisto1D("d10-x01-y01");
      _hist_Ht2_3j                = bookHisto1D("d11-x01-y01");
      _hist_LepPtHt2_2j           = bookHisto1D("d13-x01-y01");
      _hist_LepPtHt2_3j           = bookHisto1D("d14-x01-y01");
      _hist_WPt_1j                = bookHisto1D("d16-x01-y01");
      _hist_WPt_2j                = bookHisto1D("d17-x01-y01");
      _hist_WPt_3j                = bookHisto1D("d18-x01-y01");
      _hist_WPtJetPt_1j           = bookHisto1D("d20-x01-y01");
      _hist_WPtJetPt_2j           = bookHisto1D("d21-x01-y01");
      _hist_WPtJetPt_3j           = bookHisto1D("d22-x01-y01");
      _hist_WPtHt2_2j             = bookHisto1D("d24-x01-y01");
      _hist_WPtHt2_3j             = bookHisto1D("d25-x01-y01");

      // AK4 exclusive jet distributions
      _hist_JetPt_Exc_1j          = bookHisto1D("d27-x01-y01");
      _hist_JetPt_Exc_2j          = bookHisto1D("d28-x01-y01");
      _hist_JetPt_Exc_3j          = bookHisto1D("d29-x01-y01");
      _hist_LepPtJetPt_Exc_1j     = bookHisto1D("d31-x01-y01");
      _hist_LepPtJetPt_Exc_2j     = bookHisto1D("d32-x01-y01");
      _hist_LepPtJetPt_Exc_3j     = bookHisto1D("d33-x01-y01");

      // AK8 inclusive jet distributions
      _hist_JetPt_1j_AK8          = bookHisto1D("d52-x01-y01");
      _hist_JetPt_2j_AK8          = bookHisto1D("d53-x01-y01");
      _hist_JetPt_3j_AK8          = bookHisto1D("d54-x01-y01");
      _hist_LepPtJetPt_1j_AK8     = bookHisto1D("d56-x01-y01");
      _hist_LepPtJetPt_2j_AK8     = bookHisto1D("d57-x01-y01");
      _hist_LepPtJetPt_3j_AK8     = bookHisto1D("d58-x01-y01");
      _hist_Ht2_2j_AK8            = bookHisto1D("d60-x01-y01");
      _hist_Ht2_3j_AK8            = bookHisto1D("d61-x01-y01");
      _hist_LepPtHt2_2j_AK8       = bookHisto1D("d63-x01-y01");
      _hist_LepPtHt2_3j_AK8       = bookHisto1D("d64-x01-y01");
      _hist_WPt_1j_AK8            = bookHisto1D("d66-x01-y01");
      _hist_WPt_2j_AK8            = bookHisto1D("d67-x01-y01");
      _hist_WPt_3j_AK8            = bookHisto1D("d68-x01-y01");
      _hist_WPtJetPt_1j_AK8       = bookHisto1D("d70-x01-y01");
      _hist_WPtJetPt_2j_AK8       = bookHisto1D("d71-x01-y01");
      _hist_WPtJetPt_3j_AK8       = bookHisto1D("d72-x01-y01");
      _hist_WPtHt2_2j_AK8         = bookHisto1D("d74-x01-y01");
      _hist_WPtHt2_3j_AK8         = bookHisto1D("d75-x01-y01");

      // AK8 exclusive jet distributions
      _hist_JetPt_Exc_1j_AK8      = bookHisto1D("d77-x01-y01");
      _hist_JetPt_Exc_2j_AK8      = bookHisto1D("d78-x01-y01");
      _hist_JetPt_Exc_3j_AK8      = bookHisto1D("d79-x01-y01");
      _hist_LepPtJetPt_Exc_1j_AK8 = bookHisto1D("d81-x01-y01");
      _hist_LepPtJetPt_Exc_2j_AK8 = bookHisto1D("d82-x01-y01");
      _hist_LepPtJetPt_Exc_3j_AK8 = bookHisto1D("d83-x01-y01");
        
    } //end void init

    /// Perform the per-event analysis
    void analyze(const Event& event) {

      const double weight = event.weight();
      const WFinder& wfinder_mu = applyProjection<WFinder>(event, "WFinder_mu");

      if (wfinder_mu.bosons().size() != 1) {
        vetoEvent;
      }

      if (wfinder_mu.bosons().size() == 1) {

        const FourMomentum& wBoson = wfinder_mu.boson().momentum();
        double wBosonPt = wBoson.pT();

        const FourMomentum& lepton0 = wfinder_mu.constituentLepton().momentum();
        double WmT = wfinder_mu.mT();

        //W transverse mass cut
        if (WmT < 50.0*GeV) vetoEvent;

        double pt0 = lepton0.pT();
        double eta0 = lepton0.eta();

        //muon pT and eta cuts
        if ( (fabs(eta0) > 2.4) || (pt0 < 25.0*GeV) ) vetoEvent;

        // Obtain the jets (AK4 and AK8)
        vector<FourMomentum> finaljet_list;
        vector<FourMomentum> finaljet_list_AK8;

        // AK4 jets -----
        // loop over jets in an event, pushback in finaljet_list collection
        foreach (const Jet& j, applyProjection<FastJets>(event, "Jets").jetsByPt(30.0*GeV)) {
          const double jrap = j.momentum().rap();
          const double jpt = j.momentum().pT();
          //jet pT and dR(j,mu) cuts
          if ( (fabs(jrap) < 2.4) && (deltaR(lepton0, j.momentum()) > 0.4) ) {
            if (jpt > 30.0*GeV) {
              finaljet_list.push_back(j.momentum());
            }
          }
        } // end looping over jets

        // AK8 jets -----
        // loop over jets in an event, pushback in finaljet_list_AK8 collection
        foreach (const Jet& j, applyProjection<FastJets>(event, "JetsAK8").jetsByPt(200.0*GeV)) {
          const double jrap = j.momentum().rap();
          const double jpt = j.momentum().pT();
          //jet pT and dR(j,mu) cuts
          if ( (fabs(jrap) < 2.4) && (deltaR(lepton0, j.momentum()) > 0.8) ) {
            if (jpt > 200.0*GeV) {
              finaljet_list_AK8.push_back(j.momentum());
            }
          }
        } // end looping over jets
          
        // --------------- FILL HISTOGRAMS ---------------

        // Exc jet multiplicity plots
        _hist_Mult_exc->fill(finaljet_list.size(), weight);
        _hist_Mult_exc_AK8->fill(finaljet_list_AK8.size(), weight);

        // --------------- AK4 DISTRIBUTIONS ---------------

        if(finaljet_list.size() >= 1) {
          // inclusive
          _hist_JetPt_1j->fill(finaljet_list[0].pT(), weight);
          _hist_LepPtJetPt_1j->fill(pt0+finaljet_list[0].pT(), weight);
          _hist_WPt_1j->fill(wBosonPt, weight);
          _hist_WPtJetPt_1j->fill(wBosonPt+finaljet_list[0].pT(), weight);
          // exclusive
          if(finaljet_list.size() == 1) {
            _hist_JetPt_Exc_1j->fill(finaljet_list[0].pT(), weight);
            _hist_LepPtJetPt_Exc_1j->fill(pt0+finaljet_list[0].pT(), weight);
          }
        }

        if(finaljet_list.size() >= 2) {
          // inclusive
          _hist_JetPt_2j->fill(finaljet_list[0].pT(), weight);
          _hist_LepPtJetPt_2j->fill(pt0+finaljet_list[0].pT(), weight);
          _hist_Ht2_2j->fill((finaljet_list[0].pT()+finaljet_list[1].pT())/2., weight);
          _hist_LepPtHt2_2j->fill(pt0+(finaljet_list[0].pT()+finaljet_list[1].pT())/2., weight);
          _hist_WPt_2j->fill(wBosonPt, weight);
          _hist_WPtJetPt_2j->fill(wBosonPt+finaljet_list[0].pT(), weight);
          _hist_WPtHt2_2j->fill(wBosonPt+(finaljet_list[0].pT()+finaljet_list[1].pT())/2., weight);
          // exclusive
          if(finaljet_list.size() == 2) {
            _hist_JetPt_Exc_2j->fill(finaljet_list[0].pT(), weight);
            _hist_LepPtJetPt_Exc_2j->fill(pt0+finaljet_list[0].pT(), weight);
          }
        } 

        if(finaljet_list.size() >= 3) {
          // inclusive
          _hist_JetPt_3j->fill(finaljet_list[0].pT(), weight);
          _hist_LepPtJetPt_3j->fill(pt0+finaljet_list[0].pT(), weight);
          _hist_Ht2_3j->fill((finaljet_list[0].pT()+finaljet_list[1].pT())/2., weight);
          _hist_LepPtHt2_3j->fill(pt0+(finaljet_list[0].pT()+finaljet_list[1].pT())/2., weight);
          _hist_WPt_3j->fill(wBosonPt, weight);
          _hist_WPtJetPt_3j->fill(wBosonPt+finaljet_list[0].pT(), weight);
          _hist_WPtHt2_3j->fill(wBosonPt+(finaljet_list[0].pT()+finaljet_list[1].pT())/2., weight);
          // exclusive
          if(finaljet_list.size() == 3) {
            _hist_JetPt_Exc_3j->fill(finaljet_list[0].pT(), weight);
            _hist_LepPtJetPt_Exc_3j->fill(pt0+finaljet_list[0].pT(), weight);
          }
        }

        // --------------- AK8 DISTRIBUTIONS ---------------

        if(finaljet_list_AK8.size() >= 1) {
          // inclusive
          _hist_JetPt_1j_AK8->fill(finaljet_list_AK8[0].pT(), weight);
          _hist_LepPtJetPt_1j_AK8->fill(pt0+finaljet_list_AK8[0].pT(), weight);
          _hist_WPt_1j_AK8->fill(wBosonPt, weight);
          _hist_WPtJetPt_1j_AK8->fill(wBosonPt+finaljet_list_AK8[0].pT(), weight);
          // exclusive
          if(finaljet_list_AK8.size() == 1) {
            _hist_JetPt_Exc_1j_AK8->fill(finaljet_list_AK8[0].pT(), weight);
            _hist_LepPtJetPt_Exc_1j_AK8->fill(pt0+finaljet_list_AK8[0].pT(), weight);
          }
        }

        if(finaljet_list_AK8.size() >= 2) {
          // inclusive
          _hist_JetPt_2j_AK8->fill(finaljet_list_AK8[0].pT(), weight);
          _hist_LepPtJetPt_2j_AK8->fill(pt0+finaljet_list_AK8[0].pT(), weight);
          _hist_Ht2_2j_AK8->fill((finaljet_list_AK8[0].pT()+finaljet_list_AK8[1].pT())/2., weight);
          _hist_LepPtHt2_2j_AK8->fill(pt0+(finaljet_list_AK8[0].pT()+finaljet_list_AK8[1].pT())/2., weight);
          _hist_WPt_2j_AK8->fill(wBosonPt, weight);
          _hist_WPtJetPt_2j_AK8->fill(wBosonPt+finaljet_list_AK8[0].pT(), weight);
          _hist_WPtHt2_2j_AK8->fill(wBosonPt+(finaljet_list_AK8[0].pT()+finaljet_list_AK8[1].pT())/2., weight);
          // exclusive
          if(finaljet_list_AK8.size() == 2) {
            _hist_JetPt_Exc_2j_AK8->fill(finaljet_list_AK8[0].pT(), weight);
            _hist_LepPtJetPt_Exc_2j_AK8->fill(pt0+finaljet_list_AK8[0].pT(), weight);
          }
        } 

        if(finaljet_list_AK8.size() >= 3) {
          // inclusive
          _hist_JetPt_3j_AK8->fill(finaljet_list_AK8[0].pT(), weight);
          _hist_LepPtJetPt_3j_AK8->fill(pt0+finaljet_list_AK8[0].pT(), weight);
          _hist_Ht2_3j_AK8->fill((finaljet_list_AK8[0].pT()+finaljet_list_AK8[1].pT())/2., weight);
          _hist_LepPtHt2_3j_AK8->fill(pt0+(finaljet_list_AK8[0].pT()+finaljet_list_AK8[1].pT())/2., weight);
          _hist_WPt_3j_AK8->fill(wBosonPt, weight);
          _hist_WPtJetPt_3j_AK8->fill(wBosonPt+finaljet_list_AK8[0].pT(), weight);
          _hist_WPtHt2_3j_AK8->fill(wBosonPt+(finaljet_list_AK8[0].pT()+finaljet_list_AK8[1].pT())/2., weight);
          // exclusive
          if(finaljet_list_AK8.size() == 3) {
            _hist_JetPt_Exc_3j_AK8->fill(finaljet_list_AK8[0].pT(), weight);
            _hist_LepPtJetPt_Exc_3j_AK8->fill(pt0+finaljet_list_AK8[0].pT(), weight);
          }
        }

      } // close the Wboson loop
    } // end void analyze

    /// Normalise histograms etc., after the run
    void finalize() {
      const double crossec = !std::isnan(crossSectionPerEvent()) ? crossSection() : 5198.46*picobarn; /// 5198.46 pb +- ( 59.3346 pb = 1.14 % )
      if (std::isnan(crossSectionPerEvent())){
        MSG_INFO("crossSectionPerEvent() is NaN, using " << crossec/picobarn << " pb");
      }

      // Jet multiplicity distributions
      scale(_hist_Mult_exc, crossec/picobarn/sumOfWeights());
      scale(_hist_Mult_exc_AK8, crossec/picobarn/sumOfWeights());

      // AK4 inclusive jet distributions
      scale(_hist_JetPt_1j, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_1j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_Ht2_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_Ht2_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtHt2_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtHt2_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPt_1j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPt_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPt_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtJetPt_1j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtJetPt_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtJetPt_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtHt2_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtHt2_3j, crossec/picobarn/sumOfWeights());

      // AK4 exclusive jet distributions
      scale(_hist_JetPt_Exc_1j, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_Exc_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_Exc_3j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_Exc_1j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_Exc_2j, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_Exc_3j, crossec/picobarn/sumOfWeights());
      
      // AK8 inclusive jet distributions
      scale(_hist_JetPt_1j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_1j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_Ht2_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_Ht2_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtHt2_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtHt2_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPt_1j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPt_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPt_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtJetPt_1j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtJetPt_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtJetPt_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtHt2_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_WPtHt2_3j_AK8, crossec/picobarn/sumOfWeights());

      // AK8 exclusive jet distributions
      scale(_hist_JetPt_Exc_1j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_Exc_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_JetPt_Exc_3j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_Exc_1j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_Exc_2j_AK8, crossec/picobarn/sumOfWeights());
      scale(_hist_LepPtJetPt_Exc_3j_AK8, crossec/picobarn/sumOfWeights());

    } //end void finalize

  private:

    // Jet multiplicity distributions
    Histo1DPtr _hist_Mult_exc;
    Histo1DPtr _hist_Mult_exc_AK8;

    // AK4 inclusive jet mult. histos
    Histo1DPtr _hist_JetPt_1j;
    Histo1DPtr _hist_JetPt_2j;
    Histo1DPtr _hist_JetPt_3j;
    Histo1DPtr _hist_LepPtJetPt_1j;
    Histo1DPtr _hist_LepPtJetPt_2j;
    Histo1DPtr _hist_LepPtJetPt_3j;
    Histo1DPtr _hist_Ht2_2j;
    Histo1DPtr _hist_Ht2_3j;
    Histo1DPtr _hist_LepPtHt2_2j;
    Histo1DPtr _hist_LepPtHt2_3j;
    Histo1DPtr _hist_WPt_1j;
    Histo1DPtr _hist_WPt_2j;
    Histo1DPtr _hist_WPt_3j;
    Histo1DPtr _hist_WPtJetPt_1j;
    Histo1DPtr _hist_WPtJetPt_2j;
    Histo1DPtr _hist_WPtJetPt_3j;
    Histo1DPtr _hist_WPtHt2_2j;
    Histo1DPtr _hist_WPtHt2_3j;

    // AK4 exclusive jet mult. histos
    Histo1DPtr _hist_JetPt_Exc_1j;
    Histo1DPtr _hist_JetPt_Exc_2j;
    Histo1DPtr _hist_JetPt_Exc_3j;
    Histo1DPtr _hist_LepPtJetPt_Exc_1j;
    Histo1DPtr _hist_LepPtJetPt_Exc_2j;
    Histo1DPtr _hist_LepPtJetPt_Exc_3j;

    // AK8 inclusive jet mult. histos
    Histo1DPtr _hist_JetPt_1j_AK8;
    Histo1DPtr _hist_JetPt_2j_AK8;
    Histo1DPtr _hist_JetPt_3j_AK8;
    Histo1DPtr _hist_LepPtJetPt_1j_AK8;
    Histo1DPtr _hist_LepPtJetPt_2j_AK8;
    Histo1DPtr _hist_LepPtJetPt_3j_AK8;
    Histo1DPtr _hist_Ht2_2j_AK8;
    Histo1DPtr _hist_Ht2_3j_AK8;
    Histo1DPtr _hist_LepPtHt2_2j_AK8;
    Histo1DPtr _hist_LepPtHt2_3j_AK8;
    Histo1DPtr _hist_WPt_1j_AK8;
    Histo1DPtr _hist_WPt_2j_AK8;
    Histo1DPtr _hist_WPt_3j_AK8;
    Histo1DPtr _hist_WPtJetPt_1j_AK8;
    Histo1DPtr _hist_WPtJetPt_2j_AK8;
    Histo1DPtr _hist_WPtJetPt_3j_AK8;
    Histo1DPtr _hist_WPtHt2_2j_AK8;
    Histo1DPtr _hist_WPtHt2_3j_AK8;

    // AK8 exclusive jet mult. histos
    Histo1DPtr _hist_JetPt_Exc_1j_AK8;
    Histo1DPtr _hist_JetPt_Exc_2j_AK8;
    Histo1DPtr _hist_JetPt_Exc_3j_AK8;
    Histo1DPtr _hist_LepPtJetPt_Exc_1j_AK8;
    Histo1DPtr _hist_LepPtJetPt_Exc_2j_AK8;
    Histo1DPtr _hist_LepPtJetPt_Exc_3j_AK8;

  }; //end class

  // The hook for the plugin system
  DECLARE_RIVET_PLUGIN(CMS_SMP_WJetsAlphaS_Run2_NPCorrections);

} //end Rivet
