#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

#include "include/jetData.h"
#include "include/etaPhiFunc.h"

int forestToSubJeNtuple(const std::string inFileName)
{
  TRandom3* randGen_p = new TRandom3(0);

  const std::string outFileName = "outFile_SUB.root";
  TFile* outFile_p = new TFile(outFileName.c_str(), "RECREATE");

  Float_t jtpt_;
  Float_t jteta_;
  Float_t maxPFPt;
  Float_t maxPF1Pt;
  Float_t maxPF4Pt;
  Float_t maxPF5Pt;
  Float_t sumPFPt;
  Float_t sumRing1Pt;
  Float_t sumRing2Pt;
  Float_t sumRing3Pt;

  TTree* outTreeSubFake_Build_p = new TTree("outTreeSubFake_Build", "");
  outTreeSubFake_Build_p->Branch("jtpt", &jtpt_, "jtpt/F");
  outTreeSubFake_Build_p->Branch("jteta", &jteta_, "jteta/F");
  outTreeSubFake_Build_p->Branch("maxPFPt", &maxPFPt, "maxPFPt/F");
  outTreeSubFake_Build_p->Branch("maxPF1Pt", &maxPF1Pt, "maxPF1Pt/F");
  outTreeSubFake_Build_p->Branch("maxPF4Pt", &maxPF4Pt, "maxPF4Pt/F");
  outTreeSubFake_Build_p->Branch("maxPF5Pt", &maxPF5Pt, "maxPF5Pt/F");
  outTreeSubFake_Build_p->Branch("sumPFPt", &sumPFPt, "sumPFPt/F");
  outTreeSubFake_Build_p->Branch("sumRing1Pt", &sumRing1Pt, "sumRing1Pt/F");
  outTreeSubFake_Build_p->Branch("sumRing2Pt", &sumRing2Pt, "sumRing2Pt/F");
  outTreeSubFake_Build_p->Branch("sumRing3Pt", &sumRing3Pt, "sumRing3Pt/F");

  TTree* outTreeSubFake_Test_p = new TTree("outTreeSubFake_Test", "");
  outTreeSubFake_Test_p->Branch("jtpt", &jtpt_, "jtpt/F");
  outTreeSubFake_Test_p->Branch("jteta", &jteta_, "jteta/F");
  outTreeSubFake_Test_p->Branch("maxPFPt", &maxPFPt, "maxPFPt/F");
  outTreeSubFake_Test_p->Branch("maxPF1Pt", &maxPF1Pt, "maxPF1Pt/F");
  outTreeSubFake_Test_p->Branch("maxPF4Pt", &maxPF4Pt, "maxPF4Pt/F");
  outTreeSubFake_Test_p->Branch("maxPF5Pt", &maxPF5Pt, "maxPF5Pt/F");
  outTreeSubFake_Test_p->Branch("sumPFPt", &sumPFPt, "sumPFPt/F");
  outTreeSubFake_Test_p->Branch("sumRing1Pt", &sumRing1Pt, "sumRing1Pt/F");
  outTreeSubFake_Test_p->Branch("sumRing2Pt", &sumRing2Pt, "sumRing2Pt/F");
  outTreeSubFake_Test_p->Branch("sumRing3Pt", &sumRing3Pt, "sumRing3Pt/F");

  TTree* outTreeSubReal_Build_p = new TTree("outTreeSubReal_Build", "");
  outTreeSubReal_Build_p->Branch("jtpt", &jtpt_, "jtpt/F");
  outTreeSubReal_Build_p->Branch("jteta", &jteta_, "jteta/F");
  outTreeSubReal_Build_p->Branch("maxPFPt", &maxPFPt, "maxPFPt/F");
  outTreeSubReal_Build_p->Branch("maxPF1Pt", &maxPF1Pt, "maxPF1Pt/F");
  outTreeSubReal_Build_p->Branch("maxPF4Pt", &maxPF4Pt, "maxPF4Pt/F");
  outTreeSubReal_Build_p->Branch("maxPF5Pt", &maxPF5Pt, "maxPF5Pt/F");
  outTreeSubReal_Build_p->Branch("sumPFPt", &sumPFPt, "sumPFPt/F");
  outTreeSubReal_Build_p->Branch("sumRing1Pt", &sumRing1Pt, "sumRing1Pt/F");
  outTreeSubReal_Build_p->Branch("sumRing2Pt", &sumRing2Pt, "sumRing2Pt/F");
  outTreeSubReal_Build_p->Branch("sumRing3Pt", &sumRing3Pt, "sumRing3Pt/F");

  TTree* outTreeSubReal_Test_p = new TTree("outTreeSubReal_Test", "");
  outTreeSubReal_Test_p->Branch("jtpt", &jtpt_, "jtpt/F");
  outTreeSubReal_Test_p->Branch("jteta", &jteta_, "jteta/F");
  outTreeSubReal_Test_p->Branch("maxPFPt", &maxPFPt, "maxPFPt/F");
  outTreeSubReal_Test_p->Branch("maxPF1Pt", &maxPF1Pt, "maxPF1Pt/F");
  outTreeSubReal_Test_p->Branch("maxPF4Pt", &maxPF4Pt, "maxPF4Pt/F");
  outTreeSubReal_Test_p->Branch("maxPF5Pt", &maxPF5Pt, "maxPF5Pt/F");
  outTreeSubReal_Test_p->Branch("sumPFPt", &sumPFPt, "sumPFPt/F");
  outTreeSubReal_Test_p->Branch("sumRing1Pt", &sumRing1Pt, "sumRing1Pt/F");
  outTreeSubReal_Test_p->Branch("sumRing2Pt", &sumRing2Pt, "sumRing2Pt/F");
  outTreeSubReal_Test_p->Branch("sumRing3Pt", &sumRing3Pt, "sumRing3Pt/F");

  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");
  TTree* jetTree_p = (TTree*)inFile_p->Get("outTree");

  jetData jData;
  const Int_t nMaxJets = 500;
  Float_t maxPFPt_[nMaxJets];
  Float_t maxPF1Pt_[nMaxJets];
  Float_t maxPF4Pt_[nMaxJets];
  Float_t maxPF5Pt_[nMaxJets];
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
  jetTree_p->SetBranchStatus("maxPF1Pt", 1);
  jetTree_p->SetBranchStatus("maxPF4Pt", 1);
  jetTree_p->SetBranchStatus("maxPF5Pt", 1);
  jetTree_p->SetBranchStatus("sumPFPt", 1);
  jetTree_p->SetBranchStatus("sumRing1Pt", 1);
  jetTree_p->SetBranchStatus("sumRing2Pt", 1);
  jetTree_p->SetBranchStatus("sumRing3Pt", 1);

  jetTree_p->SetBranchAddress("nref", &jData.nref);
  jetTree_p->SetBranchAddress("jtpt", jData.jtpt);
  jetTree_p->SetBranchAddress("jteta", jData.jteta);
  jetTree_p->SetBranchAddress("refpt", jData.refpt);
  jetTree_p->SetBranchAddress("maxPFPt", maxPFPt_);
  jetTree_p->SetBranchAddress("maxPF1Pt", maxPF1Pt_);
  jetTree_p->SetBranchAddress("maxPF4Pt", maxPF4Pt_);
  jetTree_p->SetBranchAddress("maxPF5Pt", maxPF5Pt_);
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
      if(jData.jtpt[i] > 40) continue;
      if(TMath::Abs(jData.jteta[i]) > 1.6) continue;

      jtpt_ = jData.jtpt[i];
      jteta_ = jData.jteta[i];
      maxPFPt = maxPFPt_[i];
      maxPF1Pt_[i] > 0 ? maxPF1Pt = maxPF1Pt_[i] : maxPF1Pt = 0;
      maxPF4Pt_[i] > 0 ? maxPF4Pt = maxPF4Pt_[i] : maxPF4Pt = 0;
      maxPF5Pt_[i] > 0 ? maxPF5Pt = maxPF5Pt_[i] : maxPF5Pt = 0;
      sumPFPt = sumPFPt_[i];
      sumRing1Pt = sumRing1Pt_[i];
      sumRing2Pt = sumRing2Pt_[i];
      sumRing3Pt = sumRing3Pt_[i];

      if(jData.refpt[i] < 0){
	if(randGen_p->Uniform(0,1) < .5) outTreeSubFake_Build_p->Fill();
	else outTreeSubFake_Test_p->Fill();
      }
      else{
	if(randGen_p->Uniform(0,1) < .5) outTreeSubReal_Build_p->Fill();
	else outTreeSubReal_Test_p->Fill();
      }
    }
  }

  inFile_p->Close();
  delete inFile_p;

  outFile_p->cd();
  outTreeSubFake_Build_p->Write("", TObject::kOverwrite);
  delete outTreeSubFake_Build_p;

  outTreeSubReal_Build_p->Write("", TObject::kOverwrite);
  delete outTreeSubReal_Build_p;

  outTreeSubFake_Test_p->Write("", TObject::kOverwrite);
  delete outTreeSubFake_Test_p;

  outTreeSubReal_Test_p->Write("", TObject::kOverwrite);
  delete outTreeSubReal_Test_p;

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
