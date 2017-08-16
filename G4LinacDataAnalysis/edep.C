{
// Plot the energy spectrum of the primary particles
gROOT -> Reset();

TFile f("Data.root");
 
TCanvas* c1 = new TCanvas("c1", " ");
 // PROFILE_2D_HEAT_MAP->GetZaxis()->SetRangeUser(0.0, 2); // ... set the range ...
PROFILE_2D_HEAT_MAP->GetXaxis()->SetTitle(" x (cm)");
PROFILE_2D_HEAT_MAP->GetYaxis()->SetTitle(" y (cm)");
PROFILE_2D_HEAT_MAP->Draw("colz");


}
