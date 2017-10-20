{
gROOT -> Reset();
TFile f("Data.root");
TCanvas* Canvas_photon_spatial_distribution_xy_with_kinetic = new TCanvas("Canvas_photon_spatial_distribution_xy_with_kinetic (MeV)", " ");
particle_spatial_distribution_xy_with_kinetic->GetXaxis()->SetTitle(" x (cm)");
particle_spatial_distribution_xy_with_kinetic->GetYaxis()->SetTitle(" y (cm)");
particle_spatial_distribution_xy_with_kinetic->SetTitle(" 2D  particle spatial distribution in function of its kinetic energies (MeV)");
particle_spatial_distribution_xy_with_kinetic->Draw("colz");

}
