#include "analytics.h"

void exportData(time_t start, time_t end,std::unordered_map<time_t,std::vector<Trade *>> trades,std::string name){
    std::ofstream outfile;
    std::string filename = name + "_" + timeToString(start) + "to" + timeToString(end) +".txt";
    outfile.open(filename);
    outfile << std::showpoint<< std::setprecision(2) ;
    outfile << std::setw(10) << "Day"<< std::setw(10) << "Stock" << std::setw(10) << "Amount" << std::setw(10) << "Value";
    outfile << std::setw(15) << "Buy/Sell\n";
    std::unordered_map<std::string,Position *> positions = bot->getPositions();
    for(auto pair : trades){
        outfile << std::setw(10) << timeToString(pair.first) <<std::endl; // output day
         if(pair.second == NULL){
             outfile <<"NO TRADES FOR THE DAY!" << std::endl;
         }
        for(auto tradePtr: pair.second){//V is a trade
            double value = 0;
            //std::cout << pair.first << '\t' << *(pair.second) << std::endl;
            outfile << std::setw(10) <<" ";
            value += tradePtr->shares * tradePtr->sharePrice;
            outfile << std::setw(10) << tradePtr->stockSymbol << std::setw(10) << tradePtr->shares;
            outfile << std::setw(10) << tradePtr->sharePrice;
            if(tradePtr->type == SELL){
                outfile << std::setw(15) << "SELL\n";
            }else{
            outfile << std::setw(15) << "BUY\n";
            }
        }

    }
    outfile.close();
}

void displayStats(time_t start, time_t end,
    std::vector<double> portfolioVector,std::string title){
    std::vector<double> portfolioValue = bot->portfolioReport();


    std::string sStart=timeToString(start),
                sEnd=timeToString(end);
    std::vector<std::string> timeData;
    std::vector<double> values;
    std::vector<double> values2;
    
    //Generate X-axis for time
    TemporalIterator iter(start,previousDay(end),DAILY);
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
         values2.push_back(2*i * 100);
     }
     for( const auto& n: bot->bot_->trades){//iterate thru trade vectors
 double sum = 0;
         try{

         const std::vector<Trade> t = n.second;
         for(int i = 0;i < n.second.size();i++ ){//each trade
             //Trade *temp =  n.second[i];
             if(n.second[i]->type == BUY){
                 sum += n.second[i]->shares * n.second[i]->sharePrice;
             }
         }
     }catch(std::bad_alloc){
         std::cout <<"Hello" << std::endl;

     }
         portfolioValue.push_back(sum);
     }

     std::vector<std::pair<std::string,double>> data;
    std::vector<boost::tuple<std::string,double,double>> data;
    for(int i =0; i < timeData.size(); i++)
    {
        std::string time = timeData[i];
        double y = portfolioVector[i];
        double x =  portfolioVector[i] -1;
        data.push_back(boost::make_tuple(time,y,x));
    }

    Gnuplot gp;
    gp << "set terminal png\n";
    gp << "set xdata time\n";
    gp << "set timefmt '%Y-%m-%d'\n";
    gp << "set xrange ['" << sStart <<"':'" << sEnd<< "']\n";
    gp << "set timefmt '%Y-%m-%d'\n";
    gp << "set output '" << title << "_" + timeToString(start)<< "to" <<timeToString(end) <<".png'\n";// 'my_graph_1.png'\n";
    gp << "plot '-'  using 1:2 with lines title ' " << title <<"'\n";




    gp.send1d(data);



}
