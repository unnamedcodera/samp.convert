#define LT_ServerName "Police Life"   // Change to your Server Name
#define LoginTextDrawColor 0xFF0000FF     // Desired color for the TextDraws
#define TextDrawHoverColor 0x80FF80FF     // Desired color for the Hoover Effect
#define RandomLoginColors                 // Remove if you don't want to have random colors for TextDraws

new Text:GlobalLoginTextDraw[29],
PlayerText:PlayerLoginTextDraw[MAX_PLAYERS][4],
realtimer[MAX_PLAYERS],
bool:pRegistered[MAX_PLAYERS];

#if defined RandomLoginColors

static RandomLoginColorsArray[] = 
{
  0xFF0000FF, //Light Red
  0x5E0000FF, //Dark Red
  0x80FF00FF, //Light Green
  0x005100FF, //Dark Green
  0x0080C0FF, //Light Blue
  0x000088FF, //Dark Blue
  0xFFFFFFFF, //White
  0x9E9E9EFF //Light Grey
};

#endif

enum
{
  D_Login = 10100,
  D_Register = 10101,
  D_About = 10102,
  D_Rules = 10103,
  D_Credits = 10104
};

public OnPlayerConnect(playerid)
{
  pRegistered[playerid] = false;
  CreatePlayerLoginTextDraws(playerid);
  #if defined ETD_OnPlayerConnect
  return ETD_OnPlayerConnect(playerid);
  #else
  return 1;
  #endif
}

public OnPlayerDisconnect(playerid, reason)
{
  pRegistered[playerid] = false;
  KillTimer(realtimer[playerid]);
  DestroyPlayerLoginTextDraws(playerid);
  
  #if defined ETD_OnPlayerDisconnect
  return ETD_OnPlayerDisconnect(playerid,reason);
  #else
  return 1;
  #endif
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
  new string[512]; //Adapt the size..
  if(clickedid == GlobalLoginTextDraw[11])
  {   
    //About us Button
    strcat(string,"{FF0000}Tentang kami:{FFFFFF}\n\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    ShowPlayerDialog(playerid, D_About, DIALOG_STYLE_MSGBOX, "Tentang", string, "Oke", "");
  }

  if(clickedid == GlobalLoginTextDraw[12])
  {
    //Rules Button
    strcat(string,"{FF0000}Peraturan:{FFFFFF}\n\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    ShowPlayerDialog(playerid, D_Rules, DIALOG_STYLE_MSGBOX, "Peraturan", string, "Oke", "");

  }

  if(clickedid == GlobalLoginTextDraw[13])
  {
    //Credits Button
    strcat(string,"{FF0000}Credits:{FFFFFF}\n\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    strcat(string,"< Teks.. >\n");
    ShowPlayerDialog(playerid, D_Credits, DIALOG_STYLE_MSGBOX, "Credits", string, "Oke", "");
  }

  #if defined ETD_OnPlayerClickTextDraw
  return ETD_OnPlayerClickTextDraw(playerid, clickedid);
  #else
  return 1;
  #endif
}


forward LR_UpdateRealTime(playerid);
public LR_UpdateRealTime(playerid)
{
  new str[16];
  gettime(str[0], str[1]);
  format(str,sizeof(str),"WAKTU : %02d:%02d",str[0],str[1]);
  PlayerTextDrawSetString(playerid,PlayerLoginTextDraw[playerid][2], str);
  return 1;
}

stock PlayerIsRegistered(playerid)
{
  pRegistered[playerid] = true;
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][3], !"Akun ini sudah ~g~terdaftar~w~.~n~Kamu bisa ~g~masuk~w~ ke akunmu.");
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][0], !"      Masuk"); 
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][1], !"          Selamat datang kembali!"); 
}

stock PlayerIsNotRegistered(playerid)
{
  pRegistered[playerid] = false;
  new str[128]; //Adapt the size..
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][3], !"Akun ini ~g~tidak~w~ terdaftar.~n~Kamu sekarang bisa membuat ~g~akun.");
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][0], !"    Daftar");
  format(str, sizeof(str),"Selamat datang ke %s", LT_ServerName);
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][1], str);
}

stock ShowLoginTextDraws(playerid)
{
  for(new i; i < sizeof(PlayerLoginTextDraw[]); i++)
  {
    PlayerTextDrawShow(playerid, PlayerLoginTextDraw[playerid][i]);
  }

  for(new i; i<sizeof(GlobalLoginTextDraw); i++)
  {
    TextDrawShowForPlayer(playerid, GlobalLoginTextDraw[i]);
  }

  SelectTextDraw(playerid, TextDrawHoverColor);
  #if defined RandomLoginColors
  new Randomtextdrawcolor = RandomLoginColorsArray[random(sizeof(RandomLoginColorsArray))];
  TextDrawBoxColor(GlobalLoginTextDraw[2], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[4], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[6], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[8], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[10], Randomtextdrawcolor);
  #else
  TextDrawBoxColor(GlobalLoginTextDraw[2], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[4], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[6], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[8], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[10], LoginTextDrawColor);
  #endif
}

stock HideLoginTextDraws(playerid)
{
  for(new i; i < sizeof(PlayerLoginTextDraw[]); i++)
  {
    PlayerTextDrawHide(playerid, PlayerLoginTextDraw[playerid][i]);
  }

  for(new i; i<sizeof(GlobalLoginTextDraw); i++)
  {
    TextDrawHideForPlayer(playerid, GlobalLoginTextDraw[i]);
  }

  CancelSelectTextDraw(playerid);
  KillTimer(realtimer[playerid]);
}

stock DestroyPlayerLoginTextDraws(playerid)
{
  for(new i; i < sizeof(PlayerLoginTextDraw[]); i++)
  {
    PlayerTextDrawDestroy(playerid, PlayerLoginTextDraw[playerid][i]);
  }

  CancelSelectTextDraw(playerid);
  KillTimer(realtimer[playerid]);
}

stock DestroyGlobalLoginTextDraws()
{
  for(new i; i<sizeof(GlobalLoginTextDraw); i++)
  {
    TextDrawDestroy(GlobalLoginTextDraw[i]);
  }
}

//Callback Hooks

#if defined _ALS_OnFilterScriptInit
#undef OnFilterScriptInit
#else
#define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit ETD_OnFilterScriptInit
#if defined ETD_OnFilterScriptInit
forward ETD_OnFilterScriptInit();
#endif

#if defined _ALS_OnFilterScriptExit
#undef OnFilterScriptExit
#else
#define _ALS_OnFilterScriptExit
#endif

#define OnFilterScriptExit ETD_OnFilterScriptExit
#if defined ETD_OnFilterScriptExit
forward ETD_OnFilterScriptExit();
#endif

#if defined _ALS_OnPlayerConnect
#undef OnPlayerConnect
#else
#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect ETD_OnPlayerConnect
#if defined ETD_OnPlayerConnect
forward ETD_OnPlayerConnect();
#endif

#if defined _ALS_OnPlayerDisconnect
#undef OnPlayerDisconnect
#else
#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect ETD_OnPlayerDisconnect
#if defined ETD_OnPlayerDisconnect
forward ETD_OnPlayerDisconnect();
#endif

#if defined _ALS_OnPlayerClickTextDraw
#undef OnPlayerClickTextDraw
#else
#define _ALS_OnPlayerClickTextDraw
#endif

#define OnPlayerClickTextDraw ETD_OnPlayerClickTextDraw
#if defined ETD_OnPlayerClickTextDraw
forward ETD_OnPlayerClickTextDraw();
#endif


stock CreateGlobalLoginTextDraws()
{
  GlobalLoginTextDraw[0] = TextDrawCreate(169.000000, 121.000000, !"__");
  TextDrawBackgroundColor(GlobalLoginTextDraw[0], 255);
  TextDrawFont(GlobalLoginTextDraw[0], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[0], 0.500000, 26.200000);
  TextDrawColor(GlobalLoginTextDraw[0], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[0], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[0], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[0], 1);
  TextDrawUseBox(GlobalLoginTextDraw[0], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[0], 255);
  TextDrawTextSize(GlobalLoginTextDraw[0], 470.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[0], 0);

  GlobalLoginTextDraw[1] = TextDrawCreate(170.000000, 123.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[1], 255);
  TextDrawFont(GlobalLoginTextDraw[1], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[1], 0.500000, 25.799999);
  TextDrawColor(GlobalLoginTextDraw[1], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[1], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[1], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[1], 1);
  TextDrawUseBox(GlobalLoginTextDraw[1], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[1], 286331391);
  TextDrawTextSize(GlobalLoginTextDraw[1], 469.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[1], 0);

  GlobalLoginTextDraw[2] = TextDrawCreate(170.000000, 122.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[2], 255);
  TextDrawFont(GlobalLoginTextDraw[2], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[2], 0.500000, 1.200000);
  TextDrawColor(GlobalLoginTextDraw[2], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[2], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[2], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[2], 1);
  TextDrawUseBox(GlobalLoginTextDraw[2], 1);
  TextDrawTextSize(GlobalLoginTextDraw[2], 469.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[2], 0);

  GlobalLoginTextDraw[3] = TextDrawCreate(177.000000, 156.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[3], 255);
  TextDrawFont(GlobalLoginTextDraw[3], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[3], 0.500000, 3.700000);
  TextDrawColor(GlobalLoginTextDraw[3], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[3], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[3], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[3], 1);
  TextDrawUseBox(GlobalLoginTextDraw[3], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[3], 255);
  TextDrawTextSize(GlobalLoginTextDraw[3], 264.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[3], 0);

  GlobalLoginTextDraw[4] = TextDrawCreate(178.000000, 157.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[4], 255);
  TextDrawFont(GlobalLoginTextDraw[4], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[4], 0.500000, 3.500000);
  TextDrawColor(GlobalLoginTextDraw[4], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[4], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[4], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[4], 1);
  TextDrawUseBox(GlobalLoginTextDraw[4], 1);
  TextDrawTextSize(GlobalLoginTextDraw[4], 263.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[4], 0);

  GlobalLoginTextDraw[5] = TextDrawCreate(177.000000, 206.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[5], 255);
  TextDrawFont(GlobalLoginTextDraw[5], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[5], 0.500000, 3.700000);
  TextDrawColor(GlobalLoginTextDraw[5], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[5], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[5], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[5], 1);
  TextDrawUseBox(GlobalLoginTextDraw[5], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[5], 255);
  TextDrawTextSize(GlobalLoginTextDraw[5], 264.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[5], 0);

  GlobalLoginTextDraw[6] = TextDrawCreate(178.000000, 207.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[6], 255);
  TextDrawFont(GlobalLoginTextDraw[6], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[6], 0.500000, 3.500000);
  TextDrawColor(GlobalLoginTextDraw[6], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[6], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[6], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[6], 1);
  TextDrawUseBox(GlobalLoginTextDraw[6], 1);
  TextDrawTextSize(GlobalLoginTextDraw[6], 263.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[6], 0);

  GlobalLoginTextDraw[7] = TextDrawCreate(177.000000, 256.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[7], 255);
  TextDrawFont(GlobalLoginTextDraw[7], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[7], 0.500000, 3.700000);
  TextDrawColor(GlobalLoginTextDraw[7], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[7], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[7], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[7], 1);
  TextDrawUseBox(GlobalLoginTextDraw[7], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[7], 255);
  TextDrawTextSize(GlobalLoginTextDraw[7], 264.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[7], 0);

  GlobalLoginTextDraw[8] = TextDrawCreate(178.000000, 257.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[8], 255);
  TextDrawFont(GlobalLoginTextDraw[8], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[8], 0.500000, 3.500000);
  TextDrawColor(GlobalLoginTextDraw[8], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[8], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[8], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[8], 1);
  TextDrawUseBox(GlobalLoginTextDraw[8], 1);
  TextDrawTextSize(GlobalLoginTextDraw[8], 263.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[8], 0);

  GlobalLoginTextDraw[9] = TextDrawCreate(177.000000, 306.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[9], 255);
  TextDrawFont(GlobalLoginTextDraw[9], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[9], 0.500000, 3.700000);
  TextDrawColor(GlobalLoginTextDraw[9], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[9], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[9], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[9], 1);
  TextDrawUseBox(GlobalLoginTextDraw[9], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[9], 255);
  TextDrawTextSize(GlobalLoginTextDraw[9], 264.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[9], 0);

  GlobalLoginTextDraw[10] = TextDrawCreate(178.000000, 307.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[10], 255);
  TextDrawFont(GlobalLoginTextDraw[10], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[10], 0.500000, 3.500000);
  TextDrawColor(GlobalLoginTextDraw[10], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[10], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[10], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[10], 1);
  TextDrawUseBox(GlobalLoginTextDraw[10], 1);
  TextDrawTextSize(GlobalLoginTextDraw[10], 263.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[10], 0);

  GlobalLoginTextDraw[11] = TextDrawCreate(191.000000, 217.000000, !"     Tentang");
  TextDrawBackgroundColor(GlobalLoginTextDraw[11], 255);
  TextDrawFont(GlobalLoginTextDraw[11], 2);
  TextDrawLetterSize(GlobalLoginTextDraw[11], 0.189999, 1.299999);
  TextDrawTextSize( GlobalLoginTextDraw[11], 260.0, 20.0);
  TextDrawColor(GlobalLoginTextDraw[11], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[11], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[11], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[11], 1);

  GlobalLoginTextDraw[12] = TextDrawCreate(202.000000, 267.000000, !" Aturan");
  TextDrawBackgroundColor(GlobalLoginTextDraw[12], 255);
  TextDrawFont(GlobalLoginTextDraw[12], 2);
  TextDrawLetterSize(GlobalLoginTextDraw[12], 0.189999, 1.299999);
  TextDrawTextSize( GlobalLoginTextDraw[12], 240.0, 15.0);
  TextDrawColor(GlobalLoginTextDraw[12], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[12], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[12], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[12], 1);

  GlobalLoginTextDraw[13] = TextDrawCreate(202.000000, 316.000000, !"Credits");
  TextDrawBackgroundColor(GlobalLoginTextDraw[13], 255);
  TextDrawFont(GlobalLoginTextDraw[13], 2);
  TextDrawLetterSize(GlobalLoginTextDraw[13], 0.189999, 1.299999);
  TextDrawTextSize( GlobalLoginTextDraw[13], 240.0, 15.0);
  TextDrawColor(GlobalLoginTextDraw[13], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[13], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[13], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[13], 1);

  GlobalLoginTextDraw[14] = TextDrawCreate(340.000000, 155.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[14], 255);
  TextDrawFont(GlobalLoginTextDraw[14], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[14], 0.500000, 3.799999);
  TextDrawColor(GlobalLoginTextDraw[14], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[14], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[14], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[14], 1);
  TextDrawUseBox(GlobalLoginTextDraw[14], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[14], 255);
  TextDrawTextSize(GlobalLoginTextDraw[14], 460.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[14], 0);

  GlobalLoginTextDraw[15] = TextDrawCreate(341.000000, 156.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[15], 255);
  TextDrawFont(GlobalLoginTextDraw[15], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[15], 0.500000, 3.599999);
  TextDrawColor(GlobalLoginTextDraw[15], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[15], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[15], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[15], 1);
  TextDrawUseBox(GlobalLoginTextDraw[15], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[15], 505290495);
  TextDrawTextSize(GlobalLoginTextDraw[15], 459.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[15], 0);

  GlobalLoginTextDraw[16] = TextDrawCreate(340.000000, 206.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[16], 255);
  TextDrawFont(GlobalLoginTextDraw[16], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[16], 0.500000, 3.799999);
  TextDrawColor(GlobalLoginTextDraw[16], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[16], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[16], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[16], 1);
  TextDrawUseBox(GlobalLoginTextDraw[16], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[16], 255);
  TextDrawTextSize(GlobalLoginTextDraw[16], 460.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[16], 0);

  GlobalLoginTextDraw[17] = TextDrawCreate(341.000000, 207.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[17], 255);
  TextDrawFont(GlobalLoginTextDraw[17], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[17], 0.500000, 3.599999);
  TextDrawColor(GlobalLoginTextDraw[17], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[17], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[17], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[17], 1);
  TextDrawUseBox(GlobalLoginTextDraw[17], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[17], 505290495);
  TextDrawTextSize(GlobalLoginTextDraw[17], 459.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[17], 0);

  GlobalLoginTextDraw[18] = TextDrawCreate(318.000000, 203.000000, !"~<~");
  TextDrawBackgroundColor(GlobalLoginTextDraw[18], 255);
  TextDrawFont(GlobalLoginTextDraw[18], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[18], 0.539999, 3.900000);
  TextDrawColor(GlobalLoginTextDraw[18], -16776961);
  TextDrawSetOutline(GlobalLoginTextDraw[18], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[18], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[18], 0);

  GlobalLoginTextDraw[19] = TextDrawCreate(340.000000, 259.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[19], 255);
  TextDrawFont(GlobalLoginTextDraw[19], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[19], 0.500000, 3.799999);
  TextDrawColor(GlobalLoginTextDraw[19], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[19], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[19], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[19], 1);
  TextDrawUseBox(GlobalLoginTextDraw[19], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[19], 255);
  TextDrawTextSize(GlobalLoginTextDraw[19], 460.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[19], 0);

  GlobalLoginTextDraw[20] = TextDrawCreate(341.000000, 260.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[20], 255);
  TextDrawFont(GlobalLoginTextDraw[20], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[20], 0.500000, 3.599999);
  TextDrawColor(GlobalLoginTextDraw[20], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[20], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[20], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[20], 1);
  TextDrawUseBox(GlobalLoginTextDraw[20], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[20], 505290495);
  TextDrawTextSize(GlobalLoginTextDraw[20], 459.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[20], 0);

  GlobalLoginTextDraw[21] = TextDrawCreate(340.000000, 309.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[21], 255);
  TextDrawFont(GlobalLoginTextDraw[21], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[21], 0.500000, 3.799999);
  TextDrawColor(GlobalLoginTextDraw[21], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[21], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[21], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[21], 1);
  TextDrawUseBox(GlobalLoginTextDraw[21], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[21], 255);
  TextDrawTextSize(GlobalLoginTextDraw[21], 460.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[21], 0);

  GlobalLoginTextDraw[22] = TextDrawCreate(341.000000, 310.000000, !"_");
  TextDrawBackgroundColor(GlobalLoginTextDraw[22], 255);
  TextDrawFont(GlobalLoginTextDraw[22], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[22], 0.500000, 3.599999);
  TextDrawColor(GlobalLoginTextDraw[22], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[22], 0);
  TextDrawSetProportional(GlobalLoginTextDraw[22], 1);
  TextDrawSetShadow(GlobalLoginTextDraw[22], 1);
  TextDrawUseBox(GlobalLoginTextDraw[22], 1);
  TextDrawBoxColor(GlobalLoginTextDraw[22], 505290495);
  TextDrawTextSize(GlobalLoginTextDraw[22], 459.000000, 0.000000);
  TextDrawSetSelectable(GlobalLoginTextDraw[22], 0);

  GlobalLoginTextDraw[23] = TextDrawCreate(318.000000, 152.000000, !"~<~");
  TextDrawBackgroundColor(GlobalLoginTextDraw[23], 255);
  TextDrawFont(GlobalLoginTextDraw[23], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[23], 0.539999, 3.900000);
  TextDrawColor(GlobalLoginTextDraw[23], -16776961);
  TextDrawSetOutline(GlobalLoginTextDraw[23], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[23], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[23], 0);

  GlobalLoginTextDraw[24] = TextDrawCreate(318.000000, 256.000000, !"~<~");
  TextDrawBackgroundColor(GlobalLoginTextDraw[24], 255);
  TextDrawFont(GlobalLoginTextDraw[24], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[24], 0.539999, 3.900000);
  TextDrawColor(GlobalLoginTextDraw[24], -16776961);
  TextDrawSetOutline(GlobalLoginTextDraw[24], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[24], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[24], 0);

  GlobalLoginTextDraw[25] = TextDrawCreate(318.000000, 306.000000, !"~<~");
  TextDrawBackgroundColor(GlobalLoginTextDraw[25], 255);
  TextDrawFont(GlobalLoginTextDraw[25], 1);
  TextDrawLetterSize(GlobalLoginTextDraw[25], 0.539999, 3.900000);
  TextDrawColor(GlobalLoginTextDraw[25], -16776961);
  TextDrawSetOutline(GlobalLoginTextDraw[25], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[25], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[25], 0);

  GlobalLoginTextDraw[26] = TextDrawCreate(348.000000, 213.000000, !"Tekan ini untuk ~g~Informasi~w~.~n~Bagaimana server bekerja...");
  TextDrawBackgroundColor(GlobalLoginTextDraw[26], 255);
  TextDrawFont(GlobalLoginTextDraw[26], 2);
  TextDrawLetterSize(GlobalLoginTextDraw[26], 0.129997, 0.899999);
  TextDrawColor(GlobalLoginTextDraw[26], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[26], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[26], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[26], 0);

  GlobalLoginTextDraw[27] = TextDrawCreate(348.000000, 266.000000, !"~w~Baca dengan hati hati ~g~Aturannya.~w~~n~Hormati player lain.");
  TextDrawBackgroundColor(GlobalLoginTextDraw[27], 255);
  TextDrawFont(GlobalLoginTextDraw[27], 2);
  TextDrawLetterSize(GlobalLoginTextDraw[27], 0.129997, 0.899999);
  TextDrawColor(GlobalLoginTextDraw[27], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[27], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[27], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[27], 0);

  GlobalLoginTextDraw[28] = TextDrawCreate(348.000000, 317.000000, !"Lihat siapa saja ~g~berkontribusi~w~.~n~Untuk server ini");
  TextDrawBackgroundColor(GlobalLoginTextDraw[28], 255);
  TextDrawFont(GlobalLoginTextDraw[28], 2);
  TextDrawLetterSize(GlobalLoginTextDraw[28], 0.129997, 0.899999);
  TextDrawColor(GlobalLoginTextDraw[28], -1);
  TextDrawSetOutline(GlobalLoginTextDraw[28], 1);
  TextDrawSetProportional(GlobalLoginTextDraw[28], 1);
  TextDrawSetSelectable(GlobalLoginTextDraw[28], 0);

  #if defined RandomLoginColors
  new Randomtextdrawcolor = RandomLoginColorsArray[random(sizeof(RandomLoginColorsArray))];
  TextDrawBoxColor(GlobalLoginTextDraw[2], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[4], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[6], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[8], Randomtextdrawcolor);
  TextDrawBoxColor(GlobalLoginTextDraw[10], Randomtextdrawcolor);
  #else
  TextDrawBoxColor(GlobalLoginTextDraw[2], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[4], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[6], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[8], LoginTextDrawColor);
  TextDrawBoxColor(GlobalLoginTextDraw[10], LoginTextDrawColor);
  #endif

}

stock CreatePlayerLoginTextDraws(playerid)
{
  new str[128];
  PlayerLoginTextDraw[playerid][0] = CreatePlayerTextDraw(playerid,192.000000, 166.000000, !"      Masuk");
  PlayerTextDrawBackgroundColor(playerid,PlayerLoginTextDraw[playerid][0], 255);
  PlayerTextDrawFont(playerid,PlayerLoginTextDraw[playerid][0], 2);
  PlayerTextDrawLetterSize(playerid,PlayerLoginTextDraw[playerid][0], 0.189999, 1.299999);
  PlayerTextDrawTextSize(playerid, PlayerLoginTextDraw[playerid][0], 240.0, 15.0);
  PlayerTextDrawColor(playerid,PlayerLoginTextDraw[playerid][0], -1);
  PlayerTextDrawSetOutline(playerid,PlayerLoginTextDraw[playerid][0], 1);
  PlayerTextDrawSetProportional(playerid,PlayerLoginTextDraw[playerid][0], 1);
  PlayerTextDrawSetSelectable(playerid,PlayerLoginTextDraw[playerid][0], 1);

  PlayerLoginTextDraw[playerid][1] = CreatePlayerTextDraw(playerid,269.000000, 123.000000, !"Selamat datang ke <YOUR_SERVERNAME>");
  PlayerTextDrawBackgroundColor(playerid,PlayerLoginTextDraw[playerid][1], 255);
  PlayerTextDrawFont(playerid,PlayerLoginTextDraw[playerid][1], 2);
  PlayerTextDrawLetterSize(playerid,PlayerLoginTextDraw[playerid][1], 0.140000, 0.799998);
  PlayerTextDrawColor(playerid,PlayerLoginTextDraw[playerid][1], -1);
  PlayerTextDrawSetOutline(playerid,PlayerLoginTextDraw[playerid][1], 1);
  PlayerTextDrawSetProportional(playerid,PlayerLoginTextDraw[playerid][1], 1);
  PlayerTextDrawSetSelectable(playerid,PlayerLoginTextDraw[playerid][1], 0);
  format(str, sizeof(str),"Welcome to %s", LT_ServerName);
  PlayerTextDrawSetString(playerid, PlayerLoginTextDraw[playerid][1], str);

  PlayerLoginTextDraw[playerid][2] = CreatePlayerTextDraw(playerid,427.000000, 123.000000, !"00:00 Time");
  PlayerTextDrawBackgroundColor(playerid,PlayerLoginTextDraw[playerid][2], 255);
  PlayerTextDrawFont(playerid,PlayerLoginTextDraw[playerid][2], 2);
  PlayerTextDrawLetterSize(playerid,PlayerLoginTextDraw[playerid][2], 0.140000, 0.799998);
  PlayerTextDrawColor(playerid,PlayerLoginTextDraw[playerid][2], -1);
  PlayerTextDrawSetOutline(playerid,PlayerLoginTextDraw[playerid][2], 1);
  PlayerTextDrawSetProportional(playerid,PlayerLoginTextDraw[playerid][2], 1);
  PlayerTextDrawSetSelectable(playerid,PlayerLoginTextDraw[playerid][2], 0);

  PlayerLoginTextDraw[playerid][3] = CreatePlayerTextDraw(playerid,346.000000, 162.000000, !"Akun ini sudah ~g~terdaftar~w~.~n~Kamu bisa ~g~masuk~w~ ke akunmu.");
  PlayerTextDrawBackgroundColor(playerid,PlayerLoginTextDraw[playerid][3], 255);
  PlayerTextDrawFont(playerid,PlayerLoginTextDraw[playerid][3], 2);
  PlayerTextDrawLetterSize(playerid,PlayerLoginTextDraw[playerid][3], 0.129997, 0.899999);
  PlayerTextDrawColor(playerid,PlayerLoginTextDraw[playerid][3], -1);
  PlayerTextDrawSetOutline(playerid,PlayerLoginTextDraw[playerid][3], 1);
  PlayerTextDrawSetProportional(playerid,PlayerLoginTextDraw[playerid][3], 1);
  PlayerTextDrawSetSelectable(playerid,PlayerLoginTextDraw[playerid][3], 0);

  KillTimer(realtimer[playerid]);
  realtimer[playerid] = SetTimerEx("LR_UpdateRealTime", 1000, true, "i", playerid);
}
