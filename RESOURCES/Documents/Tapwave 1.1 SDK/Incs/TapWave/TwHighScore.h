/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __TWHIGHSCORE_H__
#define __TWHIGHSCORE_H__

#include <PalmOS.h>

#ifdef __cplusplus
extern "C" {
#endif

#define twHighScoreErrInternal       (0 + twHighScoreErrorBase)
#define twHighScoreErrNotRegistered  (1 + twHighScoreErrorBase)

typedef struct TwHighScoreTag {
    UInt32 score;                   // normalized score
    UInt32 checksum;                // score validater
    UInt32 dateAndTime;             // time in seconds (local time) the score was achieved
    Char *userString;               // user visible versions of the scores, or NULL
} TwHighScoreType;

typedef struct TwHighScoreSummaryTag {
    UInt16 numLocalScoresToKeep;    // from register
    UInt16 numServerScoresToKeep;   // from register
    Boolean reportScoresToServer;   // from register
    UInt8 pad[3];
    UInt32 timeSynced;              // time in seconds (local time) of last server connection
    Char *gameName;                 // from register, points to data in the same ptr
    UInt16 numLocalScores;          // number of scores available in local pool
    UInt16 numServerScores;         // number of scores available in server pool
    UInt32 highestLocalScore;       // best (normalized) local score
    UInt32 lowestLocalScore;        // lowest (normalized) local score kept
    UInt32 highestServerScore;      // best (normalized) server score
    UInt32 lowestServerScore;       // lowest (normalized) server score available
} TwHighScoreSummaryType;

// scores from the local device
#define twHighScorePoolLocal    (0)

// scores sync'd from the score server/website
#define twHighScorePoolServer   (1)


Err TwHighScoreRegister(
        UInt32 creatorID,
        UInt16 scoreType,
        UInt16 numLocalScoresToKeep,
        UInt16 numServerScoresToKeep,
        Boolean reportScoresToServer,
        const Char *gameName)
    TAL_TRAP(trapTwHighScoreRegister);


Err TwHighScoreUnregister(
        UInt32 creatorID,
        UInt16 scoreType)
    TAL_TRAP(trapTwHighScoreUnregister);


Err TwHighScoreReport(
        UInt32 creatorID,
        UInt16 scoreType,
        TwHighScoreType *highScoreP)
    TAL_TRAP(trapTwHighScoreReport);


TwHighScoreSummaryType * TwHighScoreGetSummary(
        UInt32 creatorID,
        UInt16 scoreType)
    TAL_TRAP(trapTwHighScoreGetSummary);


TwHighScoreType *TwHighScoreGetDetails(
        UInt32 creatorID,
        UInt16 scoreType,
        UInt16 whichPool,           // TwHighScorePoolLocal or TwHighScorePoolServer
        UInt16 index)
    TAL_TRAP(trapTwHighScoreGetDetails);

UInt16 TwHighScoreGetTournament(UInt32 creatorID, UInt16 scoreTypeIn, Char *code)
    TAL_TRAP(trapTwHighScoreGetTournament);

#ifdef __cplusplus
}
#endif

#endif /* __TWHIGHSCORE_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
