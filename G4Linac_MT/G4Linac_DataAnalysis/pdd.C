{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_pdd = new TCanvas("Canvas_pdd", " ");
pdd->GetXaxis()->SetTitle(" x (cm)");
pdd->GetYaxis()->SetTitle(" Dose (MeV/g/Nevents)");
pdd->SetMarkerStyle(21);
pdd->SetMarkerSize(0.4);
pdd->Draw();
}
