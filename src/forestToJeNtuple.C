#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "include/jetData.h"
#include "include/etaPhiFunc.h"

int forestToJeNtuple(const std::string inFileName)
{
  const std::string outFileName = "outFile.root";
  TFile* outFile_p = new TFile(outFileName.c_str(), "RECREATE");

  Int_t hiBin_;
  jetData jData;
  const Int_t nMaxJets = 500;
  Float_t maxPFPt_[nMaxJets];
  Float_t maxPF1Pt_[nMaxJets];
  Float_t maxPF2Pt_[nMaxJets];
  Float_t maxPF3Pt_[nMaxJets];
  Float_t maxPF4Pt_[nMaxJets];
  Float_t maxPF5Pt_[nMaxJets];

  Float_t sumPFPt_[nMaxJets];
  Float_t sumPF1Pt_[nMaxJets];
  Float_t sumPF2Pt_[nMaxJets];
  Float_t sumPF3Pt_[nMaxJets];
  Float_t sumPF4Pt_[nMaxJets];
  Float_t sumPF5Pt_[nMaxJets];

  Float_t sumRing1Pt_[nMaxJets];
  Float_t sumRing2Pt_[nMaxJets];
  Float_t sumRing3Pt_[nMaxJets];

  TTree* outTree_p = new TTree("outTree", "");

  outTree_p->Branch("hiBin", &hiBin_, "hiBin/I");
  outTree_p->Branch("nref", &jData.nref, "nref/I");
  outTree_p->Branch("jtpt", jData.jtpt, "jtpt[nref]/F");
  outTree_p->Branch("rawpt", jData.rawpt, "rawpt[nref]/F");
  outTree_p->Branch("jtpu", jData.jtpu, "jtpu[nref]/F");
  outTree_p->Branch("jtphi", jData.jtphi, "jtphi[nref]/F");
  outTree_p->Branch("jteta", jData.jteta, "jteta[nref]/F");
  outTree_p->Branch("refpt", jData.refpt, "refpt[nref]/F");
  outTree_p->Branch("refphi", jData.refphi, "refphi[nref]/F");
  outTree_p->Branch("refeta", jData.refeta, "refeta[nref]/F");
  outTree_p->Branch("subid", jData.subid, "subid[nref]/I");
  outTree_p->Branch("refparton_flavor", jData.refparton_flavor, "refparton_flavor[nref]/I");
  outTree_p->Branch("maxPFPt", maxPFPt_, "maxPFPt[nref]/F");
  outTree_p->Branch("maxPF1Pt", maxPF1Pt_, "maxPF1Pt[nref]/F");
  outTree_p->Branch("maxPF2Pt", maxPF2Pt_, "maxPF2Pt[nref]/F");
  outTree_p->Branch("maxPF3Pt", maxPF3Pt_, "maxPF3Pt[nref]/F");
  outTree_p->Branch("maxPF4Pt", maxPF4Pt_, "maxPF4Pt[nref]/F");
  outTree_p->Branch("maxPF5Pt", maxPF5Pt_, "maxPF5Pt[nref]/F");

  outTree_p->Branch("sumPFPt", sumPFPt_, "sumPFPt[nref]/F");
  outTree_p->Branch("sumPF1Pt", sumPF1Pt_, "sumPF1Pt[nref]/F");
  outTree_p->Branch("sumPF2Pt", sumPF2Pt_, "sumPF2Pt[nref]/F");
  outTree_p->Branch("sumPF3Pt", sumPF3Pt_, "sumPF3Pt[nref]/F");
  outTree_p->Branch("sumPF4Pt", sumPF4Pt_, "sumPF4Pt[nref]/F");
  outTree_p->Branch("sumPF5Pt", sumPF5Pt_, "sumPF5Pt[nref]/F");

  outTree_p->Branch("sumRing1Pt", sumRing1Pt_, "sumRing1Pt[nref]/F");
  outTree_p->Branch("sumRing2Pt", sumRing2Pt_, "sumRing2Pt[nref]/F");
  outTree_p->Branch("sumRing3Pt", sumRing3Pt_, "sumRing3Pt[nref]/F");

  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");
  TTree* hiTree_p = (TTree*)inFile_p->Get("hiEvtAnalyzer/HiTree");
  TTree* jetTree_p = (TTree*)inFile_p->Get("akPu3PFJetAnalyzer/t");
  TTree* pfTree_p = (TTree*)inFile_p->Get("pfcandAnalyzer/pfTree");
  //  TTree* trkTree_p = (TTree*)inFile_p->Get("trackTree/anaTrack");

  hiTree_p->SetBranchStatus("*", 0);
  hiTree_p->SetBranchStatus("hiBin", 1);

  hiTree_p->SetBranchAddress("hiBin", &hiBin_);

  jetTree_p->SetBranchStatus("*", 0);
  jetTree_p->SetBranchStatus("nref", 1);
  jetTree_p->SetBranchStatus("jtpt", 1);
  jetTree_p->SetBranchStatus("rawpt", 1);
  jetTree_p->SetBranchStatus("jtpu", 1);
  jetTree_p->SetBranchStatus("jtphi", 1);
  jetTree_p->SetBranchStatus("jteta", 1);
  jetTree_p->SetBranchStatus("refpt", 1);
  jetTree_p->SetBranchStatus("refphi", 1);
  jetTree_p->SetBranchStatus("refeta", 1);
  jetTree_p->SetBranchStatus("subid", 1);
  jetTree_p->SetBranchStatus("refparton_flavor", 1);

  jetTree_p->SetBranchAddress("nref", &jData.nref);
  jetTree_p->SetBranchAddress("jtpt", jData.jtpt);
  jetTree_p->SetBranchAddress("rawpt", jData.rawpt);
  jetTree_p->SetBranchAddress("jtpu", jData.jtpu);
  jetTree_p->SetBranchAddress("jtphi", jData.jtphi);
  jetTree_p->SetBranchAddress("jteta", jData.jteta);
  jetTree_p->SetBranchAddress("refpt", jData.refpt);
  jetTree_p->SetBranchAddress("refphi", jData.refphi);
  jetTree_p->SetBranchAddress("refeta", jData.refeta);
  jetTree_p->SetBranchAddress("subid", jData.subid);
  jetTree_p->SetBranchAddress("refparton_flavor", jData.refparton_flavor);

  /*
  const Int_t nMaxTrk = 100000;
  Int_t nTrk_;
  Float_t trkPt_[nMaxTrk];
  Float_t trkPhi_[nMaxTrk];
  Float_t trkEta_[nMaxTrk];
  Bool_t highPurity_[nMaxTrk];
  Float_t trkPtError_[nMaxTrk];
  Float_t trkDz1_[nMaxTrk];
  Float_t trkDzError1_[nMaxTrk];
  Float_t trkDxy1_[nMaxTrk];
  Float_t trkDxyError1_[nMaxTrk];
  UChar_t trkNdof_[nMaxTrk];
  UChar_t trkNlayer_[nMaxTrk];
  Float_t trkChi2_[nMaxTrk];
  UChar_t trkNHit_[nMaxTrk];
  Float_t pfHcal_[nMaxTrk];
  Float_t pfEcal_[nMaxTrk];

  trkTree_p->SetBranchStatus("nTrk", 1);
  trkTree_p->SetBranchStatus("trkPt", 1);
  trkTree_p->SetBranchStatus("trkPhi", 1);
  trkTree_p->SetBranchStatus("trkEta", 1);
  trkTree_p->SetBranchStatus("highPurity", 1);
  trkTree_p->SetBranchStatus("trkPtError", 1);
  trkTree_p->SetBranchStatus("trkDz1", 1);
  trkTree_p->SetBranchStatus("trkDzError1", 1);
  trkTree_p->SetBranchStatus("trkDxy1", 1);
  trkTree_p->SetBranchStatus("trkDxyError1", 1);
  trkTree_p->SetBranchStatus("trkNdof", 1);
  trkTree_p->SetBranchStatus("trkNlayer", 1);
  trkTree_p->SetBranchStatus("trkChi2", 1);
  trkTree_p->SetBranchStatus("trkNHit", 1);
  trkTree_p->SetBranchStatus("pfHcal", 1);
  trkTree_p->SetBranchStatus("pfEcal", 1);

  trkTree_p->SetBranchAddress("nTrk", &nTrk_);
  trkTree_p->SetBranchAddress("trkPt", trkPt_);
  trkTree_p->SetBranchAddress("trkPhi", trkPhi_);
  trkTree_p->SetBranchAddress("trkEta", trkEta_);
  trkTree_p->SetBranchAddress("highPurity", highPurity_);
  trkTree_p->SetBranchAddress("trkPtError", trkPtError_);
  trkTree_p->SetBranchAddress("trkDz1", trkDz1_);
  trkTree_p->SetBranchAddress("trkDzError1", trkDzError1_);
  trkTree_p->SetBranchAddress("trkDxy1", trkDxy1_);
  trkTree_p->SetBranchAddress("trkDxyError1", trkDxyError1_);
  trkTree_p->SetBranchAddress("trkNdof", trkNdof_);
  trkTree_p->SetBranchAddress("trkNlayer", trkNlayer_);
  trkTree_p->SetBranchAddress("trkChi2", trkChi2_);
  trkTree_p->SetBranchAddress("trkNHit", trkNHit_);
  trkTree_p->SetBranchAddress("pfHcal", pfHcal_);
  trkTree_p->SetBranchAddress("pfEcal", pfEcal_);
  */

  std::vector<Float_t>* pfPt_p=0;
  std::vector<Float_t>* pfPhi_p=0;
  std::vector<Float_t>* pfEta_p=0;
  std::vector<Int_t>* pfId_p=0;
 
  pfTree_p->SetBranchStatus("*", 0);
  pfTree_p->SetBranchStatus("pfPt", 1);
  pfTree_p->SetBranchStatus("pfPhi", 1);
  pfTree_p->SetBranchStatus("pfEta", 1);
  pfTree_p->SetBranchStatus("pfId", 1);

  pfTree_p->SetBranchAddress("pfPt", &pfPt_p);
  pfTree_p->SetBranchAddress("pfPhi", &pfPhi_p);
  pfTree_p->SetBranchAddress("pfEta", &pfEta_p);
  pfTree_p->SetBranchAddress("pfId", &pfId_p);
 

  const int nEntries = jetTree_p->GetEntries();

  for(int entry = 0; entry < nEntries; ++entry){
    if(entry%1000 == 0) std::cout << "Entry: " << entry << "/" << nEntries << std::endl;
    jetTree_p->GetEntry(entry);
    hiTree_p->GetEntry(entry);
    pfTree_p->GetEntry(entry);

    /*
    std::vector<Float_t> trkPt_p;
    std::vector<Float_t> trkPhi_p;
    std::vector<Float_t> trkEta_p;

    for(int trkIter = 0; trkIter < nTrk_; ++trkIter){
      if(trkPt_[trkIter] < 0.5) continue;
      if(TMath::Abs(trkEta_[trkIter]) > 2.4) continue;
      if(!highPurity_[trkIter]) continue;
      if(trkPtError_[trkIter]/trkPt_[trkIter] > .1) continue;
      if(TMath::Abs(trkDz1_[trkIter]/trkDzError1_[trkIter]) > 3) continue;
      if(TMath::Abs(trkDxy1_[trkIter]/trkDxyError1_[trkIter]) > 3) continue;
      if(trkNHit_[trkIter] < 11) continue;
      if(trkChi2_[trkIter]/trkNdof_[trkIter]/trkNlayer_[trkIter] >= 0.15) continue;

      if(trkPt_[trkIter] > 20 && (pfEcal_[trkIter] + pfHcal_[trkIter])/TMath::CosH(trkEta_[trkIter] <= 0.5*trkPt_[trkIter])) continue;

      trkPt_p.push_back(trkPt_[trkIter]);
      trkPhi_p.push_back(trkPhi_[trkIter]);
      trkEta_p.push_back(trkEta_[trkIter]);
    }
    */

    for(unsigned int i = 0; i < pfPt_p->size(); ++i){
      for(unsigned int j = i+1; j < pfPt_p->size(); ++j){

	if(pfPt_p->at(j) > pfPt_p->at(i)){
	  Float_t tempPfPt_ = pfPt_p->at(j);
	  Float_t tempPfPhi_ = pfPhi_p->at(j);
	  Float_t tempPfEta_ = pfEta_p->at(j);
	  Int_t tempPfId_ = pfId_p->at(j);

	  pfPt_p->at(j) = pfPt_p->at(i);
	  pfPhi_p->at(j) = pfPhi_p->at(i);
	  pfEta_p->at(j) = pfEta_p->at(i);
	  pfId_p->at(j) = pfId_p->at(i);

	  pfPt_p->at(i) = tempPfPt_;
	  pfPhi_p->at(i) = tempPfPhi_;
	  pfEta_p->at(i) = tempPfEta_;
	  pfId_p->at(i) = tempPfId_;
	}
      }
    }
   
    for(Int_t i = 0; i < jData.nref; ++i){
      maxPFPt_[i] = -999;
      maxPF1Pt_[i] = -999;
      maxPF2Pt_[i] = -999;
      maxPF3Pt_[i] = -999;
      maxPF4Pt_[i] = -999;
      maxPF5Pt_[i] = -999;

      sumPFPt_[i] = 0;
      sumPF1Pt_[i] = 0;
      sumPF2Pt_[i] = 0;
      sumPF3Pt_[i] = 0;
      sumPF4Pt_[i] = 0;
      sumPF5Pt_[i] = 0;

      for(unsigned int j = 0; j < pfPt_p->size(); ++j){
	if(getDR(pfEta_p->at(j), pfPhi_p->at(j), jData.jteta[i], jData.jtphi[i]) < .3){
	  if(maxPFPt_[i] < 0) maxPFPt_[i] = pfPt_p->at(j);
	  if(maxPF1Pt_[i] < 0 && pfId_p->at(j) == 1) maxPF1Pt_[i] = pfPt_p->at(j);
	  if(maxPF2Pt_[i] < 0 && pfId_p->at(j) == 2) maxPF2Pt_[i] = pfPt_p->at(j);
	  if(maxPF3Pt_[i] < 0 && pfId_p->at(j) == 3) maxPF3Pt_[i] = pfPt_p->at(j);
	  if(maxPF4Pt_[i] < 0 && pfId_p->at(j) == 4) maxPF4Pt_[i] = pfPt_p->at(j);
	  if(maxPF5Pt_[i] < 0 && pfId_p->at(j) == 5) maxPF5Pt_[i] = pfPt_p->at(j);

	  sumPFPt_[i] += pfPt_p->at(j);
	  if(pfId_p->at(j) == 1) sumPF1Pt_[i] += pfPt_p->at(j);
	  if(pfId_p->at(j) == 2) sumPF2Pt_[i] += pfPt_p->at(j);
	  if(pfId_p->at(j) == 3) sumPF3Pt_[i] += pfPt_p->at(j);
	  if(pfId_p->at(j) == 4) sumPF4Pt_[i] += pfPt_p->at(j);
	  if(pfId_p->at(j) == 5) sumPF5Pt_[i] += pfPt_p->at(j);

	  if(getDR(pfEta_p->at(j), pfPhi_p->at(j), jData.jteta[i], jData.jtphi[i]) < .1) sumRing1Pt_[i] += pfPt_p->at(i);
	  else if(getDR(pfEta_p->at(j), pfPhi_p->at(j), jData.jteta[i], jData.jtphi[i]) < .2) sumRing2Pt_[i] += pfPt_p->at(i);
	  else sumRing3Pt_[i] += pfPt_p->at(i);
	}
      }
    }

    pfPt_p->clear();
    pfPhi_p->clear();
    pfEta_p->clear();
    pfId_p->clear();

    outTree_p->Fill();
  }

  inFile_p->Close();
  delete inFile_p;

  outFile_p->cd();
  outTree_p->Write("", TObject::kOverwrite);
  delete outTree_p;

  outFile_p->Close();
  delete outFile_p;

  return 0;
}

int main(int argc, char* argv[])
{
  if(argc != 2){
    std::cout << "Usage: ./forestToJeNtuple.exe <inFileName>" << std::endl;
    return 1;
  }

  int retVal = 0;
  retVal += forestToJeNtuple(argv[1]);
  return retVal;
}
