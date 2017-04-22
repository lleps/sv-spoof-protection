/*
El rol de este filterscript es decirle al programa sv-spoof-protection que información
tiene el servidor (jugadores online, hostname, lenguaje, etc..).

Lo hace escribiendo un archivo "server-info.txt". Dicho archivo es leido por el programa
anteriormente mencionado, para saber la información del servidor y así mandar las queries
a los clientes.
*/
#include <a_samp>

new SERVER_INFO_FILE[] = "server-info.txt";

forward UpdateServerInfoFile();

new serverInfoTimerID = -1;

public OnFilterScriptInit() {
	print("\n--------------------------------------");
	print(" Intento para proteget tu servidor cargado");
	print("--------------------------------------\n");
	serverInfoTimerID = SetTimer("UpdateServerInfoFile", 1000, true);
	return 1;
}

public OnFilterScriptExit() {
	if (serverInfoTimerID != -1) {
	    KillTimer(serverInfoTimerID);
	}
	return 1;
}

public UpdateServerInfoFile() {
	new players, maxPlayers, hostname[64], mode[64], language[64];
	
	for (new i = 0; i < MAX_PLAYERS; i++) if (IsPlayerConnected(i) && !IsPlayerNPC(i)) {
		players++;
	}

	maxPlayers = GetMaxPlayers();
	
	GetServerVarAsString("hostname", hostname, 64);
	GetServerVarAsString("gamemodetext", mode, 64);
	GetServerVarAsString("language", language, 64);
	
	new File:file = fopen(SERVER_INFO_FILE, io_write);

	new buf[64];

	format(buf, 64, "%d", players);
	fwrite(file, buf); fwrite(file, "\n");
	
	format(buf, 64, "%d", maxPlayers);
	fwrite(file, buf); fwrite(file, "\n");
	
	fwrite(file, hostname); fwrite(file, "\n");
	fwrite(file, mode); fwrite(file, "\n");
	fwrite(file, language); fwrite(file, "\n");
	
	fclose(file);
}
