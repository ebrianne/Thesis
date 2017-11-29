void Pedestal()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Pedestal_Spectrum_AT_SSF.root", "OPEN");
  TH1F *histPed;

  f->GetObject("ADC_Spectrum_Chip236_Chn0_Mem1", histPed);

  //Get Limits iteration
  float Mean1 = histPed->GetMean();
  float RMS1 = histPed->GetRMS();
  // cout << Mean1 << " " << RMS1 << endl;
  histPed->GetXaxis()->SetRangeUser(Mean1 - 3*RMS1, Mean1 + 3*RMS1);

  TBox *box1 = new TBox(Mean1 - 3*RMS1, 0, Mean1 + 3*RMS1, 1);
  box1->SetLineColor(kBlue);
  box1->SetLineWidth(2);
  box1->SetFillColor(38);
  box1->SetFillStyle(3001);

  float Mean2 = histPed->GetMean();
  float RMS2 = histPed->GetRMS();
  // cout << Mean2 << " " << RMS2 << endl;
  histPed->GetXaxis()->SetRangeUser(Mean2 - 3*RMS2, Mean2 + 3*RMS2);

  TBox *box2 = new TBox(Mean2 - 3*RMS2, 0, Mean2 + 3*RMS2, 1);
  box2->SetLineColor(kBlue);
  box2->SetLineWidth(2);
  box2->SetFillColor(kGreen);
  box2->SetFillStyle(3004);

  float mean_final = histPed->GetMean();
  float RMS_final = histPed->GetRMS();
  // cout << mean_final << " " << RMS_final << endl;

  TBox *box3 = new TBox(Mean2, 0, Mean2, 1);
  box3->SetLineColor(kRed);
  box3->SetLineWidth(2);
  box3->SetFillColor(kRed);
  box3->SetFillStyle(3001);

  histPed->GetXaxis()->SetRangeUser(0, 1000);
  histPed->GetYaxis()->SetRangeUser(1e-6, 1);

  TLegend *leg = new TLegend(0.65, 0.6, 0.9, 0.8);
  leg->AddEntry(box1, "First Range", "lf");
  leg->AddEntry(box2, "Second Range", "lf");
  leg->AddEntry(box3, "Pedestal value", "l");

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c1 = new TCanvas("c1", "Pedestal Extraction", 800, 600);
  gPad->SetLogy();
  histPed->Draw();
  histPed->SetLineWidth(2);
  histPed->SetLineColor(kBlack);
  histPed->GetYaxis()->SetTitle("Fraction of entries");
  histPed->GetXaxis()->SetTitle("Amplitude [ADC]");
  box1->Draw("l");
  box2->Draw("l");
  box3->Draw("l");
  histPed->Draw("same");
  leg->Draw("same");
  TGaxis *axis = new TGaxis(mean_final+2, 1, 1000, 1, 0, (1000-mean_final)/500, 004, "-");
  axis->SetLabelFont(62);
  axis->SetLabelColor(kBlue);
  axis->SetLabelSize(0.03);
  axis->SetTitleFont(62);
  axis->SetTitleSize(0.03);
  axis->SetTitleOffset(1.3);
  axis->SetTitleColor(kBlue);
  axis->SetTitle("MIP");
  axis->SetLineColor(kBlue);
  axis->SetLineWidth(2);
  axis->Draw();
  TGaxis *axis2 = new TGaxis(mean_final+2, 1, 1000, 1, 0, (1000-mean_final)/23, 010, "+");
  axis2->SetLabelFont(62);
  axis2->SetLabelColor(kOrange+1);
  axis2->SetLabelSize(0.03);
  axis2->SetTitleFont(62);
  axis2->SetTitleColor(kOrange+1);
  axis2->SetTitleSize(0.03);
  axis2->SetLineColor(kOrange+1);
  axis2->SetLineWidth(2);
  axis2->SetTitle("px");
  axis2->Draw();

  c1->SaveAs("Plots/PedestalExtractionExample.pdf");

  //---------------------------------------------------
  //Make Plots spread Memory cells compared to Mean

  map<int, float> m_mapPedestal;

  ifstream fIn("Rootfiles/Pedestal_allMemory_AT_July.txt");
  string line;

  while(fIn.good())
  {
    getline(fIn, line);

    if(line == "" || line.at(0) == '#') continue;

    istringstream iss(line);
    int Module, Chip, Chn, Mem;
    float Mean, MeanError;

    iss >> Module >> Chip >> Chn >> Mem >> Mean >> MeanError;
    int index = Chip*10000 + Chn*100 + Mem;
    m_mapPedestal.insert(make_pair(index, Mean));
  }

  fIn.close();

  map<int, float> m_mapPedestalMean;

  ifstream fIn2("Rootfiles/Pedestal_AllChip_AT_July.txt");

  while(fIn2.good())
  {
    getline(fIn2, line);

    if(line == "" || line.at(0) == '#') continue;

    istringstream iss(line);
    int Module, Chip, Chn;
    float Mean, MeanError;

    iss >> Module >> Chip >> Chn >> Mean >> MeanError;
    int index = Chip*100 + Chn;

    m_mapPedestalMean.insert(make_pair(index, Mean));
  }

  fIn.close();

  cout << "Map Ped all " << m_mapPedestal.size() << endl;
  cout << "Map Ped mean " << m_mapPedestalMean.size() << endl;

  //Fill histo MeanPed - Pedi
  TH1F *hPedComp = new TH1F("hPedComp", "hPedComp", 300, -150, 150);

  for(map<int, float>::iterator it = m_mapPedestalMean.begin(); it != m_mapPedestalMean.end(); ++it)
  {
    int indexChipChn = it->first;
    float PedMean = it->second;

    for(int mem = 1; mem < 16; mem++)
    {
      if(m_mapPedestal.find(indexChipChn*100+mem) != m_mapPedestal.end())
      {
        float Pedi = m_mapPedestal[indexChipChn*100+mem];
        hPedComp->Fill(PedMean - Pedi);
      }
    }
  }

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadTickX(1);
  gStyle->SetOptStat(1110);
  gStyle->SetStatY(0.9);
  gStyle->SetStatX(0.9);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);

  hPedComp->SetStats(kTRUE);

  TCanvas *c2 = new TCanvas("c2", "Comp Ped Mean to Mem cell", 800, 600);
  // gPad->SetLogy();
  hPedComp->Draw();
  hPedComp->SetLineWidth(2);
  hPedComp->SetLineColor(kBlack);
  hPedComp->GetXaxis()->SetTitle("Mean Ped - Ped_{i} [ADC]");
  hPedComp->GetYaxis()->SetTitle("Number of entries");

  c2->SaveAs("Plots/ComparisonMeanPedtoMemorycell.pdf");

}

map<int, pair<float, float> > m_mapMIP;

void MakeMap()
{
  ifstream fIn("Rootfiles/DatabaseMIP_CERN_July2015_AllCombined_20161703.txt");
  string line;

  if(fIn.is_open())
  {
    while(getline(fIn, line))
    {
      if(line == "" || line.at(0) == '#') continue;

      istringstream iss(line);
      int Module, ChipID, Chn;
      float MIP, MIP_Error;

      iss >> Module >> ChipID >> Chn >> MIP >> MIP_Error;

      m_mapMIP.insert(make_pair(Module*10000+ChipID*100+Chn, make_pair(MIP, MIP_Error)));
    }
  }
  else
  {
    cout << "Can t open MIP File" << endl;
  }

  cout << "Map July done : " << m_mapMIP.size() << endl;

  fIn.close();
}

void MIP()
{
  CaliceStyle();
  MakeMap();

  TH1F *hError = new TH1F("hError", "hError", 100, 0, 30);

  for(map<int, pair<float, float> >::iterator it = m_mapMIP.begin(); it != m_mapMIP.end(); ++it)
  {
    float MIP = it->second.first;
    float MIP_error = it->second.second;

    if(MIP == 0) continue;
    float relative_error = MIP_error / MIP * 100;

    hError->Fill(relative_error);
  }

  gStyle->SetOptStat(1110);
  gStyle->SetStatY(0.9);
  gStyle->SetStatX(0.9);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);

  hError->SetStats(kTRUE);

  TCanvas *c1 = new TCanvas("c1", "MIP Extraction", 800, 600);
  // gPad->SetLogy();
  hError->Draw();
  hError->SetLineWidth(2);
  hError->SetLineColor(kBlack);
  hError->GetYaxis()->SetTitle("Number of entries");
  hError->GetXaxis()->SetTitle("Relative error [%]");

  c1->SaveAs("Plots/RelativeErrorMIP_Combined.pdf");

  //----------------------------------

  TFile *f = new TFile("Rootfiles/Chi2FitIteration_binned_Module3.root", "OPEN");
  TH1F *hMIP;

  f->GetObject("ADC_Spectrum_Chip236_Chn21", hMIP);

  gStyle->SetOptStat(1110);
  gStyle->SetOptFit(0);
  gStyle->SetStatY(0.9);
  gStyle->SetStatX(0.9);
  gStyle->SetStatW(0.2);
  gStyle->SetStatH(0.2);

  hMIP->SetStats(kTRUE);

  float MIP = 456.81;
  float Error = 5.95;

  TBox *box2 = new TBox(MIP, 0, MIP, 0.025);
  box2->SetLineColor(kRed);
  box2->SetLineWidth(2);
  box2->SetFillColor(kRed);
  box2->SetFillStyle(3001);

  TLegend *leg = new TLegend(0.53, 0.55, 0.78, 0.65);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(box2, TString::Format("MPV: %.2f #pm %.2f ADC", MIP, Error), "l");

  TCanvas *c2 = new TCanvas("c2", "MIP Spectra", 800, 600);
  // gPad->SetLogy();
  hMIP->Draw();
  hMIP->SetLineWidth(2);
  hMIP->SetLineColor(kBlack);
  hMIP->SetFillColor(kBlue);
  hMIP->SetFillStyle(3001);
  hMIP->GetYaxis()->SetTitle("Fraction of entries");
  hMIP->GetYaxis()->SetTitleOffset(1.3);
  hMIP->GetYaxis()->SetRangeUser(0, 0.025);
  hMIP->GetXaxis()->SetTitle("Amplitude [ADC]");
  box2->Draw("l");
  leg->Draw("same");
  // hMIP->Draw("same");

  c2->SaveAs("Plots/ExampleMIP_Module3.pdf");

}

void ComparisonMIP()
{
  CaliceStyle();

  float MaxMIP = 5.;

  TFile *f = new TFile("Rootfiles/SpectrumMIP_Data.root", "OPEN");
  TH1F *hMIPData;

  f->GetObject("hMIPData", hMIPData);

  TFile *f2 = new TFile("Rootfiles/SpectrumMIP_MC.root", "OPEN");
  TH1F *hMIPMC;

  f2->GetObject("hMIPMC", hMIPMC);

  // hMIPData->Rebin(5);
  hMIPData->Scale(1./hMIPData->Integral(hMIPData->GetXaxis()->FindBin(0.), hMIPData->GetXaxis()->FindBin(MaxMIP)));
  hMIPData->SetLineWidth(2);
  hMIPData->SetLineColor(kBlack);

  // hMIPMC->Rebin(4);
  hMIPMC->Scale(1./hMIPMC->Integral(hMIPMC->GetXaxis()->FindBin(0.), hMIPMC->GetXaxis()->FindBin(MaxMIP)));
  hMIPMC->SetLineWidth(2);
  hMIPMC->SetLineColor(kRed);
  hMIPMC->SetFillColor(kRed);
  hMIPMC->SetFillStyle(3002);

  TLegend *leg = new TLegend(0.6, 0.6, 0.85, 0.8);
  // leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->AddEntry(hMIPData, "Data", "l");
  leg->AddEntry(hMIPMC, "AHCAL Simulation", "l");

  TCanvas *c1 = new TCanvas("c1", "MIP MC/Data", 800, 600);
  hMIPData->Draw();
  hMIPData->GetXaxis()->SetRangeUser(0, MaxMIP);
  hMIPData->GetXaxis()->SetTitle("Hit Energy [MIP]");
  hMIPData->GetYaxis()->SetTitle("Fraction of hits");
  hMIPData->GetYaxis()->SetRangeUser(0, 0.12);
  hMIPMC->Draw("same");
  hMIPData->Draw("same");
  leg->Draw("same");

  c1->SaveAs("Plots/ComparisonMCData_MIPPeak.pdf");

  //-------------------------------

  TFile *f3 = new TFile("Rootfiles/OutputFit.root", "OPEN");
  TH1F *hFitData, *hFitMC;

  f3->GetObject("MIP_Data", hFitData);
  f3->GetObject("MIP_MC", hFitMC);

  hFitData->Rebin(2);
  hFitData->SetLineColor(kBlack);
  hFitData->SetLineWidth(2);

  hFitMC->Rebin(2);
  hFitMC->SetLineColor(kRed);
  hFitMC->SetLineWidth(2);

  TLegend *leg2 = new TLegend(0.2, 0.6, 0.45, 0.8);
  // leg->SetBorderSize(0);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(hFitData, "Data", "l");
  leg2->AddEntry(hFitMC, "AHCAL Simulation", "l");

  hFitData->SetStats(kTRUE);
  hFitMC->SetStats(kTRUE);

  gStyle->SetOptStat(1110);

  TCanvas *c2 = new TCanvas("c2", "Fit MPV MC/Data", 800, 600);
  hFitData->Draw();
  hFitData->GetXaxis()->SetRangeUser(0.7, 1.3);
  hFitData->GetXaxis()->SetTitle("Fitted MPV [MIP]");
  hFitData->GetYaxis()->SetTitle("Number of channels");
  hFitMC->Draw("sames");
  leg2->Draw("same");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)hFitData->GetListOfFunctions()->FindObject("stats");
  st->SetX1NDC(0.7);
  st->SetX2NDC(0.9);
  st->SetY1NDC(0.75);
  st->SetY2NDC(0.9);
  st->SetLineColor(kBlack);
  st->SetTextColor(kBlack);
  TPaveStats *st2 = (TPaveStats*)hFitMC->GetListOfFunctions()->FindObject("stats");
  st2->SetX1NDC(0.7);
  st2->SetX2NDC(0.9);
  st2->SetY1NDC(0.55);
  st2->SetY2NDC(0.70);
  st2->SetLineColor(kRed);
  st2->SetTextColor(kRed);
  gPad->Modified();

  c2->SaveAs("Plots/ComparisonMCData_MPV.pdf");

}

void SystematicMIP()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/SystematicMIP.root", "OPEN");
  TH1F *hMIP_1, *hMIP_2;

  f->GetObject("MIP_1", hMIP_1);
  f->GetObject("MIP_2", hMIP_2);

  hMIP_1->GetXaxis()->SetTitle("MPV [MIP]");
  hMIP_1->GetYaxis()->SetTitle("Number of entries");
  hMIP_1->SetLineWidth(2);
  hMIP_1->SetLineColor(kBlue);

  hMIP_2->GetXaxis()->SetTitle("MPV [MIP]");
  hMIP_2->GetYaxis()->SetTitle("Number of entries");
  hMIP_2->SetLineWidth(2);
  hMIP_2->SetLineColor(kRed);

  hMIP_1->SetStats(kTRUE);
  hMIP_2->SetStats(kTRUE);

  gStyle->SetOptStat(1110);
  // gStyle->SetStatY(0.9);
  // gStyle->SetStatX(0.9);
  // gStyle->SetStatW(0.2);
  // gStyle->SetStatH(0.2);

  hMIP_1->Rebin(2);
  hMIP_2->Rebin(2);

  TCanvas *c1 = new TCanvas("c1", "Syst MIP", 800, 600);
  hMIP_1->Draw();
  hMIP_2->Draw("sames");
  gPad->Update();
  TPaveStats *st = (TPaveStats*)hMIP_1->GetListOfFunctions()->FindObject("stats");
  st->SetX1NDC(0.7);
  st->SetX2NDC(0.9);
  st->SetY1NDC(0.75);
  st->SetY2NDC(0.9);
  st->SetLineColor(kBlue);
  st->SetTextColor(kBlue);
  TPaveStats *st2 = (TPaveStats*)hMIP_2->GetListOfFunctions()->FindObject("stats");
  st2->SetX1NDC(0.7);
  st2->SetX2NDC(0.9);
  st2->SetY1NDC(0.55);
  st2->SetY2NDC(0.70);
  st2->SetLineColor(kRed);
  st2->SetTextColor(kRed);
  gPad->Modified();

  c1->SaveAs("Plots/SystematicMIP.pdf");
}

void MakePlots()
{
  Pedestal();
  MIP();
  ComparisonMIP();
  SystematicMIP();
}
