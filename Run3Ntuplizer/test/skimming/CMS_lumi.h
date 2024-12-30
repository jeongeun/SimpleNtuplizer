#include "TPad.h"
#include "TLatex.h"
#include "TLine.h"
#include "TBox.h"
#include "TASImage.h"

//
// Global variables
//

TString cmsText     = "CMS";
float cmsTextFont   = 60 ; //60;  // default is helvetic-bold

bool writeExtraText = true;
TString extraText   = "Preliminary";
float extraTextFont = 52;  // default is helvetica-italics

// text sizes and text offsets with respect to the top frame
// in unit of the top margin size
float lumiTextSize     = 0.6;
float lumiTextOffset   = 0.2;
float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.1;  // only used in outOfFrame version

float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;

// ratio of "CMS" and extra text size
float extraOverCmsTextSize  = 0.76;

TString lumi_14TeV = "3.0 ab^{-1}";
TString lumi_13p6TeV = "34.7 fb^{-1}";
TString lumi_13p6TeV_22pre = "8.0 fb^{-1}";
TString lumi_13p6TeV_22post = "26.7 fb^{-1}";
TString lumi_13p6TeV_23pre = "17.7 fb^{-1}";
TString lumi_13p6TeV_23post = "9.45 fb^{-1}";
//TString lumi_13TeV = "20.1 fb^{-1}";
TString lumi_13TeV = "21.6+27 fb^{-1}";
//"138 fb^{-1}" ;//"34.3 fb^{-1}";
// (7.96 + 26.34) fb^{-1}";
//"3.1 fb^{-1}";//18.0 fb^{-1}";//5.8 fb^{-1}";//3.0 fb^{-1}";//5.07 fb^{-1}"; //"35.2 fb^{-1}";
TString lumi_8TeV  = "19.7 fb^{-1}";
TString lumi_7TeV  = "5.1 fb^{-1}";

bool drawLogo      = true;

void CMS_lumi( TPad* pad, int iPeriod=13, int iPosX=10 );

