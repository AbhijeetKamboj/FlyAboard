#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <string>
#include <array>
#include <vector>
#include <random>

class RandomGenerator {
public:
    // A destination is { city, latitude, longitude }
    using Destination = std::array<std::string,3>;

    RandomGenerator();

    /// Generates a random 6-digit ID (>=20000) and stores it.
    void randomIDGen();

    /// Returns the last generated ID as string.
    const std::string& getRandomNumber() const;

    /// Picks two distinct random destinations.
    std::array<Destination,2> randomDestinations();

    /// Returns a random number of seats [75..499].
    int randomNumOfSeats();

    /**
     * Generates a flight-number with `lettersCount` random letters,
     * then "-" and (numSeats/divisor).
     */
    std::string randomFlightNumbGen(int lettersCount, int divisor);

private:
    std::string              randomNum_;
    std::mt19937             mt_;
    std::uniform_int_distribution<int>    distID_;
    std::uniform_int_distribution<int>    distSeats_;
    std::uniform_int_distribution<int>    distLetter_;
    std::uniform_int_distribution<size_t> distDest_;

    // All possible destinations
    static const std::vector<Destination> DESTINATIONS;
};

#endif // RANDOM_GENERATOR_HPP
