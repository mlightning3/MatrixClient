/*
 * Matrix chat client for Arduino/ESP8266
 *
 * Matt Kohls 2017
 *
 * Code covered by LGPL v3 or higher
 *
 */

#ifndef MATRIXCLIENT_H
#define MATRIXCLIENT_H

#include "Arduino.h"
#include "ArduinoJson.h" // github.com/bblanchon/ArduinoJson
// #include wifi

class MatrixClient
{
    private:

	HTTPClient http;

	const char* access_token; // Comes from a login() or token_refresh()
	const char* user_name; // in form "user_name"
	String serverURL; // in form "sub.example.com"
	const char* password;
	
	// Refresh access token
	void token_refresh();

    public:
	// Constructors/destructors
	MatrixClient();
	~MatrixClient();

	// Arduino construction/destruction
	void begin(const String& userID, const String& serverURL);
	void end();

	// Matrix user functions
	void login();
	void logout();
	void updateStatus();

	// Matrix room functions
	void createRoom(const String& roomname);
	
	
	// Matrix event functions
	void sendMessage(const String& roomID, const String& message);
	void getMessage(const String& roomID);
	
};

#endif
