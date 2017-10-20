{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_dose_heatmap = new TCanvas("Canvas_dose_heatmap", " ");
dose_heatmap->GetXaxis()->SetTitle(" y (cm)");
dose_heatmap->GetYaxis()->SetTitle(" z (cm)");
dose_heatmap->SetTitle("2D Dose Heat Map In Plane YZ");
dose_heatmap->Draw("colz");
}
