COPY MENU
FROM '/extra/bmoya001/cs166/data/project/data/menu.csv'
WITH DELIMITER ';';

COPY USERS
FROM '/extra/bmoya001/cs166/data/project/data/users.csv'
WITH DELIMITER ';';

COPY ORDERS
FROM '/extra/bmoya001/cs166/data/project/data/orders.csv'
WITH DELIMITER ';';
ALTER SEQUENCE orders_orderid_seq RESTART 87257;

COPY ITEMSTATUS
FROM '/extra/bmoya001/cs166/data/project/data/itemStatus.csv'
WITH DELIMITER ';';

