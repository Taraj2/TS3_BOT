//
// Created by Krzysiek on 23.12.2018.
//

#include "rankings.h"


void updateRankingConnectionTimes(int mainSocket, char *cid) {

    char *description = malloc(10240);
    if (description == NULL) {
        fprintf(stderr, "Nie mozna przydzielic pamieci \"updateRankingConnectionTimes()\"\n%s\n", strerror(errno));
        exit(errno);
    }


    sprintf(description, "[center][B][size=30][COLOR=#ff0000]Ranking Czasu Połączeń[/COLOR][/size]\n"
                         "[size=20]\n");

    struct list *clients = listReverse(execQuery(
            "SELECT `total_connection_time`,`TS_client_nickname`,`total_inactivity_time`, `TS_client_unique_identifier` FROM `ranking_total_connection_time` LIMIT 20"));
    int i = 1;
    for (struct list *it = clients; it != NULL; it = it->next) {
        sprintf(description + strlen(description),
                "%d. [URL=client:///%s]%s[/URL] - %lfh [COLOR=#b3b3b3](%lfh AFK)[/COLOR]\n", i++,
                treeGetValue(it->tree, "TS_client_unique_identifier"), treeGetValue(it->tree, "TS_client_nickname"),
                strtol(treeGetValue(it->tree, "total_connection_time"), NULL, 0) / 3600.0,
                strtol(treeGetValue(it->tree, "total_inactivity_time"), NULL, 0) / 3600.0);
    }
    chanelChangeDescription(mainSocket, cid, description);
    listFree(clients);
    free(description);
}

void updateRankingConnectionCount(int mainSocket, char *cid) {

    char *description = malloc(10240);
    if (description == NULL) {
        fprintf(stderr, "Nie mozna przydzielic pamieci \"updateRankingConnectionTimes()\"\n%s\n", strerror(errno));
        exit(errno);
    }
    sprintf(description, "[center][B][size=30][COLOR=#ff0000]Ranking Ilości Połączeń[/COLOR][/size]\n"
                         "[size=20]\n");

    struct list *clients = listReverse(execQuery(
            "SELECT `total_connection_count`,`TS_client_nickname`,`TS_client_unique_identifier` FROM `ranking_total_connection_count` LIMIT 20;"));

    int i = 1;
    for (struct list *it = clients; it != NULL; it = it->next) {
        sprintf(description + strlen(description), "%d. [URL=client:///%s]%s[/URL] - %s\n", i++,
                treeGetValue(it->tree, "TS_client_unique_identifier"), treeGetValue(it->tree, "TS_client_nickname"),
                treeGetValue(it->tree, "total_connection_count"));
    }
    chanelChangeDescription(mainSocket, cid, description);
    listFree(clients);
    free(description);
}

void updateRankingLongestConnection(int mainSocket, char *cid){
    char *description = malloc(10240);
    if (description == NULL) {
        fprintf(stderr, "Nie mozna przydzielic pamieci \"updateRankingConnectionTimes()\"\n%s\n", strerror(errno));
        exit(errno);
    }


    sprintf(description, "[center][B][size=30][COLOR=#ff0000]Ranking Długości Połączeń[/COLOR][/size]\n"
                         "[size=20]\n");

    struct list *clients = listReverse(execQuery(
            "SELECT `TS_client_unique_identifier`, `TS_client_nickname`, `connection_time` FROM `ranking_longest_connection` LIMIT 20;"));
    int i = 1;
    for (struct list *it = clients; it != NULL; it = it->next) {
        sprintf(description + strlen(description),
                "%d. [URL=client:///%s]%s[/URL] - %lfh\n", i++,
                treeGetValue(it->tree, "TS_client_unique_identifier"), treeGetValue(it->tree, "TS_client_nickname"),
                strtol(treeGetValue(it->tree, "connection_time"), NULL, 0) / 3600.0 );
    }
    chanelChangeDescription(mainSocket, cid, description);
    listFree(clients);
    free(description);
}