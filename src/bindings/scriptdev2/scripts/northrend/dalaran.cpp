/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Dalaran
SD%Complete: 100
SDComment:
SDCategory: Dalaran
EndScriptData */

/* ContentData
npc_zirdomi
EndContentData */

#include "precompiled.h"

/*######
## npc_zidormi
######*/

#define GOSSIP_ITEM_ZIDORMI1    "Take me to the Caverns of Time."

enum
{
    SPELL_TELEPORT_COT          = 46343,
    GOSSIP_TEXTID_ZIDORMI1      = 14066
};

bool GossipHello_npc_zidormi(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->getLevel() >= 65)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ZIDORMI1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ZIDORMI1, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_zidormi(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        pPlayer->CastSpell(pPlayer,SPELL_TELEPORT_COT,false);

    return true;
}

// Dalaran no fly zone - Credits go to hondacrx
bool AreaTrigger_at_no_fly_zone(Player* pPlayer, AreaTriggerEntry *pAt)
{
    if(pPlayer->IsFlying() == 0)// Check if the player is flying or not. Have not tested with druid yet.
    {
        return true;
    }
    else
    {
        pPlayer->PlayDirectSound(9417); // Fel Reaver sound
        pPlayer->CastSpell(pPlayer, 58600, true); //Restricted flight spell - needs to be a debuff
        pPlayer->MonsterTextEmote("Warning: You've entered a no-fly zone and are about to be dismounted!",pPlayer->GetGUID(),true);
        int32 fly_timer = 10;
        int32 diff;
        time_t curr = time(NULL);
        while(fly_timer > 0)
        {
            if(curr != time(NULL))
            {
                int32 diff = time(NULL) - curr;
                fly_timer -= diff;
                curr += diff;
            }
        }
                if(fly_timer < diff)
                {
                    pPlayer->CastSpell(pPlayer, 61286, true);  //World generic dismount spell - Not the right way but it works.
                    pPlayer->CastSpell(pPlayer, 45472, true);  //Slow fall
                    //pPlayer->RemoveAura(58600, true);  //no need to remove the buff as it has a Duration
                }
        return false;
    }
}  

void AddSC_dalaran()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_zidormi";
    newscript->pGossipHello = &GossipHello_npc_zidormi;
    newscript->pGossipSelect = &GossipSelect_npc_zidormi;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "at_no_fly_zone";
    newscript->pAreaTrigger = &AreaTrigger_at_no_fly_zone;
    newscript->RegisterSelf();  
}

/* INSERT INTO `areatrigger_scripts` VALUES (5283, at_no_fly_zone);   */
