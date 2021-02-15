#ifndef STOP_COLLECTION_H_INCLUDED
#define STOP_COLLECTION_H_INCLUDED

#include <vector>

#include "Stop.hpp"

/**
 * Helper for working with multiple stop objects.
 * 
 */
class StopCollection
{
protected:
    std::vector<Stop *> stops;

public:
    /**
     * Construct a new Stop Collection object.
     * 
     * @param stops A vector containing all available stop objects.
     */
    StopCollection(std::vector<Stop *> stops);

    /**
     * Gets the vector containing all stop objects.
     * 
     * @return std::vector<Stop *> The vector containing all stop objects.
     */
    std::vector<Stop *> getStops();

    /**
     * Returns the first stop that was found by the anonymous finder function.
     * 
     * Each available stop is passed to the finder one by one. As soon as the 
     * finder returns the value true, the stop is output.
     * 
     * @param finder The anonymous finder function that determines what stops 
     *      should be searched.
     * @return Stop* The stop object that was found.
     * 
     * @throws std::invalid_argument Thrown when no stop was found.
     */
    Stop *findFirst(std::function<bool(Stop *)> finder);

    /**
     * Pass every stop one by one to the handler to do something with every stop.
     * 
     * @param handler The handler that handles every stop.
     */
    void forEach(std::function<void(Stop *)> handler);
};

#endif // #ifndef STOP_COLLECTION_H_INCLUDED