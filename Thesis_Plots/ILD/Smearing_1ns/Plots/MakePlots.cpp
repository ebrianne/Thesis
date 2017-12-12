void MakePlots()
{
  CaliceStyle();
  TFile *f = new TFile("Rootfiles/ILDTiming_NoSmearing.root", "OPEN");

  const int nTime = 13;
  const int nEnergy = 10;

  int timecuts[nTime] = {1, 2, 3, 5, 8, 10, 15, 20, 25, 30, 50, 70, 100};
  int energies[nEnergy] = {5, 10, 20, 30, 40, 50, 60, 70, 80, 90};
  int colors[nEnergy] = {kBlack, kRed, kGreen, kBlue, kYellow, kOrange+1, kMagenta, kViolet, kAzure-4, kTeal};
  int colors2[nTime] = {kBlack, kRed, kGreen, kBlue, kYellow, kOrange+1, kMagenta, kViolet, kAzure-4, kTeal, kSpring, kPink, kGreen-3};
  int Nevt[nEnergy] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  //Relative energy to norm
  TGraphErrors *gEnergy[nEnergy];
  //Relative Reso to norm
  TGraphErrors *gResoEnergy[nEnergy];
  //Relative width to norm
  TGraphErrors *gWidth[nEnergy];
  //Absolute width
  TGraphErrors *gWidthAbso[nEnergy];
  //Radial Profile
  TGraphErrors *gRadial[nEnergy];
  //Radial Profile Absolute
  TGraphErrors *gRadialAbso[nEnergy];
  //Relative width vs Reso
  TGraphErrors *gWidthReso[nEnergy];
  //Relative width vs Reso Residuals
  TGraphErrors *gResidualsWidthReso[nEnergy];
  //Absolute Reso
  TGraphErrors *gResoCurve[nTime];
  //Linearity
  TGraphErrors *gLinCurve[nTime];
  //Residuals
  TGraphErrors *gResidualLinCurve[nTime];

  TH1F *hEnergyHits[nEnergy][nTime];
  TH1F *hwRadius[nEnergy][nTime];
  TH1F *hRadialProfile[nEnergy][nTime];
  TH1F *hHitsRadial[nEnergy][nTime];

  for(int i = 0; i < nEnergy; i++)
  {
    for(int j = 0; j < nTime; j++)
    {
      f->GetObject(TString::Format("hEnergyHits_%02iGeV_%03ins", energies[i], timecuts[j]), hEnergyHits[i][j]);
      f->GetObject(TString::Format("hwRadius_%02iGeV_%03ins", energies[i], timecuts[j]), hwRadius[i][j]);
      f->GetObject(TString::Format("hRadialProfile_%02iGeV_%03ins", energies[i], timecuts[j]), hRadialProfile[i][j]);
      f->GetObject(TString::Format("hHitsRadial_%02iGeV_%03ins", energies[i], timecuts[j]), hHitsRadial[i][j]);
    }
  }

  for(int i = 0; i < nEnergy; i++)
  {
    Nevt[i] = hEnergyHits[i][nTime-1]->GetEntries();
    f->GetObject(TString::Format("gEnergy_%02iGeV", energies[i]), gEnergy[i]);
    f->GetObject(TString::Format("gResoEnergy_%02iGeV", energies[i]), gResoEnergy[i]);
    f->GetObject(TString::Format("gWidth_%02iGeV", energies[i]), gWidth[i]);
    f->GetObject(TString::Format("gWidthAbso_%02iGeV", energies[i]), gWidthAbso[i]);
    f->GetObject(TString::Format("gRadial_%02iGeV", energies[i]), gRadial[i]);
    f->GetObject(TString::Format("gRadialAbso_%02iGeV", energies[i]), gRadialAbso[i]);
    f->GetObject(TString::Format("gWidthReso_%02iGeV", energies[i]), gWidthReso[i]);
    f->GetObject(TString::Format("gResidualsWidthReso_%02iGeV", energies[i]), gResidualsWidthReso[i]);
  }

  for(int j = 0; j < nTime; j++)
  {
    f->GetObject(TString::Format("gResoCurve_%03ins", timecuts[j]), gResoCurve[j]);
    f->GetObject(TString::Format("gLinCurve_%03ins", timecuts[j]), gLinCurve[j]);
    f->GetObject(TString::Format("gResidualLinCurve_%03ins", timecuts[j]), gResidualLinCurve[j]);
  }

  //----------------------------------------------------------------------------

  for(int i = 0; i < nEnergy; i++)
  {
    gEnergy[i]->SetMarkerColor(colors[i]);
    gEnergy[i]->SetMarkerStyle(20);
    gEnergy[i]->SetLineColor(colors[i]);
    gEnergy[i]->SetLineWidth(2);

    gResoEnergy[i]->SetMarkerColor(colors[i]);
    gResoEnergy[i]->SetMarkerStyle(20);
    gResoEnergy[i]->SetLineColor(colors[i]);
    gResoEnergy[i]->SetLineWidth(2);

    gWidth[i]->SetMarkerColor(colors[i]);
    gWidth[i]->SetMarkerStyle(20);
    gWidth[i]->SetLineColor(colors[i]);
    gWidth[i]->SetLineWidth(2);

    gRadial[i]->SetMarkerColor(colors[i]);
    gRadial[i]->SetMarkerStyle(20);
    gRadial[i]->SetLineColor(colors[i]);
    gRadial[i]->SetLineWidth(2);

    gWidthAbso[i]->SetMarkerColor(colors[i]);
    gWidthAbso[i]->SetMarkerStyle(20);
    gWidthAbso[i]->SetLineColor(colors[i]);
    gWidthAbso[i]->SetLineWidth(2);

    gRadialAbso[i]->SetMarkerColor(colors[i]);
    gRadialAbso[i]->SetMarkerStyle(20);
    gRadialAbso[i]->SetLineColor(colors[i]);
    gRadialAbso[i]->SetLineWidth(2);

    gWidthReso[i]->SetMarkerColor(colors[i]);
    gWidthReso[i]->SetMarkerStyle(20);
    gWidthReso[i]->SetLineColor(colors[i]);
    gWidthReso[i]->SetLineWidth(2);

    gResidualsWidthReso[i]->SetMarkerColor(colors[i]);
    gResidualsWidthReso[i]->SetMarkerStyle(20);
    gResidualsWidthReso[i]->SetLineColor(colors[i]);
    gResidualsWidthReso[i]->SetLineWidth(2);
  }

  for(int i = 0; i < nTime; i++)
  {
    gResoCurve[i]->SetMarkerColor(colors2[i]);
    gResoCurve[i]->SetMarkerStyle(20);
    gResoCurve[i]->SetLineColor(colors2[i]);
    gResoCurve[i]->SetLineWidth(2);

    gLinCurve[i]->SetMarkerColor(colors2[i]);
    gLinCurve[i]->SetMarkerStyle(20);
    gLinCurve[i]->SetLineColor(colors2[i]);
    gLinCurve[i]->SetLineWidth(2);

    gResidualLinCurve[i]->SetMarkerColor(colors2[i]);
    gResidualLinCurve[i]->SetMarkerStyle(20);
    gResidualLinCurve[i]->SetLineColor(colors2[i]);
    gResidualLinCurve[i]->SetLineWidth(2);
  }

  //----------------------------------------------------------------------------

  TMultiGraph *multi = new TMultiGraph();
  TMultiGraph *multi2 = new TMultiGraph();
  TMultiGraph *multi3 = new TMultiGraph();
  TMultiGraph *multi6 = new TMultiGraph();
  TMultiGraph *multi10 = new TMultiGraph();
  TMultiGraph *multi11 = new TMultiGraph();
  TMultiGraph *multi12 = new TMultiGraph();
  TMultiGraph *multi_res = new TMultiGraph();
  TMultiGraph *multi_res2 = new TMultiGraph();

  TLegend *leg = new TLegend(0.75, 0.2, 0.9, 0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.028);

  TLegend *leg2 = new TLegend(0.75, 0.2, 0.9, 0.5);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.028);

  TLegend *leg3 = new TLegend(0.75, 0.6, 0.9, 0.9);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);

  TLegend *leg10 = new TLegend(0.6, 0.6, 0.9, 0.85);
  leg10->SetBorderSize(0);
  leg10->SetNColumns(2);
  leg10->SetTextSize(0.035);

  for(int i = 0; i < nEnergy; i++)
  {
    multi->Add(gEnergy[i]);
    multi2->Add(gWidth[i]);
    multi11->Add(gRadial[i]);
    multi12->Add(gRadialAbso[i]);
    multi6->Add(gWidthAbso[i]);
    multi3->Add(gResoEnergy[i]);
    multi10->Add(gWidthReso[i]);
    multi_res2->Add(gResidualsWidthReso[i]);

    leg->AddEntry(gEnergy[i], TString::Format("%02i GeV", energies[i]), "lp");
    leg2->AddEntry(gWidth[i], TString::Format("%02i GeV", energies[i]), "lp");
    leg3->AddEntry(gResoEnergy[i], TString::Format("%02i GeV", energies[i]), "lp");
    leg10->AddEntry(gWidthReso[i], TString::Format("%02i GeV", energies[i]), "lp");
  }

  TMultiGraph *multi4 = new TMultiGraph();
  TMultiGraph *multi5 = new TMultiGraph();

  TLegend *leg4 = new TLegend(0.3, 0.60, 0.65, 0.9);
  leg4->SetHeader("Mokka ILD_o1_v06, v17-11-p03, Hit level, K_{0}^{L}, cos(#theta) < 0.7");
  leg4->SetNColumns(3);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.028);

  TLegend *leg5 = new TLegend(0.2, 0.55, 0.55, 0.85);
  leg5->SetHeader("Mokka ILD_o1_v06, v17-11-p03, Hit level, K_{0}^{L}, cos(#theta) < 0.7");
  leg5->SetBorderSize(0);
  leg5->SetNColumns(3);
  leg5->SetTextSize(0.035);

  //Fit Resolution curve
  // TF1 *fitReso = new TF1("fitReso", "TMath::Sqrt( TMath::Power([0] / TMath::Sqrt(x[0]), 2) + TMath::Power([1], 2) + TMath::Power([2]/x[0], 2) )");
  TF1 *fitReso = new TF1("fitReso", "TMath::Sqrt( TMath::Power([0] / TMath::Sqrt(x[0]), 2) + TMath::Power([1], 2) )");
  fitReso->SetParameter(0, 50);
  fitReso->SetParameter(1, 3);
  // fitReso->SetParameter(2, 1);

  fitReso->SetParLimits(0, 0, 100);
  fitReso->SetParLimits(1, 1, 20);
  // fitReso->SetParLimits(2, 0, 5);

  fitReso->SetLineColor(colors2[nTime-1]);
  fitReso->SetLineStyle(2);

  gResoCurve[nTime-1]->Fit("fitReso", "QMER", "", 3, 100);
  cout << "Stochastic " << fitReso->GetParameter(0) << " % +/- " << fitReso->GetParError(0) << endl;
  cout << "Constant " << fitReso->GetParameter(1) << " % +/- " << fitReso->GetParError(1) << endl;
  // cout << "Noise " << fitReso->GetParameter(2) << " % +/- " << fitReso->GetParError(2) << endl;

  for(int i = 0; i < nTime; i++)
  {
    multi4->Add(gResoCurve[i]);
    leg4->AddEntry(gResoCurve[i], TString::Format("%i ns", timecuts[i]), "lp");

    multi5->Add(gLinCurve[i]);
    leg5->AddEntry(gLinCurve[i], TString::Format("%i ns", timecuts[i]), "lp");

    multi_res->Add(gResidualLinCurve[i]);
  }

  //----------------------------------------------------------------------------

  TCanvas *c1 = new TCanvas("c1", "Energy vs time cut", 800, 600);
  multi->Draw("APL");
  multi->GetXaxis()->SetTitle("Time Cut [ns]");
  multi->GetYaxis()->SetTitle("Shower Energy [%]");
  leg->Draw("same");

  c1->SaveAs("Plots/ShowerEnergy_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TCanvas *c2 = new TCanvas("c2", "Width vs time cut", 800, 600);
  multi2->Draw("APL");
  multi2->GetXaxis()->SetTitle("Time Cut [ns]");
  multi2->GetYaxis()->SetTitle("Shower Width [%]");
  // multi2->GetYaxis()->SetRangeUser(50, 100);
  leg2->Draw("same");

  c2->SaveAs("Plots/ShowerWidth_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TCanvas *c11 = new TCanvas("c11", "Radial Profile vs time cut", 800, 600);
  multi11->Draw("APL");
  multi11->GetXaxis()->SetTitle("Time Cut [ns]");
  multi11->GetYaxis()->SetTitle("Mean Radial Profile [%]");
  // multi2->GetYaxis()->SetRangeUser(50, 100);
  leg2->Draw("same");

  c11->SaveAs("Plots/RadialProfile_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TCanvas *c12 = new TCanvas("c12", "Radial Profile Abso vs time cut", 800, 600);
  multi12->Draw("APL");
  multi12->GetXaxis()->SetTitle("Time Cut [ns]");
  multi12->GetYaxis()->SetTitle("Mean Radial Profile [mm]");
  // multi12->GetYaxis()->SetTitle("Mean Radial Profile [GeV/mm^{2}]");
  // multi2->GetYaxis()->SetRangeUser(50, 100);
  leg2->Draw("same");

  c12->SaveAs("Plots/RadialProfileAbso_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TCanvas *c6 = new TCanvas("c6", "Width vs time cut", 800, 600);
  multi6->Draw("APL");
  multi6->GetXaxis()->SetTitle("Time Cut [ns]");
  multi6->GetYaxis()->SetTitle("Shower Width [mm]");
  // multi2->GetYaxis()->SetRangeUser(50, 100);
  leg2->Draw("same");

  c6->SaveAs("Plots/ShowerWidthAbso_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TLine *eyeline = new TLine(-1, 1, 100, 1);
  eyeline->SetLineColor(kBlack);
  eyeline->SetLineWidth(2);
  eyeline->SetLineStyle(2);

  TCanvas *c3 = new TCanvas("c3", "Reso vs time cut", 800, 600);
  multi3->Draw("APL");
  multi3->GetXaxis()->SetTitle("Time Cut [ns]");
  multi3->GetYaxis()->SetTitle("Relative Resolution change");
  multi3->GetYaxis()->SetRangeUser(0.7, 1.6);
  multi3->GetXaxis()->SetRangeUser(-1, 100);
  leg3->Draw("same");
  eyeline->Draw("same");

  c3->SaveAs("Plots/ShowerReso_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TCanvas *c4 = new TCanvas("c4", "Resolution curve", 800, 600);
  multi4->Draw("AP");
  multi4->GetXaxis()->SetTitle("Energy [GeV]");
  multi4->GetYaxis()->SetTitle("Resolution [%]");
  multi4->GetXaxis()->SetRangeUser(0, 100);
  multi4->GetYaxis()->SetRangeUser(0, 40);
  leg4->Draw("same");

  c4->SaveAs("Plots/ShowerResoAbsolute_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TF1 *line = new TF1("line", "x", 0, 110);
  line->SetLineColor(kBlack);
  line->SetLineWidth(2);

  //Linearity curve
  double sFactor = 0.60;

  TCanvas *c5;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c5, "c5", "Linearity curve Hit level", pad1, pad2, sFactor, 800, 600);
  pad1->cd();
  multi5->Draw("APL");
  setupAxisScalingTop(multi5, sFactor);
  multi5->GetXaxis()->SetTitle("E_{initial} [GeV]");
  multi5->GetXaxis()->SetRangeUser(0, 100);
  multi5->GetYaxis()->SetTitle("E_{reco} [GeV]");
  multi5->GetYaxis()->SetRangeUser(0, 100);
  line->Draw("same");
  leg5->Draw("same");
  pad2->cd();
  multi_res->Draw("APL");
  setupAxisScalingBottom(multi_res, sFactor);
  multi_res->GetXaxis()->SetTitle("E_{initial} [GeV]");
  multi_res->GetXaxis()->SetRangeUser(0, 100);
  multi_res->GetYaxis()->SetRangeUser(-30, 5);
  multi_res->GetYaxis()->SetTitle("(E_{reco} - E_{initial}) / E_{initial}");
  multi_res->GetYaxis()->SetTitleSize(0.09);
  multi_res->GetYaxis()->SetTitleOffset(0.55);
  multi_res->GetYaxis()->SetNdivisions(005);

  c5->SaveAs("Plots/Linearity_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TCanvas *c10;
  TPad *pad3, *pad4;
  setupPadsTopBottom(c10, "c10", "Shower width vs Reso Hit level", pad3, pad4, sFactor, 800, 600);
  pad3->cd();
  multi10->Draw("APL");
  setupAxisScalingTop(multi10, sFactor);
  multi10->GetXaxis()->SetTitle("Shower width [%]");
  multi10->GetXaxis()->SetRangeUser(0, 100);
  multi10->GetYaxis()->SetTitle("Resolution [%]");
  multi10->GetYaxis()->SetRangeUser(5, 50);
  leg10->Draw("same");
  pad4->cd();
  multi_res2->Draw("APL");
  setupAxisScalingBottom(multi_res2, sFactor);
  multi_res2->GetXaxis()->SetTitle("Shower width [%]");
  multi_res2->GetXaxis()->SetRangeUser(0, 100);
  multi_res2->GetYaxis()->SetRangeUser(-2, 10);
  multi_res2->GetYaxis()->SetTitle("Reso - Reso_{100 ns}");
  multi_res2->GetYaxis()->SetTitleSize(0.09);
  multi_res2->GetYaxis()->SetTitleOffset(0.55);
  multi_res2->GetYaxis()->SetNdivisions(010);

  c10->SaveAs("Plots/ShowerWidth_Resolution_Smearing2.pdf");

  //----------------------------------------------------------------------------

  //Histograms
  for(int i = 0; i < nEnergy; i++)
  {
    for(int j = 0; j < nTime; j++)
    {
      if(i > 1)
      hEnergyHits[i][j]->Scale(1./hEnergyHits[i][j]->GetEntries());
      else
      hEnergyHits[i][j]->Scale(2./hEnergyHits[i][j]->GetEntries());

      hEnergyHits[i][j]->SetLineColor(colors[i]);
      hEnergyHits[i][j]->SetFillColor(colors[i]);
      hEnergyHits[i][j]->SetFillStyle(3002);
      hEnergyHits[i][j]->SetLineWidth(2);
      hEnergyHits[i][j]->GetXaxis()->SetTitle("Energy [GeV]");
      hEnergyHits[i][j]->GetYaxis()->SetTitle("Normalized entries");
    }
  }

  TCanvas *c9 = new TCanvas("c9", "Superposition Shower Hit Energies", 800, 600);
  // gPad->SetLogy();
  for(int i = 0; i < nEnergy; i++)
  {
    hEnergyHits[i][nTime-1]->Draw("same");
    hEnergyHits[i][nTime-1]->GetXaxis()->SetRangeUser(0, 120);
  }

  c9->SaveAs("Plots/HitEnergyHisto_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TLegend *leg99 = new TLegend(0.2, 0.60, 0.4, 0.9);
  leg99->SetHeader("Mokka ILD_o1_v06, v17-11-p03, Hit level, 50 GeV K_{0}^{L}, cos(#theta) < 0.7");
  leg99->SetBorderSize(0);
  leg99->SetTextSize(0.028);
  leg99->AddEntry(hEnergyHits[5][0], "1 ns timing cut", "l");
  leg99->AddEntry(hEnergyHits[5][3], "5 ns timing cut", "l");
  leg99->AddEntry(hEnergyHits[5][7], "20 ns timing cut", "l");
  leg99->AddEntry(hEnergyHits[5][10], "50 ns timing cut", "l");
  leg99->AddEntry(hEnergyHits[5][12], "100 ns timing cut", "l");

  TCanvas *c99 = new TCanvas("c99", "Superposition Shower Hit Energies 50 GeV time cuts", 800, 600);
  // gPad->SetLogy();

  hEnergyHits[5][0]->SetLineColor(kBlack);
  hEnergyHits[5][0]->SetLineWidth(2);
  hEnergyHits[5][0]->SetFillStyle(0);
  hEnergyHits[5][0]->Draw();
  hEnergyHits[5][0]->GetXaxis()->SetTitle("Energy [GeV]");
  hEnergyHits[5][0]->GetYaxis()->SetTitle("Normalized events");
  hEnergyHits[5][0]->GetXaxis()->SetRangeUser(0, 80);
  hEnergyHits[5][0]->GetYaxis()->SetRangeUser(0, 0.1);

  hEnergyHits[5][3]->SetLineColor(kRed);
  hEnergyHits[5][3]->SetLineWidth(2);
  hEnergyHits[5][3]->SetFillStyle(0);
  hEnergyHits[5][3]->Draw("same");

  hEnergyHits[5][7]->SetLineColor(kBlue);
  hEnergyHits[5][7]->SetLineWidth(2);
  hEnergyHits[5][7]->SetFillStyle(0);
  hEnergyHits[5][7]->Draw("same");

  hEnergyHits[5][10]->SetLineColor(kGreen);
  hEnergyHits[5][10]->SetLineWidth(2);
  hEnergyHits[5][10]->SetFillStyle(0);
  hEnergyHits[5][10]->Draw("same");

  hEnergyHits[5][12]->SetLineColor(kOrange);
  hEnergyHits[5][12]->SetLineWidth(2);
  hEnergyHits[5][12]->SetFillStyle(0);
  hEnergyHits[5][12]->Draw("same");
  leg99->Draw("same");

  c99->SaveAs("Plots/HitEnergyHisto_50GeV_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

  //Radial Profile Overlay
  //1ns, 5ns, 10ns and 100 ns
  TLegend *leg13 = new TLegend(0.6, 0.55, 0.9, 0.85);
  leg13->SetBorderSize(0);
  leg13->SetTextSize(0.04);
  leg13->AddEntry(hRadialProfile[5][12], "50 GeV K_{0}^{L}, 100 ns", "l");
  leg13->AddEntry(hRadialProfile[5][5], "50 GeV K_{0}^{L}, 10 ns", "l");
  leg13->AddEntry(hRadialProfile[5][3], "50 GeV K_{0}^{L}, 5 ns", "l");
  leg13->AddEntry(hRadialProfile[5][0], "50 GeV K_{0}^{L}, 1 ns", "l");

  //Radial Ratios
  TH1F* hRadialRatio100 = (TH1F*)hRadialProfile[5][12]->Clone("hRadialRatio100");
  hRadialRatio100->Divide(hRadialProfile[5][12]);
  hRadialRatio100->SetLineColor(kGreen);
  hRadialRatio100->SetLineWidth(2);

  TH1F* hRadialRatio10 = (TH1F*)hRadialProfile[5][5]->Clone("hRadialRatio10");
  hRadialRatio10->Divide(hRadialProfile[5][12]);
  hRadialRatio10->SetLineColor(kBlue);
  hRadialRatio10->SetLineWidth(2);

  TH1F* hRadialRatio5 = (TH1F*)hRadialProfile[5][3]->Clone("hRadialRatio5");
  hRadialRatio5->Divide(hRadialProfile[5][12]);
  hRadialRatio5->SetLineColor(kRed);
  hRadialRatio5->SetLineWidth(2);

  TH1F* hRadialRatio1 = (TH1F*)hRadialProfile[5][0]->Clone("hRadialRatio1");
  hRadialRatio1->Divide(hRadialProfile[5][12]);
  hRadialRatio1->SetLineColor(kBlack);
  hRadialRatio1->SetLineWidth(2);

  TCanvas *c13;
  TPad *pad13, *pad14;
  setupPadsTopBottom(c13, "c13", "Radial Profile Overlay", pad13, pad14, sFactor, 800, 600);
  setupAxisScalingTop(hRadialProfile[5][12], sFactor);
  setupAxisScalingBottom(hRadialRatio100, sFactor);
  pad13->cd();
  gPad->SetLogy();
  hRadialProfile[5][12]->Scale(1. / Nevt[5] );
  hRadialProfile[5][12]->Draw("hist");
  hRadialProfile[5][12]->SetLineColor(kGreen);
  hRadialProfile[5][12]->SetLineWidth(2);
  hRadialProfile[5][12]->GetXaxis()->SetTitle("Hit radius [mm]");
  hRadialProfile[5][12]->GetXaxis()->SetRangeUser(0, 500);
  hRadialProfile[5][12]->GetYaxis()->SetTitle("E_{vis} [GeV/evt#timesmm^{2}]");

  hRadialProfile[5][5]->Scale(1. / Nevt[5] );
  hRadialProfile[5][5]->Draw("hist same");
  hRadialProfile[5][5]->SetLineColor(kBlue);
  hRadialProfile[5][5]->SetLineWidth(2);

  hRadialProfile[5][3]->Scale(1. / Nevt[5] );
  hRadialProfile[5][3]->Draw("hist same");
  hRadialProfile[5][3]->SetLineColor(kRed);
  hRadialProfile[5][3]->SetLineWidth(2);

  hRadialProfile[5][0]->Scale(1. / Nevt[5] );
  hRadialProfile[5][0]->Draw("hist same");
  hRadialProfile[5][0]->SetLineColor(kBlack);
  hRadialProfile[5][0]->SetLineWidth(2);

  leg13->Draw("same");
  pad14->cd();
  hRadialRatio100->Draw("hist");
  hRadialRatio100->GetXaxis()->SetTitle("Hit radius [mm]");
  hRadialRatio100->GetYaxis()->SetTitle("Ratio to 100 ns");
  hRadialRatio100->GetYaxis()->SetRangeUser(0.5, 1.1);
  hRadialRatio100->GetXaxis()->SetRangeUser(0, 500);
  hRadialRatio100->GetYaxis()->SetNdivisions(010);
  hRadialRatio100->GetYaxis()->SetTitleSize(0.1);
  hRadialRatio100->GetYaxis()->SetTitleOffset(0.47);
  hRadialRatio10->Draw("hist same");
  hRadialRatio5->Draw("hist same");
  hRadialRatio1->Draw("hist same");

  c13->SaveAs("Plots/RadialProfileOverlay_Smearing2.pdf");

  //----------------------------------------------------------------------------

  //Hits Radial Profile
  TH1F* hHitsRadialRatio100 = (TH1F*)hHitsRadial[5][12]->Clone("hHitsRadialRatio100");
  hHitsRadialRatio100->Divide(hHitsRadial[5][12]);
  hHitsRadialRatio100->SetLineColor(kGreen);
  hHitsRadialRatio100->SetLineWidth(2);

  TH1F* hHitsRadialRatio10 = (TH1F*)hHitsRadial[5][5]->Clone("hHitsRadialRatio10");
  hHitsRadialRatio10->Divide(hHitsRadial[5][12]);
  hHitsRadialRatio10->SetLineColor(kBlue);
  hHitsRadialRatio10->SetLineWidth(2);

  TH1F* hHitsRadialRatio5 = (TH1F*)hHitsRadial[5][3]->Clone("hHitsRadialRatio5");
  hHitsRadialRatio5->Divide(hHitsRadial[5][12]);
  hHitsRadialRatio5->SetLineColor(kRed);
  hHitsRadialRatio5->SetLineWidth(2);

  TH1F* hHitsRadialRatio1 = (TH1F*)hHitsRadial[5][0]->Clone("hHitsRadialRatio1");
  hHitsRadialRatio1->Divide(hHitsRadial[5][12]);
  hHitsRadialRatio1->SetLineColor(kBlack);
  hHitsRadialRatio1->SetLineWidth(2);

  TCanvas *c14;
  TPad *pad15, *pad16;
  setupPadsTopBottom(c14, "c14", "Hits Radial Profile Overlay", pad15, pad16, sFactor, 800, 600);
  setupAxisScalingTop(hHitsRadial[5][12], sFactor);
  setupAxisScalingBottom(hHitsRadialRatio100, sFactor);
  pad15->cd();
  gPad->SetLogy();
  hHitsRadial[5][12]->Scale(1. / Nevt[5] );
  hHitsRadial[5][12]->Draw("hist");
  hHitsRadial[5][12]->SetLineColor(kGreen);
  hHitsRadial[5][12]->SetLineWidth(2);
  hHitsRadial[5][12]->GetXaxis()->SetTitle("Hit radius [mm]");
  hHitsRadial[5][12]->GetXaxis()->SetRangeUser(0, 500);
  hHitsRadial[5][12]->GetYaxis()->SetTitle("N_{hits} [1/evt#timesmm^{2}]");

  hHitsRadial[5][5]->Scale( 1./ Nevt[5] );
  hHitsRadial[5][5]->Draw("hist same");
  hHitsRadial[5][5]->SetLineColor(kBlue);
  hHitsRadial[5][5]->SetLineWidth(2);

  hHitsRadial[5][3]->Scale( 1./ Nevt[5] );
  hHitsRadial[5][3]->Draw("hist same");
  hHitsRadial[5][3]->SetLineColor(kRed);
  hHitsRadial[5][3]->SetLineWidth(2);

  hHitsRadial[5][0]->Scale( 1./ Nevt[5] );
  hHitsRadial[5][0]->Draw("hist same");
  hHitsRadial[5][0]->SetLineColor(kBlack);
  hHitsRadial[5][0]->SetLineWidth(2);

  leg13->Draw("same");
  pad16->cd();
  hHitsRadialRatio100->Draw("hist");
  hHitsRadialRatio100->GetXaxis()->SetTitle("Hit radius [mm]");
  hHitsRadialRatio100->GetYaxis()->SetTitle("Ratio to 100 ns");
  hHitsRadialRatio100->GetYaxis()->SetRangeUser(0.5, 1.1);
  hHitsRadialRatio100->GetXaxis()->SetRangeUser(0, 500);
  hHitsRadialRatio100->GetYaxis()->SetNdivisions(010);
  hHitsRadialRatio100->GetYaxis()->SetTitleSize(0.1);
  hHitsRadialRatio100->GetYaxis()->SetTitleOffset(0.47);
  hHitsRadialRatio10->Draw("hist same");
  hHitsRadialRatio5->Draw("hist same");
  hHitsRadialRatio1->Draw("hist same");

  c14->SaveAs("Plots/HitsRadialProfileOverlay_Smearing2.pdf");

  //----------------------------------------------------------------------------

  TLegend *leg14 = new TLegend(0.65, 0.65, 0.85, 0.85);
  leg14->SetBorderSize(0);
  leg14->SetTextSize(0.03);
  leg14->AddEntry(hwRadius[5][12], "50 GeV K_{0}^{L}, 100 ns", "l");
  leg14->AddEntry(hwRadius[5][5], "50 GeV K_{0}^{L}, 10 ns", "l");
  leg14->AddEntry(hwRadius[5][3], "50 GeV K_{0}^{L}, 5 ns", "l");
  leg14->AddEntry(hwRadius[5][0], "50 GeV K_{0}^{L}, 1 ns", "l");

  TCanvas *c15 = new TCanvas("c15", "Shower Radius", 800, 600);
  // gPad->SetLogy();
  hwRadius[5][12]->Scale( 1./ hwRadius[5][12]->GetEntries() );
  hwRadius[5][12]->Draw("hist");
  hwRadius[5][12]->GetXaxis()->SetTitle("Shower Radius [mm]");
  hwRadius[5][12]->GetYaxis()->SetTitle("Normalised events");
  hwRadius[5][12]->GetYaxis()->SetRangeUser(0, 0.08);
  hwRadius[5][12]->GetXaxis()->SetRangeUser(0, 600);
  hwRadius[5][12]->SetLineColor(kGreen);
  hwRadius[5][12]->SetLineWidth(2);

  hwRadius[5][5]->Scale( 1./ hwRadius[5][5]->GetEntries() );
  hwRadius[5][5]->Draw("hist same");
  hwRadius[5][5]->SetLineColor(kBlue);
  hwRadius[5][5]->SetLineWidth(2);

  hwRadius[5][3]->Scale( 1./ hwRadius[5][3]->GetEntries() );
  hwRadius[5][3]->Draw("hist same");
  hwRadius[5][3]->SetLineColor(kRed);
  hwRadius[5][3]->SetLineWidth(2);

  hwRadius[5][0]->Scale( 1./ hwRadius[5][0]->GetEntries() );
  hwRadius[5][0]->Draw("hist same");
  hwRadius[5][0]->SetLineColor(kBlack);
  hwRadius[5][0]->SetLineWidth(2);

  leg14->Draw("same");

  c15->SaveAs("Plots/ShowerRadiusOverlay_TimeCuts_Smearing2.pdf");

  //----------------------------------------------------------------------------

}
