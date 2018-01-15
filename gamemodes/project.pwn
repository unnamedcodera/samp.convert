#include <a_samp>
#include <a_mysql>
#include <logintextdraws-en>

#define MYSQL_HOST        "sql9.freemysqlhosting.net" // Host
#define MYSQL_USER        "sql9215420" // Username
#define MYSQL_PASS        "UesBAi2zGY" // Password
#define MYSQL_DBSE    "sql9215420" // Nama database

new MySQL:handle; //TTL Mysql

//Spawns w ambil dari grandlarc
new Float:gRandomSpawns_LosSantos[][4] = {
	{1751.1097,-2106.4529,13.5469,183.1979}, // El-Corona - Outside random house
	{2652.6418,-1989.9175,13.9988,182.7107}, // Random house in willowfield - near playa de seville and stadium
	{2489.5225,-1957.9258,13.5881,2.3440}, // Hotel in willowfield - near cluckin bell
	{2689.5203,-1695.9354,10.0517,39.5312}, // Outside stadium - lots of cars
	{2770.5393,-1628.3069,12.1775,4.9637}, // South in east beach - north of stadium - carparks nearby
	{2807.9282,-1176.8883,25.3805,173.6018}, // North in east beach - near apartments
	{2552.5417,-958.0850,82.6345,280.2542}, // Random house north of Las Colinas
	{2232.1309,-1159.5679,25.8906,103.2939}, // Jefferson motel
	{2388.1003,-1279.8933,25.1291,94.3321}, // House south of pig pen
	{2481.1885,-1536.7186,24.1467,273.4944}, // East LS - near clucking bell and car wash
	{2495.0720,-1687.5278,13.5150,359.6696}, // Outside CJ's house - lots of cars nearby
	{2306.8252,-1675.4340,13.9221,2.6271}, // House in ganton - lots of cars nearby
	{2191.8403,-1455.8251,25.5391,267.9925}, // House in south jefferson - lots of cars nearby
	{1830.1359,-1092.1849,23.8656,94.0113}, // Mulholland intersection carpark
	{2015.3630,-1717.2535,13.5547,93.3655}, // Idlewood house
	{1654.7091,-1656.8516,22.5156,177.9729}, // Right next to PD
	{1219.0851,-1812.8058,16.5938,190.0045}, // Conference Center
	{1508.6849,-1059.0846,25.0625,1.8058}, // Across the street of BANK - lots of cars in intersection carpark
	{1421.0819,-885.3383,50.6531,3.6516}, // Outside house in vinewood
	{1133.8237,-1272.1558,13.5469,192.4113}, // Near hospital
	{1235.2196,-1608.6111,13.5469,181.2655}, // Backalley west of mainstreet
	{590.4648,-1252.2269,18.2116,25.0473}, // Outside "BAnk of San Andreas"
	{842.5260,-1007.7679,28.4185,213.9953}, // North of Graveyard
	{911.9332,-1232.6490,16.9766,5.2999}, // LS Film Studio
	{477.6021,-1496.6207,20.4345,266.9252}, // Rodeo Place
	{255.4621,-1366.3256,53.1094,312.0852}, // Outside propery in richman
	{281.5446,-1261.4562,73.9319,305.0017}, // Another richman property
	{790.1918,-839.8533,60.6328,191.9514}, // Mulholland house
	{1299.1859,-801.4249,84.1406,269.5274}, // Maddoggs
	{1240.3170,-2036.6886,59.9575,276.4659}, // Verdant Bluffs
	{2215.5181,-2627.8174,13.5469,273.7786}, // Ocean docks 1
	{2509.4346,-2637.6543,13.6453,358.3565} // Ocean Docks spawn 2
};

//ID Dialognya
#define DIALOG_REGISTER  1403
#define DIALOG_LOGIN     2401
#define DIALOG_SPAWN    1402
enum pDataEnum
{
	p_id,
	bool:pLoggedIn,
	pName[MAX_PLAYER_NAME],
	pLevel,
	pMoney,
	pKills,
	Select,
	pSkin,
	Float:pPos[4],
	pSpawn,
	pDeaths
}
new PlayerInfo[MAX_PLAYERS][pDataEnum];

public OnGameModeInit()
{
  	CreateGlobalLoginTextDraws();
	MySQL_SetupConnection();
	AddPlayerClasses();
	return 1;
}

public OnGameModeExit()
{
  	DestroyGlobalLoginTextDraws();
	mysql_close(handle);
	return 1;
}

public OnPlayerConnect(playerid)
{
	CreatePlayerLoginTextDraws(playerid);
	PlayerInfo[playerid][Select]     = 0;
	PlayerInfo[playerid][p_id]       = 0;
	PlayerInfo[playerid][pLoggedIn]  = false;
	PlayerInfo[playerid][pLevel]     = 0;
	PlayerInfo[playerid][pMoney]     = 0;
	PlayerInfo[playerid][pKills]     = 0;
	PlayerInfo[playerid][pDeaths]    = 0;
	PlayerInfo[playerid][pSkin]    = 0;
	PlayerInfo[playerid][pSpawn]    = 0;
	GetPlayerName(playerid, PlayerInfo[playerid][pName], MAX_PLAYER_NAME);
	
	//Check
	new query[128];
	TogglePlayerSpectating(playerid, 1);
	mysql_format(handle, query, sizeof(query), "SELECT id FROM users WHERE name = '%e'", PlayerInfo[playerid][pName]);
	mysql_pquery(handle, query, "OnUserCheck", "d", playerid);
	return 1;
}
public OnPlayerRequestClass(playerid)
{
	if(PlayerInfo[playerid][Select] == 1)
	{
		switch(random(5))
		{
            case 0: ApplyAnimation(playerid, "DANCING", "dnce_M_a", 4.1, 1, 0, 0, 0, 0);
            case 1: ApplyAnimation(playerid, "DANCING", "dnce_M_b", 4.1, 1, 0, 0, 0, 0);
            case 2: ApplyAnimation(playerid, "DANCING", "dnce_M_c", 4.1, 1, 0, 0, 0, 0);
            case 3: ApplyAnimation(playerid, "DANCING", "dnce_M_d", 4.1, 1, 0, 0, 0, 0);
            case 4: ApplyAnimation(playerid, "DANCING", "dnce_M_e", 4.1, 1, 0, 0, 0, 0);
		}
		SetPlayerInterior(playerid,11);
		SetPlayerPos(playerid,508.7362,-87.4335,998.9609);
		SetPlayerFacingAngle(playerid,0.0);
		SetPlayerCameraPos(playerid,508.7362,-83.4335,998.9609);
		SetPlayerCameraLookAt(playerid,508.7362,-87.4335,998.9609);
	}
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	if(!PlayerInfo[playerid][pLoggedIn])
	{
		SendClientMessage(playerid, -1, "{FF0000}[SERVER] : Kamu harus login terlebih dahulu.");
		return 0;
	}
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) 
{
	if(playertextid == PlayerLoginTextDraw[playerid][0])
  	{
    	if(pRegistered[playerid] == true)
    	{
      		ShowPlayerDialog(playerid, DIALOG_LOGIN,DIALOG_STYLE_PASSWORD,"Masuk", "Tolong masukan password kamu:", "Masuk", "Batal");
    	}
    	else
    	{
      		ShowPlayerDialog(playerid, DIALOG_REGISTER,DIALOG_STYLE_PASSWORD,"Daftar", "Tolong masukan password yang ingin didaftarkan:", "Daftar", "Batal");
    	}
  	}
  	return 0;
}


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_REGISTER)
	{
		if(!response) return Kick(playerid);

		if(strlen(inputtext) < 3) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Daftar", "Tolong masukan password yang ingin didaftarkan:\n{FF0000}Setidaknya 3 karakter!", "Daftar", "Batal");

		new query[256];
		mysql_format(handle, query, sizeof(query), "INSERT INTO users (name, password) VALUES ('%e', MD5('%e'))", PlayerInfo[playerid][pName], inputtext);

		mysql_pquery(handle, query, "OnUserRegister", "d", playerid);
		return 1;
	}
	if(dialogid == DIALOG_LOGIN)
	{
		if(!response) return Kick(playerid);

		if(strlen(inputtext) < 3) return ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Masuk", "Tolong masukan password kamu:\n{FF0000}Setidaknya 3 karakter!", "Masuk", "Batal");

		new query[256];
		mysql_format(handle, query, sizeof(query), "SELECT * FROM users WHERE name = '%e' AND password = MD5('%e')", PlayerInfo[playerid][pName], inputtext);

		mysql_pquery(handle, query, "OnUserLogin", "d", playerid);
		return 1;
	}
	if(dialogid == DIALOG_SPAWN)
	{
	    if(listitem == 0)
	    {
			SetSpawnInfo(playerid, NO_TEAM, 299, 1677.6185, 1447.7749, 10.7757, 0, 0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
			PlayerInfo[playerid][pSpawn] = 0;
	    }
	    if(listitem == 1)
	    {
			SetSpawnInfo(playerid, NO_TEAM, 299, 1677.6185, 1447.7749, 10.7757, 0, 0, 0, 0, 0, 0, 0);
			SpawnPlayer(playerid);
			PlayerInfo[playerid][pSpawn] = 1;
	    }
		return 1;
	}
	return 0;
}

public OnPlayerDisconnect(playerid, reason)
{
	PlayerInfo[playerid][Select]     = 0;
	SaveUserStats(playerid);
	DestroyPlayerLoginTextDraws(playerid);
	return 1;
}

forward OnUserCheck(playerid);
public OnUserCheck(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows == 0)
	{
		PlayerIsNotRegistered(playerid);
		ShowLoginTextDraws(playerid);
	}
	else
	{
		PlayerIsRegistered(playerid);
		ShowLoginTextDraws(playerid);
	}
	return 1;
}

forward OnUserRegister(playerid);
public OnUserRegister(playerid)
{
	PlayerInfo[playerid][p_id] = cache_insert_id();
	PlayerInfo[playerid][pLoggedIn]  = true;
	SendClientMessage(playerid, 0x00FF00FF, "[AKUN] Pendaftaran berhasil.");
	SendClientMessage(playerid, 0x00FF00FF, "[INFO] Silahkan pilih skin anda.");
	PlayerPlaySound(playerid, 1057 , 0.0, 0.0, 0.0);
	TogglePlayerSpectating(playerid, 0);
	PlayerInfo[playerid][Select] = 1;
	HideLoginTextDraws(playerid);
	return 1;
}

forward OnUserLogin(playerid);
public OnUserLogin(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows == 0)
	{
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Masuk", "Tolong masukan password kamu:\n{FF0000}Password salah!", "Masuk", "Batal");
	}
	else
	{
 		cache_get_value_name_int(0, "id", PlayerInfo[playerid][p_id]);
		cache_get_value_name_int(0, "level", PlayerInfo[playerid][pLevel]);
		cache_get_value_name_int(0, "money", PlayerInfo[playerid][pMoney]);
		cache_get_value_name_int(0, "kills", PlayerInfo[playerid][pKills]);
		cache_get_value_name_int(0, "deaths", PlayerInfo[playerid][pDeaths]);
		cache_get_value_name_int(0, "skin", PlayerInfo[playerid][pSkin]);
		cache_get_value_name_float(0, "PosX", PlayerInfo[playerid][pPos][0]);
		cache_get_value_name_float(0, "PosY", PlayerInfo[playerid][pPos][1]);
		cache_get_value_name_float(0, "PosZ", PlayerInfo[playerid][pPos][2]);
		cache_get_value_name_float(0, "PosA", PlayerInfo[playerid][pPos][3]);
		PlayerInfo[playerid][pLoggedIn]  = true;
		SendClientMessage(playerid, 0x00FF00FF, "[AKUN] Berhasil masuk.");
		PlayerPlaySound(playerid, 1057 , 0.0, 0.0, 0.0);
		GivePlayerMoney(playerid, PlayerInfo[playerid][pMoney]);
		HideLoginTextDraws(playerid);
		//Default Spawn Dialog
		new listitems[] = "Spawn Bebas\nPosisi Terakhir";
		ShowPlayerDialog(playerid, DIALOG_SPAWN, DIALOG_STYLE_LIST, "{00FF00}Lokasi Spawn", listitems, "Pilih", "");
	}
	return 1;
}
public OnPlayerSpawn(playerid)
{
	if(PlayerInfo[playerid][Select] == 1)
	{
	    PlayerInfo[playerid][pSkin] = GetPlayerSkin(playerid);
	    PlayerInfo[playerid][Select] = 0;
	}
	if(PlayerInfo[playerid][pSpawn] == 0)
	{
		new randSpawn = random(sizeof(gRandomSpawns_LosSantos));
		TogglePlayerSpectating(playerid, 0);
		SetPlayerPos(playerid, gRandomSpawns_LosSantos[randSpawn][0], gRandomSpawns_LosSantos[randSpawn][1], gRandomSpawns_LosSantos[randSpawn][2]);
		SetPlayerFacingAngle(playerid,gRandomSpawns_LosSantos[randSpawn][3]);
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		SetPlayerInterior(playerid, 0);
	}
	else if(PlayerInfo[playerid][pSpawn] == 1)
	{
		TogglePlayerSpectating(playerid, 0);
        SetPlayerPos(playerid, PlayerInfo[playerid][pPos][0], PlayerInfo[playerid][pPos][1], PlayerInfo[playerid][pPos][2]);
		SetPlayerFacingAngle(playerid, PlayerInfo[playerid][pPos][3]);
		SetPlayerSkin(playerid, PlayerInfo[playerid][pSkin]);
		SetPlayerInterior(playerid, 0);
	}
	return 1;
}
public OnPlayerDeath(playerid, killerid, reason)
{
	if(killerid != INVALID_PLAYER_ID)
	{
		PlayerInfo[killerid][pKills]++;
		GivePlayerMoney(killerid, 10);
		PlayerInfo[killerid][pMoney] += 10;
		if(PlayerInfo[killerid][pKills] > 3)
		{
			PlayerInfo[killerid][pLevel] = 1;
		}
	}
	PlayerInfo[playerid][pDeaths]++;
	return 1;
}

stock SaveUserStats(playerid)
{
	if(!PlayerInfo[playerid][pLoggedIn]) return 1;
	GetPlayerPos(playerid, PlayerInfo[playerid][pPos][0], PlayerInfo[playerid][pPos][1], PlayerInfo[playerid][pPos][2]);
	GetPlayerFacingAngle(playerid, PlayerInfo[playerid][pPos][3]);
    PlayerInfo[playerid][pSkin] = GetPlayerSkin(playerid);

	new query[256];
	mysql_format(handle, query, sizeof(query), "UPDATE users SET level = '%d', money = '%d', kills = '%d', deaths = '%d', skin = '%d', PosX = '%f', PosY = '%f', PosZ = '%f', PosA = '%f' WHERE id = '%d'",
		PlayerInfo[playerid][pLevel], PlayerInfo[playerid][pMoney], PlayerInfo[playerid][pKills], PlayerInfo[playerid][pDeaths], PlayerInfo[playerid][pSkin], PlayerInfo[playerid][pPos][0], PlayerInfo[playerid][pPos][1], PlayerInfo[playerid][pPos][2], PlayerInfo[playerid][pPos][3], PlayerInfo[playerid][p_id]);

	mysql_pquery(handle, query);
	return 1;
}

stock MySQL_SetupConnection(ttl = 3)
{
	print("[MySQL] Koneksi ke database...");

	handle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DBSE);

	if(mysql_errno(handle) != 0)
	{
		if(ttl > 1)
		{
			print("[MySQL] Gagal.");
			printf("[MySQL] Coba lagi (TTL: %d).", ttl-1);
			return MySQL_SetupConnection(ttl-1);
		}
		else
		{
			print("[MySQL] Gagal.");
			print("[MySQL] Cek login information.");
			print("[MySQL] Mematikan server.");
			return SendRconCommand("exit");
		}
	}
	printf("[MySQL] Koneksi berhasil! Handle: %d", _:handle);
	return 1;
}
AddPlayerClasses()
{
	AddPlayerClass(298,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(299,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(300,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(301,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(302,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(303,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(304,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(305,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(280,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(281,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(282,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(283,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(284,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(285,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(286,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(287,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(288,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(289,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(265,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(266,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(267,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(268,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(269,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(270,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(1,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(2,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(3,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(4,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(5,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(6,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(8,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(42,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(65,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	//AddPlayerClass(74,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(86,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(119,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
 	AddPlayerClass(149,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(208,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(273,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(289,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);

	AddPlayerClass(47,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(48,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(49,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(50,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(51,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(52,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(53,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(54,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(55,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(56,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(57,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(58,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
   	AddPlayerClass(68,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(69,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(70,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(71,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(72,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(73,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(75,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(76,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(78,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(79,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(80,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(81,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(82,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(83,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(84,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(85,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(87,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(88,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(89,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(91,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(92,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(93,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(95,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(96,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(97,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(98,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	AddPlayerClass(99,1759.0189,-1898.1260,13.5622,266.4503,-1,-1,-1,-1,-1,-1);
	return 1;
}
