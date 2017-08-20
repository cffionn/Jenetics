#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "include/jetData.h"

int forestToJeNtuple(const std::string inFileName)
{
  const std::string outFileName = "outFile.root";
  TFile* outFile_p = new TFile(outFileName.c_str(), "RECREATE");
  jetData jData;
  TTree* outTree_p = new TTree("outTree", "");
  outTree_p->Branch("nref", &jData.nref, "nref/I");
  outTree_p->Branch("jtpt", jData.jtpt, "jtpt[nref]/F");
  outTree_p->Branch("jtphi", jData.jtphi, "jtphi[nref]/F");
  outTree_p->Branch("jteta", jData.jteta, "jteta[nref]/F");


  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");
  TTree* jetTree_p = (TTree*)inFile_p->Get("ak3PFJetAnalyzer/t");
  jetTree_p->SetBranchStatus("*", 0);
  jetTree_p->SetBranchStatus("nref", 1);
  jetTree_p->SetBranchStatus("jtpt", 1);
  jetTree_p->SetBranchStatus("jtphi", 1);
  jetTree_p->SetBranchStatus("jteta", 1);

  jetTree_p->SetBranchAddress("nref", &jData.nref);
  jetTree_p->SetBranchAddress("jtpt", jData.jtpt);
  jetTree_p->SetBranchAddress("jtphi", jData.jtphi);
  jetTree_p->SetBranchAddress("jteta", jData.jteta);
 
  const int nEntries = jetTree_p->GetEntries();

  for(int entry = 0; entry < nEntries; ++entry){
    if(entry%10000 == 0) std::cout << "Entry: " << entry << "/" << nEntries << std::endl;
    jetTree_p->GetEntry(entry);

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
