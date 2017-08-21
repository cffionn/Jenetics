#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

#include "include/chromoCut.h"

int jetGeneration(const std::string inFileName)
{
  TRandom3* randGen_p = new TRandom3(0);
  
  const double mutRate = 1; // in percent, set high for rapid evo, uniform across chromo
  const unsigned int popSize = 100; // low for many populations
  std::vector<chromoCut> population;

  for(unsigned int i = 0; i < popSize; ++i){
    chromoCut temp;
    temp.setMaxPtFracCut(randGen_p->Uniform(0,1));
    temp.setSumRing1PtFracCut(randGen_p->Uniform(0,1));
    temp.setSumRing2PtFracCut(randGen_p->Uniform(0,1));
    temp.setSumRing3PtFracCut(randGen_p->Uniform(0,1));

    std::string compString;

    randGen_p->Uniform(0,1) > .5 ? compString = ">" : compString = "<";
    temp.setMaxPtFracComp(compString);

    randGen_p->Uniform(0,1) > .5 ? compString = ">" : compString = "<";
    temp.setSumRing1PtFracComp(compString);

    randGen_p->Uniform(0,1) > .5 ? compString = ">" : compString = "<";
    temp.setSumRing2PtFracComp(compString);

    randGen_p->Uniform(0,1) > .5 ? compString = ">" : compString = "<";
    temp.setSumRing3PtFracComp(compString);

    if(!temp.setFullCut()){
      std::cout << "Error, setting full cut returned false, return 1" << std::endl;
      return 1;
    }
    population.push_back(temp);
  }

  std::cout << "infilename: " << inFileName << std::endl;
  
  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");
  TTree* inTree_p = (TTree*)inFile_p->Get("outTreeSub");

  std::string  baseLineEffStr = "TMath::Abs(jteta) < 1.6 && jtpt > 30 && jtpt < 40 && refpt > 0";
  std::string baseLineFakesStr = "TMath::Abs(jteta) < 1.6 && jtpt > 30 && jtpt < 40 && refpt < 0";
  Double_t baseLineEff = inTree_p->GetEntries(baseLineEffStr.c_str());
  Double_t baseLineFakes = inTree_p->GetEntries(baseLineFakesStr.c_str());
  
  int nGen = 0;
  while(nGen < 100){
    for(unsigned int i = 0; i < population.size(); ++i){
      std::string cutEff = baseLineEffStr + " && " + population.at(i).getFullCut();
      std::string cutFake = baseLineFakesStr + " && " + population.at(i).getFullCut();
      
      Double_t tempEff = inTree_p->GetEntries(cutEff.c_str());
      tempEff /= baseLineEff;
      Double_t tempFake = inTree_p->GetEntries(cutFake.c_str());
      tempFake /= baseLineFakes;
      tempFake = 1.-tempFake;
      
      population.at(i).setEfficiency(tempEff);
      population.at(i).setFakeReduction(tempFake);
      population.at(i).setScore();
      //    std::cout << "cut " << i << "/" << population.size() << ": " << population.at(i).getScore() << ", " << population.at(i).getFullCut() << std::endl;
    }

    for(unsigned int i = 0; i < population.size(); ++i){
      for(unsigned int j = i+1; j < population.size(); ++j){
	if(population.at(j).getScore() > population.at(i).getScore()){
	  chromoCut temp = population.at(j);
	  population.at(j) = population.at(i);
	  population.at(i) = temp;
	}
      }
    }
    
    std::cout << "Peak score (Gen==" + nGen + "): " << population.at(0).getScore() << std::endl;
    nGen++;
    
    std::vector<chromoCut> newPop;
    for(int i = 0; i < 30; ++i){
      newPop.push_back(population(0));
      population.erase(population.begin());
    }

    for(int i = 0; i < 20; ++i){
      int pos = randGen_p->RandInt(0,population.size());
      newPop.push_back(population.at(pos));
      population.erase(population.begin()+pos);
    }
  }

  inFile_p->Close();
  delete inFile_p;
  
  delete randGen_p;

  return 0;
}

int main(int argc, char* argv[])
{
  if(argc != 2){
    std::cout << "Usage ./jetGeneration.exe <inFileName>" << std::endl;
    return 1;
  }
  
  int retVal = 0;
  retVal += jetGeneration(argv[1]);
  return retVal;
}
