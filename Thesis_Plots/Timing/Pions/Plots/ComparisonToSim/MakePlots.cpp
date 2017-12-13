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

void Energy_10GeV()
{
  CaliceStyle();
  //Comparison time vs energy
  int maxbin = 49;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergyData_Pion10;

  f->GetObject("Pion_profile10", pEnergyData_Pion10);

  TGraphErrors *gEnergyData_Pion10 = new TGraphErrors();
  gEnergyData_Pion10->SetMarkerSize(1);
  gEnergyData_Pion10->SetMarkerStyle(20);
  gEnergyData_Pion10->SetMarkerColor(kBlack);
  gEnergyData_Pion10->SetLineColor(kBlack);
  gEnergyData_Pion10->SetFillColor(kGray+1);
  gEnergyData_Pion10->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion10->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion10->GetBinContent(ibin);
    double energy = pEnergyData_Pion10->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;
    if(energy > 5) continue;

    double error_stat = pEnergyData_Pion10->GetBinError(ibin);
    double energy_err = pEnergyData_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gEnergyData_Pion10->SetPoint(ipoint, energy, content);
    gEnergyData_Pion10->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergySim_Pion10, *pEnergySim_Pion10_ErrorLow, *pEnergySim_Pion10_ErrorHigh, *pEnergySim_Pion10_Xtalk10, *pEnergySim_Pion10_Xtalk18;

  f2->GetObject("Pion_profile10", pEnergySim_Pion10);
  f2->GetObject("Pion_profile10_err_low", pEnergySim_Pion10_ErrorLow);
  f2->GetObject("Pion_profile10_err_high", pEnergySim_Pion10_ErrorHigh);
  f2->GetObject("Pion_profile10_xtalk10", pEnergySim_Pion10_Xtalk10);
  f2->GetObject("Pion_profile10_xtalk18", pEnergySim_Pion10_Xtalk18);

  TProfile *pEnergySim_Pion10_QBBC, *pEnergySim_Pion10_ErrorLow_QBBC, *pEnergySim_Pion10_ErrorHigh_QBBC, *pEnergySim_Pion10_Xtalk10_QBBC, *pEnergySim_Pion10_Xtalk18_QBBC;

  f2->GetObject("Pion_profile10_QBBC", pEnergySim_Pion10_QBBC);
  f2->GetObject("Pion_profile10_err_low_QBBC", pEnergySim_Pion10_ErrorLow_QBBC);
  f2->GetObject("Pion_profile10_err_high_QBBC", pEnergySim_Pion10_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile10_xtalk10_QBBC", pEnergySim_Pion10_Xtalk10_QBBC);
  f2->GetObject("Pion_profile10_xtalk18_QBBC", pEnergySim_Pion10_Xtalk18_QBBC);

  TProfile *pEnergySim_Pion10_QGSP_BERT, *pEnergySim_Pion10_ErrorLow_QGSP_BERT, *pEnergySim_Pion10_ErrorHigh_QGSP_BERT, *pEnergySim_Pion10_Xtalk10_QGSP_BERT, *pEnergySim_Pion10_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile10_QGSP_BERT", pEnergySim_Pion10_QGSP_BERT);
  f2->GetObject("Pion_profile10_err_low_QGSP_BERT", pEnergySim_Pion10_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile10_err_high_QGSP_BERT", pEnergySim_Pion10_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile10_xtalk10_QGSP_BERT", pEnergySim_Pion10_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile10_xtalk18_QGSP_BERT", pEnergySim_Pion10_Xtalk18_QGSP_BERT);

  TGraphAsymmErrors *gEnergySim_Pion10 = new TGraphAsymmErrors();
  gEnergySim_Pion10->SetMarkerSize(1);
  gEnergySim_Pion10->SetMarkerStyle(20);
  gEnergySim_Pion10->SetMarkerColor(kRed);
  gEnergySim_Pion10->SetLineColor(kRed);
  gEnergySim_Pion10->SetFillColor(kRed);
  gEnergySim_Pion10->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion10->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion10->GetBinContent(ibin);
    double energy = pEnergySim_Pion10->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion10_ErrorLow->GetBinContent(ibin);
    double content_up = pEnergySim_Pion10_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion10_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion10_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion10->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion10->SetPoint(ipoint, energy, content);
    gEnergySim_Pion10->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion10_QBBC = new TGraphAsymmErrors();
  gEnergySim_Pion10_QBBC->SetMarkerSize(1);
  gEnergySim_Pion10_QBBC->SetMarkerStyle(20);
  gEnergySim_Pion10_QBBC->SetMarkerColor(kBlue);
  gEnergySim_Pion10_QBBC->SetLineColor(kBlue);
  gEnergySim_Pion10_QBBC->SetFillColor(kBlue);
  gEnergySim_Pion10_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion10_QBBC->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion10_QBBC->GetBinContent(ibin);
    double energy = pEnergySim_Pion10_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion10_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pEnergySim_Pion10_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion10_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion10_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion10_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion10_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion10_QBBC->SetPoint(ipoint, energy, content);
    gEnergySim_Pion10_QBBC->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion10_QGSP_BERT = new TGraphAsymmErrors();
  gEnergySim_Pion10_QGSP_BERT->SetMarkerSize(1);
  gEnergySim_Pion10_QGSP_BERT->SetMarkerStyle(20);
  gEnergySim_Pion10_QGSP_BERT->SetMarkerColor(kGreen);
  gEnergySim_Pion10_QGSP_BERT->SetLineColor(kGreen);
  gEnergySim_Pion10_QGSP_BERT->SetFillColor(kGreen);
  gEnergySim_Pion10_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion10_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion10_QGSP_BERT->GetBinContent(ibin);
    double energy = pEnergySim_Pion10_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion10_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pEnergySim_Pion10_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion10_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion10_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion10_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion10_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion10_QGSP_BERT->SetPoint(ipoint, energy, content);
    gEnergySim_Pion10_QGSP_BERT->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange_DD4hep.root");
  TProfile *pEnergySim_Pion10_DD4hep, *pEnergySim_Pion10_ErrorLow_DD4hep, *pEnergySim_Pion10_ErrorHigh_DD4hep, *pEnergySim_Pion10_Xtalk10_DD4hep, *pEnergySim_Pion10_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile10", pEnergySim_Pion10_DD4hep);
  f3->GetObject("Pion_profile10_err_low", pEnergySim_Pion10_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile10_err_high", pEnergySim_Pion10_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile10_xtalk10", pEnergySim_Pion10_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile10_xtalk18", pEnergySim_Pion10_Xtalk18_DD4hep);

  TProfile *pEnergySim_Pion10_QBBC_DD4hep, *pEnergySim_Pion10_ErrorLow_QBBC_DD4hep, *pEnergySim_Pion10_ErrorHigh_QBBC_DD4hep, *pEnergySim_Pion10_Xtalk10_QBBC_DD4hep, *pEnergySim_Pion10_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile10_QBBC", pEnergySim_Pion10_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_err_low_QBBC", pEnergySim_Pion10_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_err_high_QBBC", pEnergySim_Pion10_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_xtalk10_QBBC", pEnergySim_Pion10_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_xtalk18_QBBC", pEnergySim_Pion10_Xtalk18_QBBC_DD4hep);

  TProfile *pEnergySim_Pion10_QGSP_BERT_DD4hep, *pEnergySim_Pion10_ErrorLow_QGSP_BERT_DD4hep, *pEnergySim_Pion10_ErrorHigh_QGSP_BERT_DD4hep, *pEnergySim_Pion10_Xtalk10_QGSP_BERT_DD4hep, *pEnergySim_Pion10_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile10_QGSP_BERT", pEnergySim_Pion10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_err_low_QGSP_BERT", pEnergySim_Pion10_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_err_high_QGSP_BERT", pEnergySim_Pion10_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_xtalk10_QGSP_BERT", pEnergySim_Pion10_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_xtalk18_QGSP_BERT", pEnergySim_Pion10_Xtalk18_QGSP_BERT_DD4hep);

  TGraphAsymmErrors *gEnergySim_Pion10_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion10_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion10_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion10_DD4hep->SetMarkerColor(kRed);
  gEnergySim_Pion10_DD4hep->SetLineColor(kRed);
  gEnergySim_Pion10_DD4hep->SetFillColor(kRed);
  gEnergySim_Pion10_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion10_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion10_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion10_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion10_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion10_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion10_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion10_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion10_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion10_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion10_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion10_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion10_QBBC_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion10_QBBC_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion10_QBBC_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion10_QBBC_DD4hep->SetMarkerColor(kBlue);
  gEnergySim_Pion10_QBBC_DD4hep->SetLineColor(kBlue);
  gEnergySim_Pion10_QBBC_DD4hep->SetFillColor(kBlue);
  gEnergySim_Pion10_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion10_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion10_QBBC_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion10_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion10_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion10_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion10_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion10_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion10_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion10_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion10_QBBC_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion10_QBBC_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion10_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion10_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion10_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion10_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gEnergySim_Pion10_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gEnergySim_Pion10_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gEnergySim_Pion10_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion10_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion10_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion10_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion10_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion10_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion10_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion10_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion10_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion10_QGSP_BERT_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion10_QGSP_BERT_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gEnergyData_Pion10, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gEnergySim_Pion10_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gEnergySim_Pion10, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gEnergySim_Pion10_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gEnergySim_Pion10_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gEnergySim_Pion10_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gEnergySim_Pion10_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("10 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Pion10);
  multi2->Add(gEnergySim_Pion10);
  multi2->Add(gEnergySim_Pion10_QGSP_BERT);
  multi2->Add(gEnergySim_Pion10_QBBC);
  multi2->Add(gEnergySim_Pion10_DD4hep);
  multi2->Add(gEnergySim_Pion10_QGSP_BERT_DD4hep);
  multi2->Add(gEnergySim_Pion10_QBBC_DD4hep);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Energy", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Deposition [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Energy_10GeV.pdf");
}

void Radius_10GeV()
{
  CaliceStyle();
  //Comparison time vs Radius
  for(int type = 1; type < 3; type++)
  {
    //Data
    TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusData_Pion10;

    if(type == 1)
    f->GetObject("Pion_profile10_SSF", pRadiusData_Pion10);
    if(type == 2)
    f->GetObject("Pion_profile10_BL", pRadiusData_Pion10);

    TGraphErrors *gRadiusData_Pion10 = new TGraphErrors();
    gRadiusData_Pion10->SetMarkerSize(1);
    gRadiusData_Pion10->SetMarkerStyle(20);
    gRadiusData_Pion10->SetMarkerColor(kBlack);
    gRadiusData_Pion10->SetLineColor(kBlack);
    gRadiusData_Pion10->SetFillColor(kGray+1);
    gRadiusData_Pion10->SetFillStyle(3001);

    int ipoint = 0;
    for(int ibin = 1; ibin < pRadiusData_Pion10->GetNbinsX(); ibin++)
    {
      double content = pRadiusData_Pion10->GetBinContent(ibin);
      double radius = pRadiusData_Pion10->GetXaxis()->GetBinCenter(ibin);

      if(content == 0) continue;

      if(type == 1 && radius > 240) continue;
      if(type == 2 && radius > 350) continue;

      double error_stat = pRadiusData_Pion10->GetBinError(ibin);

      //Error syst
      double error_syst = 0;
      if(type == 1) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 10, "SSF"));
      if(type == 2) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 10, "BL"));

      double radius_err = pRadiusData_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusData_Pion10->SetPoint(ipoint, radius, content);
      gRadiusData_Pion10->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
      ipoint++;
    }

    //MC
    TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusSim_Pion10, *pRadiusSim_Pion10_ErrorLow, *pRadiusSim_Pion10_ErrorHigh, *pRadiusSim_Pion10_Xtalk10, *pRadiusSim_Pion10_Xtalk18;

    if(type == 1)
    {
      f2->GetObject("Pion_profile10_SSF", pRadiusSim_Pion10);
      f2->GetObject("Pion_profile10_err_low_SSF", pRadiusSim_Pion10_ErrorLow);
      f2->GetObject("Pion_profile10_err_high_SSF", pRadiusSim_Pion10_ErrorHigh);
      f2->GetObject("Pion_profile10_xtalk10_SSF", pRadiusSim_Pion10_Xtalk10);
      f2->GetObject("Pion_profile10_xtalk18_SSF", pRadiusSim_Pion10_Xtalk18);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile10_BL", pRadiusSim_Pion10);
      f2->GetObject("Pion_profile10_err_low_BL", pRadiusSim_Pion10_ErrorLow);
      f2->GetObject("Pion_profile10_err_high_BL", pRadiusSim_Pion10_ErrorHigh);
      f2->GetObject("Pion_profile10_xtalk10_BL", pRadiusSim_Pion10_Xtalk10);
      f2->GetObject("Pion_profile10_xtalk18_BL", pRadiusSim_Pion10_Xtalk18);
    }

    //QBBC
    TProfile *pRadiusSim_Pion10_QBBC, *pRadiusSim_Pion10_ErrorLow_QBBC, *pRadiusSim_Pion10_ErrorHigh_QBBC, *pRadiusSim_Pion10_Xtalk10_QBBC, *pRadiusSim_Pion10_Xtalk18_QBBC;

    if(type == 1)
    {
      f2->GetObject("Pion_profile10_SSF_QBBC", pRadiusSim_Pion10_QBBC);
      f2->GetObject("Pion_profile10_err_low_SSF_QBBC", pRadiusSim_Pion10_ErrorLow_QBBC);
      f2->GetObject("Pion_profile10_err_high_SSF_QBBC", pRadiusSim_Pion10_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile10_xtalk10_SSF_QBBC", pRadiusSim_Pion10_Xtalk10_QBBC);
      f2->GetObject("Pion_profile10_xtalk18_SSF_QBBC", pRadiusSim_Pion10_Xtalk18_QBBC);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile10_BL_QBBC", pRadiusSim_Pion10_QBBC);
      f2->GetObject("Pion_profile10_err_low_BL_QBBC", pRadiusSim_Pion10_ErrorLow_QBBC);
      f2->GetObject("Pion_profile10_err_high_BL_QBBC", pRadiusSim_Pion10_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile10_xtalk10_BL_QBBC", pRadiusSim_Pion10_Xtalk10_QBBC);
      f2->GetObject("Pion_profile10_xtalk18_BL_QBBC", pRadiusSim_Pion10_Xtalk18_QBBC);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion10_QGSP_BERT, *pRadiusSim_Pion10_ErrorLow_QGSP_BERT, *pRadiusSim_Pion10_ErrorHigh_QGSP_BERT, *pRadiusSim_Pion10_Xtalk10_QGSP_BERT, *pRadiusSim_Pion10_Xtalk18_QGSP_BERT;

    if(type == 1)
    {
      f2->GetObject("Pion_profile10_SSF_QGSP_BERT", pRadiusSim_Pion10_QGSP_BERT);
      f2->GetObject("Pion_profile10_err_low_SSF_QGSP_BERT", pRadiusSim_Pion10_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile10_err_high_SSF_QGSP_BERT", pRadiusSim_Pion10_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile10_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion10_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile10_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion10_Xtalk18_QGSP_BERT);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile10_BL_QGSP_BERT", pRadiusSim_Pion10_QGSP_BERT);
      f2->GetObject("Pion_profile10_err_low_BL_QGSP_BERT", pRadiusSim_Pion10_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile10_err_high_BL_QGSP_BERT", pRadiusSim_Pion10_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile10_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion10_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile10_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion10_Xtalk18_QGSP_BERT);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion10 = new TGraphAsymmErrors();
    gRadiusSim_Pion10->SetMarkerSize(1);
    gRadiusSim_Pion10->SetMarkerStyle(20);
    gRadiusSim_Pion10->SetMarkerColor(kRed);
    gRadiusSim_Pion10->SetLineColor(kRed);
    gRadiusSim_Pion10->SetFillColor(kRed);
    gRadiusSim_Pion10->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion10->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion10->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion10->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion10_ErrorLow->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion10_ErrorHigh->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion10_Xtalk10->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion10_Xtalk18->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion10->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion10->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion10->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion10_QBBC = new TGraphAsymmErrors();
    gRadiusSim_Pion10_QBBC->SetMarkerSize(1);
    gRadiusSim_Pion10_QBBC->SetMarkerStyle(20);
    gRadiusSim_Pion10_QBBC->SetMarkerColor(kBlue);
    gRadiusSim_Pion10_QBBC->SetLineColor(kBlue);
    gRadiusSim_Pion10_QBBC->SetFillColor(kBlue);
    gRadiusSim_Pion10_QBBC->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion10_QBBC->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion10_QBBC->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion10_QBBC->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion10_ErrorLow_QBBC->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion10_ErrorHigh_QBBC->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion10_Xtalk10_QBBC->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion10_Xtalk18_QBBC->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion10_QBBC->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion10_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion10_QBBC->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion10_QBBC->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion10_QGSP_BERT = new TGraphAsymmErrors();
    gRadiusSim_Pion10_QGSP_BERT->SetMarkerSize(1);
    gRadiusSim_Pion10_QGSP_BERT->SetMarkerStyle(20);
    gRadiusSim_Pion10_QGSP_BERT->SetMarkerColor(kGreen);
    gRadiusSim_Pion10_QGSP_BERT->SetLineColor(kGreen);
    gRadiusSim_Pion10_QGSP_BERT->SetFillColor(kGreen);
    gRadiusSim_Pion10_QGSP_BERT->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion10_QGSP_BERT->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion10_QGSP_BERT->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion10_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion10_ErrorLow_QGSP_BERT->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion10_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion10_Xtalk10_QGSP_BERT->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion10_Xtalk18_QGSP_BERT->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion10_QGSP_BERT->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion10_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion10_QGSP_BERT->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion10_QGSP_BERT->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //DD4hep
    TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange_DD4hep.root");
    TProfile *pRadiusSim_Pion10_DD4hep, *pRadiusSim_Pion10_ErrorLow_DD4hep, *pRadiusSim_Pion10_ErrorHigh_DD4hep, *pRadiusSim_Pion10_Xtalk10_DD4hep, *pRadiusSim_Pion10_Xtalk18_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile10_SSF", pRadiusSim_Pion10_DD4hep);
      f3->GetObject("Pion_profile10_err_low_SSF", pRadiusSim_Pion10_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile10_err_high_SSF", pRadiusSim_Pion10_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile10_xtalk10_SSF", pRadiusSim_Pion10_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile10_xtalk18_SSF", pRadiusSim_Pion10_Xtalk18_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile10_BL", pRadiusSim_Pion10_DD4hep);
      f3->GetObject("Pion_profile10_err_low_BL", pRadiusSim_Pion10_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile10_err_high_BL", pRadiusSim_Pion10_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile10_xtalk10_BL", pRadiusSim_Pion10_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile10_xtalk18_BL", pRadiusSim_Pion10_Xtalk18_DD4hep);
    }

    //QBBC
    TProfile *pRadiusSim_Pion10_QBBC_DD4hep, *pRadiusSim_Pion10_ErrorLow_QBBC_DD4hep, *pRadiusSim_Pion10_ErrorHigh_QBBC_DD4hep, *pRadiusSim_Pion10_Xtalk10_QBBC_DD4hep, *pRadiusSim_Pion10_Xtalk18_QBBC_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile10_SSF_QBBC", pRadiusSim_Pion10_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_err_low_SSF_QBBC", pRadiusSim_Pion10_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_err_high_SSF_QBBC", pRadiusSim_Pion10_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_xtalk10_SSF_QBBC", pRadiusSim_Pion10_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_xtalk18_SSF_QBBC", pRadiusSim_Pion10_Xtalk18_QBBC_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile10_BL_QBBC", pRadiusSim_Pion10_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_err_low_BL_QBBC", pRadiusSim_Pion10_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_err_high_BL_QBBC", pRadiusSim_Pion10_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_xtalk10_BL_QBBC", pRadiusSim_Pion10_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile10_xtalk18_BL_QBBC", pRadiusSim_Pion10_Xtalk18_QBBC_DD4hep);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion10_QGSP_BERT_DD4hep, *pRadiusSim_Pion10_ErrorLow_QGSP_BERT_DD4hep, *pRadiusSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep, *pRadiusSim_Pion10_Xtalk10_QGSP_BERT_DD4hep, *pRadiusSim_Pion10_Xtalk18_QGSP_BERT_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile10_SSF_QGSP_BERT", pRadiusSim_Pion10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_err_low_SSF_QGSP_BERT", pRadiusSim_Pion10_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_err_high_SSF_QGSP_BERT", pRadiusSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion10_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion10_Xtalk18_QGSP_BERT_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile10_BL_QGSP_BERT", pRadiusSim_Pion10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_err_low_BL_QGSP_BERT", pRadiusSim_Pion10_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_err_high_BL_QGSP_BERT", pRadiusSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion10_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile10_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion10_Xtalk18_QGSP_BERT_DD4hep);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion10_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion10_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion10_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion10_DD4hep->SetMarkerColor(kRed);
    gRadiusSim_Pion10_DD4hep->SetLineColor(kRed);
    gRadiusSim_Pion10_DD4hep->SetFillColor(kRed);
    gRadiusSim_Pion10_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion10_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion10_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion10_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion10_ErrorLow_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion10_ErrorHigh_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion10_Xtalk10_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion10_Xtalk18_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion10_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion10_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion10_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion10_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion10_QBBC_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion10_QBBC_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion10_QBBC_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion10_QBBC_DD4hep->SetMarkerColor(kBlue);
    gRadiusSim_Pion10_QBBC_DD4hep->SetLineColor(kBlue);
    gRadiusSim_Pion10_QBBC_DD4hep->SetFillColor(kBlue);
    gRadiusSim_Pion10_QBBC_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion10_QBBC_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion10_QBBC_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion10_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion10_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion10_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion10_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion10_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion10_QBBC_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion10_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion10_QBBC_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion10_QBBC_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion10_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
    gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetLineColor(kGreen);
    gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetFillColor(kGreen);
    gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion10_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion10_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion10_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion10_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion10_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion10_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion10_QGSP_BERT_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion10_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion10_QGSP_BERT_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //--------------------------------------------------------

    TLegend *leg2 = new TLegend(0.20, 0.55, 0.40, 0.75);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.025);
    leg2->SetHeader("Mokka");
    leg2->AddEntry(gRadiusData_Pion10, "Data (stat #oplus syst)", "pf");
    leg2->AddEntry(gRadiusSim_Pion10_QGSP_BERT, "QGSP_BERT", "pf");
    leg2->AddEntry(gRadiusSim_Pion10, "QGSP_BERT_HP", "pf");
    leg2->AddEntry(gRadiusSim_Pion10_QBBC, "QBBC", "pf");

    TLegend *leg3 = new TLegend(0.20, 0.35, 0.40, 0.52);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.025);
    leg3->SetHeader("DD4hep");
    leg3->AddEntry(gRadiusSim_Pion10_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
    leg3->AddEntry(gRadiusSim_Pion10_DD4hep, "QGSP_BERT_HP", "pf");
    leg3->AddEntry(gRadiusSim_Pion10_QBBC_DD4hep, "QBBC", "pf");

    TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
    pt2->SetBorderSize(0);
    pt2->SetTextColor(15);
    pt2->SetFillColor(0);
    pt2->SetTextSize(0.04);
    pt2->SetTextAlign(13); //left center
    pt2->AddText("CALICE AHCAL");
    pt2->AddText("Work in progress");
    pt2->AddText("10 GeV #pi^{-} - steel");

    TMultiGraph *multi2 = new TMultiGraph();
    multi2->Add(gRadiusData_Pion10);
    multi2->Add(gRadiusSim_Pion10);
    multi2->Add(gRadiusSim_Pion10_QGSP_BERT);
    multi2->Add(gRadiusSim_Pion10_QBBC);
    multi2->Add(gRadiusSim_Pion10_DD4hep);
    multi2->Add(gRadiusSim_Pion10_QGSP_BERT_DD4hep);
    multi2->Add(gRadiusSim_Pion10_QBBC_DD4hep);

    TCanvas *c2 = new TCanvas("c2", "Timing vs Radius", 800, 600);
    c2->cd();
    multi2->Draw("APX");
    multi2->GetXaxis()->SetTitle("Shower Radius [mm]");
    multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
    multi2->GetYaxis()->SetRangeUser(-1, 12);
    pt2->Draw("SAME");
    leg2->Draw("SAME");
    leg3->Draw("SAME");

    if(type == 1)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 15);
      multi2->GetXaxis()->SetRangeUser(0, 250);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_10GeV_SSF.pdf");
    }
    if(type == 2)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 12);
      multi2->GetXaxis()->SetRangeUser(0, 400);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_10GeV_BL.pdf");
    }
  }
}

void Depth_10GeV()
{
  CaliceStyle();
  //Comparison time vs Depth
  int maxbin = 11;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthData_Pion10;

  f->GetObject("Pion_profile10", pDepthData_Pion10);

  TGraphErrors *gDepthData_Pion10 = new TGraphErrors();
  gDepthData_Pion10->SetMarkerSize(1);
  gDepthData_Pion10->SetMarkerStyle(20);
  gDepthData_Pion10->SetMarkerColor(kBlack);
  gDepthData_Pion10->SetLineColor(kBlack);
  gDepthData_Pion10->SetFillColor(kGray+1);
  gDepthData_Pion10->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion10->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion10->GetBinContent(ibin);
    double Depth = pDepthData_Pion10->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion10->GetBinError(ibin);
    //Error syst
    double error_syst = 1.04;

    double Depth_err = pDepthData_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthData_Pion10->SetPoint(ipoint, Depth, content);
    gDepthData_Pion10->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthSim_Pion10, *pDepthSim_Pion10_ErrorLow, *pDepthSim_Pion10_ErrorHigh, *pDepthSim_Pion10_Xtalk10, *pDepthSim_Pion10_Xtalk18;

  f2->GetObject("Pion_profile10", pDepthSim_Pion10);
  f2->GetObject("Pion_profile10_err_low", pDepthSim_Pion10_ErrorLow);
  f2->GetObject("Pion_profile10_err_high", pDepthSim_Pion10_ErrorHigh);
  f2->GetObject("Pion_profile10_xtalk10", pDepthSim_Pion10_Xtalk10);
  f2->GetObject("Pion_profile10_xtalk18", pDepthSim_Pion10_Xtalk18);

  //QBBC
  TProfile *pDepthSim_Pion10_QBBC, *pDepthSim_Pion10_ErrorLow_QBBC, *pDepthSim_Pion10_ErrorHigh_QBBC, *pDepthSim_Pion10_Xtalk10_QBBC, *pDepthSim_Pion10_Xtalk18_QBBC;

  f2->GetObject("Pion_profile10_QBBC", pDepthSim_Pion10_QBBC);
  f2->GetObject("Pion_profile10_err_low_QBBC", pDepthSim_Pion10_ErrorLow_QBBC);
  f2->GetObject("Pion_profile10_err_high_QBBC", pDepthSim_Pion10_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile10_xtalk10_QBBC", pDepthSim_Pion10_Xtalk10_QBBC);
  f2->GetObject("Pion_profile10_xtalk18_QBBC", pDepthSim_Pion10_Xtalk18_QBBC);

  //QGSP_BERT
  TProfile *pDepthSim_Pion10_QGSP_BERT, *pDepthSim_Pion10_ErrorLow_QGSP_BERT, *pDepthSim_Pion10_ErrorHigh_QGSP_BERT, *pDepthSim_Pion10_Xtalk10_QGSP_BERT, *pDepthSim_Pion10_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile10_QGSP_BERT", pDepthSim_Pion10_QGSP_BERT);
  f2->GetObject("Pion_profile10_err_low_QGSP_BERT", pDepthSim_Pion10_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile10_err_high_QGSP_BERT", pDepthSim_Pion10_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile10_xtalk10_QGSP_BERT", pDepthSim_Pion10_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile10_xtalk18_QGSP_BERT", pDepthSim_Pion10_Xtalk18_QGSP_BERT);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion10 = new TGraphAsymmErrors();
  gDepthSim_Pion10->SetMarkerSize(1);
  gDepthSim_Pion10->SetMarkerStyle(20);
  gDepthSim_Pion10->SetMarkerColor(kRed);
  gDepthSim_Pion10->SetLineColor(kRed);
  gDepthSim_Pion10->SetFillColor(kRed);
  gDepthSim_Pion10->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion10->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion10->GetBinContent(ibin);
    double Depth = pDepthSim_Pion10->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion10_ErrorLow->GetBinContent(ibin);
    double content_up = pDepthSim_Pion10_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion10_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion10_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion10->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion10->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion10->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion10->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion10_QBBC = new TGraphAsymmErrors();
  gDepthSim_Pion10_QBBC->SetMarkerSize(1);
  gDepthSim_Pion10_QBBC->SetMarkerStyle(20);
  gDepthSim_Pion10_QBBC->SetMarkerColor(kBlue);
  gDepthSim_Pion10_QBBC->SetLineColor(kBlue);
  gDepthSim_Pion10_QBBC->SetFillColor(kBlue);
  gDepthSim_Pion10_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion10_QBBC->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion10_QBBC->GetBinContent(ibin);
    double Depth = pDepthSim_Pion10_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion10_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pDepthSim_Pion10_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion10_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion10_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion10_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion10_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion10_QBBC->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion10_QBBC->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion10_QGSP_BERT = new TGraphAsymmErrors();
  gDepthSim_Pion10_QGSP_BERT->SetMarkerSize(1);
  gDepthSim_Pion10_QGSP_BERT->SetMarkerStyle(20);
  gDepthSim_Pion10_QGSP_BERT->SetMarkerColor(kGreen);
  gDepthSim_Pion10_QGSP_BERT->SetLineColor(kGreen);
  gDepthSim_Pion10_QGSP_BERT->SetFillColor(kGreen);
  gDepthSim_Pion10_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion10_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion10_QGSP_BERT->GetBinContent(ibin);
    double Depth = pDepthSim_Pion10_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion10_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pDepthSim_Pion10_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion10_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion10_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion10_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion10_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion10_QGSP_BERT->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion10_QGSP_BERT->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange_DD4hep.root");
  TProfile *pDepthSim_Pion10_DD4hep, *pDepthSim_Pion10_ErrorLow_DD4hep, *pDepthSim_Pion10_ErrorHigh_DD4hep, *pDepthSim_Pion10_Xtalk10_DD4hep, *pDepthSim_Pion10_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile10", pDepthSim_Pion10_DD4hep);
  f3->GetObject("Pion_profile10_err_low", pDepthSim_Pion10_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile10_err_high", pDepthSim_Pion10_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile10_xtalk10", pDepthSim_Pion10_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile10_xtalk18", pDepthSim_Pion10_Xtalk18_DD4hep);

  //QBBC
  TProfile *pDepthSim_Pion10_QBBC_DD4hep, *pDepthSim_Pion10_ErrorLow_QBBC_DD4hep, *pDepthSim_Pion10_ErrorHigh_QBBC_DD4hep, *pDepthSim_Pion10_Xtalk10_QBBC_DD4hep, *pDepthSim_Pion10_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile10_QBBC", pDepthSim_Pion10_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_err_low_QBBC", pDepthSim_Pion10_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_err_high_QBBC", pDepthSim_Pion10_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_xtalk10_QBBC", pDepthSim_Pion10_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile10_xtalk18_QBBC", pDepthSim_Pion10_Xtalk18_QBBC_DD4hep);

  //QGSP_BERT
  TProfile *pDepthSim_Pion10_QGSP_BERT_DD4hep, *pDepthSim_Pion10_ErrorLow_QGSP_BERT_DD4hep, *pDepthSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep, *pDepthSim_Pion10_Xtalk10_QGSP_BERT_DD4hep, *pDepthSim_Pion10_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile10_QGSP_BERT", pDepthSim_Pion10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_err_low_QGSP_BERT", pDepthSim_Pion10_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_err_high_QGSP_BERT", pDepthSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_xtalk10_QGSP_BERT", pDepthSim_Pion10_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile10_xtalk18_QGSP_BERT", pDepthSim_Pion10_Xtalk18_QGSP_BERT_DD4hep);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion10_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion10_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion10_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion10_DD4hep->SetMarkerColor(kRed);
  gDepthSim_Pion10_DD4hep->SetLineColor(kRed);
  gDepthSim_Pion10_DD4hep->SetFillColor(kRed);
  gDepthSim_Pion10_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion10_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion10_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion10_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion10_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion10_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion10_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion10_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion10_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion10_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion10_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion10_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion10_QBBC_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion10_QBBC_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion10_QBBC_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion10_QBBC_DD4hep->SetMarkerColor(kBlue);
  gDepthSim_Pion10_QBBC_DD4hep->SetLineColor(kBlue);
  gDepthSim_Pion10_QBBC_DD4hep->SetFillColor(kBlue);
  gDepthSim_Pion10_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion10_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion10_QBBC_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion10_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion10_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion10_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion10_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion10_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion10_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion10_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion10_QBBC_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion10_QBBC_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion10_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion10_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion10_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion10_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gDepthSim_Pion10_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gDepthSim_Pion10_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gDepthSim_Pion10_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion10_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion10_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion10_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion10_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion10_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion10_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion10_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion10_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion10_QGSP_BERT_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion10_QGSP_BERT_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.65, 0.92, 0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gDepthData_Pion10, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gDepthSim_Pion10_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gDepthSim_Pion10, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gDepthSim_Pion10_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.48, 0.92, 0.63);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gDepthSim_Pion10_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gDepthSim_Pion10_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gDepthSim_Pion10_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.70, 0.4, 0.85, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("10 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gDepthData_Pion10);
  multi2->Add(gDepthSim_Pion10);
  multi2->Add(gDepthSim_Pion10_QGSP_BERT);
  multi2->Add(gDepthSim_Pion10_QBBC);
  multi2->Add(gDepthSim_Pion10_DD4hep);
  multi2->Add(gDepthSim_Pion10_QGSP_BERT_DD4hep);
  multi2->Add(gDepthSim_Pion10_QBBC_DD4hep);

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Depth", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Layer Position [mm]");
  multi2->GetXaxis()->SetRangeUser(50, 850);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");
  TGaxis *axis = new TGaxis(48, 10, 851, 10, 0.02, 4.17, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  c2->SaveAs("Plots/ComparisonToSim/Time_Depth_10GeV.pdf");
}

void Energy_30GeV()
{
  CaliceStyle();
  //Comparison time vs energy
  int maxbin = 49;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergyData_Pion30;

  f->GetObject("Pion_profile30", pEnergyData_Pion30);

  TGraphErrors *gEnergyData_Pion30 = new TGraphErrors();
  gEnergyData_Pion30->SetMarkerSize(1);
  gEnergyData_Pion30->SetMarkerStyle(20);
  gEnergyData_Pion30->SetMarkerColor(kBlack);
  gEnergyData_Pion30->SetLineColor(kBlack);
  gEnergyData_Pion30->SetFillColor(kGray+1);
  gEnergyData_Pion30->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion30->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion30->GetBinContent(ibin);
    double energy = pEnergyData_Pion30->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;
    if(energy > 5) continue;

    double error_stat = pEnergyData_Pion30->GetBinError(ibin);
    double energy_err = pEnergyData_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gEnergyData_Pion30->SetPoint(ipoint, energy, content);
    gEnergyData_Pion30->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergySim_Pion30, *pEnergySim_Pion30_ErrorLow, *pEnergySim_Pion30_ErrorHigh, *pEnergySim_Pion30_Xtalk10, *pEnergySim_Pion30_Xtalk18;

  f2->GetObject("Pion_profile30", pEnergySim_Pion30);
  f2->GetObject("Pion_profile30_err_low", pEnergySim_Pion30_ErrorLow);
  f2->GetObject("Pion_profile30_err_high", pEnergySim_Pion30_ErrorHigh);
  f2->GetObject("Pion_profile30_xtalk10", pEnergySim_Pion30_Xtalk10);
  f2->GetObject("Pion_profile30_xtalk18", pEnergySim_Pion30_Xtalk18);

  TProfile *pEnergySim_Pion30_QBBC, *pEnergySim_Pion30_ErrorLow_QBBC, *pEnergySim_Pion30_ErrorHigh_QBBC, *pEnergySim_Pion30_Xtalk10_QBBC, *pEnergySim_Pion30_Xtalk18_QBBC;

  f2->GetObject("Pion_profile30_QBBC", pEnergySim_Pion30_QBBC);
  f2->GetObject("Pion_profile30_err_low_QBBC", pEnergySim_Pion30_ErrorLow_QBBC);
  f2->GetObject("Pion_profile30_err_high_QBBC", pEnergySim_Pion30_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile30_xtalk10_QBBC", pEnergySim_Pion30_Xtalk10_QBBC);
  f2->GetObject("Pion_profile30_xtalk18_QBBC", pEnergySim_Pion30_Xtalk18_QBBC);

  TProfile *pEnergySim_Pion30_QGSP_BERT, *pEnergySim_Pion30_ErrorLow_QGSP_BERT, *pEnergySim_Pion30_ErrorHigh_QGSP_BERT, *pEnergySim_Pion30_Xtalk10_QGSP_BERT, *pEnergySim_Pion30_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile30_QGSP_BERT", pEnergySim_Pion30_QGSP_BERT);
  f2->GetObject("Pion_profile30_err_low_QGSP_BERT", pEnergySim_Pion30_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile30_err_high_QGSP_BERT", pEnergySim_Pion30_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile30_xtalk10_QGSP_BERT", pEnergySim_Pion30_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile30_xtalk18_QGSP_BERT", pEnergySim_Pion30_Xtalk18_QGSP_BERT);

  TGraphAsymmErrors *gEnergySim_Pion30 = new TGraphAsymmErrors();
  gEnergySim_Pion30->SetMarkerSize(1);
  gEnergySim_Pion30->SetMarkerStyle(20);
  gEnergySim_Pion30->SetMarkerColor(kRed);
  gEnergySim_Pion30->SetLineColor(kRed);
  gEnergySim_Pion30->SetFillColor(kRed);
  gEnergySim_Pion30->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion30->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion30->GetBinContent(ibin);
    double energy = pEnergySim_Pion30->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion30_ErrorLow->GetBinContent(ibin);
    double content_up = pEnergySim_Pion30_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion30_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion30_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion30->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion30->SetPoint(ipoint, energy, content);
    gEnergySim_Pion30->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion30_QBBC = new TGraphAsymmErrors();
  gEnergySim_Pion30_QBBC->SetMarkerSize(1);
  gEnergySim_Pion30_QBBC->SetMarkerStyle(20);
  gEnergySim_Pion30_QBBC->SetMarkerColor(kBlue);
  gEnergySim_Pion30_QBBC->SetLineColor(kBlue);
  gEnergySim_Pion30_QBBC->SetFillColor(kBlue);
  gEnergySim_Pion30_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion30_QBBC->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion30_QBBC->GetBinContent(ibin);
    double energy = pEnergySim_Pion30_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion30_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pEnergySim_Pion30_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion30_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion30_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion30_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion30_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion30_QBBC->SetPoint(ipoint, energy, content);
    gEnergySim_Pion30_QBBC->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion30_QGSP_BERT = new TGraphAsymmErrors();
  gEnergySim_Pion30_QGSP_BERT->SetMarkerSize(1);
  gEnergySim_Pion30_QGSP_BERT->SetMarkerStyle(20);
  gEnergySim_Pion30_QGSP_BERT->SetMarkerColor(kGreen);
  gEnergySim_Pion30_QGSP_BERT->SetLineColor(kGreen);
  gEnergySim_Pion30_QGSP_BERT->SetFillColor(kGreen);
  gEnergySim_Pion30_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion30_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion30_QGSP_BERT->GetBinContent(ibin);
    double energy = pEnergySim_Pion30_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion30_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pEnergySim_Pion30_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion30_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion30_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion30_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion30_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion30_QGSP_BERT->SetPoint(ipoint, energy, content);
    gEnergySim_Pion30_QGSP_BERT->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange_DD4hep.root");
  TProfile *pEnergySim_Pion30_DD4hep, *pEnergySim_Pion30_ErrorLow_DD4hep, *pEnergySim_Pion30_ErrorHigh_DD4hep, *pEnergySim_Pion30_Xtalk10_DD4hep, *pEnergySim_Pion30_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile30", pEnergySim_Pion30_DD4hep);
  f3->GetObject("Pion_profile30_err_low", pEnergySim_Pion30_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile30_err_high", pEnergySim_Pion30_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile30_xtalk10", pEnergySim_Pion30_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile30_xtalk18", pEnergySim_Pion30_Xtalk18_DD4hep);

  TProfile *pEnergySim_Pion30_QBBC_DD4hep, *pEnergySim_Pion30_ErrorLow_QBBC_DD4hep, *pEnergySim_Pion30_ErrorHigh_QBBC_DD4hep, *pEnergySim_Pion30_Xtalk10_QBBC_DD4hep, *pEnergySim_Pion30_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile30_QBBC", pEnergySim_Pion30_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_err_low_QBBC", pEnergySim_Pion30_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_err_high_QBBC", pEnergySim_Pion30_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_xtalk10_QBBC", pEnergySim_Pion30_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_xtalk18_QBBC", pEnergySim_Pion30_Xtalk18_QBBC_DD4hep);

  TProfile *pEnergySim_Pion30_QGSP_BERT_DD4hep, *pEnergySim_Pion30_ErrorLow_QGSP_BERT_DD4hep, *pEnergySim_Pion30_ErrorHigh_QGSP_BERT_DD4hep, *pEnergySim_Pion30_Xtalk10_QGSP_BERT_DD4hep, *pEnergySim_Pion30_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile30_QGSP_BERT", pEnergySim_Pion30_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_err_low_QGSP_BERT", pEnergySim_Pion30_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_err_high_QGSP_BERT", pEnergySim_Pion30_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_xtalk10_QGSP_BERT", pEnergySim_Pion30_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_xtalk18_QGSP_BERT", pEnergySim_Pion30_Xtalk18_QGSP_BERT_DD4hep);

  TGraphAsymmErrors *gEnergySim_Pion30_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion30_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion30_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion30_DD4hep->SetMarkerColor(kRed);
  gEnergySim_Pion30_DD4hep->SetLineColor(kRed);
  gEnergySim_Pion30_DD4hep->SetFillColor(kRed);
  gEnergySim_Pion30_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion30_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion30_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion30_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion30_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion30_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion30_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion30_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion30_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion30_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion30_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion30_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion30_QBBC_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion30_QBBC_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion30_QBBC_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion30_QBBC_DD4hep->SetMarkerColor(kBlue);
  gEnergySim_Pion30_QBBC_DD4hep->SetLineColor(kBlue);
  gEnergySim_Pion30_QBBC_DD4hep->SetFillColor(kBlue);
  gEnergySim_Pion30_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion30_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion30_QBBC_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion30_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion30_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion30_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion30_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion30_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion30_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion30_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion30_QBBC_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion30_QBBC_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion30_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion30_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion30_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion30_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gEnergySim_Pion30_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gEnergySim_Pion30_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gEnergySim_Pion30_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion30_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion30_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion30_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion30_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion30_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion30_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion30_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion30_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion30_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion30_QGSP_BERT_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion30_QGSP_BERT_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gEnergyData_Pion30, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gEnergySim_Pion30_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gEnergySim_Pion30, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gEnergySim_Pion30_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gEnergySim_Pion30_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gEnergySim_Pion30_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gEnergySim_Pion30_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("30 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Pion30);
  multi2->Add(gEnergySim_Pion30);
  multi2->Add(gEnergySim_Pion30_QGSP_BERT);
  multi2->Add(gEnergySim_Pion30_QBBC);
  multi2->Add(gEnergySim_Pion30_DD4hep);
  multi2->Add(gEnergySim_Pion30_QGSP_BERT_DD4hep);
  multi2->Add(gEnergySim_Pion30_QBBC_DD4hep);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Energy", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Deposition [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Energy_30GeV.pdf");
}

void Radius_30GeV()
{
  CaliceStyle();
  //Comparison time vs Radius
  for(int type = 1; type < 3; type++)
  {
    //Data
    TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusData_Pion30;

    if(type == 1)
    f->GetObject("Pion_profile30_SSF", pRadiusData_Pion30);
    if(type == 2)
    f->GetObject("Pion_profile30_BL", pRadiusData_Pion30);

    TGraphErrors *gRadiusData_Pion30 = new TGraphErrors();
    gRadiusData_Pion30->SetMarkerSize(1);
    gRadiusData_Pion30->SetMarkerStyle(20);
    gRadiusData_Pion30->SetMarkerColor(kBlack);
    gRadiusData_Pion30->SetLineColor(kBlack);
    gRadiusData_Pion30->SetFillColor(kGray+1);
    gRadiusData_Pion30->SetFillStyle(3001);

    int ipoint = 0;
    for(int ibin = 1; ibin < pRadiusData_Pion30->GetNbinsX(); ibin++)
    {
      double content = pRadiusData_Pion30->GetBinContent(ibin);
      double radius = pRadiusData_Pion30->GetXaxis()->GetBinCenter(ibin);

      if(content == 0) continue;

      if(type == 1 && radius > 240) continue;
      if(type == 2 && radius > 350) continue;

      double error_stat = pRadiusData_Pion30->GetBinError(ibin);
      //Error syst
      double error_syst = 0;
      if(type == 1) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 30, "SSF"));
      if(type == 2) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 30, "BL"));

      double radius_err = pRadiusData_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusData_Pion30->SetPoint(ipoint, radius, content);
      gRadiusData_Pion30->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
      ipoint++;
    }

    //MC
    TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusSim_Pion30, *pRadiusSim_Pion30_ErrorLow, *pRadiusSim_Pion30_ErrorHigh, *pRadiusSim_Pion30_Xtalk10, *pRadiusSim_Pion30_Xtalk18;

    if(type == 1)
    {
      f2->GetObject("Pion_profile30_SSF", pRadiusSim_Pion30);
      f2->GetObject("Pion_profile30_err_low_SSF", pRadiusSim_Pion30_ErrorLow);
      f2->GetObject("Pion_profile30_err_high_SSF", pRadiusSim_Pion30_ErrorHigh);
      f2->GetObject("Pion_profile30_xtalk10_SSF", pRadiusSim_Pion30_Xtalk10);
      f2->GetObject("Pion_profile30_xtalk18_SSF", pRadiusSim_Pion30_Xtalk18);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile30_BL", pRadiusSim_Pion30);
      f2->GetObject("Pion_profile30_err_low_BL", pRadiusSim_Pion30_ErrorLow);
      f2->GetObject("Pion_profile30_err_high_BL", pRadiusSim_Pion30_ErrorHigh);
      f2->GetObject("Pion_profile30_xtalk10_BL", pRadiusSim_Pion30_Xtalk10);
      f2->GetObject("Pion_profile30_xtalk18_BL", pRadiusSim_Pion30_Xtalk18);
    }

    //QBBC
    TProfile *pRadiusSim_Pion30_QBBC, *pRadiusSim_Pion30_ErrorLow_QBBC, *pRadiusSim_Pion30_ErrorHigh_QBBC, *pRadiusSim_Pion30_Xtalk10_QBBC, *pRadiusSim_Pion30_Xtalk18_QBBC;

    if(type == 1)
    {
      f2->GetObject("Pion_profile30_SSF_QBBC", pRadiusSim_Pion30_QBBC);
      f2->GetObject("Pion_profile30_err_low_SSF_QBBC", pRadiusSim_Pion30_ErrorLow_QBBC);
      f2->GetObject("Pion_profile30_err_high_SSF_QBBC", pRadiusSim_Pion30_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile30_xtalk10_SSF_QBBC", pRadiusSim_Pion30_Xtalk10_QBBC);
      f2->GetObject("Pion_profile30_xtalk18_SSF_QBBC", pRadiusSim_Pion30_Xtalk18_QBBC);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile30_BL_QBBC", pRadiusSim_Pion30_QBBC);
      f2->GetObject("Pion_profile30_err_low_BL_QBBC", pRadiusSim_Pion30_ErrorLow_QBBC);
      f2->GetObject("Pion_profile30_err_high_BL_QBBC", pRadiusSim_Pion30_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile30_xtalk10_BL_QBBC", pRadiusSim_Pion30_Xtalk10_QBBC);
      f2->GetObject("Pion_profile30_xtalk18_BL_QBBC", pRadiusSim_Pion30_Xtalk18_QBBC);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion30_QGSP_BERT, *pRadiusSim_Pion30_ErrorLow_QGSP_BERT, *pRadiusSim_Pion30_ErrorHigh_QGSP_BERT, *pRadiusSim_Pion30_Xtalk10_QGSP_BERT, *pRadiusSim_Pion30_Xtalk18_QGSP_BERT;

    if(type == 1)
    {
      f2->GetObject("Pion_profile30_SSF_QGSP_BERT", pRadiusSim_Pion30_QGSP_BERT);
      f2->GetObject("Pion_profile30_err_low_SSF_QGSP_BERT", pRadiusSim_Pion30_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile30_err_high_SSF_QGSP_BERT", pRadiusSim_Pion30_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile30_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion30_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile30_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion30_Xtalk18_QGSP_BERT);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile30_BL_QGSP_BERT", pRadiusSim_Pion30_QGSP_BERT);
      f2->GetObject("Pion_profile30_err_low_BL_QGSP_BERT", pRadiusSim_Pion30_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile30_err_high_BL_QGSP_BERT", pRadiusSim_Pion30_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile30_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion30_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile30_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion30_Xtalk18_QGSP_BERT);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion30 = new TGraphAsymmErrors();
    gRadiusSim_Pion30->SetMarkerSize(1);
    gRadiusSim_Pion30->SetMarkerStyle(20);
    gRadiusSim_Pion30->SetMarkerColor(kRed);
    gRadiusSim_Pion30->SetLineColor(kRed);
    gRadiusSim_Pion30->SetFillColor(kRed);
    gRadiusSim_Pion30->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion30->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion30->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion30->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion30_ErrorLow->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion30_ErrorHigh->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion30_Xtalk10->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion30_Xtalk18->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion30->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion30->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion30->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion30_QBBC = new TGraphAsymmErrors();
    gRadiusSim_Pion30_QBBC->SetMarkerSize(1);
    gRadiusSim_Pion30_QBBC->SetMarkerStyle(20);
    gRadiusSim_Pion30_QBBC->SetMarkerColor(kBlue);
    gRadiusSim_Pion30_QBBC->SetLineColor(kBlue);
    gRadiusSim_Pion30_QBBC->SetFillColor(kBlue);
    gRadiusSim_Pion30_QBBC->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion30_QBBC->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion30_QBBC->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion30_QBBC->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion30_ErrorLow_QBBC->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion30_ErrorHigh_QBBC->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion30_Xtalk10_QBBC->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion30_Xtalk18_QBBC->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion30_QBBC->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion30_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion30_QBBC->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion30_QBBC->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion30_QGSP_BERT = new TGraphAsymmErrors();
    gRadiusSim_Pion30_QGSP_BERT->SetMarkerSize(1);
    gRadiusSim_Pion30_QGSP_BERT->SetMarkerStyle(20);
    gRadiusSim_Pion30_QGSP_BERT->SetMarkerColor(kGreen);
    gRadiusSim_Pion30_QGSP_BERT->SetLineColor(kGreen);
    gRadiusSim_Pion30_QGSP_BERT->SetFillColor(kGreen);
    gRadiusSim_Pion30_QGSP_BERT->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion30_QGSP_BERT->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion30_QGSP_BERT->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion30_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion30_ErrorLow_QGSP_BERT->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion30_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion30_Xtalk10_QGSP_BERT->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion30_Xtalk18_QGSP_BERT->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion30_QGSP_BERT->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion30_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion30_QGSP_BERT->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion30_QGSP_BERT->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //DD4hep
    TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange_DD4hep.root");
    TProfile *pRadiusSim_Pion30_DD4hep, *pRadiusSim_Pion30_ErrorLow_DD4hep, *pRadiusSim_Pion30_ErrorHigh_DD4hep, *pRadiusSim_Pion30_Xtalk10_DD4hep, *pRadiusSim_Pion30_Xtalk18_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile30_SSF", pRadiusSim_Pion30_DD4hep);
      f3->GetObject("Pion_profile30_err_low_SSF", pRadiusSim_Pion30_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile30_err_high_SSF", pRadiusSim_Pion30_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile30_xtalk10_SSF", pRadiusSim_Pion30_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile30_xtalk18_SSF", pRadiusSim_Pion30_Xtalk18_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile30_BL", pRadiusSim_Pion30_DD4hep);
      f3->GetObject("Pion_profile30_err_low_BL", pRadiusSim_Pion30_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile30_err_high_BL", pRadiusSim_Pion30_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile30_xtalk10_BL", pRadiusSim_Pion30_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile30_xtalk18_BL", pRadiusSim_Pion30_Xtalk18_DD4hep);
    }

    //QBBC
    TProfile *pRadiusSim_Pion30_QBBC_DD4hep, *pRadiusSim_Pion30_ErrorLow_QBBC_DD4hep, *pRadiusSim_Pion30_ErrorHigh_QBBC_DD4hep, *pRadiusSim_Pion30_Xtalk10_QBBC_DD4hep, *pRadiusSim_Pion30_Xtalk18_QBBC_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile30_SSF_QBBC", pRadiusSim_Pion30_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_err_low_SSF_QBBC", pRadiusSim_Pion30_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_err_high_SSF_QBBC", pRadiusSim_Pion30_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_xtalk10_SSF_QBBC", pRadiusSim_Pion30_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_xtalk18_SSF_QBBC", pRadiusSim_Pion30_Xtalk18_QBBC_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile30_BL_QBBC", pRadiusSim_Pion30_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_err_low_BL_QBBC", pRadiusSim_Pion30_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_err_high_BL_QBBC", pRadiusSim_Pion30_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_xtalk10_BL_QBBC", pRadiusSim_Pion30_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile30_xtalk18_BL_QBBC", pRadiusSim_Pion30_Xtalk18_QBBC_DD4hep);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion30_QGSP_BERT_DD4hep, *pRadiusSim_Pion30_ErrorLow_QGSP_BERT_DD4hep, *pRadiusSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep, *pRadiusSim_Pion30_Xtalk10_QGSP_BERT_DD4hep, *pRadiusSim_Pion30_Xtalk18_QGSP_BERT_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile30_SSF_QGSP_BERT", pRadiusSim_Pion30_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_err_low_SSF_QGSP_BERT", pRadiusSim_Pion30_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_err_high_SSF_QGSP_BERT", pRadiusSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion30_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion30_Xtalk18_QGSP_BERT_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile30_BL_QGSP_BERT", pRadiusSim_Pion30_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_err_low_BL_QGSP_BERT", pRadiusSim_Pion30_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_err_high_BL_QGSP_BERT", pRadiusSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion30_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile30_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion30_Xtalk18_QGSP_BERT_DD4hep);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion30_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion30_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion30_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion30_DD4hep->SetMarkerColor(kRed);
    gRadiusSim_Pion30_DD4hep->SetLineColor(kRed);
    gRadiusSim_Pion30_DD4hep->SetFillColor(kRed);
    gRadiusSim_Pion30_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion30_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion30_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion30_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion30_ErrorLow_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion30_ErrorHigh_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion30_Xtalk10_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion30_Xtalk18_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion30_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion30_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion30_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion30_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion30_QBBC_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion30_QBBC_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion30_QBBC_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion30_QBBC_DD4hep->SetMarkerColor(kBlue);
    gRadiusSim_Pion30_QBBC_DD4hep->SetLineColor(kBlue);
    gRadiusSim_Pion30_QBBC_DD4hep->SetFillColor(kBlue);
    gRadiusSim_Pion30_QBBC_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion30_QBBC_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion30_QBBC_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion30_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion30_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion30_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion30_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion30_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion30_QBBC_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion30_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion30_QBBC_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion30_QBBC_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion30_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
    gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetLineColor(kGreen);
    gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetFillColor(kGreen);
    gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion30_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion30_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion30_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion30_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion30_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion30_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion30_QGSP_BERT_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion30_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion30_QGSP_BERT_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //--------------------------------------------------------

    TLegend *leg2 = new TLegend(0.20, 0.55, 0.40, 0.75);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.025);
    leg2->SetHeader("Mokka");
    leg2->AddEntry(gRadiusData_Pion30, "Data (stat #oplus syst)", "pf");
    leg2->AddEntry(gRadiusSim_Pion30_QGSP_BERT, "QGSP_BERT", "pf");
    leg2->AddEntry(gRadiusSim_Pion30, "QGSP_BERT_HP", "pf");
    leg2->AddEntry(gRadiusSim_Pion30_QBBC, "QBBC", "pf");

    TLegend *leg3 = new TLegend(0.20, 0.35, 0.40, 0.52);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.025);
    leg3->SetHeader("DD4hep");
    leg3->AddEntry(gRadiusSim_Pion30_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
    leg3->AddEntry(gRadiusSim_Pion30_DD4hep, "QGSP_BERT_HP", "pf");
    leg3->AddEntry(gRadiusSim_Pion30_QBBC_DD4hep, "QBBC", "pf");

    TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
    pt2->SetBorderSize(0);
    pt2->SetTextColor(15);
    pt2->SetFillColor(0);
    pt2->SetTextSize(0.04);
    pt2->SetTextAlign(13); //left center
    pt2->AddText("CALICE AHCAL");
    pt2->AddText("Work in progress");
    pt2->AddText("30 GeV #pi^{-} - steel");

    TMultiGraph *multi2 = new TMultiGraph();
    multi2->Add(gRadiusData_Pion30);
    multi2->Add(gRadiusSim_Pion30);
    multi2->Add(gRadiusSim_Pion30_QGSP_BERT);
    multi2->Add(gRadiusSim_Pion30_QBBC);
    multi2->Add(gRadiusSim_Pion30_DD4hep);
    multi2->Add(gRadiusSim_Pion30_QGSP_BERT_DD4hep);
    multi2->Add(gRadiusSim_Pion30_QBBC_DD4hep);

    TCanvas *c2 = new TCanvas("c2", "Timing vs Radius", 800, 600);
    c2->cd();
    multi2->Draw("APX");
    multi2->GetXaxis()->SetTitle("Shower Radius [mm]");
    multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
    multi2->GetYaxis()->SetRangeUser(-1, 12);
    pt2->Draw("SAME");
    leg2->Draw("SAME");
    leg3->Draw("SAME");

    if(type == 1)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 15);
      multi2->GetXaxis()->SetRangeUser(0, 250);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_30GeV_SSF.pdf");
    }
    if(type == 2)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 12);
      multi2->GetXaxis()->SetRangeUser(0, 400);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_30GeV_BL.pdf");
    }
  }
}

void Depth_30GeV()
{
  CaliceStyle();
  //Comparison time vs Depth
  int maxbin = 11;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthData_Pion30;

  f->GetObject("Pion_profile30", pDepthData_Pion30);

  TGraphErrors *gDepthData_Pion30 = new TGraphErrors();
  gDepthData_Pion30->SetMarkerSize(1);
  gDepthData_Pion30->SetMarkerStyle(20);
  gDepthData_Pion30->SetMarkerColor(kBlack);
  gDepthData_Pion30->SetLineColor(kBlack);
  gDepthData_Pion30->SetFillColor(kGray+1);
  gDepthData_Pion30->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion30->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion30->GetBinContent(ibin);
    double Depth = pDepthData_Pion30->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion30->GetBinError(ibin);
    //Error syst
    double error_syst = 1.04;

    double Depth_err = pDepthData_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthData_Pion30->SetPoint(ipoint, Depth, content);
    gDepthData_Pion30->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthSim_Pion30, *pDepthSim_Pion30_ErrorLow, *pDepthSim_Pion30_ErrorHigh, *pDepthSim_Pion30_Xtalk10, *pDepthSim_Pion30_Xtalk18;

  f2->GetObject("Pion_profile30", pDepthSim_Pion30);
  f2->GetObject("Pion_profile30_err_low", pDepthSim_Pion30_ErrorLow);
  f2->GetObject("Pion_profile30_err_high", pDepthSim_Pion30_ErrorHigh);
  f2->GetObject("Pion_profile30_xtalk10", pDepthSim_Pion30_Xtalk10);
  f2->GetObject("Pion_profile30_xtalk18", pDepthSim_Pion30_Xtalk18);

  //QBBC
  TProfile *pDepthSim_Pion30_QBBC, *pDepthSim_Pion30_ErrorLow_QBBC, *pDepthSim_Pion30_ErrorHigh_QBBC, *pDepthSim_Pion30_Xtalk10_QBBC, *pDepthSim_Pion30_Xtalk18_QBBC;

  f2->GetObject("Pion_profile30_QBBC", pDepthSim_Pion30_QBBC);
  f2->GetObject("Pion_profile30_err_low_QBBC", pDepthSim_Pion30_ErrorLow_QBBC);
  f2->GetObject("Pion_profile30_err_high_QBBC", pDepthSim_Pion30_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile30_xtalk10_QBBC", pDepthSim_Pion30_Xtalk10_QBBC);
  f2->GetObject("Pion_profile30_xtalk18_QBBC", pDepthSim_Pion30_Xtalk18_QBBC);

  //QGSP_BERT
  TProfile *pDepthSim_Pion30_QGSP_BERT, *pDepthSim_Pion30_ErrorLow_QGSP_BERT, *pDepthSim_Pion30_ErrorHigh_QGSP_BERT, *pDepthSim_Pion30_Xtalk10_QGSP_BERT, *pDepthSim_Pion30_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile30_QGSP_BERT", pDepthSim_Pion30_QGSP_BERT);
  f2->GetObject("Pion_profile30_err_low_QGSP_BERT", pDepthSim_Pion30_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile30_err_high_QGSP_BERT", pDepthSim_Pion30_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile30_xtalk10_QGSP_BERT", pDepthSim_Pion30_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile30_xtalk18_QGSP_BERT", pDepthSim_Pion30_Xtalk18_QGSP_BERT);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion30 = new TGraphAsymmErrors();
  gDepthSim_Pion30->SetMarkerSize(1);
  gDepthSim_Pion30->SetMarkerStyle(20);
  gDepthSim_Pion30->SetMarkerColor(kRed);
  gDepthSim_Pion30->SetLineColor(kRed);
  gDepthSim_Pion30->SetFillColor(kRed);
  gDepthSim_Pion30->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion30->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion30->GetBinContent(ibin);
    double Depth = pDepthSim_Pion30->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion30_ErrorLow->GetBinContent(ibin);
    double content_up = pDepthSim_Pion30_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion30_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion30_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion30->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion30->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion30->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion30->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion30_QBBC = new TGraphAsymmErrors();
  gDepthSim_Pion30_QBBC->SetMarkerSize(1);
  gDepthSim_Pion30_QBBC->SetMarkerStyle(20);
  gDepthSim_Pion30_QBBC->SetMarkerColor(kBlue);
  gDepthSim_Pion30_QBBC->SetLineColor(kBlue);
  gDepthSim_Pion30_QBBC->SetFillColor(kBlue);
  gDepthSim_Pion30_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion30_QBBC->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion30_QBBC->GetBinContent(ibin);
    double Depth = pDepthSim_Pion30_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion30_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pDepthSim_Pion30_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion30_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion30_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion30_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion30_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion30_QBBC->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion30_QBBC->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion30_QGSP_BERT = new TGraphAsymmErrors();
  gDepthSim_Pion30_QGSP_BERT->SetMarkerSize(1);
  gDepthSim_Pion30_QGSP_BERT->SetMarkerStyle(20);
  gDepthSim_Pion30_QGSP_BERT->SetMarkerColor(kGreen);
  gDepthSim_Pion30_QGSP_BERT->SetLineColor(kGreen);
  gDepthSim_Pion30_QGSP_BERT->SetFillColor(kGreen);
  gDepthSim_Pion30_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion30_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion30_QGSP_BERT->GetBinContent(ibin);
    double Depth = pDepthSim_Pion30_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion30_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pDepthSim_Pion30_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion30_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion30_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion30_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion30_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion30_QGSP_BERT->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion30_QGSP_BERT->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange_DD4hep.root");
  TProfile *pDepthSim_Pion30_DD4hep, *pDepthSim_Pion30_ErrorLow_DD4hep, *pDepthSim_Pion30_ErrorHigh_DD4hep, *pDepthSim_Pion30_Xtalk10_DD4hep, *pDepthSim_Pion30_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile30", pDepthSim_Pion30_DD4hep);
  f3->GetObject("Pion_profile30_err_low", pDepthSim_Pion30_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile30_err_high", pDepthSim_Pion30_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile30_xtalk10", pDepthSim_Pion30_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile30_xtalk18", pDepthSim_Pion30_Xtalk18_DD4hep);

  //QBBC
  TProfile *pDepthSim_Pion30_QBBC_DD4hep, *pDepthSim_Pion30_ErrorLow_QBBC_DD4hep, *pDepthSim_Pion30_ErrorHigh_QBBC_DD4hep, *pDepthSim_Pion30_Xtalk10_QBBC_DD4hep, *pDepthSim_Pion30_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile30_QBBC", pDepthSim_Pion30_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_err_low_QBBC", pDepthSim_Pion30_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_err_high_QBBC", pDepthSim_Pion30_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_xtalk10_QBBC", pDepthSim_Pion30_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile30_xtalk18_QBBC", pDepthSim_Pion30_Xtalk18_QBBC_DD4hep);

  //QGSP_BERT
  TProfile *pDepthSim_Pion30_QGSP_BERT_DD4hep, *pDepthSim_Pion30_ErrorLow_QGSP_BERT_DD4hep, *pDepthSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep, *pDepthSim_Pion30_Xtalk10_QGSP_BERT_DD4hep, *pDepthSim_Pion30_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile30_QGSP_BERT", pDepthSim_Pion30_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_err_low_QGSP_BERT", pDepthSim_Pion30_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_err_high_QGSP_BERT", pDepthSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_xtalk10_QGSP_BERT", pDepthSim_Pion30_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile30_xtalk18_QGSP_BERT", pDepthSim_Pion30_Xtalk18_QGSP_BERT_DD4hep);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion30_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion30_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion30_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion30_DD4hep->SetMarkerColor(kRed);
  gDepthSim_Pion30_DD4hep->SetLineColor(kRed);
  gDepthSim_Pion30_DD4hep->SetFillColor(kRed);
  gDepthSim_Pion30_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion30_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion30_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion30_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion30_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion30_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion30_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion30_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion30_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion30_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion30_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion30_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion30_QBBC_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion30_QBBC_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion30_QBBC_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion30_QBBC_DD4hep->SetMarkerColor(kBlue);
  gDepthSim_Pion30_QBBC_DD4hep->SetLineColor(kBlue);
  gDepthSim_Pion30_QBBC_DD4hep->SetFillColor(kBlue);
  gDepthSim_Pion30_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion30_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion30_QBBC_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion30_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion30_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion30_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion30_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion30_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion30_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion30_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion30_QBBC_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion30_QBBC_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion30_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion30_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion30_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion30_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gDepthSim_Pion30_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gDepthSim_Pion30_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gDepthSim_Pion30_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion30_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion30_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion30_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion30_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion30_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion30_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion30_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion30_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion30_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion30_QGSP_BERT_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion30_QGSP_BERT_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.65, 0.92, 0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gDepthData_Pion30, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gDepthSim_Pion30_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gDepthSim_Pion30, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gDepthSim_Pion30_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.48, 0.92, 0.63);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gDepthSim_Pion30_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gDepthSim_Pion30_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gDepthSim_Pion30_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.70, 0.4, 0.85, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("30 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gDepthData_Pion30);
  multi2->Add(gDepthSim_Pion30);
  multi2->Add(gDepthSim_Pion30_QGSP_BERT);
  multi2->Add(gDepthSim_Pion30_QBBC);
  multi2->Add(gDepthSim_Pion30_DD4hep);
  multi2->Add(gDepthSim_Pion30_QGSP_BERT_DD4hep);
  multi2->Add(gDepthSim_Pion30_QBBC_DD4hep);

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Depth", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Layer Position [mm]");
  multi2->GetXaxis()->SetRangeUser(50, 850);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");
  TGaxis *axis = new TGaxis(48, 10, 851, 10, 0.02, 4.17, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  c2->SaveAs("Plots/ComparisonToSim/Time_Depth_30GeV.pdf");
}

void Energy_50GeV()
{
  CaliceStyle();
  //Comparison time vs energy
  int maxbin = 49;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergyData_Pion50;

  f->GetObject("Pion_profile50", pEnergyData_Pion50);

  TGraphErrors *gEnergyData_Pion50 = new TGraphErrors();
  gEnergyData_Pion50->SetMarkerSize(1);
  gEnergyData_Pion50->SetMarkerStyle(20);
  gEnergyData_Pion50->SetMarkerColor(kBlack);
  gEnergyData_Pion50->SetLineColor(kBlack);
  gEnergyData_Pion50->SetFillColor(kGray+1);
  gEnergyData_Pion50->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion50->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion50->GetBinContent(ibin);
    double energy = pEnergyData_Pion50->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;
    if(energy > 5) continue;

    double error_stat = pEnergyData_Pion50->GetBinError(ibin);
    double energy_err = pEnergyData_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gEnergyData_Pion50->SetPoint(ipoint, energy, content);
    gEnergyData_Pion50->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergySim_Pion50, *pEnergySim_Pion50_ErrorLow, *pEnergySim_Pion50_ErrorHigh, *pEnergySim_Pion50_Xtalk10, *pEnergySim_Pion50_Xtalk18;

  f2->GetObject("Pion_profile50", pEnergySim_Pion50);
  f2->GetObject("Pion_profile50_err_low", pEnergySim_Pion50_ErrorLow);
  f2->GetObject("Pion_profile50_err_high", pEnergySim_Pion50_ErrorHigh);
  f2->GetObject("Pion_profile50_xtalk10", pEnergySim_Pion50_Xtalk10);
  f2->GetObject("Pion_profile50_xtalk18", pEnergySim_Pion50_Xtalk18);

  TProfile *pEnergySim_Pion50_QBBC, *pEnergySim_Pion50_ErrorLow_QBBC, *pEnergySim_Pion50_ErrorHigh_QBBC, *pEnergySim_Pion50_Xtalk10_QBBC, *pEnergySim_Pion50_Xtalk18_QBBC;

  f2->GetObject("Pion_profile50_QBBC", pEnergySim_Pion50_QBBC);
  f2->GetObject("Pion_profile50_err_low_QBBC", pEnergySim_Pion50_ErrorLow_QBBC);
  f2->GetObject("Pion_profile50_err_high_QBBC", pEnergySim_Pion50_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile50_xtalk10_QBBC", pEnergySim_Pion50_Xtalk10_QBBC);
  f2->GetObject("Pion_profile50_xtalk18_QBBC", pEnergySim_Pion50_Xtalk18_QBBC);

  TProfile *pEnergySim_Pion50_QGSP_BERT, *pEnergySim_Pion50_ErrorLow_QGSP_BERT, *pEnergySim_Pion50_ErrorHigh_QGSP_BERT, *pEnergySim_Pion50_Xtalk10_QGSP_BERT, *pEnergySim_Pion50_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile50_QGSP_BERT", pEnergySim_Pion50_QGSP_BERT);
  f2->GetObject("Pion_profile50_err_low_QGSP_BERT", pEnergySim_Pion50_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile50_err_high_QGSP_BERT", pEnergySim_Pion50_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile50_xtalk10_QGSP_BERT", pEnergySim_Pion50_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile50_xtalk18_QGSP_BERT", pEnergySim_Pion50_Xtalk18_QGSP_BERT);

  TGraphAsymmErrors *gEnergySim_Pion50 = new TGraphAsymmErrors();
  gEnergySim_Pion50->SetMarkerSize(1);
  gEnergySim_Pion50->SetMarkerStyle(20);
  gEnergySim_Pion50->SetMarkerColor(kRed);
  gEnergySim_Pion50->SetLineColor(kRed);
  gEnergySim_Pion50->SetFillColor(kRed);
  gEnergySim_Pion50->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion50->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion50->GetBinContent(ibin);
    double energy = pEnergySim_Pion50->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion50_ErrorLow->GetBinContent(ibin);
    double content_up = pEnergySim_Pion50_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion50_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion50_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion50->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion50->SetPoint(ipoint, energy, content);
    gEnergySim_Pion50->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion50_QBBC = new TGraphAsymmErrors();
  gEnergySim_Pion50_QBBC->SetMarkerSize(1);
  gEnergySim_Pion50_QBBC->SetMarkerStyle(20);
  gEnergySim_Pion50_QBBC->SetMarkerColor(kBlue);
  gEnergySim_Pion50_QBBC->SetLineColor(kBlue);
  gEnergySim_Pion50_QBBC->SetFillColor(kBlue);
  gEnergySim_Pion50_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion50_QBBC->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion50_QBBC->GetBinContent(ibin);
    double energy = pEnergySim_Pion50_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion50_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pEnergySim_Pion50_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion50_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion50_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion50_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion50_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion50_QBBC->SetPoint(ipoint, energy, content);
    gEnergySim_Pion50_QBBC->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion50_QGSP_BERT = new TGraphAsymmErrors();
  gEnergySim_Pion50_QGSP_BERT->SetMarkerSize(1);
  gEnergySim_Pion50_QGSP_BERT->SetMarkerStyle(20);
  gEnergySim_Pion50_QGSP_BERT->SetMarkerColor(kGreen);
  gEnergySim_Pion50_QGSP_BERT->SetLineColor(kGreen);
  gEnergySim_Pion50_QGSP_BERT->SetFillColor(kGreen);
  gEnergySim_Pion50_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion50_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion50_QGSP_BERT->GetBinContent(ibin);
    double energy = pEnergySim_Pion50_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion50_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pEnergySim_Pion50_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion50_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion50_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion50_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion50_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion50_QGSP_BERT->SetPoint(ipoint, energy, content);
    gEnergySim_Pion50_QGSP_BERT->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange_DD4hep.root");
  TProfile *pEnergySim_Pion50_DD4hep, *pEnergySim_Pion50_ErrorLow_DD4hep, *pEnergySim_Pion50_ErrorHigh_DD4hep, *pEnergySim_Pion50_Xtalk10_DD4hep, *pEnergySim_Pion50_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile50", pEnergySim_Pion50_DD4hep);
  f3->GetObject("Pion_profile50_err_low", pEnergySim_Pion50_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile50_err_high", pEnergySim_Pion50_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile50_xtalk10", pEnergySim_Pion50_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile50_xtalk18", pEnergySim_Pion50_Xtalk18_DD4hep);

  TProfile *pEnergySim_Pion50_QBBC_DD4hep, *pEnergySim_Pion50_ErrorLow_QBBC_DD4hep, *pEnergySim_Pion50_ErrorHigh_QBBC_DD4hep, *pEnergySim_Pion50_Xtalk10_QBBC_DD4hep, *pEnergySim_Pion50_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile50_QBBC", pEnergySim_Pion50_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_err_low_QBBC", pEnergySim_Pion50_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_err_high_QBBC", pEnergySim_Pion50_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_xtalk10_QBBC", pEnergySim_Pion50_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_xtalk18_QBBC", pEnergySim_Pion50_Xtalk18_QBBC_DD4hep);

  TProfile *pEnergySim_Pion50_QGSP_BERT_DD4hep, *pEnergySim_Pion50_ErrorLow_QGSP_BERT_DD4hep, *pEnergySim_Pion50_ErrorHigh_QGSP_BERT_DD4hep, *pEnergySim_Pion50_Xtalk10_QGSP_BERT_DD4hep, *pEnergySim_Pion50_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile50_QGSP_BERT", pEnergySim_Pion50_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_err_low_QGSP_BERT", pEnergySim_Pion50_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_err_high_QGSP_BERT", pEnergySim_Pion50_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_xtalk10_QGSP_BERT", pEnergySim_Pion50_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_xtalk18_QGSP_BERT", pEnergySim_Pion50_Xtalk18_QGSP_BERT_DD4hep);

  TGraphAsymmErrors *gEnergySim_Pion50_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion50_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion50_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion50_DD4hep->SetMarkerColor(kRed);
  gEnergySim_Pion50_DD4hep->SetLineColor(kRed);
  gEnergySim_Pion50_DD4hep->SetFillColor(kRed);
  gEnergySim_Pion50_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion50_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion50_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion50_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion50_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion50_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion50_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion50_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion50_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion50_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion50_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion50_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion50_QBBC_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion50_QBBC_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion50_QBBC_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion50_QBBC_DD4hep->SetMarkerColor(kBlue);
  gEnergySim_Pion50_QBBC_DD4hep->SetLineColor(kBlue);
  gEnergySim_Pion50_QBBC_DD4hep->SetFillColor(kBlue);
  gEnergySim_Pion50_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion50_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion50_QBBC_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion50_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion50_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion50_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion50_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion50_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion50_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion50_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion50_QBBC_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion50_QBBC_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion50_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion50_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion50_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion50_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gEnergySim_Pion50_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gEnergySim_Pion50_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gEnergySim_Pion50_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion50_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion50_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion50_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion50_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion50_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion50_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion50_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion50_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion50_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion50_QGSP_BERT_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion50_QGSP_BERT_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gEnergyData_Pion50, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gEnergySim_Pion50_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gEnergySim_Pion50, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gEnergySim_Pion50_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gEnergySim_Pion50_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gEnergySim_Pion50_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gEnergySim_Pion50_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("50 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Pion50);
  multi2->Add(gEnergySim_Pion50);
  multi2->Add(gEnergySim_Pion50_QGSP_BERT);
  multi2->Add(gEnergySim_Pion50_QBBC);
  multi2->Add(gEnergySim_Pion50_DD4hep);
  multi2->Add(gEnergySim_Pion50_QGSP_BERT_DD4hep);
  multi2->Add(gEnergySim_Pion50_QBBC_DD4hep);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Energy", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Deposition [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Energy_50GeV.pdf");
}

void Radius_50GeV()
{
  CaliceStyle();
  //Comparison time vs Radius

  for(int type = 1; type < 3; type++)
  {
    //Data
    TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusData_Pion50;

    if(type == 1)
    f->GetObject("Pion_profile50_SSF", pRadiusData_Pion50);
    if(type == 2)
    f->GetObject("Pion_profile50_BL", pRadiusData_Pion50);

    TGraphErrors *gRadiusData_Pion50 = new TGraphErrors();
    gRadiusData_Pion50->SetMarkerSize(1);
    gRadiusData_Pion50->SetMarkerStyle(20);
    gRadiusData_Pion50->SetMarkerColor(kBlack);
    gRadiusData_Pion50->SetLineColor(kBlack);
    gRadiusData_Pion50->SetFillColor(kGray+1);
    gRadiusData_Pion50->SetFillStyle(3001);

    int ipoint = 0;
    for(int ibin = 1; ibin < pRadiusData_Pion50->GetNbinsX(); ibin++)
    {
      double content = pRadiusData_Pion50->GetBinContent(ibin);
      double radius = pRadiusData_Pion50->GetXaxis()->GetBinCenter(ibin);

      if(content == 0) continue;

      if(type == 1 && radius > 240) continue;
      if(type == 2 && radius > 350) continue;

      double error_stat = pRadiusData_Pion50->GetBinError(ibin);
      //Error syst
      double error_syst = 0;
      if(type == 1) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "SSF"));
      if(type == 2) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 50, "BL"));

      double radius_err = pRadiusData_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusData_Pion50->SetPoint(ipoint, radius, content);
      gRadiusData_Pion50->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
      ipoint++;
    }

    //MC
    TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusSim_Pion50, *pRadiusSim_Pion50_ErrorLow, *pRadiusSim_Pion50_ErrorHigh, *pRadiusSim_Pion50_Xtalk10, *pRadiusSim_Pion50_Xtalk18;

    if(type == 1)
    {
      f2->GetObject("Pion_profile50_SSF", pRadiusSim_Pion50);
      f2->GetObject("Pion_profile50_err_low_SSF", pRadiusSim_Pion50_ErrorLow);
      f2->GetObject("Pion_profile50_err_high_SSF", pRadiusSim_Pion50_ErrorHigh);
      f2->GetObject("Pion_profile50_xtalk10_SSF", pRadiusSim_Pion50_Xtalk10);
      f2->GetObject("Pion_profile50_xtalk18_SSF", pRadiusSim_Pion50_Xtalk18);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile50_BL", pRadiusSim_Pion50);
      f2->GetObject("Pion_profile50_err_low_BL", pRadiusSim_Pion50_ErrorLow);
      f2->GetObject("Pion_profile50_err_high_BL", pRadiusSim_Pion50_ErrorHigh);
      f2->GetObject("Pion_profile50_xtalk10_BL", pRadiusSim_Pion50_Xtalk10);
      f2->GetObject("Pion_profile50_xtalk18_BL", pRadiusSim_Pion50_Xtalk18);
    }

    //QBBC
    TProfile *pRadiusSim_Pion50_QBBC, *pRadiusSim_Pion50_ErrorLow_QBBC, *pRadiusSim_Pion50_ErrorHigh_QBBC, *pRadiusSim_Pion50_Xtalk10_QBBC, *pRadiusSim_Pion50_Xtalk18_QBBC;

    if(type == 1)
    {
      f2->GetObject("Pion_profile50_SSF_QBBC", pRadiusSim_Pion50_QBBC);
      f2->GetObject("Pion_profile50_err_low_SSF_QBBC", pRadiusSim_Pion50_ErrorLow_QBBC);
      f2->GetObject("Pion_profile50_err_high_SSF_QBBC", pRadiusSim_Pion50_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile50_xtalk10_SSF_QBBC", pRadiusSim_Pion50_Xtalk10_QBBC);
      f2->GetObject("Pion_profile50_xtalk18_SSF_QBBC", pRadiusSim_Pion50_Xtalk18_QBBC);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile50_BL_QBBC", pRadiusSim_Pion50_QBBC);
      f2->GetObject("Pion_profile50_err_low_BL_QBBC", pRadiusSim_Pion50_ErrorLow_QBBC);
      f2->GetObject("Pion_profile50_err_high_BL_QBBC", pRadiusSim_Pion50_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile50_xtalk10_BL_QBBC", pRadiusSim_Pion50_Xtalk10_QBBC);
      f2->GetObject("Pion_profile50_xtalk18_BL_QBBC", pRadiusSim_Pion50_Xtalk18_QBBC);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion50_QGSP_BERT, *pRadiusSim_Pion50_ErrorLow_QGSP_BERT, *pRadiusSim_Pion50_ErrorHigh_QGSP_BERT, *pRadiusSim_Pion50_Xtalk10_QGSP_BERT, *pRadiusSim_Pion50_Xtalk18_QGSP_BERT;

    if(type == 1)
    {
      f2->GetObject("Pion_profile50_SSF_QGSP_BERT", pRadiusSim_Pion50_QGSP_BERT);
      f2->GetObject("Pion_profile50_err_low_SSF_QGSP_BERT", pRadiusSim_Pion50_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile50_err_high_SSF_QGSP_BERT", pRadiusSim_Pion50_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile50_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion50_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile50_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion50_Xtalk18_QGSP_BERT);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile50_BL_QGSP_BERT", pRadiusSim_Pion50_QGSP_BERT);
      f2->GetObject("Pion_profile50_err_low_BL_QGSP_BERT", pRadiusSim_Pion50_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile50_err_high_BL_QGSP_BERT", pRadiusSim_Pion50_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile50_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion50_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile50_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion50_Xtalk18_QGSP_BERT);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion50 = new TGraphAsymmErrors();
    gRadiusSim_Pion50->SetMarkerSize(1);
    gRadiusSim_Pion50->SetMarkerStyle(20);
    gRadiusSim_Pion50->SetMarkerColor(kRed);
    gRadiusSim_Pion50->SetLineColor(kRed);
    gRadiusSim_Pion50->SetFillColor(kRed);
    gRadiusSim_Pion50->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion50->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion50->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion50->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion50_ErrorLow->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion50_ErrorHigh->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion50_Xtalk10->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion50_Xtalk18->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion50->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion50->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion50->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion50_QBBC = new TGraphAsymmErrors();
    gRadiusSim_Pion50_QBBC->SetMarkerSize(1);
    gRadiusSim_Pion50_QBBC->SetMarkerStyle(20);
    gRadiusSim_Pion50_QBBC->SetMarkerColor(kBlue);
    gRadiusSim_Pion50_QBBC->SetLineColor(kBlue);
    gRadiusSim_Pion50_QBBC->SetFillColor(kBlue);
    gRadiusSim_Pion50_QBBC->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion50_QBBC->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion50_QBBC->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion50_QBBC->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion50_ErrorLow_QBBC->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion50_ErrorHigh_QBBC->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion50_Xtalk10_QBBC->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion50_Xtalk18_QBBC->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion50_QBBC->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion50_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion50_QBBC->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion50_QBBC->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion50_QGSP_BERT = new TGraphAsymmErrors();
    gRadiusSim_Pion50_QGSP_BERT->SetMarkerSize(1);
    gRadiusSim_Pion50_QGSP_BERT->SetMarkerStyle(20);
    gRadiusSim_Pion50_QGSP_BERT->SetMarkerColor(kGreen);
    gRadiusSim_Pion50_QGSP_BERT->SetLineColor(kGreen);
    gRadiusSim_Pion50_QGSP_BERT->SetFillColor(kGreen);
    gRadiusSim_Pion50_QGSP_BERT->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion50_QGSP_BERT->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion50_QGSP_BERT->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion50_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion50_ErrorLow_QGSP_BERT->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion50_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion50_Xtalk10_QGSP_BERT->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion50_Xtalk18_QGSP_BERT->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion50_QGSP_BERT->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion50_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion50_QGSP_BERT->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion50_QGSP_BERT->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //DD4hep
    TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange_DD4hep.root");
    TProfile *pRadiusSim_Pion50_DD4hep, *pRadiusSim_Pion50_ErrorLow_DD4hep, *pRadiusSim_Pion50_ErrorHigh_DD4hep, *pRadiusSim_Pion50_Xtalk10_DD4hep, *pRadiusSim_Pion50_Xtalk18_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile50_SSF", pRadiusSim_Pion50_DD4hep);
      f3->GetObject("Pion_profile50_err_low_SSF", pRadiusSim_Pion50_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile50_err_high_SSF", pRadiusSim_Pion50_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile50_xtalk10_SSF", pRadiusSim_Pion50_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile50_xtalk18_SSF", pRadiusSim_Pion50_Xtalk18_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile50_BL", pRadiusSim_Pion50_DD4hep);
      f3->GetObject("Pion_profile50_err_low_BL", pRadiusSim_Pion50_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile50_err_high_BL", pRadiusSim_Pion50_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile50_xtalk10_BL", pRadiusSim_Pion50_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile50_xtalk18_BL", pRadiusSim_Pion50_Xtalk18_DD4hep);
    }

    //QBBC
    TProfile *pRadiusSim_Pion50_QBBC_DD4hep, *pRadiusSim_Pion50_ErrorLow_QBBC_DD4hep, *pRadiusSim_Pion50_ErrorHigh_QBBC_DD4hep, *pRadiusSim_Pion50_Xtalk10_QBBC_DD4hep, *pRadiusSim_Pion50_Xtalk18_QBBC_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile50_SSF_QBBC", pRadiusSim_Pion50_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_err_low_SSF_QBBC", pRadiusSim_Pion50_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_err_high_SSF_QBBC", pRadiusSim_Pion50_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_xtalk10_SSF_QBBC", pRadiusSim_Pion50_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_xtalk18_SSF_QBBC", pRadiusSim_Pion50_Xtalk18_QBBC_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile50_BL_QBBC", pRadiusSim_Pion50_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_err_low_BL_QBBC", pRadiusSim_Pion50_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_err_high_BL_QBBC", pRadiusSim_Pion50_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_xtalk10_BL_QBBC", pRadiusSim_Pion50_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile50_xtalk18_BL_QBBC", pRadiusSim_Pion50_Xtalk18_QBBC_DD4hep);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion50_QGSP_BERT_DD4hep, *pRadiusSim_Pion50_ErrorLow_QGSP_BERT_DD4hep, *pRadiusSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep, *pRadiusSim_Pion50_Xtalk10_QGSP_BERT_DD4hep, *pRadiusSim_Pion50_Xtalk18_QGSP_BERT_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile50_SSF_QGSP_BERT", pRadiusSim_Pion50_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_err_low_SSF_QGSP_BERT", pRadiusSim_Pion50_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_err_high_SSF_QGSP_BERT", pRadiusSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion50_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion50_Xtalk18_QGSP_BERT_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile50_BL_QGSP_BERT", pRadiusSim_Pion50_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_err_low_BL_QGSP_BERT", pRadiusSim_Pion50_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_err_high_BL_QGSP_BERT", pRadiusSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion50_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile50_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion50_Xtalk18_QGSP_BERT_DD4hep);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion50_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion50_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion50_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion50_DD4hep->SetMarkerColor(kRed);
    gRadiusSim_Pion50_DD4hep->SetLineColor(kRed);
    gRadiusSim_Pion50_DD4hep->SetFillColor(kRed);
    gRadiusSim_Pion50_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion50_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion50_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion50_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion50_ErrorLow_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion50_ErrorHigh_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion50_Xtalk10_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion50_Xtalk18_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion50_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion50_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion50_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion50_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion50_QBBC_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion50_QBBC_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion50_QBBC_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion50_QBBC_DD4hep->SetMarkerColor(kBlue);
    gRadiusSim_Pion50_QBBC_DD4hep->SetLineColor(kBlue);
    gRadiusSim_Pion50_QBBC_DD4hep->SetFillColor(kBlue);
    gRadiusSim_Pion50_QBBC_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion50_QBBC_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion50_QBBC_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion50_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion50_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion50_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion50_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion50_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion50_QBBC_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion50_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion50_QBBC_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion50_QBBC_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion50_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
    gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetLineColor(kGreen);
    gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetFillColor(kGreen);
    gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion50_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion50_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion50_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion50_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion50_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion50_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion50_QGSP_BERT_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion50_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion50_QGSP_BERT_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //--------------------------------------------------------

    TLegend *leg2 = new TLegend(0.20, 0.55, 0.40, 0.75);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.025);
    leg2->SetHeader("Mokka");
    leg2->AddEntry(gRadiusData_Pion50, "Data (stat #oplus syst)", "pf");
    leg2->AddEntry(gRadiusSim_Pion50_QGSP_BERT, "QGSP_BERT", "pf");
    leg2->AddEntry(gRadiusSim_Pion50, "QGSP_BERT_HP", "pf");
    leg2->AddEntry(gRadiusSim_Pion50_QBBC, "QBBC", "pf");

    TLegend *leg3 = new TLegend(0.20, 0.35, 0.40, 0.52);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.025);
    leg3->SetHeader("DD4hep");
    leg3->AddEntry(gRadiusSim_Pion50_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
    leg3->AddEntry(gRadiusSim_Pion50_DD4hep, "QGSP_BERT_HP", "pf");
    leg3->AddEntry(gRadiusSim_Pion50_QBBC_DD4hep, "QBBC", "pf");

    TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
    pt2->SetBorderSize(0);
    pt2->SetTextColor(15);
    pt2->SetFillColor(0);
    pt2->SetTextSize(0.04);
    pt2->SetTextAlign(13); //left center
    pt2->AddText("CALICE AHCAL");
    pt2->AddText("Work in progress");
    pt2->AddText("50 GeV #pi^{-} - steel");

    TMultiGraph *multi2 = new TMultiGraph();
    multi2->Add(gRadiusData_Pion50);
    multi2->Add(gRadiusSim_Pion50);
    multi2->Add(gRadiusSim_Pion50_QGSP_BERT);
    multi2->Add(gRadiusSim_Pion50_QBBC);
    multi2->Add(gRadiusSim_Pion50_DD4hep);
    multi2->Add(gRadiusSim_Pion50_QGSP_BERT_DD4hep);
    multi2->Add(gRadiusSim_Pion50_QBBC_DD4hep);

    TCanvas *c2 = new TCanvas("c2", "Timing vs Radius", 800, 600);
    c2->cd();
    multi2->Draw("APX");
    multi2->GetXaxis()->SetTitle("Shower Radius [mm]");
    multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
    multi2->GetYaxis()->SetRangeUser(-1, 12);
    pt2->Draw("SAME");
    leg2->Draw("SAME");
    leg3->Draw("SAME");

    if(type == 1)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 15);
      multi2->GetXaxis()->SetRangeUser(0, 250);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_50GeV_SSF.pdf");
    }
    if(type == 2)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 12);
      multi2->GetXaxis()->SetRangeUser(0, 400);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_50GeV_BL.pdf");
    }
  }
}

void Depth_50GeV()
{
  CaliceStyle();
  //Comparison time vs Depth
  int maxbin = 11;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthData_Pion50;

  f->GetObject("Pion_profile50", pDepthData_Pion50);

  TGraphErrors *gDepthData_Pion50 = new TGraphErrors();
  gDepthData_Pion50->SetMarkerSize(1);
  gDepthData_Pion50->SetMarkerStyle(20);
  gDepthData_Pion50->SetMarkerColor(kBlack);
  gDepthData_Pion50->SetLineColor(kBlack);
  gDepthData_Pion50->SetFillColor(kGray+1);
  gDepthData_Pion50->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion50->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion50->GetBinContent(ibin);
    double Depth = pDepthData_Pion50->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion50->GetBinError(ibin);
    //Error syst
    double error_syst = 1.04;

    double Depth_err = pDepthData_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthData_Pion50->SetPoint(ipoint, Depth, content);
    gDepthData_Pion50->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthSim_Pion50, *pDepthSim_Pion50_ErrorLow, *pDepthSim_Pion50_ErrorHigh, *pDepthSim_Pion50_Xtalk10, *pDepthSim_Pion50_Xtalk18;

  f2->GetObject("Pion_profile50", pDepthSim_Pion50);
  f2->GetObject("Pion_profile50_err_low", pDepthSim_Pion50_ErrorLow);
  f2->GetObject("Pion_profile50_err_high", pDepthSim_Pion50_ErrorHigh);
  f2->GetObject("Pion_profile50_xtalk10", pDepthSim_Pion50_Xtalk10);
  f2->GetObject("Pion_profile50_xtalk18", pDepthSim_Pion50_Xtalk18);

  //QBBC
  TProfile *pDepthSim_Pion50_QBBC, *pDepthSim_Pion50_ErrorLow_QBBC, *pDepthSim_Pion50_ErrorHigh_QBBC, *pDepthSim_Pion50_Xtalk10_QBBC, *pDepthSim_Pion50_Xtalk18_QBBC;

  f2->GetObject("Pion_profile50_QBBC", pDepthSim_Pion50_QBBC);
  f2->GetObject("Pion_profile50_err_low_QBBC", pDepthSim_Pion50_ErrorLow_QBBC);
  f2->GetObject("Pion_profile50_err_high_QBBC", pDepthSim_Pion50_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile50_xtalk10_QBBC", pDepthSim_Pion50_Xtalk10_QBBC);
  f2->GetObject("Pion_profile50_xtalk18_QBBC", pDepthSim_Pion50_Xtalk18_QBBC);

  //QGSP_BERT
  TProfile *pDepthSim_Pion50_QGSP_BERT, *pDepthSim_Pion50_ErrorLow_QGSP_BERT, *pDepthSim_Pion50_ErrorHigh_QGSP_BERT, *pDepthSim_Pion50_Xtalk10_QGSP_BERT, *pDepthSim_Pion50_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile50_QGSP_BERT", pDepthSim_Pion50_QGSP_BERT);
  f2->GetObject("Pion_profile50_err_low_QGSP_BERT", pDepthSim_Pion50_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile50_err_high_QGSP_BERT", pDepthSim_Pion50_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile50_xtalk10_QGSP_BERT", pDepthSim_Pion50_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile50_xtalk18_QGSP_BERT", pDepthSim_Pion50_Xtalk18_QGSP_BERT);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion50 = new TGraphAsymmErrors();
  gDepthSim_Pion50->SetMarkerSize(1);
  gDepthSim_Pion50->SetMarkerStyle(20);
  gDepthSim_Pion50->SetMarkerColor(kRed);
  gDepthSim_Pion50->SetLineColor(kRed);
  gDepthSim_Pion50->SetFillColor(kRed);
  gDepthSim_Pion50->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion50->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion50->GetBinContent(ibin);
    double Depth = pDepthSim_Pion50->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion50_ErrorLow->GetBinContent(ibin);
    double content_up = pDepthSim_Pion50_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion50_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion50_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion50->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion50->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion50->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion50->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion50_QBBC = new TGraphAsymmErrors();
  gDepthSim_Pion50_QBBC->SetMarkerSize(1);
  gDepthSim_Pion50_QBBC->SetMarkerStyle(20);
  gDepthSim_Pion50_QBBC->SetMarkerColor(kBlue);
  gDepthSim_Pion50_QBBC->SetLineColor(kBlue);
  gDepthSim_Pion50_QBBC->SetFillColor(kBlue);
  gDepthSim_Pion50_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion50_QBBC->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion50_QBBC->GetBinContent(ibin);
    double Depth = pDepthSim_Pion50_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion50_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pDepthSim_Pion50_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion50_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion50_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion50_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion50_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion50_QBBC->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion50_QBBC->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion50_QGSP_BERT = new TGraphAsymmErrors();
  gDepthSim_Pion50_QGSP_BERT->SetMarkerSize(1);
  gDepthSim_Pion50_QGSP_BERT->SetMarkerStyle(20);
  gDepthSim_Pion50_QGSP_BERT->SetMarkerColor(kGreen);
  gDepthSim_Pion50_QGSP_BERT->SetLineColor(kGreen);
  gDepthSim_Pion50_QGSP_BERT->SetFillColor(kGreen);
  gDepthSim_Pion50_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion50_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion50_QGSP_BERT->GetBinContent(ibin);
    double Depth = pDepthSim_Pion50_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion50_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pDepthSim_Pion50_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion50_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion50_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion50_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion50_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion50_QGSP_BERT->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion50_QGSP_BERT->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange_DD4hep.root");
  TProfile *pDepthSim_Pion50_DD4hep, *pDepthSim_Pion50_ErrorLow_DD4hep, *pDepthSim_Pion50_ErrorHigh_DD4hep, *pDepthSim_Pion50_Xtalk10_DD4hep, *pDepthSim_Pion50_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile50", pDepthSim_Pion50_DD4hep);
  f3->GetObject("Pion_profile50_err_low", pDepthSim_Pion50_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile50_err_high", pDepthSim_Pion50_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile50_xtalk10", pDepthSim_Pion50_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile50_xtalk18", pDepthSim_Pion50_Xtalk18_DD4hep);

  //QBBC
  TProfile *pDepthSim_Pion50_QBBC_DD4hep, *pDepthSim_Pion50_ErrorLow_QBBC_DD4hep, *pDepthSim_Pion50_ErrorHigh_QBBC_DD4hep, *pDepthSim_Pion50_Xtalk10_QBBC_DD4hep, *pDepthSim_Pion50_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile50_QBBC", pDepthSim_Pion50_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_err_low_QBBC", pDepthSim_Pion50_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_err_high_QBBC", pDepthSim_Pion50_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_xtalk10_QBBC", pDepthSim_Pion50_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile50_xtalk18_QBBC", pDepthSim_Pion50_Xtalk18_QBBC_DD4hep);

  //QGSP_BERT
  TProfile *pDepthSim_Pion50_QGSP_BERT_DD4hep, *pDepthSim_Pion50_ErrorLow_QGSP_BERT_DD4hep, *pDepthSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep, *pDepthSim_Pion50_Xtalk10_QGSP_BERT_DD4hep, *pDepthSim_Pion50_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile50_QGSP_BERT", pDepthSim_Pion50_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_err_low_QGSP_BERT", pDepthSim_Pion50_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_err_high_QGSP_BERT", pDepthSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_xtalk10_QGSP_BERT", pDepthSim_Pion50_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile50_xtalk18_QGSP_BERT", pDepthSim_Pion50_Xtalk18_QGSP_BERT_DD4hep);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion50_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion50_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion50_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion50_DD4hep->SetMarkerColor(kRed);
  gDepthSim_Pion50_DD4hep->SetLineColor(kRed);
  gDepthSim_Pion50_DD4hep->SetFillColor(kRed);
  gDepthSim_Pion50_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion50_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion50_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion50_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion50_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion50_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion50_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion50_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion50_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion50_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion50_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion50_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion50_QBBC_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion50_QBBC_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion50_QBBC_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion50_QBBC_DD4hep->SetMarkerColor(kBlue);
  gDepthSim_Pion50_QBBC_DD4hep->SetLineColor(kBlue);
  gDepthSim_Pion50_QBBC_DD4hep->SetFillColor(kBlue);
  gDepthSim_Pion50_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion50_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion50_QBBC_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion50_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion50_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion50_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion50_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion50_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion50_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion50_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion50_QBBC_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion50_QBBC_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion50_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion50_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion50_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion50_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gDepthSim_Pion50_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gDepthSim_Pion50_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gDepthSim_Pion50_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion50_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion50_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion50_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion50_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion50_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion50_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion50_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion50_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion50_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion50_QGSP_BERT_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion50_QGSP_BERT_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.65, 0.92, 0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gDepthData_Pion50, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gDepthSim_Pion50_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gDepthSim_Pion50, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gDepthSim_Pion50_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.48, 0.92, 0.63);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gDepthSim_Pion50_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gDepthSim_Pion50_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gDepthSim_Pion50_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.70, 0.4, 0.85, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("50 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gDepthData_Pion50);
  multi2->Add(gDepthSim_Pion50);
  multi2->Add(gDepthSim_Pion50_QGSP_BERT);
  multi2->Add(gDepthSim_Pion50_QBBC);
  multi2->Add(gDepthSim_Pion50_DD4hep);
  multi2->Add(gDepthSim_Pion50_QGSP_BERT_DD4hep);
  multi2->Add(gDepthSim_Pion50_QBBC_DD4hep);

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Depth", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Layer Position [mm]");
  multi2->GetXaxis()->SetRangeUser(50, 850);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");
  TGaxis *axis = new TGaxis(48, 10, 851, 10, 0.02, 4.17, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  c2->SaveAs("Plots/ComparisonToSim/Time_Depth_50GeV.pdf");
}

void Energy_70GeV()
{
  CaliceStyle();
  //Comparison time vs energy
  int maxbin = 49;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergyData_Pion70;

  f->GetObject("Pion_profile70", pEnergyData_Pion70);

  TGraphErrors *gEnergyData_Pion70 = new TGraphErrors();
  gEnergyData_Pion70->SetMarkerSize(1);
  gEnergyData_Pion70->SetMarkerStyle(20);
  gEnergyData_Pion70->SetMarkerColor(kBlack);
  gEnergyData_Pion70->SetLineColor(kBlack);
  gEnergyData_Pion70->SetFillColor(kGray+1);
  gEnergyData_Pion70->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion70->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion70->GetBinContent(ibin);
    double energy = pEnergyData_Pion70->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;
    if(energy > 5) continue;

    double error_stat = pEnergyData_Pion70->GetBinError(ibin);
    double energy_err = pEnergyData_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gEnergyData_Pion70->SetPoint(ipoint, energy, content);
    gEnergyData_Pion70->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergySim_Pion70, *pEnergySim_Pion70_ErrorLow, *pEnergySim_Pion70_ErrorHigh, *pEnergySim_Pion70_Xtalk10, *pEnergySim_Pion70_Xtalk18;

  f2->GetObject("Pion_profile70", pEnergySim_Pion70);
  f2->GetObject("Pion_profile70_err_low", pEnergySim_Pion70_ErrorLow);
  f2->GetObject("Pion_profile70_err_high", pEnergySim_Pion70_ErrorHigh);
  f2->GetObject("Pion_profile70_xtalk10", pEnergySim_Pion70_Xtalk10);
  f2->GetObject("Pion_profile70_xtalk18", pEnergySim_Pion70_Xtalk18);

  TProfile *pEnergySim_Pion70_QBBC, *pEnergySim_Pion70_ErrorLow_QBBC, *pEnergySim_Pion70_ErrorHigh_QBBC, *pEnergySim_Pion70_Xtalk10_QBBC, *pEnergySim_Pion70_Xtalk18_QBBC;

  f2->GetObject("Pion_profile70_QBBC", pEnergySim_Pion70_QBBC);
  f2->GetObject("Pion_profile70_err_low_QBBC", pEnergySim_Pion70_ErrorLow_QBBC);
  f2->GetObject("Pion_profile70_err_high_QBBC", pEnergySim_Pion70_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile70_xtalk10_QBBC", pEnergySim_Pion70_Xtalk10_QBBC);
  f2->GetObject("Pion_profile70_xtalk18_QBBC", pEnergySim_Pion70_Xtalk18_QBBC);

  TProfile *pEnergySim_Pion70_QGSP_BERT, *pEnergySim_Pion70_ErrorLow_QGSP_BERT, *pEnergySim_Pion70_ErrorHigh_QGSP_BERT, *pEnergySim_Pion70_Xtalk10_QGSP_BERT, *pEnergySim_Pion70_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile70_QGSP_BERT", pEnergySim_Pion70_QGSP_BERT);
  f2->GetObject("Pion_profile70_err_low_QGSP_BERT", pEnergySim_Pion70_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile70_err_high_QGSP_BERT", pEnergySim_Pion70_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile70_xtalk10_QGSP_BERT", pEnergySim_Pion70_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile70_xtalk18_QGSP_BERT", pEnergySim_Pion70_Xtalk18_QGSP_BERT);

  TGraphAsymmErrors *gEnergySim_Pion70 = new TGraphAsymmErrors();
  gEnergySim_Pion70->SetMarkerSize(1);
  gEnergySim_Pion70->SetMarkerStyle(20);
  gEnergySim_Pion70->SetMarkerColor(kRed);
  gEnergySim_Pion70->SetLineColor(kRed);
  gEnergySim_Pion70->SetFillColor(kRed);
  gEnergySim_Pion70->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion70->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion70->GetBinContent(ibin);
    double energy = pEnergySim_Pion70->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion70_ErrorLow->GetBinContent(ibin);
    double content_up = pEnergySim_Pion70_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion70_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion70_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion70->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion70->SetPoint(ipoint, energy, content);
    gEnergySim_Pion70->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion70_QBBC = new TGraphAsymmErrors();
  gEnergySim_Pion70_QBBC->SetMarkerSize(1);
  gEnergySim_Pion70_QBBC->SetMarkerStyle(20);
  gEnergySim_Pion70_QBBC->SetMarkerColor(kBlue);
  gEnergySim_Pion70_QBBC->SetLineColor(kBlue);
  gEnergySim_Pion70_QBBC->SetFillColor(kBlue);
  gEnergySim_Pion70_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion70_QBBC->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion70_QBBC->GetBinContent(ibin);
    double energy = pEnergySim_Pion70_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion70_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pEnergySim_Pion70_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion70_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion70_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion70_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion70_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion70_QBBC->SetPoint(ipoint, energy, content);
    gEnergySim_Pion70_QBBC->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion70_QGSP_BERT = new TGraphAsymmErrors();
  gEnergySim_Pion70_QGSP_BERT->SetMarkerSize(1);
  gEnergySim_Pion70_QGSP_BERT->SetMarkerStyle(20);
  gEnergySim_Pion70_QGSP_BERT->SetMarkerColor(kGreen);
  gEnergySim_Pion70_QGSP_BERT->SetLineColor(kGreen);
  gEnergySim_Pion70_QGSP_BERT->SetFillColor(kGreen);
  gEnergySim_Pion70_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion70_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion70_QGSP_BERT->GetBinContent(ibin);
    double energy = pEnergySim_Pion70_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion70_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pEnergySim_Pion70_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion70_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion70_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion70_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion70_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion70_QGSP_BERT->SetPoint(ipoint, energy, content);
    gEnergySim_Pion70_QGSP_BERT->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange_DD4hep.root");
  TProfile *pEnergySim_Pion70_DD4hep, *pEnergySim_Pion70_ErrorLow_DD4hep, *pEnergySim_Pion70_ErrorHigh_DD4hep, *pEnergySim_Pion70_Xtalk10_DD4hep, *pEnergySim_Pion70_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile70", pEnergySim_Pion70_DD4hep);
  f3->GetObject("Pion_profile70_err_low", pEnergySim_Pion70_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile70_err_high", pEnergySim_Pion70_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile70_xtalk10", pEnergySim_Pion70_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile70_xtalk18", pEnergySim_Pion70_Xtalk18_DD4hep);

  TProfile *pEnergySim_Pion70_QBBC_DD4hep, *pEnergySim_Pion70_ErrorLow_QBBC_DD4hep, *pEnergySim_Pion70_ErrorHigh_QBBC_DD4hep, *pEnergySim_Pion70_Xtalk10_QBBC_DD4hep, *pEnergySim_Pion70_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile70_QBBC", pEnergySim_Pion70_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_err_low_QBBC", pEnergySim_Pion70_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_err_high_QBBC", pEnergySim_Pion70_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_xtalk10_QBBC", pEnergySim_Pion70_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_xtalk18_QBBC", pEnergySim_Pion70_Xtalk18_QBBC_DD4hep);

  TProfile *pEnergySim_Pion70_QGSP_BERT_DD4hep, *pEnergySim_Pion70_ErrorLow_QGSP_BERT_DD4hep, *pEnergySim_Pion70_ErrorHigh_QGSP_BERT_DD4hep, *pEnergySim_Pion70_Xtalk10_QGSP_BERT_DD4hep, *pEnergySim_Pion70_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile70_QGSP_BERT", pEnergySim_Pion70_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_err_low_QGSP_BERT", pEnergySim_Pion70_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_err_high_QGSP_BERT", pEnergySim_Pion70_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_xtalk10_QGSP_BERT", pEnergySim_Pion70_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_xtalk18_QGSP_BERT", pEnergySim_Pion70_Xtalk18_QGSP_BERT_DD4hep);

  TGraphAsymmErrors *gEnergySim_Pion70_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion70_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion70_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion70_DD4hep->SetMarkerColor(kRed);
  gEnergySim_Pion70_DD4hep->SetLineColor(kRed);
  gEnergySim_Pion70_DD4hep->SetFillColor(kRed);
  gEnergySim_Pion70_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion70_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion70_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion70_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion70_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion70_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion70_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion70_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion70_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion70_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion70_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion70_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion70_QBBC_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion70_QBBC_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion70_QBBC_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion70_QBBC_DD4hep->SetMarkerColor(kBlue);
  gEnergySim_Pion70_QBBC_DD4hep->SetLineColor(kBlue);
  gEnergySim_Pion70_QBBC_DD4hep->SetFillColor(kBlue);
  gEnergySim_Pion70_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion70_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion70_QBBC_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion70_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion70_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion70_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion70_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion70_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion70_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion70_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion70_QBBC_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion70_QBBC_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion70_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion70_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion70_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion70_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gEnergySim_Pion70_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gEnergySim_Pion70_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gEnergySim_Pion70_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion70_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion70_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion70_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion70_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion70_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion70_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion70_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion70_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion70_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion70_QGSP_BERT_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion70_QGSP_BERT_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gEnergyData_Pion70, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gEnergySim_Pion70_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gEnergySim_Pion70, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gEnergySim_Pion70_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gEnergySim_Pion70_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gEnergySim_Pion70_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gEnergySim_Pion70_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("70 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Pion70);
  multi2->Add(gEnergySim_Pion70);
  multi2->Add(gEnergySim_Pion70_QGSP_BERT);
  multi2->Add(gEnergySim_Pion70_QBBC);
  multi2->Add(gEnergySim_Pion70_DD4hep);
  multi2->Add(gEnergySim_Pion70_QGSP_BERT_DD4hep);
  multi2->Add(gEnergySim_Pion70_QBBC_DD4hep);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Energy", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Deposition [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Energy_70GeV.pdf");
}

void Radius_70GeV()
{
  CaliceStyle();
  //Comparison time vs Radius
  for(int type = 1; type < 3; type++)
  {
    //Data
    TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusData_Pion70;

    if(type == 1)
    f->GetObject("Pion_profile70_SSF", pRadiusData_Pion70);
    if(type == 2)
    f->GetObject("Pion_profile70_BL", pRadiusData_Pion70);

    TGraphErrors *gRadiusData_Pion70 = new TGraphErrors();
    gRadiusData_Pion70->SetMarkerSize(1);
    gRadiusData_Pion70->SetMarkerStyle(20);
    gRadiusData_Pion70->SetMarkerColor(kBlack);
    gRadiusData_Pion70->SetLineColor(kBlack);
    gRadiusData_Pion70->SetFillColor(kGray+1);
    gRadiusData_Pion70->SetFillStyle(3001);

    int ipoint = 0;
    for(int ibin = 1; ibin < pRadiusData_Pion70->GetNbinsX(); ibin++)
    {
      double content = pRadiusData_Pion70->GetBinContent(ibin);
      double radius = pRadiusData_Pion70->GetXaxis()->GetBinCenter(ibin);

      if(content == 0) continue;

      if(type == 1 && radius > 240) continue;
      if(type == 2 && radius > 350) continue;

      double error_stat = pRadiusData_Pion70->GetBinError(ibin);
      //Error syst
      double error_syst = 0;
      if(type == 1) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 70, "SSF"));
      if(type == 2) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 70, "BL"));

      double radius_err = pRadiusData_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusData_Pion70->SetPoint(ipoint, radius, content);
      gRadiusData_Pion70->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
      ipoint++;
    }

    //MC
    TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusSim_Pion70, *pRadiusSim_Pion70_ErrorLow, *pRadiusSim_Pion70_ErrorHigh, *pRadiusSim_Pion70_Xtalk10, *pRadiusSim_Pion70_Xtalk18;

    if(type == 1)
    {
      f2->GetObject("Pion_profile70_SSF", pRadiusSim_Pion70);
      f2->GetObject("Pion_profile70_err_low_SSF", pRadiusSim_Pion70_ErrorLow);
      f2->GetObject("Pion_profile70_err_high_SSF", pRadiusSim_Pion70_ErrorHigh);
      f2->GetObject("Pion_profile70_xtalk10_SSF", pRadiusSim_Pion70_Xtalk10);
      f2->GetObject("Pion_profile70_xtalk18_SSF", pRadiusSim_Pion70_Xtalk18);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile70_BL", pRadiusSim_Pion70);
      f2->GetObject("Pion_profile70_err_low_BL", pRadiusSim_Pion70_ErrorLow);
      f2->GetObject("Pion_profile70_err_high_BL", pRadiusSim_Pion70_ErrorHigh);
      f2->GetObject("Pion_profile70_xtalk10_BL", pRadiusSim_Pion70_Xtalk10);
      f2->GetObject("Pion_profile70_xtalk18_BL", pRadiusSim_Pion70_Xtalk18);
    }

    //QBBC
    TProfile *pRadiusSim_Pion70_QBBC, *pRadiusSim_Pion70_ErrorLow_QBBC, *pRadiusSim_Pion70_ErrorHigh_QBBC, *pRadiusSim_Pion70_Xtalk10_QBBC, *pRadiusSim_Pion70_Xtalk18_QBBC;

    if(type == 1)
    {
      f2->GetObject("Pion_profile70_SSF_QBBC", pRadiusSim_Pion70_QBBC);
      f2->GetObject("Pion_profile70_err_low_SSF_QBBC", pRadiusSim_Pion70_ErrorLow_QBBC);
      f2->GetObject("Pion_profile70_err_high_SSF_QBBC", pRadiusSim_Pion70_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile70_xtalk10_SSF_QBBC", pRadiusSim_Pion70_Xtalk10_QBBC);
      f2->GetObject("Pion_profile70_xtalk18_SSF_QBBC", pRadiusSim_Pion70_Xtalk18_QBBC);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile70_BL_QBBC", pRadiusSim_Pion70_QBBC);
      f2->GetObject("Pion_profile70_err_low_BL_QBBC", pRadiusSim_Pion70_ErrorLow_QBBC);
      f2->GetObject("Pion_profile70_err_high_BL_QBBC", pRadiusSim_Pion70_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile70_xtalk10_BL_QBBC", pRadiusSim_Pion70_Xtalk10_QBBC);
      f2->GetObject("Pion_profile70_xtalk18_BL_QBBC", pRadiusSim_Pion70_Xtalk18_QBBC);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion70_QGSP_BERT, *pRadiusSim_Pion70_ErrorLow_QGSP_BERT, *pRadiusSim_Pion70_ErrorHigh_QGSP_BERT, *pRadiusSim_Pion70_Xtalk10_QGSP_BERT, *pRadiusSim_Pion70_Xtalk18_QGSP_BERT;

    if(type == 1)
    {
      f2->GetObject("Pion_profile70_SSF_QGSP_BERT", pRadiusSim_Pion70_QGSP_BERT);
      f2->GetObject("Pion_profile70_err_low_SSF_QGSP_BERT", pRadiusSim_Pion70_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile70_err_high_SSF_QGSP_BERT", pRadiusSim_Pion70_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile70_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion70_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile70_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion70_Xtalk18_QGSP_BERT);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile70_BL_QGSP_BERT", pRadiusSim_Pion70_QGSP_BERT);
      f2->GetObject("Pion_profile70_err_low_BL_QGSP_BERT", pRadiusSim_Pion70_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile70_err_high_BL_QGSP_BERT", pRadiusSim_Pion70_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile70_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion70_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile70_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion70_Xtalk18_QGSP_BERT);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion70 = new TGraphAsymmErrors();
    gRadiusSim_Pion70->SetMarkerSize(1);
    gRadiusSim_Pion70->SetMarkerStyle(20);
    gRadiusSim_Pion70->SetMarkerColor(kRed);
    gRadiusSim_Pion70->SetLineColor(kRed);
    gRadiusSim_Pion70->SetFillColor(kRed);
    gRadiusSim_Pion70->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion70->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion70->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion70->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion70_ErrorLow->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion70_ErrorHigh->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion70_Xtalk10->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion70_Xtalk18->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion70->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion70->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion70->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion70_QBBC = new TGraphAsymmErrors();
    gRadiusSim_Pion70_QBBC->SetMarkerSize(1);
    gRadiusSim_Pion70_QBBC->SetMarkerStyle(20);
    gRadiusSim_Pion70_QBBC->SetMarkerColor(kBlue);
    gRadiusSim_Pion70_QBBC->SetLineColor(kBlue);
    gRadiusSim_Pion70_QBBC->SetFillColor(kBlue);
    gRadiusSim_Pion70_QBBC->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion70_QBBC->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion70_QBBC->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion70_QBBC->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion70_ErrorLow_QBBC->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion70_ErrorHigh_QBBC->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion70_Xtalk10_QBBC->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion70_Xtalk18_QBBC->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion70_QBBC->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion70_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion70_QBBC->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion70_QBBC->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion70_QGSP_BERT = new TGraphAsymmErrors();
    gRadiusSim_Pion70_QGSP_BERT->SetMarkerSize(1);
    gRadiusSim_Pion70_QGSP_BERT->SetMarkerStyle(20);
    gRadiusSim_Pion70_QGSP_BERT->SetMarkerColor(kGreen);
    gRadiusSim_Pion70_QGSP_BERT->SetLineColor(kGreen);
    gRadiusSim_Pion70_QGSP_BERT->SetFillColor(kGreen);
    gRadiusSim_Pion70_QGSP_BERT->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion70_QGSP_BERT->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion70_QGSP_BERT->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion70_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion70_ErrorLow_QGSP_BERT->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion70_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion70_Xtalk10_QGSP_BERT->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion70_Xtalk18_QGSP_BERT->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion70_QGSP_BERT->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion70_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion70_QGSP_BERT->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion70_QGSP_BERT->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //DD4hep
    TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange_DD4hep.root");
    TProfile *pRadiusSim_Pion70_DD4hep, *pRadiusSim_Pion70_ErrorLow_DD4hep, *pRadiusSim_Pion70_ErrorHigh_DD4hep, *pRadiusSim_Pion70_Xtalk10_DD4hep, *pRadiusSim_Pion70_Xtalk18_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile70_SSF", pRadiusSim_Pion70_DD4hep);
      f3->GetObject("Pion_profile70_err_low_SSF", pRadiusSim_Pion70_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile70_err_high_SSF", pRadiusSim_Pion70_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile70_xtalk10_SSF", pRadiusSim_Pion70_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile70_xtalk18_SSF", pRadiusSim_Pion70_Xtalk18_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile70_BL", pRadiusSim_Pion70_DD4hep);
      f3->GetObject("Pion_profile70_err_low_BL", pRadiusSim_Pion70_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile70_err_high_BL", pRadiusSim_Pion70_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile70_xtalk10_BL", pRadiusSim_Pion70_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile70_xtalk18_BL", pRadiusSim_Pion70_Xtalk18_DD4hep);
    }

    //QBBC
    TProfile *pRadiusSim_Pion70_QBBC_DD4hep, *pRadiusSim_Pion70_ErrorLow_QBBC_DD4hep, *pRadiusSim_Pion70_ErrorHigh_QBBC_DD4hep, *pRadiusSim_Pion70_Xtalk10_QBBC_DD4hep, *pRadiusSim_Pion70_Xtalk18_QBBC_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile70_SSF_QBBC", pRadiusSim_Pion70_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_err_low_SSF_QBBC", pRadiusSim_Pion70_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_err_high_SSF_QBBC", pRadiusSim_Pion70_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_xtalk10_SSF_QBBC", pRadiusSim_Pion70_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_xtalk18_SSF_QBBC", pRadiusSim_Pion70_Xtalk18_QBBC_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile70_BL_QBBC", pRadiusSim_Pion70_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_err_low_BL_QBBC", pRadiusSim_Pion70_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_err_high_BL_QBBC", pRadiusSim_Pion70_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_xtalk10_BL_QBBC", pRadiusSim_Pion70_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile70_xtalk18_BL_QBBC", pRadiusSim_Pion70_Xtalk18_QBBC_DD4hep);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion70_QGSP_BERT_DD4hep, *pRadiusSim_Pion70_ErrorLow_QGSP_BERT_DD4hep, *pRadiusSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep, *pRadiusSim_Pion70_Xtalk10_QGSP_BERT_DD4hep, *pRadiusSim_Pion70_Xtalk18_QGSP_BERT_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile70_SSF_QGSP_BERT", pRadiusSim_Pion70_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_err_low_SSF_QGSP_BERT", pRadiusSim_Pion70_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_err_high_SSF_QGSP_BERT", pRadiusSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion70_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion70_Xtalk18_QGSP_BERT_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile70_BL_QGSP_BERT", pRadiusSim_Pion70_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_err_low_BL_QGSP_BERT", pRadiusSim_Pion70_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_err_high_BL_QGSP_BERT", pRadiusSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion70_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile70_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion70_Xtalk18_QGSP_BERT_DD4hep);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion70_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion70_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion70_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion70_DD4hep->SetMarkerColor(kRed);
    gRadiusSim_Pion70_DD4hep->SetLineColor(kRed);
    gRadiusSim_Pion70_DD4hep->SetFillColor(kRed);
    gRadiusSim_Pion70_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion70_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion70_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion70_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion70_ErrorLow_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion70_ErrorHigh_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion70_Xtalk10_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion70_Xtalk18_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion70_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion70_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion70_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion70_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion70_QBBC_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion70_QBBC_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion70_QBBC_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion70_QBBC_DD4hep->SetMarkerColor(kBlue);
    gRadiusSim_Pion70_QBBC_DD4hep->SetLineColor(kBlue);
    gRadiusSim_Pion70_QBBC_DD4hep->SetFillColor(kBlue);
    gRadiusSim_Pion70_QBBC_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion70_QBBC_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion70_QBBC_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion70_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion70_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion70_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion70_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion70_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion70_QBBC_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion70_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion70_QBBC_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion70_QBBC_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion70_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
    gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetLineColor(kGreen);
    gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetFillColor(kGreen);
    gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion70_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion70_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion70_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion70_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion70_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion70_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion70_QGSP_BERT_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion70_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion70_QGSP_BERT_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //--------------------------------------------------------

    TLegend *leg2 = new TLegend(0.20, 0.55, 0.40, 0.75);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.025);
    leg2->SetHeader("Mokka");
    leg2->AddEntry(gRadiusData_Pion70, "Data (stat #oplus syst)", "pf");
    leg2->AddEntry(gRadiusSim_Pion70_QGSP_BERT, "QGSP_BERT", "pf");
    leg2->AddEntry(gRadiusSim_Pion70, "QGSP_BERT_HP", "pf");
    leg2->AddEntry(gRadiusSim_Pion70_QBBC, "QBBC", "pf");

    TLegend *leg3 = new TLegend(0.20, 0.35, 0.40, 0.52);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.025);
    leg3->SetHeader("DD4hep");
    leg3->AddEntry(gRadiusSim_Pion70_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
    leg3->AddEntry(gRadiusSim_Pion70_DD4hep, "QGSP_BERT_HP", "pf");
    leg3->AddEntry(gRadiusSim_Pion70_QBBC_DD4hep, "QBBC", "pf");

    TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
    pt2->SetBorderSize(0);
    pt2->SetTextColor(15);
    pt2->SetFillColor(0);
    pt2->SetTextSize(0.04);
    pt2->SetTextAlign(13); //left center
    pt2->AddText("CALICE AHCAL");
    pt2->AddText("Work in progress");
    pt2->AddText("70 GeV #pi^{-} - steel");

    TMultiGraph *multi2 = new TMultiGraph();
    multi2->Add(gRadiusData_Pion70);
    multi2->Add(gRadiusSim_Pion70);
    multi2->Add(gRadiusSim_Pion70_QGSP_BERT);
    multi2->Add(gRadiusSim_Pion70_QBBC);
    multi2->Add(gRadiusSim_Pion70_DD4hep);
    multi2->Add(gRadiusSim_Pion70_QGSP_BERT_DD4hep);
    multi2->Add(gRadiusSim_Pion70_QBBC_DD4hep);

    TCanvas *c2 = new TCanvas("c2", "Timing vs Radius", 800, 600);
    c2->cd();
    multi2->Draw("APX");
    multi2->GetXaxis()->SetTitle("Shower Radius [mm]");
    multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
    multi2->GetYaxis()->SetRangeUser(-1, 12);
    pt2->Draw("SAME");
    leg2->Draw("SAME");
    leg3->Draw("SAME");

    if(type == 1)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 15);
      multi2->GetXaxis()->SetRangeUser(0, 250);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_70GeV_SSF.pdf");
    }
    if(type == 2)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 12);
      multi2->GetXaxis()->SetRangeUser(0, 400);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_70GeV_BL.pdf");
    }
  }
}

void Depth_70GeV()
{
  CaliceStyle();
  //Comparison time vs Depth
  int maxbin = 11;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthData_Pion70;

  f->GetObject("Pion_profile70", pDepthData_Pion70);

  TGraphErrors *gDepthData_Pion70 = new TGraphErrors();
  gDepthData_Pion70->SetMarkerSize(1);
  gDepthData_Pion70->SetMarkerStyle(20);
  gDepthData_Pion70->SetMarkerColor(kBlack);
  gDepthData_Pion70->SetLineColor(kBlack);
  gDepthData_Pion70->SetFillColor(kGray+1);
  gDepthData_Pion70->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion70->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion70->GetBinContent(ibin);
    double Depth = pDepthData_Pion70->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion70->GetBinError(ibin);

    double error_syst = 1.04;
    double Depth_err = pDepthData_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthData_Pion70->SetPoint(ipoint, Depth, content);
    gDepthData_Pion70->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthSim_Pion70, *pDepthSim_Pion70_ErrorLow, *pDepthSim_Pion70_ErrorHigh, *pDepthSim_Pion70_Xtalk10, *pDepthSim_Pion70_Xtalk18;

  f2->GetObject("Pion_profile70", pDepthSim_Pion70);
  f2->GetObject("Pion_profile70_err_low", pDepthSim_Pion70_ErrorLow);
  f2->GetObject("Pion_profile70_err_high", pDepthSim_Pion70_ErrorHigh);
  f2->GetObject("Pion_profile70_xtalk10", pDepthSim_Pion70_Xtalk10);
  f2->GetObject("Pion_profile70_xtalk18", pDepthSim_Pion70_Xtalk18);

  //QBBC
  TProfile *pDepthSim_Pion70_QBBC, *pDepthSim_Pion70_ErrorLow_QBBC, *pDepthSim_Pion70_ErrorHigh_QBBC, *pDepthSim_Pion70_Xtalk10_QBBC, *pDepthSim_Pion70_Xtalk18_QBBC;

  f2->GetObject("Pion_profile70_QBBC", pDepthSim_Pion70_QBBC);
  f2->GetObject("Pion_profile70_err_low_QBBC", pDepthSim_Pion70_ErrorLow_QBBC);
  f2->GetObject("Pion_profile70_err_high_QBBC", pDepthSim_Pion70_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile70_xtalk10_QBBC", pDepthSim_Pion70_Xtalk10_QBBC);
  f2->GetObject("Pion_profile70_xtalk18_QBBC", pDepthSim_Pion70_Xtalk18_QBBC);

  //QGSP_BERT
  TProfile *pDepthSim_Pion70_QGSP_BERT, *pDepthSim_Pion70_ErrorLow_QGSP_BERT, *pDepthSim_Pion70_ErrorHigh_QGSP_BERT, *pDepthSim_Pion70_Xtalk10_QGSP_BERT, *pDepthSim_Pion70_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile70_QGSP_BERT", pDepthSim_Pion70_QGSP_BERT);
  f2->GetObject("Pion_profile70_err_low_QGSP_BERT", pDepthSim_Pion70_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile70_err_high_QGSP_BERT", pDepthSim_Pion70_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile70_xtalk10_QGSP_BERT", pDepthSim_Pion70_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile70_xtalk18_QGSP_BERT", pDepthSim_Pion70_Xtalk18_QGSP_BERT);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion70 = new TGraphAsymmErrors();
  gDepthSim_Pion70->SetMarkerSize(1);
  gDepthSim_Pion70->SetMarkerStyle(20);
  gDepthSim_Pion70->SetMarkerColor(kRed);
  gDepthSim_Pion70->SetLineColor(kRed);
  gDepthSim_Pion70->SetFillColor(kRed);
  gDepthSim_Pion70->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion70->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion70->GetBinContent(ibin);
    double Depth = pDepthSim_Pion70->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion70_ErrorLow->GetBinContent(ibin);
    double content_up = pDepthSim_Pion70_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion70_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion70_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion70->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion70->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion70->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion70->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion70_QBBC = new TGraphAsymmErrors();
  gDepthSim_Pion70_QBBC->SetMarkerSize(1);
  gDepthSim_Pion70_QBBC->SetMarkerStyle(20);
  gDepthSim_Pion70_QBBC->SetMarkerColor(kBlue);
  gDepthSim_Pion70_QBBC->SetLineColor(kBlue);
  gDepthSim_Pion70_QBBC->SetFillColor(kBlue);
  gDepthSim_Pion70_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion70_QBBC->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion70_QBBC->GetBinContent(ibin);
    double Depth = pDepthSim_Pion70_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion70_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pDepthSim_Pion70_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion70_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion70_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion70_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion70_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion70_QBBC->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion70_QBBC->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion70_QGSP_BERT = new TGraphAsymmErrors();
  gDepthSim_Pion70_QGSP_BERT->SetMarkerSize(1);
  gDepthSim_Pion70_QGSP_BERT->SetMarkerStyle(20);
  gDepthSim_Pion70_QGSP_BERT->SetMarkerColor(kGreen);
  gDepthSim_Pion70_QGSP_BERT->SetLineColor(kGreen);
  gDepthSim_Pion70_QGSP_BERT->SetFillColor(kGreen);
  gDepthSim_Pion70_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion70_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion70_QGSP_BERT->GetBinContent(ibin);
    double Depth = pDepthSim_Pion70_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion70_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pDepthSim_Pion70_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion70_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion70_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion70_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion70_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion70_QGSP_BERT->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion70_QGSP_BERT->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange_DD4hep.root");
  TProfile *pDepthSim_Pion70_DD4hep, *pDepthSim_Pion70_ErrorLow_DD4hep, *pDepthSim_Pion70_ErrorHigh_DD4hep, *pDepthSim_Pion70_Xtalk10_DD4hep, *pDepthSim_Pion70_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile70", pDepthSim_Pion70_DD4hep);
  f3->GetObject("Pion_profile70_err_low", pDepthSim_Pion70_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile70_err_high", pDepthSim_Pion70_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile70_xtalk10", pDepthSim_Pion70_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile70_xtalk18", pDepthSim_Pion70_Xtalk18_DD4hep);

  //QBBC
  TProfile *pDepthSim_Pion70_QBBC_DD4hep, *pDepthSim_Pion70_ErrorLow_QBBC_DD4hep, *pDepthSim_Pion70_ErrorHigh_QBBC_DD4hep, *pDepthSim_Pion70_Xtalk10_QBBC_DD4hep, *pDepthSim_Pion70_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile70_QBBC", pDepthSim_Pion70_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_err_low_QBBC", pDepthSim_Pion70_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_err_high_QBBC", pDepthSim_Pion70_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_xtalk10_QBBC", pDepthSim_Pion70_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile70_xtalk18_QBBC", pDepthSim_Pion70_Xtalk18_QBBC_DD4hep);

  //QGSP_BERT
  TProfile *pDepthSim_Pion70_QGSP_BERT_DD4hep, *pDepthSim_Pion70_ErrorLow_QGSP_BERT_DD4hep, *pDepthSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep, *pDepthSim_Pion70_Xtalk10_QGSP_BERT_DD4hep, *pDepthSim_Pion70_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile70_QGSP_BERT", pDepthSim_Pion70_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_err_low_QGSP_BERT", pDepthSim_Pion70_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_err_high_QGSP_BERT", pDepthSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_xtalk10_QGSP_BERT", pDepthSim_Pion70_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile70_xtalk18_QGSP_BERT", pDepthSim_Pion70_Xtalk18_QGSP_BERT_DD4hep);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion70_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion70_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion70_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion70_DD4hep->SetMarkerColor(kRed);
  gDepthSim_Pion70_DD4hep->SetLineColor(kRed);
  gDepthSim_Pion70_DD4hep->SetFillColor(kRed);
  gDepthSim_Pion70_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion70_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion70_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion70_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion70_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion70_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion70_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion70_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion70_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion70_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion70_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion70_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion70_QBBC_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion70_QBBC_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion70_QBBC_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion70_QBBC_DD4hep->SetMarkerColor(kBlue);
  gDepthSim_Pion70_QBBC_DD4hep->SetLineColor(kBlue);
  gDepthSim_Pion70_QBBC_DD4hep->SetFillColor(kBlue);
  gDepthSim_Pion70_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion70_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion70_QBBC_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion70_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion70_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion70_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion70_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion70_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion70_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion70_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion70_QBBC_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion70_QBBC_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion70_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion70_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion70_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion70_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gDepthSim_Pion70_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gDepthSim_Pion70_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gDepthSim_Pion70_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion70_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion70_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion70_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion70_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion70_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion70_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion70_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion70_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion70_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion70_QGSP_BERT_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion70_QGSP_BERT_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.65, 0.92, 0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gDepthData_Pion70, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gDepthSim_Pion70_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gDepthSim_Pion70, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gDepthSim_Pion70_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.48, 0.92, 0.63);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gDepthSim_Pion70_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gDepthSim_Pion70_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gDepthSim_Pion70_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.70, 0.4, 0.85, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("70 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gDepthData_Pion70);
  multi2->Add(gDepthSim_Pion70);
  multi2->Add(gDepthSim_Pion70_QGSP_BERT);
  multi2->Add(gDepthSim_Pion70_QBBC);
  multi2->Add(gDepthSim_Pion70_DD4hep);
  multi2->Add(gDepthSim_Pion70_QGSP_BERT_DD4hep);
  multi2->Add(gDepthSim_Pion70_QBBC_DD4hep);

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Depth", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Layer Position [mm]");
  multi2->GetXaxis()->SetRangeUser(50, 850);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");
  TGaxis *axis = new TGaxis(48, 10, 851, 10, 0.02, 4.17, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  c2->SaveAs("Plots/ComparisonToSim/Time_Depth_70GeV.pdf");
}

void Energy_90GeV()
{
  CaliceStyle();
  //Comparison time vs energy
  int maxbin = 49;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergyData_Pion90;

  f->GetObject("Pion_profile90", pEnergyData_Pion90);

  TGraphErrors *gEnergyData_Pion90 = new TGraphErrors();
  gEnergyData_Pion90->SetMarkerSize(1);
  gEnergyData_Pion90->SetMarkerStyle(20);
  gEnergyData_Pion90->SetMarkerColor(kBlack);
  gEnergyData_Pion90->SetLineColor(kBlack);
  gEnergyData_Pion90->SetFillColor(kGray+1);
  gEnergyData_Pion90->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pEnergyData_Pion90->GetNbinsX(); ibin++)
  {
    double content = pEnergyData_Pion90->GetBinContent(ibin);
    double energy = pEnergyData_Pion90->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;
    if(energy > 5) continue;

    double error_stat = pEnergyData_Pion90->GetBinError(ibin);
    double energy_err = pEnergyData_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

    //Error syst
    double error_syst = 1.04;

    gEnergyData_Pion90->SetPoint(ipoint, energy, content);
    gEnergyData_Pion90->SetPointError(ipoint, energy_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange.root");
  TProfile *pEnergySim_Pion90, *pEnergySim_Pion90_ErrorLow, *pEnergySim_Pion90_ErrorHigh, *pEnergySim_Pion90_Xtalk10, *pEnergySim_Pion90_Xtalk18;

  f2->GetObject("Pion_profile90", pEnergySim_Pion90);
  f2->GetObject("Pion_profile90_err_low", pEnergySim_Pion90_ErrorLow);
  f2->GetObject("Pion_profile90_err_high", pEnergySim_Pion90_ErrorHigh);
  f2->GetObject("Pion_profile90_xtalk10", pEnergySim_Pion90_Xtalk10);
  f2->GetObject("Pion_profile90_xtalk18", pEnergySim_Pion90_Xtalk18);

  TProfile *pEnergySim_Pion90_QBBC, *pEnergySim_Pion90_ErrorLow_QBBC, *pEnergySim_Pion90_ErrorHigh_QBBC, *pEnergySim_Pion90_Xtalk10_QBBC, *pEnergySim_Pion90_Xtalk18_QBBC;

  f2->GetObject("Pion_profile90_QBBC", pEnergySim_Pion90_QBBC);
  f2->GetObject("Pion_profile90_err_low_QBBC", pEnergySim_Pion90_ErrorLow_QBBC);
  f2->GetObject("Pion_profile90_err_high_QBBC", pEnergySim_Pion90_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile90_xtalk10_QBBC", pEnergySim_Pion90_Xtalk10_QBBC);
  f2->GetObject("Pion_profile90_xtalk18_QBBC", pEnergySim_Pion90_Xtalk18_QBBC);

  TProfile *pEnergySim_Pion90_QGSP_BERT, *pEnergySim_Pion90_ErrorLow_QGSP_BERT, *pEnergySim_Pion90_ErrorHigh_QGSP_BERT, *pEnergySim_Pion90_Xtalk10_QGSP_BERT, *pEnergySim_Pion90_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile90_QGSP_BERT", pEnergySim_Pion90_QGSP_BERT);
  f2->GetObject("Pion_profile90_err_low_QGSP_BERT", pEnergySim_Pion90_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile90_err_high_QGSP_BERT", pEnergySim_Pion90_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile90_xtalk10_QGSP_BERT", pEnergySim_Pion90_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile90_xtalk18_QGSP_BERT", pEnergySim_Pion90_Xtalk18_QGSP_BERT);

  TGraphAsymmErrors *gEnergySim_Pion90 = new TGraphAsymmErrors();
  gEnergySim_Pion90->SetMarkerSize(1);
  gEnergySim_Pion90->SetMarkerStyle(20);
  gEnergySim_Pion90->SetMarkerColor(kRed);
  gEnergySim_Pion90->SetLineColor(kRed);
  gEnergySim_Pion90->SetFillColor(kRed);
  gEnergySim_Pion90->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion90->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion90->GetBinContent(ibin);
    double energy = pEnergySim_Pion90->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion90_ErrorLow->GetBinContent(ibin);
    double content_up = pEnergySim_Pion90_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion90_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion90_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion90->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion90->SetPoint(ipoint, energy, content);
    gEnergySim_Pion90->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion90_QBBC = new TGraphAsymmErrors();
  gEnergySim_Pion90_QBBC->SetMarkerSize(1);
  gEnergySim_Pion90_QBBC->SetMarkerStyle(20);
  gEnergySim_Pion90_QBBC->SetMarkerColor(kBlue);
  gEnergySim_Pion90_QBBC->SetLineColor(kBlue);
  gEnergySim_Pion90_QBBC->SetFillColor(kBlue);
  gEnergySim_Pion90_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion90_QBBC->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion90_QBBC->GetBinContent(ibin);
    double energy = pEnergySim_Pion90_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion90_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pEnergySim_Pion90_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion90_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion90_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion90_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion90_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion90_QBBC->SetPoint(ipoint, energy, content);
    gEnergySim_Pion90_QBBC->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion90_QGSP_BERT = new TGraphAsymmErrors();
  gEnergySim_Pion90_QGSP_BERT->SetMarkerSize(1);
  gEnergySim_Pion90_QGSP_BERT->SetMarkerStyle(20);
  gEnergySim_Pion90_QGSP_BERT->SetMarkerColor(kGreen);
  gEnergySim_Pion90_QGSP_BERT->SetLineColor(kGreen);
  gEnergySim_Pion90_QGSP_BERT->SetFillColor(kGreen);
  gEnergySim_Pion90_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion90_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion90_QGSP_BERT->GetBinContent(ibin);
    double energy = pEnergySim_Pion90_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion90_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pEnergySim_Pion90_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion90_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion90_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion90_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion90_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion90_QGSP_BERT->SetPoint(ipoint, energy, content);
    gEnergySim_Pion90_QGSP_BERT->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Energy_ShortAsymRange_DD4hep.root");
  TProfile *pEnergySim_Pion90_DD4hep, *pEnergySim_Pion90_ErrorLow_DD4hep, *pEnergySim_Pion90_ErrorHigh_DD4hep, *pEnergySim_Pion90_Xtalk10_DD4hep, *pEnergySim_Pion90_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile90", pEnergySim_Pion90_DD4hep);
  f3->GetObject("Pion_profile90_err_low", pEnergySim_Pion90_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile90_err_high", pEnergySim_Pion90_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile90_xtalk10", pEnergySim_Pion90_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile90_xtalk18", pEnergySim_Pion90_Xtalk18_DD4hep);

  TProfile *pEnergySim_Pion90_QBBC_DD4hep, *pEnergySim_Pion90_ErrorLow_QBBC_DD4hep, *pEnergySim_Pion90_ErrorHigh_QBBC_DD4hep, *pEnergySim_Pion90_Xtalk10_QBBC_DD4hep, *pEnergySim_Pion90_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile90_QBBC", pEnergySim_Pion90_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_err_low_QBBC", pEnergySim_Pion90_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_err_high_QBBC", pEnergySim_Pion90_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_xtalk10_QBBC", pEnergySim_Pion90_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_xtalk18_QBBC", pEnergySim_Pion90_Xtalk18_QBBC_DD4hep);

  TProfile *pEnergySim_Pion90_QGSP_BERT_DD4hep, *pEnergySim_Pion90_ErrorLow_QGSP_BERT_DD4hep, *pEnergySim_Pion90_ErrorHigh_QGSP_BERT_DD4hep, *pEnergySim_Pion90_Xtalk10_QGSP_BERT_DD4hep, *pEnergySim_Pion90_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile90_QGSP_BERT", pEnergySim_Pion90_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_err_low_QGSP_BERT", pEnergySim_Pion90_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_err_high_QGSP_BERT", pEnergySim_Pion90_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_xtalk10_QGSP_BERT", pEnergySim_Pion90_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_xtalk18_QGSP_BERT", pEnergySim_Pion90_Xtalk18_QGSP_BERT_DD4hep);

  TGraphAsymmErrors *gEnergySim_Pion90_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion90_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion90_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion90_DD4hep->SetMarkerColor(kRed);
  gEnergySim_Pion90_DD4hep->SetLineColor(kRed);
  gEnergySim_Pion90_DD4hep->SetFillColor(kRed);
  gEnergySim_Pion90_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion90_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion90_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion90_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion90_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion90_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion90_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion90_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion90_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion90_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion90_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion90_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QBBC
  TGraphAsymmErrors *gEnergySim_Pion90_QBBC_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion90_QBBC_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion90_QBBC_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion90_QBBC_DD4hep->SetMarkerColor(kBlue);
  gEnergySim_Pion90_QBBC_DD4hep->SetLineColor(kBlue);
  gEnergySim_Pion90_QBBC_DD4hep->SetFillColor(kBlue);
  gEnergySim_Pion90_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion90_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion90_QBBC_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion90_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion90_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion90_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion90_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion90_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion90_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion90_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion90_QBBC_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion90_QBBC_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //QGSP_BERT
  TGraphAsymmErrors *gEnergySim_Pion90_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gEnergySim_Pion90_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gEnergySim_Pion90_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gEnergySim_Pion90_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gEnergySim_Pion90_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gEnergySim_Pion90_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gEnergySim_Pion90_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pEnergySim_Pion90_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pEnergySim_Pion90_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double energy = pEnergySim_Pion90_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pEnergySim_Pion90_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pEnergySim_Pion90_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pEnergySim_Pion90_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pEnergySim_Pion90_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;
    if(energy > 5) continue;

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

    double error_stat = pEnergySim_Pion90_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double energy_err = pEnergySim_Pion90_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gEnergySim_Pion90_QGSP_BERT_DD4hep->SetPoint(ipoint, energy, content);
    gEnergySim_Pion90_QGSP_BERT_DD4hep->SetPointError(ipoint, energy_err, energy_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.70, 0.92, 0.91);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gEnergyData_Pion90, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gEnergySim_Pion90_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gEnergySim_Pion90, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gEnergySim_Pion90_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.52, 0.92, 0.68);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gEnergySim_Pion90_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gEnergySim_Pion90_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gEnergySim_Pion90_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("90 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gEnergyData_Pion90);
  multi2->Add(gEnergySim_Pion90);
  multi2->Add(gEnergySim_Pion90_QGSP_BERT);
  multi2->Add(gEnergySim_Pion90_QBBC);
  multi2->Add(gEnergySim_Pion90_DD4hep);
  multi2->Add(gEnergySim_Pion90_QGSP_BERT_DD4hep);
  multi2->Add(gEnergySim_Pion90_QBBC_DD4hep);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Energy", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Energy Deposition [MIP]");
  multi2->GetXaxis()->SetRangeUser(0, 5);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Energy_90GeV.pdf");
}

void Radius_90GeV()
{
  CaliceStyle();
  //Comparison time vs Radius
  for(int type = 1; type < 3; type++)
  {
    //Data
    TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusData_Pion90;

    if(type == 1)
    f->GetObject("Pion_profile90_SSF", pRadiusData_Pion90);
    if(type == 2)
    f->GetObject("Pion_profile90_BL", pRadiusData_Pion90);

    TGraphErrors *gRadiusData_Pion90 = new TGraphErrors();
    gRadiusData_Pion90->SetMarkerSize(1);
    gRadiusData_Pion90->SetMarkerStyle(20);
    gRadiusData_Pion90->SetMarkerColor(kBlack);
    gRadiusData_Pion90->SetLineColor(kBlack);
    gRadiusData_Pion90->SetFillColor(kGray+1);
    gRadiusData_Pion90->SetFillStyle(3001);

    int ipoint = 0;
    for(int ibin = 1; ibin < pRadiusData_Pion90->GetNbinsX(); ibin++)
    {
      double content = pRadiusData_Pion90->GetBinContent(ibin);
      double radius = pRadiusData_Pion90->GetXaxis()->GetBinCenter(ibin);

      if(content == 0) continue;

      if(type == 1 && radius > 240) continue;
      if(type == 2 && radius > 350) continue;

      double error_stat = pRadiusData_Pion90->GetBinError(ibin);
      //Error syst
      double error_syst = 0;
      if(type == 1) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 90, "SSF"));
      if(type == 2) error_syst = TMath::Sqrt(1.04*1.04 + GetSyst(radius, 90, "BL"));

      double radius_err = pRadiusData_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusData_Pion90->SetPoint(ipoint, radius, content);
      gRadiusData_Pion90->SetPointError(ipoint, radius_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
      ipoint++;
    }

    //MC
    TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange.root");
    TProfile *pRadiusSim_Pion90, *pRadiusSim_Pion90_ErrorLow, *pRadiusSim_Pion90_ErrorHigh, *pRadiusSim_Pion90_Xtalk10, *pRadiusSim_Pion90_Xtalk18;

    if(type == 1)
    {
      f2->GetObject("Pion_profile90_SSF", pRadiusSim_Pion90);
      f2->GetObject("Pion_profile90_err_low_SSF", pRadiusSim_Pion90_ErrorLow);
      f2->GetObject("Pion_profile90_err_high_SSF", pRadiusSim_Pion90_ErrorHigh);
      f2->GetObject("Pion_profile90_xtalk10_SSF", pRadiusSim_Pion90_Xtalk10);
      f2->GetObject("Pion_profile90_xtalk18_SSF", pRadiusSim_Pion90_Xtalk18);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile90_BL", pRadiusSim_Pion90);
      f2->GetObject("Pion_profile90_err_low_BL", pRadiusSim_Pion90_ErrorLow);
      f2->GetObject("Pion_profile90_err_high_BL", pRadiusSim_Pion90_ErrorHigh);
      f2->GetObject("Pion_profile90_xtalk10_BL", pRadiusSim_Pion90_Xtalk10);
      f2->GetObject("Pion_profile90_xtalk18_BL", pRadiusSim_Pion90_Xtalk18);
    }

    //QBBC
    TProfile *pRadiusSim_Pion90_QBBC, *pRadiusSim_Pion90_ErrorLow_QBBC, *pRadiusSim_Pion90_ErrorHigh_QBBC, *pRadiusSim_Pion90_Xtalk10_QBBC, *pRadiusSim_Pion90_Xtalk18_QBBC;

    if(type == 1)
    {
      f2->GetObject("Pion_profile90_SSF_QBBC", pRadiusSim_Pion90_QBBC);
      f2->GetObject("Pion_profile90_err_low_SSF_QBBC", pRadiusSim_Pion90_ErrorLow_QBBC);
      f2->GetObject("Pion_profile90_err_high_SSF_QBBC", pRadiusSim_Pion90_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile90_xtalk10_SSF_QBBC", pRadiusSim_Pion90_Xtalk10_QBBC);
      f2->GetObject("Pion_profile90_xtalk18_SSF_QBBC", pRadiusSim_Pion90_Xtalk18_QBBC);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile90_BL_QBBC", pRadiusSim_Pion90_QBBC);
      f2->GetObject("Pion_profile90_err_low_BL_QBBC", pRadiusSim_Pion90_ErrorLow_QBBC);
      f2->GetObject("Pion_profile90_err_high_BL_QBBC", pRadiusSim_Pion90_ErrorHigh_QBBC);
      f2->GetObject("Pion_profile90_xtalk10_BL_QBBC", pRadiusSim_Pion90_Xtalk10_QBBC);
      f2->GetObject("Pion_profile90_xtalk18_BL_QBBC", pRadiusSim_Pion90_Xtalk18_QBBC);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion90_QGSP_BERT, *pRadiusSim_Pion90_ErrorLow_QGSP_BERT, *pRadiusSim_Pion90_ErrorHigh_QGSP_BERT, *pRadiusSim_Pion90_Xtalk10_QGSP_BERT, *pRadiusSim_Pion90_Xtalk18_QGSP_BERT;

    if(type == 1)
    {
      f2->GetObject("Pion_profile90_SSF_QGSP_BERT", pRadiusSim_Pion90_QGSP_BERT);
      f2->GetObject("Pion_profile90_err_low_SSF_QGSP_BERT", pRadiusSim_Pion90_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile90_err_high_SSF_QGSP_BERT", pRadiusSim_Pion90_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile90_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion90_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile90_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion90_Xtalk18_QGSP_BERT);
    }
    if(type == 2)
    {
      f2->GetObject("Pion_profile90_BL_QGSP_BERT", pRadiusSim_Pion90_QGSP_BERT);
      f2->GetObject("Pion_profile90_err_low_BL_QGSP_BERT", pRadiusSim_Pion90_ErrorLow_QGSP_BERT);
      f2->GetObject("Pion_profile90_err_high_BL_QGSP_BERT", pRadiusSim_Pion90_ErrorHigh_QGSP_BERT);
      f2->GetObject("Pion_profile90_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion90_Xtalk10_QGSP_BERT);
      f2->GetObject("Pion_profile90_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion90_Xtalk18_QGSP_BERT);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion90 = new TGraphAsymmErrors();
    gRadiusSim_Pion90->SetMarkerSize(1);
    gRadiusSim_Pion90->SetMarkerStyle(20);
    gRadiusSim_Pion90->SetMarkerColor(kRed);
    gRadiusSim_Pion90->SetLineColor(kRed);
    gRadiusSim_Pion90->SetFillColor(kRed);
    gRadiusSim_Pion90->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion90->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion90->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion90->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion90_ErrorLow->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion90_ErrorHigh->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion90_Xtalk10->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion90_Xtalk18->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion90->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion90->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion90->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion90_QBBC = new TGraphAsymmErrors();
    gRadiusSim_Pion90_QBBC->SetMarkerSize(1);
    gRadiusSim_Pion90_QBBC->SetMarkerStyle(20);
    gRadiusSim_Pion90_QBBC->SetMarkerColor(kBlue);
    gRadiusSim_Pion90_QBBC->SetLineColor(kBlue);
    gRadiusSim_Pion90_QBBC->SetFillColor(kBlue);
    gRadiusSim_Pion90_QBBC->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion90_QBBC->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion90_QBBC->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion90_QBBC->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion90_ErrorLow_QBBC->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion90_ErrorHigh_QBBC->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion90_Xtalk10_QBBC->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion90_Xtalk18_QBBC->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion90_QBBC->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion90_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion90_QBBC->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion90_QBBC->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion90_QGSP_BERT = new TGraphAsymmErrors();
    gRadiusSim_Pion90_QGSP_BERT->SetMarkerSize(1);
    gRadiusSim_Pion90_QGSP_BERT->SetMarkerStyle(20);
    gRadiusSim_Pion90_QGSP_BERT->SetMarkerColor(kGreen);
    gRadiusSim_Pion90_QGSP_BERT->SetLineColor(kGreen);
    gRadiusSim_Pion90_QGSP_BERT->SetFillColor(kGreen);
    gRadiusSim_Pion90_QGSP_BERT->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion90_QGSP_BERT->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion90_QGSP_BERT->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion90_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion90_ErrorLow_QGSP_BERT->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion90_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion90_Xtalk10_QGSP_BERT->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion90_Xtalk18_QGSP_BERT->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion90_QGSP_BERT->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion90_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion90_QGSP_BERT->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion90_QGSP_BERT->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //DD4hep
    TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Radius_ShortAsymRange_DD4hep.root");
    TProfile *pRadiusSim_Pion90_DD4hep, *pRadiusSim_Pion90_ErrorLow_DD4hep, *pRadiusSim_Pion90_ErrorHigh_DD4hep, *pRadiusSim_Pion90_Xtalk10_DD4hep, *pRadiusSim_Pion90_Xtalk18_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile90_SSF", pRadiusSim_Pion90_DD4hep);
      f3->GetObject("Pion_profile90_err_low_SSF", pRadiusSim_Pion90_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile90_err_high_SSF", pRadiusSim_Pion90_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile90_xtalk10_SSF", pRadiusSim_Pion90_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile90_xtalk18_SSF", pRadiusSim_Pion90_Xtalk18_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile90_BL", pRadiusSim_Pion90_DD4hep);
      f3->GetObject("Pion_profile90_err_low_BL", pRadiusSim_Pion90_ErrorLow_DD4hep);
      f3->GetObject("Pion_profile90_err_high_BL", pRadiusSim_Pion90_ErrorHigh_DD4hep);
      f3->GetObject("Pion_profile90_xtalk10_BL", pRadiusSim_Pion90_Xtalk10_DD4hep);
      f3->GetObject("Pion_profile90_xtalk18_BL", pRadiusSim_Pion90_Xtalk18_DD4hep);
    }

    //QBBC
    TProfile *pRadiusSim_Pion90_QBBC_DD4hep, *pRadiusSim_Pion90_ErrorLow_QBBC_DD4hep, *pRadiusSim_Pion90_ErrorHigh_QBBC_DD4hep, *pRadiusSim_Pion90_Xtalk10_QBBC_DD4hep, *pRadiusSim_Pion90_Xtalk18_QBBC_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile90_SSF_QBBC", pRadiusSim_Pion90_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_err_low_SSF_QBBC", pRadiusSim_Pion90_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_err_high_SSF_QBBC", pRadiusSim_Pion90_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_xtalk10_SSF_QBBC", pRadiusSim_Pion90_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_xtalk18_SSF_QBBC", pRadiusSim_Pion90_Xtalk18_QBBC_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile90_BL_QBBC", pRadiusSim_Pion90_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_err_low_BL_QBBC", pRadiusSim_Pion90_ErrorLow_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_err_high_BL_QBBC", pRadiusSim_Pion90_ErrorHigh_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_xtalk10_BL_QBBC", pRadiusSim_Pion90_Xtalk10_QBBC_DD4hep);
      f3->GetObject("Pion_profile90_xtalk18_BL_QBBC", pRadiusSim_Pion90_Xtalk18_QBBC_DD4hep);
    }

    //QGSP_BERT
    TProfile *pRadiusSim_Pion90_QGSP_BERT_DD4hep, *pRadiusSim_Pion90_ErrorLow_QGSP_BERT_DD4hep, *pRadiusSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep, *pRadiusSim_Pion90_Xtalk10_QGSP_BERT_DD4hep, *pRadiusSim_Pion90_Xtalk18_QGSP_BERT_DD4hep;

    if(type == 1)
    {
      f3->GetObject("Pion_profile90_SSF_QGSP_BERT", pRadiusSim_Pion90_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_err_low_SSF_QGSP_BERT", pRadiusSim_Pion90_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_err_high_SSF_QGSP_BERT", pRadiusSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_xtalk10_SSF_QGSP_BERT", pRadiusSim_Pion90_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_xtalk18_SSF_QGSP_BERT", pRadiusSim_Pion90_Xtalk18_QGSP_BERT_DD4hep);
    }
    if(type == 2)
    {
      f3->GetObject("Pion_profile90_BL_QGSP_BERT", pRadiusSim_Pion90_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_err_low_BL_QGSP_BERT", pRadiusSim_Pion90_ErrorLow_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_err_high_BL_QGSP_BERT", pRadiusSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_xtalk10_BL_QGSP_BERT", pRadiusSim_Pion90_Xtalk10_QGSP_BERT_DD4hep);
      f3->GetObject("Pion_profile90_xtalk18_BL_QGSP_BERT", pRadiusSim_Pion90_Xtalk18_QGSP_BERT_DD4hep);
    }

    //---------------------------------------------------

    TGraphAsymmErrors *gRadiusSim_Pion90_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion90_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion90_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion90_DD4hep->SetMarkerColor(kRed);
    gRadiusSim_Pion90_DD4hep->SetLineColor(kRed);
    gRadiusSim_Pion90_DD4hep->SetFillColor(kRed);
    gRadiusSim_Pion90_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion90_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion90_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion90_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion90_ErrorLow_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion90_ErrorHigh_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion90_Xtalk10_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion90_Xtalk18_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion90_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion90_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion90_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion90_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QBBC
    TGraphAsymmErrors *gRadiusSim_Pion90_QBBC_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion90_QBBC_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion90_QBBC_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion90_QBBC_DD4hep->SetMarkerColor(kBlue);
    gRadiusSim_Pion90_QBBC_DD4hep->SetLineColor(kBlue);
    gRadiusSim_Pion90_QBBC_DD4hep->SetFillColor(kBlue);
    gRadiusSim_Pion90_QBBC_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion90_QBBC_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion90_QBBC_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion90_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion90_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion90_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion90_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion90_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion90_QBBC_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion90_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion90_QBBC_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion90_QBBC_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //QGSP_BERT
    TGraphAsymmErrors *gRadiusSim_Pion90_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
    gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetMarkerSize(1);
    gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetMarkerStyle(22);
    gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
    gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetLineColor(kGreen);
    gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetFillColor(kGreen);
    gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetFillStyle(3001);

    ipoint = 0;
    for(int ibin = 1; ibin < pRadiusSim_Pion90_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
    {
      double content = pRadiusSim_Pion90_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double Radius = pRadiusSim_Pion90_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

      double content_low = pRadiusSim_Pion90_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_up = pRadiusSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double content_Xtalk10 = pRadiusSim_Pion90_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
      double content_Xtalk18 = pRadiusSim_Pion90_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

      double error_low = 0.;
      double error_up = 0.;

      double error_Xtalk_low = 0.;
      double error_Xtalk_up = 0.;

      if(content == 0) continue;

      if(type == 1 && Radius > 240) continue;
      if(type == 2 && Radius > 350) continue;

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

      double error_stat = pRadiusSim_Pion90_QGSP_BERT_DD4hep->GetBinError(ibin);
      double error_syst = 0.01;
      double Radius_err = pRadiusSim_Pion90_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

      gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetPoint(ipoint, Radius, content);
      gRadiusSim_Pion90_QGSP_BERT_DD4hep->SetPointError(ipoint, Radius_err, Radius_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
      ipoint++;
    }

    //--------------------------------------------------------

    TLegend *leg2 = new TLegend(0.20, 0.55, 0.40, 0.75);
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.025);
    leg2->SetHeader("Mokka");
    leg2->AddEntry(gRadiusData_Pion90, "Data (stat #oplus syst)", "pf");
    leg2->AddEntry(gRadiusSim_Pion90_QGSP_BERT, "QGSP_BERT", "pf");
    leg2->AddEntry(gRadiusSim_Pion90, "QGSP_BERT_HP", "pf");
    leg2->AddEntry(gRadiusSim_Pion90_QBBC, "QBBC", "pf");

    TLegend *leg3 = new TLegend(0.20, 0.35, 0.40, 0.52);
    leg3->SetBorderSize(0);
    leg3->SetTextSize(0.025);
    leg3->SetHeader("DD4hep");
    leg3->AddEntry(gRadiusSim_Pion90_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
    leg3->AddEntry(gRadiusSim_Pion90_DD4hep, "QGSP_BERT_HP", "pf");
    leg3->AddEntry(gRadiusSim_Pion90_QBBC_DD4hep, "QBBC", "pf");

    TPaveText *pt2 = new TPaveText(0.20, 0.80, 0.4, 0.92, "tbNDC");
    pt2->SetBorderSize(0);
    pt2->SetTextColor(15);
    pt2->SetFillColor(0);
    pt2->SetTextSize(0.04);
    pt2->SetTextAlign(13); //left center
    pt2->AddText("CALICE AHCAL");
    pt2->AddText("Work in progress");
    pt2->AddText("90 GeV #pi^{-} - steel");

    TMultiGraph *multi2 = new TMultiGraph();
    multi2->Add(gRadiusData_Pion90);
    multi2->Add(gRadiusSim_Pion90);
    multi2->Add(gRadiusSim_Pion90_QGSP_BERT);
    multi2->Add(gRadiusSim_Pion90_QBBC);
    multi2->Add(gRadiusSim_Pion90_DD4hep);
    multi2->Add(gRadiusSim_Pion90_QGSP_BERT_DD4hep);
    multi2->Add(gRadiusSim_Pion90_QBBC_DD4hep);

    TCanvas *c2 = new TCanvas("c2", "Timing vs Radius", 800, 600);
    c2->cd();
    multi2->Draw("APX");
    multi2->GetXaxis()->SetTitle("Shower Radius [mm]");
    multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
    multi2->GetYaxis()->SetRangeUser(-1, 12);
    pt2->Draw("SAME");
    leg2->Draw("SAME");
    leg3->Draw("SAME");

    if(type == 1)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 15);
      multi2->GetXaxis()->SetRangeUser(0, 250);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_90GeV_SSF.pdf");
    }
    if(type == 2)
    {
      multi2->Draw("E3");
      multi2->Draw("PX");
      multi2->GetYaxis()->SetRangeUser(-1, 12);
      multi2->GetXaxis()->SetRangeUser(0, 400);
      c2->SaveAs("Plots/ComparisonToSim/Time_Radius_90GeV_BL.pdf");
    }
  }
}

void Depth_90GeV()
{
  CaliceStyle();
  //Comparison time vs Depth
  int maxbin = 11;

  //Data
  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthData_Pion90;

  f->GetObject("Pion_profile90", pDepthData_Pion90);

  TGraphErrors *gDepthData_Pion90 = new TGraphErrors();
  gDepthData_Pion90->SetMarkerSize(1);
  gDepthData_Pion90->SetMarkerStyle(20);
  gDepthData_Pion90->SetMarkerColor(kBlack);
  gDepthData_Pion90->SetLineColor(kBlack);
  gDepthData_Pion90->SetFillColor(kGray+1);
  gDepthData_Pion90->SetFillStyle(3001);

  int ipoint = 0;
  for(int ibin = 1; ibin < pDepthData_Pion90->GetNbinsX(); ibin++)
  {
    double content = pDepthData_Pion90->GetBinContent(ibin);
    double Depth = pDepthData_Pion90->GetXaxis()->GetBinCenter(ibin);

    if(content == 0) continue;

    double error_stat = pDepthData_Pion90->GetBinError(ibin);
    //Error syst
    double error_syst = 1.04;
    double Depth_err = pDepthData_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthData_Pion90->SetPoint(ipoint, Depth, content);
    gDepthData_Pion90->SetPointError(ipoint, Depth_err, TMath::Sqrt(error_stat*error_stat + error_syst*error_syst));
    ipoint++;
  }

  //MC
  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange.root");
  TProfile *pDepthSim_Pion90, *pDepthSim_Pion90_ErrorLow, *pDepthSim_Pion90_ErrorHigh, *pDepthSim_Pion90_Xtalk10, *pDepthSim_Pion90_Xtalk18;

  f2->GetObject("Pion_profile90", pDepthSim_Pion90);
  f2->GetObject("Pion_profile90_err_low", pDepthSim_Pion90_ErrorLow);
  f2->GetObject("Pion_profile90_err_high", pDepthSim_Pion90_ErrorHigh);
  f2->GetObject("Pion_profile90_xtalk10", pDepthSim_Pion90_Xtalk10);
  f2->GetObject("Pion_profile90_xtalk18", pDepthSim_Pion90_Xtalk18);

  //QBBC
  TProfile *pDepthSim_Pion90_QBBC, *pDepthSim_Pion90_ErrorLow_QBBC, *pDepthSim_Pion90_ErrorHigh_QBBC, *pDepthSim_Pion90_Xtalk10_QBBC, *pDepthSim_Pion90_Xtalk18_QBBC;

  f2->GetObject("Pion_profile90_QBBC", pDepthSim_Pion90_QBBC);
  f2->GetObject("Pion_profile90_err_low_QBBC", pDepthSim_Pion90_ErrorLow_QBBC);
  f2->GetObject("Pion_profile90_err_high_QBBC", pDepthSim_Pion90_ErrorHigh_QBBC);
  f2->GetObject("Pion_profile90_xtalk10_QBBC", pDepthSim_Pion90_Xtalk10_QBBC);
  f2->GetObject("Pion_profile90_xtalk18_QBBC", pDepthSim_Pion90_Xtalk18_QBBC);

  //QGSP_BERT
  TProfile *pDepthSim_Pion90_QGSP_BERT, *pDepthSim_Pion90_ErrorLow_QGSP_BERT, *pDepthSim_Pion90_ErrorHigh_QGSP_BERT, *pDepthSim_Pion90_Xtalk10_QGSP_BERT, *pDepthSim_Pion90_Xtalk18_QGSP_BERT;

  f2->GetObject("Pion_profile90_QGSP_BERT", pDepthSim_Pion90_QGSP_BERT);
  f2->GetObject("Pion_profile90_err_low_QGSP_BERT", pDepthSim_Pion90_ErrorLow_QGSP_BERT);
  f2->GetObject("Pion_profile90_err_high_QGSP_BERT", pDepthSim_Pion90_ErrorHigh_QGSP_BERT);
  f2->GetObject("Pion_profile90_xtalk10_QGSP_BERT", pDepthSim_Pion90_Xtalk10_QGSP_BERT);
  f2->GetObject("Pion_profile90_xtalk18_QGSP_BERT", pDepthSim_Pion90_Xtalk18_QGSP_BERT);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion90 = new TGraphAsymmErrors();
  gDepthSim_Pion90->SetMarkerSize(1);
  gDepthSim_Pion90->SetMarkerStyle(20);
  gDepthSim_Pion90->SetMarkerColor(kRed);
  gDepthSim_Pion90->SetLineColor(kRed);
  gDepthSim_Pion90->SetFillColor(kRed);
  gDepthSim_Pion90->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion90->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion90->GetBinContent(ibin);
    double Depth = pDepthSim_Pion90->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion90_ErrorLow->GetBinContent(ibin);
    double content_up = pDepthSim_Pion90_ErrorHigh->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion90_Xtalk10->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion90_Xtalk18->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion90->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion90->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion90->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion90->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion90_QBBC = new TGraphAsymmErrors();
  gDepthSim_Pion90_QBBC->SetMarkerSize(1);
  gDepthSim_Pion90_QBBC->SetMarkerStyle(20);
  gDepthSim_Pion90_QBBC->SetMarkerColor(kBlue);
  gDepthSim_Pion90_QBBC->SetLineColor(kBlue);
  gDepthSim_Pion90_QBBC->SetFillColor(kBlue);
  gDepthSim_Pion90_QBBC->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion90_QBBC->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion90_QBBC->GetBinContent(ibin);
    double Depth = pDepthSim_Pion90_QBBC->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion90_ErrorLow_QBBC->GetBinContent(ibin);
    double content_up = pDepthSim_Pion90_ErrorHigh_QBBC->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion90_Xtalk10_QBBC->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion90_Xtalk18_QBBC->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion90_QBBC->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion90_QBBC->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion90_QBBC->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion90_QBBC->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion90_QGSP_BERT = new TGraphAsymmErrors();
  gDepthSim_Pion90_QGSP_BERT->SetMarkerSize(1);
  gDepthSim_Pion90_QGSP_BERT->SetMarkerStyle(20);
  gDepthSim_Pion90_QGSP_BERT->SetMarkerColor(kGreen);
  gDepthSim_Pion90_QGSP_BERT->SetLineColor(kGreen);
  gDepthSim_Pion90_QGSP_BERT->SetFillColor(kGreen);
  gDepthSim_Pion90_QGSP_BERT->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion90_QGSP_BERT->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion90_QGSP_BERT->GetBinContent(ibin);
    double Depth = pDepthSim_Pion90_QGSP_BERT->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion90_ErrorLow_QGSP_BERT->GetBinContent(ibin);
    double content_up = pDepthSim_Pion90_ErrorHigh_QGSP_BERT->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion90_Xtalk10_QGSP_BERT->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion90_Xtalk18_QGSP_BERT->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion90_QGSP_BERT->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion90_QGSP_BERT->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion90_QGSP_BERT->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion90_QGSP_BERT->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //DD4hep
  TFile *f3 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Depth_ShortAsymRange_DD4hep.root");
  TProfile *pDepthSim_Pion90_DD4hep, *pDepthSim_Pion90_ErrorLow_DD4hep, *pDepthSim_Pion90_ErrorHigh_DD4hep, *pDepthSim_Pion90_Xtalk10_DD4hep, *pDepthSim_Pion90_Xtalk18_DD4hep;

  f3->GetObject("Pion_profile90", pDepthSim_Pion90_DD4hep);
  f3->GetObject("Pion_profile90_err_low", pDepthSim_Pion90_ErrorLow_DD4hep);
  f3->GetObject("Pion_profile90_err_high", pDepthSim_Pion90_ErrorHigh_DD4hep);
  f3->GetObject("Pion_profile90_xtalk10", pDepthSim_Pion90_Xtalk10_DD4hep);
  f3->GetObject("Pion_profile90_xtalk18", pDepthSim_Pion90_Xtalk18_DD4hep);

  //QBBC
  TProfile *pDepthSim_Pion90_QBBC_DD4hep, *pDepthSim_Pion90_ErrorLow_QBBC_DD4hep, *pDepthSim_Pion90_ErrorHigh_QBBC_DD4hep, *pDepthSim_Pion90_Xtalk10_QBBC_DD4hep, *pDepthSim_Pion90_Xtalk18_QBBC_DD4hep;

  f3->GetObject("Pion_profile90_QBBC", pDepthSim_Pion90_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_err_low_QBBC", pDepthSim_Pion90_ErrorLow_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_err_high_QBBC", pDepthSim_Pion90_ErrorHigh_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_xtalk10_QBBC", pDepthSim_Pion90_Xtalk10_QBBC_DD4hep);
  f3->GetObject("Pion_profile90_xtalk18_QBBC", pDepthSim_Pion90_Xtalk18_QBBC_DD4hep);

  //QGSP_BERT
  TProfile *pDepthSim_Pion90_QGSP_BERT_DD4hep, *pDepthSim_Pion90_ErrorLow_QGSP_BERT_DD4hep, *pDepthSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep, *pDepthSim_Pion90_Xtalk10_QGSP_BERT_DD4hep, *pDepthSim_Pion90_Xtalk18_QGSP_BERT_DD4hep;

  f3->GetObject("Pion_profile90_QGSP_BERT", pDepthSim_Pion90_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_err_low_QGSP_BERT", pDepthSim_Pion90_ErrorLow_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_err_high_QGSP_BERT", pDepthSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_xtalk10_QGSP_BERT", pDepthSim_Pion90_Xtalk10_QGSP_BERT_DD4hep);
  f3->GetObject("Pion_profile90_xtalk18_QGSP_BERT", pDepthSim_Pion90_Xtalk18_QGSP_BERT_DD4hep);

  //--------------------------------

  TGraphAsymmErrors *gDepthSim_Pion90_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion90_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion90_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion90_DD4hep->SetMarkerColor(kRed);
  gDepthSim_Pion90_DD4hep->SetLineColor(kRed);
  gDepthSim_Pion90_DD4hep->SetFillColor(kRed);
  gDepthSim_Pion90_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion90_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion90_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion90_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion90_ErrorLow_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion90_ErrorHigh_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion90_Xtalk10_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion90_Xtalk18_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion90_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion90_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion90_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion90_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  TGraphAsymmErrors *gDepthSim_Pion90_QBBC_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion90_QBBC_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion90_QBBC_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion90_QBBC_DD4hep->SetMarkerColor(kBlue);
  gDepthSim_Pion90_QBBC_DD4hep->SetLineColor(kBlue);
  gDepthSim_Pion90_QBBC_DD4hep->SetFillColor(kBlue);
  gDepthSim_Pion90_QBBC_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion90_QBBC_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion90_QBBC_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion90_QBBC_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion90_ErrorLow_QBBC_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion90_ErrorHigh_QBBC_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion90_Xtalk10_QBBC_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion90_Xtalk18_QBBC_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion90_QBBC_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion90_QBBC_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion90_QBBC_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion90_QBBC_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TGraphAsymmErrors *gDepthSim_Pion90_QGSP_BERT_DD4hep = new TGraphAsymmErrors();
  gDepthSim_Pion90_QGSP_BERT_DD4hep->SetMarkerSize(1);
  gDepthSim_Pion90_QGSP_BERT_DD4hep->SetMarkerStyle(22);
  gDepthSim_Pion90_QGSP_BERT_DD4hep->SetMarkerColor(kGreen);
  gDepthSim_Pion90_QGSP_BERT_DD4hep->SetLineColor(kGreen);
  gDepthSim_Pion90_QGSP_BERT_DD4hep->SetFillColor(kGreen);
  gDepthSim_Pion90_QGSP_BERT_DD4hep->SetFillStyle(3001);

  ipoint = 0;
  for(int ibin = 1; ibin < pDepthSim_Pion90_QGSP_BERT_DD4hep->GetNbinsX(); ibin++)
  {
    double content = pDepthSim_Pion90_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double Depth = pDepthSim_Pion90_QGSP_BERT_DD4hep->GetXaxis()->GetBinCenter(ibin);

    double content_low = pDepthSim_Pion90_ErrorLow_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_up = pDepthSim_Pion90_ErrorHigh_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double content_Xtalk10 = pDepthSim_Pion90_Xtalk10_QGSP_BERT_DD4hep->GetBinContent(ibin);
    double content_Xtalk18 = pDepthSim_Pion90_Xtalk18_QGSP_BERT_DD4hep->GetBinContent(ibin);

    double error_low = 0.;
    double error_up = 0.;

    double error_Xtalk_low = 0.;
    double error_Xtalk_up = 0.;

    if(content == 0) continue;

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

    double error_stat = pDepthSim_Pion90_QGSP_BERT_DD4hep->GetBinError(ibin);
    double error_syst = 0.01;
    double Depth_err = pDepthSim_Pion90_QGSP_BERT_DD4hep->GetXaxis()->GetBinWidth(ibin)/2;

    gDepthSim_Pion90_QGSP_BERT_DD4hep->SetPoint(ipoint, Depth, content);
    gDepthSim_Pion90_QGSP_BERT_DD4hep->SetPointError(ipoint, Depth_err, Depth_err, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_low*error_low + error_Xtalk_low*error_Xtalk_low), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_up*error_up + error_Xtalk_up*error_Xtalk_up));
    ipoint++;
  }

  //--------------------------------------------------------

  TLegend *leg2 = new TLegend(0.65, 0.65, 0.92, 0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.025);
  leg2->SetHeader("Mokka");
  leg2->AddEntry(gDepthData_Pion90, "Data (stat #oplus syst)", "pf");
  leg2->AddEntry(gDepthSim_Pion90_QGSP_BERT, "QGSP_BERT", "pf");
  leg2->AddEntry(gDepthSim_Pion90, "QGSP_BERT_HP", "pf");
  leg2->AddEntry(gDepthSim_Pion90_QBBC, "QBBC", "pf");

  TLegend *leg3 = new TLegend(0.65, 0.48, 0.92, 0.63);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.025);
  leg3->SetHeader("DD4hep");
  leg3->AddEntry(gDepthSim_Pion90_QGSP_BERT_DD4hep, "QGSP_BERT", "pf");
  leg3->AddEntry(gDepthSim_Pion90_DD4hep, "QGSP_BERT_HP", "pf");
  leg3->AddEntry(gDepthSim_Pion90_QBBC_DD4hep, "QBBC", "pf");

  TPaveText *pt2 = new TPaveText(0.20, 0.70, 0.4, 0.85, "tbNDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(15);
  pt2->SetFillColor(0);
  pt2->SetTextSize(0.04);
  pt2->SetTextAlign(13); //left center
  pt2->AddText("CALICE AHCAL");
  pt2->AddText("Work in progress");
  pt2->AddText("90 GeV #pi^{-} - steel");

  TMultiGraph *multi2 = new TMultiGraph();
  multi2->Add(gDepthData_Pion90);
  multi2->Add(gDepthSim_Pion90);
  multi2->Add(gDepthSim_Pion90_QGSP_BERT);
  multi2->Add(gDepthSim_Pion90_QBBC);
  multi2->Add(gDepthSim_Pion90_DD4hep);
  multi2->Add(gDepthSim_Pion90_QGSP_BERT_DD4hep);
  multi2->Add(gDepthSim_Pion90_QBBC_DD4hep);

  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadTickX(0);

  TCanvas *c2 = new TCanvas("c2", "Timing vs Depth", 800, 600);
  c2->cd();
  multi2->Draw("APX");
  multi2->GetXaxis()->SetTitle("Layer Position [mm]");
  multi2->GetXaxis()->SetRangeUser(50, 850);
  multi2->GetYaxis()->SetTitle("Time of first hit_{[-50, 200]} [ns]");
  multi2->GetYaxis()->SetRangeUser(-2, 10);
  multi2->Draw("E3");
  multi2->Draw("PX");
  pt2->Draw("SAME");
  leg2->Draw("SAME");
  leg3->Draw("SAME");
  TGaxis *axis = new TGaxis(48, 10, 851, 10, 0.02, 4.17, 510, "-");
  axis->SetLabelFont(42);
  axis->SetLabelSize(0.04);
  axis->SetTitleFont(42);
  axis->SetTitleSize(0.04);
  axis->SetTitle("#lambda_{#pi}");
  axis->Draw();

  c2->SaveAs("Plots/ComparisonToSim/Time_Depth_90GeV.pdf");
}

void TimeCorrelations_Mokka()
{
  CaliceStyle();

  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Correlation_ShortAsymRange.root", "OPEN");
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

  //----------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Correlation_ShortAsymRange.root", "OPEN");
  TH2F *hSimPions50_short, *hSimPions50_long;

  f2->GetObject("histo_Pion50_short", hSimPions50_short);
  f2->GetObject("histo_Pion50_long", hSimPions50_long);

  hSimPions50_short->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hSimPions50_short->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hSimPions50_short->SetLineColor(kRed);
  hSimPions50_short->SetLineWidth(2);

  hSimPions50_long->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hSimPions50_long->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hSimPions50_long->SetLineColor(kRed);
  hSimPions50_long->SetLineWidth(2);

  //QBBC
  TH2F *hSimPions50_short_QBBC, *hSimPions50_long_QBBC;

  f2->GetObject("histo_Pion50_short_QBBC", hSimPions50_short_QBBC);
  f2->GetObject("histo_Pion50_long_QBBC", hSimPions50_long_QBBC);

  hSimPions50_short_QBBC->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hSimPions50_short_QBBC->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hSimPions50_short_QBBC->SetLineColor(kBlue);
  hSimPions50_short_QBBC->SetLineWidth(2);

  hSimPions50_long_QBBC->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hSimPions50_long_QBBC->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hSimPions50_long_QBBC->SetLineColor(kBlue);
  hSimPions50_long_QBBC->SetLineWidth(2);

  //QGSP_BERT
  TH2F *hSimPions50_short_QGSP_BERT, *hSimPions50_long_QGSP_BERT;

  f2->GetObject("histo_Pion50_short_QGSP_BERT", hSimPions50_short_QGSP_BERT);
  f2->GetObject("histo_Pion50_long_QGSP_BERT", hSimPions50_long_QGSP_BERT);

  hSimPions50_short_QGSP_BERT->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hSimPions50_short_QGSP_BERT->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hSimPions50_short_QGSP_BERT->SetLineColor(kGreen);
  hSimPions50_short_QGSP_BERT->SetLineWidth(2);

  hSimPions50_long_QGSP_BERT->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hSimPions50_long_QGSP_BERT->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hSimPions50_long_QGSP_BERT->SetLineColor(kGreen);
  hSimPions50_long_QGSP_BERT->SetLineWidth(2);

  //-------------- Quantification -----------------------------------

  cout << "Quantification diagonal" << endl;

  //Data
  //Long
  int nEntries_long = hPions50_long->GetEntries();

  for(int i = 1; i < hPions50_long->GetNbinsX(); i++)
  {
    for(int j = 1; j < hPions50_long->GetNbinsY(); j++)
    {
      float content = hPions50_long->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hPions50_long->SetBinContent(i, j, new_content);
    }
  }

  int low_bin = hPions50_long->GetXaxis()->FindBin(50);
  int high_bin = hPions50_long->GetXaxis()->FindBin(2000);

  hPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  float integral = hPions50_long->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
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

  low_bin = hPions50_short->GetXaxis()->FindBin(50);
  high_bin = hPions50_short->GetXaxis()->FindBin(2000);

  hPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hPions50_short->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //QGSP_BERT_HP
  //Long
  nEntries_long = hSimPions50_long->GetEntries();

  for(int i = 1; i < hSimPions50_long->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_long->GetNbinsY(); j++)
    {
      float content = hSimPions50_long->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hSimPions50_long->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_long->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_long->GetXaxis()->FindBin(2000);

  hSimPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_long->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT_HP Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
  nEntries_short = hSimPions50_short->GetEntries();

  for(int i = 1; i < hSimPions50_short->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_short->GetNbinsY(); j++)
    {
      float content = hSimPions50_short->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hSimPions50_short->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_short->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_short->GetXaxis()->FindBin(2000);

  hSimPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_short->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT_HP Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //QBBC
  //Long
  nEntries_long = hSimPions50_long_QBBC->GetEntries();

  for(int i = 1; i < hSimPions50_long_QBBC->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_long_QBBC->GetNbinsY(); j++)
    {
      float content = hSimPions50_long_QBBC->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hSimPions50_long_QBBC->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_long_QBBC->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_long_QBBC->GetXaxis()->FindBin(2000);

  hSimPions50_long_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_long_QBBC->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QBBC Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
  nEntries_short = hSimPions50_short_QBBC->GetEntries();

  for(int i = 1; i < hSimPions50_short_QBBC->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_short_QBBC->GetNbinsY(); j++)
    {
      float content = hSimPions50_short_QBBC->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hSimPions50_short_QBBC->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_short_QBBC->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_short_QBBC->GetXaxis()->FindBin(2000);

  hSimPions50_short_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_short_QBBC->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QBBC Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //QGSP_BERT
  //Long
  nEntries_long = hSimPions50_long_QGSP_BERT->GetEntries();

  for(int i = 1; i < hSimPions50_long_QGSP_BERT->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_long_QGSP_BERT->GetNbinsY(); j++)
    {
      float content = hSimPions50_long_QGSP_BERT->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hSimPions50_long_QGSP_BERT->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_long_QGSP_BERT->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_long_QGSP_BERT->GetXaxis()->FindBin(2000);

  hSimPions50_long_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_long_QGSP_BERT->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
  nEntries_short = hSimPions50_short_QGSP_BERT->GetEntries();

  for(int i = 1; i < hSimPions50_short_QGSP_BERT->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_short_QGSP_BERT->GetNbinsY(); j++)
    {
      float content = hSimPions50_short_QGSP_BERT->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hSimPions50_short_QGSP_BERT->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_short_QGSP_BERT->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_short_QGSP_BERT->GetXaxis()->FindBin(2000);

  hSimPions50_short_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_short_QGSP_BERT->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //-------------------------------------------

  TPaveText *pt_Data = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_Data->SetBorderSize(0);
  pt_Data->SetTextColor(15);
  pt_Data->SetFillColor(0);
  pt_Data->SetTextSize(0.04);
  pt_Data->SetTextAlign(13); //left center
  pt_Data->AddText("CALICE AHCAL");
  pt_Data->AddText("Work in progress");
  pt_Data->AddText("50 GeV #pi^{-} (Data)");

  //Short Correlation
  //Data
  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  c1->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hPions50_short->Draw("COLZ");
  hPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_Data->Draw("SAME");

  c1->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_Data.pdf");

  TPaveText *pt_HP = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_HP->SetBorderSize(0);
  pt_HP->SetTextColor(15);
  pt_HP->SetFillColor(0);
  pt_HP->SetTextSize(0.04);
  pt_HP->SetTextAlign(13); //left center
  pt_HP->AddText("CALICE AHCAL");
  pt_HP->AddText("Work in progress");
  pt_HP->AddText("50 GeV #pi^{-} (QGSP_BERT_HP)");

  //QGSP_BERT_HP
  TCanvas *c2 = new TCanvas("c2", "", 800, 600);
  c2->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_short->Draw("COLZ");
  hSimPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_HP->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_QGSPBERTHP.pdf");

  TPaveText *pt_QBBC = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_QBBC->SetBorderSize(0);
  pt_QBBC->SetTextColor(15);
  pt_QBBC->SetFillColor(0);
  pt_QBBC->SetTextSize(0.04);
  pt_QBBC->SetTextAlign(13); //left center
  pt_QBBC->AddText("CALICE AHCAL");
  pt_QBBC->AddText("Work in progress");
  pt_QBBC->AddText("50 GeV #pi^{-} (QBBC)");

  //QBBC
  TCanvas *c3 = new TCanvas("c3", "", 800, 600);
  c3->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_short_QBBC->Draw("COLZ");
  hSimPions50_short_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QBBC->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QBBC->Draw("SAME");

  c3->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_QBBC.pdf");

  TPaveText *pt_QGSP = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_QGSP->SetBorderSize(0);
  pt_QGSP->SetTextColor(15);
  pt_QGSP->SetFillColor(0);
  pt_QGSP->SetTextSize(0.04);
  pt_QGSP->SetTextAlign(13); //left center
  pt_QGSP->AddText("CALICE AHCAL");
  pt_QGSP->AddText("Work in progress");
  pt_QGSP->AddText("50 GeV #pi^{-} (QGSP_BERT)");

  //QGSP_BERT
  TCanvas *c4 = new TCanvas("c4", "", 800, 600);
  c4->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_short_QGSP_BERT->Draw("COLZ");
  hSimPions50_short_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QGSP_BERT->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QGSP->Draw("SAME");

  c4->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_QGSPBERT.pdf");

  //Long Correlation
  //Data
  TCanvas *c5 = new TCanvas("c5", "", 800, 600);
  c5->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hPions50_long->Draw("COLZ");
  hPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_Data->Draw("SAME");

  c5->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_Data.pdf");

  //QGSP_BERT_HP
  TCanvas *c6 = new TCanvas("c6", "", 800, 600);
  c6->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_long->Draw("COLZ");
  hSimPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_HP->Draw("SAME");

  c6->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_QGSPBERTHP.pdf");

  //QBBC
  TCanvas *c7 = new TCanvas("c7", "", 800, 600);
  c7->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_long_QBBC->Draw("COLZ");
  hSimPions50_long_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QBBC->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QBBC->Draw("SAME");

  c7->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_QBBC.pdf");

  //QGSP_BERT
  TCanvas *c8 = new TCanvas("c8", "", 800, 600);
  c8->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_long_QGSP_BERT->Draw("COLZ");
  hSimPions50_long_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QGSP_BERT->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QGSP->Draw("SAME");

  c8->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_QGSPBERT.pdf");
}

void TimeCorrelations_DD4hep()
{
  CaliceStyle();

  TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/DataComparisons_LateClusters/Rootfiles/Comparison_Correlation_ShortAsymRange.root", "OPEN");
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

  //----------------------------------------------

  TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/SimComparisons_LateClusters/Rootfiles/Comparison_Correlation_ShortAsymRange_DD4hep.root", "OPEN");
  TH2F *hSimPions50_short, *hSimPions50_long;

  f2->GetObject("histo_Pion50_short", hSimPions50_short);
  f2->GetObject("histo_Pion50_long", hSimPions50_long);

  hSimPions50_short->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hSimPions50_short->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hSimPions50_short->SetLineColor(kRed);
  hSimPions50_short->SetLineWidth(2);

  hSimPions50_long->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hSimPions50_long->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hSimPions50_long->SetLineColor(kRed);
  hSimPions50_long->SetLineWidth(2);

  //QBBC
  TH2F *hSimPions50_short_QBBC, *hSimPions50_long_QBBC;

  f2->GetObject("histo_Pion50_short_QBBC", hSimPions50_short_QBBC);
  f2->GetObject("histo_Pion50_long_QBBC", hSimPions50_long_QBBC);

  hSimPions50_short_QBBC->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hSimPions50_short_QBBC->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hSimPions50_short_QBBC->SetLineColor(kBlue);
  hSimPions50_short_QBBC->SetLineWidth(2);

  hSimPions50_long_QBBC->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hSimPions50_long_QBBC->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hSimPions50_long_QBBC->SetLineColor(kBlue);
  hSimPions50_long_QBBC->SetLineWidth(2);

  //QGSP_BERT
  TH2F *hSimPions50_short_QGSP_BERT, *hSimPions50_long_QGSP_BERT;

  f2->GetObject("histo_Pion50_short_QGSP_BERT", hSimPions50_short_QGSP_BERT);
  f2->GetObject("histo_Pion50_long_QGSP_BERT", hSimPions50_long_QGSP_BERT);

  hSimPions50_short_QGSP_BERT->GetXaxis()->SetTitle("Time of hit (Module 6) [ns]");
  hSimPions50_short_QGSP_BERT->GetYaxis()->SetTitle("Time of closest hit (Module 7) [ns]");
  hSimPions50_short_QGSP_BERT->SetLineColor(kGreen);
  hSimPions50_short_QGSP_BERT->SetLineWidth(2);

  hSimPions50_long_QGSP_BERT->GetXaxis()->SetTitle("Time of hit (Module 13) [ns]");
  hSimPions50_long_QGSP_BERT->GetYaxis()->SetTitle("Time of closest hit (Module 14) [ns]");
  hSimPions50_long_QGSP_BERT->SetLineColor(kGreen);
  hSimPions50_long_QGSP_BERT->SetLineWidth(2);

  //-------------- Quantification -----------------------------------

  cout << "Quantification diagonal" << endl;

  //Data
  //Long
  int nEntries_long = hPions50_long->GetEntries();

  for(int i = 1; i < hPions50_long->GetNbinsX(); i++)
  {
    for(int j = 1; j < hPions50_long->GetNbinsY(); j++)
    {
      float content = hPions50_long->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hPions50_long->SetBinContent(i, j, new_content);
    }
  }

  int low_bin = hPions50_long->GetXaxis()->FindBin(50);
  int high_bin = hPions50_long->GetXaxis()->FindBin(2000);

  hPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  float integral = hPions50_long->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
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

  low_bin = hPions50_short->GetXaxis()->FindBin(50);
  high_bin = hPions50_short->GetXaxis()->FindBin(2000);

  hPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hPions50_short->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //QGSP_BERT_HP
  //Long
  nEntries_long = hSimPions50_long->GetEntries();

  for(int i = 1; i < hSimPions50_long->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_long->GetNbinsY(); j++)
    {
      float content = hSimPions50_long->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hSimPions50_long->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_long->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_long->GetXaxis()->FindBin(2000);

  hSimPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_long->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT_HP Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
  nEntries_short = hSimPions50_short->GetEntries();

  for(int i = 1; i < hSimPions50_short->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_short->GetNbinsY(); j++)
    {
      float content = hSimPions50_short->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hSimPions50_short->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_short->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_short->GetXaxis()->FindBin(2000);

  hSimPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_short->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT_HP Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //QBBC
  //Long
  nEntries_long = hSimPions50_long_QBBC->GetEntries();

  for(int i = 1; i < hSimPions50_long_QBBC->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_long_QBBC->GetNbinsY(); j++)
    {
      float content = hSimPions50_long_QBBC->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hSimPions50_long_QBBC->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_long_QBBC->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_long_QBBC->GetXaxis()->FindBin(2000);

  hSimPions50_long_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_long_QBBC->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QBBC Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
  nEntries_short = hSimPions50_short_QBBC->GetEntries();

  for(int i = 1; i < hSimPions50_short_QBBC->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_short_QBBC->GetNbinsY(); j++)
    {
      float content = hSimPions50_short_QBBC->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hSimPions50_short_QBBC->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_short_QBBC->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_short_QBBC->GetXaxis()->FindBin(2000);

  hSimPions50_short_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_short_QBBC->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QBBC Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //QGSP_BERT
  //Long
  nEntries_long = hSimPions50_long_QGSP_BERT->GetEntries();

  for(int i = 1; i < hSimPions50_long_QGSP_BERT->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_long_QGSP_BERT->GetNbinsY(); j++)
    {
      float content = hSimPions50_long_QGSP_BERT->GetBinContent(i, j);
      float new_content = content / nEntries_long;
      hSimPions50_long_QGSP_BERT->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_long_QGSP_BERT->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_long_QGSP_BERT->GetXaxis()->FindBin(2000);

  hSimPions50_long_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_long_QGSP_BERT->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT Long : " << nEntries_long << " " << integral << " " << (float)integral*100 << "%" << endl;

  //Short
  nEntries_short = hSimPions50_short_QGSP_BERT->GetEntries();

  for(int i = 1; i < hSimPions50_short_QGSP_BERT->GetNbinsX(); i++)
  {
    for(int j = 1; j < hSimPions50_short_QGSP_BERT->GetNbinsY(); j++)
    {
      float content = hSimPions50_short_QGSP_BERT->GetBinContent(i, j);
      float new_content = content / nEntries_short;
      hSimPions50_short_QGSP_BERT->SetBinContent(i, j, new_content);
    }
  }

  low_bin = hSimPions50_short_QGSP_BERT->GetXaxis()->FindBin(50);
  high_bin = hSimPions50_short_QGSP_BERT->GetXaxis()->FindBin(2000);

  hSimPions50_short_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  integral = hSimPions50_short_QGSP_BERT->Integral(low_bin, high_bin, low_bin, high_bin);

  cout << "QGSP_BERT Short : " << nEntries_short << " " << integral << " " << (float)integral*100 << "%" << endl;

  //-------------------------------------------

  TPaveText *pt_Data = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_Data->SetBorderSize(0);
  pt_Data->SetTextColor(15);
  pt_Data->SetFillColor(0);
  pt_Data->SetTextSize(0.04);
  pt_Data->SetTextAlign(13); //left center
  pt_Data->AddText("CALICE AHCAL");
  pt_Data->AddText("Work in progress");
  pt_Data->AddText("50 GeV #pi^{-} (Data)");

  //Short Correlation
  //Data
  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  c1->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hPions50_short->Draw("COLZ");
  hPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  hPions50_short->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_Data->Draw("SAME");

  c1->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_Data.pdf");

  TPaveText *pt_HP = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_HP->SetBorderSize(0);
  pt_HP->SetTextColor(15);
  pt_HP->SetFillColor(0);
  pt_HP->SetTextSize(0.04);
  pt_HP->SetTextAlign(13); //left center
  pt_HP->AddText("CALICE AHCAL");
  pt_HP->AddText("Work in progress");
  pt_HP->AddText("50 GeV #pi^{-} (QGSP_BERT_HP)");

  //QGSP_BERT_HP
  TCanvas *c2 = new TCanvas("c2", "", 800, 600);
  c2->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_short->Draw("COLZ");
  hSimPions50_short->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_HP->Draw("SAME");

  c2->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_QGSPBERTHP_DD4hep.pdf");

  TPaveText *pt_QBBC = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_QBBC->SetBorderSize(0);
  pt_QBBC->SetTextColor(15);
  pt_QBBC->SetFillColor(0);
  pt_QBBC->SetTextSize(0.04);
  pt_QBBC->SetTextAlign(13); //left center
  pt_QBBC->AddText("CALICE AHCAL");
  pt_QBBC->AddText("Work in progress");
  pt_QBBC->AddText("50 GeV #pi^{-} (QBBC)");

  //QBBC
  TCanvas *c3 = new TCanvas("c3", "", 800, 600);
  c3->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_short_QBBC->Draw("COLZ");
  hSimPions50_short_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QBBC->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QBBC->Draw("SAME");

  c3->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_QBBC_DD4hep.pdf");

  TPaveText *pt_QGSP = new TPaveText(0.28, 0.78, 0.53, 0.90, "tbNDC");
  pt_QGSP->SetBorderSize(0);
  pt_QGSP->SetTextColor(15);
  pt_QGSP->SetFillColor(0);
  pt_QGSP->SetTextSize(0.04);
  pt_QGSP->SetTextAlign(13); //left center
  pt_QGSP->AddText("CALICE AHCAL");
  pt_QGSP->AddText("Work in progress");
  pt_QGSP->AddText("50 GeV #pi^{-} (QGSP_BERT)");

  //QGSP_BERT
  TCanvas *c4 = new TCanvas("c4", "", 800, 600);
  c4->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_short_QGSP_BERT->Draw("COLZ");
  hSimPions50_short_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_short_QGSP_BERT->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QGSP->Draw("SAME");

  c4->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_short_QGSPBERT_DD4hep.pdf");

  //Long Correlation
  //Data
  TCanvas *c5 = new TCanvas("c5", "", 800, 600);
  c5->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hPions50_long->Draw("COLZ");
  hPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  hPions50_long->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_Data->Draw("SAME");

  c5->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_Data.pdf");

  //QGSP_BERT_HP
  TCanvas *c6 = new TCanvas("c6", "", 800, 600);
  c6->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_long->Draw("COLZ");
  hSimPions50_long->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_HP->Draw("SAME");

  c6->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_QGSPBERTHP_DD4hep.pdf");

  //QBBC
  TCanvas *c7 = new TCanvas("c7", "", 800, 600);
  c7->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_long_QBBC->Draw("COLZ");
  hSimPions50_long_QBBC->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QBBC->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QBBC->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QBBC->Draw("SAME");

  c7->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_QBBC_DD4hep.pdf");

  //QGSP_BERT
  TCanvas *c8 = new TCanvas("c8", "", 800, 600);
  c8->cd();
  gPad->SetLogz();
  gPad->SetRightMargin(0.12);
  hSimPions50_long_QGSP_BERT->Draw("COLZ");
  hSimPions50_long_QGSP_BERT->GetXaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QGSP_BERT->GetYaxis()->SetRangeUser(-50, 2000);
  hSimPions50_long_QGSP_BERT->GetZaxis()->SetRangeUser(1e-6, 1);
  pt_QGSP->Draw("SAME");

  c8->SaveAs("Plots/ComparisonToSim/Time_Correlation_50GeV_long_QGSPBERT_DD4hep.pdf");
}

void MakePlots()
{
  Energy_10GeV();
  Radius_10GeV();
  Depth_10GeV();

  Energy_30GeV();
  Radius_30GeV();
  Depth_30GeV();

  Energy_50GeV();
  Radius_50GeV();
  Depth_50GeV();

  Energy_70GeV();
  Radius_70GeV();
  Depth_70GeV();

  Energy_90GeV();
  Radius_90GeV();
  Depth_90GeV();

  TimeCorrelations_Mokka();
  TimeCorrelations_DD4hep();
}
