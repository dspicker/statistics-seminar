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




void gauss()
{
    TF1 *f1 = new TF1("f1", "gaus", -6, 6);
    f1->SetTitle("");
    f1->SetParameters(1.0, 0.0, 1.0);
    f1->Draw("C");
    f1->GetXaxis()->SetLabelSize(0.);
    f1->GetYaxis()->SetLabelSize(0.);
    

    Double_t quantil = ROOT::Math::gaussian_quantile(1-(1-0.6827)/2, 1.0);
    TLine *lxu = new TLine(-quantil, 0, -quantil, 0.6);
    lxu->SetLineColor(kOrange-1);
    lxu->SetLineWidth(2);
    lxu->Draw("same");
    TLine *lxo = new TLine(quantil, 0, quantil, 0.6);
    lxo->SetLineColor(kOrange-1);
    lxo->SetLineWidth(2);
    lxo->Draw("same");
    TLine *lxm = new TLine(0, 0, 0, 0.1);
    lxm->SetLineColor(kOrange-1);
    lxm->SetLineWidth(1);
    lxm->Draw("same");
    TLine *lxt = new TLine(0.3, 0, 0.3, 0.05);
    lxt->SetLineColor(kBlack);
    lxt->SetLineWidth(1);
    lxt->Draw("same");

    TLatex *text1 = new TLatex(-quantil, -0.05, "a");
	text1->SetTextSize(0.04);
	text1->SetTextAlign(21);
    text1->SetTextColor(kOrange-1);
	text1->Draw();
	TLatex *text2 = new TLatex(quantil, -0.05, "b");
	text2->SetTextSize(0.04);
	text2->SetTextAlign(21);
    text2->SetTextColor(kOrange-1);
	text2->Draw();
	TLatex *text3 = new TLatex(0, -0.05, "#bar{x}");
	text3->SetTextSize(0.04);
	text3->SetTextAlign(21);
    text3->SetTextColor(kOrange-1);
	text3->Draw();
    TLatex *text4 = new TLatex(0.3, -0.05, "#theta");
	text4->SetTextSize(0.04);
    text4->SetTextAlign(21);
	text4->Draw();

    TLatex *text5 = new TLatex(1.5, 0.1, "#alpha/2");
	text5->SetTextSize(0.04);
    text5->SetTextAlign(21);
	text5->Draw();
    TLatex *text6 = new TLatex(-1.5, 0.1, "#alpha/2");
	text6->SetTextSize(0.04);
    text6->SetTextAlign(21);
	text6->Draw();
    TLatex *text7 = new TLatex(0, 0.5, "1-#alpha");
	text7->SetTextSize(0.04);
    text7->SetTextAlign(21);
	text7->Draw();
}