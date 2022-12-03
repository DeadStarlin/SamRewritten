/*************************************
 * Please read the license before modifying or distributing any of the code from
 * this project. Thank you.
 *************************************/

#include "schema_parser/UserGameStatsSchemaParser.h"
#include "controller/MySteam.h"
#include "controller/MySteamClient.h"
#include "controller/MyGameServer.h"
#include "gui/MainPickerWindowFactory.h"
#include "cli/cli_funcs.h"
#include "common/PerfMon.h"
#include "globals.h"

#include <iostream>
#include <sys/stat.h>

/**************************************
 *  Declare global variables imported from globals.h
 **************************************/
MySteam* g_steam = nullptr;
MySteamClient* g_steamclient = nullptr;
PerfMon* g_perfmon = nullptr;

/**************************************
 * Main entry point
 **************************************/
int
main(int argc, char *argv[])
{
    if (getuid() == 0) {
        std::cout << "Do not run this application as root" << std::endl;
        zenity("Please do not run this application as root..");
        exit(EXIT_FAILURE);
    }

    g_perfmon = new PerfMon();
    g_steam = MySteam::get_instance();
    g_steamclient = new MySteamClient();
    g_perfmon->log("Globals initialized.");
    AppId_t initial_app_id;

    // Check for command-line options, which may prevent showing the GUI
    // Note that a rewriting should be done to further separate the GUI
    // from a command-line interface
    if(!go_cli_mode(argc, argv, &initial_app_id)) {
        // auto app = Gtk::Application::create(argc, argv);
        // MainPickerWindow* main_gui = MainPickerWindowFactory::create(initial_app_id);

        // Clear commandline parameters, otherwise this errors out with "Unknown option <parameter>"
        // Constructors declarations in the gtkmm libraries have some links to bug reports about
        // needing argc, argv...
        // if (argc > 1) {
        //     argv[1] = NULL;
        // }
        // argc = 1;
        // app->run(*main_gui);
    }

    return EXIT_SUCCESS;
}
