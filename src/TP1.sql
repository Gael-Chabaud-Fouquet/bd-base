--!!!!!IMPORTANT: tous les noms de table et des données dans les tables sont en anglais!!!!!!!

CREATE TABLE IF NOT EXISTS WorldLocation (
    LocationID INT PRIMARY KEY,
    LocationName TEXT,
    LocationDescription TEXT
);



CREATE TABLE IF NOT EXISTS Items (
    ItemID INT PRIMARY KEY,
    ItemName TEXT,
    ItemDescription TEXT,
    LocationID INT,
    FOREIGN KEY (LocationID) REFERENCES WorldLocation(LocationID)
);


CREATE TABLE IF NOT EXISTS Npcs (
    NpcID INT PRIMARY KEY,
    NpcName TEXT,
    NpcDescritpion TEXT,
    LocationID INT,
    NpcDialogue TEXT,
    IsQuestGiver INT,
    FOREIGN KEY (LocationID) REFERENCES WorldLocation(LocationID)
);



CREATE TABLE IF NOT EXISTS Hostiles (
    HostileID INT PRIMARY KEY,
    HostileName TEXT,
    HostileHealth FLOAT,
    HostileStrenght FLOAT,
    LocationID INT,
    FOREIGN KEY (LocationID) REFERENCES WorldLocation(LocationID)
);


CREATE TABLE IF NOT EXISTS Quest (
    QuestID INT PRIMARY KEY,
    QuestName TEXT,
    QuestDescription TEXT,
    QuestCompletionStatus INT, -- 0 == not completed; 1 == completed; in progression == not completed == 0;
    QuestGivingNpcID INT,
    FOREIGN KEY (QuestGivingNpcID) REFERENCES Npcs(NpcID)
);



CREATE TABLE IF NOT EXISTS Inventory (
    InventoryID INT,
    PlayerID INT,
    ItemID INT,
    FOREIGN KEY (PlayerID) REFERENCES Player(PlayerID),
    FOREIGN KEY (ItemID) REFERENCES Items(ItemID)
);


INSERT INTO WorldLocation (LocationID,LocationName,LocationDescription)
VALUES
('1','Inventory as a location','It has no purpose right now'),
('2','Miku"s Stage','The vocaloid Hatsune Miku will sing on this stage soon.'),
('3','The Library','You"re not playing on Legendary are you?'),
('4','Dangerous Cave','How high is your defense stat?');


INSERT INTO Quest (QuestID, QuestName, QuestDescription, QuestCompletionStatus, QuestGivingNpcID)
VALUES
('1','Miku"s Microphone Search','Find Miku"s microphone','0','1'),
('2','Inferno"s Cursed Quest','Bring Inferno an artifact from Installation 04','0','2'),
('3','Math Quiz','Complete 434 Passive Aggression"s math quiz','0','3'),
('4','More Defense?!','Find the item Maple is looking for','0','4');


INSERT INTO Hostiles (HostileID, HostileName, HostileHealth, HostileStrenght, LocationID)
VALUES
('1','Aggressive Miku Fan','25','10','2'),
('2','Flood combat form','25','25','3'),
('3','Flood carrier form','25','25','3'),
('4','Flood infection form','1','1000','3'), --yes, 1000 is lethal, but at 50% chance only
('5','Poison slime','2','10','4'),
('6','Rock monster','6','14','4');


INSERT INTO Npcs (NpcID, NpcName, NpcDescritpion, LocationID, NpcDialogue, IsQuestGiver)
VALUES
('1','Hatsune Miku','Vocaloid. Blue hair, blue tie, hinding in your wifi.','2','W.I.P','1'),
('2','InfernoPlus','Creator of Cursed Halo Again, a mod for Halo: Combat Evolved. Wears a pink MKV (Mark 5) MJOLNIR Powerd Assault Armor System. He can use magic to enhance weapons.','3','W.I.P','1'),
('3','434 Passive Aggression','Sub-monitor of Installation 04 (Alpha Halo, the one from Halo: CE), looks like 343 Guilty Spark, but more green','3','W.I.P','1'),
('4','Maple','Maple from the following anime: BOFURI I Don"t Want To Get Hurt So I"ll Max Out My Defense. She wears an unbreakable armor and her defense stat is through the roof (with all the multipliers and stat boosts, she has over 10 000 defense), the armor is black with redish-pink fabric under the armor','4','W.I.P','1'),
('5','Not aggressive Miku fan','Miku"s fan, but they are not hostile','2','W.I.P','0'),
('6','Arbiter','Real name: Thel "Vadam, formerly Thel "Vadamee. He was declared a heretic for not stopping the destruction of Installation 04. Wears a shiny metal armor, but the active camo is too old and doesn"t last long','3','W.I.P','0'),
('7','Sergeant Johnson','Sergeant Major Avery J. Johnson. He knows what the ladies like. He is an absolute badass','3','W.I.P','0'),
('8','Sally','Maple"s best friend. She has way less defense than Maple, obviously.','4','W.I.P','0');


INSERT INTO Items (ItemID, ItemName, ItemDescription, LocationID)
VALUES
--('Apple', 'Just regular apples', 1),
('1', 'ODST Helmet','The helmet of an Orbital Drop Shock Trooper (ODST)','3'),
('2', 'ODST Chestplate','The chestplate of an Orbital Drop Shock Trooper (ODST)','3'),
('3', 'ODST Leggings','The leggings of an Orbital Drop Shock Trooper (ODST)','3'),
('4', 'ODST Boots','The boots of an Orbital Drop Shock Trooper (ODST)','3'),
('5', 'Big Pistol','A giant M6D Personal Defense Weapon System, aka M6D Pistol, or most commonly, The Halo: CE Magnum. Inferno applied a Bandana Skull and a Bottomless Clip modifications. Bandana Skull == infinite ammo. Bottomless Clip == No need to reload, the magazine is bottomless','3'),
('6', 'Blunderbuss','A modified, single slug, musket reload, version of the M90 Close Assault Weapon System, aka M90 CAWS, or most commonly, The Halo: CE Shotgun. Inferno applied a Bandana Skull and a Bottomless Clip modifications. Bandana Skull == infinite ammo. Bottomless Clip == No need to reload, the magazine is bottomless','3'),
('7', 'Forerunner Artifact','Wait, what?! It"s just a roll of Ducktape?!!','3'),
('8', 'Miku"s Microphone','Miku will be singing tonight','2'),
('9', 'Defense Multiplier Item','What is the multiplier on this?','4');