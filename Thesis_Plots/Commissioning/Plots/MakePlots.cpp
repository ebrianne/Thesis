void DCR()
{
  CaliceStyle();

  //--------------------- DCR ------------------------------------------

  TFile *f = new TFile("Rootfiles/SM_1_DCR.root", "OPEN");
  TH1I *h;

  f->GetObject("hFilledMem_Chip241_Thr210_Time3000", h);

  h->SetLineColor(kBlack);
  h->SetLineWidth(2);

  TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
  leg->AddEntry(h, "Chip 241 (Thr. 210, 3 ms)", "l");
  leg->AddEntry(h->GetFunction("poissonfit"), "Poisson Fit", "l");

  cout << h->GetFunction("poissonfit")->GetParameter(1) << " +/- " << h->GetFunction("poissonfit")->GetParError(1) << endl;

  TCanvas *c1 = new TCanvas("c1", "Mem filled", 800, 600);
  h->GetXaxis()->SetTitle("Number of memory cells filled");
  h->GetYaxis()->SetTitle("Number of cycles");
  h->Draw();
  leg->Draw("same");

  c1->SaveAs("Plots/NumberMemFilled_Poisson.pdf");

  TCanvas *c2;
  f->GetObject("c1", c2);

  c2->SetTitle("c2");
  c2->SetName("c2");

  TGraphErrors *graph[4];
  graph[0] = (TGraphErrors*)c2->GetPrimitive("Noise_rate_Chip241");
  graph[1] = (TGraphErrors*)c2->GetPrimitive("Noise_rate_Chip242");
  graph[2] = (TGraphErrors*)c2->GetPrimitive("Noise_rate_Chip243");
  graph[3] = (TGraphErrors*)c2->GetPrimitive("Noise_rate_Chip244");

  graph[0]->SetLineWidth(2);
  graph[0]->SetLineColor(kBlue);
  graph[0]->SetMarkerColor(kBlue);
  graph[0]->SetMarkerStyle(20);

  graph[1]->SetLineWidth(2);
  graph[1]->SetLineColor(kGreen);
  graph[1]->SetMarkerColor(kGreen);
  graph[1]->SetMarkerStyle(20);

  graph[2]->SetLineWidth(2);
  graph[2]->SetLineColor(kRed);
  graph[2]->SetMarkerColor(kRed);
  graph[2]->SetMarkerStyle(20);

  graph[3]->SetLineWidth(2);
  graph[3]->SetLineColor(kOrange+2);
  graph[3]->SetMarkerColor(kOrange+2);
  graph[3]->SetMarkerStyle(20);

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(graph[0]);
  multi->Add(graph[1]);
  multi->Add(graph[2]);
  multi->Add(graph[3]);

  TLegend *leg2 = new TLegend(0.6, 0.7, 0.9, 0.9);
  leg2->AddEntry(graph[0], "Chip 241", "l");
  leg2->AddEntry(graph[1], "Chip 242", "l");
  leg2->AddEntry(graph[2], "Chip 243", "l");
  leg2->AddEntry(graph[3], "Chip 244", "l");
  leg2->SetTextSize(0.025);

  TCanvas *c3 = new TCanvas("c3", "Final", 800, 600);
  gPad->SetLogy();
  multi->Draw("AX");
  multi->GetXaxis()->SetTitle("Trigger Threshold setting");
  multi->GetYaxis()->SetTitle("Noise rate [Hz]");
  multi->Draw("PXL");
  leg2->Draw("same");

  c3->SaveAs("Plots/NoiseMeasurement_SM1.pdf");
}

void ChipTesting()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Chip_testing.root", "OPEN");
  TMultiGraph *graph;
  f->GetObject("IDAC/Chip_16/IDAC curve chip 16", graph);

  TIter next(graph->GetListOfGraphs());
  TObject *obj;
  int i = 1;
  while ((obj = next()))
  {
    if(i == 15)
    i = 20;

    TGraphErrors *tmp = (TGraphErrors*)obj;
    tmp->SetLineWidth(2);
    tmp->SetLineColor(i);
    tmp->SetMarkerStyle(20);
    tmp->SetMarkerColor(kBlack);
    i++;
  }

  TPaveText *pt2 = new TPaveText(0.70, 0.80, 0.9, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Chip 16");
  pt2->AddText("Input DACs");

  TCanvas *c1 = new TCanvas("c1", "IDACs chip 16", 800, 600);
  graph->Draw("A");
  graph->GetXaxis()->SetTitle("IDAC value");
  graph->GetYaxis()->SetTitle("IDAC voltage [V]");
  graph->Draw("PL");
  pt2->Draw("same");

  c1->SaveAs("Plots/IDACs_Chip16.pdf");

  //----------------------------------

  TGraphErrors *graph2;
  f->GetObject("OutDAC/Output DACs Gain selection chip 16", graph2);

  graph2->SetLineWidth(2);
  graph2->SetLineColor(kBlack);
  graph2->SetMarkerStyle(20);
  graph2->SetMarkerColor(kBlack);

  TPaveText *pt3 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt3->SetBorderSize(0);
  pt3->SetTextColor(15);
  pt3->SetFillColor(0);
  pt3->SetTextSize(0.04);
  pt3->SetTextAlign(13); //left center
  pt3->AddText("CALICE AHCAL");
  pt3->AddText("Chip 16");
  pt3->AddText("Output DACs");

  TCanvas *c2 = new TCanvas("c2", "OutDAC chip 16", 800, 600);
  graph2->GetXaxis()->SetTitle("Output DAC value");
  graph2->GetYaxis()->SetTitle("Output DAC voltage [V]");
  graph2->Draw("APLX");
  pt3->Draw("same");

  c2->SaveAs("Plots/OutDACs_Chip16.pdf");
}

void Commissioning()
{
  CaliceStyle();
  TFile *f = new TFile("Rootfiles/HBU2_15_Holdscan.root", "OPEN");
  TMultiGraph *multi;
  f->cd("graph");

  TIter next(gDirectory->GetListOfKeys());
  TKey *key;
  int i = 1;
  while( (key = (TKey*)next()) )
  {
    if(i == 2)
    multi = (TMultiGraph*)key->ReadObj();

    i++;
  }

  TIter next2(multi->GetListOfGraphs());
  TObject *obj;
  i = 0;
  int color = 1;
  while ((obj = next2()))
  {
    if(i > 10)
    {
      i = 0;
      color++;
    }

    TGraphErrors *tmp = (TGraphErrors*)obj;
    tmp->SetLineWidth(2);
    // tmp->SetLineColor(color);
    tmp->SetMarkerStyle(20);
    // tmp->SetMarkerColor(kBlack);
    i++;
  }

  TLine *line = new TLine(30, 200, 30, 3500);
  line->SetLineWidth(2);
  line->SetLineStyle(2);
  line->SetLineColor(kRed);

  TCanvas *c1 = new TCanvas("c1", "Holdscan", 800, 600);
  multi->Draw("A");
  multi->GetXaxis()->SetTitle("Hold time [ns]");
  multi->GetYaxis()->SetTitle("Amplitude [ADC]");
  multi->GetYaxis()->SetTitleOffset(1.2);
  multi->GetYaxis()->SetRangeUser(200, 3500);
  multi->Draw("PL");
  line->Draw("same");

  c1->SaveAs("Plots/Holdscan_HBU2_15.pdf");

  //--------------------------------

  TFile *f2 = new TFile("Rootfiles/Mainz_HBU4_Gain100fF.root", "OPEN");
  TH1F* h;
  f2->GetObject("z_ADC_chip193_chn25_5900mV", h);

  gStyle->SetOptStat(1110);
  gStyle->SetStatY(0.9);
  gStyle->SetStatX(0.9);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  h->SetStats(kTRUE);

  h->SetLineWidth(2);

  TPaveText *pt2 = new TPaveText(0.60, 0.50, 0.8, 0.72, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Chip 193 Chn 25");
  pt2->AddText("Gain: 36.41 ADC/px");

  TCanvas *c2 = new TCanvas("c2", "Gain 100 fF", 800, 600);
  h->Draw();
  h->GetXaxis()->SetTitle("Amplitude [ADC]");
  h->GetYaxis()->SetTitle("Number of entries");
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetRangeUser(200, 500);
  pt2->Draw("same");

  c2->SaveAs("Plots/Gain100fF_MainzHBU4.pdf");

  //---------------------------------------

  TFile *f3 = new TFile("Rootfiles/Mainz_HBU4_Gain675fF.root", "OPEN");
  TH1F* h3;
  f3->GetObject("z_ADC_chip193_chn25_6100mV", h3);

  gStyle->SetOptStat(1110);
  gStyle->SetStatY(0.9);
  gStyle->SetStatX(0.9);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);
  h3->SetStats(kTRUE);

  h3->SetLineWidth(2);

  TPaveText *pt3 = new TPaveText(0.60, 0.50, 0.8, 0.72, "tbNDC");
  pt3->SetBorderSize(0);
  pt3->SetTextColor(15);
  pt3->SetFillColor(0);
  pt3->SetTextSize(0.04);
  pt3->SetTextAlign(13); //left center
  pt3->AddText("CALICE AHCAL");
  pt3->AddText("Chip 193 Chn 25");
  pt3->AddText("Gain: 11.38 ADC/px");

  TCanvas *c3 = new TCanvas("c3", "Gain 675 fF", 800, 600);
  h3->Draw();
  h3->GetXaxis()->SetTitle("Amplitude [ADC]");
  h3->GetYaxis()->SetTitle("Number of entries");
  h3->GetYaxis()->SetTitleOffset(1.2);
  h3->GetXaxis()->SetRangeUser(200, 500);
  pt3->Draw("same");

  c3->SaveAs("Plots/Gain675fF_MainzHBU4.pdf");

  //-------------------------------------

  TFile *f4 = new TFile("Rootfiles/thres_scan_HBU2_12.root", "OPEN");

  gStyle->SetOptStat(0);

  TGraphAsymmErrors *grTrg1;
  TGraphErrors *grTrg2;
  f4->GetObject("gRatio/gr_400_0_0", grTrg1);
  f4->GetObject("Graphs/gTrgPos_0_0", grTrg2);

  grTrg1->GetXaxis()->SetTitle("Amplitude [ADC]");
  grTrg1->GetXaxis()->SetRangeUser(300, 650);
  grTrg1->GetYaxis()->SetRangeUser(0, 1.5);
  grTrg1->GetYaxis()->SetTitle("AT/ET events");
  grTrg1->SetMarkerColor(kBlue);
  grTrg1->SetLineColor(kBlue);

  TLegend *leg = new TLegend(0.2, 0.7, 0.45, 0.9);
  leg->AddEntry(grTrg1, "AT Threshold (400)", "pel");
  leg->AddEntry(grTrg1->GetFunction("fScurve"), "S-Curve fit", "l");

  cout << grTrg1->GetFunction("fScurve")->GetParameter(0) << " +/- " << grTrg1->GetFunction("fScurve")->GetParError(0) << endl;
  cout << grTrg1->GetFunction("fScurve")->GetParameter(1) << " +/- " << grTrg1->GetFunction("fScurve")->GetParError(1) << endl;

  TCanvas *c4 = new TCanvas("c4", "Effi Trg", 800, 600);
  grTrg1->Draw("AP");
  leg->Draw("same");

  c4->SaveAs("Plots/EfficiencyCurveFit_HBU2_12.pdf");

  grTrg2->SetMarkerStyle(20);
  grTrg2->GetXaxis()->SetTitle("Trigger Threshold Value");
  grTrg2->GetYaxis()->SetTitle("Fitted trigger position [ADC]");

  TLegend *leg2 = new TLegend(0.2, 0.7, 0.45, 0.9);
  leg2->AddEntry(grTrg2, "Trigger Threshold", "p");
  leg2->AddEntry(grTrg2->GetFunction("pol1"), "Linear Fit", "l");

  TCanvas *c5 = new TCanvas("c5", "Fit Trg", 800, 600);
  grTrg2->Draw("AP");
  leg2->Draw("same");

  c5->SaveAs("Plots/TriggerThresholdFit_HBU2_12.pdf");
}

void MakePlots()
{
  DCR();
  ChipTesting();
  Commissioning();
}
