module airline_ticket;

using namespace std;

AirlineTicket::AirlineTicket()
    : m_passengerName{ "Unknown Passenger" }
    , m_numberOfMiles{ 0 }
    , m_hasEliteSuperRewardsStatus{ false }
    , m_frequentFlyerNumber{std::nullopt}
{
}

AirlineTicket::~AirlineTicket()
{
    // Nothing to do in terms of cleanup
}

double AirlineTicket::calculatePriceInDollars() const
{
    if (hasEliteSuperRewardsStatus()) {
        // Elite Super Rewards customers fly for free!
        return 0;
    }
    // The cost of the ticket is the number of miles times 0.1.
    // Real airlines probably have a more complicated formula!
    return getNumberOfMiles() * 0.1;
}

const string& AirlineTicket::getPassengerName() const{ return m_passengerName; }
void AirlineTicket::setPassengerName(const string& name) { m_passengerName = name; }
// Other get and set methods have a similar implementation.

int AirlineTicket::getNumberOfMiles() const { return m_numberOfMiles; }
void AirlineTicket::setNumberOfMiles(const int& miles) { m_numberOfMiles = miles; }

bool AirlineTicket::hasEliteSuperRewardsStatus() const { return m_hasEliteSuperRewardsStatus; }
void AirlineTicket::setHasEliteSuperRewardsStatus(bool status) { m_hasEliteSuperRewardsStatus = status; }

const optional<int> AirlineTicket::getFrequentFlyerNumber() const
{
    return m_frequentFlyerNumber; 
}

void AirlineTicket::setFrequentFlyerNumber(const int& num)
{
    m_frequentFlyerNumber = num;
}
