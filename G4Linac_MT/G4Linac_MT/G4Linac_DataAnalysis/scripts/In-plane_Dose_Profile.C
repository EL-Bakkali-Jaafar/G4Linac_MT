{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_x_profile = new TCanvas("Canvas_x_profile", " ");
y_profile->GetXaxis()->SetTitle(" y (cm)");
y_profile->GetYaxis()->SetTitle(" Dose (MeV/g/Nevents)");
y_profile->SetTitle("In-plane Dose Profile");
y_profile->SetMarkerStyle(21);
y_profile->SetMarkerSize(0.4);
y_profile->Draw();
}
