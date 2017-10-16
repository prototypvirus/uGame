//
// Created by symbx on 05.08.17.
//

#ifndef UGAME_CONSTANTS_H
#define UGAME_CONSTANTS_H

#define GAME_DIR        ".ugame"                    ///< Name of game directory
#define GAME_NAME       "uGame"                     ///< Name of game
#define GAME_VERS       "1.0.0"                     ///< Version of game
#define WIN_WIDTH       800                         ///< Start width of game window
#define WIN_HEIGHT      600                         ///< Start height of game window
#define WIN_MIN_WIDTH   320                         ///< Minimal width of game window
#define WIN_MIN_HEIGHT  240                         ///< Minimal height of game window
#define FIX_FPS         30                          ///< Fixed FPS value
#define PACK_MAX        256                         ///< Max resource package ID [res_{id}.package]
#define GAME_SITE_HOST  "192.168.0.100"             ///< Game main server domain/ip [accounts/resources]
#define GAME_SITE_PORT  80                          ///< Game main server port [accounts/resources]
#define GAME_SITE_UPD   "/game/resources.php"       ///< Path on server to resources list
#define GAME_SITE_RES   "/game/res/res_"            ///< Path on server to resource packs
#define GAME_RES_FILE   "/res_"                     ///< Local name of resource packs
#define GAME_RES_DIR    "/res"                      ///< Name of resources directory [ONLY FOR DEBUG]
#define GAME_RES_EXT    ".package"                  ///< Extension of resource packages
#define GAME_VERS_FILE  "/cfg/version"              ///< Path in resources to version file
#define FALLBACK_FONT   "DanaLibraryHand.otf"       ///< Fallback font name
#define FALLBACK_LANG   "en";                       ///< Fallback language
#define MAP_SIZE 32                                 ///< Map size SxS
#define MAP_TILES_COUNT MAP_SIZE*MAP_SIZE           ///< Count off tiles in one layer
#define MAP_LAYERS 2                                ///< Count of layers
#define MAP_LAYER_TILES MAP_TILES_COUNT*MAP_LAYERS  ///< Count of all tiles in chunk

#endif //UGAME_CONSTANTS_H
