import ROOT
import json
import numpy as np

#ROOT.gROOT.LoadMacro('tdrstyle.C')
#ROOT.gROOT.LoadMacro('CMS_lumi.C')
#ROOT.setTDRStyle()
# Load the JSON data from 'hlt.json'
#HLT_Ele115_Eff_SF_PT_Eta_2022CD_ReReco.json
#HLT_Ele115_Eff_SF_PT_Eta_2022EFG_ReReco.json
#HLT_ORALL_Eff_SF_PT_Eta_2022CD_ReReco.json
#HLT_ORALL_Eff_SF_PT_Eta_2022EFG_ReReco.json
#HLT_Pho200_Eff_SF_PT_Eta_2022CD_ReReco.json
#HLT_Pho200_Eff_SF_PT_Eta_2022EFG_ReReco.json
#with open('json/HLT_ORALL_Eff_SF_PT_Eta_2022CD_ReReco.json', 'r') as file:
#with open('json/HLT_ORALL_Eff_SF_PT_Eta_2022EFG_ReReco.json', 'r') as file:
#with open('json/HLT_Ele115ORPho200_Eff_SF_PT_Eta_2023Cv1234_ReReco.json', 'r') as file:
#with open('json/HLT_Ele115ORPho200_Eff_SF_PT_Eta_2023Dv12_ReReco.json', 'r') as file:
#with open('json/HLT_Ele115_Eff_SF_PT_Eta_2023Cv1234_ReReco.json', 'r') as file:
#with open('json/HLT_Ele115_Eff_SF_PT_Eta_2023Dv12_ReReco.json', 'r') as file:
#with open('json/HLT_Pho200_Eff_SF_PT_Eta_2023Cv1234_ReReco.json', 'r') as file:
#with open('json/HLT_Pho200_Eff_SF_PT_Eta_2023Dv12_ReReco.json', 'r') as file:

#with open('2022preEE.json', 'r') as file:
#with open('2022postEE.json', 'r') as file:
#with open('2023preBPIX.json', 'r') as file:
with open('2023postBPIX.json', 'r') as file:
    data = json.load(file)

#output_file = ROOT.TFile("SF2D_HLT_Ele115_OR_Pho200_2022CD_ReReco.root", "RECREATE")
#output_file = ROOT.TFile("SF2D_HLT_Ele115_OR_Pho200_2022EFG_ReReco.root", "RECREATE")
#output_file = ROOT.TFile("SF2D_HLT_Ele115_OR_Pho200_2023C_ReReco.root", "RECREATE")
output_file = ROOT.TFile("SF2D_HLT_Ele115_OR_Pho200_2023D_ReReco.root", "RECREATE")

#output_file = ROOT.TFile("SF2D_HLT_Ele115_2023D_ReReco.root", "RECREATE")
#output_file = ROOT.TFile("SF2D_HLT_Pho200_2023D_ReReco.root", "RECREATE")
#output_file = ROOT.TFile("SF2D_HLT_Ele115_OR_Pho200_2023D_ReReco.root", "RECREATE")

ROOT.gROOT.SetBatch(True)
pt_bins = sorted({entry['MinPT'] for entry in data} | {entry['MaxPT'] for entry in data})
eta_bins = sorted({entry['MinEta'] for entry in data} | {entry['MaxEta'] for entry in data})

pt_bin_array = np.array(pt_bins, dtype=float)
eta_bin_array = np.array(eta_bins, dtype=float)

# Create a blank histogram for the x and y axis setup
#hist_sf = ROOT.TH2D("hist", "HLT_Ele115_CaloIdVT_GsfTrkIdT;|#eta_{SC}|;Electron p_{T} [GeV]", len(eta_bin_array)-1, eta_bin_array, len(pt_bin_array)-1, pt_bin_array)
#hist_err = ROOT.TH2D("hist", "HLT_Ele115_CaloIdVT_GsfTrkIdT;|#eta_{SC}|;Electron p_{T} [GeV]", len(eta_bin_array)-1, eta_bin_array, len(pt_bin_array)-1, pt_bin_array)
#hist_sf = ROOT.TH2D("hist_sf", "HLT_Photon200;|#eta_{SC}|;Electron p_{T} [GeV]", len(eta_bin_array)-1, eta_bin_array, len(pt_bin_array)-1, pt_bin_array)
#hist_err = ROOT.TH2D("hist_err", "HLT_Photon200;|#eta_{SC}|;Electron p_{T} [GeV]", len(eta_bin_array)-1, eta_bin_array, len(pt_bin_array)-1, pt_bin_array)
hist_sf = ROOT.TH2D("hist_sf",   "SF HLT_Ele115_CaloIdVT_GsfTrkIdT || HLT_Photon200;|#eta_{SC}|;Electron p_{T} [GeV]", len(eta_bin_array)-1, eta_bin_array, len(pt_bin_array)-1, pt_bin_array)
hist_err = ROOT.TH2D("hist_err", "SF uncertainty HLT_Ele115_CaloIdVT_GsfTrkIdT || HLT_Photon200;|#eta_{SC}|;Electron p_{T} [GeV]", len(eta_bin_array)-1, eta_bin_array, len(pt_bin_array)-1, pt_bin_array)

for entry in data:
    eta_center = (entry['MinEta'] + entry['MaxEta']) / 2
    pt_center = (entry['MinPT'] + entry['MaxPT']) / 2
    sf_value = entry['SF'] 
    sf_up = entry['SFUp']
    sf_down = entry['SFDown']

    binx = hist_sf.GetXaxis().FindBin(eta_center)
    biny = hist_sf.GetYaxis().FindBin(pt_center)
    
    hist_sf.SetBinContent(binx, biny, sf_value)
    hist_err.SetBinContent(binx, biny, sf_down)

    #hist_sf.Fill(eta_center, pt_center, sf_value)
    #hist_sf.SetBinContent(eta_center, pt_center, sf_value)
    #hist_err.SetBinError(eta_center, pt_center, sf_down)

can_sf = ROOT.TCanvas("can_sf", "Canvas", 650, 800)
can_sf.SetLogy()
hist_sf.SetStats(0)
hist_sf.Draw("colz TEXT")
ROOT.gStyle.SetPaintTextFormat("4.3f")
hist_sf.SetMarkerSize(1.5)
hist_sf.GetXaxis().SetTitleSize(0.05)
hist_sf.GetXaxis().SetTitleOffset(0.8)
hist_sf.GetYaxis().SetTitleSize(0.05)
hist_sf.GetYaxis().SetTitleOffset(0.8)
hist_sf.GetYaxis().SetRangeUser(130., 3000.)
#hist_sf.GetYaxis().SetRangeUser(240., 2000.)

latex = ROOT.TLatex()
latex.SetNDC()
latex.SetTextFont(42)
latex.SetTextSize(0.04)
#latex.DrawLatex(0.67, 0.91, "8.0 fb^{-1} (13.6 TeV)") #22preEE
#latex.DrawLatex(0.68, 0.91, "26.7 fb^{-1} (13.6 TeV)") #22postEE
#latex.DrawLatex(0.67, 0.91, "17.8 fb^{-1} (13.6 TeV)") #23preBPIX
latex.DrawLatex(0.67, 0.91, "9.45 fb^{-1} (13.6 TeV)") #23postBPIX
#latex.SetTextSize(0.04)
#latex.DrawLatex(0.1, 0.85, "CMS Preliminary")

can_err = ROOT.TCanvas("can_err", "Canvas", 650, 800)
can_err.SetLogy()
hist_err.SetStats(0)
hist_err.Draw("colz TEXT")
ROOT.gStyle.SetPaintTextFormat("4.3f")
hist_err.SetMarkerSize(1.5)
hist_err.GetXaxis().SetTitleSize(0.05)
hist_err.GetXaxis().SetTitleOffset(0.8)
hist_err.GetYaxis().SetTitleSize(0.05)
hist_err.GetYaxis().SetTitleOffset(0.8)
hist_err.GetYaxis().SetRangeUser(130., 2000.)
#hist_err.GetYaxis().SetRangeUser(240., 2000.)
latex.SetNDC()
latex.SetTextFont(42)
latex.SetTextSize(0.04)
#latex.DrawLatex(0.67, 0.91, "8.0 fb^{-1} (13.6 TeV)") #22preEE
#latex.DrawLatex(0.68, 0.91, "26.7 fb^{-1} (13.6 TeV)") #22postEE
#latex.DrawLatex(0.67, 0.91, "17.8 fb^{-1} (13.6 TeV)") #23preBPIX
latex.DrawLatex(0.67, 0.91, "9.45 fb^{-1} (13.6 TeV)") #23postBPIX
#latex.SetTextSize(0.04)
#latex.DrawLatex(0.1, 0.85, "CMS Preliminary")

# Show the can_sf
#can_sf.Draw()
#can_sf.Update()
#can_sf.SaveAs("SF_2d_pho200_23rerecoD.png")
#can_err.SaveAs("SFerr_2d_pho200_23rerecoD.png")
#can_sf.SaveAs("SF_2d_ele115_23rerecoD.png")
#can_err.SaveAs("SFerr_2d_ele115_23rerecoD.png")

#23postBPIX
can_sf.SaveAs("SF_2d_ele115_or_pho200_23rerecoD.png")
can_err.SaveAs("SFerr_2d_ele115_or_pho200_23rerecoD.png")

#23preBPIX
#can_sf.SaveAs("SF_2d_ele115_or_pho200_23rerecoC.png")
#can_err.SaveAs("SFerr_2d_ele115_or_pho200_23rerecoC.png")

#22postEE
#can_sf.SaveAs("SF_2d_ele115_or_pho200_22rerecoEFG.png")
#can_err.SaveAs("SFerr_2d_ele115_or_pho200_22rerecoEFG.png")

#22preEE
#can_sf.SaveAs("SF_2d_ele115_or_pho200_22rerecoCD.png")
#can_err.SaveAs("SFerr_2d_ele115_or_pho200_22rerecoCD.png")

hist_sf.Write()
hist_err.Write()
can_sf.Write()
can_err.Write()
print("end")
output_file.Close()
