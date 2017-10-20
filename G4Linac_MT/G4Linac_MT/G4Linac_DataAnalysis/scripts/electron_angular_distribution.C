{
gROOT -> Reset();
TFile f("Data.root");
electron_angular_distribution->GetXaxis()->SetTitle(" Theta (Deg)");
electron_angular_distribution->GetYaxis()->SetTitle("Number of electrons");
electron_angular_distribution->SetFillColor(2);
electron_angular_distribution->SetFillStyle(3001);
electron_angular_distribution->SetMarkerSize(0.1);
electron_angular_distribution->Draw("EHIST");
}
