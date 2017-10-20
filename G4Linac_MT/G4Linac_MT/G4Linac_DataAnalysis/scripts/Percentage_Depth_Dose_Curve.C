{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_pdd = new TCanvas("Canvas_pdd", " ");
pdd->GetXaxis()->SetTitle(" z (cm)");
pdd->GetYaxis()->SetTitle(" Dose (MeV/g/Nevents)");

pdd->SetMarkerSize(0.5);
pdd->SetMarkerStyle(8);
pdd->SetLineStyle(1);
pdd->SetLineWidth(1);
pdd->Draw("same");
pdd->SetTitle("Percentage Depth Dose Curve");

}
