/*
 * Matrix chat client for Arduino/ESP8266
 *
 * Matt Kohls 2017
 *
 * Code covered by LGPL v3 or higher
 *
 */

#include "MatrixClient.h"

/* Matrix user functions */

void MatrixClient::login() 
{
    const char* type; //Holds the returned login type

    // Ask server for login method
    if(1)
    {
	// Set up json buffer
	const size_t bufferSize = JSON_ARRAY_SIZE(1) + 2*JSON_OBJECT_SIZE(1);
	StaticJsonBuffer<bufferSize> jsonBuffer;

	//Get response from server
	String url = "http://" + serverURL + "/_matrix/client/r0/login";
	http.begin(url);
	int response = http.GET();
	if(response == HTTP_CODE_OK) 
	{
	    String json = http.getString();
    
	    //Parse the object
	    JsonObject& root = jsonBuffer.parseObject(json);
	    type = root["flows"][0]["type"];
	}
	else 
	{ //Probably check for connectivity errors
	}
    }

    String json; //Holds the returned json from the POST login

    if(strcmp(type, "m.login.password") == 0)
    {
	const size_t bufferSize = JSON_OBJECT_SIZE(3);
	StaticJsonBuffer<bufferSize> jsonBuffer;

	//Json {type:m.login.password user:username password:password}
	JsonObject& object = jsonBuffer.createObject();

	object["m.login.password"] = type;
	object["user"] = user_name;
	object["password"] = password;

	char buffer[255]; // Holds the resulting json string
	object.printTo(buffer, sizeof(buffer));

	String url = "http://" + serverURL + "/_matrix/client/r0/login";
	http.begin(url);
	http.addHeader("Content-Type", "application/json");
	int response = http.POST(buffer);
	if(response == HTTP_CODE_OK) 
	{
	    json = http.getString();
	}
    }
    //Add in any other login methods

    //Do error checking

    //Save the access_token from successful login
    const size_t bufferSize = JSON_OBJECT_SIZE(3);
    StaticJsonBuffer<bufferSize> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(json);
    access_token = String(root["access_token"]);
}

void MatrixClient::logout()
{
    //wifi.httppost("server url +/_matrix/client/r0/logout?access_token=+access_token")
}

// Should only be called if an access token really needs to be changed
void MatrixClient::token_refresh()
{
   //Json refresh_token:re_token
   //Json object = wifi.httppost(above json, "server url +/_matrix/client/r0/tokenrefresh?access_token=+access_token")
   //save the new access token
   //save new refresh token

    //error checking
}

void updateStatus()
{
    //string userID
    //Json with presence:changeto status_msg:msg
    //wifi.httpput(above json, "server url +/_matrix/client/r0/presence/+userID+/status?access_token=+access_token")

    //error checking
}

/* Matrix room functions */

void createRoom(const String& roomname)
{
    //Json with room_alias_name:aname
    //wifi.httppost(above json, "server url+/_matrix/client/r0/createRoom?access_token=+access_token")
    
    //error checking
}

/* Matrix event functions */
void sendMessages(const String& roomID, const String& message)
{
}

void getMessages(const String& roomID)
{
}
