CREATE TABLE banco (
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    var1 VARCHAR(10),
    var2 VARCHAR(10),
    var3 VARCHAR(10),
    Leitura TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)