#include "PlotsMaker.h"
#include "PlotsMaker.h"
#include "TApplication.h"
#include <TCanvas.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TGraph.h>
#include "PlotsMaker.h"
#include "TF1.h"
#include "TGraphErrors.h"

void PlotsMaker::MakeHistogram(std::vector<int> info, std::string filename){
    std::string destination = filename;
    // Create a ROOT canvas
    TCanvas *c1 = new TCanvas("c1", "Histogram", 800, 600);
    // Create a histogram
    TH1F *hist = new TH1F("hist", filename.c_str(), info.size(), 0, info.size());
    // Fill the histogram with the info
    for (int i = 0; i < info.size(); ++i) {
        hist->SetBinContent(i+1, info[i]);
    }
    // Set histogram style
    hist->SetFillColor(38);
    // Draw the histogram
    hist->Draw();
    // Update the canvas to display the histogram
    c1->Update();
    c1->SaveAs(destination.c_str());
    // Wait for user input to exit the application
    c1->WaitPrimitive();
    delete hist;
    delete c1;
}

void PlotsMaker::MakeHistogram(std::vector<double> info, std::string filename, std::string title, std::string xAxisLabel, std::string yAxisLabel) {
    std::string destination = filename;
    
    // Create a ROOT canvas
    TCanvas *c1 = new TCanvas("c1", title.c_str(), 800, 600);
    
    // Create a histogram
    TH1F *hist = new TH1F("hist", title.c_str(), info.size(), 0, info.size());
    
    // Fill the histogram with the info
    for (int i = 0; i < info.size(); ++i) {
        hist->SetBinContent(i+1, info[i]);
    }
    
    // Set histogram style
    hist->SetFillColor(38);

    hist->SetStats(0);
    
    // Draw the histogram
    hist->Draw();
    
    // Set title and axis labels
    hist->SetTitle(title.c_str());
    hist->GetXaxis()->SetTitle(xAxisLabel.c_str());
    hist->GetYaxis()->SetTitle(yAxisLabel.c_str());
    hist->GetXaxis()->CenterTitle();
    hist->GetYaxis()->CenterTitle();
    hist->GetYaxis()->SetTitleOffset(1.5);
    hist->GetYaxis()->SetTitleOffset(1.5);
    
    // Add a grid to the background
    gPad->SetGrid();
    
    // Update the canvas to display the histogram
    c1->Update();
    c1->SaveAs(destination.c_str());
    
    // Wait for user input to exit the application
    c1->WaitPrimitive();
    
    // Clean up
    delete hist;
    delete c1;
}

void PlotsMaker::MakeHistogram2D(std::vector<std::vector<int>> info, std::string filename){
    std::string destination = filename;
    
    // Determine the dimensions of the histogram
    int nx = info.size(); // Number of bins along x-axis
    int ny = info[0].size(); // Number of bins along y-axis

    // Create a ROOT canvas
    TCanvas *c1 = new TCanvas("c1", "2D Histogram", nx, ny);
    
    // Set grayscale color palette
    gStyle->SetPalette(kGreyScale);
    
    // Create a 2D histogram
    TH2F *hist2D = new TH2F("hist2D", filename.c_str(), nx, 0, nx, ny, 0, ny);
    hist2D->SetMinimum(-0.1);
    
    // Fill the histogram with the info
    for (int col = 0; col < nx; col++) {
        for (int row = 0; row < ny; row++) {
            hist2D->Fill(col+0.5, ny-row-0.5, info[col][row]);
        }
    }

    int total = nx*ny;
    int count = 0;
    for (int col = 0; col < nx; col++) {
        for (int row = 0; row < ny; row++) {
            if(info[col][row] == hist2D->GetBinContent(col+0.5, ny-row-0.5)){count += 1;}
        }
    }
    
    std::cout << "TOTAL EQUALITY: " << (double)count/(double)total << std::endl;


    // Draw the 2D histogram
    hist2D->Draw("COLZ");
    
    // Update the canvas to display the histogram
    c1->Update();
    
    // Save the canvas as an image file
    c1->SaveAs(destination.c_str());
    
    // Wait for user input to exit the application
    c1->WaitPrimitive();
    
    // Clean up
    delete hist2D;
    delete c1;
}

void PlotsMaker::MakePointsPlot(std::vector<int>info , std::string filename){
    std::cout << "Empty" << std::endl;
}

void PlotsMaker::MakePlotWithStringX(std::map<std::string, std::pair<int, double>> data, std::string graphTitle, std::string xAxisLabel, std::string yAxisLabel, std::string filename){
    TCanvas *canvas = new TCanvas("c1", "Graph", 800, 600);
    TGraph *graph = new TGraph(data.size());

    // Add data points to the graph
    for (const auto& entry : data) {
        std::cout << "Adding point at index "<< ": X = " << entry.second.first << ", Y = " << entry.second.second << std::endl;
        graph->SetPoint(graph->GetN(), entry.second.first, entry.second.second); // SetPoint(index, x, y)
    }

    std::cout << "Number of points added: " << graph->GetN() << std::endl;
    
    graph->SetTitle(graphTitle.c_str());
    graph->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph->GetYaxis()->SetTitle(yAxisLabel.c_str());
    canvas->cd();
    graph->Draw("AP");
    graph->SetMarkerSize(0.5); // Set marker size (adjust as desired)
    canvas->SetGrid();
    canvas->Update();

    // Save canvas as an image file
    std::string destination = filename;
    canvas->SaveAs(destination.c_str());
    canvas->Draw();

    // Clean up
    delete graph;
    delete canvas;
}

void PlotsMaker::Draw(const std::vector<double>& x, const std::vector<double>& y, std::string s,
                        std::string title, std::string xAxisLabel, std::string yAxisLabel) {
    // Create a canvas
    TCanvas* canvas = new TCanvas("canvas", "Plot", 800, 600);

    // Create a TGraph object with the given x and y vectors
    TGraph* graph = new TGraph(x.size(), &x[0], &y[0]);

    // Set the title if provided
    if (!s.empty()) {
        graph->SetTitle(s.c_str());
    }

    // Draw the graph with points
    graph->SetMarkerStyle(20); // Set marker style
    graph->SetMarkerSize(0.8); // Set marker size
    graph->Draw("AP"); // Draw the graph with axes and points
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph->GetYaxis()->SetTitle(yAxisLabel.c_str());

    graph->GetXaxis()->CenterTitle();
    graph->GetYaxis()->CenterTitle();
    graph->GetYaxis()->SetTitleOffset(1.5);
    graph->GetYaxis()->SetTitleOffset(1.5);
    

    gPad->SetGrid();

    // Update the canvas
    canvas->Update();

    // Save the plot as a PDF
    std::string dest = s;
    canvas->SaveAs(dest.c_str());

    // Display the canvas
    canvas->Draw();
    delete canvas;
    delete graph;
}

void PlotsMaker::MakeLinearFitPlot(const std::vector<double>& x, const std::vector<double>& error_x, 
                                   const std::vector<double>& y, const std::vector<double>& error_y,
                                   const std::string& filename, const std::string& title,
                                   const std::string& xAxisLabel, const std::string& yAxisLabel) {
    std::string destination = filename;

    // Create a canvas
    TCanvas* canvas = new TCanvas("canvas", "Linear Fit Plot", 800, 600);

    // Create TGraphErrors object with the given x, y, error_x, and error_y arrays
    TGraphErrors* graph = new TGraphErrors(x.size(), &x[0], &y[0], &error_x[0], &error_y[0]);

    // Perform linear fit
    TF1* linearFit = new TF1("linearFit", "pol1", x.front(), x.back());
    graph->Fit("linearFit", "Q");

    // Set titles and labels
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph->GetYaxis()->SetTitle(yAxisLabel.c_str());

    // Center the axis labels
    graph->GetXaxis()->CenterTitle();
    graph->GetYaxis()->CenterTitle();

    // Set title offsets
    graph->GetXaxis()->SetTitleOffset(1.2);
    graph->GetYaxis()->SetTitleOffset(1.2);

    // Set grid
    gPad->SetGrid();

    // Draw the graph with points and error bars
    graph->SetMarkerStyle(20); // Set marker style
    graph->SetMarkerSize(1.0); // Set marker size
    graph->Draw("AP"); // Draw the graph with axes, points, and error bars

    // Draw the linear fit curve
    linearFit->Draw("SAME");

    // Update the canvas
    canvas->Update();

    // Save the plot as a PDF
    canvas->SaveAs(destination.c_str());

    // Display the canvas
    canvas->Draw();

    // Print fit results
    double slope = linearFit->GetParameter(1);
    double slopeError = linearFit->GetParError(1);
    double intercept = linearFit->GetParameter(0);
    double interceptError = linearFit->GetParError(0);

    std::cout << "Linear Fit Results for: " << filename << std::endl;
    std::cout << "Slope: " << slope << " ± " << slopeError << std::endl;
    std::cout << "Intercept: " << intercept << " ± " << interceptError << std::endl;
    std::cout <<"===================="<< std::endl;

    // Clean up
    delete canvas;
    delete graph;
}

void PlotsMaker::MakeLinearPlot(const std::vector<double>& x, const std::vector<double>& error_x, 
                                const std::vector<double>& y, const std::vector<double>& error_y,
                                const std::string& filename, const std::string& title,
                                const std::string& xAxisLabel, const std::string& yAxisLabel,
                                double slope, double intercept) {
    std::string destination = filename;

    // Create a canvas
    TCanvas* canvas = new TCanvas("canvas", "Linear Plot", 800, 600);

    // Create TGraphErrors object with the given x, y, error_x, and error_y arrays
    TGraphErrors* graph = new TGraphErrors(x.size(), &x[0], &y[0], &error_x[0], &error_y[0]);

    // Ensure there are at least 4 points
    if (x.size() < 4) {
        std::cerr << "Error: Not enough data points to start the line from the 4th point." << std::endl;
        return;
    }

    // Create the linear function with the given slope and intercept
    // The range of the function is set to start from the x value of the 4th point
    TF1* linearFunction = new TF1("linearFunction", "[0] + [1]*x", x[3], x.back());
    linearFunction->SetParameter(0, intercept);
    linearFunction->SetParameter(1, slope);

    // Set titles and labels
    graph->SetTitle(title.c_str());
    graph->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph->GetYaxis()->SetTitle(yAxisLabel.c_str());

    // Center the axis labels
    graph->GetXaxis()->CenterTitle();
    graph->GetYaxis()->CenterTitle();

    // Set title offsets
    graph->GetXaxis()->SetTitleOffset(1.2);
    graph->GetYaxis()->SetTitleOffset(1.2);

    // Set grid
    gPad->SetGrid();

    // Draw the graph with points and error bars
    graph->SetMarkerStyle(20); // Set marker style
    graph->SetMarkerSize(1.0); // Set marker size
    graph->Draw("AP"); // Draw the graph with axes, points, and error bars

    // Draw the linear function
    linearFunction->Draw("SAME");

    // Update the canvas
    canvas->Update();

    // Save the plot as a PDF
    canvas->SaveAs(destination.c_str());

    // Display the canvas
    canvas->Draw();

    // Print the provided parameters
    std::cout << "Linear Plot Results for: " << filename << std::endl;
    std::cout << "Slope: " << slope << std::endl;
    std::cout << "Intercept: " << intercept << std::endl;
    std::cout << "====================" << std::endl;

    // Clean up
    delete canvas;
    delete graph;
    delete linearFunction;
}

void PlotsMaker::MakeOverlayHistograms(std::vector<double> info1, std::vector<double> info2, std::string filename,
                                        std::string title, std::string xAxisLabel, std::string yAxisLabel) {
    // Check if the sizes of the vectors match
    if (info1.size() != info2.size()) {
        std::cerr << "Error: Vector sizes do not match!" << std::endl;
        return;
    }

    std::string destination = filename;

    // Create a ROOT canvas
    TCanvas *c1 = new TCanvas("c1", "Overlay Histograms", 800, 600);

    // Create the first histogram
    TH1F *hist1 = new TH1F("hist1", (filename + "_1").c_str(), info1.size(), 0, info1.size());
    // Fill the first histogram with the data from info1
    for (int i = 0; i < info1.size(); ++i) {
        hist1->SetBinContent(i+1, info1[i]);
    }
    hist1->SetFillColorAlpha(kBlue, 0.5); // Set the fill color with some opacity

    // Draw the first histogram
    hist1->Draw("HIST");

    // Create the second histogram
    TH1F *hist2 = new TH1F("hist2", (filename + "_2").c_str(), info2.size(), 0, info2.size());
    // Fill the second histogram with the data from info2
    for (int i = 0; i < info2.size(); ++i) {
        hist2->SetBinContent(i+1, info2[i]);
    }
    hist2->SetFillColor(kRed); // Set the fill color without opacity

    // Draw the second histogram on top of the first one
    hist2->Draw("HIST SAME");

    hist2->SetTitle(title.c_str());
    hist2->GetXaxis()->SetTitle(xAxisLabel.c_str());
    hist2->GetYaxis()->SetTitle(yAxisLabel.c_str());

    gPad->SetGrid();

    // Update the canvas to display the histograms
    c1->Update();
    c1->SaveAs(destination.c_str());

    // Wait for user input to exit the application
    c1->WaitPrimitive();

    // Clean up
    delete hist1;
    delete hist2;
    delete c1;
}

void PlotsMaker::MakeTwoGraphsPlot(const std::vector<double>& x1, const std::vector<double>& y1, 
                                   const std::vector<double>& x2, const std::vector<double>& y2, 
                                   const std::string& filename, std::string title, 
                                   std::string xAxisLabel, std::string yAxisLabel,
                                   std::string legend1, std::string legend2) {
    std::string destination = filename;
    
    // Create a ROOT canvas
    TCanvas *c1 = new TCanvas("c1", "Two Graphs Plot", 1000, 800);
    
    // Create graphs
    TGraph *graph1 = new TGraph(x1.size(), &x1[0], &y1[0]);
    TGraph *graph2 = new TGraph(x2.size(), &x2[0], &y2[0]);
    
    // Set colors and marker styles for the graphs
    graph1->SetLineColor(kBlue);
    graph1->SetMarkerColor(kBlue);
    graph1->SetMarkerStyle(8); // Use circle markers
    graph1->SetMarkerSize(0.5); // Set marker size to 0.5
    
    graph2->SetLineColor(kRed);
    graph2->SetMarkerColor(kRed);
    graph2->SetMarkerStyle(8); // Use circle markers
    graph2->SetMarkerSize(0.5); // Set marker size to 0.5
    
    // Set titles for the graphs
    graph1->SetTitle(title.c_str());
    graph2->SetTitle(title.c_str());
    
    // Set labels for the x and y axes
    graph1->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph1->GetYaxis()->SetTitle(yAxisLabel.c_str());
    graph2->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph2->GetYaxis()->SetTitle(yAxisLabel.c_str());

    // Set offsets for the axis titles
    graph1->GetXaxis()->SetTitleOffset(1.2);
    graph1->GetYaxis()->SetTitleOffset(1.2);
    graph2->GetXaxis()->SetTitleOffset(1.2);
    graph2->GetYaxis()->SetTitleOffset(1.2);
    
    // Center the axis labels
    graph1->GetXaxis()->CenterTitle();
    graph1->GetYaxis()->CenterTitle();
    graph2->GetXaxis()->CenterTitle();
    graph2->GetYaxis()->CenterTitle();

    // Adjust the position of the y-axis label
    graph1->GetYaxis()->SetTitleOffset(1.5);
    graph2->GetYaxis()->SetTitleOffset(1.5);

    gPad->SetGrid();
    
    // Draw the first graph
    graph1->Draw("AP"); // "AP" option to draw with axes and points
    
    // Draw the second graph on top of the first one
    graph2->Draw("P SAME"); // "P SAME" option to overlay the second graph on top of the first one
    
    // Add a legend
    TLegend *legend = new TLegend(0.4, 0.7, 0.9, 0.9);
    legend->SetTextSize(0.03); // Adjust text size
    legend->AddEntry(graph1, legend1.c_str(), "lp");
    legend->AddEntry(graph2, legend2.c_str(), "lp");
    legend->Draw();
    
    // Update the canvas to display the graphs and legend
    c1->Update();
    
    // Save the canvas as an image file
    c1->SaveAs(destination.c_str());
    
    // Wait for user input to exit the application
    c1->WaitPrimitive();
    
    // Clean up
    delete graph1;
    delete graph2;
    delete legend;
    delete c1;
}

void PlotsMaker::MakeFiveGraphsPlot(const std::vector<double>& x1, const std::vector<double>& y1,
                                    const std::vector<double>& x2, const std::vector<double>& y2,
                                    const std::vector<double>& x3, const std::vector<double>& y3,
                                    const std::vector<double>& x4, const std::vector<double>& y4,
                                    const std::vector<double>& x5, const std::vector<double>& y5,
                                    const std::string& filename, std::string title,
                                    std::string xAxisLabel, std::string yAxisLabel,
                                    std::string legend1, std::string legend2,
                                    std::string legend3, std::string legend4,
                                    std::string legend5) {
    std::string destination = filename;
    
    // Create a ROOT canvas
    TCanvas *c1 = new TCanvas("c1", "Five Graphs Plot", 1000, 800);
    
    // Create graphs
    TGraph *graph1 = new TGraph(x1.size(), &x1[0], &y1[0]);
    TGraph *graph2 = new TGraph(x2.size(), &x2[0], &y2[0]);
    TGraph *graph3 = new TGraph(x3.size(), &x3[0], &y3[0]);
    TGraph *graph4 = new TGraph(x4.size(), &x4[0], &y4[0]);
    TGraph *graph5 = new TGraph(x5.size(), &x5[0], &y5[0]);
    
    // Set colors and marker styles for the graphs
    graph1->SetLineColor(kBlue);
    graph1->SetMarkerColor(kBlue);
    graph1->SetMarkerStyle(8); // Use circle markers
    graph1->SetMarkerSize(0.7); // Set marker size to 0.5
    
    graph2->SetLineColor(kRed);
    graph2->SetMarkerColor(kRed);
    graph2->SetMarkerStyle(8); // Use circle markers
    graph2->SetMarkerSize(0.7); // Set marker size to 0.5
    
    graph3->SetLineColor(kGreen);
    graph3->SetMarkerColor(kGreen);
    graph3->SetMarkerStyle(8); // Use circle markers
    graph3->SetMarkerSize(0.7); // Set marker size to 0.5
    
    graph4->SetLineColor(kMagenta);
    graph4->SetMarkerColor(kMagenta);
    graph4->SetMarkerStyle(8); // Use circle markers
    graph4->SetMarkerSize(0.7); // Set marker size to 0.5
    
    graph5->SetLineColor(kBlack);
    graph5->SetMarkerColor(kBlack);
    graph5->SetMarkerStyle(8); // Use circle markers
    graph5->SetMarkerSize(0.7); // Set marker size to 0.5
    
    // Set titles for the graphs
    graph1->SetTitle(title.c_str());
    graph2->SetTitle(title.c_str());
    graph3->SetTitle(title.c_str());
    graph4->SetTitle(title.c_str());
    graph5->SetTitle(title.c_str());
    
    // Set labels for the x and y axes
    graph1->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph1->GetYaxis()->SetTitle(yAxisLabel.c_str());
    graph2->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph2->GetYaxis()->SetTitle(yAxisLabel.c_str());
    graph3->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph3->GetYaxis()->SetTitle(yAxisLabel.c_str());
    graph4->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph4->GetYaxis()->SetTitle(yAxisLabel.c_str());
    graph5->GetXaxis()->SetTitle(xAxisLabel.c_str());
    graph5->GetYaxis()->SetTitle(yAxisLabel.c_str());

    // Set offsets for the axis titles
    graph1->GetXaxis()->SetTitleOffset(1.2);
    graph1->GetYaxis()->SetTitleOffset(1.2);
    graph2->GetXaxis()->SetTitleOffset(1.2);
    graph2->GetYaxis()->SetTitleOffset(1.2);
    graph3->GetXaxis()->SetTitleOffset(1.2);
    graph3->GetYaxis()->SetTitleOffset(1.2);
    graph4->GetXaxis()->SetTitleOffset(1.2);
    graph4->GetYaxis()->SetTitleOffset(1.2);
    graph5->GetXaxis()->SetTitleOffset(1.2);
    graph5->GetYaxis()->SetTitleOffset(1.2);
    
    // Center the axis labels
    graph1->GetXaxis()->CenterTitle();
    graph1->GetYaxis()->CenterTitle();
    graph2->GetXaxis()->CenterTitle();
    graph2->GetYaxis()->CenterTitle();
    graph3->GetXaxis()->CenterTitle();
    graph3->GetYaxis()->CenterTitle();
    graph4->GetXaxis()->CenterTitle();
    graph4->GetYaxis()->CenterTitle();
    graph5->GetXaxis()->CenterTitle();
    graph5->GetYaxis()->CenterTitle();

    // Adjust the position of the y-axis label
    graph1->GetYaxis()->SetTitleOffset(1.5);
    graph2->GetYaxis()->SetTitleOffset(1.5);
    graph3->GetYaxis()->SetTitleOffset(1.5);
    graph4->GetYaxis()->SetTitleOffset(1.5);
    graph5->GetYaxis()->SetTitleOffset(1.5);

    gPad->SetGrid();
    
    // Draw the graphs
    graph1->Draw("AP"); // "AP" option to draw with axes and points
    graph2->Draw("P SAME"); // Overlay the second graph on top of the first one
    graph3->Draw("P SAME"); // Overlay the third graph
    graph4->Draw("P SAME"); // Overlay the fourth graph
    graph5->Draw("P SAME"); // Overlay the fifth graph
    
    // Add a legend
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->SetTextSize(0.02); // Adjust text size
    legend->AddEntry(graph1, legend1.c_str(), "lp");
    legend->AddEntry(graph2, legend2.c_str(), "lp");
    legend->AddEntry(graph3, legend3.c_str(), "lp");
    legend->AddEntry(graph4, legend4.c_str(), "lp");
    legend->AddEntry(graph5, legend5.c_str(), "lp");
    legend->Draw();
    
    // Update the canvas to display the graphs and legend
    c1->Update();
    
    // Save the canvas as an image file
    c1->SaveAs(destination.c_str());
    
    // Wait for user input to exit the application
    c1->WaitPrimitive();
    
    // Clean up
    delete graph1;
    delete graph2;
    delete graph3;
    delete graph4;
    delete graph5;
    delete legend;
    delete c1;
}