#ifndef JETDATA_H
#define JETDATA_H

class jetData{
 public:
  static const Int_t nMaxJet = 500;

  int nref;
  Float_t jtpt[nMaxJet];
  Float_t rawpt[nMaxJet];
  Float_t jtpu[nMaxJet];
  Float_t jteta[nMaxJet];
  Float_t jtphi[nMaxJet];

  Float_t refpt[nMaxJet];
  Float_t refeta[nMaxJet];
  Float_t refphi[nMaxJet];

  Int_t subid[nMaxJet];
  Int_t refparton_flavor[nMaxJet];
};

#endif
