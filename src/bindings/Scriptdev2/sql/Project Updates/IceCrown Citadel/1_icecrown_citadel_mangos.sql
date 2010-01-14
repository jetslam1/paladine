UPDATE `creature_template` SET `ScriptName` = 'boss_bronjahm' WHERE `entry` =36502 LIMIT 1 ;
UPDATE `creature_template` SET `ScriptName` = 'boss_devourer' WHERE `entry` =36502 LIMIT 1 ;
UPDATE `creature_template` SET `ScriptName` = 'npc_proudmoore' WHERE `entry` =37597 LIMIT 1 ;
UPDATE `creature_template` SET `ScriptName` = 'npc_windrunner' WHERE `entry` =37596 LIMIT 1 ;
UPDATE `creature_template` SET `ScriptName` = 'boss_lord_marrowgar' WHERE `entry` =36612 LIMIT 1 ;

UPDATE `creature_template` SET `npcflag` = '3' WHERE `entry` =37596 LIMIT 1 ;
UPDATE `creature_template` SET `npcflag` = '3' WHERE `entry` =37597 LIMIT 1 ;

UPDATE `instance_template` SET `script` = 'instance_icecrown_citadel' WHERE `map` =631 LIMIT 1 ;