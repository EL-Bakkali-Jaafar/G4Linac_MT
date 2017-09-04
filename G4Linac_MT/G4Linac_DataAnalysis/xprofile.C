{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_x_profile = new TCanvas("Canvas_x_profile", " ");
x_profile->GetXaxis()->SetTitle(" x (cm)");
x_profile->GetYaxis()->SetTitle(" Dose (MeV/g/Nevents)");
x_profile->SetMarkerStyle(21);
x_profile->SetMarkerSize(0.4);
x_profile->Draw();
}
