#include "TSystem.h"
#include "TRandom.h"
#include "TRandom3.h"
#include <vector>
#include "TH1.h"
#include "TF1.h"
#include <iostream>
#include "TCanvas.h"
#include "TMath.h"
#include "root6/Math/QuantFuncMathCore.h"
#include "root6/Math/QuantFuncMathMore.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TLatex.h"


TRandom3 *rand_gen = new TRandom3(0);
const UInt_t nb_dice = 60;
const UInt_t nb_sides = 6;
const UInt_t nb_rolls = 10000;
TString sTitle = TString::Format("Throwing %d dice %d times", nb_dice, nb_rolls);
TH1I *hSample = new TH1I("hSample", sTitle, 25, 0.5, 25.5);


void roll()
{
	std::vector<std::vector<UInt_t>> data_vec(nb_rolls, std::vector<UInt_t>(nb_dice));

	for (std::vector<UInt_t> iRoll : data_vec)
	{
		UInt_t nb_of_fives = 0;
		for (UInt_t iDice : iRoll)
		{
			iDice = rand_gen->Integer(nb_sides) + 1;
			if (iDice == 5)
				nb_of_fives++;
		}
		hSample->Fill(nb_of_fives);
	}
}


void roll_60_dice()
{

	

	Int_t xlow = 0;
	Int_t xhigh = 0;
	Double_t sample_mean = 0;
	Double_t sample_sigma = 0;
	const Double_t alpha = 0.05 ;
	//const Double_t alpha = 1.0-0.6827 ;
	Double_t quantil = 0;
	Double_t ci_low = 0;
	Double_t ci_high = 0;
	for(int i=0 ; 1<100 ; i++ )
	{
		roll();
		xlow = hSample->FindFirstBinAbove() - 3;
		xhigh = hSample->FindLastBinAbove() + 3;
		sample_mean = hSample->GetMean();
		sample_sigma = hSample->GetStdDev() * sqrt(nb_rolls/(nb_rolls-1));
		//quantil = ROOT::Math::gaussian_quantile(1-alpha/2, 1);
		quantil = ROOT::Math::tdistribution_quantile(1-alpha/2, nb_rolls-1 );
		ci_low = sample_mean - ( quantil * sample_sigma/sqrt(nb_rolls));
		ci_high = sample_mean + ( quantil * sample_sigma/sqrt(nb_rolls));
		if( ci_low > 10.0 || ci_high < 10.0)
		{
			break;
		}
		hSample->Reset();
	}

	

	
	hSample->GetXaxis()->SetTitle("No of fives in each throw");
	hSample->GetYaxis()->SetTitle("Count");
	hSample->SetStats(kFALSE);
	hSample->Draw();
	//hSample->Fit("gaus","Q","",xlow, xhigh);
	//TF1 *fit = hSample->GetFunction("gaus");
	//Double_t fit_mean = fit->GetParameter(1);
	//Double_t fit_sigma = fit->GetParameter(2);

	
	//Double_t ci_low = ROOT::Math::gaussian_quantile(alpha/2, fit_sigma)/sqrt(nb_rolls) + fit_mean ;
	//Double_t ci_high = ROOT::Math::gaussian_quantile_c(alpha/2, fit_sigma)/sqrt(nb_rolls) + fit_mean ;

	

	std::cout << "x_l = " << ci_low << std::endl ;
	std::cout << "x_u = " << ci_high << std::endl ;
	//std::cout << "x_m = " << fit_mean << std::endl ;

	Double_t max = hSample->GetMaximum();

	//TLine *lxu = new TLine(ci_low,0,ci_low,fit->Eval(ci_low));
	TLine *lxu = new TLine(ci_low,0,ci_low,max);
	lxu->SetLineColor(kOrange);
	lxu->SetLineWidth(2);
	lxu->Draw("same");
	//TLine *lxo = new TLine(ci_high,0,ci_high,fit->Eval(ci_high));
	TLine *lxo = new TLine(ci_high,0,ci_high,max);
	lxo->SetLineColor(kOrange);
	lxo->SetLineWidth(2);
	lxo->Draw("same");
	TLine *lxm = new TLine(sample_mean,0,sample_mean,max);
	lxm->SetLineColor(kOrange);
	lxm->SetLineWidth(2);
	lxm->Draw("same");


	//TLatex *text1 = new TLatex(ci_low, fit->Eval(ci_low)+1, "x_{low}");
	TLatex *text1 = new TLatex(ci_low, max, "x_{low}");
	text1->SetTextSize(0.04);
	text1->SetTextAlign(32);
	//text1->SetTextColor(kOrange);
	text1->Draw();
	//TLatex *text2 = new TLatex(ci_high, fit->Eval(ci_high)+1, "x_{up}");
	TLatex *text2 = new TLatex(ci_high, max, "x_{up}");
	text2->SetTextSize(0.04);
	text2->SetTextAlign(12);
	//text2->SetTextColor(kOrange);
	text2->Draw();
	//TLatex *text3 = new TLatex(fit_mean, fit->Eval(fit_mean)+1, "#mu");
	TLatex *text3 = new TLatex(sample_mean, max, "#mu");
	text3->SetTextSize(0.04);
	text3->SetTextAlign(22);
	//text3->SetTextColor(kOrange);
	text3->Draw();

	TPaveText *pt = new TPaveText(.78,.65,.91,.91,"NDC");
	pt->SetTextAlign(12);
	pt->AddText("Sample:");
	pt->AddText( TString::Format("#mu = %.3f",sample_mean) );
	pt->AddText( TString::Format("#sigma = %.3f",sample_sigma) );
	pt->AddText("Confidence Interval:");
	pt->AddText( TString::Format("(1-#alpha) = %.3f", (1-alpha) ) );
	pt->AddText( TString::Format("x_{low} = %.3f",ci_low) );
	pt->AddText( TString::Format("x_{up} = %.3f",ci_high) );
	pt->AddText( TString::Format("x_{up} - x_{low} = %.3f", (ci_high-ci_low) ) );

	pt->Draw();
	/*
	std::cout << fit_sigma << std::endl ;
	std::cout << hSample->GetMaximum() << std::endl ;
	std::cout << hSample->FindLastBinAbove() << std::endl ;
	*/

}



