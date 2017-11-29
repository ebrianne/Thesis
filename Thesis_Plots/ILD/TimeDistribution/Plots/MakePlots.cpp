void MakePlots()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingDistribution_ILD_o1_v06_50GeV_kaon0L_100ns_NoSmearing.root", "OPEN");
  TH1F *hTimingNoSmearing;
  f->GetObject("hTiming", hTimingNoSmearing);

  TFile *f2 = new TFile("Rootfiles/TimingDistribution_ILD_o1_v06_50GeV_kaon0L_100ns_GausSmearing_0.4ns.root", "OPEN");
  TH1F *hTimingSmearing04ns;
  f2->GetObject("hTiming", hTimingSmearing04ns);

  TFile *f3 = new TFile("Rootfiles/TimingDistribution_ILD_o1_v06_50GeV_kaon0L_100ns_GausSmearing_1ns.root", "OPEN");
  TH1F *hTimingSmearing1ns;
  f3->GetObject("hTiming", hTimingSmearing1ns);

  TFile *f4 = new TFile("Rootfiles/TimingDistribution_ILD_o1_v06_50GeV_kaon0L_100ns_GausSmearing_8ns.root", "OPEN");
  TH1F *hTimingSmearing8ns;
  f4->GetObject("hTiming", hTimingSmearing8ns);

  hTimingNoSmearing->SetLineColor(kBlack);
  hTimingNoSmearing->SetLineWidth(2);
  hTimingNoSmearing->Scale(1./hTimingNoSmearing->Integral("width"));

  hTimingSmearing04ns->SetLineColor(kRed);
  hTimingSmearing04ns->SetLineWidth(2);
  hTimingSmearing04ns->Scale(1./hTimingSmearing04ns->Integral("width"));

  hTimingSmearing1ns->SetLineColor(kBlue);
  hTimingSmearing1ns->SetLineWidth(2);
  hTimingSmearing1ns->Scale(1./hTimingSmearing1ns->Integral("width"));

  hTimingSmearing8ns->SetLineColor(kGreen);
  hTimingSmearing8ns->SetLineWidth(2);
  hTimingSmearing8ns->Scale(1./hTimingSmearing8ns->Integral("width"));

  TLegend *leg = new TLegend(0.5, 0.7, 0.9, 0.9);
  leg->SetHeader("Mokka ILD_o1_v06, v17-11-p03, Hit level, K_{0}^{L}, cos(#theta) < 0.7");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.023);
  leg->AddEntry(hTimingNoSmearing, "No smearing", "l");
  leg->AddEntry(hTimingSmearing04ns, "0.4 ns smearing", "l");
  leg->AddEntry(hTimingSmearing1ns, "1 ns smearing", "l");
  leg->AddEntry(hTimingSmearing8ns, "8 ns smearing", "l");

  TCanvas *c1 = new TCanvas("c1", "Timing Smearing", 800, 600);
  gPad->SetLogy();
  hTimingNoSmearing->GetXaxis()->SetRangeUser(-50, 100);
  hTimingNoSmearing->GetXaxis()->SetTitle("Hit time [ns]");
  hTimingNoSmearing->GetYaxis()->SetTitle("Fraction of entries / ns");
  hTimingNoSmearing->Draw();
  hTimingSmearing04ns->Draw("same");
  hTimingSmearing1ns->Draw("same");
  hTimingSmearing8ns->Draw("same");
  leg->Draw("same");
  c1->SaveAs("Plots/ComparisonSmearingTimingAHCAL.pdf");
}
