#ifndef CHROMOCUT_H
#define CHROMOCUT_H

#include <string>

class chromoCut{
 public:
  std::string fullCut;
  
  Double_t maxPtFracCut;
  Double_t sumRing1PtFracCut;
  Double_t sumRing2PtFracCut;
  Double_t sumRing3PtFracCut;
 
  std::string maxPtFracComp;
  std::string sumRing1PtFracComp;
  std::string sumRing2PtFracComp;
  std::string sumRing3PtFracComp;

  Double_t efficiency;
  Double_t fakeReduction;
  Double_t score;

  chromoCut();
  ~chromoCut();

  void setMaxPtFracCut(Double_t inVal){maxPtFracCut = inVal; return;}
  void setSumRing1PtFracCut(Double_t inVal){sumRing1PtFracCut = inVal; return;}
  void setSumRing2PtFracCut(Double_t inVal){sumRing2PtFracCut = inVal; return;}
  void setSumRing3PtFracCut(Double_t inVal){sumRing3PtFracCut = inVal; return;}

  void setMaxPtFracComp(std::string inVal){maxPtFracComp = inVal; return;}
  void setSumRing1PtFracComp(std::string inVal){sumRing1PtFracComp = inVal; return;}
  void setSumRing2PtFracComp(std::string inVal){sumRing2PtFracComp = inVal; return;}
  void setSumRing3PtFracComp(std::string inVal){sumRing3PtFracComp = inVal; return;}

  Double_t getMaxPtFracCut(){return maxPtFracCut;}
  Double_t getSumRing1PtFracCut(){return sumRing1PtFracCut;}
  Double_t getSumRing2PtFracCut(){return sumRing2PtFracCut;}
  Double_t getSumRing3PtFracCut(){return sumRing3PtFracCut;}

  std::string getMaxPtFracComp(){return maxPtFracComp;}
  std::string getSumRing1PtFracComp(){return sumRing1PtFracComp;}
  std::string getSumRing2PtFracComp(){return sumRing2PtFracComp;}
  std::string getSumRing3PtFracComp(){return sumRing3PtFracComp;}


  bool setFullCut();
  std::string getFullCut(){return fullCut;}

  void setEfficiency(Double_t inVal){efficiency = inVal;}
  void setFakeReduction(Double_t inVal){fakeReduction = inVal;}
  void setScore(){score = efficiency*fakeReduction;}

  Double_t getEfficiency(){return efficiency;}
  Double_t getFakeReduction(){return fakeReduction;}
  Double_t getScore(){return score;}
};


chromoCut::chromoCut()
{
  fullCut = "";
  maxPtFracCut = -999.;
  sumRing1PtFracCut = -999.;
  sumRing2PtFracCut = -999.;
  sumRing3PtFracCut = -999.;

  maxPtFracComp = "";
  sumRing1PtFracComp = "";
  sumRing2PtFracComp = "";
  sumRing3PtFracComp = "";

  return;
}

chromoCut::~chromoCut(){return;}


bool chromoCut::setFullCut()
{
  bool retBool = true;

  if(maxPtFracCut < 0) retBool = false;
  if(sumRing1PtFracCut < 0) retBool = false;
  if(sumRing2PtFracCut < 0) retBool = false;
  if(sumRing3PtFracCut < 0) retBool = false;

  if(maxPtFracComp.size() == 0) retBool = false;
  if(sumRing1PtFracComp.size() == 0) retBool = false;
  if(sumRing2PtFracComp.size() == 0) retBool = false;
  if(sumRing3PtFracComp.size() == 0) retBool = false;

  if(retBool){
    fullCut = "((" + std::to_string(maxPtFracCut) + " " + maxPtFracComp + " maxPFPt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing1PtFracCut) + " " + sumRing1PtFracComp + " sumRing1Pt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing2PtFracCut) + " " + sumRing2PtFracComp + " sumRing2Pt/sumPFPt)";
    fullCut = fullCut + " && (" + std::to_string(sumRing3PtFracCut) + " " + sumRing3PtFracComp + " sumRing3Pt/sumPFPt))";
  }

  return retBool;
}


#endif
