{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_y_profile = new TCanvas("Canvas_y_profile", " ")
y_profile->GetXaxis()->SetTitle(" y (cm)");
y_profile->GetYaxis()->SetTitle(" Edep (MeV/Nevents)");
y_profile->Draw("col");
}
