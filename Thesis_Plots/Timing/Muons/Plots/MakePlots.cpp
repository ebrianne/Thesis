void CorrectionOffsets()
{
	CaliceStyle();

	TH1F *hOffset_Before = new TH1F("hOffset_Before", "hOffset_Before", 400, -300, 100);
	hOffset_Before->GetXaxis()->SetTitle("Offset [ns]");
	hOffset_Before->GetYaxis()->SetTitle("# Entries / ns");
	hOffset_Before->SetLineColor(kBlue);
	hOffset_Before->SetLineWidth(2);

	TH1F *hOffset = new TH1F("hOffset", "hOffset", 400, -300, 100);
	hOffset->GetXaxis()->SetTitle("Offset [ns]");
	hOffset->GetYaxis()->SetTitle("# Entries / ns");
	hOffset->SetLineColor(kRed);
	hOffset->SetLineWidth(2);

	map<int, float> m_offsets_odd;
	map<int, float> m_offsets_even;

	ifstream fIn("Rootfiles/Offsets_Cleaned.txt");

	if(fIn.is_open())
	{
		string line;
		while(getline(fIn, line))
		{
			if(line == "" || line.at(0) == '#') continue;
			istringstream iss(line);

			int Chip, BXID, Chn, Mem;
			float Mean, RMS, Mean_err;

			iss >> Chip >> Chn >> Mem >> BXID >> Mean >> Mean_err >> RMS;

			if(RMS == 0 || Mean_err == 0) continue;

			if(BXID == 1)
			m_offsets_odd.insert(make_pair(Chip*10000+Chn*100+Mem, Mean));
			if(BXID == 0)
			m_offsets_even.insert(make_pair(Chip*10000+Chn*100+Mem, Mean));

			hOffset->Fill(Mean);
		}

		fIn.close();
	}
	else
	{
		cout << "Can t open file" << endl;
	}

	ifstream fIn2("Rootfiles/Offsets.txt");

	if(fIn2.is_open())
	{
		string line;
		while(getline(fIn2, line))
		{
			if(line == "" || line.at(0) == '#') continue;
			istringstream iss(line);

			int Chip, BXID, Chn, Mem;
			float Mean, RMS, Mean_err;

			iss >> Chip >> Chn >> Mem >> BXID >> Mean >> Mean_err >> RMS;

			if(RMS == 0 || Mean_err == 0) continue;

			hOffset_Before->Fill(Mean);
		}

		fIn2.close();
	}
	else
	{
		cout << "Can t open file" << endl;
	}

	TLegend *leg = new TLegend(0.6, 0.6, 0.8, 0.7);
	leg->SetHeader("CALICE AHCAL (Muons)");
	leg->AddEntry(hOffset_Before, "First Fit", "f");
	leg->AddEntry(hOffset, "Iteration", "f");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);

	TCanvas *c1 = new TCanvas("c1", "Chip Offsets", 800, 600);
	c1->cd();
	hOffset->GetXaxis()->SetRangeUser(-220, 0);
	hOffset->Draw();
	hOffset_Before->Draw("same");
	leg->Draw("SAME");

	c1->SaveAs("Plots/ExtractedOffsets.pdf");

	//---------------------------------------------------------

	//Plot offset value BXID 0 versus BXID 1
	TH2F *hOffsetOddvsEven = new TH2F("hOffsetOddvsEven", "hOffsetOddvsEven", 250, -250, 0, 250, -250, 0);
	hOffsetOddvsEven->GetXaxis()->SetTitle("Offset BXID even [ns]");
	hOffsetOddvsEven->GetYaxis()->SetTitle("Offset BXID odd [ns]");

	TH1F *hOffsetOddvsEven2 = new TH1F("hOffsetOddvsEven2", "hOffsetOddvsEven2", 100, -50, 50);
	hOffsetOddvsEven2->GetXaxis()->SetTitle("Mem_{BXID0} - Mem_{BXID1} [ns]");
	hOffsetOddvsEven2->GetYaxis()->SetTitle("# Entries / ns");
	hOffsetOddvsEven2->SetFillColor(kBlue);
	hOffsetOddvsEven2->SetLineColor(kBlue);
	hOffsetOddvsEven2->SetFillStyle(3002);

	for(map<int, float>::iterator it = m_offsets_odd.begin(); it != m_offsets_odd.end(); ++it)
	{
		int index = it->first;
		map<int, float>::iterator found = m_offsets_even.find(index);
		if(found != m_offsets_even.end())
		{
			hOffsetOddvsEven->Fill(found->second, it->second);
			hOffsetOddvsEven2->Fill(found->second - it->second);
		}
	}

	TF1 *line = new TF1("line", "x", -250, 0);
	line->SetNpx(300);
	line->SetLineColor(kRed);
	line->SetLineStyle(2);
	line->SetLineWidth(2);

	TCanvas *c2 = new TCanvas("c2", "BXID Offsets", 800, 600);
	c2->cd();
	hOffsetOddvsEven->Draw("COLZ");
	line->Draw("same");

	c2->SaveAs("Plots/CorrelationOffsets_BXID.pdf");

	TCanvas *c3 = new TCanvas("c3", "BXID Offsets difference", 800, 600);
	c3->cd();
	hOffsetOddvsEven2->Draw();

	c3->SaveAs("Plots/MemoryCellDiff_BXID.pdf");
}

map<int, float> m_mapSlope;

void MakeSlopeMap()
{
	ifstream fIn("Rootfiles/TDCslopes_noPreSelection_noBinning.txt");

	if(fIn.is_open())
	{
		string line;
		while(getline(fIn, line))
		{
			if(line == "" || line.at(0) == '#') continue;

			istringstream iss(line);
			int Module, BXID, Chip;
			float Ped, Ped_error, slope, slope_err, slope_deadtime, slope_deadtime_err;

			iss >> Module >> BXID >> Chip >> slope >> slope_err >> slope_deadtime >> slope_deadtime_err >> Ped >> Ped_error;

			m_mapSlope.insert(make_pair(Module*10000+BXID*100+Chip, slope_deadtime));
		}

		fIn.close();
		cout << "Map done!" << endl;
	}
	else
	cout << "Could not make slope, Ped map" << endl;
}

void EdgeDetection()
{
	CaliceStyle();
	MakeSlopeMap();

	TH1F *hslope_BXID0 = new TH1F("hslope_BXID0", "hslope_BXID0", 24, 1.0, 2.2);
	hslope_BXID0->GetXaxis()->SetTitle("slope [ns/TDC]");
	hslope_BXID0->GetYaxis()->SetTitle("Entries / 0.05 ns/TDC");
	hslope_BXID0->SetFillColor(kBlue);
	hslope_BXID0->SetFillStyle(3003);

	TH1F *hslope_BXID1 = new TH1F("hslope_BXID1", "hslope_BXID1", 24, 1.0, 2.2);
	hslope_BXID1->GetXaxis()->SetTitle("slope [ns/TDC]");
	hslope_BXID1->GetYaxis()->SetTitle("Entries / 0.05 ns/TDC");
	hslope_BXID1->SetFillColor(kRed);
	hslope_BXID1->SetFillStyle(3003);

	for(std::map<int, float>::iterator it = m_mapSlope.begin(); it != m_mapSlope.end(); ++it)
	{
		if((it->first%10000)/100 == 0)
		{
			hslope_BXID0->Fill(it->second);
		}
		else
		{
			hslope_BXID1->Fill(it->second);
		}
	}

	cout << "Slopes BXID 0: mean " << hslope_BXID0->GetMean() << " RMS " << hslope_BXID0->GetRMS() << endl;
	cout << "Slopes BXID 1: mean " << hslope_BXID1->GetMean() << " RMS " << hslope_BXID1->GetRMS() << endl;

	TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");

	TLegend *leg3 = new TLegend(0.48, 0.81, 0.68, 0.91);
	leg3->AddEntry(hslope_BXID0, TString::Format("Mean %2.2f ns/TDC, RMS %2.2f (even BXID)", hslope_BXID0->GetMean(), hslope_BXID0->GetRMS()), "f");
	leg3->AddEntry(hslope_BXID1, TString::Format("Mean %2.2f ns/TDC, RMS %2.2f (odd BXID)", hslope_BXID1->GetMean(), hslope_BXID1->GetRMS()), "f");
	leg3->SetBorderSize(0);
	leg3->SetTextSize(0.028);

	TCanvas *c3 = new TCanvas("c3", "Fitted Parameters", 800, 600);
	c3->cd();
	hslope_BXID0->GetYaxis()->SetRangeUser(0, 27);
	hslope_BXID0->Draw();
	hslope_BXID1->Draw("SAME");
	pt->Draw("same");
	leg3->Draw("SAME");

	c3->SaveAs("Plots/SlopesTDC.pdf");

	//Make TDC Spectra

	TFile *f = new TFile("Rootfiles/EdgeDetectionSpectra_noPreSelection_noBinning.root", "OPEN");

	TH1F *hTDC, *hLayer12;

	f->GetObject("Other_Chips/h_TDCSpectra_Layer13_Chip15_BXID0", hTDC);
	f->GetObject("Other_Chips/h_TDCSpectra_Layer12_Chip06_BXID0", hLayer12);

	hTDC->SetLineColor(kBlack);
	hTDC->SetFillColor(kBlue);
	hTDC->SetFillStyle(3002);

	hLayer12->SetLineColor(kBlack);
	hLayer12->SetFillColor(kBlue);
	hLayer12->SetFillStyle(3002);

	TCanvas *c1 = new TCanvas("c1", "Spectra TDC", 800, 600);
	c1->cd();
	gPad->SetLogy();
	hTDC->Draw();
	//pt->Draw("same");

	TCanvas *c2 = new TCanvas("c2", "Strange Spectra TDC", 800, 600);
	c2->cd();
	gPad->SetLogy();
	hLayer12->Draw();
	//pt->Draw("same");

	c1->SaveAs("Plots/ExampleTDCSpectra.pdf");
	c2->SaveAs("Plots/BadTDCSpectra_Layer12.pdf");

	ifstream fIn("Rootfiles/TDCslopes_noPreSelection_noBinning.txt");

	TH1F *hMaxError = new TH1F("hMaxError", "hMaxError", 50, 0, 50);
	hMaxError->SetLineColor(kBlue);
	hMaxError->SetFillColor(kBlue);
	hMaxError->SetFillStyle(3003);
	hMaxError->GetXaxis()->SetTitle("#sigma_{Max} [TDC]");
	hMaxError->GetYaxis()->SetTitle("# Entries");

	if(fIn.is_open())
	{
		string line;
		while(getline(fIn, line))
		{
			if(line == "" || line.at(0) == '#') continue;

			istringstream iss(line);
			int Module, BXID, Chip;
			float slope, slope_err, slope_deadtime, slope_err_deadtime;
			int Ped, Ped_err, Max, Max_err;

			iss >> Module >> BXID >> Chip >> slope >> slope_err >> slope_deadtime >> slope_err_deadtime >> Ped >> Ped_err >> Max >> Max_err;

			if(Module > 2)
			{
				hMaxError->Fill(Max_err);
			}

		}
	}
	else
	{
		cout << "Can t open file" << endl;
		return;
	}

	TPaveText *pt2 = new TPaveText(0.65, 0.82, 0.85, 0.92, "tbNDC");
	pt2->SetBorderSize(0);
	pt2->SetTextColor(15);
	pt2->SetFillColor(0);
	pt2->SetTextSize(0.04);
	pt2->SetTextAlign(13); //left center
	pt2->AddText("CALICE AHCAL");
	pt2->AddText("Work in progress");

	TPaveText *pt3 = new TPaveText(0.65, 0.65, 0.85, 0.8, "tbNDC");
	pt3->SetBorderSize(0);
	pt3->SetTextColor(1);
	pt3->SetFillColor(0);
	pt3->SetTextSize(0.03);
	pt3->SetTextAlign(13); //left center
	pt3->AddText("Muons");
	pt3->AddText(TString::Format("Mean: %2.2f TDC", hMaxError->GetMean()));
	pt3->AddText(TString::Format("RMS: %2.3f TDC", hMaxError->GetRMS()));

	TCanvas *c4 = new TCanvas("c4", "Max Error distribution", 800, 600);
	c4->cd();
	hMaxError->Draw();
	pt2->Draw("SAME");
	pt3->Draw("SAME");

	c4->SaveAs("Plots/MaxErrorDistribution_AHCAL.pdf");
}

void LinearityCorrection()
{
	CaliceStyle();

	TFile * f = new TFile("Rootfiles/ProfilesFit.root", "OPEN");
	TProfile *prof = (TProfile*)f->Get("Timing_Module09_Chip146_BXID0_pfx");

	prof->SetMarkerColor(kBlack);
	prof->SetMarkerStyle(20);
	prof->GetYaxis()->SetRangeUser(-10, 10);

	TFile * f2 = new TFile("Rootfiles/CheckLinearityCorrection.root", "OPEN");
	TProfile *prof_corr = (TProfile*)f2->Get("Timing_Module09_Chip146_BXID0_2D_pfx");
	prof_corr->SetMarkerColor(kBlack);
	prof_corr->SetMarkerStyle(20);
	prof_corr->GetYaxis()->SetRangeUser(-10, 10);

	TFile * f3 = new TFile("Rootfiles/LinearityProfiles.root", "OPEN");
	TH2F *h = (TH2F*)f3->Get("Timing_Module09_Chip146_BXID0");

	h->SetTitle("");

	TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");

	TPaveText *pt2 = new TPaveText(0.62, 0.65, 0.82, 0.92, "tbNDC");
	pt2->SetBorderSize(0);
	pt2->SetTextColor(1);
	pt2->SetFillColor(0);
	pt2->SetTextSize(0.03);
	pt2->SetTextAlign(13); //left center
	pt2->AddText("Module09 / Chip146 / BXID0");
	pt2->AddText(TString::Format("#chi2/ndf: %2.2f/%i", prof->GetFunction("fit")->GetChisquare(), prof->GetFunction("fit")->GetNDF()));
	pt2->AddText(TString::Format("p0: %2.3f #pm %2.3f", prof->GetFunction("fit")->GetParameter(0), prof->GetFunction("fit")->GetParError(0)));
	pt2->AddText(TString::Format("p1: %2.6f #pm %2.6f", prof->GetFunction("fit")->GetParameter(1), prof->GetFunction("fit")->GetParError(1)));
	pt2->AddText(TString::Format("p2: %2.3fe-6 #pm %2.3fe-7", prof->GetFunction("fit")->GetParameter(2)*1e6, prof->GetFunction("fit")->GetParError(2)*1e7));

	TCanvas *c1 = new TCanvas("c1", "Profile TDC linearity", 800, 600);
	c1->cd();
	//h->GetYaxis()->SetRangeUser(-10, 10);
	//h->Draw();
	prof->Draw("same");
	pt->Draw("same");
	pt2->Draw("same");

	c1->SaveAs("Plots/LinearityCorrection_Module09_Chip146_BXID0.pdf");

	TCanvas *c2 = new TCanvas("c2", "Profile Corrected TDC linearity", 800, 600);
	c2->cd();
	//h->GetYaxis()->SetRangeUser(-10, 10);
	//h->Draw();
	prof_corr->Draw("same");

	c2->SaveAs("Plots/LinearityCorrection_Module09_Chip146_BXID0_Corrected.pdf");
}

void Pedestal()
{
	CaliceStyle();

	ifstream fIn("Rootfiles/PedestalExtraction_noBinning.txt");

	TH1F *hPedError = new TH1F("hPedError", "hPedError", 100, 0, 100);
	hPedError->SetLineColor(kBlue);
	hPedError->SetLineWidth(2);
	hPedError->GetXaxis()->SetTitle("#sigma_{Ped} [TDC]");
	hPedError->GetYaxis()->SetTitle("# Entries");

	if(fIn.is_open())
	{
		string line;
		while(getline(fIn, line))
		{
			if(line == "" || line.at(0) == '#') continue;

			istringstream iss(line);
			int Module, BXID, Chip, Chn, Mem, Ped, Ped_err;

			iss >> Module >> Chip >> Chn >> Mem >> Ped >> Ped_err;

			if(Module < 3)
			continue;
			else
			{
				//cout << "Module " << Module << endl;
				hPedError->Fill(Ped_err);
			}
		}
	}
	else
	{
		cout << "Can t open file" << endl;
		return;
	}

	TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");

	TPaveText *pt2 = new TPaveText(0.65, 0.7, 0.85, 0.9, "tbNDC");
	pt2->SetBorderSize(0);
	pt2->SetTextColor(1);
	pt2->SetFillColor(0);
	pt2->SetTextSize(0.03);
	pt2->SetTextAlign(13); //left center
	pt2->AddText("Muons");
	pt2->AddText(TString::Format("Mean: %2.2f TDC", hPedError->GetMean()));
	pt2->AddText(TString::Format("RMS: %2.3f TDC", hPedError->GetRMS()));

	TCanvas *c2 = new TCanvas("c2", "Pedestal Error distribution", 800, 600);
	c2->cd();
	gPad->SetLogy();
	hPedError->Draw();
	pt->Draw("SAME");
	pt2->Draw("SAME");

	c2->SaveAs("Plots/PedestalErrorDistribution_AHCAL.pdf");
}

void TimeWalk()
{
	CaliceStyle();

  TFile *f = new TFile("Rootfiles/TimeWalkFitProfiles.root", "OPEN");
  TProfile *prof;

  f->GetObject("TimeWalkProfile", prof);

  prof->SetMarkerStyle(20);
  prof->SetMarkerColor(kBlack);

  prof->GetFunction("fitFcn")->SetLineStyle(1);
  prof->GetFunction("fitFcn")->SetLineWidth(3);

  TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");

  TPaveText *pt2 = new TPaveText(0.65, 0.69, 0.85, 0.92, "tbNDC");
	pt2->SetBorderSize(0);
	pt2->SetTextColor(1);
	pt2->SetFillColor(0);
	pt2->SetTextSize(0.03);
	pt2->SetTextAlign(13); //left center
	pt2->AddText(TString::Format("#chi2/ndf %2.2f/%2i", prof->GetFunction("fitFcn")->GetChisquare(), prof->GetFunction("fitFcn")->GetNDF()));
	pt2->AddText(TString::Format("a %2.2f #pm %2.2f ns", prof->GetFunction("fitFcn")->GetParameter(0), prof->GetFunction("fitFcn")->GetParError(0)));
	pt2->AddText(TString::Format("b %2.2f #pm %2.2f MIP^{-1}", prof->GetFunction("fitFcn")->GetParameter(1), prof->GetFunction("fitFcn")->GetParError(1)));
	pt2->AddText(TString::Format("c %2.2f #pm %2.2f ns", prof->GetFunction("fitFcn")->GetParameter(2), prof->GetFunction("fitFcn")->GetParError(2)));

  TCanvas *c1 = new TCanvas("c1", "", 800, 600);
  c1->cd();
  prof->Draw();
  pt->Draw("same");
  pt2->Draw("same");

  c1->SaveAs("Plots/TimeWalkProfile.pdf");

  //----------------------------------------------

  TFile *f2 = new TFile("Rootfiles/CheckTimeWalkCorrection.root", "OPEN");
  TProfile *prof_corr;

  f2->GetObject("TimeWalkProfile_Corrected", prof_corr);

  prof_corr->SetMarkerStyle(20);
  prof_corr->SetMarkerColor(kBlack);

  TF1 *line = new TF1("line", "0", 0, 10);
  line->SetLineWidth(3);
  line->SetLineColor(kRed);
  line->SetLineStyle(2);

  TCanvas *c2 = new TCanvas("c2", "", 800, 600);
  c2->cd();
  prof_corr->GetYaxis()->SetRangeUser(-2, 2);
  prof_corr->Draw();
  line->Draw("same");

  c2->SaveAs("Plots/TimeWalkProfile_Correction.pdf");
}

void TimingFull_AHCAL()
{
	CaliceStyle();

	TFile *f = new TFile("Rootfiles/AHCALTiming.root", "OPEN");
	TH1F *h;

	f->GetObject("Timing_AHCAL_Muons", h);
	TF1 *f5 = h->GetFunction("f5");

	float A = f5->GetParameter(0);
	float Mean1 = f5->GetParameter(1);
	float sigma1 = f5->GetParameter(2);
	float B = f5->GetParameter(3);
	float Mean2 = f5->GetParameter(4);
	float sigma2 = f5->GetParameter(5);
	float cst = f5->GetParameter(6);
	float chi2 = f5->GetChisquare()/f5->GetNDF();

	float sigma_err1 = f5->GetParError(2);
	float sigma_err2 = f5->GetParError(5);

	float integral = h->Integral(h->GetXaxis()->FindBin(-50), h->GetXaxis()->FindBin(50), "width");

	//****************************************************************

	// cout << Mean1 << " " << sigma1 << " " << Mean2 << " " << sigma2 << endl;
	// cout << chi2 << endl;
	//
	// cout << "Normalised Constants" << endl;
	// cout << A/integral << " " << Mean1 << " " << sigma1 << " " << B/integral << " " << Mean2 << " " << sigma2 << endl;

	TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
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
	pt2->AddText("All Corrections");
	pt2->AddText("Muons");
	pt2->AddText(TString::Format("Mean: %2.2f, RMS: %2.3f ns", h->GetMean(), h->GetRMS()));
	pt2->AddText(TString::Format("#mu_{1}: %2.3f ns, #sigma_{1}: %2.3f ns", Mean1, sigma1));
	pt2->AddText(TString::Format("#mu_{2}: %2.3f ns, #sigma_{2}: %2.3f ns", Mean2, sigma2));
	pt2->AddText(TString::Format("#chi2: %2.2f", chi2));

	TCanvas *c1 = new TCanvas("c1", "Full AHCAL Timing (Muons)", 800, 600);
	c1->cd();
	//gPad->SetLogy();
	h->Draw();
	pt->Draw("same");
	pt2->Draw("same");

	c1->SaveAs("Plots/Timing_AllLayers.pdf");
}

void TimingFullCorrections()
{
	CaliceStyle();

	static const int NModule = 15;
	TH1F* hAllMem_BXID[NModule];
	float sigma_AllMem_BXID[NModule];
	float sigmasigma_AllMem_BXID[NModule];

	float sigma_AllMem_BXID_RMS[NModule];
	float sigmasigma_AllMem_BXID_RMS[NModule];

	for(int i = 0; i < NModule; i++)
	{
		sigma_AllMem_BXID[i] = 0;
		sigmasigma_AllMem_BXID[i] = 0;

		sigma_AllMem_BXID_RMS[i] = 0;
		sigmasigma_AllMem_BXID_RMS[i] = 0;
	}

	TGraphErrors *graph_AllMem_BXID = new TGraphErrors();
	graph_AllMem_BXID->SetMarkerColor(kRed);
	graph_AllMem_BXID->SetMarkerStyle(20);

	TGraphErrors *graph_AllMem_BXID_RMS = new TGraphErrors();
	graph_AllMem_BXID_RMS->SetMarkerColor(kBlue);
	graph_AllMem_BXID_RMS->SetMarkerStyle(22);

	TF1 *fit = new TF1("fit", "[0] / ( TMath::Sqrt(2.0 * TMath::Pi())*[2] ) * TMath::Exp( -(x-[1])*(x-[1])/(2.*[2]*[2]) ) + [3]", -50, 50);
	fit->SetParNames("A", "mu1", "sigma1", "cst");
	fit->SetLineStyle(2);
	fit->SetLineColor(kRed);

	int iMod = 0;
	//Plots
	TFile *f = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Muons/Data/TimingResolution_FullCorrections/Rootfiles/SingleLayerTiming.root", "OPEN");

	TKey *key;
	TIter next(f->GetListOfKeys());
	while( (key = (TKey*)next()) )
	{
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if (!cl->InheritsFrom("TH1"))
		continue;

		string histoname = key->GetName();
		int Module = atoi(histoname.substr(histoname.find("Module")+6, 2).c_str());

		hAllMem_BXID[Module] = 0;
		sigma_AllMem_BXID[Module] = 0;
		sigmasigma_AllMem_BXID[Module] = 0;

		sigma_AllMem_BXID_RMS[Module] = 0;
		sigmasigma_AllMem_BXID_RMS[Module] = 0;

		hAllMem_BXID[Module] = (TH1F*)f->Get(key->GetName());
		hAllMem_BXID[Module]->GetXaxis()->SetTitle("Time of first hit [ns]");
		hAllMem_BXID[Module]->GetYaxis()->SetTitle("#Entries / ns");
		hAllMem_BXID[Module]->SetLineColor(kBlack);
		hAllMem_BXID[Module]->SetLineWidth(2);
		hAllMem_BXID[Module]->GetXaxis()->SetRangeUser(-50, 50);

		int Maximum = hAllMem_BXID[Module]->GetMaximum();
		int HalfMaximumBinMinus = hAllMem_BXID[Module]->FindFirstBinAbove(Maximum/2, 1);
		int HalfMaximumBinPlus = hAllMem_BXID[Module]->FindLastBinAbove(Maximum/2, 1);

		fit->SetParameter(0, hAllMem_BXID[Module]->Integral());
		fit->SetParameter(1, hAllMem_BXID[Module]->GetXaxis()->GetBinCenter(hAllMem_BXID[Module]->GetMaximumBin()));
		fit->SetParameter(2, hAllMem_BXID[Module]->GetRMS());
		fit->SetParameter(3, 10.);

		hAllMem_BXID[Module]->Fit(fit, "0QEMR", "", hAllMem_BXID[Module]->GetXaxis()->GetBinCenter(HalfMaximumBinMinus),  hAllMem_BXID[Module]->GetXaxis()->GetBinCenter(HalfMaximumBinPlus));

		sigma_AllMem_BXID[Module] = fit->GetParameter(2);
		sigmasigma_AllMem_BXID[Module] = fit->GetParError(2);

		sigma_AllMem_BXID_RMS[Module] = hAllMem_BXID[Module]->GetRMS();
		sigmasigma_AllMem_BXID_RMS[Module] = hAllMem_BXID[Module]->GetRMSError();

		graph_AllMem_BXID->SetPoint(iMod, Module, sigma_AllMem_BXID[Module]);
		graph_AllMem_BXID->SetPointError(iMod, 0, sigmasigma_AllMem_BXID[Module]);

		graph_AllMem_BXID_RMS->SetPoint(iMod, Module, sigma_AllMem_BXID_RMS[Module]);
		graph_AllMem_BXID_RMS->SetPointError(iMod, 0, sigmasigma_AllMem_BXID_RMS[Module]);

		iMod++;
	}

	//Compute Mean resolution
	float sxx = 0.;
	float sxx_RMS = 0.;
	int NMod = 0;
	for(int Module = 3; Module < NModule; Module++)
	{
		if(Module == 11) continue;
		if(sigma_AllMem_BXID[Module] != 0) NMod++;
		sxx += sigma_AllMem_BXID[Module];
		sxx_RMS += sigma_AllMem_BXID_RMS[Module];
	}

	float sigma_comb = sxx/NMod;
	float sigma_comb_RMS = sxx_RMS/NMod;

	cout << "Combinaison: " << sigma_comb << endl;
	cout << "Combinaison (RMS): " << sigma_comb_RMS << endl;

	TF1 *f1 = new TF1("f1", "[0]", 0, 15);
	f1->SetLineColor(kRed);
	f1->SetLineStyle(2);
	f1->SetParameter(0, sigma_comb);

	TF1 *f2 = new TF1("f1_RMS", "[0]", 0, 15);
	f2->SetLineColor(kBlue);
	f2->SetLineStyle(2);
	f2->SetParameter(0, sigma_comb_RMS);

	TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
	leg->SetHeader("AHCAL Muons + All Corrections");
	leg->AddEntry(f1,TString::Format("Mean #sigma = %0.2f ns", sigma_comb), "l");
	leg->AddEntry(f2,TString::Format("Mean RMS = %0.2f ns", sigma_comb_RMS), "l");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);

	TCanvas *c3 = new TCanvas("c3", "Resolution per Module", 800, 600);
	c3->cd();
	graph_AllMem_BXID->Draw("AP");
	graph_AllMem_BXID->GetXaxis()->SetTitle("Module");
	graph_AllMem_BXID->GetYaxis()->SetTitle("Resolution [ns]");
	graph_AllMem_BXID->GetYaxis()->SetRangeUser(0, 20);
	graph_AllMem_BXID_RMS->Draw("P same");
	f1->Draw("SAME");
	f2->Draw("SAME");
	leg->Draw("SAME");

	c3->SaveAs("Plots/ResolutionPerModule_AllCorrection.pdf");
}

void TimingNoCorrections()
{
	CaliceStyle();

	TF1 *fit = new TF1("fit", "[0] / ( TMath::Sqrt(2.0 * TMath::Pi())*[2] ) * TMath::Exp( -(x-[1])*(x-[1])/(2.*[2]*[2]) ) + [3]", -50, 50);
	fit->SetParNames("A", "mu1", "sigma1", "cst");
	fit->SetLineStyle(2);
	fit->SetLineColor(kRed);

	TString histoname = TString::Format("Timing_AHCAL_noCorrections");
	TH1F* hTimingAll = new TH1F(histoname, histoname, 6000, -3000, 3000);
	hTimingAll->SetLineColor(kBlack);
	hTimingAll->SetLineWidth(2);
	hTimingAll->GetXaxis()->SetTitle("Time of first hit [ns]");
	hTimingAll->GetYaxis()->SetTitle("# Entries / ns");

	static const int NModule = 15;
	TH1F* hAllMem_BXID[NModule];
	float sigma_AllMem_BXID[NModule];
	float sigmasigma_AllMem_BXID[NModule];

	float sigma_AllMem_BXID_RMS[NModule];
	float sigmasigma_AllMem_BXID_RMS[NModule];

	TGraphErrors *graph_AllMem_BXID = new TGraphErrors();
	graph_AllMem_BXID->SetMarkerColor(kRed);
	graph_AllMem_BXID->SetMarkerStyle(8);

	TGraphErrors *graph_AllMem_BXID_RMS = new TGraphErrors();
	graph_AllMem_BXID_RMS->SetMarkerColor(kBlue);
	graph_AllMem_BXID_RMS->SetMarkerStyle(8);

	int iMod = 0;
	//Plots
	TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Muons/Data/TimingResolution_noCorrection/Rootfiles/SingleLayerTiming.root", "OPEN");

	TKey *key;
	TIter next(f2->GetListOfKeys());
	while( (key = (TKey*)next()) )
	{
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if (!cl->InheritsFrom("TH1"))
		continue;

		string histoname = key->GetName();
		int Module = atoi(histoname.substr(histoname.find("Module")+6, 2).c_str());

		hAllMem_BXID[Module] = 0;
		sigma_AllMem_BXID[Module] = 0;
		sigmasigma_AllMem_BXID[Module] = 0;

		sigma_AllMem_BXID_RMS[Module] = 0;
		sigmasigma_AllMem_BXID_RMS[Module] = 0;

		hAllMem_BXID[Module] = (TH1F*)f2->Get(key->GetName());
		hAllMem_BXID[Module]->GetXaxis()->SetTitle("Time of first hit [ns]");
		hAllMem_BXID[Module]->GetYaxis()->SetTitle("# Entries / ns");
		hAllMem_BXID[Module]->SetLineColor(kBlack);
		hAllMem_BXID[Module]->SetLineWidth(2);
		hAllMem_BXID[Module]->GetXaxis()->SetRangeUser(-50, 50);

		int Maximum = hAllMem_BXID[Module]->GetMaximum();
		int HalfMaximumBinMinus = hAllMem_BXID[Module]->FindFirstBinAbove(Maximum/2, 1);
		int HalfMaximumBinPlus = hAllMem_BXID[Module]->FindLastBinAbove(Maximum/2, 1);

		fit->SetParameter(0, hAllMem_BXID[Module]->Integral());
		fit->SetParameter(1, hAllMem_BXID[Module]->GetXaxis()->GetBinCenter(hAllMem_BXID[Module]->GetMaximumBin()));
		fit->SetParameter(2, hAllMem_BXID[Module]->GetRMS());
		fit->SetParameter(3, 10.);

		hAllMem_BXID[Module]->Fit(fit, "0QEMR", "", -50,  50);
		sigma_AllMem_BXID[Module] = fit->GetParameter(2);
		sigmasigma_AllMem_BXID[Module] = fit->GetParError(2);

		sigma_AllMem_BXID_RMS[Module] = hAllMem_BXID[Module]->GetRMS();
		sigmasigma_AllMem_BXID_RMS[Module] = hAllMem_BXID[Module]->GetRMSError();

		graph_AllMem_BXID->SetPoint(iMod, Module, sigma_AllMem_BXID[Module]);
		graph_AllMem_BXID->SetPointError(iMod, 0, sigmasigma_AllMem_BXID[Module]);

		graph_AllMem_BXID_RMS->SetPoint(iMod, Module, sigma_AllMem_BXID_RMS[Module]);
		graph_AllMem_BXID_RMS->SetPointError(iMod, 0, sigmasigma_AllMem_BXID_RMS[Module]);

		iMod++;

		//------------------------------------

		if(Module != 11)
		hTimingAll->Add(hAllMem_BXID[Module], 1);
	}

	//Compute Mean resolution
	float sxx = 0.;
	float sxx_RMS = 0.;
	int Mod = 0;
	for(int Module = 3; Module < NModule; Module++)
	{
		if(Module == 11) continue;
		if(sigma_AllMem_BXID[Module] != 0) Mod++;
		sxx += sigma_AllMem_BXID[Module];
		sxx_RMS += sigma_AllMem_BXID_RMS[Module];
	}

	float sigma_comb = sxx/Mod;
	float sigma_comb_RMS = sxx_RMS/Mod;

	cout << "Combinaison gauss: " << sigma_comb << endl;
	cout << "Combinaison RMS: " << sigma_comb_RMS << endl;

	TF1 *f1 = new TF1("f1", "[0]", 0, 15);
	f1->SetLineColor(kRed);
	f1->SetLineStyle(2);
	f1->SetParameter(0, sigma_comb);

	TF1 *f1_RMS = new TF1("f1_RMS", "[0]", 0, 15);
	f1_RMS->SetLineColor(kBlue);
	f1_RMS->SetLineStyle(2);
	f1_RMS->SetParameter(0, sigma_comb_RMS);

	TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");

	TLegend *leg = new TLegend(0.2, 0.60, 0.5, 0.75);
	leg->SetHeader("Muons (Simple Calibration)");
	leg->AddEntry(f1,TString::Format("Mean #sigma = %2.2f ns", sigma_comb), "l");
	leg->AddEntry(f1_RMS,TString::Format("Mean RMS = %2.2f ns", sigma_comb_RMS), "l");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);

	TCanvas *c3 = new TCanvas("c3", "Resolution per Module", 800, 600);
	c3->cd();
	graph_AllMem_BXID->Draw("AP");
	graph_AllMem_BXID->GetXaxis()->SetTitle("Layer");
	graph_AllMem_BXID->GetYaxis()->SetTitle("Resolution [ns]");
	graph_AllMem_BXID->GetYaxis()->SetRangeUser(0, 20);
	graph_AllMem_BXID_RMS->Draw("P same");
	f1->Draw("SAME");
	f1_RMS->Draw("SAME");
	leg->Draw("SAME");
	pt->Draw("same");

	c3->SaveAs("Plots/ResolutionPerModule_noCorrections.pdf");

	TPaveText *pt2 = new TPaveText(0.65, 0.65, 0.85, 0.92, "tbNDC");
	pt2->SetBorderSize(0);
	pt2->SetTextColor(1);
	pt2->SetFillColor(0);
	pt2->SetTextSize(0.04);
	pt2->SetTextAlign(13); //left center
	pt2->AddText("Simple Calibration");
	pt2->AddText("Muons");
	pt2->AddText(TString::Format("Mean %2.2f ns", hTimingAll->GetMean()));
	pt2->AddText(TString::Format("RMS = %2.2f ns", hTimingAll->GetRMS()));

	TCanvas *c4 = new TCanvas("c4", "Timing no Corrections", 800, 600);
	hTimingAll->GetXaxis()->SetRangeUser(-50, 50);
	hTimingAll->Draw();
	pt2->Draw("SAME");
	pt->Draw("same");

	c4->SaveAs("Plots/Timing_AHCAL_noCorrections.pdf");
}

void TimingLinCorrections()
{
	CaliceStyle();

	TF1 *fit = new TF1("fit", "[0] / ( TMath::Sqrt(2.0 * TMath::Pi())*[2] ) * TMath::Exp( -(x-[1])*(x-[1])/(2.*[2]*[2]) ) + [3]", -50, 50);
	fit->SetParNames("A", "mu1", "sigma1", "cst");
	fit->SetLineStyle(2);
	fit->SetLineColor(kRed);

	TString histoname = TString::Format("Timing_AHCAL_LinCorrection");
	TH1F* hTimingAll = new TH1F(histoname, histoname, 6000, -3000, 3000);
	hTimingAll->SetLineColor(kBlack);
	hTimingAll->SetLineWidth(2);
	hTimingAll->GetXaxis()->SetTitle("Time of first hit [ns]");
	hTimingAll->GetYaxis()->SetTitle("# Entries / ns");

	static const int NModule = 15;
	TH1F* hAllMem_BXID[NModule];
	float sigma_AllMem_BXID[NModule];
	float sigmasigma_AllMem_BXID[NModule];

	float sigma_AllMem_BXID_RMS[NModule];
	float sigmasigma_AllMem_BXID_RMS[NModule];

	TGraphErrors *graph_AllMem_BXID = new TGraphErrors();
	graph_AllMem_BXID->SetMarkerColor(kRed);
	graph_AllMem_BXID->SetMarkerStyle(8);

	TGraphErrors *graph_AllMem_BXID_RMS = new TGraphErrors();
	graph_AllMem_BXID_RMS->SetMarkerColor(kBlue);
	graph_AllMem_BXID_RMS->SetMarkerStyle(8);

	int iMod = 0;
	//Plots
	TFile *f2 = new TFile("/afs/desy.de/group/flc/pool/ebrianne/Projects/AHCAL/Testbeam_July2015/Data_Analysis/Timing/Muons/Data/TimingResolution_noTW/Rootfiles/SingleLayerTiming.root", "OPEN");

	TKey *key;
	TIter next(f2->GetListOfKeys());
	while( (key = (TKey*)next()) )
	{
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if (!cl->InheritsFrom("TH1"))
		continue;

		string histoname = key->GetName();
		int Module = atoi(histoname.substr(histoname.find("Module")+6, 2).c_str());

		hAllMem_BXID[Module] = 0;
		sigma_AllMem_BXID[Module] = 0;
		sigmasigma_AllMem_BXID[Module] = 0;

		sigma_AllMem_BXID_RMS[Module] = 0;
		sigmasigma_AllMem_BXID_RMS[Module] = 0;

		hAllMem_BXID[Module] = (TH1F*)f2->Get(key->GetName());
		hAllMem_BXID[Module]->GetXaxis()->SetTitle("Time of first hit [ns]");
		hAllMem_BXID[Module]->GetYaxis()->SetTitle("# Entries / ns");
		hAllMem_BXID[Module]->SetLineColor(kBlack);
		hAllMem_BXID[Module]->SetLineWidth(2);
		hAllMem_BXID[Module]->GetXaxis()->SetRangeUser(-50, 50);

		int Maximum = hAllMem_BXID[Module]->GetMaximum();
		int HalfMaximumBinMinus = hAllMem_BXID[Module]->FindFirstBinAbove(Maximum/2, 1);
		int HalfMaximumBinPlus = hAllMem_BXID[Module]->FindLastBinAbove(Maximum/2, 1);

		fit->SetParameter(0, hAllMem_BXID[Module]->Integral());
		fit->SetParameter(1, hAllMem_BXID[Module]->GetXaxis()->GetBinCenter(hAllMem_BXID[Module]->GetMaximumBin()));
		fit->SetParameter(2, hAllMem_BXID[Module]->GetRMS());
		fit->SetParameter(3, 10.);

		hAllMem_BXID[Module]->Fit(fit, "0QEMR", "", -50,  50);
		sigma_AllMem_BXID[Module] = fit->GetParameter(2);
		sigmasigma_AllMem_BXID[Module] = fit->GetParError(2);

		sigma_AllMem_BXID_RMS[Module] = hAllMem_BXID[Module]->GetRMS();
		sigmasigma_AllMem_BXID_RMS[Module] = hAllMem_BXID[Module]->GetRMSError();

		graph_AllMem_BXID->SetPoint(iMod, Module, sigma_AllMem_BXID[Module]);
		graph_AllMem_BXID->SetPointError(iMod, 0, sigmasigma_AllMem_BXID[Module]);

		graph_AllMem_BXID_RMS->SetPoint(iMod, Module, sigma_AllMem_BXID_RMS[Module]);
		graph_AllMem_BXID_RMS->SetPointError(iMod, 0, sigmasigma_AllMem_BXID_RMS[Module]);

		iMod++;

		if(Module != 11)
		hTimingAll->Add(hAllMem_BXID[Module], 1);
	}

	//Compute Mean resolution
	float sxx = 0.;
	float sxx_RMS = 0.;
	int Mod = 0;
	for(int Module = 3; Module < NModule; Module++)
	{
		if(Module == 11) continue;
		if(sigma_AllMem_BXID[Module] != 0) Mod++;
		sxx += sigma_AllMem_BXID[Module];
		sxx_RMS += sigma_AllMem_BXID_RMS[Module];
	}

	float sigma_comb = sxx/Mod;
	float sigma_comb_RMS = sxx_RMS/Mod;

	cout << "Combinaison gauss: " << sigma_comb << endl;
	cout << "Combinaison RMS: " << sigma_comb_RMS << endl;

	TF1 *f1 = new TF1("f1", "[0]", 0, 15);
	f1->SetLineColor(kRed);
	f1->SetLineStyle(2);
	f1->SetParameter(0, sigma_comb);

	TF1 *f1_RMS = new TF1("f1_RMS", "[0]", 0, 15);
	f1_RMS->SetLineColor(kBlue);
	f1_RMS->SetLineStyle(2);
	f1_RMS->SetParameter(0, sigma_comb_RMS);

	TPaveText *pt = new TPaveText(0.2, 0.82, 0.5, 0.92, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.04);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");

	TLegend *leg = new TLegend(0.2, 0.60, 0.5, 0.75);
	leg->SetHeader("Muons + Lin. Correction");
	leg->AddEntry(f1,TString::Format("Mean #sigma = %0.2f ns", sigma_comb), "l");
	leg->AddEntry(f1_RMS,TString::Format("Mean RMS = %0.2f ns", sigma_comb_RMS), "l");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04);

	TCanvas *c3 = new TCanvas("c3", "Resolution per Module", 800, 600);
	c3->cd();
	graph_AllMem_BXID->Draw("AP");
	graph_AllMem_BXID->GetXaxis()->SetTitle("Layer");
	graph_AllMem_BXID->GetYaxis()->SetTitle("Resolution [ns]");
	graph_AllMem_BXID->GetYaxis()->SetRangeUser(0, 20);
	graph_AllMem_BXID_RMS->Draw("P same");
	f1->Draw("SAME");
	f1_RMS->Draw("SAME");
	leg->Draw("SAME");
	pt->Draw("same");

	c3->SaveAs("Plots/ResolutionPerModule_LinCorrection.pdf");

	TPaveText *pt2 = new TPaveText(0.65, 0.65, 0.85, 0.92, "tbNDC");
	pt2->SetBorderSize(0);
	pt2->SetTextColor(1);
	pt2->SetFillColor(0);
	pt2->SetTextSize(0.03);
	pt2->SetTextAlign(13); //left center
	pt2->AddText("Non-Linearity Correction");
	pt2->AddText("Muons");
	pt2->AddText(TString::Format("Mean %2.2f ns", hTimingAll->GetMean()));
	pt2->AddText(TString::Format("RMS = %2.2f ns", hTimingAll->GetRMS()));

	TCanvas *c4 = new TCanvas("c4", "Timing Lin Correction", 800, 600);
	hTimingAll->GetXaxis()->SetRangeUser(-50, 50);
	hTimingAll->Draw();
	pt2->Draw("SAME");
	pt->Draw("same");

	c4->SaveAs("Plots/Timing_AHCAL_LinCorrection.pdf");
}

void SelectionCuts()
{
	CaliceStyle();

  TFile *f = new TFile("Rootfiles/SelectionCuts.root", "OPEN");
  TH2F *hnHitsCoGZ_Muons, *hnHitsCoGZ_Electrons, *hnHitsCoGZ_Pions;

  f->GetObject("hnHitsCoGZ_Muons", hnHitsCoGZ_Muons);
  f->GetObject("hnHitsCoGZ_Electrons", hnHitsCoGZ_Electrons);
  f->GetObject("hnHitsCoGZ_Pions", hnHitsCoGZ_Pions);

  hnHitsCoGZ_Muons->SetLineColor(kBlue);
  hnHitsCoGZ_Muons->SetLineWidth(2);
  hnHitsCoGZ_Muons->GetXaxis()->SetTitle("AHCAL CoG Z [mm]");
  hnHitsCoGZ_Muons->GetYaxis()->SetTitle("nHits");

  hnHitsCoGZ_Electrons->SetLineColor(kGreen);
  hnHitsCoGZ_Electrons->SetLineWidth(2);

  hnHitsCoGZ_Pions->SetLineColor(kRed);
  hnHitsCoGZ_Pions->SetLineWidth(2);

  TLine *line = new TLine();
  line->SetX1(0.);
  line->SetX2(800.);
  line->SetY1(20.);
  line->SetY2(20);
  line->SetLineColor(kBlack);
  line->SetLineWidth(3);

  TLine *line2 = new TLine();
  line2->SetX1(800.);
  line2->SetX2(800.);
  line2->SetY1(0.);
  line2->SetY2(20.);
  line2->SetLineColor(kBlack);
  line2->SetLineWidth(3);

  TLine *line3 = new TLine();
  line3->SetX1(0.);
  line3->SetX2(0.);
  line3->SetY1(0.);
  line3->SetY2(20.);
  line3->SetLineColor(kBlack);
  line3->SetLineWidth(3);

  TLegend *leg = new TLegend(0.62, 0.70, 0.90, 0.92);
  leg->SetHeader("AHCAL Simulation");
  leg->AddEntry(hnHitsCoGZ_Muons, "Muons", "l");
  leg->AddEntry(hnHitsCoGZ_Electrons, "Electrons", "l");
  leg->AddEntry(hnHitsCoGZ_Pions, "Pions", "l");
  leg->AddEntry(line, "MIP Preselection", "l");

  TCanvas *c1 = new TCanvas("c1", "nHits vs CoG Z", 800, 600);
  hnHitsCoGZ_Muons->Draw("BOX");
  hnHitsCoGZ_Electrons->Draw("BOX same");
  hnHitsCoGZ_Pions->Draw("BOX same");
  line->Draw("same");
  line2->Draw("same");
  line3->Draw("same");
  leg->Draw("same");

  c1->SaveAs("Plots/SelectionCut_nHitsCoGZ_Muons.pdf");

  //------------------ TrackFinder Cuts ---------------------

  TH1F *hHitsTrack_Muons_SSF, *hHitsTrack_Muons_BL, *hHitsTrack_Electrons, *hHitsTrack_Pions;

  f->GetObject("hHitsTrack_Muons_SSF", hHitsTrack_Muons_SSF);
  f->GetObject("hHitsTrack_Muons_BL", hHitsTrack_Muons_BL);
  f->GetObject("hHitsTrack_Electrons", hHitsTrack_Electrons);
  f->GetObject("hHitsTrack_Pions", hHitsTrack_Pions);

  hHitsTrack_Muons_SSF->SetLineColor(kBlue);
  hHitsTrack_Muons_SSF->SetLineWidth(2);
  hHitsTrack_Muons_SSF->GetXaxis()->SetTitle("Number of hits in Track");
  hHitsTrack_Muons_SSF->GetYaxis()->SetTitle("Fraction of Events");
  hHitsTrack_Muons_SSF->Scale(1./87139);
  hHitsTrack_Muons_SSF->GetYaxis()->SetRangeUser(0, 1.1);

  hHitsTrack_Muons_BL->SetLineColor(kBlue);
  hHitsTrack_Muons_BL->SetLineWidth(2);
  hHitsTrack_Muons_BL->SetLineStyle(2);
  hHitsTrack_Muons_BL->GetXaxis()->SetTitle("Number of hits in Track");
  hHitsTrack_Muons_BL->GetYaxis()->SetTitle("Fraction of Events");
  hHitsTrack_Muons_BL->Scale(1./70322);
  hHitsTrack_Muons_BL->GetYaxis()->SetRangeUser(0, 1.1);

  hHitsTrack_Electrons->SetLineColor(kGreen);
  hHitsTrack_Electrons->SetLineWidth(2);
  hHitsTrack_Electrons->Scale(1./100000);

  hHitsTrack_Pions->SetLineColor(kRed);
  hHitsTrack_Pions->SetLineWidth(2);
  hHitsTrack_Pions->Scale(1./100000);

  TH1F *hHitsPerLayer_Muons_SSF, *hHitsPerLayer_Muons_BL, *hHitsPerLayer_Electrons, *hHitsPerLayer_Pions;

  f->GetObject("hHitsPerLayer_Muons_SSF", hHitsPerLayer_Muons_SSF);
  f->GetObject("hHitsPerLayer_Muons_BL", hHitsPerLayer_Muons_BL);
  f->GetObject("hHitsPerLayer_Electrons", hHitsPerLayer_Electrons);
  f->GetObject("hHitsPerLayer_Pions", hHitsPerLayer_Pions);

  hHitsPerLayer_Muons_SSF->SetLineColor(kBlue);
  hHitsPerLayer_Muons_SSF->SetLineWidth(2);
  hHitsPerLayer_Muons_SSF->GetXaxis()->SetTitle("Number of hits in a layer");
  hHitsPerLayer_Muons_SSF->GetYaxis()->SetTitle("Fraction of Towers");
  hHitsPerLayer_Muons_SSF->Scale(1./87584);
  hHitsPerLayer_Muons_SSF->GetYaxis()->SetRangeUser(0, 1.1);
  hHitsPerLayer_Muons_SSF->GetXaxis()->SetRangeUser(0, 7);

  hHitsPerLayer_Muons_BL->SetLineColor(kBlue);
  hHitsPerLayer_Muons_BL->SetLineWidth(2);
  hHitsPerLayer_Muons_BL->SetLineStyle(2);
  hHitsPerLayer_Muons_BL->GetXaxis()->SetTitle("Number of hits in a layer");
  hHitsPerLayer_Muons_BL->GetYaxis()->SetTitle("Fraction of Towers");
  hHitsPerLayer_Muons_BL->Scale(1./70609);
  hHitsPerLayer_Muons_BL->GetYaxis()->SetRangeUser(0, 1.1);

  hHitsPerLayer_Electrons->SetLineColor(kGreen);
  hHitsPerLayer_Electrons->SetLineWidth(2);
  hHitsPerLayer_Electrons->Scale(1./100000);

  hHitsPerLayer_Pions->SetLineColor(kRed);
  hHitsPerLayer_Pions->SetLineWidth(2);
  hHitsPerLayer_Pions->Scale(1./100000);

  TLegend *leg2 = new TLegend(0.65, 0.7, 0.90, 0.92);
  leg2->SetHeader("AHCAL Simulation");
  leg2->AddEntry(hHitsTrack_Muons_SSF, "Muons (Inner 12 #times 12)", "l");
  leg2->AddEntry(hHitsTrack_Muons_BL, "Muons (Outer BL)", "l");
  leg2->AddEntry(hHitsTrack_Electrons, "Electrons", "l");
  leg2->AddEntry(hHitsTrack_Pions, "Pions", "l");

  TLine *line4_SSF = new TLine();
  line4_SSF->SetX1(7.5);
  line4_SSF->SetX2(7.5);
  line4_SSF->SetY1(0.);
  line4_SSF->SetY2(1.1);
  line4_SSF->SetLineColor(kBlack);
  line4_SSF->SetLineWidth(3);

  TLine *line4_BL = new TLine();
  line4_BL->SetX1(2.5);
  line4_BL->SetX2(2.5);
  line4_BL->SetY1(0.);
  line4_BL->SetY2(1.1);
  line4_BL->SetLineColor(kBlack);
  line4_BL->SetLineWidth(3);
  line4_BL->SetLineStyle(2);

  TCanvas *c2 = new TCanvas("c2", "nHits on Track", 800, 600);
  hHitsTrack_Muons_SSF->Draw("hist");
  hHitsTrack_Muons_BL->Draw("hist same");
  hHitsTrack_Electrons->Draw("hist same");
  hHitsTrack_Pions->Draw("hist same");
  line4_SSF->Draw("same");
  line4_BL->Draw("same");
  leg2->Draw("same");

  c2->SaveAs("Plots/TrackFinderCut_nHitsTrack_Muons.pdf");

  TLine *line5 = new TLine();
  line5->SetX1(2.5);
  line5->SetX2(2.5);
  line5->SetY1(0.);
  line5->SetY2(1.1);
  line5->SetLineColor(kBlack);
  line5->SetLineWidth(3);

  TCanvas *c3 = new TCanvas("c3", "nHits per layer", 800, 600);
  hHitsPerLayer_Muons_SSF->Draw("hist");
  hHitsPerLayer_Muons_BL->Draw("hist same");
  hHitsPerLayer_Electrons->Draw("hist same");
  hHitsPerLayer_Pions->Draw("hist same");
  line5->Draw("same");
  leg2->Draw("same");

  c3->SaveAs("Plots/TrackFinderCut_nHitsLayer_Muons.pdf");
}

void Validation()
{
	CaliceStyle();

	TFile *f = new TFile("Rootfiles/ValidationMuons.root", "OPEN");
	TGraphErrors *data, *Mokka, *DD4hep;

	f->GetObject("profileData", data);
	f->GetObject("profileDD4hep", DD4hep);
	f->GetObject("profileMokka", Mokka);

	data->SetLineColor(kBlack);
	data->SetLineWidth(2);
	data->SetMarkerColor(kBlack);
	data->SetMarkerStyle(20);

	Mokka->SetLineColor(kRed);
	Mokka->SetLineWidth(2);
	Mokka->SetMarkerColor(kRed);
	Mokka->SetMarkerStyle(21);

	DD4hep->SetLineColor(kBlue);
	DD4hep->SetLineWidth(2);
	DD4hep->SetMarkerColor(kBlue);
	DD4hep->SetMarkerStyle(22);

	//------------------------

	TGraphErrors *ratioData = new TGraphErrors();
	TGraphErrors *ratioMokka = new TGraphErrors();
	TGraphErrors *ratioDD4hep = new TGraphErrors();

	for(int i = 0; i < data->GetN(); i++)
	{
		double x, y, y1, y2;
		float Meandata = data->GetPoint(i, x, y);
		float MeanMokka = Mokka->GetPoint(i, x, y1);
		float MeanDD4hep = DD4hep->GetPoint(i, x, y2);

		ratioData->SetPoint(i, x, y/y);
		ratioMokka->SetPoint(i, x, y1/y);
		ratioDD4hep->SetPoint(i, x, y2/y);
	}

	ratioData->SetLineColor(kBlack);
	ratioData->SetMarkerColor(kBlack);
	ratioData->SetLineWidth(2);
	ratioData->SetMarkerStyle(20);

	ratioMokka->SetLineColor(kRed);
	ratioMokka->SetLineWidth(2);
	ratioMokka->SetMarkerColor(kRed);
	ratioMokka->SetMarkerStyle(21);

	ratioDD4hep->SetLineColor(kBlue);
	ratioDD4hep->SetLineWidth(2);
	ratioDD4hep->SetMarkerColor(kBlue);
	ratioDD4hep->SetMarkerStyle(22);

	double sFactor = 0.60;

	TLegend* leg3 = new TLegend(0.6, 0.5, 0.9, 0.8);
	leg3->AddEntry(data, "Data", "p");
	leg3->AddEntry(Mokka, "Mokka (QGSP_BERT)", "p");
	leg3->AddEntry(DD4hep, "DD4hep (QGSP_BERT)", "p");

	TPaveText *pt = new TPaveText(0.2, 0.6, 0.45, 0.8, "tbNDC");
	pt->SetBorderSize(0);
	pt->SetTextColor(15);
	pt->SetFillColor(0);
	pt->SetTextSize(0.06);
	pt->SetTextAlign(13); //left center
	pt->AddText("CALICE AHCAL");
	pt->AddText("Work in progress");
	pt->AddText("150 GeV Muons");

	TMultiGraph *multi = new TMultiGraph();
	multi->Add(data);
	multi->Add(Mokka);
	multi->Add(DD4hep);

	TMultiGraph *multi2 = new TMultiGraph();
	multi2->Add(ratioData);
	multi2->Add(ratioMokka);
	multi2->Add(ratioDD4hep);

	TCanvas *c;
	TPad *pad1, *pad2;
	setupPadsTopBottom(c, "c", "c", pad1, pad2, sFactor, 800, 600);
	setupAxisScalingTop(data, sFactor);
	setupAxisScalingBottom(ratioData, sFactor);
	pad1->cd();
	multi->Draw("AP");
	multi->GetXaxis()->SetTitle("Module");
	multi->GetYaxis()->SetTitle("<E_{dep}> [MIP]");
	multi->GetYaxis()->SetRangeUser(0.5, 5);
	multi->GetXaxis()->SetRangeUser(3, 14);
	multi->GetYaxis()->SetNdivisions(8, 5, 0);
	multi->GetYaxis()->SetLabelSize(0.05);
	leg3->Draw("same");
	pt->Draw("same");
	gPad->Modified();
	pad2->cd();
	multi2->Draw("APL");
	multi2->GetXaxis()->SetTitle("Module");
	multi2->GetXaxis()->SetLabelSize(0.07);
	multi2->GetXaxis()->SetTitleSize(0.07);
	multi2->GetXaxis()->SetTitleOffset(1.3);
	multi2->GetYaxis()->SetTitle("MC/Data");
	multi2->GetYaxis()->SetRangeUser(0.8, 1.2);
	multi2->GetXaxis()->SetRangeUser(3, 14);
	multi2->GetYaxis()->SetNdivisions(5, 5, 0);
	multi2->GetYaxis()->SetLabelSize(0.07);
	multi2->GetYaxis()->SetTitleSize(0.07);
	multi2->GetYaxis()->SetTitleOffset(0.7);
	gPad->Modified();

	c->SaveAs("Plots/ProfileMuons_Edep.pdf");

	//-------------------------------

	TH1F *hEvisMokka, *hEvisDD4hep, *hEvisData;

	f->GetObject("hEvisMokka", hEvisMokka);
	f->GetObject("hEvisDD4hep", hEvisDD4hep);
	f->GetObject("hEvisData", hEvisData);

	hEvisMokka->SetLineColor(kRed);
	hEvisMokka->SetLineWidth(2);
	hEvisMokka->SetFillColor(kRed);
	hEvisMokka->SetFillStyle(3001);
	hEvisMokka->Scale(1./hEvisMokka->Integral("width"));

	hEvisDD4hep->SetLineColor(kBlue);
	hEvisDD4hep->SetLineWidth(2);
	hEvisDD4hep->SetFillColor(kBlue);
	hEvisDD4hep->SetFillStyle(3001);
	hEvisDD4hep->Scale(1./hEvisDD4hep->Integral("width"));

	hEvisData->SetLineColor(kBlack);
	hEvisData->SetLineWidth(2);
	hEvisData->Scale(1./hEvisData->Integral("width"));

	gStyle->SetOptStat(1110);
	hEvisData->SetStats(1);
	hEvisMokka->SetStats(1);
	hEvisDD4hep->SetStats(1);

	TCanvas *c2 = new TCanvas("c2", "Evis", 800, 600);
	hEvisData->Draw();
	hEvisData->GetXaxis()->SetRangeUser(1, 50);
	hEvisData->GetYaxis()->SetRangeUser(0, 0.1);
	hEvisData->GetXaxis()->SetTitle("E_{vis} [MIP]");
	hEvisData->GetYaxis()->SetTitle("Fraction of events");
	hEvisMokka->Draw("sames");
	hEvisDD4hep->Draw("sames");
	hEvisData->Draw("same");
	gPad->Update();
	TPaveStats *st = (TPaveStats*)hEvisData->GetListOfFunctions()->FindObject("stats");
	st->SetX1NDC(0.7);
	st->SetX2NDC(0.9);
	st->SetY1NDC(0.75);
	st->SetY2NDC(0.9);
	st->SetLineColor(kBlack);
	st->SetTextColor(kBlack);
	TPaveStats *st2 = (TPaveStats*)hEvisMokka->GetListOfFunctions()->FindObject("stats");
	st2->SetX1NDC(0.7);
	st2->SetX2NDC(0.9);
	st2->SetY1NDC(0.55);
	st2->SetY2NDC(0.70);
	st2->SetLineColor(kRed);
	st2->SetTextColor(kRed);
	TPaveStats *st3 = (TPaveStats*)hEvisDD4hep->GetListOfFunctions()->FindObject("stats");
	st3->SetX1NDC(0.7);
	st3->SetX2NDC(0.9);
	st3->SetY1NDC(0.35);
	st3->SetY2NDC(0.5);
	st3->SetLineColor(kBlue);
	st3->SetTextColor(kBlue);
	gPad->Modified();

	c2->SaveAs("Plots/Validation_Evis_Muons.pdf");

	//------------------------------------

	TH1F *hnHitsMokka, *hnHitsDD4hep, *hnHitsData;

	f->GetObject("hnHitsMokka", hnHitsMokka);
	f->GetObject("hnHitsDD4hep", hnHitsDD4hep);
	f->GetObject("hnHitsData", hnHitsData);

	hnHitsMokka->SetLineColor(kRed);
	hnHitsMokka->SetLineWidth(2);
	hnHitsMokka->SetFillColor(kRed);
	hnHitsMokka->SetFillStyle(3001);
	hnHitsMokka->Scale(1./hnHitsMokka->Integral("width"));

	hnHitsDD4hep->SetLineColor(kBlue);
	hnHitsDD4hep->SetLineWidth(2);
	hnHitsDD4hep->SetFillColor(kBlue);
	hnHitsDD4hep->SetFillStyle(3001);
	hnHitsDD4hep->Scale(1./hnHitsDD4hep->Integral("width"));

	hnHitsData->SetLineColor(kBlack);
	hnHitsData->SetLineWidth(2);
	hnHitsData->Scale(1./hnHitsData->Integral("width"));

	gStyle->SetOptStat(1110);
	hnHitsData->SetStats(1);
	hnHitsMokka->SetStats(1);
	hnHitsDD4hep->SetStats(1);

	TCanvas *c3 = new TCanvas("c3", "nHits", 800, 600);
	hnHitsData->Draw();
	hnHitsData->GetXaxis()->SetRangeUser(2, 25);
	hnHitsData->GetYaxis()->SetRangeUser(0, 0.3);
	hnHitsData->GetXaxis()->SetTitle("nHits");
	hnHitsData->GetYaxis()->SetTitle("Fraction of events");
	hnHitsMokka->Draw("sames");
	hnHitsDD4hep->Draw("sames");
	hnHitsData->Draw("same");
	gPad->Update();
	TPaveStats *st1 = (TPaveStats*)hnHitsData->GetListOfFunctions()->FindObject("stats");
	st1->SetX1NDC(0.7);
	st1->SetX2NDC(0.9);
	st1->SetY1NDC(0.75);
	st1->SetY2NDC(0.9);
	st1->SetLineColor(kBlack);
	st1->SetTextColor(kBlack);
	TPaveStats *st21 = (TPaveStats*)hnHitsMokka->GetListOfFunctions()->FindObject("stats");
	st21->SetX1NDC(0.7);
	st21->SetX2NDC(0.9);
	st21->SetY1NDC(0.55);
	st21->SetY2NDC(0.70);
	st21->SetLineColor(kRed);
	st21->SetTextColor(kRed);
	TPaveStats *st31 = (TPaveStats*)hnHitsDD4hep->GetListOfFunctions()->FindObject("stats");
	st31->SetX1NDC(0.7);
	st31->SetX2NDC(0.9);
	st31->SetY1NDC(0.35);
	st31->SetY2NDC(0.5);
	st31->SetLineColor(kBlue);
	st31->SetTextColor(kBlue);
	gPad->Modified();

	c3->SaveAs("Plots/Validation_nHits_Muons.pdf");

	//--------------------------------------------

	TFile *f2 = new TFile("Rootfiles/BeamProfileSim.root", "OPEN");

	TH1F *hCogXData, *hCogXSim;
	TH1F *hCogYData, *hCogYSim;

	f2->GetObject("hCogXMokka", hCogXSim);
	f2->GetObject("hCogYMokka", hCogYSim);

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

	TFile *f3 = new TFile("Rootfiles/BeamProfileData.root", "OPEN");

	f3->GetObject("hCogXData", hCogXData);
	f3->GetObject("hCogYData", hCogYData);

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

	TLegend *leg = new TLegend(0.2, 0.7, 0.5, 0.9);
	leg->SetHeader("AHCAL #mu 150 GeV");
	leg->AddEntry(hCogXData, "Data", "l");
	leg->AddEntry(hCogXSim, "Mokka (QGSP_BERT)", "l");

	gStyle->SetOptStat(1110);
	hCogXData->SetStats(1);
	hCogYData->SetStats(1);

	hCogXSim->SetStats(1);
	hCogYSim->SetStats(1);

	TCanvas *c4 = new TCanvas("c4", "Beam Profile X", 800, 600);
	c4->cd();
	hCogXData->Draw();
	hCogXData->GetXaxis()->SetRangeUser(-400, 400);
	hCogXData->GetYaxis()->SetRangeUser(0, 0.1);
	hCogXSim->Draw("sames");
	hCogXData->Draw("same");
	leg->Draw("same");
	gPad->Update();
	TPaveStats *st7 = (TPaveStats*)hCogXData->GetListOfFunctions()->FindObject("stats");
	st7->SetX1NDC(0.7);
	st7->SetX2NDC(0.9);
	st7->SetY1NDC(0.75);
	st7->SetY2NDC(0.9);
	st7->SetLineColor(kBlack);
	st7->SetTextColor(kBlack);
	TPaveStats *st8 = (TPaveStats*)hCogXSim->GetListOfFunctions()->FindObject("stats");
	st8->SetX1NDC(0.7);
	st8->SetX2NDC(0.9);
	st8->SetY1NDC(0.55);
	st8->SetY2NDC(0.70);
	st8->SetLineColor(kRed);
	st8->SetTextColor(kRed);
	gPad->Modified();

	TCanvas *c5 = new TCanvas("c5", "Beam Profile Y", 800, 600);
	c5->cd();
	hCogYData->Draw();
	hCogYData->GetXaxis()->SetRangeUser(-400, 400);
	hCogYData->GetYaxis()->SetRangeUser(0, 0.1);
	hCogYSim->Draw("sames");
	hCogYData->Draw("same");
	leg->Draw("same");
	gPad->Update();
	TPaveStats *st9 = (TPaveStats*)hCogYData->GetListOfFunctions()->FindObject("stats");
	st9->SetX1NDC(0.7);
	st9->SetX2NDC(0.9);
	st9->SetY1NDC(0.75);
	st9->SetY2NDC(0.9);
	st9->SetLineColor(kBlack);
	st9->SetTextColor(kBlack);
	TPaveStats *st10 = (TPaveStats*)hCogYSim->GetListOfFunctions()->FindObject("stats");
	st10->SetX1NDC(0.7);
	st10->SetX2NDC(0.9);
	st10->SetY1NDC(0.55);
	st10->SetY2NDC(0.70);
	st10->SetLineColor(kRed);
	st10->SetTextColor(kRed);
	gPad->Modified();

	c4->SaveAs("Plots/BeamProfileX.pdf");
	c5->SaveAs("Plots/BeamProfileY.pdf");
}

void ComparisonSimData()
{
	CaliceStyle();

	TFile *f = new TFile("Rootfiles/TimingMokka.root", "OPEN");
	TH1F *hTimeSim, *hTimeSim_ErrorLow, *hTimeSim_ErrorUp;

	f->GetObject("hTimeSim", hTimeSim);
	f->GetObject("hTimeSim_ErrorLow", hTimeSim_ErrorLow);
	f->GetObject("hTimeSim_ErrorUp", hTimeSim_ErrorUp);

	hTimeSim->Sumw2();
	hTimeSim_ErrorLow->Sumw2();
	hTimeSim_ErrorUp->Sumw2();

	hTimeSim->SetLineColor(kRed);
	hTimeSim->SetMarkerColor(kRed);
	hTimeSim->SetLineWidth(2);

	hTimeSim->GetYaxis()->SetTitle("normalised entries");
	hTimeSim->Scale(1./hTimeSim->Integral(hTimeSim->GetXaxis()->FindBin(-30), hTimeSim->GetXaxis()->FindBin(30), "width"));

	hTimeSim_ErrorLow->SetLineColor(kBlue);
	hTimeSim_ErrorLow->SetMarkerColor(kBlue);
	hTimeSim_ErrorLow->SetLineWidth(2);

	hTimeSim_ErrorLow->Scale(1./hTimeSim_ErrorLow->Integral(hTimeSim_ErrorLow->GetXaxis()->FindBin(-30), hTimeSim_ErrorLow->GetXaxis()->FindBin(30), "width"));
	hTimeSim_ErrorLow->GetYaxis()->SetTitle("normalised entries");

	hTimeSim_ErrorUp->SetLineColor(kGreen);
	hTimeSim_ErrorUp->SetMarkerColor(kGreen);
	hTimeSim_ErrorUp->SetLineWidth(2);

	hTimeSim_ErrorUp->Scale(1./hTimeSim_ErrorUp->Integral(hTimeSim_ErrorUp->GetXaxis()->FindBin(-30), hTimeSim_ErrorUp->GetXaxis()->FindBin(30), "width"));
	hTimeSim_ErrorUp->GetYaxis()->SetTitle("normalised entries");


	//-------------------------------------------------

	TFile *f2 = new TFile("Rootfiles/AHCALTiming.root", "OPEN");
	TH1F* hData;

	f2->GetObject("Timing_AHCAL_Muons", hData);

	hData->Sumw2();
	hData->Scale(1./hData->Integral(hData->GetXaxis()->FindBin(-30), hData->GetXaxis()->FindBin(30), "width"));
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

		double error_syst = 0.20*content;

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

		double error_low = 0.;
		double error_up = 0.;

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

		double error_stat = hTimeSim->GetBinError(ibin);
		double error_syst = 0.00*content;

		gTimeSim->SetPoint(ibin, hTimeSim->GetXaxis()->GetBinCenter(ibin), content);
		gTimeSim->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_syst*error_syst));
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

		double error_syst = 0.20*content;

		gTimeDataRatio->SetPoint(ibin, hRatioData->GetXaxis()->GetBinCenter(ibin), content);
		gTimeDataRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_syst*error_syst), TMath::Sqrt(error_syst*error_syst + error_stat*error_stat + error_syst*error_syst));
	}


	TH1F *hRatioMokka = (TH1F*)hTimeSim->Clone("hRatioMokka");
	hRatioMokka->Divide(hData);
	hRatioMokka->GetXaxis()->SetTitle("Time of first hit [ns]");
	hRatioMokka->GetYaxis()->CenterTitle();
	hRatioMokka->GetYaxis()->SetTitle("MC/Data");
	hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
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

	//------------------------- Ratio Errors ---------------------------------

	TGraphAsymmErrors *gTimeSimRatio = new TGraphAsymmErrors();
	gTimeSimRatio->SetLineColor(kRed);
	gTimeSimRatio->SetLineWidth(2);

	for(int ibin = 0; ibin < hRatioMokka->GetNbinsX(); ibin++)
	{
		double content = hRatioMokka->GetBinContent(ibin);
		double content_low = hRatioMokka_ErrorLow->GetBinContent(ibin);
		double content_up = hRatioMokka_ErrorUp->GetBinContent(ibin);

		double error_low = 0.;
		double error_up = 0.;

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

		double error_stat = hRatioMokka->GetBinError(ibin);
		double error_syst = 0.00*content;

		gTimeSimRatio->SetPoint(ibin, hRatioMokka->GetXaxis()->GetBinCenter(ibin), content);
		gTimeSimRatio->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_syst*error_syst));
	}

	//***************************************************************//
	//*
	//*
	//*
	//------------------- DD4hep -----------------------------

	TFile *f3 = new TFile("Rootfiles/TimingDD4hep.root", "OPEN");
	TH1F *hTimeSim_DD4hep, *hTimeSim_DD4hep_ErrorLow, *hTimeSim_DD4hep_ErrorUp;

	f3->GetObject("hTimeSim", hTimeSim_DD4hep);
	f3->GetObject("hTimeSim_ErrorLow", hTimeSim_DD4hep_ErrorLow);
	f3->GetObject("hTimeSim_ErrorUp", hTimeSim_DD4hep_ErrorUp);

	hTimeSim_DD4hep->Sumw2();
	hTimeSim_DD4hep_ErrorLow->Sumw2();
	hTimeSim_DD4hep_ErrorUp->Sumw2();

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

	hTimeSim_DD4hep->Scale(1./hTimeSim_DD4hep->Integral(hTimeSim_DD4hep->GetXaxis()->FindBin(-30), hTimeSim_DD4hep->GetXaxis()->FindBin(30), "width"));
	hTimeSim_DD4hep_ErrorLow->Scale(1./hTimeSim_DD4hep_ErrorLow->Integral(hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(-30), hTimeSim_DD4hep_ErrorLow->GetXaxis()->FindBin(30), "width"));
	hTimeSim_DD4hep_ErrorUp->Scale(1./hTimeSim_DD4hep_ErrorUp->Integral(hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(-30), hTimeSim_DD4hep_ErrorUp->GetXaxis()->FindBin(30), "width"));

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

		double error_low = 0.;
		double error_up = 0.;

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

		double error_stat = hTimeSim_DD4hep->GetBinError(ibin);
		double error_syst = 0.00*content;

		gTimeSim_DD4hep->SetPoint(ibin, hTimeSim_DD4hep->GetXaxis()->GetBinCenter(ibin), content);
		gTimeSim_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_syst*error_syst));
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

	//------------------------- Ratio Errors ---------------------------------

	TGraphAsymmErrors *gTimeSimRatio_DD4hep = new TGraphAsymmErrors();
	gTimeSimRatio_DD4hep->SetLineColor(kBlue);
	gTimeSimRatio_DD4hep->SetLineWidth(2);

	for(int ibin = 0; ibin < hRatioDD4hep->GetNbinsX(); ibin++)
	{
		double content = hRatioDD4hep->GetBinContent(ibin);
		double content_low = hRatioDD4hep_ErrorLow->GetBinContent(ibin);
		double content_up = hRatioDD4hep_ErrorUp->GetBinContent(ibin);

		double error_low = 0.;
		double error_up = 0.;

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

		double error_stat = hRatioDD4hep->GetBinError(ibin);
		double error_syst = 0.00*content;

		gTimeSimRatio_DD4hep->SetPoint(ibin, hRatioDD4hep->GetXaxis()->GetBinCenter(ibin), content);
		gTimeSimRatio_DD4hep->SetPointError(ibin, 0.5, 0.5, TMath::Sqrt(error_stat*error_stat + error_low*error_low + error_syst*error_syst), TMath::Sqrt(error_stat*error_stat + error_up*error_up + error_syst*error_syst));
	}

	//---------------------------------------------------------

	double sFactor = 0.60;

	TLegend* leg3 = new TLegend(0.70, 0.55, 0.9, 0.85);
	leg3->SetBorderSize(0);
	leg3->SetTextSize(0.035);
	leg3->SetHeader("Muons");
	leg3->AddEntry(gTimeData, "Data (stat #oplus syst)", "pf");
	leg3->AddEntry(gTimeSim, "Mokka (QGSP_BERT)", "l");
	leg3->AddEntry(gTimeSim_DD4hep, "DD4hep (QGSP_BERT)", "l");

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
	hTimeSim->GetXaxis()->SetRangeUser(-20,20);
	hTimeSim->GetYaxis()->SetRangeUser(0.0001, 0.13);
	hTimeSim->Draw("p hist");
	gTimeData->Draw("E2");
	gTimeSim->Draw("PE");
	gTimeSim_DD4hep->Draw("PE");
	hData->Draw("ep hist same");
	leg3->Draw("same");
	pt->Draw("same");
	pad2->cd();
	hRatioMokka->GetXaxis()->SetRangeUser(-20,20);
	hRatioMokka->GetYaxis()->SetRangeUser(0.5, 1.5);
	hRatioMokka->Draw("p");
	gTimeDataRatio->Draw("E2");
	gTimeSimRatio->Draw("PE");
	gTimeSimRatio_DD4hep->Draw("PE");
	hRatioData->Draw("p hist same");

	c->SaveAs("Plots/Comparison_MokkaDD4hepData_Muons.pdf");
}

void MakePlots()
{
	CorrectionOffsets();
	EdgeDetection();
	LinearityCorrection();
	Pedestal();
	TimeWalk();
	TimingFull_AHCAL();
	TimingFullCorrections();
	TimingNoCorrections();
	TimingLinCorrections();
	SelectionCuts();
	Validation();
	ComparisonSimData();
}
