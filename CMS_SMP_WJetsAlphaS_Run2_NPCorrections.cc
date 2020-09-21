// -*- C++ -*-

//********** Apichart Hortiangtham **********

//************* WJets@13TeV ************

#include "Rivet/AnalysisInfo.hh"
#include "Rivet/Analysis.hh"
#include "Rivet/Tools/RivetYODA.hh"
#include "Rivet/Tools/Logging.hh"
#include "Rivet/Projections/FinalState.hh"
// @todo Include more projections as required, e.g. ChargedFinalState, FastJets, ZFinder...
#include "Rivet/Particle.fhh"
#include "Rivet/Projections/Beam.hh"
#include "Rivet/ParticleName.hh"
#include "Rivet/Projections/WFinder.hh"
#include "Rivet/Projections/FastJets.hh"
#include "Rivet/Projections/VetoedFinalState.hh"
#include "Rivet/AnalysisLoader.hh"
//#include "Rivet/RivetAIDA.hh"

#include <iostream>

namespace Rivet {
    
    
    class CMS_SMP_WJetsAlphaS_Run2_NPCorrections: public Analysis {
        public:
        
            // Constructors
            CMS_SMP_WJetsAlphaS_Run2_NPCorrections()
                : Analysis("CMS_SMP_WJetsAlphaS_Run2_NPCorrections")
            {
                //setBeams(PID::PROTON, PID::PROTON);
                setNeedsCrossSection(true);
            }
        
        public:
        
            // Book histograms and initialise projections before the run
            void init() {
                
                FinalState fs;
                //WFinder wfinder_mu(fs, -2.4, 2.4, 0*GeV, MUON, 50*GeV, 1000000*GeV, 0*GeV, 0.1, 1, true, false);
                //WFinder wfinder_mu(fs, -2.4, 2.4, 0*GeV, MUON, 50*GeV, 1000000*GeV, 0*GeV, 0.1, true, false, 80.4, true);
                //WFinder wfinder_mu(fs, -2.4, 2.4, 0*GeV,                            MUON, 0*GeV, 1000000*GeV, 0*GeV, 0.1, true, false);
                WFinder wfinder_mu(fs, Cuts::abseta < 2.4 && Cuts::pT > 0*GeV, PID::MUON, 0*GeV, 1000000*GeV, 0*GeV, 0.1, WFinder::CLUSTERNODECAY, WFinder::NOTRACK, WFinder::TRANSMASS);
                // WFinder (const FinalState &inputfs, const Cut &leptoncuts, PdgId pid, double minmass, double maxmass, double missingET, double dRmax=0.1, ClusterPhotons clusterPhotons=CLUSTERNODECAY, PhotonTracking trackPhotons=NOTRACK, MassWindow masstype=MASS, double masstarget=80.4 *GeV)
                addProjection(wfinder_mu, "WFinder_mu");
                
                
                // Define veto FS
                VetoedFinalState vfs;
                vfs.addVetoOnThisFinalState(wfinder_mu);
                vfs.addVetoPairId(PID::MUON);
                vfs.vetoNeutrinos();
                
                FastJets fastjets(vfs, FastJets::ANTIKT, 0.4);
                addProjection(fastjets, "Jets");
                
                // ---- book all the required histograms with correct binning ----
                // define binning and book Histos
                vector<double> jetPt_Winc1jet ;
                vector<double> jetPt_Winc2jet ;
                vector<double> jetPt_Winc3jet ;
                
                vector<double> jetHT_Winc1jet ;
                vector<double> jetHT_Winc2jet ;
                vector<double> jetHT_Winc3jet ;

				jetPt_Winc1jet += 20, 24, 30, 39, 49, 62, 79, 105, 138, 181, 231, 294, 375, 550, 900;
                jetPt_Winc2jet += 20, 24, 30, 39, 49, 62, 78, 105, 142, 185, 235, 300, 380, 500;
                jetPt_Winc3jet += 20, 24, 30, 41, 59, 81, 110, 152, 200, 300;

                jetHT_Winc1jet += 30, 39, 49, 62, 78, 96, 118, 150, 190, 240, 300, 370, 450, 540, 650, 820, 1100, 1500;
                jetHT_Winc2jet += 60, 78, 96, 118, 150, 190, 240, 300, 370, 450, 540, 650, 800, 1200;
                jetHT_Winc3jet += 90, 118, 168, 220, 300, 400, 550, 780, 1100;

                _hist_JetPt1j =bookHisto1D("jet_Pt1jetcase", jetPt_Winc1jet);
                _hist_JetPt2j =bookHisto1D("jet_Pt2jetcase", jetPt_Winc2jet);
                _hist_JetPt3j =bookHisto1D("jet_Pt3jetcase", jetPt_Winc3jet);
               
                _hist_Ht_1j =bookHisto1D("JetsHT_inc1jet", jetHT_Winc1jet);
                _hist_Ht_2j =bookHisto1D("JetsHT_inc2jet", jetHT_Winc2jet);
                _hist_Ht_3j =bookHisto1D("JetsHT_inc3jet", jetHT_Winc3jet);
                
                //-------------
                _hist_inc_WJetMult = bookHisto1D("njetWJet_incl", 7, -0.5, 6.5);
                _hist_excl_WJetMult= bookHisto1D("njetWJet_excl", 7, -0.5, 6.5);
                _hist_Mult_exc = bookHisto1D("njet_exc_fbin", 7, -0.5, 6.5);
                
                //-------------
                _hist_JetRap1j =bookHisto1D("jet_Rap1jetcase", 12, 0, 2.4);
                _hist_JetRap2j =bookHisto1D("jet_Rap2jetcase", 12, 0, 2.4);
                _hist_JetRap3j =bookHisto1D("jet_Rap3jetcase", 8, 0., 2.4);
				
				//-------------
				_hist_dphij1mu_1j =bookHisto1D("dphij1mu_inc1jet", 20, 0, 3.14159265359);
				_hist_dphij2mu_2j =bookHisto1D("dphij2mu_inc2jet", 20, 0, 3.14159265359);
				_hist_dphij3mu_3j =bookHisto1D("dphij3mu_inc3jet", 16, 0, 3.14159265359);
				
				//-------------
				_hist_dRmuj_1j =bookHisto1D("dRmuj_inc1jet", 20, 0, 4.0);
				
                //-------------
                _hist_coutEvnt        = bookHisto1D("coutEvnt", 7, 0.5, 7.5);
                _hist_countWeightEvnt = bookHisto1D("countWeightEvnt", 7, 0.5, 7.5);
               
            }
        
            // define function used for filiing inc Njets histo
            void Fill(Histo1DPtr& _histJetMult, const double& weight, std::vector<FourMomentum>& finaljet_list){
                _histJetMult->fill(0, weight);
                for (size_t i=0 ; i<finaljet_list.size() ; ++i) {
                    if (i==6) break;
                    _histJetMult->fill(i+1, weight);  // inclusive multiplicity
                }
            }
            
            
            /// Perform the per-event analysis
            void analyze(const Event& event) {
                
                //cout << " beamIdpairs " << beamIds().first << " " << beamIds().second << " energy " << sqrtS() << endl;
                
                const double weight = event.weight();
                const WFinder& wfinder_mu = applyProjection<WFinder>(event, "WFinder_mu");
                
                _hist_coutEvnt->fill(1, 1.0);
                _hist_countWeightEvnt->fill(1, weight);
                
                if (wfinder_mu.bosons().size() != 1) {
                    vetoEvent;
                }
                
                _hist_coutEvnt->fill(2, 1.0);
                _hist_countWeightEvnt->fill(2, weight);
                
                if (wfinder_mu.bosons().size() == 1) {
                    
                    const FourMomentum& lepton0 = wfinder_mu.constituentLeptons()[0].momentum();
                    const FourMomentum& neutrino = wfinder_mu.constituentNeutrinos()[0].momentum();
                    double WmT = sqrt( 2 * lepton0.pT() * neutrino.pT() * (1 - cos(deltaPhi(lepton0, neutrino))) );
                    
                    if (WmT < 50.0*GeV) vetoEvent;
                    _hist_coutEvnt->fill(3, 1.0);
                    _hist_countWeightEvnt->fill(3, weight);
                    
                    double pt0 = lepton0.pT();
                    double eta0 = lepton0.eta();
                    
                    if ( (fabs(eta0) > 2.4) || (pt0 < 25.0*GeV) ) vetoEvent;
                    _hist_coutEvnt->fill(4, 1.0); // this is inclusive 0j events
                    _hist_countWeightEvnt->fill(4, weight);
                    
                    // Obtain the jets.
                    vector<FourMomentum> finaljet_list;
					vector<FourMomentum> jet100_list;
                    double HT = 0.0;
                    
                    // loop over jets in an event, pushback in finaljet_list collection
                    foreach (const Jet& j, applyProjection<FastJets>(event, "Jets").jetsByPt(30.0*GeV)) {
                        const double jrap = j.momentum().rap();
                        const double jpt = j.momentum().pT();
                        
                        if ( (fabs(jrap) < 2.4) && (deltaR(lepton0, j.momentum()) > 0.4) ) {
                            
                            if(jpt > 30.0*GeV) {
                                finaljet_list.push_back(j.momentum());
                                HT += j.momentum().pT();
                            }
							if(jpt > 100.0*GeV) {
								jet100_list.push_back(j.momentum());
							}
                        }
                    } // end looping over jets
					
					//---------------------- FILL HISTOGRAMS ------------------
					
                    // Multiplicity exc plot.
                    _hist_excl_WJetMult->fill(finaljet_list.size(), weight);
					
					// Multiplicity exc plot with last bin inc.
                    if(finaljet_list.size()<=6) {
                        _hist_Mult_exc->fill(finaljet_list.size(), weight);
                    }
                    else if (finaljet_list.size()>6){
                        _hist_Mult_exc->fill(6., weight);
                    }
                    
                    // Multiplicity inc plot.
                    Fill(_hist_inc_WJetMult, weight, finaljet_list);
					
					// dRmuj plot.
					double mindR(99999);
					if(jet100_list.size()>=1) {
						for (unsigned ji = 0; ji < jet100_list.size(); ji++){
							double dr_(9999);
							dr_ = fabs(deltaR(lepton0, jet100_list[ji]));
							if (dr_ < mindR){
								mindR = dr_;
							}
						}
						if(jet100_list[0].pT() > 300.0*GeV){
							_hist_dRmuj_1j->fill(mindR, weight);
						}
					}
					
                    if(finaljet_list.size()>=1) {
                        _hist_JetPt1j->fill(finaljet_list[0].pT(), weight);
                        _hist_JetRap1j->fill(fabs(finaljet_list[0].rap()), weight);
                        _hist_Ht_1j->fill(HT, weight);
						_hist_dphij1mu_1j->fill(deltaPhi(finaljet_list[0].phi(), lepton0.phi()), weight);
                    }
                    
                    if(finaljet_list.size()>=2) {
                        _hist_JetPt2j->fill(finaljet_list[1].pT(), weight);
                        _hist_JetRap2j->fill(fabs(finaljet_list[1].rap()), weight);
                        _hist_Ht_2j->fill(HT, weight);
						_hist_dphij2mu_2j->fill(deltaPhi(finaljet_list[1].phi(), lepton0.phi()), weight);
                    }
                    
                    if(finaljet_list.size()>=3) {
                        _hist_JetPt3j->fill(finaljet_list[2].pT(), weight);
                        _hist_JetRap3j->fill(fabs(finaljet_list[2].rap()), weight);
                        _hist_Ht_3j->fill(HT, weight);
						_hist_dphij3mu_3j->fill(deltaPhi(finaljet_list[2].phi(), lepton0.phi()), weight);
                    }
                } // close the Wboson loop
                
            } // void loop
        
        
            /// Normalise histograms etc., after the run
            void finalize() {
                
                double crossSec=60290.0;
                
                scale(_hist_inc_WJetMult, crossSec/sumOfWeights());
                scale(_hist_excl_WJetMult, crossSec/sumOfWeights());
                scale(_hist_Mult_exc, crossSec/sumOfWeights());
                
                scale(_hist_JetPt1j, crossSec/sumOfWeights());
                scale(_hist_JetPt2j, crossSec/sumOfWeights());
                scale(_hist_JetPt3j, crossSec/sumOfWeights());
                
                scale(_hist_JetRap1j, crossSec/sumOfWeights());
                scale(_hist_JetRap2j, crossSec/sumOfWeights());
                scale(_hist_JetRap3j, crossSec/sumOfWeights());
                
                scale(_hist_Ht_1j, crossSec/sumOfWeights());
                scale(_hist_Ht_2j, crossSec/sumOfWeights());
                scale(_hist_Ht_3j, crossSec/sumOfWeights());
				
				scale(_hist_dphij1mu_1j, crossSec/sumOfWeights());
				scale(_hist_dphij2mu_2j, crossSec/sumOfWeights());
				scale(_hist_dphij3mu_3j, crossSec/sumOfWeights());
				
				scale(_hist_dRmuj_1j, crossSec/sumOfWeights());
            }
        
        private:
            
            // Data members like post-cuts event weight counters go here
        
        private:
        
            Histo1DPtr _hist_coutEvnt;
            Histo1DPtr _hist_countWeightEvnt;
        
            Histo1DPtr _hist_inc_WJetMult;
            Histo1DPtr _hist_excl_WJetMult;
            Histo1DPtr _hist_Mult_exc;
            
            Histo1DPtr _hist_JetPt1j;
            Histo1DPtr _hist_JetPt2j;
            Histo1DPtr _hist_JetPt3j;
            
            Histo1DPtr _hist_JetRap1j;
            Histo1DPtr _hist_JetRap2j;
            Histo1DPtr _hist_JetRap3j;
        
            Histo1DPtr _hist_Ht_1j;
            Histo1DPtr _hist_Ht_2j;
            Histo1DPtr _hist_Ht_3j;
		
			Histo1DPtr _hist_dphij1mu_1j;
			Histo1DPtr _hist_dphij2mu_2j;
			Histo1DPtr _hist_dphij3mu_3j;
		
			Histo1DPtr _hist_dRmuj_1j;
            //-------------------------------------

    };
    
    // This global object acts as a hook for the plugin system
    AnalysisBuilder<CMS_SMP_WJetsAlphaS_Run2_NPCorrections> plugin_CMS_SMP_WJetsAlphaS_Run2_NPCorrections;
    
}
