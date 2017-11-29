void MakePlots()
{
  CaliceStyle();
  TH1::SetDefaultSumw2(kTRUE);

  TFile *f = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_50GeV_kaon0L_100ns.root", "OPEN");
  TH1F *hNPFO_100ns;

  f->GetObject("hNPFO", hNPFO_100ns);

  TFile *f2 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_50GeV_kaon0L_50ns.root", "OPEN");
  TH1F *hNPFO_50ns;

  f2->GetObject("hNPFO", hNPFO_50ns);

  TFile *f3 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_50GeV_kaon0L_20ns.root", "OPEN");
  TH1F *hNPFO_20ns;

  f3->GetObject("hNPFO", hNPFO_20ns);

  TFile *f4 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_50GeV_kaon0L_5ns.root", "OPEN");
  TH1F *hNPFO_5ns;

  f4->GetObject("hNPFO", hNPFO_5ns);

  TFile *f5 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_50GeV_kaon0L_1ns.root", "OPEN");
  TH1F *hNPFO_1ns;

  f5->GetObject("hNPFO", hNPFO_1ns);

  hNPFO_100ns->SetLineColor(kBlack);
  hNPFO_100ns->SetLineWidth(2);
  hNPFO_100ns->Scale(1./hNPFO_100ns->Integral("width"));

  hNPFO_50ns->SetLineColor(kRed);
  hNPFO_50ns->SetLineWidth(2);
  hNPFO_50ns->Scale(1./hNPFO_50ns->Integral("width"));

  hNPFO_20ns->SetLineColor(kBlue);
  hNPFO_20ns->SetLineWidth(2);
  hNPFO_20ns->Scale(1./hNPFO_20ns->Integral("width"));

  hNPFO_5ns->SetLineColor(kGreen);
  hNPFO_5ns->SetLineWidth(2);
  hNPFO_5ns->Scale(1./hNPFO_5ns->Integral("width"));

  hNPFO_1ns->SetLineColor(kOrange);
  hNPFO_1ns->SetLineWidth(2);
  hNPFO_1ns->Scale(1./hNPFO_1ns->Integral("width"));

  TLegend *leg = new TLegend(0.5, 0.65, 0.9, 0.9);
  leg->SetHeader("Mokka ILD_o1_v06, v17-11-p03, 50 GeV K_{0}^{L}, cos(#theta) < 0.7");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.023);
  leg->AddEntry(hNPFO_100ns, "100 ns time cut", "l");
  leg->AddEntry(hNPFO_50ns, "50 ns time cut", "l");
  leg->AddEntry(hNPFO_20ns, "20 ns time cut", "l");
  leg->AddEntry(hNPFO_5ns, "5 ns time cut", "l");
  leg->AddEntry(hNPFO_1ns, "1 ns time cut", "l");

  TCanvas *c1 = new TCanvas("c1", "Number of PFOs", 800, 600);
  gPad->SetLogy();
  hNPFO_100ns->GetXaxis()->SetRangeUser(0, 15);
  hNPFO_100ns->GetXaxis()->SetTitle("Number of reconstructed PFO");
  hNPFO_100ns->GetYaxis()->SetRangeUser(1e-4, 2);
  hNPFO_100ns->GetYaxis()->SetTitle("Fraction of events");
  hNPFO_100ns->Draw("hist");
  hNPFO_50ns->Draw("hist same");
  hNPFO_20ns->Draw("hist same");
  hNPFO_5ns->Draw("hist same");
  hNPFO_1ns->Draw("hist same");
  leg->Draw("same");

  c1->SaveAs("Plots/NumberReconstructedPFO_TimeCuts_50GeV.pdf");

  //------------------------------------------------

  TH1F *h2ndCluster, *hDistance2ndCluster;

  f->GetObject("hOtherClusterEnergy", h2ndCluster);
  f->GetObject("hDistancetoMainCluster", hDistance2ndCluster);

  h2ndCluster->SetLineWidth(2);
  h2ndCluster->SetLineColor(kBlack);
  h2ndCluster->Scale(1./h2ndCluster->GetEntries());

  hDistance2ndCluster->SetLineWidth(2);
  hDistance2ndCluster->SetLineColor(kBlack);
  hDistance2ndCluster->Scale(1./hDistance2ndCluster->GetEntries());

  cout << h2ndCluster->Integral(h2ndCluster->GetXaxis()->FindBin(0.), h2ndCluster->GetXaxis()->FindBin(20)) << " " << h2ndCluster->Integral(h2ndCluster->GetXaxis()->FindBin(50), h2ndCluster->GetXaxis()->FindBin(100)) << endl;

  TCanvas *c2 = new TCanvas("c2", "Energy of 2nd most energetic cluster", 800, 600);
  gPad->SetLogy();
  // h2ndCluster->Rebin(2);
  h2ndCluster->GetXaxis()->SetTitle("Energy relative to main cluster [%]");
  h2ndCluster->GetYaxis()->SetTitle("Fraction of events / %");
  h2ndCluster->Draw("hist");

  c2->SaveAs("Plots/Energy2ndCluster_100ns_50GeV.pdf");

  cout << hDistance2ndCluster->Integral(hDistance2ndCluster->GetXaxis()->FindBin(0.), hDistance2ndCluster->GetXaxis()->FindBin(400)) << endl;

  TCanvas *c3 = new TCanvas("c3", "Distance of 2nd most energetic cluster to main cluster", 800, 600);
  hDistance2ndCluster->Rebin(2);
  hDistance2ndCluster->GetXaxis()->SetTitle("Distance to main cluster [mm]");
  hDistance2ndCluster->GetXaxis()->SetRangeUser(0, 1000);
  hDistance2ndCluster->GetYaxis()->SetTitle("Fraction of events / 15 mm");
  hDistance2ndCluster->GetYaxis()->SetTitleOffset(1.4);
  hDistance2ndCluster->Draw("hist");

  c3->SaveAs("Plots/Distance2ndCluster_100ns_50GeV.pdf");

  //--------------------------------------------------------
  //--------------------------------------------------------
  //--------------------------------------------------------
  //--------------------------------------------------------
  //--------------------------------------------------------
  //--------------------------------------------------------

  TFile *f6 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_10GeV_kaon0L_100ns.root", "OPEN");
  TFile *f7 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_30GeV_kaon0L_100ns.root", "OPEN");
  TFile *f8 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_80GeV_kaon0L_100ns.root", "OPEN");

  //CAN 028
  TH1F* hEsum, *hEsum_low, *hEsum_high;

  f7->GetObject("hEsum", hEsum);
  f7->GetObject("hEsum_low", hEsum_low);
  f7->GetObject("hEsum_high", hEsum_high);

  hEsum->SetLineWidth(2);
  hEsum->SetLineColor(kBlack);
  hEsum->SetFillColor(kGray);
  // hEsum->SetFillStyle(3001);

  hEsum_low->SetLineWidth(2);
  hEsum_low->SetLineColor(kBlue);
  hEsum_low->SetFillColor(kBlue);

  hEsum_high->SetLineWidth(2);
  hEsum_high->SetLineColor(kRed);
  hEsum_high->SetFillColor(kRed);

  TLegend *leg2 = new TLegend(0.6, 0.7, 0.9, 0.9);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.03);
  leg2->SetHeader("K^{0}_{L} 30 GeV");
  leg2->AddEntry(hEsum_low, "E_{event} < E_{mean} - #sigma", "l");
  leg2->AddEntry(hEsum_high, "E_{event} > E_{mean} + #sigma", "l");

  TCanvas *c4 = new TCanvas("c4", "Energy Sum", 800, 600);
  hEsum->GetXaxis()->SetTitle("E_{reco} [GeV]");
  hEsum->GetXaxis()->SetRangeUser(0, 80);
  hEsum->GetYaxis()->SetTitle("Number of events");
  hEsum->Draw("hist");
  hEsum_low->Draw("hist same");
  hEsum_high->Draw("hist same");
  leg2->Draw("same");

  c4->SaveAs("Plots/EnergySum_100ns_30GeV.pdf");

  //-----------------------------------------------------

  TH1F *hEhit_low_10, *hEhit_high_10;
  TH1F *hEhit_low_30, *hEhit_high_30;
  TH1F *hEhit_low_50, *hEhit_high_50;
  TH1F *hEhit_low_80, *hEhit_high_80;

  f7->GetObject("hEhit_low", hEhit_low_30);
  f7->GetObject("hEhit_high", hEhit_high_30);

  f->GetObject("hEhit_low", hEhit_low_50);
  f->GetObject("hEhit_high", hEhit_high_50);

  f6->GetObject("hEhit_low", hEhit_low_10);
  f6->GetObject("hEhit_high", hEhit_high_10);

  f8->GetObject("hEhit_low", hEhit_low_80);
  f8->GetObject("hEhit_high", hEhit_high_80);

  hEhit_low_10->SetLineWidth(2);
  hEhit_low_10->SetLineColor(kBlue);
  hEhit_low_10->Scale(1./hEhit_low_10->GetEntries());

  hEhit_high_10->SetLineWidth(2);
  hEhit_high_10->SetLineColor(kRed);
  hEhit_high_10->Scale(1./hEhit_high_10->GetEntries());

  hEhit_low_30->SetLineWidth(2);
  hEhit_low_30->SetLineColor(kBlue);
  hEhit_low_30->Scale(1./hEhit_low_30->GetEntries());

  hEhit_high_30->SetLineWidth(2);
  hEhit_high_30->SetLineColor(kRed);
  hEhit_high_30->Scale(1./hEhit_high_30->GetEntries());

  hEhit_low_50->SetLineWidth(2);
  hEhit_low_50->SetLineColor(kBlue);
  hEhit_low_50->Scale(1./hEhit_low_50->GetEntries());

  hEhit_high_50->SetLineWidth(2);
  hEhit_high_50->SetLineColor(kRed);
  hEhit_high_50->Scale(1./hEhit_high_50->GetEntries());

  hEhit_low_80->SetLineWidth(2);
  hEhit_low_80->SetLineColor(kBlue);
  hEhit_low_80->Scale(1./hEhit_low_80->GetEntries());

  hEhit_high_80->SetLineWidth(2);
  hEhit_high_80->SetLineColor(kRed);
  hEhit_high_80->Scale(1./hEhit_high_80->GetEntries());

  //Ratio Red top Blue
  TH1F *hRatio_30 = (TH1F*)hEhit_high_30->Clone("hRatio_30");
  hRatio_30->Divide(hEhit_low_30);
  hRatio_30->GetXaxis()->SetTitle("Hit Energy in HCAL [MIP]");
  hRatio_30->GetYaxis()->CenterTitle();
  hRatio_30->GetYaxis()->SetTitle("Ratio of hit spectra");
  hRatio_30->GetYaxis()->SetNdivisions(505);
  hRatio_30->SetMarkerStyle(20);
  hRatio_30->GetYaxis()->SetTitleSize(0.04);
  hRatio_30->GetYaxis()->SetTitleOffset(1.3);

  TCanvas *c5 = new TCanvas("c5", "Hit Energy Spectra", 800, 600);
  gPad->SetLogy();
  hEhit_low_30->GetXaxis()->SetTitle("Hit Energy in HCAL [MIP]");
  hEhit_low_30->GetXaxis()->SetRangeUser(0, 120);
  hEhit_low_30->GetYaxis()->SetTitle("Normalised entries");
  hEhit_low_30->Draw("hist");
  hEhit_high_30->Draw("hist same");
  leg2->Draw("same");

  c5->SaveAs("Plots/HitEnergySpectra_100ns_30GeV.pdf");

  TLine *line = new TLine(0, 1, 14, 1);
  line->SetLineWidth(2);
  line->SetLineColor(kBlack);

  TLegend *leg3 = new TLegend(0.6, 0.6, 0.9, 0.8);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.04);
  leg3->SetHeader("K^{0}_{L} 30 GeV");
  leg3->AddEntry(hEsum_low, "E_{event} < E_{mean} - #sigma", "l");
  leg3->AddEntry(hEsum_high, "E_{event} > E_{mean} + #sigma", "l");

  float sFactor = 0.6;
  TCanvas *c6;
  TPad *pad1, *pad2;
  setupPadsTopBottom(c6, "c6", "c6", pad1, pad2, sFactor, 800, 600);
  setupAxisScalingTop(hEhit_low_30, sFactor);
  setupAxisScalingBottom(hRatio_30, sFactor);
  pad1->cd();
  hEhit_low_30->GetXaxis()->SetRangeUser(0, 14);
  hEhit_low_30->GetYaxis()->SetTitle("Normalised entries");
  hEhit_low_30->Draw("hist");
  hEhit_high_30->Draw("hist same");
  leg3->Draw("same");
  pad2->cd();
  hRatio_30->GetXaxis()->SetRangeUser(0, 14);
  hRatio_30->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatio_30->Draw("pe");
  line->Draw("same");

  c6->SaveAs("Plots/HitEnergySpectra_Zoom_100ns_30GeV.pdf");

  TH1F *hRatio_10 = (TH1F*)hEhit_high_10->Clone("hRatio_10");
  hRatio_10->Divide(hEhit_low_10);
  hRatio_10->GetXaxis()->SetTitle("Hit Energy in HCAL [MIP]");
  hRatio_10->GetYaxis()->CenterTitle();
  hRatio_10->GetYaxis()->SetTitle("Ratio of hit spectra");
  hRatio_10->GetYaxis()->SetNdivisions(505);
  hRatio_10->SetMarkerStyle(20);
  hRatio_10->GetYaxis()->SetTitleSize(0.04);
  hRatio_10->GetYaxis()->SetTitleOffset(1.3);

  TLegend *leg4 = new TLegend(0.6, 0.6, 0.9, 0.8);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.04);
  leg4->SetHeader("K^{0}_{L} 10 GeV");
  leg4->AddEntry(hEsum_low, "E_{event} < E_{mean} - #sigma", "l");
  leg4->AddEntry(hEsum_high, "E_{event} > E_{mean} + #sigma", "l");

  TCanvas *c6_1;
  TPad *pad3, *pad4;
  setupPadsTopBottom(c6_1, "c6_1", "c6_1", pad3, pad4, sFactor, 800, 600);
  setupAxisScalingTop(hEhit_low_10, sFactor);
  setupAxisScalingBottom(hRatio_10, sFactor);
  pad3->cd();
  hEhit_low_10->GetXaxis()->SetRangeUser(0, 14);
  hEhit_low_10->GetYaxis()->SetTitle("Normalised entries");
  hEhit_low_10->Draw("hist");
  hEhit_high_10->Draw("hist same");
  leg4->Draw("same");
  pad4->cd();
  hRatio_10->GetXaxis()->SetRangeUser(0, 14);
  hRatio_10->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatio_10->Draw("pe");
  line->Draw("same");

  c6_1->SaveAs("Plots/HitEnergySpectra_Zoom_100ns_10GeV.pdf");

  TH1F *hRatio_50 = (TH1F*)hEhit_high_50->Clone("hRatio_50");
  hRatio_50->Divide(hEhit_low_10);
  hRatio_50->GetXaxis()->SetTitle("Hit Energy in HCAL [MIP]");
  hRatio_50->GetYaxis()->CenterTitle();
  hRatio_50->GetYaxis()->SetTitle("Ratio of hit spectra");
  hRatio_50->GetYaxis()->SetNdivisions(505);
  hRatio_50->SetMarkerStyle(20);
  hRatio_50->GetYaxis()->SetTitleSize(0.04);
  hRatio_50->GetYaxis()->SetTitleOffset(1.3);

  TLegend *leg5 = new TLegend(0.6, 0.6, 0.9, 0.8);
  leg5->SetBorderSize(0);
  leg5->SetTextSize(0.04);
  leg5->SetHeader("K^{0}_{L} 50 GeV");
  leg5->AddEntry(hEsum_low, "E_{event} < E_{mean} - #sigma", "l");
  leg5->AddEntry(hEsum_high, "E_{event} > E_{mean} + #sigma", "l");

  TCanvas *c6_2;
  TPad *pad5, *pad6;
  setupPadsTopBottom(c6_2, "c6_2", "c6_2", pad5, pad6, sFactor, 800, 600);
  setupAxisScalingTop(hEhit_low_50, sFactor);
  setupAxisScalingBottom(hRatio_50, sFactor);
  pad5->cd();
  hEhit_low_50->GetXaxis()->SetRangeUser(0, 14);
  hEhit_low_50->GetYaxis()->SetTitle("Normalised entries");
  hEhit_low_50->Draw("hist");
  hEhit_high_50->Draw("hist same");
  leg5->Draw("same");
  pad6->cd();
  hRatio_50->GetXaxis()->SetRangeUser(0, 14);
  hRatio_50->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatio_50->Draw("pe");
  line->Draw("same");

  c6_2->SaveAs("Plots/HitEnergySpectra_Zoom_100ns_50GeV.pdf");

  TH1F *hRatio_80 = (TH1F*)hEhit_high_80->Clone("hRatio_80");
  hRatio_80->Divide(hEhit_low_10);
  hRatio_80->GetXaxis()->SetTitle("Hit Energy in HCAL [MIP]");
  hRatio_80->GetYaxis()->CenterTitle();
  hRatio_80->GetYaxis()->SetTitle("Ratio of hit spectra");
  hRatio_80->GetYaxis()->SetNdivisions(505);
  hRatio_80->SetMarkerStyle(20);
  hRatio_80->GetYaxis()->SetTitleSize(0.04);
  hRatio_80->GetYaxis()->SetTitleOffset(1.3);

  TLegend *leg6 = new TLegend(0.6, 0.6, 0.9, 0.8);
  leg6->SetBorderSize(0);
  leg6->SetTextSize(0.04);
  leg6->SetHeader("K^{0}_{L} 80 GeV");
  leg6->AddEntry(hEsum_low, "E_{event} < E_{mean} - #sigma", "l");
  leg6->AddEntry(hEsum_high, "E_{event} > E_{mean} + #sigma", "l");

  TCanvas *c6_3;
  TPad *pad7, *pad8;
  setupPadsTopBottom(c6_3, "c6_3", "c6_3", pad7, pad8, sFactor, 800, 600);
  setupAxisScalingTop(hEhit_low_80, sFactor);
  setupAxisScalingBottom(hRatio_80, sFactor);
  pad7->cd();
  hEhit_low_80->GetXaxis()->SetRangeUser(0, 14);
  hEhit_low_80->GetYaxis()->SetTitle("Normalised entries");
  hEhit_low_80->Draw("hist");
  hEhit_high_80->Draw("hist same");
  leg6->Draw("same");
  pad8->cd();
  hRatio_80->GetXaxis()->SetRangeUser(0, 14);
  hRatio_80->GetYaxis()->SetRangeUser(0.5, 1.5);
  hRatio_80->Draw("pe");
  line->Draw("same");

  c6_3->SaveAs("Plots/HitEnergySpectra_Zoom_100ns_80GeV.pdf");

  //------------------------------------------

  TH1F *hCLim1_10, *hCLim2_10, *hCLim3_10;
  TH1F *hCLim1_80, *hCLim2_80, *hCLim3_80;

  f6->GetObject("hCLim1", hCLim1_10);
  f6->GetObject("hCLim2", hCLim2_10);
  f6->GetObject("hCLim3", hCLim3_10);

  f8->GetObject("hCLim1", hCLim1_80);
  f8->GetObject("hCLim2", hCLim2_80);
  f8->GetObject("hCLim3", hCLim3_80);

  hCLim1_10->SetLineWidth(2);
  hCLim1_10->SetLineColor(kGreen+2);

  hCLim2_10->SetLineWidth(2);
  hCLim2_10->SetLineColor(kBlue);

  hCLim3_10->SetLineWidth(2);
  hCLim3_10->SetLineColor(kRed);

  hCLim1_80->SetLineWidth(2);
  hCLim1_80->SetLineColor(kGreen+2);

  hCLim2_80->SetLineWidth(2);
  hCLim2_80->SetLineColor(kBlue);

  hCLim3_80->SetLineWidth(2);
  hCLim3_80->SetLineColor(kRed);

  TLegend *leg7 = new TLegend(0.7, 0.7, 0.9, 0.9);
  leg7->SetBorderSize(0);
  leg7->SetTextSize(0.03);
  leg7->SetHeader("K^{0}_{L} 10 GeV / e^{lim}");
  leg7->AddEntry(hCLim1_10, "2.5 MIP", "l");
  leg7->AddEntry(hCLim2_10, "3.5 MIP", "l");
  leg7->AddEntry(hCLim3_10, "4.5 MIP", "l");

  TCanvas *c7 = new TCanvas("c7", "CLim 10 GeV", 800, 600);
  // gPad->SetLogy();
  hCLim1_10->GetXaxis()->SetTitle("C^{Lim}");
  hCLim1_10->GetXaxis()->SetRangeUser(0.4, 1.01);
  hCLim1_10->GetYaxis()->SetRangeUser(0, 800);
  hCLim1_10->GetYaxis()->SetTitle("Number of events");
  hCLim1_10->Draw("hist");
  hCLim2_10->Draw("hist same");
  hCLim3_10->Draw("hist same");
  leg7->Draw("same");

  c7->SaveAs("Plots/CLim_100ns_10GeV.pdf");

  TLegend *leg8 = new TLegend(0.7, 0.7, 0.9, 0.9);
  leg8->SetBorderSize(0);
  leg8->SetTextSize(0.03);
  leg8->SetHeader("K^{0}_{L} 80 GeV / e^{lim}");
  leg8->AddEntry(hCLim1_80, "2.5 MIP", "l");
  leg8->AddEntry(hCLim2_80, "3.5 MIP", "l");
  leg8->AddEntry(hCLim3_80, "4.5 MIP", "l");

  TCanvas *c7_1 = new TCanvas("c7_1", "CLim 80 GeV", 800, 600);
  // gPad->SetLogy();
  hCLim1_80->GetXaxis()->SetTitle("C^{Lim}");
  hCLim1_80->GetXaxis()->SetRangeUser(0.4, 1.01);
  hCLim1_80->GetYaxis()->SetRangeUser(0, 1500);
  hCLim1_80->GetYaxis()->SetTitle("Number of events");
  hCLim1_80->Draw("hist");
  hCLim2_80->Draw("hist same");
  hCLim3_80->Draw("hist same");
  leg8->Draw("same");

  c7_1->SaveAs("Plots/CLim_100ns_80GeV.pdf");

  //-----------------------------------------

  TH1F *hCLimCav_10, *hCLimCav_30, *hCLimCav_50, *hCLimCav_80;

  f->GetObject("hCLimCav2", hCLimCav_50);
  f6->GetObject("hCLimCav2", hCLimCav_10);
  f7->GetObject("hCLimCav2", hCLimCav_30);
  f8->GetObject("hCLimCav2", hCLimCav_80);

  hCLimCav_10->SetLineWidth(2);
  hCLimCav_10->SetLineColor(kViolet);
  hCLimCav_10->Scale(1./hCLimCav_10->GetEntries());

  hCLimCav_30->SetLineWidth(2);
  hCLimCav_30->SetLineColor(kGreen+2);
  hCLimCav_30->Scale(1./hCLimCav_30->GetEntries());

  hCLimCav_50->SetLineWidth(2);
  hCLimCav_50->SetLineColor(kBlue);
  hCLimCav_50->Scale(1./hCLimCav_50->GetEntries());

  hCLimCav_80->SetLineWidth(2);
  hCLimCav_80->SetLineColor(kRed);
  hCLimCav_80->Scale(1./hCLimCav_80->GetEntries());

  TLegend *leg9 = new TLegend(0.7, 0.6, 0.9, 0.9);
  leg9->SetBorderSize(0);
  leg9->SetTextSize(0.03);
  leg9->SetHeader("e^{lim} 3.5 MIP");
  leg9->AddEntry(hCLimCav_10, "K^{0}_{L} 10 GeV", "l");
  leg9->AddEntry(hCLimCav_30, "K^{0}_{L} 30 GeV", "l");
  leg9->AddEntry(hCLimCav_50, "K^{0}_{L} 50 GeV", "l");
  leg9->AddEntry(hCLimCav_80, "K^{0}_{L} 80 GeV", "l");

  TCanvas *c8 = new TCanvas("c8", "CLimCav", 800, 600);
  // gPad->SetLogy();
  hCLimCav_10->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hCLimCav_10->GetXaxis()->SetRangeUser(0.6, 1.3);
  hCLimCav_10->GetYaxis()->SetRangeUser(0, 0.21);
  hCLimCav_10->GetYaxis()->SetTitle("Normalised entries");
  hCLimCav_10->Draw("hist");
  hCLimCav_30->Draw("hist same");
  hCLimCav_50->Draw("hist same");
  hCLimCav_80->Draw("hist same");
  leg9->Draw("same");

  c8->SaveAs("Plots/CLimCav_100ns_SeveralEnergies.pdf");

  //------------------------------------------

  TH2F *hEloss_CLimCav_10, *hEloss_CLimCav_30, *hEloss_CLimCav_80;

  f6->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_10);
  f7->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_30);
  f8->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_80);

  TPaveText *pt = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("K^{0}_{L} 10 GeV, 100 ns");

  TCanvas *c9 = new TCanvas("c9", "hEloss_CLimCav 10 GeV", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_10->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_10->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_10->GetYaxis()->SetRangeUser(0, 20);
  hEloss_CLimCav_10->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_10->Draw("colz");
  pt->Draw("same");

  c9->SaveAs("Plots/EhcalCLimCav_100ns_10GeV.pdf");

  TPaveText *pt2 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("K^{0}_{L} 30 GeV, 100 ns");

  TCanvas *c9_1 = new TCanvas("c9_1", "hEloss_CLimCav 30 GeV", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_30->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_30->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_30->GetYaxis()->SetRangeUser(5, 50);
  hEloss_CLimCav_30->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_30->Draw("colz");
  pt2->Draw("same");

  c9_1->SaveAs("Plots/EhcalCLimCav_100ns_30GeV.pdf");

  TPaveText *pt3 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt3->SetBorderSize(0);
  pt3->SetTextColor(15);
  pt3->SetFillColor(0);
  pt3->SetTextSize(0.04);
  pt3->SetTextAlign(13); //left center
  pt3->AddText("K^{0}_{L} 80 GeV, 100 ns");

  TCanvas *c9_2 = new TCanvas("c9_2", "hEloss_CLimCav 80 GeV", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_80->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_80->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_80->GetYaxis()->SetRangeUser(30, 110);
  hEloss_CLimCav_80->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_80->Draw("colz");
  pt3->Draw("same");

  c9_2->SaveAs("Plots/EhcalCLimCav_100ns_80GeV.pdf");

  //------------------------------------------------------
  //Timing Cut 5 ns

  TH2F *hEloss_CLimCav_10_5ns, *hEloss_CLimCav_30_5ns, *hEloss_CLimCav_80_5ns;

  TFile *f9 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_10GeV_kaon0L_5ns.root", "OPEN");
  TFile *f10 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_30GeV_kaon0L_5ns.root", "OPEN");
  TFile *f11 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_80GeV_kaon0L_5ns.root", "OPEN");

  f9->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_10_5ns);
  f10->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_30_5ns);
  f11->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_80_5ns);

  TPaveText *pt4 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt4->SetBorderSize(0);
  pt4->SetTextColor(15);
  pt4->SetFillColor(0);
  pt4->SetTextSize(0.04);
  pt4->SetTextAlign(13); //left center
  pt4->AddText("K^{0}_{L} 10 GeV, 5 ns");

  TCanvas *c10 = new TCanvas("c10", "hEloss_CLimCav 10 GeV 5ns", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_10_5ns->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_10_5ns->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_10_5ns->GetYaxis()->SetRangeUser(0, 20);
  hEloss_CLimCav_10_5ns->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_10_5ns->Draw("colz");
  pt4->Draw("same");

  c10->SaveAs("Plots/EhcalCLimCav_5ns_10GeV.pdf");

  TPaveText *pt5 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt5->SetBorderSize(0);
  pt5->SetTextColor(15);
  pt5->SetFillColor(0);
  pt5->SetTextSize(0.04);
  pt5->SetTextAlign(13); //left center
  pt5->AddText("K^{0}_{L} 30 GeV, 5 ns");

  TCanvas *c10_1 = new TCanvas("c10_1", "hEloss_CLimCav 30 GeV 5ns", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_30_5ns->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_30_5ns->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_30_5ns->GetYaxis()->SetRangeUser(5, 50);
  hEloss_CLimCav_30_5ns->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_30_5ns->Draw("colz");
  pt5->Draw("same");

  c10_1->SaveAs("Plots/EhcalCLimCav_5ns_30GeV.pdf");

  TPaveText *pt6 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt6->SetBorderSize(0);
  pt6->SetTextColor(15);
  pt6->SetFillColor(0);
  pt6->SetTextSize(0.04);
  pt6->SetTextAlign(13); //left center
  pt6->AddText("K^{0}_{L} 80 GeV, 5 ns");

  TCanvas *c10_2 = new TCanvas("c10_2", "hEloss_CLimCav 80 GeV 5ns", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_80_5ns->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_80_5ns->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_80_5ns->GetYaxis()->SetRangeUser(30, 110);
  hEloss_CLimCav_80_5ns->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_80_5ns->Draw("colz");
  pt6->Draw("same");

  c10_2->SaveAs("Plots/EhcalCLimCav_5ns_80GeV.pdf");

  //------------------------------------

  TH2F *hEloss_CLimCav_10_1ns, *hEloss_CLimCav_30_1ns, *hEloss_CLimCav_80_1ns;

  TFile *f12 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_10GeV_kaon0L_1ns.root", "OPEN");
  TFile *f13 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_30GeV_kaon0L_1ns.root", "OPEN");
  TFile *f14 = new TFile("Rootfiles/AdditionalPlots_ILD_o1_v06_80GeV_kaon0L_1ns.root", "OPEN");

  f9->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_10_1ns);
  f10->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_30_1ns);
  f11->GetObject("hEhcal_CLimCav2", hEloss_CLimCav_80_1ns);

  TPaveText *pt4_1 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt4_1->SetBorderSize(0);
  pt4_1->SetTextColor(15);
  pt4_1->SetFillColor(0);
  pt4_1->SetTextSize(0.04);
  pt4_1->SetTextAlign(13); //left center
  pt4_1->AddText("K^{0}_{L} 10 GeV, 1 ns");

  TCanvas *c10_3 = new TCanvas("c10_3", "hEloss_CLimCav 10 GeV 1ns", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_10_1ns->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_10_1ns->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_10_1ns->GetYaxis()->SetRangeUser(0, 20);
  hEloss_CLimCav_10_1ns->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_10_1ns->Draw("colz");
  pt4_1->Draw("same");

  c10_3->SaveAs("Plots/EhcalCLimCav_1ns_10GeV.pdf");

  TPaveText *pt5_1 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt5_1->SetBorderSize(0);
  pt5_1->SetTextColor(15);
  pt5_1->SetFillColor(0);
  pt5_1->SetTextSize(0.04);
  pt5_1->SetTextAlign(13); //left center
  pt5_1->AddText("K^{0}_{L} 30 GeV, 1 ns");

  TCanvas *c10_4 = new TCanvas("c10_4", "hEloss_CLimCav 30 GeV 1ns", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_30_1ns->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_30_1ns->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_30_1ns->GetYaxis()->SetRangeUser(5, 50);
  hEloss_CLimCav_30_1ns->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_30_1ns->Draw("colz");
  pt5_1->Draw("same");

  c10_4->SaveAs("Plots/EhcalCLimCav_1ns_30GeV.pdf");

  TPaveText *pt6_1 = new TPaveText(0.65, 0.85, 0.8, 0.9, "tbNDC");
  pt6_1->SetBorderSize(0);
  pt6_1->SetTextColor(15);
  pt6_1->SetFillColor(0);
  pt6_1->SetTextSize(0.04);
  pt6_1->SetTextAlign(13); //left center
  pt6_1->AddText("K^{0}_{L} 80 GeV, 1 ns");

  TCanvas *c10_5 = new TCanvas("c10_5", "hEloss_CLimCav 80 GeV 1ns", 800, 600);
  // gPad->SetLogy();
  hEloss_CLimCav_80_1ns->GetXaxis()->SetTitle("C^{Lim}/C^{av}");
  hEloss_CLimCav_80_1ns->GetXaxis()->SetRangeUser(0.6, 1.3);
  hEloss_CLimCav_80_1ns->GetYaxis()->SetRangeUser(30, 110);
  hEloss_CLimCav_80_1ns->GetYaxis()->SetTitle("E_{HCAL} [GeV]");
  hEloss_CLimCav_80_1ns->Draw("colz");
  pt6_1->Draw("same");

  c10_5->SaveAs("Plots/EhcalCLimCav_1ns_80GeV.pdf");

  //--------------------------------------------

  TH1F *hHitEnergy_80_100ns, *hHitEnergy_80_5ns, *hHitEnergy_80_1ns;

  f8->GetObject("hHitEnergy", hHitEnergy_80_100ns);
  f11->GetObject("hHitEnergy", hHitEnergy_80_5ns);
  f14->GetObject("hHitEnergy", hHitEnergy_80_1ns);

  hHitEnergy_80_100ns->SetLineColor(kBlue);
  hHitEnergy_80_100ns->SetLineWidth(2);
  hHitEnergy_80_100ns->Scale(1./hHitEnergy_80_100ns->GetEntries());

  hHitEnergy_80_5ns->SetLineColor(kRed);
  hHitEnergy_80_5ns->SetLineWidth(2);
  hHitEnergy_80_5ns->Scale(1./hHitEnergy_80_5ns->GetEntries());

  hHitEnergy_80_1ns->SetLineColor(kViolet);
  hHitEnergy_80_1ns->SetLineWidth(2);
  hHitEnergy_80_1ns->Scale(1./hHitEnergy_80_1ns->GetEntries());

  //Ratio Blue to Red
  TH1F *hHitEnergyRatio_80_5ns = (TH1F*)hHitEnergy_80_5ns->Clone("hHitEnergyRatio_80_5ns");
  hHitEnergyRatio_80_5ns->Divide(hHitEnergy_80_100ns);
  hHitEnergyRatio_80_5ns->GetXaxis()->SetTitle("Hit Energy [MIP]");
  hHitEnergyRatio_80_5ns->GetYaxis()->CenterTitle();
  hHitEnergyRatio_80_5ns->GetYaxis()->SetTitle("Ratio to 100 ns");
  hHitEnergyRatio_80_5ns->GetYaxis()->SetTitleSize(0.04);
  hHitEnergyRatio_80_5ns->GetYaxis()->SetTitleOffset(1.3);
  hHitEnergyRatio_80_5ns->GetYaxis()->SetNdivisions(505);
  hHitEnergyRatio_80_5ns->SetMarkerStyle(20);

  TH1F *hHitEnergyRatio_80_1ns = (TH1F*)hHitEnergy_80_1ns->Clone("hHitEnergyRatio_80_1ns");
  hHitEnergyRatio_80_1ns->Divide(hHitEnergy_80_100ns);
  hHitEnergyRatio_80_1ns->GetXaxis()->SetTitle("Hit Energy [MIP]");
  hHitEnergyRatio_80_1ns->GetYaxis()->CenterTitle();
  hHitEnergyRatio_80_1ns->GetYaxis()->SetTitle("Ratio to 100 ns");
  hHitEnergyRatio_80_1ns->GetYaxis()->SetTitleSize(0.04);
  hHitEnergyRatio_80_1ns->GetYaxis()->SetTitleOffset(1.3);
  hHitEnergyRatio_80_1ns->GetYaxis()->SetNdivisions(505);
  hHitEnergyRatio_80_1ns->SetMarkerStyle(20);

  TLine *line_Elim = new TLine(3.5, 0.5, 3.5, 1.5);
  line_Elim->SetLineWidth(2);
  line_Elim->SetLineStyle(2);
  line_Elim->SetLineColor(kGreen+2);

  TLegend *leg10 = new TLegend(0.7, 0.5, 0.9, 0.8);
  leg10->SetBorderSize(0);
  leg10->SetTextSize(0.04);
  leg10->SetHeader("K^{0}_{L} 80 GeV");
  leg10->AddEntry(line_Elim, "elim 3.5 MIP", "l");
  leg10->AddEntry(hHitEnergy_80_100ns, "100 ns", "l");
  leg10->AddEntry(hHitEnergy_80_5ns, "5 ns", "l");
  leg10->AddEntry(hHitEnergy_80_1ns, "1 ns", "l");

  TCanvas *c11;
  TPad *pad20, *pad21;
  setupPadsTopBottom(c11, "c11", "c11", pad20, pad21, sFactor, 800, 600);
  setupAxisScalingTop(hHitEnergy_80_100ns, sFactor);
  setupAxisScalingBottom(hHitEnergyRatio_80_5ns, sFactor);
  pad20->cd();
  gPad->SetLogy();
  hHitEnergy_80_100ns->GetXaxis()->SetTitle("Hit Energy [MIP]");
  hHitEnergy_80_100ns->GetXaxis()->SetRangeUser(0, 14);
  hHitEnergy_80_100ns->GetYaxis()->SetTitle("Normalised entries");
  hHitEnergy_80_100ns->Draw("hist");
  hHitEnergy_80_5ns->Draw("hist same");
  hHitEnergy_80_1ns->Draw("hist same");
  leg10->Draw("same");
  pad21->cd();
  hHitEnergyRatio_80_5ns->GetXaxis()->SetRangeUser(0, 14);
  hHitEnergyRatio_80_5ns->GetYaxis()->SetRangeUser(0.5, 1.5);
  hHitEnergyRatio_80_5ns->Draw("pe");
  hHitEnergyRatio_80_1ns->Draw("pe same");
  line->Draw("same");
  line_Elim->Draw("same");

  c11->SaveAs("Plots/HitEnergySpectra_80GeV.pdf");

}
