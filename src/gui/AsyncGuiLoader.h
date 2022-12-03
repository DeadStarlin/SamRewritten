#pragma once

#include "../../steam/steamtypes.h"
#include "../schema_parser/UserGameStatsSchemaParser.h"
#include <mutex>
#include <future>

#define MAX_CONCURRENT_ICON_DOWNLOADS 10

class MainPickerWindow;

/**
 * Information for implementing lazy loading of games.
 * source: https://www.bassi.io/pages/lazy-loading/
 */

/* states in the GUI-loading FSMs */
enum {
    APPS_STATE_STARTED,                 /* start state */
    APPS_STATE_WAITING_FOR_OWNED_APPS,  /* waiting for owned apps thread to finish */
    APPS_STATE_LOADING_GUI,             /* feeding game rows to the model */
    APPS_STATE_DOWNLOADING_ICONS,       /* fire off icon downloads (to be added to the model) */
    APPS_STATE_FINISHED                 /* finish state */
};

enum {
    ACH_STATE_STARTED,                  /* start state */
    ACH_STATE_WAITING_FOR_ACHIEVEMENTS_AND_STATS, /* waiting for child to fetch achievements and stats */
    ACH_STATE_LOADING_ACHIEVEMENTS_GUI, /* feeding achievement rows to the model */
    ACH_STATE_LOADING_STATS_GUI,        /* feeding stats rows to the model */
    ACH_STATE_DOWNLOADING_ICONS,        /* fire off icon downloads (to be added to the model) */
    ACH_STATE_FINISHED                  /* fin ish state */
};

/* data to be passed to the idle handler */
typedef struct
{
    /* the current state */
    unsigned state;

    /**
     * other information is pulled from the
     * AsyncGuiLoader object
     */

    /* the currently loaded item */
    unsigned current_item;
} IdleData;
