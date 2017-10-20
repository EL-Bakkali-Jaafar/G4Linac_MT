{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_electron_energy_spectrum = new TCanvas("Canvas_electron_energy_spectrum", " ");
electron_energy_spectrum->GetXaxis()->SetTitle(" Kinetic Energy(MeV)");
electron_energy_spectrum->GetYaxis()->SetTitle(" Number of electrons ");
electron_energy_spectrum->SetTitle(" Electron Energy Spectrum ");
electron_energy_spectrum->SetFillColor(2);
electron_energy_spectrum->SetFillStyle(3001);
electron_energy_spectrum->SetMarkerSize(0.1);
electron_energy_spectrum->Draw("EHIST");
}
