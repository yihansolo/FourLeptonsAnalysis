#define LHEF4_cxx
#include "LHEF4.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void LHEF4::Loop()
{
//   In a ROOT session, you can do:
//      root> .L LHEF4.C
//      root> LHEF4 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
       int arr[4];
       int size=0;
       int farr[15000];
       int fsize=0;
       for(Long64_t i=0; i<kMaxParticle-1; i++){
           int mother=Particle_Mother1[i];
           if (abs(Particle_PID[i])>=11 && abs(Particle_PID[i]) <=14 && Particle_PID[mother]==1023){//if it is a lepton and it's mother is 1023
               arr[size++]=i;
            //   printf("PID= %d\n",Particle_PID[i]);
              // printf("event= %lld\n",jentry);
           }
       }
       
       if(size<=4){// if there aren't 4 leptons
           continue;
       }else{// if there are 4 leptons
           for(int j=0;j<4;j++){
               farr[fsize]=arr[j];//save it to the bigger array
               printf("4 leptons PID= %d\n",farr[fsize]);
               printf("event= %lld\n",jentry);
               fsize++;
           }
       }

       for(int k=0;k<fsize;k++){
           printf ("%d", farr[k]);
       }
   }
}
