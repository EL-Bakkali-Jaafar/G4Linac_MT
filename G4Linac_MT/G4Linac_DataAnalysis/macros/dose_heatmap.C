{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_dose_heatmap = new TCanvas("Canvas_dose_heatmap", " ");
dose_heatmap->GetXaxis()->SetTitle(" x (cm)");
dose_heatmap->GetYaxis()->SetTitle(" y (cm)");
dose_heatmap->Draw("colz");
}
