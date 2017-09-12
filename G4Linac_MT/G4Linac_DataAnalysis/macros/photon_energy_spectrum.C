{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_photon_energy_spectrum = new TCanvas("Canvas_photon_energy_spectrum", " ");
photon_energy_spectrum->GetXaxis()->SetTitle(" Kinetic Energy(MeV)");
photon_energy_spectrum->GetYaxis()->SetTitle(" Number of photons ");
photon_energy_spectrum->SetFillColor(2);
photon_energy_spectrum->SetFillStyle(3001);
photon_energy_spectrum->SetMarkerSize(0.1);
photon_energy_spectrum->Draw("EHIST");
}
