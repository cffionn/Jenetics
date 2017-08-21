#ifndef CHROMOCUT_H
#define CHROMOCUT_H

#include <string>

class chromoCut{
 public:
  std::string fullCut;
  
  Double_t maxPtFracCutHigh;
  Double_t maxPtFracCutLow;
  Double_t sumRing1PtFracCutHigh;
  Double_t sumRing1PtFracCutLow;
  Double_t sumRing2PtFracCutHigh;
  Double_t sumRing2PtFracCutLow;
  Double_t sumRing3PtFracCutHigh;
  Double_t sumRing3PtFracCutLow;

  Double_t efficiency;
  Double_t fakeReduction;
  Double_t score;

  chromoCut();
  ~chromoCut();

  void setMaxPtFracCutHigh(Double_t inVal){maxPtFracCutHigh = inVal; return;}
  void setSumRing1PtFracCutHigh(Double_t inVal){sumRing1PtFracCutHigh = inVal; return;}
  void setSumRing2PtFracCutHigh(Double_t inVal){sumRing2PtFracCutHigh = inVal; return;}
  void setSumRing3PtFracCutHigh(Double_t inVal){sumRing3PtFracCutHigh = inVal; return;}

  void setMaxPtFracCutLow(Double_t inVal){maxPtFracCutLow = inVal; return;}
  void setSumRing1PtFracCutLow(Double_t inVal){sumRing1PtFracCutLow = inVal; return;}
  void setSumRing2PtFracCutLow(Double_t inVal){sumRing2PtFracCutLow = inVal; return;}
  void setSumRing3PtFracCutLow(Double_t inVal){sumRing3PtFracCutLow = inVal; return;}

  Double_t getMaxPtFracCutHigh(){return maxPtFracCutHigh;}
  Double_t getSumRing1PtFracCutHigh(){return sumRing1PtFracCutHigh;}
  Double_t getSumRing2PtFracCutHigh(){return sumRing2PtFracCutHigh;}
  Double_t getSumRing3PtFracCutHigh(){return sumRing3PtFracCutHigh;}

  Double_t getMaxPtFracCutLow(){return maxPtFracCutLow;}
  Double_t getSumRing1PtFracCutLow(){return sumRing1PtFracCutLow;}
  Double_t getSumRing2PtFracCutLow(){return sumRing2PtFracCutLow;}
  Double_t getSumRing3PtFracCutLow(){return sumRing3PtFracCutLow;}

  bool setFullCut();
  std::string getFullCut(){return fullCut;}

  void setEfficiency(Double_t inVal){efficiency = inVal;}
  void setFakeReduction(Double_t inVal){fakeReduction = inVal;}
  void setScore(){efficiency < .95 ? score = 0.00001*fakeReduction : score = fakeReduction;}

  Double_t getEfficiency(){return efficiency;}
  Double_t getFakeReduction(){return fakeReduction;}
  Double_t getScore(){return score;}
};


chromoCut::chromoCut()
{
  fullCut = "";
  maxPtFracCutHigh = -999.;
  sumRing1PtFracCutHigh = -999.;
  sumRing2PtFracCutHigh = -999.;
  sumRing3PtFracCutHigh = -999.;

  maxPtFracCutLow = -999.;
  sumRing1PtFracCutLow = -999.;
  sumRing2PtFracCutLow = -999.;
  sumRing3PtFracCutLow = -999.;

  return;
}

chromoCut::~chromoCut(){return;}


bool chromoCut::setFullCut()
{
  bool retBool = true;

  if(maxPtFracCutLow < 0) retBool = false;
  if(sumRing1PtFracCutLow < 0) retBool = false;
  if(sumRing2PtFracCutLow < 0) retBool = false;
  if(sumRing3PtFracCutLow < 0) retBool = false;

  if(maxPtFracCutHigh < 0) retBool = false;
  if(sumRing1PtFracCutHigh < 0) retBool = false;
  if(sumRing2PtFracCutHigh < 0) retBool = false;
  if(sumRing3PtFracCutHigh < 0) retBool = false;

  if(retBool){
    fullCut = "((" + std::to_string(maxPtFracCutLow) + " < maxPFPt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing1PtFracCutLow) + " < sumRing1Pt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing2PtFracCutLow) + " < sumRing2Pt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing3PtFracCutLow) + " < sumRing3Pt/sumPFPt)";

    fullCut = fullCut + " && (" + std::to_string(maxPtFracCutHigh) + " > maxPFPt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing1PtFracCutHigh) + " > sumRing1Pt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing2PtFracCutHigh) + " > sumRing2Pt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing3PtFracCutHigh) + " > sumRing3Pt/sumPFPt))";
  }

  return retBool;
}


#endif
