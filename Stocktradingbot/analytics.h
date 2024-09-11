#include <vector>
#include <cmath>
#include "stock/StockSimulation.h"
#include "bot/Bot.h"
#include "gnuplot-iostream.h"
#include "temporal/TemporalIterator.h"
#include "bot/Position.h"
#include "bot/Trade.h"

 void displayStats(time_t start, time_t end){
     std::string sStart=timeToString(start),
                 sEnd=timeToString(end);
     std::vector<std::string> timeData;
     std::vector<double> values;
     std::vector<double> values2;
     std::vector<std::pair<std::string,double>> data;
     //Generate X-axis for time
     TemporalIterator iter(start,end,DAILY);
     while(iter.hasNext())
     {
         timeData.push_back(timeToString(iter.next()));
     }

     //Collect stock data
     for(int i = 0; i < timeData.size();i++)
     {
         values.push_back(i * 400);
     }
     //Collect stock data
     for(int i = 0; i < timeData.size();i++)
     {
         values2.push_back(2*i * 400);
     }


     for(int i =0; i < timeData.size(); i++)
     {
         std::string time = timeData[i];
         double y = values[i];
         data.push_back(std::make_pair(time,y));
     }

     Gnuplot gp;
     gp << "set xdata time\n";
     gp << "set timefmt '\"%Y-%m-%d\"'\n";
     gp << "set xrange ['" << sStart <<"':'" << sEnd<< "']\n";
     gp << "set timefmt '%Y-%m-%d'\n";
     gp << "plot '-' using 1:2 with points title 'test'\n";
     gp.send1d(boost::make_tuple(timeData, values, values2));


 }

#include <vector>
#include <cmath>


// #include "stock/StockSimulation.h"
// #include "bot/Bot.h"
#include "gnuplot-iostream.h"
#include "temporal/TemporalIterator.h"
#include "bot/Position.h"
#include "bot/Trade.h"
#include "bot/Bot.h"
#include <fstream>
#include <iomanip>
void exportData(time_t start, time_t end,std::unordered_map<time_t,std::vector<Trade *>> trades, std::string name="Bot");

void displayStats(time_t start, time_t end,
    std::vector<double> portfolioVector, std::string title="Portfolio");
