UPDATE `creature_template` SET `ScriptName` = 'boss_freya' WHERE `entry` =32906;
UPDATE `creature_template` SET `ScriptName` = 'npc_freya_death' WHERE `entry` =33241;
UPDATE `creature_template` SET `ScriptName` = 'npc_freya_help' WHERE `entry` =33410;
UPDATE `creature_template` SET `ScriptName` = 'boss_mimiron' WHERE `entry` =33350;
UPDATE `creature_template` SET `ScriptName` = 'npc_mimiron_death' WHERE `entry` =33244;
UPDATE `creature_template` SET `ScriptName` = 'npc_mimiron_help' WHERE `entry` =33412;
UPDATE `creature_template` SET `ScriptName` = 'boss_hodir' WHERE `entry` =32845;
UPDATE `creature_template` SET `ScriptName` = 'npc_hodir_death' WHERE `entry` =33213;
UPDATE `creature_template` SET `ScriptName` = 'npc_hodir_help' WHERE `entry` =33411;
UPDATE `creature_template` SET `ScriptName` = 'boss_thorim' WHERE `entry` =32865;
UPDATE `creature_template` SET `ScriptName` = 'npc_thorim_death' WHERE `entry` =33242;
UPDATE `creature_template` SET `ScriptName` = 'npc_thorim_help' WHERE `entry` =33413;
UPDATE `creature_template` SET `ScriptName` = 'npc_sanity_well' WHERE `entry` =33991;
UPDATE `creature_template` SET `ScriptName` = 'npc_sara' WHERE `entry` =33134;

UPDATE `creature_template` SET `npcflag` = '1' WHERE `entry` =33213;
UPDATE `creature_template` SET `npcflag` = '1' WHERE `entry` =33241;
UPDATE `creature_template` SET `npcflag` = '1' WHERE `entry` =33242;
UPDATE `creature_template` SET `npcflag` = '1' WHERE `entry` =33244;
UPDATE `creature_template` SET `faction_A` = '35' WHERE `entry` =33213;
UPDATE `creature_template` SET `faction_H` = '35' WHERE `entry` =33213;
UPDATE `creature_template` SET `faction_A` = '35' WHERE `entry` =33244;
UPDATE `creature_template` SET `faction_H` = '35' WHERE `entry` =33244;
UPDATE `creature_template` SET `faction_A` = '35' WHERE `entry` =33241;
UPDATE `creature_template` SET `faction_H` = '35' WHERE `entry` =33241;
UPDATE `creature_template` SET `faction_A` = '35' WHERE `entry` =33242;
UPDATE `creature_template` SET `faction_H` = '35' WHERE `entry` =33242;
UPDATE `creature_template` SET `faction_A` = '14' WHERE `entry` =33292;
UPDATE `creature_template` SET `faction_H` = '14' WHERE `entry` =33292;
UPDATE `creature_template` SET `faction_A` = '35' WHERE `entry` =33134;
UPDATE `creature_template` SET `faction_H` = '35' WHERE `entry` =33134;
UPDATE `creature_template` SET `faction_A` = '14' WHERE `entry` =33288;
UPDATE `creature_template` SET `faction_H` = '14' WHERE `entry` =33288;

UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33241;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33410;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33411;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33412;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 17319688, maxhealth = 17319688, minmana =0, maxmana =0, rank =3 where entry =33413;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33242;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33213;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 14433075, maxhealth = 14433075, minmana =0, maxmana =0, rank =3 where entry =33244;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 1394500 , maxhealth = 4183500, minmana = 234190, maxmana = 234190, rank =3 where entry =32906;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 1742400, maxhealth = 1742400, minmana =0, maxmana =0, rank =3 where entry =33350;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 8115990 , maxhealth = 32477904, minmana =0, maxmana =0, rank =3 where entry =32845;
UPDATE creature_template SET minlevel =83, maxlevel =83, minhealth = 4183500 , maxhealth = 14642250, minmana = 425800, maxmana = 425800, rank =3 where entry =32865;


