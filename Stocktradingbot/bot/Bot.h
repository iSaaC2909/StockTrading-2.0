#ifndef AbstractBot_H
#define AbstractBot_H

#include <map>

#include "../stock/Stock.h"
#include "string.h"
#include "Position.h"
#include "Trade.h"


enum BotType
{
    CONSERVATIVE,
    AGGRESSIVE,
    PASSIVE
};
class AbstractBot {
    private:
        virtual void trade(time_t currentDay) = 0;
        std::string name;

    protected:
        double accountBalance;
        double startingBalance;
        int daysToDeposit;
        int depositPeriod;
        double depositAmount;
        double cumulativeDeposit;
        // std::unordered_map<std::string,Position *> positions;
        // std::unordered_map<time_t,std::vector<Trade *>> trades;

        void deposit(double depositAmount);
        Trade * buyStock(std::string stockSymbol,double spendingMoney);
        Trade * sellStock(std::string stockSymbol, float shares);


    public:
        //should not be public
        std::unordered_map<std::string,Position *> positions;
        std::unordered_map<time_t,std::vector<Trade *>> trades;
        std::string getName();


        AbstractBot();
        AbstractBot(std::string name,double startingBalance, int daysToDeposit, double depositAmount);
        ~AbstractBot();

        std::unordered_map<time_t,std::vector<Trade *>>  getTrades();
        std::unordered_map<std::string,Position *> getPositions();
        void checkForDeposit();

        double getPortfolioValue();
        double getProfit();

        std::map<double,Position *>* rankStocks(time_t currentDay);

        void notify(time_t currentDay,std::vector<StockSnapshot> snapshots);

        friend std::ostream& operator<<(std::ostream& out, const AbstractBot& AbstractBot);

        friend class Bot;

};

class ConservativeBot: public AbstractBot
{
    public:
        ConservativeBot();
        ConservativeBot(std::string name,double startingBalance, int daysToDeposit, double depositAmount);
        ~ConservativeBot();
    private:
        void trade(time_t currentDay);
};

class AggressiveBot: public AbstractBot
{
    public:
        AggressiveBot();
        AggressiveBot(std::string name,double startingBalance, int daysToDeposit, double depositAmount);
        ~AggressiveBot();
    private:
        void trade(time_t currentDay);
};
class PassiveBot: public AbstractBot
{
    public:
        PassiveBot();
        PassiveBot(std::string name,double startingBalance, int daysToDeposit, double depositAmount);
        ~PassiveBot();
    private:
        void trade(time_t currentDay);
};
class Bot
{
    public:
        Bot()
        {
            bot_ = NULL;
        }
        Bot(double startingBalance, int daysToDeposit, double depositAmount);
        ~Bot();
        void setBotType(BotType type);
        void setBotType(std::string Name,BotType type, double startingBalance, int depo, double depositAmount);
        void notify(time_t currentDay,std::vector<StockSnapshot> snapshots);
        void trade(time_t currentDay);
        std::vector <double> portfolioReport();
        AbstractBot * getBot(){ return this->bot_;}
    private:
        AbstractBot * bot_;
};


#endif
