{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_pdd_statistics = new TCanvas("Canvas_pdd_statistics", " ");
pdd->GetXaxis()->SetTitle(" z (cm)");
pdd->GetYaxis()->SetTitle(" Relative Standard Deviation (%)");
pdd->SetMarkerStyle(21);
pdd->SetMarkerSize(0.4);
pdd->SetTitle("RSD Curve of Perecentage Depth Dose");
pdd->Draw();
}
