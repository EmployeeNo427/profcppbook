export module airline_ticket;

import std;

export class AirlineTicket
{
public:
    AirlineTicket();
    ~AirlineTicket();

    double calculatePriceInDollars() const;

    const std::string& getPassengerName() const;
    void setPassengerName(const std::string& name);

    int getNumberOfMiles() const;
    void setNumberOfMiles(const int& miles);

    bool hasEliteSuperRewardsStatus() const;
    void setHasEliteSuperRewardsStatus(bool status);

    const std::optional<int> getFrequentFlyerNumber() const;
    void setFrequentFlyerNumber(const int& num);
private:
    std::string m_passengerName;
    int m_numberOfMiles;
    bool m_hasEliteSuperRewardsStatus;
    std::optional<int> m_frequentFlyerNumber;
};