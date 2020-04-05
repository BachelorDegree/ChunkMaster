#pragma once

class ChunkFSM
{
public:
    enum Status
    {
        STANDBY     = 0,
        WRITING     = 1,
        ERROR       = 2,
        MOVING      = 3,
        EMPTY       = 4,
        EMPTYERROR  = 5,
        NOTKNOWN    = 6
    };

    enum Action
    {
        SET_DIRTY,
        RECOVERED,
        ALLOCATE_UPLOAD,
        FINISH_UPLOAD,
        START_MOVING,
        FINISH_MOVING_AS_SOURCE,
        FINISH_MOVING_AS_DESTINATION
    };

    static Status Transit(Status iCurrentState, Action iAction);
};
