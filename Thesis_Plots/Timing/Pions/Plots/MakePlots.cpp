float GetSyst(int radius, int energy, string type)
{
  TString PATH;
  if(type == "SSF")
  PATH = "Rootfiles/SystRadius_SSF.root";
  else
  PATH = "Rootfiles/SystRadius_BL.root";

  TFile *fGraph = new TFile(PATH, "OPEN");
  float syst = 0.;

  TGraphErrors *gsyst;
  if(energy == 10)
  fGraph->GetObject("syst10", gsyst);
  if(energy == 30)
  fGraph->GetObject("syst30", gsyst);
  if(energy == 50)
  fGraph->GetObject("syst50", gsyst);
  if(energy == 70)
  fGraph->GetObject("syst70", gsyst);
  if(energy == 90)
  fGraph->GetObject("syst90", gsyst);

  if(gsyst)
  {
    if( (radius <= 195 && type == "SSF") || (radius <= 315 && type == "BL") )
    syst = gsyst->Eval(radius);
    else{
      if(type == "SSF")
      syst = gsyst->Eval(195);
      else
      syst = gsyst->Eval(315);
    }
  }

  return syst*syst;
}

void TimingPions_10GeV()
{
  CaliceStyle();

  TString MokkaFile;
  MokkaFile = "Rootfiles/TimingMokkaAdd_10GeV.root";

  TFile *f = new TFile(MokkaFile, "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  //QBBC
  TH1F* hTimeSim_QBBC, *hTimeSim_ErrorLow_QBBC, *hTimeSim_ErrorUp_QBBC, *hTimeSim_Xtalk10_QBBC, *hTimeSim_Xtalk18_QBBC;
  f->GetObject("hTimeSim_QBBC", hTimeSim_QBBC);
  f->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_ErrorLow_QBBC);
  f->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_ErrorUp_QBBC);
  f->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_Xtalk10_QBBC);
  f->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_QGSP_BERT, *hTimeSim_ErrorLow_QGSP_BERT, *hTimeSim_ErrorUp_QGSP_BERT, *hTimeSim_Xtalk10_QGSP_BERT, *hTimeSim_Xtalk18_QGSP_BERT;
  f->GetObject("hTimeSim_QGSP_BERT", hTimeSim_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_ErrorLow_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_ErrorUp_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_Xtalk10_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_Xtalk18_QGSP_BERT);

  hTimeSim->Rebin(4);
  hTimeSim_ErrorLow->Rebin(4);
  hTimeSim_ErrorUp->Rebin(4);
  hTimeSim_Xtalk10->Rebin(4);
  hTimeSim_Xtalk18->Rebin(4);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(hTimeSim->GetXaxis()->FindBin(-50), hTimeSim->GetXaxis()->FindBin(200), "width"));
  hTimeSim->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(hTimeSim_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(hTimeSim_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(hTimeSim_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(hTimeSim_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_QBBC->Rebin(4);
  hTimeSim_QBBC->Sumw2();

  hTimeSim_QBBC->SetLineColor(kBlue);
  hTimeSim_QBBC->SetMarkerColor(kBlue);
  hTimeSim_QBBC->SetLineWidth(2);

  hTimeSim_QBBC->Scale(1./hTimeSim_QBBC->Integral(hTimeSim_QBBC->GetXaxis()->FindBin(-50), hTimeSim_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QBBC->Rebin(4);
  hTimeSim_ErrorLow_QBBC->Sumw2();

  hTimeSim_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_ErrorLow_QBBC->Scale(1./hTimeSim_ErrorLow_QBBC->Integral(hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QBBC->Rebin(4);
  hTimeSim_ErrorUp_QBBC->Sumw2();

  hTimeSim_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_ErrorUp_QBBC->Scale(1./hTimeSim_ErrorUp_QBBC->Integral(hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QBBC->Rebin(4);
  hTimeSim_Xtalk10_QBBC->Sumw2();

  hTimeSim_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk10_QBBC->Scale(1./hTimeSim_Xtalk10_QBBC->Integral(hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QBBC->Rebin(4);
  hTimeSim_Xtalk18_QBBC->Sumw2();

  hTimeSim_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk18_QBBC->Scale(1./hTimeSim_Xtalk18_QBBC->Integral(hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_QGSP_BERT->Rebin(4);
  hTimeSim_QGSP_BERT->Sumw2();

  hTimeSim_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_QGSP_BERT->SetLineWidth(2);

  hTimeSim_QGSP_BERT->Scale(1./hTimeSim_QGSP_BERT->Integral(hTimeSim_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_ErrorLow_QGSP_BERT->Integral(hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_ErrorUp_QGSP_BERT->Integral(hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_Xtalk10_QGSP_BERT->Integral(hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_Xtalk18_QGSP_BERT->Integral(hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  TString PATH;
  PATH = "/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/10GeV/Data/Timing_LateClusters/Rootfiles/Timing_FullAHCAL.root";
  TFile *f2 = new TFile(PATH, "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Pion", hData);

  hData->Rebin(4);
  hData->Sumw2();
  hData->Scale(1./hData->Integral(hData->GetXaxis()->FindBin(-50), hData->GetXaxis()->FindBin(200), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = (0.20+0.10)*content;

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetMarkerColor(kRed);
  gTimeSim->SetFillColor(kRed);
  gTimeSim->SetLineWidth(2);
  gTimeSim->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
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
    double error_syst = 0.00*hTimeSim->GetBinContent(ibin);

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_QBBC = new TGraphAsymmErrors();
  gTimeSim_QBBC->SetLineColor(kBlue);
  gTimeSim_QBBC->SetMarkerColor(kBlue);
  gTimeSim_QBBC->SetFillColor(kBlue);
  gTimeSim_QBBC->SetLineWidth(2);
  gTimeSim_QBBC->SetLineStyle(1);
  gTimeSim_QBBC->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QBBC->GetBinContent(ibin);

    gTimeSim_QBBC->SetPoint(ibin, hTimeSim_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_QGSP_BERT->SetLineWidth(2);
  gTimeSim_QGSP_BERT->SetLineStyle(1);
  gTimeSim_QGSP_BERT->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_QGSP_BERT->SetPoint(ibin, hTimeSim_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TString DD4hepFile;
  DD4hepFile = "Rootfiles/TimingDD4hepAdd_10GeV.root";

  TFile *f3 = new TFile(DD4hepFile, "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F* hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  //QBBC
  TH1F* hTimeSim_DD4hep_QBBC, *hTimeSim_DD4hep_ErrorLow_QBBC, *hTimeSim_DD4hep_ErrorUp_QBBC, *hTimeSim_DD4hep_Xtalk10_QBBC, *hTimeSim_DD4hep_Xtalk18_QBBC;
  f3->GetObject("hTimeSim_QBBC", hTimeSim_DD4hep_QBBC);
  f3->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_DD4hep_ErrorLow_QBBC);
  f3->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_DD4hep_ErrorUp_QBBC);
  f3->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_DD4hep_Xtalk10_QBBC);
  f3->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_DD4hep_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_DD4hep_QGSP_BERT, *hTimeSim_DD4hep_ErrorLow_QGSP_BERT, *hTimeSim_DD4hep_ErrorUp_QGSP_BERT, *hTimeSim_DD4hep_Xtalk10_QGSP_BERT, *hTimeSim_DD4hep_Xtalk18_QGSP_BERT;
  f3->GetObject("hTimeSim_QGSP_BERT", hTimeSim_DD4hep_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_DD4hep_ErrorLow_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_DD4hep_ErrorUp_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_DD4hep_Xtalk10_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_DD4hep_Xtalk18_QGSP_BERT);

  hTimeSim_DD4hep->Rebin(4);
  hTimeSim_DD4hep_ErrorLow->Rebin(4);
  hTimeSim_DD4hep_ErrorUp->Rebin(4);
  hTimeSim_DD4hep_Xtalk10->Rebin(4);
  hTimeSim_DD4hep_Xtalk18->Rebin(4);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kRed);
  hTimeSim_DD4hep->SetMarkerColor(kRed);
  hTimeSim_DD4hep->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(hTimeSim_DD4hep->GetXaxis()->FindBin(-50), hTimeSim_DD4hep->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_DD4hep_QBBC->Rebin(4);
  hTimeSim_DD4hep_QBBC->Sumw2();

  hTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_QBBC->Scale(1./hTimeSim_DD4hep_QBBC->Integral(hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QBBC->Scale(1./hTimeSim_DD4hep_ErrorLow_QBBC->Integral(hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QBBC->Scale(1./hTimeSim_DD4hep_ErrorUp_QBBC->Integral(hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk10_QBBC->Integral(hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk18_QBBC->Integral(hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_DD4hep_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_QGSP_BERT->Scale(1./hTimeSim_DD4hep_QGSP_BERT->Integral(hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kRed);
  gTimeSim_DD4hep->SetMarkerColor(kRed);
  gTimeSim_DD4hep->SetFillColor(kRed);
  gTimeSim_DD4hep->SetLineWidth(2);
  gTimeSim_DD4hep->SetLineStyle(2);
  gTimeSim_DD4hep->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep->GetBinContent(ibin);

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_DD4hep_QBBC = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetFillColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetLineWidth(2);
  gTimeSim_DD4hep_QBBC->SetLineStyle(2);
  gTimeSim_DD4hep_QBBC->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QBBC->GetBinContent(ibin);

    gTimeSim_DD4hep_QBBC->SetPoint(ibin, hTimeSim_DD4hep_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_DD4hep_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);
  gTimeSim_DD4hep_QGSP_BERT->SetLineStyle(2);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_DD4hep_QGSP_BERT->SetPoint(ibin, hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->SetHeader("Mokka");
  leg3->AddEntry(gTimeData, "Data", "pf");
  leg3->AddEntry(gTimeSim_QGSP_BERT, "QGSP_BERT", "epl");
  leg3->AddEntry(gTimeSim, "QGSP_BERT_HP", "epl");
  leg3->AddEntry(gTimeSim_QBBC, "QBBC", "epl");

  TLegend* leg4 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.028);
  leg4->SetHeader("DD4hep");
  leg4->AddEntry(gTimeSim_DD4hep_QGSP_BERT, "QGSP_BERT", "epl");
  leg4->AddEntry(gTimeSim_DD4hep, "QGSP_BERT_HP", "epl");
  leg4->AddEntry(gTimeSim_DD4hep_QBBC, "QBBC", "epl");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("10 GeV #pi^{-} - steel");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(gTimeSim);
  multi->Add(gTimeSim_QGSP_BERT);
  multi->Add(gTimeSim_QBBC);
  multi->Add(gTimeSim_DD4hep);
  multi->Add(gTimeSim_DD4hep_QGSP_BERT);
  multi->Add(gTimeSim_DD4hep_QBBC);

  TCanvas *c = new TCanvas("c1", "", 800, 600);
  gPad->SetLogy();
  gTimeData->Draw("APL");
  gTimeData->GetXaxis()->SetTitle("Time of first hit [ns]");
  gTimeData->GetYaxis()->SetTitle("Fraction of hits");
  gTimeData->GetXaxis()->SetRangeUser(-50, 200);
  gTimeData->GetYaxis()->SetRangeUser(1e-6, 10);
  gTimeData->Draw("E3");
  multi->Draw("PEL");
  //hData->GetXaxis()->SetRangeUser(-50, 200);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  leg4->Draw("same");
  pt->Draw("same");

  c->SaveAs("Plots/Comparison_SimData_Pion10GeV_LateClusters.pdf");
}

void TimingPions_30GeV()
{
  CaliceStyle();

  TString MokkaFile;
  MokkaFile = "Rootfiles/TimingMokkaAdd_30GeV.root";

  TFile *f = new TFile(MokkaFile, "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  //QBBC
  TH1F* hTimeSim_QBBC, *hTimeSim_ErrorLow_QBBC, *hTimeSim_ErrorUp_QBBC, *hTimeSim_Xtalk10_QBBC, *hTimeSim_Xtalk18_QBBC;
  f->GetObject("hTimeSim_QBBC", hTimeSim_QBBC);
  f->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_ErrorLow_QBBC);
  f->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_ErrorUp_QBBC);
  f->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_Xtalk10_QBBC);
  f->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_QGSP_BERT, *hTimeSim_ErrorLow_QGSP_BERT, *hTimeSim_ErrorUp_QGSP_BERT, *hTimeSim_Xtalk10_QGSP_BERT, *hTimeSim_Xtalk18_QGSP_BERT;
  f->GetObject("hTimeSim_QGSP_BERT", hTimeSim_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_ErrorLow_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_ErrorUp_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_Xtalk10_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_Xtalk18_QGSP_BERT);

  hTimeSim->Rebin(4);
  hTimeSim_ErrorLow->Rebin(4);
  hTimeSim_ErrorUp->Rebin(4);
  hTimeSim_Xtalk10->Rebin(4);
  hTimeSim_Xtalk18->Rebin(4);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(hTimeSim->GetXaxis()->FindBin(-50), hTimeSim->GetXaxis()->FindBin(200), "width"));
  hTimeSim->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(hTimeSim_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(hTimeSim_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(hTimeSim_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(hTimeSim_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_QBBC->Rebin(4);
  hTimeSim_QBBC->Sumw2();

  hTimeSim_QBBC->SetLineColor(kBlue);
  hTimeSim_QBBC->SetMarkerColor(kBlue);
  hTimeSim_QBBC->SetLineWidth(2);

  hTimeSim_QBBC->Scale(1./hTimeSim_QBBC->Integral(hTimeSim_QBBC->GetXaxis()->FindBin(-50), hTimeSim_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QBBC->Rebin(4);
  hTimeSim_ErrorLow_QBBC->Sumw2();

  hTimeSim_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_ErrorLow_QBBC->Scale(1./hTimeSim_ErrorLow_QBBC->Integral(hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QBBC->Rebin(4);
  hTimeSim_ErrorUp_QBBC->Sumw2();

  hTimeSim_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_ErrorUp_QBBC->Scale(1./hTimeSim_ErrorUp_QBBC->Integral(hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QBBC->Rebin(4);
  hTimeSim_Xtalk10_QBBC->Sumw2();

  hTimeSim_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk10_QBBC->Scale(1./hTimeSim_Xtalk10_QBBC->Integral(hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QBBC->Rebin(4);
  hTimeSim_Xtalk18_QBBC->Sumw2();

  hTimeSim_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk18_QBBC->Scale(1./hTimeSim_Xtalk18_QBBC->Integral(hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_QGSP_BERT->Rebin(4);
  hTimeSim_QGSP_BERT->Sumw2();

  hTimeSim_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_QGSP_BERT->SetLineWidth(2);

  hTimeSim_QGSP_BERT->Scale(1./hTimeSim_QGSP_BERT->Integral(hTimeSim_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_ErrorLow_QGSP_BERT->Integral(hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_ErrorUp_QGSP_BERT->Integral(hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_Xtalk10_QGSP_BERT->Integral(hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_Xtalk18_QGSP_BERT->Integral(hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  TString PATH;
  PATH = "/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/30GeV/Data/Timing_LateClusters/Rootfiles/Timing_FullAHCAL.root";
  TFile *f2 = new TFile(PATH, "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Pion", hData);

  hData->Rebin(4);
  hData->Sumw2();
  hData->Scale(1./hData->Integral(hData->GetXaxis()->FindBin(-50), hData->GetXaxis()->FindBin(200), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = (0.20+0.10)*content;

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetMarkerColor(kRed);
  gTimeSim->SetFillColor(kRed);
  gTimeSim->SetLineWidth(2);
  gTimeSim->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
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
    double error_syst = 0.00*hTimeSim->GetBinContent(ibin);

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_QBBC = new TGraphAsymmErrors();
  gTimeSim_QBBC->SetLineColor(kBlue);
  gTimeSim_QBBC->SetMarkerColor(kBlue);
  gTimeSim_QBBC->SetFillColor(kBlue);
  gTimeSim_QBBC->SetLineWidth(2);
  gTimeSim_QBBC->SetLineStyle(1);
  gTimeSim_QBBC->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QBBC->GetBinContent(ibin);

    gTimeSim_QBBC->SetPoint(ibin, hTimeSim_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_QGSP_BERT->SetLineWidth(2);
  gTimeSim_QGSP_BERT->SetLineStyle(1);
  gTimeSim_QGSP_BERT->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_QGSP_BERT->SetPoint(ibin, hTimeSim_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TString DD4hepFile;
  DD4hepFile = "Rootfiles/TimingDD4hepAdd_30GeV.root";

  TFile *f3 = new TFile(DD4hepFile, "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F* hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  //QBBC
  TH1F* hTimeSim_DD4hep_QBBC, *hTimeSim_DD4hep_ErrorLow_QBBC, *hTimeSim_DD4hep_ErrorUp_QBBC, *hTimeSim_DD4hep_Xtalk10_QBBC, *hTimeSim_DD4hep_Xtalk18_QBBC;
  f3->GetObject("hTimeSim_QBBC", hTimeSim_DD4hep_QBBC);
  f3->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_DD4hep_ErrorLow_QBBC);
  f3->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_DD4hep_ErrorUp_QBBC);
  f3->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_DD4hep_Xtalk10_QBBC);
  f3->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_DD4hep_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_DD4hep_QGSP_BERT, *hTimeSim_DD4hep_ErrorLow_QGSP_BERT, *hTimeSim_DD4hep_ErrorUp_QGSP_BERT, *hTimeSim_DD4hep_Xtalk10_QGSP_BERT, *hTimeSim_DD4hep_Xtalk18_QGSP_BERT;
  f3->GetObject("hTimeSim_QGSP_BERT", hTimeSim_DD4hep_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_DD4hep_ErrorLow_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_DD4hep_ErrorUp_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_DD4hep_Xtalk10_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_DD4hep_Xtalk18_QGSP_BERT);

  hTimeSim_DD4hep->Rebin(4);
  hTimeSim_DD4hep_ErrorLow->Rebin(4);
  hTimeSim_DD4hep_ErrorUp->Rebin(4);
  hTimeSim_DD4hep_Xtalk10->Rebin(4);
  hTimeSim_DD4hep_Xtalk18->Rebin(4);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kRed);
  hTimeSim_DD4hep->SetMarkerColor(kRed);
  hTimeSim_DD4hep->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(hTimeSim_DD4hep->GetXaxis()->FindBin(-50), hTimeSim_DD4hep->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_DD4hep_QBBC->Rebin(4);
  hTimeSim_DD4hep_QBBC->Sumw2();

  hTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_QBBC->Scale(1./hTimeSim_DD4hep_QBBC->Integral(hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QBBC->Scale(1./hTimeSim_DD4hep_ErrorLow_QBBC->Integral(hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QBBC->Scale(1./hTimeSim_DD4hep_ErrorUp_QBBC->Integral(hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk10_QBBC->Integral(hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk18_QBBC->Integral(hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_DD4hep_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_QGSP_BERT->Scale(1./hTimeSim_DD4hep_QGSP_BERT->Integral(hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kRed);
  gTimeSim_DD4hep->SetMarkerColor(kRed);
  gTimeSim_DD4hep->SetFillColor(kRed);
  gTimeSim_DD4hep->SetLineWidth(2);
  gTimeSim_DD4hep->SetLineStyle(2);
  gTimeSim_DD4hep->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep->GetBinContent(ibin);

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_DD4hep_QBBC = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetFillColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetLineWidth(2);
  gTimeSim_DD4hep_QBBC->SetLineStyle(2);
  gTimeSim_DD4hep_QBBC->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QBBC->GetBinContent(ibin);

    gTimeSim_DD4hep_QBBC->SetPoint(ibin, hTimeSim_DD4hep_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_DD4hep_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);
  gTimeSim_DD4hep_QGSP_BERT->SetLineStyle(2);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_DD4hep_QGSP_BERT->SetPoint(ibin, hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->SetHeader("Mokka");
  leg3->AddEntry(gTimeData, "Data", "pf");
  leg3->AddEntry(gTimeSim_QGSP_BERT, "QGSP_BERT", "epl");
  leg3->AddEntry(gTimeSim, "QGSP_BERT_HP", "epl");
  leg3->AddEntry(gTimeSim_QBBC, "QBBC", "epl");

  TLegend* leg4 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.028);
  leg4->SetHeader("DD4hep");
  leg4->AddEntry(gTimeSim_DD4hep_QGSP_BERT, "QGSP_BERT", "epl");
  leg4->AddEntry(gTimeSim_DD4hep, "QGSP_BERT_HP", "epl");
  leg4->AddEntry(gTimeSim_DD4hep_QBBC, "QBBC", "epl");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("30 GeV #pi^{-} - steel");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(gTimeSim);
  multi->Add(gTimeSim_QGSP_BERT);
  multi->Add(gTimeSim_QBBC);
  multi->Add(gTimeSim_DD4hep);
  multi->Add(gTimeSim_DD4hep_QGSP_BERT);
  multi->Add(gTimeSim_DD4hep_QBBC);

  TCanvas *c = new TCanvas("c1", "", 800, 600);
  gPad->SetLogy();
  gTimeData->Draw("APL");
  gTimeData->GetXaxis()->SetTitle("Time of first hit [ns]");
  gTimeData->GetYaxis()->SetTitle("Fraction of hits");
  gTimeData->GetXaxis()->SetRangeUser(-50, 200);
  gTimeData->GetYaxis()->SetRangeUser(1e-6, 10);
  gTimeData->Draw("E3");
  multi->Draw("PEL");
  //hData->GetXaxis()->SetRangeUser(-50, 200);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  leg4->Draw("same");
  pt->Draw("same");

  c->SaveAs("Plots/Comparison_SimData_Pion30GeV_LateClusters.pdf");
}

void TimingPions_50GeV()
{
  CaliceStyle();

  TString MokkaFile;
  MokkaFile = "Rootfiles/TimingMokkaAdd_50GeV.root";

  TFile *f = new TFile(MokkaFile, "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  //QBBC
  TH1F* hTimeSim_QBBC, *hTimeSim_ErrorLow_QBBC, *hTimeSim_ErrorUp_QBBC, *hTimeSim_Xtalk10_QBBC, *hTimeSim_Xtalk18_QBBC;
  f->GetObject("hTimeSim_QBBC", hTimeSim_QBBC);
  f->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_ErrorLow_QBBC);
  f->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_ErrorUp_QBBC);
  f->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_Xtalk10_QBBC);
  f->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_QGSP_BERT, *hTimeSim_ErrorLow_QGSP_BERT, *hTimeSim_ErrorUp_QGSP_BERT, *hTimeSim_Xtalk10_QGSP_BERT, *hTimeSim_Xtalk18_QGSP_BERT;
  f->GetObject("hTimeSim_QGSP_BERT", hTimeSim_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_ErrorLow_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_ErrorUp_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_Xtalk10_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_Xtalk18_QGSP_BERT);

  hTimeSim->Rebin(4);
  hTimeSim_ErrorLow->Rebin(4);
  hTimeSim_ErrorUp->Rebin(4);
  hTimeSim_Xtalk10->Rebin(4);
  hTimeSim_Xtalk18->Rebin(4);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(hTimeSim->GetXaxis()->FindBin(-50), hTimeSim->GetXaxis()->FindBin(200), "width"));
  hTimeSim->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(hTimeSim_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(hTimeSim_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(hTimeSim_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(hTimeSim_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_QBBC->Rebin(4);
  hTimeSim_QBBC->Sumw2();

  hTimeSim_QBBC->SetLineColor(kBlue);
  hTimeSim_QBBC->SetMarkerColor(kBlue);
  hTimeSim_QBBC->SetLineWidth(2);

  hTimeSim_QBBC->Scale(1./hTimeSim_QBBC->Integral(hTimeSim_QBBC->GetXaxis()->FindBin(-50), hTimeSim_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QBBC->Rebin(4);
  hTimeSim_ErrorLow_QBBC->Sumw2();

  hTimeSim_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_ErrorLow_QBBC->Scale(1./hTimeSim_ErrorLow_QBBC->Integral(hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QBBC->Rebin(4);
  hTimeSim_ErrorUp_QBBC->Sumw2();

  hTimeSim_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_ErrorUp_QBBC->Scale(1./hTimeSim_ErrorUp_QBBC->Integral(hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QBBC->Rebin(4);
  hTimeSim_Xtalk10_QBBC->Sumw2();

  hTimeSim_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk10_QBBC->Scale(1./hTimeSim_Xtalk10_QBBC->Integral(hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QBBC->Rebin(4);
  hTimeSim_Xtalk18_QBBC->Sumw2();

  hTimeSim_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk18_QBBC->Scale(1./hTimeSim_Xtalk18_QBBC->Integral(hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_QGSP_BERT->Rebin(4);
  hTimeSim_QGSP_BERT->Sumw2();

  hTimeSim_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_QGSP_BERT->SetLineWidth(2);

  hTimeSim_QGSP_BERT->Scale(1./hTimeSim_QGSP_BERT->Integral(hTimeSim_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_ErrorLow_QGSP_BERT->Integral(hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_ErrorUp_QGSP_BERT->Integral(hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_Xtalk10_QGSP_BERT->Integral(hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_Xtalk18_QGSP_BERT->Integral(hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  TString PATH;
  PATH = "/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/50GeV/Data/Timing_LateClusters/Rootfiles/Timing_FullAHCAL.root";
  TFile *f2 = new TFile(PATH, "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Pion", hData);

  hData->Rebin(4);
  hData->Sumw2();
  hData->Scale(1./hData->Integral(hData->GetXaxis()->FindBin(-50), hData->GetXaxis()->FindBin(200), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = (0.20+0.10)*content;

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetMarkerColor(kRed);
  gTimeSim->SetFillColor(kRed);
  gTimeSim->SetLineWidth(2);
  gTimeSim->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
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
    double error_syst = 0.00*hTimeSim->GetBinContent(ibin);

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_QBBC = new TGraphAsymmErrors();
  gTimeSim_QBBC->SetLineColor(kBlue);
  gTimeSim_QBBC->SetMarkerColor(kBlue);
  gTimeSim_QBBC->SetFillColor(kBlue);
  gTimeSim_QBBC->SetLineWidth(2);
  gTimeSim_QBBC->SetLineStyle(1);
  gTimeSim_QBBC->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QBBC->GetBinContent(ibin);

    gTimeSim_QBBC->SetPoint(ibin, hTimeSim_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_QGSP_BERT->SetLineWidth(2);
  gTimeSim_QGSP_BERT->SetLineStyle(1);
  gTimeSim_QGSP_BERT->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_QGSP_BERT->SetPoint(ibin, hTimeSim_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TString DD4hepFile;
  DD4hepFile = "Rootfiles/TimingDD4hepAdd_50GeV.root";

  TFile *f3 = new TFile(DD4hepFile, "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F* hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  //QBBC
  TH1F* hTimeSim_DD4hep_QBBC, *hTimeSim_DD4hep_ErrorLow_QBBC, *hTimeSim_DD4hep_ErrorUp_QBBC, *hTimeSim_DD4hep_Xtalk10_QBBC, *hTimeSim_DD4hep_Xtalk18_QBBC;
  f3->GetObject("hTimeSim_QBBC", hTimeSim_DD4hep_QBBC);
  f3->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_DD4hep_ErrorLow_QBBC);
  f3->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_DD4hep_ErrorUp_QBBC);
  f3->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_DD4hep_Xtalk10_QBBC);
  f3->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_DD4hep_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_DD4hep_QGSP_BERT, *hTimeSim_DD4hep_ErrorLow_QGSP_BERT, *hTimeSim_DD4hep_ErrorUp_QGSP_BERT, *hTimeSim_DD4hep_Xtalk10_QGSP_BERT, *hTimeSim_DD4hep_Xtalk18_QGSP_BERT;
  f3->GetObject("hTimeSim_QGSP_BERT", hTimeSim_DD4hep_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_DD4hep_ErrorLow_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_DD4hep_ErrorUp_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_DD4hep_Xtalk10_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_DD4hep_Xtalk18_QGSP_BERT);

  hTimeSim_DD4hep->Rebin(4);
  hTimeSim_DD4hep_ErrorLow->Rebin(4);
  hTimeSim_DD4hep_ErrorUp->Rebin(4);
  hTimeSim_DD4hep_Xtalk10->Rebin(4);
  hTimeSim_DD4hep_Xtalk18->Rebin(4);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kRed);
  hTimeSim_DD4hep->SetMarkerColor(kRed);
  hTimeSim_DD4hep->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(hTimeSim_DD4hep->GetXaxis()->FindBin(-50), hTimeSim_DD4hep->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_DD4hep_QBBC->Rebin(4);
  hTimeSim_DD4hep_QBBC->Sumw2();

  hTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_QBBC->Scale(1./hTimeSim_DD4hep_QBBC->Integral(hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QBBC->Scale(1./hTimeSim_DD4hep_ErrorLow_QBBC->Integral(hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QBBC->Scale(1./hTimeSim_DD4hep_ErrorUp_QBBC->Integral(hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk10_QBBC->Integral(hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk18_QBBC->Integral(hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_DD4hep_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_QGSP_BERT->Scale(1./hTimeSim_DD4hep_QGSP_BERT->Integral(hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kRed);
  gTimeSim_DD4hep->SetMarkerColor(kRed);
  gTimeSim_DD4hep->SetFillColor(kRed);
  gTimeSim_DD4hep->SetLineWidth(2);
  gTimeSim_DD4hep->SetLineStyle(2);
  gTimeSim_DD4hep->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep->GetBinContent(ibin);

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_DD4hep_QBBC = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetFillColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetLineWidth(2);
  gTimeSim_DD4hep_QBBC->SetLineStyle(2);
  gTimeSim_DD4hep_QBBC->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QBBC->GetBinContent(ibin);

    gTimeSim_DD4hep_QBBC->SetPoint(ibin, hTimeSim_DD4hep_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_DD4hep_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);
  gTimeSim_DD4hep_QGSP_BERT->SetLineStyle(2);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_DD4hep_QGSP_BERT->SetPoint(ibin, hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->SetHeader("Mokka");
  leg3->AddEntry(gTimeData, "Data", "pf");
  leg3->AddEntry(gTimeSim_QGSP_BERT, "QGSP_BERT", "epl");
  leg3->AddEntry(gTimeSim, "QGSP_BERT_HP", "epl");
  leg3->AddEntry(gTimeSim_QBBC, "QBBC", "epl");

  TLegend* leg4 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.028);
  leg4->SetHeader("DD4hep");
  leg4->AddEntry(gTimeSim_DD4hep_QGSP_BERT, "QGSP_BERT", "epl");
  leg4->AddEntry(gTimeSim_DD4hep, "QGSP_BERT_HP", "epl");
  leg4->AddEntry(gTimeSim_DD4hep_QBBC, "QBBC", "epl");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("50 GeV #pi^{-} - steel");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(gTimeSim);
  multi->Add(gTimeSim_QGSP_BERT);
  multi->Add(gTimeSim_QBBC);
  multi->Add(gTimeSim_DD4hep);
  multi->Add(gTimeSim_DD4hep_QGSP_BERT);
  multi->Add(gTimeSim_DD4hep_QBBC);

  TCanvas *c = new TCanvas("c1", "", 800, 600);
  gPad->SetLogy();
  gTimeData->Draw("APL");
  gTimeData->GetXaxis()->SetTitle("Time of first hit [ns]");
  gTimeData->GetYaxis()->SetTitle("Fraction of hits");
  gTimeData->GetXaxis()->SetRangeUser(-50, 200);
  gTimeData->GetYaxis()->SetRangeUser(1e-6, 10);
  gTimeData->Draw("E3");
  multi->Draw("PEL");
  //hData->GetXaxis()->SetRangeUser(-50, 200);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  leg4->Draw("same");
  pt->Draw("same");

  c->SaveAs("Plots/Comparison_SimData_Pion50GeV_LateClusters.pdf");
}

void TimingPions_70GeV()
{
  CaliceStyle();

  TString MokkaFile;
  MokkaFile = "Rootfiles/TimingMokkaAdd_70GeV.root";

  TFile *f = new TFile(MokkaFile, "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  //QBBC
  TH1F* hTimeSim_QBBC, *hTimeSim_ErrorLow_QBBC, *hTimeSim_ErrorUp_QBBC, *hTimeSim_Xtalk10_QBBC, *hTimeSim_Xtalk18_QBBC;
  f->GetObject("hTimeSim_QBBC", hTimeSim_QBBC);
  f->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_ErrorLow_QBBC);
  f->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_ErrorUp_QBBC);
  f->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_Xtalk10_QBBC);
  f->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_QGSP_BERT, *hTimeSim_ErrorLow_QGSP_BERT, *hTimeSim_ErrorUp_QGSP_BERT, *hTimeSim_Xtalk10_QGSP_BERT, *hTimeSim_Xtalk18_QGSP_BERT;
  f->GetObject("hTimeSim_QGSP_BERT", hTimeSim_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_ErrorLow_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_ErrorUp_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_Xtalk10_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_Xtalk18_QGSP_BERT);

  hTimeSim->Rebin(4);
  hTimeSim_ErrorLow->Rebin(4);
  hTimeSim_ErrorUp->Rebin(4);
  hTimeSim_Xtalk10->Rebin(4);
  hTimeSim_Xtalk18->Rebin(4);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(hTimeSim->GetXaxis()->FindBin(-50), hTimeSim->GetXaxis()->FindBin(200), "width"));
  hTimeSim->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(hTimeSim_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(hTimeSim_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(hTimeSim_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(hTimeSim_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_QBBC->Rebin(4);
  hTimeSim_QBBC->Sumw2();

  hTimeSim_QBBC->SetLineColor(kBlue);
  hTimeSim_QBBC->SetMarkerColor(kBlue);
  hTimeSim_QBBC->SetLineWidth(2);

  hTimeSim_QBBC->Scale(1./hTimeSim_QBBC->Integral(hTimeSim_QBBC->GetXaxis()->FindBin(-50), hTimeSim_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QBBC->Rebin(4);
  hTimeSim_ErrorLow_QBBC->Sumw2();

  hTimeSim_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_ErrorLow_QBBC->Scale(1./hTimeSim_ErrorLow_QBBC->Integral(hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QBBC->Rebin(4);
  hTimeSim_ErrorUp_QBBC->Sumw2();

  hTimeSim_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_ErrorUp_QBBC->Scale(1./hTimeSim_ErrorUp_QBBC->Integral(hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QBBC->Rebin(4);
  hTimeSim_Xtalk10_QBBC->Sumw2();

  hTimeSim_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk10_QBBC->Scale(1./hTimeSim_Xtalk10_QBBC->Integral(hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QBBC->Rebin(4);
  hTimeSim_Xtalk18_QBBC->Sumw2();

  hTimeSim_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk18_QBBC->Scale(1./hTimeSim_Xtalk18_QBBC->Integral(hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_QGSP_BERT->Rebin(4);
  hTimeSim_QGSP_BERT->Sumw2();

  hTimeSim_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_QGSP_BERT->SetLineWidth(2);

  hTimeSim_QGSP_BERT->Scale(1./hTimeSim_QGSP_BERT->Integral(hTimeSim_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_ErrorLow_QGSP_BERT->Integral(hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_ErrorUp_QGSP_BERT->Integral(hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_Xtalk10_QGSP_BERT->Integral(hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_Xtalk18_QGSP_BERT->Integral(hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  TString PATH;
  PATH = "/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/70GeV/Data/Timing_LateClusters/Rootfiles/Timing_FullAHCAL.root";
  TFile *f2 = new TFile(PATH, "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Pion", hData);

  hData->Rebin(4);
  hData->Sumw2();
  hData->Scale(1./hData->Integral(hData->GetXaxis()->FindBin(-50), hData->GetXaxis()->FindBin(200), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = (0.20+0.10)*content;

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetMarkerColor(kRed);
  gTimeSim->SetFillColor(kRed);
  gTimeSim->SetLineWidth(2);
  gTimeSim->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
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
    double error_syst = 0.00*hTimeSim->GetBinContent(ibin);

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_QBBC = new TGraphAsymmErrors();
  gTimeSim_QBBC->SetLineColor(kBlue);
  gTimeSim_QBBC->SetMarkerColor(kBlue);
  gTimeSim_QBBC->SetFillColor(kBlue);
  gTimeSim_QBBC->SetLineWidth(2);
  gTimeSim_QBBC->SetLineStyle(1);
  gTimeSim_QBBC->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QBBC->GetBinContent(ibin);

    gTimeSim_QBBC->SetPoint(ibin, hTimeSim_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_QGSP_BERT->SetLineWidth(2);
  gTimeSim_QGSP_BERT->SetLineStyle(1);
  gTimeSim_QGSP_BERT->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_QGSP_BERT->SetPoint(ibin, hTimeSim_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TString DD4hepFile;
  DD4hepFile = "Rootfiles/TimingDD4hepAdd_70GeV.root";

  TFile *f3 = new TFile(DD4hepFile, "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F* hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  //QBBC
  TH1F* hTimeSim_DD4hep_QBBC, *hTimeSim_DD4hep_ErrorLow_QBBC, *hTimeSim_DD4hep_ErrorUp_QBBC, *hTimeSim_DD4hep_Xtalk10_QBBC, *hTimeSim_DD4hep_Xtalk18_QBBC;
  f3->GetObject("hTimeSim_QBBC", hTimeSim_DD4hep_QBBC);
  f3->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_DD4hep_ErrorLow_QBBC);
  f3->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_DD4hep_ErrorUp_QBBC);
  f3->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_DD4hep_Xtalk10_QBBC);
  f3->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_DD4hep_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_DD4hep_QGSP_BERT, *hTimeSim_DD4hep_ErrorLow_QGSP_BERT, *hTimeSim_DD4hep_ErrorUp_QGSP_BERT, *hTimeSim_DD4hep_Xtalk10_QGSP_BERT, *hTimeSim_DD4hep_Xtalk18_QGSP_BERT;
  f3->GetObject("hTimeSim_QGSP_BERT", hTimeSim_DD4hep_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_DD4hep_ErrorLow_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_DD4hep_ErrorUp_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_DD4hep_Xtalk10_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_DD4hep_Xtalk18_QGSP_BERT);

  hTimeSim_DD4hep->Rebin(4);
  hTimeSim_DD4hep_ErrorLow->Rebin(4);
  hTimeSim_DD4hep_ErrorUp->Rebin(4);
  hTimeSim_DD4hep_Xtalk10->Rebin(4);
  hTimeSim_DD4hep_Xtalk18->Rebin(4);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kRed);
  hTimeSim_DD4hep->SetMarkerColor(kRed);
  hTimeSim_DD4hep->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(hTimeSim_DD4hep->GetXaxis()->FindBin(-50), hTimeSim_DD4hep->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_DD4hep_QBBC->Rebin(4);
  hTimeSim_DD4hep_QBBC->Sumw2();

  hTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_QBBC->Scale(1./hTimeSim_DD4hep_QBBC->Integral(hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QBBC->Scale(1./hTimeSim_DD4hep_ErrorLow_QBBC->Integral(hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QBBC->Scale(1./hTimeSim_DD4hep_ErrorUp_QBBC->Integral(hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk10_QBBC->Integral(hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk18_QBBC->Integral(hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_DD4hep_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_QGSP_BERT->Scale(1./hTimeSim_DD4hep_QGSP_BERT->Integral(hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kRed);
  gTimeSim_DD4hep->SetMarkerColor(kRed);
  gTimeSim_DD4hep->SetFillColor(kRed);
  gTimeSim_DD4hep->SetLineWidth(2);
  gTimeSim_DD4hep->SetLineStyle(2);
  gTimeSim_DD4hep->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep->GetBinContent(ibin);

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_DD4hep_QBBC = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetFillColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetLineWidth(2);
  gTimeSim_DD4hep_QBBC->SetLineStyle(2);
  gTimeSim_DD4hep_QBBC->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QBBC->GetBinContent(ibin);

    gTimeSim_DD4hep_QBBC->SetPoint(ibin, hTimeSim_DD4hep_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_DD4hep_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);
  gTimeSim_DD4hep_QGSP_BERT->SetLineStyle(2);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_DD4hep_QGSP_BERT->SetPoint(ibin, hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->SetHeader("Mokka");
  leg3->AddEntry(gTimeData, "Data", "pf");
  leg3->AddEntry(gTimeSim_QGSP_BERT, "QGSP_BERT", "epl");
  leg3->AddEntry(gTimeSim, "QGSP_BERT_HP", "epl");
  leg3->AddEntry(gTimeSim_QBBC, "QBBC", "epl");

  TLegend* leg4 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.028);
  leg4->SetHeader("DD4hep");
  leg4->AddEntry(gTimeSim_DD4hep_QGSP_BERT, "QGSP_BERT", "epl");
  leg4->AddEntry(gTimeSim_DD4hep, "QGSP_BERT_HP", "epl");
  leg4->AddEntry(gTimeSim_DD4hep_QBBC, "QBBC", "epl");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("70 GeV #pi^{-} - steel");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(gTimeSim);
  multi->Add(gTimeSim_QGSP_BERT);
  multi->Add(gTimeSim_QBBC);
  multi->Add(gTimeSim_DD4hep);
  multi->Add(gTimeSim_DD4hep_QGSP_BERT);
  multi->Add(gTimeSim_DD4hep_QBBC);

  TCanvas *c = new TCanvas("c1", "", 800, 600);
  gPad->SetLogy();
  gTimeData->Draw("APL");
  gTimeData->GetXaxis()->SetTitle("Time of first hit [ns]");
  gTimeData->GetYaxis()->SetTitle("Fraction of hits");
  gTimeData->GetXaxis()->SetRangeUser(-50, 200);
  gTimeData->GetYaxis()->SetRangeUser(1e-6, 10);
  gTimeData->Draw("E3");
  multi->Draw("PEL");
  //hData->GetXaxis()->SetRangeUser(-50, 200);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  leg4->Draw("same");
  pt->Draw("same");

  c->SaveAs("Plots/Comparison_SimData_Pion70GeV_LateClusters.pdf");
}

void TimingPions_90GeV()
{
  CaliceStyle();

  TString MokkaFile;
  MokkaFile = "Rootfiles/TimingMokkaAdd_90GeV.root";

  TFile *f = new TFile(MokkaFile, "OPEN");
  TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;
  TH1F* hTimeSim_Xtalk10, *hTimeSim_Xtalk18;

  f->GetObject("hTimeSim", hTimeSim);
  f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
  f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);
  f->GetObject("hTimeSim_Xtalk10", hTimeSim_Xtalk10);
  f->GetObject("hTimeSim_Xtalk18", hTimeSim_Xtalk18);

  //QBBC
  TH1F* hTimeSim_QBBC, *hTimeSim_ErrorLow_QBBC, *hTimeSim_ErrorUp_QBBC, *hTimeSim_Xtalk10_QBBC, *hTimeSim_Xtalk18_QBBC;
  f->GetObject("hTimeSim_QBBC", hTimeSim_QBBC);
  f->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_ErrorLow_QBBC);
  f->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_ErrorUp_QBBC);
  f->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_Xtalk10_QBBC);
  f->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_QGSP_BERT, *hTimeSim_ErrorLow_QGSP_BERT, *hTimeSim_ErrorUp_QGSP_BERT, *hTimeSim_Xtalk10_QGSP_BERT, *hTimeSim_Xtalk18_QGSP_BERT;
  f->GetObject("hTimeSim_QGSP_BERT", hTimeSim_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_ErrorLow_QGSP_BERT);
  f->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_ErrorUp_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_Xtalk10_QGSP_BERT);
  f->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_Xtalk18_QGSP_BERT);

  hTimeSim->Rebin(4);
  hTimeSim_ErrorLow->Rebin(4);
  hTimeSim_ErrorUp->Rebin(4);
  hTimeSim_Xtalk10->Rebin(4);
  hTimeSim_Xtalk18->Rebin(4);

  hTimeSim->Sumw2();
  hTimeSim_ErrorLow->Sumw2();
  hTimeSim_ErrorUp->Sumw2();
  hTimeSim_Xtalk10->Sumw2();
  hTimeSim_Xtalk18->Sumw2();

  hTimeSim->SetLineColor(kRed);
  hTimeSim->SetMarkerColor(kRed);
  hTimeSim->SetLineWidth(2);

  hTimeSim->Scale(1./hTimeSim->Integral(hTimeSim->GetXaxis()->FindBin(-50), hTimeSim->GetXaxis()->FindBin(200), "width"));
  hTimeSim->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow->SetLineColor(kBlue);
  hTimeSim_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_ErrorLow->SetLineWidth(2);

  hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(hTimeSim_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp->SetLineColor(kGreen);
  hTimeSim_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp->SetLineWidth(2);

  hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(hTimeSim_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_Xtalk10->SetLineWidth(2);

  hTimeSim_Xtalk10->Scale(1./hTimeSim_Xtalk10->Integral(hTimeSim_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_Xtalk18->SetLineWidth(2);

  hTimeSim_Xtalk18->Scale(1./hTimeSim_Xtalk18->Integral(hTimeSim_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_QBBC->Rebin(4);
  hTimeSim_QBBC->Sumw2();

  hTimeSim_QBBC->SetLineColor(kBlue);
  hTimeSim_QBBC->SetMarkerColor(kBlue);
  hTimeSim_QBBC->SetLineWidth(2);

  hTimeSim_QBBC->Scale(1./hTimeSim_QBBC->Integral(hTimeSim_QBBC->GetXaxis()->FindBin(-50), hTimeSim_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QBBC->Rebin(4);
  hTimeSim_ErrorLow_QBBC->Sumw2();

  hTimeSim_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_ErrorLow_QBBC->Scale(1./hTimeSim_ErrorLow_QBBC->Integral(hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QBBC->Rebin(4);
  hTimeSim_ErrorUp_QBBC->Sumw2();

  hTimeSim_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_ErrorUp_QBBC->Scale(1./hTimeSim_ErrorUp_QBBC->Integral(hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QBBC->Rebin(4);
  hTimeSim_Xtalk10_QBBC->Sumw2();

  hTimeSim_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk10_QBBC->Scale(1./hTimeSim_Xtalk10_QBBC->Integral(hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QBBC->Rebin(4);
  hTimeSim_Xtalk18_QBBC->Sumw2();

  hTimeSim_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_Xtalk18_QBBC->Scale(1./hTimeSim_Xtalk18_QBBC->Integral(hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_QGSP_BERT->Rebin(4);
  hTimeSim_QGSP_BERT->Sumw2();

  hTimeSim_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_QGSP_BERT->SetLineWidth(2);

  hTimeSim_QGSP_BERT->Scale(1./hTimeSim_QGSP_BERT->Integral(hTimeSim_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_ErrorLow_QGSP_BERT->Integral(hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_ErrorUp_QGSP_BERT->Integral(hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_Xtalk10_QGSP_BERT->Integral(hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_Xtalk18_QGSP_BERT->Integral(hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  TString PATH;
  PATH = "/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/90GeV/Data/Timing_LateClusters/Rootfiles/Timing_FullAHCAL.root";
  TFile *f2 = new TFile(PATH, "OPEN");
  TH1F* hData;

  f2->GetObject("Timing_AHCAL_Pion", hData);

  hData->Rebin(4);
  hData->Sumw2();
  hData->Scale(1./hData->Integral(hData->GetXaxis()->FindBin(-50), hData->GetXaxis()->FindBin(200), "width"));
  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(0.8);

  TGraphAsymmErrors *gTimeData = new TGraphAsymmErrors();
  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hData->GetNbinsX(); ibin++)
  {
    double content = hData->GetBinContent(ibin);
    double error_stat = hData->GetBinError(ibin);

    double error_syst = (0.20+0.10)*content;

    gTimeData->SetPoint(ibin, hData->GetXaxis()->GetBinCenter(ibin), content);
    gTimeData->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat));
  }

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim = new TGraphAsymmErrors();
  gTimeSim->SetLineColor(kRed);
  gTimeSim->SetMarkerColor(kRed);
  gTimeSim->SetFillColor(kRed);
  gTimeSim->SetLineWidth(2);
  gTimeSim->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim->GetNbinsX(); ibin++)
  {
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
    double error_syst = 0.00*hTimeSim->GetBinContent(ibin);

    gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_QBBC = new TGraphAsymmErrors();
  gTimeSim_QBBC->SetLineColor(kBlue);
  gTimeSim_QBBC->SetMarkerColor(kBlue);
  gTimeSim_QBBC->SetFillColor(kBlue);
  gTimeSim_QBBC->SetLineWidth(2);
  gTimeSim_QBBC->SetLineStyle(1);
  gTimeSim_QBBC->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QBBC->GetBinContent(ibin);

    gTimeSim_QBBC->SetPoint(ibin, hTimeSim_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_QGSP_BERT->SetLineWidth(2);
  gTimeSim_QGSP_BERT->SetLineStyle(1);
  gTimeSim_QGSP_BERT->SetMarkerStyle(20);

  for(int ibin = 0; ibin < hTimeSim_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_QGSP_BERT->SetPoint(ibin, hTimeSim_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TString DD4hepFile;
  DD4hepFile = "Rootfiles/TimingDD4hepAdd_90GeV.root";

  TFile *f3 = new TFile(DD4hepFile, "OPEN");
  TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;
  TH1F* hTimeSim_DD4hep_Xtalk10, *hTimeSim_DD4hep_Xtalk18;

  f3->GetObject("hTimeSim", hTimeSim_DD4hep);
  f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
  f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);
  f3->GetObject("hTimeSim_Xtalk10", hTimeSim_DD4hep_Xtalk10);
  f3->GetObject("hTimeSim_Xtalk18", hTimeSim_DD4hep_Xtalk18);

  //QBBC
  TH1F* hTimeSim_DD4hep_QBBC, *hTimeSim_DD4hep_ErrorLow_QBBC, *hTimeSim_DD4hep_ErrorUp_QBBC, *hTimeSim_DD4hep_Xtalk10_QBBC, *hTimeSim_DD4hep_Xtalk18_QBBC;
  f3->GetObject("hTimeSim_QBBC", hTimeSim_DD4hep_QBBC);
  f3->GetObject("hTimeSim_ErrorLow_QBBC", hTimeSim_DD4hep_ErrorLow_QBBC);
  f3->GetObject("hTimeSim_ErrorUp_QBBC", hTimeSim_DD4hep_ErrorUp_QBBC);
  f3->GetObject("hTimeSim_Xtalk10_QBBC", hTimeSim_DD4hep_Xtalk10_QBBC);
  f3->GetObject("hTimeSim_Xtalk18_QBBC", hTimeSim_DD4hep_Xtalk18_QBBC);

  //QGSP_BERT
  TH1F* hTimeSim_DD4hep_QGSP_BERT, *hTimeSim_DD4hep_ErrorLow_QGSP_BERT, *hTimeSim_DD4hep_ErrorUp_QGSP_BERT, *hTimeSim_DD4hep_Xtalk10_QGSP_BERT, *hTimeSim_DD4hep_Xtalk18_QGSP_BERT;
  f3->GetObject("hTimeSim_QGSP_BERT", hTimeSim_DD4hep_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorLow_QGSP_BERT", hTimeSim_DD4hep_ErrorLow_QGSP_BERT);
  f3->GetObject("hTimeSim_ErrorUp_QGSP_BERT", hTimeSim_DD4hep_ErrorUp_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk10_QGSP_BERT", hTimeSim_DD4hep_Xtalk10_QGSP_BERT);
  f3->GetObject("hTimeSim_Xtalk18_QGSP_BERT", hTimeSim_DD4hep_Xtalk18_QGSP_BERT);

  hTimeSim_DD4hep->Rebin(4);
  hTimeSim_DD4hep_ErrorLow->Rebin(4);
  hTimeSim_DD4hep_ErrorUp->Rebin(4);
  hTimeSim_DD4hep_Xtalk10->Rebin(4);
  hTimeSim_DD4hep_Xtalk18->Rebin(4);

  hTimeSim_DD4hep->Sumw2();
  hTimeSim_DD4hep_ErrorLow->Sumw2();
  hTimeSim_DD4hep_ErrorUp->Sumw2();
  hTimeSim_DD4hep_Xtalk10->Sumw2();
  hTimeSim_DD4hep_Xtalk18->Sumw2();

  hTimeSim_DD4hep->SetLineColor(kRed);
  hTimeSim_DD4hep->SetMarkerColor(kRed);
  hTimeSim_DD4hep->SetLineWidth(2);

  hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(hTimeSim_DD4hep->GetXaxis()->FindBin(-50), hTimeSim_DD4hep->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow->SetLineColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_ErrorLow->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10->SetLineColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetMarkerColor(kMagenta);
  hTimeSim_DD4hep_Xtalk10->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10->Scale(1./hTimeSim_DD4hep_Xtalk10->Integral(hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18->SetLineColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetMarkerColor(kOrange+1);
  hTimeSim_DD4hep_Xtalk18->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18->Scale(1./hTimeSim_DD4hep_Xtalk18->Integral(hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18->GetYaxis()->SetTitle("Fraction of hits");

  //QBBC
  hTimeSim_DD4hep_QBBC->Rebin(4);
  hTimeSim_DD4hep_QBBC->Sumw2();

  hTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  hTimeSim_DD4hep_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_QBBC->Scale(1./hTimeSim_DD4hep_QBBC->Integral(hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QBBC->Scale(1./hTimeSim_DD4hep_ErrorLow_QBBC->Integral(hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QBBC->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QBBC->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QBBC->Scale(1./hTimeSim_DD4hep_ErrorUp_QBBC->Integral(hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk10_QBBC->Integral(hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QBBC->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QBBC->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QBBC->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QBBC->Scale(1./hTimeSim_DD4hep_Xtalk18_QBBC->Integral(hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QBBC->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QBBC->GetYaxis()->SetTitle("Fraction of hits");

  //-------------------------------------------------

  //QGSP_BERT
  hTimeSim_DD4hep_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_QGSP_BERT->Scale(1./hTimeSim_DD4hep_QGSP_BERT->Integral(hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorLow_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Scale(1./hTimeSim_DD4hep_ErrorUp_QGSP_BERT->Integral(hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk10_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Rebin(4);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Sumw2();

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetMarkerColor(kGreen);
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->SetLineWidth(2);

  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Scale(1./hTimeSim_DD4hep_Xtalk18_QGSP_BERT->Integral(hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(-50), hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetXaxis()->FindBin(200), "width"));
  hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetYaxis()->SetTitle("Fraction of hits");

  //------------------- Handle Bin Errors ----------------------------------

  TGraphAsymmErrors *gTimeSim_DD4hep = new TGraphAsymmErrors();
  gTimeSim_DD4hep->SetLineColor(kRed);
  gTimeSim_DD4hep->SetMarkerColor(kRed);
  gTimeSim_DD4hep->SetFillColor(kRed);
  gTimeSim_DD4hep->SetLineWidth(2);
  gTimeSim_DD4hep->SetLineStyle(2);
  gTimeSim_DD4hep->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep->GetBinContent(ibin);

    gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QBBC
  TGraphAsymmErrors *gTimeSim_DD4hep_QBBC = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QBBC->SetLineColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetMarkerColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetFillColor(kBlue);
  gTimeSim_DD4hep_QBBC->SetLineWidth(2);
  gTimeSim_DD4hep_QBBC->SetLineStyle(2);
  gTimeSim_DD4hep_QBBC->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QBBC->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QBBC->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QBBC->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QBBC->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QBBC->GetBinContent(ibin);

    gTimeSim_DD4hep_QBBC->SetPoint(ibin, hTimeSim_DD4hep_QBBC->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QBBC->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //QGSP_BERT
  TGraphAsymmErrors *gTimeSim_DD4hep_QGSP_BERT = new TGraphAsymmErrors();
  gTimeSim_DD4hep_QGSP_BERT->SetLineColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetFillColor(kGreen);
  gTimeSim_DD4hep_QGSP_BERT->SetLineWidth(2);
  gTimeSim_DD4hep_QGSP_BERT->SetLineStyle(2);
  gTimeSim_DD4hep_QGSP_BERT->SetMarkerStyle(22);

  for(int ibin = 0; ibin < hTimeSim_DD4hep_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);
    double content_low = hTimeSim_DD4hep_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = hTimeSim_DD4hep_ErrorUp_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = hTimeSim_DD4hep_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = hTimeSim_DD4hep_Xtalk18_QGSP_BERT->GetBinContent(ibin);

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

    double error_stat = hTimeSim_DD4hep_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.00*hTimeSim_DD4hep_QGSP_BERT->GetBinContent(ibin);

    gTimeSim_DD4hep_QGSP_BERT->SetPoint(ibin, hTimeSim_DD4hep_QGSP_BERT->GetXaxis()->GetBinCenter(ibin), content);
    gTimeSim_DD4hep_QGSP_BERT->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up + error_syst*error_syst));
  }

  //------------------------------------------------------------

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->SetHeader("Mokka");
  leg3->AddEntry(gTimeData, "Data", "pf");
  leg3->AddEntry(gTimeSim_QGSP_BERT, "QGSP_BERT", "epl");
  leg3->AddEntry(gTimeSim, "QGSP_BERT_HP", "epl");
  leg3->AddEntry(gTimeSim_QBBC, "QBBC", "epl");

  TLegend* leg4 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.028);
  leg4->SetHeader("DD4hep");
  leg4->AddEntry(gTimeSim_DD4hep_QGSP_BERT, "QGSP_BERT", "epl");
  leg4->AddEntry(gTimeSim_DD4hep, "QGSP_BERT_HP", "epl");
  leg4->AddEntry(gTimeSim_DD4hep_QBBC, "QBBC", "epl");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("90 GeV #pi^{-} - steel");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(gTimeSim);
  multi->Add(gTimeSim_QGSP_BERT);
  multi->Add(gTimeSim_QBBC);
  multi->Add(gTimeSim_DD4hep);
  multi->Add(gTimeSim_DD4hep_QGSP_BERT);
  multi->Add(gTimeSim_DD4hep_QBBC);

  TCanvas *c = new TCanvas("c1", "", 800, 600);
  gPad->SetLogy();
  gTimeData->Draw("APL");
  gTimeData->GetXaxis()->SetTitle("Time of first hit [ns]");
  gTimeData->GetYaxis()->SetTitle("Fraction of hits");
  gTimeData->GetXaxis()->SetRangeUser(-50, 200);
  gTimeData->GetYaxis()->SetRangeUser(1e-6, 10);
  gTimeData->Draw("E3");
  multi->Draw("PEL");
  //hData->GetXaxis()->SetRangeUser(-50, 200);
  hData->Draw("ep hist same");
  leg3->Draw("same");
  leg4->Draw("same");
  pt->Draw("same");

  c->SaveAs("Plots/Comparison_SimData_Pion90GeV_LateClusters.pdf");
}

void BeamProfile_10GeV()
{
  CaliceStyle();

  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/10GeV/Data/SelectionCuts/Rootfiles/BeamProfile10GeV.root", "OPEN");
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
  leg->SetHeader("AHCAL #pi- 10 GeV");
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

  c2->SaveAs("Plots/Run24306_CoGX_AHCAL_10GeV_Comparison.pdf");
  c3->SaveAs("Plots/Run24306_CoGY_AHCAL_10GeV_Comparison.pdf");
}

void BeamProfile_90GeV()
{
  CaliceStyle();

  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/90GeV/Data/SelectionCuts/Rootfiles/BeamProfile90GeV.root", "OPEN");
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

  TFile *f2 = new TFile("Rootfiles/BeamProfile90GeV_Sim.root", "OPEN");
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
  leg->SetHeader("AHCAL #pi- 90 GeV");
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

  c2->SaveAs("Plots/Run24332_CoGX_AHCAL_90GeV_Comparison.pdf");
  c3->SaveAs("Plots/Run24332_CoGY_AHCAL_90GeV_Comparison.pdf");
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
  hHitsCoGZ_Muons->GetYaxis()->SetRangeUser(0, 300);

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
  line->SetX1(0.);
  line->SetX2(800.);
  line->SetY1(20.);
  line->SetY2(20.);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);

  TCanvas *c1 = new TCanvas("c1", "nHits vs CoG Z", 800, 600);
  hHitsCoGZ_Muons->Draw("BOX");
  hHitsCoGZ_Electrons->Draw("BOX same");
  hHitsCoGZ_Pions->Draw("BOX same");
  line->Draw("same");
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
  hRatio_Muons->GetYaxis()->SetTitle("Fraction of events");

  hRatio_Electrons->Scale(1./hRatio_Electrons->Integral());
  hRatio_Electrons->SetLineColor(kGreen);
  hRatio_Electrons->SetLineWidth(2);
  hRatio_Electrons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Electrons->GetYaxis()->SetTitle("Fraction of events");
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

  TH1F *hHitsFirst2_Muons, *hHitsFirst2_Electrons, *hHitsFirst2_Pions;

  f->GetObject("hHitsFirst2_Muons", hHitsFirst2_Muons);
  f->GetObject("hHitsFirst2_Electrons", hHitsFirst2_Electrons);
  f->GetObject("hHitsFirst2_Pions", hHitsFirst2_Pions);

  hHitsFirst2_Muons->Scale(1./hHitsFirst2_Muons->Integral());
  hHitsFirst2_Muons->SetLineColor(kBlue);
  hHitsFirst2_Muons->SetLineWidth(2);
  hHitsFirst2_Muons->GetXaxis()->SetTitle("N_{3}+N_{4}");
  hHitsFirst2_Muons->GetYaxis()->SetTitle("Fraction of events");
  hHitsFirst2_Muons->GetYaxis()->SetRangeUser(0.00001, 1);

  hHitsFirst2_Electrons->Scale(1./hHitsFirst2_Electrons->Integral());
  hHitsFirst2_Electrons->SetLineColor(kGreen);
  hHitsFirst2_Electrons->SetLineWidth(2);

  hHitsFirst2_Pions->Scale(1./hHitsFirst2_Pions->Integral());
  hHitsFirst2_Pions->SetLineColor(kRed);
  hHitsFirst2_Pions->SetLineWidth(2);

  TLine *line8 = new TLine();
  line8->SetX1(5.);
  line8->SetX2(5.);
  line8->SetY1(0.);
  line8->SetY2(1.);
  line8->SetLineColor(kBlack);
  line8->SetLineWidth(3);

  TCanvas *c4 = new TCanvas("c4", "Number of hits int two first layers", 800, 600);
  gPad->SetLogy();
  hHitsFirst2_Muons->Draw("hist");
  hHitsFirst2_Electrons->Draw("hist same");
  hHitsFirst2_Pions->Draw("hist same");
  leg->Draw("same");
  line8->Draw("same");

  c4->SaveAs("Plots/SelectionCut_N3N4_10GeV.pdf");
}

void SelectionCuts_90GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/SelectionCuts_90GeV.root", "OPEN");
  TH2F *hHitsCoGZ_Muons, *hHitsCoGZ_Electrons, *hHitsCoGZ_Pions;

  f->GetObject("hHitsCoGZ_Muons", hHitsCoGZ_Muons);
  f->GetObject("hHitsCoGZ_Electrons", hHitsCoGZ_Electrons);
  f->GetObject("hHitsCoGZ_Pions", hHitsCoGZ_Pions);

  hHitsCoGZ_Muons->SetLineColor(kBlue);
  hHitsCoGZ_Muons->SetLineWidth(2);
  hHitsCoGZ_Muons->GetXaxis()->SetTitle("AHCAL CoG Z [mm]");
  hHitsCoGZ_Muons->GetYaxis()->SetTitle("nHits");
  hHitsCoGZ_Muons->GetYaxis()->SetRangeUser(0, 300);

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
  line->SetX1(0.);
  line->SetX2(800.);
  line->SetY1(20.);
  line->SetY2(20.);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);

  TCanvas *c1 = new TCanvas("c1", "nHits vs CoG Z", 800, 600);
  hHitsCoGZ_Muons->Draw("BOX");
  hHitsCoGZ_Electrons->Draw("BOX same");
  hHitsCoGZ_Pions->Draw("BOX same");
  line->Draw("same");
  leg->Draw("same");

  c1->SaveAs("Plots/SelectionCut_nHitsCoGZ_90GeV.pdf");

  //******************************************************//

  TH1F *hRatio_Muons, *hRatio_Electrons, *hRatio_Pions;

  f->GetObject("hRatio_Muons", hRatio_Muons);
  f->GetObject("hRatio_Electrons", hRatio_Electrons);
  f->GetObject("hRatio_Pions", hRatio_Pions);

  hRatio_Muons->Scale(1./hRatio_Muons->Integral());
  hRatio_Muons->SetLineColor(kBlue);
  hRatio_Muons->SetLineWidth(2);
  hRatio_Muons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Muons->GetYaxis()->SetTitle("Fraction of events");

  hRatio_Electrons->Scale(1./hRatio_Electrons->Integral());
  hRatio_Electrons->SetLineColor(kGreen);
  hRatio_Electrons->SetLineWidth(2);
  hRatio_Electrons->GetXaxis()->SetTitle("(E_{13}+E_{14})/#sumE [%]");
  hRatio_Electrons->GetYaxis()->SetTitle("Fraction of events");
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

  c3->SaveAs("Plots/SelectionCut_EnergyLastLayers_90GeV.pdf");

  //******************************************************//

  TH1F *hHitsFirst2_Muons, *hHitsFirst2_Electrons, *hHitsFirst2_Pions;

  f->GetObject("hHitsFirst2_Muons", hHitsFirst2_Muons);
  f->GetObject("hHitsFirst2_Electrons", hHitsFirst2_Electrons);
  f->GetObject("hHitsFirst2_Pions", hHitsFirst2_Pions);

  hHitsFirst2_Muons->Scale(1./hHitsFirst2_Muons->Integral());
  hHitsFirst2_Muons->SetLineColor(kBlue);
  hHitsFirst2_Muons->SetLineWidth(2);
  hHitsFirst2_Muons->GetXaxis()->SetTitle("N_{3}+N_{4}");
  hHitsFirst2_Muons->GetYaxis()->SetTitle("Fraction of events");
  hHitsFirst2_Muons->GetYaxis()->SetRangeUser(0.00001, 1);

  hHitsFirst2_Electrons->Scale(1./hHitsFirst2_Electrons->Integral());
  hHitsFirst2_Electrons->SetLineColor(kGreen);
  hHitsFirst2_Electrons->SetLineWidth(2);

  hHitsFirst2_Pions->Scale(1./hHitsFirst2_Pions->Integral());
  hHitsFirst2_Pions->SetLineColor(kRed);
  hHitsFirst2_Pions->SetLineWidth(2);

  TLine *line8 = new TLine();
  line8->SetX1(5.);
  line8->SetX2(5.);
  line8->SetY1(0.);
  line8->SetY2(1.);
  line8->SetLineColor(kBlack);
  line8->SetLineWidth(3);

  TCanvas *c4 = new TCanvas("c4", "Number of hits int two first layers", 800, 600);
  gPad->SetLogy();
  hHitsFirst2_Muons->Draw("hist");
  hHitsFirst2_Electrons->Draw("hist same");
  hHitsFirst2_Pions->Draw("hist same");
  leg->Draw("same");
  line8->Draw("same");

  c4->SaveAs("Plots/SelectionCut_N3N4_90GeV.pdf");
}

void ShowerStartChecks()
{
  CaliceStyle();

  string PATH = "/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Pions/50GeV/Simulation/Reconstruction_2/Mokka/Rootfiles/Reco_Mokka_Run24578_pi-_50GeV_QGSP_BERT_HP_SingleLayerReso_Selected_Add_wNoiseFlat.root";

  int eventNumber;
  int runNumber;
  int ahc_nHits;
  int ShowerStartReco;
  int MCTruthShowerStart;

  TFile *f = new TFile(PATH.c_str(), "OPEN");
  TTree *tree = (TTree*)f->Get("bigtree");

  tree->SetBranchAddress("eventNumber", &eventNumber);
  tree->SetBranchAddress("runNumber", &runNumber);
  tree->SetBranchAddress("event_MCTruth_ShowerStartLayer", &MCTruthShowerStart);
  tree->SetBranchAddress("event_ShowerStartLayer", &ShowerStartReco);

  //--------------------

  TH1I *hMC_Reco_SS = new TH1I("hMC_Reco_SS", "hMC_Reco_SS", 120, -60, 60);
  hMC_Reco_SS->GetXaxis()->SetTitle("FHI Layer Difference (MC Truth - Reconstructed)");
  hMC_Reco_SS->GetYaxis()->SetTitle("Number of Events");
  hMC_Reco_SS->SetLineColor(kBlack);
  hMC_Reco_SS->SetLineWidth(2);

  TH2I *hMC_Reco_SS_2D = new TH2I("hMC_Reco_SS_2D", "hMC_Reco_SS_2D", 15, 0, 15, 15, 0, 15);
  hMC_Reco_SS_2D->GetXaxis()->SetTitle("FHI Layer (MC Truth)");
  hMC_Reco_SS_2D->GetYaxis()->SetTitle("FHI Layer (Reconstructed)");

  for(int itree = 0; itree < tree->GetEntries(); itree++)
  {
    tree->GetEntry(itree);

    if(MCTruthShowerStart == -1 || ShowerStartReco == -1 || ShowerStartReco == 0) continue;

    int ShowerStartRecoTemp = -1;

    if(MCTruthShowerStart > 11 || ShowerStartReco > 11) continue;

    if(ShowerStartReco == 12)
    ShowerStartRecoTemp = 13;
    else if(ShowerStartReco == 13)
    ShowerStartRecoTemp = 21;
    else if(ShowerStartReco == 14)
    ShowerStartRecoTemp = 31;
    else
    ShowerStartRecoTemp = ShowerStartReco;

    hMC_Reco_SS->Fill(MCTruthShowerStart - ShowerStartRecoTemp);
    hMC_Reco_SS_2D->Fill(MCTruthShowerStart, ShowerStartRecoTemp);
  }

  TPaveText *pt10 = new TPaveText(0.65, 0.75, 0.90, 0.90, "tbNDC");
  pt10->SetBorderSize(0);
  pt10->SetTextColor(15);
  pt10->SetFillColor(0);
  pt10->SetTextSize(0.04);
  pt10->SetTextAlign(12); //left center
  pt10->AddText("CALICE AHCAL");
  pt10->AddText("Work in progress");
  pt10->AddText("50 GeV #pi^{-}");

  TPaveText *pt11 = new TPaveText(0.65, 0.60, 0.90, 0.70, "tbNDC");
  pt11->SetBorderSize(0);
  pt11->SetTextColor(15);
  pt11->SetFillColor(0);
  pt11->SetTextSize(0.04);
  pt11->SetTextAlign(12); //left center
  pt11->AddText(TString::Format("#mu = %.2f", hMC_Reco_SS->GetMean()));
  pt11->AddText(TString::Format("RMS = %.2f", hMC_Reco_SS->GetRMS()));

  TF1 *line = new TF1("line", "x", 0, 15);
  line->SetLineColor(kBlack);
  line->SetLineStyle(2);
  line->SetLineWidth(2);

  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  gPad->SetLogy();
  hMC_Reco_SS->Draw();
  pt10->Draw("same");
  pt11->Draw("same");
  c1->SaveAs("Plots/ShowerStart_Difference_noOptimisation.pdf");

  TCanvas *c2 = new TCanvas("c2", "", 800, 600);
  gPad->SetLogz();
  hMC_Reco_SS_2D->Draw("COLZ");
  line->Draw("same");
  c2->SaveAs("Plots/ShowerStart_Difference_noOptimisation_2D.pdf");
}

void ComparisonTungstendNdt()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/ComparisondNdt_Tungsten.root", "OPEN");
  TH1F *hData;
  TH1D *hDataTungsten;
  TGraphAsymmErrors *gTimeData, *gTimeDataTungsten;

  f->GetObject("DataSteel", gTimeData);
  f->GetObject("DataTungsten", gTimeDataTungsten);
  f->GetObject("Timing_AHCAL_Pion", hData);
  f->GetObject("h_resolution_t0Time", hDataTungsten);

  hData->SetLineColor(kBlack);
  hData->SetMarkerColor(kBlack);
  hData->SetMarkerStyle(20);
  hData->SetMarkerSize(0.8);

  gTimeData->SetLineWidth(0);
  gTimeData->SetFillColor(kGray);
  gTimeData->SetMarkerStyle(20);

  hDataTungsten->SetLineColor(kBlue);
  hDataTungsten->SetMarkerColor(kBlue);
  hDataTungsten->SetMarkerStyle(20);
  hDataTungsten->SetMarkerSize(0.8);

  gTimeDataTungsten->SetLineWidth(0);
  gTimeDataTungsten->SetFillColor(kGray);
  gTimeDataTungsten->SetMarkerStyle(20);
  gTimeDataTungsten->SetMarkerColor(kBlue);

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->AddEntry(gTimeData, "Steel stack", "pf");
  leg3->AddEntry(gTimeDataTungsten, "Tungsten stack", "pf");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("50 GeV #pi^{-}");

  TCanvas *c1 = new TCanvas("c1", "dNdt", 800, 600);
  gPad->SetLogy();
  gTimeData->Draw("APL");
  gTimeData->GetXaxis()->SetTitle("Time of first hit [ns]");
  gTimeData->GetYaxis()->SetTitle("Fraction of hits");
  gTimeData->GetXaxis()->SetRangeUser(-50, 200);
  gTimeData->GetYaxis()->SetRangeUser(1e-6, 5);
  gTimeData->Draw("E3");
  gTimeDataTungsten->Draw("E3 same");
  hData->Draw("ep hist same");
  hDataTungsten->Draw("ep hist same");
  leg3->Draw("same");
  pt->Draw("same");

  c1->SaveAs("Plots/ComparisondNdt_SteelTungsten.pdf");
}

void ComparisonTungstenEnergy()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/ComparisonEnergy_Tungsten.root", "OPEN");
  TGraphErrors *gEnergyData_Pion50, *gEnergyDataTungsten_Pion50;

  f->GetObject("DataSteel", gEnergyData_Pion50);
  f->GetObject("DataTungsten", gEnergyDataTungsten_Pion50);

  gEnergyData_Pion50->SetMarkerSize(1);
  gEnergyData_Pion50->SetMarkerStyle(20);
  gEnergyData_Pion50->SetMarkerColor(kBlack);
  gEnergyData_Pion50->SetLineColor(kBlack);
  gEnergyData_Pion50->SetFillColor(kGray+1);
  gEnergyData_Pion50->SetFillStyle(3001);

  gEnergyDataTungsten_Pion50->SetMarkerSize(1);
  gEnergyDataTungsten_Pion50->SetMarkerStyle(20);
  gEnergyDataTungsten_Pion50->SetMarkerColor(kBlue);
  gEnergyDataTungsten_Pion50->SetLineColor(kBlue);
  gEnergyDataTungsten_Pion50->SetFillColor(kBlue+1);
  gEnergyDataTungsten_Pion50->SetFillStyle(3001);

  TLegend* leg3 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->AddEntry(gEnergyData_Pion50, "Steel stack", "pf");
  leg3->AddEntry(gEnergyDataTungsten_Pion50, "Tungsten stack", "pf");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("50 GeV #pi^{-}");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Pion50);
  multi2->Add(gEnergyDataTungsten_Pion50);

  TCanvas *c1 = new TCanvas("c1", "Time vs Energy", 800, 600);
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Deposition [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 12);
  multi2->Draw("E3");
  multi2->Draw("PX");
  leg3->Draw("same");
  pt->Draw("same");

  c1->SaveAs("Plots/ComparisonEnergy_SteelTungsten.pdf");
}

void ComparisonTungstenRadius()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/ComparisonRadius_Tungsten.root", "OPEN");
  TGraphErrors *gRadiusData_Pion50, *gRadiusDataTungsten_Pion50;

  f->GetObject("DataSteel", gRadiusData_Pion50);
  f->GetObject("DataTungsten", gRadiusDataTungsten_Pion50);

  gRadiusData_Pion50->SetMarkerSize(1);
  gRadiusData_Pion50->SetMarkerStyle(20);
  gRadiusData_Pion50->SetMarkerColor(kBlack);
  gRadiusData_Pion50->SetLineColor(kBlack);
  gRadiusData_Pion50->SetFillColor(kGray+1);
  gRadiusData_Pion50->SetFillStyle(3001);

  gRadiusDataTungsten_Pion50->SetMarkerSize(1);
  gRadiusDataTungsten_Pion50->SetMarkerStyle(20);
  gRadiusDataTungsten_Pion50->SetMarkerColor(kBlue);
  gRadiusDataTungsten_Pion50->SetLineColor(kBlue);
  gRadiusDataTungsten_Pion50->SetFillColor(kBlue+1);
  gRadiusDataTungsten_Pion50->SetFillStyle(3001);

  TLegend* leg3 = new TLegend(0.20, 0.55, 0.5, 0.75);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->AddEntry(gRadiusData_Pion50, "Steel stack", "pf");
  leg3->AddEntry(gRadiusDataTungsten_Pion50, "Tungsten stack", "pf");

  TPaveText *pt = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");
  pt->AddText("50 GeV #pi^{-}");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gRadiusData_Pion50);
  multi2->Add(gRadiusDataTungsten_Pion50);

  TCanvas *c1 = new TCanvas("c1", "Time vs Radius", 800, 600);
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Shower Radius [mm]");
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->Draw("E3");
  multi2->Draw("PX");
  // multi2->GetYaxis()->SetRangeUser(-1, 12);
  multi2->GetXaxis()->SetRangeUser(0, 300);
  leg3->Draw("same");
  pt->Draw("same");

  c1->SaveAs("Plots/ComparisonRadius_SteelTungsten.pdf");
}

void ComparisonData()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Comparison_dNdt.root", "OPEN");
  TGraphAsymmErrors *gTimeData_Muon, *gTimeData_Electron, *gTimeData_Pion;

  f->GetObject("gTimeData_Muon", gTimeData_Muon);
  f->GetObject("gTimeData_Electron", gTimeData_Electron);
  f->GetObject("gTimeData_Pion", gTimeData_Pion);

  gTimeData_Muon->SetMarkerStyle(20);
  gTimeData_Muon->SetMarkerColor(kRed);
  gTimeData_Muon->SetLineColor(kRed);

  gTimeData_Electron->SetMarkerStyle(20);
  gTimeData_Electron->SetMarkerColor(kGreen);
  gTimeData_Electron->SetLineColor(kGreen);

  gTimeData_Pion->SetMarkerStyle(20);
  gTimeData_Pion->SetMarkerColor(kBlue);
  gTimeData_Pion->SetLineColor(kBlue);

  TPaveText *pt = new TPaveText(0.68, 0.45, 0.88, 0.55, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("Work in progress");

  TLegend *leg = new TLegend(0.50, 0.60, 0.90, 0.90);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.025);
  leg->SetHeader("f(t) = A_{fast} . e^{-t/#tau_{fast}} + A_{slow} . e^{-t/#tau_{slow}} + c");
  leg->AddEntry(gTimeData_Pion, "50 GeV Pions - steel", "lp");
  leg->AddEntry(gTimeData_Pion->GetFunction("fit_pion"), TString::Format("#tau_{fast} = %2.1f ns, #tau_{slow} = %3.0f ns, c = %1.1e", gTimeData_Pion->GetFunction("fit_pion")->GetParameter(1), gTimeData_Pion->GetFunction("fit_pion")->GetParameter(3), gTimeData_Pion->GetFunction("fit_pion")->GetParameter(4)), "");
  leg->AddEntry(gTimeData_Electron, "10 GeV Electrons - steel", "lp");
  leg->AddEntry(gTimeData_Electron->GetFunction("fit_electron"), TString::Format("c = %1.1e", gTimeData_Electron->GetFunction("fit_electron")->GetParameter(0)), "");
  leg->AddEntry(gTimeData_Muon, "150 GeV Muons - steel", "lp");
  leg->AddEntry(gTimeData_Muon->GetFunction("fit_muon"), TString::Format("c = %1.1e", gTimeData_Muon->GetFunction("fit_muon")->GetParameter(0)), "");

  TMultiGraph *multi = new TMultiGraph();
  multi->Add(gTimeData_Muon);
  multi->Add(gTimeData_Electron);
  multi->Add(gTimeData_Pion);

  TCanvas *c1 = new TCanvas("c1", "Full AHCAL Timing", 800, 600);
  c1->cd();
  gPad->SetLogy();
  //hData->Draw();
  multi->Draw("AP");
  multi->GetXaxis()->SetTitle("Time of first hit [ns]");
  multi->GetYaxis()->SetTitle("Fraction of hits");
  multi->GetXaxis()->SetRangeUser(-50, 200);
  multi->GetYaxis()->SetRangeUser(1e-7, 1);
  pt->Draw("SAME");
  leg->Draw("SAME");

  c1->SaveAs("Plots/Timing_dNdt_Comparison.pdf");

  //--------------------------- Energy -------------------------------

  TString rootfilename = "Rootfiles/Comparison_Energy";
  rootfilename += "_ShortAsymRange.root";
  // rootfilename += "_ShortAsymRange_RmMiddleChips.root";

  TFile *f2 = new TFile(rootfilename, "OPEN");
  TProfile *pEnergyData_Muon, *pEnergyData_Electron, *pEnergyData_Pion10, *pEnergyData_Pion30, *pEnergyData_Pion50, *pEnergyData_Pion70, *pEnergyData_Pion90;

  f2->GetObject("Muon_profile", pEnergyData_Muon);
  f2->GetObject("Electron_profile", pEnergyData_Electron);
  f2->GetObject("Pion_profile10", pEnergyData_Pion10);
  f2->GetObject("Pion_profile30", pEnergyData_Pion30);
  f2->GetObject("Pion_profile50", pEnergyData_Pion50);
  f2->GetObject("Pion_profile70", pEnergyData_Pion70);
  f2->GetObject("Pion_profile90", pEnergyData_Pion90);

  TGraphErrors *gEnergyData_Muon = new TGraphErrors();
  TGraphErrors *gEnergyData_Electron = new TGraphErrors();
  TGraphErrors *gEnergyData_Pion10 = new TGraphErrors();
  TGraphErrors *gEnergyData_Pion30 = new TGraphErrors();
  TGraphErrors *gEnergyData_Pion50 = new TGraphErrors();
  TGraphErrors *gEnergyData_Pion70 = new TGraphErrors();
  TGraphErrors *gEnergyData_Pion90 = new TGraphErrors();

  gEnergyData_Muon->SetMarkerSize(1);
  gEnergyData_Muon->SetMarkerStyle(22);
  gEnergyData_Muon->SetMarkerColor(kRed);
  gEnergyData_Muon->SetLineColor(kRed);
  gEnergyData_Muon->SetFillColor(kRed);
  gEnergyData_Muon->SetFillStyle(3001);

  gEnergyData_Electron->SetMarkerSize(1);
  gEnergyData_Electron->SetMarkerStyle(24);
  gEnergyData_Electron->SetMarkerColor(kGreen);
  gEnergyData_Electron->SetLineColor(kGreen);
  gEnergyData_Electron->SetFillColor(kGreen);
  gEnergyData_Electron->SetFillStyle(3001);

  gEnergyData_Pion10->SetMarkerSize(1);
  gEnergyData_Pion10->SetMarkerStyle(20);
  gEnergyData_Pion10->SetMarkerColor(kBlue);
  gEnergyData_Pion10->SetLineColor(kBlue);
  gEnergyData_Pion10->SetFillColor(kBlue);
  gEnergyData_Pion10->SetFillStyle(3001);

  gEnergyData_Pion30->SetMarkerSize(1);
  gEnergyData_Pion30->SetMarkerStyle(20);
  gEnergyData_Pion30->SetMarkerColor(kOrange+1);
  gEnergyData_Pion30->SetLineColor(kOrange+1);
  gEnergyData_Pion30->SetFillColor(kOrange+1);
  gEnergyData_Pion30->SetFillStyle(3001);

  gEnergyData_Pion50->SetMarkerSize(1);
  gEnergyData_Pion50->SetMarkerStyle(20);
  gEnergyData_Pion50->SetMarkerColor(kMagenta);
  gEnergyData_Pion50->SetLineColor(kMagenta);
  gEnergyData_Pion50->SetFillColor(kMagenta);
  gEnergyData_Pion50->SetFillStyle(3001);

  gEnergyData_Pion70->SetMarkerSize(1);
  gEnergyData_Pion70->SetMarkerStyle(20);
  gEnergyData_Pion70->SetMarkerColor(kYellow+2);
  gEnergyData_Pion70->SetLineColor(kYellow+2);
  gEnergyData_Pion70->SetFillColor(kYellow+2);
  gEnergyData_Pion70->SetFillStyle(3001);

  gEnergyData_Pion90->SetMarkerSize(1);
  gEnergyData_Pion90->SetMarkerStyle(20);
  gEnergyData_Pion90->SetMarkerColor(46);
  gEnergyData_Pion90->SetLineColor(46);
  gEnergyData_Pion90->SetFillColor(46);
  gEnergyData_Pion90->SetFillStyle(3001);

  //----------- Add systematic error ------------------

  int ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Muon->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Muon->GetBinContent(ibin);
    double energy = pEnergyData_Muon->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Muon->GetBinError(ibin);
    double energy_err = pEnergyData_Muon->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Muon->SetPoint(ipoint, energy, content);
    gEnergyData_Muon->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Electron->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Electron->GetBinContent(ibin);
    double energy = pEnergyData_Electron->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Electron->GetBinError(ibin);
    double energy_err = pEnergyData_Electron->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Electron->SetPoint(ipoint, energy, content);
    gEnergyData_Electron->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion10->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion10->GetBinContent(ibin);
    double energy = pEnergyData_Pion10->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Pion10->GetBinError(ibin);
    double energy_err = pEnergyData_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Pion10->SetPoint(ipoint, energy, content);
    gEnergyData_Pion10->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion30->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion30->GetBinContent(ibin);
    double energy = pEnergyData_Pion30->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Pion30->GetBinError(ibin);
    double energy_err = pEnergyData_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Pion30->SetPoint(ipoint, energy, content);
    gEnergyData_Pion30->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion50->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion50->GetBinContent(ibin);
    double energy = pEnergyData_Pion50->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Pion50->GetBinError(ibin);
    double energy_err = pEnergyData_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Pion50->SetPoint(ipoint, energy, content);
    gEnergyData_Pion50->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion70->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion70->GetBinContent(ibin);
    double energy = pEnergyData_Pion70->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Pion70->GetBinError(ibin);
    double energy_err = pEnergyData_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Pion70->SetPoint(ipoint, energy, content);
    gEnergyData_Pion70->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion90->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion90->GetBinContent(ibin);
    double energy = pEnergyData_Pion90->GetXaxis()->GetBinCenter(ibin);

    if(energy < 0.5) continue;
    if(energy > 5) break;

    double error_stat = pEnergyData_Pion90->GetBinError(ibin);
    double energy_err = pEnergyData_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

    //Syst
    double error_syst = 1.04;

    gEnergyData_Pion90->SetPoint(ipoint, energy, content);
    gEnergyData_Pion90->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Muon);
  multi2->Add(gEnergyData_Electron);
  multi2->Add(gEnergyData_Pion10);
  multi2->Add(gEnergyData_Pion30);
  multi2->Add(gEnergyData_Pion50);
  multi2->Add(gEnergyData_Pion70);
  multi2->Add(gEnergyData_Pion90);

  TLegend *leg2 = new TLegend(0.25, 0.65, 0.60, 0.90);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.03);
  leg2->AddEntry(gEnergyData_Pion10, "10 GeV Pions - steel", "pf");
  leg2->AddEntry(gEnergyData_Pion30, "30 GeV Pions - steel", "pf");
  leg2->AddEntry(gEnergyData_Pion50, "50 GeV Pions - steel", "pf");
  leg2->AddEntry(gEnergyData_Pion70, "70 GeV Pions - steel", "pf");
  leg2->AddEntry(gEnergyData_Pion90, "90 GeV Pions - steel", "pf");
  leg2->AddEntry(gEnergyData_Electron, "50 GeV Electrons - steel", "pf");
  leg2->AddEntry(gEnergyData_Muon, "150 GeV Muons - steel", "pf");

  TPaveText *pt2 = new TPaveText(0.68, 0.80, 0.88, 0.90, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");

  TCanvas *c2 = new TCanvas("c2", "Timing vs Energy", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Depostion [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  multi2->Draw("E3");

  TString canvasname = "Plots/Timing_Energy_Comparison";
  canvasname += "_ShortAsymRange.pdf";
  // canvasname += "_ShortAsymRange_RmMiddleChips.pdf";

  c2->SaveAs(canvasname);

  //------------------- Radius --------------------------

  rootfilename = "Rootfiles/Comparison_Radius";
  rootfilename += "_ShortAsymRange.root";
  // rootfilename += "_ShortAsymRange_RmMiddleChips.root";

  TFile *f3 = new TFile(rootfilename, "OPEN");
  TProfile *pRadiusData_Muon, *pRadiusData_Electron;
  TProfile *pRadiusData_Pion10_SSF, *pRadiusData_Pion30_SSF, *pRadiusData_Pion50_SSF, *pRadiusData_Pion70_SSF, *pRadiusData_Pion90_SSF;
  TProfile *pRadiusData_Pion10_BL, *pRadiusData_Pion30_BL, *pRadiusData_Pion50_BL, *pRadiusData_Pion70_BL, *pRadiusData_Pion90_BL;

  f3->GetObject("Muon_profile", pRadiusData_Muon);
  f3->GetObject("Electron_profile", pRadiusData_Electron);

  f3->GetObject("Pion_profile10_SSF", pRadiusData_Pion10_SSF);
  f3->GetObject("Pion_profile30_SSF", pRadiusData_Pion30_SSF);
  f3->GetObject("Pion_profile50_SSF", pRadiusData_Pion50_SSF);
  f3->GetObject("Pion_profile70_SSF", pRadiusData_Pion70_SSF);
  f3->GetObject("Pion_profile90_SSF", pRadiusData_Pion90_SSF);

  f3->GetObject("Pion_profile10_BL", pRadiusData_Pion10_BL);
  f3->GetObject("Pion_profile30_BL", pRadiusData_Pion30_BL);
  f3->GetObject("Pion_profile50_BL", pRadiusData_Pion50_BL);
  f3->GetObject("Pion_profile70_BL", pRadiusData_Pion70_BL);
  f3->GetObject("Pion_profile90_BL", pRadiusData_Pion90_BL);

  TGraphErrors *gRadiusData_Muon = new TGraphErrors();
  TGraphErrors *gRadiusData_Electron = new TGraphErrors();

  TGraphErrors *gRadiusData_Pion10_SSF = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion30_SSF = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_SSF = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion70_SSF = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion90_SSF = new TGraphErrors();

  TGraphErrors *gRadiusData_Pion10_BL = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion30_BL = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_BL = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion70_BL = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion90_BL = new TGraphErrors();

  gRadiusData_Muon->SetMarkerSize(1);
  gRadiusData_Muon->SetMarkerStyle(22);
  gRadiusData_Muon->SetMarkerColor(kRed);
  gRadiusData_Muon->SetLineColor(kRed);
  gRadiusData_Muon->SetFillColor(kRed);
  gRadiusData_Muon->SetFillStyle(3001);

  gRadiusData_Electron->SetMarkerSize(1);
  gRadiusData_Electron->SetMarkerStyle(24);
  gRadiusData_Electron->SetMarkerColor(kGreen);
  gRadiusData_Electron->SetLineColor(kGreen);
  gRadiusData_Electron->SetFillColor(kGreen);
  gRadiusData_Electron->SetFillStyle(3001);

  //SSF

  gRadiusData_Pion10_SSF->SetMarkerSize(1);
  gRadiusData_Pion10_SSF->SetMarkerStyle(20);
  gRadiusData_Pion10_SSF->SetMarkerColor(kBlue);
  gRadiusData_Pion10_SSF->SetLineColor(kBlue);
  gRadiusData_Pion10_SSF->SetFillColor(kBlue);
  gRadiusData_Pion10_SSF->SetFillStyle(3001);

  gRadiusData_Pion30_SSF->SetMarkerSize(1);
  gRadiusData_Pion30_SSF->SetMarkerStyle(20);
  gRadiusData_Pion30_SSF->SetMarkerColor(kOrange+1);
  gRadiusData_Pion30_SSF->SetLineColor(kOrange+1);
  gRadiusData_Pion30_SSF->SetFillColor(kOrange+1);
  gRadiusData_Pion30_SSF->SetFillStyle(3001);

  gRadiusData_Pion50_SSF->SetMarkerSize(1);
  gRadiusData_Pion50_SSF->SetMarkerStyle(20);
  gRadiusData_Pion50_SSF->SetMarkerColor(kMagenta);
  gRadiusData_Pion50_SSF->SetLineColor(kMagenta);
  gRadiusData_Pion50_SSF->SetFillColor(kMagenta);
  gRadiusData_Pion50_SSF->SetFillStyle(3001);

  gRadiusData_Pion70_SSF->SetMarkerSize(1);
  gRadiusData_Pion70_SSF->SetMarkerStyle(20);
  gRadiusData_Pion70_SSF->SetMarkerColor(kYellow+2);
  gRadiusData_Pion70_SSF->SetLineColor(kYellow+2);
  gRadiusData_Pion70_SSF->SetFillColor(kYellow+2);
  gRadiusData_Pion70_SSF->SetFillStyle(3001);

  gRadiusData_Pion90_SSF->SetMarkerSize(1);
  gRadiusData_Pion90_SSF->SetMarkerStyle(20);
  gRadiusData_Pion90_SSF->SetMarkerColor(46);
  gRadiusData_Pion90_SSF->SetLineColor(46);
  gRadiusData_Pion90_SSF->SetFillColor(46);
  gRadiusData_Pion90_SSF->SetFillStyle(3001);

  //BL

  gRadiusData_Pion10_BL->SetMarkerSize(1);
  gRadiusData_Pion10_BL->SetMarkerStyle(20);
  gRadiusData_Pion10_BL->SetMarkerColor(kBlue);
  gRadiusData_Pion10_BL->SetLineColor(kBlue);
  gRadiusData_Pion10_BL->SetFillColor(kBlue);
  gRadiusData_Pion10_BL->SetFillStyle(3001);

  gRadiusData_Pion30_BL->SetMarkerSize(1);
  gRadiusData_Pion30_BL->SetMarkerStyle(20);
  gRadiusData_Pion30_BL->SetMarkerColor(kOrange+1);
  gRadiusData_Pion30_BL->SetLineColor(kOrange+1);
  gRadiusData_Pion30_BL->SetFillColor(kOrange+1);
  gRadiusData_Pion30_BL->SetFillStyle(3001);

  gRadiusData_Pion50_BL->SetMarkerSize(1);
  gRadiusData_Pion50_BL->SetMarkerStyle(20);
  gRadiusData_Pion50_BL->SetMarkerColor(kMagenta);
  gRadiusData_Pion50_BL->SetLineColor(kMagenta);
  gRadiusData_Pion50_BL->SetFillColor(kMagenta);
  gRadiusData_Pion50_BL->SetFillStyle(3001);

  gRadiusData_Pion70_BL->SetMarkerSize(1);
  gRadiusData_Pion70_BL->SetMarkerStyle(20);
  gRadiusData_Pion70_BL->SetMarkerColor(kYellow+2);
  gRadiusData_Pion70_BL->SetLineColor(kYellow+2);
  gRadiusData_Pion70_BL->SetFillColor(kYellow+2);
  gRadiusData_Pion70_BL->SetFillStyle(3001);

  gRadiusData_Pion90_BL->SetMarkerSize(1);
  gRadiusData_Pion90_BL->SetMarkerStyle(20);
  gRadiusData_Pion90_BL->SetMarkerColor(46);
  gRadiusData_Pion90_BL->SetLineColor(46);
  gRadiusData_Pion90_BL->SetFillColor(46);
  gRadiusData_Pion90_BL->SetFillStyle(3001);

  //----------- Add systematic error ------------------

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Muon->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Muon->GetBinContent(ibin);
    double radius = pRadiusData_Muon->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Muon->GetBinError(ibin);
    double radius_err = pRadiusData_Muon->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gRadiusData_Muon->SetPoint(ipoint, radius, content);
    gRadiusData_Muon->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Electron->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Electron->GetBinContent(ibin);
    double radius = pRadiusData_Electron->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Electron->GetBinError(ibin);
    double radius_err = pRadiusData_Electron->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gRadiusData_Electron->SetPoint(ipoint, radius, content);
    gRadiusData_Electron->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //SSF
  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion10_SSF->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion10_SSF->GetBinContent(ibin);
    double radius = pRadiusData_Pion10_SSF->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion10_SSF->GetBinError(ibin);
    double radius_err = pRadiusData_Pion10_SSF->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 10, "SSF"));

    gRadiusData_Pion10_SSF->SetPoint(ipoint, radius, content);
    gRadiusData_Pion10_SSF->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion30_SSF->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion30_SSF->GetBinContent(ibin);
    double radius = pRadiusData_Pion30_SSF->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion30_SSF->GetBinError(ibin);
    double radius_err = pRadiusData_Pion30_SSF->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 30, "SSF"));

    gRadiusData_Pion30_SSF->SetPoint(ipoint, radius, content);
    gRadiusData_Pion30_SSF->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_SSF->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_SSF->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_SSF->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_SSF->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_SSF->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_SSF->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_SSF->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion70_SSF->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion70_SSF->GetBinContent(ibin);
    double radius = pRadiusData_Pion70_SSF->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion70_SSF->GetBinError(ibin);
    double radius_err = pRadiusData_Pion70_SSF->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 70, "SSF"));

    gRadiusData_Pion70_SSF->SetPoint(ipoint, radius, content);
    gRadiusData_Pion70_SSF->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion90_SSF->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion90_SSF->GetBinContent(ibin);
    double radius = pRadiusData_Pion90_SSF->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion90_SSF->GetBinError(ibin);
    double radius_err = pRadiusData_Pion90_SSF->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 90, "SSF"));

    gRadiusData_Pion90_SSF->SetPoint(ipoint, radius, content);
    gRadiusData_Pion90_SSF->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //BL
  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion10_BL->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion10_BL->GetBinContent(ibin);
    double radius = pRadiusData_Pion10_BL->GetXaxis()->GetBinCenter(ibin);

    if(radius > 350) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion10_BL->GetBinError(ibin);
    double radius_err = pRadiusData_Pion10_BL->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 10, "BL"));

    gRadiusData_Pion10_BL->SetPoint(ipoint, radius, content);
    gRadiusData_Pion10_BL->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion30_BL->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion30_BL->GetBinContent(ibin);
    double radius = pRadiusData_Pion30_BL->GetXaxis()->GetBinCenter(ibin);

    if(radius > 350) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion30_BL->GetBinError(ibin);
    double radius_err = pRadiusData_Pion30_BL->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 30, "BL"));

    gRadiusData_Pion30_BL->SetPoint(ipoint, radius, content);
    gRadiusData_Pion30_BL->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_BL->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_BL->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_BL->GetXaxis()->GetBinCenter(ibin);

    if(radius > 350) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_BL->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_BL->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "BL"));

    gRadiusData_Pion50_BL->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_BL->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion70_BL->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion70_BL->GetBinContent(ibin);
    double radius = pRadiusData_Pion70_BL->GetXaxis()->GetBinCenter(ibin);

    if(radius > 350) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion70_BL->GetBinError(ibin);
    double radius_err = pRadiusData_Pion70_BL->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 70, "BL"));

    gRadiusData_Pion70_BL->SetPoint(ipoint, radius, content);
    gRadiusData_Pion70_BL->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion90_BL->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion90_BL->GetBinContent(ibin);
    double radius = pRadiusData_Pion90_BL->GetXaxis()->GetBinCenter(ibin);

    if(radius > 350) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion90_BL->GetBinError(ibin);
    double radius_err = pRadiusData_Pion90_BL->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 90, "BL"));

    gRadiusData_Pion90_BL->SetPoint(ipoint, radius, content);
    gRadiusData_Pion90_BL->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  TMultiGraph *multi3_SSF = new TMultiGraph();
  multi3_SSF->Add(gRadiusData_Muon);
  multi3_SSF->Add(gRadiusData_Electron);
  multi3_SSF->Add(gRadiusData_Pion10_SSF);
  multi3_SSF->Add(gRadiusData_Pion30_SSF);
  multi3_SSF->Add(gRadiusData_Pion50_SSF);
  multi3_SSF->Add(gRadiusData_Pion70_SSF);
  multi3_SSF->Add(gRadiusData_Pion90_SSF);

  TMultiGraph *multi3_BL = new TMultiGraph();
  multi3_BL->Add(gRadiusData_Muon);
  multi3_BL->Add(gRadiusData_Electron);
  multi3_BL->Add(gRadiusData_Pion10_BL);
  multi3_BL->Add(gRadiusData_Pion30_BL);
  multi3_BL->Add(gRadiusData_Pion50_BL);
  multi3_BL->Add(gRadiusData_Pion70_BL);
  multi3_BL->Add(gRadiusData_Pion90_BL);

  TLegend *leg3 = new TLegend(0.25, 0.65, 0.60, 0.90);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(gRadiusData_Pion10_SSF, "10 GeV Pions - steel", "pf");
  leg3->AddEntry(gRadiusData_Pion30_SSF, "30 GeV Pions - steel", "pf");
  leg3->AddEntry(gRadiusData_Pion50_SSF, "50 GeV Pions - steel", "pf");
  leg3->AddEntry(gRadiusData_Pion70_SSF, "70 GeV Pions - steel", "pf");
  leg3->AddEntry(gRadiusData_Pion90_SSF, "90 GeV Pions - steel", "pf");
  leg3->AddEntry(gRadiusData_Electron, "50 GeV Electrons - steel", "pf");
  leg3->AddEntry(gRadiusData_Muon, "150 GeV Muons - steel", "pf");

  TPaveText *pt3 = new TPaveText(0.68, 0.80, 0.88, 0.90, "tbNDC");
  pt3->SetBorderSize(0);
  pt3->SetTextColor(15);
  pt3->SetFillColor(0);
  pt3->SetTextSize(0.04);
  pt3->SetTextAlign(13); //left center
  pt3->AddText("CALICE AHCAL");
  pt3->AddText("Work in progress");

  TCanvas *c3_SSF = new TCanvas("c3_SSF", "Timing vs Radius SSF", 800, 600);
  c3_SSF->cd();
  multi3_SSF->Draw("APX");
  multi3_SSF->GetXaxis()->SetTitle("Distance to shower CoG [mm]");
  multi3_SSF->GetXaxis()->SetRangeUser(0, 260);
  multi3_SSF->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi3_SSF->GetYaxis()->SetRangeUser(-2, 18);
  pt3->Draw("SAME");
  leg3->Draw("SAME");
  multi3_SSF->Draw("E3");

  canvasname = "Plots/Timing_Radius_Comparison";
  canvasname += "_ShortAsymRange_SSF.pdf";

  c3_SSF->SaveAs(canvasname);

  TCanvas *c3_BL = new TCanvas("c3_BL", "Timing vs Radius BL", 800, 600);
  c3_BL->cd();
  multi3_BL->Draw("APX");
  multi3_BL->GetXaxis()->SetTitle("Distance to shower CoG [mm]");
  multi3_BL->GetXaxis()->SetRangeUser(0, 400);
  multi3_BL->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi3_BL->GetYaxis()->SetRangeUser(-2, 18);
  pt3->Draw("SAME");
  leg3->Draw("SAME");
  multi3_BL->Draw("E3");

  canvasname = "Plots/Timing_Radius_Comparison";
  canvasname += "_ShortAsymRange_BL.pdf";

  c3_BL->SaveAs(canvasname);

  //------------------- Depth --------------------------

  rootfilename = "Rootfiles/Comparison_Depth";
  rootfilename += "_ShortAsymRange.root";
  // rootfilename += "_ShortAsymRange_RmMiddleChips.root";

  TFile *f4 = new TFile(rootfilename, "OPEN");
  TProfile *pDepthData_Muon, *pDepthData_Electron, *pDepthData_Pion10, *pDepthData_Pion30, *pDepthData_Pion50, *pDepthData_Pion70, *pDepthData_Pion90;

  f4->GetObject("Muon_profile", pDepthData_Muon);
  f4->GetObject("Electron_profile", pDepthData_Electron);
  f4->GetObject("Pion_profile10", pDepthData_Pion10);
  f4->GetObject("Pion_profile30", pDepthData_Pion30);
  f4->GetObject("Pion_profile50", pDepthData_Pion50);
  f4->GetObject("Pion_profile70", pDepthData_Pion70);
  f4->GetObject("Pion_profile90", pDepthData_Pion90);

  TGraphErrors *gDepthData_Muon = new TGraphErrors();
  TGraphErrors *gDepthData_Electron = new TGraphErrors();
  TGraphErrors *gDepthData_Pion10 = new TGraphErrors();
  TGraphErrors *gDepthData_Pion30 = new TGraphErrors();
  TGraphErrors *gDepthData_Pion50 = new TGraphErrors();
  TGraphErrors *gDepthData_Pion70 = new TGraphErrors();
  TGraphErrors *gDepthData_Pion90 = new TGraphErrors();

  gDepthData_Muon->SetMarkerSize(1);
  gDepthData_Muon->SetMarkerStyle(22);
  gDepthData_Muon->SetMarkerColor(kRed);
  gDepthData_Muon->SetLineColor(kRed);
  gDepthData_Muon->SetFillColor(kRed);
  gDepthData_Muon->SetFillStyle(3001);

  gDepthData_Electron->SetMarkerSize(1);
  gDepthData_Electron->SetMarkerStyle(24);
  gDepthData_Electron->SetMarkerColor(kGreen);
  gDepthData_Electron->SetLineColor(kGreen);
  gDepthData_Electron->SetFillColor(kGreen);
  gDepthData_Electron->SetFillStyle(3001);

  gDepthData_Pion10->SetMarkerSize(1);
  gDepthData_Pion10->SetMarkerStyle(20);
  gDepthData_Pion10->SetMarkerColor(kBlue);
  gDepthData_Pion10->SetLineColor(kBlue);
  gDepthData_Pion10->SetFillColor(kBlue);
  gDepthData_Pion10->SetFillStyle(3001);

  gDepthData_Pion30->SetMarkerSize(1);
  gDepthData_Pion30->SetMarkerStyle(20);
  gDepthData_Pion30->SetMarkerColor(kOrange+1);
  gDepthData_Pion30->SetLineColor(kOrange+1);
  gDepthData_Pion30->SetFillColor(kOrange+1);
  gDepthData_Pion30->SetFillStyle(3001);

  gDepthData_Pion50->SetMarkerSize(1);
  gDepthData_Pion50->SetMarkerStyle(20);
  gDepthData_Pion50->SetMarkerColor(kMagenta);
  gDepthData_Pion50->SetLineColor(kMagenta);
  gDepthData_Pion50->SetFillColor(kMagenta);
  gDepthData_Pion50->SetFillStyle(3001);

  gDepthData_Pion70->SetMarkerSize(1);
  gDepthData_Pion70->SetMarkerStyle(20);
  gDepthData_Pion70->SetMarkerColor(kYellow+2);
  gDepthData_Pion70->SetLineColor(kYellow+2);
  gDepthData_Pion70->SetFillColor(kYellow+2);
  gDepthData_Pion70->SetFillStyle(3001);

  gDepthData_Pion90->SetMarkerSize(1);
  gDepthData_Pion90->SetMarkerStyle(20);
  gDepthData_Pion90->SetMarkerColor(46);
  gDepthData_Pion90->SetLineColor(46);
  gDepthData_Pion90->SetFillColor(46);
  gDepthData_Pion90->SetFillStyle(3001);

  //----------- Add systematic error ------------------

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Muon->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Muon->GetBinContent(ibin);
    double Depth = pDepthData_Muon->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Muon->GetBinError(ibin);
    double Depth_err = pDepthData_Muon->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Muon->SetPoint(ipoint, Depth, content);
    gDepthData_Muon->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Electron->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Electron->GetBinContent(ibin);
    double Depth = pDepthData_Electron->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Electron->GetBinError(ibin);
    double Depth_err = pDepthData_Electron->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Electron->SetPoint(ipoint, Depth, content);
    gDepthData_Electron->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion10->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion10->GetBinContent(ibin);
    double Depth = pDepthData_Pion10->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion10->GetBinError(ibin);
    double Depth_err = pDepthData_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Pion10->SetPoint(ipoint, Depth, content);
    gDepthData_Pion10->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion30->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion30->GetBinContent(ibin);
    double Depth = pDepthData_Pion30->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion30->GetBinError(ibin);
    double Depth_err = pDepthData_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Pion30->SetPoint(ipoint, Depth, content);
    gDepthData_Pion30->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion50->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion50->GetBinContent(ibin);
    double Depth = pDepthData_Pion50->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion50->GetBinError(ibin);
    double Depth_err = pDepthData_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Pion50->SetPoint(ipoint, Depth, content);
    gDepthData_Pion50->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion70->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion70->GetBinContent(ibin);
    double Depth = pDepthData_Pion70->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion70->GetBinError(ibin);
    double Depth_err = pDepthData_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Pion70->SetPoint(ipoint, Depth, content);
    gDepthData_Pion70->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion90->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion90->GetBinContent(ibin);
    double Depth = pDepthData_Pion90->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion90->GetBinError(ibin);
    double Depth_err = pDepthData_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Pion90->SetPoint(ipoint, Depth, content);
    gDepthData_Pion90->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  TMultiGraph *multi4 = new TMultiGraph();
  multi4->Add(gDepthData_Muon);
  multi4->Add(gDepthData_Electron);
  multi4->Add(gDepthData_Pion10);
  multi4->Add(gDepthData_Pion30);
  multi4->Add(gDepthData_Pion50);
  multi4->Add(gDepthData_Pion70);
  multi4->Add(gDepthData_Pion90);

  TLegend *leg5 = new TLegend(0.25, 0.60, 0.60, 0.85);
  leg5->SetBorderSize(0);
  leg5->SetTextSize(0.03);
  leg5->AddEntry(gDepthData_Pion10, "10 GeV Pions - steel", "pf");
  leg5->AddEntry(gDepthData_Pion30, "30 GeV Pions - steel", "pf");
  leg5->AddEntry(gDepthData_Pion50, "50 GeV Pions - steel", "pf");
  leg5->AddEntry(gDepthData_Pion70, "70 GeV Pions - steel", "pf");
  leg5->AddEntry(gDepthData_Pion90, "90 GeV Pions - steel", "pf");
  leg5->AddEntry(gDepthData_Electron, "50 GeV Electrons - steel", "pf");
  leg5->AddEntry(gDepthData_Muon, "150 GeV Muons - steel", "pf");

  TPaveText *pt4 = new TPaveText(0.68, 0.75, 0.88, 0.85, "tbNDC");
  pt4->SetBorderSize(0);
  pt4->SetTextColor(15);
  pt4->SetFillColor(0);
  pt4->SetTextSize(0.04);
  pt4->SetTextAlign(13); //left center
  pt4->AddText("CALICE AHCAL");
  pt4->AddText("Work in progress");

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c4 = new TCanvas("c4", "Timing vs Depth", 800, 600);
  c4->cd();
  multi4->Draw("APX");
  multi4->GetXaxis()->SetTitle("Layer Position [mm]");
  multi4->GetXaxis()->SetRangeUser(50, 850);
  multi4->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi4->GetYaxis()->SetRangeUser(-2, 10);
  pt4->Draw("SAME");
  leg5->Draw("SAME");
  multi4->Draw("E3");
  TGaxis *axis = new TGaxis(48, 10, 851, 10, 0.02, 4.17, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  canvasname = "Plots/Timing_Depth_Comparison";
  canvasname += "_ShortAsymRange.pdf";
  // canvasname += "_ShortAsymRange_RmMiddleChips.pdf";

  c4->SaveAs(canvasname);
}

void AdditionalShowerStart()
{
  CaliceStyle();

  TString rootfilename = "Rootfiles/Comparison_Depth";
  rootfilename += "_ShortAsymRange_ShowerStart.root";
  // rootfilename += "_ShortAsymRange_RmMiddleChips.root";

  TFile *f = new TFile(rootfilename, "OPEN");
  TProfile *pDepthData_Pion50;

  f->GetObject("Pion_profile50", pDepthData_Pion50);

  TGraphErrors *gDepthData_Pion50 = new TGraphErrors();

  gDepthData_Pion50->SetMarkerSize(1);
  gDepthData_Pion50->SetMarkerStyle(20);
  gDepthData_Pion50->SetMarkerColor(kBlue);
  gDepthData_Pion50->SetLineColor(kBlue);
  gDepthData_Pion50->SetFillColor(kBlue);
  gDepthData_Pion50->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion50->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion50->GetBinContent(ibin);
    double Depth = pDepthData_Pion50->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion50->GetBinError(ibin);
    double Depth_err = pDepthData_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gDepthData_Pion50->SetPoint(ipoint, Depth, content);
    gDepthData_Pion50->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  TMultiGraph *multi4 = new TMultiGraph();
  multi4->Add(gDepthData_Pion50);

  TLegend *leg5 = new TLegend(0.25, 0.77, 0.60, 0.85);
  leg5->SetBorderSize(0);
  leg5->SetTextSize(0.03);
  leg5->AddEntry(gDepthData_Pion50, "50 GeV Pions - steel", "pf");

  TPaveText *pt4 = new TPaveText(0.68, 0.75, 0.88, 0.85, "tbNDC");
  pt4->SetBorderSize(0);
  pt4->SetTextColor(15);
  pt4->SetFillColor(0);
  pt4->SetTextSize(0.04);
  pt4->SetTextAlign(13); //left center
  pt4->AddText("CALICE AHCAL");
  pt4->AddText("Work in progress");

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c4 = new TCanvas("c4", "Timing vs Depth", 800, 600);
  c4->cd();
  multi4->Draw("APX");
  multi4->GetXaxis()->SetTitle("Distance to FHI [mm]");
  multi4->GetXaxis()->SetRangeUser(0, 750);
  multi4->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi4->GetYaxis()->SetRangeUser(-2, 10);
  pt4->Draw("SAME");
  leg5->Draw("SAME");
  multi4->Draw("E3");
  TGaxis *axis = new TGaxis(-2, 10, 751, 10, 0.001, 3.68, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  TString canvasname = "Plots/Timing_Depth_Comparison";
  canvasname += "_ShortAsymRange_ShowerStart.pdf";
  // canvasname += "_ShortAsymRange_RmMiddleChips.pdf";

  c4->SaveAs(canvasname);

  rootfilename = "Rootfiles/Comparison_Radius";
  rootfilename += "_ShortAsymRange_ShowerStart_FixedModule.root";

  TFile *f3 = new TFile(rootfilename, "OPEN");
  TProfile *pRadiusData_Pion50_Module10_SS4, *pRadiusData_Pion50_Module10_SS5, *pRadiusData_Pion50_Module10_SS6, *pRadiusData_Pion50_Module10_SS7, *pRadiusData_Pion50_Module10_SS8, *pRadiusData_Pion50_Module10_SS9, *pRadiusData_Pion50_Module10_SS10, *pRadiusData_Pion50_Module10_SS11;

  f3->GetObject("Pion_profile50_Module10_SS04", pRadiusData_Pion50_Module10_SS4);
  f3->GetObject("Pion_profile50_Module10_SS05", pRadiusData_Pion50_Module10_SS5);
  f3->GetObject("Pion_profile50_Module10_SS06", pRadiusData_Pion50_Module10_SS6);
  f3->GetObject("Pion_profile50_Module10_SS07", pRadiusData_Pion50_Module10_SS7);
  f3->GetObject("Pion_profile50_Module10_SS08", pRadiusData_Pion50_Module10_SS8);
  f3->GetObject("Pion_profile50_Module10_SS09", pRadiusData_Pion50_Module10_SS9);
  f3->GetObject("Pion_profile50_Module10_SS10", pRadiusData_Pion50_Module10_SS10);

  TGraphErrors *gRadiusData_Pion50_Module10_SS4 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS5 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS6 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS7 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS8 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS9 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS10 = new TGraphErrors();

  gRadiusData_Pion50_Module10_SS4->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS4->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS4->SetMarkerColor(kRed);
  gRadiusData_Pion50_Module10_SS4->SetLineColor(kRed);
  gRadiusData_Pion50_Module10_SS4->SetFillColor(kRed);
  gRadiusData_Pion50_Module10_SS4->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS5->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS5->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS5->SetMarkerColor(kBlue);
  gRadiusData_Pion50_Module10_SS5->SetLineColor(kBlue);
  gRadiusData_Pion50_Module10_SS5->SetFillColor(kBlue);
  gRadiusData_Pion50_Module10_SS5->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS6->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS6->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS6->SetMarkerColor(kGreen);
  gRadiusData_Pion50_Module10_SS6->SetLineColor(kGreen);
  gRadiusData_Pion50_Module10_SS6->SetFillColor(kGreen);
  gRadiusData_Pion50_Module10_SS6->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS7->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS7->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS7->SetMarkerColor(kOrange+1);
  gRadiusData_Pion50_Module10_SS7->SetLineColor(kOrange+1);
  gRadiusData_Pion50_Module10_SS7->SetFillColor(kOrange+1);
  gRadiusData_Pion50_Module10_SS7->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS8->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS8->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS8->SetMarkerColor(kYellow);
  gRadiusData_Pion50_Module10_SS8->SetLineColor(kYellow);
  gRadiusData_Pion50_Module10_SS8->SetFillColor(kYellow);
  gRadiusData_Pion50_Module10_SS8->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS9->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS9->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS9->SetMarkerColor(kOrange+1);
  gRadiusData_Pion50_Module10_SS9->SetLineColor(kOrange+1);
  gRadiusData_Pion50_Module10_SS9->SetFillColor(kOrange+1);
  gRadiusData_Pion50_Module10_SS9->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS10->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS10->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS10->SetMarkerColor(kMagenta);
  gRadiusData_Pion50_Module10_SS10->SetLineColor(kMagenta);
  gRadiusData_Pion50_Module10_SS10->SetFillColor(kMagenta);
  gRadiusData_Pion50_Module10_SS10->SetFillStyle(3001);

  //----------- Add systematic error ------------------

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS4->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS4->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS4->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS4->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS4->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS4->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS4->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS5->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS5->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS5->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS5->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS5->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS5->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS5->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //---------

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS6->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS6->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS6->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS6->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS6->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS6->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS6->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS7->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS7->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS7->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS7->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS7->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS7->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS7->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS8->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS8->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS8->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS8->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS8->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS8->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS8->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS9->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS9->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS9->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS9->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS9->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS9->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS9->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS10->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS10->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS10->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS10->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS10->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS10->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS10->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //----------------------------------------------------------------

  TMultiGraph *multi3 = new TMultiGraph();
  multi3->Add(gRadiusData_Pion50_Module10_SS4);
  multi3->Add(gRadiusData_Pion50_Module10_SS5);
  multi3->Add(gRadiusData_Pion50_Module10_SS6);
  multi3->Add(gRadiusData_Pion50_Module10_SS7);
  multi3->Add(gRadiusData_Pion50_Module10_SS8);
  multi3->Add(gRadiusData_Pion50_Module10_SS9);
  multi3->Add(gRadiusData_Pion50_Module10_SS10);

  TLegend *leg3 = new TLegend(0.22, 0.60, 0.62, 0.85);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS4, "Shower Start Layer 4", "pf");
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS5, "Shower Start Layer 5", "pf");
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS6, "Shower Start Layer 6", "pf");
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS7, "Shower Start Layer 7", "pf");
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS8, "Shower Start Layer 8", "pf");
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS9, "Shower Start Layer 9", "pf");
  leg3->AddEntry(gRadiusData_Pion50_Module10_SS10, "Shower Start Layer 10", "pf");

  TPaveText *pt3 = new TPaveText(0.68, 0.71, 0.88, 0.85, "tbNDC");
  pt3->SetBorderSize(0);
  pt3->SetTextColor(15);
  pt3->SetFillColor(0);
  pt3->SetTextSize(0.04);
  pt3->SetTextAlign(13); //left center
  pt3->AddText("CALICE AHCAL");
  pt3->AddText("Work in progress");
  pt3->AddText("Module 10");

  TCanvas *c3 = new TCanvas("c3", "Timing vs Radius ShowerStart", 800, 600);
  c3->cd();
  multi3->Draw("APX");
  multi3->GetXaxis()->SetTitle("Distance to shower CoG [mm]");
  multi3->GetXaxis()->SetRangeUser(0, 380);
  multi3->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi3->GetYaxis()->SetRangeUser(-2, 18);
  pt3->Draw("SAME");
  leg3->Draw("SAME");
  multi3->Draw("E3");

  canvasname = "Plots/Timing_Radius_Comparison";
  canvasname += "_ShortAsymRange_ShowerStart_FixedModule.pdf";

  c3->SaveAs(canvasname);
}

void AdditionalShowerStart2()
{
  CaliceStyle();

  TString rootfilename = "Rootfiles/Comparison_Radius";
  rootfilename += "_ShortAsymRange_ShowerStart.root";

  TFile *f6 = new TFile(rootfilename, "OPEN");
  TProfile *pRadiusData_Pion50_Module06_SS4, *pRadiusData_Pion50_Module10_SS7;
  TProfile *pRadiusData_Pion50_Module07_SS4, *pRadiusData_Pion50_Module10_SS6;

  f6->GetObject("Pion_profile50_Module06_SS4", pRadiusData_Pion50_Module06_SS4);
  f6->GetObject("Pion_profile50_Module10_SS7", pRadiusData_Pion50_Module10_SS7);

  f6->GetObject("Pion_profile50_Module07_SS4", pRadiusData_Pion50_Module07_SS4);
  f6->GetObject("Pion_profile50_Module10_SS6", pRadiusData_Pion50_Module10_SS6);

  TGraphErrors *gRadiusData_Pion50_Module06_SS4 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS7 = new TGraphErrors();

  TGraphErrors *gRadiusData_Pion50_Module07_SS4 = new TGraphErrors();
  TGraphErrors *gRadiusData_Pion50_Module10_SS6 = new TGraphErrors();

  gRadiusData_Pion50_Module06_SS4->SetMarkerSize(1);
  gRadiusData_Pion50_Module06_SS4->SetMarkerStyle(20);
  gRadiusData_Pion50_Module06_SS4->SetMarkerColor(kOrange+1);
  gRadiusData_Pion50_Module06_SS4->SetLineColor(kOrange+1);
  gRadiusData_Pion50_Module06_SS4->SetFillColor(kOrange+1);
  gRadiusData_Pion50_Module06_SS4->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS7->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS7->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS7->SetMarkerColor(kYellow+2);
  gRadiusData_Pion50_Module10_SS7->SetLineColor(kYellow+2);
  gRadiusData_Pion50_Module10_SS7->SetFillColor(kYellow+2);
  gRadiusData_Pion50_Module10_SS7->SetFillStyle(3001);

  //----

  gRadiusData_Pion50_Module07_SS4->SetMarkerSize(1);
  gRadiusData_Pion50_Module07_SS4->SetMarkerStyle(20);
  gRadiusData_Pion50_Module07_SS4->SetMarkerColor(kOrange+1);
  gRadiusData_Pion50_Module07_SS4->SetLineColor(kOrange+1);
  gRadiusData_Pion50_Module07_SS4->SetFillColor(kOrange+1);
  gRadiusData_Pion50_Module07_SS4->SetFillStyle(3001);

  gRadiusData_Pion50_Module10_SS6->SetMarkerSize(1);
  gRadiusData_Pion50_Module10_SS6->SetMarkerStyle(20);
  gRadiusData_Pion50_Module10_SS6->SetMarkerColor(kYellow+2);
  gRadiusData_Pion50_Module10_SS6->SetLineColor(kYellow+2);
  gRadiusData_Pion50_Module10_SS6->SetFillColor(kYellow+2);
  gRadiusData_Pion50_Module10_SS6->SetFillStyle(3001);

  //----------- Add systematic error ------------------

  int ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module06_SS4->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module06_SS4->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module06_SS4->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module06_SS4->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module06_SS4->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module06_SS4->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module06_SS4->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS7->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS7->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS7->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS7->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS7->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS7->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS7->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //---------

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module07_SS4->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module07_SS4->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module07_SS4->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module07_SS4->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module07_SS4->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module07_SS4->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module07_SS4->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  ipoint = 0;
  for(int ibin = 1; ibin < pRadiusData_Pion50_Module10_SS6->GetNbinsX(); ibin++)
  {
    double content = pRadiusData_Pion50_Module10_SS6->GetBinContent(ibin);
    double radius = pRadiusData_Pion50_Module10_SS6->GetXaxis()->GetBinCenter(ibin);

    if(radius > 260) continue;
    if(content == 0) continue;

    double error_stat = pRadiusData_Pion50_Module10_SS6->GetBinError(ibin);
    double radius_err = pRadiusData_Pion50_Module10_SS6->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));

    gRadiusData_Pion50_Module10_SS6->SetPoint(ipoint, radius, content);
    gRadiusData_Pion50_Module10_SS6->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  TMultiGraph *multi5 = new TMultiGraph();
  // multi3->Add(gRadiusData_Pion50_Module06_SS4);
  // multi3->Add(gRadiusData_Pion50_Module10_SS7);

  multi5->Add(gRadiusData_Pion50_Module07_SS4);
  multi5->Add(gRadiusData_Pion50_Module10_SS6);

  TLegend *leg5 = new TLegend(0.22, 0.75, 0.62, 0.90);
  leg5->SetBorderSize(0);
  leg5->SetTextSize(0.03);
  // leg3->AddEntry(gRadiusData_Pion50_Module06_SS4, "Module 6", "pf");
  // leg3->AddEntry(gRadiusData_Pion50_Module10_SS7, "Module 10", "pf");

  leg5->AddEntry(gRadiusData_Pion50_Module07_SS4, "Module 7 (Shower Start Layer 3)", "pf");
  leg5->AddEntry(gRadiusData_Pion50_Module10_SS6, "Module 10 (Shower Start Layer 6)", "pf");

  TPaveText *pt5 = new TPaveText(0.68, 0.80, 0.88, 0.90, "tbNDC");
  pt5->SetBorderSize(0);
  pt5->SetTextColor(15);
  pt5->SetFillColor(0);
  pt5->SetTextSize(0.04);
  pt5->SetTextAlign(13); //left center
  pt5->AddText("CALICE AHCAL");
  pt5->AddText("Work in progress");

  TCanvas *c4 = new TCanvas("c3", "Timing vs Radius ShowerStart", 800, 600);
  c4->cd();
  multi5->Draw("APX");
  multi5->GetXaxis()->SetTitle("Distance to shower CoG [mm]");
  multi5->GetXaxis()->SetRangeUser(0, 380);
  multi5->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi5->GetYaxis()->SetRangeUser(-2, 18);
  pt5->Draw("SAME");
  leg5->Draw("SAME");
  multi5->Draw("E3");

  TString canvasname = "Plots/Timing_Radius_Comparison";
  canvasname += "_ShortAsymRange_ShowerStart.pdf";

  c4->SaveAs(canvasname);
}

void TimeData()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Comparison_Correlation_ShortAsymRange.root", "OPEN");
  TH2F *hPions50_short, *hPions50_long;

  f->GetObject("histo_Pion50_short", hPions50_short);
  f->GetObject("histo_Pion50_long", hPions50_long);

  hPions50_short->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hPions50_short->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hPions50_short->SetLineColor(kBlack);
  hPions50_short->SetLineWidth(2);

  hPions50_long->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hPions50_long->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hPions50_long->SetLineColor(kBlack);
  hPions50_long->SetLineWidth(2);

  int nEntries_long = hPions50_long->GetEntries();

  //Normalisation of each bin to the number of entries
  for(int i = 1; i < hPions50_long->GetNbinsX(); i++)
  {
    for(int j = 1; j < hPions50_long->GetNbinsY(); j++)
    {
      float content = hPions50_long->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hPions50_long->SetBinContent(i, j, new_content);
    }
  }

  //Long
  hPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  int low_bin = hPions50_long->GetXaxis()->FindBin(50);
  int high_bin = hPions50_long->GetXaxis()->FindBin(2000);
  float integral = hPions50_long->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  int nEntries_short = hPions50_short->GetEntries();

  for(int i = 1; i < hPions50_short->GetNbinsX(); i++)
  {
    for(int j = 1; j < hPions50_short->GetNbinsY(); j++)
    {
      float content = hPions50_short->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hPions50_short->SetBinContent(i, j, new_content);
    }
  }

  //Short
  hPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  low_bin = hPions50_short->GetXaxis()->FindBin(50);
  high_bin = hPions50_short->GetXaxis()->FindBin(2000);
  integral = hPions50_short->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  TPaveText *pt = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt->SetBorderSize(0);
  pt->SetTextColor(15);
  pt->SetFillColor(0);
  pt->SetTextSize(0.04);
  pt->SetTextAlign(13); //left center
  pt->AddText("CALICE AHCAL");
  pt->AddText("50 GeV #pi-");
  pt->AddText("Work in progress");

  TLine *line = new TLine(50, 50, 50, 2000);
  line->SetLineColor(kRed);
  line->SetLineWidth(3);
  line->SetLineStyle(2);

  TLine *line2 = new TLine(50, 50, 2000, 50);
  line2->SetLineColor(kRed);
  line2->SetLineWidth(3);
  line2->SetLineStyle(2);

  TLine *line3 = new TLine(2000, 50, 2000, 2000);
  line3->SetLineColor(kRed);
  line3->SetLineWidth(3);
  line3->SetLineStyle(2);

  TLine *line4 = new TLine(50, 2000, 2000, 2000);
  line4->SetLineColor(kRed);
  line4->SetLineWidth(3);
  line4->SetLineStyle(2);

  TCanvas *c2 = new TCanvas("c2", "", 800, 600);
  c2->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hPions50_short->Draw("COLZ");
  hPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetZaxis()->SetRangeUser(1e-6, 1);
  pt->Draw("SAME");
  line->Draw("same");
  line2->Draw("same");
  line3->Draw("same");
  line4->Draw("same");

  TCanvas *c3 = new TCanvas("c3", "", 800, 600);
  c3->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hPions50_long->Draw("COLZ");
  hPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetZaxis()->SetRangeUser(1e-6, 1);
  pt->Draw("SAME");
  line->Draw("same");
  line2->Draw("same");
  line3->Draw("same");
  line4->Draw("same");

  c2->SaveAs("Plots/Time_Correlation_short.pdf");
  c3->SaveAs("Plots/Time_Correlation_long.pdf");
}

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
  multi->GetYaxis()->SetRangeUser(0, 800);
  leg->Draw("same");
  leg2->Draw("same");
  gPad->Modified();

  c1->SaveAs("Plots/EsumPions_BeamEnergy.pdf");

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

  c2->SaveAs("Plots/nHitsPions_BeamEnergy.pdf");
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
  hData->GetXaxis()->SetRangeUser(0, 100);
  hData->GetYaxis()->SetRangeUser(0, 0.15);
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

  c1->SaveAs("Plots/Comparison_nHits_Xtalk_pions10GeV.pdf");

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
  hCoGZData->GetXaxis()->SetRangeUser(100, 800);
  hCoGZData->GetYaxis()->SetRangeUser(0, 0.01);
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

  c2->SaveAs("Plots/Comparison_CoGZ_Xtalk_pions10GeV.pdf");

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
  hEsumData->GetXaxis()->SetRangeUser(0, 800);
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

  c3->SaveAs("Plots/Comparison_EnergySum_Xtalk_pions10GeV.pdf");

  //------------------

  cout << "nHits " << 10 << " " << hData->GetMean() << " " << hSim_10->GetMean() << " " << hSim_18->GetMean() << " " << hSim_10_DD4hep->GetMean() << " " << hSim_18_DD4hep->GetMean() << endl;
  cout << "Esum " << 10 << " " << hEsumData->GetMean() << " " << hEsum_10->GetMean() << " " << hEsum_18->GetMean() << " " << hEsum_10_DD4hep->GetMean() << " " << hEsum_18_DD4hep->GetMean() << endl;
}

void Variables_90GeV()
{
  CaliceStyle();

  TFile *f = new TFile("Rootfiles/Hits_90GeV.root", "OPEN");
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
  hData->GetXaxis()->SetRangeUser(0, 200);
  hData->GetYaxis()->SetRangeUser(0, 0.04);
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

  c1->SaveAs("Plots/Comparison_nHits_Xtalk_pions90GeV.pdf");

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
  hCoGZData->GetXaxis()->SetRangeUser(200, 900);
  hCoGZData->GetYaxis()->SetRangeUser(0, 0.01);
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

  c2->SaveAs("Plots/Comparison_CoGZ_Xtalk_pions90GeV.pdf");

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
  hEsumData->GetXaxis()->SetRangeUser(0, 2000);
  hEsumData->GetYaxis()->SetRangeUser(0, 0.005);
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

  c3->SaveAs("Plots/Comparison_EnergySum_Xtalk_pions90GeV.pdf");

  //------------------

  cout << "nHits " << 90 << " " << hData->GetMean() << " " << hSim_10->GetMean() << " " << hSim_18->GetMean() << " " << hSim_10_DD4hep->GetMean() << " " << hSim_18_DD4hep->GetMean() << endl;
  cout << "Esum " << 90 << " " << hEsumData->GetMean() << " " << hEsum_10->GetMean() << " " << hEsum_18->GetMean() << " " << hEsum_10_DD4hep->GetMean() << " " << hEsum_18_DD4hep->GetMean() << endl;
}

void MakePlots()
{
  // TimingPions_10GeV();
  // TimingPions_30GeV();
  // TimingPions_50GeV();
  // TimingPions_70GeV();
  // TimingPions_90GeV();
  //
  // BeamProfile_10GeV();
  // BeamProfile_90GeV();
  //
  // SelectionCuts_10GeV();
  // SelectionCuts_90GeV();
  //
  // ShowerStartChecks();
  //
  // ComparisonTungstendNdt();
  // ComparisonTungstenEnergy();
  // ComparisonTungstenRadius();
  //
  // ComparisonData();
  // AdditionalShowerStart();
  // AdditionalShowerStart2();
  TimeCorrelationData();
  //
  // Validation();
  //
  // Variables_10GeV();
  // Variables_90GeV();
}
