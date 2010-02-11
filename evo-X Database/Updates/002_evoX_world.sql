INSERT INTO `areatrigger_teleport` VALUES ('5508', 'Trial of the Crusader (Exit)', '0', '0', '0', '0', '0', '0', '0', null, '571', '8515.46', '728.92', '558.3', '4.74206');
INSERT INTO `areatrigger_teleport` VALUES ('5503', 'Trial of the Crusader (Entrance)', '80', '0', '0', '0', '0', '0', '0', null, '649', '563.61', '80.6815', '395.139', '1.65937');
INSERT INTO `areatrigger_teleport` VALUES ('5505', 'Trial of the Champion (Entrance)', '75', '0', '0', '0', '0', '0', '0', null, '650', '805.227', '618.038', '412.393', '3.14569');
INSERT INTO `areatrigger_teleport` VALUES ('5510', 'Trial of the Champion (Exit)', '0', '0', '0', '0', '0', '0', '0', null, '571', '8577.4', '791.732', '558.235', '0');
INSERT INTO `areatrigger_teleport` VALUES ('5643', 'Pit of Saron (Exit)', '0', '0', '0', '0', '0', '0', '0', null, '571', '5595.92', '2013.02', '798.041', '0.648728');
INSERT INTO `areatrigger_teleport` VALUES ('5670', 'IceCrown Citadel (Entrance)', '80', '0', '0', '0', '0', '0', '0', null, '631', '76.8638', '2211.37', '30', '3.14965');
INSERT INTO `areatrigger_teleport` VALUES ('5636', 'Halls of Reflection (Entrance)', '75', '0', '0', '0', '0', '24712', '24712', 'You have to the quest, \"Deliverance from the Pit\" has been completed in order to enter the Halls of reflection to be able.', '668', '5239.01', '1932.64', '707.695', '0.800565');
INSERT INTO `areatrigger_teleport` VALUES ('5646', 'Halls of Reflection (Exit)', '0', '0', '0', '0', '0', '0', '0', null, '571', '5630.59', '1997.55', '798.049', '1.44042');
INSERT INTO `areatrigger_teleport` VALUES ('5642', 'Forge of Souls (Exit)', '0', '0', '0', '0', '0', '0', '0', null, '571', '5667.72', '2007.19', '798.042', '2.31535');
INSERT INTO `areatrigger_teleport` VALUES ('5635', 'Forge of Souls (Entrance)', '75', '0', '0', '0', '0', '0', '0', null, '632', '4922.86', '2175.63', '638.734', '2.00355');
INSERT INTO `areatrigger_teleport` VALUES ('5668', 'IceCrown Citadel (Exit)', '0', '0', '0', '0', '0', '0', '0', null, '571', '5790', '2071.48', '636.065', '0.459897');
INSERT INTO `areatrigger_teleport` VALUES ('5688', 'Forge of Souls (Exit) Pit of Saron (Entrance)', '0', '0', '0', '0', '0', '0', '0', '', '658', '435.743', '212.413', '528.709', '6.25646');
INSERT INTO `areatrigger_teleport` VALUES ('5637', 'Pit of Saron (Entrance)', '75', '0', '0', '0', '0', '24499', '24499', 'You have to the quest \"Echoes of Tortured Souls\" have been completed in order to be able to enter Pit of Sharon.', '658', '435.743', '212.413', '528.709', '6.25646');
INSERT INTO `areatrigger_teleport` VALUES ('5683', 'Pit of Saron (Exit) Halls of Reflection (Entrance)', '75', '0', '0', '0', '0', '0', '0', '', '668', '5239.01', '1932.64', '707.695', '0.800565');
INSERT INTO `areatrigger_teleport` VALUES ('5698', 'IceCrown Citadel Spire (Entrance)', '80', '0', '0', '0', '0', '0', '0', null, '631', '4138.76', '2769.25', '351', '0');
INSERT INTO `areatrigger_teleport` VALUES ('5700', 'IceCrown Citadel Spire (Exit)', '80', '0', '0', '0', '0', '0', '0', null, '631', '-482.01', '2211.44', '541.2', '3.14');

INSERT INTO `instance_template` VALUES ('650', '0', '75', '0', null, null, null, null, '');
INSERT INTO `instance_template` VALUES ('649', '0', '80', '0', null, null, null, null, '');
INSERT INTO `instance_template` VALUES ('668', '0', '75', '0', null, null, null, null, '');
INSERT INTO `instance_template` VALUES ('658', '0', '75', '0', null, null, null, null, '');
INSERT INTO `instance_template` VALUES ('631', '0', '80', '0', null, null, null, null, '');
INSERT INTO `instance_template` VALUES ('632', '0', '75', '0', null, null, null, null, '');


UPDATE db_version SET `cache_id`= '2';
UPDATE db_version SET `version`= 'evo-X 002 for evo-X 418 with SD2 SQL for rev. 1573';

