![logo](https://i.ibb.co/YthtbLh/Giifff-mid.gif)
***
# Comunicação com MySQL: ESP32
Neste guia, iremos montar um datalogger usando um banco de dados MySQL.
***
## Contextualização
Iremos criar três variáveis que mudam os valores de forma randômica. Os dados serão enviados para um banco de dados MySQL. Os dados serão atualizados automaticamente, permitindo, além do armazenamento, a visualização em tempo real.

## Requerimentos
- Placa ESP32;
- Banco de dados (disponiblizarei um guia para criar um banco MySQL numa Raspberry Pi).

## Biblioteca MySQL
Para realizar a comunicação com o MySQL é necessário instalar uma biblioteca.

Em sua Arduino IDE vá em: Sketch > Incluir Biblioteca > Gerenciar Bibliotecas

<p align="center">
  <img src="https://i.ibb.co/xC958xP/preparando-5.png" alt="5"/>
</p>

Pesquise por "MySQL_MariaDB_Generic", escolha a opção da imagem e clique em "Instalar" (como eu já tinha instalado, não apareceu a opção "Instalar").

<p align="center">
  <img src="https://i.ibb.co/frzf8ds/library.png" alt="5"/>
</p>

## Código SQL
Agora iremos criar o banco de dados no phpMyAdmin. Clique em "Banco de dados", selecione um nome e clique em "Criar". 

<p align="center">
  <img src="https://i.ibb.co/fDBqYrP/php.png" alt="5"/>
</p>

Com o banco de dados criado, clique em "SQL", digite o código a seguir e clique em "Executar".

```sql
CREATE TABLE banco (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    var1 VARCHAR(10),
    var2 VARCHAR(10),
    var3 VARCHAR(10),
    Leitura TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)
```

<p align="center">
  <img src="https://i.ibb.co/SfcB7L0/php2.png" alt="5"/>
</p>

Pronto! Agora a tabela com as variáveis está criada.

## Código do ESP32

```cpp
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
```

## Preparando a IDE do Arduino para utilizar o ESP32.
Em sua Arduino IDE vá em: Arquivo > Preferências

<p align="center">
  <img src="https://i.ibb.co/pfNTZ7p/preparando-1.png" alt="1"/>
</p>

Em "URLs Adicionais para Gerenciadores de Placas" escreva: https://dl.espressif.com/dl/package_esp32_index.json

Dê "OK" para salvar.

<p align="center">
  <img src="https://i.ibb.co/qydsfk8/esp32-preg.png" alt="1"/>
</p>

Vá em: Ferramentas > Placa > ESP32 Arduino > DOIT ESP32 DEVKIT v1

<p align="center">
  <img src="https://i.ibb.co/jMtdJjk/esp32222.png" alt="1"/>
</p>

Agora é só enviar o código!

## Conclusão
Esse tipo de projeto é bastante útil quando se utiliza o ESP32 em monitoramento. Também é possível usar esse projeto em um banco de dados que está hospedado em nuvem.

# Até mais!
<p align="center">
  <img src="https://i.ibb.co/4WmGpqx/sqlbanco.png" alt="5"/>
</p>
