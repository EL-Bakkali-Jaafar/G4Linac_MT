{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_photon_angular_distribution = new TCanvas("Canvas_photon_angular_distribution", " ");
photon_angular_distribution->GetXaxis()->SetTitle(" Theta (Deg)");
photon_angular_distribution->GetYaxis()->SetTitle("Number of photons");
photon_angular_distribution->SetFillColor(2);
photon_angular_distribution->SetFillStyle(3001);
photon_angular_distribution->SetMarkerSize(0.1);
photon_angular_distribution->Draw("EHIST");
}
