#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "include/jetData.h"
#include "include/etaPhiFunc.h"

int forestToSubJeNtuple(const std::string inFileName)
{
  const std::string outFileName = "outFile_SUB.root";
  TFile* outFile_p = new TFile(outFileName.c_str(), "RECREATE");

  Float_t jtpt_;
  Float_t refpt_;
  Float_t jteta_;
  Float_t maxPFPt;
  Float_t sumPFPt;
  Float_t sumRing1Pt;
  Float_t sumRing2Pt;
  Float_t sumRing3Pt;

  TTree* outTree_p = new TTree("outTreeSub", "");
  outTree_p->Branch("jtpt", &jtpt_, "jtpt/F");
  outTree_p->Branch("jteta", &jteta_, "jteta/F");
  outTree_p->Branch("refpt", &refpt_, "refpt/F");
  outTree_p->Branch("maxPFPt", &maxPFPt, "maxPFPt/F");
  outTree_p->Branch("sumPFPt", &sumPFPt, "sumPFPt/F");
  outTree_p->Branch("sumRing1Pt", &sumRing1Pt, "sumRing1Pt/F");
  outTree_p->Branch("sumRing2Pt", &sumRing2Pt, "sumRing2Pt/F");
  outTree_p->Branch("sumRing3Pt", &sumRing3Pt, "sumRing3Pt/F");

  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");
  TTree* jetTree_p = (TTree*)inFile_p->Get("outTree");

  jetData jData;
  const Int_t nMaxJets = 500;
  Float_t maxPFPt_[nMaxJets];
  Float_t sumPFPt_[nMaxJets];
  Float_t sumRing1Pt_[nMaxJets];
  Float_t sumRing2Pt_[nMaxJets];
  Float_t sumRing3Pt_[nMaxJets];

  jetTree_p->SetBranchStatus("*", 0);
  jetTree_p->SetBranchStatus("nref", 1);
  jetTree_p->SetBranchStatus("jtpt", 1);
  jetTree_p->SetBranchStatus("jteta", 1);
  jetTree_p->SetBranchStatus("refpt", 1);
  jetTree_p->SetBranchStatus("maxPFPt", 1);
  jetTree_p->SetBranchStatus("sumPFPt", 1);
  jetTree_p->SetBranchStatus("sumRing1Pt", 1);
  jetTree_p->SetBranchStatus("sumRing2Pt", 1);
  jetTree_p->SetBranchStatus("sumRing3Pt", 1);

  jetTree_p->SetBranchAddress("nref", &jData.nref);
  jetTree_p->SetBranchAddress("jtpt", jData.jtpt);
  jetTree_p->SetBranchAddress("jteta", jData.jteta);
  jetTree_p->SetBranchAddress("refpt", jData.refpt);
  jetTree_p->SetBranchAddress("maxPFPt", maxPFPt_);
  jetTree_p->SetBranchAddress("sumPFPt", sumPFPt_);
  jetTree_p->SetBranchAddress("sumRing1Pt", sumRing1Pt_);
  jetTree_p->SetBranchAddress("sumRing2Pt", sumRing2Pt_);
  jetTree_p->SetBranchAddress("sumRing3Pt", sumRing3Pt_);

  const int nEntries = jetTree_p->GetEntries();

  for(int entry = 0; entry < nEntries; ++entry){
    if(entry%1000 == 0) std::cout << "Entry: " << entry << "/" << nEntries << std::endl;
    jetTree_p->GetEntry(entry);

    for(int i = 0; i < jData.nref; ++i){
      if(jData.jtpt[i] < 30) continue;
      if(jData.jtpt[i] > 50) continue;
      if(TMath::Abs(jData.jteta[i]) > 1.6) continue;

      jtpt_ = jData.jtpt[i];
      refpt_ = jData.refpt[i];
      jteta_ = jData.jteta[i];
      maxPFPt = maxPFPt_[i];
      sumPFPt = sumPFPt_[i];
      sumRing1Pt = sumRing1Pt_[i];
      sumRing2Pt = sumRing2Pt_[i];
      sumRing3Pt = sumRing3Pt_[i];

      outTree_p->Fill();
    }
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
    std::cout << "Usage: ./forestToSubJeNtuple.exe <inFileName>" << std::endl;
    return 1;
  }

  int retVal = 0;
  retVal += forestToSubJeNtuple(argv[1]);
  return retVal;
}
