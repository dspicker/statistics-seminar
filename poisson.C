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
#include "THStack.h"

void poisson()
{

    TRandom3 *rand_gen = new TRandom3(0);
    const UInt_t mean = 5;
    const UInt_t background = 2;
    const Double_t alpha = 0.05;
    const UInt_t dof = 100;
    TString sTitle = TString::Format("Number of events");
    TH1I *hSample = new TH1I("hSample", sTitle, 30, -4.5, 25.5);


    for ( int i = 0 ; i<dof ; i++)
    {
        Double_t val = rand_gen->Poisson(mean+background);
        hSample->Fill(val);
    }

    Double_t sample_mean = hSample->GetMean();
    //hSample->Draw();

    TF1 *f1 = new TF1("f1", "[1] * TMath::PoissonI(x,[0])", -5, 30);
    f1->SetParameter(0, (Double_t)(mean + background));
    f1->SetParameter(1, 1 );
    //f1->Draw();

    TF1 *f2 = new TF1("f1", "[1] * TMath::PoissonI(x,[0])", -5, 30);
    f2->SetParameter(0, (Double_t)(mean));
    f2->SetParameter(1, 1);
    f2->SetLineColor(5);
    f2->Draw();
    f1->Draw("same");
    //f2->GetHistogram()->SetAxisRange(-5., 25);

    Double_t ci_low = 0.5 * ROOT::Math::chisquared_quantile(alpha / 2., 2. * mean) - background;
    //Double_t ci_up = 0.5 * ROOT::Math::chisquared_quantile(1 - alpha / 2, 2 * (mean + 1)) - background;
    Double_t ci_up = 0.5 * ROOT::Math::chisquared_quantile(1. - alpha, 2. * (mean + 1.)) - background;


    std::cout << "x_l = " << ci_low << std::endl ;
	std::cout << "x_u = " << ci_up << std::endl ;

    TLine *lxu = new TLine(ci_low, 0, ci_low, 0.1);
    lxu->SetLineColor(kOrange);
    lxu->SetLineWidth(2);
    lxu->Draw("same");
    TLine *lxo = new TLine(ci_up, 0, ci_up, 0.1);
    lxo->SetLineColor(kOrange);
    lxo->SetLineWidth(2);
    lxo->Draw("same");


}