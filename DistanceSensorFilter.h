#ifndef DISTANCE_SENSOR_FILTER_H
#define DISTANCE_SENSOR_FILTER_H

#define MAX_VALUE_FOR_SENSOR_POLLING_COUNTER      20
#define MAX_VALUE_FOR_SENSOR_CURRENT_COUNTER      15
#define FILTER_RESULT_MERGE_ALPHA                 0.7
#define SENSOR_DATA_VARIANCE                      3
#define COUNTER_DIFFERENCE_TO_UPDATE_FILTER_RES   SENSOR_DATA_VARIANCE
#define MAX_POLLING_COUNTER_TO_UPDATE_FILTER_VAL  6

class DistanceSensorFilter
{
public:
    DistanceSensorFilter()
    {
        // filter vars
        biggerValCounter = 0;
        smallerValCounter = 0;
        currentValCounter = 0;

        sensorPollingCounter = 0;

        returnVal = -1;
    }

    ~DistanceSensorFilter()
    {

    }

    int Filter(int sensorValue)
    {
        if (returnVal < 0)
            returnVal = sensorValue;

        if (abs(sensorValue - returnVal) < SENSOR_DATA_VARIANCE)
            currentValCounter++;
        else if (sensorValue < returnVal)
            smallerValCounter++;
        else
            biggerValCounter++;

        sensorPollingCounter++;

        bool isUpdateVal = sensorPollingCounter > MAX_POLLING_COUNTER_TO_UPDATE_FILTER_VAL;
        if (isUpdateVal)
        {
            bool isValBigger  = biggerValCounter  > currentValCounter + COUNTER_DIFFERENCE_TO_UPDATE_FILTER_RES;
            bool isValSmaller = smallerValCounter > currentValCounter + COUNTER_DIFFERENCE_TO_UPDATE_FILTER_RES;
            isUpdateVal = isValBigger || isValSmaller;
        }

        if (isUpdateVal)
        {
            returnVal = sensorValue * FILTER_RESULT_MERGE_ALPHA + returnVal * (1.0 - FILTER_RESULT_MERGE_ALPHA);
        }

        if (isUpdateVal || sensorPollingCounter > MAX_VALUE_FOR_SENSOR_POLLING_COUNTER || currentValCounter > MAX_VALUE_FOR_SENSOR_CURRENT_COUNTER)
        {
            biggerValCounter = 0;
            currentValCounter = 0;
            smallerValCounter = 0;
            sensorPollingCounter = 0;
        }

        return returnVal;
    }

private:
    // filter vars
    int biggerValCounter;
    int smallerValCounter;
    int currentValCounter;

    int sensorPollingCounter;

    int returnVal;
};

#endif
