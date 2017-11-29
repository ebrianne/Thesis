void T0s()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/T0_Resolution.root", "OPEN");

  TH1F *hT12_T14_BeforeCorrection;
  TH1F *hT12_T14;

  f->GetObject("hT12_T14_BeforeCorrection", hT12_T14_BeforeCorrection);
  f->GetObject("hT12_T14", hT12_T14);

  hT12_T14_BeforeCorrection->GetXaxis()->SetTitle("T_{12} - T_{14} [ns]");
  hT12_T14_BeforeCorrection->GetYaxis()->SetTitle("# Events");
  hT12_T14_BeforeCorrection->SetLineColor(kBlue);
  hT12_T14_BeforeCorrection->SetLineWidth(2);

  hT12_T14->GetXaxis()->SetTitle("T_{12} - T_{14} [ns]");
  hT12_T14->GetYaxis()->SetTitle("# Events");
  hT12_T14->SetLineColor(kRed);
  hT12_T14->SetLineWidth(2);

  TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.03);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TLegend *leg5 = new TLegend(0.2, 0.6, 0.5, 0.8);
  leg5->SetBorderSize(0);
  leg5->AddEntry(hT12_T14, TString::Format("#splitline{With Correction:}{Mean %2.2f RMS %2.2f}", hT12_T14->GetMean(), hT12_T14->GetRMS()), "l");
  leg5->AddEntry(hT12_T14_BeforeCorrection, TString::Format("#splitline{No Correction:}{Mean %2.2f RMS %2.2f}", hT12_T14_BeforeCorrection->GetMean(), hT12_T14_BeforeCorrection->GetRMS()), "l");

  TCanvas *c5 = new TCanvas("c5", "T0 Resolution", 800, 600);
  //gPad->SetLogy();
  hT12_T14->GetYaxis()->SetTitleOffset(1.5);
  hT12_T14->Draw();
  hT12_T14_BeforeCorrection->Draw("same");
  //hT12_T14_BeforeCorrection_2->Draw("same");
  leg5->Draw("same");
  pt->Draw("same");
  c5->SaveAs("Plots/T0_Resolution_5.pdf");
}

void T0_Error()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/T0ReferenceError.root", "OPEN");
  TH1F *hT0_Error;

  f->GetObject("hT0_Error", hT0_Error);

  hT0_Error->SetLineColor(kBlack);
  hT0_Error->SetLineWidth(2);
  hT0_Error->Scale(1./hT0_Error->GetEntries());

  TPaveText *pt = new TPaveText(0.6, 0.8, 0.9, 0.9, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TLine *line = new TLine(4, 1e-6, 4, 1);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->SetLineStyle(2);

  TCanvas *c1 = new TCanvas("c1", "T0ReferenceError", 800, 600);
  gPad->SetLogy();
  hT0_Error->Draw();
  hT0_Error->GetXaxis()->SetTitle("Time reference uncertainty [ns]");
  hT0_Error->GetYaxis()->SetTitle("Fraction of events");
  hT0_Error->GetYaxis()->SetRangeUser(1e-6, 1);
  pt->Draw("same");
  line->Draw("same");

  c1->SaveAs("Plots/T0ReferenceError.pdf");

  // hT0_Error->GetXaxis()->SetRangeUser(0, 4);
  // cout << hT0_Error->GetMean() << endl;
}

void T0_Correction_Profiles()
{
  CaliceStyle();

  TFile *f0 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Muons/Data/T0s/T0s_SingleCorrelation/Rootfiles/T0s_SingleCorrelations_Plots_SelectionAllT0s_TDC2ns_BeforeCorr.root", "OPEN");
  TH2F *hDeviation12_14_0;
  TH2F *hDeviation12_14_1;

  f0->GetObject("hDeviation12_14_BXID0", hDeviation12_14_0);
  f0->GetObject("hDeviation12_14_BXID1", hDeviation12_14_1);

  TProfile* Prof12_14_0 = (TProfile*)hDeviation12_14_0->ProfileX("_pfx", 1, -1, "o");
  Prof12_14_0->SetMarkerColor(kRed);
  Prof12_14_0->SetLineColor(kRed);

  TProfile* Prof12_14_1 = (TProfile*)hDeviation12_14_1->ProfileX("_pfx", 1, -1, "o");
  Prof12_14_1->SetMarkerColor(kBlue);
  Prof12_14_1->SetLineColor(kBlue);

  TCanvas *c2 = new TCanvas("c2", "Profiles deviation compared to T_{0}^{14}", 800, 600);
  Prof12_14_0->Draw();
  Prof12_14_0->GetYaxis()->SetTitle("T_{0}^{12} - T_{0}^{14} [ns]");
  Prof12_14_0->GetYaxis()->SetRangeUser(-50, 50);
  Prof12_14_1->Draw("SAME");
  c2->SaveAs("Plots/Profiles_DeviationT0_12_14.pdf");
}

void T0_Correction()
{
  CaliceStyle();

  TF1 *line = new TF1("line", "x", 0, 6000);
  line->SetLineColor(kRed);
  line->SetLineStyle(2);

  //PreSelection file
  TFile *fSelection = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Muons/Data/T0s/T0s_SingleCorrelation/Rootfiles/T0s_SingleCorrelations_Plots_SelectionAllT0s_TDC2ns.root", "OPEN");

  fSelection->cd("Module12");
  TH2F *hCorr12_14 = (TH2F*)gDirectory->Get("hCorr12_14_BXID0");
  TH2F *hDeviation12_14 = (TH2F*)gDirectory->Get("hDeviation12_14_BXID0");
  TProfile *Prof12_14 = hDeviation12_14->ProfileX("_pfx2", 1, -1, "o");
  Prof12_14->GetYaxis()->SetTitle("T_{0}^{12} - T_{0}^{14} [ns]");
  Prof12_14->SetMarkerColor(kRed);
  Prof12_14->SetLineColor(kRed);

  TF1 *line2 = new TF1("line2", "0", 0, 4000);
  line2->SetLineColor(kRed);
  line2->SetLineStyle(2);

  double sFactor = 0.6;

  TCanvas *c5;
  TPad *pad9, *pad10;
  setupPadsTopBottom(c5, TString::Format("c5"), TString::Format("T12 vs T14"), pad9, pad10, sFactor, 800, 600);

  c5->cd();
  pad9->cd();
  pad9->SetBottomMargin(0.02);
  setupAxisScalingTop(hCorr12_14, sFactor);
  hCorr12_14->GetXaxis()->SetRangeUser(0, 4000);
  hCorr12_14->GetXaxis()->SetLabelSize(0);
  hCorr12_14->Draw("COLZ");
  line->Draw("SAME");
  pad10->cd();
  pad10->SetTopMargin(0.02);
  setupAxisScalingBottom(Prof12_14, sFactor);
  Prof12_14->GetXaxis()->SetRangeUser(0, 4000);
  Prof12_14->GetYaxis()->SetRangeUser(-1, 1);
  Prof12_14->GetYaxis()->SetNdivisions(5, 5, 0);
  Prof12_14->Draw("p");
  Prof12_14->Draw("p same");
  line2->Draw("same");

  c5->SaveAs(TString::Format("Plots/Correlation_T12vsT14_TDC2ns.pdf"));
}

void MakePlots()
{
  T0s();
  T0_Error();
  T0_Correction_Profiles();
  T0_Correction();
}
