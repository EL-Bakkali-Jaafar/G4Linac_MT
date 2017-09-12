{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_electron_spatial_distribution_xy_with_kinetic = new TCanvas("Canvas_electron_spatial_distribution_xy_with_kinetic", " ");
electron_spatial_distribution_xy_with_kinetic->GetXaxis()->SetTitle(" x (cm)");
electron_spatial_distribution_xy_with_kinetic->GetYaxis()->SetTitle(" y (cm)");
electron_spatial_distribution_xy_with_kinetic->Draw("colz");
}
