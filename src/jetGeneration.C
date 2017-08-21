#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

#include "include/chromoCut.h"

void genFullPop(const unsigned int popSize, TRandom3* randGen_p, std::vector<chromoCut>* pop)
{
  while(pop->size() < popSize){
    chromoCut temp;
    temp.setMaxPtFracCutLow(randGen_p->Uniform(0,.3));
    temp.setMaxPtFracCutHigh(randGen_p->Uniform(.7,1.));

    double ring1Low = randGen_p->Uniform(0,1);
    double ring1High = randGen_p->Uniform(ring1Low,1);
    double ring2Low = randGen_p->Uniform(0,1);
    double ring2High = randGen_p->Uniform(ring2Low,1);
    double ring3Low = randGen_p->Uniform(0,1);
    double ring3High = randGen_p->Uniform(ring3Low,1);

    temp.setSumRing1PtFracCutLow(ring1Low);
    temp.setSumRing2PtFracCutLow(ring2Low);
    temp.setSumRing3PtFracCutLow(ring3Low);

    temp.setSumRing1PtFracCutHigh(ring1High);
    temp.setSumRing2PtFracCutHigh(ring2High);
    temp.setSumRing3PtFracCutHigh(ring3High);

    if(!temp.setFullCut()){
      std::cout << "Error, setting full cut returned false, return 1" << std::endl;
      return;
    }
    pop->push_back(temp);
  }

  pop->at(popSize-1).setMaxPtFracCutLow(0.01);
  pop->at(popSize-1).setMaxPtFracCutHigh(0.99);
  pop->at(popSize-1).setSumRing1PtFracCutLow(0.01);
  pop->at(popSize-1).setSumRing1PtFracCutHigh(0.99);
  pop->at(popSize-1).setSumRing2PtFracCutLow(0.01);
  pop->at(popSize-1).setSumRing2PtFracCutHigh(0.99);
  pop->at(popSize-1).setSumRing3PtFracCutLow(0.01);
  pop->at(popSize-1).setSumRing3PtFracCutHigh(0.99);
  pop->at(popSize-1).setFullCut();

  return;
}

int jetGeneration(const std::string inFileName)
{
  TRandom3* randGen_p = new TRandom3(0);
  
  const double valMutRate = 50; // in percent, set high for rapid evo, uniform across chromo
  const unsigned int popSize = 100; // low for many populations
  std::vector<chromoCut> population;
  genFullPop(popSize, randGen_p, &population);  

  std::cout << "infilename: " << inFileName << std::endl;
  
  TFile* inFile_p = new TFile(inFileName.c_str(), "READ");
  TTree* inTreeFake_Build_p = (TTree*)inFile_p->Get("outTreeSubFake_Build");
  TTree* inTreeReal_Build_p = (TTree*)inFile_p->Get("outTreeSubReal_Build");

  TTree* inTreeFake_Test_p = (TTree*)inFile_p->Get("outTreeSubFake_Test");
  TTree* inTreeReal_Test_p = (TTree*)inFile_p->Get("outTreeSubReal_Test");

  Double_t baseLineEff = inTreeReal_Build_p->GetEntries();
  Double_t baseLineFakes = inTreeFake_Build_p->GetEntries();

  Double_t baseLineEff_Test = inTreeReal_Test_p->GetEntries();
  Double_t baseLineFakes_Test = inTreeFake_Test_p->GetEntries();

  int nGen = 0;
  const int nMaxGen = 10000;
  while(nGen < nMaxGen){
    for(unsigned int i = 0; i < population.size(); ++i){
      std::string cutEff = population.at(i).getFullCut();
      std::string cutFake = population.at(i).getFullCut();
      
      Double_t tempEff = inTreeReal_Build_p->GetEntries(cutEff.c_str());
      tempEff /= baseLineEff;
      Double_t tempFake = inTreeFake_Build_p->GetEntries(cutFake.c_str());
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

    Double_t mean = 0;
    for(unsigned int i = 0; i < population.size(); ++i){
      mean += population.at(i).getScore();
    }

    mean /= (Double_t)population.size();
    
    std::cout << "Peak, mean, median score (Gen==" << nGen << "): " << population.at(0).getScore() << ", " << mean << ", " << population.at(population.size()/2).getScore() << std::endl;

    nGen++;
    
    std::vector<chromoCut> newPop;
    for(unsigned int i = 0; i < 3*popSize/10; ++i){
      newPop.push_back(population.at(0));
      population.erase(population.begin());
    }

    //Rain fire
    if(population.at(0).getFullCut().size() == population.at(population.size()-1).getFullCut().size() && population.at(0).getFullCut().find(population.at(population.size()-1).getFullCut()) != std::string::npos){
      std::cout << "God brings fire" << std::endl;
      chromoCut temp = population.at(0);
      population.push_back(newPop.at(0));
      newPop.clear();

      genFullPop(popSize, randGen_p, &population);
    }
    else{
      for(unsigned int i = 0; i < 2*popSize/10; ++i){
	int pos = randGen_p->Uniform(0,population.size());
	newPop.push_back(population.at(pos));
	population.erase(population.begin()+pos);
      }

      population = newPop;
    }

    while(population.size() < popSize){
      int pos1;
      int pos2;

      chromoCut parent1;
      chromoCut parent2;
      if(newPop.size() > 0){
	pos1 = randGen_p->Uniform(0,newPop.size());
	pos2 = randGen_p->Uniform(0,newPop.size());

	parent1 = newPop.at(pos1);
	parent2 = newPop.at(pos2);
      }
      else{
	pos1 = randGen_p->Uniform(0,5*popSize/10);
	pos2 = randGen_p->Uniform(0,5*popSize/10);

	parent1 = population.at(pos1);
	parent2 = population.at(pos2);
      }

      //      if(pos1 == pos2) continue;
      //      else if(newPop.size() > 0){
      if(newPop.size() > 0){
	newPop.erase(newPop.begin()+std::max(pos1,pos2));
	newPop.erase(newPop.begin()+std::min(pos1,pos2));
      }
      //      }
      
      chromoCut child = parent1;
      child.setSumRing2PtFracCutLow(parent2.getSumRing2PtFracCutLow());
      child.setSumRing3PtFracCutLow(parent2.getSumRing3PtFracCutLow());

      child.setSumRing2PtFracCutHigh(parent2.getSumRing2PtFracCutHigh());
      child.setSumRing3PtFracCutHigh(parent2.getSumRing3PtFracCutHigh());

      if(randGen_p->Uniform(0,100) < valMutRate) child.setMaxPtFracCutLow(randGen_p->Uniform(0,.3));
      if(randGen_p->Uniform(0,100) < valMutRate) child.setMaxPtFracCutHigh(randGen_p->Uniform(.7,1));


      if(randGen_p->Uniform(0,100) < valMutRate){
	double ring1Low = randGen_p->Uniform(0,1);
	double ring1High = randGen_p->Uniform(ring1Low,1);

	child.setSumRing1PtFracCutLow(ring1Low);
	child.setSumRing1PtFracCutHigh(ring1High);
      }
      if(randGen_p->Uniform(0,100) < valMutRate){
	double ring2Low = randGen_p->Uniform(0,1);
	double ring2High = randGen_p->Uniform(ring2Low,1);

	child.setSumRing2PtFracCutLow(ring2Low);
	child.setSumRing2PtFracCutHigh(ring2High);
      }
      if(randGen_p->Uniform(0,100) < valMutRate){
	double ring3Low = randGen_p->Uniform(0,1);
	double ring3High = randGen_p->Uniform(ring3Low,1);

	child.setSumRing3PtFracCutLow(ring3Low);
	child.setSumRing3PtFracCutHigh(ring3High);
      }


      child.setFullCut();

      population.push_back(child);
    }
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

  std::cout << "Final score, eff, fake: " << std::endl;
  std::cout << " " << population.at(0).getScore() << ", " << population.at(0).getEfficiency() << ", " << population.at(0).getFakeReduction() << std::endl;
  std::cout << population.at(0).getFullCut() << std::endl;

  std::cout << "In orthoganl test tree: " << std::endl;
  Double_t effTest = inTreeReal_Build_p->GetEntries(population.at(0).getFullCut().c_str());
  Double_t fakeTest = inTreeFake_Build_p->GetEntries(population.at(0).getFullCut().c_str()); 

  effTest /= (Double_t)baseLineEff_Test;
  fakeTest /= (Double_t)baseLineFakes_Test;

  std::cout << " Eff, fake: " << effTest << ", " << 1. - fakeTest << std::endl;

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
