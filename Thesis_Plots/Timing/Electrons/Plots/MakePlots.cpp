void Validation()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/EnergySum.root", "OPEN");
  TGraphErrors *dataEsum, *MokkaEsum_10, *DD4hepEsum_10, *MokkaEsum_18, *DD4hepEsum_18;

  f->GetObject("dataEsum", dataEsum);
  f->GetObject("MokkaEsum_10", MokkaEsum_10);
  f->GetObject("DD4hepEsum_10", DD4hepEsum_10);
  f->GetObject("MokkaEsum_18", MokkaEsum_18);
  f->GetObject("DD4hepEsum_18", DD4hepEsum_18);

  dataEsum->SetLineColor(kBlack);
  dataEsum->SetLineWidth(2);
  dataEsum->SetMarkerColor(kBlack);
  dataEsum->SetMarkerStyle(20);

  MokkaEsum_10->SetLineColor(kRed);
  MokkaEsum_10->SetLineWidth(2);
  MokkaEsum_10->SetMarkerColor(kRed);
  MokkaEsum_10->SetMarkerStyle(21);

  DD4hepEsum_10->SetLineColor(kBlue);
  DD4hepEsum_10->SetLineWidth(2);
  DD4hepEsum_10->SetMarkerColor(kBlue);
  DD4hepEsum_10->SetMarkerStyle(22);

  MokkaEsum_18->SetLineColor(kRed);
  MokkaEsum_18->SetLineWidth(2);
  MokkaEsum_18->SetLineStyle(2);
  MokkaEsum_18->SetMarkerColor(kRed);
  MokkaEsum_18->SetMarkerStyle(21);

  DD4hepEsum_18->SetLineColor(kBlue);
  DD4hepEsum_18->SetLineWidth(2);
  DD4hepEsum_18->SetLineStyle(2);
  DD4hepEsum_18->SetMarkerColor(kBlue);
  DD4hepEsum_18->SetMarkerStyle(22);

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(dataEsum);
  multi->Add(MokkaEsum_10);
  multi->Add(DD4hepEsum_10);
  multi->Add(MokkaEsum_18);
  multi->Add(DD4hepEsum_18);

  TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(dataEsum, "Data", "lp");
  leg->AddEntry(MokkaEsum_10, "Mokka (10%)", "lp");
  leg->AddEntry(MokkaEsum_18, "Mokka (18%)", "lp");

  TLegend *leg2 = new TLegend(0.6, 0.2, 0.9, 0.35);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(DD4hepEsum_10, "DD4hep (10%)", "lp");
  leg2->AddEntry(DD4hepEsum_18, "DD4hep (18%)", "lp");

  TCanvas *c1 = new TCanvas("c1", "Esum", 800, 600);
  multi->Draw("APL");
  multi->GetXaxis()->SetTitle("Beam Energy [GeV]");
  multi->GetYaxis()->SetTitle("<E_{sum}> [MIP]");
  multi->GetYaxis()->SetRangeUser(0, 2000);
  leg->Draw("same");
  leg2->Draw("same");
  gPad->Modified();

  c1->SaveAs("Plots/EsumElectrons_BeamEnergy.pdf");

  //-------------------------------------

  TFile *f2 = new TFile("Rootfiles/NumberHits.root", "OPEN");
  TGraphErrors *datanHits, *MokkanHits_10, *DD4hepnHits_10, *MokkanHits_18, *DD4hepnHits_18;

  f2->GetObject("datanHits", datanHits);
  f2->GetObject("MokkanHits_10", MokkanHits_10);
  f2->GetObject("DD4hepnHits_10", DD4hepnHits_10);
  f2->GetObject("MokkanHits_18", MokkanHits_18);
  f2->GetObject("DD4hepnHits_18", DD4hepnHits_18);

  datanHits->SetLineColor(kBlack);
  datanHits->SetLineWidth(2);
  datanHits->SetMarkerColor(kBlack);
  datanHits->SetMarkerStyle(20);

  MokkanHits_10->SetLineColor(kRed);
  MokkanHits_10->SetLineWidth(2);
  MokkanHits_10->SetMarkerColor(kRed);
  MokkanHits_10->SetMarkerStyle(21);

  DD4hepnHits_10->SetLineColor(kBlue);
  DD4hepnHits_10->SetLineWidth(2);
  DD4hepnHits_10->SetMarkerColor(kBlue);
  DD4hepnHits_10->SetMarkerStyle(22);

  MokkanHits_18->SetLineColor(kRed);
  MokkanHits_18->SetLineWidth(2);
  MokkanHits_18->SetLineStyle(2);
  MokkanHits_18->SetMarkerColor(kRed);
  MokkanHits_18->SetMarkerStyle(21);

  DD4hepnHits_18->SetLineColor(kBlue);
  DD4hepnHits_18->SetLineWidth(2);
  DD4hepnHits_18->SetLineStyle(2);
  DD4hepnHits_18->SetMarkerColor(kBlue);
  DD4hepnHits_18->SetMarkerStyle(22);

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(datanHits);
  multi2->Add(MokkanHits_10);
  multi2->Add(DD4hepnHits_10);
  multi2->Add(MokkanHits_18);
  multi2->Add(DD4hepnHits_18);

  TCanvas *c2 = new TCanvas("c2", "nHits", 800, 600);
  multi2->Draw("APL");
  multi2->GetXaxis()->SetTitle("Beam Energy [GeV]");
  multi2->GetYaxis()->SetTitle("<nHits>");
  multi2->GetYaxis()->SetRangeUser(0, 150);
  leg->Draw("same");
  leg2->Draw("same");
  gPad->Modified();

  c2->SaveAs("Plots/nHitsElectrons_BeamEnergy.pdf");
}

void NumberHits()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TriggeredChannels.root", "OPEN");

  TProfile *prof;
  f->GetObject("Time_vs_TriggeredChannels_profX", prof);

  prof->SetMarkerStyle(20);
  prof->SetMarkerColor(kBlack);
  prof->SetLineColor(kBlack);
  prof->GetXaxis()->SetRangeUser(0, 22);
  prof->GetYaxis()->SetRangeUser(-1, 50);
  prof->GetYaxis()->SetTitle("Mean time of first hit [ns]");
  prof->GetXaxis()->SetTitle("Number of triggered channels above 0.5 MIPs");

  TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TF1 *fit = new TF1("fit", "[0]+x*[1]+x*x*[2]", 1, 21);
  // TF1 *fit = new TF1("fit", "[0]*x*(1+x*x)", 1, 21);
  fit->SetLineColor(kRed);
  fit->SetLineWidth(2);
  fit->SetLineStyle(2);

  fit->SetParNames("offset", "slope", "quad");
  fit->SetParameters(0., 1., 0.1);
  // fit->SetParNames("slope");
  // fit->SetParameter(0, 1.);

  prof->Fit("fit", "QBRW", "", 1, 21);

  float offset = fit->GetParameter(0);
  float slope = fit->GetParameter(1);
  float quad = fit->GetParameter(2);
  float chi2 = fit->GetChisquare()/fit->GetNDF();

  float offset_err = fit->GetParError(0);
  float slope_err = fit->GetParError(1);
  float quad_err = fit->GetParError(2);

  ofstream fOut("Rootfiles/ParametersHits.txt");
  fOut << "#Offset \t slope \t quad \t chi2" << endl;
  cout << offset << " " << slope << " " << quad << " " << chi2 << endl;
  fOut << offset << "\t" << slope << "\t" << quad << "\t" << chi2 << endl;
  fOut.close();

  TPaveText *pt2 = new TPaveText(0.2, 0.60, 0.5, 0.78, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(kBlack);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.03);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("f(x) = a*x^{2} + b*x +c");
  pt2->AddText(TString::Format("a: %2.2f #pm %2.2f ns", quad, quad_err));
  pt2->AddText(TString::Format("b: %2.2f #pm %2.2f ns", slope, slope_err));
  pt2->AddText(TString::Format("c: %2.2f #pm %2.2f ns", offset, offset_err));

  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  c1->cd();
  prof->Draw();
  pt->Draw("same");
  pt2->Draw("same");

  c1->SaveAs("Plots/NumberHits_Dependance_AllEnergies.pdf");
}

void Parametrisation()
{
  CaliceStyle();

  TFile *f10 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/10GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");

  TH1F* hData_10;

  f10->GetObject("Timing_AHCAL_Electron", hData_10);

  hData_10->Sumw2();
  hData_10->GetXaxis()->SetRangeUser(-30, 30);
  hData_10->Scale(1./hData_10->Integral(hData_10->GetXaxis()->FindBin(-30), hData_10->GetXaxis()->FindBin(30), "width"));
  hData_10->SetLineColor(kBlack);
  hData_10->SetLineWidth(3);

  //------------------------------------------

  TFile *f15 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/15GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");

  TH1F* hData_15;

  f15->GetObject("Timing_AHCAL_Electron", hData_15);

  hData_15->Sumw2();
  hData_15->GetXaxis()->SetRangeUser(-30, 30);
  hData_15->Scale(1./hData_15->Integral(hData_15->GetXaxis()->FindBin(-30), hData_15->GetXaxis()->FindBin(30), "width"));
  hData_15->SetLineColor(kRed);
  hData_15->SetLineWidth(3);

  //--------------------------------------------

  TFile *f20 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/20GeV/Data/Timing_FullAHCAL_NHitsCorrected/Rootfiles/Timing_FullAHCAL.root", "OPEN");

  TH1F* hData_20;

  f20->GetObject("Timing_AHCAL_Electron", hData_20);

  hData_20->Sumw2();
  hData_20->GetXaxis()->SetRangeUser(-30, 30);
  hData_20->Scale(1./hData_20->Integral(hData_20->GetXaxis()->FindBin(-30), hData_20->GetXaxis()->FindBin(30), "width"));
  hData_20->SetLineColor(kBlue);
  hData_20->SetLineWidth(3);

  //------------------------------------------

  TFile *f30 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/30GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");

  TH1F* hData_30;

  f30->GetObject("Timing_AHCAL_Electron", hData_30);

  hData_30->Sumw2();
  hData_30->GetXaxis()->SetRangeUser(-30, 30);
  hData_30->Scale(1./hData_30->Integral(hData_30->GetXaxis()->FindBin(-30), hData_30->GetXaxis()->FindBin(30), "width"));
  hData_30->SetLineColor(kGreen);
  hData_30->SetLineWidth(3);

  //--------------------------------------------

  TFile *f40 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/40GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");

  TH1F* hData_40;

  f40->GetObject("Timing_AHCAL_Electron", hData_40);

  hData_40->Sumw2();
  hData_40->GetXaxis()->SetRangeUser(-30, 30);
  hData_40->Scale(1./hData_40->Integral(hData_40->GetXaxis()->FindBin(-30), hData_40->GetXaxis()->FindBin(30), "width"));
  hData_40->SetLineColor(kMagenta);
  hData_40->SetLineWidth(3);

  //--------------------------------------------

  TFile *f50 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/50GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");

  TH1F* hData_50;

  f50->GetObject("Timing_AHCAL_Electron", hData_50);

  hData_50->Sumw2();
  hData_50->GetXaxis()->SetRangeUser(-30, 30);
  hData_50->Scale(1./hData_50->Integral(hData_50->GetXaxis()->FindBin(-30), hData_50->GetXaxis()->FindBin(30), "width"));
  hData_50->SetLineColor(kOrange+1);
  hData_50->SetLineWidth(3);

  //--------------------------------------------

  TPaveText *pt2 = new TPaveText(0.2, 0.82, 0.4, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");

  // TCanvas *c1 = new TCanvas("c1", "Comparison Data different energies", 800, 600);
  // hData_10->GetYaxis()->SetRangeUser(0.00001, 0.07);
  // hData_10->GetYaxis()->SetTitle("normalised entries");
  // hData_10->Draw("hist");
  // hData_15->Draw("hist same");
  // hData_20->Draw("hist same");
  // hData_30->Draw("hist same");
  // hData_40->Draw("hist same");
  // hData_50->Draw("hist same");
  // pt->Draw("same");
  // leg->Draw("same");
  //
  // c1->SaveAs("ComparisonDataEnergies.pdf");

  //Ratio of energies compared to 20GeV
  TH1F *hRatio20 = (TH1F*)hData_20->Clone("hRatio20");
  hRatio20->Divide(hData_20);
  hRatio20->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatio20->GetYaxis()->CenterTitle();
  hRatio20->GetYaxis()->SetTitle("Ratio to 20 GeV");
  hRatio20->GetYaxis()->SetTitleSize(0.035);
  hRatio20->GetYaxis()->SetTitleOffset(1.4);
  hRatio20->GetYaxis()->SetNdivisions(505);

  TH1F *hRatio10 = (TH1F*)hData_10->Clone("hRatio10");
  hRatio10->Divide(hData_20);
  hRatio10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatio10->GetYaxis()->CenterTitle();
  hRatio10->GetYaxis()->SetTitle("Ratio to 20 GeV");
  hRatio10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatio15 = (TH1F*)hData_15->Clone("hRatio15");
  hRatio15->Divide(hData_20);
  hRatio15->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatio15->GetYaxis()->CenterTitle();
  hRatio15->GetYaxis()->SetTitle("Ratio to 20 GeV");
  hRatio15->GetYaxis()->SetNdivisions(505);

  TH1F *hRatio30 = (TH1F*)hData_30->Clone("hRatio30");
  hRatio30->Divide(hData_20);
  hRatio30->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatio30->GetYaxis()->CenterTitle();
  hRatio30->GetYaxis()->SetTitle("Ratio to 20 GeV");
  hRatio30->GetYaxis()->SetNdivisions(505);

  TH1F *hRatio40 = (TH1F*)hData_40->Clone("hRatio40");
  hRatio40->Divide(hData_20);
  hRatio40->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatio40->GetYaxis()->CenterTitle();
  hRatio40->GetYaxis()->SetTitle("Ratio to 20 GeV");
  hRatio40->GetYaxis()->SetNdivisions(505);

  TH1F *hRatio50 = (TH1F*)hData_50->Clone("hRatio50");
  hRatio50->Divide(hData_20);
  hRatio50->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatio50->GetYaxis()->CenterTitle();
  hRatio50->GetYaxis()->SetTitle("Ratio to 20 GeV");
  hRatio50->GetYaxis()->SetNdivisions(505);

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.04);
  leg3->AddEntry(hData_10, "10 GeV e-", "l");
  leg3->AddEntry(hData_15, "15 GeV e-", "l");
  leg3->AddEntry(hData_20, "20 GeV e-", "l");
  leg3->AddEntry(hData_30, "30 GeV e-", "l");
  leg3->AddEntry(hData_40, "40 GeV e-", "l");
  leg3->AddEntry(hData_50, "50 GeV e-", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.60;

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hData_20, sFactor);
  setupAxisScalingBottom(hRatio20, sFactor);
  pad1->cd();
  hData_20->GetYaxis()->SetRangeUser(0.00001, 0.07);
  hData_20->GetYaxis()->SetTitle("normalised entries");
  hData_20->Draw("hist");
  hData_15->Draw("hist same");
  hData_10->Draw("hist same");
  hData_30->Draw("hist same");
  hData_40->Draw("hist same");
  hData_50->Draw("hist same");
  pt->Draw("same");
  leg3->Draw("same");
  pad2->cd();
  hRatio20->Draw("hist");
  hRatio20->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatio15->Draw("hist same");
  hRatio10->Draw("hist same");
  hRatio30->Draw("hist same");
  hRatio40->Draw("hist same");
  hRatio50->Draw("hist same");

  c->SaveAs("Plots/ComparisonDataEnergies.pdf");

  //------------------------------------------ PARAMETRISATION ------------------------------------------------------------

  TFile *f10_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/10GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_10;

  f10_Para->GetObject("ParametrisationHitBins2", hPara_10);

  hPara_10->SetMarkerStyle(20);
  hPara_10->SetMarkerColor(kBlack);
  hPara_10->SetLineColor(kBlack);
  hPara_10->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f15_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/15GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_15;

  f15_Para->GetObject("ParametrisationHitBins2", hPara_15);

  hPara_15->SetMarkerStyle(20);
  hPara_15->SetMarkerColor(kRed);
  hPara_15->SetLineColor(kRed);
  hPara_15->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f20_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/20GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_20;

  f20_Para->GetObject("ParametrisationHitBins2", hPara_20);

  hPara_20->SetMarkerStyle(20);
  hPara_20->SetMarkerColor(kBlue);
  hPara_20->SetLineColor(kBlue);
  hPara_20->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f30_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/30GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_30;

  f30_Para->GetObject("ParametrisationHitBins2", hPara_30);

  hPara_30->SetMarkerStyle(20);
  hPara_30->SetMarkerColor(kGreen);
  hPara_30->SetLineColor(kGreen);
  hPara_30->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f40_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/40GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_40;

  f40_Para->GetObject("ParametrisationHitBins2", hPara_40);

  hPara_40->SetMarkerStyle(20);
  hPara_40->SetMarkerColor(kMagenta);
  hPara_40->SetLineColor(kMagenta);
  hPara_40->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f50_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/50GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_50;

  f50_Para->GetObject("ParametrisationHitBins2", hPara_50);

  hPara_50->SetMarkerStyle(20);
  hPara_50->SetMarkerColor(kOrange+1);
  hPara_50->SetLineColor(kOrange+1);
  hPara_50->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TLegend* leg2 = new TLegend(0.2, 0.55, 0.40, 0.78);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->AddEntry(hPara_10, "10 GeV e-", "l");
  leg2->AddEntry(hPara_15, "15 GeV e-", "l");
  leg2->AddEntry(hPara_20, "20 GeV e-", "l");
  leg2->AddEntry(hPara_30, "30 GeV e-", "l");
  leg2->AddEntry(hPara_40, "40 GeV e-", "l");
  leg2->AddEntry(hPara_50, "50 GeV e-", "l");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(hPara_10);
  multi->Add(hPara_15);
  multi->Add(hPara_20);
  multi->Add(hPara_30);
  multi->Add(hPara_40);
  multi->Add(hPara_50);

  TCanvas *c2 = new TCanvas("c2", "Comparison Parametrisation different energies", 800, 600);
  multi->Draw("APLX");
  multi->GetXaxis()->SetTitle("Number of triggered channels above 0.5 MIPs");
  multi->GetYaxis()->SetTitle("#sigma_{effect} [ns]");
  multi->GetYaxis()->SetRangeUser(-1, 20);
  pt2->Draw("same");
  leg2->Draw("same");

  c2->SaveAs("Plots/ComparisonDataParamEnergies.pdf");
}

void MeanParametrisation()
{
  CaliceStyle();

  //------------------------------------------ PARAMETRISATION ------------------------------------------------------------

  TFile *f10_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/10GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_10;

  f10_Para->GetObject("ParametrisationHitBins2", hPara_10);

  hPara_10->SetMarkerStyle(20);
  hPara_10->SetMarkerColor(kBlack);
  hPara_10->SetLineColor(kBlack);
  hPara_10->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f15_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/15GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_15;

  f15_Para->GetObject("ParametrisationHitBins2", hPara_15);

  hPara_15->SetMarkerStyle(20);
  hPara_15->SetMarkerColor(kRed);
  hPara_15->SetLineColor(kRed);
  hPara_15->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f20_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/20GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_20;

  f20_Para->GetObject("ParametrisationHitBins2", hPara_20);

  hPara_20->SetMarkerStyle(20);
  hPara_20->SetMarkerColor(kBlue);
  hPara_20->SetLineColor(kBlue);
  hPara_20->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f30_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/30GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_30;

  f30_Para->GetObject("ParametrisationHitBins2", hPara_30);

  hPara_30->SetMarkerStyle(20);
  hPara_30->SetMarkerColor(kGreen);
  hPara_30->SetLineColor(kGreen);
  hPara_30->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f40_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/40GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_40;

  f40_Para->GetObject("ParametrisationHitBins2", hPara_40);

  hPara_40->SetMarkerStyle(20);
  hPara_40->SetMarkerColor(kMagenta);
  hPara_40->SetLineColor(kMagenta);
  hPara_40->SetLineWidth(2);

  //----------------------------------------------------------------------------

  TFile *f50_Para = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/50GeV/Data/Checks/TimingEnergyBins/Rootfiles/TimingParametrizationHitBins.root", "OPEN");

  TGraphErrors* hPara_50;

  f50_Para->GetObject("ParametrisationHitBins2", hPara_50);

  hPara_50->SetMarkerStyle(20);
  hPara_50->SetMarkerColor(kOrange+1);
  hPara_50->SetLineColor(kOrange+1);
  hPara_50->SetLineWidth(2);

  //----------------- BUILD Mean Parametrisation -------------------------------

  TGraphErrors *hMean = new TGraphErrors();

  hMean->SetMarkerStyle(24);
  hMean->SetMarkerColor(kBlack);
  hMean->SetLineColor(kBlack);
  hMean->SetLineWidth(3);
  hMean->SetLineStyle(2);

  TGraphAsymmErrors *hMean_clone = new TGraphAsymmErrors();

  hMean_clone->SetMarkerStyle(24);
  hMean_clone->SetMarkerColor(kBlack);
  hMean_clone->SetLineColor(kBlack);
  hMean_clone->SetLineWidth(3);
  hMean_clone->SetFillColor(kGray);

  TGraphErrors *hError_low = new TGraphErrors();
  hError_low->SetMarkerStyle(22);

  TGraphErrors *hError_up = new TGraphErrors();
  hError_up->SetMarkerStyle(22);

  for(int i = 0; i < hPara_10->GetN(); i++)
  {
    double x_10, y_10;
    hPara_10->GetPoint(i, x_10, y_10);
    double err_10 = hPara_10->GetErrorY(i);

    double x_15, y_15;
    hPara_15->GetPoint(i, x_15, y_15);
    double err_15 = hPara_15->GetErrorY(i);

    double x_20, y_20;
    hPara_20->GetPoint(i, x_20, y_20);
    double err_20 = hPara_20->GetErrorY(i);

    double x_30, y_30;
    hPara_30->GetPoint(i, x_30, y_30);
    double err_30 = hPara_30->GetErrorY(i);

    double x_40, y_40;
    hPara_40->GetPoint(i, x_40, y_40);
    double err_40 = hPara_40->GetErrorY(i);

    double x_50, y_50;
    hPara_50->GetPoint(i, x_50, y_50);
    double err_50 = hPara_50->GetErrorY(i);

    // cout << "10 GeV x " << x_10 << " y " << y_10 << endl;
    // cout << "15 GeV x " << x_15 << " y " << y_15 << endl;
    // cout << "20 GeV x " << x_20 << " y " << y_20 << endl;
    // cout << "30 GeV x " << x_30 << " y " << y_30 << endl;
    // cout << "40 GeV x " << x_40 << " y " << y_40 << endl;
    // cout << "50 GeV x " << x_50 << " y " << y_50 << endl;

    double mean = (y_10 + y_15 + y_20 + y_30 + y_40 + y_50)/6;
    double mean_error = TMath::Sqrt( err_10*err_10 + err_15*err_15 + err_20*err_20 + err_30*err_30 + err_40*err_40 + err_50*err_50 );

    double min = 1000;
    double max = 0;

    if(y_10 < min)
    min = y_10;
    if(y_15 < min)
    min = y_15;
    if(y_20 < min)
    min = y_20;
    if(y_30 < min)
    min = y_30;
    if(y_40 < min)
    min = y_40;
    if(y_50 < min)
    min = y_50;

    if(y_10 > max)
    max = y_10;
    if(y_15 > max)
    max = y_15;
    if(y_20 > max)
    max = y_20;
    if(y_30 > max)
    max = y_30;
    if(y_40 > max)
    max = y_40;
    if(y_50 > max)
    max = y_50;

    double error_low = TMath::Abs(mean - min);
    double error_high = TMath::Abs(mean - max);

    hMean->SetPoint(i, x_10, mean);
    hMean->SetPointError(i, 0, mean_error);

    hMean_clone->SetPoint(i, x_10, mean);
    hMean_clone->SetPointError(i, 0, 0, error_low, error_high);

    hError_low->SetPoint(i, x_10, mean - error_low);
    hError_up->SetPoint(i, x_10, mean + error_high);
  }

  for(int i = hPara_10->GetN(); i < hPara_15->GetN(); i++)
  {
    double x_15, y_15;
    hPara_15->GetPoint(i, x_15, y_15);
    double err_15 = hPara_15->GetErrorY(i);

    double x_20, y_20;
    hPara_20->GetPoint(i, x_20, y_20);
    double err_20 = hPara_20->GetErrorY(i);

    double x_30, y_30;
    hPara_30->GetPoint(i, x_30, y_30);
    double err_30 = hPara_30->GetErrorY(i);

    double x_40, y_40;
    hPara_40->GetPoint(i, x_40, y_40);
    double err_40 = hPara_40->GetErrorY(i);

    double x_50, y_50;
    hPara_50->GetPoint(i, x_50, y_50);
    double err_50 = hPara_50->GetErrorY(i);

    // cout << "10 GeV x " << x_10 << " y " << y_10 << endl;
    // cout << "15 GeV x " << x_15 << " y " << y_15 << endl;
    // cout << "20 GeV x " << x_20 << " y " << y_20 << endl;
    // cout << "30 GeV x " << x_30 << " y " << y_30 << endl;
    // cout << "40 GeV x " << x_40 << " y " << y_40 << endl;
    // cout << "50 GeV x " << x_50 << " y " << y_50 << endl;

    double mean = (y_15 + y_20 + y_30 + y_40 + y_50)/5;
    double mean_error = TMath::Sqrt( err_15*err_15 + err_20*err_20 + err_30*err_30 + err_40*err_40 + err_50*err_50 );

    double min = 1000;
    double max = 0;

    if(y_15 < min)
    min = y_15;
    if(y_20 < min)
    min = y_20;
    if(y_30 < min)
    min = y_30;
    if(y_40 < min)
    min = y_40;
    if(y_50 < min)
    min = y_50;

    if(y_15 > max)
    max = y_15;
    if(y_20 > max)
    max = y_20;
    if(y_30 > max)
    max = y_30;
    if(y_40 > max)
    max = y_40;
    if(y_50 > max)
    max = y_50;

    double error_low = TMath::Abs(mean - min);
    double error_high = TMath::Abs(mean - max);

    hMean->SetPoint(i, x_15, mean);
    hMean->SetPointError(i, 0, mean_error);

    hMean_clone->SetPoint(i, x_15, mean);
    hMean_clone->SetPointError(i, 0, 0, error_low, error_high);

    hError_low->SetPoint(i, x_15, mean - error_low);
    hError_up->SetPoint(i, x_15, mean + error_high);
  }

  //Add point by interpolation
  hMean_clone->SetPoint(11, 12, hMean_clone->Eval(12));
  hMean_clone->SetPoint(12, 13, hMean_clone->Eval(13));
  hMean_clone->SetPoint(13, 14, hMean_clone->Eval(14));
  hMean_clone->SetPoint(14, 15, hMean_clone->Eval(15));

  double error_low_last = TMath::Abs(hMean_clone->Eval(11) - hError_low->Eval(11));
  double error_high_last = TMath::Abs(hError_up->Eval(11) - hMean_clone->Eval(11));

  hMean_clone->SetPointError(11, 0, 0, error_low_last, error_high_last);
  hMean_clone->SetPointError(12, 0, 0, error_low_last, error_high_last);
  hMean_clone->SetPointError(13, 0, 0, error_low_last, error_high_last);
  hMean_clone->SetPointError(14, 0, 0, error_low_last, error_high_last);

  hError_low->SetPoint(11, 12, TMath::Abs(hMean_clone->Eval(12) - error_low_last));
  hError_low->SetPoint(12, 13, TMath::Abs(hMean_clone->Eval(13) - error_low_last));
  hError_low->SetPoint(13, 14, TMath::Abs(hMean_clone->Eval(14) - error_low_last));
  hError_low->SetPoint(14, 15, TMath::Abs(hMean_clone->Eval(15) - error_low_last));

  hError_up->SetPoint(11, 12, TMath::Abs(hMean_clone->Eval(12) + error_high_last));
  hError_up->SetPoint(12, 13, TMath::Abs(hMean_clone->Eval(13) + error_high_last));
  hError_up->SetPoint(13, 14, TMath::Abs(hMean_clone->Eval(14) + error_high_last));
  hError_up->SetPoint(14, 15, TMath::Abs(hMean_clone->Eval(15) + error_high_last));

  //----------------------------------------------------------------------------

  TLegend* leg2 = new TLegend(0.2, 0.52, 0.4, 0.78);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->AddEntry(hPara_10, "10 GeV e-", "l");
  leg2->AddEntry(hPara_15, "15 GeV e-", "l");
  leg2->AddEntry(hPara_20, "20 GeV e-", "l");
  leg2->AddEntry(hPara_30, "30 GeV e-", "l");
  leg2->AddEntry(hPara_40, "40 GeV e-", "l");
  leg2->AddEntry(hPara_50, "50 GeV e-", "l");
  leg2->AddEntry(hMean, "Mean Parametrisation", "l");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(hPara_10);
  multi->Add(hPara_15);
  multi->Add(hPara_20);
  multi->Add(hPara_30);
  multi->Add(hPara_40);
  multi->Add(hPara_50);
  multi->Add(hMean);

  //--------------------------------------------------------------

  TPaveText *pt = new TPaveText(0.2, 0.82, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c2 = new TCanvas("c2", "Comparison Parametrisation different energies", 800, 600);
  multi->Draw("APLX");
  multi->GetXaxis()->SetTitle("Number of triggered channels above 0.5 MIPs");
  multi->GetYaxis()->SetTitle("#sigma_{effect} [ns]");
  multi->GetYaxis()->SetRangeUser(-1, 20);
  pt->Draw("same");
  leg2->Draw("same");

  c2->SaveAs("Plots/MeanParametrisation.pdf");

  hMean_clone->SetMarkerStyle(20);

  TLegend* leg3 = new TLegend(0.2, 0.72, 0.4, 0.78);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->AddEntry(hMean_clone, "Mean Parametrisation", "p");

  TCanvas *c3 = new TCanvas("c3", "Mean Parametrisation", 800, 600);
  hMean_clone->Draw("APX");
  hMean_clone->GetXaxis()->SetTitle("Number of triggered channels above 0.5 MIPs");
  hMean_clone->GetYaxis()->SetTitle("#sigma_{effect} [ns]");
  hMean_clone->Draw("E3 same");
  hMean_clone->Draw("PX same");
  hMean_clone->GetXaxis()->SetLimits(0., 16.);
  pt->Draw("same");
  leg3->Draw("same");

  c3->SaveAs("Plots/MeanParametrisationWithSystErrors.pdf");
}

void Timing_AfterMuons()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Timing_FullAHCAL_AfterMuons.root", "OPEN");
  TH1F *h;

  f->GetObject("Timing_AHCAL_Electron", h);

  h->SetLineColor(kBlack);
  h->SetLineWidth(2);
  h->GetXaxis()->SetTitle("Time of first hit [ns]");
  h->GetYaxis()->SetTitle("# Entries / ns");
  h->GetYaxis()->SetTitleOffset(1.4);
  h->GetXaxis()->SetRangeUser(-50, 50);

  TPaveText *pt = new TPaveText(0.17, 0.82, 0.35, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TPaveText *pt2 = new TPaveText(0.65, 0.65, 0.85, 0.9, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(1);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.03);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("20 GeV e");
  pt2->AddText(TString::Format("Max: %2.3f ns", h->GetXaxis()->GetBinCenter(h->GetMaximumBin())));
  pt2->AddText(TString::Format("RMS: %2.3f ns", h->GetRMS()));

  TCanvas *c1 = new TCanvas("c1", "Full AHCAL Timing (Electrons)", 800, 600);
  c1->cd();
  h->Draw();
  pt->Draw("same");
  pt2->Draw("SAME");

  c1->SaveAs("Plots/Timing_AllLayers_AfterMuons.pdf");
}

void Timing_AHCAL_20GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Timing_FullAHCAL_20GeV.root", "OPEN");
  TH1F *histo;
  TH1F* hDataElectrons;

  f->GetObject("Timing_AHCAL_Electron", histo);

  histo->GetXaxis()->SetRangeUser(-30, 30);
  histo->SetLineColor(kBlack);
  histo->SetLineWidth(2);
  histo->GetYaxis()->SetTitleOffset(1.4);

  TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TPaveText *pt2 = new TPaveText(0.68, 0.7, 0.88, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(1);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.03);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("20 GeV e");
  pt2->AddText(TString::Format("Mean: %2.3f ns", histo->GetMean()));
  pt2->AddText(TString::Format("RMS: %2.3f ns", histo->GetRMS()));

  TCanvas *c1 = new TCanvas("c1", "Full AHCAL Timing (Electrons)", 800, 600);
  c1->cd();
  //gPad->SetLogy();
  histo->Draw();
  pt->Draw("SAME");
  pt2->Draw("SAME");

  c1->SaveAs("Plots/Timing_AllLayers_20GeV.pdf");

  TFile *f2 = new TFile("../Muons/Rootfiles/AHCALTiming.root", "OPEN");
  TH1F *hDataMuons;

  f2->GetObject("Timing_AHCAL_Muons", hDataMuons);
  hDataMuons->GetFunction("f5")->Delete();

  hDataMuons->Scale(1./hDataMuons->Integral("width"));
  hDataMuons->SetLineColor(9);
  hDataMuons->SetFillColor(9);
  hDataMuons->SetFillStyle(3001);
  hDataMuons->SetLineWidth(2);
  hDataMuons->GetXaxis()->SetRangeUser(-30, 30);

  f->GetObject("hTimingSingleHit", hDataElectrons);
  hDataElectrons->Scale(1./hDataElectrons->Integral("width"));
  hDataElectrons->SetLineColor(kRed);
  hDataElectrons->SetLineWidth(2);
  hDataElectrons->GetXaxis()->SetRangeUser(-30, 30);

  TLegend *leg2 = new TLegend(0.62, 0.72, 0.82, 0.9);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.03);
  leg2->SetHeader("20 GeV e");
  leg2->AddEntry(histo, TString::Format("All hits - RMS: %2.3f ns", histo->GetRMS()), "l");
  leg2->AddEntry(hDataElectrons, TString::Format("Single hit - RMS: %2.3f ns", hDataElectrons->GetRMS()), "l");
  leg2->AddEntry(hDataMuons, TString::Format("Muons - RMS: %2.3f ns", hDataMuons->GetRMS()), "f");

  hDataMuons->GetYaxis()->SetTitle("normalised entries");

  TCanvas *c2 = new TCanvas("c2", "e all/e single comparison", 800, 600);
  hDataMuons->Draw();
  hDataElectrons->Draw("hist same");
  histo->Draw("hist same");
  pt->Draw("same");
  leg2->Draw("same");

  c2->SaveAs("Plots/ComparisonAll_ElectronsSingleHit.pdf");

  float nCore = histo->Integral(histo->GetXaxis()->FindBin(-35), histo->GetXaxis()->FindBin(35));
  float nRightTail = histo->Integral(histo->GetXaxis()->FindBin(35), histo->GetXaxis()->FindBin(2000));
  cout << "Integral between +/- 5 sigmas " << nCore << endl;
  cout << "Percentage of events between 5 sigma and 2000 ns " << nRightTail/nCore*100 << "%" << endl;
}

void CheckParametrisation()
{
  CaliceStyle();

  TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  //----------------------------------------------------------

  TFile *f3 = new TFile("Rootfiles/TimingHitBins.root", "OPEN");
  TH1F *hBin1_Hit, *hBin2_Hit, *hBin3_Hit, *hBin4_Hit;

  f3->GetObject("Timing_HitBin1", hBin1_Hit);
  f3->GetObject("Timing_HitBin2", hBin2_Hit);
  f3->GetObject("Timing_HitBin3", hBin3_Hit);
  f3->GetObject("Timing_HitBin4", hBin4_Hit);

  hBin1_Hit->GetXaxis()->SetTitle("Time of first hit [ns]");
  hBin1_Hit->GetYaxis()->SetTitle("# Entries / ns");
  hBin1_Hit->SetLineColor(kBlue);
  hBin1_Hit->SetLineWidth(2);

  hBin2_Hit->GetXaxis()->SetTitle("Time of first hit [ns]");
  hBin2_Hit->GetYaxis()->SetTitle("# Entries / ns");
  hBin2_Hit->SetLineColor(kRed);
  hBin2_Hit->SetLineWidth(2);

  hBin3_Hit->GetXaxis()->SetTitle("Time of first hit [ns]");
  hBin3_Hit->GetYaxis()->SetTitle("# Entries / ns");
  hBin3_Hit->SetLineColor(kGreen+3);
  hBin3_Hit->SetLineWidth(2);

  hBin4_Hit->GetXaxis()->SetTitle("Time of first hit [ns]");
  hBin4_Hit->GetYaxis()->SetTitle("# Entries / ns");
  hBin4_Hit->SetLineColor(kMagenta);
  hBin4_Hit->SetLineWidth(2);

  hBin1_Hit->Scale(1./hBin1_Hit->Integral("width"));
  hBin2_Hit->Scale(1./hBin2_Hit->Integral("width"));
  hBin3_Hit->Scale(1./hBin3_Hit->Integral("width"));
  hBin4_Hit->Scale(1./hBin4_Hit->Integral("width"));

  TLegend *leg3 = new TLegend(0.57, 0.7, 0.90, 0.9);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(hBin1_Hit, "Triggered Channels < 3", "l");
  leg3->AddEntry(hBin2_Hit, "3 < Triggered Channels < 5", "l");
  leg3->AddEntry(hBin3_Hit, "5 < Triggered Channels < 10", "l");
  leg3->AddEntry(hBin4_Hit, "Triggered Channels > 10", "l");

  TCanvas *c3 = new TCanvas("c3", "TimingDistribution with nHits Bins", 800, 600);
  c3->cd();
  hBin1_Hit->GetXaxis()->SetRangeUser(-40, 50);
  hBin1_Hit->Draw();
  pt->Draw("same");
  hBin1_Hit->Draw("same");
  hBin2_Hit->Draw("same");
  hBin3_Hit->Draw("same");
  hBin4_Hit->Draw("same");
  leg3->Draw("same");

  c3->SaveAs("Plots/TimingHitsBins.pdf");

  TFile* f1 = new TFile("Rootfiles/TimingParametrizationHitBins.root", "OPEN");
  TGraphErrors *hParametrization;

  f1->GetObject("ParametrisationHitBins", hParametrization);

  hParametrization->SetMarkerStyle(20);
  hParametrization->SetMarkerSize(0.7);
  hParametrization->GetXaxis()->SetTitle("Number of triggered channels above 0.5 MIP");
  hParametrization->GetYaxis()->SetTitle("RMS [ns]");

  TPaveText *pt2 = new TPaveText(0.2, 0.78, 0.5, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("20 GeV e-");

  TCanvas *c1 = new TCanvas("c1", "Parametrisation Raw", 800, 600);
  hParametrization->Draw("APL");
  hParametrization->GetXaxis()->SetTitle("Number of triggered channels over 0.5 MIPs");
  hParametrization->GetYaxis()->SetTitle("RMS [ns]");
  pt2->Draw("same");

  c1->SaveAs("Plots/ParametrisationPedestalShift_20GeV.pdf");
}

void ComparisonSimData_nHits20GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/NumberHits_20GeV.root", "OPEN");
  TH1F *hHitSim, *hHitSim_Xtalk10, *hHitSim_Xtalk18;

  f->GetObject("hHitSim", hHitSim);
  f->GetObject("hHitSim_Xtalk10", hHitSim_Xtalk10);
  f->GetObject("hHitSim_Xtalk18", hHitSim_Xtalk18);

  hHitSim->Sumw2();
  hHitSim->Scale(1./hHitSim->Integral("width"));

  hHitSim->SetLineColor(kRed);
  hHitSim->SetLineWidth(2);

  hHitSim_Xtalk10->Sumw2();
  hHitSim_Xtalk10->Scale(1./hHitSim_Xtalk10->Integral("width"));

  hHitSim_Xtalk10->SetLineColor(kGreen);
  hHitSim_Xtalk10->SetLineWidth(2);

  hHitSim_Xtalk18->Sumw2();
  hHitSim_Xtalk18->Scale(1./hHitSim_Xtalk18->Integral("width"));

  hHitSim_Xtalk18->SetLineColor(kMagenta);
  hHitSim_Xtalk18->SetLineWidth(2);

  //-------------------------------------------

  TH1F *hHitData;
  f->GetObject("hHitData", hHitData);

  hHitData->Sumw2();
  hHitData->Scale(1./hHitData->Integral("width"));

  hHitData->SetMarkerStyle(20);
  hHitData->SetMarkerColor(kBlack);

  hHitData->GetYaxis()->SetTitle("normalised entries");

  //--------------------------------------------

  TH1F* hHitSim_DD4hep, *hHitSim_DD4hep_Xtalk10, *hHitSim_DD4hep_Xtalk18;
  f->GetObject("hHitSim_DD4hep", hHitSim_DD4hep);
  f->GetObject("hHitSim_DD4hep_Xtalk10", hHitSim_DD4hep_Xtalk10);
  f->GetObject("hHitSim_DD4hep_Xtalk18", hHitSim_DD4hep_Xtalk18);

  hHitSim_DD4hep->Sumw2();
  hHitSim_DD4hep->Scale(1./hHitSim_DD4hep->Integral("width"));

  hHitSim_DD4hep->SetLineColor(kBlue);
  hHitSim_DD4hep->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk10->Sumw2();
  hHitSim_DD4hep_Xtalk10->Scale(1./hHitSim_DD4hep_Xtalk10->Integral("width"));

  hHitSim_DD4hep_Xtalk10->SetLineColor(kGreen);
  hHitSim_DD4hep_Xtalk10->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk18->Sumw2();
  hHitSim_DD4hep_Xtalk18->Scale(1./hHitSim_DD4hep_Xtalk18->Integral("width"));

  hHitSim_DD4hep_Xtalk18->SetLineColor(kMagenta);
  hHitSim_DD4hep_Xtalk18->SetLineWidth(2);

  //--------------------------------------------

  //Error handling (Xtalk)

  TGraphAsymmErrors *gHitSim = new TGraphAsymmErrors();
  gHitSim->SetLineColor(kRed);
  gHitSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim->GetBinError(ibin);

    gHitSim->SetPoint(ibin, hHitSim->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }


  TGraphAsymmErrors *gHitSim_DD4hep = new TGraphAsymmErrors();
  gHitSim_DD4hep->SetLineColor(kBlue);
  gHitSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim_DD4hep->GetBinError(ibin);

    gHitSim_DD4hep->SetPoint(ibin, hHitSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitData = new TGraphAsymmErrors();
  gHitData->SetLineWidth(0);
  gHitData->SetFillColor(kGray);
  gHitData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitData->GetBinContent(ibin);
    double error_stat = hHitData->GetBinError(ibin);

    gHitData->SetPoint(ibin, hHitData->GetXaxis()->GetBinCenter(ibin), content);
    gHitData->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //------------------------------------ Ratio ------------------------------------

  TH1F* hRatio = (TH1F*)hHitSim->Clone("hRatio");
  hRatio->Divide(hHitData);
  hRatio->GetYaxis()->SetTitle("MC/Data");
  hRatio->GetYaxis()->CenterTitle();

  TH1F* hRatio_Xtalk10 = (TH1F*)hHitSim_Xtalk10->Clone("hRatio_Xtalk10");
  hRatio_Xtalk10->Divide(hHitData);
  hRatio_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_Xtalk18 = (TH1F*)hHitSim_Xtalk18->Clone("hRatio_Xtalk18");
  hRatio_Xtalk18->Divide(hHitData);
  hRatio_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep = (TH1F*)hHitSim_DD4hep->Clone("hRatio_DD4hep");
  hRatio_DD4hep->Divide(hHitData);
  hRatio_DD4hep->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk10 = (TH1F*)hHitSim_DD4hep_Xtalk10->Clone("hRatio_DD4hep_Xtalk10");
  hRatio_DD4hep_Xtalk10->Divide(hHitData);
  hRatio_DD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk18 = (TH1F*)hHitSim_DD4hep_Xtalk18->Clone("hRatio_DD4hep_Xtalk18");
  hRatio_DD4hep_Xtalk18->Divide(hHitData);
  hRatio_DD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatioData = (TH1F*)hHitData->Clone("hRatioData");
  hRatioData->Divide(hHitData);

  //------ Error handling ----------------------------

  TGraphAsymmErrors *gHitSimRatio = new TGraphAsymmErrors();
  gHitSimRatio->SetLineColor(kRed);
  gHitSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio->GetBinError(ibin);

    gHitSimRatio->SetPoint(ibin, hRatio->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitSimRatio_DD4hep = new TGraphAsymmErrors();
  gHitSimRatio_DD4hep->SetLineColor(kBlue);
  gHitSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio_DD4hep->GetBinError(ibin);

    gHitSimRatio_DD4hep->SetPoint(ibin, hRatio_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitDataRatio = new TGraphAsymmErrors();
  gHitDataRatio->SetLineColor(kBlack);
  gHitDataRatio->SetLineWidth(2);
  gHitDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    gHitDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gHitDataRatio->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //--------------------------------------------------

  TLegend* leg = new TLegend(0.65, 0.35, 0.85, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader("20 GeV e-");
  leg->AddEntry(gHitData, "Data", "pf");
  leg->AddEntry(gHitSim, "Mokka (QGSP_BERT_HP)", "l");
  leg->AddEntry(gHitSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.65, 0.70, 0.85, 0.85, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.6;

  TCanvas *c1;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c1, "c1", "c1", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hHitData, sFactor);
  setupAxisScalingBottom(hRatio, sFactor);
  pad1->cd();
  pad1->SetLogy();
  hHitData->GetXaxis()->SetRangeUser(1, 20);
  hHitData->Draw("p hist");
  gHitData->Draw("E2");
  gHitSim->Draw("PE");
  gHitSim_DD4hep->Draw("PE");
  hHitData->Draw("p hist same");
  pt->Draw("same");
  leg->Draw("same");
  pad2->cd();
  hRatio->GetYaxis()->SetRangeUser(0, 1.5);
  hRatio->GetXaxis()->SetRangeUser(1, 20);
  hRatio->Draw("p hist");
  gHitDataRatio->Draw("E2");
  gHitSimRatio->Draw("PE");
  gHitSimRatio_DD4hep->Draw("PE");
  hRatioData->Draw("p hist same");

  c1->SaveAs("Plots/Comparison_SimData_Electrons_nHits_20GeV.pdf");
}

void ComparisonSimData_Timing20GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMokka_20GeV.root", "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(1, hTimeSim->GetNbinsX(), "width"));
  hTimeSim->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(1, hTimeSim_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(1, hTimeSim_ErrorUp->GetNbinsX(), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(1, hTimeSim_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(1, hTimeSim_Xtalk18->GetNbinsX(), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("normalised entries");

  //-------------------------------------------------

  TFile *f2 = new TFile("Rootfiles/Timing_FullAHCAL_20GeV.root", "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Electron", hData);

  hData->Sumw2();
  hData->Scale(1./hData->Integral(1, hData->GetNbinsX(), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  //hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //-------------------------------------------------

  //Ratio Plots
  TH1F* hRatioData = (TH1F*)hData->Clone("hRatioData");
  hRatioData->Divide(hData);
  hRatioData->GetYaxis()->SetTitle("MC/Data");
  hRatioData->SetMarkerStyle(20);
  hRatioData->SetMarkerColor(kBlack);

  TGraphAsymmErrors *gTimeDataRatio = new TGraphAsymmErrors();
  gTimeDataRatio->SetLineColor(kBlack);
  gTimeDataRatio->SetLineWidth(2);
  gTimeDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
  hRatioMokka->Divide(hData);
  hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka->GetYaxis()->CenterTitle();
  hRatioMokka->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorLow = (TH1F*)hTimeSim_ErrorLow->Clone("hRatioMokka_ErrorLow");
  hRatioMokka_ErrorLow->Divide(hData);
  hRatioMokka_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorLow->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorUp = (TH1F*)hTimeSim_ErrorUp->Clone("hRatioMokka_ErrorUp");
  hRatioMokka_ErrorUp->Divide(hData);
  hRatioMokka_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorUp->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk10 = (TH1F*)hTimeSim_Xtalk10->Clone("hRatioMokka_Xtalk10");
  hRatioMokka_Xtalk10->Divide(hData);
  hRatioMokka_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk10->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk18 = (TH1F*)hTimeSim_Xtalk18->Clone("hRatioMokka_Xtalk18");
  hRatioMokka_Xtalk18->Divide(hData);
  hRatioMokka_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk18->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
  gTimeSimRatio->SetLineColor(kRed);
  gTimeSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
  {
    double content = hRatioMokka->GetBinContent(ibin);
    double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioMokka_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioMokka_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioMokka->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //***************************************************************//
  //*
  //*
  //*
  //------------------- DD4hep -----------------------------

  TFile *f3 = new TFile("Rootfiles/TimingDD4hep_20GeV.root", "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F *hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kBlue);
  hTimeSim_DD4hep->SetMarkerColor(kBlue);
  hTimeSim_DD4hep->SetLineWidth(2);
  hTimeSim_DD4hep->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(1, hTimeSim_DD4hep->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(1, hTimeSim_DD4hep_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(1, hTimeSim_DD4hep_ErrorUp->GetNbinsX(), "width"));

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(1, hTimeSim_DD4hep_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(1, hTimeSim_DD4hep_Xtalk18->GetNbinsX(), "width"));

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kBlue);
  gTimeSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //----------------------------------------------

  TH1F *hRatioDD4hep = (TH1F*)hTimeSim_DD4hep->Clone("hRatioDD4hep");
  hRatioDD4hep->Divide(hData);
  hRatioDD4hep->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep->GetYaxis()->CenterTitle();
  hRatioDD4hep->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorLow = (TH1F*)hTimeSim_DD4hep_ErrorLow->Clone("hRatioDD4hep_ErrorLow");
  hRatioDD4hep_ErrorLow->Divide(hData);
  hRatioDD4hep_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorLow->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorLow->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorUp = (TH1F*)hTimeSim_DD4hep_ErrorUp->Clone("hRatioDD4hep_ErrorUp");
  hRatioDD4hep_ErrorUp->Divide(hData);
  hRatioDD4hep_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorUp->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorUp->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk10 = (TH1F*)hTimeSim_DD4hep_Xtalk10->Clone("hRatioDD4hep_Xtalk10");
  hRatioDD4hep_Xtalk10->Divide(hData);
  hRatioDD4hep_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk10->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk10->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk18 = (TH1F*)hTimeSim_DD4hep_Xtalk18->Clone("hRatioDD4hep_Xtalk18");
  hRatioDD4hep_Xtalk18->Divide(hData);
  hRatioDD4hep_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk18->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk18->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
  gTimeSimRatio_DD4hep->SetLineColor(kBlue);
  gTimeSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
  {
    double content = hRatioDD4hep->GetBinContent(ibin);
    double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioDD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioDD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioDD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //------------------------------------------------------------

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("20 GeV e-");
  leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
  leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT_HP)", "l");
  leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTimeSim, sFactor);
  setupAxisScalingBottom(hRatioMokka, sFactor);
  pad1->cd();
  hTimeSim->GetXaxis()->SetRangeUser(-30,30);
  hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.090);
  hTimeSim->Draw("p hist");
  gTimeData->Draw("E2");
  gTimeSim->Draw("PE");
  gTimeSim_DD4hep->Draw("PE");
  hData->GetXaxis()->SetRangeUser(-30,30);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioMokka->GetXaxis()->SetRangeUser(-30,30);
  hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatioMokka->Draw("p");
  gTimeDataRatio->Draw("E2");
  gTimeSimRatio->Draw("PE");
  gTimeSimRatio_DD4hep->Draw("PE");
  hRatioData->GetXaxis()->SetRangeUser(-30,30);
  hRatioData->Draw("p hist same");

  c->SaveAs("Plots/Comparison_SimData_Electrons20GeV.pdf");
}

void SelectionCuts_10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/SelectionCuts_10GeV.root", "OPEN");
  TH2F *hHitsCoGZ_Muons, *hHitsCoGZ_Electrons, *hHitsCoGZ_Pions;

  f->GetObject("hHitsCoGZ_Muons", hHitsCoGZ_Muons);
  f->GetObject("hHitsCoGZ_Electrons", hHitsCoGZ_Electrons);
  f->GetObject("hHitsCoGZ_Pions", hHitsCoGZ_Pions);

  hHitsCoGZ_Muons->SetLineColor(kBlue);
  hHitsCoGZ_Muons->SetLineWidth(2);
  hHitsCoGZ_Muons->GetXaxis()->SetTitle("AHCAL CoG Z [mm]");
  hHitsCoGZ_Muons->GetYaxis()->SetTitle("nHits");

  hHitsCoGZ_Electrons->SetLineColor(kGreen);
  hHitsCoGZ_Electrons->SetLineWidth(2);

  hHitsCoGZ_Pions->SetLineColor(kRed);
  hHitsCoGZ_Pions->SetLineWidth(2);

  TLegend *leg = new TLegend(0.62, 0.70, 0.90, 0.92);
  leg->SetHeader("AHCAL Simulation");
  leg->AddEntry(hHitsCoGZ_Muons, "Muons", "l");
  leg->AddEntry(hHitsCoGZ_Electrons, "Electrons", "l");
  leg->AddEntry(hHitsCoGZ_Pions, "Pions", "l");

  TLine *line = new TLine();
  line->SetX1(250.);
  line->SetX2(250.);
  line->SetY1(25.);
  line->SetY2(75);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);

  TLine *line2 = new TLine();
  line2->SetX1(0.);
  line2->SetX2(250.);
  line2->SetY1(25.);
  line2->SetY2(25.);
  line2->SetLineColor(kBlack);
  line2->SetLineWidth(3);

  TLine *line10 = new TLine();
  line10->SetX1(0.);
  line10->SetX2(250.);
  line10->SetY1(75.);
  line10->SetY2(75.);
  line10->SetLineColor(kBlack);
  line10->SetLineWidth(3);

  // TLine *line11 = new TLine();
  // line11->SetX1(90.);
  // line11->SetX2(250.);
  // line11->SetY1(90.);
  // line11->SetY2(90.);
  // line11->SetLineColor(kBlack);
  // line11->SetLineWidth(3);

  TCanvas *c1 = new TCanvas("c1", "nHits vs CoG Z", 800, 600);
  hHitsCoGZ_Muons->Draw("BOX");
  hHitsCoGZ_Electrons->Draw("BOX same");
  hHitsCoGZ_Pions->Draw("BOX same");
  line->Draw("same");
  line2->Draw("same");
  line10->Draw("same");
  //line11->Draw("same");
  leg->Draw("same");

  c1->SaveAs("Plots/SelectionCut_nHitsCoGZ_10GeV.pdf");

  //******************************************************//

  TH1F *hRatio_Muons, *hRatio_Electrons, *hRatio_Pions;

  f->GetObject("hRatio_Muons", hRatio_Muons);
  f->GetObject("hRatio_Electrons", hRatio_Electrons);
  f->GetObject("hRatio_Pions", hRatio_Pions);

  hRatio_Muons->Scale(1./hRatio_Muons->Integral());
  hRatio_Muons->SetLineColor(kBlue);
  hRatio_Muons->SetLineWidth(2);
  hRatio_Muons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Muons->GetYaxis()->SetTitle("# Events");

  hRatio_Electrons->Scale(1./hRatio_Electrons->Integral());
  hRatio_Electrons->SetLineColor(kGreen);
  hRatio_Electrons->SetLineWidth(2);
  hRatio_Electrons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Electrons->GetYaxis()->SetTitle("# Events");
  hRatio_Electrons->GetYaxis()->SetRangeUser(0.00001, 2);

  hRatio_Pions->Scale(1./hRatio_Pions->Integral());
  hRatio_Pions->SetLineColor(kRed);
  hRatio_Pions->SetLineWidth(2);

  TLine *line7 = new TLine();
  line7->SetX1(1.);
  line7->SetX2(1.);
  line7->SetY1(0.);
  line7->SetY2(2.);
  line7->SetLineColor(kBlack);
  line7->SetLineWidth(3);

  TCanvas *c3 = new TCanvas("c3", "Energy in last two layers", 800, 600);
  gPad->SetLogy();
  hRatio_Electrons->Draw("hist");
  hRatio_Muons->Draw("hist same");
  hRatio_Pions->Draw("hist same");
  leg->Draw("same");
  line7->Draw("same");

  c3->SaveAs("Plots/SelectionCut_EnergyLastLayers_10GeV.pdf");

  //******************************************************//

  TH1F *hEnergyE3_Muons, *hEnergyE3_Electrons, *hEnergyE3_Pions;

  f->GetObject("hEnergyE3_Muons", hEnergyE3_Muons);
  f->GetObject("hEnergyE3_Electrons", hEnergyE3_Electrons);
  f->GetObject("hEnergyE3_Pions", hEnergyE3_Pions);

  hEnergyE3_Muons->Scale(1./hEnergyE3_Muons->Integral());
  hEnergyE3_Muons->SetLineColor(kBlue);
  hEnergyE3_Muons->SetLineWidth(2);
  hEnergyE3_Muons->GetXaxis()->SetTitle("(E_{3}+E_{4}+E_{5}) [MIP]");
  hEnergyE3_Muons->GetYaxis()->SetTitle("# Events");
  hEnergyE3_Muons->GetYaxis()->SetRangeUser(0.00001, 2);

  hEnergyE3_Electrons->Scale(1./hEnergyE3_Electrons->Integral());
  hEnergyE3_Electrons->SetLineColor(kGreen);
  hEnergyE3_Electrons->SetLineWidth(2);
  hEnergyE3_Electrons->GetXaxis()->SetTitle("(E_{3}+E_{4}+E_{5}) [MIP]");
  hEnergyE3_Electrons->GetYaxis()->SetTitle("# Events");
  hEnergyE3_Electrons->GetYaxis()->SetRangeUser(0.00001, 2);

  hEnergyE3_Pions->Scale(1./hEnergyE3_Pions->Integral());
  hEnergyE3_Pions->SetLineColor(kRed);
  hEnergyE3_Pions->SetLineWidth(2);

  TLine *line20 = new TLine();
  line20->SetX1(10);
  line20->SetX2(10);
  line20->SetY1(0.);
  line20->SetY2(2.);
  line20->SetLineColor(kBlack);
  line20->SetLineWidth(3);

  TCanvas *c4 = new TCanvas("c4", "Energy in 3 first AHCAL layers", 800, 600);
  gPad->SetLogy();
  hEnergyE3_Muons->Draw("hist");
  hEnergyE3_Electrons->Draw("hist same");
  hEnergyE3_Pions->Draw("hist same");
  leg->Draw("same");
  line20->Draw("same");

  c4->SaveAs("Plots/SelectionCut_EnergyE3_10GeV.pdf");
}

void SelectionCuts_50GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/SelectionCuts_50GeV.root", "OPEN");
  TH2F *hHitsCoGZ_Muons, *hHitsCoGZ_Electrons, *hHitsCoGZ_Pions;

  f->GetObject("hHitsCoGZ_Muons", hHitsCoGZ_Muons);
  f->GetObject("hHitsCoGZ_Electrons", hHitsCoGZ_Electrons);
  f->GetObject("hHitsCoGZ_Pions", hHitsCoGZ_Pions);

  hHitsCoGZ_Muons->SetLineColor(kBlue);
  hHitsCoGZ_Muons->SetLineWidth(2);
  hHitsCoGZ_Muons->GetXaxis()->SetTitle("AHCAL CoG Z [mm]");
  hHitsCoGZ_Muons->GetYaxis()->SetTitle("nHits");

  hHitsCoGZ_Electrons->SetLineColor(kGreen);
  hHitsCoGZ_Electrons->SetLineWidth(2);

  hHitsCoGZ_Pions->SetLineColor(kRed);
  hHitsCoGZ_Pions->SetLineWidth(2);

  TLegend *leg = new TLegend(0.62, 0.70, 0.90, 0.92);
  leg->SetHeader("AHCAL Simulation");
  leg->AddEntry(hHitsCoGZ_Muons, "Muons", "l");
  leg->AddEntry(hHitsCoGZ_Electrons, "Electrons", "l");
  leg->AddEntry(hHitsCoGZ_Pions, "Pions", "l");

  TLine *line = new TLine();
  line->SetX1(250.);
  line->SetX2(250.);
  line->SetY1(70.);
  line->SetY2(140);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);

  TLine *line2 = new TLine();
  line2->SetX1(0.);
  line2->SetX2(250.);
  line2->SetY1(70.);
  line2->SetY2(70.);
  line2->SetLineColor(kBlack);
  line2->SetLineWidth(3);

  TLine *line10 = new TLine();
  line10->SetX1(0.);
  line10->SetX2(250.);
  line10->SetY1(140.);
  line10->SetY2(140.);
  line10->SetLineColor(kBlack);
  line10->SetLineWidth(3);

  // TLine *line11 = new TLine();
  // line11->SetX1(90.);
  // line11->SetX2(250.);
  // line11->SetY1(90.);
  // line11->SetY2(90.);
  // line11->SetLineColor(kBlack);
  // line11->SetLineWidth(3);

  TCanvas *c1 = new TCanvas("c1", "nHits vs CoG Z", 800, 600);
  hHitsCoGZ_Muons->Draw("BOX");
  hHitsCoGZ_Electrons->Draw("BOX same");
  hHitsCoGZ_Pions->Draw("BOX same");
  line->Draw("same");
  line2->Draw("same");
  line10->Draw("same");
  //line11->Draw("same");
  leg->Draw("same");

  c1->SaveAs("Plots/SelectionCut_nHitsCoGZ_50GeV.pdf");

  //******************************************************//

  TH1F *hRatio_Muons, *hRatio_Electrons, *hRatio_Pions;

  f->GetObject("hRatio_Muons", hRatio_Muons);
  f->GetObject("hRatio_Electrons", hRatio_Electrons);
  f->GetObject("hRatio_Pions", hRatio_Pions);

  hRatio_Muons->Scale(1./hRatio_Muons->Integral());
  hRatio_Muons->SetLineColor(kBlue);
  hRatio_Muons->SetLineWidth(2);
  hRatio_Muons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Muons->GetYaxis()->SetTitle("# Events");

  hRatio_Electrons->Scale(1./hRatio_Electrons->Integral());
  hRatio_Electrons->SetLineColor(kGreen);
  hRatio_Electrons->SetLineWidth(2);
  hRatio_Electrons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Electrons->GetYaxis()->SetTitle("# Events");
  hRatio_Electrons->GetYaxis()->SetRangeUser(0.00001, 2);

  hRatio_Pions->Scale(1./hRatio_Pions->Integral());
  hRatio_Pions->SetLineColor(kRed);
  hRatio_Pions->SetLineWidth(2);

  TLine *line7 = new TLine();
  line7->SetX1(1.);
  line7->SetX2(1.);
  line7->SetY1(0.);
  line7->SetY2(2.);
  line7->SetLineColor(kBlack);
  line7->SetLineWidth(3);

  TCanvas *c3 = new TCanvas("c3", "Energy in last two layers", 800, 600);
  gPad->SetLogy();
  hRatio_Electrons->Draw("hist");
  hRatio_Muons->Draw("hist same");
  hRatio_Pions->Draw("hist same");
  leg->Draw("same");
  line7->Draw("same");

  c3->SaveAs("Plots/SelectionCut_EnergyLastLayers_50GeV.pdf");

  //******************************************************//

  TH1F *hEnergyE3_Muons, *hEnergyE3_Electrons, *hEnergyE3_Pions;

  f->GetObject("hEnergyE3_Muons", hEnergyE3_Muons);
  f->GetObject("hEnergyE3_Electrons", hEnergyE3_Electrons);
  f->GetObject("hEnergyE3_Pions", hEnergyE3_Pions);

  hEnergyE3_Muons->Scale(1./hEnergyE3_Muons->Integral());
  hEnergyE3_Muons->SetLineColor(kBlue);
  hEnergyE3_Muons->SetLineWidth(2);
  hEnergyE3_Muons->GetXaxis()->SetTitle("(E_{3}+E_{4}+E_{5}) [MIP]");
  hEnergyE3_Muons->GetYaxis()->SetTitle("# Events");
  hEnergyE3_Muons->GetYaxis()->SetRangeUser(0.00001, 2);

  hEnergyE3_Electrons->Scale(1./hEnergyE3_Electrons->Integral());
  hEnergyE3_Electrons->SetLineColor(kGreen);
  hEnergyE3_Electrons->SetLineWidth(2);
  hEnergyE3_Electrons->GetXaxis()->SetTitle("(E_{3}+E_{4}+E_{5}) [MIP]");
  hEnergyE3_Electrons->GetYaxis()->SetTitle("# Events");
  hEnergyE3_Electrons->GetYaxis()->SetRangeUser(0.00001, 2);

  hEnergyE3_Pions->Scale(1./hEnergyE3_Pions->Integral());
  hEnergyE3_Pions->SetLineColor(kRed);
  hEnergyE3_Pions->SetLineWidth(2);

  TLine *line20 = new TLine();
  line20->SetX1(10);
  line20->SetX2(10);
  line20->SetY1(0.);
  line20->SetY2(2.);
  line20->SetLineColor(kBlack);
  line20->SetLineWidth(3);

  TCanvas *c4 = new TCanvas("c4", "Energy in 3 first AHCAL layers", 800, 600);
  gPad->SetLogy();
  hEnergyE3_Muons->Draw("hist");
  hEnergyE3_Electrons->Draw("hist same");
  hEnergyE3_Pions->Draw("hist same");
  leg->Draw("same");
  line20->Draw("same");

  c4->SaveAs("Plots/SelectionCut_EnergyE3_50GeV.pdf");
}

void Systematics_10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Timing_FullAHCAL_TopLeftTile_10GeV.root", "OPEN");
  TH1F *hTopLeftTile;

  f->GetObject("Timing_AHCAL_Electron", hTopLeftTile);

  hTopLeftTile->Sumw2();
  hTopLeftTile->GetXaxis()->SetRangeUser(-30, 30);
  hTopLeftTile->GetXaxis()->SetTitle("Time of first hit [ns]");
  hTopLeftTile->SetLineColor(kOrange+1);
  hTopLeftTile->SetLineWidth(2);
  hTopLeftTile->GetYaxis()->SetTitleOffset(1.4);
  hTopLeftTile->GetYaxis()->SetTitle("Fraction of hits");
  hTopLeftTile->Scale(1./hTopLeftTile->Integral("width"));

  TFile *f2 = new TFile("Rootfiles/Timing_FullAHCAL_TopRightTile_10GeV.root", "OPEN");
  TH1F *hTopRightTile;

  f2->GetObject("Timing_AHCAL_Electron", hTopRightTile);

  hTopRightTile->Sumw2();
  hTopRightTile->Scale(1./hTopRightTile->Integral("width"));
  hTopRightTile->SetLineColor(kRed);
  hTopRightTile->SetLineWidth(2);

  TFile *f3 = new TFile("Rootfiles/Timing_FullAHCAL_BottomLeftTile_10GeV.root", "OPEN");
  TH1F *hBottomLeftTile;

  f3->GetObject("Timing_AHCAL_Electron", hBottomLeftTile);

  hBottomLeftTile->Sumw2();
  hBottomLeftTile->Scale(1./hBottomLeftTile->Integral("width"));
  hBottomLeftTile->SetLineColor(kBlue);
  hBottomLeftTile->SetLineWidth(2);

  TFile *f4 = new TFile("Rootfiles/Timing_FullAHCAL_BottomRightTile_10GeV.root", "OPEN");
  TH1F *hBottomRightTile;

  f4->GetObject("Timing_AHCAL_Electron", hBottomRightTile);

  hBottomRightTile->Sumw2();
  hBottomRightTile->Scale(1./hBottomRightTile->Integral("width"));
  hBottomRightTile->SetLineColor(kGreen);
  hBottomRightTile->SetLineWidth(2);

  TH1F *hRatioTopLeft = (TH1F*)hTopLeftTile->Clone("hRatioTopLeft");
  hRatioTopLeft->Divide(hTopLeftTile);
  hRatioTopLeft->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioTopLeft->GetYaxis()->CenterTitle();
  hRatioTopLeft->GetYaxis()->SetTitle("Diff");
  hRatioTopLeft->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioTopRight = (TH1F*)hTopRightTile->Clone("hRatioTopRight");
  hRatioTopRight->Divide(hTopLeftTile);
  hRatioTopRight->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioTopRight->GetYaxis()->CenterTitle();
  hRatioTopRight->GetYaxis()->SetTitle("Diff");
  hRatioTopRight->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioBottomLeft = (TH1F*)hBottomLeftTile->Clone("hRatioBottomLeft");
  hRatioBottomLeft->Divide(hTopLeftTile);
  hRatioBottomLeft->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioBottomLeft->GetYaxis()->CenterTitle();
  hRatioBottomLeft->GetYaxis()->SetTitle("Diff");
  hRatioBottomLeft->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioBottomRight = (TH1F*)hBottomRightTile->Clone("hRatioBottomRight");
  hRatioBottomRight->Divide(hTopLeftTile);
  hRatioBottomRight->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioBottomRight->GetYaxis()->CenterTitle();
  hRatioBottomRight->GetYaxis()->SetTitle("Diff");
  hRatioBottomRight->GetYaxis()->SetNdivisions(505);

  // TCanvas *c1 = new TCanvas("c1", "Superposition", 800, 600);
  // hTopLeftTile->Draw("hist");
  // hTopRightTile->Draw("same hist");
  // hBottomLeftTile->Draw("same hist");
  // hBottomRightTile->Draw("same hist");
  // //hData->Draw("same hist");
  //
  // TCanvas *c2 = new TCanvas("c2", "Superposition Ratio", 800, 600);
  // hRatioTopLeft->Draw("hist");
  // hRatioTopRight->Draw("same hist");
  // hRatioBottomLeft->Draw("same hist");
  // hRatioBottomRight->Draw("same hist");

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("10 GeV e-");
  leg3->AddEntry(hTopLeftTile, "Top Left Tile", "l");
  leg3->AddEntry(hTopRightTile, "Top Right Tile", "l");
  leg3->AddEntry(hBottomLeftTile, "Bottom Left Tile", "l");
  leg3->AddEntry(hBottomRightTile, "Bottom Right Tile", "l");

  TPaveText *pt = new TPaveText(0.2, 0.63, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("Systematic study");

  TLine *line = new TLine();
  line->SetLineWidth(2);
  line->SetLineStyle(2);
  line->SetX1(-30);
  line->SetX2(30);
  line->SetY1(0.9);
  line->SetY2(0.9);

  TLine *line2 = new TLine();
  line2->SetLineWidth(2);
  line2->SetLineStyle(2);
  line2->SetX1(-30);
  line2->SetX2(30);
  line2->SetY1(1.1);
  line2->SetY2(1.1);

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTopLeftTile, sFactor);
  setupAxisScalingBottom(hRatioTopLeft, sFactor);
  pad1->cd();
  hTopLeftTile->Draw("hist");
  hTopRightTile->Draw("same hist");
  hBottomLeftTile->Draw("same hist");
  hBottomRightTile->Draw("same hist");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioTopLeft->Draw("hist");
  hRatioTopLeft->GetYaxis()->SetRangeUser(0.8, 1.2);
  hRatioTopRight->Draw("same hist");
  hRatioBottomLeft->Draw("same hist");
  hRatioBottomRight->Draw("same hist");
  line->Draw("same");
  line2->Draw("same");

  c->SaveAs("Plots/Systematic_Inhomogeneity_10GeV.pdf");
}

void Systematics_50GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Timing_FullAHCAL_TopLeftTile_50GeV.root", "OPEN");
  TH1F *hTopLeftTile;

  f->GetObject("Timing_AHCAL_Electron", hTopLeftTile);

  hTopLeftTile->Sumw2();
  hTopLeftTile->GetXaxis()->SetRangeUser(-30, 30);
  hTopLeftTile->GetXaxis()->SetTitle("Time of first hit [ns]");
  hTopLeftTile->SetLineColor(kOrange+1);
  hTopLeftTile->SetLineWidth(2);
  hTopLeftTile->GetYaxis()->SetTitleOffset(1.4);
  hTopLeftTile->GetYaxis()->SetTitle("Fraction of hits");
  hTopLeftTile->Scale(1./hTopLeftTile->Integral("width"));

  TFile *f2 = new TFile("Rootfiles/Timing_FullAHCAL_TopRightTile_50GeV.root", "OPEN");
  TH1F *hTopRightTile;

  f2->GetObject("Timing_AHCAL_Electron", hTopRightTile);

  hTopRightTile->Sumw2();
  hTopRightTile->Scale(1./hTopRightTile->Integral("width"));
  hTopRightTile->SetLineColor(kRed);
  hTopRightTile->SetLineWidth(2);

  TFile *f3 = new TFile("Rootfiles/Timing_FullAHCAL_BottomLeftTile_50GeV.root", "OPEN");
  TH1F *hBottomLeftTile;

  f3->GetObject("Timing_AHCAL_Electron", hBottomLeftTile);

  hBottomLeftTile->Sumw2();
  hBottomLeftTile->Scale(1./hBottomLeftTile->Integral("width"));
  hBottomLeftTile->SetLineColor(kBlue);
  hBottomLeftTile->SetLineWidth(2);

  TFile *f4 = new TFile("Rootfiles/Timing_FullAHCAL_BottomRightTile_50GeV.root", "OPEN");
  TH1F *hBottomRightTile;

  f4->GetObject("Timing_AHCAL_Electron", hBottomRightTile);

  hBottomRightTile->Sumw2();
  hBottomRightTile->Scale(1./hBottomRightTile->Integral("width"));
  hBottomRightTile->SetLineColor(kGreen);
  hBottomRightTile->SetLineWidth(2);

  TH1F *hRatioTopLeft = (TH1F*)hTopLeftTile->Clone("hRatioTopLeft");
  hRatioTopLeft->Divide(hTopLeftTile);
  hRatioTopLeft->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioTopLeft->GetYaxis()->CenterTitle();
  hRatioTopLeft->GetYaxis()->SetTitle("Diff");
  hRatioTopLeft->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioTopRight = (TH1F*)hTopRightTile->Clone("hRatioTopRight");
  hRatioTopRight->Divide(hTopLeftTile);
  hRatioTopRight->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioTopRight->GetYaxis()->CenterTitle();
  hRatioTopRight->GetYaxis()->SetTitle("Diff");
  hRatioTopRight->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioBottomLeft = (TH1F*)hBottomLeftTile->Clone("hRatioBottomLeft");
  hRatioBottomLeft->Divide(hTopLeftTile);
  hRatioBottomLeft->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioBottomLeft->GetYaxis()->CenterTitle();
  hRatioBottomLeft->GetYaxis()->SetTitle("Diff");
  hRatioBottomLeft->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioBottomRight = (TH1F*)hBottomRightTile->Clone("hRatioBottomRight");
  hRatioBottomRight->Divide(hTopLeftTile);
  hRatioBottomRight->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioBottomRight->GetYaxis()->CenterTitle();
  hRatioBottomRight->GetYaxis()->SetTitle("Diff");
  hRatioBottomRight->GetYaxis()->SetNdivisions(505);

  // TCanvas *c1 = new TCanvas("c1", "Superposition", 800, 600);
  // hTopLeftTile->Draw("hist");
  // hTopRightTile->Draw("same hist");
  // hBottomLeftTile->Draw("same hist");
  // hBottomRightTile->Draw("same hist");
  // //hData->Draw("same hist");
  //
  // TCanvas *c2 = new TCanvas("c2", "Superposition Ratio", 800, 600);
  // hRatioTopLeft->Draw("hist");
  // hRatioTopRight->Draw("same hist");
  // hRatioBottomLeft->Draw("same hist");
  // hRatioBottomRight->Draw("same hist");

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("50 GeV e-");
  leg3->AddEntry(hTopLeftTile, "Top Left Tile", "l");
  leg3->AddEntry(hTopRightTile, "Top Right Tile", "l");
  leg3->AddEntry(hBottomLeftTile, "Bottom Left Tile", "l");
  leg3->AddEntry(hBottomRightTile, "Bottom Right Tile", "l");

  TPaveText *pt = new TPaveText(0.2, 0.63, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("Systematic study");

  TLine *line = new TLine();
  line->SetLineWidth(2);
  line->SetLineStyle(2);
  line->SetX1(-30);
  line->SetX2(30);
  line->SetY1(0.9);
  line->SetY2(0.9);

  TLine *line2 = new TLine();
  line2->SetLineWidth(2);
  line2->SetLineStyle(2);
  line2->SetX1(-30);
  line2->SetX2(30);
  line2->SetY1(1.1);
  line2->SetY2(1.1);

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTopLeftTile, sFactor);
  setupAxisScalingBottom(hRatioTopLeft, sFactor);
  pad1->cd();
  hTopLeftTile->Draw("hist");
  hTopRightTile->Draw("same hist");
  hBottomLeftTile->Draw("same hist");
  hBottomRightTile->Draw("same hist");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioTopLeft->Draw("hist");
  hRatioTopLeft->GetYaxis()->SetRangeUser(0.8, 1.2);
  hRatioTopRight->Draw("same hist");
  hRatioBottomLeft->Draw("same hist");
  hRatioBottomRight->Draw("same hist");
  line->Draw("same");
  line2->Draw("same");

  c->SaveAs("Plots/Systematic_Inhomogeneity_50GeV.pdf");
}

void ComparisonSimData_nHits10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/NumberHits_10GeV.root", "OPEN");
  TH1F *hHitSim, *hHitSim_Xtalk10, *hHitSim_Xtalk18;

  f->GetObject("hHitSim", hHitSim);
  f->GetObject("hHitSim_Xtalk10", hHitSim_Xtalk10);
  f->GetObject("hHitSim_Xtalk18", hHitSim_Xtalk18);

  hHitSim->Sumw2();
  hHitSim->Scale(1./hHitSim->Integral("width"));

  hHitSim->SetLineColor(kRed);
  hHitSim->SetLineWidth(2);

  hHitSim_Xtalk10->Sumw2();
  hHitSim_Xtalk10->Scale(1./hHitSim_Xtalk10->Integral("width"));

  hHitSim_Xtalk10->SetLineColor(kGreen);
  hHitSim_Xtalk10->SetLineWidth(2);

  hHitSim_Xtalk18->Sumw2();
  hHitSim_Xtalk18->Scale(1./hHitSim_Xtalk18->Integral("width"));

  hHitSim_Xtalk18->SetLineColor(kMagenta);
  hHitSim_Xtalk18->SetLineWidth(2);

  //-------------------------------------------

  TH1F *hHitData;
  f->GetObject("hHitData", hHitData);

  hHitData->Sumw2();
  hHitData->Scale(1./hHitData->Integral("width"));

  hHitData->SetMarkerStyle(20);
  hHitData->SetMarkerColor(kBlack);

  hHitData->GetYaxis()->SetTitle("normalised entries");

  //--------------------------------------------

  TH1F* hHitSim_DD4hep, *hHitSim_DD4hep_Xtalk10, *hHitSim_DD4hep_Xtalk18;
  f->GetObject("hHitSim_DD4hep", hHitSim_DD4hep);
  f->GetObject("hHitSim_DD4hep_Xtalk10", hHitSim_DD4hep_Xtalk10);
  f->GetObject("hHitSim_DD4hep_Xtalk18", hHitSim_DD4hep_Xtalk18);

  hHitSim_DD4hep->Sumw2();
  hHitSim_DD4hep->Scale(1./hHitSim_DD4hep->Integral("width"));

  hHitSim_DD4hep->SetLineColor(kBlue);
  hHitSim_DD4hep->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk10->Sumw2();
  hHitSim_DD4hep_Xtalk10->Scale(1./hHitSim_DD4hep_Xtalk10->Integral("width"));

  hHitSim_DD4hep_Xtalk10->SetLineColor(kGreen);
  hHitSim_DD4hep_Xtalk10->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk18->Sumw2();
  hHitSim_DD4hep_Xtalk18->Scale(1./hHitSim_DD4hep_Xtalk18->Integral("width"));

  hHitSim_DD4hep_Xtalk18->SetLineColor(kMagenta);
  hHitSim_DD4hep_Xtalk18->SetLineWidth(2);

  //--------------------------------------------

  //Error handling (Xtalk)

  TGraphAsymmErrors *gHitSim = new TGraphAsymmErrors();
  gHitSim->SetLineColor(kRed);
  gHitSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim->GetBinError(ibin);

    gHitSim->SetPoint(ibin, hHitSim->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }


  TGraphAsymmErrors *gHitSim_DD4hep = new TGraphAsymmErrors();
  gHitSim_DD4hep->SetLineColor(kBlue);
  gHitSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim_DD4hep->GetBinError(ibin);

    gHitSim_DD4hep->SetPoint(ibin, hHitSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitData = new TGraphAsymmErrors();
  gHitData->SetLineWidth(0);
  gHitData->SetFillColor(kGray);
  gHitData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitData->GetBinContent(ibin);
    double error_stat = hHitData->GetBinError(ibin);

    gHitData->SetPoint(ibin, hHitData->GetXaxis()->GetBinCenter(ibin), content);
    gHitData->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //------------------------------------ Ratio ------------------------------------

  TH1F* hRatio = (TH1F*)hHitSim->Clone("hRatio");
  hRatio->Divide(hHitData);
  hRatio->GetYaxis()->SetTitle("MC/Data");
  hRatio->GetYaxis()->CenterTitle();

  TH1F* hRatio_Xtalk10 = (TH1F*)hHitSim_Xtalk10->Clone("hRatio_Xtalk10");
  hRatio_Xtalk10->Divide(hHitData);
  hRatio_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_Xtalk18 = (TH1F*)hHitSim_Xtalk18->Clone("hRatio_Xtalk18");
  hRatio_Xtalk18->Divide(hHitData);
  hRatio_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep = (TH1F*)hHitSim_DD4hep->Clone("hRatio_DD4hep");
  hRatio_DD4hep->Divide(hHitData);
  hRatio_DD4hep->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk10 = (TH1F*)hHitSim_DD4hep_Xtalk10->Clone("hRatio_DD4hep_Xtalk10");
  hRatio_DD4hep_Xtalk10->Divide(hHitData);
  hRatio_DD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk18 = (TH1F*)hHitSim_DD4hep_Xtalk18->Clone("hRatio_DD4hep_Xtalk18");
  hRatio_DD4hep_Xtalk18->Divide(hHitData);
  hRatio_DD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatioData = (TH1F*)hHitData->Clone("hRatioData");
  hRatioData->Divide(hHitData);

  //------ Error handling ----------------------------

  TGraphAsymmErrors *gHitSimRatio = new TGraphAsymmErrors();
  gHitSimRatio->SetLineColor(kRed);
  gHitSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio->GetBinError(ibin);

    gHitSimRatio->SetPoint(ibin, hRatio->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitSimRatio_DD4hep = new TGraphAsymmErrors();
  gHitSimRatio_DD4hep->SetLineColor(kBlue);
  gHitSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio_DD4hep->GetBinError(ibin);

    gHitSimRatio_DD4hep->SetPoint(ibin, hRatio_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitDataRatio = new TGraphAsymmErrors();
  gHitDataRatio->SetLineColor(kBlack);
  gHitDataRatio->SetLineWidth(2);
  gHitDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    gHitDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gHitDataRatio->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //--------------------------------------------------

  TLegend* leg = new TLegend(0.65, 0.35, 0.85, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader("10 GeV e-");
  leg->AddEntry(gHitData, "Data", "pf");
  leg->AddEntry(gHitSim, "Mokka (QGSP_BERT_HP)", "l");
  leg->AddEntry(gHitSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.65, 0.70, 0.85, 0.85, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.6;

  TCanvas *c1;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c1, "c1", "c1", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hHitData, sFactor);
  setupAxisScalingBottom(hRatio, sFactor);
  pad1->cd();
  pad1->SetLogy();
  hHitData->GetXaxis()->SetRangeUser(1, 20);
  hHitData->Draw("p hist");
  gHitData->Draw("E2");
  gHitSim->Draw("PE");
  gHitSim_DD4hep->Draw("PE");
  hHitData->Draw("p hist same");
  pt->Draw("same");
  leg->Draw("same");
  pad2->cd();
  hRatio->GetYaxis()->SetRangeUser(0, 1.5);
  hRatio->GetXaxis()->SetRangeUser(1, 20);
  hRatio->Draw("p hist");
  gHitDataRatio->Draw("E2");
  gHitSimRatio->Draw("PE");
  gHitSimRatio_DD4hep->Draw("PE");
  hRatioData->Draw("p hist same");

  c1->SaveAs("Plots/Comparison_SimData_Electrons_nHits_10GeV.pdf");
}

void ComparisonSimData_Timing10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMokka_10GeV.root", "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(1, hTimeSim->GetNbinsX(), "width"));
  hTimeSim->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(1, hTimeSim_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(1, hTimeSim_ErrorUp->GetNbinsX(), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(1, hTimeSim_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(1, hTimeSim_Xtalk18->GetNbinsX(), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("normalised entries");

  //-------------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/10GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Electron", hData);

  hData->Sumw2();
  hData->Scale(1./hData->Integral(1, hData->GetNbinsX(), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  //hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //-------------------------------------------------

  //Ratio Plots
  TH1F* hRatioData = (TH1F*)hData->Clone("hRatioData");
  hRatioData->Divide(hData);
  hRatioData->GetYaxis()->SetTitle("MC/Data");
  hRatioData->SetMarkerStyle(20);
  hRatioData->SetMarkerColor(kBlack);

  TGraphAsymmErrors *gTimeDataRatio = new TGraphAsymmErrors();
  gTimeDataRatio->SetLineColor(kBlack);
  gTimeDataRatio->SetLineWidth(2);
  gTimeDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
  hRatioMokka->Divide(hData);
  hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka->GetYaxis()->CenterTitle();
  hRatioMokka->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorLow = (TH1F*)hTimeSim_ErrorLow->Clone("hRatioMokka_ErrorLow");
  hRatioMokka_ErrorLow->Divide(hData);
  hRatioMokka_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorLow->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorUp = (TH1F*)hTimeSim_ErrorUp->Clone("hRatioMokka_ErrorUp");
  hRatioMokka_ErrorUp->Divide(hData);
  hRatioMokka_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorUp->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk10 = (TH1F*)hTimeSim_Xtalk10->Clone("hRatioMokka_Xtalk10");
  hRatioMokka_Xtalk10->Divide(hData);
  hRatioMokka_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk10->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk18 = (TH1F*)hTimeSim_Xtalk18->Clone("hRatioMokka_Xtalk18");
  hRatioMokka_Xtalk18->Divide(hData);
  hRatioMokka_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk18->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
  gTimeSimRatio->SetLineColor(kRed);
  gTimeSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
  {
    double content = hRatioMokka->GetBinContent(ibin);
    double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioMokka_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioMokka_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioMokka->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //***************************************************************//
  //*
  //*
  //*
  //------------------- DD4hep -----------------------------

  TFile *f3 = new TFile("Rootfiles/TimingDD4hep_10GeV.root", "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F *hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kBlue);
  hTimeSim_DD4hep->SetMarkerColor(kBlue);
  hTimeSim_DD4hep->SetLineWidth(2);
  hTimeSim_DD4hep->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(1, hTimeSim_DD4hep->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(1, hTimeSim_DD4hep_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(1, hTimeSim_DD4hep_ErrorUp->GetNbinsX(), "width"));

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(1, hTimeSim_DD4hep_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(1, hTimeSim_DD4hep_Xtalk18->GetNbinsX(), "width"));

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kBlue);
  gTimeSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //----------------------------------------------

  TH1F *hRatioDD4hep = (TH1F*)hTimeSim_DD4hep->Clone("hRatioDD4hep");
  hRatioDD4hep->Divide(hData);
  hRatioDD4hep->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep->GetYaxis()->CenterTitle();
  hRatioDD4hep->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorLow = (TH1F*)hTimeSim_DD4hep_ErrorLow->Clone("hRatioDD4hep_ErrorLow");
  hRatioDD4hep_ErrorLow->Divide(hData);
  hRatioDD4hep_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorLow->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorLow->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorUp = (TH1F*)hTimeSim_DD4hep_ErrorUp->Clone("hRatioDD4hep_ErrorUp");
  hRatioDD4hep_ErrorUp->Divide(hData);
  hRatioDD4hep_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorUp->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorUp->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk10 = (TH1F*)hTimeSim_DD4hep_Xtalk10->Clone("hRatioDD4hep_Xtalk10");
  hRatioDD4hep_Xtalk10->Divide(hData);
  hRatioDD4hep_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk10->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk10->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk18 = (TH1F*)hTimeSim_DD4hep_Xtalk18->Clone("hRatioDD4hep_Xtalk18");
  hRatioDD4hep_Xtalk18->Divide(hData);
  hRatioDD4hep_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk18->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk18->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
  gTimeSimRatio_DD4hep->SetLineColor(kBlue);
  gTimeSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
  {
    double content = hRatioDD4hep->GetBinContent(ibin);
    double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioDD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioDD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioDD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //------------------------------------------------------------

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("10 GeV e-");
  leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
  leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT_HP)", "l");
  leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTimeSim, sFactor);
  setupAxisScalingBottom(hRatioMokka, sFactor);
  pad1->cd();
  hTimeSim->GetXaxis()->SetRangeUser(-30,30);
  hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.090);
  hTimeSim->Draw("p hist");
  gTimeData->Draw("E2");
  gTimeSim->Draw("PE");
  gTimeSim_DD4hep->Draw("PE");
  hData->GetXaxis()->SetRangeUser(-30,30);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioMokka->GetXaxis()->SetRangeUser(-30,30);
  hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatioMokka->Draw("p");
  gTimeDataRatio->Draw("E2");
  gTimeSimRatio->Draw("PE");
  gTimeSimRatio_DD4hep->Draw("PE");
  hRatioData->GetXaxis()->SetRangeUser(-30,30);
  hRatioData->Draw("p hist same");

  c->SaveAs("Plots/Comparison_SimData_Electrons10GeV.pdf");
}

void ComparisonSimData_nHits15GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/NumberHits_15GeV.root", "OPEN");
  TH1F *hHitSim, *hHitSim_Xtalk10, *hHitSim_Xtalk18;

  f->GetObject("hHitSim", hHitSim);
  f->GetObject("hHitSim_Xtalk10", hHitSim_Xtalk10);
  f->GetObject("hHitSim_Xtalk18", hHitSim_Xtalk18);

  hHitSim->Sumw2();
  hHitSim->Scale(1./hHitSim->Integral("width"));

  hHitSim->SetLineColor(kRed);
  hHitSim->SetLineWidth(2);

  hHitSim_Xtalk10->Sumw2();
  hHitSim_Xtalk10->Scale(1./hHitSim_Xtalk10->Integral("width"));

  hHitSim_Xtalk10->SetLineColor(kGreen);
  hHitSim_Xtalk10->SetLineWidth(2);

  hHitSim_Xtalk18->Sumw2();
  hHitSim_Xtalk18->Scale(1./hHitSim_Xtalk18->Integral("width"));

  hHitSim_Xtalk18->SetLineColor(kMagenta);
  hHitSim_Xtalk18->SetLineWidth(2);

  //-------------------------------------------

  TH1F *hHitData;
  f->GetObject("hHitData", hHitData);

  hHitData->Sumw2();
  hHitData->Scale(1./hHitData->Integral("width"));

  hHitData->SetMarkerStyle(20);
  hHitData->SetMarkerColor(kBlack);

  hHitData->GetYaxis()->SetTitle("normalised entries");

  //--------------------------------------------

  TH1F* hHitSim_DD4hep, *hHitSim_DD4hep_Xtalk10, *hHitSim_DD4hep_Xtalk18;
  f->GetObject("hHitSim_DD4hep", hHitSim_DD4hep);
  f->GetObject("hHitSim_DD4hep_Xtalk10", hHitSim_DD4hep_Xtalk10);
  f->GetObject("hHitSim_DD4hep_Xtalk18", hHitSim_DD4hep_Xtalk18);

  hHitSim_DD4hep->Sumw2();
  hHitSim_DD4hep->Scale(1./hHitSim_DD4hep->Integral("width"));

  hHitSim_DD4hep->SetLineColor(kBlue);
  hHitSim_DD4hep->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk10->Sumw2();
  hHitSim_DD4hep_Xtalk10->Scale(1./hHitSim_DD4hep_Xtalk10->Integral("width"));

  hHitSim_DD4hep_Xtalk10->SetLineColor(kGreen);
  hHitSim_DD4hep_Xtalk10->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk18->Sumw2();
  hHitSim_DD4hep_Xtalk18->Scale(1./hHitSim_DD4hep_Xtalk18->Integral("width"));

  hHitSim_DD4hep_Xtalk18->SetLineColor(kMagenta);
  hHitSim_DD4hep_Xtalk18->SetLineWidth(2);

  //--------------------------------------------

  //Error handling (Xtalk)

  TGraphAsymmErrors *gHitSim = new TGraphAsymmErrors();
  gHitSim->SetLineColor(kRed);
  gHitSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim->GetBinError(ibin);

    gHitSim->SetPoint(ibin, hHitSim->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }


  TGraphAsymmErrors *gHitSim_DD4hep = new TGraphAsymmErrors();
  gHitSim_DD4hep->SetLineColor(kBlue);
  gHitSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim_DD4hep->GetBinError(ibin);

    gHitSim_DD4hep->SetPoint(ibin, hHitSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitData = new TGraphAsymmErrors();
  gHitData->SetLineWidth(0);
  gHitData->SetFillColor(kGray);
  gHitData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitData->GetBinContent(ibin);
    double error_stat = hHitData->GetBinError(ibin);

    gHitData->SetPoint(ibin, hHitData->GetXaxis()->GetBinCenter(ibin), content);
    gHitData->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //------------------------------------ Ratio ------------------------------------

  TH1F* hRatio = (TH1F*)hHitSim->Clone("hRatio");
  hRatio->Divide(hHitData);
  hRatio->GetYaxis()->SetTitle("MC/Data");
  hRatio->GetYaxis()->CenterTitle();

  TH1F* hRatio_Xtalk10 = (TH1F*)hHitSim_Xtalk10->Clone("hRatio_Xtalk10");
  hRatio_Xtalk10->Divide(hHitData);
  hRatio_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_Xtalk18 = (TH1F*)hHitSim_Xtalk18->Clone("hRatio_Xtalk18");
  hRatio_Xtalk18->Divide(hHitData);
  hRatio_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep = (TH1F*)hHitSim_DD4hep->Clone("hRatio_DD4hep");
  hRatio_DD4hep->Divide(hHitData);
  hRatio_DD4hep->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk10 = (TH1F*)hHitSim_DD4hep_Xtalk10->Clone("hRatio_DD4hep_Xtalk10");
  hRatio_DD4hep_Xtalk10->Divide(hHitData);
  hRatio_DD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk18 = (TH1F*)hHitSim_DD4hep_Xtalk18->Clone("hRatio_DD4hep_Xtalk18");
  hRatio_DD4hep_Xtalk18->Divide(hHitData);
  hRatio_DD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatioData = (TH1F*)hHitData->Clone("hRatioData");
  hRatioData->Divide(hHitData);

  //------ Error handling ----------------------------

  TGraphAsymmErrors *gHitSimRatio = new TGraphAsymmErrors();
  gHitSimRatio->SetLineColor(kRed);
  gHitSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio->GetBinError(ibin);

    gHitSimRatio->SetPoint(ibin, hRatio->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitSimRatio_DD4hep = new TGraphAsymmErrors();
  gHitSimRatio_DD4hep->SetLineColor(kBlue);
  gHitSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio_DD4hep->GetBinError(ibin);

    gHitSimRatio_DD4hep->SetPoint(ibin, hRatio_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitDataRatio = new TGraphAsymmErrors();
  gHitDataRatio->SetLineColor(kBlack);
  gHitDataRatio->SetLineWidth(2);
  gHitDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    gHitDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gHitDataRatio->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //--------------------------------------------------

  TLegend* leg = new TLegend(0.65, 0.35, 0.85, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader("15 GeV e-");
  leg->AddEntry(gHitData, "Data", "pf");
  leg->AddEntry(gHitSim, "Mokka (QGSP_BERT_HP)", "l");
  leg->AddEntry(gHitSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.65, 0.70, 0.85, 0.85, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.6;

  TCanvas *c1;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c1, "c1", "c1", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hHitData, sFactor);
  setupAxisScalingBottom(hRatio, sFactor);
  pad1->cd();
  pad1->SetLogy();
  hHitData->GetXaxis()->SetRangeUser(1, 20);
  hHitData->Draw("p hist");
  gHitData->Draw("E2");
  gHitSim->Draw("PE");
  gHitSim_DD4hep->Draw("PE");
  hHitData->Draw("p hist same");
  pt->Draw("same");
  leg->Draw("same");
  pad2->cd();
  hRatio->GetYaxis()->SetRangeUser(0, 1.5);
  hRatio->GetXaxis()->SetRangeUser(1, 20);
  hRatio->Draw("p hist");
  gHitDataRatio->Draw("E2");
  gHitSimRatio->Draw("PE");
  gHitSimRatio_DD4hep->Draw("PE");
  hRatioData->Draw("p hist same");

  c1->SaveAs("Plots/Comparison_SimData_Electrons_nHits_15GeV.pdf");
}

void ComparisonSimData_Timing15GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMokka_15GeV.root", "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(1, hTimeSim->GetNbinsX(), "width"));
  hTimeSim->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(1, hTimeSim_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(1, hTimeSim_ErrorUp->GetNbinsX(), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(1, hTimeSim_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(1, hTimeSim_Xtalk18->GetNbinsX(), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("normalised entries");

  //-------------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/15GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Electron", hData);

  hData->Sumw2();
  hData->Scale(1./hData->Integral(1, hData->GetNbinsX(), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  //hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //-------------------------------------------------

  //Ratio Plots
  TH1F* hRatioData = (TH1F*)hData->Clone("hRatioData");
  hRatioData->Divide(hData);
  hRatioData->GetYaxis()->SetTitle("MC/Data");
  hRatioData->SetMarkerStyle(20);
  hRatioData->SetMarkerColor(kBlack);

  TGraphAsymmErrors *gTimeDataRatio = new TGraphAsymmErrors();
  gTimeDataRatio->SetLineColor(kBlack);
  gTimeDataRatio->SetLineWidth(2);
  gTimeDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
  hRatioMokka->Divide(hData);
  hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka->GetYaxis()->CenterTitle();
  hRatioMokka->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorLow = (TH1F*)hTimeSim_ErrorLow->Clone("hRatioMokka_ErrorLow");
  hRatioMokka_ErrorLow->Divide(hData);
  hRatioMokka_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorLow->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorUp = (TH1F*)hTimeSim_ErrorUp->Clone("hRatioMokka_ErrorUp");
  hRatioMokka_ErrorUp->Divide(hData);
  hRatioMokka_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorUp->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk10 = (TH1F*)hTimeSim_Xtalk10->Clone("hRatioMokka_Xtalk10");
  hRatioMokka_Xtalk10->Divide(hData);
  hRatioMokka_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk10->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk18 = (TH1F*)hTimeSim_Xtalk18->Clone("hRatioMokka_Xtalk18");
  hRatioMokka_Xtalk18->Divide(hData);
  hRatioMokka_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk18->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
  gTimeSimRatio->SetLineColor(kRed);
  gTimeSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
  {
    double content = hRatioMokka->GetBinContent(ibin);
    double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioMokka_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioMokka_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioMokka->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //***************************************************************//
  //*
  //*
  //*
  //------------------- DD4hep -----------------------------

  TFile *f3 = new TFile("Rootfiles/TimingDD4hep_15GeV.root", "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F *hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kBlue);
  hTimeSim_DD4hep->SetMarkerColor(kBlue);
  hTimeSim_DD4hep->SetLineWidth(2);
  hTimeSim_DD4hep->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(1, hTimeSim_DD4hep->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(1, hTimeSim_DD4hep_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(1, hTimeSim_DD4hep_ErrorUp->GetNbinsX(), "width"));

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(1, hTimeSim_DD4hep_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(1, hTimeSim_DD4hep_Xtalk18->GetNbinsX(), "width"));

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kBlue);
  gTimeSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //----------------------------------------------

  TH1F *hRatioDD4hep = (TH1F*)hTimeSim_DD4hep->Clone("hRatioDD4hep");
  hRatioDD4hep->Divide(hData);
  hRatioDD4hep->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep->GetYaxis()->CenterTitle();
  hRatioDD4hep->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorLow = (TH1F*)hTimeSim_DD4hep_ErrorLow->Clone("hRatioDD4hep_ErrorLow");
  hRatioDD4hep_ErrorLow->Divide(hData);
  hRatioDD4hep_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorLow->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorLow->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorUp = (TH1F*)hTimeSim_DD4hep_ErrorUp->Clone("hRatioDD4hep_ErrorUp");
  hRatioDD4hep_ErrorUp->Divide(hData);
  hRatioDD4hep_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorUp->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorUp->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk10 = (TH1F*)hTimeSim_DD4hep_Xtalk10->Clone("hRatioDD4hep_Xtalk10");
  hRatioDD4hep_Xtalk10->Divide(hData);
  hRatioDD4hep_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk10->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk10->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk18 = (TH1F*)hTimeSim_DD4hep_Xtalk18->Clone("hRatioDD4hep_Xtalk18");
  hRatioDD4hep_Xtalk18->Divide(hData);
  hRatioDD4hep_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk18->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk18->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
  gTimeSimRatio_DD4hep->SetLineColor(kBlue);
  gTimeSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
  {
    double content = hRatioDD4hep->GetBinContent(ibin);
    double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioDD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioDD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioDD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //------------------------------------------------------------

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("15 GeV e-");
  leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
  leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT_HP)", "l");
  leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTimeSim, sFactor);
  setupAxisScalingBottom(hRatioMokka, sFactor);
  pad1->cd();
  hTimeSim->GetXaxis()->SetRangeUser(-30,30);
  hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.090);
  hTimeSim->Draw("p hist");
  gTimeData->Draw("E2");
  gTimeSim->Draw("PE");
  gTimeSim_DD4hep->Draw("PE");
  hData->GetXaxis()->SetRangeUser(-30,30);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioMokka->GetXaxis()->SetRangeUser(-30,30);
  hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatioMokka->Draw("p");
  gTimeDataRatio->Draw("E2");
  gTimeSimRatio->Draw("PE");
  gTimeSimRatio_DD4hep->Draw("PE");
  hRatioData->GetXaxis()->SetRangeUser(-30,30);
  hRatioData->Draw("p hist same");

  c->SaveAs("Plots/Comparison_SimData_Electrons15GeV.pdf");
}

void ComparisonSimData_nHits30GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/NumberHits_30GeV.root", "OPEN");
  TH1F *hHitSim, *hHitSim_Xtalk10, *hHitSim_Xtalk18;

  f->GetObject("hHitSim", hHitSim);
  f->GetObject("hHitSim_Xtalk10", hHitSim_Xtalk10);
  f->GetObject("hHitSim_Xtalk18", hHitSim_Xtalk18);

  hHitSim->Sumw2();
  hHitSim->Scale(1./hHitSim->Integral("width"));

  hHitSim->SetLineColor(kRed);
  hHitSim->SetLineWidth(2);

  hHitSim_Xtalk10->Sumw2();
  hHitSim_Xtalk10->Scale(1./hHitSim_Xtalk10->Integral("width"));

  hHitSim_Xtalk10->SetLineColor(kGreen);
  hHitSim_Xtalk10->SetLineWidth(2);

  hHitSim_Xtalk18->Sumw2();
  hHitSim_Xtalk18->Scale(1./hHitSim_Xtalk18->Integral("width"));

  hHitSim_Xtalk18->SetLineColor(kMagenta);
  hHitSim_Xtalk18->SetLineWidth(2);

  //-------------------------------------------

  TH1F *hHitData;
  f->GetObject("hHitData", hHitData);

  hHitData->Sumw2();
  hHitData->Scale(1./hHitData->Integral("width"));

  hHitData->SetMarkerStyle(20);
  hHitData->SetMarkerColor(kBlack);

  hHitData->GetYaxis()->SetTitle("normalised entries");

  //--------------------------------------------

  TH1F* hHitSim_DD4hep, *hHitSim_DD4hep_Xtalk10, *hHitSim_DD4hep_Xtalk18;
  f->GetObject("hHitSim_DD4hep", hHitSim_DD4hep);
  f->GetObject("hHitSim_DD4hep_Xtalk10", hHitSim_DD4hep_Xtalk10);
  f->GetObject("hHitSim_DD4hep_Xtalk18", hHitSim_DD4hep_Xtalk18);

  hHitSim_DD4hep->Sumw2();
  hHitSim_DD4hep->Scale(1./hHitSim_DD4hep->Integral("width"));

  hHitSim_DD4hep->SetLineColor(kBlue);
  hHitSim_DD4hep->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk10->Sumw2();
  hHitSim_DD4hep_Xtalk10->Scale(1./hHitSim_DD4hep_Xtalk10->Integral("width"));

  hHitSim_DD4hep_Xtalk10->SetLineColor(kGreen);
  hHitSim_DD4hep_Xtalk10->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk18->Sumw2();
  hHitSim_DD4hep_Xtalk18->Scale(1./hHitSim_DD4hep_Xtalk18->Integral("width"));

  hHitSim_DD4hep_Xtalk18->SetLineColor(kMagenta);
  hHitSim_DD4hep_Xtalk18->SetLineWidth(2);

  //--------------------------------------------

  //Error handling (Xtalk)

  TGraphAsymmErrors *gHitSim = new TGraphAsymmErrors();
  gHitSim->SetLineColor(kRed);
  gHitSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim->GetBinError(ibin);

    gHitSim->SetPoint(ibin, hHitSim->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }


  TGraphAsymmErrors *gHitSim_DD4hep = new TGraphAsymmErrors();
  gHitSim_DD4hep->SetLineColor(kBlue);
  gHitSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim_DD4hep->GetBinError(ibin);

    gHitSim_DD4hep->SetPoint(ibin, hHitSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitData = new TGraphAsymmErrors();
  gHitData->SetLineWidth(0);
  gHitData->SetFillColor(kGray);
  gHitData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitData->GetBinContent(ibin);
    double error_stat = hHitData->GetBinError(ibin);

    gHitData->SetPoint(ibin, hHitData->GetXaxis()->GetBinCenter(ibin), content);
    gHitData->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //------------------------------------ Ratio ------------------------------------

  TH1F* hRatio = (TH1F*)hHitSim->Clone("hRatio");
  hRatio->Divide(hHitData);
  hRatio->GetYaxis()->SetTitle("MC/Data");
  hRatio->GetYaxis()->CenterTitle();

  TH1F* hRatio_Xtalk10 = (TH1F*)hHitSim_Xtalk10->Clone("hRatio_Xtalk10");
  hRatio_Xtalk10->Divide(hHitData);
  hRatio_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_Xtalk18 = (TH1F*)hHitSim_Xtalk18->Clone("hRatio_Xtalk18");
  hRatio_Xtalk18->Divide(hHitData);
  hRatio_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep = (TH1F*)hHitSim_DD4hep->Clone("hRatio_DD4hep");
  hRatio_DD4hep->Divide(hHitData);
  hRatio_DD4hep->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk10 = (TH1F*)hHitSim_DD4hep_Xtalk10->Clone("hRatio_DD4hep_Xtalk10");
  hRatio_DD4hep_Xtalk10->Divide(hHitData);
  hRatio_DD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk18 = (TH1F*)hHitSim_DD4hep_Xtalk18->Clone("hRatio_DD4hep_Xtalk18");
  hRatio_DD4hep_Xtalk18->Divide(hHitData);
  hRatio_DD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatioData = (TH1F*)hHitData->Clone("hRatioData");
  hRatioData->Divide(hHitData);

  //------ Error handling ----------------------------

  TGraphAsymmErrors *gHitSimRatio = new TGraphAsymmErrors();
  gHitSimRatio->SetLineColor(kRed);
  gHitSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio->GetBinError(ibin);

    gHitSimRatio->SetPoint(ibin, hRatio->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitSimRatio_DD4hep = new TGraphAsymmErrors();
  gHitSimRatio_DD4hep->SetLineColor(kBlue);
  gHitSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio_DD4hep->GetBinError(ibin);

    gHitSimRatio_DD4hep->SetPoint(ibin, hRatio_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitDataRatio = new TGraphAsymmErrors();
  gHitDataRatio->SetLineColor(kBlack);
  gHitDataRatio->SetLineWidth(2);
  gHitDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    gHitDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gHitDataRatio->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //--------------------------------------------------

  TLegend* leg = new TLegend(0.65, 0.35, 0.85, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader("30 GeV e-");
  leg->AddEntry(gHitData, "Data", "pf");
  leg->AddEntry(gHitSim, "Mokka (QGSP_BERT_HP)", "l");
  leg->AddEntry(gHitSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.65, 0.70, 0.85, 0.85, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.6;

  TCanvas *c1;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c1, "c1", "c1", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hHitData, sFactor);
  setupAxisScalingBottom(hRatio, sFactor);
  pad1->cd();
  pad1->SetLogy();
  hHitData->GetXaxis()->SetRangeUser(1, 20);
  hHitData->Draw("p hist");
  gHitData->Draw("E2");
  gHitSim->Draw("PE");
  gHitSim_DD4hep->Draw("PE");
  hHitData->Draw("p hist same");
  pt->Draw("same");
  leg->Draw("same");
  pad2->cd();
  hRatio->GetYaxis()->SetRangeUser(0, 1.5);
  hRatio->GetXaxis()->SetRangeUser(1, 20);
  hRatio->Draw("p hist");
  gHitDataRatio->Draw("E2");
  gHitSimRatio->Draw("PE");
  gHitSimRatio_DD4hep->Draw("PE");
  hRatioData->Draw("p hist same");

  c1->SaveAs("Plots/Comparison_SimData_Electrons_nHits_30GeV.pdf");
}

void ComparisonSimData_Timing30GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMokka_30GeV.root", "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(1, hTimeSim->GetNbinsX(), "width"));
  hTimeSim->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(1, hTimeSim_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(1, hTimeSim_ErrorUp->GetNbinsX(), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(1, hTimeSim_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(1, hTimeSim_Xtalk18->GetNbinsX(), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("normalised entries");

  //-------------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/30GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Electron", hData);

  hData->Sumw2();
  hData->Scale(1./hData->Integral(1, hData->GetNbinsX(), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  //hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //-------------------------------------------------

  //Ratio Plots
  TH1F* hRatioData = (TH1F*)hData->Clone("hRatioData");
  hRatioData->Divide(hData);
  hRatioData->GetYaxis()->SetTitle("MC/Data");
  hRatioData->SetMarkerStyle(20);
  hRatioData->SetMarkerColor(kBlack);

  TGraphAsymmErrors *gTimeDataRatio = new TGraphAsymmErrors();
  gTimeDataRatio->SetLineColor(kBlack);
  gTimeDataRatio->SetLineWidth(2);
  gTimeDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
  hRatioMokka->Divide(hData);
  hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka->GetYaxis()->CenterTitle();
  hRatioMokka->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorLow = (TH1F*)hTimeSim_ErrorLow->Clone("hRatioMokka_ErrorLow");
  hRatioMokka_ErrorLow->Divide(hData);
  hRatioMokka_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorLow->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorUp = (TH1F*)hTimeSim_ErrorUp->Clone("hRatioMokka_ErrorUp");
  hRatioMokka_ErrorUp->Divide(hData);
  hRatioMokka_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorUp->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk10 = (TH1F*)hTimeSim_Xtalk10->Clone("hRatioMokka_Xtalk10");
  hRatioMokka_Xtalk10->Divide(hData);
  hRatioMokka_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk10->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk18 = (TH1F*)hTimeSim_Xtalk18->Clone("hRatioMokka_Xtalk18");
  hRatioMokka_Xtalk18->Divide(hData);
  hRatioMokka_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk18->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
  gTimeSimRatio->SetLineColor(kRed);
  gTimeSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
  {
    double content = hRatioMokka->GetBinContent(ibin);
    double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioMokka_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioMokka_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioMokka->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //***************************************************************//
  //*
  //*
  //*
  //------------------- DD4hep -----------------------------

  TFile *f3 = new TFile("Rootfiles/TimingDD4hep_30GeV.root", "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F *hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kBlue);
  hTimeSim_DD4hep->SetMarkerColor(kBlue);
  hTimeSim_DD4hep->SetLineWidth(2);
  hTimeSim_DD4hep->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(1, hTimeSim_DD4hep->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(1, hTimeSim_DD4hep_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(1, hTimeSim_DD4hep_ErrorUp->GetNbinsX(), "width"));

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(1, hTimeSim_DD4hep_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(1, hTimeSim_DD4hep_Xtalk18->GetNbinsX(), "width"));

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kBlue);
  gTimeSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //----------------------------------------------

  TH1F *hRatioDD4hep = (TH1F*)hTimeSim_DD4hep->Clone("hRatioDD4hep");
  hRatioDD4hep->Divide(hData);
  hRatioDD4hep->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep->GetYaxis()->CenterTitle();
  hRatioDD4hep->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorLow = (TH1F*)hTimeSim_DD4hep_ErrorLow->Clone("hRatioDD4hep_ErrorLow");
  hRatioDD4hep_ErrorLow->Divide(hData);
  hRatioDD4hep_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorLow->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorLow->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorUp = (TH1F*)hTimeSim_DD4hep_ErrorUp->Clone("hRatioDD4hep_ErrorUp");
  hRatioDD4hep_ErrorUp->Divide(hData);
  hRatioDD4hep_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorUp->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorUp->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk10 = (TH1F*)hTimeSim_DD4hep_Xtalk10->Clone("hRatioDD4hep_Xtalk10");
  hRatioDD4hep_Xtalk10->Divide(hData);
  hRatioDD4hep_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk10->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk10->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk18 = (TH1F*)hTimeSim_DD4hep_Xtalk18->Clone("hRatioDD4hep_Xtalk18");
  hRatioDD4hep_Xtalk18->Divide(hData);
  hRatioDD4hep_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk18->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk18->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
  gTimeSimRatio_DD4hep->SetLineColor(kBlue);
  gTimeSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
  {
    double content = hRatioDD4hep->GetBinContent(ibin);
    double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioDD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioDD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioDD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //------------------------------------------------------------

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("30 GeV e-");
  leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
  leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT_HP)", "l");
  leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTimeSim, sFactor);
  setupAxisScalingBottom(hRatioMokka, sFactor);
  pad1->cd();
  hTimeSim->GetXaxis()->SetRangeUser(-30,30);
  hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.090);
  hTimeSim->Draw("p hist");
  gTimeData->Draw("E2");
  gTimeSim->Draw("PE");
  gTimeSim_DD4hep->Draw("PE");
  hData->GetXaxis()->SetRangeUser(-30,30);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioMokka->GetXaxis()->SetRangeUser(-30,30);
  hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatioMokka->Draw("p");
  gTimeDataRatio->Draw("E2");
  gTimeSimRatio->Draw("PE");
  gTimeSimRatio_DD4hep->Draw("PE");
  hRatioData->GetXaxis()->SetRangeUser(-30,30);
  hRatioData->Draw("p hist same");

  c->SaveAs("Plots/Comparison_SimData_Electrons30GeV.pdf");
}

void ComparisonSimData_nHits40GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/NumberHits_40GeV.root", "OPEN");
  TH1F *hHitSim, *hHitSim_Xtalk10, *hHitSim_Xtalk18;

  f->GetObject("hHitSim", hHitSim);
  f->GetObject("hHitSim_Xtalk10", hHitSim_Xtalk10);
  f->GetObject("hHitSim_Xtalk18", hHitSim_Xtalk18);

  hHitSim->Sumw2();
  hHitSim->Scale(1./hHitSim->Integral("width"));

  hHitSim->SetLineColor(kRed);
  hHitSim->SetLineWidth(2);

  hHitSim_Xtalk10->Sumw2();
  hHitSim_Xtalk10->Scale(1./hHitSim_Xtalk10->Integral("width"));

  hHitSim_Xtalk10->SetLineColor(kGreen);
  hHitSim_Xtalk10->SetLineWidth(2);

  hHitSim_Xtalk18->Sumw2();
  hHitSim_Xtalk18->Scale(1./hHitSim_Xtalk18->Integral("width"));

  hHitSim_Xtalk18->SetLineColor(kMagenta);
  hHitSim_Xtalk18->SetLineWidth(2);

  //-------------------------------------------

  TH1F *hHitData;
  f->GetObject("hHitData", hHitData);

  hHitData->Sumw2();
  hHitData->Scale(1./hHitData->Integral("width"));

  hHitData->SetMarkerStyle(20);
  hHitData->SetMarkerColor(kBlack);

  hHitData->GetYaxis()->SetTitle("normalised entries");

  //--------------------------------------------

  TH1F* hHitSim_DD4hep, *hHitSim_DD4hep_Xtalk10, *hHitSim_DD4hep_Xtalk18;
  f->GetObject("hHitSim_DD4hep", hHitSim_DD4hep);
  f->GetObject("hHitSim_DD4hep_Xtalk10", hHitSim_DD4hep_Xtalk10);
  f->GetObject("hHitSim_DD4hep_Xtalk18", hHitSim_DD4hep_Xtalk18);

  hHitSim_DD4hep->Sumw2();
  hHitSim_DD4hep->Scale(1./hHitSim_DD4hep->Integral("width"));

  hHitSim_DD4hep->SetLineColor(kBlue);
  hHitSim_DD4hep->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk10->Sumw2();
  hHitSim_DD4hep_Xtalk10->Scale(1./hHitSim_DD4hep_Xtalk10->Integral("width"));

  hHitSim_DD4hep_Xtalk10->SetLineColor(kGreen);
  hHitSim_DD4hep_Xtalk10->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk18->Sumw2();
  hHitSim_DD4hep_Xtalk18->Scale(1./hHitSim_DD4hep_Xtalk18->Integral("width"));

  hHitSim_DD4hep_Xtalk18->SetLineColor(kMagenta);
  hHitSim_DD4hep_Xtalk18->SetLineWidth(2);

  //--------------------------------------------

  //Error handling (Xtalk)

  TGraphAsymmErrors *gHitSim = new TGraphAsymmErrors();
  gHitSim->SetLineColor(kRed);
  gHitSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim->GetBinError(ibin);

    gHitSim->SetPoint(ibin, hHitSim->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }


  TGraphAsymmErrors *gHitSim_DD4hep = new TGraphAsymmErrors();
  gHitSim_DD4hep->SetLineColor(kBlue);
  gHitSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim_DD4hep->GetBinError(ibin);

    gHitSim_DD4hep->SetPoint(ibin, hHitSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitData = new TGraphAsymmErrors();
  gHitData->SetLineWidth(0);
  gHitData->SetFillColor(kGray);
  gHitData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitData->GetBinContent(ibin);
    double error_stat = hHitData->GetBinError(ibin);

    gHitData->SetPoint(ibin, hHitData->GetXaxis()->GetBinCenter(ibin), content);
    gHitData->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //------------------------------------ Ratio ------------------------------------

  TH1F* hRatio = (TH1F*)hHitSim->Clone("hRatio");
  hRatio->Divide(hHitData);
  hRatio->GetYaxis()->SetTitle("MC/Data");
  hRatio->GetYaxis()->CenterTitle();

  TH1F* hRatio_Xtalk10 = (TH1F*)hHitSim_Xtalk10->Clone("hRatio_Xtalk10");
  hRatio_Xtalk10->Divide(hHitData);
  hRatio_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_Xtalk18 = (TH1F*)hHitSim_Xtalk18->Clone("hRatio_Xtalk18");
  hRatio_Xtalk18->Divide(hHitData);
  hRatio_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep = (TH1F*)hHitSim_DD4hep->Clone("hRatio_DD4hep");
  hRatio_DD4hep->Divide(hHitData);
  hRatio_DD4hep->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk10 = (TH1F*)hHitSim_DD4hep_Xtalk10->Clone("hRatio_DD4hep_Xtalk10");
  hRatio_DD4hep_Xtalk10->Divide(hHitData);
  hRatio_DD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk18 = (TH1F*)hHitSim_DD4hep_Xtalk18->Clone("hRatio_DD4hep_Xtalk18");
  hRatio_DD4hep_Xtalk18->Divide(hHitData);
  hRatio_DD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatioData = (TH1F*)hHitData->Clone("hRatioData");
  hRatioData->Divide(hHitData);

  //------ Error handling ----------------------------

  TGraphAsymmErrors *gHitSimRatio = new TGraphAsymmErrors();
  gHitSimRatio->SetLineColor(kRed);
  gHitSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio->GetBinError(ibin);

    gHitSimRatio->SetPoint(ibin, hRatio->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitSimRatio_DD4hep = new TGraphAsymmErrors();
  gHitSimRatio_DD4hep->SetLineColor(kBlue);
  gHitSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio_DD4hep->GetBinError(ibin);

    gHitSimRatio_DD4hep->SetPoint(ibin, hRatio_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitDataRatio = new TGraphAsymmErrors();
  gHitDataRatio->SetLineColor(kBlack);
  gHitDataRatio->SetLineWidth(2);
  gHitDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    gHitDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gHitDataRatio->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //--------------------------------------------------

  TLegend* leg = new TLegend(0.65, 0.35, 0.85, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader("40 GeV e-");
  leg->AddEntry(gHitData, "Data", "pf");
  leg->AddEntry(gHitSim, "Mokka (QGSP_BERT_HP)", "l");
  leg->AddEntry(gHitSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.65, 0.70, 0.85, 0.85, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.6;

  TCanvas *c1;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c1, "c1", "c1", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hHitData, sFactor);
  setupAxisScalingBottom(hRatio, sFactor);
  pad1->cd();
  pad1->SetLogy();
  hHitData->GetXaxis()->SetRangeUser(1, 20);
  hHitData->Draw("p hist");
  gHitData->Draw("E2");
  gHitSim->Draw("PE");
  gHitSim_DD4hep->Draw("PE");
  hHitData->Draw("p hist same");
  pt->Draw("same");
  leg->Draw("same");
  pad2->cd();
  hRatio->GetYaxis()->SetRangeUser(0, 1.5);
  hRatio->GetXaxis()->SetRangeUser(1, 20);
  hRatio->Draw("p hist");
  gHitDataRatio->Draw("E2");
  gHitSimRatio->Draw("PE");
  gHitSimRatio_DD4hep->Draw("PE");
  hRatioData->Draw("p hist same");

  c1->SaveAs("Plots/Comparison_SimData_Electrons_nHits_40GeV.pdf");
}

void ComparisonSimData_Timing40GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMokka_40GeV.root", "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(1, hTimeSim->GetNbinsX(), "width"));
  hTimeSim->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(1, hTimeSim_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(1, hTimeSim_ErrorUp->GetNbinsX(), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(1, hTimeSim_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(1, hTimeSim_Xtalk18->GetNbinsX(), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("normalised entries");

  //-------------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/40GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Electron", hData);

  hData->Sumw2();
  hData->Scale(1./hData->Integral(1, hData->GetNbinsX(), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  //hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //-------------------------------------------------

  //Ratio Plots
  TH1F* hRatioData = (TH1F*)hData->Clone("hRatioData");
  hRatioData->Divide(hData);
  hRatioData->GetYaxis()->SetTitle("MC/Data");
  hRatioData->SetMarkerStyle(20);
  hRatioData->SetMarkerColor(kBlack);

  TGraphAsymmErrors *gTimeDataRatio = new TGraphAsymmErrors();
  gTimeDataRatio->SetLineColor(kBlack);
  gTimeDataRatio->SetLineWidth(2);
  gTimeDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
  hRatioMokka->Divide(hData);
  hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka->GetYaxis()->CenterTitle();
  hRatioMokka->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorLow = (TH1F*)hTimeSim_ErrorLow->Clone("hRatioMokka_ErrorLow");
  hRatioMokka_ErrorLow->Divide(hData);
  hRatioMokka_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorLow->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorUp = (TH1F*)hTimeSim_ErrorUp->Clone("hRatioMokka_ErrorUp");
  hRatioMokka_ErrorUp->Divide(hData);
  hRatioMokka_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorUp->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk10 = (TH1F*)hTimeSim_Xtalk10->Clone("hRatioMokka_Xtalk10");
  hRatioMokka_Xtalk10->Divide(hData);
  hRatioMokka_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk10->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk18 = (TH1F*)hTimeSim_Xtalk18->Clone("hRatioMokka_Xtalk18");
  hRatioMokka_Xtalk18->Divide(hData);
  hRatioMokka_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk18->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
  gTimeSimRatio->SetLineColor(kRed);
  gTimeSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
  {
    double content = hRatioMokka->GetBinContent(ibin);
    double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioMokka_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioMokka_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioMokka->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //***************************************************************//
  //*
  //*
  //*
  //------------------- DD4hep -----------------------------

  TFile *f3 = new TFile("Rootfiles/TimingDD4hep_40GeV.root", "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F *hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kBlue);
  hTimeSim_DD4hep->SetMarkerColor(kBlue);
  hTimeSim_DD4hep->SetLineWidth(2);
  hTimeSim_DD4hep->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(1, hTimeSim_DD4hep->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(1, hTimeSim_DD4hep_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(1, hTimeSim_DD4hep_ErrorUp->GetNbinsX(), "width"));

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(1, hTimeSim_DD4hep_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(1, hTimeSim_DD4hep_Xtalk18->GetNbinsX(), "width"));

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kBlue);
  gTimeSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //----------------------------------------------

  TH1F *hRatioDD4hep = (TH1F*)hTimeSim_DD4hep->Clone("hRatioDD4hep");
  hRatioDD4hep->Divide(hData);
  hRatioDD4hep->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep->GetYaxis()->CenterTitle();
  hRatioDD4hep->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorLow = (TH1F*)hTimeSim_DD4hep_ErrorLow->Clone("hRatioDD4hep_ErrorLow");
  hRatioDD4hep_ErrorLow->Divide(hData);
  hRatioDD4hep_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorLow->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorLow->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorUp = (TH1F*)hTimeSim_DD4hep_ErrorUp->Clone("hRatioDD4hep_ErrorUp");
  hRatioDD4hep_ErrorUp->Divide(hData);
  hRatioDD4hep_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorUp->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorUp->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk10 = (TH1F*)hTimeSim_DD4hep_Xtalk10->Clone("hRatioDD4hep_Xtalk10");
  hRatioDD4hep_Xtalk10->Divide(hData);
  hRatioDD4hep_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk10->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk10->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk18 = (TH1F*)hTimeSim_DD4hep_Xtalk18->Clone("hRatioDD4hep_Xtalk18");
  hRatioDD4hep_Xtalk18->Divide(hData);
  hRatioDD4hep_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk18->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk18->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
  gTimeSimRatio_DD4hep->SetLineColor(kBlue);
  gTimeSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
  {
    double content = hRatioDD4hep->GetBinContent(ibin);
    double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioDD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioDD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioDD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //------------------------------------------------------------

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("40 GeV e-");
  leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
  leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT_HP)", "l");
  leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTimeSim, sFactor);
  setupAxisScalingBottom(hRatioMokka, sFactor);
  pad1->cd();
  hTimeSim->GetXaxis()->SetRangeUser(-30,30);
  hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.090);
  hTimeSim->Draw("p hist");
  gTimeData->Draw("E2");
  gTimeSim->Draw("PE");
  gTimeSim_DD4hep->Draw("PE");
  hData->GetXaxis()->SetRangeUser(-30,30);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioMokka->GetXaxis()->SetRangeUser(-30,30);
  hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatioMokka->Draw("p");
  gTimeDataRatio->Draw("E2");
  gTimeSimRatio->Draw("PE");
  gTimeSimRatio_DD4hep->Draw("PE");
  hRatioData->GetXaxis()->SetRangeUser(-30,30);
  hRatioData->Draw("p hist same");

  c->SaveAs("Plots/Comparison_SimData_Electrons40GeV.pdf");
}

void ComparisonSimData_nHits50GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/NumberHits_50GeV.root", "OPEN");
  TH1F *hHitSim, *hHitSim_Xtalk10, *hHitSim_Xtalk18;

  f->GetObject("hHitSim", hHitSim);
  f->GetObject("hHitSim_Xtalk10", hHitSim_Xtalk10);
  f->GetObject("hHitSim_Xtalk18", hHitSim_Xtalk18);

  hHitSim->Sumw2();
  hHitSim->Scale(1./hHitSim->Integral("width"));

  hHitSim->SetLineColor(kRed);
  hHitSim->SetLineWidth(2);

  hHitSim_Xtalk10->Sumw2();
  hHitSim_Xtalk10->Scale(1./hHitSim_Xtalk10->Integral("width"));

  hHitSim_Xtalk10->SetLineColor(kGreen);
  hHitSim_Xtalk10->SetLineWidth(2);

  hHitSim_Xtalk18->Sumw2();
  hHitSim_Xtalk18->Scale(1./hHitSim_Xtalk18->Integral("width"));

  hHitSim_Xtalk18->SetLineColor(kMagenta);
  hHitSim_Xtalk18->SetLineWidth(2);

  //-------------------------------------------

  TH1F *hHitData;
  f->GetObject("hHitData", hHitData);

  hHitData->Sumw2();
  hHitData->Scale(1./hHitData->Integral("width"));

  hHitData->SetMarkerStyle(20);
  hHitData->SetMarkerColor(kBlack);

  hHitData->GetYaxis()->SetTitle("normalised entries");

  //--------------------------------------------

  TH1F* hHitSim_DD4hep, *hHitSim_DD4hep_Xtalk10, *hHitSim_DD4hep_Xtalk18;
  f->GetObject("hHitSim_DD4hep", hHitSim_DD4hep);
  f->GetObject("hHitSim_DD4hep_Xtalk10", hHitSim_DD4hep_Xtalk10);
  f->GetObject("hHitSim_DD4hep_Xtalk18", hHitSim_DD4hep_Xtalk18);

  hHitSim_DD4hep->Sumw2();
  hHitSim_DD4hep->Scale(1./hHitSim_DD4hep->Integral("width"));

  hHitSim_DD4hep->SetLineColor(kBlue);
  hHitSim_DD4hep->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk10->Sumw2();
  hHitSim_DD4hep_Xtalk10->Scale(1./hHitSim_DD4hep_Xtalk10->Integral("width"));

  hHitSim_DD4hep_Xtalk10->SetLineColor(kGreen);
  hHitSim_DD4hep_Xtalk10->SetLineWidth(2);

  hHitSim_DD4hep_Xtalk18->Sumw2();
  hHitSim_DD4hep_Xtalk18->Scale(1./hHitSim_DD4hep_Xtalk18->Integral("width"));

  hHitSim_DD4hep_Xtalk18->SetLineColor(kMagenta);
  hHitSim_DD4hep_Xtalk18->SetLineWidth(2);

  //--------------------------------------------

  //Error handling (Xtalk)

  TGraphAsymmErrors *gHitSim = new TGraphAsymmErrors();
  gHitSim->SetLineColor(kRed);
  gHitSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim->GetBinError(ibin);

    gHitSim->SetPoint(ibin, hHitSim->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }


  TGraphAsymmErrors *gHitSim_DD4hep = new TGraphAsymmErrors();
  gHitSim_DD4hep->SetLineColor(kBlue);
  gHitSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitSim_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hHitSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hHitSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hHitSim_DD4hep->GetBinError(ibin);

    gHitSim_DD4hep->SetPoint(ibin, hHitSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitData = new TGraphAsymmErrors();
  gHitData->SetLineWidth(0);
  gHitData->SetFillColor(kGray);
  gHitData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hHitData->GetNbinsX(); ibin++)
  {
    if(hHitData->GetBinContent(ibin) == 0) continue;

    double content = hHitData->GetBinContent(ibin);
    double error_stat = hHitData->GetBinError(ibin);

    gHitData->SetPoint(ibin, hHitData->GetXaxis()->GetBinCenter(ibin), content);
    gHitData->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //------------------------------------ Ratio ------------------------------------

  TH1F* hRatio = (TH1F*)hHitSim->Clone("hRatio");
  hRatio->Divide(hHitData);
  hRatio->GetYaxis()->SetTitle("MC/Data");
  hRatio->GetYaxis()->CenterTitle();

  TH1F* hRatio_Xtalk10 = (TH1F*)hHitSim_Xtalk10->Clone("hRatio_Xtalk10");
  hRatio_Xtalk10->Divide(hHitData);
  hRatio_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_Xtalk18 = (TH1F*)hHitSim_Xtalk18->Clone("hRatio_Xtalk18");
  hRatio_Xtalk18->Divide(hHitData);
  hRatio_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep = (TH1F*)hHitSim_DD4hep->Clone("hRatio_DD4hep");
  hRatio_DD4hep->Divide(hHitData);
  hRatio_DD4hep->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk10 = (TH1F*)hHitSim_DD4hep_Xtalk10->Clone("hRatio_DD4hep_Xtalk10");
  hRatio_DD4hep_Xtalk10->Divide(hHitData);
  hRatio_DD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatio_DD4hep_Xtalk18 = (TH1F*)hHitSim_DD4hep_Xtalk18->Clone("hRatio_DD4hep_Xtalk18");
  hRatio_DD4hep_Xtalk18->Divide(hHitData);
  hRatio_DD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");

  TH1F* hRatioData = (TH1F*)hHitData->Clone("hRatioData");
  hRatioData->Divide(hHitData);

  //------ Error handling ----------------------------

  TGraphAsymmErrors *gHitSimRatio = new TGraphAsymmErrors();
  gHitSimRatio->SetLineColor(kRed);
  gHitSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio->GetBinError(ibin);

    gHitSimRatio->SetPoint(ibin, hRatio->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitSimRatio_DD4hep = new TGraphAsymmErrors();
  gHitSimRatio_DD4hep->SetLineColor(kBlue);
  gHitSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatio_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = hRatio_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatio_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatio_DD4hep->GetBinError(ibin);

    gHitSimRatio_DD4hep->SetPoint(ibin, hRatio_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gHitSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_stat*error_stat + error_Xtalk_up*error_Xtalk_up));
  }

  TGraphAsymmErrors *gHitDataRatio = new TGraphAsymmErrors();
  gHitDataRatio->SetLineColor(kBlack);
  gHitDataRatio->SetLineWidth(2);
  gHitDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    gHitDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gHitDataRatio->SetPointError(ibin, 0.5, 0.5, error_stat, error_stat);
  }

  //--------------------------------------------------

  TLegend* leg = new TLegend(0.65, 0.35, 0.85, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetHeader("50 GeV e-");
  leg->AddEntry(gHitData, "Data", "pf");
  leg->AddEntry(gHitSim, "Mokka (QGSP_BERT_HP)", "l");
  leg->AddEntry(gHitSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.65, 0.70, 0.85, 0.85, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  double sFactor = 0.6;

  TCanvas *c1;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c1, "c1", "c1", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hHitData, sFactor);
  setupAxisScalingBottom(hRatio, sFactor);
  pad1->cd();
  pad1->SetLogy();
  hHitData->GetXaxis()->SetRangeUser(1, 20);
  hHitData->Draw("p hist");
  gHitData->Draw("E2");
  gHitSim->Draw("PE");
  gHitSim_DD4hep->Draw("PE");
  hHitData->Draw("p hist same");
  pt->Draw("same");
  leg->Draw("same");
  pad2->cd();
  hRatio->GetYaxis()->SetRangeUser(0, 1.5);
  hRatio->GetXaxis()->SetRangeUser(1, 20);
  hRatio->Draw("p hist");
  gHitDataRatio->Draw("E2");
  gHitSimRatio->Draw("PE");
  gHitSimRatio_DD4hep->Draw("PE");
  hRatioData->Draw("p hist same");

  c1->SaveAs("Plots/Comparison_SimData_Electrons_nHits_50GeV.pdf");
}

void ComparisonSimData_Timing50GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMokka_50GeV.root", "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(1, hTimeSim->GetNbinsX(), "width"));
  hTimeSim->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(1, hTimeSim_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(1, hTimeSim_ErrorUp->GetNbinsX(), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(1, hTimeSim_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(1, hTimeSim_Xtalk18->GetNbinsX(), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("normalised entries");

  //-------------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/50GeV/Data/Timing/Rootfiles/Timing_FullAHCAL.root", "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Electron", hData);

  hData->Sumw2();
  hData->Scale(1./hData->Integral(1, hData->GetNbinsX(), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  //hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //-------------------------------------------------

  //Ratio Plots
  TH1F* hRatioData = (TH1F*)hData->Clone("hRatioData");
  hRatioData->Divide(hData);
  hRatioData->GetYaxis()->SetTitle("MC/Data");
  hRatioData->SetMarkerStyle(20);
  hRatioData->SetMarkerColor(kBlack);

  TGraphAsymmErrors *gTimeDataRatio = new TGraphAsymmErrors();
  gTimeDataRatio->SetLineColor(kBlack);
  gTimeDataRatio->SetLineWidth(2);
  gTimeDataRatio->SetFillColor(kGray);

  for(int ibin = 0; ibin < hRatioData->GetNbinsX(); ibin++)
  {
    if(hRatioData->GetBinContent(ibin) == 0) continue;

    double content = hRatioData->GetBinContent(ibin);
    double error_stat = hRatioData->GetBinError(ibin);

    double error_syst = 0.20*content;//Detector Inhomogeneities

    gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
  hRatioMokka->Divide(hData);
  hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka->GetYaxis()->CenterTitle();
  hRatioMokka->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorLow = (TH1F*)hTimeSim_ErrorLow->Clone("hRatioMokka_ErrorLow");
  hRatioMokka_ErrorLow->Divide(hData);
  hRatioMokka_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorLow->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_ErrorUp = (TH1F*)hTimeSim_ErrorUp->Clone("hRatioMokka_ErrorUp");
  hRatioMokka_ErrorUp->Divide(hData);
  hRatioMokka_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_ErrorUp->GetYaxis()->CenterTitle();
  hRatioMokka_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk10 = (TH1F*)hTimeSim_Xtalk10->Clone("hRatioMokka_Xtalk10");
  hRatioMokka_Xtalk10->Divide(hData);
  hRatioMokka_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk10->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioMokka_Xtalk18 = (TH1F*)hTimeSim_Xtalk18->Clone("hRatioMokka_Xtalk18");
  hRatioMokka_Xtalk18->Divide(hData);
  hRatioMokka_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioMokka_Xtalk18->GetYaxis()->CenterTitle();
  hRatioMokka_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioMokka_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
  gTimeSimRatio->SetLineColor(kRed);
  gTimeSimRatio->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
  {
    double content = hRatioMokka->GetBinContent(ibin);
    double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioMokka_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioMokka_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioMokka->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //***************************************************************//
  //*
  //*
  //*
  //------------------- DD4hep -----------------------------

  TFile *f3 = new TFile("Rootfiles/TimingDD4hep_50GeV.root", "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F *hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kBlue);
  hTimeSim_DD4hep->SetMarkerColor(kBlue);
  hTimeSim_DD4hep->SetLineWidth(2);
  hTimeSim_DD4hep->GetYaxis()->SetTitle("normalised entries");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(1, hTimeSim_DD4hep->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(1, hTimeSim_DD4hep_ErrorLow->GetNbinsX(), "width"));
  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(1, hTimeSim_DD4hep_ErrorUp->GetNbinsX(), "width"));

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kRed);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(1, hTimeSim_DD4hep_Xtalk10->GetNbinsX(), "width"));
  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(1, hTimeSim_DD4hep_Xtalk18->GetNbinsX(), "width"));

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kBlue);
  gTimeSim_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    if(hData->GetBinContent(ibin) == 0) continue;

    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //----------------------------------------------

  TH1F *hRatioDD4hep = (TH1F*)hTimeSim_DD4hep->Clone("hRatioDD4hep");
  hRatioDD4hep->Divide(hData);
  hRatioDD4hep->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep->GetYaxis()->CenterTitle();
  hRatioDD4hep->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorLow = (TH1F*)hTimeSim_DD4hep_ErrorLow->Clone("hRatioDD4hep_ErrorLow");
  hRatioDD4hep_ErrorLow->Divide(hData);
  hRatioDD4hep_ErrorLow->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorLow->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorLow->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorLow->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorLow->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_ErrorUp = (TH1F*)hTimeSim_DD4hep_ErrorUp->Clone("hRatioDD4hep_ErrorUp");
  hRatioDD4hep_ErrorUp->Divide(hData);
  hRatioDD4hep_ErrorUp->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_ErrorUp->GetYaxis()->CenterTitle();
  hRatioDD4hep_ErrorUp->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_ErrorUp->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_ErrorUp->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk10 = (TH1F*)hTimeSim_DD4hep_Xtalk10->Clone("hRatioDD4hep_Xtalk10");
  hRatioDD4hep_Xtalk10->Divide(hData);
  hRatioDD4hep_Xtalk10->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk10->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk10->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk10->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk10->GetYaxis()->SetNdivisions(505);

  TH1F *hRatioDD4hep_Xtalk18 = (TH1F*)hTimeSim_DD4hep_Xtalk18->Clone("hRatioDD4hep_Xtalk18");
  hRatioDD4hep_Xtalk18->Divide(hData);
  hRatioDD4hep_Xtalk18->GetXaxis()->SetTitle("Time of first hit [ns]");
  hRatioDD4hep_Xtalk18->GetYaxis()->CenterTitle();
  hRatioDD4hep_Xtalk18->GetYaxis()->SetTitle("MC/Data");
  hRatioDD4hep_Xtalk18->GetYaxis()->SetRangeUser(0, 2.);
  hRatioDD4hep_Xtalk18->GetYaxis()->SetNdivisions(505);

  //------------------------- Ratio Errors ---------------------------------

  TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
  gTimeSimRatio_DD4hep->SetLineColor(kBlue);
  gTimeSimRatio_DD4hep->SetLineWidth(2);

  for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
  {
    double content = hRatioDD4hep->GetBinContent(ibin);
    double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hRatioDD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hRatioDD4hep_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    //Error Param

    if( (content - content_low < 0 && content - content_up > 0) || (content - content_low == 0 && content - content_up > 0) || (content - content_low < 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_up);
      error_up = TMath::Abs(content - content_low);
    }

    if( (content - content_low > 0 && content - content_up < 0) || (content - content_low == 0 && content - content_up < 0) || (content - content_low > 0 && content - content_up == 0) )
    {
      error_low = TMath::Abs(content - content_low);
      error_up = TMath::Abs(content - content_up);
    }

    if( (content - content_low > 0 && content - content_up > 0) )
    {
      error_low = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
      error_up = 0;
    }

    if( (content - content_low < 0 && content - content_up < 0) )
    {
      error_low = 0;
      error_up = std::max(TMath::Abs(content - content_up), TMath::Abs(content - content_low));
    }

    //Xtalk Error

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 > 0) || (content - content_Xtalk10 < 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk18);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk10);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 == 0 && content - content_Xtalk18 < 0) || (content - content_Xtalk10 > 0 && content - content_Xtalk18 == 0) )
    {
      error_Xtalk_low = TMath::Abs(content - content_Xtalk10);
      error_Xtalk_up = TMath::Abs(content - content_Xtalk18);
    }

    if( (content - content_Xtalk10 > 0 && content - content_Xtalk18 > 0) )
    {
      error_Xtalk_low = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
      error_Xtalk_up = 0;
    }

    if( (content - content_Xtalk10 < 0 && content - content_Xtalk18 < 0) )
    {
      error_Xtalk_low = 0;
      error_Xtalk_up = std::max(TMath::Abs(content - content_Xtalk18), TMath::Abs(content - content_Xtalk10));
    }

    double error_stat = hRatioDD4hep->GetBinError(ibin);
    double error_syst = 0.00*content;

    gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
  }

  //------------------------------------------------------------

  double sFactor = 0.60;

  TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("50 GeV e-");
  leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
  leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT_HP)", "l");
  leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT_HP)", "l");

  TPaveText *pt = new TPaveText(0.2, 0.65, 0.45, 0.80, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.06);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TCanvas *c;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hTimeSim, sFactor);
  setupAxisScalingBottom(hRatioMokka, sFactor);
  pad1->cd();
  hTimeSim->GetXaxis()->SetRangeUser(-30,30);
  hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.090);
  hTimeSim->Draw("p hist");
  gTimeData->Draw("E2");
  gTimeSim->Draw("PE");
  gTimeSim_DD4hep->Draw("PE");
  hData->GetXaxis()->SetRangeUser(-30,30);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");
  pad2->cd();
  hRatioMokka->GetXaxis()->SetRangeUser(-30,30);
  hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatioMokka->Draw("p");
  gTimeDataRatio->Draw("E2");
  gTimeSimRatio->Draw("PE");
  gTimeSimRatio_DD4hep->Draw("PE");
  hRatioData->GetXaxis()->SetRangeUser(-30,30);
  hRatioData->Draw("p hist same");

  c->SaveAs("Plots/Comparison_SimData_Electrons50GeV.pdf");
}

void Variables_10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Hits_10GeV.root", "OPEN");
  TH1F* hData, *hSim_10, *hSim_10_DD4hep, *hSim_18, *hSim_18_DD4hep;

  f->GetObject("hHits_10", hSim_10);
  f->GetObject("hHits_10_DD4hep", hSim_10_DD4hep);
  f->GetObject("hHits_18", hSim_18);
  f->GetObject("hHits_18_DD4hep", hSim_18_DD4hep);
  f->GetObject("hHits_Data", hData);

  hData->SetLineColor(kBlack);
  hData->SetLineWidth(2);
  hData->Scale(1./hData->Integral("width"));
  hData->GetXaxis()->SetTitle("nHits");
  hData->GetYaxis()->SetTitle("Fraction of Events");

  hSim_10->SetLineColor(kRed);
  hSim_10->SetLineWidth(2);
  hSim_10->Scale(1./hSim_10->Integral("width"));

  hSim_10_DD4hep->SetLineColor(kBlue);
  hSim_10_DD4hep->SetLineWidth(2);
  hSim_10_DD4hep->Scale(1./hSim_10_DD4hep->Integral("width"));

  hSim_18->SetLineColor(kRed);
  hSim_18->SetLineWidth(2);
  hSim_18->SetLineStyle(2);
  hSim_18->Scale(1./hSim_18->Integral("width"));

  hSim_18_DD4hep->SetLineColor(kBlue);
  hSim_18_DD4hep->SetLineWidth(2);
  hSim_18_DD4hep->SetLineStyle(2);
  hSim_18_DD4hep->Scale(1./hSim_18_DD4hep->Integral("width"));

  TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  leg->AddEntry(hData, "Data", "l");
  leg->AddEntry(hSim_10, "Mokka (10%)", "l");
  leg->AddEntry(hSim_18, "Mokka (18%)", "l");
  leg->AddEntry(hSim_10_DD4hep, "DD4hep (10%)", "l");
  leg->AddEntry(hSim_18_DD4hep, "DD4hep (18%)", "l");

  gStyle->SetOptStat(1110);
  hData->SetStats(1);
  hSim_10->SetStats(1);
  hSim_10_DD4hep->SetStats(1);
  hSim_18->SetStats(1);
  hSim_18_DD4hep->SetStats(1);

  TCanvas *c1 = new TCanvas("c1", "nHits", 800, 600);
  hData->Draw();
  hData->GetXaxis()->SetRangeUser(10, 150);
  hData->GetYaxis()->SetRangeUser(0, 0.12);
  hSim_10->Draw("sames");
  hSim_10_DD4hep->Draw("sames");
  hSim_18->Draw("sames");
  hSim_18_DD4hep->Draw("sames");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)hData->GetListOfFunctions()->FindObject("stats");
  st->SetX1NDC(0.7);
  st->SetX2NDC(0.9);
  st->SetY1NDC(0.75);
  st->SetY2NDC(0.9);
  st->SetLineColor(kBlack);
  st->SetTextColor(kBlack);
  TPaveStats *st2 = (TPaveStats*)hSim_10->GetListOfFunctions()->FindObject("stats");
  st2->SetX1NDC(0.48);
  st2->SetX2NDC(0.68);
  st2->SetY1NDC(0.55);
  st2->SetY2NDC(0.70);
  st2->SetLineColor(kRed);
  st2->SetTextColor(kRed);
  TPaveStats *st3 = (TPaveStats*)hSim_10_DD4hep->GetListOfFunctions()->FindObject("stats");
  st3->SetX1NDC(0.48);
  st3->SetX2NDC(0.68);
  st3->SetY1NDC(0.35);
  st3->SetY2NDC(0.50);
  st3->SetLineColor(kBlue);
  st3->SetTextColor(kBlue);
  TPaveStats *st4 = (TPaveStats*)hSim_18->GetListOfFunctions()->FindObject("stats");
  st4->SetX1NDC(0.7);
  st4->SetX2NDC(0.9);
  st4->SetY1NDC(0.55);
  st4->SetY2NDC(0.70);
  st4->SetLineColor(kRed);
  st4->SetTextColor(kRed);
  st4->SetLineStyle(2);
  TPaveStats *st5 = (TPaveStats*)hSim_18_DD4hep->GetListOfFunctions()->FindObject("stats");
  st5->SetX1NDC(0.7);
  st5->SetX2NDC(0.9);
  st5->SetY1NDC(0.35);
  st5->SetY2NDC(0.50);
  st5->SetLineColor(kBlue);
  st5->SetTextColor(kBlue);
  st5->SetLineStyle(2);
  gPad->Modified();

  c1->SaveAs("Plots/Comparison_nHits_Xtalk_electrons10GeV.pdf");

  //---------------------------

  TH1F* hCoGZData, *hCoGZSim_10, *hCoGZSim_10_DD4hep, *hCoGZSim_18, *hCoGZSim_18_DD4hep;

  f->GetObject("hCoGZ_10", hCoGZSim_10);
  f->GetObject("hCoGZ_10_DD4hep", hCoGZSim_10_DD4hep);
  f->GetObject("hCoGZ_18", hCoGZSim_18);
  f->GetObject("hCoGZ_18_DD4hep", hCoGZSim_18_DD4hep);
  f->GetObject("hCoGZ_Data", hCoGZData);

  hCoGZData->SetLineColor(kBlack);
  hCoGZData->SetLineWidth(2);
  hCoGZData->Scale(1./hCoGZData->Integral("width"));
  hCoGZData->GetXaxis()->SetTitle("AHCAL CoG Z [mm]");
  hCoGZData->GetYaxis()->SetTitle("Fraction of Events");

  hCoGZSim_10->SetLineColor(kRed);
  hCoGZSim_10->SetLineWidth(2);
  hCoGZSim_10->Scale(1./hCoGZSim_10->Integral("width"));

  hCoGZSim_10_DD4hep->SetLineColor(kBlue);
  hCoGZSim_10_DD4hep->SetLineWidth(2);
  hCoGZSim_10_DD4hep->Scale(1./hCoGZSim_10_DD4hep->Integral("width"));

  hCoGZSim_18->SetLineColor(kRed);
  hCoGZSim_18->SetLineWidth(2);
  hCoGZSim_18->Scale(1./hCoGZSim_18->Integral("width"));
  hCoGZSim_18->SetLineStyle(2);

  hCoGZSim_18_DD4hep->SetLineColor(kBlue);
  hCoGZSim_18_DD4hep->SetLineWidth(2);
  hCoGZSim_18_DD4hep->Scale(1./hCoGZSim_18_DD4hep->Integral("width"));
  hCoGZSim_18_DD4hep->SetLineStyle(2);

  hCoGZData->SetStats(1);
  hCoGZSim_10->SetStats(1);
  hCoGZSim_10_DD4hep->SetStats(1);
  hCoGZSim_18->SetStats(1);
  hCoGZSim_18_DD4hep->SetStats(1);

  TCanvas *c2 = new TCanvas("c2", "CoG Z", 800, 600);
  hCoGZData->Draw();
  hCoGZData->GetXaxis()->SetRangeUser(80, 300);
  hCoGZData->GetYaxis()->SetRangeUser(0, 0.05);
  hCoGZSim_10->Draw("sames");
  hCoGZSim_10_DD4hep->Draw("sames");
  hCoGZSim_18->Draw("sames");
  hCoGZSim_18_DD4hep->Draw("sames");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st6 = (TPaveStats*)hCoGZData->GetListOfFunctions()->FindObject("stats");
  st6->SetX1NDC(0.7);
  st6->SetX2NDC(0.9);
  st6->SetY1NDC(0.75);
  st6->SetY2NDC(0.9);
  st6->SetLineColor(kBlack);
  st6->SetTextColor(kBlack);
  TPaveStats *st7 = (TPaveStats*)hCoGZSim_10->GetListOfFunctions()->FindObject("stats");
  st7->SetX1NDC(0.48);
  st7->SetX2NDC(0.68);
  st7->SetY1NDC(0.55);
  st7->SetY2NDC(0.70);
  st7->SetLineColor(kRed);
  st7->SetTextColor(kRed);
  TPaveStats *st8 = (TPaveStats*)hCoGZSim_10_DD4hep->GetListOfFunctions()->FindObject("stats");
  st8->SetX1NDC(0.48);
  st8->SetX2NDC(0.68);
  st8->SetY1NDC(0.35);
  st8->SetY2NDC(0.50);
  st8->SetLineColor(kBlue);
  st8->SetTextColor(kBlue);
  TPaveStats *st9 = (TPaveStats*)hCoGZSim_18->GetListOfFunctions()->FindObject("stats");
  st9->SetX1NDC(0.7);
  st9->SetX2NDC(0.9);
  st9->SetY1NDC(0.55);
  st9->SetY2NDC(0.70);
  st9->SetLineColor(kRed);
  st9->SetTextColor(kRed);
  st9->SetLineStyle(2);
  TPaveStats *st10 = (TPaveStats*)hCoGZSim_18_DD4hep->GetListOfFunctions()->FindObject("stats");
  st10->SetX1NDC(0.7);
  st10->SetX2NDC(0.9);
  st10->SetY1NDC(0.35);
  st10->SetY2NDC(0.50);
  st10->SetLineColor(kBlue);
  st10->SetTextColor(kBlue);
  st10->SetLineStyle(2);
  gPad->Modified();

  c2->SaveAs("Plots/Comparison_CoGZ_Xtalk_electrons10GeV.pdf");

  //---------------------

  TH1F* hEsumData, *hEsum_10, *hEsum_10_DD4hep, *hEsum_18, *hEsum_18_DD4hep;

  f->GetObject("hEsum_10", hEsum_10);
  f->GetObject("hEsum_10_DD4hep", hEsum_10_DD4hep);
  f->GetObject("hEsum_18", hEsum_18);
  f->GetObject("hEsum_18_DD4hep", hEsum_18_DD4hep);
  f->GetObject("hEsum_Data", hEsumData);

  hEsumData->SetLineColor(kBlack);
  hEsumData->SetLineWidth(2);
  hEsumData->Scale(1./hEsumData->Integral("width"));
  hEsumData->GetXaxis()->SetTitle("E_{sum} [MIP]");
  hEsumData->GetYaxis()->SetTitle("Fraction of Events");

  hEsum_10->SetLineColor(kRed);
  hEsum_10->SetLineWidth(2);
  hEsum_10->Scale(1./hEsum_10->Integral("width"));

  hEsum_10_DD4hep->SetLineColor(kBlue);
  hEsum_10_DD4hep->SetLineWidth(2);
  hEsum_10_DD4hep->Scale(1./hEsum_10_DD4hep->Integral("width"));

  hEsum_18->SetLineColor(kRed);
  hEsum_18->SetLineWidth(2);
  hEsum_18->SetLineStyle(2);
  hEsum_18->Scale(1./hEsum_18->Integral("width"));

  hEsum_18_DD4hep->SetLineColor(kBlue);
  hEsum_18_DD4hep->SetLineWidth(2);
  hEsum_18_DD4hep->SetLineStyle(2);
  hEsum_18_DD4hep->Scale(1./hEsum_18_DD4hep->Integral("width"));

  hEsumData->SetStats(1);
  hEsum_10->SetStats(1);
  hEsum_10_DD4hep->SetStats(1);
  hEsum_18->SetStats(1);
  hEsum_18_DD4hep->SetStats(1);

  TCanvas *c3 = new TCanvas("c3", "E sum", 800, 600);
  hEsumData->Draw();
  hEsumData->GetXaxis()->SetRangeUser(0, 3000);
  hEsumData->GetYaxis()->SetRangeUser(0, 0.015);
  hEsumData->GetYaxis()->SetTitleOffset(1.3);
  hEsum_10->Draw("sames");
  hEsum_10_DD4hep->Draw("sames");
  hEsum_18->Draw("sames");
  hEsum_18_DD4hep->Draw("sames");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st11 = (TPaveStats*)hEsumData->GetListOfFunctions()->FindObject("stats");
  st11->SetX1NDC(0.7);
  st11->SetX2NDC(0.9);
  st11->SetY1NDC(0.75);
  st11->SetY2NDC(0.9);
  st11->SetLineColor(kBlack);
  st11->SetTextColor(kBlack);
  TPaveStats *st12 = (TPaveStats*)hEsum_10->GetListOfFunctions()->FindObject("stats");
  st12->SetX1NDC(0.48);
  st12->SetX2NDC(0.68);
  st12->SetY1NDC(0.55);
  st12->SetY2NDC(0.70);
  st12->SetLineColor(kRed);
  st12->SetTextColor(kRed);
  TPaveStats *st13 = (TPaveStats*)hEsum_10_DD4hep->GetListOfFunctions()->FindObject("stats");
  st13->SetX1NDC(0.48);
  st13->SetX2NDC(0.68);
  st13->SetY1NDC(0.35);
  st13->SetY2NDC(0.50);
  st13->SetLineColor(kBlue);
  st13->SetTextColor(kBlue);
  TPaveStats *st14 = (TPaveStats*)hEsum_18->GetListOfFunctions()->FindObject("stats");
  st14->SetX1NDC(0.7);
  st14->SetX2NDC(0.9);
  st14->SetY1NDC(0.55);
  st14->SetY2NDC(0.70);
  st14->SetLineColor(kRed);
  st14->SetTextColor(kRed);
  st14->SetLineStyle(2);
  TPaveStats *st15 = (TPaveStats*)hEsum_18_DD4hep->GetListOfFunctions()->FindObject("stats");
  st15->SetX1NDC(0.7);
  st15->SetX2NDC(0.9);
  st15->SetY1NDC(0.35);
  st15->SetY2NDC(0.50);
  st15->SetLineColor(kBlue);
  st15->SetTextColor(kBlue);
  st15->SetLineStyle(2);
  gPad->Modified();

  c3->SaveAs("Plots/Comparison_EnergySum_Xtalk_electrons10GeV.pdf");

  //------------------

  cout << "nHits " << 10 << " " << hData->GetMean() << " " << hSim_10->GetMean() << " " << hSim_18->GetMean() << " " << hSim_10_DD4hep->GetMean() << " " << hSim_18_DD4hep->GetMean() << endl;
  cout << "Esum " << 10 << " " << hEsumData->GetMean() << " " << hEsum_10->GetMean() << " " << hEsum_18->GetMean() << " " << hEsum_10_DD4hep->GetMean() << " " << hEsum_18_DD4hep->GetMean() << endl;
}

void Variables_50GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Hits_50GeV.root", "OPEN");
  TH1F* hData, *hSim_10, *hSim_10_DD4hep, *hSim_18, *hSim_18_DD4hep;

  f->GetObject("hHits_10", hSim_10);
  f->GetObject("hHits_10_DD4hep", hSim_10_DD4hep);
  f->GetObject("hHits_18", hSim_18);
  f->GetObject("hHits_18_DD4hep", hSim_18_DD4hep);
  f->GetObject("hHits_Data", hData);

  hData->SetLineColor(kBlack);
  hData->SetLineWidth(2);
  hData->Scale(1./hData->Integral("width"));
  hData->GetXaxis()->SetTitle("nHits");
  hData->GetYaxis()->SetTitle("Fraction of Events");

  hSim_10->SetLineColor(kRed);
  hSim_10->SetLineWidth(2);
  hSim_10->Scale(1./hSim_10->Integral("width"));

  hSim_10_DD4hep->SetLineColor(kBlue);
  hSim_10_DD4hep->SetLineWidth(2);
  hSim_10_DD4hep->Scale(1./hSim_10_DD4hep->Integral("width"));

  hSim_18->SetLineColor(kRed);
  hSim_18->SetLineWidth(2);
  hSim_18->SetLineStyle(2);
  hSim_18->Scale(1./hSim_18->Integral("width"));

  hSim_18_DD4hep->SetLineColor(kBlue);
  hSim_18_DD4hep->SetLineWidth(2);
  hSim_18_DD4hep->SetLineStyle(2);
  hSim_18_DD4hep->Scale(1./hSim_18_DD4hep->Integral("width"));

  TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  leg->AddEntry(hData, "Data", "l");
  leg->AddEntry(hSim_10, "Mokka (10%)", "l");
  leg->AddEntry(hSim_18, "Mokka (18%)", "l");
  leg->AddEntry(hSim_10_DD4hep, "DD4hep (10%)", "l");
  leg->AddEntry(hSim_18_DD4hep, "DD4hep (18%)", "l");

  gStyle->SetOptStat(1110);
  hData->SetStats(1);
  hSim_10->SetStats(1);
  hSim_10_DD4hep->SetStats(1);
  hSim_18->SetStats(1);
  hSim_18_DD4hep->SetStats(1);

  TCanvas *c1 = new TCanvas("c1", "nHits", 800, 600);
  hData->Draw();
  hData->GetXaxis()->SetRangeUser(50, 250);
  hData->GetYaxis()->SetRangeUser(0, 0.07);
  hSim_10->Draw("sames");
  hSim_10_DD4hep->Draw("sames");
  hSim_18->Draw("sames");
  hSim_18_DD4hep->Draw("sames");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)hData->GetListOfFunctions()->FindObject("stats");
  st->SetX1NDC(0.7);
  st->SetX2NDC(0.9);
  st->SetY1NDC(0.75);
  st->SetY2NDC(0.9);
  st->SetLineColor(kBlack);
  st->SetTextColor(kBlack);
  TPaveStats *st2 = (TPaveStats*)hSim_10->GetListOfFunctions()->FindObject("stats");
  st2->SetX1NDC(0.48);
  st2->SetX2NDC(0.68);
  st2->SetY1NDC(0.55);
  st2->SetY2NDC(0.70);
  st2->SetLineColor(kRed);
  st2->SetTextColor(kRed);
  TPaveStats *st3 = (TPaveStats*)hSim_10_DD4hep->GetListOfFunctions()->FindObject("stats");
  st3->SetX1NDC(0.48);
  st3->SetX2NDC(0.68);
  st3->SetY1NDC(0.35);
  st3->SetY2NDC(0.50);
  st3->SetLineColor(kBlue);
  st3->SetTextColor(kBlue);
  TPaveStats *st4 = (TPaveStats*)hSim_18->GetListOfFunctions()->FindObject("stats");
  st4->SetX1NDC(0.7);
  st4->SetX2NDC(0.9);
  st4->SetY1NDC(0.55);
  st4->SetY2NDC(0.70);
  st4->SetLineColor(kRed);
  st4->SetTextColor(kRed);
  st4->SetLineStyle(2);
  TPaveStats *st5 = (TPaveStats*)hSim_18_DD4hep->GetListOfFunctions()->FindObject("stats");
  st5->SetX1NDC(0.7);
  st5->SetX2NDC(0.9);
  st5->SetY1NDC(0.35);
  st5->SetY2NDC(0.50);
  st5->SetLineColor(kBlue);
  st5->SetTextColor(kBlue);
  st5->SetLineStyle(2);
  gPad->Modified();

  c1->SaveAs("Plots/Comparison_nHits_Xtalk_electrons50GeV.pdf");

  //---------------------------

  TH1F* hCoGZData, *hCoGZSim_10, *hCoGZSim_10_DD4hep, *hCoGZSim_18, *hCoGZSim_18_DD4hep;

  f->GetObject("hCoGZ_10", hCoGZSim_10);
  f->GetObject("hCoGZ_10_DD4hep", hCoGZSim_10_DD4hep);
  f->GetObject("hCoGZ_18", hCoGZSim_18);
  f->GetObject("hCoGZ_18_DD4hep", hCoGZSim_18_DD4hep);
  f->GetObject("hCoGZ_Data", hCoGZData);

  hCoGZData->SetLineColor(kBlack);
  hCoGZData->SetLineWidth(2);
  hCoGZData->Scale(1./hCoGZData->Integral("width"));
  hCoGZData->GetXaxis()->SetTitle("AHCAL CoG Z [mm]");
  hCoGZData->GetYaxis()->SetTitle("Fraction of Events");

  hCoGZSim_10->SetLineColor(kRed);
  hCoGZSim_10->SetLineWidth(2);
  hCoGZSim_10->Scale(1./hCoGZSim_10->Integral("width"));

  hCoGZSim_10_DD4hep->SetLineColor(kBlue);
  hCoGZSim_10_DD4hep->SetLineWidth(2);
  hCoGZSim_10_DD4hep->Scale(1./hCoGZSim_10_DD4hep->Integral("width"));

  hCoGZSim_18->SetLineColor(kRed);
  hCoGZSim_18->SetLineWidth(2);
  hCoGZSim_18->Scale(1./hCoGZSim_18->Integral("width"));
  hCoGZSim_18->SetLineStyle(2);

  hCoGZSim_18_DD4hep->SetLineColor(kBlue);
  hCoGZSim_18_DD4hep->SetLineWidth(2);
  hCoGZSim_18_DD4hep->Scale(1./hCoGZSim_18_DD4hep->Integral("width"));
  hCoGZSim_18_DD4hep->SetLineStyle(2);

  hCoGZData->SetStats(1);
  hCoGZSim_10->SetStats(1);
  hCoGZSim_10_DD4hep->SetStats(1);
  hCoGZSim_18->SetStats(1);
  hCoGZSim_18_DD4hep->SetStats(1);

  TCanvas *c2 = new TCanvas("c2", "CoG Z", 800, 600);
  hCoGZData->Draw();
  hCoGZData->GetXaxis()->SetRangeUser(80, 300);
  hCoGZData->GetYaxis()->SetRangeUser(0, 0.05);
  hCoGZSim_10->Draw("sames");
  hCoGZSim_10_DD4hep->Draw("sames");
  hCoGZSim_18->Draw("sames");
  hCoGZSim_18_DD4hep->Draw("sames");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st6 = (TPaveStats*)hCoGZData->GetListOfFunctions()->FindObject("stats");
  st6->SetX1NDC(0.7);
  st6->SetX2NDC(0.9);
  st6->SetY1NDC(0.75);
  st6->SetY2NDC(0.9);
  st6->SetLineColor(kBlack);
  st6->SetTextColor(kBlack);
  TPaveStats *st7 = (TPaveStats*)hCoGZSim_10->GetListOfFunctions()->FindObject("stats");
  st7->SetX1NDC(0.48);
  st7->SetX2NDC(0.68);
  st7->SetY1NDC(0.55);
  st7->SetY2NDC(0.70);
  st7->SetLineColor(kRed);
  st7->SetTextColor(kRed);
  TPaveStats *st8 = (TPaveStats*)hCoGZSim_10_DD4hep->GetListOfFunctions()->FindObject("stats");
  st8->SetX1NDC(0.48);
  st8->SetX2NDC(0.68);
  st8->SetY1NDC(0.35);
  st8->SetY2NDC(0.50);
  st8->SetLineColor(kBlue);
  st8->SetTextColor(kBlue);
  TPaveStats *st9 = (TPaveStats*)hCoGZSim_18->GetListOfFunctions()->FindObject("stats");
  st9->SetX1NDC(0.7);
  st9->SetX2NDC(0.9);
  st9->SetY1NDC(0.55);
  st9->SetY2NDC(0.70);
  st9->SetLineColor(kRed);
  st9->SetTextColor(kRed);
  st9->SetLineStyle(2);
  TPaveStats *st10 = (TPaveStats*)hCoGZSim_18_DD4hep->GetListOfFunctions()->FindObject("stats");
  st10->SetX1NDC(0.7);
  st10->SetX2NDC(0.9);
  st10->SetY1NDC(0.35);
  st10->SetY2NDC(0.50);
  st10->SetLineColor(kBlue);
  st10->SetTextColor(kBlue);
  st10->SetLineStyle(2);
  gPad->Modified();

  c2->SaveAs("Plots/Comparison_CoGZ_Xtalk_electrons50GeV.pdf");

  //---------------------

  TH1F* hEsumData, *hEsum_10, *hEsum_10_DD4hep, *hEsum_18, *hEsum_18_DD4hep;

  f->GetObject("hEsum_10", hEsum_10);
  f->GetObject("hEsum_10_DD4hep", hEsum_10_DD4hep);
  f->GetObject("hEsum_18", hEsum_18);
  f->GetObject("hEsum_18_DD4hep", hEsum_18_DD4hep);
  f->GetObject("hEsum_Data", hEsumData);

  hEsumData->SetLineColor(kBlack);
  hEsumData->SetLineWidth(2);
  hEsumData->Scale(1./hEsumData->Integral("width"));
  hEsumData->GetXaxis()->SetTitle("E_{sum} [MIP]");
  hEsumData->GetYaxis()->SetTitle("Fraction of Events");

  hEsum_10->SetLineColor(kRed);
  hEsum_10->SetLineWidth(2);
  hEsum_10->Scale(1./hEsum_10->Integral("width"));

  hEsum_10_DD4hep->SetLineColor(kBlue);
  hEsum_10_DD4hep->SetLineWidth(2);
  hEsum_10_DD4hep->Scale(1./hEsum_10_DD4hep->Integral("width"));

  hEsum_18->SetLineColor(kRed);
  hEsum_18->SetLineWidth(2);
  hEsum_18->SetLineStyle(2);
  hEsum_18->Scale(1./hEsum_18->Integral("width"));

  hEsum_18_DD4hep->SetLineColor(kBlue);
  hEsum_18_DD4hep->SetLineWidth(2);
  hEsum_18_DD4hep->SetLineStyle(2);
  hEsum_18_DD4hep->Scale(1./hEsum_18_DD4hep->Integral("width"));

  hEsumData->SetStats(1);
  hEsum_10->SetStats(1);
  hEsum_10_DD4hep->SetStats(1);
  hEsum_18->SetStats(1);
  hEsum_18_DD4hep->SetStats(1);

  TCanvas *c3 = new TCanvas("c3", "E sum", 800, 600);
  hEsumData->Draw();
  hEsumData->GetXaxis()->SetRangeUser(600, 3000);
  hEsumData->GetYaxis()->SetRangeUser(0, 0.006);
  hEsumData->GetYaxis()->SetTitleOffset(1.3);
  hEsum_10->Draw("sames");
  hEsum_10_DD4hep->Draw("sames");
  hEsum_18->Draw("sames");
  hEsum_18_DD4hep->Draw("sames");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st11 = (TPaveStats*)hEsumData->GetListOfFunctions()->FindObject("stats");
  st11->SetX1NDC(0.7);
  st11->SetX2NDC(0.9);
  st11->SetY1NDC(0.75);
  st11->SetY2NDC(0.9);
  st11->SetLineColor(kBlack);
  st11->SetTextColor(kBlack);
  TPaveStats *st12 = (TPaveStats*)hEsum_10->GetListOfFunctions()->FindObject("stats");
  st12->SetX1NDC(0.48);
  st12->SetX2NDC(0.68);
  st12->SetY1NDC(0.55);
  st12->SetY2NDC(0.70);
  st12->SetLineColor(kRed);
  st12->SetTextColor(kRed);
  TPaveStats *st13 = (TPaveStats*)hEsum_10_DD4hep->GetListOfFunctions()->FindObject("stats");
  st13->SetX1NDC(0.48);
  st13->SetX2NDC(0.68);
  st13->SetY1NDC(0.35);
  st13->SetY2NDC(0.50);
  st13->SetLineColor(kBlue);
  st13->SetTextColor(kBlue);
  TPaveStats *st14 = (TPaveStats*)hEsum_18->GetListOfFunctions()->FindObject("stats");
  st14->SetX1NDC(0.7);
  st14->SetX2NDC(0.9);
  st14->SetY1NDC(0.55);
  st14->SetY2NDC(0.70);
  st14->SetLineColor(kRed);
  st14->SetTextColor(kRed);
  st14->SetLineStyle(2);
  TPaveStats *st15 = (TPaveStats*)hEsum_18_DD4hep->GetListOfFunctions()->FindObject("stats");
  st15->SetX1NDC(0.7);
  st15->SetX2NDC(0.9);
  st15->SetY1NDC(0.35);
  st15->SetY2NDC(0.50);
  st15->SetLineColor(kBlue);
  st15->SetTextColor(kBlue);
  st15->SetLineStyle(2);
  gPad->Modified();

  c3->SaveAs("Plots/Comparison_EnergySum_Xtalk_electrons50GeV.pdf");

  //------------------

  cout << "nHits " << 50 << " " << hData->GetMean() << " " << hSim_10->GetMean() << " " << hSim_18->GetMean() << " " << hSim_10_DD4hep->GetMean() << " " << hSim_18_DD4hep->GetMean() << endl;
  cout << "Esum " << 50 << " " << hEsumData->GetMean() << " " << hEsum_10->GetMean() << " " << hEsum_18->GetMean() << " " << hEsum_10_DD4hep->GetMean() << " " << hEsum_18_DD4hep->GetMean() << endl;
}

void BeamProfile_10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/10GeV/Data/SelectionCuts/Rootfiles/BeamProfile10GeV.root", "OPEN");
  TH1F* hCogXData, *hCogYData, *hHitsData, *hCogZData;
  TH2F* hCogXYData;

  f->GetObject("hCogX", hCogXData);
  f->GetObject("hCogY", hCogYData);
  f->GetObject("hCogXY", hCogXYData);

  hCogXYData->SetLineColor(kBlack);
  hCogXYData->SetLineWidth(2);

  float Entries = hCogXYData->GetEntries();
  for(int i = 0; i < hCogXYData->GetNbinsX()+1; i++)
  {
    for(int j = 0; j < hCogXYData->GetNbinsY()+1; j++)
    {
      float content = hCogXYData->GetBinContent(i, j);
      hCogXYData->SetBinContent(i, j, (float)content/Entries);
    }
  }

  hCogXData->SetLineColor(kBlack);
  hCogXData->SetLineWidth(2);
  hCogXData->Scale(1./hCogXData->Integral("width"));
  hCogXData->GetYaxis()->SetTitle("Fraction of events");
  hCogXData->GetYaxis()->SetTitleOffset(1.3);

  hCogYData->SetLineColor(kBlack);
  hCogYData->SetLineWidth(2);
  hCogYData->Scale(1./hCogYData->Integral("width"));
  hCogYData->GetYaxis()->SetTitle("Fraction of events");
  hCogYData->GetYaxis()->SetTitleOffset(1.3);

  TFile *f2 = new TFile("Rootfiles/BeamProfile10GeV_Sim.root", "OPEN");
  TH1F* hCogXSim, *hCogYSim, *hHitsSim, *hCogZSim;
  TH2F* hCogXYSim;

  f2->GetObject("hCogX", hCogXSim);
  f2->GetObject("hCogY", hCogYSim);
  f2->GetObject("hCogXY", hCogXYSim);

  hCogXYSim->SetLineColor(kRed);
  hCogXYSim->SetLineWidth(2);

  Entries = hCogXYSim->GetEntries();
  for(int i = 0; i < hCogXYSim->GetNbinsX()+1; i++)
  {
    for(int j = 0; j < hCogXYSim->GetNbinsY()+1; j++)
    {
      float content = hCogXYSim->GetBinContent(i, j);
      hCogXYSim->SetBinContent(i, j, (float)content/Entries);
    }
  }

  hCogXSim->SetLineColor(kRed);
  hCogXSim->SetLineWidth(2);
  hCogXSim->SetFillColor(kRed);
  hCogXSim->SetFillStyle(3001);
  hCogXSim->Scale(1./hCogXSim->Integral("width"));

  hCogYSim->SetLineColor(kRed);
  hCogYSim->SetLineWidth(2);
  hCogYSim->SetFillColor(kRed);
  hCogYSim->SetFillStyle(3001);
  hCogYSim->Scale(1./hCogYSim->Integral("width"));

  //------------------------------------------------------

  TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
  leg->SetHeader("AHCAL e- 10 GeV");
  leg->AddEntry(hCogXYData, "Data", "l");
  leg->AddEntry(hCogXYSim, "Mokka (QGSP_BERT_HP)", "l");

  gStyle->SetOptStat(1110);
  hCogXData->SetStats(1);
  hCogYData->SetStats(1);

  hCogXSim->SetStats(1);
  hCogYSim->SetStats(1);

  TCanvas *c2 = new TCanvas("c2", "Beam Profile X", 800, 600);
  c2->cd();
  hCogXData->Draw();
  hCogXData->GetYaxis()->SetRangeUser(0, 0.04);
  hCogXSim->Draw("sames");
  hCogXData->Draw("same");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)hCogXData->GetListOfFunctions()->FindObject("stats");
  st->SetX1NDC(0.7);
  st->SetX2NDC(0.9);
  st->SetY1NDC(0.75);
  st->SetY2NDC(0.9);
  st->SetLineColor(kBlack);
  st->SetTextColor(kBlack);
  TPaveStats *st2 = (TPaveStats*)hCogXSim->GetListOfFunctions()->FindObject("stats");
  st2->SetX1NDC(0.7);
  st2->SetX2NDC(0.9);
  st2->SetY1NDC(0.55);
  st2->SetY2NDC(0.70);
  st2->SetLineColor(kRed);
  st2->SetTextColor(kRed);
  gPad->Modified();

  TCanvas *c3 = new TCanvas("c3", "Beam Profile Y", 800, 600);
  c3->cd();
  hCogYData->Draw();
  hCogYData->GetYaxis()->SetRangeUser(0, 0.04);
  hCogYSim->Draw("sames");
  hCogYData->Draw("same");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st3 = (TPaveStats*)hCogYData->GetListOfFunctions()->FindObject("stats");
  st3->SetX1NDC(0.7);
  st3->SetX2NDC(0.9);
  st3->SetY1NDC(0.75);
  st3->SetY2NDC(0.9);
  st3->SetLineColor(kBlack);
  st3->SetTextColor(kBlack);
  TPaveStats *st4 = (TPaveStats*)hCogYSim->GetListOfFunctions()->FindObject("stats");
  st4->SetX1NDC(0.7);
  st4->SetX2NDC(0.9);
  st4->SetY1NDC(0.55);
  st4->SetY2NDC(0.70);
  st4->SetLineColor(kRed);
  st4->SetTextColor(kRed);
  gPad->Modified();

  c2->SaveAs("Plots/Run24542_CoGX_AHCAL_10GeV_Comparison.pdf");
  c3->SaveAs("Plots/Run24542_CoGY_AHCAL_10GeV_Comparison.pdf");
}

void BeamProfile_50GeV()
{
  CaliceStyle();

  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Electrons/50GeV/Data/SelectionCuts/Rootfiles/BeamProfile50GeV.root", "OPEN");
  TH1F* hCogXData, *hCogYData, *hHitsData, *hCogZData;
  TH2F* hCogXYData;

  f->GetObject("hCogX", hCogXData);
  f->GetObject("hCogY", hCogYData);
  f->GetObject("hCogXY", hCogXYData);

  hCogXYData->SetLineColor(kBlack);
  hCogXYData->SetLineWidth(2);

  float Entries = hCogXYData->GetEntries();
  for(int i = 0; i < hCogXYData->GetNbinsX()+1; i++)
  {
    for(int j = 0; j < hCogXYData->GetNbinsY()+1; j++)
    {
      float content = hCogXYData->GetBinContent(i, j);
      hCogXYData->SetBinContent(i, j, (float)content/Entries);
    }
  }

  hCogXData->SetLineColor(kBlack);
  hCogXData->SetLineWidth(2);
  hCogXData->Scale(1./hCogXData->Integral("width"));
  hCogXData->GetYaxis()->SetTitle("Fraction of events");
  hCogXData->GetYaxis()->SetTitleOffset(1.3);

  hCogYData->SetLineColor(kBlack);
  hCogYData->SetLineWidth(2);
  hCogYData->Scale(1./hCogYData->Integral("width"));
  hCogYData->GetYaxis()->SetTitle("Fraction of events");
  hCogYData->GetYaxis()->SetTitleOffset(1.3);

  TFile *f2 = new TFile("Rootfiles/BeamProfile50GeV_Sim.root", "OPEN");
  TH1F* hCogXSim, *hCogYSim, *hHitsSim, *hCogZSim;
  TH2F* hCogXYSim;

  f2->GetObject("hCogX", hCogXSim);
  f2->GetObject("hCogY", hCogYSim);
  f2->GetObject("hCogXY", hCogXYSim);

  hCogXYSim->SetLineColor(kRed);
  hCogXYSim->SetLineWidth(2);

  Entries = hCogXYSim->GetEntries();
  for(int i = 0; i < hCogXYSim->GetNbinsX()+1; i++)
  {
    for(int j = 0; j < hCogXYSim->GetNbinsY()+1; j++)
    {
      float content = hCogXYSim->GetBinContent(i, j);
      hCogXYSim->SetBinContent(i, j, (float)content/Entries);
    }
  }

  hCogXSim->SetLineColor(kRed);
  hCogXSim->SetLineWidth(2);
  hCogXSim->SetFillColor(kRed);
  hCogXSim->SetFillStyle(3001);
  hCogXSim->Scale(1./hCogXSim->Integral("width"));

  hCogYSim->SetLineColor(kRed);
  hCogYSim->SetLineWidth(2);
  hCogYSim->SetFillColor(kRed);
  hCogYSim->SetFillStyle(3001);
  hCogYSim->Scale(1./hCogYSim->Integral("width"));

  //------------------------------------------------------

  TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
  leg->SetHeader("AHCAL e- 50 GeV");
  leg->AddEntry(hCogXYData, "Data", "l");
  leg->AddEntry(hCogXYSim, "Mokka (QGSP_BERT_HP)", "l");

  gStyle->SetOptStat(1110);
  hCogXData->SetStats(1);
  hCogYData->SetStats(1);

  hCogXSim->SetStats(1);
  hCogYSim->SetStats(1);

  TCanvas *c2 = new TCanvas("c2", "Beam Profile X", 800, 600);
  c2->cd();
  hCogXData->Draw();
  hCogXData->GetYaxis()->SetRangeUser(0, 0.04);
  hCogXSim->Draw("sames");
  hCogXData->Draw("same");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)hCogXData->GetListOfFunctions()->FindObject("stats");
  st->SetX1NDC(0.7);
  st->SetX2NDC(0.9);
  st->SetY1NDC(0.75);
  st->SetY2NDC(0.9);
  st->SetLineColor(kBlack);
  st->SetTextColor(kBlack);
  TPaveStats *st2 = (TPaveStats*)hCogXSim->GetListOfFunctions()->FindObject("stats");
  st2->SetX1NDC(0.7);
  st2->SetX2NDC(0.9);
  st2->SetY1NDC(0.55);
  st2->SetY2NDC(0.70);
  st2->SetLineColor(kRed);
  st2->SetTextColor(kRed);
  gPad->Modified();

  TCanvas *c3 = new TCanvas("c3", "Beam Profile Y", 800, 600);
  c3->cd();
  hCogYData->Draw();
  hCogYData->GetYaxis()->SetRangeUser(0, 0.04);
  hCogYSim->Draw("sames");
  hCogYData->Draw("same");
  leg->Draw("same");
  gPad->Update();
  TPaveStats *st3 = (TPaveStats*)hCogYData->GetListOfFunctions()->FindObject("stats");
  st3->SetX1NDC(0.7);
  st3->SetX2NDC(0.9);
  st3->SetY1NDC(0.75);
  st3->SetY2NDC(0.9);
  st3->SetLineColor(kBlack);
  st3->SetTextColor(kBlack);
  TPaveStats *st4 = (TPaveStats*)hCogYSim->GetListOfFunctions()->FindObject("stats");
  st4->SetX1NDC(0.7);
  st4->SetX2NDC(0.9);
  st4->SetY1NDC(0.55);
  st4->SetY2NDC(0.70);
  st4->SetLineColor(kRed);
  st4->SetTextColor(kRed);
  gPad->Modified();

  c2->SaveAs("Plots/Run24405_CoGX_AHCAL_50GeV_Comparison.pdf");
  c3->SaveAs("Plots/Run24405_CoGY_AHCAL_50GeV_Comparison.pdf");
}

void TimingMay2016()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimingMay2016.root", "OPEN");
  TH1F *h13, *h14;

  f->GetObject("Timing_Module03", h13);
  f->GetObject("Timing_Module04", h14);

  h13->Add(h14, 1);

  h13->SetLineColor(kBlack);
  h13->SetLineWidth(2);
  h13->GetXaxis()->SetTitle("Time of first hit [ns]");
  h13->GetYaxis()->SetTitle("Fraction of hits / ns");
  h13->Scale(1./h13->Integral(h13->GetXaxis()->FindBin(-100), h13->GetXaxis()->FindBin(100), "width"));

  TPaveText *pt = new TPaveText(0.2, 0.76, 0.5, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("May 2016");

  TPaveText *pt2 = new TPaveText(0.68, 0.7, 0.88, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(1);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.03);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("3 GeV e");
  pt2->AddText(TString::Format("Mean: %2.3f ns", h13->GetMean()));
  pt2->AddText(TString::Format("RMS: %2.3f ns", h13->GetRMS()));

  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  // gPad->SetLogy();
  h13->GetXaxis()->SetRangeUser(-30, 30);
  h13->Draw();
  pt->Draw("same");
  pt2->Draw("same");

  c1->SaveAs("Plots/Timing_May2016_BigLayers.pdf");
}

void ChipRejection()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/FractionHits.root", "OPEN");
  TH1F *hFrac;
  TH1F *hChip;

  f->GetObject("hFrac", hFrac);

  TIter next(f->GetListOfKeys());
  TKey *key;

  while ((key = (TKey*)next()))
  {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TH1")) continue;

    TH1 *h = (TH1*)key->ReadObj();
    string histoname = key->GetName();
    int Chip = atoi(histoname.substr(histoname.find("Chip")+4, 3).c_str());

    if(Chip == 149)
    hChip = (TH1F*)h;
  }

  TLine *line = new TLine(98, 0, 98, 10);
  line->SetLineColor(kRed);
  line->SetLineWidth(3);
  line->SetLineStyle(2);

  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  // hFrac->Rebin(2);
  hFrac->SetLineColor(kBlue);
  hFrac->SetFillColor(kBlue);
  hFrac->SetLineWidth(2);
  hFrac->SetFillStyle(3002);
  hFrac->GetXaxis()->SetRangeUser(90, 100);
  hFrac->GetYaxis()->SetRangeUser(0, 10);
  hFrac->GetXaxis()->SetTitle("Fraction of hits between [-50, 50] ns [%]");
  hFrac->GetYaxis()->SetTitle("Number of chips");
  hFrac->Draw();
  line->Draw("same");

  c1->SaveAs("Plots/FractionRejectedChips.pdf");

  TPaveText *pt = new TPaveText(0.18, 0.75, 0.38, 0.90, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("50 GeV e-, Chip 149");
  pt->AddText("Work in progress");

  hChip->GetXaxis()->SetRangeUser(-200, 200);
  hChip->Scale(1./hChip->Integral("width"));

  TCanvas *c2 = new TCanvas("c2", "", 800, 600);
  gPad->SetLogy();
  hChip->SetLineColor(kBlack);
  hChip->SetLineWidth(2);
  hChip->GetXaxis()->SetTitle("Time of first hit [ns]");
  hChip->GetYaxis()->SetTitle("Fraction of hits");
  hChip->Draw();
  pt->Draw("same");

  c2->SaveAs("Plots/ExampleBadChip149.pdf");
}

void MakePlots()
{
  Validation();
  NumberHits();
  Parametrisation();
  MeanParametrisation();
  Timing_AfterMuons();
  Timing_AHCAL_20GeV();
  CheckParametrisation();

  SelectionCuts_10GeV();
  SelectionCuts_50GeV();

  Systematics_10GeV();
  Systematics_50GeV();

  ComparisonSimData_nHits10GeV();
  ComparisonSimData_Timing10GeV();

  ComparisonSimData_nHits15GeV();
  ComparisonSimData_Timing15GeV();

  ComparisonSimData_nHits20GeV();
  ComparisonSimData_Timing20GeV();

  ComparisonSimData_nHits30GeV();
  ComparisonSimData_Timing30GeV();

  ComparisonSimData_nHits40GeV();
  ComparisonSimData_Timing40GeV();

  ComparisonSimData_nHits50GeV();
  ComparisonSimData_Timing50GeV();

  Variables_10GeV();
  Variables_50GeV();

  BeamProfile_10GeV();
  BeamProfile_50GeV();

  TimingMay2016();
  ChipRejection();
}
