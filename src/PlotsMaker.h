#ifndef __PLOTSMAKER__
#define __PLOTSMAKER__

#include <iostream>
#include <vector>
#include <string>
#include <map>

class PlotsMaker{
    public:
        PlotsMaker() = default;
        ~PlotsMaker() = default;

        //make plots
        void MakeHistogram(std::vector<int> info, std::string filename);
        void MakeHistogram(std::vector<double> info, std::string filename, std::string title, std::string xAxisLabel, std::string yAxisLabel);
        void MakeHistogram2D(std::vector<std::vector<int>> info, std::string filename);

        void MakePointsPlot(std::vector<int> info, std::string filename);
        void MakePlotWithStringX(std::map<std::string, std::pair<int, double>> data, std::string graphTitle, std::string xAxisLabel, std::string yAxisLabel, std::string filename);
        void Draw(const std::vector<double>& x, const std::vector<double>& y, std::string s, 
                    std::string title, std::string xAxisLabel, std::string yAxisLabel);
        
        void MakeLinearFitPlot(const std::vector<double>& x, const std::vector<double>& error_x, 
                                    const std::vector<double>& y,const std::vector<double>& error_y,
                                   const std::string& filename, const std::string& title,
                                   const std::string& xAxisLabel, const std::string& yAxisLabel);
        
        void MakeLinearPlot(const std::vector<double>& x, const std::vector<double>& error_x, 
                                const std::vector<double>& y, const std::vector<double>& error_y,
                                const std::string& filename, const std::string& title,
                                const std::string& xAxisLabel, const std::string& yAxisLabel,
                                double slope, double intercept);

        void MakeOverlayHistograms(std::vector<double> info1, std::vector<double> info2, std::string filename,
                                    std::string title, std::string xAxisLabel, std::string yAxisLabel);


        void MakeTwoGraphsPlot(const std::vector<double>& x1, const std::vector<double>& y1, 
                                   const std::vector<double>& x2, const std::vector<double>& y2,  const std::string& filename,
                                   std::string title, std::string xAxisLabel, std::string yAxisLabel,
                                        std::string legend1, std::string legend2);

        void MakeFiveGraphsPlot(const std::vector<double>& x1, const std::vector<double>& y1,
                                const std::vector<double>& x2, const std::vector<double>& y2,
                                const std::vector<double>& x3, const std::vector<double>& y3,
                                const std::vector<double>& x4, const std::vector<double>& y4,
                                const std::vector<double>& x5, const std::vector<double>& y5,
                                const std::string& filename, std::string title,
                                std::string xAxisLabel, std::string yAxisLabel,
                                std::string legend1, std::string legend2,
                                std::string legend3, std::string legend4,
                                std::string legend5);

    private:

};

#endif