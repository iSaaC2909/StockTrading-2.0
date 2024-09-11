#include "Position.h"

#include <iostream>

Position::Position(/* args */)
{
    this->avg_cost = 0;
    this->shares = 0;
    
}

Position::~Position()
{
    
}

Position::Position(const Position &source)
{
    this->shares = source.shares;
    this->avg_cost = source.avg_cost;
}

void Position::addShares(float shares)
{
    this->shares += shares;
}
void Position::subShares(float shares)
{
    this->shares -= shares;
}
void Position::setAvgcost(double price,float shares)
{
    if(this->getShares() < 0.009)
    {
        this->avg_cost =   price; 
        return;     
    }
    float prevShares = this->getShares();
    double prevAvg_cost = this->getAvgCost();
    float total_shares = shares + prevShares;
    double total_cost = prevAvg_cost + price;
    this->avg_cost = total_cost/total_shares;
}

double Position::getCurrentPrice(void)
{
    if(snapshots.size() > 0)
        return this->snapshots.back().getLow();
    else return 0;
}
std::ostream& operator<<(std::ostream& out, const Position& position)
{
    
    std::cout << "Shares: " << position.shares << " at average cost " << position.avg_cost;

    return out;
}