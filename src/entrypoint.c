#include "entrypoint.h"
#include "sqlite3.h"
#include "knob.h"

#include <time.h>
#include <stdlib.h>

#define LOG_SQLITE3_ERROR(db) knob_log(KNOB_ERROR, "%s:%d: SQLITE3 ERROR: %s\n", __FILE__, __LINE__, sqlite3_errmsg(db))

// void see_state_fruits(sqlite3* db,char* state_name){
//     sqlite3_stmt* stmt = NULL;
//     char content[] =
//     "SELECT fruit,price\n"
//     "FROM FruitsForSale\n"
//     "WHERE etat=?;";
//     int ret = sqlite3_prepare_v2(db,content,-1,&stmt,NULL);

//     if(ret != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }

//     if(sqlite3_bind_text(stmt,1,state_name,-1,SQLITE_STATIC) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }

//     for(int ret = sqlite3_step(stmt);ret != SQLITE_DONE;ret = sqlite3_step(stmt)){
//         if(ret != SQLITE_ROW){
//             LOG_SQLITE3_ERROR(db);
//         }
//         int column = 0;
//         const unsigned char* fruit = sqlite3_column_text(stmt,column++);
//         float price = sqlite3_column_double(stmt,column);
//         knob_log(KNOB_INFO,"Etat %s a le fruit %s avec le prix %.2f$",state_name,fruit,price);
//     }

//     sqlite3_finalize(stmt);
// }
// const char* fruits[] = {
//     "Banana",
//     "Orange",
//     "Grape",
//     "Pear",
//     "Kumqat"
// };
// const char* states[] = {
//     "CA",
//     "SC",
//     "NC",
//     "FL",
//     "HA"
// };
// void add_random_fruit(sqlite3* db){
//     if (sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL) != SQLITE_OK) {
//         LOG_SQLITE3_ERROR(db);
//         return;
//     }
//     sqlite3_stmt* stmt = NULL;
//     char content[] =
//     "INSERT INTO FruitsForSale(fruit,etat,price)\n"
//     "VALUES\n"
//     "(?,?,?);";
//     int ret = sqlite3_prepare_v2(db,content,-1,&stmt,NULL);
//     int fruit = rand() %5;
//     int state = rand() %5;
//     double price = ((rand()+1) % 100) /100 + rand() % 2;
//     if(sqlite3_bind_text(stmt,1,fruits[fruit],-1,SQLITE_STATIC) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }
//     if(sqlite3_bind_text(stmt,2,states[state],-1,SQLITE_STATIC) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }
//     if(sqlite3_bind_double(stmt,3,price) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }
//     ret = sqlite3_step(stmt);
//     if (sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL) != SQLITE_OK) {
//         LOG_SQLITE3_ERROR(db);
//     }
// }
// void SeeNpcs(){
//     int option;
//     printf("There are 8 npcs. Which one do you want to see? If you wish to go back to the previous menu the option is 9\n");
//     printf("1: Hatsune Miku\n2: InfernoPlus\n3: 434 Passive Aggresion\n4: Maple\n5: Not Aggressive Miku Fan\n6: Arbiter\n7: Johnson\n8: Sally\n");
//     scanf("%d", &option);
//     while (option != 9)
//     {
//         switch (option) {
//             case 1: {
                
//                 break;
//             }
//             default:
//             printf("This is not the option you're looking for.");
//             break;
//         }
//     }
    
// }
// sqlite3 *db;


// void SeeNpcs(int NpcID) {
//     char *err;
//     char *sql;
//     int rc;
//     sql = sqlite3_mprintf("SELECT * FROM table1 WHERE primary_key_column = %d", NpcID);
//     rc = sqlite3_exec(db, sql, ShowTheData, NULL, &err);
//     sqlite3_free(sql);
//     if (rc != SQLITE_OK) {
    //         fprintf(stderr, "SQL error: %s\n", err);
    //         sqlite3_free(err);
//     }
// }

int ShowTheData(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

// 

void raylib_start(void){
    //srand(time(NULL));
    sqlite3* db;
    char *err;
    char *sql;
    int rc;
    sqlite3_open("./aventure.db",&db);
    int option;
    printf("I couldn't figure out how to setup most of the thing, so the available options are to see each npcs, locations, items, \nquests and enemies, all with their own sub selections\n");
    /*
    1 = see character
    2 = see locations
    3 = see items
    4 = see quests
    5 = see enemies
    6 = exit
    */
   printf("These are the options:\n1 = see the npcs;\n2 = see the locations;\n3 = see the items;\n4 = see the quests\n5 = see the enemies;\n6 = quit\nWhat will you do?");
   scanf("%d", &option);
    while (option < 7)
    {
        switch (option)
        {
            case 1:{
            sql = sqlite3_mprintf("SELECT * FROM Npcs");
            break;}
            case 2:
{            sql = sqlite3_mprintf("SELECT * FROM WorldLocation");
            break;
    }    case 3:
{            sql = sqlite3_mprintf("SELECT * FROM Items");
            break;
            }            case 4:
{            sql = sqlite3_mprintf("SELECT * FROM Quest");
            break;
            }            case 5:
{            sql = sqlite3_mprintf("SELECT * FROM Hostiles");
            break;
}            case 6: {

                sqlite3_close(db);
                return;
            }
        default:
        printf("This is not the option you're looking for.");
            break;
        }
    }
    
    
    if (sql != NULL) { // Only execute if a valid choice was made
        rc = sqlite3_exec(db, sql, ShowTheData, NULL, &err);
        sqlite3_free(sql);
        if (rc != SQLITE_OK) {
            printf(stderr, "SQL error: %s\n", err);
            sqlite3_free(err);
            sqlite3_close(db);
            //return 1;
        }
    }
    
    
    while (1)
    {
        getchar();
    }

    
}
