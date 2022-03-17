#include <iostream>
#include <vector>
#include "TROOT.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TStyle.h"


void fit(){
  gStyle->SetPadGridX(true);
 gStyle->SetPadGridY(true);
TCanvas *canvas = new TCanvas("canvas","Data",700,700);
TPad *pad1 = new TPad("pad1","Graph",0,.2,1,1);
TPad *pad2 = new TPad("pad2","Scarti",0,0,1,.2);
std::string filename,title,xTitle,yTitle,strFit;

std::cout<<"Please insert name of datafile:";
std::getline(std::cin>> std::ws, filename);

TGraphErrors *graph = new TGraphErrors(filename.c_str(),"%lg%lg%lg%lg","");
graph->SetMarkerStyle(7);
graph->SetMarkerColor(kBlue);
std::cout<<"Insert graph title:";
std::getline(std::cin>> std::ws, title);
std::cout<<"Insert x axis title:";
std::getline(std::cin>> std::ws, xTitle);
std::cout<<"Insert y axis title:";
std::getline(std::cin>> std::ws, yTitle);
graph->SetTitle((title+';'+xTitle+';'+yTitle).c_str());
graph->GetYaxis()->SetTitleOffset(1.4);

pad1->cd();

graph->Draw("APE");




std::cout<<"Insert function to fit:";
std::getline(std::cin>> std::ws, strFit);

TF1 *fitFun = new TF1("fitFun",strFit.c_str());

double par;
for(int i{0};i!=fitFun->GetNpar();++i)
{
  std::cout<<"Insert [p"<<i<<"]:";
std::cin>>par;
fitFun->SetParameter(i,par);
}

graph->Fit("fitFun");

int N{graph->GetN()};
std::vector<double> delta;

TF1 *fitRes = graph->GetFunction("fitFun");
double *X{graph->GetX()},*Y{graph->GetY()};

for(int i{0};i!=N ; ++i){
  delta.push_back(fitRes->Eval(X[i+1])-Y[i+1]);
}

double *d = &delta[0];

TGraph *noise = new TGraph(graph->GetN(),graph->GetX(),d);
noise->SetTitle((';'+xTitle+';'+yTitle).c_str());
noise->GetYaxis()->SetLabelSize(.1);
noise->GetYaxis()->SetNdivisions(5);
noise->GetXaxis()->SetLabelSize(.1);
noise->GetXaxis()->SetTitleSize(.1);
noise->GetYaxis()->SetTitleSize(.1);
noise->GetXaxis()->SetTitleOffset(.8);
noise->GetYaxis()->SetTitleOffset(.5);

pad2->cd();
noise->Draw("APL");

TF1 *lin = new TF1("lin","[0]");

noise->Fit(lin,"0Q");

TF1 *fitScarti=noise->GetFunction("lin");
fitScarti->SetLineColor(kBlack);
fitScarti->SetLineStyle(2);
fitScarti->Draw("SAME");

pad1->cd();
TLegend* leg = new TLegend(0.78, 0.85, .99, .99);
leg->AddEntry(graph,"Punti sperimentali","lep");
leg->AddEntry(fitFun,"Fit","l");
leg->AddEntry(noise,"Scarti fit/dati","l");
leg->Draw();

canvas->cd();
pad1->Draw();
pad2->Draw();



}