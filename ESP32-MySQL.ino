#include <MySQL_Generic.h>
#include <WiFi.h>

#define MYSQL_DEBUG_PORT Serial
#define _MYSQL_LOGLEVEL_ 1

#define SERVER_PORT 3306
#define SERVER "SEU SERVER"
#define DATABASE "SEU DATABASE"
#define TABLE "SUA TABLE"
#define MYSQL_USER "SEU USUÁRIO MYSQL"
#define MYSQL_PASSWORD "SUA SENHA MYSQL"

MySQL_Connection conn((Client *)&client);
MySQL_Query *query_mem;

#define WIFI_SSID "SUA REDE WIFI"
#define WIFI_PASSWORD "SUA SENHA WIFI"

String INSERT_SQL;


void setup(){
  
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    
  Serial.println("\nConectado:");
  Serial.println(WiFi.localIP());
  delay(500);
}


void loop(){

  int viVar1 = random(0, 101);
  int viVar2 = random(0, 101);
  int viVar3 = random(0, 101);

  INSERT_SQL = String("INSERT INTO ") + DATABASE + "." + TABLE 
               + " (var1, var2, var3) VALUES (" 
               +  String(viVar1)+ "," 
               +  String(viVar2) + "," 
               +  String(viVar3) + ")";

  MYSQL_DISPLAY("Conectando...");

  if (conn.connect(SERVER, SERVER_PORT, MYSQL_USER, MYSQL_PASSWORD)){
    delay(500);
    
    InsertMySQL();
    
    conn.close();
  } 
  else {
    MYSQL_DISPLAY("\nConexão falhou.");
  }
 
  delay(60000);
}


void InsertMySQL(){

  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected()){
    MYSQL_DISPLAY(INSERT_SQL);
    if (!query_mem.execute(INSERT_SQL.c_str())){
      MYSQL_DISPLAY("Insert falhou.");
      }
    else{
      MYSQL_DISPLAY("Insert concluído.");
    }
  }
  else{
    MYSQL_DISPLAY("Disconectado do servidor.");
  }
}
