{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_dose_heatmap = new TCanvas("Canvas_dose_heatmap", " ");
dose_heatmap->GetXaxis()->SetTitle(" z (cm)");
dose_heatmap->GetYaxis()->SetTitle(" x (cm)");
dose_heatmap->SetTitle("2D Dose Heat Map In Plane ZX");
dose_heatmap->Draw("colz");
}
