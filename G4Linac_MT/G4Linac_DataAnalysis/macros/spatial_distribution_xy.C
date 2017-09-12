{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_spatial_distribution_xy = new TCanvas("Canvas_spatial_distribution_xy", " ");
spatial_distribution_xy->SetFillColor(2);
spatial_distribution_xy->GetXaxis()->SetTitle(" x (cm)");
spatial_distribution_xy->GetYaxis()->SetTitle(" y (cm)");
spatial_distribution_xy->SetFillStyle(3001);
spatial_distribution_xy->SetMarkerSize(0.1);
spatial_distribution_xy->Draw("colz");
}
