{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_electron_spatial_distribution_xy_with_kinetic = new TCanvas("Canvas_electron_spatial_distribution_xy_with_kinetic", " ");
spatial_distribution_xy->GetXaxis()->SetTitle(" x (cm)");
spatial_distribution_xy->SetTitle(" Electron Spatial Distribution");
spatial_distribution_xy->GetYaxis()->SetTitle(" y (cm)");
spatial_distribution_xy->Draw("colz");
}
