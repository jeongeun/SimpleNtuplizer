import ROOT
import math
import ctypes
from ROOT import TFile, TGraphAsymmErrors, TCanvas, TPad, TH2F, TF1, TLine, TLegend, TLatex, gROOT, gStyle, kGreen, kBlack, kRed, kBlue, kGray

def set_tdr_style():
    ROOT.gStyle.SetCanvasBorderMode(0)
    ROOT.gStyle.SetFrameBorderMode(0)
    ROOT.gStyle.SetPadBorderMode(0)
    ROOT.gStyle.SetPadColor(0)
    ROOT.gStyle.SetCanvasColor(0)
    ROOT.gStyle.SetTitleFont(42, "XYZ")
    ROOT.gStyle.SetLabelFont(42, "XYZ")
    ROOT.gStyle.SetLabelSize(0.05, "XYZ")
    ROOT.gStyle.SetTitleSize(0.07, "XYZ")  # Increase title size
    ROOT.gStyle.SetTitleFontSize(0.07)  # Increase font size of title
    ROOT.gStyle.SetTitleOffset(0.12, "X")
    ROOT.gStyle.SetTitleOffset(0.9, "Y")
    ROOT.gStyle.SetPadTopMargin(0.10)
    ROOT.gStyle.SetPadBottomMargin(0.15)
    ROOT.gStyle.SetPadLeftMargin(0.15)
    ROOT.gStyle.SetPadRightMargin(0.05)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetLegendBorderSize(0)
    ROOT.gStyle.SetLegendFont(42)

def add_cms_lumi(pad, lumi_text="26.7 fb^{-1} (13.6 TeV)", cms_text="CMS", extra_text="Preliminary"):
    pad.cd()
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.07)
    latex.SetTextFont(62)
    latex.SetTextAlign(11)  # Left-align
    latex.DrawLatex(0.15, 0.92, cms_text)  # CMS in bold
    latex.SetTextFont(52)  # Italic font for Preliminary
    latex.DrawLatex(0.26, 0.92, extra_text)  # Preliminary in italic next to CMS

    #latex.DrawLatex(0.16, 0.92, f"#bf{{{cms_text}}} #it{{{extra_text}}}")
    latex.SetTextSize(0.07)  # Slightly smaller for lumi text
    latex.SetTextFont(42)  # Regular font for lumi text
    latex.SetTextAlign(31)  # Right-align for lumi text
    latex.DrawLatex(0.94, 0.92, lumi_text)


def divide_graphs(graph1, graph2, print_flag=0):
    if not graph1 or not graph2:
        print("Error: Invalid input graphs.")
        return None
    if graph1.GetN() != graph2.GetN():
        print(f"Error: Graphs have different number of points. graph1 = {graph1.GetN()}, graph2 = {graph2.GetN()}")

    ratio_graph = TGraphAsymmErrors()
    for i in range(graph1.GetN()):
        x1, y1 = ctypes.c_double(), ctypes.c_double()
        x2, y2 = ctypes.c_double(), ctypes.c_double()
        graph1.GetPoint(i, x1, y1)
        graph2.GetPoint(i, x2, y2)

        if y2.value != 0:
            ratio = y1.value / y2.value
            exl1, exh1 = graph1.GetErrorXlow(i), graph1.GetErrorXhigh(i)
            errl, errh = 0.0, 0.0  # Adjust if systematic uncertainties are needed
            ratio_graph.SetPoint(i, x1.value, ratio)
            ratio_graph.SetPointError(i, exl1, exh1, errl, errh)

    return ratio_graph


def calculate_median_value(graph, x_min, x_max):
    y_values = []
    for i in range(graph.GetN()):
        x, y = ctypes.c_double(0), ctypes.c_double(0)  # Use ctypes.c_double for pass-by-reference
        graph.GetPoint(i, x, y)
        if x_min <= x.value <= x_max:
            y_values.append(y.value)
    y_values.sort()
    n = len(y_values)
    if n == 0:
        return 1.0  # Return 1.0 if no points found
    elif n % 2 == 1:
        return y_values[n // 2]  # Odd number of elements
    else:
        return (y_values[n // 2 - 1] + y_values[n // 2]) / 2.0  # Even number of elements


def draw1D():

    # Set ROOT style
    gROOT.SetStyle("Default")
    gStyle.SetOptStat(0)
    gStyle.SetCanvasColor(0)

    # Open data files
    DATA = "heff_22Muon_ReReco_EFG.root"
    MC = "heff_22MC_postEE.root"
    file_fg = TFile.Open(DATA)
    file_mc = TFile.Open(MC)
    print("--- FileOpen Done.")

    # Load histograms
    hFG_heep_eb_pt = file_fg.Get("h_heep_eb_pt")
    hFG_heep_ee_pt = file_fg.Get("h_heep_ee_pt")
    hMC_heep_eb_pt = file_mc.Get("h_heep_eb_pt")
    hMC_heep_ee_pt = file_mc.Get("h_heep_ee_pt")
    hFG_hltORALL_eb_pt = file_fg.Get("h_hltORALL_eb_pt")
    hFG_hltORALL_ee_pt = file_fg.Get("h_hltORALL_ee_pt")
    hMC_hltORALL_eb_pt = file_mc.Get("h_hltORALL_eb_pt")
    hMC_hltORALL_ee_pt = file_mc.Get("h_hltORALL_ee_pt")

    # Efficiency graphs
    eff_22FG_hltORALL_eb_pt = TGraphAsymmErrors()
    eff_22FG_hltORALL_eb_pt.Divide(hFG_hltORALL_eb_pt, hFG_heep_eb_pt, "cl=0.683 b(1,1) mode")
    eff_22FG_hltORALL_ee_pt = TGraphAsymmErrors()
    eff_22FG_hltORALL_ee_pt.Divide(hFG_hltORALL_ee_pt, hFG_heep_ee_pt, "cl=0.683 b(1,1) mode")
    eff_22MC_hltORALL_eb_pt = TGraphAsymmErrors()
    eff_22MC_hltORALL_eb_pt.Divide(hMC_hltORALL_eb_pt, hMC_heep_eb_pt, "cl=0.683 b(1,1) mode")
    eff_22MC_hltORALL_ee_pt = TGraphAsymmErrors()
    eff_22MC_hltORALL_ee_pt.Divide(hMC_hltORALL_ee_pt, hMC_heep_ee_pt, "cl=0.683 b(1,1) mode")

    # Scale factor graphs
    hSF_hltORALL_eb_pt = divide_graphs(eff_22FG_hltORALL_eb_pt, eff_22MC_hltORALL_eb_pt)
    hSF_hltORALL_ee_pt = divide_graphs(eff_22FG_hltORALL_ee_pt, eff_22MC_hltORALL_ee_pt)

    # Set custom style
    set_tdr_style()

    # Canvas and pad settings for EB
    W, H = 800, 800
    canvas_eb = TCanvas("Can_eb_pt", "canvas", 50, 60, W, H)
    padU = TPad("padU", "padUpper", 0, 0.35, 1, 1)
    padL = TPad("padL", "padLower", 0, 0, 1, 0.35)
    padU.SetTopMargin(0.09)
    padU.SetBottomMargin(0.01)  # Narrow gap by reducing bottom margin of padU
    padL.SetTopMargin(0.01)     # Narrow gap by reducing top margin of padL
    padL.SetBottomMargin(0.35)
    padU.SetLogx()
    padL.SetLogx()
    padU.Draw()
    padL.Draw()

    # Upper pad - Efficiency for EB
    padU.cd()
    n1eb = TH2F("n1eb", "", 2, 90, 3000, 2, 0., 1.1)
    n1eb.GetYaxis().SetTitle("HLT Efficiency")
    n1eb.GetYaxis().SetTitleSize(0.07)  # Increase Y-axis title size
    n1eb.GetYaxis().SetLabelSize(0.05)
    n1eb.Draw()
    eff_22MC_hltORALL_eb_pt.SetLineColor(kGreen+2)
    eff_22MC_hltORALL_eb_pt.SetFillColorAlpha(kGreen+2, 0.3)
    eff_22MC_hltORALL_eb_pt.SetFillStyle(3001)
    eff_22MC_hltORALL_eb_pt.Draw("E2psame")
    eff_22FG_hltORALL_eb_pt.SetLineColor(kBlack)
    eff_22FG_hltORALL_eb_pt.SetMarkerStyle(20)
    eff_22FG_hltORALL_eb_pt.Draw("E1psame")

    # Legend for EB
    leg_eb = TLegend(0.40, 0.15, 0.9, 0.35)
    leg_eb.SetTextSize(0.045)
    leg_eb.SetFillStyle(0)
    leg_eb.AddEntry(eff_22FG_hltORALL_eb_pt, "Data (Run2022EFG 22Sep2023)", "pl")
    leg_eb.AddEntry(eff_22MC_hltORALL_eb_pt, "MC (t#bar{t}#rightarrow2l2#nu postEE 130X)", "f")
    leg_eb.Draw()

    add_cms_lumi(padU, lumi_text="26.7 fb^{-1} (13.6 TeV)", cms_text="CMS", extra_text="Preliminary")

    # Lower pad - Scale Factor for EB
    padL.cd()
    n2eb = TH2F("n2eb", "", 2, 90, 3000, 2, 0.5, 1.5)
    n2eb.GetYaxis().SetTitle("Scale Factor")
    n2eb.GetYaxis().SetTitleSize(0.12)  # Increase Y-axis title size
    n2eb.GetYaxis().SetTitleOffset(0.55)  # Increase Y-axis title size
    n2eb.GetYaxis().SetLabelSize(0.07)
    n2eb.GetXaxis().SetTitle("Offline EB electron p_{T} (GeV)")
    n2eb.GetXaxis().SetTitleSize(0.12)  # Increase X-axis title size
    n2eb.GetXaxis().SetTitleOffset(1.0)  # Increase Y-axis title size
    n2eb.GetXaxis().SetLabelSize(0.08)
    n2eb.Draw()

    hSF_hltORALL_eb_pt.SetLineColor(kBlack)
    hSF_hltORALL_eb_pt.SetMarkerStyle(20)
    hSF_hltORALL_eb_pt.Draw("E1psame")

    for i in range(hSF_hltORALL_eb_pt.GetN()):
        x, y = ctypes.c_double(0), ctypes.c_double(0)
        hSF_hltORALL_eb_pt.GetPoint(i, x, y)
        print(f"Point {i}: x = {x.value}, y = {y.value}")

    # Perform constant fit on hSF_hltORALL_eb_pt between pT 130 and 3000
    initial_value = calculate_median_value(hSF_hltORALL_eb_pt, 130., 3000.)  # Calculate initial value for the fit
    print("Initial value for fit:", initial_value)
    constant_fit_eb = TF1("constant_fit_eb", "[0]", 130, 3000)  # Define a constant function
    constant_fit_eb.SetParameter(0, initial_value)  # Set initial parameter value
    constant_fit_eb.SetParLimits(0, initial_value, 1.0001) 
    hSF_hltORALL_eb_pt.Fit(constant_fit_eb, "R0")  # "R" option restricts the fit to the specified range
    constant_fit_eb.SetLineColor(kRed-9)
    constant_fit_eb.SetLineStyle(2)
    constant_fit_eb.Draw("same")
    parConst_eb = constant_fit_eb.GetParameter(0)
    errConst_eb = constant_fit_eb.GetParError(0)
    ci95_eb = 1.96 * errConst_eb  # 95% confidence interval
    print(f"Error = {ci95_eb}")
    Err_eb = math.sqrt((errConst_eb * errConst_eb) + (0.0001 * 0.0001))
    print(f"ci95_eb = {ci95_eb}, Err = {Err_eb}")

    # Display the fit result on padL
    fit_result_eb = TLatex()
    fit_result_eb.SetNDC()
    fit_result_eb.SetTextSize(0.08)
    fit_result_eb.SetTextAlign(13)
    fit_result_eb.SetTextColor(kRed-9)
    textConst_eb = f"EB Const Fit: SF = {parConst_eb:.3f} #pm {Err_eb:.3f}"
    fit_result_eb.DrawLatex(0.25, 0.85, textConst_eb)

    hline = TLine(90, 1.0, 3000, 1.0)
    hline.SetLineStyle(2)
    hline.SetLineColor(kGray)
    hline.Draw()

    canvas_eb.SaveAs("ceb_1sfpt_22postEE_sf_fit.png")

########################################################
########################################################

    # EE Canvas
    canvas_ee = TCanvas("Can_ee_pt", "canvas", 50, 60, W, H)
    padU1 = TPad("padU1", "padU1pper", 0, 0.35, 1, 1)
    padL1 = TPad("padL1", "padL1ower", 0, 0, 1, 0.35)
    padU1.SetTopMargin(0.09)
    padU1.SetBottomMargin(0.01)  # Narrow gap by reducing bottom margin of padU1
    padL1.SetTopMargin(0.01)     # Narrow gap by reducing top margin of padL1
    padL1.SetBottomMargin(0.35)
    padU1.SetLogx()
    padL1.SetLogx()
    padU1.Draw()
    padL1.Draw()

    # Upper pad - Efficiency for EE
    padU1.cd()
    n1ee = TH2F("n1ee", "", 2, 90, 3000, 2, 0., 1.1)
    n1ee.GetYaxis().SetTitle("HLT Efficiency")
    n1ee.GetYaxis().SetTitleSize(0.07)  # Increase Y-axis title size
    n1ee.GetYaxis().SetLabelSize(0.05)
    n1ee.Draw()
    eff_22MC_hltORALL_ee_pt.SetLineColor(kGreen+2)
    eff_22MC_hltORALL_ee_pt.SetFillColorAlpha(kGreen+2, 0.3)
    eff_22MC_hltORALL_ee_pt.SetFillStyle(3001)
    eff_22MC_hltORALL_ee_pt.Draw("E2psame")
    eff_22FG_hltORALL_ee_pt.SetLineColor(kBlack)
    eff_22FG_hltORALL_ee_pt.SetMarkerStyle(20)
    eff_22FG_hltORALL_ee_pt.Draw("E1psame")

    # Legend for EE
    leg_ee = TLegend(0.40, 0.15, 0.9, 0.35)
    leg_ee.SetTextSize(0.045)
    leg_ee.SetFillStyle(0)
    leg_ee.AddEntry(eff_22FG_hltORALL_ee_pt, "Data (Run2022EFG 22Sep2023)", "pl")
    leg_ee.AddEntry(eff_22MC_hltORALL_ee_pt, "MC (t#bar{t}#rightarrow2l2#nu postEE 130X)", "f")
    leg_ee.Draw()

    add_cms_lumi(padU1, lumi_text="26.7 fb^{-1} (13.6 TeV)", cms_text="CMS", extra_text="Preliminary")

    # Lower pad - Scale Factor for EE
    padL1.cd()
    n2ee = TH2F("n2ee", "", 2, 90, 3000, 2, 0.5, 1.5)
    n2ee.GetYaxis().SetTitle("Scale Factor")
    n2ee.GetYaxis().SetTitleSize(0.12)  # Increase Y-axis title size
    n2ee.GetYaxis().SetTitleOffset(0.55)  # Increase Y-axis title size
    n2ee.GetYaxis().SetLabelSize(0.07)
    n2ee.GetXaxis().SetTitle("Offline EE electron p_{T} (GeV)")
    n2ee.GetXaxis().SetTitleSize(0.12)  # Increase X-axis title size
    n2ee.GetXaxis().SetTitleOffset(1.0)  # Increase Y-axis title size
    n2ee.GetXaxis().SetLabelSize(0.08)
    n2ee.Draw()

    hSF_hltORALL_ee_pt.SetLineColor(kBlack)
    hSF_hltORALL_ee_pt.SetMarkerStyle(20)
    hSF_hltORALL_ee_pt.Draw("E1psame")

    for i in range(hSF_hltORALL_ee_pt.GetN()):
        x, y = ctypes.c_double(0), ctypes.c_double(0)
        hSF_hltORALL_ee_pt.GetPoint(i, x, y)
        print(f"Point {i}: x = {x.value}, y = {y.value}")

    # Perform constant fit on hSF_hltORALL_ee_pt between pT 130 and 3000
    initial_value = calculate_median_value(hSF_hltORALL_ee_pt, 130., 3000.)  # Calculate initial value for the fit
    print("Initial value for fit:", initial_value)
    constant_fit_ee = TF1("constant_fit_ee", "[0]", 130, 3000)  # Define a constant function
    constant_fit_ee.SetParameter(0, initial_value)  # Set initial parameter value
    constant_fit_ee.SetParLimits(0, initial_value+0.015, 1.001) 
    hSF_hltORALL_ee_pt.Fit(constant_fit_ee, "R0")  # "R" option restricts the fit to the specified range
    constant_fit_ee.SetLineColor(kBlue-9)
    constant_fit_ee.SetLineStyle(2)
    constant_fit_ee.Draw("same")
    parConst_ee = constant_fit_ee.GetParameter(0)
    errConst_ee = constant_fit_ee.GetParError(0)
    ci95_ee = 1.96 * errConst_ee  # 95% confidence interval
    print(f"Error = {ci95_ee}")
    Err_ee = math.sqrt((errConst_ee * errConst_ee) + (0.0004 * 0.0004))
    print(f"ci95_ee = {ci95_ee}, Err = {Err_ee}")

    # Display the fit result on padL
    fit_result_ee = TLatex()
    fit_result_ee.SetNDC()
    fit_result_ee.SetTextSize(0.08)
    fit_result_ee.SetTextAlign(13)
    fit_result_ee.SetTextColor(kBlue-9)
    textConst_ee = f"EE Const Fit: SF = {parConst_ee:.3f} #pm {Err_ee:.3f}"
    fit_result_ee.DrawLatex(0.25, 0.85, textConst_ee)

    hline = TLine(90, 1.0, 3000, 1.0)
    hline.SetLineStyle(2)
    hline.SetLineColor(kGray)
    hline.Draw()

    canvas_ee.SaveAs("cee_1sfpt_22postEE_sf_fit.png")

# Run the function
draw1D()
