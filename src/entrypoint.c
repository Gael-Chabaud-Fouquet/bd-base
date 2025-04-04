#include "entrypoint.h"
#include "sqlite3.h"
#include "knob.h"

#include <time.h>
#include <stdlib.h>

#define LOG_SQLITE3_ERROR(db) knob_log(KNOB_ERROR, "%s:%d: SQLITE3 ERROR: %s\n", __FILE__, __LINE__, sqlite3_errmsg(db))

void SeeNpcs() {
    printf("Data is setup this way: | NpcID | NpcName | NpcDescription | LocationID | NpcDialogue | IsQuestGiver |; where IsQuestGiver is bool (0 = false, 1 = true)\n");
    printf("| 1 |Hatsune Miku | Vocaloid. Blue hair, blue tie, hinding in your wifi. | 2 | W.I.P | 1 |\n");
    printf("| 2 | InfernoPlus | Creator of Cursed Halo Again, a mod for Halo: Combat Evolved. Wears a pink MKV (Mark 5) MJOLNIR Powerd Assault Armor System. He can use magic to enhance weapons. | 3 | W.I.P |1 |\n");
    printf("| 3 | 434 Passive Aggression | Sub-monitor of Installation 04 (Alpha Halo, the one from Halo: CE), looks like 343 Guilty Spark, but more green | 3 | W.I.P | 1 |\n");
    printf("| 4 | Maple | Maple from the following anime: BOFURI I Don't Want To Get Hurt So I'll Max Out My Defense. She wears an unbreakable armor and her defense stat is through the roof (with all the multipliers and stat boosts, she has over 10 000 defense), the armor is black with redish-pink fabric under the armor | 4 | W.I.P | 1 |\n");
    printf("| 5 |Not aggressive Miku fan | Miku's fan, but they are not hostile | 2 | W.I.P | 0 |\n");
    printf("| 6 | Arbiter | Real name: Thel 'Vadam, formerly Thel 'Vadamee. He was declared a heretic for not stopping the destruction of Installation 04. Wears a shiny metal armor, but the active camo is too old and doesn't last long | 3 | W.I.P | 0 |\n");
    printf("| 7 | Sergeant Johnson | Sergeant Major Avery J. Johnson. He knows what the ladies like. He is an absolute badass | 3 | W.I.P | 0 |\n");
    printf("| 8 | Sally | Maple's best friend. She has way less defense than Maple, obviously. | 4 | W.I.P | 0 |\n");
}

void SeeLocations() {
    printf("Data is setup this way: | LocationID | LocationName | Locationdescription |\n");
    printf("| 1 | Inventory as a location | It has no purpose right now |\n");
    printf("| 2 | Miku's Stage | The vocaloid Hatsune Miku will sing on this stage soon. |\n");
    printf("| 3 | The Library | You're not playing on Legendary are you? |\n");
    printf("| 4 | Dangerous Cave | How high is your defense stat? |\n");
}

void SeeItems() {
    printf("Data is setup this way: | ItemID | ItemName | ItemDescritption | LocationID |\n");
    printf("| 1 | ODST Helmet | The helmet of an Orbital Drop Shock Trooper (ODST) | 3 |\n");
    printf("| 2 | ODST Chestplate | The chestplate of an Orbital Drop Shock Trooper (ODST) | 3 |\n");
    printf("| 3 | ODST Leggings | The leggings of an Orbital Drop Shock Trooper (ODST) | 3 |\n");
    printf("| 4 | ODST Boots | The boots of an Orbital Drop Shock Trooper (ODST) | 3 |\n");
    printf("| 5 | Big Pistol | A giant M6D Personal Defense Weapon System, aka M6D Pistol, or most commonly, The Halo: CE Magnum. Inferno applied a Bandana Skull and a Bottomless Clip modifications. Bandana Skull == infinite ammo. Bottomless Clip == No need to reload, the magazine is bottomless | 3 |\n");
    printf("| 6 | Blunderbuss | A modified, single slug, musket reload, version of the M90 Close Assault Weapon System, aka M90 CAWS, or most commonly, The Halo: CE Shotgun. Inferno applied a Bandana Skull and a Bottomless Clip modifications. Bandana Skull == infinite ammo. Bottomless Clip == No need to reload, the magazine is bottomless | 3 |\n");
    printf("| 7 | Forerunner Artifact | Wait, what?! It's just a roll of Ducktape?!! | 3 |\n");
    printf("| 8 | Miku's Microphone | Miku will be singing tonight | 2 |\n");
    printf("| 9 | Defense Multiplier Item | What is the multiplier on this? | 4 |\n");
}

void SeeQuests() {
    printf("Data is setup this way: | QuestID | QuestName | QuestDescritption | QuestCompletionStatus | LocationID |; where QuestCompletionStatus is bool (0 = not completed, 1 = completed)\n");
    printf("| 1 | Miku's Microphone Search | Find Miku's microphone | 0 | 1 |\n");
    printf("| 2 | Inferno's Cursed Quest | Bring Inferno an artifact from Installation 04 | 0 | 2 |\n");
    printf("| 3 | Math Quiz | Complete 434 Passive Aggression's math quiz | 0 | 3 |\n");
    printf("| 4 | More Defense?! | Find the item Maple is looking for | 0 | 4 |\n");
}

void SeeHostiles() {
    printf("Data is setup this way: | HostileID | HostileName | HostileHealth | HostileDamage | LocationID |\n");
    printf("| 1 | Aggressive Miku Fan | 25 | 10 | 2 |\n");
    printf("| 2 | Flood combat form | 25 | 25 | 3 |\n");
    printf("| 3 | Flood carrier form | 25 | 25 | 3|\n");
    printf("| 4 | Flood infection form | 1 | 1000 | 3 |\n"); //yes, 1000 is lethal, but at 50% chance only
    printf("| 5 | Poison slime | 2 | 10 | 4 |\n");
    printf("| 6 | Rock monster | 6 | 14 | 4 |\n");
}

void raylib_start(void){
    //srand(time(NULL));
    sqlite3* db;
    //char sql;
    sqlite3_open("./aventure.db",&db);
    int option;
    printf("Having cmd in fullscreen will help with cutting in the middle of words\n");
    printf("I couldn't figure out how to setup most of the thing, so the available options are to see each npcs, locations, items, \nquests and enemies. Also, I counldn't open the aventure.db file, so i used printf, but i tried, i had a commit at 1:15 am where the code is for trying with opennig the .db file\n");
    
    /*
    1 = see character
    2 = see locations
    3 = see items
    4 = see quests
    5 = see enemies
    6 = exit
    */
   
    printf("These are the options:\n1 = see the npcs;\n2 = see the locations;\n3 = see the items;\n4 = see the quests\n5 = see the enemies;\n6 = quit\nWhat will you do?\n");
    scanf("%d", &option);

    while (option != 6) {
        if (option == 1) { //npcs
            SeeNpcs();
        }
        if (option == 2) { //locations
            SeeLocations();
        }
        if (option == 3) { //items
            SeeItems();
        }
        if (option == 4) { //quest
            SeeQuests();
        }
        if (option == 5) { //enemies
            SeeHostiles();
        }
        if (option == 6) { //quit
            sqlite3_close(db);
            return;
        }
        if (option < 1 || option > 6) {
            printf("This is not the option you're looking for\n");
        }
        printf("Next: ");
        scanf("%d", &option);
    }
    sqlite3_close(db);
    return;

    //The buggy code with the .db file to open (I say buggy, 'cause it just stops working, like it laucnhes and all, but it freezes and does nothing, only if option 6 (quit) is used first will the code work as intended (it just closes))
    /*
    *    while (option != 7)
    *    {
    *    switch (option)
    *    {
    *        case 1:{
    *        sqlite3_mprintf("SELECT * FROM Npcs");
    *        break;}
    *        case 2:{
    *      sqlite3_mprintf("SELECT * FROM WorldLocation");
    *        break;}
    *        case 3:{
    *      sqlite3_mprintf("SELECT * FROM Items");
    *        break;}
    *        case 4: {
    *       sqlite3_mprintf("SELECT * FROM Quest");
    *        break;
    *        }
    *        case 5: {
    *       sqlite3_mprintf("SELECT * FROM Hostiles");
    *        break;
    *    }
    *        case 6: {
    *
    *        }
    *    default:
    *    printf("This is not the option you're looking for.");
    *        break;
    *    }
    *   }
    */

    while (1)
    {
        getchar();
    }    
}