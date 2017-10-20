{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_y_profile = new TCanvas("Canvas_y_profile", " ");
y_profile->GetXaxis()->SetTitle(" y (cm)");
y_profile->GetYaxis()->SetTitle(" Dose (MeV/g/Nevents)");
y_profile->SetTitle("Rsd Curve Of In-plane Dose Profile");
y_profile->SetMarkerStyle(21);
y_profile->SetMarkerSize(0.4);
y_profile->Draw();
}
